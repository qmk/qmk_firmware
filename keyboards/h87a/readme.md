h87a
===

A QMK-powered replacement PCB for custom TKL keyboards. This PCB has the same size of the b.87 PCB, while using the USB port placement and spacebar stabilizer orientation as the a.87 PCB.

Keyboard Maintainer: hineybush (Josh Hinnebusch)  

Hardware Supported: h87a Rev 1  

Hardware Availability: Currently prototyped, group buy TBD  

Make example for this keyboard (after setting up your build environment):
     
     make h87a:default
   
## h87a hardware information

Controller: Atmega32u4

    /* Column pin configuration
    * col: 0   1   2   3   4   5   6   7   8   
    * pin: F0  F1  F4  F5  F6  F7  C7  C6  D2
    */
     
    /* Row pin configuration
    * row: 0   1   2   3   4   5   6   7   8   9   10  11
    * pin: B0  B1  B2  B3  D0  D1  B5  B6  D7  B4  D6  D4  (Rev 1)
    */
    
The H87a PCB utilizes duplex matrix organization.

    Caps Lock LED: D5
    Scroll Lock LED: E6
    Num Lock LED: not supported
    Backlight Pin: B7
    RGB Data Pin: D3
    
To connect the Caps Lock LED to the main backlight matrix, jump the middle pad and the left pad on J1. To use the Caps Lock LED as an indicator, jump the middle pad and the right pad on J1.

To connect the Scroll Lock LED to the main backlight matrix, jump the middle pad and the right pad on J2. To use the Scroll Lock LED as an indicator, jump the middle pad and the left pad on J2.

Note: The different orientations of J1 and J2 will be fixed with Rev 2.
