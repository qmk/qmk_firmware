import subprocess


def check_subcommand(command, *args):
    cmd = ['bin/qmk', command] + list(args)
    return subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)


def test_cformat():
    assert check_subcommand('cformat', 'tmk_core/common/backlight.c').returncode == 0


def test_compile():
    assert check_subcommand('compile', '-kb', 'handwired/onekey/pytest', '-km', 'default').returncode == 0


def test_config():
    result = check_subcommand('config')
    assert result.returncode == 0
    assert 'general.color' in result.stdout


def test_doctor():
    result = check_subcommand('doctor')
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
