"""Functions that help us generate and use info.json files.
"""
import json
from glob import glob
from pathlib import Path

from milc import cli

from qmk.constants import CHIBIOS_PROCESSORS, LUFA_PROCESSORS, VUSB_PROCESSORS, LED_INDICATORS
from qmk.c_parse import find_layouts
from qmk.keyboard import config_h, rules_mk
from qmk.keymap import list_keymaps
from qmk.makefile import parse_rules_mk_file
from qmk.math import compute

rgblight_properties = {
    'led_count': 'RGBLED_NUM',
    'pin': 'RGB_DI_PIN',
    'split_count': 'RGBLED_SPLIT',
    'max_brightness': 'RGBLIGHT_LIMIT_VAL',
    'hue_steps': 'RGBLIGHT_HUE_STEP',
    'saturation_steps': 'RGBLIGHT_SAT_STEP',
    'brightness_steps': 'RGBLIGHT_VAL_STEP'
}

rgblight_toggles = {
    'sleep': 'RGBLIGHT_SLEEP',
    'split': 'RGBLIGHT_SPLIT',
}

rgblight_animations = {
    'all': 'RGBLIGHT_ANIMATIONS',
    'alternating': 'RGBLIGHT_EFFECT_ALTERNATING',
    'breathing': 'RGBLIGHT_EFFECT_BREATHING',
    'christmas': 'RGBLIGHT_EFFECT_CHRISTMAS',
    'knight': 'RGBLIGHT_EFFECT_KNIGHT',
    'rainbow_mood': 'RGBLIGHT_EFFECT_RAINBOW_MOOD',
    'rainbow_swirl': 'RGBLIGHT_EFFECT_RAINBOW_SWIRL',
    'rgb_test': 'RGBLIGHT_EFFECT_RGB_TEST',
    'snake': 'RGBLIGHT_EFFECT_SNAKE',
    'static_gradient': 'RGBLIGHT_EFFECT_STATIC_GRADIENT',
    'twinkle': 'RGBLIGHT_EFFECT_TWINKLE'
}

true_values = ['1', 'on', 'yes']
false_values = ['0', 'off', 'no']


def info_json(keyboard):
    """Generate the info.json data for a specific keyboard.
    """
    cur_dir = Path('keyboards')
    rules = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk')
    if 'DEFAULT_FOLDER' in rules:
        keyboard = rules['DEFAULT_FOLDER']
        rules = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk', rules)

    info_data = {
        'keyboard_name': str(keyboard),
        'keyboard_folder': str(keyboard),
        'keymaps': {},
        'layouts': {},
        'parse_errors': [],
        'parse_warnings': [],
        'maintainer': 'qmk',
    }

    # Populate the list of JSON keymaps
    for keymap in list_keymaps(keyboard, c=False, fullpath=True):
        info_data['keymaps'][keymap.name] = {'url': f'https://raw.githubusercontent.com/qmk/qmk_firmware/master/{keymap}/keymap.json'}

    # Populate layout data
    for layout_name, layout_json in _find_all_layouts(info_data, keyboard).items():
        if not layout_name.startswith('LAYOUT_kc'):
            layout_json['c_macro'] = True
            info_data['layouts'][layout_name] = layout_json

    # Merge in the data from info.json, config.h, and rules.mk
    info_data = merge_info_jsons(keyboard, info_data)
    info_data = _extract_config_h(info_data)
    info_data = _extract_rules_mk(info_data)

    # Make sure we have at least one layout
    if not info_data.get('layouts'):
        _log_error(info_data, 'No LAYOUTs defined! Need at least one layout defined in the keyboard.h or info.json.')

    # Make sure we supply layout macros for the community layouts we claim to support
    # FIXME(skullydazed): This should be populated into info.json and read from there instead
    if 'LAYOUTS' in rules and info_data.get('layouts'):
        # Match these up against the supplied layouts
        supported_layouts = rules['LAYOUTS'].strip().split()
        for layout_name in sorted(info_data['layouts']):
            layout_name = layout_name[7:]

            if layout_name in supported_layouts:
                supported_layouts.remove(layout_name)

        if supported_layouts:
            for supported_layout in supported_layouts:
                _log_error(info_data, 'Claims to support community layout %s but no LAYOUT_%s() macro found' % (supported_layout, supported_layout))

    return info_data


