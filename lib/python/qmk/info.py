"""Functions that help us generate and use info.json files.
"""
import re
import os
from pathlib import Path
import jsonschema
from dotty_dict import dotty

from milc import cli

from qmk.constants import COL_LETTERS, ROW_LETTERS, CHIBIOS_PROCESSORS, LUFA_PROCESSORS, VUSB_PROCESSORS, JOYSTICK_AXES
from qmk.c_parse import find_layouts, parse_config_h_file, find_led_config
from qmk.json_schema import deep_update, json_load, validate
from qmk.keyboard import config_h, rules_mk
from qmk.commands import parse_configurator_json
from qmk.makefile import parse_rules_mk_file
from qmk.math import compute
from qmk.util import maybe_exit, truthy

true_values = ['1', 'on', 'yes']
false_values = ['0', 'off', 'no']


def _keyboard_in_layout_name(keyboard, layout):
    """Validate that a layout macro does not contain name of keyboard
    """
    # TODO: reduce this list down
    safe_layout_tokens = {
        'ansi',
        'iso',
        'jp',
        'jis',
        'ortho',
        'wkl',
        'tkl',
        'preonic',
        'planck',
    }

    # Ignore tokens like 'split_3x7_4' or just '2x4'
    layout = re.sub(r"_split_\d+x\d+_\d+", '', layout)
    layout = re.sub(r"_\d+x\d+", '', layout)

    name_fragments = set(keyboard.split('/')) - safe_layout_tokens

    return any(fragment in layout for fragment in name_fragments)


def _valid_community_layout(layout):
    """Validate that a declared community list exists
    """
    return (Path('layouts/default') / layout).exists()


def _get_key_left_position(key):
    # Special case for ISO enter
    return key['x'] - 0.25 if key.get('h', 1) == 2 and key.get('w', 1) == 1.25 else key['x']


def _find_invalid_encoder_index(info_data):
    """Perform additional validation of encoders
    """
    enc_left = info_data.get('encoder', {}).get('rotary', [])
    enc_right = []

    if info_data.get('split', {}).get('enabled', False):
        enc_right = info_data.get('split', {}).get('encoder', {}).get('right', {}).get('rotary', enc_left)

    enc_count = len(enc_left) + len(enc_right)

    ret = []
    layouts = info_data.get('layouts', {})
    for layout_name, layout_data in layouts.items():
        found = set()
        for key in layout_data['layout']:
            if 'encoder' in key:
                if enc_count == 0:
                    ret.append((layout_name, key['encoder'], 'non-configured'))
                elif key['encoder'] >= enc_count:
                    ret.append((layout_name, key['encoder'], 'out of bounds'))
                elif key['encoder'] in found:
                    ret.append((layout_name, key['encoder'], 'duplicate'))
                found.add(key['encoder'])

    return ret


def _validate_build_target(keyboard, info_data):
    """Non schema checks
    """
    keyboard_json_path = Path('keyboards') / keyboard / 'keyboard.json'
    config_files = find_info_json(keyboard)

    # keyboard.json can only exist at the deepest part of the tree
    keyboard_json_count = 0
    for info_file in config_files:
        if info_file.name == 'keyboard.json':
            keyboard_json_count += 1
            if info_file != keyboard_json_path:
                _log_error(info_data, f'Invalid keyboard.json location detected: {info_file}.')

    # Moving forward keyboard.json should be used as a build target
    if keyboard_json_count == 0:
        _log_warning(info_data, 'Build marker "keyboard.json" not found.')


