# My 34 keys layout

This is my principles for layout:

* I am using Callum style layout. Here you can read explanation by
  Callum himself and his reasoning for not using mod-tap:
  [here](../../../../users/callum/readme.md)

* There should be only one way to type key. Key can be on
  different layer but it must maintain its physical location. I
  broke this rule for Shift key only.

* The less features are used the better.

* trilayer is cool.

* There is 🐍 key for no reason.

* There is simple TMUX layer.

## Improvements over Callum

* I have added one shot layers compatible with Callum's one shot
  keys.

* There is one issue with accidental uppercase characters fixed
  that exists in original Callum layout.

* Sometimes when I press `NAV (layer key) + S + Tab` to get
  `Command + Tab` I ended up with `S + Nav + Tab`. This happened
  because I did that really fast and sometimes clicked S slightly
  earlier than NAV layer key. Initially I have solved this problem
  using Combo keys, but that's additional dependency and combo
  keys are not ideal for Callum layer. You need to release both
  keys to trigger Combo key release. Therefore I have written
  custom code that allows pressing S some milliseconds earlier.
  This is controlled by FLOW_TERM and defaults to 10. I do not
  recommend setting this to higher than 30.

* Another annoying feature of Callum layer is one shot keys frozen
  until you cancel them. This is problem when you use one hand for
  keyboard and another for mouse. E.g. you click Ctrl and mouse to
  get some menu, and then you want to click some item in that
  menu. You have to remember to cancel one shot in such
  situation. I have added default 500ms period (can be changed
  using FLOW_ONESHOT_TERM) where you have to press next key.
  Otherwise oneshot is canceled.

Since differences are quite significant I named this `flow`.

NOTE: this is still work in progress and might change in the
future.

## Using flow with your keyboard

Copy `flow.c` and `flow.h` to keyboard folder.

Add following line to `rules.mk`:

```make
SRC += flow.c
```

Define following in `config.h`:

```c
#define FLOW_COUNT 7
#define FLOW_LAYERS_COUNT 3
```

In your `keymap.c` add and configure like this:

```c
#include "flow.h"

...

// flow_config should correspond to following format:
// * layer keycode
// * non-layer keycode
// * modifier keycode that must be triggered when layer and
//   non-layer are pressed
// Note that non-layer keycode must be used both in main layer and layer that
// is turned on by layer keycode
const uint16_t flow_config[FLOW_COUNT][3] = {
    {L_NAV, KC_A, KC_LALT},
    {L_NAV, KC_S, KC_LGUI},
    {L_NAV, KC_D, KC_LCTL},
    {L_NAV, KC_E, KC_LSFT},
    {L_SYM, KC_K, KC_LCTL},
    {L_SYM, KC_L, KC_LGUI},
    {L_SYM, KC_SCLN, KC_LALT},
};

const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_TMUX, _TMUX},
    {OS_MISC, _MISC},
    {OS_FUNC, _FUNC},
};

...

// Add following to handle flow

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;
    return true;
}

void matrix_scan_user(void) {
    flow_matrix_scan();
}

```

## Development

Note that `flow` is covered with tests. You can run tests in two
ways:

* Run `./tests/test.sh` directly

* Install `fswatch` to your system and run `./tests/monitor.sh` in
  separate terminal, tab or tmux pane. Make changes to `flow.c` or
  `./tests/test.c` and see if you have not broken any tests.
