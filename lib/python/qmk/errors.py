class Error(Exception):
    pass


class NoSuchKeyboardError(Error):
    """Raised when we can't find a keyboard/keymap directory.
    """
    def __init__(self, message):
        self.message = message
