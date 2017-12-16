# The Leader Key: A New Kind of Modifier

If you've ever used Vim, you know what a Leader key is. If not, you're about to discover a wonderful concept. :) Instead of hitting Alt+Shift+W for example (holding down three keys at the same time), what if you could hit a _sequence_ of keys instead? So you'd hit our special modifier (the Leader key), followed by W and then C (just a rapid succession of keys), and something would happen.

That's what `KC_LEAD` does. Here's an example:

1. Pick a key on your keyboard you want to use as the Leader key. Assign it the keycode `KC_LEAD`. This key would be dedicated just for this -- it's a single action key, can't be used for anything else.
2. Include the line `#define LEADER_TIMEOUT 300` somewhere in your keymap.c file, probably near the top. The 300 there is 300ms -- that's how long you have for the sequence of keys following the leader. You can tweak this value for comfort, of course.
3. Within your `matrix_scan_user` function, do something like this:

```
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      register_code(KC_S);
      unregister_code(KC_S);
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_H);
      unregister_code(KC_H);
    }
    SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
```

As you can see, you have three function. you can use - `SEQ_ONE_KEY` for single-key sequences (Leader followed by just one key), and `SEQ_TWO_KEYS` and `SEQ_THREE_KEYS` for longer sequences. Each of these accepts one or more keycodes as arguments. This is an important point: You can use keycodes from **any layer on your keyboard**. That layer would need to be active for the leader macro to fire, obviously.
