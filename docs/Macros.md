# Macro shortcuts: Send a whole string when pressing just one key

Instead of using the `ACTION_MACRO` function, you can simply use `M(n)` to access macro *n* - *n* will get passed into the `action_get_macro` as the `id`, and you can use a switch statement to trigger it. This gets called on the keydown and keyup, so you'll need to use an if statement testing `record->event.pressed` (see keymap_default.c).

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
  }
  return MACRO_NONE;
};
```
A macro can include the following commands:

* I() change interval of stroke in milliseconds.
* D() press key.
* U() release key.
* T() type key(press and release).
* W() wait (milliseconds).
* END end mark.

So above you can see the stroke interval changed to 255ms between each keystroke, then a bunch of keys being typed, waits a while, then the macro ends.

Note: Using macros to have your keyboard send passwords for you is possible, but a bad idea.

## Advanced macro functions

To get more control over the keys/actions your keyboard takes, the following functions are available to you in the `action_get_macro` function block:

* `record->event.pressed`

This is a boolean value that can be tested to see if the switch is being pressed or released. An example of this is

```c
if (record->event.pressed) {
  // on keydown
} else {
  // on keyup
}
```

* `register_code(<kc>);`

This sends the `<kc>` keydown event to the computer. Some examples would be `KC_ESC`, `KC_C`, `KC_4`, and even modifiers such as `KC_LSFT` and `KC_LGUI`.

* `unregister_code(<kc>);`

Parallel to `register_code` function, this sends the `<kc>` keyup event to the computer. If you don't use this, the key will be held down until it's sent.

* `layer_on(<n>);`

This will turn on the layer `<n>` - the higher layer number will always take priority. Make sure you have `KC_TRNS` for the key you're pressing on the layer you're switching to, or you'll get stick there unless you have another plan.

* `layer_off(<n>);`

This will turn off the layer `<n>`.

* `clear_keyboard();`

This will clear all mods and keys currently pressed.

* `clear_mods();`

This will clear all mods currently pressed.

* `clear_keyboard_but_mods();`

This will clear all keys besides the mods currently pressed.

* `update_tri_layer(layer_1, layer_2, layer_3);`

If the user attempts to activate layer 1 AND layer 2 at the same time (for example, by hitting their respective layer keys), layer 3 will be activated. Layers 1 and 2 will _also_ be activated, for the purposes of fallbacks (so a given key will fall back from 3 to 2, to 1 -- and only then to 0).

### Naming your macros

If you have a bunch of macros you want to refer to from your keymap, while keeping the keymap easily readable, you can just name them like so:

```
#define AUD_OFF M(6)
#define AUD_ON M(7)
#define MUS_OFF M(8)
#define MUS_ON M(9)
#define VC_IN M(10)
#define VC_DE M(11)
#define PLOVER M(12)
#define EXT_PLV M(13)
```

As was done on the [Planck default keymap](https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/default/keymap.c#L33-L40)

#### Timer functionality

It's possible to start timers and read values for time-specific events - here's an example:

```c
static uint16_t key_timer;
key_timer = timer_read();
if (timer_elapsed(key_timer) < 100) {
  // do something if less than 100ms have passed
} else {
  // do something if 100ms or more have passed
}
```

It's best to declare the `static uint16_t key_timer;` outside of the macro block (top of file, etc).

### Example: Single-key copy/paste (hold to copy, tap to paste)

With QMK, it's easy to make one key do two things, as long as one of those things is being a modifier. :) So if you want a key to act as Ctrl when held and send the letter R when tapped, that's easy: `CTL_T(KC_R)`. But what do you do when you want that key to send Ctrl-V (paste) when tapped, and Ctrl-C (copy) when held?

Here's what you do:


```
static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0: {
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LCTL), T(C), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LCTL), T(V), U(LCTL), END  );
                }
            }
            break;
        }
      }
    return MACRO_NONE;
};
```

And then, to assign this macro to a key on your keyboard layout, you just use `M(0)` on the key you want to press for copy/paste.

# Dynamic macros: record and replay macros in runtime

In addition to the static macros described above, you may enable the dynamic macros which you may record while writing. They are forgotten as soon as the keyboard is unplugged. Only two such macros may be stored at the same time, with the total length of 64 keypresses (by default).

To enable them, first add a new element to the `planck_keycodes` enum — `DYNAMIC_MACRO_RANGE`:

    enum planck_keycodes {
      QWERTY = SAFE_RANGE,
      COLEMAK,
      DVORAK,
      PLOVER,
      LOWER,
      RAISE,
      BACKLIT,
      EXT_PLV,
      DYNAMIC_MACRO_RANGE,
    };

It must be the last element because `dynamic_macros.h` will add some more keycodes after it.

Below it include the `dynamic_macro.h` header:

    #include "dynamic_macro.h"`

Add the following keys to your keymap:

- `DYN_REC_START1` — start recording the macro 1,
- `DYN_REC_START2` — start recording the macro 2,
- `DYN_MACRO_PLAY1` — replay the macro 1,
- `DYN_MACRO_PLAY2` — replay the macro 2,
- `DYN_REC_STOP` — finish the macro that is currently being recorded.

Add the following code to the very beginning of your `process_record_user()` function:

    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

That should be everything necessary. To start recording the macro, press either `DYN_REC_START1` or `DYN_REC_START2`. To finish the recording, press the `DYN_REC_STOP` layer button. To replay the macro, press either `DYN_MACRO_PLAY1` or `DYN_MACRO_PLAY2`.

Note that it's possible to replay a macro as part of a macro. It's ok to replay macro 2 while recording macro 1 and vice versa but never create recursive macros i.e. macro 1 that replays macro 1. If you do so and the keyboard will get unresponsive, unplug the keyboard and plug it again.

For users of the earlier versions of dynamic macros: It is still possible to finish the macro recording using just the layer modifier used to access the dynamic macro keys, without a dedicated `DYN_REC_STOP` key. If you want this behavior back, use the following snippet instead of the one above:

    uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);
    if (!process_record_dynamic_macro(macro_kc, record)) {
        return false;
    }

If the LED-s start blinking during the recording with each keypress, it means there is no more space for the macro in the macro buffer. To fit the macro in, either make the other macro shorter (they share the same buffer) or increase the buffer size by setting the `DYNAMIC_MACRO_SIZE` preprocessor macro (default value: 128; please read the comments for it in the header).

For the details about the internals of the dynamic macros, please read the comments in the `dynamic_macro.h` header.

# Sending strings
Some people want to have a password or some text on a key. This is possible without having to do every key individually using `SEND_STRING("<text>");`. Note the caps, because `send_string("<text>");` does something else. For example:
```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
				SEND_STRING("QMK is the best thing ever!"); // This would type "QMK is the best thing ever!" (without quotation marks).
        return false; // This is false because it has to return something.
      }
      break;
  }
  return MACRO_NONE;
};
```
If you'd want it to press enter as well, just replace `return false;` with `return MACRO( T(ENT), END );`.
