// Decompile the Radical Red AI. Run through analyzeHeadless with -noanalysis on test/rr_gh.gba.
// Arguments: gh.json path, sigs.txt path, output folder. Reads a small JSON by hand so no extra jars are needed.
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.pcode.JumpTable;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.math.BigInteger;
import java.nio.file.*;
import java.util.*;

public class RRDecomp extends GhidraScript {
    Address A(long v) { return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(v); }

    // tiny JSON reader for the shape gh.json uses
    Object parse(StringBuilder s, int[] p) {
        while (Character.isWhitespace(s.charAt(p[0]))) p[0]++;
        char c = s.charAt(p[0]);
        if (c == '{') {
            Map<String, Object> m = new HashMap<>(); p[0]++;
            while (true) {
                while (Character.isWhitespace(s.charAt(p[0])) || s.charAt(p[0]) == ',') p[0]++;
                if (s.charAt(p[0]) == '}') { p[0]++; return m; }
                String k = (String) parse(s, p);
                while (s.charAt(p[0]) != ':') p[0]++;
                p[0]++;
                m.put(k, parse(s, p));
            }
        }
        if (c == '[') {
            List<Object> l = new ArrayList<>(); p[0]++;
            while (true) {
                while (Character.isWhitespace(s.charAt(p[0])) || s.charAt(p[0]) == ',') p[0]++;
                if (s.charAt(p[0]) == ']') { p[0]++; return l; }
                l.add(parse(s, p));
            }
        }
        if (c == '"') {
            int e = s.indexOf("\"", p[0] + 1);
            String v = s.substring(p[0] + 1, e); p[0] = e + 1; return v;
        }
        if (s.indexOf("null", p[0]) == p[0]) { p[0] += 4; return null; }
        int st = p[0];
        while (p[0] < s.length() && "-0123456789".indexOf(s.charAt(p[0])) >= 0) p[0]++;
        return Long.parseLong(s.substring(st, p[0]));
    }

    DataType typeOf(String t, Map<String, Structure> structs) {
        t = t.trim();
        java.util.regex.Matcher m = java.util.regex.Pattern.compile("^(.*)\\[(\\d+)\\]$").matcher(t);
        if (m.matches()) {
            // innermost dimension is the last one written
            String head = m.group(1);
            int n = Integer.parseInt(m.group(2));
            if (n == 0) return null;
            DataType inner = typeOf(head.replaceAll("\\[\\d+\\]$", ""), structs);
            java.util.List<Integer> dims = new ArrayList<>();
            java.util.regex.Matcher d = java.util.regex.Pattern.compile("\\[(\\d+)\\]").matcher(t);
            while (d.find()) dims.add(Integer.parseInt(d.group(1)));
            DataType base = typeOf(t.replaceAll("\\[\\d+\\]", ""), structs);
            if (base == null) return null;
            for (int i = dims.size() - 1; i >= 0; i--) { if (dims.get(i) == 0) return null; base = new ArrayDataType(base, dims.get(i), base.getLength()); }
            return base;
        }
        if (t.endsWith("*")) {
            DataType in = typeOf(t.substring(0, t.length() - 1), structs);
            return new PointerDataType(in == null ? VoidDataType.dataType : in, 4);
        }
        if (t.startsWith("struct ")) return structs.get(t.substring(7).trim());
        switch (t) {
            case "u8": case "bool8": return ByteDataType.dataType;
            case "s8": return SignedByteDataType.dataType;
            case "u16": case "bool16": return UnsignedShortDataType.dataType;
            case "s16": return ShortDataType.dataType;
            case "u32": case "bool32": return UnsignedIntegerDataType.dataType;
            case "s32": return IntegerDataType.dataType;
            case "u64": return UnsignedLongLongDataType.dataType;
            case "void": return VoidDataType.dataType;
        }
        return ByteDataType.dataType;
    }

