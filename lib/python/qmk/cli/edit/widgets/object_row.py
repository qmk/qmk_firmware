"""Object row widget for navigable nested objects."""

from asciimatics.widgets import Button
from qmk.cli.edit.widgets.base import FieldWidget


class ObjectRow(FieldWidget):
    """Widget for navigating into nested objects."""
    def __init__(self, name, schema, state, path, on_navigate=None):
        """Initialize the object row widget.

        Args:
            name
                Field name.
            schema
                Property schema fragment.
            state
                EditorState instance.
            path
                Tuple path to this field.
            on_navigate
                Optional callback overriding default navigation.
        """
        super().__init__(name, schema, state, path)
        self._widget = None
        self._custom_navigate = on_navigate

    def as_asciimatics_widget(self):
        """Return asciimatics Button widget for navigation."""
        self._widget = Button(
            text=self.label + " [->]",
            on_click=self._on_navigate,
            name=self._path_string,
        )
        return self._widget

    def set_on_navigate(self, callback):
        """Override the default navigation handler.

        Must be called before as_asciimatics_widget().
        """
        self._custom_navigate = callback

    def _on_navigate(self):
        """Handle navigation into this object."""
        if self._custom_navigate:
            self._custom_navigate()
        else:
            self._state.navigate_into(self._name)

    def get_display_value(self):
        """Return navigation indicator for display."""
        return "[->]"
