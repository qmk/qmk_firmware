# The Redox keyboard

To build the Pro Micro firmware, first set your config:
```sh
qmk config user.keyboard=davinci_v1
```

Don't forget to set a layout. 
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
* **Keycode in layout**: Press the key mapped to `RESET` if you have a layout that has one.

The WS2812 driver is *untested* on the Proton C, but if you choose to use this feature, you will need to source 5v from the Proton's VUSB pin and not use the PCB's dedicated pin which will be 3v3 *and* follow the [documentation](https://docs.qmk.fm/#/ws2812_driver) to enable the correct driver settings.

Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
