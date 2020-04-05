"""Functions that help us work with keyboards.
"""
from array import array
from glob import glob
from math import ceil
from pathlib import Path
from os.path import exists

from milc import cli

default_key_entry = {'x': -1, 'y': -1, 'w': 1}


def is_keyboard(keyboard_folder):
    """Returns True if keyboard is a valid keyboard_folder.
    """
    keyboard_folder = Path('keyboards') / keyboard_folder
    rules_mk = keyboard_folder / 'rules.mk'
    return keyboard_folder.exists() and rules_mk.exists()


def default_key(label=None):
    """Increment x and return a copy of the default_key_entry.
    """
    default_key_entry['x'] += 1
    new_key = default_key_entry.copy()

    if label:
        new_key['label'] = label

    return new_key


def find_layouts(file):
    """Returns list of parsed layout macros found in the supplied file.
    """
    file = Path(file)
    aliases = {}  # Populated with all `#define`s that aren't functions
    writing_keymap = False
    discovered_keymaps = []
    parsed_keymaps = {}
    current_keymap = []

    for line in file.read_text().split('\n'):
        if not writing_keymap:
            if '#define' in line and '(' in line and ('LAYOUT' in line or 'KEYMAP' in line):
                writing_keymap = True
            elif '#define' in line:
                try:
                    _, pp_macro_name, pp_macro_text = line.strip().split(' ', 2)
                    aliases[pp_macro_name] = pp_macro_text
                except ValueError:
                    continue

        if writing_keymap:
            current_keymap.append(line.strip() + '\n')
            if ')' in line:
                writing_keymap = False
                discovered_keymaps.append(''.join(current_keymap))
                current_keymap = []

    for keymap in discovered_keymaps:
        # Clean-up the keymap text, extract the macro name, and end up with a list
        # of key entries.
        keymap = keymap.replace('\\', '').replace(' ', '').replace('\t', '').replace('#define', '')
        macro_name, keymap = keymap.split('(', 1)
        keymap = keymap.split(')', 1)[0]

        # Reject any macros that don't start `LAYOUT`
        if not macro_name.startswith('LAYOUT'):
            continue

        # Parse the keymap entries into naive x/y data
        parsed_keymap = []
        default_key_entry['y'] = -1
        for row in keymap.strip().split(',\n'):
            default_key_entry['x'] = -1
            default_key_entry['y'] += 1
            parsed_keymap.extend([default_key(key) for key in row.split(',')])
        parsed_keymaps[macro_name] = {
            'key_count': len(parsed_keymap),
            'layout': parsed_keymap,
        }

    for alias, text in aliases.items():
        if text in parsed_keymaps and not alias.startswith('KEYMAP'):
            parsed_keymaps[alias] = parsed_keymaps[text]

    return parsed_keymaps


def find_all_layouts(keyboard):
    """Looks for layout macros associated with this keyboard.
    """
    layouts = {}
    rules_mk = parse_rules_mk(keyboard)
    keyboard_path = Path(rules_mk.get('DEFAULT_FOLDER', keyboard))

    # Pull in all keymaps defined in the standard files
    current_path = Path('keyboards/')
    for directory in keyboard_path.parts:
        current_path = current_path / directory
        keyboard_h = '%s.h' % (directory,)
        keyboard_h_path = current_path / keyboard_h
        if keyboard_h_path.exists():
            layouts.update(find_layouts(keyboard_h_path))

    if not layouts:
        # If we didn't find any layouts above we widen our search. This is error
        # prone which is why we want to encourage people to follow the standard above.
        cli.log.warning('%s: Falling back to searching for KEYMAP/LAYOUT macros.' % (keyboard))
        for file in glob('keyboards/%s/*.h' % keyboard):
            if file.endswith('.h'):
                these_layouts = find_layouts(file)
                if these_layouts:
                    layouts.update(these_layouts)

    if 'LAYOUTS' in rules_mk:
        # Match these up against the supplied layouts
        supported_layouts = rules_mk['LAYOUTS'].strip().split()
        for layout_name in sorted(layouts):
            if not layout_name.startswith('LAYOUT_'):
                continue
            layout_name = layout_name[7:]
            if layout_name in supported_layouts:
                supported_layouts.remove(layout_name)

        if supported_layouts:
            cli.log.error('%s: Missing layout pp macro for %s' % (keyboard, supported_layouts))

    return layouts


