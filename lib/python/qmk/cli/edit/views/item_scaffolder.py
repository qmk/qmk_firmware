"""Stateless utility for creating default items from JSON schemas.

Extracted from FieldListView._scaffold_item and
FieldListView._default_value_for_type to enable independent testing
and reuse across view collaborators.
"""


class ItemScaffolder:
    """Create new items with default values based on JSON schema definitions.

    Args:
        schema_loader
            A SchemaLoader instance used to inspect schema metadata
            such as required fields and property types.
    """
    def __init__(self, schema_loader):
        self._schema_loader = schema_loader

    def default_value_for_type(self, field_type):
        """Return the default value for a schema type string.

        Args:
            field_type
                Schema type string like 'string', 'integer', 'boolean'.

        Returns:
            Default value appropriate for the type.
        """
        if field_type in ('integer', 'number'):
            return 0
        if field_type == 'boolean':
            return False
        return ''

    def scaffold(self, item_schema):
        """Create a new item with default values based on schema type.

        For non-object types, returns the type's default value directly.
        For object types, builds a dict populated with default values for
        each required field found in the schema's properties.

        Args:
            item_schema
                Schema dict describing the item to create.

        Returns:
            A new item with default values matching the schema.
        """
        item_type = item_schema.get('type', 'string')

        if item_type != 'object':
            return self.default_value_for_type(item_type)

        obj = {}
        required_fields = self._schema_loader.get_required_fields(item_schema)
        properties = item_schema.get('properties', {})

        for field_name in required_fields:
            if field_name in properties:
                field_type = self._schema_loader.get_type(properties[field_name])
                obj[field_name] = self.default_value_for_type(field_type)

        return obj
