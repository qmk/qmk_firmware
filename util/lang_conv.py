from pathlib import Path

langs = set()
files = Path('quantum/keymap_extras/').glob('keymap_*.h')
for file in files:
    langs.add(file.stem.replace('keymap_', ''))

for lang in langs:
    try:
        file = Path(f'quantum/keymap_extras/keymap_{lang}.h')
        print(f'Reading:{file}')
        collect = None
        out = []
        out += ['{']
        out += ['    "aliases": {']
        lines = file.read_text(encoding='utf-8').split('\n')
        for line in lines:

            if line.startswith("// Row"):
                # print(line)
                continue
            elif line.startswith("/*******************************************************************************"):
                raise Exception(f'Skipping:{file}')
            elif '/*' in line:
                collect = [line]
            elif '*/' in line:
                collect += [line]
                if 'copyright' in collect[0].lower():
                    collect = None
                    continue
                out += collect
                collect = None
            elif collect:
                collect += [line]

            elif '#define' in line:
                define = line.split()
                while len(define) < 5:
                    define.append("")

                if define[4] == "(backslash)":
                    define[4] = '\\\\'

                define[4] = " ".join(define[4:]).strip()
                define[4] = define[4].replace('"', '\\"')

                if define[4]:
                    out += [f'        "{define[2]}": {{']
                    out += [f'            "key": "{define[1]}",']
                    out += [f'            "label": "{define[4]}",']
                    out += [f'        }}']
                else:
                    out += [f'        "{define[2]}": {{']
                    out += [f'            "key": "{define[1]}"']
                    out += [f'        }}']

        out += ['    }']
        out += ['}']

        dump = Path(f'data/constants/keycodes/extras/keycodes_{lang}_0.0.1.hjson')
        print(f'Writing:{dump}')
        dump.write_text("\n".join(out), encoding='utf-8')

    except Exception as e:
        print(e)
