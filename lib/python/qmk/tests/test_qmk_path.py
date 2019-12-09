import os

import qmk.path


def test_keymap_onekey_pytest():
    path = qmk.path.keymap('handwired/onekey/pytest')
    assert path == 'keyboards/handwired/onekey/keymaps'


def test_normpath():
    path = qmk.path.normpath('lib/python')
    assert path == os.path.join(os.environ['ORIG_CWD'], 'lib/python')