def _extract_debounce(info_data, config_c):
    """Handle debounce.
    """
    if 'debounce' in info_data and 'DEBOUNCE' in config_c:
        _log_warning(info_data, 'Debounce is specified in both info.json and config.h, the config.h value wins.')

    if 'DEBOUNCE' in config_c:
        info_data['debounce'] = config_c.get('DEBOUNCE')

    return info_data


def _extract_diode_direction(info_data, config_c):
    """Handle the diode direction.
    """
    if 'diode_direction' in info_data and 'DIODE_DIRECTION' in config_c:
        _log_warning(info_data, 'Diode direction is specified in both info.json and config.h, the config.h value wins.')

    if 'DIODE_DIRECTION' in config_c:
        info_data['diode_direction'] = config_c.get('DIODE_DIRECTION')

    return info_data


def _extract_indicators(info_data, config_c):
    """Find the LED indicator information.
    """
    for json_key, config_key in LED_INDICATORS.items():
        if json_key in info_data.get('indicators', []) and config_key in config_c:
            _log_warning(info_data, f'Indicator {json_key} is specified in both info.json and config.h, the config.h value wins.')

        if config_key in config_c:
            if 'indicators' not in info_data:
                info_data['indicators'] = {}

            info_data['indicators'][json_key] = config_c.get(config_key)

    return info_data


def _extract_community_layouts(info_data, rules):
    """Find the community layouts in rules.mk.
    """
    community_layouts = rules['LAYOUTS'].split() if 'LAYOUTS' in rules else []

    if 'community_layouts' in info_data:
        for layout in community_layouts:
            if layout not in info_data['community_layouts']:
                community_layouts.append(layout)

    else:
        info_data['community_layouts'] = community_layouts

    return info_data


def _extract_features(info_data, rules):
    """Find all the features enabled in rules.mk.
    """
    for key, value in rules.items():
        if key.endswith('_ENABLE'):
            key = '_'.join(key.split('_')[:-1]).lower()
            value = True if value in true_values else False if value in false_values else value

            if 'config_h_features' not in info_data:
                info_data['config_h_features'] = {}

            if 'features' not in info_data:
                info_data['features'] = {}

            if key in info_data['features']:
                _log_warning(info_data, 'Feature %s is specified in both info.json and rules.mk, the rules.mk value wins.' % (key,))

            info_data['features'][key] = value
            info_data['config_h_features'][key] = value

    return info_data


def _extract_rgblight(info_data, config_c):
    """Handle the rgblight configuration
    """
    rgblight = info_data.get('rgblight', {})
    animations = rgblight.get('animations', {})

    for json_key, config_key in rgblight_properties.items():
        if config_key in config_c:
            if json_key in rgblight:
                _log_warning(info_data, 'RGB Light: %s is specified in both info.json and config.h, the config.h value wins.' % (json_key,))

            rgblight[json_key] = config_c[config_key]

    for json_key, config_key in rgblight_toggles.items():
        if config_key in config_c:
            if json_key in rgblight:
                _log_warning(info_data, 'RGB Light: %s is specified in both info.json and config.h, the config.h value wins.', json_key)

            rgblight[json_key] = config_c[config_key]

    for json_key, config_key in rgblight_animations.items():
        if config_key in config_c:
            if json_key in animations:
                _log_warning(info_data, 'RGB Light: animations: %s is specified in both info.json and config.h, the config.h value wins.' % (json_key,))

            animations[json_key] = config_c[config_key]

    if animations:
        rgblight['animations'] = animations

    if rgblight:
        info_data['rgblight'] = rgblight

    return info_data


