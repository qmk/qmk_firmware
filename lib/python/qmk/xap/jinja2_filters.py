"""This script enables attachment of XAP-specific filters to Jinja2
"""
import re
from fnvhash import fnv1a_32
from jinja2 import Environment

from qmk.casing import to_snake

TRIPLET_PATTERN = re.compile(r'^(\d+)\.(\d+)\.(\d+)')
TYPE_ARRAY_PATTERN = re.compile(r'^([^\[]+)\[([^[\]]+)\]$')


def _fnv1a_32(s: str):
    res = fnv1a_32(bytes(s, 'utf-8'))
    return f'0x{res:08X}'


def _xap_type_to_c_before(xt: str):
    m = TYPE_ARRAY_PATTERN.match(xt)
    if m:
        return _xap_type_to_c(m.group(1))
    if xt == 'u8':
        return 'uint8_t'
    elif xt == 'u16':
        return 'uint16_t'
    elif xt == 'u32':
        return 'uint32_t'
    elif xt == 'u64':
        return 'uint64_t'
    elif xt == 'bool':
        return 'uint8_t'
    elif xt == 'string':
        return 'const char*'
    elif xt == 'token':
        return 'xap_token_t'
    elif xt == 'response_flags':
        return 'xap_response_flags_t'
    raise TypeError(f'Unknown XAP type: {xt}')


def _xap_type_to_c_after(xt: str):
    m = TYPE_ARRAY_PATTERN.match(xt)
    if m:
        try:
            extent = int(m.group(2))
            return f'[{extent}]'
        except ValueError:
            return '[]'
    return ''


def _xap_type_to_c(xt: str, name: str = None):
    if name is not None:
        name = re.sub(' ', '_', name)
        return f'{(_xap_type_to_c_before(xt))} {name}{(_xap_type_to_c_after(xt))}'
    return f'{(_xap_type_to_c_before(xt))}{(_xap_type_to_c_after(xt))}'


def _triplet_to_bcd(value: str):
    m = TRIPLET_PATTERN.match(value)
    if not m:
        return '0'
    return f'0x{int(m.group(1)):02d}{int(m.group(2)):02d}{int(m.group(3)):04d}'


def _newline_to_br(value: str):
    return value.replace('\n', '<br>')


def attach_filters(j2: Environment):
    j2.filters['to_snake'] = to_snake
    j2.filters['newline_to_br'] = _newline_to_br
    j2.filters['triplet_to_bcd'] = _triplet_to_bcd
    j2.filters['fnv1a_32'] = _fnv1a_32
    j2.filters['type_to_c'] = _xap_type_to_c
    j2.filters['type_to_c_before'] = _xap_type_to_c_before
    j2.filters['type_to_c_after'] = _xap_type_to_c_after
