"""Enum field widget for dropdown picker."""

from asciimatics.widgets import DropdownList
from qmk.cli.edit.widgets.base import FieldWidget


class EnumField(FieldWidget):
    """Widget for selecting from enumerated values."""
    def __init__(self, name, schema, state, path):
        """Initialize the enum field widget.

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
        self._enum_values = state.schema_loader.get_enum_values(schema) or []

    def as_asciimatics_widget(self):
        """Return asciimatics DropdownList widget."""
        options = [("(unset)", None)] + [(str(v), v) for v in self._enum_values]

        self._widget = DropdownList(
            options,
            label=self.label + ":",
            name=self._path_string,
            on_change=self._on_change,
        )

        current = self.value
        if current is None:
            self._widget.value = None
        else:
            for _, val in options:
                if val == current:
                    self._widget.value = val
                    break

        return self._widget

    def _on_change(self):
        """Handle selection change."""
        if self._widget:
            self.value = self._widget.value
