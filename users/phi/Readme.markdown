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

## Enhanced shift key

- HOLD or INTERRUPT -> works normally as a shift key
- TAP -> next input will be capitalized (sticky shift)
- DOUBLE TAP -> shift locked (tap again to unlock)

### Usage

Enable `ENHANCED_SHIFT` (this also enables `TAPDANCE_ENABLE`),

```mk
ENHANCED_SHIFT = yes
```

include `enhanced_shift.h`,

```c
#include "enhanced_shift.h"
```

and add `ACTION_ENHANCED_SHIFT` to `tap_dance_actions` in your `keymap.c`.

```c
#define KC_ESFT TD(0)

qk_tap_dance_action_t tap_dance_actions[] = {
    ACTION_ENHANCED_SHIFT,
    ....
};
```

You can also get whether shift is locked (by tapping more twice) or not, via `shift_held` external variable. This may be useful to indicate the status with OLEDs or LEDs.

```c
rgblight_setrgb_at(shift_held ? 255 : 0, 0, 0, 0);
```
