# QMK User Configuration for snowkuma
Moving from one type of keyboard to 2 (planck to crkbd) I felt it made sense to start utilizing user keymaps.  
Building on [ninjonas](github.com/ninjonas/qmk-yonas) and [drashna](github.com/drashna) approaches.

See: https://docs.qmk.fm/#/feature_userspace

### Layout Blocks
Predefined keyboard layout templates to speed up configuring keyboards

|Code | Description |
|---|---|
|COLEMAK | Colemak Layout |
|NAV | Navigation |
|SYMBOL | Symbol |
|NUMBER | Numpad layout and one hand shortcuts |
|ARRANGE | Window Layout shortcuts (using Magnet) |
|MOUSE | Mouse layer |
|THUMB | Thumb shortcuts |
|FUNCTION | Function key layer |

### Secrets
There's times where you have macros you don't want to share like emails, an address you need but you always forget, passwords 😱, & and private strings. Based off [drashna's secret macros](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme_secrets.md), it's now possible to do this. All you need to do is create a `secrets.c` file. Below is an example of how this is used.

```c
// secrets.c
#include "snowkuma.h"

static const char * const secret[] = {
  "BLANK1",
  "BLANK2",
  "BLANK3",
  "BLANK4",
  "BLANK5"
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_XXX1...M_XXX5:
      if (record->event.pressed) {
        send_string(secret[keycode - M_XXX1]);
      }
      break;
  }
  return true;
}

```