# le_chiffre_neue_rp2040

![le_chiffre_neue_rp2040](https://i.imgur.com/Kig3OeG.jpeg)

a mostly 3d printed/solder-free/handwired/hotswap/rp2040W-powered rendition of tominabox1's classic le_chiffre, sans rotary encoder and with the space and enter key positions swapped.

* Keyboard Maintainer: [jkaunert](https://github.com/jkaunert)
* Hardware Supported: Handwired, rp_2040W(support for LED, BLE in rev2), ![HSSv4.4 3D printed sockets](https://github.com/stingray127/handwirehotswap).
* Hardware Availability: [Build log coming soon](https://philoandgunge.com/handwired/builds/le_chiffre_neue_rp2040)

Make example for this keyboard (after setting up your build environment):

    make handwired/philo_and_gunge/le_chiffre_neue_rp2040:default

Flashing example for this keyboard:

    make handwired/philo_and_gunge/le_chiffre_neue_rp2040:default:flash

## Bootloader

Enter the bootloader by holding down the boot button on the board while plugging in the board. Release the button and your machine should recognize the rp as a drive.  Drag and drop the file in the root folder of the drive and you're done!

## More information

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
