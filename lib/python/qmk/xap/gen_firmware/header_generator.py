"""This script generates the XAP protocol generated header to be compiled into QMK.
"""
import re
from fnvhash import fnv1a_32

from qmk.casing import to_snake
from qmk.commands import dump_lines
from qmk.git import git_get_version
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE
from qmk.xap.common import latest_xap_defs, route_conditions


def _get_c_type(xap_type):
    if xap_type == 'bool':
        return 'bool'
    elif xap_type == 'u8':
        return 'uint8_t'
    elif xap_type == 'u16':
        return 'uint16_t'
    elif xap_type == 'u32':
        return 'uint32_t'
    elif xap_type == 'u64':
        return 'uint64_t'
    elif xap_type == 'struct':
        return 'struct'
    elif xap_type == 'string':
        return 'const char *'
    return 'unknown'


def _append_route_defines(lines, container, container_id=None, route_stack=None):
    """Handles building the list of the XAP routes, combining parent and child names together, as well as the route number.
    """
    if route_stack is None:
        route_stack = [container]
    else:
        route_stack.append(container)

    route_name = '_'.join([r['define'] for r in route_stack])

    if container_id:
        lines.append(f'#define {route_name} {container_id}')

    if 'routes' in container:
        for route_id in container['routes']:
            route = container['routes'][route_id]
            _append_route_defines(lines, route, route_id, route_stack)

    route_stack.pop()


def _append_route_masks(lines, container, container_id=None, route_stack=None):
    """Handles creating the equivalent XAP route masks, for capabilities checks. Forces value of `0` if disabled in the firmware.
    """
    if route_stack is None:
        route_stack = [container]
    else:
        route_stack.append(container)

    route_name = '_'.join([r['define'] for r in route_stack])
    condition = route_conditions(route_stack)

    if container_id:
        if condition:
            lines.append('')
            lines.append(f'#if {condition}')

        lines.append(f'#define {route_name}_MASK (1ul << ({route_name}))')

        if condition:
            lines.append(f'#else  // {condition}')
            lines.append(f'#define {route_name}_MASK 0')
            lines.append(f'#endif  // {condition}')
            lines.append('')

    if 'routes' in container:
        for route_id in container['routes']:
            route = container['routes'][route_id]
            _append_route_masks(lines, route, route_id, route_stack)

    route_stack.pop()


def _append_route_capabilities(lines, container, container_id=None, route_stack=None):
    """Handles creating the equivalent XAP route masks, for capabilities checks. Forces value of `0` if disabled in the firmware.
    """
    if route_stack is None:
        route_stack = [container]
    else:
        route_stack.append(container)

    route_name = '_'.join([r['define'] for r in route_stack])

    if 'routes' in container:
        lines.append('')
        lines.append(f'#define {route_name}_CAPABILITIES (0 \\')

        if 'routes' in container:
            for route_id in container['routes']:
                route = container['routes'][route_id]
                route_stack.append(route)
                child_name = '_'.join([r['define'] for r in route_stack])
                lines.append(f'  | ({child_name}_MASK) \\')
                route_stack.pop()

        lines.append('  )')

    if 'routes' in container:
        for route_id in container['routes']:
            route = container['routes'][route_id]
            _append_route_capabilities(lines, route, route_id, route_stack)

    route_stack.pop()


