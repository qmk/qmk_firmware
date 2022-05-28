# QMK for my broken Planck

After my Planck keyboard was exposed to a static shock the third row starting from the `n` key (QWERTY layout) started to activate multiple key presses at once

Other users report about the same issue with their Planck keyboards:

- [Reddit example 1](https://www.reddit.com/r/olkb/comments/eqjpdl/need_help_troubleshooting_planck_rev_6/)
- [Reddit example 2](https://www.reddit.com/r/olkb/comments/hgc2by/help_planck_rev6_registering_multiple_columns_for/)
- [QMK issue 8610](https://github.com/qmk/qmk_firmware/issues/8610)

The issue seems to be coming from a combination of a hardware issue plus a change made to the QMK firmware to [add dip switch as a core feature](https://github.com/qmk/qmk_firmware/pull/6140)

## Resolution

To continue using my keyboard I performed the following actions:

- revert everything back to commit [`9f46606dff2f52f31c6c36a63035cfb75824276a`](https://github.com/qmk/qmk_firmware/commit/9f46606dff2f52f31c6c36a63035cfb75824276a)
- removed the `inline` keyword from `tmk_core/common/mousekey.c` (line 26)
- add my own keymap under `keyboards/planck/keymaps/theblob42/`

Now I can build and flash my keymap with the following command:

```shell
sudo make CFLAGS=-Wno-error=deprecated planck/rev6:theblob42:flash
```

> The keyboard needs to be in DFU mode for the flash to work (omit `:flash` to just build the firmware)

## Troubleshooting

### Git Submodules

If you see the following warning:

```text
WARNING:
 Some git sub-modules are out of date or modified, please consider running:
 make git-submodule
 You can ignore this warning if you are not compiling any ChibiOS keyboards,
 or if you have modified the ChibiOS libraries yourself.
```

Execute `make git-submodule` in the project directory to fix it

### Dependencies

Another error you might encounter if you don't have all needed dependencies installed:

```text
/bin/sh: 1: arm-none-eabi-gcc: not found
sh: 1: arm-none-eabi-gcc: not found
sh: 1: arm-none-eabi-gcc: not found
```

To install all the needed/missing dependencies use the `util/qmk_install.sh` script

## References

- [QMK](https://github.com/qmk/qmk_firmware)
- [OLKB](https://olkb.com/)
