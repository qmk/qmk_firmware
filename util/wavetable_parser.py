#!/usr/bin/env python3
#
# Copyright 2019 Jack Humbert
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

import wave, struct, sys

waveFile = wave.open(sys.argv[1], 'r')

length = waveFile.getnframes()
out = "#define DAC_WAVETABLE_CUSTOM_LENGTH " + str(int(length / 256)) + "\n\n"
out += "static const dacsample_t dac_wavetable_custom[" + str(int(length / 256)) + "][256] = {"
for i in range(0,length):
    if (i % 8 == 0):
        out += "\n    "
    if (i % 256 == 0):
        out = out[:-2]
        out += "{\n    "
    waveData = waveFile.readframes(1)
    data = struct.unpack("<h", waveData)
    out += str(int((int(data[0]) + 0x8000) / 16)) + ", "
    if (i % 256 == 255):
        out = out[:-2]
        out += "\n  },"
out = out[:-1]
out += "\n};"
print(out)
