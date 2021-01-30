## Greetings, Traveler!

This layout is for the [Massdrop ALT Keyboard](https://drop.com/buy/massdrop-alt-mechanical-keyboard) and targets Windows machines.

This keymap is very similar to the default keymap for the Drop ALT, but it overloads the left alt key to behave like an additional 'Fn' key while keeping the functionality of the alt key intact.

### For example:
```
LeftAlt + 1...N      -> F1...FN
LeftAlt + L/R Arrows -> Home/End
LeftAlt + Home       -> End
LeftAlt + Backspace  -> Delete
LeftAlt + Esc        -> Backtick (`)
```

The novel part of this keymap is that it **preserves the default functionality** of the left alt key, so ```'alt + tab', 'ctrl + alt + del', 'alt + f4'```, etc. all work as expected without using any janky timers.

Everything also works with other modifier keys, so ```'alt + L/R' and 'alt + shift + L/R'``` work great for text manipulation to select lines.

This **'super alt'** keymap will feel very familiar for anyone **coming from macOS** since the Windows alt key is in the same position as CMD on macOS keyboards.

And finally, the original alt key functionality can be toggled at any time by pressing **```'Fn + period'```** so even if you don't like it, you can turn it off.

This keymap was based on the 'default' Drop ALT keymap (and _not_ 'default_md') which means it supports all the fancy QMK RGB patterns, and isn't limited to the stock options that come with the board.

It's also worth noting that this keymap fixes an outstanding issue where the caps lock LED flickers when the RGB mode is keylight or underglow. I could not find a general purpose fix, but the one included here works quite well.

If you have any questions, feel free to reach out to me at: ewersp [at] gmail [dot] com.

Enjoy! **<3**
