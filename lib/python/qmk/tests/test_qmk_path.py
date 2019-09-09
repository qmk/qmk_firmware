import os

import qmk.path


def test_keymap_onekey_pytest():
    path = qmk.path.keymap('handwired/onekey/pytest')
    assert path == 'keyboards/handwired/onekey/keymaps'


def test_normpath():
    path = qmk.path.normpath('lib/python')
    assert path == os.environ['ORIG_CWD'] + '/lib/python'


def test_subcommand_modules():
    count = 0
    for module in qmk.path.subcommand_modules():
        count += 1
        assert module.startswith('qmk.cli.')

    assert count > 9
