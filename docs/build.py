#!/usr/bin/env python3
"""Build the Radical Red AI doc: doc.txt -> radical_red_ai.html (page content, the host adds the document shell).

Markup in doc.txt:
  #! title, # section, ## subsection, |a|b table rows (first row is the header),
  #details Title ... #end  a closed section, > tip  a callout, @@doubles  the doubles picture guide.
"""
import html, os, re

HERE = os.path.dirname(os.path.abspath(__file__))
text = open(os.path.join(HERE, 'doc.txt')).read()
# chance label: "+3 (50%)" reads "+3 (50%), no score change other 50%"
text = re.sub(r'^(\s*)([+-]\d+) \((\d+)%\)$',
              lambda m: f'{m.group(1)}{m.group(2)} ({m.group(3)}%), no score change other {100 - int(m.group(3))}%', text, flags=re.M)
E = html.escape

# Doubles picture guide. Each card is one tested situation: who the AI aims at, and how often.
# arrows: (target, percent[, label]). Percent 0 draws a dashed "never" line.
DOUBLES = [
    dict(t='One foe is in KO range', ai='Attacking style',
         L='In KO range', R='Weak to its move, not in KO range', arrows=[('L', 100)],
         cap='It always takes the KO, even when the other foe is weak to its move.', test='Tested 60 of 60'),
    dict(t='Both in KO range, one can KO the AI', ai='Attacking style',
         L='In KO range', R='In KO range, can KO the AI', arrows=[('R', 100)],
         cap='It removes the bigger threat first.', test='Tested 60 of 60'),
    dict(t='Both in KO range, nothing else different', ai='Attacking style',
         L='In KO range', R='In KO range', arrows=[('L', 50), ('R', 50)],
         cap='A coin flip. A Mega or Dynamaxed foe would be picked first.', test='Tested 57 to 43'),
    dict(t='No KO, both lose half, one can KO the AI', ai='Attacking style',
         L='Loses half its HP or more', R='Loses half its HP or more, can KO the AI', arrows=[('R', 100)],
         cap='Big hits on both: it goes for the one that threatens it.', test='Tested 160 of 160'),
    dict(t='No KO: more damage, sometimes', ai='Attacking style',
         L='Loses 30% of max HP', R='Loses 15% of max HP', arrows=[('L', 63), ('R', 37)],
         cap='25% of the time it goes for the bigger share of max HP. Otherwise it flips a coin.', test='Tested 154 of 240'),
    dict(t="Super effective doesn't pull the arrow", ai='Attacking style',
         L='Weak to its move but bulky, loses 8%', R='Neutral, loses 15%', arrows=[('L', 37), ('R', 63)],
         cap="Only damage counts. The bulky foe that is weak to the move gets picked less.", test='Tested 151 of 240'),
    dict(t='Support styles flip a coin', ai='Utility, Phazer, Team Support',
         L='In KO range', R='Not in KO range', arrows=[('L', 50), ('R', 50)],
         cap="For these styles a KO scores the same as a normal hit, so it doesn't chase it.", test='Tested 83 to 77'),
    dict(t='A foe that is immune', ai='Any style',
         L='Immune to all its attacks', R='Can be hit', arrows=[('L', 0), ('R', 100)],
         cap='It never aims an attack at a foe it can\'t hurt.', test='Tested 48 of 48'),
    dict(t='Its partner already has a KO', ai='Attacking style', partner='Picks first',
         L="Partner's move KOs it", R='Healthy', arrows=[('R', 100)], partner_arrow=('L', 'KO'),
         cap='It treats a foe its partner is already KOing as handled.', test='Tested 60 of 60'),
    dict(t='Spread move beats a single KO', ai='Attacking style',
         L='In KO range of a single target move', R='Healthy', arrows=[('L', 100, 'Heat Wave'), ('R', 100, 'Heat Wave')],
         cap="A spread move doing 1/3 of each foe's max HP or more beats a single target KO. Under 1/3 each, it uses a single target move.",
         test='Tested 60 of 60, both ways'),
    dict(t='It will hit its own partner', ai='Attacking style', partner='Gets hit',
         L='Healthy', R='Healthy', arrows=[('L', 100, 'Earthquake'), ('R', 100, 'Earthquake')], partner_hit=True,
         cap='Hitting its partner is only -3 to the level. It picked Earthquake even when that would KO its own partner.',
         test='Tested 40 of 40'),
]


