"""Simple confirmation dialog for array item deletion.
"""
from asciimatics.widgets import Frame, Layout, Label, Button
from asciimatics.event import KeyboardEvent
from asciimatics.screen import Screen


class DeleteConfirmDialog(Frame):
    """Modal dialog for confirming item deletion.
    """
    def __init__(self, screen, item_index, on_confirm, on_cancel):
        """Initialize the delete confirmation dialog.

        Args:
            screen
                Asciimatics Screen instance.
            item_index
                Index of item to delete.
            on_confirm
                Callback to invoke when user confirms deletion.
            on_cancel
                Callback to invoke when user cancels.
        """
        super().__init__(screen, 7, 50, has_border=True, title="Confirm Delete", is_modal=True)

        self._on_confirm = on_confirm
        self._on_cancel = on_cancel

        layout = Layout([100], fill_frame=True)
        self.add_layout(layout)

        layout.add_widget(Label(""))
        layout.add_widget(Label("Delete item [%d]?" % item_index, height=2))
        layout.add_widget(Label(""))

        button_layout = Layout([1, 1, 1])
        self.add_layout(button_layout)
        button_layout.add_widget(Button("Yes (y)", self._yes), 0)
        button_layout.add_widget(Button("No (n)", self._no), 2)

        self.fix()

    def _dismiss(self):
        """Remove dialog from the scene.
        """
        self._scene.remove_effect(self)

    def _yes(self):
        """Handle Yes button click.
        """
        self._dismiss()
        self._on_confirm()

    def _no(self):
        """Handle No button click.
        """
        self._dismiss()
        self._on_cancel()

    def process_event(self, event):
        """Process keyboard events.

        Args:
            event
                Event to process.

        Returns:
            Event processing result.
        """
        if isinstance(event, KeyboardEvent):
            if event.key_code in (ord('y'), ord('Y')):
                self._yes()
                return None
            if event.key_code in (ord('n'), ord('N'), Screen.KEY_ESCAPE):
                self._no()
                return None

        return super().process_event(event)