def _validate_layouts(keyboard, info_data):  # noqa C901
    """Non schema checks
    """
    col_num = info_data.get('matrix_size', {}).get('cols', 0)
    row_num = info_data.get('matrix_size', {}).get('rows', 0)
    layouts = info_data.get('layouts', {})
    layout_aliases = info_data.get('layout_aliases', {})
    community_layouts = info_data.get('community_layouts', [])
    community_layouts_names = list(map(lambda layout: f'LAYOUT_{layout}', community_layouts))

    # Make sure we have at least one layout
    if len(layouts) == 0 or all(not layout.get('json_layout', False) for layout in layouts.values()):
        _log_error(info_data, 'No LAYOUTs defined! Need at least one layout defined in info.json.')

    # Make sure all layouts are DD
    for layout_name, layout_data in layouts.items():
        if layout_data.get('c_macro', False):
            _log_error(info_data, f'{layout_name}: Layout macro should not be defined within ".h" files.')

    # Make sure all matrix values are in bounds
    for layout_name, layout_data in layouts.items():
        for index, key_data in enumerate(layout_data['layout']):
            row, col = key_data['matrix']
            key_name = key_data.get('label', f'k{ROW_LETTERS[row]}{COL_LETTERS[col]}')
            if row >= row_num:
                _log_error(info_data, f'{layout_name}: Matrix row for key {index} ({key_name}) is {row} but must be less than {row_num}')
            if col >= col_num:
                _log_error(info_data, f'{layout_name}: Matrix column for key {index} ({key_name}) is {col} but must be less than {col_num}')

    # Reject duplicate matrix locations
    for layout_name, layout_data in layouts.items():
        seen = set()
        for index, key_data in enumerate(layout_data['layout']):
            key = f"{key_data['matrix']}"
            if key in seen:
                _log_error(info_data, f'{layout_name}: Matrix location for key {index} is not unique {key_data}')
            seen.add(key)

    # Warn if physical positions are offset (at least one key should be at x=0, and at least one key at y=0)
    for layout_name, layout_data in layouts.items():
        offset_x = min([_get_key_left_position(k) for k in layout_data['layout']])
        if offset_x > 0:
            _log_warning(info_data, f'Layout "{layout_name}" is offset on X axis by {offset_x}')

        offset_y = min([k['y'] for k in layout_data['layout']])
        if offset_y > 0:
            _log_warning(info_data, f'Layout "{layout_name}" is offset on Y axis by {offset_y}')

    # Providing only LAYOUT_all "because I define my layouts in a 3rd party tool"
    if len(layouts) == 1 and 'LAYOUT_all' in layouts:
        _log_warning(info_data, '"LAYOUT_all" should be "LAYOUT" unless additional layouts are provided.')

    # Extended layout name checks - ignoring community_layouts and "safe" values
    potential_layouts = set(layouts.keys()) - set(community_layouts_names)
    for layout in potential_layouts:
        if _keyboard_in_layout_name(keyboard, layout):
            _log_warning(info_data, f'Layout "{layout}" should not contain name of keyboard.')

    # Filter out any non-existing community layouts
    for layout in community_layouts:
        if not _valid_community_layout(layout):
            # Ignore layout from future checks
            info_data['community_layouts'].remove(layout)
            _log_error(info_data, 'Claims to support a community layout that does not exist: %s' % (layout))

    # Make sure we supply layout macros for the community layouts we claim to support
    for layout_name in community_layouts_names:
        if layout_name not in layouts and layout_name not in layout_aliases:
            _log_error(info_data, 'Claims to support community layout %s but no %s() macro found' % (layout, layout_name))


def _validate_keycodes(keyboard, info_data):
    """Non schema checks
    """
    # keycodes with length > 7 must have short forms for visualisation purposes
    for decl in info_data.get('keycodes', []):
        if len(decl["key"]) > 7:
            if not decl.get("aliases", []):
                _log_error(info_data, f'Keycode {decl["key"]} has no short form alias')


def _validate_encoders(keyboard, info_data):
    """Non schema checks
    """
    # encoder IDs in layouts must be in range and not duplicated
    found = _find_invalid_encoder_index(info_data)
    for layout_name, encoder_index, reason in found:
        _log_error(info_data, f'Layout "{layout_name}" contains {reason} encoder index {encoder_index}.')


def _validate(keyboard, info_data):
    """Perform various validation on the provided info.json data
    """
    # First validate against the jsonschema
    try:
        validate(info_data, 'qmk.api.keyboard.v1')

        # Additional validation
        _validate_build_target(keyboard, info_data)
        _validate_layouts(keyboard, info_data)
        _validate_keycodes(keyboard, info_data)
        _validate_encoders(keyboard, info_data)

    except jsonschema.ValidationError as e:
        json_path = '.'.join([str(p) for p in e.absolute_path])
        cli.log.error('Invalid API data: %s: %s: %s', keyboard, json_path, e.message)
        maybe_exit(1)


def info_json(keyboard, force_layout=None):
    """Generate the info.json data for a specific keyboard.
    """
    cur_dir = Path('keyboards')
    root_rules_mk = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk')

    if 'DEFAULT_FOLDER' in root_rules_mk:
        keyboard = root_rules_mk['DEFAULT_FOLDER']

    info_data = {
        'keyboard_name': str(keyboard),
        'keyboard_folder': str(keyboard),
        'keymaps': {},
        'layouts': {},
        'parse_errors': [],
        'parse_warnings': [],
        'maintainer': 'qmk',
    }

    # Populate layout data
    layouts, aliases = _search_keyboard_h(keyboard)

    if aliases:
        info_data['layout_aliases'] = aliases

    for layout_name, layout_json in layouts.items():
        if not layout_name.startswith('LAYOUT_kc'):
            layout_json['c_macro'] = True
            layout_json['json_layout'] = False
            info_data['layouts'][layout_name] = layout_json

    # Merge in the data from info.json, config.h, and rules.mk
    info_data = merge_info_jsons(keyboard, info_data)
    info_data = _process_defaults(info_data)
    info_data = _extract_rules_mk(info_data, rules_mk(str(keyboard)))
    info_data = _extract_config_h(info_data, config_h(str(keyboard)))

    # Ensure that we have various calculated values
    info_data = _matrix_size(info_data)
    info_data = _joystick_axis_count(info_data)

    # Merge in data from <keyboard.c>
    info_data = _extract_led_config(info_data, str(keyboard))

    # Force a community layout if requested
    community_layouts = info_data.get("community_layouts", [])
    if force_layout in community_layouts:
        info_data["community_layouts"] = [force_layout]

    # Validate
    # Skip processing if necessary
    if not truthy(os.environ.get('SKIP_SCHEMA_VALIDATION'), False):
        _validate(keyboard, info_data)

    # Check that the reported matrix size is consistent with the actual matrix size
    _check_matrix(info_data)

    return info_data


