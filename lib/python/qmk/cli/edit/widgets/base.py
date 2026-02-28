"""Base widget interface for field editors.
"""
from abc import ABC, abstractmethod

from qmk.cli.edit.constraint_formatter import format_hint


class FieldWidget(ABC):
    """Base interface for all field editor widgets.
    """
    def __init__(self, name, schema, state, path):
        """Initialize the field widget.

        Args:
            name
                Field name (e.g., 'vid').
            schema
                Property schema fragment.
            state
                EditorState instance.
            path
                Tuple path to this field, e.g. ('usb', 'vid').
        """
        self._name = name
        self._schema = schema
        self._state = state
        self._path = path

    @property
    def _path_string(self):
        """Return path as dot-string for asciimatics widget name.
        """
        return '.'.join(str(s) for s in self._path)

    @property
    def name(self):
        """Field name (e.g., 'vid').
        """
        return self._name

    @property
    def index(self):
        """Array index for ArrayItemRow widgets, or None.

        Base implementation returns None. ArrayItemRow overrides
        to return the integer index.
        """
        return None

    @property
    def asciimatics_widget(self):
        """The underlying asciimatics widget, or None if not yet created.
        """
        return getattr(self, '_widget', None)

    @property
    def label(self):
        """Display label for the field.
        """
        if 'title' in self._schema:
            return self._schema['title']
        return self._name

    @property
    def value(self):
        """Current value from state, or None if unset.
        """
        return self._state.get(self._path)

    @value.setter
    def value(self, new_value):
        """Update value in state.
        """
        self._state.set(self._path, new_value)

    @abstractmethod
    def as_asciimatics_widget(self):
        """Return asciimatics Widget instance for rendering.
        """
        pass

    def get_hint(self):
        """Return constraint hint string for this field, or None.
        """
        constraints = self._state.schema_loader.get_constraints(self._schema)
        enum_values = self._state.schema_loader.get_enum_values(self._schema)
        return format_hint(constraints, enum_values)

    def get_display_value(self):
        """Return string representation for display in field list.
        """
        val = self.value
        if val is None:
            return '[-]'
        return '[%s]' % str(val)
