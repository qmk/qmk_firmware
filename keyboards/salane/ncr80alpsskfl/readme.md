# NCR80 ALPS SKFL

![NCR80 ALPS SKFL](https://i.imgur.com/X964J2P.jpeg)

 PCB Replace for NCR80 with ALPS SKFL switch.

 **Firmware files are SPECIFIC to each board. Firmware files from one, will not work on the other.** Please use the `.hex` or `.bin` appropriate for your board.

* Keyboard Maintainer: [Mai The San](https://github.com/MaiTheSan) 
* Hardware Supported: NCR80 
* Hardware Availability: [Github](https://github.com/MaiTheSan/NCR80-ALPS-SKFL)

Make examples for this keyboard (after setting up your build environment):

    make salane/ncr80alpsskfl:default

Flashing example for this keyboard:

    make salane/ncr80alpsskfl:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: short 2 pin in the back of pcb and plug the usb in
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).