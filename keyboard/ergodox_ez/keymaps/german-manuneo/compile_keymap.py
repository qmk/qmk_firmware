# encoding: utf-8
from __future__ import division
from __future__ import print_function
from __future__ import absolute_import
from __future__ import unicode_literals

import os
import io
import re
import sys
import json
import unicodedata
import collections

PY2 = sys.version_info.major == 2

if PY2:
	chr = unichr


ONELINE_COMMENT_RE = re.compile(r"^\s*//.*$", re.MULTILINE)
INLINE_COMMENT_RE = re.compile(
    r"([\,\"\[\]\{\}\d])\s+//\s[^\"\]\}\{\[]*$", re.MULTILINE
)
TRAILING_COMMA_RE = re.compile(
    r",$\s*([\]\}])", re.MULTILINE
)

def loads(raw_data):
    if isinstance(raw_data, bytes):
        raw_data = raw_data.decode('utf-8')
    raw_data = ONELINE_COMMENT_RE.sub(r"", raw_data)
    raw_data = INLINE_COMMENT_RE.sub(r"\1", raw_data)
    raw_data = TRAILING_COMMA_RE.sub(r"\1", raw_data)
    return json.loads(raw_data)

with io.open("keymap.md", encoding="utf-8") as fh:
	lines = fh.readlines()

SECTIONS = [
	'layout_config',
	'layers',
]

config = {
	"includes_basedir": "quantum/",
    "keymaps_includes": [
        "keymap_common.h",
    ],
	'filler': "-+.':x",
	'separator': "|",
    'default_key_prefix': ["KC_"],
    'unicode_macros': [],
    'macro_ids': ['UMS'],
    'layers': collections.OrderedDict(),
	'layer_lines': collections.OrderedDict(),
}

section_start_index = -1
current_section = None
current_layer_name = None
current_layer_lines = []
config_data = []

def end_section():
	global section_start_index
	global current_layer_lines
	section_start_index = -1
	if current_section == 'layout_config':
		config.update(loads("".join(
			config_data
		)))
	elif current_section == 'layers':
		config['layer_lines'][current_layer_name] = current_layer_lines
		current_layer_lines = []


for i, line in enumerate(lines):
	if line.startswith("# "):
		section = line[2:].strip().replace(" ", "_").lower()
		if section in SECTIONS:
			current_section = section
	elif line.startswith("## "):
		sub_section = line[3:]
		if current_section == 'layers':
			current_layer_name = sub_section.strip()
			# TODO: parse descriptio
			config['layers'][current_layer_name] = ""
	elif line.startswith("    "):
		if section_start_index < 0:
			section_start_index = i
		if current_section == 'layout_config':
			config_data.append(line)
		elif current_section == 'layers':
			if not line.strip():
				continue
			current_layer_lines.append(line)
	elif section_start_index > 0:
		end_section()

end_section()

KEYDEF_RE = re.compile(r"#define ((?:{})(?:\w+))".format(
	"|".join(config['key_prefixes'])
))
IF0_RE = re.compile(r"^#if 0$.*?#endif", re.MULTILINE | re.DOTALL)
COMMENT_RE = re.compile(r"/\*.*?\*/", re.MULTILINE | re.DOTALL)
ENUM_RE = re.compile(r"(enum\s\w+\s\{.*?\};)", re.MULTILINE | re.DOTALL)
ENUM_KEY_RE = re.compile(r"({}\w+)".format(
	"|".join(config['key_prefixes'])
))

def parse_keydefs(path):
	with io.open(path, encoding="utf-8") as fh:
		data = fh.read()
	data, _ = COMMENT_RE.subn("", data)
	data, _ = IF0_RE.subn("", data)

	for match in KEYDEF_RE.finditer(data):
		yield match.groups()[0]

	for enum_match in ENUM_RE.finditer(data):
		enum = enum_match.groups()[0]
		for key_match in ENUM_KEY_RE.finditer(enum):
			yield key_match.groups()[0]

