# `info.json`

This file is used by the [QMK API](https://github.com/qmk/qmk_api). It contains the information [QMK Configurator](https://config.qmk.fm/) needs to display a representation of your keyboard. You can also set metadata here.

You can create `info.json` files at every level under `qmk_firmware/keyboards/<name>` to specify this metadata. These files are combined, with more specific files overriding keys in less specific files. This means you do not need to duplicate your metadata information. For example, `qmk_firmware/keyboards/clueboard/info.json` specifies `manufacturer` and `maintainer`, while `qmk_firmware/keyboards/clueboard/66/info.json` specifies more specific information about Clueboard 66%.

## `info.json` Format

The `info.json` file is a JSON formatted dictionary with the following keys available to be set. You do not have to set all of them, merely the keys that apply to your keyboard.

* `keyboard_name`
    * A free-form text string describing the keyboard.
    * Example: `Clueboard 66%`
* `manufacturer`
    * A free-form text string describing the keyboard's manufacturer.
    * Example: `Clueboard`
* `url`
    * A URL to the keyboard's product page, [QMK.fm/keyboards](https://qmk.fm/keyboards) page, or other page describing information about the keyboard.
    * Example: `https://clueboard.co`
* `maintainer`
    * GitHub username of the maintainer, or `qmk` for community maintained boards.
    * Example: `skullydazed`
* `debounce`
    * The amount of time in milliseconds to wait for debounce to happen.
    * Default: `5`
* `diode_direction`
    * The direction diodes face. See [`DIRECT_PINS` in the hardware configuration](https://docs.qmk.fm/#/config_options?id=hardware-options) for more details.
* `layout_aliases`
    * A dictionary containing layout aliases. The key is the alias and the value is a layout in `layouts` it maps to.
* `layouts`
    * Physical Layout representations. See the [Layout Format](#layout-format) section for more detail.
* `matrix_pins`
    * Configure the pins corresponding to columns and rows, or direct pins. See the [Matrix Pins](#matrix-pins) section for more detail.
* `rgblight`
    * Configure the [RGB Lighting feature](feature_rgblight.md). See the [RGB Lighting](#rgb-lighting) section for more detail.
* `usb`
    * Configure USB VID, PID, and other parameters. See the [USB](#USB) section for more detail.

### Layout Format

Within our `info.json` file the `layouts` portion of the dictionary contains several nested dictionaries. The outer layer consists of QMK layout macros, for example `LAYOUT_ansi` or `LAYOUT_iso`.

* `layout`
    * A list of Key Dictionaries describing the physical layout. See the next section for more details.

### Key Dictionary Format

Each Key Dictionary in a layout describes the physical properties of a key. If you are familiar with the Raw Code for <https://keyboard-layout-editor.com> you will find many of the concepts the same. We re-use the same key names and layout choices wherever possible, but unlike keyboard-layout-editor each key is stateless, inheriting no properties from the keys that came before it.

All key positions and rotations are specified in relation to the top-left corner of the keyboard, and the top-left corner of each key.

* `x`
    * **Required**. The absolute position of the key in the horizontal axis, in Key Units.
* `y`
    * **Required**. The absolute position of the key in the vertical axis, in Key Units.
* `w`
    * The width of the key, in Key Units.
    * Default: `1`
* `h`
    * The height of the key, in Key Units.
    * Default: `1`
* `label`
    * What to name this position in the matrix. This should usually correspond to the keycode for the first layer of the default keymap.
* `matrix`
    * A two item list describing the row and column location for this key.
    * Example: `[0, 4]`

### Matrix Pins

Currently QMK supports connecting switches either directly to GPIO pins or via a switch matrix. At this time you can not combine these, they are mutually exclusive.

#### Switch Matrix

Most keyboards use a switch matrix to connect keyswitches to the MCU. You can define your pin columns and rows to configure your switch matrix. When defining switch matrices you should also define your `diode_direction`.

Example:

```json
{
    "diode_direction": "COL2ROW",
    "matrix_pins": {
        "cols": ["F4", "E6", "B1", "D2"],
        "rows": ["B0", "D3", "D5", "D4", "D6"]
    }
}
```

#### Direct Pins

Direct pins are when you connect one side of the switch to GND and the other side to a GPIO pin on your MCU. No diode is required, but there is a 1:1 mapping between switches and pins.

When specifying direct pins you need to arrange them in nested arrays. The outer array consists of rows, while the inner array is a text string corresponding to a pin. You can use `null` to indicate an empty spot in the matrix.

Example:

```json
{
    "matrix_pins": {
        "direct": [
            ["A10", "A9"],
            ["A0", "B8"],
            [null, "B11"],
            ["B9", "A8"],
            ["A7", "B1"],
            [null, "B2"]
        ]
    }
}
```

### RGB Lighting

This section controls the legacy WS2812 support in QMK. This should not be confused with the RGB Matrix feature, which can be used to control both WS2812 and ISSI RGB LEDs.

The following items can be set. Not every value is required.

* `led_count`
    * The number of LEDs in your strip
* `pin`
    * The GPIO pin that your LED strip is connected to
* `animations`
    * A dictionary that lists enabled and disabled animations. See [RGB Light Animations](#rgb_light_animations) below.
* `sleep`
    * Set to `true` to enable lighting during host sleep
* `split`
    * Set to `true` to enable synchronization functionality between split halves
* `split_count`
    * For split keyboards, the number of LEDs on each side
* `max_brightness`
    * (0-255) What the maxmimum brightness (value) level is
* `hue_steps`
    * How many steps of adjustment to have for hue
* `saturation_steps`
    * How many steps of adjustment to have for saturation
* `brightness_steps`
    * How many steps of adjustment to have for brightness (value)

Example:

```json
{
    "rgblight": {
        "led_count": 4,
        "pin": "F6",
        "hue_steps": 10,
        "saturation_steps": 17,
        "brightness_steps": 17,
        "animations": {
            "all": true
        }
    }
}
```

#### RGBLight Animations

The following animations can be enabled:

|Key              |Description                           |
|-----------------|--------------------------------------|
|`all`            |Enable all additional animation modes.|
|`alternating`    |Enable alternating animation mode.    |
|`breathing`      |Enable breathing animation mode.      |
|`christmas`      |Enable christmas animation mode.      |
|`knight`         |Enable knight animation mode.         |
|`rainbow_mood`   |Enable rainbow mood animation mode.   |
|`rainbow_swirl`  |Enable rainbow swirl animation mode.  |
|`rgb_test`       |Enable RGB test animation mode.       |
|`snake`          |Enable snake animation mode.          |
|`static_gradient`|Enable static gradient mode.          |
|`twinkle`        |Enable twinkle animation mode.        |

### USB

Every USB keyboard needs to have its USB parameters defined. At a minimum you need to set the Vendor ID, Product ID, and device version.

Example:

```json
{
    "usb": {
        "vid": "0xC1ED",
        "pid": "0x23B0",
        "device_version": "1.0.0"
    }
}
```

The device version is a BCD (binary coded decimal) value, in the format `MMmr`, so the below value would look like `0x0100` in the generated code. This also means the maximum valid values for each part are `99.9.9`, despite it being a hexadecimal value under the hood.
