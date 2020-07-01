# Duck Orion V3

Non official firmware for custom TKL Korean keyboard made by Duck.  
Group buy was run December 2018 via [geekhack](https://geekhack.org/index.php?topic=98581.0) with 100 keyboards total. 

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: Duck Orion V3 PCB Ver 2.1
* Hardware Availability: Wait until GB of the next revision

Make example for this keyboard (after setting up your build environment):

    make duck/orion/v3:default

**Reset Key:** To put the Orion V3 into reset, hold Backspace key (`K4N`) while plugging in. 

**CAUTION:** At this time 12/19/19 layer indicator lighting has not been implemented by default. 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware Notes

The Orion V3 PCB consists of:

### Microchips
2 74HC237D 3-to-8 line decoders U1, U2
1 Atmega32u4 microcontroller
2 WS2811 LED controller U5, U6

## Notes
Special thanks to Marcus aka Keebology for doing this remotely and mapping the matrix, indicator LEDs, and backlight LEDs. 
