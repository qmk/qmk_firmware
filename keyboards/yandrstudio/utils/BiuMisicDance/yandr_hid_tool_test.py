"""
/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
"""
import hid
vid = 0xFEED
pid = 0x6060
h = hid.device()
h.open(vid,pid)
print(f'Device manufacturer: {h.get_manufacturer_string()}')
print(f'Product: {h.get_product_string()}')
h.set_nonblocking(1)
h.write(bytes([3,5]))

# NOTE: Change the 64 here if your board uses 32-byte RAW_EPSIZE
def pad_message(payload):
    return payload + b'\x00' * (32 - len(payload))

def tobyte(data):
    if type(data) is bytes:
        return data
    else:
        return (data).to_bytes(1, 'big')

def tobytes(data):
    out = b''
    for num in data:
        out += tobyte(num)
    return out


# print(f'Serial Number: {h.serial}')
#     # 0x03,!0x02......
#     #h.send_feature_report(b'\0x03\0x44')
