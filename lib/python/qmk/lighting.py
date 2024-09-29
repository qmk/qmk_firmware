import re
from pathlib import Path

from qmk.json_schema import json_load


def list_lighting_versions(feature):
    """Return available versions - sorted newest first
    """
    ret = []
    for file in Path('data/constants/lighting/').glob(f'{feature}_[0-9].[0-9].[0-9].hjson'):
        ret.append(file.stem.split('_')[-1])

    ret.sort(reverse=True)
    return ret


def load_lighting_spec(feature, version='latest'):
    """Build lighting data from the requested spec file
    """
    if version == 'latest':
        version = list_lighting_versions(feature)[0]

    spec = json_load(Path(f'data/constants/lighting/{feature}_{version}.hjson'))

    # preprocess for gross rgblight "mode + n"
    for obj in spec.get('effects', {}).values():
        define = obj['key']
        offset = 0
        found = re.match('(.*)_(\\d+)$', define)
        if found:
            define = found.group(1)
            offset = int(found.group(2)) - 1
        obj['define'] = define
        obj['offset'] = offset

    return spec
