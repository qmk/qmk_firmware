import os
from pathlib import Path

from milc.attrdict import AttrDict

from qmk.json_schema import json_load, validate
from qmk.util import truthy


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


def load_module_jsons(modules):
    """Load the module JSON files, matching the specified order.
    """
    module_jsons = []
    for module in modules:

        module_json_path = Path('modules') / module / 'qmk_module.json'
        if not module_json_path.exists():
            raise FileNotFoundError(f'Module JSON file not found: {module_json_path}')

        module_json = json_load(module_json_path)

        if not truthy(os.environ.get('SKIP_SCHEMA_VALIDATION'), False):
            validate(module_json, 'qmk.community_module.v1')

        module_jsons.append(module_json)

    return module_jsons
