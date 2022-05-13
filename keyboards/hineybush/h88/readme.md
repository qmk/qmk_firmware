h88
===

A QMK-powered replacement PCB for custom TKL keyboards that feature an extra key in the Fn row. This PCB is designed with the TGR Jane V2 CE in mind, however other keyboards with the same layout and a.87 USB positioning may work.

Keyboard Maintainer: [hineybush](https://github.com/hineybush)  
Hardware Supported: h88 ver 1.0  
Hardware Availability: hineybush.com

Make example for this keyboard (after setting up your build environment):
     
     make hineybush/h88:default
   
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## h88 hardware information

Controller: Atmega32u4

    /* Column pin configuration
    * col: 0   1   2   3   4   5   6   7   8   
    * pin: F0  F1  F4  F5  F6  F7  C7  C6  D2
    */
     
    /* Row pin configuration
    * row: 0   1   2   3   4   5   6   7   8   9   10  11
    * pin: B0  B1  B2  B3  D0  D1  B5  B6  D7  B4  D6  D4  (Rev 1)
    */
    
The H88 PCB utilizes duplex matrix organization.

    Caps Lock LED: D5
    Scroll Lock LED: E6
    Num Lock LED: not supported
    Backlight Pin: B7
    RGB Data Pin: D3
    


For in-switch indicator LEDs, bridge the center pad of the J1 and J2 3-pad jumpers follwing the small silk screen line.
