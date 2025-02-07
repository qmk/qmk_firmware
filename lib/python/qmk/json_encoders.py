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

    def encode_dict(self, obj, path):
        """Encode a dict-like object.
        """
        if obj:
            self.indentation_level += 1

            items = sorted(obj.items(), key=self.sort_dict) if self.sort_keys else obj.items()
            output = [self.indent_str + f"{json.dumps(key)}: {self.encode(value, path + [key])}" for key, value in items]

            self.indentation_level -= 1

            return "{\n" + ",\n".join(output) + "\n" + self.indent_str + "}"
        else:
            return "{}"

    def encode_dict_single_line(self, obj, path):
        """Encode a dict-like object onto a single line.
        """
        return "{" + ", ".join(f"{json.dumps(key)}: {self.encode(value, path + [key])}" for key, value in sorted(obj.items(), key=self.sort_layout)) + "}"

    def encode_list(self, obj, path):
        """Encode a list-like object.
        """
        if self.primitives_only(obj):
            return "[" + ", ".join(self.encode(value, path + [index]) for index, value in enumerate(obj)) + "]"

        else:
            self.indentation_level += 1

            if path[-1] in ('layout', 'rotary'):
                # These are part of a LED layout or encoder config, put them on a single line
                output = [self.indent_str + self.encode_dict_single_line(value, path + [index]) for index, value in enumerate(obj)]
            else:
                output = [self.indent_str + self.encode(value, path + [index]) for index, value in enumerate(obj)]

            self.indentation_level -= 1

            return "[\n" + ",\n".join(output) + "\n" + self.indent_str + "]"

    def encode(self, obj, path=[]):
        """Encode JSON objects for QMK.
        """
        if isinstance(obj, Decimal):
            return self.encode_decimal(obj)

        elif isinstance(obj, (list, tuple)):
            return self.encode_list(obj, path)

        elif isinstance(obj, dict):
            return self.encode_dict(obj, path)

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
    def sort_layout(self, item):
        """Sorts the hashes in a nice way.
        """
        key = item[0]

        if key == 'label':
            return '00label'

        elif key == 'matrix':
            return '01matrix'

        elif key == 'x':
            return '02x'

        elif key == 'y':
            return '03y'

        elif key == 'w':
            return '04w'

        elif key == 'h':
            return '05h'

        elif key == 'flags':
            return '06flags'

        return key

    def sort_dict(self, item):
        """Forces layout to the back of the sort order.
        """
        key = item[0]

        if self.indentation_level == 1:
            if key == 'manufacturer':
                return '10manufacturer'

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
    def encode_list(self, obj, path):
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

    def sort_dict(self, item):
        """Sorts the hashes in a nice way.
        """
        key = item[0]

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


class UserspaceJSONEncoder(QMKJSONEncoder):
    """Custom encoder to make userspace qmk.json's a little nicer to work with.
    """
    def sort_dict(self, item):
        """Sorts the hashes in a nice way.
        """
        key = item[0]

        if self.indentation_level == 1:
            if key == 'userspace_version':
                return '00userspace_version'

            if key == 'build_targets':
                return '01build_targets'

        return key


class CommunityModuleJSONEncoder(QMKJSONEncoder):
    """Custom encoder to make qmk_module.json's a little nicer to work with.
    """
    def sort_dict(self, item):
        """Sorts the hashes in a nice way.
        """
        key = item[0]

        if self.indentation_level == 1:
            if key == 'module_name':
                return '00module_name'
            if key == 'maintainer':
                return '01maintainer'
            if key == 'url':
                return '02url'
            if key == 'features':
                return '03features'
            if key == 'keycodes':
                return '04keycodes'
        elif self.indentation_level == 3:  # keycodes
            if key == 'key':
                return '00key'
            if key == 'aliases':
                return '01aliases'

        return key
