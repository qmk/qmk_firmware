"""Class that pretty-prints QMK info.json files.
"""
import json
from decimal import Decimal

newline = '\n'


class QMKJSONEncoder(json.JSONEncoder):
    """Base class for all QMK JSON encoders.
    """
    container_types = (list, tuple, dict)
    indentation_char = " "

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.indentation_level = 0

        if not self.indent:
            self.indent = 4

    def encode_decimal(self, obj):
        """Encode a decimal object.
        """
        if obj == int(obj):  # I can't believe Decimal objects don't have .is_integer()
            return int(obj)

        return float(obj)

    def encode_list(self, obj):
        """Encode a list-like object.
        """
        if self.primitives_only(obj):
            return "[" + ", ".join(self.encode(element) for element in obj) + "]"

        else:
            self.indentation_level += 1
            output = [self.indent_str + self.encode(element) for element in obj]
            self.indentation_level -= 1

            return "[\n" + ",\n".join(output) + "\n" + self.indent_str + "]"

    def encode(self, obj):
        """Encode keymap.json objects for QMK.
        """
        if isinstance(obj, Decimal):
            return self.encode_decimal(obj)

        elif isinstance(obj, (list, tuple)):
            return self.encode_list(obj)

        elif isinstance(obj, dict):
            return self.encode_dict(obj)

        else:
            return super().encode(obj)

    def primitives_only(self, obj):
        """Returns true if the object doesn't have any container type objects (list, tuple, dict).
        """
        if isinstance(obj, dict):
            obj = obj.values()

        return not any(isinstance(element, self.container_types) for element in obj)

    @property
    def indent_str(self):
        return self.indentation_char * (self.indentation_level * self.indent)


class InfoJSONEncoder(QMKJSONEncoder):
    """Custom encoder to make info.json's a little nicer to work with.
    """
    def encode_dict(self, obj):
        """Encode info.json dictionaries.
        """
        if obj:
            if self.indentation_level == 4:
                # These are part of a layout, put them on a single line.
                return "{ " + ", ".join(f"{self.encode(key)}: {self.encode(element)}" for key, element in sorted(obj.items())) + " }"

            else:
                self.indentation_level += 1
                output = [self.indent_str + f"{json.dumps(key)}: {self.encode(value)}" for key, value in sorted(obj.items(), key=self.sort_dict)]
                self.indentation_level -= 1
                return "{\n" + ",\n".join(output) + "\n" + self.indent_str + "}"
        else:
            return "{}"

    def sort_dict(self, key):
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

            elif key == 'community_layouts':
                return '97community_layouts'

            elif key == 'layout_aliases':
                return '98layout_aliases'

            elif key == 'layouts':
                return '99layouts'

            else:
                return '50' + str(key)

        return key


class KeymapJSONEncoder(QMKJSONEncoder):
    """Custom encoder to make keymap.json's a little nicer to work with.
    """
    def encode_dict(self, obj):
        """Encode dictionary objects for keymap.json.
        """
        if obj:
            self.indentation_level += 1
            output_lines = [f"{self.indent_str}{json.dumps(key)}: {self.encode(value)}" for key, value in sorted(obj.items(), key=self.sort_dict)]
            output = ',\n'.join(output_lines)
            self.indentation_level -= 1

            return f"{{\n{output}\n{self.indent_str}}}"

        else:
            return "{}"

    def encode_list(self, obj):
        """Encode a list-like object.
        """
        if self.indentation_level == 2:
            indent_level = self.indentation_level + 1
            # We have a list of keycodes
            layer = [[]]

            for key in obj:
                if key == 'JSON_NEWLINE':
                    layer.append([])
                else:
                    if isinstance(key, dict):
                        # We have a macro

                        # TODO: Add proper support for nicely formatting keymap.json macros
                        layer[-1].append(f'{self.encode(key)}')
                    else:
                        layer[-1].append(f'"{key}"')

            layer = [f"{self.indent_str*indent_level}{', '.join(row)}" for row in layer]

            return f"{self.indent_str}[\n{newline.join(layer)}\n{self.indent_str*self.indentation_level}]"

        elif self.primitives_only(obj):
            return "[" + ", ".join(self.encode(element) for element in obj) + "]"

        else:
            self.indentation_level += 1
            output = [self.indent_str + self.encode(element) for element in obj]
            self.indentation_level -= 1

            return "[\n" + ",\n".join(output) + "\n" + self.indent_str + "]"

    def sort_dict(self, key):
        """Sorts the hashes in a nice way.
        """
        key = key[0]

        if self.indentation_level == 1:
            if key == 'version':
                return '00version'

            elif key == 'author':
                return '01author'

            elif key == 'notes':
                return '02notes'

            elif key == 'layers':
                return '98layers'

            elif key == 'documentation':
                return '99documentation'

            else:
                return '50' + str(key)

        return key
