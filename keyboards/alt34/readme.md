# alt34

![alt34](https://i.imgur.com/GDv0dL0h.png)

alt34 was designed as a minimalistic, 'no frills' workhorse keyboard with focus on efficiency and ergonomics.
This breaks down into the following priorities in the design:

* Keyboard Maintainer: [Tommy Alatalo](https://github.com/altosys)
* Hardware Supported: 
   * Compact 34 key split layout with two thumb keys per hand
   * Orthogonal layout with a somewhat aggressive column stagger
   * Compatibility with standard controllers (Elite-C, Pro Micro etc.)
   * Cherry MX switch support
   * Kailh hotswap socket support
   * Tenting puck support

## Hardware

A bill of materials for building alt34 is found in [the alt34 git repo](https://gitlab.com/altosys/alt34)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset jumper**: Briefly short the pads just below the TRRS connector on the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Latest updates and information for alt34 is found at https://gitlab.com/altosys/alt34

## Build Guide

There is no dedicated build guide for alt34. If you are a novice builder and need guidance then suggested reading would be build guides for the Corne keyboard (aka. crkbd), they will cover the usual installation of the controller, diodes and hotswap sockets, which is essentially all there is to assembling the alt34.

## Flashing QMK Firmware

Set up your build environment according to the QMK documentation, then after cloning the `qmk_firmware` repository you can run the below commands in the repo root to build and flash the firmware onto your controller.

Note that this method enables `EE_HANDS` mode which allows you to connect the USB cable to either half of alt34 when using the keyboard.


Flash `EE_HANDS` to the left hand half, this updates the persistent EEPROM storage along with the firmware.
Run the below command and then set the board into bootloader mode by bridging the reset pads below the TRRS connector with a paper clip or similar.
```
make alt34/rev1:default:dfu-split-left
```

Do the same for the right hand side:
```
make alt34/rev1:default:dfu-split-right
```

Now you should be able to connect the USB cable to either side of the split and it should work the same.

For any further changes it is enough to flash only the firmware and not the EEPROM:
```
make alt34/rev1:default:flash
```

It is still recommended to do this for both sides of the split when updating keymaps etc.

**Note I:** the above examples are using an Elite-C controller with an `atmel-dfu` bootloader, adjust this according to your own hardware.

**Note II:** the included keymap is rudimentary, the recommended layout to use with alt34 is `miryoku`, see the [miryoku docs](https://github.com/manna-harbour/miryoku) for instructions.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
