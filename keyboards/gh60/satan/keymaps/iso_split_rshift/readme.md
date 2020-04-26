toneman77's Satan Layout
=====================

##Quantum MK Firmware
For the full Quantum feature list, see the parent readme.md.

* heavily modified ISO (!) layout with split right shift key
* spaceFn
* Dual-Role keys:
* 
 | Original key     | when tapped   | when held     |
 | ---------------- | ------------- | ------------- |
 | Space            | Space         | layer change  |
 | Caps lock        | Escape        | Control       |
 | Tab              | Tab           | layer change  |
 | Enter            | Enter         | Control       |

* Lockable layer for LED functions and numpad
* vim-style arrow keys on hjkl (spacefn layer)
* corresponding Home/PgDn/PgUp/End on hjkl (tab layer)
* bonus arrow keys in the bottom right corner on Alt/Win/Menu/rCtrl/Shift
* more bonus arrow keys on wasd (spacefn layer)
* media keys prev/next/play/vol+/vol- (spacefn layer)
* firmware bootloader button
* WS2812 RGB Underglow Support (not needed anymore to solder directly to the atmega)
* additional brackets that only work in german layout due to horrible placement
in the default qwertz layout


### Additional Credits
* Keymap has been based on TerryMathews' fork of Aqoush's fork of qmk-satan-rgb. [here](https://github.com/TerryMathews/qmk-satan-rgb/tree/master/keyboard/satan)
* nice visualization of the layers [here](http://www.keyboard-layout-editor.com/#/gists/aba4e4396459ede85bc66a22cee88e48)
* no-need-to-solder-on-chip picture:
![no need to solder directly on the chip anymore](https://i.imgur.com/AitpDoB.jpg)
* special thanks to /u/TerryMathews  who suggested the pin PB2, so soldering
directly on the atmega is not needed anymore. Happened on [reddit](https://www.reddit.com/r/MechanicalKeyboards/comments/4ghq9z/photos_satan_rgb60_w1976/d2k5tra)
