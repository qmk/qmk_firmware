## Phrygian Design ph100

![ph100](https://cdn.shopify.com/s/files/1/0470/8814/0443/products/DSCF0064_1080x.png)

The ph100 is a 100-key modular keyboard from Phrygian Design.

* Keyboard Maintainer: https://github.com/phrygiandesign
* Hardware Supported: ph100 PCB
* Hardware Availability: https://phrygiandesign.com/products/ph100-mechanical-keyboard
* Keyboard support: contact@phrygiandesign.com

Make example for this keyboard:

    make phrygian/ph100:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

#### Note: Booting into the STM32 USB Bootloader
The STM32F042 range of microcontrollers have problems with entering into the USB bootloader with QMK's bootloader key sequence.  
To boot into the bootloader, apply power to the keyboard while holding down "SW0" on the bottom of PCB near the USB port.
