# Mouse keys

Mouse keys is a feature that allows you to emulate a mouse using your keyboard. You can move the pointer at different speeds, press 5 buttons and scroll in 8 directions.

## Adding mouse keys to your keyboard

To use mouse keys, you must at least enable mouse keys support and map mouse actions to keys on your keyboard.

### Enabling mouse keys

To enable mouse keys, add the following line to your keymap’s `rules.mk`:

```c
MOUSEKEY_ENABLE = yes
```

### Mapping mouse actions

In your keymap you can use the following keycodes to map key presses to mouse actions:

|Key             |Aliases  |Description      |
|----------------|---------|-----------------|
|`KC_MS_UP`      |`KC_MS_U`|Move cursor up   |
|`KC_MS_DOWN`    |`KC_MS_D`|Move cursor down |
|`KC_MS_LEFT`    |`KC_MS_L`|Move cursor left |
|`KC_MS_RIGHT`   |`KC_MS_R`|Move cursor right|
|`KC_MS_BTN1`    |`KC_BTN1`|Press button 1   |
|`KC_MS_BTN2`    |`KC_BTN2`|Press button 2   |
|`KC_MS_BTN3`    |`KC_BTN3`|Press button 3   |
|`KC_MS_BTN4`    |`KC_BTN4`|Press button 4   |
|`KC_MS_BTN5`    |`KC_BTN5`|Press button 5   |
|`KC_MS_WH_UP`   |`KC_WH_U`|Move wheel up    |
|`KC_MS_WH_DOWN` |`KC_WH_D`|Move wheel down  |
|`KC_MS_WH_LEFT` |`KC_WH_L`|Move wheel left  |
|`KC_MS_WH_RIGHT`|`KC_WH_R`|Move wheel right |
|`KC_MS_ACCEL0`  |`KC_ACL0`|Set speed to 0   |
|`KC_MS_ACCEL1`  |`KC_ACL1`|Set speed to 1   |
|`KC_MS_ACCEL2`  |`KC_ACL2`|Set speed to 2   |

## Configuring mouse keys

Configuration options that are times, intervals or delays are given in milliseconds. Scroll speed is given as multiples of the default scroll step. For example, a scroll speed of 8 means that each scroll action covers 8 times the length of the default scroll step as defined by your operating system or application.

You can adjust the cursor and scrolling acceleration using the following settings in your keymap’s `config.h` file:

|Define                      |Default|Description                                              |
|----------------------------|-------|---------------------------------------------------------|
|`MOUSEKEY_DELAY`            |300    |Delay between pressing a movement key and cursor movement|
|`MOUSEKEY_INTERVAL`         |50     |Time between cursor movements                            |
|`MOUSEKEY_MAX_SPEED`        |10     |Maximum cursor speed at which acceleration stops         |
|`MOUSEKEY_TIME_TO_MAX`      |20     |Time until maximum cursor speed is reached               |
|`MOUSEKEY_WHEEL_MAX_SPEED`  |8      |Maximum number of scroll steps per scroll action         |
|`MOUSEKEY_WHEEL_TIME_TO_MAX`|40     |Time until maximum scroll speed is reached               |

Tips:

* Setting `MOUSEKEY_DELAY` too low makes the cursor unresponsive. Setting it too high makes small movements difficult.
* For smoother cursor movements, lower the value of `MOUSEKEY_INTERVAL`. If the refresh rate of your display is 60Hz, you could set it to `16` (1/60). As this raises the cursor speed significantly, you may want to lower `MOUSEKEY_MAX_SPEED`.
* Setting `MOUSEKEY_TIME_TO_MAX` or `MOUSEKEY_WHEEL_TIME_TO_MAX` to `0` will disable acceleration for the cursor or scrolling respectively. This way you can even make one of them constant while keeping the other accelerated.

Cursor acceleration uses the same algorithm as the X Window System MouseKeysAccel feature. You can read more about it [on Wikipedia](https://en.wikipedia.org/wiki/Mouse_keys).

## Configuring `KC_ACL_*` behavior

You can define up to 3 different speeds for both the cursor and the mouse wheel. `KC_ACL0`, `KC_ACL1` and `KC_ACL2` change the cursor and scroll speed to their respective setting. There is no acceleration during a preset speed is activated.

You can choose whether speed selection is momentary or tap-to-select:

* **Momentary (default):** The chosen speed is only active while you hold the respective key. When the key is raised, mouse keys returns to the unmodified speed.
* **Tap-to-select:** The chosen speed is activated when you press the respective key and remains active even after the key has been raised.

To enable tap-to-select mode, define `MOUSEKEY_PERSISTENT_ACCEL`:

```c
#define MOUSEKEY_PERSISTENT_ACCEL
```

Use the following settings if you want to adjust cursor movement or scrolling:

|Define                      |Default                     |Description                                |
|----------------------------|----------------------------|-------------------------------------------|
|`MOUSEKEY_PERSISTENT_ACCEL` |*Not defined*               |Enable momentary speed selection           |
|`MOUSEKEY_SPEED_0`          |MOUSEKEY_MAX_SPEED / 4      |Cursor offset per movement (`KC_ACL0`)     |
|`MOUSEKEY_INTERVAL_0`       |MOUSEKEY_INTERVAL           |Time between cursor movements (`KC_ACL0`)  |
|`MOUSEKEY_SPEED_1`          |MOUSEKEY_MAX_SPEED / 2      |Cursor offset per movement (`KC_ACL1`)     |
|`MOUSEKEY_INTERVAL_1`       |MOUSEKEY_INTERVAL           |Time between cursor movements (`KC_ACL1`)  |
|`MOUSEKEY_SPEED_2`          |MOUSEKEY_MAX_SPEED          |Cursor offset per movement (`KC_ACL2`)     |
|`MOUSEKEY_INTERVAL_2`       |MOUSEKEY_INTERVAL           |Time between cursor movements (`KC_ACL2`)  |
|`MOUSEKEY_WHEEL_SPEED_0`    |MOUSEKEY_WHEEL_MAX_SPEED / 4|Scroll steps per scroll action (`KC_ACL0`) |
|`MOUSEKEY_WHEEL_INTERVAL_0` |MOUSEKEY_WHEEL_INTERVAL     |Time between scroll steps (`KC_ACL0`)      |
|`MOUSEKEY_WHEEL_SPEED_1`    |MOUSEKEY_WHEEL_MAX_SPEED / 2|Scroll steps per scroll action (`KC_ACL1`) |
|`MOUSEKEY_WHEEL_INTERVAL_1` |MOUSEKEY_WHEEL_INTERVAL     |Time between scroll steps (`KC_ACL1`)      |
|`MOUSEKEY_WHEEL_SPEED_2`    |MOUSEKEY_WHEEL_MAX_SPEED    |Scroll steps per scroll action (`KC_ACL2`) |
|`MOUSEKEY_WHEEL_INTERVAL_2` |MOUSEKEY_WHEEL_INTERVAL     |Time between scroll steps (`KC_ACL2`)      |
