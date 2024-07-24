# Key Cancellation

Upon a selected key press down, if another key is pressed, it will release another key until it is physically pressed again.

## How do I enable key cancellation {#how-do-i-enable-key-cancellation}

in `rules.mk` add this:
```make
KEY_CANCELLATION_ENABLE = yes
```

By default, key cancellation is disabled even after adding to `rules.mk`. To enable it, you need to use the `KX_CATG` or `KX_CAON` keycode to enable it. The status is stored in persistent memory, so you shouldn't need to enable it again.

### Keycodes {#keycodes}

|Keycode                     |Aliases   |Description                                        |
|----------------------------|----------|---------------------------------------------------|
|`QK_KEY_CANCELLATION_ON`    |`KX_CAON` |Turns on the key cancellation feature.             |
|`QK_KEY_CANCELLATION_OFF`   |`KX_CAOF` |Turns off the key cancellation feature.            |
|`QK_KEY_CANCELLATION_TOGGLE`|`KX_CATG` |Toggles the status of the key cancellation feature.|

## User Callback Functions

```c
bool process_key_cancellation_user(uint16_t keycode, keyrecord_t *record);
```

## Process Key Cancellation Example

```c
const key_cancellation_t PROGMEM key_cancellation_list[] = {
    // on key down
    //       |    key to be released
    //       |     |
    [0] = {KC_D, KC_A},
    [1] = {KC_A, KC_D},
    [2] = {KC_A, KC_F},
};
```

## Key Cancellation Status

Additional user callback functions to manipulate Key Cancellation:

| Function                     | Description                                    |
|------------------------------|------------------------------------------------|
| `key_cancellation_enable()`     | Turns Key Cancellation on.                        |
| `key_cancellation_disable()`    | Turns Key Cancellation off.                       |
| `key_cancellation_toggle()`     | Toggles Key Cancellation.                         |
| `key_cancellation_is_enabled()` | Returns true if Key Cancellation is currently on. |
