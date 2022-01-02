# Grave Escape

If you're using a 60% keyboard, or any other layout with no F-row, you will have noticed that there is no dedicated Escape key. Grave Escape is a feature that allows you to share the grave key (<code>&#96;</code> and `~`) with Escape.

## Usage

Replace the `KC_GRV` key in your keymap (usually to the left of the `1` key) with `KC_GESC`. Most of the time this key will output `KC_ESC` when pressed. However, when Shift or GUI are held down it will output `KC_GRV` instead.

## What Your OS Sees

If Mary presses GESC on her keyboard, the OS will see an KC_ESC character. Now if Mary holds Shift down and presses GESC it will output `~`, or a shifted backtick. Now if she holds GUI/CMD/WIN, it will output a simple <code>&#96;</code> character.

## Keycodes

|Key      |Aliases    |Description                                                       |
|---------|-----------|------------------------------------------------------------------|
|`KC_GESC`|`GRAVE_ESC`|Escape when pressed, <code>&#96;</code> when Shift or GUI are held|

### Caveats

On macOS, Command+<code>&#96;</code> is by default mapped to "Move focus to next window" so it will not output a backtick. Additionally, Terminal always recognises this shortcut to cycle between windows, even if the shortcut is changed in the Keyboard preferences.

## Configuration

There are several possible key combinations this will break, among them Control+Shift+Escape on Windows and Command+Option+Escape on macOS. To work around this, you can `#define` these options in your `config.h`:

|Define                    |Description                              |
|--------------------------|-----------------------------------------|
|`GRAVE_ESC_ALT_OVERRIDE`  |Always send Escape if Alt is pressed     |
|`GRAVE_ESC_CTRL_OVERRIDE` |Always send Escape if Control is pressed |
|`GRAVE_ESC_GUI_OVERRIDE`  |Always send Escape if GUI is pressed     |
|`GRAVE_ESC_SHIFT_OVERRIDE`|Always send Escape if Shift is pressed   |
