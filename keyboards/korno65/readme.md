# korno65

Korno65

* Keyboard Maintainer: [Jordan-Ramos](https://github.com/Jordan_Ramos)
* Hardware Supported: PCB v3
* Hardware Availability: https://eschit.com/products/gb-korno65s-r2-v3

Make example for this keyboard (after setting up your build environment):

    make korno65:default

Entering bootloader mode:
    
    Try the following, in order:
        Unplug your keyboard, hold down the top or bottom left key (usually Escape or Left Control) and plug in your keyboard
	Press the physical RESET button, usually located on the underside of the PCB
	Locate header pins on the PCB labeled RESET and GND, and short them together while plugging your PCB in

Flashing example for this keyboard:

    make korno65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
