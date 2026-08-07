#!/usr/bin/env python3

import os
import json
from pathlib import Path
from time import gmtime, strftime

DATETIME_FORMAT = '%Y-%m-%d %H:%M:%S %Z'


def current_datetime():
    return strftime(DATETIME_FORMAT, gmtime())


qmk_firmware_dir = Path(os.path.realpath(__file__)).parents[2]

binaries = []
binaries.extend(qmk_firmware_dir.glob("*.bin"))
binaries.extend(qmk_firmware_dir.glob("*.hex"))
binaries.extend(qmk_firmware_dir.glob("*.uf2"))
binaries = list(sorted(binaries))

data = []
for binary in binaries:
    data.append(binary.name)

keyboard_all_json = json.dumps({'last_updated': current_datetime(), 'files': data}, separators=(',', ':'))

print(keyboard_all_json)
