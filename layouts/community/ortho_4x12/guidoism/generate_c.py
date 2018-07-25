import itertools
import json
from pprint import pprint as pp

layer_names = dict(enumerate(['_QWERTY', '_LOWER', '_RAISE', '_MOVEMENT', '_NUMPAD']))
layer_name = {('MO(%d)' % i): layer_names.get(i).strip('_') for i in layer_names.keys()}

keys = json.load(open('layouts/community/ortho_4x12/guidoism/keys.json'))

unicodes = {
    "<i class='fa fa-fast-forward'></i>": "next",
    "<i class='fa fa-volume-down'></i>": "vol-",
    "<i class='fa fa-volume-up'></i>": "vol+",
    "<i class='fa fa-play'></i>": "play",
}

def unicode(k, only_unicode=True):
    k = keys.get(k, k)
    if only_unicode:
        return unicodes.get(k, k)

d = json.load(open('layouts/community/ortho_4x12/guidoism/guidoism.json'))

def surround(s, a, b, c):
    return a + b.join(s) + c

def pattern(cell, table):
    return ['─'*cell for i in range(table)]

top    = surround(pattern(5, 12), '┌', '┬', '┐')
mid    = surround(pattern(5, 12), '├', '┼', '┤')
bottom = surround(pattern(5, 12), '└', '┴', '┘')

from more_itertools import chunked, intersperse, interleave_longest

def uni(k):
    k = keys.get(k, k)
    return unicodes.get(k, k).center(5)

def c_layout(i, definition):
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
    
    return """/* {0}
{1}
*/
[{2}] = {3}(
    {4})
""".format(pretty_name, pretty, c_name, layout, c_layer)

print(',\n\n'.join(c_layout(i, l) for i, l in enumerate(d['layers'])))


