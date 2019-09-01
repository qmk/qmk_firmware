class DirectoryError(Exception):
    """Raised when we have generic directory issues
    """
    def __init__(self, message):
        """Default initialization method

        Args
            message
                Message to show when exception is raised
        """
        self.message = message


class NoSuchKeyboardError(DirectoryError):
    """Raised when we can't find a keyboard/keymap directory.
    """
    pass
