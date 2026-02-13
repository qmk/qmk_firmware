# The Neodox keyboard

Inspired by Redox from Mattia Dal Ben

**Neodox** project. More information and building instruction [here](todo).

- Keyboard Maintainer: [MatteoDM](todo)  
- Hardware Supported: rp2040 ,ws2812b, GC9A01, [handwire 3D printed case](https://www.thingiverse.com/thing:5625196)
- Hardware Availability: handwire at the moment


Make example for this keyboard (after setting up your build environment):

    make neodox:default

Enter the bootloader when prompted by doing one of the following:
* **Physical boot button**: Unplug your keyboard then press the BOOT button on the microcontroller PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if you have a layout that has one.


Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
