# Raindrop

![stacked](https://i.imgur.com/R2iPqjIh.png)

60% sized keyboard with a gasket mounted plate and aluminium case. 

* Keyboard Maintainer: [Laneware Peripherals Support](mailto:support@lanewareperipherals.zendesk.com)
* Hardware Supported: Raindrop PCB
* Hardware Availability: Group Buy

## Layouts
The Raindrop PCB can be configured in the following key layouts:  
* **Standard 60%**  
![diagram_ansi](https://i.imgur.com/nSO4CwYh.png)
* **2u Left Shift with Arrow Keys**  
![diagram_arrows](https://i.imgur.com/7yPCNCoh.png)  
* **HHKB Rows 1-4**  
![diagram_hhkb](https://i.imgur.com/FPLmClah.png)
* **Standard ISO**  
![diagram_iso](https://i.imgur.com/8oyAuTWh.png)

Each layout has it's own QMK keyboard directory:  
| Key Layout | Directory |
| :---: | :---: |
| Standard 60% | [raindrop/ansi](/keyboards/laneware/raindrop/ansi) |
| 2u Left Shift with Arrow Keys | [raindrop/arrows](/keyboards/laneware/raindrop/arrows) |
| HHKB Rows 1-4 | [raindrop/hhkb](/keyboards/laneware/raindrop/hhkb) |

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