valid_keycodes = set()
basepath = os.path.abspath(os.path.join(
	os.path.dirname(__file__), "..", "..", "..", ".."
))

valid_keycodes.update(parse_keydefs(os.path.join(
	basepath, "tmk_core", "common", "keycode.h"
)))

for include_path in config['keymaps_includes']:
	path = os.path.join(basepath, config['includes_dir'], include_path)
	path = path.replace("/", os.sep)
	if os.path.exists(path):
		valid_keycodes.update(parse_keydefs(path))

LAYER_CHANGE_RE = re.compile(r"(DF|TG|MO)\(\d+\)")
MACRO_RE = re.compile(r"M\(\w+\)")
UNICODE_RE = re.compile(r"U[0-9A-F]{4}")
NON_CODE = re.compile(r"^[^A-Z0-9_]$")


def UNICODE_MACRO(config, c):
	# TODO: don't use macro for codepoints below 0x2000
	macro_id = "UC_" + (
		unicodedata.name(c)
		.replace(" ", "_")
		.replace("-", "_")
		.replace("SUPERSCRIPT_", "SUP_")
		.replace("SUBSCRIPT_", "SUB_")
		.replace("GREEK_SMALL_LETTER", "GR_LC")
		.replace("GREEK_CAPITAL_LETTER", "GR_UC")
		.replace("VULGAR_FRACTION_", "FR_")
	)
	if macro_id not in config['macro_ids']:
		config['macro_ids'].append(macro_id)
	code = "{:04X}".format(ord(c))
	if (macro_id, code) not in config['unicode_macros']:
		config['unicode_macros'].append((macro_id, code))
	return "M({})".format(macro_id)


def MACRO(config, code):
	macro_id = code[2:-1]
	if macro_id not in config['macro_ids']:
		config['macro_ids'].append(macro_id)
	return code

# TODO: presumably we can have a macro or function which takes
#		the hex code and produces much smaller code.

WIN_UNICODE_MACRO_TEMPLATE = """
case {0}:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), {1}, U(LALT), END
	);
"""

LINUX_UNICODE_MACRO_TEMPLATE = """
case {0}:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), {1}, T(KP_ENTER), END
	);
"""

def macro_cases(config, mode):
	if mode == 'win':
		template = WIN_UNICODE_MACRO_TEMPLATE
	elif mode == 'linux':
		template = LINUX_UNICODE_MACRO_TEMPLATE
	else:
		raise ValueError("Invalid mode: ", mode)
	template = template.strip()

	for macro_id, unimacro_chars in config['unicode_macros']:
		unimacro_keys = ", ".join(
			"T({})".format(
				"KP_" + char if char.isdigit() else char
			) for char in unimacro_chars
		)
		yield template.format(macro_id, unimacro_keys)


MACROCODE = """
#define UC_MODE_WIN 0
#define UC_MODE_LINUX 1

static uint16_t unicode_mode = UC_MODE_WIN;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {{
	if (!record->event.pressed) {{
		return MACRO_NONE;
	}}
  	// MACRODOWN only works in this function
    switch(id) {{
    	case UMS:
    		unicode_mode = (unicode_mode + 1) % 2;
    		break;
    	{macro_cases}
    	default:
    		break;
    }}
	if (unicode_mode == UC_MODE_WIN) {{
		switch(id) {{
			{win_macro_cases}
	    	default:
	    		break;
		}}
	}} else if (unicode_mode == UC_MODE_LINUX) {{
		switch(id) {{
			{linux_macro_cases}
	    	default:
	    		break;
		}}
	}}
    return MACRO_NONE;
}};
"""


