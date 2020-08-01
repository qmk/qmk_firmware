import subprocess
from qmk.commands import run


def check_subcommand(command, *args):
    cmd = ['bin/qmk', command] + list(args)
    result = run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    return result


def check_returncode(result, expected=0):
    """Print stdout if `result.returncode` does not match `expected`.
    """
    if result.returncode != expected:
        print('`%s` stdout:' % ' '.join(result.args))
        print(result.stdout)
        print('returncode:', result.returncode)
    assert result.returncode == expected


def test_cformat():
    result = check_subcommand('cformat', 'quantum/matrix.c')
    check_returncode(result)


def test_compile():
    result = check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default', '-n')
    check_returncode(result)


def test_flash():
    result = check_subcommand('flash', '-kb', 'handwired/onekey/pytest', '-km', 'default', '-n')
    check_returncode(result)


def test_flash_bootloaders():
    result = check_subcommand('flash', '-b')
    check_returncode(result, 1)


def test_config():
    result = check_subcommand('config')
    check_returncode(result)
    assert 'general.color' in result.stdout


def test_kle2json():
    result = check_subcommand('kle2json', 'kle.txt', '-f')
    check_returncode(result)


def test_doctor():
    result = check_subcommand('doctor', '-n')
    check_returncode(result)
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
    check_returncode(result, 0)
    assert 'default' and 'test' in result.stdout


def test_list_keymaps_long():
    result = check_subcommand('list-keymaps', '--keyboard', 'handwired/onekey/pytest')
    check_returncode(result, 0)
    assert 'default' and 'test' in result.stdout


def test_list_keymaps_kb_only():
    result = check_subcommand('list-keymaps', '-kb', 'niu_mini')
    check_returncode(result, 0)
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_vendor_kb():
    result = check_subcommand('list-keymaps', '-kb', 'ai03/lunar')
    check_returncode(result, 0)
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_vendor_kb_rev():
    result = check_subcommand('list-keymaps', '-kb', 'kbdfans/kbd67/mkiirgb/v2')
    check_returncode(result, 0)
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_no_keyboard_found():
    result = check_subcommand('list-keymaps', '-kb', 'asdfghjkl')
    check_returncode(result, 1)
    assert 'does not exist' in result.stdout


def test_json2c():
    result = check_subcommand('json2c', 'keyboards/handwired/onekey/keymaps/default_json/keymap.json')
    check_returncode(result, 0)
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
    assert '│A │' in result.stdout


def test_info_matrix_render():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest', '-m')
    check_returncode(result)
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert 'LAYOUT_ortho_1x1' in result.stdout
    assert '│0A│' in result.stdout
    assert 'Matrix for "LAYOUT_ortho_1x1"' in result.stdout
