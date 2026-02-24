# handwired/blackmuller/flash

![handwired/blackmuller/flash](https://imgur.com/a/Ed7VxtJ)

Left half of ~90% split keyboard

* Keyboard Maintainer: [Jake Muller](https://github.com/JakeEMuller)
* Hardware Supported: FlashV3 PCB
* Hardware Availability: N/A

Make example for this keyboard (after setting up your build environment):

    make handwired/blackmuller/flash:default

Flashing example for this keyboard:

    make handwired/blackmuller/flash:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Keyboard Layer drivers

Special drivers are required for full layer support. 
On Windows: https://github.com/JakeEMuller/FlashBangLayerApp
On Linux: N/A
On Mac: N/A

## Bootloader

Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at Escape and plug in the keyboard
* **Physical reset button**: Briefly bridge the pads on the back of the PCB (R2)
