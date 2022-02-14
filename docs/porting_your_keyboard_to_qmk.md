# Adding Your Keyboard to QMK

This page describes the support for [Compatible Microcontrollers](compatible_microcontrollers.md) in QMK.

If you have not yet you should read the [Keyboard Guidelines](hardware_keyboard_guidelines.md) to get a sense of how keyboards fit into QMK.


QMK has a number of features to simplify working with keyboards. For most, you don't have to write a single line of code. To get started, run `qmk new-keyboard`:

```
$ qmk new-keyboard
Ψ Generating a new QMK keyboard directory

Name Your Keyboard Project
For more infomation, see:
https://docs.qmk.fm/#/hardware_keyboard_guidelines?id=naming-your-keyboardproject

keyboard Name? mycoolkeeb

Attribution
Used for maintainer, copyright, etc

Your GitHub Username?  [jsmith] 

More Attribution
Used for maintainer, copyright, etc

Your Real Name?  [John Smith] 

Pick Base Layout
As a starting point, one of the common layouts can be used to bootstrap the process

Default Layout? 
	1. 60_ansi
...
	50. tkl_iso
	51. none of the above
Please enter your choice:  [51] 

What Powers Your Project
For more infomation, see:
https://docs.qmk.fm/#/compatible_microcontrollers

MCU? 
	1. atmega32u4
...
	22. STM32F303
Please enter your choice:  [12]
Ψ Created a new keyboard called mycoolkeeb.
Ψ To start working on things, `cd` into keyboards/mycoolkeeb,
Ψ or open the directory in your preferred text editor.
Ψ And build with qmk compile -kb mycoolkeeb -km default.
```

This will create all the files needed to support your new keyboard, and populate the settings with default values. Now you just need to customize it for your keyboard.

## `readme.md`

This is where you'll describe your keyboard. Please follow the [Keyboard Readme Template](documentation_templates.md#keyboard-readmemd-template) when writing your `readme.md`. You're encouraged to place an image at the top of your `readme.md`, please use an external service such as [Imgur](https://imgur.com) to host the images.

## `info.json`

The `info.json` file is where you configure the hardware and feature set for your keyboard. There are a lot of options that can be placed in that file, too many to list here. For a complete overview of available options see the [Data Driven Configuration Options](reference_info_json.md) page.

### Hardware Configuration

At the top of the `info.json` you'll find USB related settings. These control how your keyboard appears to the Operating System. If you don't have a good reason to change you should leave the `usb.vid` as `0xFEED`. For the `usb.pid` you should pick a number that is not yet in use.

Do change the `manufacturer` and `keyboard_name` lines to accurately reflect your keyboard.

```json
    "keyboard_name": "my_awesome_keyboard",
    "maintainer": "You",
    "usb": {
        "device_ver": "0x0001",
        "pid": "0x0000",
        "vid": "0xFEED"
    },
```

?> Windows and macOS will display the `manufacturer` and `keyboard_name` in the list of USB devices. `lsusb` on Linux instead prefers the values in the list maintained by the [USB ID Repository](http://www.linux-usb.org/usb-ids.html). By default, it will only use `manufacturer` and `keyboard_name` if the list does not contain that `usb.vid` / `usb.pid`. `sudo lsusb -v` will show the values reported by the device, and they are also present in kernel logs after plugging it in.


### Matrix Configuration

The next section of the `info` file deals with your keyboard's matrix. The first thing you should define is which pins on your MCU are connected to rows and columns. To do so simply specify the names of those pins:

```json
    "matrix_pins": {
        "cols": ["C1", "C2", "C3", "C4"],
        "rows": ["D1", "D2", "D3", "D4"]
    },
```

The size of the `matrix_pins.cols` and `matrix_pins.rows` arrays infer the size of the matrix (previously `MATRIX_ROWS` and `MATRIX_COLS`). 

Finally, you can specify the direction your diodes point. This can be `COL2ROW` or `ROW2COL`.

```json
    "diode_direction": "ROW2COL",
```

#### Direct Pin Matrix
To configure a keyboard where each switch is connected to a separate pin and ground instead of sharing row and column pins, use `matrix_pins.direct`. The mapping defines the pins of each switch in rows and columns, from left to right. The size of the `matrix_pins.direct` array infers the size of the matrix. Use `NO_PIN` to fill in blank spaces. Overrides the behaviour of `diode_direction`, `matrix_pins.cols` and `matrix_pins.rows`.

```json
    "matrix_pins": {
        "direct": [
            ["F1", "E6", "B0", "B2", "B3" ],
            ["F5", "F0", "B1", "B7", "D2" ],
            ["F6", "F7", "C7", "D5", "D3" ],
            ["B5", "C6", "B6", "NO_PIN", "NO_PIN"]
        ]
    },
```

### Layout macros

Next is configuring Layout Macro(s). These define the physical arrangement of keys, and its position within the matrix that a switch are connected to. This allows you to have a physical arrangement of keys that differs from the wiring matrix.

```json
    "layouts": {
        "LAYOUT_ortho_4x4": {
            "layout": [
                { "matrix": [0, 0], "x": 0, "y": 0 },
                { "matrix": [0, 1], "x": 1, "y": 0 },
                { "matrix": [0, 2], "x": 2, "y": 0 },
                { "matrix": [0, 3], "x": 3, "y": 0 },
                { "matrix": [1, 0], "x": 0, "y": 1 },
                { "matrix": [1, 1], "x": 1, "y": 1 },
                { "matrix": [1, 2], "x": 2, "y": 1 },
                { "matrix": [1, 3], "x": 3, "y": 1 },
                { "matrix": [2, 0], "x": 0, "y": 2 },
                { "matrix": [2, 1], "x": 1, "y": 2 },
                { "matrix": [2, 2], "x": 2, "y": 2 },
                { "matrix": [2, 3], "x": 3, "y": 2 },
                { "matrix": [3, 0], "x": 0, "y": 3 },
                { "matrix": [3, 1], "x": 1, "y": 3 },
                { "matrix": [3, 2], "x": 2, "y": 3 },
                { "matrix": [3, 3], "x": 3, "y": 3 }
            ]
        }
    }

```

In the above example, 

* `LAYOUT_ortho_4x4` defines the name of the layout macro
  * It must conform to [hardware_keyboard_guidelines.md#ltkeyboard_namehgt]
* `"matrix": [0, 0]` defines the electrical position

## Additional Configuration

There are a lot of features that can be turned on or off, configured or tuned. Some of these have yet to be migrated over to [Data Driven Configuration](data_driven_config.md). The following sections cover the process for when an `info.json` option is unavailable.

### Configuration Options

For available options for `config.h`, you should see the [Config Options](config_options.md) page for more details.

### Build Options

For available options for `rules.mk`, see the [Config Options](config_options.md#feature-options) page for a detailed list and description.
