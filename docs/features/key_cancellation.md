# Key Cancellation

This feature iterates over the `key_cancellation_list`, and upon any matches of key down, all specified keys are released.

Imagine you're holding down the `A` key. If you then press the `D` key, the `A` key will stop being active. To use the `A` key again, you need to press it once more.

## Usage {#usage}

Add the following to your `rules.mk`
```make
KEY_CANCELLATION_ENABLE = yes
```

By default, key cancellation is disabled even after adding to `rules.mk`. To enable it, you need to use the `KX_CATG` or `KX_CAON` keycode to enable it. The status is stored in persistent memory, so you shouldn't need to enable it again.

Your `keymap.c` will then need a Key Cancellation list definition:

```c
#if defined(KEY_CANCELLATION_ENABLE)
const key_cancellation_t PROGMEM key_cancellation_list[] = {
    // on key down
    //       |    key to be released
    //       |     |
    [0] = {KC_D, KC_A},
    [1] = {KC_A, KC_D},
};
#endif
```

## Examples {#examples}
### SOCD WASD Example

```c
#if defined(KEY_CANCELLATION_ENABLE)
const key_cancellation_t PROGMEM key_cancellation_list[] = {
    // on key down
    //       |    key to be released
    //       |     |
    [0] = {KC_D, KC_A},
    [1] = {KC_A, KC_D},
    [2] = {KC_W, KC_S},
    [3] = {KC_S, KC_W},
};
#endif
```

## Keycodes {#keycodes}

|Keycode                     |Aliases   |Description                                        |
|----------------------------|----------|---------------------------------------------------|
|`QK_KEY_CANCELLATION_ON`    |`KX_CAON` |Turns on the key cancellation feature.             |
|`QK_KEY_CANCELLATION_OFF`   |`KX_CAOF` |Turns off the key cancellation feature.            |
|`QK_KEY_CANCELLATION_TOGGLE`|`KX_CATG` |Toggles the status of the key cancellation feature.|

## User Callback Functions

```c
bool process_key_cancellation_user(uint16_t keycode, keyrecord_t *record);
```


## Functions {#functions}

Additional functions provided to manipulate Key Cancellation:

| Function                        | Description                                       |
|---------------------------------|---------------------------------------------------|
| `key_cancellation_enable()`     | Turns Key Cancellation on.                        |
| `key_cancellation_disable()`    | Turns Key Cancellation off.                       |
| `key_cancellation_toggle()`     | Toggles Key Cancellation.                         |
| `key_cancellation_is_enabled()` | Returns true if Key Cancellation is currently on. |
