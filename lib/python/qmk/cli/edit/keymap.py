"""Configurable keybinding mapping for editor navigation."""

from asciimatics.screen import Screen

_CTRL_SLASH = 31  # Ctrl+/ sends 0x1F in most terminals

_KEY_NAMES = {
    Screen.KEY_UP: "up",
    Screen.KEY_DOWN: "down",
    Screen.KEY_DELETE: "Delete",
    Screen.KEY_ESCAPE: "Esc",
    ord("\n"): "Enter",
    ord("\r"): "Enter",
    ord(" "): "Space",
    Screen.ctrl(Screen.KEY_UP): "Ctrl+up",
    Screen.ctrl(Screen.KEY_DOWN): "Ctrl+down",
    _CTRL_SLASH: "Ctrl+/",
}


class Keymap:
    """Configurable keybinding mapping for the TUI editor."""

    DEFAULTS = {
        "navigate_up": [Screen.KEY_UP],
        "navigate_down": [Screen.KEY_DOWN],
        "select": [ord("\n"), ord("\r")],
        "back": [Screen.KEY_ESCAPE],
        "search": [ord("/")],
        "save": [Screen.ctrl("s")],
        "quit": [ord("q")],
        "help": [_CTRL_SLASH],
        "validate": [Screen.ctrl("e")],
        "add_item": [Screen.ctrl("a")],
        "delete_item": [Screen.ctrl("d"), Screen.KEY_DELETE],
        "move_up": [Screen.ctrl("p")],
        "move_down": [Screen.ctrl("n")],
    }

    def __init__(self, overrides=None):
        """Initialize with optional overrides.

        Args:
            overrides
                Dictionary mapping action names to key code lists.
        """
        self._bindings = dict(self.DEFAULTS)
        if overrides:
            self._bindings.update(overrides)

    def matches(self, action, key_code):
        """Return True if key_code matches the action's binding.

        Args:
            action
                Action name like 'save' or 'quit'.
            key_code
                Integer key code from keyboard event.

        Returns:
            True if key_code is bound to the action.
        """
        if action not in self._bindings:
            return False

        return key_code in self._bindings[action]

    def get_display(self, action):
        """Return human-readable string for action's primary key.

        Args:
            action
                Action name like 'save' or 'quit'.

        Returns:
            String representation of the primary key binding.
        """
        if action not in self._bindings or not self._bindings[action]:
            return ""

        primary_key = self._bindings[action][0]
        return self._format_key(primary_key)

    def _format_key(self, key_code):
        """Format a key code as human-readable string.

        Args:
            key_code
                Integer key code.

        Returns:
            Human-readable string like 'Ctrl+S' or 'Enter'.
        """
        if key_code in _KEY_NAMES:
            return _KEY_NAMES[key_code]

        if 1 <= key_code <= 26:
            return "Ctrl+%s" % chr(ord("a") + key_code - 1).upper()

        if 32 <= key_code <= 126:
            return chr(key_code)

        return "?"
