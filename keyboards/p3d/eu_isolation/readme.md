# EU ISOlation

![euisolation](https://i.imgur.com/5LGsiJZh.jpg)

EU ISOlation is an ortholinear 40% keyboard designed to use up your spare iso
enters from you collection of keyboard kits.

* Keyboard Maintainer: Originally by [TuckTuckFloof](https://github.com/TuckTuckFloof)
 cleaned up and merged to QMK by [aadriance](https://github.com/aadriance)
* Hardware Supported: EU ISOlation
* Hardware Availability: Originally a [P3DStore](https://p3dstore.com/) group buy. 
 Open source pcb info available on [TuckTuckFloofs github](https://github.com/TuckTuckFloof/EUISO-pcb)

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Information

Make example for this keyboard (after setting up your build environment):

    make p3d/eu_isolation:default

Flashing example for this keyboard:

    make p3d/eu_isolation:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
