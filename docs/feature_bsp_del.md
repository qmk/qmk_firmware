# Backspace Delete

## Usage

`KC_BSDL` will function as normal `KC_BSPC` when pressed. When either `SHIFT` key is held, it will function as `KC_DEL` instead. When both `KC_RSHIFT` and `KC_LSHIFT` are held, the output will be `SHIFT` modifier with `KC_DEL` pressed.

## What Your OS Sees

If Mary presses BSDL on her keyboard, the OS will see an `KC_BSPC` character. Now if Mary holds Shift down and presses BSDL it will output `KC_DEL`. If she holds down both Shift keys, it will output `SHIFT` and `KC_DEL`.

## Keycodes

|Key      |Aliases    |Description                                                       |
|---------|-----------|------------------------------------------------------------------|
|`KC_BSDL`|`BSP_DEL`|Backspace when pressed, Delete when Shift is held, Shift+Delete when both Shift keys are held.|

### Caveats

With this option enabled you won't be able to output `SHIFT` + `KC_BSPC`. You can however, still use the regular keycode `KC_BSPC` anywhere in your keymap.

## Configuration

Add `BSP_DEL_ENABLE = yes` to your `rules.mk` file.
