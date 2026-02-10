"""Used by the make system to generate keyboard.c from info.json.
"""
import bisect
import dataclasses
from typing import Optional

from milc import cli

from qmk.info import info_json
from qmk.commands import dump_lines
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.path import normpath
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, JOYSTICK_AXES


def _gen_led_configs(info_data):
    lines = []

    if 'layout' in info_data.get('rgb_matrix', {}):
        lines.extend(_gen_led_config(info_data, 'rgb_matrix'))

    if 'layout' in info_data.get('led_matrix', {}):
        lines.extend(_gen_led_config(info_data, 'led_matrix'))

    return lines


def _gen_led_config(info_data, config_type):
    """Convert info.json content to g_led_config
    """
    cols = info_data['matrix_size']['cols']
    rows = info_data['matrix_size']['rows']

    lines = []

    matrix = [['NO_LED'] * cols for _ in range(rows)]
    pos = []
    flags = []

    led_layout = info_data[config_type]['layout']
    for index, led_data in enumerate(led_layout):
        if 'matrix' in led_data:
            row, col = led_data['matrix']
            matrix[row][col] = str(index)
        pos.append(f'{{{led_data.get("x", 0)}, {led_data.get("y", 0)}}}')
        flags.append(str(led_data.get('flags', 0)))

    if config_type == 'rgb_matrix':
        lines.append('#ifdef RGB_MATRIX_ENABLE')
        lines.append('#include "rgb_matrix.h"')
    elif config_type == 'led_matrix':
        lines.append('#ifdef LED_MATRIX_ENABLE')
        lines.append('#include "led_matrix.h"')

    lines.append('__attribute__ ((weak)) led_config_t g_led_config = {')
    lines.append('  {')
    for line in matrix:
        lines.append(f'    {{ {", ".join(line)} }},')
    lines.append('  },')
    lines.append(f'  {{ {", ".join(pos)} }},')
    lines.append(f'  {{ {", ".join(flags)} }},')
    lines.append('};')
    lines.append('#endif')
    lines.append('')

    return lines


def _gen_matrix_mask(info_data):
    """Convert info.json content to matrix_mask
    """
    cols = info_data['matrix_size']['cols']
    rows = info_data['matrix_size']['rows']

    # Default mask to everything disabled
    mask = [['0'] * cols for _ in range(rows)]

    # Mirror layout macros squashed on top of each other
    for layout_name, layout_data in info_data['layouts'].items():
        for key_data in layout_data['layout']:
            row, col = key_data['matrix']
            if row >= rows or col >= cols:
                cli.log.error(f'Skipping matrix_mask due to {layout_name} containing invalid matrix values')
                return []
            mask[row][col] = '1'

    lines = []
    lines.append('#ifdef MATRIX_MASKED')
    lines.append('__attribute__((weak)) const matrix_row_t matrix_mask[] = {')
    for i in range(rows):
        lines.append(f'    0b{"".join(reversed(mask[i]))},')
    lines.append('};')
    lines.append('#endif')
    lines.append('')

    return lines


def _gen_joystick_axes(info_data):
    """Convert info.json content to joystick_axes
    """
    if 'axes' not in info_data.get('joystick', {}):
        return []

    axes = info_data['joystick']['axes']
    axes_keys = list(axes.keys())

    lines = []
    lines.append('#ifdef JOYSTICK_ENABLE')
    lines.append('joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {')

    # loop over all available axes - injecting virtual axis for those not specified
    for index, cur in enumerate(JOYSTICK_AXES):
        # bail out if we have generated all requested axis
        if len(axes_keys) == 0:
            break

        axis = 'virtual'
        if cur in axes:
            axis = axes[cur]
            axes_keys.remove(cur)

        if axis == 'virtual':
            lines.append(f"    [{index}] = JOYSTICK_AXIS_VIRTUAL,")
        else:
            lines.append(f"    [{index}] = JOYSTICK_AXIS_IN({axis['input_pin']}, {axis['low']}, {axis['rest']}, {axis['high']}),")

    lines.append('};')
    lines.append('#endif')
    lines.append('')

    return lines


@dataclasses.dataclass
class LayoutKey:
    """Geometric info for one key in a layout."""
    row: int
    col: int
    x: float
    y: float
    w: float = 1.0
    h: float = 1.0
    hand: Optional[str] = None

    @staticmethod
    def from_json(key_json):
        row, col = key_json['matrix']
        return LayoutKey(
            row=row,
            col=col,
            x=key_json['x'],
            y=key_json['y'],
            w=key_json.get('w', 1.0),
            h=key_json.get('h', 1.0),
            hand=key_json.get('hand', None),
        )

    @property
    def cx(self):
        """Center x coordinate of the key."""
        return self.x + self.w / 2.0

    @property
    def cy(self):
        """Center y coordinate of the key."""
        return self.y + self.h / 2.0


