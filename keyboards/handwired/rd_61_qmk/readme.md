# Redragon K617 (QMK ported)

![Keyboard image](https://imagizer.imageshack.com/img922/3464/qUpU8k.png)

*Firmware,layout and schematics for porting Redragon K617 keyboard to qmk*

* Keyboard Maintainer: *[abhijithabhiakl](https://github.com/abhijithabhiakl)*
* Hardware Supported: *Redragon K617, Pro micro(caterina)*
* Hardware Availability: *[Redragon K617](https://redragon.in/products/fizz-k617-60-wired-mechanical-keyboard-white-and-grey-red-switches)*

Make example for this keyboard (after setting up your build environment):

    make handwired/rd_61_qmk:default

Flashing example for this keyboard:

    make handwired/rd_61_qmk:default:flash
    
Also can be flashed with QMK *[QMK toolbox](https://github.com/qmk/qmk_toolbox)* or *[avrdudess](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/)*

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware details: 

#### Matrix layout:
![Keyboard image](https://imagizer.imageshack.com/img924/8415/hX5gAb.jpg)

#### Schematic:
![Keyboard image](https://imagizer.imageshack.com/img922/5585/vXorPx.png)

* *The header J0 in not present in the normal pro mirco, for my purpose i directly soldered the `D5`, `C7` and `F0` pins to the pad of the microcontroller with micro soldering tools.

* **To connect the promicro to PCB - Micro USB to the USB C, i made use of an old micro usb cable lying around, cut the cable to approprite length and exposed the wires, connected the male connector to female port of  pro micro, Connected the Vcc and Gnd wires to Vcc and Gnd in the PCB, In PCB there's a differential pair (D+, D-) running from USB C port in the PCB to microcontroller in the PCB, in between the connection there's a resistor and filter capacitors, after removing both (bypassing the connection) i connected the D+ and D- wires to the bypassed point respectively (make sure the cable wires are also impedance matched)

## Bootloader

Entering the bootloader:

* **Physical reset button**: Briefly press the button soldered to promicro (In my case i soldered the reset button to the promicro with wires and glued in outside in front of the case)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available ( I haven't added that in the keymap since i added a physical reset button )
