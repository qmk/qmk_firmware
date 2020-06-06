"""Functions that help us generate and use info.json files.
"""
import json
from glob import glob
from pathlib import Path

from milc import cli

from qmk.constants import ARM_PROCESSORS, AVR_PROCESSORS, VUSB_PROCESSORS
from qmk.c_parse import find_layouts
from qmk.keyboard import config_h, rules_mk
from qmk.math import compute


def info_json(keyboard):
    """Generate the info.json data for a specific keyboard.
    """
    info_data = {
        'keyboard_name': str(keyboard),
        'keyboard_folder': str(keyboard),
        'layouts': {},
        'maintainer': 'qmk',
    }

    for layout_name, layout_json in _find_all_layouts(keyboard).items():
        if not layout_name.startswith('LAYOUT_kc'):
            info_data['layouts'][layout_name] = layout_json

    info_data = merge_info_jsons(keyboard, info_data)
    info_data = _extract_config_h(info_data)
    info_data = _extract_rules_mk(info_data)

    return info_data


def _extract_config_h(info_data):
    """Pull some keyboard information from existing rules.mk files
    """
    config_c = config_h(info_data['keyboard_folder'])
    row_pins = config_c.get('MATRIX_ROW_PINS', '').replace('{', '').replace('}', '').strip()
    col_pins = config_c.get('MATRIX_COL_PINS', '').replace('{', '').replace('}', '').strip()
    direct_pins = config_c.get('DIRECT_PINS', '').replace(' ', '')[1:-1]

    info_data['diode_direction'] = config_c.get('DIODE_DIRECTION')
    info_data['matrix_size'] = {
        'rows': compute(config_c.get('MATRIX_ROWS', '0')),
        'cols': compute(config_c.get('MATRIX_COLS', '0')),
    }
    info_data['matrix_pins'] = {}

    if row_pins:
        info_data['matrix_pins']['rows'] = row_pins.split(',')
    if col_pins:
        info_data['matrix_pins']['cols'] = col_pins.split(',')

    if direct_pins:
        direct_pin_array = []
        for row in direct_pins.split('},{'):
            if row.startswith('{'):
                row = row[1:]
            if row.endswith('}'):
                row = row[:-1]

            direct_pin_array.append([])

            for pin in row.split(','):
                if pin == 'NO_PIN':
                    pin = None

                direct_pin_array[-1].append(pin)

        info_data['matrix_pins']['direct'] = direct_pin_array

    info_data['usb'] = {
        'vid': config_c.get('VENDOR_ID'),
        'pid': config_c.get('PRODUCT_ID'),
        'device_ver': config_c.get('DEVICE_VER'),
        'manufacturer': config_c.get('MANUFACTURER'),
        'product': config_c.get('PRODUCT'),
        'description': config_c.get('DESCRIPTION'),
    }

    return info_data


def _extract_rules_mk(info_data):
    """Pull some keyboard information from existing rules.mk files
    """
    rules = rules_mk(info_data['keyboard_folder'])
    mcu = rules.get('MCU')

    if mcu in ARM_PROCESSORS:
        arm_processor_rules(info_data, rules)
    elif mcu in AVR_PROCESSORS:
        avr_processor_rules(info_data, rules)
    else:
        cli.log.warning("%s: Unknown MCU: %s" % (info_data['keyboard_folder'], mcu))
        unknown_processor_rules(info_data, rules)

    return info_data


def _find_all_layouts(keyboard):
    """Looks for layout macros associated with this keyboard.
    """
    layouts = {}
    rules = rules_mk(keyboard)
    keyboard_path = Path(rules.get('DEFAULT_FOLDER', keyboard))

    # Pull in all layouts defined in the standard files
    current_path = Path('keyboards/')
    for directory in keyboard_path.parts:
        current_path = current_path / directory
        keyboard_h = '%s.h' % (directory,)
        keyboard_h_path = current_path / keyboard_h
        if keyboard_h_path.exists():
            layouts.update(find_layouts(keyboard_h_path))

    if not layouts:
        # If we didn't find any layouts above we widen our search. This is error
        # prone which is why we want to encourage people to follow the standard above.
        cli.log.warning('%s: Falling back to searching for KEYMAP/LAYOUT macros.' % (keyboard))
        for file in glob('keyboards/%s/*.h' % keyboard):
            if file.endswith('.h'):
                these_layouts = find_layouts(file)
                if these_layouts:
                    layouts.update(these_layouts)

    if 'LAYOUTS' in rules:
        # Match these up against the supplied layouts
        supported_layouts = rules['LAYOUTS'].strip().split()
        for layout_name in sorted(layouts):
            if not layout_name.startswith('LAYOUT_'):
                continue
            layout_name = layout_name[7:]
            if layout_name in supported_layouts:
                supported_layouts.remove(layout_name)

        if supported_layouts:
            cli.log.error('%s: Missing LAYOUT() macro for %s' % (keyboard, ', '.join(supported_layouts)))

    return layouts


