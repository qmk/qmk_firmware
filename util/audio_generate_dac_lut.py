#!/usr/bin/env python3

DAC_BUFFER_SIZE=256
DAC_SAMPLE_MAX=4095

def plot(values):
    for v in values:
        print('0'* int(v * 80/DAC_SAMPLE_MAX))

def to_lut(values):
    for v in values:
        print(hex(int(v)), end=", ")


from math import sin, tau, pi

samples=[]

def sampleSine():
    for s in range(DAC_BUFFER_SIZE):
        samples.append((sin((s/DAC_BUFFER_SIZE)*tau - pi/2) + 1 )/2* DAC_SAMPLE_MAX)

def sampleTriangle():
    for s in range(DAC_BUFFER_SIZE):
        if s < DAC_BUFFER_SIZE/2:
            samples.append(s/(DAC_BUFFER_SIZE/2) * DAC_SAMPLE_MAX)
        else:
            samples.append(DAC_SAMPLE_MAX - (s-DAC_BUFFER_SIZE/2)/(DAC_BUFFER_SIZE/2) * DAC_SAMPLE_MAX)

#compromise between square and triangle wave,
def sampleTrapezoidal():
    for i in range(DAC_BUFFER_SIZE):
        a=3 #slope/inclination
        if (i < DAC_BUFFER_SIZE/2):
            s = a * (i * DAC_SAMPLE_MAX/(DAC_BUFFER_SIZE/2)) + (1-a)*DAC_SAMPLE_MAX/2
        else:
            i = i - DAC_BUFFER_SIZE/2
            s = DAC_SAMPLE_MAX - a * (i * DAC_SAMPLE_MAX/(DAC_BUFFER_SIZE/2)) - (1-a)*DAC_SAMPLE_MAX/2

        if s < 0:
            s=0
        if s> DAC_SAMPLE_MAX:
            s=DAC_SAMPLE_MAX
        samples.append(s)


#sampleSine()
sampleTrapezoidal()
#print(samples)
plot(samples)
to_lut(samples)
