#! /bin/python

import wave, struct, sys

waveFile = wave.open(sys.argv[1], 'r')

length = waveFile.getnframes()
out = "static const dacsample_t dac_buffer_custom[" + str(int(length / 256)) + "][256] = {"
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
