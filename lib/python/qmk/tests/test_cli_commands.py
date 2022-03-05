import platform
from subprocess import DEVNULL

from milc import cli

is_windows = 'windows' in platform.platform().lower()


def check_subcommand(command, *args):
    cmd = ['qmk', command, *args]
    result = cli.run(cmd, stdin=DEVNULL, combined_output=True)
    return result


def check_subcommand_stdin(file_to_read, command, *args):
    """Pipe content of a file to a command and return output.
    """
    with open(file_to_read, encoding='utf-8') as my_file:
        cmd = ['qmk', command, *args]
        result = cli.run(cmd, stdin=my_file, combined_output=True)
    return result


def check_returncode(result, expected=[0]):
    """Print stdout if `result.returncode` does not match `expected`.
    """
    if result.returncode not in expected:
        print('`%s` stdout:' % ' '.join(result.args))
        print(result.stdout)
        print('returncode:', result.returncode)
    assert result.returncode in expected


def test_format_c():
    result = check_subcommand('format-c', '-n', 'quantum/matrix.c')
    check_returncode(result)


def test_format_c_all():
    result = check_subcommand('format-c', '-n', '-a')
    check_returncode(result, [0, 1])


def test_compile():
    result = check_subcommand('compile', '-kb', 'handwired/pytest/basic', '-km', 'default', '-n')
    check_returncode(result)


def test_compile_json():
    result = check_subcommand('compile', '-kb', 'handwired/pytest/basic', '-km', 'default_json', '-n')
    check_returncode(result)


def test_flash():
    result = check_subcommand('flash', '-kb', 'handwired/pytest/basic', '-km', 'default', '-n')
    check_returncode(result)


def test_flash_bootloaders():
    result = check_subcommand('flash', '-b')
    check_returncode(result, [1])


def test_kle2json():
    result = check_subcommand('kle2json', 'lib/python/qmk/tests/kle.txt', '-f')
    check_returncode(result)
    assert 'Wrote out' in result.stdout


def test_doctor():
    result = check_subcommand('doctor', '-n')
    check_returncode(result, [0, 1])
    assert 'QMK Doctor is checking your environment.' in result.stdout
    assert 'QMK is ready to go' in result.stdout


def test_hello():
    result = check_subcommand('hello')
    check_returncode(result)
    assert 'Hello,' in result.stdout


def test_format_python():
    result = check_subcommand('format-python', '-n', '-a')
    check_returncode(result)
    assert 'Successfully formatted the python code.' in result.stdout


def test_list_keyboards():
    result = check_subcommand('list-keyboards')
    check_returncode(result)
    # check to see if a known keyboard is returned
    # this will fail if handwired/pytest/basic is removed
    assert 'handwired/pytest/basic' in result.stdout


def test_list_keymaps():
    result = check_subcommand('list-keymaps', '-kb', 'handwired/pytest/basic')
    check_returncode(result)
    assert 'default' and 'default_json' in result.stdout


def test_list_keymaps_long():
    result = check_subcommand('list-keymaps', '--keyboard', 'handwired/pytest/basic')
    check_returncode(result)
    assert 'default' and 'default_json' in result.stdout


def test_list_keymaps_community():
    result = check_subcommand('list-keymaps', '--keyboard', 'handwired/pytest/has_community')
    check_returncode(result)
    assert 'test' in result.stdout


def test_list_keymaps_kb_only():
    result = check_subcommand('list-keymaps', '-kb', 'contra')
    check_returncode(result)
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_vendor_kb():
    result = check_subcommand('list-keymaps', '-kb', 'ai03/lunar')
    check_returncode(result)
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_vendor_kb_rev():
    result = check_subcommand('list-keymaps', '-kb', 'kbdfans/kbd67/mkiirgb/v2')
    check_returncode(result)
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_no_keyboard_found():
    result = check_subcommand('list-keymaps', '-kb', 'asdfghjkl')
    check_returncode(result, [2])
    assert 'invalid keyboard_folder value' in result.stdout


def test_json2c():
    result = check_subcommand('json2c', 'keyboards/handwired/pytest/has_template/keymaps/default_json/keymap.json')
    check_returncode(result)
    assert result.stdout == '#include QMK_KEYBOARD_H\nconst uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\t[0] = LAYOUT_ortho_1x1(KC_A)};\n\n'


