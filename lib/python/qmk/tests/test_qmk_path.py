import os
from pathlib import Path

import qmk.path


def test_keymap_onekey_pytest():
    path = qmk.path.keymap('handwired/onekey/pytest')
    assert path.samefile('keyboards/handwired/onekey/keymaps')


def test_normpath():
    path = qmk.path.normpath('lib/python')
    assert path.samefile(Path(os.environ['ORIG_CWD']) / 'lib/python')
