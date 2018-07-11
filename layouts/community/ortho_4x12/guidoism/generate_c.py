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

def truthy(s):
    return [a for a in s if a]

def grouper(iterable, n):
    args = [iter(iterable)] * n
    return (truthy(r) for r in itertools.zip_longest(*args))

def just(s, n=5):
    return [a.center(n*2+1 if len(s) == 11 and i == 5 else n) for i, a in enumerate(s)]

def surround(s, a, b, c):
    return a + b.join(s) + c

def pattern(cell, table):
    return ['─'*cell for i in range(table)]

def layer5(i, l, rename):
    return [just(list(map(rename, row))) for row in grouper(l, 12)]

for i, l in enumerate(d['layers']):
    print('/*')
    print(surround(pattern(5, 12), '┌', '┬', '┐'))
    for n, row in enumerate(layer5(i, l, unicode)):
        print(surround(row, '│', '│', '│'))
        if n < 3:
            print(surround(pattern(5, 12), '├', '┼', '┤'))
        else:
            print(surround(pattern(5, 12), '└', '┴', '┘'))
    print('*/')
    print('  [%s] = %s(' % (layer_names[i], d['layout']))
    for n, row in enumerate(layer5(i, l, lambda k: layer_name.get(k, k))):
        print(surround(row, '    ', ', ', ','))
    print('  ),\n')
