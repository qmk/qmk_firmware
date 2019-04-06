# SpacebarRacecar Userspace

The main purpose of this userspace is to keep my personal keymaps clean by moving shared code in here and also allowing me to easily change all my keymaps at once. However it also contains code that might be interesting to QMK Users living in Germany. Most of this code will be explained here.


## US Layout Keys for German PCs

I'm using the US Ansi layout however I'm living in Germany which means that every PC here has its input language set to German. My goal was to create custom keycodes that emulate the US Keys so that I can plug my keyboards into any German PC and have them working without changing any settings.

### How to use

- To activate the custom keycodes set GERMAN_ENABLE = yes in the keyboards rules.mk file.
- The keycodes are listed and explained in [spacebarracecar.h](spacebarracecar.h) under `enum userspace_custom_keycodes`.
- The keycodes are handled by the `process_record_user` function which is now located in [spacebarracecar.c](spacebarracecar.c). To change keyboard specific configuration `process_record_keymap` is used (see [drashna userspace readme](../drashna/readme.md) for better explanation).
- There is a predefined `_DEADKEY` layer in [spacebarracecar.h](spacebarracecar.h) under `enum userspace_layers`. Shifted CU_QUOT enables the dead key layer, just like KC_QUOT would when using the US International layout. (See `enum userspace_custom_keycodes` for more explanation).
- On Windows grave and circonflexe are defined as dead keys when using the standard german layout. Those are automatically escaped when using the custom keycodes. `CU_ESCT` can be used to enable/disable this behavior.
- For a complete example see my [fc660c](../../keyboards/fc660c/keymaps/spacebarracecar/keymap.c) or [planck](../../keyboards/planck/keymaps/spacebarracecar/keymap.c) keymaps.

### How it works

Creating the custom keycodes was not a trivial task because it is necessary that they are able to send different keycodes depending on the physical shift state. Also the shift state of the actual send keycodes has to be completely independent of the physical shift state. At the same time it has to be ensured that shift never gets stuck or disabled accidentaly.

(Shift state: If shift keycode is registered; Physical shift state: If shift key is actually pressed)

Here is an example for a custom *US Equal* keycode that illustrates the problem:

| Physical Shift State | Custom keycode | Actual send keycodes |
|----------------------|----------------|----------------------|
| Unshifted            | =              | Shifted DE_0         |
| Shifted              | +              | Unshifted DE_PLUS    |

#### Tracking the physical shift state

To track the physical shift state there are two custom left and right shift keycodes `CU_LSFT` and `CU_RSFT`. These track the current physical shift state using two booleans `lshift` and `rshift`. To make things easier both custom shifts use KC_LSFT. A space cadet shift functionality is also included. The preexisting space cadet shift implementation could not be used because it doesn't reset when custom keycodes are pressed and therefore produces unwated parenthesis. 

#### Custom keycode templates

To ease the creation of custom keycodes there are a few templates defined in [spacebarracecar.h](spacebarracecar.h).

- `SHIFT_NORM(kc1, kc2)` Sends independent keycodes kc1 and kc2 depending on physical shift state without changing shift state.
- `SHIFT_SWITCH(kc1, kc2)` Sends independent keycodes kc1 and kc2 depending on physical shift state while flipping shift state.
- `SHIFT_ALL(kc1, kc2)` Sends independent keycodes kc1 and kc2 depending on physical shift state while always sending shift.
- `SHIFT_NO(kc1, kc2)` Sends independent keycodes kc1 and kc2 depending on physical shift state while never sending shift.
- `SHIFT_ALGR(kc1, kc2)` Sends independent keycodes kc1 and kc2 depending on physical shift state while never sending shift and always sending ralt.
- `UML(kc)` Sends keycode kc without changing shift state and then escapes the `_DEADKEY` layer.

Here is `SHIFT_NORM` as an example:
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

It is noticeable that before registering a keycode the same keycode gets unregistered first. The reason for this is that there can now be two physical keys that use the same keycode only with different shift states. When rolling those two keys the keycode has to be unregistered first, otherwise the second key doesn't register. Also noticable is that sometimes the `add_to_prev` function is called. This will be explained later. The `timer_timeout` function is necessary to reset the timers of the custom space cadet shift functionality.

It's worth mentioning that `SHIFT_ALGR` unlike the other templates doesn't allow repetition of characters when held. This is because it would otherwise require extensive checking of physical ralt status similar to shift to prevent ralt from getting stuck.

#### Ensuring that shift state is always correct when pressing normal keycodes

To ensure that non custom keycodes always get send with the correct shift state the default case in `process_record_user` includes a physical shift check that sets shift accordingly before registering the keycode. Also `timer_timeout` is always called to reset the space cadet shift timers to prevent unwanted parenthesis.

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

#### Ensuring that custom keycodes always produce the correct character

When very specific key combinations that include custom keycodes and/or shift are pressed it can happen that wrong characters are produced due to changing shift states. The previously mentioned `add_to_prev` function is there to prevent that. It can be used to add a keycode to the `prev_kcs` array that can hold up to 6 keycodes. On various occasions, but mainly when shift is released `unreg_prev` is called, which then unregisters all saved keycodes.

For real use this is probably not needed, but it doesn't hurt either.

#### Adapting the templates for other languages

In theory the templates can be used to create custom keycodes that map any layout to any other layout.

## Other stuff

### Custom Nav/Esc Key

Since I'm always using a navigation layer with all my keyboards there is a `_NAV` layer predefined in [spacebarracecar.h](spacebarracecar.h) under `enum userspace_layers`. In addition to that I wanted to have a keycode that activates the navigation layer when held, but acts as Escape when pressed. In QMK there already exists `LT(layer, kc)`, however I found that there is some amount of lag before the layer is actived. Therefore I created a custom keycode CU_NAV that does the same without lag using a custom timer. Since I already need timers for the custom space cadet shift implementing this was very easy by adding the timer to the `timer_timeout` function.

### Gamemode

The userspace includes the custom keycode `CU_GAME` that is used to flip a boolean variable called `game`. That variable is used to enable/disable windows keys and space cadet shift. In my [planck keymap](../../keyboards/planck/keymaps/spacebarracecar/keymap.c) it also makes Lower act like Space which is more comfortable when resting on wasd and it could also be used to change various other things when gaming.
