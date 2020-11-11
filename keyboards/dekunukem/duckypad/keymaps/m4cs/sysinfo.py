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
