# LED Indicators

?>  Currently, this feature is not supported for split keyboards

QMK provides methods to read 5 of the LEDs defined in the HID spec:

* Num Lock
* Caps Lock
* Scroll Lock
* Compose
* Kana

There are three ways to get the lock LED state:
* by specifying configuration options within `config.h`
* by implementing `bool led_update_kb(led_t led_state)` or `_user(led_t led_state)`; or
* by calling `led_t host_keyboard_led_state()`

!> `host_keyboard_led_state()` may already reflect a new value before `led_update_user()` is called.

Two more deprecated functions exist that provide the LED state as a `uint8_t`:

* `uint8_t led_set_kb(uint8_t usb_led)` and `_user(uint8_t usb_led)`
* `uint8_t host_keyboard_leds()`

## Configuration Options

To configure the indicators, `#define` these in your `config.h`:

|Define               |Default      |Description                                |
|---------------------|-------------|-------------------------------------------|
|`LED_NUM_LOCK_PIN`   |*Not defined*|The pin that controls the `Num Lock` LED   |
|`LED_CAPS_LOCK_PIN`  |*Not defined*|The pin that controls the `Caps Lock` LED  |
|`LED_SCROLL_LOCK_PIN`|*Not defined*|The pin that controls the `Scroll Lock` LED|
|`LED_COMPOSE_PIN`    |*Not defined*|The pin that controls the `Compose` LED    |
|`LED_KANA_PIN`       |*Not defined*|The pin that controls the `Kana` LED       |
|`LED_PIN_ON_STATE`   |`1`          |The state of the indicator pins when the LED is "on" - `1` for high, `0` for low|

Unless you are designing your own keyboard, you generally should not need to change the above config options.

## `led_update_*()`

When the configuration options do not provide enough flexibility, the API hooks provided allow custom control of the LED behavior. These functions will be called when the state of one of those 5 LEDs changes. It receives the LED state as a struct parameter.

By convention, return `true` from `led_update_user()` to get the `led_update_kb()` hook to run its code, and
return `false` when you would prefer not to run the code in `led_update_kb()`.

Some examples include:

  - overriding the LEDs to use them for something else like layer indication
    - return `false` because you do not want the `_kb()` function to run, as it would override your layer behavior.
  - play a sound when an LED turns on or off.
    - return `true` because you want the `_kb` function to run, and this is in addition to the default LED behavior.

?> Because the `led_set_*` functions return `void` instead of `bool`, they do not allow for overriding the keyboard LED control, and thus it's recommended to use `led_update_*` instead.

### Example `led_update_kb()` Implementation

```c
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(B0, !led_state.num_lock);
        writePin(B1, !led_state.caps_lock);
        writePin(B2, !led_state.scroll_lock);
        writePin(B3, !led_state.compose);
        writePin(B4, !led_state.kana);
    }
    return res;
}
```

### Example `led_update_user()` Implementation

This incomplete example would play a sound if Caps Lock is turned on or off. It returns `true`, because you also want the LEDs to maintain their state.

```c
#ifdef AUDIO_ENABLE
  float caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
  float caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

bool led_update_user(led_t led_state) {
    #ifdef AUDIO_ENABLE
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
        led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
        caps_state = led_state.caps_lock;
    }
    #endif
    return true;
}
```

### `led_update_*` Function Documentation

* Keyboard/Revision: `bool led_update_kb(led_t led_state)`
* Keymap: `bool led_update_user(led_t led_state)`

## `host_keyboard_led_state()`

Call this function to get the last received LED state as a `led_t`. This is useful for reading the LED state outside `led_update_*`, e.g. in [`matrix_scan_user()`](#matrix-scanning-code).

## Setting Physical LED State

Some keyboard implementations provide convenience methods for setting the state of the physical LEDs.

### Ergodox Boards

The Ergodox implementations provide `ergodox_right_led_1`/`2`/`3_on`/`off()` to turn individual LEDs on or off, as well as `ergodox_right_led_on`/`off(uint8_t led)` to turn them on or off by their index.

In addition, it is possible to specify the brightness level of all LEDs with `ergodox_led_all_set(uint8_t n)`; of individual LEDs with `ergodox_right_led_1`/`2`/`3_set(uint8_t n)`; or by index with `ergodox_right_led_set(uint8_t led, uint8_t n)`.

Ergodox boards also define `LED_BRIGHTNESS_LO` for the lowest brightness and `LED_BRIGHTNESS_HI` for the highest brightness (which is the default).
