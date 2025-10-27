# Tvrd Rad Keyboards TRK2

![TRK2](https://imgur.com/iO2zIIT)

Custom keyboard designed by Tvrd Rad Keyboards aka TRK2

* Keyboard Maintainer: [Tvrd Rad Keyboards](https://www.trkeyboards.com)
* Hardware Supported: TRK2 PCB
* Hardware Availability: https://www.trkeyboards.com/en/keyboards/5-trk2/

Getting the board into bootloader mode:
To be able to flash firmware onto this board and put keyboard into bootloader mode, you need to press the "Fn" and "Esc" keys on the keyboard at the same time. 

Make example for this keyboard (after setting up your build environment):

    make trkeyboards/trk2:default

Flashing example for this keyboard:
    
    make trkeyboards/trk2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
