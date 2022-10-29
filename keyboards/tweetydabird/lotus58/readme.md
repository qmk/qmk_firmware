# Lotus 58 Glow

![lotus58](https://i.imgur.com/WWgpp0Sh.jpeg)

* Lotus 58 Glow is a fully programmable 58-key split, ortho-columnar keyboard with a 4x6 main matrix and 4+1 thumb-keys per hand. Optional support for one OLED screen per hand/side showing information such as active layer, CapsLock/NumLock etc. as well as one Rotary Encoder per hand, with optional placement.*

* Keyboard Maintainer: [TweetyDaBird](https://github.com/TweetyDaBird)
* Hardware Supported: *Lotus 58 Glow v1.11 - 1.24 PCB, Pro Micro or pin-compatible*
* Hardware Availability: [Lectronz Store](https://lectronz.com/stores/tweetys-wild-thinking)
* Hardware Design: [link](https://github.com/TweetyDaBird/Lotus58)


#### This keyboard firmware contains three different versions, all for the same PCB/hardware, but depending on your choice of RGB configuration. 

* RGB Full - Uses the 58 RGB LEDs under the keys, and is configured with RGB and a few effects. 
* RGB Glow - Uses the 12 RGB LEDs underneath the PCB to create a nice glow effect between the plates. 
* RGB None - Not configured with RGB.  


Make example for this keyboard (after setting up your build environment):

    make tweetydabird/lotus58/rgb_full:default

Flashing example for this keyboard:

    make tweetydabird/lotus58/rgb_none:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top outer key for each hand and plug in the keyboard
* **Physical reset**: Briefly short the marked pads on PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if mapped (not in default keymap)
