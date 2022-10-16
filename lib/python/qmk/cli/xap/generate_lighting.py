from milc import cli

from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.xap.common import load_lighting_spec
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


def _append_lighting_map(lines, feature, spec):
    """TODO:
    """
    groups = spec.get('groups', {})
    ifdef_prefix = PREFIX_MAP[feature]['ifdef']
    def_prefix = PREFIX_MAP[feature]['def']

    lines.append(f'static uint8_t {feature}_effect_map[][2] = {{')
    for id, obj in spec.get('effects', {}).items():
        define = obj['define']
        offset = f' + {obj["offset"]}' if obj['offset'] else ''

        line = f'''
#ifdef {ifdef_prefix}_{define}
    {{ {id}, {def_prefix}_{define}{offset}}},
#endif'''

        group = groups.get(obj.get('group', None), {}).get('define', None)
        if group:
            line = f'''
#ifdef {group}
{line}
#endif'''

        lines.append(line)

    lines.append('};')

    # add helper funcs
    lines.append(
        f'''
uint8_t {feature}2xap(uint8_t val) {{
    for(uint8_t i = 0; i < ARRAY_SIZE({feature}_effect_map); i++) {{
        if ({feature}_effect_map[i][1] == val)
            return {feature}_effect_map[i][0];
    }}
    return 0xFF;
}}

uint8_t xap2{feature}(uint8_t val) {{
    for(uint8_t i = 0; i < ARRAY_SIZE({feature}_effect_map); i++) {{
        if ({feature}_effect_map[i][0] == val)
            return {feature}_effect_map[i][1];
    }}
    return 0xFF;
}}'''
    )


def _append_lighting_bitmask(lines, feature, spec):
    """TODO:
    """
    groups = spec.get('groups', {})
    ifdef_prefix = PREFIX_MAP[feature]['ifdef']

    lines.append(f'enum {{ ENABLED_{feature.upper()}_EFFECTS = 0')
    for id, obj in spec.get('effects', {}).items():
        define = obj['define']

        line = f'''
#ifdef {ifdef_prefix}_{define}
    | (1ULL << {id})
#endif'''

        group = groups.get(obj.get('group', None), {}).get('define', None)
        if group:
            line = f'''
#ifdef {group}
{line}
#endif'''

        lines.append(line)

    lines.append('};')


def _append_lighting_mapping(lines):
    """TODO:
    """
    # TODO: remove bodge for always enabled effects
    lines.append('''
#define RGBLIGHT_EFFECT_STATIC_LIGHT
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_LED_MATRIX_SOLID
''')

    for feature in PREFIX_MAP.keys():
        spec = load_lighting_spec(feature)

        lines.append(f'#ifdef {feature.upper()}_ENABLE')
        _append_lighting_map(lines, feature, spec)
        _append_lighting_bitmask(lines, feature, spec)
        lines.append(f'#endif //{feature.upper()}_ENABLE')


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.subcommand('Generates effect header.')
def xap_generate_lighting_map(cli):
    # Preamble
    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '// clang-format off']

    _append_lighting_mapping(lines)

    dump_lines(cli.args.output, lines, cli.args.quiet)
