# `info.json` Reference :id=info-json-reference

The information contained in `info.json` is combined with the `config.h` and `rules.mk` files, dynamically generating the necessary configuration for your keyboard at compile time. It is also used by the [QMK API](https://github.com/qmk/qmk_api), and contains the information [QMK Configurator](https://config.qmk.fm/) needs to display a representation of your keyboard. Its key/value pairs are ruled by the [`data/schemas/keyboard.jsonschema`](https://github.com/qmk/qmk_firmware/blob/master/data/schemas/keyboard.jsonschema) file. To learn more about the why and how of the schema file see the [Data Driven Configuration](https://docs.qmk.fm/#/data_driven_config) page.

You can create `info.json` files at every level under `qmk_firmware/keyboards/<keyboard_name>`. These files are combined, with more specific files overriding keys in less specific files. This means you do not need to duplicate your metadata information. For example, `qmk_firmware/keyboards/clueboard/info.json` specifies information common to all Clueboard products, such as `manufacturer` and `maintainer`, while `qmk_firmware/keyboards/clueboard/66/info.json` contains more specific information about Clueboard 66%.

## General Metadata :id=general-metadata

* `keyboard_name` (Required)
    * A free-form text string describing the keyboard. This will be used as the USB product string. Can include Unicode characters, escaped to ASCII eg. `\u03A8` (Ψ).
    * Example: `"Clueboard 66%"`
* `maintainer` (Required)
    * GitHub username of the maintainer, or `qmk` for community maintained boards.
    * Example: `"skullydazed"`
* `manufacturer` (Required)
    * A free-form text string describing the keyboard's manufacturer. This will be used as the USB manufacturer string. Can include Unicode characters, escaped to ASCII eg. `\u03A8` (Ψ).
    * Example: `"Clueboard"`
* `url` (Required)
    * A URL to the keyboard's product page, [QMK.fm/keyboards](https://qmk.fm/keyboards) page, or other page describing information about the keyboard.
    * Example: `"https://clueboard.co"`
* `bootloader_instructions`
    * Instructions for putting the keyboard into a mode that allows for firmware flashing.
    * Example: `"Press the button marked RESET on the back of the PCB"`
* `tags`
    * A list of tags describing the keyboard.
    * Example: `["ortho", "split", "rgb"]`

## Hardware Configuration :id=hardware-configuration

* `board`
    * Override the default ChibiOS board name (ARM-based keyboards only).
    * Example: `"BLACKPILL_STM32_F411"`
* `bootloader`
    * The bootloader in use on the keyboard. Required if `development_board` is not specified.
* `development_board`
    * The microcontroller development board, if applicable.
    * Example: `"promicro"`
* `pin_compatible`
    * The form factor of the development board, if applicable. Must be one of `elite_c`, `promicro`.
* `processor`
    * The microcontroller in use on the keyboard. Required if `development_board` is not specified.

## Firmware Configuration :id=firmware-configuration

* `build`
    * `debounce_type`
        * The debounce algorithm to use. Must be one of `asym_eager_defer_pk`, `custom`, `sym_defer_g`, `sym_defer_pk`, `sym_defer_pr`, `sym_eager_pk`, `sym_eager_pr`.
    * `firmware_format`
        * The format of the final output binary. Must be one of `bin`, `hex`, `uf2`.
    * `lto`
        * Enable Link-Time Optimization.
        * Default: `false`
* `features`
    * A dictionary of features to enable or disable.
    * Example:
    ```json
    {
        "rgb_matrix": true,
        "rgblight": false
    }
    ```
* `qmk`
    * `locking`
        * `enabled`
            * Enable locking switch support.
            * Default: `false`
        * `resync`
            * Keep switch state consistent with keyboard LED state.
            * Default: `false`
    * `tap_capslock_delay`
        * The delay between keydown and keyup for Caps Lock tap events in milliseconds.
        * Default: `80` (80 ms)
    * `tap_keycode_delay`
        * The delay between keydown and keyup for tap events in milliseconds.
        * Default: `0` (no delay)
* `tapping`
    * `hold_on_other_key_press`
        * Default: `false`
    * `hold_on_other_key_press_per_key`
        * Default: `false`
    * `permissive_hold`
        * Default: `false`
    * `permissive_hold_per_key`
        * Default: `false`
    * `retro`
        * Default: `false`
    * `retro_per_key`
        * Default: `false`
    * `term`
        * Default: `200` (200 ms)
    * `term_per_key`
        * Default: `false`
    * `toggle`
        * Default: `5`

## APA102 :id=apa102

Configures the [APA102](apa102_driver.md) driver.

* `apa102`
    * `clock_pin` (Required)
        * The GPIO pin connected to `CI` on the first LED in the chain.
    * `data_pin` (Required)
        * The GPIO pin connected to `DI` on the first LED in the chain.
    * `default_brightness`
        * The initial global brightness level (independent of the RGB data), from 0 to 31.
        * Default: `31`

## Audio :id=audio

Configures the [Audio](feature_audio.md) feature.

* `audio`
    * `default`
        * `on`
            * The default audio enabled state.
            * Default: `true`
        * `clicky`
            * The default audio clicky enabled state.
            * Default: `true`
    * `driver`
        * The driver to use. Must be one of `dac_additive`, `dac_basic`, `pwm_software`, `pwm_hardware`.
    * `macro_beep`
        * Play a short beep for `\a` (ASCII `BEL`) characters in Send String macros.
        * Default: `false`
    * `pins` (Required)
        * The GPIO pin(s) connected to the speaker(s).
    * `power_control`
        * `on_state`
            * The logical GPIO state required to turn the speaker on.
            * Default: `1` (on = high)
        * `pin`
            * The GPIO pin connected to speaker power circuit.
    * `voices`
        * Use multiple audio voices.
        * Default: `false`


## Backlight :id=backlight

Configures the [Backlight](feature_backlight.md) feature.

* `backlight`
    * `as_caps_lock`
        * Use the backlight as a Caps Lock indicator.
        * Default: `false`
    * `breathing`
        * Whether backlight breathing is enabled.
        * Default: `false`
    * `breathing_period`
        * The length of one backlight breathing cycle in seconds.
        * Default: `6` (6 seconds)
    * `default`
        * `on`
            * The default backlight enabled state.
            * Default: `true`
        * `breathing`
            * The default backlight breathing state.
            * Default: `false`
        * `brightness`
            * The default brightness level.
            * Default: `max_brightness`
    * `driver`
        * The driver to use. Must be one of `custom`, `pwm`, `software`, `timer`.
        * Default: `"pwm"`
    * `levels`
        * The number of brightness levels (excluding off), from 1 to 31.
        * Default: `3`
    * `max_brightness`
        * The maximum PWM value which brightness is scaled to, from 0 to 255.
        * Default: `255`
    * `on_state`
        * The logical GPIO state required to turn the LEDs on.
        * Default: `1` (on = high)
    * `pin`
        * The GPIO pin connected to the backlight circuit.
    * `pins`
        * A list of GPIO pins connected to the backlight LEDs (`software` and `timer` drivers only).

## Bluetooth :id=bluetooth

Configures the [Bluetooth](feature_bluetooth.md) feature.

* `bluetooth`
    * `driver`
        * The driver to use. Must be one of `custom`, `bluefruit_le`, `rn42`.

## Bootmagic :id=bootmagic

Configures the [Bootmagic](feature_bootmagic.md) feature.

* `bootmagic`
    * `enabled`
        * Enables the Bootmagic feature.
        * Default: `false`
    * `matrix`
        * The matrix position of the key to check during startup. This should generally be set to the (physically) top left key.
        * Default: `[0, 0]`

## Caps Word :id=caps-word

Configures the [Caps Word](feature_caps_word.md) feature.

* `caps_word`
    * `both_shifts_turns_on`
        * Activate Caps Word by pressing both Shift keys.
        * Default: `false`
    * `double_tap_shift_turns_on`
        * Activate Caps Word by pressing Left Shift twice.
        * Default: `false`
    * `enabled`
        * Enables the Caps Word feature.
        * Default: `false`
    * `idle_timeout`
        * The amount of time before Caps Word automatically deactivates in milliseconds.
        * Default: `5000` (5 seconds)
    * `invert_on_shift`
        * Invert shift state instead of deactivating Caps Word when Shift is pressed.
        * Default: `false`

## Combo :id=combo

Configures the [Combo](feature_combo.md) feature.

* `combo`
    * `term`
        * The amount of time to recognize a combo in milliseconds.
        * Default: `50` (50 ms)

## DIP Switches :id=dip-switch

Configures the [DIP Switches](feature_dip_switch.md) feature.

* `dip_switch`
    * `enabled`
        * Enable the DIP Switches feature.
        * Default: `false`
    * `pins`
        * A list of GPIO pins connected to the MCU.
    * `matrix_grid`
        * A list of matrix locations in the key matrix.
        * Example: `[ [0,6], [1,6], [2,6] ]`

## EEPROM :id=eeprom

Configures the [EEPROM](eeprom_driver.md) driver.

* `eeprom`
    * `driver`
        * The EEPROM backend to use. Must be one of `custom`, `i2c`, `legacy_stm32_flash`, `spi`, `transient`, `vendor`, `wear_leveling`.
        * Default: `"vendor"`
    * `wear_leveling`
        * `driver`
            * The driver to use. Must be one of `embedded_flash`, `legacy`, `rp2040_flash`, `spi_flash`, `custom`.
        * `backing_size`
            * Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.
        * `logical_size`
            * Number of bytes “exposed” to the rest of QMK and denotes the size of the usable EEPROM.

## Encoder :id=encoder

Configures the [Encoder](feature_encoders.md) feature.

* `encoder`
    * `rotary`
        * A list of encoder objects.
            * `pin_a` (Required)
                * The GPIO pin connected to the encoder's `A` pin.
            * `pin_b` (Required)
                * The GPIO pin connected to the encoder's `B` pin.
            * `resolution`
                * The number of edge transitions on both pins required to register an input.
                * Default: `4`

## Indicators :id=indicators

Configures the [LED Indicators](feature_led_indicators.md) feature.

* `indicators`
    * `caps_lock`
        * The GPIO pin connected to the Caps Lock LED.
    * `compose`
        * The GPIO pin connected to the Compose LED.
    * `kana`
        * The GPIO pin connected to the Kana LED.
    * `num_lock`
        * The GPIO pin connected to the Num Lock LED.
    * `on_state`
        * The logical GPIO state required to turn the LEDs on.
        * Default: `1` (on = high)
    * `scroll_lock`
        * The GPIO pin connected to the Scroll Lock LED.

## Layouts :id=layouts

The `layouts` portion of the dictionary contains several nested dictionaries. The outer layer consists of QMK layout names, for example `LAYOUT_60_ansi` or `LAYOUT_60_iso`.

Each key dictionary in a layout describes the physical properties of a key. If you are familiar with the Raw Data format for [Keyboard Layout Editor](https://keyboard-layout-editor.com), you will find many of the concepts the same. Key names and layout choices are reused wherever possible, but unlike KLE each key is stateless, inheriting no properties from the keys that came before it.

All key positions and rotations are specified in relation to the top-left corner of the keyboard, and the top-left corner of each key.

The ISO enter key is represented by a 1.25u×2uh key. Renderers which utilize info.json layout data (such as `qmk info -l` and the QMK Configurator) should display this key as expected.

* `community_layouts`
    * A list of community layouts supported by the keyboard.
    * Example: `["60_ansi", "60_iso"]`
* `layout_aliases`
    * A mapping of layout aliases to layout definitions.
    * Example:
    ```json
    {
        "LAYOUT_ansi": "LAYOUT_60_ansi",
        "LAYOUT_iso": "LAYOUT_60_iso"
    }
    ```
* `layouts`
    * A dictionary of layouts supported by the keyboard.
    * `LAYOUT_<layout_name>`
        * `layout`
            * A list of key dictionaries comprising the layout. Each key dictionary contains:
                * `matrix` (Required)
                    * The matrix position for the key.
                    * Example: `[0, 4]` (row 0, column 4)
                * `x` (Required)
                    * The absolute position of the key in the horizontal axis, in key units.
                * `y` (Required)
                    * The absolute position of the key in the vertical axis, in key units.
                * `h`
                    * The height of the key, in key units.
                    * Default: `1` (1u)
                * `label`
                    * What to name the key. This is *not* a key assignment as in the keymap, but should usually correspond to the keycode for the first layer of the default keymap.
                    * Example: `"Escape"`
                * `r`
                    * The rotation angle in degrees. Currently not implemented.
                * `rx`
                    * The absolute X position of the rotation axis. Currently not implemented.
                * `ry`
                    * The absolute Y position of the rotation axis. Currently not implemented.
                * `w`
                    * The width of the key, in key units.
                    * Default: `1` (1u)
                * `encoder`
                    * The index of an encoder this key should be linked to
                * Example: `{"label": "Shift", "matrix": [4, 0], "x": 0, "y": 4.25, "w": 2.25}`

## Leader Key :id=leader-key

Configures the [Leader Key](feature_leader_key.md) feature.

* `leader_key`
    * `timing`
        * Reset the `timeout` on each keypress.
        * Default: `false`
    * `strict_processing`
        * Do not extract the tap keycodes from Layer-Tap and Mod-Tap key events.
        * Default: `false`
    * `timeout`
        * The amount of time to complete a leader sequence in milliseconds.
        * Default: `300` (300 ms)

## LED Matrix :id=led-matrix

Configures the [LED Matrix](feature_led_matrix.md) feature.

* `led_matrix`
    * `animations`
        * A dictionary of effects to enable or disable. Effects which are absent default to `false`.
        * Example:
        ```json
        {
            "alphas_mods": true,
            "breathing": true,
            "cycle_left_right": false
        }
        ```
    * `center_point`
        * The centroid (geometric center) of the LEDs. Used for certain effects.
        * Default: `[112, 32]`
    * `default`
        * `animation`
            * The default effect. Must be one of `led_matrix.animations`
            * Default: `"solid"`
        * `on`
            * The default enabled state.
            * Default: `true`
        * `val`
            * The default brightness level.
            * Default: `max_brightness`
        * `speed`
            * The default animation speed.
            * Default: `128`
    * `driver` (Required)
        * The driver to use. Must be one of `custom`, `is31fl3218`, `is31fl3731`, `is31fl3733`, `is31fl3736`, `is31fl3737`, `is31fl3741`, `is31fl3742a`, `is31fl3743a`, `is31fl3745`, `is31fl3746a`, `snled27351`.
    * `layout` (Required)
        * List of LED configuration dictionaries. Each dictionary contains:
            * `flags` (Required)
                * A bitfield of flags describing the type of LED.
            * `x` (Required)
                * The position of the LED in the horizontal axis, from 0 to 224.
            * `y` (Required)
                * The position of the LED in the vertical axis, from 0 to 64.
            * `matrix`
                * The key matrix position associated with the LED.
                * Example: `[0, 2]`
            * Example: `{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}`
    * `led_flush_limit`
        * Limits in milliseconds how frequently an animation will update the LEDs.
        * Default: `16`
    * `led_process_limit`
        * Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness).
        * Default: `led_count / 5`
    * `max_brightness`
        * The maximum value which brightness is scaled to, from 0 to 255.
        * Default: `255`
    * `react_on_keyup`
        * Animations react to keyup instead of keydown.
        * Default: `false`
    * `sleep`
        * Turn off the LEDs when the host goes to sleep.
        * Default: `false`
    * `speed_steps`
        * The number of speed adjustment steps.
        * Default: `16`
    * `split_count`
        * For split keyboards, the number of LEDs on each half.
        * Example: `[16, 16]`
    * `timeout`
        * The LED activity timeout in milliseconds.
        * Default: `0` (no timeout)
    * `val_steps`
        * The number of brightness adjustment steps.
        * Default: `8`

## Matrix :id=matrix

* `debounce`
    * The debounce time in milliseconds.
    * Default: `5` (5 ms)
* `diode_direction`
    * Which way the diodes are "pointing". Unused for `matrix_pins.direct`. Must be one of `COL2ROW`, `ROW2COL`.
* `matrix_pins`
    * `cols`
        * A list of GPIO pins connected to the matrix columns.
        * Example: `["A0", "A1", "A2"]`
    * `custom`
        * Whether to use a custom matrix scanning implementation.
        * Default: `false`
    * `custom_lite`
        * Whether to use a "lite" custom matrix scanning implementation.
        * Default: `false`
    * `direct`
        * A 2-dimensional list of GPIO pins connected to each keyswitch, forming the "matrix" rows and columns.
        * Example:
        ```json
        [
            ["A0", "A1", "A2"],
            ["B0", "B1", "B2"],
            ["C0", "C1", "C2"]
        ]
        ```
    * `ghost`
        * Whether the matrix has no anti-ghosting diodes.
        * Default: `false`
    * `input_pressed_state`
        * The logical GPIO state of the input pins when a key is pressed.
        * Default: `0` (pressed = low)
    * `io_delay`
        * The amount of time to wait between row/col selection and col/row pin reading, in microseconds.
        * Default: `30` (30 µs)
    * `rows`
        * A list of GPIO pins connected to the matrix rows.
        * Example: `["B0", "B1", "B2"]`

## Mouse Keys :id=mouse-keys

Configures the [Mouse Keys](feature_mouse_keys.md) feature.

* `mouse_key`
    * `delay`
    * `enabled`
        * Enables the Mouse Keys feature.
        * Default: `false`
    * `interval`
    * `max_speed`
    * `time_to_max`
    * `wheel_delay`

## One Shot :id=one-shot

Configures [One Shot keys](one_shot_keys.md).

* `oneshot`
    * `tap_toggle`
        * The number of times to tap the key in order to hold it.
    * `timeout`
        * The amount of time before the key is released in milliseconds.

## PS/2 :id=ps2

Configures the [PS/2](feature_ps2_mouse.md) feature.

* `ps2`
    * `clock_pin`
        * The GPIO pin connected to `CLK` on the PS/2 device.
    * `data_pin`
        * The GPIO pin connected to `DATA` on the PS/2 device.
    * `driver`
        * The PS/2 driver to use. Must be one of `busywait`, `interrupt`, `usart`, `vendor`.
        * Default: `"busywait"`
    * `enabled`
        * Enable the PS/2 feature.
        * Default: `false`
    * `mouse_enabled`
        * Enable the PS/2 mouse handling.
        * Default: `false`

## QMK LUFA Bootloader :id=qmk-lufa-bootloader

* `qmk_lufa_bootloader`
    * `esc_input` (Required)
        * The GPIO pin connected to the designated "exit bootloader" key's row (if `COL2ROW`).
    * `esc_output` (Required)
        * The GPIO pin connected to the designated "exit bootloader" key's column (if `COL2ROW`).
    * `led`
        * The GPIO pin connected to an LED to flash.
    * `speaker`
        * The GPIO pin connected to a speaker to click (can also be used for a second LED).

## RGBLight :id=rgblight

Configures the [RGB Lighting](feature_rgblight.md) feature.

* `rgblight`
    * `led_count` (Required)
        * The number of LEDs in the chain.
    * `animations`
        * A dictionary of effects to enable or disable. Effects which are absent default to `false`.
        * Example:
        ```json
        {
            "breathing": true,
            "rainbow_mood": true,
            "snake": false
        }
        ```
    * `brightness_steps`
        * The number of brightness adjustment steps.
        * Default: `17`
    * `default`
        * `animation`
            * The default effect. Must be one of `rgblight.animations`
            * Default: `"static_light"`
        * `on`
            * The default enabled state.
            * Default: `true`
        * `hue`
            * The default hue value.
            * Default: `0`
        * `sat`
            * The default saturation value.
            * Default: `255`
        * `val`
            * The default brightness level.
            * Default: `max_brightness`
        * `speed`
            * The default animation speed.
            * Default: `0`
    * `driver`
        * The driver to use. Must be one of `apa102`, `custom`, `ws2812`.
        * Default: `"ws2812"`
    * `hue_steps`
        * The number of hue adjustment steps.
        * Default: `8`
    * `layers`
        * `blink`
            * Enable layer blinking API.
            * Default: `false`
        * `enabled`
            * Enable RGB Lighting Layers.
            * Default: `false`
        * `max`
            * The maximum layer count, from 1 to 32.
            * Default: `8`
    * `led_map`
        * Remap LED indices.
        * Example: `[4, 3, 2, 1, 0]`
    * `max_brightness`
        * The maximum value which the HSV "V" component is scaled to, from 0 to 255.
        * Default: `255`
    * `rgbw`
        * Enable RGBW LEDs.
        * Default: `false`
    * `saturation_steps`
        * The number of saturation adjustment steps.
        * Default: `17`
    * `sleep`
        * Turn off the LEDs when the host goes to sleep.
        * Default: `false`
    * `split`
        * Enable synchronization between split halves.
        * Default: `false`
    * `split_count`
        * When `rgblight.split` is enabled, the number of LEDs on each half.
        * Example: `[10, 10]`

## RGB Matrix :id=rgb-matrix

Configures the [RGB Matrix](feature_rgb_matrix.md) feature.

* `rgb_matrix`
    * `animations`
        * A dictionary of effects to enable or disable. Effects which are absent default to `false`.
        * Example:
        ```json
        {
            "alphas_mods": true,
            "breathing": true,
            "cycle_left_right": false
        }
        ```
    * `center_point`
        * The centroid (geometric center) of the LEDs. Used for certain effects.
        * Default: `[112, 32]`
    * `default`
        * `animation`
            * The default effect. Must be one of `rgb_matrix.animations`
            * Default: `"solid_color"`
        * `on`
            * The default enabled state.
            * Default: `true`
        * `hue`
            * The default hue value.
            * Default: `0`
        * `sat`
            * The default saturation value.
            * Default: `255`
        * `val`
            * The default brightness level.
            * Default: `max_brightness`
        * `speed`
            * The default animation speed.
            * Default: `128`
    * `driver` (Required)
        * The driver to use. Must be one of `aw20216s`, `custom`, `is31fl3218`, `is31fl3236`, `is31fl3729`, `is31fl3731`, `is31fl3733`, `is31fl3736`, `is31fl3737`, `is31fl3741`, `is31fl3742a`, `is31fl3743a`, `is31fl3745`, `is31fl3746a`, `snled27351`, `ws2812`.
    * `hue_steps`
        * The number of hue adjustment steps.
        * Default: `8`
    * `layout` (Required)
        * List of LED configuration dictionaries. Each dictionary contains:
            * `flags` (Required)
                * A bitfield of flags describing the type of LED.
            * `x` (Required)
                * The position of the LED in the horizontal axis, from 0 to 224.
            * `y` (Required)
                * The position of the LED in the vertical axis, from 0 to 64.
            * `matrix`
                * The key matrix position associated with the LED.
                * Example: `[0, 2]`
            * Example: `{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}`
    * `led_flush_limit`
        * Limits in milliseconds how frequently an animation will update the LEDs.
        * Default: `16`
    * `led_process_limit`
        * Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness).
        * Default: `led_count / 5`
    * `max_brightness`
        * The maximum value which the HSV "V" component is scaled to, from 0 to 255.
        * Default: `255`
    * `react_on_keyup`
        * Animations react to keyup instead of keydown.
        * Default: `false`
    * `sat_steps`
        * The number of saturation adjustment steps.
        * Default: `16`
    * `sleep`
        * Turn off the LEDs when the host goes to sleep.
        * Default: `false`
    * `speed_steps`
        * The number of speed adjustment steps.
        * Default: `16`
    * `split_count`
        * For split keyboards, the number of LEDs on each half.
        * Example: `[16, 16]`
    * `timeout`
        * The LED activity timeout in milliseconds.
        * Default: `0` (no timeout)
    * `val_steps`
        * The number of brightness adjustment steps.
        * Default: `16`

