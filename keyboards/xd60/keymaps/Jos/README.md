# Jos's Layout

Custom layout with various options. Designed to be used with the Canadian Multilingual software layout.

## Layout
This is the physical layout of my xd60, for reference. See the keymap file for actual software layout.
![Keyboard Layout (Physical appearence)](https://i.imgur.com/qzOmqyq.png "Physical Layout")

## Features
**Caps Lock** is **Escape** and the **Window key** is a **Function** key that still acts like the **Window** key in conjuction with `w`, `s`, `d`, `l`, `t`, `e`, `h`, and `SPACE`.

There are a few `#define` lines at the beginning of the keymap file that enable the following options if not commented:
- `ISOLIKE_ALT_ENTER`: `RALT` + `ENT` is the same as `RALT`+`BSLS`. For logical placement of `{` and `}` (the former being `RALT`+`BSLS`) with ANSI enter on a ISO-based layout.
- `TWO_SFT_CAPS`: Both shifts together → Caps Lock.
- `APP_IS_RALT_RCTRL`: Menu would be between `RCTRL` and `RALT`, so now `RALT` + `RCTRL` → `APP`.
- `HELD_ESC_IS_SHIFT`: Holding `ESC` → `SHIFT`. It always register shift when pressing `ESC`. Useful for VIM.
- `BSPC_BLOCKS_DEL`: If `BSPC` is held, we disable `DEL`. To avoid acidental presses of `DEL` with split backspace key. 
- `ALT_MINSEQL_IS_ALT_78`: Pressing `ALT+MINS/EQL` will act like `ALT+7/8`. Will yield `{}` instead of `½¬` in Canadian Multilingual Layout. Diminished finger stretching. 


# Build
To build, simply run `make xd60:Jos`