def _extract_matrix_info(info_data, config_c):
    """Populate the matrix information.
    """
    row_pins = config_c.get('MATRIX_ROW_PINS', '').replace('{', '').replace('}', '').strip()
    col_pins = config_c.get('MATRIX_COL_PINS', '').replace('{', '').replace('}', '').strip()
    direct_pins = config_c.get('DIRECT_PINS', '').replace(' ', '')[1:-1]

    if 'MATRIX_ROWS' in config_c and 'MATRIX_COLS' in config_c:
        if 'matrix_size' in info_data:
            _log_warning(info_data, 'Matrix size is specified in both info.json and config.h, the config.h values win.')

        info_data['matrix_size'] = {
            'rows': compute(config_c.get('MATRIX_ROWS', '0')),
            'cols': compute(config_c.get('MATRIX_COLS', '0')),
        }

    if row_pins and col_pins:
        if 'matrix_pins' in info_data:
            _log_warning(info_data, 'Matrix pins are specified in both info.json and config.h, the config.h values win.')

        info_data['matrix_pins'] = {}

        if row_pins:
            info_data['matrix_pins']['rows'] = row_pins.split(',')

        if col_pins:
            info_data['matrix_pins']['cols'] = col_pins.split(',')

    if direct_pins:
        if 'matrix_pins' in info_data:
            _log_warning(info_data, 'Direct pins are specified in both info.json and config.h, the config.h values win.')

        info_data['matrix_pins'] = {}
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

    return info_data


def _extract_usb_info(info_data, config_c):
    """Populate the USB information.
    """
    usb_properties = {'vid': 'VENDOR_ID', 'pid': 'PRODUCT_ID', 'device_ver': 'DEVICE_VER'}

    if 'usb' not in info_data:
        info_data['usb'] = {}

    for info_name, config_name in usb_properties.items():
        if config_name in config_c:
            if info_name in info_data['usb']:
                _log_warning(info_data, '%s in config.h is overwriting usb.%s in info.json' % (config_name, info_name))

            info_data['usb'][info_name] = config_c[config_name]

        elif info_name not in info_data['usb']:
            _log_error(info_data, '%s not specified in config.h, and %s not specified in info.json. One is required.' % (config_name, info_name))

    return info_data


def _extract_config_h(info_data):
    """Pull some keyboard information from existing config.h files
    """
    config_c = config_h(info_data['keyboard_folder'])

    _extract_debounce(info_data, config_c)
    _extract_diode_direction(info_data, config_c)
    _extract_indicators(info_data, config_c)
    _extract_matrix_info(info_data, config_c)
    _extract_usb_info(info_data, config_c)
    _extract_rgblight(info_data, config_c)

    return info_data


def _extract_rules_mk(info_data):
    """Pull some keyboard information from existing rules.mk files
    """
    rules = rules_mk(info_data['keyboard_folder'])
    mcu = rules.get('MCU')

    if mcu in CHIBIOS_PROCESSORS:
        arm_processor_rules(info_data, rules)

    elif mcu in LUFA_PROCESSORS + VUSB_PROCESSORS:
        avr_processor_rules(info_data, rules)

    else:
        cli.log.warning("%s: Unknown MCU: %s" % (info_data['keyboard_folder'], mcu))
        unknown_processor_rules(info_data, rules)

    _extract_community_layouts(info_data, rules)
    _extract_features(info_data, rules)

    return info_data


