import os

from pathlib import Path

from milc.attrdict import AttrDict

from qmk.json_schema import json_load, validate
from qmk.util import truthy
from qmk.constants import QMK_FIRMWARE, QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.path import under_qmk_firmware, under_qmk_userspace

COMMUNITY_MODULE_JSON_FILENAME = 'qmk_module.json'


class ModuleAPI(AttrDict):
    def __init__(self, **kwargs):
        super().__init__()
        for key, value in kwargs.items():
            self[key] = value


MODULE_API_LIST = [
    ModuleAPI(ret_type='void', name='keyboard_pre_init', args='void', call_params='', guard=None, header=None),
    ModuleAPI(ret_type='void', name='keyboard_post_init', args='void', call_params='', guard=None, header=None),
    ModuleAPI(ret_type='bool', name='pre_process_record', args='uint16_t keycode, keyrecord_t *record', call_params='keycode, record', guard=None, header=None),
    ModuleAPI(ret_type='bool', name='process_record', args='uint16_t keycode, keyrecord_t *record', call_params='keycode, record', guard=None, header=None),
    ModuleAPI(ret_type='void', name='post_process_record', args='uint16_t keycode, keyrecord_t *record', call_params='keycode, record', guard=None, header=None),
    ModuleAPI(ret_type='void', name='housekeeping_task', args='void', call_params='', guard=None, header=None),
    ModuleAPI(ret_type='void', name='suspend_power_down', args='void', call_params='', guard=None, header=None),
    ModuleAPI(ret_type='void', name='suspend_wakeup_init', args='void', call_params='', guard=None, header=None),
    ModuleAPI(ret_type='bool', name='shutdown', args='bool jump_to_bootloader', call_params='jump_to_bootloader', guard=None, header=None),
    ModuleAPI(ret_type='bool', name='process_detected_host_os', args='os_variant_t os', call_params='os', guard="defined(OS_DETECTION_ENABLE)", header="os_detection.h"),
]

MODULE_API_VERSION = '20250122'


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
