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
# print(str(waveFile.getparams()))
# sys.exit()

if (waveFile.getsampwidth() != 2):
    raise(Exception("This script currently only works with 16bit audio files"))

length = waveFile.getnframes()
out = "#define DAC_SAMPLE_CUSTOM_LENGTH " + str(length) + "\n\n"
out += "static const dacsample_t dac_sample_custom[" + str(length) + "] = {"
for i in range(0,length):
    if (i % 8 == 0):
        out += "\n    "
    waveData = waveFile.readframes(1)
    data = struct.unpack("<h", waveData)
    out += str(int((int(data[0]) + 0x8000) / 16)) + ", "
out = out[:-2]
out += "\n};"
print(out)
