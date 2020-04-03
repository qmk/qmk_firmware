#!/usr/bin/env python3

AUDIO_DAC_BUFFER_SIZE=256
AUDIO_DAC_SAMPLE_MAX=4095

def plot(values):
    for v in values:
        print('0'* int(v * 80/AUDIO_DAC_SAMPLE_MAX))

def to_lut(values):
    for v in values:
        print(hex(int(v)), end=", ")


from math import sin, tau, pi

samples=[]

def sampleSine():
    for s in range(AUDIO_DAC_BUFFER_SIZE):
        samples.append((sin((s/AUDIO_DAC_BUFFER_SIZE)*tau - pi/2) + 1 )/2* AUDIO_DAC_SAMPLE_MAX)

def sampleTriangle():
    for s in range(AUDIO_DAC_BUFFER_SIZE):
        if s < AUDIO_DAC_BUFFER_SIZE/2:
            samples.append(s/(AUDIO_DAC_BUFFER_SIZE/2) * AUDIO_DAC_SAMPLE_MAX)
        else:
            samples.append(AUDIO_DAC_SAMPLE_MAX - (s-AUDIO_DAC_BUFFER_SIZE/2)/(AUDIO_DAC_BUFFER_SIZE/2) * AUDIO_DAC_SAMPLE_MAX)

#compromise between square and triangle wave,
def sampleTrapezoidal():
    for i in range(AUDIO_DAC_BUFFER_SIZE):
        a=3 #slope/inclination
        if (i < AUDIO_DAC_BUFFER_SIZE/2):
            s = a * (i * AUDIO_DAC_SAMPLE_MAX/(AUDIO_DAC_BUFFER_SIZE/2)) + (1-a)*AUDIO_DAC_SAMPLE_MAX/2
        else:
            i = i - AUDIO_DAC_BUFFER_SIZE/2
            s = AUDIO_DAC_SAMPLE_MAX - a * (i * AUDIO_DAC_SAMPLE_MAX/(AUDIO_DAC_BUFFER_SIZE/2)) - (1-a)*AUDIO_DAC_SAMPLE_MAX/2

        if s < 0:
            s=0
        if s> AUDIO_DAC_SAMPLE_MAX:
            s=AUDIO_DAC_SAMPLE_MAX
        samples.append(s)


#sampleSine()
sampleTrapezoidal()
#print(samples)
plot(samples)
to_lut(samples)
