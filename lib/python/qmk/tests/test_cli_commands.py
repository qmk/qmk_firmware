import platform

from subprocess import STDOUT, PIPE

from qmk.commands import run

is_windows = 'windows' in platform.platform().lower()


def check_subcommand(command, *args):
    cmd = ['bin/qmk', command] + list(args)
    result = run(cmd, stdout=PIPE, stderr=STDOUT, universal_newlines=True)
    return result


def check_returncode(result, expected=[0]):
    """Print stdout if `result.returncode` does not match `expected`.
    """
    if result.returncode not in expected:
        print('`%s` stdout:' % ' '.join(result.args))
        print(result.stdout)
        print('returncode:', result.returncode)
    assert result.returncode in expected


def test_cformat():
    result = check_subcommand('cformat', 'quantum/matrix.c')
    check_returncode(result)


def test_compile():
    result = check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default', '-n')
    check_returncode(result)


def test_compile_json():
    result = check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default_json', '-n')
    check_returncode(result)


def test_flash():
    result = check_subcommand('flash', '-kb', 'handwired/onekey/pytest', '-km', 'default', '-n')
    check_returncode(result)


def test_flash_bootloaders():
    result = check_subcommand('flash', '-b')
    check_returncode(result, [1])


def test_config():
    result = check_subcommand('config')
    check_returncode(result)
    assert 'general.color' in result.stdout


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


def test_pyformat():
    result = check_subcommand('pyformat')
    check_returncode(result)
    assert 'Successfully formatted the python code' in result.stdout


def test_list_keyboards():
    result = check_subcommand('list-keyboards')
    check_returncode(result)
    # check to see if a known keyboard is returned
    # this will fail if handwired/onekey/pytest is removed
    assert 'handwired/onekey/pytest' in result.stdout


def test_list_keymaps():
    result = check_subcommand('list-keymaps', '-kb', 'handwired/onekey/pytest')
    check_returncode(result)
    assert 'default' and 'test' in result.stdout


def test_list_keymaps_long():
    result = check_subcommand('list-keymaps', '--keyboard', 'handwired/onekey/pytest')
    check_returncode(result)
    assert 'default' and 'test' in result.stdout


def test_list_keymaps_kb_only():
    result = check_subcommand('list-keymaps', '-kb', 'niu_mini')
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
    check_returncode(result, [1])
    assert 'does not exist' in result.stdout


def test_json2c():
    result = check_subcommand('json2c', 'keyboards/handwired/onekey/keymaps/default_json/keymap.json')
    check_returncode(result)
    assert result.stdout == '#include QMK_KEYBOARD_H\nconst uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\t[0] = LAYOUT_ortho_1x1(KC_A)};\n\n'


def test_info():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest')
    check_returncode(result)
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert 'Layout:' not in result.stdout
    assert 'k0' not in result.stdout


def test_info_keyboard_render():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest', '-l')
    check_returncode(result)
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert 'Layouts:' in result.stdout
    assert 'k0' in result.stdout


def test_info_keymap_render():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest', '-km', 'default_json')
    check_returncode(result)
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout

    if is_windows:
        assert '|A |' in result.stdout
    else:
        assert '│A │' in result.stdout


def test_info_matrix_render():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest', '-m')
    check_returncode(result)
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert 'LAYOUT_ortho_1x1' in result.stdout

    if is_windows:
        assert '|0A|' in result.stdout
    else:
        assert '│0A│' in result.stdout

    assert 'Matrix for "LAYOUT_ortho_1x1"' in result.stdout


def test_c2json():
    result = check_subcommand("c2json", "-kb", "handwired/onekey/pytest", "-km", "default", "keyboards/handwired/onekey/keymaps/default/keymap.c")
    check_returncode(result)
    assert result.stdout.strip() == '{"keyboard": "handwired/onekey/pytest", "documentation": "This file is a keymap.json file for handwired/onekey/pytest", "keymap": "default", "layout": "LAYOUT_ortho_1x1", "layers": [["KC_A"]]}'


def test_c2json_nocpp():
    result = check_subcommand("c2json", "--no-cpp", "-kb", "handwired/onekey/pytest", "-km", "default", "keyboards/handwired/onekey/keymaps/pytest_nocpp/keymap.c")
    check_returncode(result)
    assert result.stdout.strip() == '{"keyboard": "handwired/onekey/pytest", "documentation": "This file is a keymap.json file for handwired/onekey/pytest", "keymap": "default", "layout": "LAYOUT", "layers": [["KC_ENTER"]]}'


def test_clean():
    result = check_subcommand('clean', '-a')
    check_returncode(result)
    assert result.stdout.count('done') == 2


def test_generate_rgb_breathe_table():
    result = check_subcommand("generate-rgb-breathe-table", "-c", "1.2", "-m", "127")
    check_returncode(result)
    assert 'Breathing center: 1.2' in result.stdout
    assert 'Breathing max:    127' in result.stdout
