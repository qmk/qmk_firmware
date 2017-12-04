# Grave Escape

Grave Escape is a feature that allows you to share the grave key (`\`` and `~`) on the same key as Escape. When `KC_GESC` is used it will act as `KC_ESC`, unless Shift or GUI is pressed, in which case it will act as `KC_GRAVE`.


| Key | Alias | Description |
|-----|-------|-------------|
| `GRAVE_ESC` | `KC_GESC` | Act as `KC_ESC` normally, or `KC_GRAVE` when GUI or Shift are held. |

There are several possible key combinations this will break, among them Ctrl+Shift+Esc on Windows and Cmd+Opt+Esc on macOS. You can use these options in your `config.h` to work around this:

| Option | Description |
|--------|-------------|
| `GRAVE_ESC_ALT_OVERRIDE` | Always send Escape if Alt is pressed. |
| `GRAVE_ESC_CTRL_OVERRIDE` | Always send Escape if Ctrl is pressed. |
| `GRAVE_ESC_GUI_OVERRIDE` | Always send Escape if GUI is pressed. |
| `GRAVE_ESC_SHIFT_OVERRIDE` | Always send Escape if SHIFT is pressed. |
