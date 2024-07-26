# How to Customize Your Keyboard's Behavior

For a lot of people a custom keyboard is about more than sending button presses to your computer. You want to be able to do things that are more complex than simple button presses and macros. QMK has hooks that allow you to inject code, override functionality, and otherwise customize how your keyboard behaves in different situations.

This page does not assume any special knowledge about QMK, but reading [Understanding QMK](understanding_qmk) will help you understand what is going on at a more fundamental level.

## A Word on Core vs Keyboards vs Keymap {#a-word-on-core-vs-keyboards-vs-keymap}

We have structured QMK as a hierarchy:

* Core (`_quantum`)
  * Keyboard/Revision (`_kb`)
    * Keymap (`_user`)

Each of the functions described below can be defined with a `_kb()` suffix or a `_user()` suffix. We intend for you to use the `_kb()` suffix at the Keyboard/Revision level, while the `_user()` suffix should be used at the Keymap level.

When defining functions at the Keyboard/Revision level it is important that your `_kb()` implementation call `_user()` before executing anything else- otherwise the keymap level function will never be called.

# Custom Keycodes

By far the most common task is to change the behavior of an existing keycode or to create a new keycode. From a code standpoint the mechanism for each is very similar.

## Defining a New Keycode

The first step to creating your own custom keycode(s) is to enumerate them. This means both naming them and assigning a unique number to that keycode. Rather than limit custom keycodes to a fixed range of numbers QMK provides the `SAFE_RANGE` macro. You can use `SAFE_RANGE` when enumerating your custom keycodes to guarantee that you get a unique number.


Here is an example of enumerating 2 keycodes. After adding this block to your `keymap.c` you will be able to use `FOO` and `BAR` inside your keymap.

```c
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## Programming the Behavior of Any Keycode {#programming-the-behavior-of-any-keycode}

When you want to override the behavior of an existing key, or define the behavior for a new key, you should use the `process_record_kb()` and `process_record_user()` functions. These are called by QMK during key processing before the actual key event is handled. If these functions return `true` QMK will process the keycodes as usual. That can be handy for extending the functionality of a key rather than replacing it. If these functions return `false` QMK will skip the normal key handling, and it will be up to you to send any key up or down events that are required.

These function are called every time a key is pressed or released.

### Example `process_record_user()` Implementation

This example does two things. It defines the behavior for a custom keycode called `FOO`, and it supplements our Enter key by playing a tone whenever it is pressed.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case KC_ENTER:
      // Play a tone when enter is pressed
      if (record->event.pressed) {
        PLAY_SONG(tone_qwerty);
      }
      return true; // Let QMK send the enter press/release events
    default:
      return true; // Process all other keycodes normally
  }
}
```

### `process_record_*` Function Documentation

* Keyboard/Revision: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* Keymap: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

The `keycode` argument is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. You should use a `switch...case` block to handle these events.

The `record` argument contains information about the actual press:

