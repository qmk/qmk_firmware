#!/usr/bin/env python
#
# Copyright 2021 Don Kjer
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

from __future__ import print_function

import argparse
from struct import pack, unpack
import os, sys

MAGIC_FEEA     = '\xea\xff\xfe\xff'

MAGIC_FEE9     = '\x16\x01'
EMPTY_WORD     = '\xff\xff'
WORD_ENCODING  = 0x8000
VALUE_NEXT     = 0x6000
VALUE_RESERVED = 0x4000
VALUE_ENCODED  = 0x2000
BYTE_RANGE     = 0x80

CHUNK_SIZE = 1024

STRUCT_FMTS = {
    1: 'B',
    2: 'H',
    4: 'I'
}
PRINTABLE='0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ '

EECONFIG_V1 = [
    ("MAGIC",                0, 2),
    ("DEBUG",                2, 1),
    ("DEFAULT_LAYER",        3, 1),
    ("KEYMAP",               4, 1),
    ("MOUSEKEY_ACCEL",       5, 1),
    ("BACKLIGHT",            6, 1),
    ("AUDIO",                7, 1),
    ("RGBLIGHT",             8, 4),
    ("UNICODEMODE",         12, 1),
    ("STENOMODE",           13, 1),
    ("HANDEDNESS",          14, 1),
    ("KEYBOARD",            15, 4),
    ("USER",                19, 4),
    ("VELOCIKEY",           23, 1),
    ("HAPTIC",              24, 4),
    ("MATRIX",              28, 4),
    ("MATRIX_EXTENDED",     32, 2),
    ("KEYMAP_UPPER_BYTE",   34, 1),
]
VIABASE_V1 = 35

VERBOSE = False

def parseArgs():
    parser = argparse.ArgumentParser(description='Decode an STM32 emulated eeprom dump')
    parser.add_argument('-s', '--size', type=int,
                        help='Size of the emulated eeprom (default: input_size / 2)')
    parser.add_argument('-o', '--output', help='File to write decoded eeprom to')
    parser.add_argument('-y', '--layout-options-size', type=int,
                        help='VIA layout options size (default: 1)', default=1)
    parser.add_argument('-t', '--custom-config-size', type=int,
                        help='VIA custom config size (default: 0)', default=0)
    parser.add_argument('-l', '--layers', type=int,
                        help='VIA keyboard layers (default: 4)', default=4)
    parser.add_argument('-r', '--rows', type=int, help='VIA matrix rows')
    parser.add_argument('-c', '--cols', type=int, help='VIA matrix columns')
    parser.add_argument('-m', '--macros', type=int,
                        help='VIA macro count (default: 16)', default=16)
    parser.add_argument('-C', '--canonical', action='store_true',
                        help='Canonical hex+ASCII display.')
    parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
    parser.add_argument('input', help='Raw contents of the STM32 flash area used to emulate eeprom')
    return parser.parse_args()


def decodeEepromFEEA(in_file, size):
    decoded=size*[None]
    pos = 0
    while True:
        chunk = in_file.read(CHUNK_SIZE)
        for i in range(0, len(chunk), 2):
            decoded[pos] = unpack('B', chunk[i])[0]
            pos += 1
            if pos >= size:
                break

        if len(chunk) < CHUNK_SIZE or pos >= size:
            break
    return decoded

def decodeEepromFEE9(in_file, size):
    decoded=size*[None]
    pos = 0
    # Read compacted flash 
    while True:
        read_size = min(size - pos, CHUNK_SIZE)
        chunk = in_file.read(read_size)
        for i in range(len(chunk)):
            decoded[pos] = unpack('B', chunk[i])[0] ^ 0xFF
            pos += 1
            if pos >= size:
                break

        if len(chunk) < read_size or pos >= size:
            break
    if VERBOSE:
        print("COMPACTED EEPROM:")
        dumpBinary(decoded, True)
        print("WRITE LOG:")
    # Read write log
    while True:
        entry = in_file.read(2)
        if len(entry) < 2:
            print("Partial log address at position 0x%04x" % pos, file=sys.stderr)
            break
        pos += 2

        if entry == EMPTY_WORD:
            break

        be_entry = unpack('>H', entry)[0]
        entry = unpack('H', entry)[0]
        if not (entry & WORD_ENCODING):
            address = entry >> 8
            decoded[address] = entry & 0xFF
            if VERBOSE:
                print("[0x%04x]: BYTE 0x%02x = 0x%02x" % (be_entry, address, decoded[address]))
        else:
            if (entry & VALUE_NEXT) == VALUE_NEXT:
                # Read next word as value
                value = in_file.read(2)
                if len(value) < 2:
                    print("Partial log value at position 0x%04x" % pos, file=sys.stderr)
                    break
                pos += 2
                address = entry & 0x1FFF
                address <<= 1
                address += BYTE_RANGE
                decoded[address]   = unpack('B', value[0])[0] ^ 0xFF
                decoded[address+1] = unpack('B', value[1])[0] ^ 0xFF
                be_value = unpack('>H', value)[0]
                if VERBOSE:
                    print("[0x%04x 0x%04x]: WORD 0x%04x = 0x%02x%02x" % (be_entry, be_value, address, decoded[address+1], decoded[address]))
            else:
                # Reserved for future use
                if entry & VALUE_RESERVED:
                    if VERBOSE:
                        print("[0x%04x]: RESERVED 0x%04x" % (be_entry, address))
                    continue
                address = entry & 0x1FFF
                address <<= 1
                decoded[address]   = (entry & VALUE_ENCODED) >> 13
                decoded[address+1] = 0
                if VERBOSE:
                    print("[0x%04x]: ENCODED 0x%04x = 0x%02x%02x" % (be_entry, address, decoded[address+1], decoded[address]))

    return decoded

