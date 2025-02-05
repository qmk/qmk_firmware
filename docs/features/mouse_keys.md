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

|Key                      |Aliases  |Description                |
|-------------------------|---------|---------------------------|
|`QK_MOUSE_CURSOR_UP`     |`MS_UP`  |Mouse cursor up            |
|`QK_MOUSE_CURSOR_DOWN`   |`MS_DOWN`|Mouse cursor down          |
|`QK_MOUSE_CURSOR_LEFT`   |`MS_LEFT`|Mouse cursor left          |
|`QK_MOUSE_CURSOR_RIGHT`  |`MS_RGHT`|Mouse cursor right         |
|`QK_MOUSE_BUTTON_1`      |`MS_BTN1`|Mouse button 1             |
|`QK_MOUSE_BUTTON_2`      |`MS_BTN2`|Mouse button 2             |
|`QK_MOUSE_BUTTON_3`      |`MS_BTN3`|Mouse button 3             |
|`QK_MOUSE_BUTTON_4`      |`MS_BTN4`|Mouse button 4             |
|`QK_MOUSE_BUTTON_5`      |`MS_BTN5`|Mouse button 5             |
|`QK_MOUSE_BUTTON_6`      |`MS_BTN6`|Mouse button 6             |
|`QK_MOUSE_BUTTON_7`      |`MS_BTN7`|Mouse button 7             |
|`QK_MOUSE_BUTTON_8`      |`MS_BTN8`|Mouse button 8             |
|`QK_MOUSE_WHEEL_UP`      |`MS_WHLU`|Mouse wheel up             |
|`QK_MOUSE_WHEEL_DOWN`    |`MS_WHLD`|Mouse wheel down           |
|`QK_MOUSE_WHEEL_LEFT`    |`MS_WHLL`|Mouse wheel left           |
|`QK_MOUSE_WHEEL_RIGHT`   |`MS_WHLR`|Mouse wheel right          |
|`QK_MOUSE_ACCELERATION_0`|`MS_ACL0`|Set mouse acceleration to 0|
|`QK_MOUSE_ACCELERATION_1`|`MS_ACL1`|Set mouse acceleration to 1|
|`QK_MOUSE_ACCELERATION_2`|`MS_ACL2`|Set mouse acceleration to 2|

## Configuring mouse keys

Mouse keys supports three different modes to move the cursor:

* **Accelerated (default):** Holding movement keys accelerates the cursor until it reaches its maximum speed.
* **Kinetic:** Holding movement keys accelerates the cursor with its speed following a quadratic curve until it reaches its maximum speed.
* **Constant:** Holding movement keys moves the cursor at constant speeds.
* **Combined:** Holding movement keys accelerates the cursor until it reaches its maximum speed, but holding acceleration and movement keys simultaneously moves the cursor at constant speeds.
* **Inertia:** Cursor accelerates when key held, and decelerates after key release.  Tracks X and Y velocity separately for more nuanced movements.  Applies to cursor only, not scrolling.

The same principle applies to scrolling, in most modes.

Configuration options that are times, intervals or delays are given in milliseconds. Scroll speed is given as multiples of the default scroll step. For example, a scroll speed of 8 means that each scroll action covers 8 times the length of the default scroll step as defined by your operating system or application.

### Accelerated mode

This is the default mode. You can adjust the cursor and scrolling acceleration using the following settings in your keymap’s `config.h` file:

|Define                      |Default|Description                                              |
|----------------------------|-------|---------------------------------------------------------|
|`MOUSEKEY_DELAY`            |10     |Delay between pressing a movement key and cursor movement|
|`MOUSEKEY_INTERVAL`         |20     |Time between cursor movements in milliseconds            |
|`MOUSEKEY_MOVE_DELTA`       |8      |Step size                                                |
|`MOUSEKEY_MAX_SPEED`        |10     |Maximum cursor speed at which acceleration stops         |
|`MOUSEKEY_TIME_TO_MAX`      |30     |Time until maximum cursor speed is reached               |
|`MOUSEKEY_WHEEL_DELAY`      |10     |Delay between pressing a wheel key and wheel movement    |
|`MOUSEKEY_WHEEL_INTERVAL`   |80     |Time between wheel movements                             |
|`MOUSEKEY_WHEEL_DELTA`      |1      |Wheel movement step size                                 |
|`MOUSEKEY_WHEEL_MAX_SPEED`  |8      |Maximum number of scroll steps per scroll action         |
|`MOUSEKEY_WHEEL_TIME_TO_MAX`|40     |Time until maximum scroll speed is reached               |

Tips:

