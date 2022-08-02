# Optical Keyboard - rev1

* Keyboard Maintainer: [Girish](https://github.com/girishji)
* Hardware Supported: Black pill STM32F401

A keyboard using optical switches instead of pure mechanical switches.
The main difference is in the way matrix scan is implemented. It is assumed
that each column is selected (set pin to Output and High) and rows are read in
sequence. Row pins are set as Input, with or without inbuilt pullup resistor.

Column can be powered using a GPIO pin (for IR LED) and 3v3 or 5v pin for
Phototransistor. Appropriate delay should be inserted before reading the row
GPIO pins, thereby giving enough time for Phototransistor to 'rise'. This delay
is generally around 15us and results in very high scan rate. It is also 
possible to use transistors to boost current to IR LED to get better rise times
and thereby improve scanning frequency, but this is generally not necessary.
You can exceed 3kHz scanning frequency without transistors. Also, there is no
need for debounce with optical switches. 

You can use Geteron optical switches (MX profile), or similar ones from Kailh
and Keychron (low profile).

PCB for this keyboard can be found on [github](https://github.com/girishji/optical-keyboard).

## Build

Make example for this keyboard (after setting up your build environment):

    make opticalkb/rev1:default

Flashing example for this keyboard:

    make opticalkb/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button BOOT and then button NRST, release NRST first and then BOOT 
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Verify that it entered DFU (bootloader) mode through QMK Toolbox before
flashing.

## Wiring Instructions

There is only one way to solder Blackpill (STM32F401) to the [PCB](https://github.com/girishji/optical-keyboard).
If you are going to use Blackpill in other projects, note that certain pins are [not usable](https://docs.qmk.fm/#/platformdev_blackpill_f411).

