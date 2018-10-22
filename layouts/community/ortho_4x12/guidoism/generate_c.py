import itertools
import json
from pprint import pprint as pp

layers = dict(enumerate(['_QWERTY', '_LOWER', '_RAISE', '_MOVEMENT', '_NUMPAD']))
key_names = {('MO(%d)' % i): layers.get(i).strip('_') for i in layers.keys()}

unicodes = {
    "<i class='fa fa-fast-forward'></i>": "next",
    "<i class='fa fa-volume-down'></i>": "vol-",
    "<i class='fa fa-volume-up'></i>": "vol+",
    "<i class='fa fa-play'></i>": "play",
}

d = json.load(open('layouts/community/ortho_4x12/guidoism/guidoism.json'))

def grouper(iterable, n):
    args = [iter(iterable)] * n
    return itertools.zip_longest(*args, fillvalue='')

def truthy(s):
    return [a for a in s if a]

def just(s, n):
    return [a.center(n*2+1 if len(s) == 11 and i == 5 else n) for i, a in enumerate(s)]

def replace(s):
    return [key_names.get(a, a) for a in s]

def layer(i, l):
    n = max(len(s) for s in l)
    rows = [', '.join(replace(truthy(row))) for row in grouper(l, 12)]
    return '[%s] = %s(\n%s)' % (layers[i], d['layout'], ',\n'.join(rows))

print(',\n\n'.join(layer(i, l) for i, l in enumerate(d['layers'])))

def surround(s, a, b, c):
    return a + b.join(s) + c

def pattern(cell, table):
    return ['─'*cell for i in range(table)]

keys = json.load(open('layouts/community/ortho_4x12/guidoism/keys.json'))

def layer2(i, l):
    def replace(s):
        s = [keys.get(a, a) for a in s]
        return [unicodes.get(a, a) for a in s]
    n = max(len(s) for s in l)
    return [surround(just(replace(truthy(row)), 5), '│', '│', '│') for row in grouper(l, 12)]

for i, l in enumerate(d['layers']):
    print(surround(pattern(5, 12), '┌', '┬', '┐'))
    for n, row in enumerate(layer2(i, l)):
        print(row)
        if n < 3:
            print(surround(pattern(5, 12), '├', '┼', '┤'))
        else:
            print(surround(pattern(5, 12), '└', '┴', '┘'))
