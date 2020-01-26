# Duck Eagle/Viper V2

Non official firmware for custom Korean keyboard with 60% key layout made by Duck.  
Group buy was run November 2016 via [geekhack](https://geekhack.org/index.php?topic=86087.0) with 100 keyboards total. 

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)  
Hardware Supported: Duck Eagle/Viper PCB Ver 2.0, Atmega32u4  
Hardware Availability: Wait until GB of the next revision

Make example for this keyboard (after setting up your build environment):

    make eagle_viper/v2:default

**Reset Key:** To put the Eagle/Viper V2 into reset, hold caps lock key (`K2A`) while plugging in. 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware Notes

The Duck Eagle/Viper V2 PCB consists of:

### Microchips
2 74HC237D 3-to-8 line decoders
1 Atmega32u4 microcontroller
2 WS2811 LED controller

## Notes
Thanks to Ralf Schmitt for previous implementations in his [TMK fork](https://github.com/xauser/tmk_keyboard/tree/xauser/) and few helping words.

Based heavily on Rasmus Schults [Duck Lightsaver QMK Port](https://github.com/qmk/qmk_firmware/tree/master/keyboards/lightsaver)

Special thanks to profanum429 for debugging help and contributions to support the Viper and LED indicators. 
