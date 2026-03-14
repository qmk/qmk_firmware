"""Confirm dialog for unsaved changes.
"""
# TODO(unassigned): Write integration tests for TUI views once testing infrastructure supports headless asciimatics testing

from asciimatics.widgets import Frame, Layout, Label, Button
from asciimatics.event import KeyboardEvent
from asciimatics.screen import Screen


class ConfirmDialog(Frame):
    """Modal dialog for confirming unsaved changes.
    """
    def __init__(self, screen, on_close=None):
        """Initialize the confirm dialog.

        Args:
            screen
                Asciimatics Screen instance.
            on_close
                Callback receiving action: 'save', 'discard', or 'cancel'.
        """
        height = 9
        width = min(screen.width - 4, 60)

        super().__init__(screen, height, width, has_border=True, title="Unsaved Changes", reduce_cpu=True, is_modal=True)

        self._on_close = on_close

        layout = Layout([100], fill_frame=True)
        self.add_layout(layout)

        layout.add_widget(Label("You have unsaved changes."))
        layout.add_widget(Label("What would you like to do?"))
        layout.add_widget(Label(""))

        button_layout = Layout([1, 1, 1])
        self.add_layout(button_layout)
        button_layout.add_widget(Button("Save", self._on_save), 0)
        button_layout.add_widget(Button("Discard", self._on_discard), 2)

        hint_layout = Layout([100])
        self.add_layout(hint_layout)
        hint_layout.add_widget(Label("Press ESC to cancel"))

        self.fix()

    def _on_save(self):
        """Handle Save button press.
        """
        self._dismiss('save')

    def _on_discard(self):
        """Handle Discard button press.
        """
        self._dismiss('discard')

    def _dismiss(self, action):
        """Remove dialog from scene and invoke callback.
        """
        self._scene.remove_effect(self)
        if self._on_close:
            self._on_close(action)

    def process_event(self, event):
        """Process keyboard events for shortcuts.

        Args:
            event
                Asciimatics event to process.

        Returns:
            Event processing result from parent class.
        """
        if isinstance(event, KeyboardEvent):
            key_lower = chr(event.key_code).lower() if 32 <= event.key_code < 127 else ''

            if key_lower == 's':
                self._on_save()
                return None
            if key_lower == 'd':
                self._on_discard()
                return None
            if event.key_code == Screen.KEY_ESCAPE:
                self._dismiss('cancel')
                return None

        return super().process_event(event)