def dumpBinary(data, canonical):
    def display(pos, row):
        print("%04x" % pos, end='')
        for i in range(len(row)):
            if i % 8 == 0:
                print(" ", end='')
            char = row[i]
            if char is None:
                print("   ", end='')
            else:
                print(" %02x" % row[i], end='')
        if canonical:
            print("  |", end='')
            for i in range(len(row)):
                char = row[i]
                if char is None:
                    char = " "
                else:
                    char = chr(char)
                if char not in PRINTABLE:
                    char = "."
                print(char, end='')
            print("|", end='')

        print("")

    size = len(data)
    prev_row = ''
    first_repeat = True
    for pos in range(0, size, 16):
        row=data[pos:pos+16]
        row[len(row):16] = (16-len(row))*[None]
        if row == prev_row:
            if first_repeat:
                print("*")
                first_repeat = False
        else:
            first_repeat = True
            display(pos, row)
        prev_row = row
    print("%04x" % (pos+16))

def dumpEeconfig(data, eeconfig):
    print("EECONFIG:")
    for (name, pos, length) in eeconfig:
        fmt = STRUCT_FMTS[length]
        value = unpack(fmt, ''.join([chr(x) for x in data[pos:pos+length]]))[0]
        print(("%%04x %%s = 0x%%0%dx" % (length * 2)) % (pos, name, value))

def dumpVia(data, base, layers, cols, rows, macros,
            layout_options_size, custom_config_size):
    magicYear  = data[base + 0]
    magicMonth = data[base + 1]
    magicDay   = data[base + 2]
    # Sanity check
    if not 10 <= magicYear <= 0x99 or \
       not 0 <= magicMonth <= 0x12 or \
       not 0 <= magicDay <= 0x31:
        print("ERROR: VIA Signature is not valid; Year:%x, Month:%x, Day:%x" % (magicYear, magicMonth, magicDay))
        return
    if cols is None or rows is None:
        print("ERROR: VIA dump requires specifying --rows and --cols", file=sys.stderr)
        return 2
    print("VIA:")
    # Decode magic
    print("%04x MAGIC = 20%02x-%02x-%02x" % (base, magicYear, magicMonth, magicDay))
    # Decode layout options
    options = 0
    pos = base + 3
    for i in range(base+3, base+3+layout_options_size):
        options = options << 8
        options |= data[i]
    print(("%%04x LAYOUT_OPTIONS = 0x%%0%dx" % (layout_options_size * 2)) % (pos, options))
    pos += layout_options_size + custom_config_size
    # Decode keycodes
    keymap_size = layers * rows * cols * 2
    if (pos + keymap_size) >= (len(data) - 1):
        print("ERROR: VIA keymap requires %d bytes, but only %d available" % (keymap_size, len(data) - pos))
        return 3
    for layer in range(layers):
        print("%s LAYER %d %s" % ('-'*int(cols*2.5), layer, '-'*int(cols*2.5)))
        for row in range(rows):
            print("%04x  | " % pos, end='')
            for col in range(cols):
                keycode = (data[pos] << 8) | (data[pos+1])
                print(" %04x" % keycode, end='')
                pos += 2
            print("")
    # Decode macros
    for macro_num in range(macros):
        macro = ""
        macro_pos = pos
        while pos < len(data):
            char = chr(data[pos])
            pos += 1
            if char == '\x00':
                print("%04x MACRO[%d] = '%s'" % (macro_pos, macro_num, macro))
                break
            else:
                macro += char
    return 0


def decodeSTM32Eeprom(input, canonical, size=None, output=None, **kwargs):
    input_size = os.path.getsize(input)
    if size is None:
        size = input_size >> 1

    # Read the first few bytes to check magic signature
    with open(input, 'rb') as in_file:
        magic=in_file.read(4)
        in_file.seek(0)

        if magic == MAGIC_FEEA:
            decoded = decodeEepromFEEA(in_file, size)
            eeconfig = EECONFIG_V1
            via_base = VIABASE_V1
        elif magic[:2] == MAGIC_FEE9:
            decoded = decodeEepromFEE9(in_file, size)
            eeconfig = EECONFIG_V1
            via_base = VIABASE_V1
        else:
            print("Unknown magic signature: %s" % " ".join(["0x%02x" % ord(x) for x in magic]), file=sys.stderr)
            return 1

    if output is not None:
        with open(output, 'wb') as out_file:
            out_file.write(pack('%dB' % len(decoded), *decoded))
    print("DECODED EEPROM:")
    dumpBinary(decoded, canonical)
    dumpEeconfig(decoded, eeconfig)
    if kwargs['rows'] is not None and kwargs['cols'] is not None:
        return dumpVia(decoded, via_base, **kwargs)

    return 0

def main():
    global VERBOSE
    kwargs = vars(parseArgs())
    VERBOSE = kwargs.pop('verbose')
    return decodeSTM32Eeprom(**kwargs)

if __name__ == '__main__':
    sys.exit(main())
