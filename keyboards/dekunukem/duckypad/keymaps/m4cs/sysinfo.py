import psutil
import GPUtil
import time

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
    data.append(10)
    for x in str(memPerc):
        data.append(int(x))
    data.append(10)
    for x in str(load):
        data.append(int(x))
    data.append(10)
    for x in str(temp):
        data.append(int(x))
    data.append(10)
    h.write(data)
