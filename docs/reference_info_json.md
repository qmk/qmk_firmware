# `info.json`

This file is used by the [QMK API](https://github.com/qmk/qmk_api). It contains the information [QMK Configurator](https://config.qmk.fm/) needs to display a representation of your keyboard. You can also set metadata here.

You can create `info.json` files at every level under `qmk_firmware/keyboards/<name>` to specify this metadata. These files are combined, with more specific files overriding keys in less specific files. This means you do not need to duplicate your metadata information. For example, `qmk_firmware/keyboards/clueboard/info.json` specifies `manufacturer` and `maintainer`, while `qmk_firmware/keyboards/clueboard/66/info.json` specifies more specific information about Clueboard 66%.

## `info.json` Format

The `info.json` file is a JSON formatted dictionary with the following keys available to be set. You do not have to set all of them, merely the keys that apply to your keyboard.

* `keyboard_name`
  * A free-form text string describing the keyboard.
  * Example: `Clueboard 66%`
* `url`
  * A URL to the keyboard's product page, [QMK.fm/keyboards](https://qmk.fm/keyboards) page, or other page describing information about the keyboard.
* `maintainer`
  * GitHub username of the maintainer, or `qmk` for community maintained boards
* `width`
  * Width of the board in Key Units
* `height`
  * Height of the board in Key Units
* `layouts`
  * Physical Layout representations. See the next section for more detail.

### Layout Format

Within our `info.json` file the `layouts` portion of the dictionary contains several nested dictionaries. The outer layer consists of QMK layout macros, for example `LAYOUT_ansi` or `LAYOUT_iso`. Within each layout macro are keys for `width`, `height`, and `key_count`, each of which should be self-explanatory.

* `width`
  * Optional: The width of the layout in Key Units
* `height`
  * Optional: The height of the layout in Key Units
* `key_count`
  * Optional: The number of keys in this layout
* `layout`
  * A list of Key Dictionaries describing the physical layout. See the next section for more details.

### Key Dictionary Format

Each Key Dictionary in a layout describes the physical properties of a key. If you are familiar with the Raw Code for <http://keyboard-layout-editor.com> you will find many of the concepts the same. We re-use the same key names and layout choices wherever possible, but unlike keyboard-layout-editor each key is stateless, inheriting no properties from the keys that came before it.

All key positions and rotations are specified in relation to the top-left corner of the keyboard, and the top-left corner of each key.

* `x`
  * **Required**: The absolute position of the key in the horizontal axis, in Key Units.
* `y`
  * **Required**: The absolute position of the key in the vertical axis, in Key Units.
* `w`
  * The width of the key, in Key Units. Ignored if `ks` is provided. Default: `1`
* `h`
  * The height of the key, in Key Units. Ignored if `ks` is provided. Default: `1`
* `r`
  * How many degrees clockwise to rotate the key.
* `rx`
  * The absolute position of the point to rotate the key around in the horizontal axis. Default: `x`
* `ry`
  * The absolute position of the point to rotate the key around in the vertical axis. Default: `y`
* `ks`
  * Key Shape: define a polygon by providing a list of points, in Key Units.
  * **Important**: These are relative to the top-left of the key, not absolute.
  * Example ISO Enter: `[ [0,0], [1.5,0], [1.5,2], [0.25,2], [0.25,1], [0,1], [0,0] ]`
* `label`
  * What to name this position in the matrix.
  * This should usually be the same name as what is silkscreened on the PCB at this location.

## How is the Metadata Exposed?

This metadata is primarily used in two ways:

* To allow web-based configurators to dynamically generate UI
* To support the new `make keyboard:keymap:qmk` target, which bundles this metadata up with the firmware to allow QMK Toolbox to be smarter.

Configurator authors can see the [QMK Compiler](https://docs.api.qmk.fm/using-the-api) docs for more information on using the JSON API.
