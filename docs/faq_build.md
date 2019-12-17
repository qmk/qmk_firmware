# Frequently Asked Build Questions

This page covers questions about building QMK. If you haven't yet done so, you should read the [Build Environment Setup](getting_started_build_tools.md) and [Make Instructions](getting_started_make_guide.md) guides.

## Can't Program on Linux
You will need proper permissions to operate a device. For Linux users, see the instructions regarding `udev` rules, below. If you have issues with `udev`, a work-around is to use the `sudo` command. If you are not familiar with this command, check its manual with `man sudo` or [see this webpage](https://linux.die.net/man/8/sudo).

An example of using `sudo`, when your controller is ATMega32u4:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

or just:

    $ sudo make <keyboard>:<keymap>:dfu

Note that running `make` with `sudo` is generally ***not*** a good idea, and you should use one of the former methods, if possible.

### Linux `udev` Rules
On Linux, you'll need proper privileges to access the MCU. You can either use
`sudo` when flashing firmware, or place these files in `/etc/udev/rules.d/`. Once added run the following:
```console
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**/etc/udev/rules.d/50-atmel-dfu.rules:**
```
# Atmel ATMega32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"
# Atmel USBKEY AT90USB1287
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ffb", MODE:="0666"
# Atmel ATMega32U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff0", MODE:="0666"
```

**/etc/udev/rules.d/52-tmk-keyboard.rules:**
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```
**/etc/udev/rules.d/54-input-club-keyboard.rules:**

```
# Input Club keyboard bootloader
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1c11", MODE:="0666"
```

**/etc/udev/rules.d/55-caterina.rules:**
```
# ModemManager should ignore the following devices
ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"
ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"
```

**Note:** ModemManager filtering only works when not in strict mode, the following commands can update that settings:
```console
sudo sed -i 's/--filter-policy=strict/--filter-policy=default/' /lib/systemd/system/ModemManager.service
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
```

**/etc/udev/rules.d/56-dfu-util.rules:**
```
# stm32duino
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1eaf", ATTRS{idProduct}=="0003", MODE:="0666"
# Generic stm32
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", MODE:="0666"
```

**/etc/udev/rules.d/57-bootloadhid.rules:**
```
# bootloadHID
SUBSYSTEMS=="usb", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="05df", MODE:="0666"
```

### Serial device is not detected in bootloader mode on Linux
Make sure your kernel has appropriate support for your device. If your device uses USB ACM, such as
Pro Micro (Atmega32u4), make sure to include `CONFIG_USB_ACM=y`. Other devices may require `USB_SERIAL` and any of its sub options.

## Unknown Device for DFU Bootloader

Issues encountered when flashing keyboards on Windows are most often due to having the wrong drivers installed for the bootloader, or none at all.

Re-running the QMK installation script (`./util/qmk_install.sh` from the `qmk_firmware` directory in MSYS2 or WSL) or reinstalling the QMK Toolbox may fix the issue. Alternatively, you can download and run the [`qmk_driver_installer`](https://github.com/qmk/qmk_driver_installer) package manually.

If that doesn't work, then you may need to download and run Zadig. See [Bootloader Driver Installation with Zadig](driver_installation_zadig.md) for more detailed information.

## USB VID and PID
You can use any ID you want with editing `config.h`. Using any presumably unused ID will be no problem in fact except for very low chance of collision with other product.

Most boards in QMK use `0xFEED` as the vendor ID. You should look through other keyboards to make sure you pick a unique Product ID.

Also see this.
https://github.com/tmk/tmk_keyboard/issues/150

You can buy a really unique VID:PID here. I don't think you need this for personal use.
- http://www.obdev.at/products/vusb/license.html
- http://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

## BOOTLOADER_SIZE for AVR
Note that Teensy2.0++ bootloader size is 2048byte. Some Makefiles may have wrong comment.

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 2048
#   Atmel DFU loader 4096       (TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=2048
```

## `avr-gcc: internal compiler error: Abort trap: 6 (program cc1)` on MacOS
This is an issue with updating on brew, causing symlinks that avr-gcc depend on getting mangled.

The solution is to remove and reinstall all affected modules.

```
brew rm avr-gcc
brew rm dfu-programmer
brew rm dfu-util
brew rm gcc-arm-none-eabi
brew rm avrdude
brew install avr-gcc
brew install dfu-programmer
brew install dfu-util
brew install gcc-arm-none-eabi
brew install avrdude
```

### avr-gcc 8.1 and LUFA

If you updated your avr-gcc to above 7 you may see errors involving LUFA. For example:

`lib/lufa/LUFA/Drivers/USB/Class/Device/AudioClassDevice.h:380:5: error: 'const' attribute on function returning 'void'`

For now, you need to rollback avr-gcc to 7 in brew.

```
brew uninstall --force avr-gcc
brew install avr-gcc@8
brew link --force avr-gcc@8
```

### I just flashed my keyboard and it does nothing/keypresses don't register - it's also ARM (rev6 planck, clueboard 60, hs60v2, etc...) (Feb 2019)
Due to how EEPROM works on ARM based chips, saved settings may no longer be valid.  This affects the default layers, and *may*, under certain circumstances we are still figuring out, make the keyboard unusable.  Resetting the EEPROM will correct this.

[Planck rev6 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) can be used to force an eeprom reset. After flashing this image, flash your normal firmware again which should restore your keyboard to _normal_ working order.
[Preonic rev3 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

If bootmagic is enabled in any form, you should be able to do this too (see [Bootmagic docs](feature_bootmagic.md) and keyboard info for specifics on how to do this).
