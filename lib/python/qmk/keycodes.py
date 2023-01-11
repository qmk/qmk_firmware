from pathlib import Path

from qmk.json_schema import deep_update, json_load, validate

CONSTANTS_PATH = Path('data/constants/keycodes/')


def _validate(spec):
    # first throw it to the jsonschema
    validate(spec, 'qmk.keycodes.v1')

    # no duplicate keycodes
    keycodes = []
    for value in spec['keycodes'].values():
        keycodes.append(value['key'])
        keycodes.extend(value.get('aliases', []))
    duplicates = set([x for x in keycodes if keycodes.count(x) > 1])
    if duplicates:
        raise ValueError(f'Keycode spec contains duplicate keycodes! ({",".join(duplicates)})')


def load_spec(version):
    """Build keycode data from the requested spec file
    """
    if version == 'latest':
        version = list_versions()[0]

    file = CONSTANTS_PATH / f'keycodes_{version}.hjson'
    if not file.exists():
        raise ValueError(f'Requested keycode spec ({version}) is invalid!')

    # Load base
    spec = json_load(file)

    # Merge in fragments
    fragments = CONSTANTS_PATH.glob(f'keycodes_{version}_*.hjson')
    for file in fragments:
        deep_update(spec, json_load(file))

    # Sort?
    spec['keycodes'] = dict(sorted(spec['keycodes'].items()))

    # Validate?
    _validate(spec)

    return spec


def list_versions():
    """Return available versions - sorted newest first
    """
    ret = []
    for file in CONSTANTS_PATH.glob('keycodes_[0-9].[0-9].[0-9].hjson'):
        ret.append(file.stem.split('_')[1])

    ret.sort(reverse=True)
    return ret
