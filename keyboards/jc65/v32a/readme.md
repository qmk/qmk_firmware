JC65 ps2avrGB
=======

![JC65](https://i.imgur.com/9cJ9UbX.jpg)

A 65% keyboard with RGB

Keyboard Maintainer: [Jason Barnachea](https://github.com/nautxx)  

Hardware Supported: JC65 rev.ps2avrgb  

Hardware Availability: [keyclack.com](https://keyclack.com/)  

The JC65 PCB actually has two revisions: A QMK native version, and a PS2AVRGB version. Jchan offered both PCBs as options during the M65-A Round 1 group buy, and were also available choices for the 65% acrylic case group buy.

Please note that there have been issues with QMK and PS2AVRGB boards. Random shutdowns and overheating have been reported. As of now, the cause has not been discovered. 

These docs are for the PS2AVRGB version of the PCB. More info on qmk.fm

Make example for this keyboard (after setting up your build environment):

    make jc65/v32a:default
    
Flash example for this keyboard:

    bootloadHID -r jc65_v32a_default.hex

Flashing on Windows can be accomplished by downloading [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash)

To put the PS2AVRGB board into reset, hold down the left control key while plugging in the keyboard. 

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.