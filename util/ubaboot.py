#!/usr/bin/env python3

# Copyright 2017 by Robert Evans (rrevans@gmail.com)
#
# This file is part of ubaboot.
#
# ubaboot is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ubaboot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ubaboot.  If not, see <http://www.gnu.org/licenses/>.

import usb.core
import argparse
from collections import namedtuple
import time
# yapf: disable
# Default vendor/product id assigned by openmoko.
DEFAULT_DEV = '1d50:611c'

def parse_args():
    """Parses command line arguments.

    See --help for details.
    """
    vidpid = lambda s: [int(v, 16) for v in s.split(':', 1)]
    number = lambda s: int(s, 0)

    dev = vidpid(DEFAULT_DEV) if DEFAULT_DEV else None
    dev_required = dev is None
    dev_help = 'sets the USB device ID ({})'.format(
        "default {}".format(DEFAULT_DEV) if dev else "required")

    parser = argparse.ArgumentParser(description='ubaboot demo client')
    parser.add_argument('--dev', type=vidpid, default=dev, metavar='VID:PID',
                        required=dev_required, help=dev_help)
    parser.add_argument('--wait', action='store_const', const=True, default=False,
                        help='Wait until the device is set in programming mode')
    subparsers = parser.add_subparsers(title='loader commands',
                                       metavar='<command>')
    stat = subparsers.add_parser('stat', help='read signature/fuses')
    stat.set_defaults(mode='stat')

    read = subparsers.add_parser('read', help='read memory')
    read.set_defaults(mode='read')
    read.add_argument('start', type=number, help='start address')
    read.add_argument('count', type=number, help='length to read')
    read.add_argument('--type', choices=('eeprom', 'flash'), default='flash',
                      help='selects memory to read (default flash)')

    write = subparsers.add_parser('write', help='write memory')
    write.set_defaults(mode='write')
    write.add_argument('file', help='input file to write')
    write.add_argument('--no-reboot', action='store_false', dest='reboot',
                       help='do not reboot after programming')
    write.add_argument('--type', choices=('eeprom', 'flash'), default='flash',
                       help='selects memory to write (default flash)')

    verify = subparsers.add_parser('verify', help='verify memory')
    verify.set_defaults(mode='verify')
    verify.add_argument('file', help='input file to verify')
    verify.add_argument('--type', choices=('eeprom', 'flash'), default='flash',
                        help='selects memory to verify (default flash)')

    reboot = subparsers.add_parser('reboot', help='reboot device')
    reboot.set_defaults(mode='reboot', reboot=True)
    return parser.parse_args()

class IHexLine(namedtuple('IHexLine', 'addr type data')):
    """Stores one line of an Intel hex file."""

    @staticmethod
    def parse(s):
        """Parse one input line."""
        s = s.strip()
        if s[0] != ':':
            raise ValueError('missing start byte')
        if len(s) % 2 != 1:
            raise ValueError('expected even number of input chars')
        b = bytearray(int(s[i:i+2], 16) for i in range(1, len(s), 2))
        if len(b) != b[0] + 5:
            raise ValueError('invalid byte count')
        if sum(b) & 0xff:
            raise ValueError('invalid checksum byte')
        return IHexLine(addr=(b[1] << 8) + b[2], type=b[3], data=b[4:-1])

    def __str__(self):
        """Print the hex line in Intel format.

        This is suitable for output in a .hex file.
        The trailing newline is not included.
        """
        hdr = [len(self.data), self.addr >> 8, self.addr & 0xff, self.type]
        data = bytearray(hdr)
        data.extend(self.data)
        data.append(-sum(data) & 0xff)
        return ':' + ''.join('%02X' % v for v in data)

def read_ihex(f):
    """Parse input lines and return the parsed program bytes."""
    pgm = bytearray()
    for line in f:
        l = IHexLine.parse(line)
        if l.type == 0:
            end = l.addr + len(l.data)
            if end > len(pgm):
                pgm += bytearray(end - len(pgm))
            pgm[l.addr:end] = l.data
    return pgm