def test_json2c_macros():
    result = check_subcommand("json2c", 'keyboards/handwired/pytest/macro/keymaps/default/keymap.json')
    check_returncode(result)
    assert 'LAYOUT_ortho_1x1(MACRO_0)' in result.stdout
    assert 'case MACRO_0:' in result.stdout
    assert 'SEND_STRING("Hello, World!"SS_TAP(X_ENTER));' in result.stdout


def test_json2c_stdin():
    result = check_subcommand_stdin('keyboards/handwired/pytest/has_template/keymaps/default_json/keymap.json', 'json2c', '-')
    check_returncode(result)
    assert result.stdout == '#include QMK_KEYBOARD_H\nconst uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\t[0] = LAYOUT_ortho_1x1(KC_A)};\n\n'


def test_json2c_wrong_json():
    result = check_subcommand('json2c', 'keyboards/handwired/pytest/info.json')
    check_returncode(result, [1])
    assert 'Invalid JSON keymap' in result.stdout


def test_json2c_no_json():
    result = check_subcommand('json2c', 'keyboards/handwired/pytest/pytest.h')
    check_returncode(result, [1])
    assert 'Invalid JSON encountered' in result.stdout


def test_info():
    result = check_subcommand('info', '-kb', 'handwired/pytest/basic')
    check_returncode(result)
    assert 'Keyboard Name: pytest' in result.stdout
    assert 'Processor: atmega32u4' in result.stdout
    assert 'Layout:' not in result.stdout
    assert 'k0' not in result.stdout


def test_info_keyboard_render():
    result = check_subcommand('info', '-kb', 'handwired/pytest/basic', '-l')
    check_returncode(result)
    assert 'Keyboard Name: pytest' in result.stdout
    assert 'Processor: atmega32u4' in result.stdout
    assert 'Layouts:' in result.stdout
    assert 'k0' in result.stdout


def test_info_keymap_render():
    result = check_subcommand('info', '-kb', 'handwired/pytest/basic', '-km', 'default_json')
    check_returncode(result)
    assert 'Keyboard Name: pytest' in result.stdout
    assert 'Processor: atmega32u4' in result.stdout

    if is_windows:
        assert '|A |' in result.stdout
    else:
        assert '│A │' in result.stdout


def test_info_matrix_render():
    result = check_subcommand('info', '-kb', 'handwired/pytest/basic', '-m')
    check_returncode(result)
    assert 'Keyboard Name: pytest' in result.stdout
    assert 'Processor: atmega32u4' in result.stdout
    assert 'LAYOUT_ortho_1x1' in result.stdout

    if is_windows:
        assert '|0A|' in result.stdout
    else:
        assert '│0A│' in result.stdout

    assert 'Matrix for "LAYOUT_ortho_1x1"' in result.stdout


def test_c2json():
    result = check_subcommand("c2json", "-kb", "handwired/pytest/has_template", "-km", "default", "keyboards/handwired/pytest/has_template/keymaps/default/keymap.c")
    check_returncode(result)
    assert result.stdout.strip() == '{"keyboard": "handwired/pytest/has_template", "documentation": "This file is a keymap.json file for handwired/pytest/has_template", "keymap": "default", "layout": "LAYOUT_ortho_1x1", "layers": [["KC_A"]]}'


def test_c2json_nocpp():
    result = check_subcommand("c2json", "--no-cpp", "-kb", "handwired/pytest/has_template", "-km", "default", "keyboards/handwired/pytest/has_template/keymaps/nocpp/keymap.c")
    check_returncode(result)
    assert result.stdout.strip() == '{"keyboard": "handwired/pytest/has_template", "documentation": "This file is a keymap.json file for handwired/pytest/has_template", "keymap": "default", "layout": "LAYOUT", "layers": [["KC_ENTER"]]}'


def test_c2json_stdin():
    result = check_subcommand_stdin("keyboards/handwired/pytest/has_template/keymaps/default/keymap.c", "c2json", "-kb", "handwired/pytest/has_template", "-km", "default", "-")
    check_returncode(result)
    assert result.stdout.strip() == '{"keyboard": "handwired/pytest/has_template", "documentation": "This file is a keymap.json file for handwired/pytest/has_template", "keymap": "default", "layout": "LAYOUT_ortho_1x1", "layers": [["KC_A"]]}'


