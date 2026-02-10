# rp2040_orbweaver
QMK firmware for RP2040 based MCU replacement PCB for the Razer Orbweaver gaming keypad

![RP2040 Orbweaver](https://i.imgur.com/GCPRUbs.png)


This firmware is for the Razer Orbweaver Chroma keypad with a custom, plug and play, RP2040 MCU PCB. For installation instructions and board availability see [geekhack](https://geekhack.org/index.php?topic=124092.0).

The firmware controls a 6x5 key matrix (4x5 keypad + 6 additional keys on the thumb pad and up to 4 additional keys added by user). It also controls a IS31FL3731 RGB Matrix controller (on the Chroma model) via I2C interface. This requires a single I2C Driver with 20 common anode RGB LEDs.

Key 20 (bottom right) is used to switch layers.  

The default key map provides 3 preset layers.  

(layer 0) is a generic layer based on the original Razer defaults.  
(layer 1) replaces modifier keys with letter keys.   
(layer 2) replaces the 2 top rows with RGB control keys.  

The three LEDs on the thumb pad indicate the active layer. 

Blue = layer 0  
Green = layer 1  
Yellow = layer 3  

All LEDs will be off when any other (user added) layout is activated

A set of RGB animations are included in confg.h.  These are controlled by activating the Yellow layer and using keys 01 - 11 (11 toggles the lighting on and off - see /keymaps/default/keymap.c for more information)

Many thanks to a_marmot. Without his original handwired project, this board would not have been possible. His original work can be found here. [geekhack](https://geekhack.org/index.php?topic=119396.0).

* Keyboard Maintainer: [Lostdotfish](https://github.com/Lostdotfish)
* Hardware Supported: RP2040 + IS31FL3731
* Hardware Availability: [https://geekhack.org/index.php?topic=124092.0](https://geekhack.org/index.php?topic=124092.0)

Make example for this keyboard (after setting up your build environment):

    make lostdotfish/rp2040_orbweaver:default

Flashing example for this keyboard:

    make lostdotfish/rp2040_orbweaver:default:flash
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* Press and hold the upper left hand key on the main keyboard while you plug in the USB.
* Press and release the boot button on the top of the RP2040_Orbweaver v2.0 inside the modded unit. 
