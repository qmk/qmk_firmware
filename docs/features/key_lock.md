# Key Lock

Sometimes you may find yourself needing to hold down a specific key for a long period of time. Key Lock holds down the next key you press for you. Press it again, and it will be released.

Let's say you need to type in ALL CAPS for a few sentences. Hit `QK_LOCK`, and then Shift. Now, Shift will be considered held until you tap it again. You can think of Key Lock as Caps Lock, but supercharged.

## Usage

First, enable Key Lock by setting `KEY_LOCK_ENABLE = yes` in your `rules.mk`. Then pick a key in your keymap and assign it the keycode `QK_LOCK`.

## Keycodes

|Keycode  |Description                                                   |
|---------|--------------------------------------------------------------|
|`QK_LOCK`|Hold down the next key pressed, until the key is pressed again|

## User callbacks

In addition to the keycodes, there are a few functions that you can use to interact with Key Lock.

|Function            |Description                                                            |
|--------------------|-----------------------------------------------------------------------|
|begin_key_lock()    |Begins the key lock sequence. Mimics pressing QK_LOCK                  |
|cancel_key_lock()   |Cancels the key lock sequnec if called before a lockable key is pressed|
|get_key_lock_begun()|Checks whether the key lock sequence has started                       |
|get_key_lock_state()|Checks whether a specific key is locked                                |

## Caveats

Key Lock is only able to hold standard action keys and [One Shot modifier](../one_shot_keys) keys (for example, if you have your Shift defined as `OSM(MOD_LSFT)`).
This does not include any of the QMK special functions (except One Shot modifiers), or shifted versions of keys such as `KC_LPRN`. If it's in the [Basic Keycodes](../keycodes_basic) list, it can be held.

Switching layers will not cancel the Key Lock. The Key Lock can be cancelled by calling the `cancel_key_lock()` function.

QK_LOCK is incompatible with tap_code and tap_code16, to send QK_LOCK from code call the `begin_key_lock()` function.

## Examples

Force certain modifiers, in this case RCTL, RSFT, and RALT to toggle on/off like CAPS LOCK when pressed.

```
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_RCTL || keycode == KC_RSFT || keycode == KC_RALT) {
        if (!get_key_lock_state(keycode) && !get_key_lock_begun()) {
            begin_key_lock(); // emulates pressing QK_LOCK when needed
        }
    }
    return true;   
}
```