def _extract_features(info_data, rules):
    """Find all the features enabled in rules.mk.
    """
    # Process booleans rules
    for key, value in rules.items():
        if key.endswith('_ENABLE'):
            key = '_'.join(key.split('_')[:-1]).lower()
            value = True if value.lower() in true_values else False if value.lower() in false_values else value

            if key in ['lto']:
                continue

            if 'config_h_features' not in info_data:
                info_data['config_h_features'] = {}

            if 'features' not in info_data:
                info_data['features'] = {}

            if key in info_data['features']:
                _log_warning(info_data, 'Feature %s is specified in both info.json (%s) and rules.mk (%s). The rules.mk value wins.' % (key, info_data['features'], value))

            info_data['features'][key] = value
            info_data['config_h_features'][key] = value

    return info_data


def _pin_name(pin):
    """Returns the proper representation for a pin.
    """
    pin = pin.strip()

    if not pin:
        return None

    elif pin.isdigit():
        return int(pin)

    elif pin == 'NO_PIN':
        return None

    return pin


def _extract_pins(pins):
    """Returns a list of pins from a comma separated string of pins.
    """
    return [_pin_name(pin) for pin in pins.split(',')]


def _extract_2d_array(raw):
    """Return a 2d array of strings
    """
    out_array = []

    while raw[-1] != '}':
        raw = raw[:-1]

    for row in raw.split('},{'):
        if row.startswith('{'):
            row = row[1:]

        if row.endswith('}'):
            row = row[:-1]

        out_array.append([])

        for val in row.split(','):
            out_array[-1].append(val)

    return out_array


def _extract_2d_int_array(raw):
    """Return a 2d array of ints
    """
    ret = _extract_2d_array(raw)

    return [list(map(int, x)) for x in ret]


def _extract_direct_matrix(direct_pins):
    """extract direct_matrix
    """
    direct_pin_array = _extract_2d_array(direct_pins)

    for i in range(len(direct_pin_array)):
        for j in range(len(direct_pin_array[i])):
            if direct_pin_array[i][j] == 'NO_PIN':
                direct_pin_array[i][j] = None

    return direct_pin_array


def _extract_audio(info_data, config_c):
    """Populate data about the audio configuration
    """
    audio_pins = []

    for pin in 'B5', 'B6', 'B7', 'C4', 'C5', 'C6':
        if config_c.get(f'{pin}_AUDIO'):
            audio_pins.append(pin)

    if audio_pins:
        info_data['audio'] = {'pins': audio_pins}


def _extract_encoders_values(config_c, postfix=''):
    """Common encoder extraction logic
    """
    a_pad = config_c.get(f'ENCODER_A_PINS{postfix}', '').replace(' ', '')[1:-1]
    b_pad = config_c.get(f'ENCODER_B_PINS{postfix}', '').replace(' ', '')[1:-1]
    resolutions = config_c.get(f'ENCODER_RESOLUTIONS{postfix}', '').replace(' ', '')[1:-1]

    default_resolution = config_c.get('ENCODER_RESOLUTION', None)

    if a_pad and b_pad:
        a_pad = list(filter(None, a_pad.split(',')))
        b_pad = list(filter(None, b_pad.split(',')))
        resolutions = list(filter(None, resolutions.split(',')))
        if default_resolution:
            resolutions += [default_resolution] * (len(a_pad) - len(resolutions))

        encoders = []
        for index in range(len(a_pad)):
            encoder = {'pin_a': a_pad[index], 'pin_b': b_pad[index]}
            if index < len(resolutions):
                encoder['resolution'] = int(resolutions[index])
            encoders.append(encoder)

        return encoders


