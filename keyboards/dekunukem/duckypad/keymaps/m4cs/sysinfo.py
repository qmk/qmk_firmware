
###
# M4cs Keymap for dekuNukem/duckyPad QMK firmware

# Copyright (C) 2020 Max Bridgland

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
###


import hid
import time
import string
import psutil
import GPUtil
import datetime

h = hid.device()
h.open(0xFEED, 0x0B91)
h.set_nonblocking(1)
time.sleep(0.05)
while True:
    time.sleep(0.75)
    cpufreq = psutil.cpu_freq()
    currFreq = int(cpufreq.current)
    svmem = psutil.virtual_memory()
    memPerc = int(svmem.percent * 10)
    gpus = GPUtil.getGPUs()
    gpu = gpus[0]
    load = int(gpu.load*100)
    temp = int(gpu.temperature)
    data = [0]
    for x in str(currFreq):
        data.append(int(x))
    data.append(13)
    for x in str(memPerc):
        data.append(int(x))
    data.append(13)
    for x in str(load):
        data.append(int(x))
    data.append(13)
    for x in str(temp):
        data.append(int(x))
    data.append(13)
    now_hour = datetime.datetime.now().strftime("%I")
    now_min = datetime.datetime.now().strftime("%M")
    data.append(int(now_hour[0]))
    data.append(int(now_hour[1]))
    data.append(13)
    data.append(int(now_min[0]))
    data.append(int(now_min[1]))
    data.append(13)
    h.write(data)
