import subprocess
from qmk.commands import run


def check_subcommand(command, *args):
    cmd = ['bin/qmk', command] + list(args)
    return run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)


def test_cformat():
    result = check_subcommand('cformat', 'quantum/matrix.c')
    assert result.returncode == 0


def test_compile():
    # keyboard compile
    assert check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default').returncode == 0

    # json compile
    test_json = ['encoder', 'no_encoder']
    for j in test_json:
        assert check_subcommand('compile', f'keyboards/handwired/onekey/encodertest/{j}.json').returncode == 0  # with encoder


def test_flash():
    assert check_subcommand('flash', '-b').returncode == 1
    assert check_subcommand('flash').returncode == 1


def test_config():
    result = check_subcommand('config')
    assert result.returncode == 0
    assert 'general.color' in result.stdout


def test_kle2json():
    assert check_subcommand('kle2json', 'kle.txt', '-f').returncode == 0


def test_doctor():
    result = check_subcommand('doctor', '-n')
    assert result.returncode == 0
    assert 'QMK Doctor is checking your environment.' in result.stderr
    assert 'QMK is ready to go' in result.stderr


def test_hello():
    result = check_subcommand('hello')
    assert result.returncode == 0
    assert 'Hello,' in result.stderr


def test_pyformat():
    result = check_subcommand('pyformat')
    assert result.returncode == 0
    assert 'Successfully formatted the python code' in result.stderr


def test_list_keyboards():
    result = check_subcommand('list-keyboards')
    assert result.returncode == 0
    # check to see if a known keyboard is returned
    # this will fail if handwired/onekey/pytest is removed
    assert 'handwired/onekey/pytest' in result.stdout


def test_list_keymaps():
    result = check_subcommand("list-keymaps", "-kb", "handwired/onekey/pytest")
    assert result.returncode == 0
    assert "default" and "test" in result.stdout


def test_list_keymaps_no_keyboard_found():
    result = check_subcommand("list-keymaps", "-kb", "asdfghjkl")
    assert result.returncode == 0
    assert "does not exist" in result.stdout