class UbabootDevice(object):
    """Sends requests to ubaboot USB device via pyusb."""

    # Requests
    GET_SIGNATURE = 1
    READ_FLASH = 2
    WRITE_FLASH = 3
    REBOOT = 4
    READ_EEPROM = 5
    WRITE_EEPROM = 6
    GET_LOCK = 7

    # Request types
    DEV_READ = 0xc0
    DEV_WRITE = 0x40

    def __init__(self, dev):
        self.__dev = dev

    def get_signature(self):
        return self.__dev_read(UbabootDevice.GET_SIGNATURE, 0, 0, 3)

    def get_lock(self):
        return self.__dev_read(UbabootDevice.GET_LOCK, 0, 0, 4)

    def read_flash(self, base, length):
        return self.__read_mem(UbabootDevice.READ_FLASH, base, length, 512)

    def read_eeprom(self, base, length):
        return self.__read_mem(UbabootDevice.READ_EEPROM, base, length, 16)

    def write_flash(self, base, pgm):
        return self.__write_mem(UbabootDevice.WRITE_FLASH, base, pgm, 512)

    def write_eeprom(self, base, pgm):
        return self.__write_mem(UbabootDevice.WRITE_EEPROM, base, pgm, 16)

    def reboot(self):
        return self.__dev_write(UbabootDevice.REBOOT, 0, 0, b'')

    def __dev_read(self, *args):
        return self.__dev.ctrl_transfer(UbabootDevice.DEV_READ, *args)

    def __dev_write(self, *args):
        return self.__dev.ctrl_transfer(UbabootDevice.DEV_WRITE, *args)

    def __read_mem(self, cmd, base, length, blksz):
        pgm = bytearray()
        for offset in range(0, length, blksz):
            addr = base + offset
            nb = min(blksz, length - offset)
            pgm.extend(self.__dev_read(cmd, addr, 0, nb))
        return pgm

    def __write_mem(self, cmd, base, pgm, blksz):
        for offset in range(0, len(pgm), blksz):
            block = pgm[offset:offset+blksz]
            padding = ((len(block) + blksz - 1) & ~(blksz-1)) - len(block)
            block += bytearray(b'\xff') * padding
            self.__dev_write(cmd, base+offset, 0, block)

def main():
    args = parse_args()

    vid, pid = args.dev
    dev = usb.core.find(idVendor=vid, idProduct=pid)
    if not dev:
        if (args.wait):
            while True:
                dev = usb.core.find(idVendor=vid, idProduct=pid)
                if dev:
                    break
                print("Cannot open ubaboot device. Retrying...")
                time.sleep(1)
        else:
            raise ValueError('cannot open ubaboot device')

    ubaboot = UbabootDevice(dev)

    if args.mode == 'stat':
        to_hex = lambda v: '%02X' % (v,)
        sig = ubaboot.get_signature()
        lofuse, lock, extfuse, hifuse = bytearray(ubaboot.get_lock())
        fuses = [lofuse, hifuse, extfuse]
        print('Signature:', ''.join(to_hex(v) for v in bytearray(sig)), \
            'Fuses: L:{0} H:{1} E:{2}'.format(*(to_hex(v) for v in fuses)), \
            'Lock: {0}'.format(to_hex(lock)))

    if args.mode in ('verify', 'write'):
        with open(args.file) as f:
            pgm = read_ihex(f)
        print('Loaded', len(pgm), 'bytes from', args.file)

    if args.mode in ('read', 'write', 'verify'):
        if args.type == 'flash':
            read, write = ubaboot.read_flash, ubaboot.write_flash
        elif args.type == 'eeprom':
            read, write = ubaboot.read_eeprom, ubaboot.write_eeprom

    if args.mode == 'read':
        start = args.start
        count = args.count
        mem = read(start, count)
        mem = mem.rstrip(bytearray(b'\xff'))
        for offset in range(0, len(mem), 16):
            print(IHexLine(addr=start+offset, type=0, data=mem[offset:offset+16]))
        print(IHexLine(addr=0, type=1, data=''))

    if args.mode == 'write':
        write(0, pgm)
        print('Wrote', len(pgm), 'bytes OK')

    if args.mode in ('verify', 'write'):
        actual = read(0, len(pgm))
        for pos in range(len(pgm)):
            if actual[pos] != pgm[pos]:
                raise ValueError('mismatch at offset 0x%x' % (pos,))
        print('Verified', len(pgm), 'bytes OK')

    if args.mode in ('write', 'reboot') and args.reboot:
        ubaboot.reboot()
        print('Rebooting')

if __name__ == '__main__':
    main()
