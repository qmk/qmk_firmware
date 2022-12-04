# Key Lock

Sometimes you may find yourself needing to hold down a specific key for a long period of time. Key Lock holds down the next key you press for you. Press it again, and it will be released.

Let's say you need to type in ALL CAPS for a few sentences. Hit `KC_LOCK`, and then Shift. Now, Shift will be considered held until you tap it again. You can think of Key Lock as Caps Lock, but supercharged.

## Usage

First, enable Key Lock by setting `KEY_LOCK_ENABLE = yes` in your `rules.mk`. Then pick a key in your keymap and assign it the keycode `KC_LOCK`.

## Keycodes

|Keycode  |Description                                                   |
|---------|--------------------------------------------------------------|
|`KC_LOCK`|Hold down the next key pressed, until the key is pressed again|

## Caveats

Key Lock is only able to hold standard action keys and [One Shot modifier](one_shot_keys.md) keys (for example, if you have your Shift defined as `OSM(MOD_LSFT)`).
This does not include any of the QMK special functions (except One Shot modifiers), or shifted versions of keys such as `KC_LPRN`. If it's in the [Basic Keycodes](keycodes_basic.md) list, it can be held.

Switching layers will not cancel the Key Lock. The Key Lock can be cancelled by calling the `cancel_key_lock()` function.

