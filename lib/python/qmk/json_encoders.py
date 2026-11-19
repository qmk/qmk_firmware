"""Class that pretty-prints QMK info.json files."""

import json
from decimal import Decimal

JSON_NEWLINE = "__JSON_NEWLINE__"

_sentinel = object()
newline = '\n'


class QMKJSONEncoder(json.JSONEncoder):
    """Base class for all QMK JSON encoders."""

    container_types = (list, tuple, dict)
    indentation_char = " "

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.indentation_level = 0

        if not self.indent:
            self.indent = 4

    def encode_decimal(self, obj):
        """Encode a decimal object."""
        if obj == int(obj):  # I can't believe Decimal objects don't have .is_integer()
            return int(obj)

        return float(obj)

    def encode_dict(self, obj, path):
        """Encode a dict-like object."""
        if obj:
            self.indentation_level += 1

            items = sorted(obj.items(), key=self.sort_dict) if self.sort_keys else obj.items()
            output = [self.indent_str + f"{json.dumps(key)}: {self.encode(value, path + [key])}" for key, value in items]

            self.indentation_level -= 1

            return "{\n" + ",\n".join(output) + "\n" + self.indent_str + "}"
        else:
            return "{}"

    def encode_dict_single_line(self, obj, path, sort_keys=True):
        """Encode a dict-like object onto a single line."""
        items = sorted(obj.items(), key=self.sort_layout) if sort_keys else obj.items()
        return "{" + ", ".join(f"{json.dumps(key)}: {self.encode(value, path + [key])}" for key, value in items) + "}"

    def encode_list(self, obj, path):
        """Encode a list-like object."""
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

    def encode(self, obj, path=_sentinel):
        """Encode JSON objects for QMK."""
        if path is _sentinel:
            path = []

        if isinstance(obj, Decimal):
            return self.encode_decimal(obj)

        elif isinstance(obj, (list, tuple)):
            return self.encode_list(obj, path)

        elif isinstance(obj, dict):
            return self.encode_dict(obj, path)

        else:
            return super().encode(obj)

    def primitives_only(self, obj):
        """Returns true if the object doesn't have any container type objects (list, tuple, dict)."""
        if isinstance(obj, dict):
            obj = obj.values()

        return not any(isinstance(element, self.container_types) for element in obj)

    @property
    def indent_str(self):
        return self.indentation_char * (self.indentation_level * self.indent)


class InfoJSONEncoder(QMKJSONEncoder):
    """Custom encoder to make info.json's a little nicer to work with."""
    def sort_layout(self, item):
        """Sorts the hashes in a nice way."""
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
        """Forces layout to the back of the sort order."""
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
    """Custom encoder to make keymap.json's a little nicer to work with."""
    def encode_layout(self, obj, path):
        """Encode a layout object."""
        if JSON_NEWLINE not in obj:
            return "[" + ", ".join(self.encode(value, path + [index]) for index, value in enumerate(obj)) + "]"

        self.indentation_level += 1

        # We want to align the keycodes roughly in line with layout, however this breaks down if a keycode is longer than 7 characters (9 when quoted).
        # When a keycode is longer than 7 characters, we stop padding for the rest of the line.
        can_pad = True

        output = []
        for index, value in enumerate(obj):
            if value == JSON_NEWLINE:
                val = "\n" + self.indent_str
                can_pad = True
            elif index == len(obj) - 1:
                val = self.encode(value, path + [index])
            else:
                if len(value) > 9:
                    can_pad = False
                val = self.encode(value, path + [index]) + ","
                val = val.ljust(11) if can_pad else f"{val} "
            output.append(val)

        output.insert(0, self.indent_str)

        self.indentation_level -= 1

        return "[\n" + "".join(output) + "\n" + self.indent_str + "]"

    def encode_macro(self, obj, path):
        """Encode a macro object."""
        self.indentation_level += 1

        output = []
        for index, value in enumerate(obj):
            if isinstance(value, dict):
                output.append(f"{self.indent_str}{self.encode_dict_single_line(value, path + [index], sort_keys=False)}")
            else:
                output.append(f"{self.indent_str}{self.encode(value, path + [index])}")

        self.indentation_level -= 1

        return "[\n" + ",\n".join(output) + "\n" + self.indent_str + "]"

    def encode_list(self, obj, path):
        """Encode a list-like object."""
        if self.primitives_only(obj):
            return "[" + ", ".join(self.encode(value, path + [index]) for index, value in enumerate(obj)) + "]"

        else:
            self.indentation_level += 1

            if path[-1] == 'layers':
                output = [self.indent_str + self.encode_layout(value, path + [index]) for index, value in enumerate(obj)]
            elif path[-1] == 'macros':
                output = [self.indent_str + self.encode_macro(value, path + [index]) for index, value in enumerate(obj)]
            else:
                output = [self.indent_str + self.encode(value, path + [index]) for index, value in enumerate(obj)]

            self.indentation_level -= 1

            return "[\n" + ",\n".join(output) + "\n" + self.indent_str + "]"

    def sort_dict(self, item):
        """Sorts the hashes in a nice way."""
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
    """Custom encoder to make userspace qmk.json's a little nicer to work with."""
    def sort_dict(self, item):
        """Sorts the hashes in a nice way."""
        key = item[0]

        if self.indentation_level == 1:
            if key == 'userspace_version':
                return '00userspace_version'

            if key == 'build_targets':
                return '01build_targets'

        return key


class CommunityModuleJSONEncoder(QMKJSONEncoder):
    """Custom encoder to make qmk_module.json's a little nicer to work with."""
    def sort_dict(self, item):
        """Sorts the hashes in a nice way."""
        key = item[0]

        if self.indentation_level == 1:
            if key == 'module_name':
                return '00module_name'
            if key == 'maintainer':
                return '01maintainer'
            if key == 'license':
                return '02license'
            if key == 'url':
                return '03url'
            if key == 'features':
                return '04features'
            if key == 'keycodes':
                return '05keycodes'
        elif self.indentation_level == 3:  # keycodes
            if key == 'key':
                return '00key'
            if key == 'aliases':
                return '01aliases'

        return key
