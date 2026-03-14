"""Array row widget for navigable array fields.

This module provides the ArrayRow widget, which displays array fields
in the keyboard configuration editor and allows navigation into arrays
for viewing and editing array items.
"""

from asciimatics.widgets import Button
from qmk.cli.edit.widgets.base import FieldWidget


class ArrayRow(FieldWidget):
    """Widget for navigating into arrays.

    Displays array fields as a navigable button showing the item count.
    Clicking the button navigates into the array to view and edit items.
    Supports both simple arrays (strings, numbers) and object arrays.
    """
    def __init__(self, name, schema, state, path, on_navigate=None):
        """Initialize the array row widget.

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
        """Return asciimatics Button widget for navigation.

        Returns:
            Button widget configured with navigation handler.
        """
        display_text = "%s: %s" % (self.label, self.get_display_value())
        self._widget = Button(text=display_text, on_click=self._on_navigate, name=self._path_string)
        return self._widget

    def set_on_navigate(self, callback):
        """Override the default navigation handler.

        Must be called before as_asciimatics_widget().
        """
        self._custom_navigate = callback

    def _on_navigate(self):
        """Handle navigation into this array.

        Pushes the array field name onto the navigation path,
        triggering a view update to show array items.
        """
        if self._custom_navigate:
            self._custom_navigate()
        else:
            self._state.navigate_into(self._name)

    def get_display_value(self):
        """Return item count or empty indicator for display.

        Returns:
            String showing item count like '[3 items] [->]' or '[empty] [->]'.
        """
        val = self.value
        if val is None or not isinstance(val, list):
            return "[empty] [->]"

        item_count = len(val)
        if item_count == 0:
            return "[empty] [->]"

        return "[%d items] [->]" % item_count
