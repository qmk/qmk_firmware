"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


http://www.nxp.com/documents/user_manual/UM10360.pdf

32.3.1.1 Criterion for Valid User Code
The reserved Cortex-M3 exception vector location 7 (offset 0x1C in the vector table)
should contain the 2's complement of the check-sum of table entries 0 through 6. This
causes the checksum of the first 8 table entries to be 0. The boot loader code checksums
the first 8 locations in sector 0 of the flash. If the result is 0, then execution control is
transferred to the user code.
"""
from struct import unpack, pack


def patch(bin_path):
    with open(bin_path, 'r+b') as bin:
        # Read entries 0 through 6 (Little Endian 32bits words)
        vector = [unpack('<I', bin.read(4))[0] for _ in range(7)]

        # location 7 (offset 0x1C in the vector table) should contain the 2's
        # complement of the check-sum of table entries 0 through 6
        bin.seek(0x1C)
        bin.write(pack('<I', (~sum(vector) + 1) & 0xFFFFFFFF))


def is_patched(bin_path):
    with open(bin_path, 'rb') as bin:
        # The checksum of the first 8 table entries should be 0
        return (sum([unpack('<I', bin.read(4))[0] for _ in range(8)]) & 0xFFFFFFFF) == 0


if __name__ == '__main__':
    bin_path = "C:/Users/emimon01/releases/emilmont/build/test/LPC1768/ARM/MBED_A1/basic.bin"
    patch(bin_path)
    assert is_patched(bin_path), "The file is not patched"