def wrap(s, n):
    out, cur = [], ''
    for w in s.split():
        if cur and len(cur) + 1 + len(w) > n:
            out.append(cur)
            cur = w
        else:
            cur = (cur + ' ' + w).strip()
    return out + [cur] if cur else out


def box(x, y, w, h, title, sub, cls, n=22):
    lines = wrap(sub, n)[:2]
    t = [f'<rect class="{cls}" x="{x - w / 2:.0f}" y="{y}" width="{w}" height="{h}" rx="6"/>',
         f'<text class="bt" x="{x}" y="{y + 15}" text-anchor="middle">{E(title)}</text>']
    for i, ln in enumerate(lines):
        t.append(f'<text class="bs" x="{x}" y="{y + 28 + 11 * i}" text-anchor="middle">{E(ln)}</text>')
    return ''.join(t)


def arrow(x0, y0, x1, y1, cls, width, label):
    dx, dy = x1 - x0, y1 - y0
    d = (dx * dx + dy * dy) ** .5
    ux, uy = dx / d, dy / d
    hl = 6 + width * 1.2  # head length
    bx, by = x1 - ux * hl, y1 - uy * hl
    px, py = -uy * (hl * .6), ux * (hl * .6)
    dash = ' stroke-dasharray="5 4"' if cls == 'no' else ''
    s = [f'<line class="ln {cls}" x1="{x0:.1f}" y1="{y0:.1f}" x2="{bx:.1f}" y2="{by:.1f}" stroke-width="{width:.1f}"{dash}/>']
    if cls != 'no':
        s.append(f'<polygon class="hd {cls}" points="{x1:.1f},{y1:.1f} {bx + px:.1f},{by + py:.1f} {bx - px:.1f},{by - py:.1f}"/>')
    if label:
        mx, my = x0 + dx * .5, y0 + dy * .5
        lw = 8 + 6.2 * len(label)
        s.append(f'<rect class="pill" x="{mx - lw / 2:.1f}" y="{my - 9:.1f}" width="{lw:.1f}" height="18" rx="9"/>'
                 f'<text class="pl {cls}" x="{mx:.1f}" y="{my + 4:.1f}" text-anchor="middle">{E(label)}</text>')
    return ''.join(s)


def card(c):
    you = {'L': 76, 'R': 224}
    yb, ab = 138, 10  # top of your boxes, top of the AI row
    two = 'partner' in c
    ax = 220 if two else 150
    g = []
    if two:
        g.append(box(80, ab, 112, 40, 'AI partner', c['partner'], 'pbox'))
    g.append(box(ax, ab, 112 if two else 132, 40, 'AI', c['ai'], 'abox', 24))
    g.append(box(you['L'], yb, 130, 50, 'Your left', c['L'], 'ybox'))
    g.append(box(you['R'], yb, 130, 50, 'Your right', c['R'], 'ybox'))
    if c.get('partner_arrow'):
        tgt, lab = c['partner_arrow']
        g.append(arrow(80, ab + 42, you[tgt] - 12, yb - 2, 'pt', 2, lab))
    if c.get('partner_hit'):
        g.append(arrow(ax - 58, ab + 20, 80 + 58, ab + 20, 'hit', 2, '-3'))
    for a in c['arrows']:
        tgt, pct = a[0], a[1]
        label = a[2] if len(a) > 2 else f'{pct}%'
        cls = 'no' if pct == 0 else ('go' if pct >= 50 else 'lo')
        width = 1.5 if pct == 0 else 1.5 + pct / 25
        x1 = you[tgt] + (8 if tgt == 'L' and ax > 150 else 0)
        if label == '0%':
            label = 'never'
        g.append(arrow(ax + (-14 if tgt == 'L' else 14), ab + 42, x1, yb - 2, cls, width, label))
    desc = f"{c['t']}. {c['cap']}"
    return (f'<figure class="dcard"><figcaption>{E(c["t"])}</figcaption>'
            f'<svg viewBox="0 0 300 196" role="img" aria-label="{E(desc)}">{"".join(g)}</svg>'
            f'<p class="dcap">{E(c["cap"])}</p><p class="dtest">{E(c["test"])}</p></figure>')


