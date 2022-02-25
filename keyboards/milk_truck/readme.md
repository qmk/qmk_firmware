# Milk Truck

![Milk Truck](https://imgur.com/NUmiTDSh.jpg)

A dairy-filled, left-handed, numpad-having, extended-minivan, forty-percent keyboard.

* Keyboard Maintainer: [Ryan Boone](https://github.com/rjboone) (Drmmr#0004)
* Hardware Supported: Milk Truck
* Hardware Availability: Group buy from [P3D Store](https://p3dstore.com)

Make example for this keyboard (after setting up your build environment):

    make milk_truck:default

Flashing example for this keyboard:

    make milk_truck:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET`