class Layout:
    """Geometric info of a layout."""
    def __init__(self, layout_json):
        self.keys = [LayoutKey.from_json(key_json) for key_json in layout_json['layout']]
        self.x_min = min(key.cx for key in self.keys)
        self.x_max = max(key.cx for key in self.keys)
        self.x_mid = (self.x_min + self.x_max) / 2
        # If there is one key with width >= 6u, it is probably the spacebar.
        i = [i for i, key in enumerate(self.keys) if key.w >= 6.0]
        self.spacebar = self.keys[i[0]] if len(i) == 1 else None

    def is_symmetric(self, tol: float = 0.02):
        """Whether the key positions are symmetric about x_mid."""
        x = sorted([key.cx for key in self.keys])
        for i in range(len(x)):
            x_i_mirrored = 2.0 * self.x_mid - x[i]
            # Find leftmost x element greater than or equal to (x_i_mirrored - tol).
            j = bisect.bisect_left(x, x_i_mirrored - tol)
            if j == len(x) or abs(x[j] - x_i_mirrored) > tol:
                return False

        return True

    def widest_horizontal_gap(self):
        """Finds the x midpoint of the widest horizontal gap between keys."""
        x = sorted([key.cx for key in self.keys])
        x_mid = self.x_mid
        max_sep = 0
        for i in range(len(x) - 1):
            sep = x[i + 1] - x[i]
            if sep > max_sep:
                max_sep = sep
                x_mid = (x[i + 1] + x[i]) / 2

        return x_mid


def _gen_chordal_hold_layout(info_data):
    """Convert info.json content to chordal_hold_layout
    """
    # NOTE: If there are multiple layouts, only the first is read.
    for layout_name, layout_json in info_data['layouts'].items():
        layout = Layout(layout_json)
        break

    if layout.is_symmetric():
        # If the layout is symmetric (e.g. most split keyboards), guess the
        # handedness based on the sign of (x - layout.x_mid).
        hand_signs = [key.x - layout.x_mid for key in layout.keys]
    elif layout.spacebar is not None:
        # If the layout has a spacebar, form a dividing line through the spacebar,
        # nearly vertical but with a slight angle to follow typical row stagger.
        x0 = layout.spacebar.cx - 0.05
        y0 = layout.spacebar.cy - 1.0
        hand_signs = [(key.x - x0) - (key.y - y0) / 3.0 for key in layout.keys]
    else:
        # Fallback: assume handedness based on the widest horizontal separation.
        x_mid = layout.widest_horizontal_gap()
        hand_signs = [key.x - x_mid for key in layout.keys]

    for key, hand_sign in zip(layout.keys, hand_signs):
        if key.hand is None:
            if key == layout.spacebar or abs(hand_sign) <= 0.02:
                key.hand = '*'
            else:
                key.hand = 'L' if hand_sign < 0.0 else 'R'

    lines = []
    lines.append('#ifdef CHORDAL_HOLD')
    line = ('__attribute__((weak)) const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = ' + layout_name + '(')

    x_prev = None
    for key in layout.keys:
        if x_prev is None or key.x < x_prev:
            lines.append(line)
            line = '  '
        line += f"'{key.hand}', "
        x_prev = key.x

    lines.append(line[:-2])
    lines.append(');')
    lines.append('#endif')

    return lines


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to generate keyboard.c for.')
@cli.subcommand('Used by the make system to generate keyboard.c from info.json', hidden=True)
def generate_keyboard_c(cli):
    """Generates the keyboard.h file.
    """
    kb_info_json = info_json(cli.args.keyboard)

    # Build the layouts.h file.
    keyboard_c_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#include QMK_KEYBOARD_H', '']

    keyboard_c_lines.extend(_gen_led_configs(kb_info_json))
    keyboard_c_lines.extend(_gen_matrix_mask(kb_info_json))
    keyboard_c_lines.extend(_gen_joystick_axes(kb_info_json))
    keyboard_c_lines.extend(_gen_chordal_hold_layout(kb_info_json))

    # Show the results
    dump_lines(cli.args.output, keyboard_c_lines, cli.args.quiet)
