# Launch Pad
The guidance computer inside the [Launch Pad](https://ungodly.design/products/launch-pad) by Ungodly Design.

**Features:**
* Onboard atmega32u4 controller, 5V @ 16MHz
* Kaihl hotswap sockets
* USB-C connector
* 18 in-switch RGB LEDs
* 4 underglow RGB LEDs
* 100 Ω potentiometer slider
* (optional) M2 pcb mounting holes
* (optional) pcb-mount stablizer footprints
* (optional) pin breakout:
  * F5, F4, F1, F0, VBUS, GND

PCB Front             |  PCB Back
:-------------------------:|:-------------------------:
![Numpad](https://i.imgur.com/f47ZFZZl.png)  |  ![5x4](https://i.imgur.com/wZH76Ppl.png)

Numpad Layout             |  5x4 Layout
:-------------------------:|:-------------------------:
![Numpad](https://i.imgur.com/4XvqCBHl.jpg)  |  ![5x4](https://i.imgur.com/mwtGnPSl.jpg)


|Reset Bootloader|   |
|---|---|
|Use tweezers to short the two bottom pins of the J-Link pinout.|![Numpad](https://i.imgur.com/ArSIcK0.pngl)|

* Keyboard Maintainer: [Luis Godinez](https://github.com/luis-Godinez)
* Hardware Supported: Launch Pad PCB
* Hardware Availability: [Ungodly.Design](https://ungodly.design/products/launch-pad-pcb)

Make example for this keyboard (after setting up your build environment):

    make ungodly/launch_pad:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
