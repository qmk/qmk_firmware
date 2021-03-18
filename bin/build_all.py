import subprocess
import os

BOARDS = ['redragon/k552', 'redragon/k556']

for kb in BOARDS:
    subprocess.run(f"bin/qmk compile -kb {kb} -km default -j{os.cpu_count()}", shell=True)
