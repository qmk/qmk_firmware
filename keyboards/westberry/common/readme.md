## Description
On a limited hardware budget, you can use WB32's PWM Channels + some mos tubes to drive your rgb 

## Waveform
The following waveforms describe the waveforms of this driver as a single SW is selected, Both SW and RGB are active at low levels.  
<img src="https://svg.wavedrom.com/{ signal: [{ name: 'SW1', wave: 'hL....H|L....H.',period: 1 },{ name: 'PWM CH1', wave: 'hl..h..|l...h..',period: 1 },{ name: 'PWM CH2', wave: 'hl.h...|l..h...',period: 1 },{ name: 'PWM CH3', wave: 'hl...h.|l...h..',period: 1 }]}"/>

## To Use
To use this driver you need to add the following code to rule.mk:
```makefile
VPATH += keyboards/westberry/common
SRC += wb32_driver.c
```
