"""Runtime configuration from CLI flags.

This module provides the EditorConfig class, which encapsulates
runtime configuration options derived from CLI flags. It allows
behavioral configuration of the keyboard editor without using
global state.
"""


class EditorConfig:
    """Runtime configuration from CLI flags.

    Holds configuration options that affect editor behavior,
    such as whether to skip confirmation dialogs. This allows
    the editor to be configured at runtime based on user preferences
    passed via command-line flags.
    """
    def __init__(self, no_confirm_delete=False):
        """Initialize with CLI flag values.

        Args:
            no_confirm_delete
                If True, skip delete confirmation dialogs.
        """
        self.no_confirm_delete = no_confirm_delete