def _extract_encoders(info_data, config_c):
    """Populate data about encoder pins
    """
    encoders = _extract_encoders_values(config_c)
    if encoders:
        if 'encoder' not in info_data:
            info_data['encoder'] = {}

        if 'rotary' in info_data['encoder']:
            _log_warning(info_data, 'Encoder config is specified in both config.h (%s) and info.json (%s). The config.h value wins.' % (encoders, info_data['encoder']['rotary']))

        info_data['encoder']['rotary'] = encoders

    # TODO: some logic still assumes ENCODER_ENABLED would partially create encoder dict
    if info_data.get('features', {}).get('encoder', False):
        if 'encoder' not in info_data:
            info_data['encoder'] = {}
        info_data['encoder']['enabled'] = True


def _extract_split_encoders(info_data, config_c):
    """Populate data about split encoder pins
    """
    encoders = _extract_encoders_values(config_c, '_RIGHT')
    if encoders:
        if 'split' not in info_data:
            info_data['split'] = {}

        if 'encoder' not in info_data['split']:
            info_data['split']['encoder'] = {}

        if 'right' not in info_data['split']['encoder']:
            info_data['split']['encoder']['right'] = {}

        if 'rotary' in info_data['split']['encoder']['right']:
            _log_warning(info_data, 'Encoder config is specified in both config.h and info.json (encoder.rotary) (Value: %s), the config.h value wins.' % info_data['split']['encoder']['right']['rotary'])

        info_data['split']['encoder']['right']['rotary'] = encoders


def _extract_secure_unlock(info_data, config_c):
    """Populate data about the secure unlock sequence
    """
    unlock = config_c.get('SECURE_UNLOCK_SEQUENCE', '').replace(' ', '')[1:-1]
    if unlock:
        unlock_array = _extract_2d_int_array(unlock)
        if 'secure' not in info_data:
            info_data['secure'] = {}

        if 'unlock_sequence' in info_data['secure']:
            _log_warning(info_data, 'Secure unlock sequence is specified in both config.h (SECURE_UNLOCK_SEQUENCE) and info.json (secure.unlock_sequence) (Value: %s), the config.h value wins.' % info_data['secure']['unlock_sequence'])

        info_data['secure']['unlock_sequence'] = unlock_array


def _extract_split_handedness(info_data, config_c):
    # Migrate
    split = info_data.get('split', {})
    if 'matrix_grid' in split:
        split['handedness'] = split.get('handedness', {})
        split['handedness']['matrix_grid'] = split.pop('matrix_grid')


def _extract_split_serial(info_data, config_c):
    # Migrate
    split = info_data.get('split', {})
    if 'soft_serial_pin' in split:
        split['serial'] = split.get('serial', {})
        split['serial']['pin'] = split.pop('soft_serial_pin')


def _extract_split_transport(info_data, config_c):
    # Figure out the transport method
    if config_c.get('USE_I2C') is True:
        if 'split' not in info_data:
            info_data['split'] = {}

        if 'transport' not in info_data['split']:
            info_data['split']['transport'] = {}

        if 'protocol' in info_data['split']['transport']:
            _log_warning(info_data, 'Split transport is specified in both config.h (USE_I2C) and info.json (split.transport.protocol) (Value: %s), the config.h value wins.' % info_data['split']['transport'])

        info_data['split']['transport']['protocol'] = 'i2c'

    # Ignore transport defaults if "SPLIT_KEYBOARD" is unset
    elif 'enabled' in info_data.get('split', {}):
        if 'split' not in info_data:
            info_data['split'] = {}

        if 'transport' not in info_data['split']:
            info_data['split']['transport'] = {}

        if 'protocol' not in info_data['split']['transport']:
            info_data['split']['transport']['protocol'] = 'serial'

    # Migrate
    transport = info_data.get('split', {}).get('transport', {})
    if 'sync_matrix_state' in transport:
        transport['sync'] = transport.get('sync', {})
        transport['sync']['matrix_state'] = transport.pop('sync_matrix_state')
    if 'sync_modifiers' in transport:
        transport['sync'] = transport.get('sync', {})
        transport['sync']['modifiers'] = transport.pop('sync_modifiers')


def _extract_split_right_pins(info_data, config_c):
    # Figure out the right half matrix pins
    row_pins = config_c.get('MATRIX_ROW_PINS_RIGHT', '').replace('{', '').replace('}', '').strip()
    col_pins = config_c.get('MATRIX_COL_PINS_RIGHT', '').replace('{', '').replace('}', '').strip()
    direct_pins = config_c.get('DIRECT_PINS_RIGHT', '').replace(' ', '')[1:-1]

    if row_pins or col_pins or direct_pins:
        if info_data.get('split', {}).get('matrix_pins', {}).get('right', None):
            _log_warning(info_data, 'Right hand matrix data is specified in both info.json and config.h, the config.h values win.')

        if 'split' not in info_data:
            info_data['split'] = {}

        if 'matrix_pins' not in info_data['split']:
            info_data['split']['matrix_pins'] = {}

        if 'right' not in info_data['split']['matrix_pins']:
            info_data['split']['matrix_pins']['right'] = {}

        if col_pins:
            info_data['split']['matrix_pins']['right']['cols'] = _extract_pins(col_pins)

        if row_pins:
            info_data['split']['matrix_pins']['right']['rows'] = _extract_pins(row_pins)

        if direct_pins:
            info_data['split']['matrix_pins']['right']['direct'] = _extract_direct_matrix(direct_pins)


