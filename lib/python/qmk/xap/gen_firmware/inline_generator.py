"""This script generates the XAP protocol generated header to be compiled into QMK.
"""
from qmk.casing import to_snake
from qmk.commands import dump_lines
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE
from qmk.xap.common import merge_xap_defs, route_conditions


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


def _get_c_size(xap_type):
    if xap_type == 'u8':
        return 'sizeof(uint8_t)'
    elif xap_type == 'u16':
        return 'sizeof(uint16_t)'
    elif xap_type == 'u32':
        return 'sizeof(uint32_t)'
    elif xap_type == 'u64':
        return 8
    elif xap_type == 'u8[32]':
        return 32
    return 0


def _get_route_type(container):
    if 'routes' in container:
        return 'XAP_ROUTE'
    elif 'return_execute' in container:
        return 'XAP_EXECUTE'
    elif 'return_value' in container:
        if container['return_type'] == 'u8':
            return 'XAP_VALUE'
    elif 'return_constant' in container:
        if container['return_type'] == 'u8':
            return 'XAP_CONST_MEM'
        elif container['return_type'] == 'u16':
            return 'XAP_CONST_MEM'
        elif container['return_type'] == 'u32':
            return 'XAP_CONST_MEM'
        elif container['return_type'] == 'u64':
            return 'XAP_CONST_MEM'
        elif container['return_type'] == 'struct':
            return 'XAP_CONST_MEM'
        elif container['return_type'] == 'string':
            return 'XAP_CONST_MEM'
    elif 'return_getter' in container:
        if container['return_type'] == 'u32':
            return 'XAP_GETTER'
    return 'UNSUPPORTED'


def _append_routing_table_declaration(lines, container, container_id, route_stack):
    route_stack.append(container)

    route_name = to_snake('_'.join([r['define'] for r in route_stack]))

    condition = route_conditions(route_stack)
    if condition:
        lines.append(f'#if {condition}')

    if 'routes' in container:
        pass
    elif 'return_execute' in container:
        execute = container['return_execute']
        lines.append(f'bool xap_respond_{execute}(xap_token_t token, const uint8_t *data, size_t data_len);')

    # elif 'return_value' in container:
    #     value = container['return_value']
    #     return_type = container['return_type']
    #     lines.append('')
    #     lines.append(f'{_get_c_type(return_type)} {value} = 0;')

    elif 'return_constant' in container:

        if container['return_type'] == 'u8':
            constant = container['return_constant']
            lines.append('')
            lines.append(f'static const uint8_t {route_name}_data PROGMEM = {constant};')

        elif container['return_type'] == 'u16':
            constant = container['return_constant']
            lines.append('')
            lines.append(f'static const uint16_t {route_name}_data PROGMEM = {constant};')

        elif container['return_type'] == 'u32':
            constant = container['return_constant']
            lines.append('')
            lines.append(f'static const uint32_t {route_name}_data PROGMEM = {constant};')

        elif container['return_type'] == 'u64':
            constant = container['return_constant']
            lines.append('')
            lines.append(f'static const uint64_t {route_name}_data PROGMEM = {constant};')

        elif container['return_type'] == 'struct':
            lines.append('')
            lines.append(f'static const {route_name}_t {route_name}_data PROGMEM = {{')

            for constant in container['return_constant']:
                lines.append(f'    {constant},')

            lines.append('};')

        elif container['return_type'] == 'string':
            constant = container['return_constant']
            lines.append('')
            lines.append(f'static const char {route_name}_str[] PROGMEM = {constant};')

    elif 'return_getter' in container:

        if container['return_type'] == 'u32':
            lines.append('')
            lines.append(f'extern uint32_t {route_name}_getter(void);')

        elif container['return_type'] == 'struct':
            pass

    if condition:
        lines.append(f'#endif  // {condition}')
        lines.append('')

    route_stack.pop()


def _append_routing_table_entry_flags(lines, container, container_id, route_stack):
    pem_map = {
        None: 'ROUTE_PERMISSIONS_INSECURE',
        'secure': 'ROUTE_PERMISSIONS_SECURE',
    }

    is_secure = pem_map[container.get('permissions', None)]

    lines.append('        .flags = {')
    lines.append(f'            .type = {_get_route_type(container)},')
    lines.append(f'            .secure = {is_secure},')
    lines.append('        },')


def _append_routing_table_entry_route(lines, container, container_id, route_stack):
    route_name = to_snake('_'.join([r['define'] for r in route_stack]))
    lines.append(f'        .child_routes = {route_name}_table,')
    lines.append(f'        .child_routes_len = sizeof({route_name}_table)/sizeof(xap_route_t),')


def _append_routing_table_entry_execute(lines, container, container_id, route_stack):
    value = container['return_execute']
    lines.append(f'        .handler = xap_respond_{value},')