```c
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

# Keyboard Initialization Code

There are several steps in the keyboard initialization process.  Depending on what you want to do, it will influence which function you should use.

These are the three main initialization functions, listed in the order that they're called.

* `keyboard_pre_init_*` - Happens before most anything is started. Good for hardware setup that you want running very early.
* `matrix_init_*` - Happens midway through the firmware's startup process. Hardware is initialized, but features may not be yet.
* `keyboard_post_init_*` - Happens at the end of the firmware's startup process. This is where you'd want to put "customization" code, for the most part.

::: warning
For most people, the `keyboard_post_init_user` function is what you want to call.  For instance, this is where you want to set up things for RGB Underglow.
:::

## Keyboard Pre Initialization code

This runs very early during startup, even before the USB has been started.

Shortly after this, the matrix is initialized.

For most users, this shouldn't be used, as it's primarily for hardware oriented initialization.

However, if you have hardware stuff that you need initialized, this is the best place for it (such as initializing LED pins).

### Example `keyboard_pre_init_user()` Implementation

This example, at the keyboard level, sets up B0, B1, B2, B3, and B4 as LED pins.

```c
void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  gpio_set_pin_output(B0);
  gpio_set_pin_output(B1);
  gpio_set_pin_output(B2);
  gpio_set_pin_output(B3);
  gpio_set_pin_output(B4);
}
```

### `keyboard_pre_init_*` Function Documentation

* Keyboard/Revision: `void keyboard_pre_init_kb(void)`
* Keymap: `void keyboard_pre_init_user(void)`

## Matrix Initialization Code

This is called when the matrix is initialized, and after some of the hardware has been set up, but before many of the features have been initialized.

This is useful for setting up stuff that you may need elsewhere, but isn't hardware related nor is dependant on where it's started.


### `matrix_init_*` Function Documentation

* Keyboard/Revision: `void matrix_init_kb(void)`
* Keymap: `void matrix_init_user(void)`

### Low-level Matrix Overrides Function Documentation {#low-level-matrix-overrides}

* GPIO pin initialisation: `void matrix_init_pins(void)`
  * This needs to perform the low-level initialisation of all row and column pins. By default this will initialise the input/output state of each of the GPIO pins listed in `MATRIX_ROW_PINS` and `MATRIX_COL_PINS`, based on whether or not the keyboard is set up for `ROW2COL`, `COL2ROW`, or `DIRECT_PINS`. Should the keyboard designer override this function, no initialisation of pin state will occur within QMK itself, instead deferring to the keyboard's override.
* `COL2ROW`-based row reads: `void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)`
* `ROW2COL`-based column reads: `void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter)`
* `DIRECT_PINS`-based reads: `void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)`
  * These three functions need to perform the low-level retrieval of matrix state of relevant input pins, based on the matrix type. Only one of the functions should be implemented, if needed. By default this will iterate through `MATRIX_ROW_PINS` and `MATRIX_COL_PINS`, configuring the inputs and outputs based on whether or not the keyboard is set up for `ROW2COL`, `COL2ROW`, or `DIRECT_PINS`. Should the keyboard designer override this function, no manipulation of matrix GPIO pin state will occur within QMK itself, instead deferring to the keyboard's override.

## Keyboard Post Initialization code

This is ran as the very last task in the keyboard initialization process. This is useful if you want to make changes to certain features, as they should be initialized by this point.


### Example `keyboard_post_init_user()` Implementation

This example, running after everything else has initialized, sets up the rgb underglow configuration.

```c
void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}
```

### `keyboard_post_init_*` Function Documentation

* Keyboard/Revision: `void keyboard_post_init_kb(void)`
* Keymap: `void keyboard_post_init_user(void)`

# Matrix Scanning Code

Whenever possible you should customize your keyboard by using `process_record_*()` and hooking into events that way, to ensure that your code does not have a negative performance impact on your keyboard. However, in rare cases it is necessary to hook into the matrix scanning. Be extremely careful with the performance of code in these functions, as it will be called at least 10 times per second.

### Example `matrix_scan_*` Implementation

This example has been deliberately omitted. You should understand enough about QMK internals to write this without an example before hooking into such a performance sensitive area. If you need help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) or [chat with us on Discord](https://discord.gg/Uq7gcHh).

### `matrix_scan_*` Function Documentation

* Keyboard/Revision: `void matrix_scan_kb(void)`
* Keymap: `void matrix_scan_user(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

You should use this function if you need custom matrix scanning code. It can also be used for custom status output (such as LEDs or a display) or other functionality that you want to trigger regularly even when the user isn't typing.

# Keyboard housekeeping

* Keyboard/Revision: `void housekeeping_task_kb(void)`
* Keymap: `void housekeeping_task_user(void)`

This function gets called at the end of all QMK processing, before starting the next iteration. You can safely assume that QMK has dealt with the last matrix scan at the time that these functions are invoked -- layer states have been updated, USB reports have been sent, LEDs have been updated, and displays have been drawn.

Similar to `matrix_scan_*`, these are called as often as the MCU can handle. To keep your board responsive, it's suggested to do as little as possible during these function calls, potentially throtting their behaviour if you do indeed require implementing something special.

### Example `void housekeeping_task_user(void)` implementation

This example will show you how to use `void housekeeping_task_user(void)` to turn off [RGB Light](features/rgblight). For RGB Matrix, the [builtin](features/rgb_matrix#additional-configh-options) `RGB_MATRIX_TIMEOUT` should be used.

First, add the following lines to your keymap's `config.h`:

```c
#define RGBLIGHT_SLEEP  // enable rgblight_suspend() and rgblight_wakeup() in keymap.c
#define RGBLIGHT_TIMEOUT 900000  // ms to wait until rgblight time out, 900K ms is 15min.
```

Next, add the following code to your `keymap.c`:

```c
static uint32_t key_timer;           // timer for last keyboard activity, use 32bit value and function to make longer idle time possible
static void refresh_rgb(void);       // refreshes the activity timer and RGB, invoke whenever any activity happens
static void check_rgb_timeout(void); // checks if enough time has passed for RGB to timeout
bool is_rgb_timeout = false;         // store if RGB has timed out or not in a boolean

void refresh_rgb(void) {
    key_timer = timer_read32(); // store time of last refresh
    if (is_rgb_timeout)
    {
        is_rgb_timeout = false;
        rgblight_wakeup();
    }
}
void check_rgb_timeout(void) {
    if (!is_rgb_timeout && timer_elapsed32(key_timer) > RGBLIGHT_TIMEOUT) // check if RGB has already timeout and if enough time has passed
    {
        rgblight_suspend();
        is_rgb_timeout = true;
    }
}
/* Then, call the above functions from QMK's built in post processing functions like so */
/* Runs at the end of each scan loop, check if RGB timeout has occured or not */
void housekeeping_task_user(void) {
#ifdef RGBLIGHT_TIMEOUT
    check_rgb_timeout();
#endif
}
/* Runs after each key press, check if activity occurred */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_TIMEOUT
    if (record->event.pressed)
        refresh_rgb();
#endif
}
/* Runs after each encoder tick, check if activity occurred */
void post_encoder_update_user(uint8_t index, bool clockwise) {
#ifdef RGBLIGHT_TIMEOUT
    refresh_rgb();
#endif
}
```

# Keyboard Idling/Wake Code

If the board supports it, it can be "idled", by stopping a number of functions.  A good example of this is RGB lights or backlights.   This can save on power consumption, or may be better behavior for your keyboard.

This is controlled by two functions: `suspend_power_down_*` and `suspend_wakeup_init_*`, which are called when the system board is idled and when it wakes up, respectively.


### Example `suspend_power_down_user()` and `suspend_wakeup_init_user()` Implementation


```c
void suspend_power_down_user(void) {
    // code will run multiple times while keyboard is suspended
}

void suspend_wakeup_init_user(void) {
    // code will run on keyboard wakeup
}
```

### Keyboard suspend/wake  Function Documentation

* Keyboard/Revision: `void suspend_power_down_kb(void)` and `void suspend_wakeup_init_user(void)`
* Keymap: `void suspend_power_down_kb(void)` and `void suspend_wakeup_init_user(void)`


# Keyboard Shutdown/Reboot Code {#keyboard-shutdown-reboot-code}

This function gets called whenever the firmware is reset, whether it's a soft reset or reset to the bootloader.  This is the spot to use for any sort of cleanup, as this happens right before the actual reset.  And it can be useful for turning off different systems (such as RGB, onboard screens, etc).

Additionally, it differentiates between the soft reset (eg, rebooting back into the firmware) or jumping to the bootloader.

Certain tasks are performed during shutdown too.  The keyboard is cleared, music and midi is stopped (if enabled), the shutdown chime is triggered (if audio is enabled), and haptic is stopped.

If `jump_to_bootloader` is set to `true`, this indicates that the board will be entering the bootloader for a new firmware flash, whereas `false` indicates that this is happening for a soft reset and will load the firmware agaim immediately (such as when using `QK_REBOOT` or `QK_CLEAR_EEPROM`).

As there is a keyboard and user level function, returning `false` for the user function will disable the keyboard level function, allowing for customization.

::: tip
Bootmagic does not trigger `shutdown_*()` as it happens before most of the initialization process.
:::

### Example `shutdown_kb()` Implementation

```c
bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    
    if (jump_to_bootloader) {
        // red for bootloader
        rgb_matrix_set_color_all(RGB_OFF);
    } else {
        // off for soft reset
        rgb_matrix_set_color_all(RGB_GREEN);
    }
    // force flushing -- otherwise will never happen
    rgb_matrix_update_pwm_buffers();
    return true;
}
```

### Example `shutdown_user()` Implementation

```c
bool shutdown_user(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        // red for bootloader
        rgb_matrix_set_color_all(RGB_RED);
    } else {
        // off for soft reset
        rgb_matrix_set_color_all(RGB_OFF);
    }
    // force flushing -- otherwise will never happen
    rgb_matrix_update_pwm_buffers();
    // false to not process kb level
    return false;
}
```

### Keyboard shutdown/reboot Function Documentation

* Keyboard/Revision: `bool shutdown_kb(bool jump_to_bootloader)`
* Keymap: `bool shutdown_user(bool jump_to_bootloader)`

# Deferred Execution {#deferred-execution}

QMK has the ability to execute a callback after a specified period of time, rather than having to manually manage timers. To enable this functionality, set `DEFERRED_EXEC_ENABLE = yes` in rules.mk.

## Deferred executor callbacks

All _deferred executor callbacks_ have a common function signature and look like:

```c
uint32_t my_callback(uint32_t trigger_time, void *cb_arg) {
    /* do something */
    bool repeat = my_deferred_functionality();
    return repeat ? 500 : 0;
}
```

The first argument `trigger_time` is the intended time of execution. If other delays prevent executing at the exact trigger time, this allows for "catch-up" or even skipping intervals, depending on the required behaviour.

The second argument `cb_arg` is the same argument passed into `defer_exec()` below, and can be used to access state information from the original call context.

The return value is the number of milliseconds to use if the function should be repeated -- if the callback returns `0` then it's automatically unregistered. In the example above, a hypothetical `my_deferred_functionality()` is invoked to determine if the callback needs to be repeated -- if it does, it reschedules for a `500` millisecond delay, otherwise it informs the deferred execution background task that it's done, by returning `0`.

::: tip
Note that the returned delay will be applied to the intended trigger time, not the time of callback invocation. This allows for generally consistent timing even in the face of occasional late execution.
:::

## Deferred executor registration

Once a callback has been defined, it can be scheduled using the following API:

```c
deferred_token my_token = defer_exec(1500, my_callback, NULL);
```

The first argument is the number of milliseconds to wait until executing `my_callback` -- in the case above, `1500` milliseconds, or 1.5 seconds.

The third parameter is the `cb_arg` that gets passed to the callback at the point of execution. This value needs to be valid at the time the callback is invoked -- a local function value will be destroyed before the callback is executed and should not be used. If this is not required, `NULL` should be used.

The return value is a `deferred_token` that can consequently be used to cancel the deferred executor callback before it's invoked. If a failure occurs, the returned value will be `INVALID_DEFERRED_TOKEN`. Usually this will be as a result of supplying `0` to the delay, or a `NULL` for the callback. The other failure case is if there are too many deferred executions "in flight" -- this can be increased by changing the limit, described below.

## Extending a deferred execution

The `deferred_token` returned by `defer_exec()` can be used to extend a the duration a pending execution waits before it gets invoked:
```c
// This will re-delay my_token's future execution such that it is invoked 800ms after the current time
extend_deferred_exec(my_token, 800);
```

## Cancelling a deferred execution

The `deferred_token` returned by `defer_exec()` can be used to cancel a pending execution before it gets invoked:
```c
// This will cancel my_token's future execution
cancel_deferred_exec(my_token);
```

Once a token has been canceled, it should be considered invalid. Reusing the same token is not supported.

## Deferred callback limits

There are a maximum number of deferred callbacks that can be scheduled, controlled by the value of the define `MAX_DEFERRED_EXECUTORS`.

If registrations fail, then you can increase this value in your keyboard or keymap `config.h` file, for example to 16 instead of the default 8:

```c
#define MAX_DEFERRED_EXECUTORS 16
```

# Advanced topics {#advanced-topics}

This page used to encompass a large set of features. We have moved many sections that used to be part of this page to their own pages. Everything below this point is simply a redirect so that people following old links on the web find what they're looking for.

## Layer Change Code {#layer-change-code}

[Layer change code](feature_layers#layer-change-code)

## Persistent Configuration (EEPROM) {#persistent-configuration-eeprom}

[Persistent Configuration (EEPROM)](feature_eeprom)