def _extract_matrix_info(info_data, config_c):
    """Populate the matrix information.
    """
    row_pins = config_c.get('MATRIX_ROW_PINS', '').replace('{', '').replace('}', '').strip()
    col_pins = config_c.get('MATRIX_COL_PINS', '').replace('{', '').replace('}', '').strip()
    direct_pins = config_c.get('DIRECT_PINS', '').replace(' ', '')[1:-1]
    info_snippet = {}

    if 'MATRIX_ROWS' in config_c and 'MATRIX_COLS' in config_c:
        if 'matrix_size' in info_data:
            _log_warning(info_data, 'Matrix size is specified in both info.json and config.h, the config.h values win.')

        info_data['matrix_size'] = {
            'cols': compute(config_c.get('MATRIX_COLS', '0')),
            'rows': compute(config_c.get('MATRIX_ROWS', '0')),
        }

    if row_pins and col_pins:
        if 'matrix_pins' in info_data and 'cols' in info_data['matrix_pins'] and 'rows' in info_data['matrix_pins']:
            _log_warning(info_data, 'Matrix pins are specified in both info.json and config.h, the config.h values win.')

        info_snippet['cols'] = _extract_pins(col_pins)
        info_snippet['rows'] = _extract_pins(row_pins)

    if direct_pins:
        if 'matrix_pins' in info_data and 'direct' in info_data['matrix_pins']:
            _log_warning(info_data, 'Direct pins are specified in both info.json and config.h, the config.h values win.')

        info_snippet['direct'] = _extract_direct_matrix(direct_pins)

    if config_c.get('CUSTOM_MATRIX', 'no') != 'no':
        if 'matrix_pins' in info_data and 'custom' in info_data['matrix_pins']:
            _log_warning(info_data, 'Custom Matrix is specified in both info.json and config.h, the config.h values win.')

        info_snippet['custom'] = True

        if config_c['CUSTOM_MATRIX'] == 'lite':
            info_snippet['custom_lite'] = True

    if info_snippet:
        info_data['matrix_pins'] = info_snippet

    return info_data


def _config_to_json(key_type, config_value):
    """Convert config value using spec
    """
    if key_type.startswith('array'):
        if key_type.count('.') > 1:
            raise Exception(f"Conversion of {key_type} not possible")

        if '.' in key_type:
            key_type, array_type = key_type.split('.', 1)
        else:
            array_type = None

        config_value = config_value.replace('{', '').replace('}', '').strip()

        if array_type == 'int':
            return list(map(int, config_value.split(',')))
        else:
            return list(map(str.strip, config_value.split(',')))

    elif key_type in ['bool', 'flag']:
        if isinstance(config_value, bool):
            return config_value
        return config_value in true_values

    elif key_type == 'hex':
        return '0x' + config_value[2:].upper()

    elif key_type == 'list':
        return config_value.split()

    elif key_type == 'int':
        return int(config_value)

    elif key_type == 'str':
        return config_value.strip('"').replace('\\"', '"').replace('\\\\', '\\')

    elif key_type == 'bcd_version':
        major = int(config_value[2:4])
        minor = int(config_value[4])
        revision = int(config_value[5])

        return f'{major}.{minor}.{revision}'

    return config_value


def _extract_config_h(info_data, config_c):
    """Pull some keyboard information from existing config.h files
    """
    # Pull in data from the json map
    dotty_info = dotty(info_data)
    info_config_map = json_load(Path('data/mappings/info_config.hjson'))

    for config_key, info_dict in info_config_map.items():
        info_key = info_dict['info_key']
        key_type = info_dict.get('value_type', 'raw')

        try:
            replace_with = info_dict.get('replace_with')
            if config_key in config_c and info_dict.get('invalid', False):
                if replace_with:
                    _log_error(info_data, '%s in config.h is no longer a valid option and should be replaced with %s' % (config_key, replace_with))
                else:
                    _log_error(info_data, '%s in config.h is no longer a valid option and should be removed' % config_key)
            elif config_key in config_c and info_dict.get('deprecated', False):
                if replace_with:
                    _log_warning(info_data, '%s in config.h is deprecated in favor of %s and will be removed at a later date' % (config_key, replace_with))
                else:
                    _log_warning(info_data, '%s in config.h is deprecated and will be removed at a later date' % config_key)

            if config_key in config_c and info_dict.get('to_json', True):
                if dotty_info.get(info_key) and info_dict.get('warn_duplicate', True):
                    _log_warning(info_data, '%s in config.h is overwriting %s in info.json' % (config_key, info_key))

                dotty_info[info_key] = _config_to_json(key_type, config_c[config_key])

        except Exception as e:
            _log_warning(info_data, f'{config_key}->{info_key}: {e}')

    info_data.update(dotty_info)

    # Pull data that easily can't be mapped in json
    _extract_matrix_info(info_data, config_c)
    _extract_audio(info_data, config_c)
    _extract_secure_unlock(info_data, config_c)
    _extract_split_handedness(info_data, config_c)
    _extract_split_serial(info_data, config_c)
    _extract_split_transport(info_data, config_c)
    _extract_split_right_pins(info_data, config_c)
    _extract_encoders(info_data, config_c)
    _extract_split_encoders(info_data, config_c)

    return info_data


