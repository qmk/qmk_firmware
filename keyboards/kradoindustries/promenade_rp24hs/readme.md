# Promenade RP24HS 

![Promenade RP24HS](https://i.imgur.com/uQOhmmJ.jpeg)

The Promenade RP24HS is the newer version of the [Promenade](https://github.com/qmk/qmk_firmware/tree/master/keyboards/kradoindustries/promenade) which is based on the [Boardwalk](https://github.com/qmk/qmk_firmware/tree/master/keyboards/boardwalk), a 60% ortholinear keyboard that uses 1.5u Ergodoxian modifier keys. In addition to Pok3r-style 60% tray mounting points, the pcb also has edge cuts for use in gummy o-ring mount boards like the Bakeneko60. Some additional spacebar options including 3u and 6u were added. The pcb has two footprint locations for a JST connector, many breakout pins, and several rotary encoder locations. The MCU has been upgraded to a RP2040 with 32M-bit of flash memory. 

The 1.5u vertical inner mods are the default configuration, but the board can be configured to use 3x2 1u keys either by removing the existing hotswap sockets and soldering 6 hotswap sockets to the 1u pads. *Note that the some of the 1u keys may require the plastic legs of 5-pin switches to be trimmed.*


* Keyboard Maintainer: [Feags](https://github.com/Feags) / [Krado Industries](https://kradoindustries.com/)
* Hardware Supported: Promenade pcb. Many 60% cases.  
* Hardware Availability: [Krado Industries](https://kradoindustries.com/)

Make example for this keyboard (after setting up your build environment):

    make kradoindustries/promenade_rp24hs:default

Flashing example for this keyboard:

    make kradoindustries/promenade_rp24hs:default:flash
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
