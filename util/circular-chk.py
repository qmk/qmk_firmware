import glob
import re
from sys import exit, argv
from pathlib import Path

strict = False
if len(argv) > 1 and argv[1] == '--strict' :
    strict = True

regexExclude = r"keymaps\/(.*)via\/"
reg = re.compile(regexExclude)
filesToscan = Path('keyboards').glob('**/rules.mk')
illegalSRC = list()

for f in filesToscan:
    p = str(f).replace('\\','/')
    basepath = p.replace('keyboards/','')
    basepath_arr = basepath.split('/')

    # Skip 'via' file
    if reg.search(p):
        continue

    # Read file as lines
    lineList = list()
    with f.open() as file:
        try:
            lineList = file.readlines()
        except:
            # sometimes encoding issues with japanese characters for example
            pass

    # Concat multilines
    lineList = '\n'.join(lineList).replace('\\\n','').split('\n')
    for l in lineList:
        if not l.startswith('SRC ='):
            continue
        imports = l.replace('SRC =','').replace('\t','').split(' ')
        for i in imports:
            _i = i.split('/')
            if(_i[0] == 'keyboards' and _i[1] != basepath_arr[0]):
                illegalSRC.append(f)

if len(illegalSRC) > 0:
    for fp in illegalSRC:
        print(str(fp))
    print(f'{len(illegalSRC)} files with illegal imports')
    if strict:
        exit(1)
    else:
        exit(0)