def _process_defaults(info_data):
    """Process any additional defaults based on currently discovered information
    """
    defaults_map = json_load(Path('data/mappings/defaults.hjson'))
    for default_type in defaults_map.keys():
        thing_map = defaults_map[default_type]
        if default_type in info_data:
            merged_count = 0
            thing_items = thing_map.get(info_data[default_type], {}).items()
            for key, value in thing_items:
                if key not in info_data:
                    info_data[key] = value
                    merged_count += 1

            if merged_count == 0 and len(thing_items) > 0:
                _log_warning(info_data, 'All defaults for \'%s\' were skipped, potential redundant config or misconfiguration detected' % (default_type))

    return info_data


def _extract_rules_mk(info_data, rules):
    """Pull some keyboard information from existing rules.mk files
    """
    info_data['processor'] = rules.get('MCU', info_data.get('processor', 'atmega32u4'))

    if info_data['processor'] in CHIBIOS_PROCESSORS:
        arm_processor_rules(info_data, rules)

    elif info_data['processor'] in LUFA_PROCESSORS + VUSB_PROCESSORS:
        avr_processor_rules(info_data, rules)

    else:
        cli.log.warning("%s: Unknown MCU: %s" % (info_data['keyboard_folder'], info_data['processor']))
        unknown_processor_rules(info_data, rules)

    # Pull in data from the json map
    dotty_info = dotty(info_data)
    info_rules_map = json_load(Path('data/mappings/info_rules.hjson'))

    for rules_key, info_dict in info_rules_map.items():
        info_key = info_dict['info_key']
        key_type = info_dict.get('value_type', 'raw')

        try:
            replace_with = info_dict.get('replace_with')
            if rules_key in rules and info_dict.get('invalid', False):
                if replace_with:
                    _log_error(info_data, '%s in rules.mk is no longer a valid option and should be replaced with %s' % (rules_key, replace_with))
                else:
                    _log_error(info_data, '%s in rules.mk is no longer a valid option and should be removed' % rules_key)
            elif rules_key in rules and info_dict.get('deprecated', False):
                if replace_with:
                    _log_warning(info_data, '%s in rules.mk is deprecated in favor of %s and will be removed at a later date' % (rules_key, replace_with))
                else:
                    _log_warning(info_data, '%s in rules.mk is deprecated and will be removed at a later date' % rules_key)

            if rules_key in rules and info_dict.get('to_json', True):
                if dotty_info.get(info_key) and info_dict.get('warn_duplicate', True):
                    _log_warning(info_data, '%s in rules.mk is overwriting %s in info.json' % (rules_key, info_key))

                dotty_info[info_key] = _config_to_json(key_type, rules[rules_key])

        except Exception as e:
            _log_warning(info_data, f'{rules_key}->{info_key}: {e}')

    info_data.update(dotty_info)

    # Merge in config values that can't be easily mapped
    _extract_features(info_data, rules)

    return info_data


def find_keyboard_c(keyboard):
    """Find all <keyboard>.c files
    """
    keyboard = Path(keyboard)
    current_path = Path('keyboards/')

    files = []
    for directory in keyboard.parts:
        current_path = current_path / directory
        keyboard_c_path = current_path / f'{directory}.c'
        if keyboard_c_path.exists():
            files.append(keyboard_c_path)

    return files