CSS = """
/* layout: a plain reading column with a sticky outline beside it */
:root{--bg:#f1f3f4;--page:#fff;--ink:#202124;--soft:#5f6368;--line:#dadce0;--hl:#fff3b0;--hover:#f1f3f4;--head:#e8eaed;--accent:#1a5fd0;--lo:#8d96a3;--warn:#c2410c;--tip:#eef3fd;--card:#f8f9fb}
@media (prefers-color-scheme:dark){:root:not([data-theme="light"]){--bg:#121417;--page:#1b1e23;--ink:#e6e8eb;--soft:#9aa0a6;--line:#30343a;--hl:#5a4b00;--hover:#262a30;--head:#262a30;--accent:#7eaaff;--lo:#79818c;--warn:#fb923c;--tip:#1f2a3d;--card:#22262c;color-scheme:dark}}
:root[data-theme="dark"]{--bg:#121417;--page:#1b1e23;--ink:#e6e8eb;--soft:#9aa0a6;--line:#30343a;--hl:#5a4b00;--hover:#262a30;--head:#262a30;--accent:#7eaaff;--lo:#79818c;--warn:#fb923c;--tip:#1f2a3d;--card:#22262c;color-scheme:dark}
*{box-sizing:border-box}html{scroll-behavior:smooth;scroll-padding-top:16px}
body{margin:0;background:var(--bg);color:var(--ink);font:15px/1.5 Arial,Helvetica,sans-serif}
.wrap{display:flex;justify-content:center;gap:24px;align-items:flex-start;padding-block:24px;padding-left:max(16px,env(safe-area-inset-left,0px));padding-right:max(16px,env(safe-area-inset-right,0px))}
nav{position:sticky;top:16px;width:250px;max-height:calc(100vh - 32px);overflow:auto;font-size:13px;flex:none}
nav a{display:block;color:var(--soft);text-decoration:none;padding:3px 8px;border-radius:4px;line-height:1.35}
nav a:hover,nav a:focus-visible{color:var(--ink);background:var(--line)}nav a.sub{padding-left:20px;font-size:12px}
nav .tools{display:flex;gap:8px;margin-bottom:10px}
input{flex:1;min-width:0;padding:6px 8px;border:1px solid var(--line);border-radius:4px;background:var(--page);color:var(--ink);font-size:13px}
button{padding:6px 10px;border:1px solid var(--line);border-radius:4px;background:var(--page);color:var(--ink);font-size:12px;cursor:pointer}
main{background:var(--page);width:100%;max-width:860px;min-width:0;padding:56px 64px;border:1px solid var(--line);box-shadow:0 1px 3px rgba(0,0,0,.08)}
h1{font-size:27px;font-weight:400;margin:0 0 14px;text-wrap:balance}
h2{font-size:17px;font-weight:700;margin:30px 0 8px;padding-top:12px;border-top:1px solid var(--line);text-wrap:balance}
h3{font-size:15px;font-weight:700;margin:22px 0 6px;text-wrap:balance}
p{margin:0 0 10px;max-width:68ch}
.l{margin:0;overflow-wrap:anywhere}
.row{display:flex;flex-wrap:wrap;justify-content:space-between;gap:0 16px;max-width:680px}.row:hover{background:var(--hover)}.row span{flex:1 1 200px;min-width:0}.row b{flex:0 1 auto;margin-left:auto;font-weight:600;font-variant-numeric:tabular-nums;text-align:right}
.sc{display:grid;grid-template-columns:5.6em 1fr;gap:0 6px;max-width:680px}.sc b{font-weight:600;font-variant-numeric:tabular-nums}.sc:hover{background:var(--hover)}
.tip{background:var(--tip);border-left:3px solid var(--accent);padding:10px 14px;border-radius:0 6px 6px 0;max-width:68ch}
.tw{overflow-x:auto;margin:8px 0 12px}
table{border-collapse:collapse;font-size:12.5px;font-variant-numeric:tabular-nums}
th,td{border:1px solid var(--line);padding:4px 6px;text-align:center}
th{background:var(--head);font-weight:600}
td:first-child,th:first-child{text-align:left;min-width:150px}
tr:hover td{background:var(--hover)}
.hit{background:var(--hl)}
.gap{height:8px}
details{border:1px solid var(--line);border-radius:6px;margin:8px 0;padding:0 14px;background:var(--page)}
details[open]{padding-bottom:10px}
summary{cursor:pointer;font-weight:700;padding:10px 0;list-style-position:inside}
summary:focus-visible{outline:2px solid var(--accent);outline-offset:2px}
.dgrid{display:grid;grid-template-columns:repeat(auto-fill,minmax(min(250px,100%),1fr));gap:14px;margin:12px 0 16px}
.dcard{margin:0;border:1px solid var(--line);border-radius:8px;background:var(--card);padding:12px 12px 10px;display:flex;flex-direction:column;min-width:0}
.dcard figcaption{font-weight:700;font-size:14px;margin-bottom:4px;text-wrap:balance}
.dcard svg{width:100%;height:auto;display:block}
.dcap{font-size:13px;margin:6px 0 4px;color:var(--ink)}.dtest{font-size:12px;color:var(--soft);margin:auto 0 0}
.abox{fill:var(--page);stroke:var(--accent);stroke-width:1.5}.pbox{fill:var(--page);stroke:var(--lo);stroke-width:1;stroke-dasharray:4 3}
.ybox{fill:var(--page);stroke:var(--line);stroke-width:1.5}
.bt{fill:var(--ink);font:700 11.5px Arial,Helvetica,sans-serif}.bs{fill:var(--soft);font:10px Arial,Helvetica,sans-serif}
.ln{fill:none;stroke-linecap:round}.ln.go{stroke:var(--accent)}.ln.lo{stroke:var(--lo)}.ln.no{stroke:var(--lo)}.ln.pt{stroke:var(--lo)}.ln.hit{stroke:var(--warn)}
.hd.go{fill:var(--accent)}.hd.lo,.hd.pt{fill:var(--lo)}.hd.hit{fill:var(--warn)}
.pill{fill:var(--card);stroke:var(--line)}
.pl{font:700 11px Arial,Helvetica,sans-serif;fill:var(--ink)}.pl.go{fill:var(--accent)}.pl.hit{fill:var(--warn)}.pl.no,.pl.lo,.pl.pt{fill:var(--soft)}
@media(max-width:1000px){.wrap{display:block}nav{position:static;width:auto;max-height:260px;margin-bottom:16px;background:var(--page);border:1px solid var(--line);padding:10px}main{padding:28px 20px}}
@media(prefers-reduced-motion:reduce){html{scroll-behavior:auto}}
"""

