"""Text field widget for string input."""

from asciimatics.widgets import Text
from qmk.cli.edit.widgets.base import FieldWidget


class TextField(FieldWidget):
    """Widget for editing string values."""
    def __init__(self, name, schema, state, path):
        """Initialize the text field widget.

        Args:
            name
                Field name.
            schema
                Property schema fragment.
            state
                EditorState instance.
            path
                Tuple path to this field.
        """
        super().__init__(name, schema, state, path)
        self._widget = None

    def as_asciimatics_widget(self):
        """Return asciimatics Text widget."""
        self._widget = Text(label=self.label + ":", name=self._path_string, on_change=self._on_change)
        self._widget.value = self.value or ""
        return self._widget

    def _on_change(self):
        """Handle value change."""
        if self._widget:
            new_value = self._widget.value
            self.value = new_value if new_value else None
