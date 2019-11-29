# zk-phi userspace
## `process_record_keymap`

`phi.c` in the userspace reserves `process_record_user`, instead you can use `process_record_keymap` for per-keymap customizations.

## Common configurations

Common configurations such as `TAPPING_TERM`, `TAPPING_FORCE_HOLD`, `PERMISSIVE_HOLD` are automatically applied to `phi` keymaps.

See `config.h` for details.

## Custom mousekey accelaration

Enables customized version of mousekeys. Wheel and cursor speed are configured independently (in a bit hack-y way).

### Usage

Add `CUSTOM_MOUSEKEY` to `rules.mk` (this also enables `MOUSEKEY_ENABLE`).

```mk
CUSTOM_MOUSEKEY = yes
```

Note that `KC_MS_ACCEL0` is the only supported keycode among the `KC_MS_ACCEL*` keycodes.

### Per-board settings

Default configuration (somewhat like karabiner) is provided, but you can also apply some keyboard-specifig modifications.

```c
#undef MOUSEKEY_WHHEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 2
```

See `custom_mousekey.h` for available options.

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