JS = """
(function(){var r=document.documentElement,b=document.getElementById('theme'),k='rr-ai-theme';
function dark(){var t=r.getAttribute('data-theme');return t?t==='dark':window.matchMedia('(prefers-color-scheme: dark)').matches}
function label(){b.textContent=dark()?'Light':'Dark'}
var saved=null;try{saved=localStorage.getItem(k)}catch(e){}
if(saved)r.setAttribute('data-theme',saved);label();
b.onclick=function(){var t=dark()?'light':'dark';r.setAttribute('data-theme',t);label();try{localStorage.setItem(k,t)}catch(e){}};
function reveal(e){for(var p=e;p;p=p.parentElement){if(p.tagName==='DETAILS')p.open=true}}
document.querySelectorAll('nav a').forEach(function(a){a.addEventListener('click',function(){var t=document.getElementById(a.getAttribute('href').slice(1));if(t)reveal(t)})});
var q=document.getElementById('q'),rows=[].slice.call(document.querySelectorAll('main .l,main p,main h2,main h3,main tr,main figure,main summary'));
q.oninput=function(){var v=q.value.trim().toLowerCase(),first=null;
 rows.forEach(function(e){var on=v&&e.textContent.toLowerCase().indexOf(v)>-1;e.classList.toggle('hit',!!on);if(on&&!first)first=e});
 if(first){reveal(first);first.scrollIntoView({block:'center'})}};
})();
"""

