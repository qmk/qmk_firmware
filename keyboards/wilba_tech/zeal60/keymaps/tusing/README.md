# RGB Underglow Strip on the Zeal60: A Guide

<img src="https://i.imgur.com/UuUdOCb.jpg" width="800">

## Requirements

- WS2812B RGB strip, preferably 60 LEDs/meter
- Wire, solder
- Tape, hot glue, or some sort of adhesive

## A. Connecting the strip
You might find the [**full PCB image**](https://cdn.shopify.com/s/files/1/0490/7329/files/zeal60jumpers.png) helpful. Ignore the red boxes!

1. Connect V+ to the receiving end of the thermistor labeled F1; connect GND to the board's GND pin. (*Avoid connecting +V to the board's +5V pin* - you will likely overload the thermistor, and you will limit your maximum brightness.)

    <img src="https://i.imgur.com/jd7qivh.png" width="300">

2. Connect DI to PB0.

    <img src="https://i.imgur.com/BiMyMLv.jpg" width="300">

3. Should look something like this when finished:

    <img src="https://i.imgur.com/ngxYMuA.jpg" width="600">

*Optional:* To allow considerably more light to escape, consider angling the strip outwards by using some sort of fulcrum under the strip. (I used a thick wire.)

## B. Enabling the strip
1. If it is not present already, add the following to your ***keymap's*** ```Makefile```:

    ```Makefile
    RGBLIGHT_ENABLE = yes
    AUDIO_ENABLE = no     #Underglow animations cannot be used with audio.
    ```
2. If it is not present already, add the following to your *keymap's* ```config.h```, and edit the values as necessary:

    ```c
    // Set up RGB underglow.
    #define RGB_DI_PIN B0          // The pin your RGB strip is wired to
    #define RGBLED_NUM 35          // Number of LEDs
    #define RGBLIGHT_HUE_STEP 5    // How much each press of rgb_hue changes hue
    #define RGBLIGHT_SAT_STEP 10   // How much each press of rgb_sat changes sat
    #define RGBLIGHT_VAL_STEP 10   // How much each press of rgb_val changes val
    ```
3. If they are not present already, add the following keycodes to your keymap to control the RGB strip: ```RGB_TOG``` (on/off), ```RGB_MOD``` (step through modes), ```RGB_HUI```, ```RGB_HUD```, ```RGB_SAI```, ```RGB_SAD```, ```RGB_VAI```, ```RGB_VAD``` (HSV increase/decrease). Add these to your keymap.

## C. Dealing with current limits
USB 2.0 ports on laptops provide up to 500mA max, but USB 3.0 ports can provide up to 900mA; USB 3.1 up to 1.5A; and powered USB hubs even more. We can run our keyboard at a higher brightness if we draw more power. **The Zeal60 uses 500mA at max brightness.** This means that **you have about 400mA remaining for the strip to use on a USB 3.0 port**; 1000mA free on a USB 3.1 port, so on and so forth.

***Warning:*** **This means you will need to turn *off* your RGB strip before connecting to a USB 2.0 port**, as USB 2.0 cannot sustain the current necessary!

1. If not present already, add the following to your keymap's ```config.h```. Change the numbers based on your needs. The ones below are safe underestimates.

    ```c
    // Enable current limiting for RGB underglow.
    #define RGBSTRIP_CURRENT_LIMIT 400    // Strip current limit in mA. (USB amperage - 500mA for keyboard)
    #define RGBSTRIP_MAX_CURRENT_PER_LIGHT 50 // mA per light when at max brightness.
    ```
    *Example:* I use a USB port capable of providing 1800 mA. The keyboard uses 500mA, so my personal value (in the `tusing` keymap) for `RGBSTRIP_CURRENT_LIMIT` is 1300. The particular WS2812B RGB strip I have uses a maximum of 60 mA per LED, so that is my personal value for `RGBSTRIP_MAX_CURRENT_PER_LIGHT`.
2. Toggle on the LED strip (```RGB_TOG```) and step through animations (```RGB_MOD```) to test it out!

## D. Sources and resources
### A. Connecting the strip.
* [In-depth description of connecting an RGB strip to the GH60](https://www.reddit.com/r/MechanicalKeyboards/comments/4d5or2/my_first_custom_build_satan_gh60_rbg_underglow_in/d1nz3o7/)
* [32U4 Pinout](https://40.media.tumblr.com/93b6bbd4113418c2b45459bb177e67c5/tumblr_mi49a20QMB1s5t695o1_1280.png)
* [Redditor describes connecting RGB strips on his Satan GH60](https://www.reddit.com/r/MechanicalKeyboards/comments/4hbjw4/finally_finished_my_satan_gh60_also_granite_o/d2qn8zx/?context=3)
* [Another Redditor on RGB with the Satan GH60](https://www.reddit.com/r/MechanicalKeyboards/comments/4ewzdx/gh60_satan_with_the_rgb_mod/d251uu6/ )

### B. Enabling the strip.
* [QMK Wiki portion on underglow](https://github.com/jackhumbert/qmk_firmware/wiki#rgb-under-glow-mod)
* [Planck ```Makefile```, ```config.h```, and ```keymap.c``` config example](https://github.com/jackhumbert/qmk_firmware/tree/master/keyboards/planck/keymaps/yang)
* [Video demonstrating keycode functions and RGB modes on a KC60](https://www.youtube.com/watch?v=VKrpPAHlisY)

### C. Dealing with current limits.
* [Discussion of cutting jumpers and adding resistors to lower current from Zeal60](https://www.reddit.com/r/MechanicalKeyboards/comments/5hou92/photos_zeal60_lets_just_say_santa_came_early_this/db23qid/)
* [A selection of 900mA-1.5A current hold fuses - look for an SMD 0805-sized fuse.](https://goo.gl/748avG)
* [Video detailing technique to solder 0805 resistors](https://www.youtube.com/watch?v=PU7wLcuqc-I&t=123s&list=FLheMlKEVQ5cmVXazUt6HrxQ&index=2)
* [QMK feature request to implement max power draw limits in ```config.h```](https://github.com/jackhumbert/qmk_firmware/issues/954)
* [Commit enabling max power draw limits in ```config.h```](https://github.com/jackhumbert/qmk_firmware/commit/83e613ad239459582ae28f78b6c81535b9b138d7)
