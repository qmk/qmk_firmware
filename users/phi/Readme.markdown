# zk-phi userspace
## `process_record_keymap`

`phi.c` in the userspace reserves `process_record_user`. You can use `process_record_keymap` for per-keymap customizations instead.

## Common configurations

Common configurations such as `TAPPING_TERM`, `TAPPING_FORCE_HOLD`, `PERMISSIVE_HOLD` are automatically applied to `phi` keymaps.

See `config.h` for details.

## HSV dump utility

Add a keycode to dump the current RGB Matrix's HSV value.

### Usage

Add `HSVDUMP` to `rules.mk` and in your `process_record_user` function, call `process_hsvdump`.

```c
switch (keycode) {
  KC_DUMP:
    return process_hsvdump(record);
}
```
