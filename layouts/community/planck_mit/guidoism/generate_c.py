import itertools
import json
import os.path
import re

KEYMAP_C = """/* {0}
{1}
*/
[{2}] = {3}(
    {4})
"""

README_MD = """## {0}
```
{1}
```
"""

base = os.path.dirname(__file__)

layer_names = dict(enumerate(['_QWERTY', '_LOWER', '_RAISE', '_MOVEMENT', '_NUMPAD', '_FUNCTION']))
layer_name = {('MO(%d)' % i): layer_names.get(i).strip('_') for i in layer_names.keys()}

keys = json.load(open(os.path.join(base, 'keys.json')))

d = json.load(open(os.path.join(base, 'guidoism.json')))

def surround(s, a, b, c):
    return a + b.join(s) + c

def pattern(cell, table):
    return ['─'*cell for i in range(table)]

top    = surround(pattern(5, 12), '┌', '┬', '┐')
mid    = surround(pattern(5, 12), '├', '┼', '┤')
bottom = surround(pattern(5, 12), '└', '┴', '┘')

from more_itertools import chunked, intersperse, interleave_longest

def uni(k):
    return keys.get(k, k).lower().center(5)

def c_layout(i, definition, template):
    c_name = layer_names[i]
    pretty_name = c_name.strip('_').capitalize()
    layout = d['layout']
    
    surround = lambda s: ''.join(interleave_longest(['│']*(len(s)+1), s))
    layer = list(map(uni, definition))
    layer[41] = layer[41].center(11)
    layer = chunked(layer, 12)
    rows = intersperse(mid, map(surround, layer))
    pretty = '\n'.join(itertools.chain([top], rows, [bottom]))
    
    surround = lambda s: ', '.join(s)
    layer = list(map(lambda k: layer_name.get(k, k), definition))
    layer = chunked(layer, 12)
    rows = map(surround, layer)
    c_layer = ',\n    '.join(itertools.chain([], rows, []))
    
    return template.format(pretty_name, pretty, c_name, layout, c_layer)

start = '// START_REPLACEMENT\n'
end = '// END_REPLACEMENT\n'
replacement = start + ',\n\n'.join(c_layout(i, l, KEYMAP_C) for i, l in enumerate(d['layers'])) + end
keymap = os.path.join(base, 'keymap.c')
existing = open(keymap).read()
r = re.compile(r'// START_REPLACEMENT.*// END_REPLACEMENT', re.DOTALL)
open(keymap, 'w').write(r.sub(replacement, existing))

replacement = '## Current Configuration\n\n' + '\n\n'.join(c_layout(i, l, README_MD) for i, l in enumerate(d['layers']))
keymap = os.path.join(base, 'readme.md')
existing = open(keymap).read()
r = re.compile(r'## Current Configuration.*', re.DOTALL)
open(keymap, 'w').write(r.sub(replacement, existing))
