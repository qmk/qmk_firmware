# Layer Lock

Some [layer switches](../feature_layers#switching-and-toggling-layers) access
the layer by holding the key, including momentary layer `MO(layer)` and layer
tap `LT(layer, key)` keys. You may sometimes need to stay on the layer for a
long period of time. Layer Lock "locks" the current layer to stay on, supposing
it was accessed by one of:

 * `MO(layer)` momentary layer switch
 * `LT(layer, key)` layer tap
 * `OSL(layer)` one-shot layer
 * `TT(layer)` layer tap toggle
 * `LM(layer, mod)` layer-mod key (the layer is locked, but not the mods)

Press the Layer Lock key again to unlock the layer. Additionally, when a layer
is locked, layer switch keys that turn off the layer such as `TO(other_layer)`
will unlock it.


## How do I enable Layer Lock

In your rules.mk, add:

```make
LAYER_LOCK_ENABLE = yes
```

Pick a key in your keymap on a layer you intend to lock, and assign it the
keycode `QK_LAYER_LOCK` (short alias `QK_LLCK`). Note that locking the base
layer has no effect, so typically, this key is used on layers above the base
layer.


## Example use

Consider a keymap with the following base layer.

![Base layer with a MO(NAV) key.](https://i.imgur.com/DkEhj9x.png)

The highlighted key is a momentary layer switch `MO(NAV)`. Holding it accesses a
navigation layer.

![Nav layer with a Layer Lock key.](https://i.imgur.com/2wUZNWk.png)


Holding the NAV key is fine for brief use, but awkward to continue holding when
using navigation functions continuously. The Layer Lock key comes to the rescue:

1. Hold the NAV key, activating the navigation layer.
2. Tap Layer Lock.
3. Release NAV. The navigation layer stays on.
4. Make use of the arrow keys, etc.
5. Tap Layer Lock or NAV again to turn the navigation layer back off.

A variation that would also work is to put the Layer Lock key on the base layer
and make other layers transparent (`KC_TRNS`) in that position. Pressing the
Layer Lock key locks (or unlocks) the highest active layer, regardless of which
layer the Layer Lock key is on.


## Idle timeout

Optionally, Layer Lock may be configured to unlock if the keyboard is idle
for some time. In config.h, define `LAYER_LOCK_IDLE_TIMEOUT` in units of
milliseconds:

```c
#define LAYER_LOCK_IDLE_TIMEOUT 60000  // Turn off after 60 seconds.
```


## Functions

Use the following functions to query and manipulate the layer lock state.

| Function                   | Description                        |
|----------------------------|------------------------------------|
| `is_layer_locked(layer)`   | Checks whether `layer` is locked.  |
| `layer_lock_on(layer)`     | Locks and turns on `layer`.        |
| `layer_lock_off(layer)`    | Unlocks and turns off `layer`.     |
| `layer_lock_invert(layer)` | Toggles whether `layer` is locked. |


## Representing the current Layer Lock state

There is an optional callback `layer_lock_set_user()` that gets called when a
layer is locked or unlocked. This is useful to represent the current lock state
for instance by setting an LED. In keymap.c, define

```c
bool layer_lock_set_user(layer_state_t locked_layers) {
  // Do something like `set_led(is_layer_locked(NAV));`
  return true;
}
```

The argument `locked_layers` is a bitfield in which the kth bit is on if the kth
layer is locked. Alternatively, you can use `is_layer_locked(layer)` to check if
a given layer is locked.


## Combine Layer Lock with a mod-tap

It is possible to create a [mod-tap MT key](../mod_tap) that acts as a modifier
on hold and Layer Lock on tap. Since Layer Lock is not a [basic
keycode](../keycodes_basic), attempting `MT(mod, QK_LLCK)` is invalid does not
work directly, yet this effect can be achieved through [changing the tap
function](../mod_tap#changing-tap-function). For example, the following
implements a `SFTLLCK` key that acts as Shift on hold and Layer Lock on tap:

```c
#define SFTLLCK LSFT_T(KC_0)

// Use SFTLLCK in your keymap...

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFTLLCK:
            if (record->tap.count) {
                if (record->event.pressed) {
                    // Toggle the lock on the highest layer.
                    layer_lock_invert(get_highest_layer(layer_state));
                }
                return false;
            }
            break;

        // Other macros...
    }
    return true;
}
```

In the above, `KC_0` is an arbitrary placeholder for the tapping keycode. This
keycode will never be sent, so any basic keycode will do. In
`process_record_user()`, the tap press event is changed to toggle the lock on
the highest layer. Layer Lock can be combined with a [layer-tap LT
key](../feature_layers#switching-and-toggling-layers) similarly.

