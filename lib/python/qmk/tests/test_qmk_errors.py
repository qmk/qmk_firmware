from qmk.errors import NoSuchKeyboardError


def test_NoSuchKeyboardError():
    try:
        raise NoSuchKeyboardError("test message")
    except NoSuchKeyboardError as e:
        assert e.message == 'test message'
