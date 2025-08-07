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

See [QMK repo cloning](https://docs.qmk.fm/#/getting_started_github) for information about cloning the repo

## Hardware details: 

Note : Before doing any modifications in the PCB make sure that the stock microcontroller is removed.

#### Matrix layout:
![Keyboard image](https://imagizer.imageshack.com/img924/8415/hX5gAb.jpg)

#### Schematic:
![Keyboard image](https://imagizer.imageshack.com/img922/5585/vXorPx.png)

* *The header `J0` in not present in the normal pro mirco, for my purpose i directly soldered the `D5`, `C7` and `F0` pins to the pad of the microcontroller with micro soldering tools.

* **To connect the promicro to PCB - Micro USB to the USB C, i made use of an old micro usb cable lying around, cut the cable to approprite length and exposed the wires, connected the male connector to female port of  pro micro, Connected the Vcc and Gnd wires to Vcc and Gnd in the PCB, In PCB there's a differential pair (D+, D-) running from USB C port in the PCB to microcontroller in the PCB, in between the connection there's a resistor and filter capacitors, after removing both (bypassing the connection) i connected the D+ and D- wires to the bypassed point respectively (make sure the cable wires are also impedance matched)

#### RGB Lighting:

The stock RGB Lighting used on the keyboard is [this](https://www.luckylight.cn/en/products/smd-led/multi-color-smd-led/?series_code=sr187-rgb-series) `SR187RGBC` `Multi-color PLCC SMD LEDs`, to use this kind of LED with qmk I either have to write a custom led matrix code ( I don't know for sure if qmk already have any support this neither currently have the knowledge or time to do so ) or need to make a led matrix with qmk supported led matrix drivers, due to above mentioned reasons I haven't did any RGB lightings in the keyboard except a single ws2812 led 

I'm  trying to make a custom PCB for this keyboard (will work for all redragon 60% keyboard (ig) ),  I'll update here 

## Bootloader

Entering the bootloader:

* **Physical reset button**: Briefly press the button soldered to promicro (In my case i soldered the reset button to the promicro with wires and glued in outside in front of the case)
* **Bootmagic key at [0,0]**: Hold this key down when plugging the keyboard in. Just the single key
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. Also in `layer #3` keys `DB_TOGG` `QK_RBT` `QK_BOOT` `QK_MAKE` are present at the top right corner for debug mode, keyboard reboot, bootloader mode and qmk make (`qmk flash` if shift is held ) in the respective order to make the flasing easier.
`QK_MAKE` will type `qmk compile -kb handwired/rd_61_qmk -km default` in the terminal and `qmk flash` will type `qmk flash -kb handwired/rd_61_qmk -km default`

