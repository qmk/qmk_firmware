# List of Useful Core Functions To Make Your Keyboard Better

There are a lot of hidden functions in QMK that are incredible useful, or may add a bit of functionality that you've been wanting.  Functions that are specific to certain features are not included here, as those will be on their respective feature page.

## (OLKB) Tri Layers

There are actually separate functions that you can use there, depending on what you're after.

### `update_tri_layer(x, y, z)`

The first is the `update_tri_layer(x, y, z)` function.   This function check to see if layers `x` and `y` are both on. If they are both on, then it runs on layer `z`.  Otherwise, if both `x` and `y` are not both on (either only one is, or neither is), then it runs off layer `z`.

This function is useful if you want to create specific keys that have this functionality, but other layer keycodes won't do this.

#### Example

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    }
  return true;
}
```

### `update_tri_layer_state(state, x, y, z)`
The other function is `update_tri_layer_state(state, x, y, z)`.  This function is meant to be called from they [`layer_state_set_*` functions](custom_quantum_functions.md#layer-change-code).  This means that any time that you use a keycode to change the layer, this will be checked.  So you could use `LT(layer, kc)` to change the layer and it will trigger the same layer check.

The caveat to this method is that you cannot access the `z` layer without having `x` and `y` layers on, since if you try to activate just layer `z`, it will run this code and turn off layer `z` before you could use it.

#### Example

```c
uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
```

Alternatively, you don't have to immediately "return" the value.  This is useful if you want to add multiple tri layers, or if you want to add additional effects.

```c
uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  state = update_tri_layer_state(state, _RAISE, _SYMB, _SPECIAL);
  return state;
}
```

## Setting the Persistent Default Layer

Do you want to set the default layer, so that it's retained even after you unplug the board?  If so, this is the function for you.

To use this, you would use `set_single_persistent_default_layer(layer)`.  If you have a name defined for your layer, you can use that instead (such as _QWERTY, _DVORAK or _COLEMAK).

This will set the default layer, update the persistent settings, and play a tune if you have [Audio](feature_audio.md) enabled on your board, and the default layer sounds set.

To configure the default layer sounds, you would want to define this in your `config.h` file, like this:

```c
#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                              SONG(COLEMAK_SOUND), \
                              SONG(DVORAK_SOUND) \
                            }
```


?> There are a large number of predefined songs in [quantum/audio/song_list.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/song_list.h) that you can use.

## Reseting the keyboard

There is the `RESET` quantum keycode that you can use. But if you want to reset the board as part of a macro, rather than hitting a key separately, you can do that.

And to do so, add `reset_keyboard()` to your function or macro, and this will reset to bootloader.

## Wiping the EEPROM (Persistent Storage)

If you're having issues with Audio, RGB Underglow, backlighting or keys acting weird, then you can reset the EEPROM (persistent setting storage).  Bootmagic is one way to do this, but if that isn't enabled, then you can use a custom macro to do so.

To wipe the EEPROM, run `eeconfig_init()` from your function or macro to reset most of the settings to default.
