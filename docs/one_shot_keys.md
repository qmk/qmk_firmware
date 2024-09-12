# One Shot Keys

One Shot keys are keys that remain active until the next key is pressed, and then are released. This allows you to type keyboard combinations without pressing more than one key at a time. These keys are usually called "Sticky keys" or "Dead keys".

For example, if you define a key as `OSM(MOD_LSFT)`, you can type a capital `A` character by first pressing and releasing the One Shot key, and then pressing and releasing `A`. Your computer will see the shift key being held the moment the One Shot key is pressed, and it will see the shift key being released immediately after `A` is released.

One Shot keys also work as normal modifiers: if you hold down a One Shot key and type other keys, your One Shot will be released immediately after you let go of the key.

Additionally, hitting a One Shot key five times in a short period will lock that key. This applies for both One Shot Modifiers and One Shot Layers, and is controlled by the `ONESHOT_TAP_TOGGLE` define.

You can control the behavior of One Shot keys by defining these in `config.h`:

```c
#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
```

* `OSM(mod)` — Momentarily hold down *mod*. You must use the `MOD_*` keycodes as shown in [Mod-Tap](mod_tap), not the `KC_*` codes.
* `OSL(layer)` — momentary switch to *layer*.
* `OS_ON` — Turns on One Shot keys.
* `OS_OFF` — Turns off One Shot keys. OSM act as regular mod keys, and OSL act like `MO`.
* `OS_TOGG` — Toggles the One Shot key status.

Sometimes, you want to activate a One Shot key as part of a macro or Tap Dance routine.

For One Shot layers, you need to call `set_oneshot_layer(LAYER, ONESHOT_START)` on key down, and `clear_oneshot_layer_state(ONESHOT_PRESSED)` on key up. If you want to cancel the One Shot, call `reset_oneshot_layer()`.

For One Shot mods, you need to call `set_oneshot_mods(MOD_BIT(KC_*))` to set it, or `clear_oneshot_mods()` to cancel it.

::: warning
If you're having issues with OSM translating over Remote Desktop Connection, this can be fixed by opening the settings; going to the "Local Resources" tab; and in the keyboard section, changing the drop down to "On this Computer".  This will fix the issue and allow OSM to function properly over Remote Desktop.
:::

## Callbacks

When you'd like to perform custom logic when pressing a One Shot key, there are several callbacks you can choose to implement. You could indicate changes in One Shot keys by flashing an LED or making a sound, for example.

There is a callback for `OSM(mod)`. It is called whenever the state of any One Shot modifier key is changed; that is, when it toggles on, but also when it is toggled off. You can use it as follows:

```c
void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot mods GUI");
  }
  if (!mods) {
    println("Oneshot mods off");
  }
}
```

The `mods` argument contains the active mods after the change, so it reflects the current state.

When you use One Shot Tap Toggle (by adding `#define ONESHOT_TAP_TOGGLE 2` in your `config.h` file), you may lock a modifier key by pressing it the specified amount of times. There's a callback for that, too:

```c
void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot locked mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot locked mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot locked mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot locked mods GUI");
  }
  if (!mods) {
    println("Oneshot locked mods off");
  }
}
```

Lastly, there is also a callback for the `OSL(layer)` One Shot key:

```c
void oneshot_layer_changed_user(uint8_t layer) {
  if (layer == 1) {
    println("Oneshot layer 1 on");
  }
  if (!layer) {
    println("Oneshot layer off");
  }
}
```

If any One Shot layer is switched off, `layer` will be zero. When you're looking to do something on any layer change instead of One Shot layer changes, `layer_state_set_user` is a better callback to use.

If you are making your own keyboard, there are also `_kb` equivalent functions:

```c
void oneshot_locked_mods_changed_kb(uint8_t mods);
void oneshot_mods_changed_kb(uint8_t mods);
void oneshot_layer_changed_kb(uint8_t layer);
```

As with any callback, be sure to call the `_user` variant to allow for further customizability.
