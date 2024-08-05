# The Redox keyboard

<p align="center">
<img src="https://github.com/mattdibi/redox-keyboard/raw/master/img/redox-logo.png" alt="Redox logo" width="600"/>
</p>

<p align="center">
<img src="https://github.com/mattdibi/redox-keyboard/raw/master/img/redox-pcb2.jpg" alt="Redox PCB rev1.0" width="600"/>
</p>

**Redox**: the **R**educed **E**rgo**dox** project. More information and building instruction [here](https://github.com/mattdibi/redox-keyboard).

- Keyboard Maintainer: [Mattia Dal Ben](https://github.com/mattdibi)  
- Hardware Supported: 
    - Redox PCB rev1.0 
    - Pro Micro or Proton C micro controllers
- Hardware Availability: [Falbatech](https://falba.tech/product-category/keyboard-parts/redox-parts/)

Make example for this keyboard (after setting up [qmk](https://docs.qmk.fm/#/getting_started_build_tools)):

To build the Pro Micro firmware, first set your config:
```sh
qmk config user.keyboard=redox/rev1
```
or if your using the Proton C:
```sh
qmk config user.keyboard=redox/rev1/proton_c
```

Don't forget to set a layout. There's many to choose from in the keymaps folder.
```sh
qmk config user.keymap=default
```

Now you can build your firmware!
```sh
qmk compile
```

Flashing is also straightforward. Run:
```sh
qmk flash
```
Enter the bootloader when prompted by doing one of the following:
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if you have a layout that has one.

The WS2812 driver is *untested* on the Proton C, but if you choose to use this feature, you will need to source 5v from the Proton's VUSB pin and not use the PCB's dedicated pin which will be 3v3 *and* follow the [documentation](https://docs.qmk.fm/#/ws2812_driver) to enable the correct driver settings.

Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
