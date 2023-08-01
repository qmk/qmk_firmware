# K3X0 = K310, K320, etc.

This K3X0 code is shared between both the ANSI and ISO variants of both the
K310 full-sized 104/105-key and K320 TKL 87/88-key keyboards.

* Keyboard Maintainers: [dkjer](https://github.com/dkjer) and [tylert](https://github.com/tylert)
* Hardware Supported:
  * [Durgod Taurus K310 with STM32F070RBT6](https://www.durgod.com/page9?product_id=53&_l=en "Taurus K310 Product Page | Durgod.com")
  * [Durgod Taurus K320 with STM32F070RBT6](https://www.durgod.com/page9?product_id=47&_l=en "Taurus K320 Product Page | Durgod.com")
* Hardware Availability:
  * [K310 on Amazon.com](https://www.amazon.com/Durgod-Taurus-K310-Mechanical-Keyboard/dp/B07TXB4XF3)
  * [K320 on Amazon.com](https://www.amazon.com/Durgod-Taurus-Corona-Mechanical-Keyboard/dp/B078H3WPHM)

## Instructions

### Build

Instructions for building the K310 and K320 firmware can be found here:
* [K310](k310/readme.md)
* [K320](k320/readme.md)

### Initial Flash

#### Requirements

- The Durgod K320/K310 - different batches have different controllers, so when opening the keyboard, you will have to make sure it's using SMT32 controller.
- Another keyboard - when on bootloader mode, you can't use the keyboard to type and execute the commands (not really required if you can use any mouse interface to type and execute the commands).
- 2 prying tools - to open the keyboard.
- Another helping hand - it can be also done with just two hands, but it will require a lot of dexterity.
- A small cable with both ends cut.

#### Enter bootloader while using the original firmware

1. Unplug USB cable.
2. Open the keyboard case - there are plenty of youtube videos in that, but you will basically need 2 prying tools and a certain amount of force.
3. After opening the keyboard, put the PCB upsides down, and the controller should be near the LEDs, and make sure it's using the right controller (SMT32).
4. Use the cable to short Boot0 to Vdd, by shorting R21 to C27 on the sides closest to the processor, as shown:

<img src="https://i.imgur.com/hvDnw5a.jpg" width="520" height="693" alt="Shorting Boot0 to Vdd on K320">

5. While shorting both contacts as instructed in step 4, plug in the USB cable.
6. When the USB cable is fully inserted, the LEDs should not turn on and the keyboard it's not able to type, you are probably on bootloader mode, to be sure:
  - Using dfu-util, it should show something like "Found DFU…" after using this command:
```
dfu-util --list
```

Now that you are sure to be in bootloader mode, you can backup the original firmware and flash QMK Firmware.

If it does not behave like described, remove the cable and go back to step 4.

#### Backup original firmware

1. Be in Bootloader mode.
2. Execute this command to backup:
  - Using dfu-util:
```bash
dfu-util -a 0 -d 0483:DF11 -s 0x08000000 -U k3x0_original.bin
```

#### Flash the QMK Firmware Image

1. Be in Bootloader mode.
2. Here are a few options for performing the initial Flash:
  - Using [QMK Toolbox](https://github.com/qmk/qmk_toolbox)
  - Using qmk on command line:

```bash
# k310
qmk flash -kb durgod/k3x0/k310 -km default

# k320
qmk flash -kb durgod/k3x0/k320 -km default
```

### Subsequent Flashing

For repeating Flashing you can use BootMagic Lite has been enabled by default and assigned to the "Esc" key:

1. Unplug USB Cable.
2. Hold the "Esc" key.
2. Plug in the USB Cable, the Keyboard should be in ST-Bootloader state.
