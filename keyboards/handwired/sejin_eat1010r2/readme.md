# QMK-based firmware for Sejin EAT-1010R2 keyboard

* Keyboard Maintainer: [DmNosachev](https://github.com/DmNosachev)
* Hardware Supported: Sejin EAT-1010R2 (membrane keyboard, Sejin
Futaba-mount dome, Asian 101 ISO layout), Blue/Black Pill STM32F103 MCU 
oard. Alternatevely you can use any MCU which is supported by QMK and
has 27 or more IO pins

Make example for this keyboard (after setting up your build environment):

    make handwired/sejin_eat1010r2:default
    
Flashing example for this keyboard:

    make handwired/sejin_eat1010r2:default:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Additional hardware
* 16 and 8 pin 2.54mm (0.1'') FPC connectors. They can be found at
Aliexpress for 2–3 USD for 10pcs. Two 8 pin connectors can be glued
together as a replacement for 16 pin.
* Three 5mm LEDs and current limiting resistors (150–300Ω, depending on
LED specs). This keyboard has exactly the same spacing between LEDs as
IBM Model M, so a corresponding PCB can be used after adding resistors.

## Membrane
Sejin EAT-1010R2 has 16x8 matrix. There are 16 and 8 pin flex connectors
from membrane sheets. Solder FPC connectors to devboard (numbering from
left to right, see *matrix_pins* in info.json file).

## Bootloader
Burn [STM32duino bootloader](https://github.com/rogerclarkmelbourne/STM32duino-bootloader)
to Blue Pill board.

There are several ways to get into the bootloader:
* STM32duino bootloader waits for 3 seconds in DFU mode before jumping to application.
You just have to start the flashing process, then connect the USB.
* This firmware is configured with [bootmagic feature](https://docs.qmk.fm/#/feature_bootmagic).
Hold the ESC key down when plugging the keyboard in to trigger the bootloader.

## Troubleshooting
There is *debug* layout which has mapping for every matrix position and
prints column and raw numbers to console (hid_listen or QMK toolbox).
