import sys
import subprocess
from tempfile import NamedTemporaryFile
import filecmp
import shutil

from nose2.tools.decorators import with_setup, with_teardown
from milc import cli


pre_run_config = cli.config.pid.db_path
test_files = 'lib/python/qmk/tests/templates/test_pid/'
test_dir = 'lib/python/qmk/tests/test_pid/'

# The configs to test on, output to check, full sha-1 has of their path.
configs = [
    ("othervid_comments/config.h", "Keyboard does not use QMK VID, or it's not a keyboard config", None),
    ("qmkvid_comments/config.h", "Assigned PID 0x%s", "C147BFB525F9A0280BD9D89A1DABEADB3FEB4620"),
    ("qmkvid_no_comments/config.h", "Assigned PID 0x%s", "5749D78610C7B6F1536450B0732E8B8115CF09FC")
]


def setup():
    shutil.copytree(test_files, test_dir)


def teardown():
    shutil.rmtree(test_dir)


def run_qmk_pid(cfgs, apply=False, commit=False):
    if isinstance(cfgs, str):
        cfgs = [cfgs]
    cfgs = [test_dir + c for c in cfgs]

    command = []
    if apply:
        command.append('--apply')
    if commit:
        command.append('--commit')
    command += cfgs

    result = subprocess.run(
        [sys.executable, 'bin/qmk', 'pid', '--db', '%stest.json' % (test_dir)] + command,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        universal_newlines=True
    )
    return result


@with_setup(setup)
@with_teardown(teardown)
def test_pid():

    # Run one by one without --apply
    for config in configs:
        if config[2] is None:
            assert config[1] in run_qmk_pid(config[0]).stdout
        else:
            assert config[1] % config[2][0:4] in run_qmk_pid(config[0]).stdout

    # Run all at once without --apply
    cfgs = [c[0] for c in configs]
    result = run_qmk_pid(cfgs)

    for config in configs:
        if config[2] is None:
            assert config[1] in result.stdout
        else:
            assert config[1] % config[2][0:4] in result.stdout

    # Run all at once and apply PID
    result = run_qmk_pid(cfgs, apply=True)
    assert 'Applying PID' in result

    for config in configs:
        ref_file = "%sreference_configs/%s.h" % (test_dir, config.split('/')[:-1])
        assert filecmp("%s%s" % (test_dir, config), ref_file)


    # run qmk pid with all but one config and --apply
    #   check that the correct PIDS are applied
    #   check that it doesn't apply to other vids than 0x03A8
    #   check that comments have been carried over
    # run qmk pid with only one config (the remaining one) and --apply
    #   check that the pid has been applied
    # force pid collision by renaming assigned keyboard in test.json
    #   verify that it doesn't exceed max tries
    # change PID in already assigned file, run that file again.
    #   verify that it warns about the changed pid and re-applies it
    # run without --apply
    #   verify that it generates but doesn't apply PID
    # run with --commit but not --apply
    #   verify that it errors out
