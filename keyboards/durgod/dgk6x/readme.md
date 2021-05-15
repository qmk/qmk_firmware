# DGK6X = Venus, Hades, etc.

This DGK6X is shared between the ANSI variants of Venus and Hades keyboards. 

* Keyboard Maintainer: [J-Sully](https://github.com/J-Sully) and [dkjer](https://github.com/dkjer)
* Hardware Supported: Durgod Venus or Hades board with STM32F070RBT6 
* Hardware Availability: [Venus](https://www.amazon.com/dp/B07XFP5MMZ) and [Hades](https://www.amazon.com/gp/product/B08562392T)

## Instructions

### Build

Instructions for building the Venus and Hades firmware can be found here: 
* [Venus](venus/readme.md)
* [Hades](hades/readme.md)

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
  - Using DFuseDemo.exe if STTub30 driver is used.
  - Using dfu-util:

        dfu-util --alt 0 --dfuse-address 0x08000000 --download ${NEW_QMK_BIN}

You can short Boot0 to Vdd by shorting R19 to C30 on the sides closest to the processor, as shown:

<img src="https://i.imgur.com/JwF7MeZ.jpg" width="520" height="571" alt="Shorting Boot0 to Vdd on DGK6x">

### Subsequent Flashing

For repeating Flashing you can use BootMagic:
- BootMagic Lite has been enabled with Assigned "Esc" key 
- Unplug USB Cable
- Holding Esc Button 
- Plug in USB Cable, Keyboard should be in ST-Bootloader state

