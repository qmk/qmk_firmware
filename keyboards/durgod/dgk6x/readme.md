# DGK6X = Venus, Hades, Galaxy, etc.

This DGK6X code is shared between the ANSI variants of Venus, Hades and Galaxy keyboards. 

* Keyboard Maintainer: [J-Sully](https://github.com/J-Sully) and [dkjer](https://github.com/dkjer)
* Hardware Supported: Durgod Venus, Hades or Galaxy board with STM32F070RBT6 
* Hardware Availability: [Venus](https://www.amazon.com/dp/B07XFP5MMZ), [Hades](https://www.amazon.com/gp/product/B08562392T) and [Galaxy](https://www.amazon.com/Galaxy-75-Modular-Mechanical-Keyboard/dp/B08PDRD8MP)

## Instructions

### Build

Instructions for building the Venus, Hades and Galaxy firmware can be found here: 
* [Venus ANSI](venus_ansi/readme.md)
* [Venus ISO](venus_iso/readme.md)
* [Hades ANSI](hades_ansi/readme.md)
* [Hades ISO](hades_iso/readme.md)
* [Galaxy](galaxy/readme.md)

### Initial Flash

For first Flashing from initial Stock's Firmware

1. Back up original Firmware Image:
- Unplug
- Short Boot0 to Vdd (See below)
- Plug In USB
- Make a Flash Image's Backup in case you wanted to restore the Keyboard to Stock's Image:
  - Using dfu-util:

        dfu-util --list
        dfu-util --alt 0 --dfuse-address 0x08000000 --upload ${OLD_STOCK_BIN}

2. Flash the QMK Firmware Image.
- Put board into Bootloader mode, using the same method as when backing up the original Firmware (above)
- Here are a few options for performing the initial Flash:
  - Using [QMK Toolbox](https://github.com/qmk/qmk_toolbox)
  - Using dfu-util:

        dfu-util --alt 0 --dfuse-address 0x08000000 --download ${NEW_QMK_BIN}

You can short Boot0 to Vdd by shorting R19 to C30 on the sides closest to the processor, as shown:

* Hades & Venus:
<img src="https://i.imgur.com/JwF7MeZ.jpg" width="520" height="571" alt="Shorting Boot0 to Vdd on Hades or Venus">

* Galaxy 75
<img src="https://i.imgur.com/b9eZG5T.jpg" width="520" height="571" alt="Shorting Boot0 to Vdd on Galaxy 75">

### Subsequent Flashing

For repeating Flashing you can use BootMagic:
- BootMagic Lite has been enabled with Assigned "Esc" key 
- Unplug USB Cable
- Holding Esc Button 
- Plug in USB Cable, Keyboard should be in ST-Bootloader state

