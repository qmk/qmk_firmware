# Kousa TKL 

![Photo](https://i.imgur.com/b2JJoiIh.jpg)

A hotswap H88-Compact Type-C compatible ortholinear TKL PCB that uses ergodox modifiers. Based on the [Boardwalk](https://github.com/qmk/qmk_firmware/tree/master/keyboards/boardwalk)'s split hand layout, with the addtion of 6u and split 3u spacebar stabilizer support.  F13 and F12 layouts are supported. The F13 location also supports a rotary encoder. The default layout will have 1.5u vertical inner modifiers, but it is possible to convert the center keys to 1u by soldering hotswap sockets. The board is designed to be compatible with H88-C type C boards and the outline of the board was based on zykrah's [slime88 pcb](https://github.com/zykrah/slime88). The usb C port can be broken off and used with a JST connector and daughterboard. 

The name is meant to be read "Kousa Tenkeyless". "Kousaten" (交差点) means intersection or crossing in Japanese. I wanted the name to be a nod to the Boardwalk without using u/shensmobile's naming conventions and Crosswalk seemed pretty close, but then I realized "crossing" in Japanese is "kousaten" and I thought it would call it the Kousa Tenkeyless! 

* Keyboard Maintainer: [Feags](https://github.com/Feags) / [Krado Industries](https://kradoindustries.com/)
* Hardware Supported: H88-C type C cases. Confirmed working in KFA Freebird TKL. Also confirmed working in KBDFans Tiger80 Lite. *Please note that you will need a custom plate for any case.*
* Hardware Availabilitiy: [Krado Industries](https://kradoindustries.com/)

Make example for this keyboard (after setting up your build environment):

    make kradoindustries/kousa:default

Flashing example for this keyboard:

    make kradoindustries/kousa:default:flash




See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available