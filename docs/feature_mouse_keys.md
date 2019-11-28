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

Mouse keys supports two different modes to move the cursor:

* **Accelerated (default):** Holding movement keys accelerates the cursor until it reaches its maximum speed.
* **Constant:** Holding movement keys moves the cursor at constant speeds.

The same principle applies to scrolling.

Configuration options that are times, intervals or delays are given in milliseconds. Scroll speed is given as multiples of the default scroll step. For example, a scroll speed of 8 means that each scroll action covers 8 times the length of the default scroll step as defined by your operating system or application.

### Accelerated mode

This is the default mode. You can adjust the cursor and scrolling acceleration using the following settings in your keymap’s `config.h` file:

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
* Setting `MOUSEKEY_TIME_TO_MAX` or `MOUSEKEY_WHEEL_TIME_TO_MAX` to `0` will disable acceleration for the cursor or scrolling respectively. This way you can make one of them constant while keeping the other accelerated, which is not possible in constant speed mode.

Cursor acceleration uses the same algorithm as the X Window System MouseKeysAccel feature. You can read more about it [on Wikipedia](https://en.wikipedia.org/wiki/Mouse_keys).

### Constant mode

In this mode you can define multiple different speeds for both the cursor and the mouse wheel. There is no acceleration. `KC_ACL0`, `KC_ACL1` and `KC_ACL2` change the cursor and scroll speed to their respective setting.

You can choose whether speed selection is momentary or tap-to-select:

* **Momentary:** The chosen speed is only active while you hold the respective key. When the key is raised, mouse keys returns to the unmodified speed.
* **Tap-to-select:** The chosen speed is activated when you press the respective key and remains active even after the key has been raised. The default speed is that of `KC_ACL1`. There is no unmodified speed.

The default speeds from slowest to fastest are as follows:

* **Momentary:** `KC_ACL0` < `KC_ACL1` < *unmodified* < `KC_ACL2`
* **Tap-to-select:** `KC_ACL0` < `KC_ACL1` < `KC_ACL2`

To use constant speed mode, you must at least define `MK_3_SPEED` in your keymap’s `config.h` file:

```c
#define MK_3_SPEED
```

To enable momentary mode, also define `MK_MOMENTARY_ACCEL`:

```c
#define MK_MOMENTARY_ACCEL
```

Use the following settings if you want to adjust cursor movement or scrolling:

|Define               |Default      |Description                                |
|---------------------|-------------|-------------------------------------------|
|`MK_3_SPEED`         |*Not defined*|Enable constant cursor speeds              |
|`MK_MOMENTARY_ACCEL` |*Not defined*|Enable momentary speed selection           |
|`MK_C_OFFSET_UNMOD`  |16           |Cursor offset per movement (unmodified)    |
|`MK_C_INTERVAL_UNMOD`|16           |Time between cursor movements (unmodified) |
|`MK_C_OFFSET_0`      |1            |Cursor offset per movement (`KC_ACL0`)     |
|`MK_C_INTERVAL_0`    |32           |Time between cursor movements (`KC_ACL0`)  |
|`MK_C_OFFSET_1`      |4            |Cursor offset per movement (`KC_ACL1`)     |
|`MK_C_INTERVAL_1`    |16           |Time between cursor movements (`KC_ACL1`)  |
|`MK_C_OFFSET_2`      |32           |Cursor offset per movement (`KC_ACL2`)     |
|`MK_C_INTERVAL_2`    |16           |Time between cursor movements (`KC_ACL2`)  |
|`MK_W_OFFSET_UNMOD`  |1            |Scroll steps per scroll action (unmodified)|
|`MK_W_INTERVAL_UNMOD`|40           |Time between scroll steps (unmodified)     |
|`MK_W_OFFSET_0`      |1            |Scroll steps per scroll action (`KC_ACL0`) |
|`MK_W_INTERVAL_0`    |360          |Time between scroll steps (`KC_ACL0`)      |
|`MK_W_OFFSET_1`      |1            |Scroll steps per scroll action (`KC_ACL1`) |
|`MK_W_INTERVAL_1`    |120          |Time between scroll steps (`KC_ACL1`)      |
|`MK_W_OFFSET_2`      |1            |Scroll steps per scroll action (`KC_ACL2`) |
|`MK_W_INTERVAL_2`    |20           |Time between scroll steps (`KC_ACL2`)      |
