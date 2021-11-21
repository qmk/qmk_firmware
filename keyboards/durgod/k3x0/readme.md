# K3X0 = K310, K320, etc.

This K3X0 code is shared between both the ANSI and ISO variants of both the
K310 full-sized 104/105-key and K320 TKL 87/88-key keyboards.

* Keyboard Maintainers: [dkjer](https://github.com/dkjer) and [tylert](https://github.com/tylert)
* Hardware Supported: Durgod Taurus K310 or K320 board with STM32F070RBT6
* Hardware Availability: K310 https://www.durgod.com/page9?product_id=53&_l=en
                         and K320 https://www.durgod.com/page9?product_id=47&_l=en

## Instructions

### Build

Instructions for building the K310 and K320 firmware can be found here:
* [K310](k310/readme.md)
* [K320](k320/readme.md)

### Initial Flash

For first Flashing from initial Stock Firmware

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

You can short Boot0 to Vdd by shorting R21 to C27 on the sides closest to the processor, as shown:

<img src="https://i.imgur.com/hvDnw5a.jpg" width="520" height="693" alt="Shorting Boot0 to Vdd on K320">

### Subsequent Flashing

For repeating Flashing you can use BootMagic:
- BootMagic Lite has been enabled with Assigned "Esc" key 
- Unplug USB Cable
- Holding Esc Button 
- Plug in USB Cable, Keyboard should be in ST-Bootloader state
