# Cap Words

This is taken from [Pascal Getreuer's implemenation](https://getreuer.info/posts/keyboards/caps-word/index.html), with a number of modifications. 

To enable Caps Word, add `CAPS_WORD_ENABLE = yes` to your `rules.mk`.

This is mostly a reproduction of Pascal's docs:

## Overview

All-caps identifiers like “MOD_MASK_ALT” are awkward to type.

Caps Lock would be the standard solution to this problem, but it is awkward: it needs a dedicated key to toggle it (an imposition on smaller keyboards), and we need to remember to toggle it off after typing the word. Or with normal shifting, we either perform finger gymnastics or need to stop typing in the middle of the word to release shift with one hand to switch to holding shift with the other hand. In my experience, this is a nuisance especially if your shift keys are mod-taps, as in home row mods.

Caps Word, implemented here, is a modern alternative to Caps Lock:

* Caps Word is activated by pressing the left and right shift keys at the same time. This way you don’t need a dedicated key for using Caps Word.
* Caps Word automatically disables itself at the end of the word.

**Compatibility**: I’ve tested that this implementation works with one-shot mods and Space Cadet Shift, and it predictably handles key repeating.

Unlike some other QMK Caps Word implementations, this library does not use the Caps Lock (KC_CAPS) keycode. It works even if the OS remaps Caps Lock to Ctrl or something else, as Emacs and Vim users often do.

## Using Caps Word
With the above flashed to your keyboard:

1. **Activating**: Press and release both left and right shift keys at the same time. If your shift keys are mod-taps, activate Caps Word by holding both shift mod-tap keys until the tapping term, then release them.
2. Then begin typing to get capitalized letters.
3. **Disabling**: Caps Word disables itself when the next word breaking key is typed.

If you want to explicitly stop Caps Word, press and release Ctrl or another non-shift modifier or layer key. This also disables Caps Word.

## Explanation
The code checks the mod bits on each key event, enabling Caps Word when both left and right shifts are active.

While enabled, Caps Word automatically presses and releases left shift (KC_LSFT) as needed so that letters are shifted and other keys are not. The word continues while typing a–z, 0–9, -, _, and backspace. Any other key is considered “word breaking” and disables Caps Word. You can edit the switch statement at the end of the process_caps_word() function to adjust which keys count as word breaking.
