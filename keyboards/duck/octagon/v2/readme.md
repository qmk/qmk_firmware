# Duck Octagon V2

Non official firmware for custom Korean keyboard with 75% key layout made by Duck.  
Group buy was run January 2016 via [geekhack](https://geekhack.org/index.php?topic=78549.0) with 2 rounds, 100 keyboards total. 

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)  
Hardware Supported: Duck Octagon PCB Ver 2.0, Atmega32u4  
Hardware Availability: Wait until GB of the next revision

Make example for this keyboard (after setting up your build environment):

    make octagon/v2:default

**Reset Key:** To put the Octagon V2 into reset, hold the top right most key (`K5Q`) while plugging in. 

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Hardware Notes

The Duck Octagon V2 PCB consists of:

### Microchips
2 74HC237D 3-to-8 line decoders
1 Atmega32u4 microcontroller
2 WS2811 LED controller

## Notes
Thanks to Ralf Schmitt for previous implementations in his [TMK fork](https://github.com/xauser/tmk_keyboard/tree/xauser/) and few helping words.

Based heavily on Rasmus Schults [Duck Lightsaver QMK Port](https://github.com/qmk/qmk_firmware/tree/master/keyboards/lightsaver)
