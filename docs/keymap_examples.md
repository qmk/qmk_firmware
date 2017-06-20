# Share your keymap idea here!
https://github.com/tmk/tmk_keyboard/issues/265

---

## Reverse-shifted for numbers
With pressing Shift and '1' key you get **1** while with just '1' key you get **!**.
- https://geekhack.org/index.php?topic=41989.msg1959718#msg1959718


## KBT Pure layout
Keymap code on Alps64
https://github.com/thisisshi/tmk_keyboard/blob/15fe63e8d181a8a95988dcc71929f0024df55caa/keyboard/alps64/keymap_pure.c

and guide.
https://github.com/thisisshi/tmk_keyboard/blob/77ac0805ade565fb23657e3644c920ada71edccf/keyboard/alps64/Guide.md

## Prevent stuck modifiers

Consider the following scenario:

1. Layer 0 has a key defined as Shift.
2. The same key is defined on layer 1 as the letter A.
3. User presses Shift.
4. User switches to layer 1 for whatever reason.
5. User releases Shift, or rather the letter A.
6. User switches back to layer 0.

Shift was actually never released and is still considered pressed.

If such situation bothers you add this to your `config.h`:

    #define PREVENT_STUCK_MODIFIERS

This option uses 5 bytes of memory per every 8 keys on the keyboard
rounded up (5 bits per key). For example on Planck (48 keys) it uses
(48/8)\*5 = 30 bytes.