def _append_routing_table_entry_value(lines, container, container_id, route_stack):
    value = container['return_value']
    lines.append(f'        .const_data = &{value},')
    lines.append(f'        .const_data_len = sizeof({value}),')


def _append_routing_table_entry_u32getter(lines, container, container_id, route_stack):
    route_name = to_snake('_'.join([r['define'] for r in route_stack]))
    lines.append(f'        .u32getter = &{route_name}_getter,')


def _append_routing_table_entry_const_data(lines, container, container_id, route_stack):
    route_name = to_snake('_'.join([r['define'] for r in route_stack]))
    lines.append(f'        .const_data = &{route_name}_data,')
    lines.append(f'        .const_data_len = sizeof({route_name}_data),')


def _append_routing_table_entry_string(lines, container, container_id, route_stack):
    route_name = to_snake('_'.join([r['define'] for r in route_stack]))
    lines.append(f'        .const_data = {route_name}_str,')
    lines.append(f'        .const_data_len = sizeof({route_name}_str) - 1,')


def _append_routing_table_entry(lines, container, container_id, route_stack):
    route_stack.append(container)
    route_name = '_'.join([r['define'] for r in route_stack])
    condition = route_conditions(route_stack)

    if condition:
        lines.append(f'#if {condition}')

    lines.append(f'    [{route_name}] = {{')

    _append_routing_table_entry_flags(lines, container, container_id, route_stack)
    if 'routes' in container:
        _append_routing_table_entry_route(lines, container, container_id, route_stack)
    elif 'return_execute' in container:
        _append_routing_table_entry_execute(lines, container, container_id, route_stack)
    elif 'return_value' in container:
        _append_routing_table_entry_value(lines, container, container_id, route_stack)
    elif 'return_constant' in container:
        if container['return_type'] == 'u8':
            _append_routing_table_entry_const_data(lines, container, container_id, route_stack)
        elif container['return_type'] == 'u16':
            _append_routing_table_entry_const_data(lines, container, container_id, route_stack)
        elif container['return_type'] == 'u32':
            _append_routing_table_entry_const_data(lines, container, container_id, route_stack)
        elif container['return_type'] == 'u64':
            _append_routing_table_entry_const_data(lines, container, container_id, route_stack)
        elif container['return_type'] == 'struct':
            _append_routing_table_entry_const_data(lines, container, container_id, route_stack)
        elif container['return_type'] == 'string':
            _append_routing_table_entry_string(lines, container, container_id, route_stack)
    elif 'return_getter' in container:
        if container['return_type'] == 'u32':
            _append_routing_table_entry_u32getter(lines, container, container_id, route_stack)

    lines.append('    },')

    if condition:
        lines.append(f'#endif  // {condition}')

    route_stack.pop()


def _append_routing_tables(lines, container, container_id=None, route_stack=None):
    """Handles building the list of the XAP routes, combining parent and child names together, as well as the route number.
    """
    if route_stack is None:
        route_stack = [container]
    else:
        route_stack.append(container)

    route_name = to_snake('_'.join([r['define'] for r in route_stack]))
    condition = route_conditions(route_stack)

    if 'routes' in container:
        for route_id in container['routes']:
            route = container['routes'][route_id]
            _append_routing_tables(lines, route, route_id, route_stack)

        for route_id in container['routes']:
            route = container['routes'][route_id]
            _append_routing_table_declaration(lines, route, route_id, route_stack)

        lines.append('')
        if condition:
            lines.append(f'#if {condition}')

        lines.append(f'static const xap_route_t {route_name}_table[] PROGMEM = {{')

        for route_id in container['routes']:
            route = container['routes'][route_id]
            _append_routing_table_entry(lines, route, route_id, route_stack)

        lines.append('};')

        if condition:
            lines.append(f'#endif  // {condition}')
            lines.append('')

    route_stack.pop()


def _append_broadcast_messages(lines, container):
    """TODO:
    """
    broadcast_messages = container.get('broadcast_messages', {})
    broadcast_prefix = broadcast_messages['define_prefix']
    for key, value in broadcast_messages['messages'].items():
        define = value.get('define')
        name = to_snake(f'{broadcast_prefix}_{define}')

        if 'return_type' in value:
            ret_type = _get_c_type(value['return_type'])
            lines.append(f'void {name}({ret_type} value) {{ xap_broadcast({key}, &value, sizeof(value)); }}')
        else:
            lines.append(f'void {name}(const void *data, size_t length){{ xap_broadcast({key}, data, length); }}')


def generate_inline(output_file, keyboard, keymap):
    """Generates the XAP protocol header file, generated during normal build.
    """
    xap_defs = merge_xap_defs(keyboard, keymap)

    # Preamble
    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '']

    # Add all the generated code
    _append_broadcast_messages(lines, xap_defs)
    _append_routing_tables(lines, xap_defs)

    dump_lines(output_file, lines)