def _extract_led_config(info_data, keyboard):
    """Scan all <keyboard>.c files for led config
    """
    for feature in ['rgb_matrix', 'led_matrix']:
        if info_data.get('features', {}).get(feature, False) or feature in info_data:
            # Only attempt search if dd led config is missing
            if 'layout' not in info_data.get(feature, {}):
                cols = info_data.get('matrix_size', {}).get('cols')
                rows = info_data.get('matrix_size', {}).get('rows')
                if cols and rows:
                    # Process
                    for file in find_keyboard_c(keyboard):
                        try:
                            ret = find_led_config(file, cols, rows)
                            if ret:
                                info_data[feature] = info_data.get(feature, {})
                                info_data[feature]['layout'] = ret
                        except Exception as e:
                            _log_warning(info_data, f'led_config: {file.name}: {e}')
                else:
                    _log_warning(info_data, 'led_config: matrix size required to parse g_led_config')

            if info_data[feature].get('layout', None) and not info_data[feature].get('led_count', None):
                info_data[feature]['led_count'] = len(info_data[feature]['layout'])

    return info_data


def _matrix_size(info_data):
    """Add info_data['matrix_size'] if it doesn't exist.
    """
    if 'matrix_size' not in info_data and 'matrix_pins' in info_data:
        info_data['matrix_size'] = {}

        if 'direct' in info_data['matrix_pins']:
            info_data['matrix_size']['cols'] = len(info_data['matrix_pins']['direct'][0])
            info_data['matrix_size']['rows'] = len(info_data['matrix_pins']['direct'])
        elif 'cols' in info_data['matrix_pins'] and 'rows' in info_data['matrix_pins']:
            info_data['matrix_size']['cols'] = len(info_data['matrix_pins']['cols'])
            info_data['matrix_size']['rows'] = len(info_data['matrix_pins']['rows'])

        # Assumption of split common
        if 'split' in info_data:
            if info_data['split'].get('enabled', False):
                info_data['matrix_size']['rows'] *= 2

    return info_data


def _joystick_axis_count(info_data):
    """Add info_data['joystick.axis_count'] if required
    """
    if 'axes' in info_data.get('joystick', {}):
        axes_keys = info_data['joystick']['axes'].keys()
        info_data['joystick']['axis_count'] = max(JOYSTICK_AXES.index(a) for a in axes_keys) + 1 if axes_keys else 0

    return info_data


def _check_matrix(info_data):
    """Check the matrix to ensure that row/column count is consistent.
    """
    if 'matrix_pins' in info_data and 'matrix_size' in info_data:
        actual_col_count = info_data['matrix_size'].get('cols', 0)
        actual_row_count = info_data['matrix_size'].get('rows', 0)
        col_count = row_count = 0

        if 'direct' in info_data['matrix_pins']:
            col_count = len(info_data['matrix_pins']['direct'][0])
            row_count = len(info_data['matrix_pins']['direct'])
        elif 'cols' in info_data['matrix_pins'] and 'rows' in info_data['matrix_pins']:
            col_count = len(info_data['matrix_pins']['cols'])
            row_count = len(info_data['matrix_pins']['rows'])
        elif 'cols' not in info_data['matrix_pins'] and 'rows' not in info_data['matrix_pins']:
            # This case caters for custom matrix implementations where normal rows/cols are specified
            return

        if col_count != actual_col_count and col_count != (actual_col_count / 2):
            # FIXME: once we can we should detect if split is enabled to do the actual_col_count/2 check.
            _log_error(info_data, f'MATRIX_COLS is inconsistent with the size of MATRIX_COL_PINS: {col_count} != {actual_col_count}')

        if row_count != actual_row_count and row_count != (actual_row_count / 2):
            # FIXME: once we can we should detect if split is enabled to do the actual_row_count/2 check.
            _log_error(info_data, f'MATRIX_ROWS is inconsistent with the size of MATRIX_ROW_PINS: {row_count} != {actual_row_count}')


def _search_keyboard_h(keyboard):
    keyboard = Path(keyboard)
    current_path = Path('keyboards/')
    aliases = {}
    layouts = {}

    for directory in keyboard.parts:
        current_path = current_path / directory
        keyboard_h = '%s.h' % (directory,)
        keyboard_h_path = current_path / keyboard_h
        if keyboard_h_path.exists():
            new_layouts, new_aliases = find_layouts(keyboard_h_path)
            layouts.update(new_layouts)

            for alias, alias_text in new_aliases.items():
                if alias_text in layouts:
                    aliases[alias] = alias_text

    return layouts, aliases


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
    info_data['protocol'] = 'ChibiOS'
    info_data['platform_key'] = 'chibios'

    if 'STM32' in info_data['processor']:
        info_data['platform'] = 'STM32'
    elif 'MCU_SERIES' in rules:
        info_data['platform'] = rules['MCU_SERIES']

    return info_data


