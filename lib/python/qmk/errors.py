class NoSuchKeyboardError(Exception):
    """Raised when we can't find a keyboard/keymap directory.
    """
    def __init__(self, message):
        self.message = message


class KeymapAlreadyExistsError(Exception):
    """Raised when the keymap for a keyboard already exists.
    """