def parse_config_h(keyboard):
    """Parses all the config_h.mk files for a keyboard.
    """
    rules_mk = parse_rules_mk(keyboard)
    config_h = parse_config_h_file('keyboards/%s/config.h' % keyboard)

    if 'DEFAULT_FOLDER' in rules_mk:
        keyboard = rules_mk['DEFAULT_FOLDER']
        config_h = parse_config_h_file('keyboards/%s/%s/config.h' % (keyboard, rules_mk['DEFAULT_FOLDER']), config_h)

    return config_h


def parse_config_h_file(file, config_h=None):
    """Extract defines from a config.h file.
    """
    if not config_h:
        config_h = {}

    file = Path(file)

    if exists(file):
        config_h_lines = file.read_text().split('\n')

        for linenum, line in enumerate(config_h_lines):
            line = line.strip()

            if '//' in line:
                line = line[:line.index('//')].strip()

            if not line:
                continue

            line = line.split()

            if line[0] == '#define':
                if len(line) == 1:
                    cli.log.error('%s: Incomplete #define! On or around line %s' % (file, linenum))
                elif len(line) == 2:
                    config_h[line[1]] = True
                else:
                    config_h[line[1]] = ' '.join(line[2:])

            elif line[0] == '#undef':
                if len(line) == 2:
                    if line[1] in config_h:
                        if config_h[line[1]] is True:
                            del config_h[line[1]]
                        else:
                            config_h[line[1]] = False
                else:
                    cli.log.error('%s: Incomplete #undef! On or around line %s' % (file, linenum))

    return config_h


def parse_rules_mk(keyboard):
    """Parses all the rules.mk files for a keyboard.
    """
    rules_mk = parse_rules_mk_file('keyboards/%s/rules.mk' % keyboard)

    if 'DEFAULT_FOLDER' in rules_mk:
        keyboard = rules_mk['DEFAULT_FOLDER']
        rules_mk = parse_rules_mk_file('keyboards/%s/%s/rules.mk' % (keyboard, rules_mk['DEFAULT_FOLDER']), rules_mk)

    return rules_mk


def parse_rules_mk_file(file, rules_mk=None):
    """Turn a rules.mk file into a dictionary.
    """
    if not rules_mk:
        rules_mk = {}

    file = Path(file)

    if file.exists():
        rules_mk_lines = file.read_text().split('\n')

        for line in rules_mk_lines:
            line = line.strip().split('#')[0]

            if '#' in line:
                line = line[:line.index('#')].strip()

            if not line:
                continue

            if '=' in line:
                if '+=' in line:
                    key, value = line.split('+=')
                    if key.strip() not in rules_mk:
                        rules_mk[key.strip()] = value.strip()
                    else:
                        rules_mk[key.strip()] += ' ' + value.strip()

                else:
                    key, value = line.split('=', 1)
                    rules_mk[key.strip()] = value.strip()

    return rules_mk


def render_layout(layout_data, key_labels=None):
    """Renders a single layout.
    """
    textpad = [array('u', ' ' * 200) for x in range(50)]

    for key in layout_data:
        x = ceil(key.get('x', 0) * 4)
        y = ceil(key.get('y', 0) * 3)
        w = ceil(key.get('w', 1) * 4)
        h = ceil(key.get('h', 1) * 3)

        if key_labels:
            label = key_labels.pop(0)
            if label.startswith('KC_'):
                label = label[3:]
        else:
            label = key.get('label', '')

        label_len = w - 2
        label_leftover = label_len - len(label)

        if len(label) > label_len:
            label = label[:label_len]

        label_blank = ' ' * label_len
        label_border = '─' * label_len
        label_middle = label + ' '*label_leftover  # noqa: yapf insists there be no whitespace around *

        top_line = array('u', '┌' + label_border + '┐')
        lab_line = array('u', '│' + label_middle + '│')
        mid_line = array('u', '│' + label_blank + '│')
        bot_line = array('u', '└' + label_border + "┘")

        textpad[y][x:x + w] = top_line
        textpad[y + 1][x:x + w] = lab_line
        for i in range(h - 3):
            textpad[y + i + 2][x:x + w] = mid_line
        textpad[y + h - 1][x:x + w] = bot_line

    lines = []
    for line in textpad:
        if line.tounicode().strip():
            lines.append(line.tounicode().rstrip())

    return '\n'.join(lines)


def render_layouts(info_json):
    """Renders all the layouts from an `info_json` structure.
    """
    layouts = {}

    for layout in info_json['layouts']:
        layout_data = info_json['layouts'][layout]['layout']
        layouts[layout] = render_layout(layout_data)

    return layouts
