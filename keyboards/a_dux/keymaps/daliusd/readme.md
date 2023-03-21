# My 34 keys layout

This is my principles for layout:

* I am using Callum style layout. Here you can read explanation by
  Callum himself and his reasoning for not using mod-tap:
  [here](../../../../users/callum/readme.md)

* There should be only one way to type key. Key can be on
  different layer but it must maintain its physical location. I
  broke this rule for Shift key only.

* The less features are used the better.

* There is simple TMUX layer.

* Common keys must be accessible using two keys if possible.

* It should be possible to work with left keyboard side and mouse
  in right hand without lifting hands for some scenarios (that's
  why I had to duplicate Shift key).

## Improvements over Callum

* I have added one shot layers compatible with Callum's one shot
  keys.

* There is one issue with accidental uppercase characters fixed
  that exists in original Callum layout's implementation.

* Another annoying feature of Callum layer is one shot keys are
  frozen until you cancel them. This is problem when you use one
  hand for keyboard and another for mouse. E.g. you click Ctrl and
  mouse to get some menu (on Mac OS X), and then you want to click
  some item in that menu. You have to remember to cancel one shot in such
  situation. I have added two settings two handle situations like
  this:

  * `FLOW_ONESHOT_WAIT_TERM` - if hold one shot key longer than
    `FLOW_ONESHOT_WAIT_TERM` ms then mod key / layer key is not
    treated as one shot key (defaults to 500ms).

  * `FLOW_ONESHOT_TERM` - if you do not click another key in
  `FLOW_ONESHOT_TERM` ms then one shot key / layer key is treated
  as normal key. Therefore if you lift it after `FLOW_ONESHOT_TERM`
  it will not be treated as one shot (defaults to 500ms).

  After adding those two settings I have found out that I don't
  need one shot cancel key anymore so I have removed it.

Since differences are significant I named this layout `flow`.

## Using flow with your keyboard

Copy `flow.c` and `flow.h` to keyboard folder.

Add following line to `rules.mk`:

```make
SRC += flow.c
```

Define following in `config.h` for modifiers and layers:

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
// * modifier keycode
const uint16_t flow_config[FLOW_COUNT][2] = {
    {L_NAV, KC_LALT},
    {L_NAV, KC_LGUI},
    {L_NAV, KC_LCTL},
    {L_NAV, KC_LSFT},
    {L_SYM, KC_LCTL},
    {L_SYM, KC_LGUI},
    {L_SYM, KC_LALT},
};


// for layers configuration follow this format:
// * custom layer key
// * layer name
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

## Lithuanian letters

There are at least two ways how to enter Lithuanian letters: to
use Unicode support from QMK or to switch OS language when
necessary. Unicode support has some problems:

* it is OS specific (you need to change Unicode input mode based
  on your OS and I sometimes switch between Mac OS X and Ubuntu).
  This is minor issue but it is still issue.

* There is bug in Mac OS X and I can't enter `Š` using unicode
  input method.

* Unicode Hex Input in Mac OS X is not perfect and there are some
  minor issue while using it.

On Linux Unicode support meanwhile works perfectly.

This leaves us with other option to use OS language switching as
you most probably have done before. Still there is space for
improvement. E.g. I have added Lithuanian letters to trilayer and
trilayer activation toggles OS language (this works because I use
only two languages). Check `layer_state_set_user` implementation
for details.

# Rejected ideas

## Mods as combos

Sometimes when I press `NAV (layer key) + S + Tab` to get `Command
+ Tab` I ended up with `S + Nav + Tab`. This happened because I
did that really fast and sometimes clicked S slightly earlier than
NAV layer key. Initially I have solved this problem using Combo
keys, but that's additional dependency and combo keys are not
ideal for Callum layer. You need to release both keys to trigger
Combo key release. Therefore I have written custom code that
allows pressing S some milliseconds earlier. This is controlled by
FLOW_TERM and defaults to 10. I do not recommend setting this to
higher than 30.

This idea was rejected because it looks like 10ms did not made
that big difference.

## Swapper

Idea of swapper is to have key that registers Mode key (e.g.
Command while layer and some key is pressed) to simulate two key
combo, e.g. Command + Tab. Overall I found that 3 keys combo that
I have currently for swapping windows is equally good as 2 keys
swapper. Another problem with swapper is that it is OS specific.
Still if you want here is swapper implementation I have used:

```c
bool active;

void update_swapper(
    uint16_t trigger,
    uint16_t keycode,
    bool pressed
) {
    if (keycode == trigger) {
        if (pressed) {
            if (!active) {
                active = true;
                register_code(KC_LGUI);
            }
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
    } else if (active && keycode != KC_LSFT && keycode != KC_LEFT && keycode != KC_RIGHT) {
        unregister_code(KC_LGUI);
        active = false;
    }
}
```

## Combos

I have seen that some people use two letter horizontal combos for
some actions, e.g. XC for Command+C, CV for Command+V, JK for ESC
and etc. I found that this kind of kicks me out of the flow when
working as it requires different kind of action and I need to
pause to make that action.

## Comma-space

I have noticed that I put space after comma `,` usually. That
means I can use comma + letter for something else with backspace,
e.g. for Lithuanian letters. Performance wise that works OK, but
practically that does not feel really good. Trilayer with language
layer switch works better.

Still if you are interested here is comma-space implementation:

```c
void swap_layout(void) {
    uint8_t saved_mods = get_mods();
    clear_mods();
    tap_code16(LCTL(KC_SPC));
    set_mods(saved_mods);
}

void press_with_layout_swap(uint16_t keycode) {
    tap_code16(KC_BSPC);
    swap_layout();
    tap_code16(keycode);
    swap_layout();
}

bool comma_pressed = false;

bool update_commaspace(
    uint16_t keycode,
    bool pressed
) {
    if (keycode == KC_COMM) {
        if (!(get_mods() & MOD_MASK_SHIFT)) {
            comma_pressed = true;
        }
    } else if (comma_pressed) {
        if (keycode != KC_LSFT) {
            comma_pressed = false;
        }

        switch(keycode) {
            case KC_Q:
                if (pressed) {
                    press_with_layout_swap(KC_1);
                    return false;
                }
                break;
            case KC_W:
                if (pressed) {
                    press_with_layout_swap(KC_2);
                    return false;
                }
                break;
            case KC_E:
                if (pressed) {
                    press_with_layout_swap(KC_3);
                    return false;
                }
                break;
            case KC_R:
                if (pressed) {
                    press_with_layout_swap(KC_4);
                    return false;
                }
                break;
            case KC_T:
                if (pressed) {
                    press_with_layout_swap(KC_5);
                    return false;
                }
                break;
            case KC_Y:
                if (pressed) {
                    press_with_layout_swap(KC_6);
                    return false;
                }
                break;
            case KC_U:
                if (pressed) {
                    press_with_layout_swap(KC_7);
                    return false;
                }
                break;
            case KC_I:
                if (pressed) {
                    press_with_layout_swap(KC_8);
                    return false;
                }
                break;
            case KC_O:
                if (pressed) {
                    press_with_layout_swap(KC_EQL);
                    return false;
                }
                break;
        }
    }

    return true;
};
```

## Using one shot layers on top layer keys (NAV and SYM)

While this looked promising and fun it was really easy to get lost
in which layer you actually are. You can still use it as `flow`
supports this scenario, but I do not recommend it.
