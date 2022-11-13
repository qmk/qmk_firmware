# The Neodox keyboard

Inspired by Redox from Mattia Dal Ben

**Neodox** project. More information and building instruction [here](todo).

- Keyboard Maintainer: [MatteoDM](todo)  
- Hardware Supported: rp2040 ,ws2812b, GC9A01
- Hardware Availability: handwire at the moment


To build the rp2040 firmware, first set your config:
```sh
qmk config user.keyboard=neodox
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
* **Physical boot button**: Unplug your keyboard then press the BOOT button on the microcontroller PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if you have a layout that has one.


Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