body, nav, n, table = [], [], 0, []


def flush():
    global table
    if not table:
        return
    out = ['<div class="tw"><table>']
    for i, row in enumerate(table):
        tag = 'th' if i == 0 else 'td'
        out.append('<tr>' + ''.join(f'<{tag}>{E(c)}</{tag}>' for c in row) + '</tr>')
    out.append('</table></div>')
    body.append(''.join(out))
    table = []


for raw in text.split('\n'):
    line = raw.rstrip()
    if line.startswith('|'):
        table.append(line[1:].split('|'))
        continue
    flush()
    if line.startswith('#! '):
        body.append(f'<h1>{E(line[3:])}</h1>')
    elif line.startswith('#details '):
        n += 1
        t = line[len('#details '):]
        body.append(f'<details id="s{n}"><summary>{E(t)}</summary>')
        nav.append(f'<a href="#s{n}" class="sub">{E(t)}</a>')
    elif line == '#end':
        body.append('</details>')
    elif line == '@@doubles':
        body.append('<div class="dgrid">' + ''.join(card(c) for c in DOUBLES) + '</div>')
    elif line.startswith('> '):
        body.append(f'<p class="tip">{E(line[2:])}</p>')
    elif line.startswith('## ') or line.startswith('# '):
        lvl = 3 if line.startswith('## ') else 2
        t = line.lstrip('# ').rstrip(':')
        n += 1
        body.append(f'<h{lvl} id="s{n}">{E(line.lstrip("# "))}</h{lvl}>')
        nav.append(f'<a href="#s{n}"{" class=sub" if lvl == 3 else ""}>{E(t)}</a>')
    elif not line:
        if body and not body[-1].startswith('<div class="gap"'):
            body.append('<div class="gap"></div>')
    elif not line.startswith(' '):
        m = re.match(r'(.*\S):  (\S.*)$', line)
        if m and len(m.group(2)) <= 30:  # "situation:  score" lines line up as two columns
            body.append(f'<div class="l row"><span>{E(m.group(1))}:</span><b>{E(m.group(2))}</b></div>')
        else:
            body.append(f'<p>{E(line)}</p>')
    else:
        indent = (len(line) - len(line.lstrip())) // 4
        s = line.strip()
        parts = re.split(r'\s{2,}', s)
        pad = f'padding-left:{indent * 1.6}em'
        sc = re.match(r'([+-]?\d+(?: to [+-]?\d+)?):\s+(.*)$', s)
        if sc:
            body.append(f'<div class="l sc" style="{pad}"><b>{E(sc.group(1))}</b><span>{E(sc.group(2))}</span></div>')
        elif len(parts) >= 2 and len(parts[-1]) <= 30:
            body.append(f'<div class="l row" style="{pad}"><span>{E(" ".join(parts[:-1]))}</span><b>{E(parts[-1])}</b></div>')
        else:
            body.append(f'<div class="l" style="{pad}">{E(" ".join(parts))}</div>')
flush()

page = f"""<title>Radical Red AI Doc</title>
<meta name="claude:viewport-fit-sides" content="cover">
<style>{CSS}</style>
<div class="wrap"><nav aria-label="Sections"><div class="tools"><input id="q" placeholder="Search" aria-label="Search the doc"><button id="theme" type="button">Dark</button></div>{''.join(nav)}</nav>
<main>{''.join(body)}</main></div><script>{JS}</script>
"""
open(os.path.join(HERE, 'radical_red_ai.html'), 'w').write(page)
print('built', len(text.splitlines()), 'lines,', len(nav), 'sections,', len(DOUBLES), 'pictures,', len(page) // 1024, 'KB')
