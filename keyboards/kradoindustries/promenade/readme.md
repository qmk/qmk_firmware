# Promenade

![Promenade](https://i.imgur.com/VXlXflth.jpg)

The Promenade is a 60% ortholinear hotswap keyboard based on the split hand layout of the [Boardwalk](https://github.com/qmk/qmk_firmware/tree/master/keyboards/boardwalk). While similar to the Professional 2 hotswap version of the Boardwalk, it uses 1.5u verticle inner mods instead of 1u keys, includes a JST connector, adds stabilizer mounting positions for 6u and split 3u spacebards, and in addition to 60% tray mounting points the pcb has edge cuts for for use in gummy o-ring mount boards like the Bakeneko60. 

The 1.5u vertical inner mods are the default configuration, but the board can be configured to use 3x2 1u keys either by removing the existing hotswap sockets and soldering 6 hotswap sockets to the 1u pads. *Note that the some of the 1u keys may require the plastic legs of 5-pin switches to be trimmed.*

* Keyboard Maintainer: [Feags](https://github.com/Feags) / [Krado Industries](https://kradoindustries.com/)
* Hardware Supported: Promenade pcb. Many 60% cases.  
* Hardware Availability: [Krado Industries](https://kradoindustries.com/)

Make example for this keyboard (after setting up your build environment):

    make kradoindustries/promenade:default

Flashing example for this keyboard:

    make kradoindustries/promenade:default:flash
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available