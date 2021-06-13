# QMK for my broken Planck

After my Planck keyboard was exposed to a static shock the third row starting from the `N` key (QWERTY layout) started to activate multiple key presses at once.

Other users report about the same issue with their Planck keyboards:

- https://www.reddit.com/r/olkb/comments/eqjpdl/need_help_troubleshooting_planck_rev_6/
- https://www.reddit.com/r/olkb/comments/hgc2by/help_planck_rev6_registering_multiple_columns_for/
- https://github.com/qmk/qmk_firmware/issues/8610

The issue seems to be coming from a combination of a hardware issue plus a change made to the QMK firmware to [add dip switch as a core feature](https://github.com/qmk/qmk_firmware/pull/6140).

## Resolution

To continue using my keyboard I performed the following actions:

- revert everything back to commit `9f46606dff2f52f31c6c36a63035cfb75824276a`
- removed the `inline` keyword from `tmk_core/common/mousekey.c` (line 26)
- add my own keymap under `keyboards/planck/keymaps/theblob42/`

Now I can build and flash my keymap with the following command:

```shell
sudo make CFLAGS=-Wno-error=deprecated planck/rev6:theblob42:flash
```

> You might need to execute `make git-submodule` first
>
> The keyboard needs to be in DFU mode for the flash to work (omit `:flash` to just built the firmware)

## References

- [QMK](https://github.com/qmk/qmk_firmware)
- [OLKB](https://olkb.com/)
