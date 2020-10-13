# Frequently Asked Build Questions

This page covers questions about building QMK. If you haven't yet done so, you should read the [Build Environment Setup](getting_started_build_tools.md) and [Make Instructions](getting_started_make_guide.md) guides.

## Can't Program on Linux
You will need proper permissions to operate a device. For Linux users, see the instructions regarding `udev` rules, below. If you have issues with `udev`, a work-around is to use the `sudo` command. If you are not familiar with this command, check its manual with `man sudo` or [see this webpage](https://linux.die.net/man/8/sudo).

An example of using `sudo`, when your controller is ATMega32u4:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

or just:

    $ sudo make <keyboard>:<keymap>:flash

Note that running `make` with `sudo` is generally ***not*** a good idea, and you should use one of the former methods, if possible.

### Linux `udev` Rules

On Linux, you'll need proper privileges to communicate with the bootloader device. You can either use `sudo` when flashing firmware, or place this file in `/etc/udev/rules.d/`:

**/etc/udev/rules.d/50-qmk.rules:**
```
# Atmel DFU
### ATmega16U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03EB", ATTRS{idProduct}=="2FEF", TAG+="uaccess", RUN{builtin}+="uaccess"
### ATmega32U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03EB", ATTRS{idProduct}=="2FF0", TAG+="uaccess", RUN{builtin}+="uaccess"
### ATmega16U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03EB", ATTRS{idProduct}=="2FF3", TAG+="uaccess", RUN{builtin}+="uaccess"
### ATmega32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03EB", ATTRS{idProduct}=="2FF4", TAG+="uaccess", RUN{builtin}+="uaccess"
### AT90USB64
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03EB", ATTRS{idProduct}=="2FF9", TAG+="uaccess", RUN{builtin}+="uaccess"
### AT90USB128
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03EB", ATTRS{idProduct}=="2FFB", TAG+="uaccess", RUN{builtin}+="uaccess"

# Input Club
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1C11", ATTRS{idProduct}=="B007", TAG+="uaccess", RUN{builtin}+="uaccess"

# STM32duino
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1EAF", ATTRS{idProduct}=="0003", TAG+="uaccess", RUN{builtin}+="uaccess"
# STM32 DFU
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="DF11", TAG+="uaccess", RUN{builtin}+="uaccess"

# BootloadHID
SUBSYSTEMS=="usb", ATTRS{idVendor}=="16C0", ATTRS{idProduct}=="05DF", TAG+="uaccess", RUN{builtin}+="uaccess"

# USBAspLoader
SUBSYSTEMS=="usb", ATTRS{idVendor}=="16C0", ATTRS{idProduct}=="05DC", TAG+="uaccess", RUN{builtin}+="uaccess"

# ModemManager should ignore the following devices
# Atmel SAM-BA (Massdrop)
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03EB", ATTRS{idProduct}=="6124", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"

# Caterina (Pro Micro)
## Spark Fun Electronics
### Pro Micro 3V3/8MHz
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1B4F", ATTRS{idProduct}=="9203", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
### Pro Micro 5V/16MHz
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1B4F", ATTRS{idProduct}=="9205", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
### LilyPad 3V3/8MHz (and some Pro Micro clones)
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1B4F", ATTRS{idProduct}=="9207", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
## Pololu Electronics
### A-Star 32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1FFB", ATTRS{idProduct}=="0101", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
## Arduino SA
### Leonardo
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0036", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
### Micro
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0037", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
## Adafruit Industries LLC
### Feather 32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="239A", ATTRS{idProduct}=="000C", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
### ItsyBitsy 32U4 3V3/8MHz
SUBSYSTEMS=="usb", ATTRS{idVendor}=="239A", ATTRS{idProduct}=="000D", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
### ItsyBitsy 32U4 5V/16MHz
SUBSYSTEMS=="usb", ATTRS{idVendor}=="239A", ATTRS{idProduct}=="000E", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
## dog hunter AG
### Leonardo
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2A03", ATTRS{idProduct}=="0036", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
### Micro
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2A03", ATTRS{idProduct}=="0037", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
```

Once added, run the following:

```
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**Note:** With older versions of ModemManager (< 1.12), filtering only works when not in strict mode. The following commands can update that setting:

```
printf '[Service]\nExecStart=\nExecStart=/usr/sbin/ModemManager --filter-policy=default' | sudo tee /etc/systemd/system/ModemManager.service.d/policy.conf
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
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

### I just flashed my keyboard and it does nothing/keypresses don't register - it's also ARM (rev6 planck, clueboard 60, hs60v2, etc...) (Feb 2019)
Due to how EEPROM works on ARM based chips, saved settings may no longer be valid.  This affects the default layers, and *may*, under certain circumstances we are still figuring out, make the keyboard unusable.  Resetting the EEPROM will correct this.

[Planck rev6 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) can be used to force an eeprom reset. After flashing this image, flash your normal firmware again which should restore your keyboard to _normal_ working order.
[Preonic rev3 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

If bootmagic is enabled in any form, you should be able to do this too (see [Bootmagic docs](feature_bootmagic.md) and keyboard info for specifics on how to do this).
