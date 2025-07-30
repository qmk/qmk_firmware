# HLB PoorKoi

60% HLB PoorKoi's pcb is based on 4pplet/waffling60/rev_e (https://github.com/4pplet/waffling60).
* PCB features tsangan layout with ansi/iso layouts as well as split spacebar, split left/right shift, stepped capslock.
* PCB feature dedicated graphic art and flex cut were removed.

Regarding source code we added extra features with dedicated custom keycode **L_INDIC**: 

* LED indicator and capslock indicator are managed through lightning layers
* Layer indicator is shown even if rgb underglow is off
* Added a led indicator when custom keycode L_INDIC is on/off
  * Blink on top when off
  * Blink on bottom when on

Make example for this keyboard (after setting up your build environment):

    make hlb/poorkoi:vial

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

How to enter bootloader (DFU):
* Short the reset-header (labled BL/RESET) on the back of the PCB for about 2 seconds for the keyboard to enter DFU. When in DFU, it's ready to flash the firmware. If using a APM MCU it will not automatically reset after flash. Simply short the reset-header for a very short time to just reset the PCB, alternatively unplug and repluck the USB-cable to the keyboard.

Alternative option if the firmware is already pre-flashed:
* Unplug your keyboard, hold down the Spacebar and B at the same time, plug in your keyboard and wait a second before releasing the keys. The keyboard will enter DFU and is ready to flash the firmware.