def arm_processor_rules(info_data, rules):
    """Setup the default info for an ARM board.
    """
    info_data['processor_type'] = 'arm'
    info_data['bootloader'] = rules['BOOTLOADER'] if 'BOOTLOADER' in rules else 'unknown'
    info_data['processor'] = rules['MCU'] if 'MCU' in rules else 'unknown'
    info_data['protocol'] = 'ChibiOS'

    if info_data['bootloader'] == 'unknown':
        if 'STM32' in info_data['processor']:
            info_data['bootloader'] = 'stm32-dfu'
        elif info_data.get('manufacturer') == 'Input Club':
            info_data['bootloader'] = 'kiibohd-dfu'

    if 'STM32' in info_data['processor']:
        info_data['platform'] = 'STM32'
    elif 'MCU_SERIES' in rules:
        info_data['platform'] = rules['MCU_SERIES']
    elif 'ARM_ATSAM' in rules:
        info_data['platform'] = 'ARM_ATSAM'

    return info_data


def avr_processor_rules(info_data, rules):
    """Setup the default info for an AVR board.
    """
    info_data['processor_type'] = 'avr'
    info_data['bootloader'] = rules['BOOTLOADER'] if 'BOOTLOADER' in rules else 'atmel-dfu'
    info_data['platform'] = rules['ARCH'] if 'ARCH' in rules else 'unknown'
    info_data['processor'] = rules['MCU'] if 'MCU' in rules else 'unknown'
    info_data['protocol'] = 'V-USB' if rules.get('MCU') in VUSB_PROCESSORS else 'LUFA'

    # FIXME(fauxpark/anyone): Eventually we should detect the protocol by looking at PROTOCOL inherited from mcu_selection.mk:
    # info_data['protocol'] = 'V-USB' if rules.get('PROTOCOL') == 'VUSB' else 'LUFA'

    return info_data


def unknown_processor_rules(info_data, rules):
    """Setup the default keyboard info for unknown boards.
    """
    info_data['bootloader'] = 'unknown'
    info_data['platform'] = 'unknown'
    info_data['processor'] = 'unknown'
    info_data['processor_type'] = 'unknown'
    info_data['protocol'] = 'unknown'

    return info_data


def merge_info_jsons(keyboard, info_data):
    """Return a merged copy of all the info.json files for a keyboard.
    """
    for info_file in find_info_json(keyboard):
        # Load and validate the JSON data
        with info_file.open('r') as info_fd:
            new_info_data = json.load(info_fd)

        if not isinstance(new_info_data, dict):
            cli.log.error("Invalid file %s, root object should be a dictionary.", str(info_file))
            continue

        # Copy whitelisted keys into `info_data`
        for key in ('keyboard_name', 'manufacturer', 'identifier', 'url', 'maintainer', 'processor', 'bootloader', 'width', 'height'):
            if key in new_info_data:
                info_data[key] = new_info_data[key]

        # Merge the layouts in
        if 'layouts' in new_info_data:
            for layout_name, json_layout in new_info_data['layouts'].items():
                # Only pull in layouts we have a macro for
                if layout_name in info_data['layouts']:
                    if info_data['layouts'][layout_name]['key_count'] != len(json_layout['layout']):
                        cli.log.error('%s: %s: Number of elements in info.json does not match! info.json:%s != %s:%s', info_data['keyboard_folder'], layout_name, len(json_layout['layout']), layout_name, len(info_data['layouts'][layout_name]['layout']))
                    else:
                        for i, key in enumerate(info_data['layouts'][layout_name]['layout']):
                            key.update(json_layout['layout'][i])

    return info_data


def find_info_json(keyboard):
    """Finds all the info.json files associated with a keyboard.
    """
    # Find the most specific first
    base_path = Path('keyboards')
    keyboard_path = base_path / keyboard
    keyboard_parent = keyboard_path.parent
    info_jsons = [keyboard_path / 'info.json']

    # Add DEFAULT_FOLDER before parents, if present
    rules = rules_mk(keyboard)
    if 'DEFAULT_FOLDER' in rules:
        info_jsons.append(Path(rules['DEFAULT_FOLDER']) / 'info.json')

    # Add in parent folders for least specific
    for _ in range(5):
        info_jsons.append(keyboard_parent / 'info.json')
        if keyboard_parent.parent == base_path:
            break
        keyboard_parent = keyboard_parent.parent

    # Return a list of the info.json files that actually exist
    return [info_json for info_json in info_jsons if info_json.exists()]
