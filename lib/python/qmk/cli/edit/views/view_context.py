"""Shared data container for view collaborators.

Bundles the references every collaborator needs so they can be passed
as a single object instead of five separate parameters.
"""


class ViewContext:
    """Read-only data bag holding shared state for all view collaborators.

    Args:
        state
            The EditorState instance that owns working data and navigation.

        keyboard
            Keyboard identifier string (e.g. 'planck/rev6').

        keymap
            Keymap name string.

        registry
            The widget registry used for field type resolution.

        config
            Optional configuration object (may be None).
    """
    def __init__(self, state, keyboard, keymap, registry, config):
        self.state = state
        self.keyboard = keyboard
        self.keymap = keymap
        self.registry = registry
        self.config = config
