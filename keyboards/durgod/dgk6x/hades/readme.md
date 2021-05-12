# Hades

This is a standard off-the-shelf Durgod Hades 65% ANSI layout keyboard with RGB matrix.

* Keyboard Maintainer: [J-Sully](https://github.com/J-Sully)
* Hardware Supported: Durgod Hades board with STM32F070RBT6
* Hardware Availability: https://www.amazon.com/gp/product/B08562392T

## Instructions

### Build

Make command example for this keyboard (after setting up your build environment):

    make durgod/hades:default

Flashing example for this keyboard:

    make durgod/hades:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Initial Flash

For first Flashing from initial Stock's Firmware

1. Back up original Firmware Image:
- Unplug
- Short Boot0 to Vdd (See below)
- Plug In USB
- Make a Flash Image's Backup in case you wanted to restore the Keyboard to Stock's Image:
  - Using DFUseDemo.exe from ST's STSW-STM32080: https://www.st.com/en/development-tools/stsw-stm32080.html
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
