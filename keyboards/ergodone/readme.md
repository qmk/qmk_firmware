ErgoDone
===

![ErgoDone](https://i.imgur.com/QERsQGQ.jpg)

ErgoDone is a modified ErgoDox with pre-soldered components made by K.T.E.C. It has different wiring and uses a Pro Micro instead of Teensy.

  - Keyboard Maintainer: [Yu He](http://github.com/yuhe00)
  - Hardware Supported: 
    - ErgoDone ver. 1.3 (tested)
  - Hardware Availability: [KBDFans](https://kbdfans.myshopify.com/collections/pcb/products/ergodone-keyboard-pcb-1pcs-free-shipping?variant=37178300237)

Make example for this keyboard (after setting up your build environment):

    make ergodox-ergodone-default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

# Flashing the keyboard

The ErgoDone uses an HID bootloader rather than the Teensy one, and requires a different way of flashing the firmware.

1. While plugging in the USB cable, hold the two right-most keys on the left half of the ErgoDone to enter FLASH mode.
2. Use the `hid_bootloader_cli` utlity from [TKG Toolkit](https://github.com/kairyu/tkg-toolkit):
   
        hid_bootloader_cli -mmcu=atmega32u4 ergodox_ergodone_default
