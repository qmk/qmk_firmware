"""This script generates the XAP protocol generated header to be compiled into QMK.
"""
from qmk.casing import to_snake
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


def _get_route_type(container):
    if 'routes' in container:
        return 'XAP_ROUTE'
    elif 'return_constant' in container:
        if container['return_type'] == 'u32':
            return 'XAP_VALUE'
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

    if 'routes' in container:
        pass

    elif 'return_constant' in container:

        if container['return_type'] == 'u32':
            pass

        elif container['return_type'] == 'struct':
            lines.append('')
            lines.append(f'static const struct {route_name}_t {{')

            for member in container['return_struct_members']:
                member_type = _get_c_type(member['type'])
                member_name = to_snake(member['name'])
                lines.append(f'    const {member_type} {member_name};')

            lines.append(f'}} {route_name}_data PROGMEM = {{')

            for constant in container['return_constant']:
                lines.append(f'    {constant},')

            lines.append('}};')

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

    route_stack.pop()


def _append_routing_table_entry_flags(lines, container, container_id, route_stack):
    is_secure = 1 if ('secure' in container and container['secure'] is True) else 0
    lines.append('        .flags = {{')
    lines.append(f'            .type = {_get_route_type(container)},')
    lines.append(f'            .is_secure = {is_secure},')
    lines.append('        }},')


def _append_routing_table_entry_route(lines, container, container_id, route_stack):
    route_name = to_snake('_'.join([r['define'] for r in route_stack]))
    lines.append(f'        .child_routes = {route_name}_table,')
    lines.append(f'        .child_routes_len = sizeof({route_name}_table)/sizeof(xap_route_t),')


def _append_routing_table_entry_u32value(lines, container, container_id, route_stack):
    value = container['return_constant']
    lines.append(f'        .u32value = {value},')


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
    elif 'return_constant' in container:
        if container['return_type'] == 'u32':
            _append_routing_table_entry_u32value(lines, container, container_id, route_stack)
        elif container['return_type'] == 'struct':
            _append_routing_table_entry_const_data(lines, container, container_id, route_stack)
        elif container['return_type'] == 'string':
            _append_routing_table_entry_string(lines, container, container_id, route_stack)
    elif 'return_getter' in container:
        if container['return_type'] == 'u32':
            _append_routing_table_entry_u32getter(lines, container, container_id, route_stack)

    lines.append('    }},')

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


def generate_inline(output_file):
    """Generates the XAP protocol header file, generated during normal build.
    """
    xap_defs = latest_xap_defs()

    # Preamble
    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '']

    # Add all the generated code
    _append_routing_tables(lines, xap_defs)

    # Generate the full output
    xap_generated_inl = '\n'.join(lines)

    # Clean up newlines
    while "\n\n\n" in xap_generated_inl:
        xap_generated_inl = xap_generated_inl.replace("\n\n\n", "\n\n")

    if output_file:
        if output_file.name == '-':
            print(xap_generated_inl)
        else:
            output_file.parent.mkdir(parents=True, exist_ok=True)
            if output_file.exists():
                output_file.replace(output_file.parent / (output_file.name + '.bak'))
            output_file.write_text(xap_generated_inl)
