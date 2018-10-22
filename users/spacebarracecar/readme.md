# SpacebarRacecar Userspace

The main purpose of this userspace is to keep my personal keymaps clean by moving shared code in here and allowing me to easily change all my keymaps at once. However it also contains code that might be interesting to QMK Users living in Germany. Most of this code will be explained here.


## US Layout Keys for German PCs

I'm using the US Ansi layout however I'm living in Germany which means that every PC here has its input language set to German. My goal was to create custom keycodes that emulate the US Keys so that I can use my keyboards on any German PC without changing any settings.

The custom keycodes are defined in spacebarracecar.h in `enum userspace_custom_keycodes`. To activate them GERMAN_ENABLE = yes has to be set in the keyboards rules.mk file. The keycodes are handled in the `process_record_user` function which is now located in spacebarracecar.c. To change keyboard specific configuration `process_record_keymap` is used (see drashna userspace readme for better explanation).

### How it works

Creating the custom keycodes is not a trivial task because it is necessary that they can send different keycodes depending on the physical shift state. Also the shift state of the actual send keycodes has to be completely independent of the physical shift state. At the same time it has to be ensured that shift never gets stuck or disabled accidentaly.

Here is an example for a custom **US Equal =** keycode that illustrates the problem:

| Shift State | Custom keycode | Actual send keycodes |
|-------------|----------------|----------------------|
| Unshifted   | =              | Shifted DE_0         |
| Shifted     | +              | Unshifted DE_PLUS    |

#### Tracking the physical shift state

To track the physical shift state there are two custom left and right shift keycodes `CU_LSFT` and `CU_RSFT`. These track the current physical shift state using two booleans `lshift` and `rshift`. To make things easier both custom shifts use KC_LSFT. A space cadet shift functionality is also included. The preexisting space cadet shift implementation could not be used because it doesn't reset when custom keycodes are pressed and therefore produces unwated parenthesis. 

#### Custom keycode templates

To ease the creation of custom keycodes there are a few templates defined in spacebarracecar.h.

`SHIFT_NORM(kc1, kc2)` Sends independent keycodes depending on physical shift state without changing shift state.
`SHIFT_SWITCH(kc1, kc2)` Sends independent keycodes depending on physical shift state while flipping shift state.
`SHIFT_ALL(kc1, kc2)` Sends independent keycodes depending on physical shift state while always sending shift.
`SHIFT_NO(kc1, kc2)` Sends independent keycodes depending on physical shift state while never sending shift.
`SHIFT_ALGR(kc1, kc2)` Sends independent keycodes depending on physical shift state while never sending shift and always sending ralt.

Example:
```c
#define SHIFT_NORM(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    register_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} \
return false;
```

It is noticeable that before registering a keycode the same keycode gets unregistered first. The reason for this is that there can now be two physical keys that use the same keycode with different shift states. When rolling those two keys the keycode has to be unregistered first, otherwise the second key doesn't register. Also noticable is that sometimes the `add_to_prev` function is called. This will be explained later. The `timer_timeout` function is necessary for the custom space cadet shift.

It's worth mentioning that SHIFT_ALGR unlike the other templates doesn't allow repetition of characters when held. This is because it would otherwise require extensive checking of physical ralt status similar to shift to prevent ralt from getting stuck.

####Ensuring that shift state is always correct when pressing normal keycodes

To ensure that non custom keycodes always get send with the right shift state the default case in the `process_record_user` function includes a physical shift check that sets shift accordingly.

```c
default:
    if(record->event.pressed) {
      timer_timeout();

      #ifdef GERMAN_ENABLE
      if (lshift || rshift)
        register_code(KC_LSFT);
      else
        unregister_code(KC_LSFT);
      #endif

    }
    return process_record_keymap(keycode, record);
```

####Ensuring that custom keycodes always produce the correct character

When very specific key combinations that include custom keycodes are pressed it can happen that wrong characters are produced due to changing shift states. The previously mentioned `add_to_prev` function is there to prevent that. It can be used to add a keycode to the `prev_kcs` array that can hold up to 6 keycodes. On various occasions, but mainly when shift is released `unreg_prev` is called, which then unregisters all saved keycodes.

For real use this is probably not needed, but I implemented it anyway.

#### Adapting the templates for other languages

In theory the templates can be used to create custom keycodes that map any layout to any other layout.