* Setting `MOUSEKEY_DELAY` too low makes the cursor unresponsive. Setting it too high makes small movements difficult.
* For smoother cursor movements, lower the value of `MOUSEKEY_INTERVAL`. If the refresh rate of your display is 60Hz, you could set it to `16` (1/60). As this raises the cursor speed significantly, you may want to lower `MOUSEKEY_MAX_SPEED`.
* Setting `MOUSEKEY_TIME_TO_MAX` or `MOUSEKEY_WHEEL_TIME_TO_MAX` to `0` will disable acceleration for the cursor or scrolling respectively. This way you can make one of them constant while keeping the other accelerated, which is not possible in constant speed mode.
* Setting `MOUSEKEY_WHEEL_INTERVAL` too low will make scrolling too fast. Setting it too high will make scrolling too slow when the wheel key is held down.

Cursor acceleration uses the same algorithm as the X Window System MouseKeysAccel feature. You can read more about it [on Wikipedia](https://en.wikipedia.org/wiki/Mouse_keys).

### Kinetic Mode

This is an extension of the accelerated mode. The kinetic mode uses a quadratic curve on the cursor speed which allows precise movements at the beginning and allows to cover large distances by increasing cursor speed quickly thereafter.  You can adjust the cursor and scrolling acceleration using the following settings in your keymap’s `config.h` file:

|Define                                |Default  |Description                                                    |
|--------------------------------------|---------|---------------------------------------------------------------|
|`MK_KINETIC_SPEED`                    |undefined|Enable kinetic mode                                            |
|`MOUSEKEY_DELAY`                      |5        |Delay between pressing a movement key and cursor movement      |
|`MOUSEKEY_INTERVAL`                   |10       |Time between cursor movements in milliseconds                  |
|`MOUSEKEY_MOVE_DELTA`                 |16       |Step size for accelerating from initial to base speed          |
|`MOUSEKEY_INITIAL_SPEED`              |100      |Initial speed of the cursor in pixel per second                |
|`MOUSEKEY_BASE_SPEED`                 |5000     |Maximum cursor speed at which acceleration stops               |
|`MOUSEKEY_DECELERATED_SPEED`          |400      |Decelerated cursor speed                                       |
|`MOUSEKEY_ACCELERATED_SPEED`          |3000     |Accelerated cursor speed                                       |
|`MOUSEKEY_WHEEL_INITIAL_MOVEMENTS`    |16       |Initial number of movements of the mouse wheel                 |
|`MOUSEKEY_WHEEL_BASE_MOVEMENTS`       |32       |Maximum number of movements at which acceleration stops        |
|`MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS`|48       |Accelerated wheel movements                                    |
|`MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS`|8        |Decelerated wheel movements                                    |

Tips:

* The smoothness of the cursor movement depends on the `MOUSEKEY_INTERVAL` setting. The shorter the interval is set the smoother the movement will be.  Setting the value too low makes the cursor unresponsive.  Lower settings are possible if the micro processor is fast enough. For example: At an interval of `8` milliseconds, `125` movements per second will be initiated.  With a base speed of `1000` each movement will move the cursor by `8` pixels.
* Mouse wheel movements are implemented differently from cursor movements. While it's okay for the cursor to move multiple pixels at once for the mouse wheel this would lead to jerky movements. Instead, the mouse wheel operates at step size `1`. Setting mouse wheel speed is done by adjusting the number of wheel movements per second.

### Constant mode

In this mode you can define multiple different speeds for both the cursor and the mouse wheel. There is no acceleration. `MS_ACL0`, `MS_ACL1` and `MS_ACL2` change the cursor and scroll speed to their respective setting.

You can choose whether speed selection is momentary or tap-to-select:

* **Momentary:** The chosen speed is only active while you hold the respective key. When the key is raised, mouse keys returns to the unmodified speed.
* **Tap-to-select:** The chosen speed is activated when you press the respective key and remains active even after the key has been raised. The default speed is that of `MS_ACL1`. There is no unmodified speed.

The default speeds from slowest to fastest are as follows:

* **Momentary:** `MS_ACL0` < `MS_ACL1` < *unmodified* < `MS_ACL2`
* **Tap-to-select:** `MS_ACL0` < `MS_ACL1` < `MS_ACL2`

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
|`MK_C_OFFSET_0`      |1            |Cursor offset per movement (`MS_ACL0`)     |
|`MK_C_INTERVAL_0`    |32           |Time between cursor movements (`MS_ACL0`)  |
|`MK_C_OFFSET_1`      |4            |Cursor offset per movement (`MS_ACL1`)     |
|`MK_C_INTERVAL_1`    |16           |Time between cursor movements (`MS_ACL1`)  |
|`MK_C_OFFSET_2`      |32           |Cursor offset per movement (`MS_ACL2`)     |
|`MK_C_INTERVAL_2`    |16           |Time between cursor movements (`MS_ACL2`)  |
|`MK_W_OFFSET_UNMOD`  |1            |Scroll steps per scroll action (unmodified)|
|`MK_W_INTERVAL_UNMOD`|40           |Time between scroll steps (unmodified)     |
|`MK_W_OFFSET_0`      |1            |Scroll steps per scroll action (`MS_ACL0`) |
|`MK_W_INTERVAL_0`    |360          |Time between scroll steps (`MS_ACL0`)      |
|`MK_W_OFFSET_1`      |1            |Scroll steps per scroll action (`MS_ACL1`) |
|`MK_W_INTERVAL_1`    |120          |Time between scroll steps (`MS_ACL1`)      |
|`MK_W_OFFSET_2`      |1            |Scroll steps per scroll action (`MS_ACL2`) |
|`MK_W_INTERVAL_2`    |20           |Time between scroll steps (`MS_ACL2`)      |

### Combined mode

This mode functions like **Accelerated** mode, however, you can hold `MS_ACL0`, `MS_ACL1` and `MS_ACL2`
to momentarily (while held) set the cursor and scroll speeds to constant speeds. When no acceleration
keys are held, this mode is identical to **Accelerated** mode, and can be modified using all of the
relevant settings.

* **MS_ACL0:** This acceleration sets your cursor to the slowest possible speed. This is useful for very
small and detailed movements of the cursor.
* **MS_ACL1:** This acceleration sets your cursor to half the maximum (user defined) speed.
* **MS_ACL2:** This acceleration sets your cursor to the maximum (computer defined) speed. This is
useful for moving the cursor large distances without much accuracy.

To use combined speed mode, you must at least define `MK_COMBINED` in your keymap’s `config.h` file:

```c
#define MK_COMBINED
```

### Inertia mode

This mode provides smooth motion, like sliding on ice.  The cursor accelerates
along a quadratic curve while a key is held, then glides to a stop after the
key is released.  Vertical and horizontal movements are tracked independently,
so the cursor can move in many directions and make curves.

Cannot be used at the same time as Kinetic mode, Constant mode, or Combined mode.

Recommended settings in your keymap’s `config.h` file:

|Define                      |Default  |Description                                                |
|----------------------------|---------|-----------------------------------------------------------|
|`MOUSEKEY_INERTIA`          |undefined|Enable Inertia mode                                        |
|`MOUSEKEY_DELAY`            |150      |Delay between pressing a movement key and cursor movement  |
|`MOUSEKEY_INTERVAL`         |16       |Time between cursor movements in milliseconds (16 = 60fps) |
|`MOUSEKEY_MAX_SPEED`        |32       |Maximum cursor speed at which acceleration stops           |
|`MOUSEKEY_TIME_TO_MAX`      |32       |Number of frames until maximum cursor speed is reached     |
|`MOUSEKEY_FRICTION`         |24       |How quickly the cursor stops after releasing a key         |
|`MOUSEKEY_MOVE_DELTA`       |1        |How much to move on first frame (1 strongly recommended)   |

Tips:

* Set `MOUSEKEY_DELAY` to roughly the same value as your host computer's key repeat delay, in ms.  Recommended values are 100 to 300.
* Set `MOUSEKEY_INTERVAL` to a value of 1000 / your monitor's FPS.  For 60 FPS, 1000/60 = 16.
* Set `MOUSEKEY_MAX_SPEED` based on your screen resolution and refresh rate, like Width / FPS.  For example, 1920 pixels / 60 FPS = 32 pixels per frame.
* Set `MOUSEKEY_TIME_TO_MAX` to a value of approximately FPS / 2, to make it reach full speed in half a second (or so).
* Set `MOUSEKEY_FRICTION` to something between 1 and 255.  Lower makes the cursor glide longer. Values from 8 to 40 are the most effective.
* Keep `MOUSEKEY_MOVE_DELTA` at 1.  This allows precise movements before the gliding effect starts.
* Mouse wheel options are the same as the default accelerated mode, and do not use inertia.

### Overlapping mouse key control

When additional overlapping mouse key is pressed, the mouse cursor will continue in a new direction with the same acceleration. The following settings can be used to reset the acceleration with new overlapping keys for more precise control if desired:

|Define                        |Default               |Description                                                            |
|------------------------------|----------------------|-----------------------------------------------------------------------|
|`MOUSEKEY_OVERLAP_RESET`      |undefined             |Enables overlapping mouse key control                                  |
|`MOUSEKEY_OVERLAP_MOVE_DELTA` |`MOUSEKEY_MOVE_DELTA` |Step size of reset movement acceleration                               |
|`MOUSEKEY_OVERLAP_WHEEL_DELTA`|`MOUSEKEY_WHEEL_DELTA`|Step size of reset mouse wheel acceleration                            |
|`MOUSEKEY_OVERLAP_INTERVAL`   |`MOUSEKEY_INTERVAL`   |Reset time between cursor movements in milliseconds (Kinetic mode only)|

::: tip
This feature will not be applied on Inertial mode
:::

## Use with PS/2 Mouse and Pointing Device

Mouse keys button state is shared with [PS/2 mouse](ps2_mouse) and [pointing device](pointing_device) so mouse keys button presses can be used for clicks and drags.
