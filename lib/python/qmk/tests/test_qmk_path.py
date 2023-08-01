import os
from pathlib import Path

import qmk.path


def test_keymap_pytest_basic():
    path = qmk.path.keymap('handwired/pytest/basic', 'default')
    assert path.samefile('keyboards/handwired/pytest/basic/keymaps/default')


def test_normpath():
    path = qmk.path.normpath('lib/python')
    assert path.samefile(Path(os.environ['ORIG_CWD']) / 'lib/python')
