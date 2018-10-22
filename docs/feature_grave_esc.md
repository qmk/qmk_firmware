# Grave Escape

If you're using a 60% keyboard, or any other layout with no F-row, you will have noticed that there is no dedicated Escape key. Grave Escape is a feature that allows you to share the grave key (<code>&#96;</code> and `~`) with Escape.

## Usage

Replace the `KC_GRAVE` key in your keymap (usually to the left of the `1` key) with `KC_GESC`. When pressed it will behave like `KC_ESC`, but with Shift or GUI held it will send `KC_GRAVE`.

## Keycodes

|Key      |Aliases    |Description                                                       |
|---------|-----------|------------------------------------------------------------------|
|`KC_GESC`|`GRAVE_ESC`|Escape when pressed, <code>&#96;</code> when Shift or GUI are held|

## Configuration

There are several possible key combinations this will break, among them Control+Shift+Escape on Windows and Command+Option+Escape on macOS. To work around this, you can `#define` these options in your `config.h`:

|Define                    |Description                              |
|--------------------------|-----------------------------------------|
|`GRAVE_ESC_ALT_OVERRIDE`  |Always send Escape if Alt is pressed     |
|`GRAVE_ESC_CTRL_OVERRIDE` |Always send Escape if Control is pressed |
|`GRAVE_ESC_GUI_OVERRIDE`  |Always send Escape if GUI is pressed     |
|`GRAVE_ESC_SHIFT_OVERRIDE`|Always send Escape if Shift is pressed   |
