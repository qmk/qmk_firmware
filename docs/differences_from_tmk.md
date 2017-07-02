Understanding the essential changes made on the [tmk_keyboard firmware](http://github.com/tmk/tmk_keyboard) should help you understand the QMK Firmware.

| Firmware                     |TMK                    |QMK                      |
|------------------------------|-----------------------|-------------------------|
| Maintainer                   |hasu  (@tmk)           |Jack Humbert et al.      |
| Build path customization     | `TMK_DIR = ...`       | `include .../Makefile`  |
| `keymaps` array data | 3D array of `uint8_t`  holding **keycode**      | 3D array of `uint16_t` holding **keycode**  |
