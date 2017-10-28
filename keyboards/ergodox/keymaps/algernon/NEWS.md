<!-- -*- mode: markdown; fill-column: 8192 -*- -->

## v1.10

*2016-12-28*

### Miscellaneous

* `µ` can now be entered with UCIS.
* `™` can now be entered with UCIS.

### Tools

* `tools/hid-commands` can now find Banshee, and prefers it over Kodi.
* `tools/hid-commands` can now find Chrome too, not juts Chromium.

## v1.9

*2016-10-16*

### Overall changes

* `F12` was replaced by an `Fx` key, that activate the **Media** layer as a one-shot layer, and also `Alt` as a one-shot modifier.

### Base layer changes

* The `Media Stop` key is now a tap-dance key, and resets the device for programming on the fourth tap.

### Miscellaneous

* `π` can now be entered with UCIS.
* `🐁` can now be entered with UCIS.

### Tools

* The `tools/layer-notify` tool was removed, it was an example, which I don't use.

#### `tools/hid-commands`

* Now looks at the `DISABLE_APPSEL_START` environment value, and does not display an AppSel notification if it is non-empty.
* Will attempt to re-program the keyboard when receiving a `reflash` command.
* No longer tries to select Emacs 24 on `APPSEL_EMACS`, rather, it goes for any Emacs.
* The `APPSEL_MUSIC` command now includes Kodi in the list too, as the last choice.

## v1.8

*2016-10-03*

### ADORE

* Major rearrangements were made, to reduce pinky use, and to balance out the hand usage.

### Tools

* The `hid-commands` tool will now display a notification when the **AppSel** layer is triggered.
* The `log-to-heatmap.py` tool now treats the innermost keys on the bottom row as thumb keys, as far as statistics are concerned.

### Miscellaneous

* Fixed the **Steno** toggle key.

## v1.7

*2016-09-18*

### Overall changes

