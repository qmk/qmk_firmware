## Space Cadet Shift: The Future, Built In

Steve Losh [described](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) the Space Cadet Shift quite well. Essentially, you hit the left Shift on its own, and you get an opening parenthesis; hit the right Shift on its own, and you get the closing one. When hit with other keys, the Shift key keeps working as it always does. Yes, it's as cool as it sounds.

To use it, use `KC_LSPO` (Left Shift, Parenthesis Open) for your left Shift on your keymap, and `KC_RSPC` (Right Shift, Parenthesis Close) for your right Shift.

It's defaulted to work on US keyboards, but if your layout uses different keys for parenthesis, you can define those in your `config.h` like this:

    #define LSPO_KEY KC_9
    #define RSPC_KEY KC_0

You can also choose between different rollover behaviors of the shift keys by defining:

    #define DISABLE_SPACE_CADET_ROLLOVER

in your `config.h`. Disabling rollover allows you to use the opposite shift key to cancel the space cadet state in the event of an erroneous press instead of emitting a pair of parentheses when the keys are released.

The only other thing you're going to want to do is create a `Makefile` in your keymap directory and set the following:

```
COMMAND_ENABLE   = no  # Commands for debug and configuration
```

This is just to keep the keyboard from going into command mode when you hold both Shift keys at the same time.
