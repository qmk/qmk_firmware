import subprocess
from qmk.commands import run


def check_subcommand(command, *args):
    cmd = ['bin/qmk', command] + list(args)
    result = run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    return result


def print_stdout_if_error(result):
    if result.returncode != 0:
        print('`qmk info -kb handwired/onekey/pytest` stdout:')
        print(result.stdout)
        print('returncode:', result.returncode)


def test_cformat():
    result = check_subcommand('cformat', 'quantum/matrix.c')
    print_stdout_if_error(result)
    assert result.returncode == 0


def test_compile():
    result = check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default', '-n')
    print_stdout_if_error(result)
    assert result.returncode == 0


def test_flash():
    result = check_subcommand('flash', '-kb', 'handwired/onekey/pytest', '-km', 'default', '-n')
    print_stdout_if_error(result)
    assert result.returncode == 0


def test_flash_bootloaders():
    result = check_subcommand('flash', '-b')
    assert result.returncode == 1


def test_config():
    result = check_subcommand('config')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'general.color' in result.stdout


def test_kle2json():
    result = check_subcommand('kle2json', 'kle.txt', '-f')
    print_stdout_if_error(result)
    assert result.returncode == 0


def test_doctor():
    result = check_subcommand('doctor', '-n')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'QMK Doctor is checking your environment.' in result.stdout
    assert 'QMK is ready to go' in result.stdout


def test_hello():
    result = check_subcommand('hello')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'Hello,' in result.stdout


def test_pyformat():
    result = check_subcommand('pyformat')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'Successfully formatted the python code' in result.stdout


def test_list_keymaps():
    result = check_subcommand('list-keymaps', '-kb', 'handwired/onekey/pytest')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'default' and 'test' in result.stdout


def test_list_keymaps_long():
    result = check_subcommand('list-keymaps', '--keyboard', 'handwired/onekey/pytest')
    assert result.returncode == 0
    assert 'default' and 'test' in result.stdout


def test_list_keymaps_kb_only():
    result = check_subcommand('list-keymaps', '-kb', 'niu_mini')
    assert result.returncode == 0
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_vendor_kb():
    result = check_subcommand('list-keymaps', '-kb', 'ai03/lunar')
    assert result.returncode == 0
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_vendor_kb_rev():
    result = check_subcommand('list-keymaps', '-kb', 'kbdfans/kbd67/mkiirgb/v2')
    assert result.returncode == 0
    assert 'default' and 'via' in result.stdout


def test_list_keymaps_no_keyboard_found():
    result = check_subcommand('list-keymaps', '-kb', 'asdfghjkl')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'does not exist' in result.stdout


def test_info():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert 'LAYOUT:' not in result.stdout
    assert 'k0' not in result.stdout


def test_info_keyboard_render():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest', '-l')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert 'LAYOUT:' in result.stdout
    assert 'k0' in result.stdout


def test_info_keymap_render():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest', '-km', 'default')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert '│NO│' in result.stdout


def test_info_matrix_render():
    result = check_subcommand('info', '-kb', 'handwired/onekey/pytest', '-m')
    print_stdout_if_error(result)
    assert result.returncode == 0
    assert 'Keyboard Name: handwired/onekey/pytest' in result.stdout
    assert 'Processor: STM32F303' in result.stdout
    assert 'LAYOUT' in result.stdout
    assert '│0A│' in result.stdout
    assert 'Matrix for "LAYOUT"' in result.stdout
