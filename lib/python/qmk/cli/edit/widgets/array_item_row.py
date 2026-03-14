"""Array item row widget for individual array items.

This module provides the ArrayItemRow widget, which displays individual
items within an array. It shows the item index and value for simple types,
or the index and required field values for object types. Clicking the widget
navigates into the item for editing.
"""

from asciimatics.widgets import Button
from qmk.cli.edit.widgets.base import FieldWidget
from qmk.cli.edit.widgets.numeric_field import NumericField
from qmk.cli.edit.widgets.text_field import TextField


class ArrayItemRow(FieldWidget):
    """Widget representing one item in an array.

    For object types, displays as a navigable button showing required field values.
    For simple types (strings, numbers), displays as an editable text field.
    """
    def __init__(self, index, item_schema, state, path, on_navigate=None):
        """Initialize the array item row widget.

        Args:
            index
                Integer position in array.
            item_schema
                Schema for array items.
            state
                EditorState instance.
            path
                Tuple path including index, e.g. ('encoder', 'rotary', 0).
            on_navigate
                Optional callback overriding default navigation for object items.
        """
        super().__init__(str(index), item_schema, state, path)
        self._index = index
        self._widget = None
        self._delegate = None
        self._custom_navigate = on_navigate

    @property
    def index(self):
        """Integer position in array."""
        return self._index

    def as_asciimatics_widget(self):
        """Return asciimatics widget for navigation/editing.

        For object types, returns a Button for navigation.
        For simple types, delegates to a typed widget (NumericField
        or TextField) that handles coercion and validation.

        Returns:
            Button or Text widget.
        """
        if self._schema.get("type") == "object":
            self._widget = Button(
                text=self.get_display_value(),
                on_click=self._on_navigate,
                name=self._path_string,
            )
            return self._widget

        self._delegate = self._create_delegate()
        self._widget = self._init_delegate_widget()
        # asciimatics Text.label is a read-only property; _label is the
        # underlying attribute that stores the display text.
        self._widget._label = "[%d]" % self._index
        return self._widget

    def _init_delegate_widget(self):
        """Initialize the delegate's asciimatics widget safely.

        Suppresses the on_change callback during widget creation to
        prevent ValueError when EditorState rejects None for array
        elements. The asciimatics Text widget fires on_change during
        initial value setting, and for empty values the delegate
        would try to write None to an array element.

        Note: Accesses delegate._on_change (private) because asciimatics
        provides no public API to suppress change callbacks during
        widget initialization.

        Returns:
            The delegate's asciimatics widget.
        """
        saved_on_change = (self._delegate._on_change)  # noqa: private access required by asciimatics
        self._delegate._on_change = lambda: None
        try:
            widget = self._delegate.as_asciimatics_widget()
        finally:
            self._delegate._on_change = saved_on_change
        widget._on_change = saved_on_change
        return widget

    def _create_delegate(self):
        """Create a typed widget delegate based on schema type.

        Returns:
            NumericField or TextField instance.
        """
        schema_type = self._state.schema_loader.get_type(self._schema)
        if schema_type in ("integer", "number"):
            return NumericField(
                str(self._index),
                self._schema,
                self._state,
                self._path,
            )
        return TextField(
            str(self._index),
            self._schema,
            self._state,
            self._path,
        )

    def set_on_navigate(self, callback):
        """Override the default navigation handler.

        Must be called before as_asciimatics_widget().
        """
        self._custom_navigate = callback

    def _on_navigate(self):
        """Handle navigation into this array item.

        Pushes the array index onto the navigation path.
        Only called for object type items.
        """
        if self._custom_navigate:
            self._custom_navigate()
        else:
            self._state.navigate_into(self._index)

    def get_display_value(self):
        """Return formatted value for object type items.

        Shows index and required field values in a compact format.
        Truncates display to 40 characters to fit in UI.

        Returns:
            Formatted string like '[1] pin_a=GP22, pin_b=GP23'.
        """
        val = self._state.get(self._path)
        prefix = "[%d] " % self._index

        if not isinstance(val, dict):
            return prefix + "[invalid]"

        display_parts = []
        required_fields = self._schema.get("required", [])
        properties = self._schema.get("properties", {})

        for field_name in required_fields:
            if field_name in properties:
                field_value = val.get(field_name) if val else None
                field_str = "" if field_value is None else str(field_value)
                display_parts.append("%s=%s" % (field_name, field_str))

        display_str = prefix + ", ".join(display_parts)

        if len(display_str) > 40:
            return display_str[:37] + "..."

        return display_str
