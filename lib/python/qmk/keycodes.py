from pathlib import Path

from qmk.json_schema import deep_update, json_load, validate

CONSTANTS_PATH = Path('data/constants/')
KEYCODES_PATH = CONSTANTS_PATH / 'keycodes'
EXTRAS_PATH = KEYCODES_PATH / 'extras'


def _find_versions(path, prefix):
    ret = []
    for file in path.glob(f'{prefix}_[0-9].[0-9].[0-9].hjson'):
        ret.append(file.stem.split('_')[-1])

    ret.sort(reverse=True)
    return ret


def _load_fragments(path, prefix, version):
    file = path / f'{prefix}_{version}.hjson'
    if not file.exists():
        raise ValueError(f'Requested keycode spec ({prefix}:{version}) is invalid!')

    # Load base
    spec = json_load(file)

    # Merge in fragments
    fragments = path.glob(f'{prefix}_{version}_*.hjson')
    for file in fragments:
        deep_update(spec, json_load(file))

    return spec


def _search_path(lang=None):
    return EXTRAS_PATH if lang else KEYCODES_PATH


def _search_prefix(lang=None):
    return f'keycodes_{lang}' if lang else 'keycodes'


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


def load_spec(version, lang=None):
    """Build keycode data from the requested spec file
    """
    if version == 'latest':
        version = list_versions(lang)[0]

    path = _search_path(lang)
    prefix = _search_prefix(lang)

    # Load base
    spec = _load_fragments(path, prefix, version)

    # Sort?
    spec['keycodes'] = dict(sorted(spec.get('keycodes', {}).items()))

    # Validate?
    _validate(spec)

    return spec


def list_versions(lang=None):
    """Return available versions - sorted newest first
    """
    path = _search_path(lang)
    prefix = _search_prefix(lang)

    return _find_versions(path, prefix)


def list_languages():
    """Return available languages
    """
    ret = set()
    for file in EXTRAS_PATH.glob('keycodes_*_[0-9].[0-9].[0-9].hjson'):
        ret.add(file.stem.split('_')[1])

    return ret
