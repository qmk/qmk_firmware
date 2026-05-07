# Adding Your Keyboard to QMK

This page describes the support for [Compatible Microcontrollers](compatible_microcontrollers) in QMK.

If you have not yet you should read the [Keyboard Guidelines](hardware_keyboard_guidelines) to get a sense of how keyboards fit into QMK.

QMK has a number of features to simplify working with keyboards. For most, you don't have to write a single line of code. To get started, run `qmk new-keyboard`:

```
$ qmk new-keyboard
Ψ Generating a new QMK keyboard directory

Ψ Name Your Keyboard Project
Ψ For more information, see:
https://docs.qmk.fm/hardware_keyboard_guidelines#naming-your-keyboard-project
Keyboard Name? mycoolkeeb
Ψ Attribution
Ψ Used for maintainer, copyright, etc.
Your GitHub Username? [jsmith] 
Ψ More Attribution
Ψ Used for maintainer, copyright, etc.
Your Real Name? [John Smith] 
Ψ Pick Base Layout
Ψ As a starting point, one of the common layouts can be used to
bootstrap the process
Default Layout?
    1. 60_abnt2
    ...
    65. none of the above
Please enter your choice: [65] 
Ψ What Powers Your Project
Ψ Is your board using a separate development board, such as a Pro Micro,
or is the microcontroller integrated onto the PCB?

For more information, see:
https://docs.qmk.fm/compatible_microcontrollers
Using a Development Board? [y/n] y
Ψ Select Development Board
Ψ For more information, see:
https://docs.qmk.fm/compatible_microcontrollers
Development Board?
    1. bit_c_pro
    ...
    14. promicro
    ...
    18. svlinky
Please enter your choice: [14] 
Ψ Created a new keyboard called mycoolkeeb.
Ψ Build Command: qmk compile -kb mycoolkeeb -km default.
Ψ Project Location: /Users/jsmith/qmk_firmware/keyboards/mycoolkeeb.
Ψ Now update the config files to match the hardware!
```

This will create all the files needed to support your new keyboard, and populate the settings with default values. Now you just need to customize it for your keyboard.

## `readme.md`

This is where you'll describe your keyboard. Please follow the [Keyboard Readme Template](documentation_templates#keyboard-readmemd-template) when writing your `readme.md`. You're encouraged to place an image at the top of your `readme.md`, please use an external service such as [Imgur](https://imgur.com) to host the images.

## `keyboard.json`

The `keyboard.json` file is where you configure the hardware and feature set for your keyboard. There are a lot of options that can be placed in that file, too many to list here. For a complete overview of available options see the [Data Driven Configuration Options](reference_info_json) page.

### Hardware Configuration

At the top of the `keyboard.json` you'll find USB related settings. These control how your keyboard appears to the Operating System. If you don't have a good reason to change you should leave the `usb.vid` as `0xFEED`. For the `usb.pid` you should pick a number that is not yet in use.

Do change the `manufacturer` and `keyboard_name` lines to accurately reflect your keyboard.

```json
    "keyboard_name": "my_awesome_keyboard",
    "maintainer": "You",
    "usb": {
        "vid": "0xFEED",
        "pid": "0x0000",
        "device_version": "1.0.0"
    },
```

::: tip
Windows and macOS will display the `manufacturer` and `keyboard_name` in the list of USB devices. `lsusb` on Linux instead prefers the values in the list maintained by the [USB ID Repository](http://www.linux-usb.org/usb-ids.html). By default, it will only use `manufacturer` and `keyboard_name` if the list does not contain that `usb.vid` / `usb.pid`. `sudo lsusb -v` will show the values reported by the device, and they are also present in kernel logs after plugging it in.
:::

### Matrix Configuration

The next section of the `keyboard.json` deals with your keyboard's matrix. The first thing you should define is which pins on your MCU are connected to rows and columns. To do so simply specify the names of those pins:

#### Diode Matrix

```json
    "matrix_pins": {
        "cols": ["C1", "C2", "C3", "C4"],
        "rows": ["D1", "D2", "D3", "D4"]
    },
```

The matrix dimensions are inferred from the length of the `matrix_pins.cols` and `matrix_pins.rows` arrays (previously specified explicitly in `config.h` with `MATRIX_ROWS` and `MATRIX_COLS`).

Finally, you can specify the direction your diodes point. This can be `COL2ROW` or `ROW2COL`.

```json
    "diode_direction": "ROW2COL",
```

#### Direct Pin Matrix

To configure a keyboard where each switch is connected to a separate pin and ground instead of sharing row and column pins, use `matrix_pins.direct`. This overrides the behaviour of `diode_direction`, `matrix_pins.cols` and `matrix_pins.rows`, and they should not be specified together.

```json
    "matrix_pins": {
        "direct": [
            ["F1", "E6", "B0", "B2", "B3"],
            ["F5", "F0", "B1", "B7", "D2"],
            ["F6", "F7", "C7", "D5", "D3"],
            ["B5", "C6", "B6", null, null]
        ]
    },
```

Here, the matrix dimensions are inferred directly from the dimensions of the `matrix_pins.direct` array. Since there are no row or column pins to prescribe the matrix dimensions, you can arrange it however you like. Each "row" must contain the same number of "column"s; use `null` to fill in blank spaces, but try to minimize them.

### Layout Macros

Next is configuring layout macro(s). These define the physical arrangement of keys, and their position within the matrix that switches are connected to. This allows you to have a physical arrangement of keys that differs from the wiring matrix.

```json
    "layouts": {
        "LAYOUT_ortho_4x4": {
            "layout": [
                {"matrix": [0, 0], "x": 0, "y": 0},
                {"matrix": [0, 1], "x": 1, "y": 0},
                {"matrix": [0, 2], "x": 2, "y": 0},
                {"matrix": [0, 3], "x": 3, "y": 0},
                {"matrix": [1, 0], "x": 0, "y": 1},
                {"matrix": [1, 1], "x": 1, "y": 1},
                {"matrix": [1, 2], "x": 2, "y": 1},
                {"matrix": [1, 3], "x": 3, "y": 1},
                {"matrix": [2, 0], "x": 0, "y": 2},
                {"matrix": [2, 1], "x": 1, "y": 2},
                {"matrix": [2, 2], "x": 2, "y": 2},
                {"matrix": [2, 3], "x": 3, "y": 2},
                {"matrix": [3, 0], "x": 0, "y": 3},
                {"matrix": [3, 1], "x": 1, "y": 3},
                {"matrix": [3, 2], "x": 2, "y": 3},
                {"matrix": [3, 3], "x": 3, "y": 3}
            ]
        }
    }
```

In the above example,

* `LAYOUT_ortho_4x4` defines the name of the layout macro
  * It must conform to the [layout guidelines](hardware_keyboard_guidelines#keyboard-name-h)
* `"matrix": [0, 0]` defines the matrix row and column that the key is associated with

::: tip
See also: [Split Keyboard Layout Macro](features/split_keyboard#layout-macro) and [Matrix to Physical Layout](understanding_qmk#matrix-to-physical-layout-map).
:::

## Additional Configuration

There are a lot of features that can be turned on or off, configured or tuned. Some of these have yet to be migrated over to [Data Driven Configuration](data_driven_config). The following sections cover the process for when a data-driven option is unavailable.

### Configuration Options

For available options for `config.h`, you should see the [Config Options](config_options#the-config-h-file) page for more details.

### Build Options

For available options for `rules.mk`, see the [Config Options](config_options#feature-options) page for a detailed list and description.
