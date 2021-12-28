#!/usr/bin/env python3
#
# Copyright 2020 JohSchneider
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
