# Pandora

![Pandora](https://i.imgur.com/fQRmwfOh.jpg)

Pandora is an ultra premium 60 percent keyboard. The construction uses 6063 alu, pvd coated brass/stainless steel and dyed polycarbonate. The finishes include e-coating, anodizing, micro arc anodization, metal polish and fine beadblasting. Layouts are limited to a few ANSI variations such as tsangan/wkl and ISO. The keyboard also has a usb-c daugtherboard, an integrated usb hub and rotary encoder. The case has indicator lights for caps and is gasket mounted. The pcb is designed by me in house and has some super cool tricks up its sleeve as well.

More info at www.pearlboards.net :]

* Keyboard Maintainer: Koobaczech
* Hardware Supported: Pandora
* Availability: www.pearlboards.net

Make example for this keyboard (after setting up your build environment):

    make pearlboards/pandora:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB labeled `RESET`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` in conjunction with the key mapped to `MO(1))` 
