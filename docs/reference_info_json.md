# `info.json` Reference {#info-json-reference}

The information contained in `info.json` is combined with the `config.h` and `rules.mk` files, dynamically generating the necessary configuration for your keyboard at compile time. It is also used by the [QMK API](https://github.com/qmk/qmk_api), and contains the information [QMK Configurator](https://config.qmk.fm/) needs to display a representation of your keyboard. Its key/value pairs are ruled by the [`data/schemas/keyboard.jsonschema`](https://github.com/qmk/qmk_firmware/blob/master/data/schemas/keyboard.jsonschema) file. To learn more about the why and how of the schema file see the [Data Driven Configuration](data_driven_config) page.

You can create `info.json` files at every level under `qmk_firmware/keyboards/<keyboard>`. These files are combined, with more specific files overriding keys in less specific files. This means you do not need to duplicate your metadata information. For example, `qmk_firmware/keyboards/clueboard/info.json` specifies information common to all Clueboard products, such as `manufacturer` and `maintainer`, while `qmk_firmware/keyboards/clueboard/66/info.json` contains more specific information about Clueboard 66%.

## General Metadata {#general-metadata}

* `keyboard_name` <Badge type="info">String</Badge> <Badge>Required</Badge>
    * A free-form text string describing the keyboard. This will be used as the USB product string. Can include Unicode characters, escaped to ASCII eg. `\u03A8` (Ψ).
    * Example: `"Clueboard 66%"`
* `maintainer` <Badge type="info">String</Badge> <Badge>Required</Badge>
    * GitHub username of the maintainer, or `qmk` for community maintained boards.
    * Example: `"skullydazed"`
* `manufacturer` <Badge type="info">String</Badge> <Badge>Required</Badge>
    * A free-form text string describing the keyboard's manufacturer. This will be used as the USB manufacturer string. Can include Unicode characters, escaped to ASCII eg. `\u03A8` (Ψ).
    * Example: `"Clueboard"`
* `url` <Badge type="info">String</Badge> <Badge>Required</Badge>
    * A URL to the keyboard's product page, [QMK Keyboards](https://browse.qmk.fm/) page, or other page describing information about the keyboard.
    * Example: `"https://clueboard.co"`
* `bootloader_instructions` <Badge type="info">String</Badge>
    * Instructions for putting the keyboard into a mode that allows for firmware flashing.
    * Example: `"Press the button marked RESET on the back of the PCB"`
* `tags` <Badge type="info">Array: String</Badge>
    * A list of tags describing the keyboard.
    * Example: `["ortho", "split", "rgb"]`

## Hardware Configuration {#hardware-configuration}

* `board` <Badge type="info">String</Badge>
    * Override the default ChibiOS board name (ARM-based keyboards only).
    * Example: `"BLACKPILL_STM32_F411"`
* `bootloader` <Badge type="info">String</Badge>
    * The bootloader in use on the keyboard. Required if `development_board` is not specified.
* `development_board` <Badge type="info">String</Badge>
    * The microcontroller development board, if applicable.
    * Example: `"promicro"`
* `pin_compatible` <Badge type="info">String</Badge>
    * The form factor of the development board, if applicable. Must be one of `elite_c`, `promicro`.
* `processor` <Badge type="info">String</Badge>
    * The microcontroller in use on the keyboard. Required if `development_board` is not specified.

## Firmware Configuration {#firmware-configuration}

* `build`
    * `debounce_type`<Badge type="info">String</Badge>
        * The debounce algorithm to use. Must be one of `asym_eager_defer_pk`, `custom`, `sym_defer_g`, `sym_defer_pk`, `sym_defer_pr`, `sym_eager_pk`, `sym_eager_pr`.
    * `firmware_format`<Badge type="info">String</Badge>
        * The format of the final output binary. Must be one of `bin`, `hex`, `uf2`.
    * `lto`<Badge type="info">Boolean</Badge>
        * Enable Link-Time Optimization.
        * Default: `false`
* `features`<Badge type="info">Object: Boolean</Badge>
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
        * `enabled` <Badge type="info">Boolean</Badge>
            * Enable locking switch support.
            * Default: `false`
        * `resync` <Badge type="info">Boolean</Badge>
            * Keep switch state consistent with keyboard LED state.
            * Default: `false`
    * `tap_capslock_delay` <Badge type="info">Number</Badge>
        * The delay between keydown and keyup for Caps Lock tap events in milliseconds.
        * Default: `80` (80 ms)
    * `tap_keycode_delay` <Badge type="info">Number</Badge>
        * The delay between keydown and keyup for tap events in milliseconds.
        * Default: `0` (no delay)
* `tapping`
    * `chordal_hold` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `hold_on_other_key_press` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `hold_on_other_key_press_per_key` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `permissive_hold` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `permissive_hold_per_key` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `retro` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `retro_per_key` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `term` <Badge type="info">Number</Badge>
        * Default: `200` (200 ms)
    * `term_per_key` <Badge type="info">Boolean</Badge>
        * Default: `false`
    * `toggle` <Badge type="info">Number</Badge>
        * Default: `5`

## APA102 {#apa102}

Configures the [APA102](drivers/apa102) driver.

* `apa102`
    * `clock_pin` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
        * The GPIO pin connected to `CI` on the first LED in the chain.
    * `data_pin` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
        * The GPIO pin connected to `DI` on the first LED in the chain.
    * `default_brightness` <Badge type="info">Number</Badge>
        * The initial global brightness level (independent of the RGB data), from 0 to 31.
        * Default: `31`

## Audio {#audio}

Configures the [Audio](features/audio) feature.

* `audio`
    * `default`
        * `on` <Badge type="info">Boolean</Badge>
            * The default audio enabled state.
            * Default: `true`
        * `clicky` <Badge type="info">Boolean</Badge>
            * The default audio clicky enabled state.
            * Default: `true`
    * `driver` <Badge type="info">String</Badge>
        * The driver to use. Must be one of `dac_additive`, `dac_basic`, `pwm_software`, `pwm_hardware`.
    * `macro_beep` <Badge type="info">Boolean</Badge>
        * Play a short beep for `\a` (ASCII `BEL`) characters in Send String macros.
        * Default: `false`
    * `pins` <Badge type="info">Array: Pin</Badge> <Badge>Required</Badge>
        * The GPIO pin(s) connected to the speaker(s).
    * `power_control`
        * `on_state` <Badge type="info">0|1</Badge>
            * The logical GPIO state required to turn the speaker on.
            * Default: `1` (on = high)
        * `pin` <Badge type="info">Pin</Badge>
            * The GPIO pin connected to speaker power circuit.
    * `voices` <Badge type="info">Boolean</Badge>
        * Use multiple audio voices.
        * Default: `false`


## Backlight {#backlight}

Configures the [Backlight](features/backlight) feature.

* `backlight`
    * `as_caps_lock` <Badge type="info">Boolean</Badge>
        * Use the backlight as a Caps Lock indicator.
        * Default: `false`
    * `breathing` <Badge type="info">Boolean</Badge>
        * Whether backlight breathing is enabled.
        * Default: `false`
    * `breathing_period` <Badge type="info">Number</Badge>
        * The length of one backlight breathing cycle in seconds.
        * Default: `6` (6 seconds)
    * `default`
        * `on` <Badge type="info">Boolean</Badge>
            * The default backlight enabled state.
            * Default: `true`
        * `breathing` <Badge type="info">Boolean</Badge>
            * The default backlight breathing state.
            * Default: `false`
        * `brightness` <Badge type="info">Number</Badge>
            * The default brightness level.
            * Default: `max_brightness`
    * `driver` <Badge type="info">String</Badge>
        * The driver to use. Must be one of `custom`, `pwm`, `software`, `timer`.
        * Default: `"pwm"`
    * `levels` <Badge type="info">Number</Badge>
        * The number of brightness levels (excluding off), from 1 to 31.
        * Default: `3`
    * `max_brightness` <Badge type="info">Number</Badge>
        * The maximum PWM value which brightness is scaled to, from 0 to 255.
        * Default: `255`
    * `on_state` <Badge type="info">0|1</Badge>
        * The logical GPIO state required to turn the LEDs on.
        * Default: `1` (on = high)
    * `pin` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to the backlight circuit.
    * `pins` <Badge type="info">Array: Pin</Badge>
        * A list of GPIO pins connected to the backlight LEDs (`software` and `timer` drivers only).

## Battery

Configures the [Battery](features/battery) feature.

* `battery`
    * `adc`
        * `pin` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
            * The GPIO pin connected to the voltage divider.
        * `reference_voltage` <Badge type="info">Number</Badge>
            * The ADC reverence voltage, in millivolts. 
            * Default: `3300`
        * `divider_r1` <Badge type="info">Number</Badge>
            * The voltage divider resistance, in kOhm. Set to 0 to disable.
            * Default: `100`
        * `divider_r2` <Badge type="info">Number</Badge>
            * The voltage divider resistance, in kOhm. Set to 0 to disable.
            * Default: `100`
        * `resolution` <Badge type="info">Number</Badge>
            * The ADC resolution configured for the ADC Driver.
            * Default: `10`
    * `driver` <Badge type="info">String</Badge> <Badge>Required</Badge>
        * The driver to use. Must be one of `adc`, `custom`, `vendor`.
    * `sample_interval` <Badge type="info">Number</Badge>
        * The delay between sampling the battery in milliseconds.
        * Default: `30000` (30 s)

## Wireless/Bluetooth {#bluetooth}

Configures the [Wireless](features/wireless) feature.

* `bluetooth`
    * `driver` <Badge type="info">String</Badge>
        * The driver to use. Must be one of `custom`, `bluefruit_le`, `rn42`.

## Bootmagic {#bootmagic}

Configures the [Bootmagic](features/bootmagic) feature.

* `bootmagic`
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enables the Bootmagic feature.
        * Default: `false`
    * `matrix` <Badge type="info">Matrix</Badge>
        * The matrix position of the key to check during startup. This should generally be set to the (physically) top left key.
        * Default: `[0, 0]`

## Caps Word {#caps-word}

Configures the [Caps Word](features/caps_word) feature.

* `caps_word`
    * `both_shifts_turns_on` <Badge type="info">Boolean</Badge>
        * Activate Caps Word by pressing both Shift keys.
        * Default: `false`
    * `double_tap_shift_turns_on` <Badge type="info">Boolean</Badge>
        * Activate Caps Word by pressing Left Shift twice.
        * Default: `false`
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enables the Caps Word feature.
        * Default: `false`
    * `idle_timeout` <Badge type="info">Number</Badge>
        * The amount of time before Caps Word automatically deactivates in milliseconds.
        * Default: `5000` (5 seconds)
    * `invert_on_shift` <Badge type="info">Boolean</Badge>
        * Invert shift state instead of deactivating Caps Word when Shift is pressed.
        * Default: `false`

## Combo {#combo}

Configures the [Combo](features/combo) feature.

* `combo`
    * `term` <Badge type="info">Number</Badge>
        * The amount of time to recognize a combo in milliseconds.
        * Default: `50` (50 ms)

## DIP Switches {#dip-switch}

Configures the [DIP Switches](features/dip_switch) feature.

* `dip_switch`
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enable the DIP Switches feature.
        * Default: `false`
    * `pins` <Badge type="info">Array: Pin</Badge>
        * A list of GPIO pins connected to the MCU.
    * `matrix_grid` <Badge type="info">Array: Matrix</Badge>
        * A list of matrix locations in the key matrix.
        * Example: `[ [0,6], [1,6], [2,6] ]`

## EEPROM {#eeprom}

Configures the [EEPROM](drivers/eeprom) driver.

* `eeprom`
    * `driver` <Badge type="info">String</Badge>
        * The EEPROM backend to use. Must be one of `custom`, `i2c`, `legacy_stm32_flash`, `spi`, `transient`, `vendor`, `wear_leveling`.
        * Default: `"vendor"`
    * `wear_leveling`
        * `driver` <Badge type="info">String</Badge>
            * The driver to use. Must be one of `embedded_flash`, `legacy`, `rp2040_flash`, `spi_flash`, `custom`.
        * `backing_size` <Badge type="info">Number</Badge>
            * Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.
        * `logical_size` <Badge type="info">Number</Badge>
            * Number of bytes “exposed” to the rest of QMK and denotes the size of the usable EEPROM.

## Encoder {#encoder}

Configures the [Encoder](features/encoders) feature.

* `encoder`
    * `rotary` <Badge type="info">Array: Object</Badge>
        * A list of encoder objects.
            * `pin_a` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
                * The GPIO pin connected to the encoder's `A` pin.
            * `pin_b` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
                * The GPIO pin connected to the encoder's `B` pin.
            * `resolution` <Badge type="info">Number</Badge>
                * The number of edge transitions on both pins required to register an input.
                * Default: `4`

## Host {#host}

* `host`
    * `default`
        * `nkro` <Badge type="info">Boolean</Badge>
            * The default nkro state.
            * Default: `false`

## Indicators {#indicators}

Configures the [LED Indicators](features/led_indicators) feature.

* `indicators`
    * `caps_lock` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to the Caps Lock LED.
    * `compose` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to the Compose LED.
    * `kana` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to the Kana LED.
    * `num_lock` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to the Num Lock LED.
    * `on_state` <Badge type="info">0|1</Badge>
        * The logical GPIO state required to turn the LEDs on.
        * Default: `1` (on = high)
    * `scroll_lock` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to the Scroll Lock LED.

## (Custom) Keycodes {#keycodes}

Defines [custom keycodes](custom_quantum_functions#definining-a-new-keycode) for use within keymaps.

* `keycodes` <Badge type="info">Array: Object</Badge>
    * A list of keycode objects.
        * `key` <Badge type="info">String</Badge> <Badge>Required</Badge>
            * The enum name of the custom keycode. 
            * Example: `LAYER_CHANGE_BEEP_ON`
        * `label` <Badge type="info">String</Badge>
            * A short description of the custom keycode.
        * `aliases` <Badge type="info">Array: String</Badge>
            * A list of shortened names for the custom keycode.
            * Example: `["LCBON", "LCB_ON"]`

## Layouts {#layouts}

The `layouts` portion of the dictionary contains several nested dictionaries. The outer layer consists of QMK layout names, for example `LAYOUT_60_ansi` or `LAYOUT_60_iso`.

Each key dictionary in a layout describes the physical properties of a key. If you are familiar with the Raw Data format for [Keyboard Layout Editor](https://keyboard-layout-editor.com), you will find many of the concepts the same. Key names and layout choices are reused wherever possible, but unlike KLE each key is stateless, inheriting no properties from the keys that came before it.

All key positions and rotations are specified in relation to the top-left corner of the keyboard, and the top-left corner of each key.

The ISO enter key is represented by a 1.25u×2uh key. Renderers which utilize info.json layout data (such as `qmk info -l` and the QMK Configurator) should display this key as expected.

* `community_layouts` <Badge type="info">Array: String</Badge>
    * A list of community layouts supported by the keyboard.
    * Example: `["60_ansi", "60_iso"]`
* `layout_aliases` <Badge type="info">Object: String</Badge>
    * A mapping of layout aliases to layout definitions.
    * Example:
    ```json
    {
        "LAYOUT_ansi": "LAYOUT_60_ansi",
        "LAYOUT_iso": "LAYOUT_60_iso"
    }
    ```
* `layouts` <Badge type="info">Object</Badge>
    * A dictionary of layouts supported by the keyboard.
    * `LAYOUT_<layout_name>` <Badge type="info">Object</Badge>
        * `layout` <Badge type="info">Array: Object</Badge>
            * A list of key dictionaries comprising the layout. Each key dictionary contains:
                * `matrix` <Badge type="info">Matrix</Badge> <Badge>Required</Badge>
                    * The matrix position for the key.
                    * Example: `[0, 4]` (row 0, column 4)
                * `x` <Badge type="info">KeyUnit</Badge> <Badge>Required</Badge>
                    * The absolute position of the key in the horizontal axis, in key units.
                * `y` <Badge type="info">KeyUnit</Badge> <Badge>Required</Badge>
                    * The absolute position of the key in the vertical axis, in key units.
                * `h` <Badge type="info">KeyUnit</Badge>
                    * The height of the key, in key units.
                    * Default: `1` (1u)
                * `hand` <Badge type="info">String</Badge>
                    * The handedness of the key for Chordal Hold, either `"L"` (left hand), `"R"` (right hand), or `"*"` (either or exempted handedness).
                * `label` <Badge type="info">String</Badge>
                    * What to name the key. This is *not* a key assignment as in the keymap, but should usually correspond to the keycode for the first layer of the default keymap.
                    * Example: `"Escape"`
                * `r` <Badge type="info">Number</Badge>
                    * The rotation angle in degrees. Currently not implemented.
                * `rx` <Badge type="info">Number</Badge>
                    * The absolute X position of the rotation axis. Currently not implemented.
                * `ry` <Badge type="info">Number</Badge>
                    * The absolute Y position of the rotation axis. Currently not implemented.
                * `w` <Badge type="info">KeyUnit</Badge>
                    * The width of the key, in key units.
                    * Default: `1` (1u)
                * `encoder` <Badge type="info">Number</Badge>
                    * The index of an encoder this key should be linked to
                * Example: `{"label": "Shift", "matrix": [4, 0], "x": 0, "y": 4.25, "w": 2.25}`

## Leader Key {#leader-key}

Configures the [Leader Key](features/leader_key) feature.

* `leader_key`
    * `timing` <Badge type="info">Boolean</Badge>
        * Reset the `timeout` on each keypress.
        * Default: `false`
    * `strict_processing` <Badge type="info">Boolean</Badge>
        * Do not extract the tap keycodes from Layer-Tap and Mod-Tap key events.
        * Default: `false`
    * `timeout` <Badge type="info">Number</Badge>
        * The amount of time to complete a leader sequence in milliseconds.
        * Default: `300` (300 ms)

## LED Matrix {#led-matrix}

Configures the [LED Matrix](features/led_matrix) feature.

* `led_matrix`
    * `animations` <Badge type="info">Object: Boolean</Badge>
        * A dictionary of effects to enable or disable. Effects which are absent default to `false`.
        * Example:
        ```json
        {
            "alphas_mods": true,
            "breathing": true,
            "cycle_left_right": false
        }
        ```
    * `center_point` <Badge type="info">Array: Number</Badge>
        * The centroid (geometric center) of the LEDs. Used for certain effects.
        * Default: `[112, 32]`
    * `flag_steps` <Badge type="info">Array: Number</Badge>
        * A list of flag bitfields that can be cycled through.
        * Default: `[255, 5, 0]`
    * `default`
        * `animation` <Badge type="info">String</Badge>
            * The default effect. Must be one of `led_matrix.animations`
            * Default: `"solid"`
        * `on` <Badge type="info">Boolean</Badge>
            * The default enabled state.
            * Default: `true`
        * `val` <Badge type="info">Number</Badge>
            * The default brightness level.
            * Default: `max_brightness`
        * `speed` <Badge type="info">Number</Badge>
            * The default animation speed.
            * Default: `128`
        * `flags` <Badge type="info">Number</Badge>
            * The default LED flags.
            * Default: `255`
    * `driver` <Badge type="info">String</Badge> <Badge>Required</Badge>
        * The driver to use. Must be one of `custom`, `is31fl3218`, `is31fl3731`, `is31fl3733`, `is31fl3736`, `is31fl3737`, `is31fl3741`, `is31fl3742a`, `is31fl3743a`, `is31fl3745`, `is31fl3746a`, `snled27351`.
    * `layout` <Badge type="info">Array: Object</Badge> <Badge>Required</Badge>
        * List of LED configuration dictionaries. Each dictionary contains:
            * `flags` <Badge type="info">Number</Badge> <Badge>Required</Badge>
                * A bitfield of flags describing the type of LED.
            * `x` <Badge type="info">Number</Badge> <Badge>Required</Badge>
                * The position of the LED in the horizontal axis, from 0 to 224.
            * `y` <Badge type="info">Number</Badge> <Badge>Required</Badge>
                * The position of the LED in the vertical axis, from 0 to 64.
            * `matrix` <Badge type="info">Matrix</Badge>
                * The key matrix position associated with the LED.
                * Example: `[0, 2]`
            * Example: `{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}`
    * `led_flush_limit` <Badge type="info">Number</Badge>
        * Limits in milliseconds how frequently an animation will update the LEDs.
        * Default: `16`
    * `led_process_limit` <Badge type="info">Number</Badge>
        * Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness).
        * Default: `(led_count + 4) / 5`
    * `max_brightness` <Badge type="info">Number</Badge>
        * The maximum value which brightness is scaled to, from 0 to 255.
        * Default: `255`
    * `react_on_keyup` <Badge type="info">Boolean</Badge>
        * Animations react to keyup instead of keydown.
        * Default: `false`
    * `sleep` <Badge type="info">Boolean</Badge>
        * Turn off the LEDs when the host goes to sleep.
        * Default: `false`
    * `speed_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the speed.
        * Default: `16`
    * `split_count` <Badge type="info">Array: Number</Badge>
        * For split keyboards, the number of LEDs on each half.
        * Example: `[16, 16]`
    * `timeout` <Badge type="info">Number</Badge>
        * The LED activity timeout in milliseconds.
        * Default: `0` (no timeout)
    * `val_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the brightness.
        * Default: `8`

## Matrix {#matrix}

* `debounce` <Badge type="info">Number</Badge>
    * The debounce time in milliseconds.
    * Default: `5` (5 ms)
* `diode_direction` <Badge type="info">String</Badge>
    * Which way the diodes are "pointing". Unused for `matrix_pins.direct`. Must be one of `COL2ROW`, `ROW2COL`.
* `matrix_pins`
    * `cols` <Badge type="info">Array: Pin</Badge>
        * A list of GPIO pins connected to the matrix columns.
        * Example: `["A0", "A1", "A2"]`
    * `custom` <Badge type="info">Boolean</Badge>
        * Whether to use a custom matrix scanning implementation.
        * Default: `false`
    * `custom_lite` <Badge type="info">Boolean</Badge>
        * Whether to use a "lite" custom matrix scanning implementation.
        * Default: `false`
    * `direct` <Badge type="info">Array: Array: Pin</Badge>
        * A 2-dimensional list of GPIO pins connected to each keyswitch, forming the "matrix" rows and columns.
        * Example:
        ```json
        [
            ["A0", "A1", "A2"],
            ["B0", "B1", "B2"],
            ["C0", "C1", "C2"]
        ]
        ```
    * `ghost` <Badge type="info">Boolean</Badge>
        * Whether the matrix has no anti-ghosting diodes.
        * Default: `false`
    * `input_pressed_state` <Badge type="info">0|1</Badge>
        * The logical GPIO state of the input pins when a key is pressed.
        * Default: `0` (pressed = low)
    * `io_delay` <Badge type="info">Number</Badge>
        * The amount of time to wait between row/col selection and col/row pin reading, in microseconds.
        * Default: `30` (30 µs)
    * `masked` <Badge type="info">Boolean</Badge>
        * Whether unconfigured intersections should be ignored.
        * Default: `false`
    * `rows` <Badge type="info">Array: Pin</Badge>
        * A list of GPIO pins connected to the matrix rows.
        * Example: `["B0", "B1", "B2"]`

## Mouse Keys {#mouse-keys}

Configures the [Mouse Keys](features/mouse_keys) feature.

* `mouse_key`
    * `delay` <Badge type="info">Number</Badge>
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enables the Mouse Keys feature.
        * Default: `false`
    * `interval` <Badge type="info">Number</Badge>
    * `max_speed` <Badge type="info">Number</Badge>
    * `time_to_max` <Badge type="info">Number</Badge>
    * `wheel_delay` <Badge type="info">Number</Badge>

## One Shot {#one-shot}

Configures [One Shot keys](one_shot_keys).

* `oneshot`
    * `tap_toggle` <Badge type="info">Number</Badge>
        * The number of times to tap the key in order to hold it.
    * `timeout` <Badge type="info">Number</Badge>
        * The amount of time before the key is released in milliseconds.

## PS/2 {#ps2}

Configures the [PS/2](features/ps2_mouse) feature.

* `ps2`
    * `clock_pin` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to `CLK` on the PS/2 device.
    * `data_pin` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to `DATA` on the PS/2 device.
    * `driver` <Badge type="info">String</Badge>
        * The PS/2 driver to use. Must be one of `busywait`, `interrupt`, `usart`, `vendor`.
        * Default: `"busywait"`
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enable the PS/2 feature.
        * Default: `false`
    * `mouse_enabled` <Badge type="info">Boolean</Badge>
        * Enable the PS/2 mouse handling.
        * Default: `false`

## QMK LUFA Bootloader {#qmk-lufa-bootloader}

* `qmk_lufa_bootloader`
    * `esc_input` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
        * The GPIO pin connected to the designated "exit bootloader" key's row (if `COL2ROW`).
    * `esc_output` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
        * The GPIO pin connected to the designated "exit bootloader" key's column (if `COL2ROW`).
    * `led` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to an LED to flash.
    * `speaker` <Badge type="info">Pin</Badge>
        * The GPIO pin connected to a speaker to click (can also be used for a second LED).

## RGBLight {#rgblight}

Configures the [RGB Lighting](features/rgblight) feature.

* `rgblight`
    * `led_count` <Badge type="info">Number</Badge> <Badge>Required</Badge>
        * The number of LEDs in the chain.
    * `animations` <Badge type="info">Object: Boolean</Badge>
        * A dictionary of effects to enable or disable. Effects which are absent default to `false`.
        * Example:
        ```json
        {
            "breathing": true,
            "rainbow_mood": true,
            "snake": false
        }
        ```
    * `brightness_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the brightness.
        * Default: `17`
    * `default`
        * `animation` <Badge type="info">String</Badge>
            * The default effect. Must be one of `rgblight.animations`
            * Default: `"static_light"`
        * `on` <Badge type="info">Boolean</Badge>
            * The default enabled state.
            * Default: `true`
        * `hue` <Badge type="info">Number</Badge>
            * The default hue value.
            * Default: `0`
        * `sat` <Badge type="info">Number</Badge>
            * The default saturation value.
            * Default: `255`
        * `val` <Badge type="info">Number</Badge>
            * The default brightness level.
            * Default: `max_brightness`
        * `speed` <Badge type="info">Number</Badge>
            * The default animation speed.
            * Default: `0`
    * `driver` <Badge type="info">String</Badge>
        * The driver to use. Must be one of `apa102`, `custom`, `ws2812`.
        * Default: `"ws2812"`
    * `hue_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the hue.
        * Default: `8`
    * `layers`
        * `blink` <Badge type="info">Boolean</Badge>
            * Enable layer blinking API.
            * Default: `false`
        * `enabled` <Badge type="info">Boolean</Badge>
            * Enable RGB Lighting Layers.
            * Default: `false`
        * `max` <Badge type="info">Number</Badge>
            * The maximum layer count, from 1 to 32.
            * Default: `8`
    * `led_map` <Badge type="info">Array: Number</Badge>
        * Remap LED indices.
        * Example: `[4, 3, 2, 1, 0]`
    * `max_brightness` <Badge type="info">Number</Badge>
        * The maximum value which the HSV "V" component is scaled to, from 0 to 255.
        * Default: `255`
    * `saturation_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the suturation.
        * Default: `17`
    * `sleep` <Badge type="info">Boolean</Badge>
        * Turn off the LEDs when the host goes to sleep.
        * Default: `false`
    * `split` <Badge type="info">Boolean</Badge>
        * Enable synchronization between split halves.
        * Default: `false`
    * `split_count` <Badge type="info">Array: Number</Badge>
        * When `rgblight.split` is enabled, the number of LEDs on each half.
        * Example: `[10, 10]`

## RGB Matrix {#rgb-matrix}

Configures the [RGB Matrix](features/rgb_matrix) feature.

* `rgb_matrix`
    * `animations` <Badge type="info">Object: Boolean</Badge>
        * A dictionary of effects to enable or disable. Effects which are absent default to `false`.
        * Example:
        ```json
        {
            "alphas_mods": true,
            "breathing": true,
            "cycle_left_right": false
        }
        ```
    * `center_point` <Badge type="info">Array: Number</Badge>
        * The centroid (geometric center) of the LEDs. Used for certain effects.
        * Default: `[112, 32]`
    * `flag_steps` <Badge type="info">Array: Number</Badge>
        * A list of flag bitfields that can be cycled through.
        * Default: `[255, 5, 2, 0]`
    * `default`
        * `animation` <Badge type="info">String</Badge>
            * The default effect. Must be one of `rgb_matrix.animations`
            * Default: `"solid_color"`
        * `on` <Badge type="info">Boolean</Badge>
            * The default enabled state.
            * Default: `true`
        * `hue` <Badge type="info">Number</Badge>
            * The default hue value.
            * Default: `0`
        * `sat` <Badge type="info">Number</Badge>
            * The default saturation value.
            * Default: `255`
        * `val` <Badge type="info">Number</Badge>
            * The default brightness level.
            * Default: `max_brightness`
        * `speed` <Badge type="info">Number</Badge>
            * The default animation speed.
            * Default: `128`
        * `flags` <Badge type="info">Number</Badge>
            * The default LED flags.
            * Default: `255`
    * `driver` <Badge type="info">String</Badge> <Badge>Required</Badge>
        * The driver to use. Must be one of `aw20216s`, `custom`, `is31fl3218`, `is31fl3236`, `is31fl3729`, `is31fl3731`, `is31fl3733`, `is31fl3736`, `is31fl3737`, `is31fl3741`, `is31fl3742a`, `is31fl3743a`, `is31fl3745`, `is31fl3746a`, `snled27351`, `ws2812`.
    * `hue_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the hue.
        * Default: `8`
    * `layout` <Badge type="info">Array: Object</Badge> <Badge>Required</Badge>
        * List of LED configuration dictionaries. Each dictionary contains:
            * `flags` <Badge type="info">Number</Badge> <Badge>Required</Badge>
                * A bitfield of flags describing the type of LED.
            * `x` <Badge type="info">Number</Badge> <Badge>Required</Badge>
                * The position of the LED in the horizontal axis, from 0 to 224.
            * `y` <Badge type="info">Number</Badge> <Badge>Required</Badge>
                * The position of the LED in the vertical axis, from 0 to 64.
            * `matrix` <Badge type="info">Matrix</Badge>
                * The key matrix position associated with the LED.
                * Example: `[0, 2]`
            * Example: `{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}`
    * `led_flush_limit` <Badge type="info">Number</Badge>
        * Limits in milliseconds how frequently an animation will update the LEDs.
        * Default: `16`
    * `led_process_limit` <Badge type="info">Number</Badge>
        * Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness).
        * Default: `(led_count + 4) / 5`
    * `max_brightness` <Badge type="info">Number</Badge>
        * The maximum value which the HSV "V" component is scaled to, from 0 to 255.
        * Default: `255`
    * `react_on_keyup` <Badge type="info">Boolean</Badge>
        * Animations react to keyup instead of keydown.
        * Default: `false`
    * `sat_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the saturation.
        * Default: `16`
    * `sleep` <Badge type="info">Boolean</Badge>
        * Turn off the LEDs when the host goes to sleep.
        * Default: `false`
    * `speed_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the speed.
        * Default: `16`
    * `split_count` <Badge type="info">Array: Number</Badge>
        * For split keyboards, the number of LEDs on each half.
        * Example: `[16, 16]`
    * `timeout` <Badge type="info">Number</Badge>
        * The LED activity timeout in milliseconds.
        * Default: `0` (no timeout)
    * `val_steps` <Badge type="info">Number</Badge>
        * The value by which to increment the brightness.
        * Default: `16`

## Secure {#secure}

Configures the [Secure](features/secure) feature.

* `secure`
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enable the Secure feature.
        * Default: `false`
    * `idle_timeout` <Badge type="info">Number</Badge>
        * Timeout while unlocked before returning to the locked state. Set to `0` to disable.
        * Default: `60000` (1 minute)
    * `unlock_sequence` <Badge type="info">Array: Matrix</Badge>
        * A list of up to five matrix locations comprising the "unlock sequence".
        * Example: `[[0, 0], [0, 1], [4, 3]]`
    * `unlock_timeout` <Badge type="info">Number</Badge>
        * Timeout for the user to perform the unlock sequence. Set to `0` to disable.
        * Default: `5000` (5 seconds)

## Split Keyboard {#split-keyboard}

Configures the [Split Keyboard](features/split_keyboard) feature.

* `split`
    * `bootmagic`
        * `matrix`
            * See [Bootmagic](#bootmagic) config.
    * `dip_switch`
        * `right`
            * `pins`
                * See [DIP Switches](#dip-switch) config.
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enable the Split Keyboard feature.
        * Default: `false`
    * `encoder`
        * `right`
            * `rotary`
                * See [Encoder](#encoder) config.
    * `handedness`
        * `pin` <Badge type="info">Pin</Badge>
            * The GPIO pin connected to determine handedness.
        * `matrix_grid` <Badge type="info">Array: Pin</Badge>
            * The GPIO pins of the matrix position which determines the handedness.
            * Example: `["A1", "B5"]`
    * `matrix_pins`
        * `right`
            * See [Matrix](#matrix) config.
    * `serial`
        * `driver` <Badge type="info">String</Badge>
            * The driver to use. Must be one of `bitbang`, `usart`, `vendor`.
            * Default: `"bitbang"`
        * `pin` <Badge type="info">Pin</Badge>
            * The GPIO pin to use for transmit and receive.
        * `speed` <Badge type="info">Number</Badge>
            * The protocol speed, from `0` to `5` (fastest to slowest).
            * Default: `1`
    * `transport`
        * `protocol` <Badge type="info">String</Badge>
            * The split transport protocol to use. Must be one of `custom`, `i2c`, `serial`.
        * `sync`
            * `activity` <Badge type="info">Boolean</Badge>
                * Mirror the activity timestamps to the secondary half.
                * Default: `false`
            * `detected_os` <Badge type="info">Boolean</Badge>
                * Mirror the [detected OS](features/os_detection) to the secondary half.
                * Default: `false`
            * `haptic` <Badge type="info">Boolean</Badge>
                * Mirror the haptic state and process haptic feedback to the secondary half.
                * Default: `false`
            * `layer_state` <Badge type="info">Boolean</Badge>
                * Mirror the layer state to the secondary half.
                * Default: `false`
            * `indicators` <Badge type="info">Boolean</Badge>
                * Mirror the indicator state to the secondary half.
                * Default: `false`
            * `matrix_state` <Badge type="info">Boolean</Badge>
                * Mirror the main/primary half's matrix state to the secondary half.
                * Default: `false`
            * `modifiers` <Badge type="info">Boolean</Badge>
                * Mirror the modifier state to the secondary half.
                * Default: `false`
            * `oled` <Badge type="info">Boolean</Badge>
                * Mirror the OLED on/off status to the secondary half.
                * Default: `false`
            * `st7565` <Badge type="info">Boolean</Badge>
                * Mirror the ST7565 on/off status to the secondary half.
                * Default: `false`
            * `wpm` <Badge type="info">Boolean</Badge>
                * Mirror the current WPM value to the secondary half.
                * Default: `false`
        * `watchdog` <Badge type="info">Boolean</Badge>
            * Reboot the secondary half if it loses connection.
            * Default: `false`
        * `watchdog_timeout` <Badge type="info">Number</Badge>
            * The amount of time to wait for communication from the primary half in milliseconds.
    * `usb_detect`
        * `enabled` <Badge type="info">Boolean</Badge>
            * Detect USB connection when determining split half roles.
        * `polling_interval` <Badge type="info">Number</Badge>
            * The polling frequency in milliseconds.
            * Default: `10` (10 ms)
        * `timeout` <Badge type="info">Number</Badge>
            * The amount of time to wait for a USB connection in milliseconds.
            * Default: `2000` (2 seconds)

## Stenography {#stenography}

Configures the [Stenography](features/stenography) feature.

* `stenography`
    * `enabled` <Badge type="info">Boolean</Badge>
        * Enable the Stenography feature.
        * Default: `false`
    * `protocol` <Badge type="info">String</Badge>
        * The Steno protocol to use. Must be one of `all`, `geminipr`, `txbolt`.
        * Default: `"all"`

## USB {#usb}

* `usb`
    * `device_version` <Badge type="info">String</Badge> <Badge>Required</Badge>
        * A BCD version number in the format `MM.m.r` (up to `99.9.9`).
        * Example: `"1.0.0"`
    * `pid` <Badge type="info">String</Badge> <Badge>Required</Badge>
        * The USB product ID as a four-digit hexadecimal number.
        * Example: `"0x23B0"`
    * `vid` <Badge type="info">String</Badge> <Badge>Required</Badge>
        * The USB vendor ID as a four-digit hexadecimal number.
        * Example: `"0xC1ED"`
    * `max_power` <Badge type="info">Number</Badge>
        * The maximum current draw the host should expect from the device. This does not control the actual current usage.
        * Default: `500` (500 mA)
    * `no_startup_check` <Badge type="info">Boolean</Badge>
        * Disable USB suspend check after keyboard startup.
        * Default: `false`
    * `polling_interval` <Badge type="info">Number</Badge>
        * The frequency at which the host should poll the keyboard for reports.
        * Default: `1` (1 ms/1000 Hz)
    * `shared_endpoint`
        * `keyboard` <Badge type="info">Boolean</Badge>
            * Send keyboard reports through the "shared" USB endpoint.
            * Default: `false`
        * `mouse` <Badge type="info">Boolean</Badge>
            * Send mouse reports through the "shared" USB endpoint.
            * Default: `true`
    * `suspend_wakeup_delay` <Badge type="info">Number</Badge>
        * The amount of time to wait after sending a wakeup packet, in milliseconds.
        * Default: `0` (disabled)
    * `wait_for_enumeration` <Badge type="info">Boolean</Badge>
        * Force the keyboard to wait for USB enumeration before starting up.
        * Default: `false`

## WS2812 {#ws2812}

Configures the [WS2812](drivers/ws2812) driver.

* `ws2812`
    * `driver` <Badge type="info">String</Badge>
        * The driver to use. Must be one of `bitbang`, `custom`, `i2c`, `pwm`, `spi`, `vendor`.
        * Default: `"bitbang"`
    * `pin` <Badge type="info">Pin</Badge> <Badge>Required</Badge>
        * The GPIO pin connected to `DI` on the first LED in the chain (`bitbang`, `pwm`, `spi` and `vendor` drivers only).
    * `i2c_address` <Badge type="info">String</Badge>
        * The I²C address of the WS2812 controller (`i2c` driver only).
        * Default: `"0xB0"`
    * `i2c_timeout` <Badge type="info">Number</Badge>
        * The I²C timeout in milliseconds (`i2c` driver only).
        * Default: `100` (100 ms)
    * `rgbw` <Badge type="info">Boolean</Badge>
        * Enable RGBW LEDs.
        * Default: `false`