    @SuppressWarnings("unchecked")
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        Map<String, Object> gh = (Map<String, Object>) parse(new StringBuilder(new String(Files.readAllBytes(Paths.get(args[0])))), new int[]{0});
        Path sigFile = Paths.get(args[1]);
        Path outDir = Paths.get(args[2]);
        Files.createDirectories(outDir);
        Memory mem = currentProgram.getMemory();
        int tx = currentProgram.startTransaction("setup");
        // RAM so pointers resolve
        try { mem.createUninitializedBlock("EWRAM", A(0x2000000L), 0x40000, false); } catch (Exception e) { println("ewram " + e); }
        try { mem.createUninitializedBlock("IWRAM", A(0x3000000L), 0x8000, false); } catch (Exception e) { println("iwram " + e); }
        mem.getBlock(A(0x8000000L)).setWrite(false);
        // all code is Thumb
        Register tm = currentProgram.getRegister("TMode");
        currentProgram.getProgramContext().setValue(tm, A(0x8000000L), A(0x8000000L + mem.getBlock(A(0x8000000L)).getSize() - 1), BigInteger.ONE);
        // types
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        String[][] td = {{"u8", "b"}, {"bool8", "b"}, {"s8", "c"}, {"u16", "h"}, {"move_t", "h"}, {"item_t", "h"}, {"species_t", "h"}, {"ability_t", "b"}, {"bool16", "h"}, {"s16", "s"}, {"u32", "i"}, {"s32", "l"}, {"bool32", "i"}};
        for (String[] t : td) {
            DataType base = t[1].equals("b") ? ByteDataType.dataType : t[1].equals("c") ? SignedByteDataType.dataType : t[1].equals("h") ? UnsignedShortDataType.dataType : t[1].equals("s") ? ShortDataType.dataType : t[1].equals("i") ? UnsignedIntegerDataType.dataType : IntegerDataType.dataType;
            dtm.addDataType(new TypedefDataType(t[0], base), DataTypeConflictHandler.REPLACE_HANDLER);
        }
        // structs
        Map<String, Structure> structs = new HashMap<>();
        Path typeFile = Paths.get(args[0]).getParent().resolve("types.txt");
        List<String> tl = Files.readAllLines(typeFile);
        for (String l : tl) {
            String[] x = l.split("\\t");
            if (x[0].equals("S") && Integer.parseInt(x[2]) > 0 && !structs.containsKey(x[1])) {
                structs.put(x[1], (Structure) dtm.addDataType(new StructureDataType(x[1], Integer.parseInt(x[2])), DataTypeConflictHandler.REPLACE_HANDLER));
            }
        }
        Structure curS = null;
        for (String l : tl) {
            String[] x = l.split("\\t");
            if (x[0].equals("S")) { curS = structs.get(x[1]); continue; }
            if (curS == null) continue;
            try {
                DataType ft = typeOf(x[2], structs);
                if (ft != null && ft.getLength() > 0) curS.replaceAtOffset(Integer.parseInt(x[1]), ft, ft.getLength(), x[3], null);
            } catch (Exception ex) { }
        }
        // labels
        Map<String, String> labels = (Map<String, String>) (Map<?, ?>) gh.get("labels");
        for (Map.Entry<String, String> e : labels.entrySet()) {
            try {
                long v = Long.decode(e.getKey());
                createLabel(A(v & ~1L), e.getValue(), true);
            } catch (Exception ex) { }
        }
        // typed globals
        Object[][] globals = {{0x203E038L, "gNewBS", "u32"}, {0x2023FE8L, "gBattleStruct", "struct BattleStruct*"}, {0x2023FF4L, "gBattleResources", "struct BattleResources*"},
            {0x2023BE4L, "gBattleMons", "struct BattlePokemon[4]"}, {0x2023E0CL, "gDisableStructs", "struct DisableStruct[4]"}, {0x2023DE4L, "gSideTimers", "struct SideTimer[2]"},
            {0x2023DFCL, "gStatuses3", "u32[4]"}, {0x2023BCEL, "gBattlerPartyIndexes", "u16[4]"}, {0x2023DC4L, "gChosenMovesByBanks", "u16[4]"}, {0x2023D98L, "gLastUsedMoves", "u16[4]"},
            {0x2023DA0L, "gLastLandedMoves", "u16[4]"}, {0x2023DB8L, "gLockedMoves", "u16[4]"}, {0x2023DDEL, "gSideStatuses", "u16[2]"}, {0x2023D7CL, "gChosenActionByBank", "u8[4]"},
            {0x2024284L, "gPlayerParty", "struct Pokemon[6]"}, {0x202402CL, "gEnemyParty", "struct Pokemon[6]"}, {0x91521D0L, "gBattleMoves", "struct BattleMove[1006]"}};
        for (Object[] x : globals) {
            try {
                createLabel(A((Long) x[0]), (String) x[1], true);
                DataType dt = typeOf((String) x[2], structs);
                clearListing(A((Long) x[0]), A((Long) x[0] + dt.getLength() - 1));
                createData(A((Long) x[0]), dt);
            } catch (Exception ex) { println("global " + x[1] + " " + ex); }
        }
        // code
        List<Object> funcs = (List<Object>) gh.get("functions");
        AddressSet codeSet = new AddressSet();
        for (Object o : funcs) {
            for (Object r : (List<Object>) ((Map<String, Object>) o).get("ranges")) {
                List<Object> rr = (List<Object>) r;
                codeSet.addRange(A((Long) rr.get(0)), A((Long) rr.get(1) - 1));
            }
        }
        // the stubs and helpers outside the AI ranges
        List<Object> thunks = (List<Object>) gh.get("thunks");
        for (Object t : thunks) codeSet.addRange(A((Long) t), A((Long) t + 1));
        DisassembleCommand dc = new DisassembleCommand(codeSet, codeSet, true);
        dc.enableCodeAnalysis(false);
        dc.applyTo(currentProgram, monitor);
        println("instructions " + currentProgram.getListing().getNumInstructions());
        // stubs: call and return through the register, inlined into callers
        for (Object t : thunks) {
            Address a = A((Long) t);
            Instruction i = getInstructionAt(a);
            if (i == null) continue;
            i.setFlowOverride(FlowOverride.CALL_RETURN);
            Function fn = createFunction(a, "stub_" + Long.toHexString((Long) t));
            if (fn != null) fn.setInline(true);
        }
        // long jumps written as bl
        for (Object j : (List<Object>) gh.get("longjumps")) {
            Instruction i = getInstructionAt(A((Long) j));
            if (i != null) i.setFlowOverride(FlowOverride.BRANCH);
        }
        // switch tables
        for (Object s : (List<Object>) gh.get("switches")) {
            Map<String, Object> sw = (Map<String, Object>) s;
            Instruction i = getInstructionAt(A((Long) sw.get("addr")));
            if (i == null) continue;
            for (Object t : new LinkedHashSet<Object>((List<Object>) sw.get("targets"))) {
                i.addOperandReference(0, A((Long) t), RefType.COMPUTED_JUMP, SourceType.USER_DEFINED);
            }
        }
        // functions
        Map<Long, Function> made = new LinkedHashMap<>();
        for (Object o : funcs) {
            Map<String, Object> m = (Map<String, Object>) o;
            long a = (Long) m.get("addr");
            String name = (String) m.get("name");
            if (name == null) name = "sub_" + Long.toHexString(a);
            removeFunctionAt(A(a));
            try {
                CreateFunctionCmd c = new CreateFunctionCmd(name, A(a), null, SourceType.USER_DEFINED);
                c.applyTo(currentProgram, monitor);
                Function fn = getFunctionAt(A(a));
                if (fn != null) made.put(a, fn);
            } catch (Exception ex) { println("func " + name + " " + ex); }
        }
        println("functions " + made.size());
        // jump tables
        Map<Long, Function> byAddr = made;
        int jt = 0;
        for (Object s : (List<Object>) gh.get("switches")) {
            Map<String, Object> sw = (Map<String, Object>) s;
            Address op = A((Long) sw.get("addr"));
            Function fn = getFunctionContaining(op);
            if (fn == null) continue;
            ArrayList<Address> dest = new ArrayList<>();
            for (Object t : (List<Object>) sw.get("targets")) dest.add(A((Long) t));
            new JumpTable(op, dest, true, 0).writeOverride(fn);
            jt++;
        }
        println("jump tables " + jt);
        for (Function fn : made.values()) CreateFunctionCmd.fixupFunctionBody(currentProgram, fn, monitor);
        // signatures from the source, where they parse
        int okSig = 0, badSig = 0;
        if (Files.exists(sigFile)) {
            for (String line : Files.readAllLines(sigFile)) {
                String[] p = line.split("\\t", 2);
                if (p.length < 2) continue;
                SymbolIterator it = currentProgram.getSymbolTable().getSymbols(p[0]);
                while (it.hasNext()) {
                    Symbol sym = it.next();
                    Function fn = getFunctionAt(sym.getAddress());
                    if (fn == null) continue;
                    try {
                        FunctionDefinitionDataType sig = CParserUtils.parseSignature((ghidra.app.services.DataTypeManagerService) null, currentProgram, p[1], false);
                        if (sig != null) {
                            new ApplyFunctionSignatureCmd(fn.getEntryPoint(), sig, SourceType.USER_DEFINED).applyTo(currentProgram, monitor);
                            okSig++;
                        }
                    } catch (Exception ex) { badSig++; }
                }
            }
        }
        println("signatures ok " + okSig + " bad " + badSig);
        for (Object o : (List<Object>) gh.get("sites")) {
            List<Object> l = (List<Object>) o;
            setPreComment(A((Long) l.get(0)), "TARGET " + l.get(1));
        }
        currentProgram.endTransaction(tx, true);
        // decompile
        DecompInterface d = new DecompInterface();
        DecompileOptions opt = new DecompileOptions();
        opt.setPRECommentIncluded(true);
        d.setOptions(opt);
        d.toggleCCode(true);
        d.toggleSyntaxTree(true);
        d.setSimplificationStyle("decompile");
        d.openProgram(currentProgram);
        PrintWriter index = new PrintWriter(outDir.resolve("index.tsv").toFile());
        int done = 0, fail = 0;
        for (Map.Entry<Long, Function> e : made.entrySet()) {
            Function fn = e.getValue();
            DecompileResults r = d.decompileFunction(fn, 300, monitor);
            String name = fn.getName();
            String body;
            if (r != null && r.decompileCompleted()) {
                body = r.getDecompiledFunction().getC();
                done++;
            } else {
                body = "// DECOMPILE FAILED " + (r == null ? "" : r.getErrorMessage());
                fail++;
            }
            Files.write(outDir.resolve(name.replaceAll("[^A-Za-z0-9_]", "_") + ".c"), ("// ROM " + Long.toHexString(e.getKey()) + "\n" + body).getBytes());
            index.println(Long.toHexString(e.getKey()) + "\t" + name + "\t" + fn.getBody().getNumAddresses());
        }
        index.close();
        println("decompiled " + done + " failed " + fail);
    }
}
