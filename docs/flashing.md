# Flashing Instructions and Bootloader Information

There are quite a few different types of bootloaders that keyboards use, and just about all of the use a different flashing method. Luckily, projects like the [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) aim to be compatible with all the different types without having to think about it much, but this article will describe the different types of bootloaders, and available methods for flashing them.

If you have a bootloader selected with the `BOOTLOADER` variable in your `rules.mk`, QMK will automatically calculate if your .hex file is the right size to be flashed to the device, and output the total size in bytes (along with the max). To run this process manually, compile with the target `check-size`, eg `make planck/rev4:default:check-size`.

## DFU

Atmel's DFU bootloader comes on all atmega32u4 chips by default, and is used by many keyboards that have their own ICs on their PCBs (Older OLKB boards, Clueboards). Some keyboards may also use LUFA's DFU bootloader (or QMK's fork) (Newer OLKB boards) that adds in additional features specific to that hardware.

To ensure compatibility with the DFU bootloader, make sure this block is present your `rules.mk` (optionally with `lufa-dfu` or `qmk-dfu` instead):

    # Bootloader
    #     This definition is optional, and if your keyboard supports multiple bootloaders of
    #     different sizes, comment this out, and the correct address will be loaded
    #     automatically (+60). See bootloader.mk for all options.
    BOOTLOADER = atmel-dfu

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer) / `:dfu` in QMK (recommended command line)
* [Atmel's Flip](http://www.microchip.com/developmenttools/productdetails.aspx?partno=flip) (not recommended)

Flashing sequence:

1. Press the `RESET` keycode, or tap the RESET button (or short RST to GND).
2. Wait for the OS to detect the device
3. Erase the memory (may be done automatically)
4. Flash a .hex file
5. Reset the device into application mode (may be done automatically)

or:

    make <keyboard>:<keymap>:dfu

### QMK DFU

QMK has a fork of the LUFA DFU bootloader that allows for a simple matrix scan for exiting the bootloader and returning to the application, as well as flashing an LED/making a ticking noise with a speaker when things are happening. To enable these features, use this block in your `config.h` (The key that exits the bootloader needs to be hooked-up to the INPUT and OUTPUT defined here):

    #define QMK_ESC_OUTPUT F1 // usually COL
    #define QMK_ESC_INPUT D5 // usually ROW
    #define QMK_LED E6
    #define QMK_SPEAKER C6

The Manufacturer and Product names are automatically pulled from your `config.h`, and "Bootloader" is added to the product.

To generate this bootloader, use the `bootloader` target, eg `make planck/rev4:default:bootloader`.

To generate a production-ready .hex file (containing the application and the bootloader), use the `production` target, eg `make planck/rev4:default:production`.

## Caterina

Arduino boards and their clones use the [Caterina bootloader](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/bootloaders/caterina) (any keyboard built with a Pro Micro, or clone), and uses the avr109 protocol to communicate through virtual serial. Bootloaders like [A-Star](https://www.pololu.com/docs/0J61/9) are based on Caterina.

To ensure compatibility with the Caterina bootloader, make sure this block is present your `rules.mk`:

    # Bootloader
    #     This definition is optional, and if your keyboard supports multiple bootloaders of
    #     different sizes, comment this out, and the correct address will be loaded
    #     automatically (+60). See bootloader.mk for all options.
    BOOTLOADER = caterina

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [avrdude](http://www.nongnu.org/avrdude/) with avr109 / `:avrdude` (recommended command line)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Flashing sequence:

1. Press the `RESET` keycode, or short RST to GND quickly (you only have 7 seconds to flash once it enters)
2. Wait for the OS to detect the device
4. Flash a .hex file
5. Wait for the device to reset automatically

or

    make <keyboard>:<keymap>:avrdude

or if you want to flash multiple boards, use the following command

    make <keyboard>:<keymap>:avrdude-loop

When you're done flashing boards, you'll need to hit Ctrl + C or whatever the correct keystroke is for your operating system to break the loop.

## Halfkay

Halfkay is a super-slim protocol developed by PJRC that uses HID, and come on all Teensys (namely the 2.0).

To ensure compatibility with the Halfkay bootloader, make sure this block is present your `rules.mk`:

    # Bootloader
    #     This definition is optional, and if your keyboard supports multiple bootloaders of
    #     different sizes, comment this out, and the correct address will be loaded
    #     automatically (+60). See bootloader.mk for all options.
    BOOTLOADER = halfkay

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Teensy Loader Command Line](https://www.pjrc.com/teensy/loader_cli.html) (recommended command line)

Flashing sequence:

1. Press the `RESET` keycode, or short RST to GND quickly (you only have 7 seconds to flash once it enters)
2. Wait for the OS to detect the device
4. Flash a .hex file
5. Reset the device into application mode (may be done automatically)