def _merge_layouts(info_data, new_info_data):
    """Merge new_info_data into info_data in an intelligent way.
    """
    for layout_name, layout_json in new_info_data['layouts'].items():
        if layout_name in info_data['layouts']:
            # Pull in layouts we have a macro for
            if len(info_data['layouts'][layout_name]['layout']) != len(layout_json['layout']):
                msg = '%s: %s: Number of elements in info.json does not match! info.json:%s != %s:%s'
                _log_error(info_data, msg % (info_data['keyboard_folder'], layout_name, len(layout_json['layout']), layout_name, len(info_data['layouts'][layout_name]['layout'])))
            else:
                for i, key in enumerate(info_data['layouts'][layout_name]['layout']):
                    key.update(layout_json['layout'][i])
        else:
            # Pull in layouts that have matrix data
            missing_matrix = False
            for key in layout_json.get('layout', {}):
                if 'matrix' not in key:
                    missing_matrix = True

            if not missing_matrix:
                if layout_name in info_data['layouts']:
                    # Update an existing layout with new data
                    for i, key in enumerate(info_data['layouts'][layout_name]['layout']):
                        key.update(layout_json['layout'][i])

                else:
                    # Copy in the new layout wholesale
                    layout_json['c_macro'] = False
                    info_data['layouts'][layout_name] = layout_json

    return info_data


def _search_keyboard_h(path):
    current_path = Path('keyboards/')
    layouts = {}
    for directory in path.parts:
        current_path = current_path / directory
        keyboard_h = '%s.h' % (directory,)
        keyboard_h_path = current_path / keyboard_h
        if keyboard_h_path.exists():
            layouts.update(find_layouts(keyboard_h_path))

    return layouts


def _find_all_layouts(info_data, keyboard):
    """Looks for layout macros associated with this keyboard.
    """
    layouts = _search_keyboard_h(Path(keyboard))

    if not layouts:
        # If we don't find any layouts from info.json or keyboard.h we widen our search. This is error prone which is why we want to encourage people to follow the standard above.
        info_data['parse_warnings'].append('%s: Falling back to searching for KEYMAP/LAYOUT macros.' % (keyboard))

        for file in glob('keyboards/%s/*.h' % keyboard):
            if file.endswith('.h'):
                these_layouts = find_layouts(file)
                if these_layouts:
                    layouts.update(these_layouts)

    return layouts


def _log_error(info_data, message):
    """Send an error message to both JSON and the log.
    """
    info_data['parse_errors'].append(message)
    cli.log.error('%s: %s', info_data.get('keyboard_folder', 'Unknown Keyboard!'), message)


def _log_warning(info_data, message):
    """Send a warning message to both JSON and the log.
    """
    info_data['parse_warnings'].append(message)
    cli.log.warning('%s: %s', info_data.get('keyboard_folder', 'Unknown Keyboard!'), message)


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
        try:
            new_info_data = json.load(info_file.open('r'))
        except Exception as e:
            _log_error(info_data, "Invalid JSON in file %s: %s: %s" % (str(info_file), e.__class__.__name__, e))
            new_info_data = {}

        if not isinstance(new_info_data, dict):
            _log_error(info_data, "Invalid file %s, root object should be a dictionary." % (str(info_file),))
            continue

        # Copy whitelisted keys into `info_data`
        for key in ('debounce', 'diode_direction', 'indicators', 'keyboard_name', 'manufacturer', 'identifier', 'url', 'maintainer', 'processor', 'bootloader', 'width', 'height'):
            if key in new_info_data:
                info_data[key] = new_info_data[key]

        # Deep merge certain keys
        # FIXME(skullydazed/anyone): this should be generalized more so that we can inteligently merge more than one level deep. It would be nice if we could filter on valid keys too. That may have to wait for a future where we use openapi or something.
        for key in ('features', 'layout_aliases', 'matrix_pins', 'rgblight', 'usb'):
            if key in new_info_data:
                if key not in info_data:
                    info_data[key] = {}

                info_data[key].update(new_info_data[key])

        # Merge the layouts
        if 'community_layouts' in new_info_data:
            if 'community_layouts' in info_data:
                for layout in new_info_data['community_layouts']:
                    if layout not in info_data['community_layouts']:
                        info_data['community_layouts'].append(layout)
            else:
                info_data['community_layouts'] = new_info_data['community_layouts']

        if 'layouts' in new_info_data:
            _merge_layouts(info_data, new_info_data)

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
