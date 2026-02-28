"""Widget package for field editors.
"""
from qmk.cli.edit.widgets.base import FieldWidget
from qmk.cli.edit.widgets.text_field import TextField
from qmk.cli.edit.widgets.numeric_field import NumericField
from qmk.cli.edit.widgets.boolean_field import BooleanField
from qmk.cli.edit.widgets.enum_field import EnumField
from qmk.cli.edit.widgets.object_row import ObjectRow
from qmk.cli.edit.widgets.array_row import ArrayRow
from qmk.cli.edit.widgets.array_item_row import ArrayItemRow
from qmk.cli.edit.widget_registry import WidgetRegistry


def create_default_registry():
    """Create and configure the default widget registry.

    Returns:
        WidgetRegistry instance with standard type mappings.
    """
    registry = WidgetRegistry()

    registry.register_type_default('string', TextField)
    registry.register_type_default('boolean', BooleanField)
    registry.register_type_default('integer', NumericField)
    registry.register_type_default('number', NumericField)
    registry.register_type_default('enum', EnumField)
    registry.register_type_default('object', ObjectRow)
    registry.register_type_default('array', ArrayRow)

    def create_hex_field(name, schema, state, path):
        return NumericField(name, schema, state, path, hex_format=True)

    registry.register_path_override(('usb', 'vid'), create_hex_field)
    registry.register_path_override(('usb', 'pid'), create_hex_field)

    return registry


__all__ = [
    'FieldWidget',
    'TextField',
    'NumericField',
    'BooleanField',
    'EnumField',
    'ObjectRow',
    'ArrayRow',
    'ArrayItemRow',
    'create_default_registry',
]
