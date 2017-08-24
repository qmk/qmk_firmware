## Key Lock: Holding down keys for you

Sometimes, you need to hold down a specific key for a long period of time. Whether this is while typing in ALL CAPS, or playing a video game that hasn't implemented auto-run, Key Lock is here to help. Key Lock adds a new keycode, `KC_LOCK`, that will hold down the next key you hit for you. The key is released when you hit it again. Here's an example: let's say you need to type in all caps for a few sentences. You hit KC_LOCK, and then shift. Now, shift will be considered held until you hit it again. You can think of key lock as caps lock, but supercharged.

Here's how to use it:

1. Pick a key on your keyboard. This will be the key lock key. Assign it the keycode `KC_LOCK`. This will be a single-action key: you won't be able to use it for anything else.
2. Enable key lock by including `KEY_LOCK_ENABLE = yes` in your Makefile.
3. That's it!

Important: switching layers does not cancel the key lock. Additionally, key lock is only able to hold standard action keys and One Shot modifier keys (for example, if you have your shift defined as `OSM(KC_LSFT)`; see [One Shot Keys](quantum_keycodes.md#one-shot-keys)). This does not include any of the QMK special functions (except One Shot modifiers), or shifted versions of keys such as KC_LPRN. If it's in the [basic_keycodes](basic_keycodes.md) list, it can be held. If it's not, then it can't be.
