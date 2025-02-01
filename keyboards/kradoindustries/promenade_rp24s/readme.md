# Promenade RP24S 

![Promenade RP24S](https://i.imgur.com/uQOhmmJ.jpeg)

The Promenade RP24S is the solder version of the [Promenade](https://github.com/qmk/qmk_firmware/tree/master/keyboards/kradoindustries/promenade) pcb which is based on the [Boardwalk](https://github.com/qmk/qmk_firmware/tree/master/keyboards/boardwalk), a 60% ortholinear keyboard that uses 1.5u Ergodoxian modifier keys. The original Boardwalk's split hand and 65% layouts are supported, and a new 50% extended layout similar to [RGBKB's Pan](https://github.com/qmk/qmk_firmware/tree/master/keyboards/rgbkb/pan) with two right-side macro columns was also added. In addition to Pok3r-style 60% tray mounting points, the pcb also has edge cuts for use in gummy o-ring mount boards like the Bakeneko60. Some additional spacebar options including 3u, 6u, and triple 2u were added. The pcb has two footprint locations for a JST connector, many breakout pins, and 19 rotary encoder locations. The MCU has been upgraded to a RP2040 with 32M-bit of flash memory. 


* Keyboard Maintainer: [Feags](https://github.com/Feags) / [Krado Industries](https://kradoindustries.com/)
* Hardware Supported: Promenade pcb. Many 60% cases.  
* Hardware Availability: [Krado Industries](https://kradoindustries.com/)

Make example for this keyboard (after setting up your build environment):

    make kradoindustries/promenade_rp24s:default

Flashing example for this keyboard:

    make kradoindustries/promenade_rp24s:default:flash
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available