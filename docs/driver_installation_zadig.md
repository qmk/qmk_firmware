# Bootloader Driver Installation with Zadig

QMK presents itself to the host as a regular HID keyboard device, and as such requires no special drivers. However, in order to flash your keyboard on Windows, the bootloader device that appears when you reset the board often *does*.

There are two notable exceptions: the Caterina bootloader, usually seen on Pro Micros, and the HalfKay bootloader shipped with PJRC Teensys, appear as a serial port and a generic HID device respectively, and so do not require a driver.

We recommend the use of the [Zadig](https://zadig.akeo.ie/) utility. If you have set up the development environment with MSYS2, the `qmk_install.sh` script will have already installed the drivers for you.

## Installation

Put your keyboard into bootloader mode, either by hitting the `RESET` keycode (which may be on a different layer), or by pressing the reset switch that's usually located on the underside of the board. If your keyboard has neither, try holding Escape or Space+`B` as you plug it in (see the [Bootmagic Lite](feature_bootmagic.md) docs for more details). Some boards use [Command](feature_command.md) instead of Bootmagic; in this case, you can enter bootloader mode by hitting Left Shift+Right Shift+`B` or Left Shift+Right Shift+Escape at any point while the keyboard is plugged in.
Some keyboards may have specific instructions for entering the bootloader. For example, the [Bootmagic Lite](feature_bootmagic.md) key (default: Escape) might be on a different key, e.g. Left Control; or the magic combination for Command (default: Left Shift+Right Shift) might require you to hold something else, e.g. Left Control+Right Control. Refer to the board's README file if you are unsure.

To put a device in bootloader mode with USBaspLoader, tap the `RESET` button while holding down the `BOOT` button.
Alternatively, hold `BOOT` while inserting the USB cable.

Zadig should automatically detect the bootloader device, but you may sometimes need to check **Options → List All Devices** and select the device from the dropdown instead.

!> If Zadig lists one or more devices with the `HidUsb` driver, your keyboard is probably not in bootloader mode. The arrow will be colored orange and you will be asked to confirm modifying a system driver. **Do not** proceed if this is the case!

If the arrow appears green, select the driver, and click **Install Driver**. See the [list of known bootloaders](#list-of-known-bootloaders) for the correct driver to install.

![Zadig with a bootloader driver correctly installed](https://i.imgur.com/b8VgXzx.png)

Finally, unplug and replug the keyboard to make sure the new driver has been loaded. If you are using the QMK Toolbox to flash, exit and restart it too, as it can sometimes fail to recognize the driver change.

## Recovering from Installation to Wrong Device

If you find that you can no longer type with the keyboard, you may have accidentally replaced the driver for the keyboard itself instead of for the bootloader. This can happen when the keyboard is not in the bootloader mode. You can easily confirm this in Zadig - a healthy keyboard has the `HidUsb` driver installed on all of its interfaces:

![A healthy keyboard as seen by Zadig](https://i.imgur.com/Hx0E5kC.png)

Open the Device Manager, select **View → Devices by container**, and look for an entry with your keyboard's name.

![The board with the wrong driver installed, in Device Manager](https://i.imgur.com/o7WLvBl.png)

Right-click each entry and hit **Uninstall device**. Make sure to tick **Delete the driver software for this device** first if it appears.

![The Device Uninstall dialog, with the "delete driver" checkbox ticked](https://i.imgur.com/aEs2RuA.png)

Click **Action → Scan for hardware changes**. At this point, you should be able to type again. Double check in Zadig that the keyboard device(s) are using the `HidUsb` driver. If so, you're all done, and your board should be functional again! Otherwise, repeat this process until Zadig reports the correct driver.

?> A full reboot of your computer may sometimes be necessary at this point, to get Windows to pick up the new driver.

## Uninstallation

Uninstallation of bootloader devices is a little more involved than installation.

Open the Device Manager, select **View → Devices by container**, and look for the bootloader device. Match up the USB VID and PID in Zadig with one from [the table below](#list-of-known-bootloaders).

Find the `Inf name` value in the Details tab of the device properties. This should generally be something like `oemXX.inf`:

![Device properties showing the Inf name value](https://i.imgur.com/Bu4mk9m.png)

Then, open a new Command Prompt window as an Administrator (type in `cmd` into the Start menu and press Ctrl+Shift+Enter). Run `pnputil /enum-drivers` to verify the `Inf name` matches the `Published Name` field of one of the entries:

![pnputil output with matching driver highlighted](https://i.imgur.com/3RrSjzW.png)

Run `pnputil /delete-driver oemXX.inf /uninstall`. This will delete the driver and remove it from any devices using it. Note that this will not uninstall the device itself.

As with the previous section, this process may need to be repeated multiple times, as multiple drivers can be applicable to the same device.

!> **WARNING:** Be *extremely careful* when doing this! You could potentially uninstall the driver for some other critical device. If you are unsure, double check the output of `/enum-drivers`, and omit the `/uninstall` flag when running `/delete-driver`.

## List of Known Bootloaders

This is a list of known bootloader devices and their USB vendor and product IDs, as well as the correct driver to assign for flashing with QMK. Note that the usbser and HidUsb drivers are built in to Windows, and cannot be assigned with Zadig - if your device has an incorrect driver, you must use the Device Manager to uninstall it as described in the previous section.

The device name here is the name that appears in Zadig, and may not be what the Device Manager or QMK Toolbox displays.

|Bootloader    |Device Name                   |VID/PID       |Driver |
|--------------|------------------------------|--------------|-------|
|`atmel-dfu`   |ATmega16u2 DFU                |`03EB:2FEF`   |libusb0|
|`atmel-dfu`   |ATmega32U2 DFU                |`03EB:2FF0`   |libusb0|
|`atmel-dfu`   |ATm16U4 DFU V1.0.2            |`03EB:2FF3`   |libusb0|
|`atmel-dfu`   |ATm32U4DFU                    |`03EB:2FF4`   |libusb0|
|`atmel-dfu`   |*none* (AT90USB64)            |`03EB:2FF9`   |libusb0|
|`atmel-dfu`   |AT90USB128 DFU                |`03EB:2FFB`   |libusb0|
|`qmk-dfu`     |(keyboard name) Bootloader    |As `atmel-dfu`|libusb0|
|`halfkay`     |*none*                        |`16C0:0478`   |HidUsb |
|`caterina`    |Pro Micro 3.3V                |`1B4F:9203`   |usbser |
|`caterina`    |Pro Micro 5V                  |`1B4F:9205`   |usbser |
|`caterina`    |LilyPadUSB                    |`1B4F:9207`   |usbser |
|`caterina`    |Pololu A-Star 32U4 Bootloader |`1FFB:0101`   |usbser |
|`caterina`    |Arduino Leonardo              |`2341:0036`   |usbser |
|`caterina`    |Arduino Micro                 |`2341:0037`   |usbser |
|`caterina`    |Adafruit Feather 32u4         |`239A:000C`   |usbser |
|`caterina`    |Adafruit ItsyBitsy 32u4 3V    |`239A:000D`   |usbser |
|`caterina`    |Adafruit ItsyBitsy 32u4 5V    |`239A:000E`   |usbser |
|`caterina`    |Arduino Leonardo              |`2A03:0036`   |usbser |
|`caterina`    |Arduino Micro                 |`2A03:0037`   |usbser |
|`bootloadhid` |HIDBoot                       |`16C0:05DF`   |HidUsb |
|`usbasploader`|USBasp                        |`16C0:05DC`   |libusbK|
|`apm32-dfu`   |APM32 DFU ISP Mode            |`314B:0106`   |WinUSB |
|`stm32-dfu`   |STM32 BOOTLOADER              |`0483:DF11`   |WinUSB |
|`kiibohd`     |Kiibohd DFU Bootloader        |`1C11:B007`   |WinUSB |
|`stm32duino`  |Maple 003                     |`1EAF:0003`   |WinUSB |
|`qmk-hid`     |(keyboard name) Bootloader    |`03EB:2067`   |HidUsb |