def avr_processor_rules(info_data, rules):
    """Setup the default info for an AVR board.
    """
    info_data['processor_type'] = 'avr'
    info_data['platform'] = rules['ARCH'] if 'ARCH' in rules else 'unknown'
    info_data['platform_key'] = 'avr'
    info_data['protocol'] = 'V-USB' if info_data['processor'] in VUSB_PROCESSORS else 'LUFA'

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
    config_files = find_info_json(keyboard)

    for info_file in config_files:
        # Load and validate the JSON data
        new_info_data = json_load(info_file)

        if not isinstance(new_info_data, dict):
            _log_error(info_data, "Invalid file %s, root object should be a dictionary." % (str(info_file),))
            continue

        if not truthy(os.environ.get('SKIP_SCHEMA_VALIDATION'), False):
            try:
                validate(new_info_data, 'qmk.keyboard.v1')
            except jsonschema.ValidationError as e:
                json_path = '.'.join([str(p) for p in e.absolute_path])
                cli.log.error('Not including data from file: %s', info_file)
                cli.log.error('\t%s: %s', json_path, e.message)
                continue

        # Merge layout data in
        if 'layout_aliases' in new_info_data:
            info_data['layout_aliases'] = {**info_data.get('layout_aliases', {}), **new_info_data['layout_aliases']}
            del new_info_data['layout_aliases']

        for layout_name, layout in new_info_data.get('layouts', {}).items():
            if layout_name in info_data.get('layout_aliases', {}):
                _log_warning(info_data, f"info.json uses alias name {layout_name} instead of {info_data['layout_aliases'][layout_name]}")
                layout_name = info_data['layout_aliases'][layout_name]

            if layout_name in info_data['layouts']:
                if len(info_data['layouts'][layout_name]['layout']) != len(layout['layout']):
                    msg = 'Number of keys for %s does not match! info.json specifies %d keys, C macro specifies %d'
                    _log_error(info_data, msg % (layout_name, len(layout['layout']), len(info_data['layouts'][layout_name]['layout'])))
                else:
                    info_data['layouts'][layout_name]['json_layout'] = True
                    for new_key, existing_key in zip(layout['layout'], info_data['layouts'][layout_name]['layout']):
                        existing_key.update(new_key)
            else:
                if not all('matrix' in key_data.keys() for key_data in layout['layout']):
                    _log_error(info_data, f'Layout "{layout_name}" has no "matrix" definition in either "info.json" or "<keyboard>.h"!')
                else:
                    layout['c_macro'] = False
                    layout['json_layout'] = True
                    info_data['layouts'][layout_name] = layout

        # Update info_data with the new data
        if 'layouts' in new_info_data:
            del new_info_data['layouts']

        deep_update(info_data, new_info_data)

    return info_data


def find_info_json(keyboard):
    """Finds all the info.json files associated with a keyboard.
    """
    # Find the most specific first
    base_path = Path('keyboards')
    keyboard_path = base_path / keyboard
    keyboard_parent = keyboard_path.parent
    info_jsons = [keyboard_path / 'info.json', keyboard_path / 'keyboard.json']

    # Add DEFAULT_FOLDER before parents, if present
    rules = rules_mk(keyboard)
    if 'DEFAULT_FOLDER' in rules:
        info_jsons.append(Path(rules['DEFAULT_FOLDER']) / 'info.json')

    # Add in parent folders for least specific
    for _ in range(5):
        if keyboard_parent == base_path:
            break
        info_jsons.append(keyboard_parent / 'info.json')
        info_jsons.append(keyboard_parent / 'keyboard.json')
        keyboard_parent = keyboard_parent.parent

    # Return a list of the info.json files that actually exist
    return [info_json for info_json in info_jsons if info_json.exists()]


def keymap_json_config(keyboard, keymap, force_layout=None):
    """Extract keymap level config
    """
    # TODO: resolve keymap.py and info.py circular dependencies
    from qmk.keymap import locate_keymap

    keymap_folder = locate_keymap(keyboard, keymap, force_layout=force_layout).parent

    km_info_json = parse_configurator_json(keymap_folder / 'keymap.json')
    return km_info_json.get('config', {})


def keymap_json(keyboard, keymap, force_layout=None):
    """Generate the info.json data for a specific keymap.
    """
    # TODO: resolve keymap.py and info.py circular dependencies
    from qmk.keymap import locate_keymap

    keymap_folder = locate_keymap(keyboard, keymap, force_layout=force_layout).parent

    # Files to scan
    keymap_config = keymap_folder / 'config.h'
    keymap_rules = keymap_folder / 'rules.mk'
    keymap_file = keymap_folder / 'keymap.json'

    # Build the info.json file
    kb_info_json = info_json(keyboard, force_layout=force_layout)

    # Merge in the data from keymap.json
    km_info_json = keymap_json_config(keyboard, keymap, force_layout=force_layout) if keymap_file.exists() else {}
    deep_update(kb_info_json, km_info_json)

    # Merge in the data from config.h, and rules.mk
    _extract_rules_mk(kb_info_json, parse_rules_mk_file(keymap_rules))
    _extract_config_h(kb_info_json, parse_config_h_file(keymap_config))

    return kb_info_json