## Secure :id=secure

Configures the [Secure](feature_secure.md) feature.

* `secure`
    * `enabled`
        * Enable the Secure feature.
        * Default: `false`
    * `idle_timeout`
        * Timeout while unlocked before returning to the locked state. Set to `0` to disable.
        * Default: `60000` (1 minute)
    * `unlock_sequence`
        * A list of up to five matrix locations comprising the "unlock sequence".
        * Example: `[[0, 0], [0, 1], [4, 3]]`
    * `unlock_timeout`
        * Timeout for the user to perform the unlock sequence. Set to `0` to disable.
        * Default: `5000` (5 seconds)

## Split Keyboard :id=split-keyboard

Configures the [Split Keyboard](feature_split_keyboard.md) feature.

* `split`
    * `bootmagic`
        * `matrix`
            * See [Bootmagic](#bootmagic) config.
    * `dip_switch`
        * `right`
            * `pins`
                * See [DIP Switches](#dip-switch) config.
    * `enabled`
        * Enable the Split Keyboard feature.
        * Default: `false`
    * `encoder`
        * `right`
            * `rotary`
                * See [Encoder](#encoder) config.
    * `handedness`
        * `pin`
            * The GPIO pin connected to determine handedness.
        * `matrix_grid`
            * The GPIO pins of the matrix position which determines the handedness.
            * Example: `["A1", "B5"]`
    * `matrix_pins`
        * `right`
            * See [Matrix](#matrix) config.
    * `soft_serial_pin`
        * The GPIO pin to use (`serial` transport protocol only).
    * `soft_serial_speed`
        * The protocol speed, from `0` to `5` (`serial` transport protocol only).
        * Default: `1`
    * `transport`
        * `protocol`
            * The split transport protocol to use. Must be one of `custom`, `i2c`, `serial`, `serial_usart`.
        * `sync`
            * `activity`
                * Mirror the activity timestamps to the secondary half.
                * Default: `false`
            * `detected_os`
                * Mirror the [detected OS](feature_os_detection.md) to the secondary half.
                * Default: `false`
            * `haptic`
                * Mirror the haptic state and process haptic feedback to the secondary half.
                * Default: `false`
            * `layer_state`
                * Mirror the layer state to the secondary half.
                * Default: `false`
            * `indicators`
                * Mirror the indicator state to the secondary half.
                * Default: `false`
            * `matrix_state`
                * Mirror the main/primary half's matrix state to the secondary half.
                * Default: `false`
            * `modifiers`
                * Mirror the modifier state to the secondary half.
                * Default: `false`
            * `oled`
                * Mirror the OLED on/off status to the secondary half.
                * Default: `false`
            * `st7565`
                * Mirror the ST7565 on/off status to the secondary half.
                * Default: `false`
            * `wpm`
                * Mirror the current WPM value to the secondary half.
                * Default: `false`
        * `watchdog`
            * Reboot the secondary half if it loses connection.
            * Default: `false`
        * `watchdog_timeout`
            * The amount of time to wait for communication from the primary half in milliseconds.
    * `usb_detect`
        * `enabled`
            * Detect USB connection when determining split half roles.
        * `polling_interval`
            * The polling frequency in milliseconds.
            * Default: `10` (10 ms)
        * `timeout`
            * The amount of time to wait for a USB connection in milliseconds.
            * Default: `2000` (2 seconds)

## Stenography :id=stenography

Configures the [Stenography](feature_stenography.md) feature.

* `stenography`
    * `enabled`
        * Enable the Stenography feature.
        * Default: `false`
    * `protocol`
        * The Steno protocol to use. Must be one of `all`, `geminipr`, `txbolt`.
        * Default: `"all"`

## USB :id=usb

* `usb`
    * `device_version` (Required)
        * A BCD version number in the format `MM.m.r` (up to `99.9.9`).
        * Example: `"1.0.0"`
    * `pid` (Required)
        * The USB product ID as a four-digit hexadecimal number.
        * Example: `"0x23B0"`
    * `vid` (Required)
        * The USB vendor ID as a four-digit hexadecimal number.
        * Example: `"0xC1ED"`
    * `force_nkro`
        * Force NKRO to be active.
        * Default: `false`
    * `max_power`
        * The maximum current draw the host should expect from the device. This does not control the actual current usage.
        * Default: `500` (500 mA)
    * `no_startup_check`
        * Disable USB suspend check after keyboard startup.
        * Default: `false`
    * `polling_interval`
        * The frequency at which the host should poll the keyboard for reports.
        * Default: `1` (1 ms/1000 Hz)
    * `shared_endpoint`
        * `keyboard`
            * Send keyboard reports through the "shared" USB endpoint.
            * Default: `false`
        * `mouse`
            * Send mouse reports through the "shared" USB endpoint.
            * Default: `true`
    * `suspend_wakeup_delay`
        * The amount of time to wait after sending a wakeup packet, in milliseconds.
        * Default: `0` (disabled)
    * `wait_for_enumeration`
        * Force the keyboard to wait for USB enumeration before starting up.
        * Default: `false`

## WS2812 :id=ws2812

Configures the [WS2812](ws2812_driver.md) driver.

* `ws2812`
    * `driver`
        * The driver to use. Must be one of `bitbang`, `custom`, `i2c`, `pwm`, `spi`, `vendor`.
        * Default: `"bitbang"`
    * `pin` (Required)
        * The GPIO pin connected to `DI` on the first LED in the chain (`bitbang`, `pwm`, `spi` and `vendor` drivers only).
    * `i2c_address`
        * The I²C address of the WS2812 controller (`i2c` driver only).
        * Default: `"0xB0"`
    * `i2c_timeout`
        * The I²C timeout in milliseconds (`i2c` driver only).
        * Default: `100` (100 ms)
