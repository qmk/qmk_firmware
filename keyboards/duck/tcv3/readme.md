# Duck TC-V3

Non official firmware for custom Korean keyboard made by Duck.  
Group buy was run April 2018 via [geekhack](https://geekhack.org/index.php?topic=95335.0).  

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: Duck TC-V3 ver 1.0 PCB, Atmega32u4, 74HC237D 
* Hardware Availability: Wait until GB of the next revision

Make example for this keyboard (after setting up your build environment):

    make duck/tcv3:default

**Reset Key:** To put the TC-V3 into reset, hold the top second most right key (`K0J`) while plugging in. 

**CAUTION:** At this time 02/28/20 backlighting has not been tested fully and may not properly work. 

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Hardware Notes

The Duck TC-V3 PCB consists of:

### Microchips
* 2 74HC237D 3-to-8 line decoders
* 1 Atmega32u4 microcontroller
* 3 WS2811 LED controller
