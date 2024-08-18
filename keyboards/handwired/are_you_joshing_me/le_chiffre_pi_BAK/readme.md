# le_chiffre_pi

![le_chiffre_pi](https://github.com/user-attachments/assets/8991ef32-331e-4a57-b435-bee1fe92902c)

a mostly 3d printed, solder-free, hand-wired, hot-swap, rp2040W-powered variant of tominabox1's classic le_chiffre, sans rotary encoder and with a custom default keymap.

* Keyboard Maintainer: [jkaunert](https://github.com/jkaunert)
* Hardware Supported: Hand-wired, rp_2040W(support for LED, BLE in future revision), [HSSv4.4 3D printed sockets](https://github.com/stingray127/handwirehotswap).
* Hardware Availability: [Build log coming soon](https://areyoujoshing.me)

Make example for this keyboard (after setting up your build environment):

    make handwired/are_you_joshing_me/le_chiffre_pi:default

Flashing example for this keyboard:

    make handwired/are_you_joshing_me/le_chiffre_pi:default:flash

## Bootloader

Enter the bootloader by holding down the boot button on the board while plugging in the board. Release the button and your machine should recognize the rp as a drive.  Drag and drop the file in the root folder of the drive and you're done!

## More information

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
