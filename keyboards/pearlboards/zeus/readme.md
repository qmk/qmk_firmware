# Zeus

![Zeus](https://i.imgur.com/jdCaP1mh.jpg)

Zeus is a modern Greek themed TKL keyboard. The construction uses 6061 alu, pvd coated brass/stainless steel and dyed polycarbonate. The finishes include e-coating, anodizing, micro arc anodization, metal polish and fine beadblasting. The keyboard has a usb-c daugtherboard, an integrated dual usb hub with an audio jack and dac, an internal speaker and a rotary encoder. The case has indicator lights and is top mounted. The pcb is designed by me in house and has some super cool tricks up its sleeve as well.

* Keyboard Maintainer: Koobaczech
* Hardware Supported: Koobaczech
* Availability: https://pearlboards.net/products/zeus-tkl?variant=39646626250884

Make example for this keyboard (after setting up your build environment):

    make pearlboards/zeus:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB labeled `RESET`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` in conjunction with the key mapped to `MO(1))` 
