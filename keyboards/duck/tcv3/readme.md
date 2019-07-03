# Duck TC-V3

Non official firmware for custom Korean keyboard made by Duck.  
Group buy was run April 2018 via [geekhack](https://geekhack.org/index.php?topic=95335.0).  

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)<br> 
Hardware Supported: Duck TC-V3 ver 1.0 PCB, Atmega32u4, 74HC237D<br> 
Hardware Availability: Wait until GB of the next revision<br>

Make example for this keyboard (after setting up your build environment):

    make tcv3:default

**Reset Key:** To put the TC-V3 into reset, hold the top second most right key while plugging in. 

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Hardware Notes

The Duck TC-V3 PCB consists of:

### Microchips
2 74HC237D 3-to-8 line decoders<br>
1 Atmega32u4 microcontroller<br>
3 WS2811 LED controller<br>