def _append_route_types(lines, container, container_id=None, route_stack=None):
    """Handles creating typedefs used by routes
    """
    if route_stack is None:
        route_stack = [container]
    else:
        route_stack.append(container)

    route_name = to_snake('_'.join([r['define'] for r in route_stack]))

    # Inbound
    if 'request_struct_members' in container:
        request_struct_members = container['request_struct_members']
        lines.append('typedef struct {')
        for member in request_struct_members:
            member_type = _get_c_type(member['type'])
            member_name = to_snake(member['name'])
            lines.append(f'    {member_type} {member_name};')
        lines.append(f'}} {route_name}_arg_t;')

    elif 'request_type' in container:
        request_type = container['request_type']
        lines.append(f'typedef {_get_c_type(request_type)} {route_name}_arg_t;')

    # Outbound
    qualifier = 'const' if 'return_constant' in container else ''
    if 'return_struct_members' in container:
        return_struct_members = container['return_struct_members']
        lines.append('typedef struct {')
        for member in return_struct_members:
            member_type = _get_c_type(member['type'])
            member_name = f'{qualifier} {to_snake(member["name"])}'
            lines.append(f'    {member_type} {member_name};')
        lines.append(f'}} {route_name}_t;')

    elif 'return_type' in container:
        return_type = container['return_type']
        found = re.search(r'(u\d+)\[(\d+)\]', return_type)
        if found:
            return_type, size = found.groups()
            lines.append(f'typedef struct {{ {_get_c_type(return_type)} x[{size}]; }} {route_name}_t;')
        else:
            lines.append(f'typedef {_get_c_type(return_type)} {route_name}_t;')

    # Recurse
    if 'routes' in container:
        for route_id in container['routes']:
            route = container['routes'][route_id]
            _append_route_types(lines, route, route_id, route_stack)

    route_stack.pop()


def _append_internal_types(lines, container):
    """Handles creating the various constants, types, defines, etc.
    """
    response_flags = container.get('response_flags', {})
    prefix = response_flags['define_prefix']
    for key, value in response_flags['bits'].items():
        define = value.get('define')
        lines.append(f'#define {prefix}_{define} (1ul << ({key}))')

    # Add special
    lines.append(f'#define {prefix}_FAILED 0x00')
    lines.append('')

    broadcast_messages = container.get('broadcast_messages', {})
    broadcast_prefix = broadcast_messages['define_prefix']
    for key, value in broadcast_messages['messages'].items():
        define = value.get('define')
        lines.append(f'#define {broadcast_prefix}_{define} {key}')

    # Add special
    lines.append(f'#define {broadcast_prefix}_TOKEN 0xFFFF')
    lines.append('')

    additional_types = {}
    types = container.get('type_definitions', {})
    for key, value in types.items():
        data_type = _get_c_type(value['type'])
        additional_types[key] = f'xap_{key}_t'

    for key, value in types.items():
        data_type = _get_c_type(value['type'])
        if data_type == 'struct':
            members = value['struct_members']

            lines.append(f'typedef {data_type} {{')
            for member in members:
                member_name = member["name"]
                member_type = _get_c_type(member["type"])
                if member_type == 'unknown':
                    member_type = additional_types[member["type"]]
                lines.append(f'  {member_type} {member_name};')
            lines.append(f'}} xap_{key}_t;')
        else:
            lines.append(f'typedef {data_type} xap_{key}_t;')


def generate_header(output_file, keyboard):
    """Generates the XAP protocol header file, generated during normal build.
    """
    xap_defs = latest_xap_defs()

    # Preamble
    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '']

    # Versions
    prog = re.compile(r'^(\d+)\.(\d+)\.(\d+)')
    b = prog.match(xap_defs['version'])
    lines.append(f'#define XAP_BCD_VERSION 0x{int(b.group(1)):02d}{int(b.group(2)):02d}{int(b.group(3)):04d}ul')
    b = prog.match(git_get_version() or "")
    lines.append(f'#define QMK_BCD_VERSION 0x{int(b.group(1)):02d}{int(b.group(2)):02d}{int(b.group(3)):04d}ul')
    keyboard_id = fnv1a_32(bytes(keyboard, 'utf-8'))
    lines.append(f'#define XAP_KEYBOARD_IDENTIFIER 0x{keyboard_id:08X}ul')
    lines.append('')

    # Types
    _append_internal_types(lines, xap_defs)
    lines.append('')
    _append_route_types(lines, xap_defs)
    lines.append('')

    # Append the route and command defines
    _append_route_defines(lines, xap_defs)
    lines.append('')
    _append_route_masks(lines, xap_defs)
    lines.append('')
    _append_route_capabilities(lines, xap_defs)
    lines.append('')

    dump_lines(output_file, lines)
