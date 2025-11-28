#  Bridge75
The Bridge75 is based on a Westberry Tech WB32FQ95 MCU in a LQFP64 package
and can be programmed with wb32-dfu. The keyboard uses a WCH CH582F chip
to provide wireless connectivity. The wireless code is in userspace to avoid
causing any issues or support burden on the main QMK code base.

## Flashing a new firmware
Hold ESCAPE [0,0] to enter bootloader mode while inserting the USB cable into
the keyboard. Then run the following to flash the firmware.
```shell
qmk flash -kb shortcut/bridge75/ansi -km default
```