* The number row has been completely rearranged on both the **Base** and the **ADORE** layers.
* The number/function key behavior was changed: function keys are now on the **Media**.
* The `:`/`;` and `-`/`_` keys were put back to their thumb position on the bottom row, on both the **Base** and **ADORE** layers.
* The bottom large keys on the inner side of each half now function as [tmux](http://tmux.github.io/) keys: the left to send the prefix, the right to send the `display-panes` key. The left also doubles as a GNU screen prefix key, and sends `C-a` when double tapped.
* A number of functions, such as the **AppSel** layer, now require the `hid-commands` tool to be running, with the output of `hid_listen` being piped to it.

### ADORE

* `Y` and `X` have been swapped again.

### Media/Navigation layer

* The function keys are now on this layer.
* Mouse keys have been removed.
* Media start/stop/prev/next have been removed.
* `Print screen` has been removed.
* There is only one screen lock key now.

### Heatmap

* Fixed a few issues in the finger-stats calculation.
* The tool now also timestamps and saves all input lines to a logfile, which it loads on start, allowing one to continue the collection after upgrading the tool.
* The heatmap tool will now colorize the stats by default.
* The periodic stats are now printed in a more compact format.

### Tools

* Added a new tool, `tools/layer-notify` that listens to layer change events on the HID console, and pops up a notification on layer changes.
* Another new tool, `tools/text-to-log.py` has been added that converts arbitrary text to a keylogger output, which can be fed to the heatmap generator.
* A number of features have been moved to the `tools/hid-commands` utility. These generally are OS dependent, and are easier to implement on the software side.

## v1.6

*2016-08-24*

### Base layer changes

* The parentheses & bracket keys have been merged: tapping them results in `[` or `{` (if it was shifted), double tapping leads to `(`.
* The `:;` and `-_` keys are now available on the base layer, on their **ADORE** location, too, just below `[{(`/`]})`.
* The `Apps` key has been replaced by `F12`.
* The `-`/`_` is no longer a tap-dance key.

### ADORE layer changes

* Adjustments were made to the **ADORE** layer, to separate some inconvenient combinations.

### Miscellaneous changes

* `LEAD u` now starts the symbolic unicode input system, instead of the OS-one.
* The mouse acceleration keys on the **Navigation/Media** layer have been turned into toggles: tap them once to turn them on, until tapped again. Tapping an accelerator button will turn all the others off.
* When the **ARROW** layer is on, the *red* and *blue* LEDs light up now.

### Heatmap

* The built-in keylogger has been greatly enhanced, it now outputs the pressed state, and the layer (Dvorak or ADORE). As such, the `ADORE_AUTOLOG` option has been removed, instead there is `AUTOLOG_ENABLE` now, which when enabled, makes the keylogger start when the keyboard boots. It defaults to off.
* The heatmap generator received a lot of updates.

## v1.5

*2016-08-12*

* The **1HAND** layer has been removed.
* A `Delete` key is now available on the right thumb cluster.
* The **ADORE** layer received a major update, see the layout image above.
* It is now possible to enable automatic logging for the **ADORE** layer, by setting the `ADORE_AUTOLOG` makefile variable to `yes` when compiling the keymap. It is off by default.
* The `~` key and the `Media Next/Prev` key have been swapped on the **Base** layer.
* On the **ARROW** layer, `Backspace` has been replaced by `Enter`.
* There is some experimental support for entering Unicode symbols.

## v1.4

*2016-07-29*

* When toggling the key logging on or off, the LEDs will do a little dance.
* The keylogger is now optional, but enabled by default. Use `KEYLOGGER_ENABLE=no` on the `make` command line to disable it.
* The `TAB`/`ARRW` key was turned into a tap-dance key, allowing one to toggle the **ARROW** layer on by double-tapping, and as such, avoid the need to hold the key.
* The `-`/`_` key was turned into a tap-dance key too.
* There is now a way to travel time with the keyboard, toggle the feature on by hitting `LEAD t`.

## v1.3

*2016-07-06*

* Added support for logging keys, by pressing `LEAD d`. Also included is a tool to generate a *heatmap* out of the logs.
* The arrow and navigation keys were rearranged again, and now require an additional key being held to activate. See the **Base** layer for an image that shows where arrows are.
* The **experimental** layer has been redone, and is now called **ADORE**, and as such, can be enabled by `LEAD a` now.
* Switching between Dvorak and ADORE is now persisted into EEPROM, and survives a reboot.

## v1.2

*2016-06-22*

* The forced NKRO mode can be easily toggled off at compile-time, to make the firmware compatible with certain operating systems.
* The `:;` key has changed behaviour: to access the `;` symbol, the key needs to be double-tapped, instead of shifted.
* The `=` and `\` keys were swapped, `=` moved to the home row, on both the **Base** and the **experimental** layers.
* The arrow and navigation keys were redone, they are now more accessible, but the navigation keys require an extra tap to access.
* The **Emacs** layer is gone, replaced by a simplified **navigation and media** layer.
* `LEAD v` types the firmware version, and the keymap version.
* On the **experimental** layer, the `L` and `Q`, and the `K` and `G` keys were swapped.
* The **Steno** layer gained a few more `#` and `*` keys, to make it easier on my fingers.

## v1.1

*2016-06-14*

* The keyboard starts in NKRO mode, bootmagic and other things are disabled.
* A **Steno** layer was added, to be used with Plover.
* An **experimental** layer was added, something halfway between Dvorak and Capewell-Dvorak. A work in progress.
* `LEAD y` types `\o/`.
* Some keys on the **Base** layer have been moved around:
    - `?` moved to the left pinky, left of `Q`.
    - `=` shifted one row down, but `F11` stayed where it was.
    - `-` on the left half was replaced by `Tab`.
    - `Tab`'s original position is taken by a `Media Next`/`Media Prev` key.
    - `:` now inputs `;` when shifted.
* `ESC` cancels the **Hungarian** layer too, not just modifiers.

## v1.0

*2016-05-26*

Initial version.
