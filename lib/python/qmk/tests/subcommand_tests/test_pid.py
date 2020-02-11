import sys
import os
from tempfile import NamedTemporaryFile

from nose2.tools.decorators import with_setup, with_teardown
from milc import cli

from qmk import keyboard

pre_run_config = cli.config.pid.db_path
test_board_dir = 'keyboards/handwired/onekey/pytest/'


def setup_qmk_config():
    cli.config.pid.db_path = test_board_dir + 'test.json'


def restore_qmk_config():
    if pre_run_config is None:
        del cli.config.pid.db_path
    else:
        cli.config.pid.db_path = pre_run_config


@with_setup(setup_qmk_config)
@with_teardown(restore_qmk_config)
def test_pid():
    pass
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
