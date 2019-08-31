# QMK User Configuration for [ninjonas](https://github.com/ninjonas/qmk-yonas)
Tired of copying and pasting the same macros and tap dances for all my keymaps. Utilizing user keymaps functionality.
See: https://docs.qmk.fm/#/feature_userspace

## [ninjonas.c](ninjonas.c)
- ninjonas [QMK user configuration](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_userspace.md)
- On `keymap.c` include `ninjonas.h`
  ```c
  #include "ninjonas.h"     
  ```

## Features
### [Keys](ninjonas.h#L44)
|Code | Description |
|---|---|
|K_LOCK | MacOS shortcut to execute lock command  + ctrl + Q |
|K_CSCN | MacOS shortcut to copy a portion of the screen to the clipboard |

### [Layers](ninjonas.h#L48)
|Code | Description |
|---|---|
|LT_LOW | Tap for ENTER, hold for RAISE |
|LT_FUNC | Tap for ENTER, hold for FUNCTIONS |
|LT_RAI | Tap for SPACE, hold for LOWER |
|LT_NUM | Tap for SPACE, hold for NUMBERS |
|LT_LOW + LT_RAI | Hold for ADJUST  |
|L_LOWER | Dedicated key to momentarily toggle to use LOWER layer |

### [Layout Blocks](ninjonas.h#L57)
Predefined keyboard layout templates to speed up configuring split keyboards

|Code | Description |
|---|---|
|QWERTY | Qwerty Layout |
|DVORAK | Dvorak Layout |
|COLEMAK | Colemak Layout |
|NUM | Number Rows |
|FUNC | Function Rows |
|SYM | Symbol Rows \(When holding shift on numbers\) |
|NAV | Navigation Cluster |
|MOUSE | Mouse Cluster |
|MEDIA | Media Cluster |
|MOD | Modifier Cluster |

### [Macros](process_records.c)
|Code | Description |
|---|---|
|M_PYNV | macro to activate pyenv with the name `jira` |
|M_MAKE | macro to send QMK make command to compile keyboard |
|M_FLSH | macro to send QMK make command to compile keyboard with the correct bootloader |
|M_VRSN | macro to send QMK version |
|M_SHFT | Sends  + alt + shift to a keycode to activate [ShiftIt](https://github.com/fikovnik/ShiftIt) |
|M_CODE | Opens [Visual Studio Code](https://code.visualstudio.com/) on current directory |

### [Tap-Dance](tap_dances.h)
|Code | Description |
|---|---|
|T_ESC | Tap once for ESC, double tap for CAPS_LOCK |
|T_LBRC | Tap once for [, double for back browser |
|T_RBRC | Tap once for ], double for forward browser |
|T_TAB | Tap once for TAB, double for CTRL + TAB |
|T_GRV | Tap once for GRV, double for  + GRV |
|T_GUI | Tap once for , double to open spotlight |
|T_W | Tap for W, double tap for  + W |
|T_Q | Tap for Q, double tap for  + Q |

### Secrets
There's times where you have macros you don't want to share like emails, passwords 😱, & and private strings. Based off [drashna's secret macros](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme_secrets.md), it's now possible to do this. All you need to do is create a `secrets.c` file. Below is an example of how this is used.

```c
// secrets.c
#include "ninjonas.h" 

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Sends zoom URL
    case M_ZOOM:
      if (record->event.pressed) {
        SEND_STRING("SECRET_STRING_HERE" SS_TAP(X_ENTER));
      }
      break;
  }
  return true;
}
```