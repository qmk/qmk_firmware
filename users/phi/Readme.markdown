# zk-phi userspace
## Common configurations

Common configurations such as `TAPPING_TERM`, `TAPPING_FORCE_HOLD`, `PERMISSIVE_HOLD` are automatically applied to `phi` keymaps.

See `config.h` for details.

## Custom mousekey accelaration

You may configure wheel speen and cursor speed separately.

### Usage

Include `mousekey_accel.h` from `keymap.c` and call `process_mousekey_accel` in `process_record_user`.

```c
#ifdef MOUSEKEY_ENABLE
#    include "mousekey_accel.h"
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   ....
#    ifdef MOUSEKEY_ENABLE
    if (!process_mousekey_accel(keycode, record)) {
        return false;
    }
#    endif
 ...
    return true;
}
```

Only `KC_MS_ACCEL0` is supported among the `KC_MS_ACCEL*` keycodes.

### Per-board settings

Default settings (somewhat like karabiner) are provided, but you can also apply some keyboard-specifig settings.

```c
#define MOUSEKEY_DELAY             48
#define MOUSEKEY_INTERVAL          24
#define MOUSEKEY_MOVE_DELTA        3
#define MOUSEKEY_MAX_SPEED         11
#define MOUSEKEY_TIME_TO_MAX       10

#define MOUSEKEY_WHEEL_DELAY       72
#define MOUSEKEY_WHEEL_INTERVAL    72
#define MOUSEKEY_WHEEL_DELTA       1
#define MOUSEKEY_WHEEL_MAX_SPEED   1
#define MOUSEKEY_WHEEL_TIME_TO_MAX 1

#define MOUSEKEY_ACL_MAX_SPEED 16
#define MOUSEKEY_ACL_WHEEL_MAX_SPEED 4
```

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

You can also get whether shift is locked (by tapping more twice) or not, via `shift_holded` external variable. This may be useful to indicate the status with OLEDs or LEDs.

```c
rgblight_setrgb_at(shift_holded ? 255 : 0, 0, 0, 0);
```
