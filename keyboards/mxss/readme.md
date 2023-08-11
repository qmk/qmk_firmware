# MxSS - Polycarb 65% Kit for MX/SMK

![MxSS - Polycarb 65% Kit for MX/SMK](https://i.imgur.com/WDTWcmU.jpg)

### Important Note:
**This PCB supports the VIA configurator, and this is the recommended way to configure the keymap on this keyboard. Building the firmware should only be necessary if you would like to change the colours of the front LEDs in indicator mode.**

**For more information about the VIA configurator, [see here](https://caniusevia.com/).**

### Information:

 - Case: Frosted Polycarbonate, CNC milled
 - Plate: Brass, mirror-finished and electroplated
 - Weight: Same as plate
 - PCB: Custom designed for the MxSS by kawasaki161, White solder mask and ENIG finish

### Details:

 - 2.9 degrees angle on the case
 - Top mount plate
 - Center USB, Type-B Mini
 - MX and SMK (White and Orange) switch support
 - Holtite support
 - RGB underglow
 - 1.5kg with plate and weight

Keyboard Maintainer: [MxBlue](https://github.com/mxblu)  

Hardware Supported: Custom PCB, ATMega32u4

Hardware Availability: https://geekhack.org/index.php?topic=94986.0

Make example for this keyboard (after setting up your build environment):

    make mxss:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

# Front LED Operation

The MxSS PCB has 2 front RGB LEDs which has a separate brightness and mode of operation to the rest of the RGB LEDs. These are controlled through the supplied custom keycodes.

There are 3 modes of operation:

 - FLED_OFF - Front LEDs stay off
 - FLED_RGB - Front LEDs are part of the standard RGB LED modes, only works correctly with rainbow modes (will fix on request)
 - FLED_INDI - Top front LED represents Caps Lock status, bottom LED represents current layer
 
Colors for FLED_INDI mode are hardcoded as hue/saturation values, the caps lock color can be found in mxss_frontled.h, the layer colors are defined in keymap.c (see default/keymap.c for example).

## Custom Keycodes

 - FLED_MOD - Cycle between the 3 modes (FLED_OFF -> FLED_RGB -> FLED_INDI)
 - FLED_VAI - Increase front LED brightness
 - FLED_VAD - Decrease front LED brightness
