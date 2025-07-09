# One Shot Keys

One shot keys are keys that remain active until the next key is pressed, and then are released. This allows you to type keyboard combinations without pressing more than one key at a time. These keys are usually called "Sticky keys" or "Dead keys".

For example, if you define a key as `OSM(MOD_LSFT)`, you can type a capital A character by first pressing and releasing shift, and then pressing and releasing A. Your computer will see the shift key being held the moment shift is pressed, and it will see the shift key being released immediately after A is released.

One shot keys also work as normal modifiers. If you hold down a one shot key and type other keys, your one shot will be released immediately after you let go of the key.

Additionally, hitting keys five times in a short period will lock that key. This applies for both One Shot Modifiers and One Shot Layers, and is controlled by the `ONESHOT_TAP_TOGGLE` define.

You can control the behavior of one shot keys by defining these in `config.h`:

```c
#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
```

## Keycodes {#keycodes}

|Key                 |Aliases  |Description                                                          |
|--------------------|---------|---------------------------------------------------------------------|
|`QK_ONE_SHOT_TOGGLE`|`OS_TOGG`|Toggles One Shot keys status                                         |
|`QK_ONE_SHOT_ON`    |`OS_ON`  |Turns One Shot keys on                                               |
|`QK_ONE_SHOT_OFF`   |`OS_OFF` |Turns One Shot keys off                                              |
|`OSL(layer)`        |         |Switch to `layer` for one keypress                                   |
|`OSM(mod)`          |         |Hold `mod` for one keypress                                          |
|`OS_LCTL`           |         |Hold Left Control for one keypress                                   |
|`OS_LSFT`           |         |Hold Left Shift for one keypress                                     |
|`OS_LALT`           |         |Hold Left Alt for one keypress                                       |
|`OS_LGUI`           |         |Hold Left GUI for one keypress                                       |
|`OS_LCS`            |         |Hold Left Control and Left Shift for one keypress                    |
|`OS_LCA`            |         |Hold Left Control and left Alt for one keypress                      |
|`OS_LCG`            |         |Hold Left Control and Left GUI for one keypress                      |
|`OS_LSA`            |         |Hold Left Shift and Left Alt for one keypress                        |
|`OS_LSG`            |         |Hold Left Shift and Left GUI for one keypress                        |
|`OS_LAG`            |         |Hold Left Alt and Left GUI for one keypress                          |
|`OS_LCSG`           |         |Hold Left Control, Left Shift and Left GUI for one keypress          |
|`OS_LCAG`           |         |Hold Left Control, Left Alt and Left GUI for one keypress            |
|`OS_LSAG`           |         |Hold Left Shift, Left Alt and Left GUI for one keypress              |
|`OS_RCTL`           |         |Hold Right Control for one keypress                                  |
|`OS_RSFT`           |         |Hold Right Shift for one keypress                                    |
|`OS_RALT`           |         |Hold Right Alt for one keypress                                      |
|`OS_RGUI`           |         |Hold Right GUI for one keypress                                      |
|`OS_RCS`            |         |Hold Right Control and Right Shift for one keypress                  |
|`OS_RCA`            |         |Hold Right Control and Right Alt for one keypress                    |
|`OS_RCG`            |         |Hold Right Control and Right GUI for one keypress                    |
|`OS_RSA`            |         |Hold Right Shift and Right Alt for one keypress                      |
|`OS_RSG`            |         |Hold Right Shift and Right GUI for one keypress                      |
|`OS_RAG`            |         |Hold Right Alt and Right GUI for one keypress                        |
|`OS_RCSG`           |         |Hold Right Control, Right Shift and Right GUI for one keypress       |
|`OS_RCAG`           |         |Hold Right Control, Right Alt and Right GUI for one keypress         |
|`OS_RSAG`           |         |Hold Right Shift, Right Alt and Right GUI for one keypress           |
|`OS_MEH`            |         |Hold Left Control, Left Shift and Left Alt for one keypress          |
|`OS_HYPR`           |         |Hold Left Control, Left Shift, Left Alt and Left GUI for one keypress|

When One Shot keys are turned off, `OSM()` and `OSL()` will behave like normal modifier keys and `MO()`, respectively.

::: info
The `mod` parameter to the `OSM()` keycode must use the `MOD_*` prefix, rather than `KC_*`, eg. `OSM(MOD_LCTL | MOD_LSFT)`.
:::

Sometimes, you want to activate a one-shot key as part of a macro or tap dance routine.  

For one shot layers, you need to call `set_oneshot_layer(LAYER, ONESHOT_START)` on key down, and `clear_oneshot_layer_state(ONESHOT_PRESSED)` on key up. If you want to cancel the oneshot, call `reset_oneshot_layer()`.

For one shot mods, you need to call `set_oneshot_mods(MOD_BIT(KC_*))` to set it, or `clear_oneshot_mods()` to cancel it.

::: warning
If you're having issues with OSM translating over Remote Desktop Connection, this can be fixed by opening the settings, going to the "Local Resources" tab, and in the keyboard section, change the drop down to "On this Computer".  This will fix the issue and allow OSM to function properly over Remote Desktop.
:::

## Callbacks

When you'd like to perform custom logic when pressing a one shot key, there are several callbacks you can choose to implement. You could indicate changes in one shot keys by flashing an LED or making a sound, for example.

There is a callback for `OSM(mod)`. It is called whenever the state of any one shot modifier key is changed: when it toggles on, but also when it is toggled off. You can use it like this:

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

Last, there is also a callback for the `OSL(layer)` one shot key:

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

If any one shot layer is switched off, `layer` will be zero. When you're looking to do something on any layer change instead of one shot layer changes, `layer_state_set_user` is a better callback to use.

If you are making your own keyboard, there are also `_kb` equivalent functions:

```c
void oneshot_locked_mods_changed_kb(uint8_t mods);
void oneshot_mods_changed_kb(uint8_t mods);
void oneshot_layer_changed_kb(uint8_t layer);
```

As with any callback, be sure to call the `_user` variant to allow for further customizability.
