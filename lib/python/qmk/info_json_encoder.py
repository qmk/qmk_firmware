"""Class that pretty-prints QMK info.json files.
"""
import json
from decimal import Decimal


class InfoJSONEncoder(json.JSONEncoder):
    """Custom encoder to make info.json's a little nicer to work with.
    """
    container_types = (list, tuple, dict)
    indentation_char = " "

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.indentation_level = 0

        if not self.indent:
            self.indent = 2

    def encode(self, obj):
        """Encode JSON objects for QMK.
        """
        if isinstance(obj, Decimal):
            if obj == int(obj):  # I can't believe Decimal objects don't have .is_integer()
                return int(obj)
            return float(obj)

        elif isinstance(obj, (list, tuple)):
            if self._primitives_only(obj):
                return "[" + ", ".join(self.encode(element) for element in obj) + "]"

            else:
                self.indentation_level += 1
                output = [self.indent_str + self.encode(element) for element in obj]
                self.indentation_level -= 1
                return "[\n" + ",\n".join(output) + "\n" + self.indent_str + "]"

        elif isinstance(obj, dict):
            if obj:
                if self.indentation_level == 4:
                    # These are part of a layout, put them on a single line.
                    return "{ " + ", ".join(f"{self.encode(key)}: {self.encode(element)}" for key, element in sorted(obj.items())) + " }"

                else:
                    self.indentation_level += 1
                    output = [self.indent_str + f"{json.dumps(key)}: {self.encode(value)}" for key, value in sorted(obj.items(), key=self.sort_root_dict)]
                    self.indentation_level -= 1
                    return "{\n" + ",\n".join(output) + "\n" + self.indent_str + "}"
            else:
                return "{}"
        else:
            return super().encode(obj)

    def _primitives_only(self, obj):
        """Returns true if the object doesn't have any container type objects (list, tuple, dict).
        """
        if isinstance(obj, dict):
            obj = obj.values()

        return not any(isinstance(element, self.container_types) for element in obj)

    def sort_root_dict(self, key):
        """Forces layout to the back of the sort order.
        """
        key = key[0]

        if self.indentation_level == 1:
            if key == 'manufacturer':
                return '10keyboard_name'

            elif key == 'keyboard_name':
                return '11keyboard_name'

            elif key == 'maintainer':
                return '12maintainer'

            elif key in ('height', 'width'):
                return '40' + str(key)

            elif key == 'layouts':
                return '99layouts'

            else:
                return '50' + str(key)

        return key

    @property
    def indent_str(self):
        return self.indentation_char * (self.indentation_level * self.indent)
