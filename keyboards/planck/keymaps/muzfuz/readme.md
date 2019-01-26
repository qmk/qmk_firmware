# The muzfuz Planck Layout

```shell
docker run -e KEYMAP=muzfuz -e KEYBOARD=planck --rm -v $('pwd'):/qmk:rw qmk_firmware
dfu-programmer atmega32u4 erase
dfu-programmer atmega32u4 flash .build/planck_rev6_muzfuz.hex
dfu-programmer atmega32u4 launch
```
