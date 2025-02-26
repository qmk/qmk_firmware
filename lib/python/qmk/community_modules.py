import os

from pathlib import Path
from functools import lru_cache

from milc.attrdict import AttrDict

from qmk.json_schema import json_load, validate, merge_ordered_dicts
from qmk.util import truthy
from qmk.constants import QMK_FIRMWARE, QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.path import under_qmk_firmware, under_qmk_userspace

COMMUNITY_MODULE_JSON_FILENAME = 'qmk_module.json'


class ModuleAPI(AttrDict):
    def __init__(self, **kwargs):
        super().__init__()
        for key, value in kwargs.items():
            self[key] = value


@lru_cache(maxsize=1)
def module_api_list():
    module_definition_files = sorted(set(QMK_FIRMWARE.glob('data/constants/module_hooks/*.hjson')))
    module_definition_jsons = [json_load(f) for f in module_definition_files]
    module_definitions = merge_ordered_dicts(module_definition_jsons)
    latest_module_version = module_definition_files[-1].stem
    latest_module_version_parts = latest_module_version.split('.')

    api_list = []
    for name, mod in module_definitions.items():
        api_list.append(ModuleAPI(
            ret_type=mod['ret_type'],
            name=name,
            args=mod['args'],
            call_params=mod.get('call_params', ''),
            guard=mod.get('guard', None),
            header=mod.get('header', None),
        ))

    return api_list, latest_module_version, latest_module_version_parts[0], latest_module_version_parts[1], latest_module_version_parts[2]


def find_available_module_paths():
    """Find all available modules.
    """
    search_dirs = []
    if HAS_QMK_USERSPACE:
        search_dirs.append(QMK_USERSPACE / 'modules')
    search_dirs.append(QMK_FIRMWARE / 'modules')

    modules = []
    for search_dir in search_dirs:
        for module_json_path in search_dir.rglob(COMMUNITY_MODULE_JSON_FILENAME):
            modules.append(module_json_path.parent)
    return modules


def find_module_path(module):
    """Find a module by name.
    """
    for module_path in find_available_module_paths():
        # Ensure the module directory is under QMK Firmware or QMK Userspace
        relative_path = under_qmk_firmware(module_path)
        if not relative_path:
            relative_path = under_qmk_userspace(module_path)
        if not relative_path:
            continue

        lhs = str(relative_path.as_posix())[len('modules/'):]
        rhs = str(Path(module).as_posix())

        if relative_path and lhs == rhs:
            return module_path
    return None


def load_module_json(module):
    """Load a module JSON file.
    """
    module_path = find_module_path(module)
    if not module_path:
        raise FileNotFoundError(f'Module not found: {module}')

    module_json = json_load(module_path / COMMUNITY_MODULE_JSON_FILENAME)

    if not truthy(os.environ.get('SKIP_SCHEMA_VALIDATION'), False):
        validate(module_json, 'qmk.community_module.v1')

    module_json['module'] = module
    module_json['module_path'] = module_path

    return module_json


def load_module_jsons(modules):
    """Load the module JSON files, matching the specified order.
    """
    return list(map(load_module_json, modules))
