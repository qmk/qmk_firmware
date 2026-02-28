"""Widget registry for mapping schema types to widget factories.
"""
from qmk.cli.edit.widgets.text_field import TextField


class WidgetRegistry:
    """Maps schema paths and types to widget factories.
    """
    def __init__(self):
        """Initialize with empty registries.
        """
        self._type_defaults = {}
        self._path_overrides = {}
        self._pattern_overrides = []

    def register_type_default(self, schema_type, widget_factory):
        """Register default factory for a schema type.

        Args:
            schema_type
                Schema type string like 'string', 'boolean', 'integer'.
            widget_factory
                Callable(name, schema, state, path) -> FieldWidget.
        """
        self._type_defaults[schema_type] = widget_factory

    def register_path_override(self, path, widget_factory):
        """Register override for exact path.

        Args:
            path
                Tuple path like ('usb', 'vid').
            widget_factory
                Callable(name, schema, state, path) -> FieldWidget.
        """
        self._path_overrides[path] = widget_factory

    def register_pattern_override(self, pattern, widget_factory):
        """Register override for paths matching compiled regex pattern.

        Args:
            pattern
                Compiled re.Pattern object.
            widget_factory
                Callable(name, schema, state, path) -> FieldWidget.
        """
        self._pattern_overrides.append((pattern, widget_factory))

    def create_widget(self, name, property_schema, state, path):
        """Create widget with precedence: path > pattern > type > fallback.

        Args:
            name
                Field name (e.g., 'vid').
            property_schema
                Property schema fragment.
            state
                EditorState instance.
            path
                Tuple path, e.g. ('usb', 'vid').

        Returns:
            FieldWidget instance.
        """
        if path in self._path_overrides:
            return self._path_overrides[path](name, property_schema, state, path)

        dot_path = '.'.join(str(s) for s in path)
        for pattern, factory in self._pattern_overrides:
            if pattern.match(dot_path):
                return factory(name, property_schema, state, path)

        schema_type = state.schema_loader.get_type(property_schema)
        if schema_type in self._type_defaults:
            return self._type_defaults[schema_type](name, property_schema, state, path)

        return TextField(name, property_schema, state, path)
