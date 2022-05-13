# Alpha 28-Key Keyboard Alternate Keymap
Alternate keymap for [Alpha 28-key keyboard](https://github.com/qmk/qmk_firmware/tree/master/keyboards/alpha).

## How-to
Assuming you've followed all the instructions from the original post, put my "keymap.c" file in "$qmk-firmware-folder$/keyboards/alpha/keymaps/vderm/" and then run your make command ("make alpha:vderm" while in $qmk-firmware-folder$ where this folder is what you've downloaded from the official github page) to compile the hex file to upload to your microcontroller. I've also uploaded my hex file.

## Description
Instead of going up and down layers like in the original Alpha keyboard, I've made the bottom row keys all have alternate functions:
+ Like in the original Alpha28 keymap, the 2U spacebar is a shift key when held down and space when tapped
+ Z and M are Ctrl keys when held down or Z and M when tapped
+ X and N are Alt keys
+ C activates the function keys layer (arrows, page up/dn, esc, tab, etc.)
+ V activates the characters and numbers layer
+ C and V combined activated the F-keys layer (F1, F2, F3, etc.)
+ The enter key is an enter key in the home layer, backspace in the function keys and characters/numbers layer and a delete in the F-keys layer
+ While in the other layers, the bottom row acts like a "regular" bottom modified row: ctrl, alt, winkey

## Keymap
![keymap](https://imgur.com/ZbDz0eL.jpg)

## Build Images
Here is my keyboard.
+ Switches: Aliaz Silent Switches (Tactile), PCB mount, 80g from [KBDfans](https://kbdfans.cn/collections/aliaz-switches/products/pre-orderaliaz-silent-switch-tactile?variant=2519899832333)
+ PCB board: ordered from JLCPCB, in white
+ Keycaps: ebay, can't find link :S
+ Bottom plate: I cut a piece of canary wood that was laying around, needs to be varnished; I also need to actually screw the pcb to the wood instead of relying on double-sided tape

![vderm_alpha0](https://imgur.com/MjjoVtr.jpg)
![vderm_alpha1](https://imgur.com/mIFu9WV.jpg)
![vderm_alpha2](https://imgur.com/A70Iemw.jpg)
![vderm_alpha3](https://imgur.com/eYljPWh.jpg)
![vderm_alpha4](https://imgur.com/OhUKowj.jpg)

Good luck on your build!  
//vderm
