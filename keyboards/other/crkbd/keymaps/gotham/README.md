# Gotham's custom CRKBD Layout

My take on the 40% layout with programming in mind. Do read about the layers, it helps with forming a mental model to remember the keymap better than just memorization.

## Layers
- QWERTY: Base layer. The idea is to reduce thumb movement by placing commonly used keys and layers on resting thumb positions (center thumb keys). You might need to play around with TAPPING_TERM to find your perfect setting. Also, both Lower and Raise buttons appear on both halves for easy access (think of it as: middle thumb key is Lower, outer thumb key is Raise).
- LOWER: Numbers, common symbols and navigation. Easiest layer to reach (middle thumb button on both halves). The nav is shaped as a T instead of an inverted T for a few reasons. First, Left and Right needed to be on the home row (since I use them a lot to navigate through code). But the Up key can't be on the top row because numbers occupy that space. So I moved the Up and Down keys one key down. It takes some getting used to, but I find this a great balance without separating the nav and number rows. The nav cluster also contains Home and End keys below Left and Right, making it a breeze to navigate through code.
- RAISE: All symbols are here, arranged in a way that can be (kind of) deduced more by logic and less by memory. On the left hand, the first 2 cols contain the symbols for shifted numbers 1-6, with ! and @ in the home row instead of the top row. Think of the 3 rows as symbols for 3 and 4, 1 and 2, 5 and 6). The next 2 cols contain common brackets. On the right hand is everything else. Note that -, _ and = are close to the home row because of how common they are in code. Operators (&, | and !) are on the top row for convinience. Just try and remember where +, *, < and > located. Admitedlly, the locations for these symbols could use improvement.
- ADJUST: Contains settings and Function keys. This is placed on the bottom-right corner (triggerred by the pinky), since the thumb keys already have multiple uses.

## Custom OLED
This keymap includes custom OLED font and code. The font contains some logos and status indidcators for some of the features I use (RGB and Audio). Enable OLED in rukes.mk to check it out. Feel free to reuse the font or parts of it.
__KNOWN BUG:__ When the computer sleeps, one of the OLEDs is always on (they don't turn off on their own, and the timeout doesn't work). I haven't been able to figure out what's going on there and am open to suggestions/PRs.

## Flashing
Flash using `make crkbd:gotham:avrdude` for Pro Micro and `make crkbd:gotham:dfu` for Elite-C.
