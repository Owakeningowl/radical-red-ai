#!/usr/bin/env python3
"""Build the Radical Red AI doc: doc.txt -> radical_red_ai.html (page content, the host adds the document shell)."""
import html, os, re

HERE = os.path.dirname(os.path.abspath(__file__))
text = open(os.path.join(HERE, 'doc.txt')).read()
# chance label: "+3 (50%)" reads "+3 (50%), no score change other 50%"
text = re.sub(r'^(\s*)([+-]\d+) \((\d+)%\)$',
              lambda m: f'{m.group(1)}{m.group(2)} ({m.group(3)}%), no score change other {100 - int(m.group(3))}%', text, flags=re.M)

CSS = """
/* layout: a plain reading column with a sticky outline beside it */
:root{--bg:#f1f3f4;--page:#fff;--ink:#202124;--soft:#5f6368;--line:#dadce0;--hl:#fff3b0;--hover:#f1f3f4;--head:#e8eaed}
@media (prefers-color-scheme:dark){:root:not([data-theme="light"]){--bg:#121417;--page:#1b1e23;--ink:#e6e8eb;--soft:#9aa0a6;--line:#30343a;--hl:#5a4b00;--hover:#262a30;--head:#262a30;color-scheme:dark}}
:root[data-theme="dark"]{--bg:#121417;--page:#1b1e23;--ink:#e6e8eb;--soft:#9aa0a6;--line:#30343a;--hl:#5a4b00;--hover:#262a30;--head:#262a30;color-scheme:dark}
*{box-sizing:border-box}html{scroll-behavior:smooth;scroll-padding-top:16px}
body{margin:0;background:var(--bg);color:var(--ink);font:15px/1.5 Arial,Helvetica,sans-serif}
.wrap{display:flex;justify-content:center;gap:24px;align-items:flex-start;padding-block:24px;padding-left:max(16px,env(safe-area-inset-left,0px));padding-right:max(16px,env(safe-area-inset-right,0px))}
nav{position:sticky;top:16px;width:250px;max-height:calc(100vh - 32px);overflow:auto;font-size:13px;flex:none}
nav a{display:block;color:var(--soft);text-decoration:none;padding:3px 8px;border-radius:4px;line-height:1.35}
nav a:hover,nav a:focus-visible{color:var(--ink);background:var(--line)}nav a.sub{padding-left:20px;font-size:12px}
nav .tools{display:flex;gap:8px;margin-bottom:10px}
input{flex:1;min-width:0;padding:6px 8px;border:1px solid var(--line);border-radius:4px;background:var(--page);color:var(--ink);font-size:13px}
button{padding:6px 10px;border:1px solid var(--line);border-radius:4px;background:var(--page);color:var(--ink);font-size:12px;cursor:pointer}
main{background:var(--page);width:100%;max-width:816px;min-width:0;padding:56px 64px;border:1px solid var(--line);box-shadow:0 1px 3px rgba(0,0,0,.08)}
h1{font-size:27px;font-weight:400;margin:0 0 14px;text-wrap:balance}
h2{font-size:17px;font-weight:700;margin:30px 0 8px;padding-top:12px;border-top:1px solid var(--line);text-wrap:balance}
h3{font-size:15px;font-weight:700;margin:22px 0 6px;text-wrap:balance}
p{margin:0 0 10px;max-width:68ch}
.l{margin:0;overflow-wrap:anywhere}
.row{display:flex;flex-wrap:wrap;justify-content:space-between;gap:0 16px;max-width:640px}.row:hover{background:var(--hover)}.row span{flex:1 1 200px;min-width:0}.row b{flex:0 0 auto;margin-left:auto;font-weight:600;font-variant-numeric:tabular-nums}
.sc{display:grid;grid-template-columns:2.8em 1fr}.sc b{font-weight:600;font-variant-numeric:tabular-nums}
.tw{overflow-x:auto;margin:8px 0 12px}
table{border-collapse:collapse;font-size:12.5px;font-variant-numeric:tabular-nums}
th,td{border:1px solid var(--line);padding:4px 5px;text-align:center}
th{background:var(--head);font-weight:600}
td:first-child,th:first-child{text-align:left;min-width:150px}
tr:hover td{background:var(--hover)}
.hit{background:var(--hl)}
.gap{height:8px}
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
var q=document.getElementById('q'),rows=[].slice.call(document.querySelectorAll('main .l,main p,main h2,main h3,main tr'));
q.oninput=function(){var v=q.value.trim().toLowerCase(),first=null;
 rows.forEach(function(e){var on=v&&e.textContent.toLowerCase().indexOf(v)>-1;e.classList.toggle('hit',!!on);if(on&&!first)first=e});
 if(first)first.scrollIntoView({block:'center'})};
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
        out.append('<tr>' + ''.join(f'<{tag}>{html.escape(c)}</{tag}>' for c in row) + '</tr>')
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
        body.append(f'<h1>{html.escape(line[3:])}</h1>')
    elif line.startswith('## ') or line.startswith('# '):
        lvl = 3 if line.startswith('## ') else 2
        t = line.lstrip('# ').rstrip(':')
        n += 1
        body.append(f'<h{lvl} id="s{n}">{html.escape(line.lstrip("# "))}</h{lvl}>')
        nav.append(f'<a href="#s{n}"{" class=sub" if lvl == 3 else ""}>{html.escape(t)}</a>')
    elif not line:
        if body and not body[-1].startswith('<div class="gap"'):
            body.append('<div class="gap"></div>')
    elif not line.startswith(' '):
        m = re.match(r'(.*\S):  (\S.*)$', line)
        if m and len(m.group(2)) <= 30:  # "situation:  score" lines line up as two columns
            body.append(f'<div class="l row"><span>{html.escape(m.group(1))}:</span><b>{html.escape(m.group(2))}</b></div>')
        else:
            body.append(f'<p>{html.escape(line)}</p>')
    else:
        indent = (len(line) - len(line.lstrip())) // 4
        s = line.strip()
        parts = re.split(r'\s{2,}', s)
        pad = f'padding-left:{indent * 1.6}em'
        sc = re.match(r'([+-]?\d+):\s+(.*)$', s)
        if sc:
            body.append(f'<div class="l sc" style="{pad}"><b>{html.escape(sc.group(1))}</b><span>{html.escape(sc.group(2))}</span></div>')
        elif len(parts) >= 2 and len(parts[-1]) <= 30:
            body.append(f'<div class="l row" style="{pad}"><span>{html.escape(" ".join(parts[:-1]))}</span><b>{html.escape(parts[-1])}</b></div>')
        else:
            body.append(f'<div class="l" style="{pad}">{html.escape(" ".join(parts))}</div>')
flush()

page = f"""<title>Radical Red AI Doc</title>
<meta name="claude:viewport-fit-sides" content="cover">
<style>{CSS}</style>
<div class="wrap"><nav aria-label="Sections"><div class="tools"><input id="q" placeholder="Search" aria-label="Search the doc"><button id="theme" type="button">Dark</button></div>{''.join(nav)}</nav>
<main>{''.join(body)}</main></div><script>{JS}</script>
"""
open(os.path.join(HERE, 'radical_red_ai.html'), 'w').write(page)
print('built', len(text.splitlines()), 'lines,', len(nav), 'sections,', len(page) // 1024, 'KB')
