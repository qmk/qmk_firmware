from milc import cli

from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.lighting import load_lighting_spec
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE

PREFIX_MAP = {
    'rgblight': {
        'ifdef': 'RGBLIGHT_EFFECT',
        'def': 'RGBLIGHT_MODE',
    },
    'rgb_matrix': {
        'ifdef': 'ENABLE_RGB_MATRIX',
        'def': 'RGB_MATRIX',
    },
    'led_matrix': {
        'ifdef': 'ENABLE_LED_MATRIX',
        'def': 'LED_MATRIX',
    },
}


def _always_enabled(id):
    """Assumption that first effect is always enabled
    """
    return id == '0x00'


def _wrap_ifdef(line, define):
    return f'''
#ifdef {define}
{line}
#endif'''


def _append_lighting_map(lines, feature, spec):
    """Translate effect to 'constant id'->'firmware id' lookup table
    """
    groups = spec.get('groups', {})
    ifdef_prefix = PREFIX_MAP[feature]['ifdef']
    def_prefix = PREFIX_MAP[feature]['def']

    lines.append(f'static const uint8_t {feature}_effect_map[][2] PROGMEM = {{')
    for id, obj in spec.get('effects', {}).items():
        define = obj['define']
        offset = f' + {obj["offset"]}' if obj['offset'] else ''

        line = f'{{ {id}, {def_prefix}_{define}{offset}}},'

        if not _always_enabled(id):
            line = _wrap_ifdef(line, f'{ifdef_prefix}_{define}')

        group = groups.get(obj.get('group', None), {}).get('define', None)
        if group:
            line = _wrap_ifdef(line, group)

        lines.append(line)

    lines.append('};')

    # add helper funcs
    lines.append(
        f'''
uint8_t {feature}_effect_to_id(uint8_t val) {{
    for(uint8_t i = 0; i < ARRAY_SIZE({feature}_effect_map); i++) {{
        if (pgm_read_byte(&{feature}_effect_map[i][1]) == val)
            return pgm_read_byte(&{feature}_effect_map[i][0]);
    }}
    return 0xFF;
}}

uint8_t {feature}_id_to_effect(uint8_t val) {{
    for(uint8_t i = 0; i < ARRAY_SIZE({feature}_effect_map); i++) {{
        if (pgm_read_byte(&{feature}_effect_map[i][0]) == val)
            return pgm_read_byte(&{feature}_effect_map[i][1]);
    }}
    return 0xFF;
}}'''
    )


def _append_lighting_bit_field(lines, feature, spec):
    """Translate effect to bit of bit-field
    """
    groups = spec.get('groups', {})
    ifdef_prefix = PREFIX_MAP[feature]['ifdef']

    lines.append(f'enum {{ ENABLED_{feature.upper()}_EFFECTS = 0')
    for id, obj in spec.get('effects', {}).items():
        define = obj['define']

        line = f'    | (1ULL << {id})'

        if not _always_enabled(id):
            line = _wrap_ifdef(line, f'{ifdef_prefix}_{define}')

        group = groups.get(obj.get('group', None), {}).get('define', None)
        if group:
            line = _wrap_ifdef(line, group)

        lines.append(line)

    lines.append('};')


def _append_lighting_mapping(lines, feature):
    """Generate lookup table and bit-field of effect
    """
    spec = load_lighting_spec(feature)

    _append_lighting_bit_field(lines, feature, spec)
    _append_lighting_map(lines, feature, spec)


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help='Quiet mode, only output error messages')
@cli.argument('-f', '--feature', required=True, help='Feature to generate map', choices=PREFIX_MAP.keys())
@cli.subcommand('Generates effect header.')
def generate_lighting_map(cli):
    # Preamble
    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '// clang-format off']

    _append_lighting_mapping(lines, cli.args.feature)

    dump_lines(cli.args.output, lines, cli.args.quiet)
