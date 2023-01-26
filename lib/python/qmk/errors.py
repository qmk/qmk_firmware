class NoSuchKeyboardError(Exception):
    """Raised when we can't find a keyboard/keymap directory.
    """
    def __init__(self, message):
        self.message = message


class CppError(Exception):
    """Raised when 'cpp' cannot process a file.
    """
    def __init__(self, message):
        self.message = message
