# dlip's Gamepad

Gamepad config for use in fighting games. Forked from https://github.com/brentaro/QMK_HID_Gamepad_with_SOCD

## Usage in keymap

- Add to `config.h`

```c
// Joystick Button Count
#define JOYSTICK_BUTTON_COUNT 32

// Joystick Axes Count
#define JOYSTICK_AXIS_COUNT 6

// Joystick Axes Resolution
#define JOYSTICK_AXIS_RESOLUTION 8
```

- Add to `rules.mk`

```
# Enable Joystick
JOYSTICK_ENABLE = yes

JOYSTICK_DRIVER = digital
```

Add to `keymap.c`:

- Include `gamepad.h`

```c
#include "users/dlip/gamepad.h"
```

- Add `_GAMEPAD` to your layers eg.

```c
enum layers {
  _BASE
  _GAMEPAD,
};
```

- Add layer to your `keymaps` with `GP_*` key mappings eg.

```c
    [_GAMEPAD] = LAYOUT_split_2x4_2(
        XXXXXXX,     GP_BCK,    GP_DPU,        GP_STA,          GP_X,       GP_Y,        GP_RB,     GP_LB,
        GP_HOM,      GP_DPL,    GP_DPD,        GP_DPR,          GP_A,       GP_B,        GP_RT,     GP_LT,
                                XXXXXXX,       GP_DPU,          GP_LSB,     GP_RSB
    ),
```

- Add a layer switch key to your base layer eg. `TO(_GAMEPAD)`
- Add taipo calls in `process_record_user` eg.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(_GAMEPAD)) {
        return gamepad_process_record_user(keycode, record);
    }  else {
        return true;
    }
};
```