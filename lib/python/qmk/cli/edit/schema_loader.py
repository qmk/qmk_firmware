"""Schema loader for keyboard.jsonschema.
"""
from qmk.json_schema import load_jsonschema, compile_schema_store


class SchemaLoader:
    """Loads and navigates keyboard.jsonschema with $ref resolution.
    """
    def __init__(self):
        """Load schema from data/schemas/keyboard.jsonschema.
        """
        self.schema = load_jsonschema('keyboard')
        self.schema_store = compile_schema_store()

    def get_properties(self, path=None):
        """Return dict of property_name -> property_schema at path.

        Args:
            path
                Tuple of keys like ('usb',) or None for root.

        Returns:
            Dictionary of property definitions.
        """
        schema_fragment = self._get_schema_fragment(path)
        schema_fragment = self._resolve_ref(schema_fragment)

        return schema_fragment.get('properties', {})

    def get_property_order(self, path=None):
        """Return list of property names in schema definition order.

        Args:
            path
                Tuple of keys like ('usb',) or None for root.

        Returns:
            List of property names in order.
        """
        properties = self.get_properties(path)
        return list(properties.keys())

    def get_type(self, property_schema):
        """Return normalized type for a property schema.

        Args:
            property_schema
                Property schema fragment.

        Returns:
            One of: 'string', 'boolean', 'integer', 'number', 'enum', 'array', 'object'.
        """
        property_schema = self._resolve_ref(property_schema)

        if 'enum' in property_schema:
            return 'enum'

        type_value = property_schema.get('type')
        if type_value:
            return type_value

        return 'string'

    def get_enum_values(self, property_schema):
        """Return list of allowed values for enum types.

        Args:
            property_schema
                Property schema fragment.

        Returns:
            List of enum values, or None if not an enum.
        """
        property_schema = self._resolve_ref(property_schema)
        return property_schema.get('enum')

    def get_constraints(self, property_schema):
        """Return dict of constraints for a property.

        Args:
            property_schema
                Property schema fragment.

        Returns:
            Dictionary containing constraints like minimum, maximum, pattern, etc.
        """
        property_schema = self._resolve_ref(property_schema)

        constraints = {}
        for key in ['minimum', 'maximum', 'minLength', 'maxLength', 'pattern']:
            if key in property_schema:
                constraints[key] = property_schema[key]

        return constraints

    def is_array_at_path(self, path):
        """Check if the schema at path defines an array type.

        Args:
            path
                Tuple of keys like ('backlight', 'pins') or None for root.

        Returns:
            True if schema at path is an array type, False otherwise.
        """
        schema_fragment = self._get_schema_fragment(path)
        schema_fragment = self._resolve_ref(schema_fragment)
        return schema_fragment.get('type') == 'array'

    def get_items_schema(self, path=None):
        """Return schema for items in an array.

        Args:
            path
                Tuple of keys like ('matrix_pins', 'cols') or None for root.

        Returns:
            Items schema with $ref resolved, or None if not an array.
        """
        schema_fragment = self._get_schema_fragment(path)
        schema_fragment = self._resolve_ref(schema_fragment)

        if schema_fragment.get('type') != 'array':
            return None

        items_schema = schema_fragment.get('items')
        if items_schema is None:
            return None

        # Resolve the items schema. If it has a $ref that points to definitions,
        # we need to resolve it in the context of the base schema it came from
        resolved_items = self._resolve_ref(items_schema)

        # If resolution failed (empty dict), try resolving in definitions schema
        if not resolved_items and isinstance(items_schema, dict) and '$ref' in items_schema:
            ref = items_schema['$ref']
            if ref.startswith('#/'):
                defs_schema = load_jsonschema('definitions')
                resolved_items = self._resolve_json_pointer(defs_schema, ref[1:])

        return resolved_items

    def get_required_fields(self, property_schema):
        """Return list of required fields from a schema.

        Args:
            property_schema
                Property schema fragment.

        Returns:
            List of required field names, or empty list if none.
        """
        if not isinstance(property_schema, dict):
            return []

        return property_schema.get('required', [])

    def _get_schema_fragment(self, path):
        """Navigate to a schema fragment at the given path.

        Args:
            path
                Tuple of keys or None for root.

        Returns:
            Schema fragment at the path.
        """
        if not path:
            return self.schema

        fragment = self.schema
        for key in path:
            fragment = self._resolve_ref(fragment)

            if isinstance(key, int):
                if fragment.get('type') == 'array' and 'items' in fragment:
                    fragment = fragment['items']
                else:
                    return {}
            else:
                properties = fragment.get('properties', {})
                if key not in properties:
                    return {}
                fragment = properties[key]

        return fragment

    def _resolve_relative_ref(self, ref, seen=None):
        """Resolve a relative $ref starting with './'.

        Args:
            ref
                $ref string starting with './'.
            seen
                Set of already-visited $ref strings for cycle detection.

        Returns:
            Resolved schema fragment.
        """
        schema_name = ref.split('#')[0].replace('./', '').replace('.jsonschema', '')

        if '#' not in ref:
            return load_jsonschema(schema_name)

        json_path = ref.split('#')[1]
        base_schema = load_jsonschema(schema_name) if schema_name else self.schema
        return self._resolve_json_pointer(base_schema, json_path, seen=seen)

    def _resolve_ref(self, schema_fragment, seen=None):
        """Resolve $ref references in a schema fragment.

        Args:
            schema_fragment
                Schema fragment that may contain $ref.
            seen
                Set of already-visited $ref strings for cycle detection.

        Returns:
            Resolved schema fragment, or {} if a circular $ref is detected.
        """
        if not isinstance(schema_fragment, dict):
            return schema_fragment

        if '$ref' not in schema_fragment:
            return schema_fragment

        ref = schema_fragment['$ref']

        if seen is None:
            seen = set()
        if ref in seen:
            return {}
        seen.add(ref)

        if ref.startswith('./'):
            return self._resolve_relative_ref(ref, seen=seen)

        if ref.startswith('#/'):
            return self._resolve_json_pointer(self.schema, ref[1:], seen=seen)

        if ref in self.schema_store:
            return self.schema_store[ref]

        return schema_fragment

    def _resolve_json_pointer(self, schema, pointer, seen=None):
        """Resolve a JSON pointer path like /definitions/encoder_config.

        Args:
            schema
                Base schema to resolve from.
            pointer
                JSON pointer path.
            seen
                Set of already-visited $ref strings for cycle detection.

        Returns:
            Resolved schema fragment.
        """
        if not pointer.startswith('/'):
            return schema

        parts = pointer[1:].split('/')
        fragment = schema

        for part in parts:
            if isinstance(fragment, dict) and part in fragment:
                fragment = fragment[part]
            else:
                return {}

        return self._resolve_ref(fragment, seen=seen)
