# RGB Underglow Strip on the Zeal60: A Guide

***WARNING:*** This guide is untested and likely has errors.

***NOTE:*** As explained in Part C, due to current limits, **underglow will only work on USB 3.0 or above**. If you want to use your keyboard on USB 2.0, make sure either underglow or backlighting is off when you plug in your Zeal60 - or that you have fiddled with the brightness of both to take the board's total consumption under 500mA.

## A. Connecting the strip
You might find the [**full PCB image**](https://cdn.shopify.com/s/files/1/0490/7329/files/zeal60jumpers.png) helpful. Ignore the red boxes!

1. Connect V+ and GND to 5V and GND from USB (J1A). 
    
    <img src="https://i.imgur.com/k1TUw7p.png" width="300">
    * ***Alternatively,*** if you don't want to further mess with the PCB, and you want to deal with the current limits purely in software as described in Part C, connect V+ and GND to the actual USB pinout V+ and GND. 
    
        <img src="http://i.imgur.com/3ShNaBt.png" width="300">
2. Connect DI to PB0 (or another unused pin on the 32U4).

    <img src="https://i.imgur.com/BiMyMLv.jpg" width="300">

## B. Enabling the strip
1. Add the following to your [```Makefile```](https://github.com/Wilba6582/qmk_firmware/blob/zeal60/keyboards/zeal60/Makefile):

    ```Makefile
    RGBLIGHT_ENABLE = yes
    AUDIO_ENABLE = no     #Underglow animations cannot be used with audio.
    ```
2. Add the following to your [```config.h```](https://github.com/Wilba6582/qmk_firmware/blob/zeal60/keyboards/zeal60/keymaps/default/config.h):

    ```c
    #define RGBLIGHT_ANIMATIONS    // Underglow animations.
    #define RGBW 0                 // 1 if you have an RGBW strip. 
    #define RGB_DI_PIN B0          // The pin your RGB strip is wired to
    #define RGBLED_NUM 16          // Number of LEDs
    #define RGBLIGHT_HUE_STEP 5    // How much each press of rgb_hue changes hue
    #define RGBLIGHT_SAT_STEP 10   // How much each press of rgb_sat changes sat
    #define RGBLIGHT_VAL_STEP 10   // How much each press of rgb_val changes val
    ```
3. Keycodes are ```RGB_TOG``` (on/off), ```RGB_MOD``` (step through modes), ```RGB_HUI```, ```RGB_HUD```, ```RGB_SAI```, ```RGB_SAD```, ```RGB_VAI```, ```RGB_VAD``` (HSV increase/decrease). Add these to your keymap. Test it out with **1 LED only** (```RGBLED_NUM 1``` in [```config.h```](https://github.com/Wilba6582/qmk_firmware/blob/zeal60/keyboards/zeal60/keymaps/default/config.h) above). 

## C. Dealing with current limits
USB 2.0 ports on laptops provide up to 500mA max, but USB 3.0 ports can provide up to 900mA; USB 3.1 up to 1.5A; and powered USB hubs even more. We can run our keyboard at a higher brightness if we draw more power.

An option to halve the Zeal60's current draw is to cut the trace on the pre-connected jumpers and bridge them with a 30kohm resistor. But let's try to limit brightness in software instead.

Here are some possible configurations with 16 RGB neopixels (6 on top and bottom of PCB; 2 on each side):

| Zeal60 (500mA maxed) | 16 RGB LEDs (60mA/LED maxed) | Total Current Consumption 
|:----------------------:|:--------------------------:|:----------------------:|
|       36% / 180mA      |         33% / 20mA         |     496mA (USB 2.0)     |
|      **100% / 500mA**      |         **41% / 25mA**         |     **900mA (USB 3.0)**     |
|       50% / 250mA      |         66% / 40mA         |     890mA (USB 3.0)     |
|      100% / 500mA      |         100% / 60mA        |     1460mA (USB 3.1)    

I'll take the second option.

1. Add the following to your keymap's [```config.h```](https://github.com/Wilba6582/qmk_firmware/blob/zeal60/keyboards/zeal60/keymaps/default/config.h). Change variable definitions based on your needs.

    ```c
    // Current limiting.
    #define USB_MAX_POWER_CONSUMPTION 900     // Limit device max power consumption.
    #define RGBSTRIP_CURRENT_LIMIT 400        // Strip current limit in mA.
    #define RGBSTRIP_MAX_CURRENT_PER_LIGHT 60 // mA per light when at max brightness.
    ```
3. **If you've connected +5V and GND to J1A**, either short or replace the thermistor labeled F1 under the USB port with one that supports your current needs. [Here's a selection](https://goo.gl/748avG) of 900mA-1.5A current hold fuses - look for an SMD 0805-sized fuse. **Otherwise, if you've connected directly to the USB +5V/GND pins**, you don't need to do anything other than limit brightness in software.
4. Enable all LEDs and test it out!

## D. Additional resources
### A. Connecting the strip.
* [In-depth description of connecting an RGB strip to the GH60](https://www.reddit.com/r/MechanicalKeyboards/comments/4d5or2/my_first_custom_build_satan_gh60_rbg_underglow_in/d1nz3o7/)
* [32U4 Pinout](https://40.media.tumblr.com/93b6bbd4113418c2b45459bb177e67c5/tumblr_mi49a20QMB1s5t695o1_1280.png)
* [Redditor describes connecting RGB strips on his Satan GH60](https://www.reddit.com/r/MechanicalKeyboards/comments/4hbjw4/finally_finished_my_satan_gh60_also_granite_o/d2qn8zx/?context=3)
* [Another Redditor on RGB with the Satan GH60](https://www.reddit.com/r/MechanicalKeyboards/comments/4ewzdx/gh60_satan_with_the_rgb_mod/d251uu6/ )

### B. Enabling the strip.
* [QMK Wiki portion on underglow](https://github.com/jackhumbert/qmk_firmware/wiki#rgb-under-glow-mod)
* [**Planck ```Makefile```, ```config.h```, and ```keymap.c``` config example**](https://github.com/jackhumbert/qmk_firmware/tree/master/keyboards/planck/keymaps/yang)
* [Video demonstrating keycode functions on a KC60](https://www.youtube.com/watch?v=VKrpPAHlisY)

### C. Dealing with current limits.
* [Discussion of cutting jumpers and adding resistors to lower current from Zeal60](https://www.reddit.com/r/MechanicalKeyboards/comments/5hou92/photos_zeal60_lets_just_say_santa_came_early_this/db23qid/)
* [A selection of 900mA-1.5A current hold fuses - look for an SMD 0805-sized fuse.](https://goo.gl/748avG)
* [Video detailing technique to solder 0805 resistors](https://www.youtube.com/watch?v=PU7wLcuqc-I&t=123s&list=FLheMlKEVQ5cmVXazUt6HrxQ&index=2)
* [QMK feature request to implement max power draw limits in ```config.h```](https://github.com/jackhumbert/qmk_firmware/issues/954)
* [Commit enabling max power draw limits in ```config.h```](https://github.com/jackhumbert/qmk_firmware/commit/83e613ad239459582ae28f78b6c81535b9b138d7)