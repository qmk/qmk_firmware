"""Numeric field widget for integer and number input."""

from asciimatics.widgets import Text
from qmk.cli.edit.widgets.base import FieldWidget


class NumericField(FieldWidget):
    """Widget for editing integer and number values."""
    def __init__(self, name, schema, state, path, hex_format=False):
        """Initialize the numeric field widget.

        Args:
            name
                Field name.
            schema
                Property schema fragment.
            state
                EditorState instance.
            path
                Tuple path to this field.
            hex_format
                If True, display and accept hex format (0x prefix).
        """
        super().__init__(name, schema, state, path)
        self._widget = None
        self._hex_format = hex_format
        self._constraints = state.schema_loader.get_constraints(schema)
        self._is_integer = state.schema_loader.get_type(schema) == "integer"
        self._updating = False

    def as_asciimatics_widget(self):
        """Return asciimatics Text widget with numeric validation."""
        self._widget = Text(label=self.label + ":", name=self._path_string, on_change=self._on_change)
        self._widget.value = self._format_value(self.value)
        return self._widget

    def _on_change(self):
        """Handle value change with validation."""
        if self._updating:
            return

        if not self._widget:
            return

        raw_value = self._widget.value
        if not raw_value:
            self.value = None
            return

        parsed = self._parse_value(raw_value)
        if parsed is not None and self._validate(parsed):
            self.value = parsed
        else:
            try:
                self._updating = True
                self._widget.value = self._format_value(self.value)
            finally:
                self._updating = False

    def _parse_value(self, raw_value):
        """Parse string input to numeric value.

        Args:
            raw_value
                String input from user.

        Returns:
            Parsed numeric value, or None if invalid.
        """
        if not raw_value:
            return None

        try:
            if self._hex_format:
                return int(raw_value, 16)

            if self._is_integer:
                return int(raw_value)
            return float(raw_value)
        except ValueError:
            return None

    def _format_value(self, value):
        """Format value for display.

        Args:
            value
                Numeric value to format.

        Returns:
            Formatted string.
        """
        if value is None:
            return ""

        if not self._hex_format:
            return str(value)

        if not isinstance(value, str):
            return "0x%X" % value

        if value.startswith("0x"):
            return value

        try:
            return "0x%X" % int(value, 16)
        except ValueError:
            return value

    def _validate(self, value):
        """Validate numeric value against constraints.

        Args:
            value
                Numeric value to validate.

        Returns:
            True if valid, False otherwise.
        """
        if "minimum" in self._constraints and value < self._constraints["minimum"]:
            return False
        if "maximum" in self._constraints and value > self._constraints["maximum"]:
            return False
        return True

    def get_display_value(self):
        """Return string representation for display in field list."""
        val = self.value
        if val is None:
            return "[-]"
        return "[%s]" % self._format_value(val)
