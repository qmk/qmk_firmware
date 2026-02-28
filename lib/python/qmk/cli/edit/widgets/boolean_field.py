"""Boolean field widget for tri-state toggle."""

from asciimatics.widgets import Button
from qmk.cli.edit.widgets.base import FieldWidget


class BooleanField(FieldWidget):
    """Widget for editing boolean values with tri-state support.

    States: unset (None) -> true -> false -> unset
    """
    def __init__(self, name, schema, state, path):
        """Initialize the boolean field widget.

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
        """Return asciimatics Button widget for tri-state toggle."""
        self._widget = Button(
            text=self._get_button_text(),
            on_click=self._on_click,
            name=self._path_string,
        )
        return self._widget

    def _get_button_text(self):
        """Get button text based on current value.

        Returns:
            Button text showing label and state indicator.
        """
        current = self.value
        if current is None:
            state_indicator = "[ ]"
        elif current:
            state_indicator = "[x]"
        else:
            state_indicator = "[-]"
        return "%s %s" % (self.label, state_indicator)

    def _on_click(self):
        """Handle button click through tri-state cycle.

        Cycle: unset (None) -> true -> false -> unset
        """
        current = self.value

        if current is None:
            self.value = True
        elif current is True:
            self.value = False
        else:
            self.value = None

        if self._widget:
            self._widget.text = self._get_button_text()

    def get_display_value(self):
        """Return string representation for display in field list."""
        val = self.value
        if val is None:
            return "[ ]"
        if val:
            return "[x]"
        return "[-]"
