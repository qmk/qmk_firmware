"""Error dialog for displaying validation errors.
"""
# TODO(unassigned): Write integration tests for TUI views once testing infrastructure supports headless asciimatics testing

from asciimatics.widgets import Frame, Layout, Label, TextBox
from asciimatics.event import KeyboardEvent
from asciimatics.screen import Screen


class ErrorDialog(Frame):
    """Modal dialog for displaying validation or error messages.
    """
    def __init__(self, screen, errors, on_close=None):
        """Initialize the error dialog.

        Args:
            screen
                Asciimatics Screen instance.
            errors
                List of error dicts with 'path' and 'message' keys.
            on_close
                Optional callback when dialog is dismissed.
        """
        height = min(screen.height - 4, len(errors) * 2 + 8)
        width = min(screen.width - 4, 80)

        super().__init__(screen, height, width, has_border=True, title="Validation Errors", reduce_cpu=True, is_modal=True)

        self._on_close = on_close
        self._errors = errors

        layout = Layout([100], fill_frame=True)
        self.add_layout(layout)

        layout.add_widget(Label("The following errors were found:"))
        layout.add_widget(Label(""))

        error_lines = ["%s: %s" % (error.get('path', '<unknown>'), error.get('message', 'Unknown error')) for error in errors]

        error_text = "\n".join(error_lines)
        text_box = TextBox(height=height - 6, as_string=True, line_wrap=True, readonly=True)
        text_box.value = error_text
        layout.add_widget(text_box)

        hint_layout = Layout([100])
        self.add_layout(hint_layout)
        hint_layout.add_widget(Label("Press Enter or Esc to close"))

        self.fix()

    def _on_ok(self):
        """Dismiss the dialog and invoke the on_close callback.
        """
        self._scene.remove_effect(self)
        if self._on_close:
            self._on_close()

    def process_event(self, event):
        """Process keyboard events for shortcuts.

        Args:
            event
                Asciimatics event to process.

        Returns:
            Event processing result from parent class.
        """
        if isinstance(event, KeyboardEvent):
            if event.key_code in (Screen.KEY_ESCAPE, ord('\n'), ord('\r')):
                self._on_ok()
                return None

        return super().process_event(event)
