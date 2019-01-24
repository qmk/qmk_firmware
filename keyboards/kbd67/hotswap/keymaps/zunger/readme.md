* Custom keymap for kbd67, for those who need to both code and type math.
* Author: Yonatan Zunger (zunger@gmail.com)

This keymap is presently rather Mac-centric, as it uses Mac media keys in its function layer and the
OS X Unicode input mode for the "magic" layers.

*Layer 0 (Base QWERTY):* The layout (somewhat unusually) puts the pause key at the top right; I use
this as a fast screen lock, which is very important when working with and sitting next to security folks.

Backspace and backslash are currently swapped to match my keycaps, but I'm not thrilled about it and
will probably change that after a bit more experimenting.

There's a grave key still on the map, in addition to a grave escape, and that should probably be
replaced with something more useful. Not sure what yet.

*Layer 1 (Functions):* This layer deliberately sets KC_NO for the keys it doesn't use. I realize
this isn't common, but I like to keep my functions quite distinct from all other layers. It has RESET
at fn-esc, and various media controls elsewhere.

*Layers 2 and 3*: These are invoked by the "magic" key (beneath pause) and by magic+shift. The
letters mostly produce Greek; the numbers, superscripts (magic) and subscripts (magic+shift); and
the various other keys, mathematical symbols. There unfortunately aren't nearly enough keys for all
the symbols I'd like, so magic+alt and magic+alt+shift may end up existing as well, giving this a
proper Space Cadet effect; but that said, it's going to be hard to remember where all these symbols
are without some extremely custom keycaps.