def iter_keycodes(layer_lines, config):
	filler_re = re.compile("[" +
		config['filler'] + " " +
	"]")

	all_codes = []
	for line in layer_lines:
		line, _ = filler_re.subn("", line.strip())
		if not line:
			continue
		codes = line.split(config['separator'])
		all_codes.extend(codes[1:-1])

	key_groups = {}
	for group_index, key_indexes in enumerate(config['keymap_indexes']):
		for key_index in key_indexes:
			key_groups[key_index] = group_index

	keymap_indexes = sum(config['keymap_indexes'], [])
	assert len(all_codes) == len(keymap_indexes)
	code_index_pairs = zip(all_codes, keymap_indexes)
	prev_index = None
	for i, (code, key_index) in enumerate(code_index_pairs):
		code = code.strip()
		layer_match = LAYER_CHANGE_RE.match(code)
		unicode_match = UNICODE_RE.match(code)
		noncode_match = NON_CODE.match(code)
		macro_match = MACRO_RE.match(code)

		ws = "\n" if key_groups[key_index] != prev_index else ""
		prev_index = key_groups[key_index]

		try:
			if not code:
				code = 'KC_TRNS'
			elif layer_match:
				pass
			elif macro_match:
				code = MACRO(config, code)
			elif unicode_match:
				hex_code = code[1:]
				code = UNICODE_MACRO(config, chr(int(hex_code, 16)))
			elif noncode_match:
				code = UNICODE_MACRO(config, code)
			elif "_" in code:
				assert code in valid_keycodes, "unknown code '{}'".format(code)
			else:
				for prefix in config['key_prefixes']:
					if prefix + code in valid_keycodes:
						code = prefix + code
						break
				assert code in valid_keycodes, "unknown code '{}'".format(code)
			yield code, key_index, ws
		except AssertionError:
			print("Error processing code", repr(code).encode("utf-8"))
			raise

USERCODE = """
// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case L1:
            ergodox_right_led_1_on();
            break;
        case L2:
            ergodox_right_led_2_on();
            break;
        case L3:
            ergodox_right_led_3_on();
            break;
        case L4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case L5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        // case L6:
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        // case L7:
        //     ergodox_right_led_1_on();
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        default:
            ergodox_board_led_off();
            break;
    }
};
"""

def parse_keymaps(config):
	keymaps = {}
	layer_line_items = config['layer_lines'].items()
	for i, (layer_name, layer_lines) in enumerate(layer_line_items):
		print("parseing layer", layer_name)
		keymap = {}
		for code, key_index, ws in iter_keycodes(layer_lines, config):
			keymap[key_index] = (code, ws)
		keymaps[layer_name] = [v for k, v in sorted(keymap.items())]
	return keymaps


def iter_keymap_lines(config, keymaps):
	for include_path in config['keymaps_includes']:
		yield '#include "{}"\n'.format(include_path)

	yield "\n"

	layer_items = config['layers'].items()
	for i, (layer_name, description) in enumerate(layer_items):
		yield '#define L{0:<3} {0:<5}  // {1}\n'.format(i, layer_name)

	for i, macro_id in enumerate(config['macro_ids']):
		yield "#define {} {}\n".format(macro_id, i)

	yield "\n"

	yield "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n"

	layer_line_items = config['layer_lines'].items()
	last_index = config['keymap_indexes'][-1]
	for i, (layer_name, layer_lines) in enumerate(layer_line_items):
		keymap = keymaps[layer_name]
		yield "/*\n"
		for line in layer_lines:
			yield " *{}".format(line)
		yield "*/\n"

		yield "[L{0}] = KEYMAP(\n".format(i)

		for key_index, (code, ws) in enumerate(keymap):
			yield "\t{}".format(code)
			if key_index < len(keymap) - 1:
				yield ","
			yield ws
		yield "),\n"

	yield "};\n\n"

	yield "const uint16_t PROGMEM fn_actions[] = {\n"
	yield "};\n"

	yield MACROCODE.format(
		macro_cases="",
		win_macro_cases="\n".join(macro_cases(config, mode='win')),
		linux_macro_cases="\n".join(macro_cases(config, mode='linux')),
	)

	yield USERCODE


with io.open("keymap.c", mode="w", encoding="utf-8") as fh:
	for data in iter_keymap_lines(config, parse_keymaps(config)):
		fh.write(data)


# print("\n".join(sorted(valid_keycodes)))
# print(json.dumps(config, indent=4))
