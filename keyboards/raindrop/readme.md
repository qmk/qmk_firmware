# Raindrop

![stacked](https://i.imgur.com/R2iPqjIh.png)  
*Casing*  
![PCB Front](https://i.imgur.com/00TpL3nh.png)  
*PCB Front*  

60% sized keyboard with a gasket mounted plate and aluminium case, made by Laneware Peripherals.

* Keyboard Maintainer: [Laneware Peripherals](https://github.com/laneware)
* Hardware Supported: Raindrop PCB
* Hardware Availability: Group Buy

## Layouts
The Raindrop PCB can be configured in the following key layouts: 
| Key Layout | Keymap | Diagram |
| :---: | :---: | :---: |
| Standard 60% | default | ![diagram_ansi](https://i.imgur.com/oibG44o.png) |
| 2u Left Shift with Arrow Keys | arrows | ![diagram_arrows](https://i.imgur.com/cQ4Kwb5h.png) |
| HHKB with 6.25 Spacebar | hhkb | ![diagram_hhkb](https://i.imgur.com/WU6gb1Qh.png) |

Make example for this keyboard (after setting up your build environment):

    make raindrop:default

Flashing example for this keyboard:

    make raindrop:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