def test_c2json_nocpp_stdin():
    result = check_subcommand_stdin("keyboards/handwired/pytest/has_template/keymaps/nocpp/keymap.c", "c2json", "--no-cpp", "-kb", "handwired/pytest/has_template", "-km", "default", "-")
    check_returncode(result)
    assert result.stdout.strip() == '{"keyboard": "handwired/pytest/has_template", "documentation": "This file is a keymap.json file for handwired/pytest/has_template", "keymap": "default", "layout": "LAYOUT", "layers": [["KC_ENTER"]]}'


def test_clean():
    result = check_subcommand('clean', '-a')
    check_returncode(result)
    assert result.stdout.count('done') == 2


def test_generate_api():
    result = check_subcommand('generate-api', '--dry-run')
    check_returncode(result)


def test_generate_rgb_breathe_table():
    result = check_subcommand("generate-rgb-breathe-table", "-c", "1.2", "-m", "127")
    check_returncode(result)
    assert 'Breathing center: 1.2' in result.stdout
    assert 'Breathing max:    127' in result.stdout


def test_generate_config_h():
    result = check_subcommand('generate-config-h', '-kb', 'handwired/pytest/basic')
    check_returncode(result)
    assert '#   define DEVICE_VER 0x0001' in result.stdout
    assert '#   define DESCRIPTION handwired/pytest/basic' in result.stdout
    assert '#   define DIODE_DIRECTION COL2ROW' in result.stdout
    assert '#   define MANUFACTURER none' in result.stdout
    assert '#   define PRODUCT pytest' in result.stdout
    assert '#   define PRODUCT_ID 0x6465' in result.stdout
    assert '#   define VENDOR_ID 0xFEED' in result.stdout
    assert '#   define MATRIX_COLS 1' in result.stdout
    assert '#   define MATRIX_COL_PINS { F4 }' in result.stdout
    assert '#   define MATRIX_ROWS 1' in result.stdout
    assert '#   define MATRIX_ROW_PINS { F5 }' in result.stdout


def test_generate_rules_mk():
    result = check_subcommand('generate-rules-mk', '-kb', 'handwired/pytest/basic')
    check_returncode(result)
    assert 'BOOTLOADER ?= atmel-dfu' in result.stdout
    assert 'MCU ?= atmega32u4' in result.stdout


def test_generate_version_h():
    result = check_subcommand('generate-version-h')
    check_returncode(result)
    assert '#define QMK_VERSION' in result.stdout


def test_generate_layouts():
    result = check_subcommand('generate-layouts', '-kb', 'handwired/pytest/basic')
    check_returncode(result)
    assert '#define LAYOUT_custom(k0A) {' in result.stdout


def test_format_json_keyboard():
    result = check_subcommand('format-json', '--format', 'keyboard', 'lib/python/qmk/tests/minimal_info.json')
    check_returncode(result)
    assert result.stdout == '{\n    "keyboard_name": "tester",\n    "maintainer": "qmk",\n    "layouts": {\n        "LAYOUT": {\n            "layout": [\n                { "label": "KC_A", "matrix": [0, 0], "x": 0, "y": 0 }\n            ]\n        }\n    }\n}\n'


def test_format_json_keymap():
    result = check_subcommand('format-json', '--format', 'keymap', 'lib/python/qmk/tests/minimal_keymap.json')
    check_returncode(result)
    assert result.stdout == '{\n    "version": 1,\n    "keyboard": "handwired/pytest/basic",\n    "keymap": "test",\n    "layout": "LAYOUT_ortho_1x1",\n    "layers": [\n                [\n                        "KC_A"\n                ]\n    ]\n}\n'


def test_format_json_keyboard_auto():
    result = check_subcommand('format-json', '--format', 'auto', 'lib/python/qmk/tests/minimal_info.json')
    check_returncode(result)
    assert result.stdout == '{\n    "keyboard_name": "tester",\n    "maintainer": "qmk",\n    "layouts": {\n        "LAYOUT": {\n            "layout": [\n                { "label": "KC_A", "matrix": [0, 0], "x": 0, "y": 0 }\n            ]\n        }\n    }\n}\n'


def test_format_json_keymap_auto():
    result = check_subcommand('format-json', '--format', 'auto', 'lib/python/qmk/tests/minimal_keymap.json')
    check_returncode(result)
    assert result.stdout == '{\n    "keyboard": "handwired/pytest/basic",\n    "keymap": "test",\n    "layers": [\n        ["KC_A"]\n    ],\n    "layout": "LAYOUT_ortho_1x1",\n    "version": 1\n}\n'
