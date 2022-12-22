from pathlib import Path

from qmk.json_schema import deep_update, json_load, validate

CONSTANTS_PATH = Path('data/constants/')
KEYCODES_PATH = CONSTANTS_PATH / 'keycodes'
EXTRAS_PATH = KEYCODES_PATH / 'extras'


def _merge_ordered_dicts(dicts):
    """Merges nested OrderedDict objects resulting from reading a hjson file.
    Later input dicts overrides earlier dicts for plain values.
    Arrays will be appended. If the first entry of an array is "!reset!", the contents of the array will be cleared and replaced with RHS.
    Dictionaries will be recursively merged. If any entry is "!reset!", the contents of the dictionary will be cleared and replaced with RHS.
    """
    from typing import OrderedDict
    result = OrderedDict()

    def add_entry(target, k, v):
        if k in target and isinstance(v, (OrderedDict, dict)):
            if "!reset!" in v:
                target[k] = v
            else:
                target[k] = _merge_ordered_dicts([target[k], v])
            if "!reset!" in target[k]:
                del target[k]["!reset!"]
        elif k in target and isinstance(v, list):
            if v[0] == '!reset!':
                target[k] = v[1:]
            else:
                target[k] = target[k] + v
        else:
            target[k] = v

    for d in dicts:
        for (k, v) in d.items():
            add_entry(result, k, v)

    return result


def _find_versions(path, prefix):
    ret = []
    for file in path.glob(f'{prefix}_[0-9].[0-9].[0-9].hjson'):
        ret.append(file.stem.split('_')[-1])

    ret.sort(reverse=True)
    return ret


def _potential_search_versions(version, lang=None):
    versions = list_versions(lang)
    versions.reverse()
    return versions[:versions.index(version)+1]


def _search_path(lang=None):
    return EXTRAS_PATH if lang else KEYCODES_PATH


def _search_prefix(lang=None):
    return f'keycodes_{lang}' if lang else 'keycodes'


def _locate_files(path, prefix, versions):
    # collate files by fragment "type"
    files = {'_': []}
    for version in versions:
        files['_'].append(path / f'{prefix}_{version}.hjson')

        for file in path.glob(f'{prefix}_{version}_*.hjson'):
            fragment = file.stem.replace(f'{prefix}_{version}_', '')
            if fragment not in files:
                files[fragment] = []
            files[fragment].append(file)

    return files


def _process_files(files):
    # allow override within types of fragments - but not globally
    spec = {}
    for category in files.values():
        specs = []
        for file in category:
            specs.append(json_load(file))

        deep_update(spec, _merge_ordered_dicts(specs))

    return spec


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
    versions = _potential_search_versions(version, lang)

    # Load bases + any fragments
    spec = _process_files(_locate_files(path, prefix, versions))

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
