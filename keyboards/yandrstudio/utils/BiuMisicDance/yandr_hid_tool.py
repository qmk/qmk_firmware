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
import platform
import seaborn as sns
import time
import numpy as np
import colorsys
import sys

from audio_lib import *


vid = 0xFEED
pid = 0x6060
dev = hid.device()

for dev_info in hid.enumerate():
    if (dev_info['vendor_id'] == vid and dev_info['product_id'] == pid and dev_info['interface_number'] == 1):
        dev.open_path(dev_info['path'])
        break

# NOTE: Change the 64 here if your board uses 32-byte RAW_EPSIZE
RAW_EPSIZE = 32
def pad_message(payload):
    return payload + b'\x00' * (RAW_EPSIZE - len(payload))

def tobyte(data):
    if type(data) is bytes:
        return data
    else:
        return (data).to_bytes(1, 'big')

def tobytes(data):
    data = [0] + data
    if (len(data) > RAW_EPSIZE):
        raise IndexError
    out = b''
    for num in data:
        out += tobyte(num)
    return out

# protocol define
'''
[00] + [commond1, commond2, data1, data2, ..., data30]


todo:
pack per 10 LED into one report
'''

# pre-config
LED_KEY_NUM = 5
LED_INDEX = [i for i in range(LED_KEY_NUM)]
DECAY_WEIGHT = 0.8
MAX_POW = 150
MATRIX_ROWS = 5
MATRIX_COLS = 15

# step 1: set the kb rgb effect to be audio_visualization. 4ForCol 5ForRow
audio_mod = 4
dev.write(tobytes([60, audio_mod]))

if (audio_mod==4):
    is_col_visual = True
else:
    is_col_visual = False

try:
    # open stream
    stream, rgb_power_list, fft_samp_indexs = start_audio_dance(MATRIX_ROWS, MATRIX_COLS, is_col_visual)
    # some algorithm for audio visualization
    with stream:
        while True:
            if (audio_mod == 4):
                # rgb_power = (np.random.rand(MATRIX_COLS)*10).astype(np.int).tolist()
                rgb_power = get_power(MATRIX_COLS, rgb_power_list, fft_samp_indexs).tolist()
            else:
                # rgb_power = (np.random.rand(MATRIX_ROWS)*10).astype(np.int).tolist()
                rgb_power = get_power(MATRIX_ROWS, rgb_power_list, fft_samp_indexs).tolist()
            # print(rgb_power)
            dev.write(tobytes([60, 6]+rgb_power))
            time.sleep(0.01)

except KeyboardInterrupt:
    # recover pre mold
    dev.write(tobytes([60, audio_mod]))
    print("exit")
    sys.exit()
