# Digitizer

The digitizer HID interface allows setting the mouse cursor position at absolute coordinates, unlike the Pointing Device feature that applies relative displacements.

To enable the digitizer interface, add the following line to your rules.mk:

```make
DIGITIZER_ENABLE = yes
```

## Moving the pointer

In order to set the mouse cursor position from your `keymap.c` file, include the digitizer header:

```c
#include "digitizer.h"
```

This gives you access to the `digitizer` structure whose members allow you to change the cursor position and send stylus button events.

?> The current digitizer report can be retrieved via `digitizer_get_report()` if you wish to modify it.

### Absolute coordinates

Here is an example setting the cursor near the top left corner of the screen at *(5, 5)*:

```c
digitizer_t digitizer;
digitizer.x = 5;
digitizer.y = 5;
digitizer.buttons = 0;
digitizer.inrange = true;
digitizer_set_report(digitizer);
```

The `x` member represents the absolute x coordinate of the desired pointer position, and may be any integer between `0` and `DIGITIZER_MAX_X` (default `32767`).  Similary, the `y` member may be any integer between `0` and `DIGITIZER_MAX_Y` (default `32767`).

The `buttons` member represents which stylus buttons are pressed, encoded as an 8-bit bitmask. Check the [stylus buttons documentation](#stylus-buttons) for details.

The `inrange` member is required for the change in coordinates to be taken. It can then be set to `0` in a new report to signal the end of the digitizer interaction, but this is not strictly required.

Once all members are set to the desired value, the `status` member needs its bitmask `DZ_UPDATED` to be set so the report is sent during the next main loop iteration.  While this can be done manually, the `status` bitmask is always updated for you by `digitizer_set_report`.

### Relative coordinates

The `DIG_REL2ABS_X` and `DIG_REL2ABS_Y` macros convert a relative position to absolute x/y coordinates by multiplying by `DIGITIZER_MAX_X` or `DIGITIZER_MAX_Y` and then casting to `int`.

For the x coordinate, the value `0.0` is the leftmost position, whereas the value `1.0` is the rightmost position.  For the y coordinate, `0.0` is at the top and `1.0` at the bottom.

Here is an example setting the cursor to the center of the screen using relative values of *(0.5, 0.5)*:

```c
digitizer_t digitizer;
digitizer.x = DIG_REL2ABS_X(0.5);
digitizer.y = DIG_REL2ABS_Y(0.5);
digitizer.buttons = 0;
digitizer.inrange = true;
digitizer_set_report(digitizer);
```


## Stylus buttons

A digitizer stylus may have buttons in its tip, along its barrel/shaft, and at the eraser/end opposite the tip.

### Pressing stylus buttons

Pressed buttons may be set or unset using the `buttons` member of the `digitizer` structure:

```c
// Get current report to update buttons, while leaving x/y unchanged
digitizer_t digitizer = digitizer_get_report();

// Start pressing the primary tip switch; stop pressing the barrel switch
digitizer.buttons |= DIG_TIP_PRIMARY;
digitizer.buttons &= ~DIG_BARREL_PRIMARY;

// Must be InRange for all operating systems to accept this event
digitizer.inrange = true;
digitizer_set_report(digitizer);
```

### Available stylus buttons

The following stylus buttons are supported:

|Button                 |Description |
|-----------------------|------------|
|`DIG_TIP_PRIMARY`      |Switch in the stylus tip, indicating contact of the stylus with a surface. Often mapped to the primary mouse button. |
|`DIG_TIP_SECONDARY`    |Second switch in the stylus tip, indicating extra pressure. Should only be closed if the primary tip switch already is. |
|`DIG_BARREL_PRIMARY`   |Non-tip button on the stylus barrel. Often mapped to a secondary mouse button. |
|`DIG_BARREL_SECONDARY` |Second non-tip button on the stylus barrel. Often mapped to a secondary mouse button. |
|`DIG_TABLET_PICK`      |Main button used by CAD systems. Also known as "Button Zero". |
|`DIG_ERASER`           |Switch used to erase objects, usually in the stylus's opposite end. |
|`DIG_INVERT`           |Indicates an InRange event originates from the stylus's opposite end. Not technically a button! |


## Digitizer keys

Like mouse keys, digitizer keys makes it easy to map keys on your keyboard to digitizer actions like touching the screen or pressing a button on the stylus.

### Enabling digitizer keys

Digitizer keys are enabled automatically when the digitizer is enabled via `DIGITIZER_ENABLE = yes` in your keyboard's `rules.mk`.

### Mapping digitizer actions

In your keymap you can use the following keycodes to map standard key presses to digitizer actions:

|Key                       |Aliases   |Description                                  |
|--------------------------|----------|---------------------------------------------|
|`DZ_TIP_PRIMARY`          |`DZ_TIP1` |Press tip switch                             |
|`DZ_TIP_SECONDARY`        |`DZ_TIP2` |Press secondary tip switch                   |
|`DZ_BARREL_PRIMARY`       |`DZ_BAR1` |Press non-tip barrel switch                  |
|`DZ_BARREL_SECONDARY`     |`DZ_BAR1` |Press secondary barrel switch                |
|`DZ_TABLET_PICK`          |`DZ_PICK` |Press "tablet pick" / "button zero"          |
|`DZ_ERASER`               |`DZ_ERSR` |Press eraser switch                          |
|`DZ_INVERT`               |`DZ_INVT` |Indicate stylus is held upside-down          |
|`DZ_POINTER_CENTER`       |`DZ_P_C`  |Fuzzy-move pointer to center of screen       |
|`DZ_POINTER_TOP_LEFT`     |`DZ_P_TL` |Fuzzy-move pointer to top-left of screen     |
|`DZ_POINTER_TOP_RIGHT`    |`DZ_P_TR` |Fuzzy-move pointer to top-right of screen    |
|`DZ_POINTER_BOTTOM_LEFT`  |`DZ_P_BL` |Fuzzy-move pointer to bottom-left of screen  |
|`DZ_POINTER_BOTTOM_RIGHT` |`DZ_P_BR` |Fuzzy-move pointer to bottom-right of screen |
|`DZ_POINTER_USER0`        |`DZ_P_U0` |Fuzzy-move pointer to `USER0`                |
|`DZ_POINTER_USER1`        |`DZ_P_U1` |Fuzzy-move pointer to `USER1`                |
|`DZ_POINTER_USER2`        |`DZ_P_U2` |Fuzzy-move pointer to `USER2`                |
|`DZ_POINTER_USER3`        |`DZ_P_U3` |Fuzzy-move pointer to `USER3`                |

### Configuring digitizer keys

The x/y coordinates of the four user-customizable pointer keys may be set to absolute coordinates or relative positions (percentage across screen from `0.0` to `1.0`) in your keyboard's `config.h`:

```c
#define DIGITIZER_USER0_X 10
#define DIGITIZER_USER0_Y 20

#define DIGITIZER_USER1_X 100
#define DIGITIZER_USER1_Y 200

#define DIGITIZER_USER2_X DIG_REL2ABS_X(0.1)
#define DIGITIZER_USER2_Y DIG_REL2ABS_Y(0.2)

#define DIGITIZER_USER3_X DIG_REL2ABS_X(0.3)
#define DIGITIZER_USER3_Y DIG_REL2ABS_Y(0.4)
```


## Device type

Your keyboard can identify itself as a specific type of digitizer device, such as a touchscreen or a digital whiteboard, by setting `DIGITIZER_USAGE_ID` in your keyboard's `config.h` file:

```c
#define DIGITIZER_USAGE_ID DIG_TOUCH_SCREEN
```


### Common devices

While you may set `DIGITIZER_USAGE_ID` to arbitrary values, some common types are already defined:

|Device             |Usage  |Description |
|-------------------|-------|------------|
|`DIG_DIGITIZER`    |`0x01` |A generic device that measures absolute spatial position. **This is the default.** |
|`DIG_PEN`          |`0x02` |A digitizer that pairs a stylus with an integrated display, and ensures that the detected stylus position is the same as the display representation. |
|`DIG_LIGHT_PEN`    |`0x03` |A digitizer whose position relies on the underlying video raster, similar to a touch screen but with increased precision. |
|`DIG_TOUCH_SCREEN` |`0x04` |A digitizer with integrated display that allows interaction with a stylus or finger. |
|`DIG_TOUCH_PAD`    |`0x05` |A digitizer common on laptops, featuring a tactile sensor that can detect finger position, motion, and pressure. |
|`DIG_WHITEBOARD`   |`0x06` |A digitizer that may be paired with a video projector, typically mounted vertically. |

?> Linux does not allow the generic `DIG_DIGITIZER` device to move the mouse cursor without additional configuration. It is therefore recommended to emulate one of the more specific devices listed above.


## Operating system work-arounds

Real-world physical digitizer devices can generate false or repeat InRange events, as users are rarely able to precisely touch a single coordinate using their finger or a stylus exactly one time.  To combat this, operating systems ignore digitizer events they deem spurious.

Operating systems can also produce inconsistent behavior when a digitizer is used at the same time as a traditional mouse, resulting in the cursor being rendered at incorrect locations or disappearing from the screen entirely.

QMK provides two ways of "fuzzing" pointer events to work around these operating system quirks: sending multiple digitizer InRange events around the target x/y, and sending small mouse movement events after moving to the target x/y.

To enable all fuzzing strategies, add the following to your keyboard's `config.h`:

```c
#define DIGITIZER_FUZZ
```

Note that enabling the [fuzzy mouse strategy](#using-digitizer_fuzz_mouse) also requires the pointing device to be enabled.

### Using `DIGITIZER_FUZZ_INRANGE`

If the same x/y coordinate is involved in consecutive InRange events, Linux often ignores the second and all subsequent events.

To ensure the target x/y is always seen as a valid event by your operating system, the `digitizer_fuzz_inrange(x, y)` function generates two InRange events back-to-back, with the first occurring slightly offset from the target x/y and the second occurring precisely at the target x/y.

To enable only the fuzzy InRange strategy, add the following to your keyboard's `config.h`:

```c
#define DIGITIZER_FUZZ_INRANGE
```

When this strategy is enabled, all digitizer keys that move the pointer will call `digitizer_fuzz_inrange(x, y)` to move the cursor during keydown.

#### Configuring `DIGITIZER_FUZZ_INRANGE`

The values of `DIGITIZER_FUZZ_X` and `DIGITIZER_FUZZ_Y` determine the distance that fuzzy InRange events are offset from the target x/y coordinates.  The default for both values is `1`, but they may be changed in your keyboard's `config.h`:

```c
#define DIGITIZER_FUZZ_X 3
#define DIGITIZER_FUZZ_Y 2
```

With the above settings, a call to `fuzzy_inrange_xy(x, y)` will first send a fuzzy InRange event at `(x+3, y+2)` before a second event at `(x, y)` precisely.

Note that events which occur at the bottom or right edges of the screen may instead produce fuzzy InRange events at `x-3` or `y-2`, if required to keep their values below `DIGITIZER_MAX_X` and `DIGITIZER_MAX_Y`.

!> `DIGITIZER_FUZZ_X` and `DIGITIZER_FUZZ_Y` are used by both the `DIGITIZER_FUZZ_INRANGE` and `DIGITIZER_FUZZ_MOUSE` fuzzing strategies. Setting these values will change the behavior of both strategies!

### Using `DIGITIZER_FUZZ_MOUSE`

If the mouse moves while digitizer events are being sent, or if certain sequences of digitizer button and InRange events are sent, OSX sometimes fails to render the mouse cursor correctly on screen. This problem persists until the mouse is moved again, which forces the operating system to re-draw the cursor.

To ensure the cursor is rendered correctly after moving to a target x/y, the `digitizer_fuzz_mouse()` function generates a series of small mouse movement events which jitter the pointer around its current position.

To enable only the fuzzy mouse strategy, add the following to your keyboard's `config.h`:

```c
#define DIGITIZER_FUZZ_MOUSE
```

You must also enable the mouse pointer device by adding the following to your `rules.mk`:

```
POINTING_DEVICE_ENABLE = yes
```

When this strategy is enabled, all digitizer keys that move the pointer will call `digitizer_fuzz_mouse()` to force re-rendering the cursor during keyup, after the InRange event has finished.

#### Configuring `DIGITIZER_FUZZ_MOUSE`

- The values of `DIGITIZER_FUZZ_X` and `DIGITIZER_FUZZ_Y` determine the amount of relative mouse jitter that is produced after an InRange event.  The default for both values is `1`.

- The value of `DIGITIZER_FUZZ_MOUSE_TIMES` determines the number of out-and-back mouse movements that are generated by `digitizer_fuzz_mouse()`. The default is `2`.

Any of these configuration options may be changed in your keyboard's `config.h`:

```c
#define DIGITIZER_FUZZ_X 3
#define DIGITIZER_FUZZ_Y 2
#define DIGITIZER_FUZZ_MOUSE_TIMES 3
```

With the above settings, a total of 6 mouse movement events will be generated by `digitizer_fuzz_mouse()`, ultiumately leaving the cursor in the same position it started at:

1. Move cursor: `x=x+3` and `y=y+2` (1st out)
2. Move cursor: `x=x-3` and `y=y-2` (back)
3. Move cursor: `x=x+3` and `y=y+2` (2nd out)
4. Move cursor: `x=x-3` and `y=y-2` (back)
5. Move cursor: `x=x+3` and `y=y+2` (3rd out)
6. Move cursor: `x=x-3` and `y=y-2` (back)

!> `DIGITIZER_FUZZ_X` and `DIGITIZER_FUZZ_Y` are used by both the `DIGITIZER_FUZZ_INRANGE` and `DIGITIZER_FUZZ_MOUSE` fuzzing strategies. Setting these values will change the behavior of both strategies!

### Using `digitizer_fuzz_xy(x, y)`

The helper `digitizer_fuzz_xy(x, y)` utilizes all enabled fuzzy strategies to move the cursor to the target x/y absolute coordinates, before immediately un-registering the InRange event.

This function returns the resulting `digitizer` report to make scripting digitizer action sequences easier.

## Example: digitizer action sequence

Here is an example of a simple digitizer action sequence in `keymap.c`, which sets the mouse cursor to a specific x/y and presses `DIG_TIP_PRIMARY` on key down, and releases `DIG_TIP_PRIMARY` on key up:

```c
enum my_keycodes {
    MY_FUZZ = SAFE_RANGE
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    digitizer_t digitizer;
    switch (keycode) {
        case MY_FUZZ:
            if (record->event.pressed) {
                // Set mouse to the top of the screen, 50% of the way across
                digitizer = digitizer_fuzz_xy(DIG_REL2ABS_X(0.5), 0);
                // Press the tip switch (usually treated as left mouse button)
                digitizer.buttons |= DIG_TIP_PRIMARY;
                digitizer.inrange = true;
                digitizer_set_report(digitizer);
                return false;
            } else {
                // Release the tip switch
                digitizer = digitizer_get_report();
                digitizer.buttons &= ~DIG_TIP_PRIMARY;
                digitizer.inrange = true;
                digitizer_set_report(digitizer);
                return false;
            }
        default:
            return true;
    }
}
```