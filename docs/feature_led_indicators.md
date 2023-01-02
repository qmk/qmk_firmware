# LED Indicators

?> LED indicators on split keyboards will require state information synced to the slave half (e.g. `#define SPLIT_LED_STATE_ENABLE`). See [data sync options](feature_split_keyboard.md#data-sync-options) for more details.

QMK provides methods to read 5 of the LEDs defined in the HID spec:

* Num Lock
* Caps Lock
* Scroll Lock
* Compose
* Kana

There are three ways to get the lock LED state:
* Configuration options in `config.h`
* Implement `led_update_*` function
* Call `led_t host_keyboard_led_state()`

!> The `host_keyboard_led_state()` may reflect an updated state before `led_update_user()` is called.

Two deprecated functions that provide the LED state as `uint8_t`:

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

## LED update function

When the configuration options do not provide enough flexibility, the following callbacks allow custom control of the LED behavior. These functions will be called when one of those 5 LEDs changes state: 

* Keyboard/revision: `bool led_update_kb(led_t led_state)`
* Keymap: `bool led_update_user(led_t led_state)`

Both receives LED state as a struct parameter. Returning `true` in `led_update_user()` will allow the keyboard level code in `led_update_kb()` to run as well. Returning `false` will override the keyboard level code, depending on how the keyboard level function is set up.

?> This boolean return type of `led_update_user` allows for overriding keyboard LED controls, and is thus recommended over the void `led_set_user` function.

### Example of keyboard LED update implementation

This is a template indicator function that can be implemented on keyboard level code:

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

### Example of user LED update implementation

This is an incomplete example will play a sound if Caps Lock is turned on or off. It returns `true` to allow keyboard LED function to maintain their state.

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

## Host keyboard LED state 

The `host_keyboard_led_state()` function will report the LED state returned from the host computer as `led_t`. This is useful for reading the LED state outside `led_update_*`. For example, you can get the boolean state of Caps Lock from the host with:

```c
bool caps = host_keyboard_led_state().caps_lock;
```

## `led_update_ports()`

This function writes the LED state to the actual hardware. Call it manually
from your `led_update_*()` callbacks to modify the handling of the standard
keyboard LEDs.
For example when repurposing a standard LED indicator as layer indicator.

## Setting Physical LED State

Some keyboard implementations provide convenient methods for setting the state of the physical LEDs.

### Ergodox Boards

The Ergodox implementations provide `ergodox_right_led_1`/`2`/`3_on`/`off()` to turn individual LEDs on or off, as well as `ergodox_right_led_on`/`off(uint8_t led)` to turn them on or off by their index.

In addition, it is possible to specify the brightness level of all LEDs with `ergodox_led_all_set(uint8_t n)`; of individual LEDs with `ergodox_right_led_1`/`2`/`3_set(uint8_t n)`; or by index with `ergodox_right_led_set(uint8_t led, uint8_t n)`.

Ergodox boards also define `LED_BRIGHTNESS_LO` for the lowest brightness and `LED_BRIGHTNESS_HI` for the highest brightness (which is the default).
