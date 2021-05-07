* Custom keymap for kbd67, for those who need to both code and type math.
* Author: Yonatan Zunger (zunger@gmail.com)

This keymap is presently rather Mac-centric, as it uses Mac media keys in its function layer and the
OS X Unicode input mode for the "magic" layers.

*Layer 0 (Base QWERTY):* The layout has a few minor quirks: grave escape, Home/End/PgUp/PgDn in the
right-hand column (rather than the more common Home/PgUp/PgDn/End), and a pause key between
backspace and home -- this being something I use for screen lock, a necessity when one works with
and sits next to security engineers. (Using a heavier switch on the pause key greatly reduces the
risk of accidental triggering) In OS X style, alt and win are swapped on the left-hand side.

The right-hand alt and gui keys take on a different meaning: right-alt lives up to its old name of
AltGr by invoking Greek (the "magic" layers, 2 and 3), and right-gui invokes the function layer.

*Layer 1 (Functions):* This layer deliberately sets KC_NO for the keys it doesn't use. I realize
this isn't common, but I like to keep my functions quite distinct from all other layers.

RESET can be accessed at Fn+Left Shift+Escape.

*Layers 2 and 3*: These are invoked by the "magic" key (AltGr) and by magic+shift. The
letters mostly produce Greek; the numbers, superscripts (magic) and subscripts (magic+shift); and
the various other keys, mathematical symbols. There unfortunately aren't nearly enough keys for all
the symbols I'd like, so magic+alt and magic+alt+shift may end up existing as well, giving this a
proper Space Cadet effect; but that said, it's going to be hard to remember where all these symbols
are without some extremely custom keycaps. In the limit of arbitrarily complex layers, the keyboard
will probably start running LISP and turn into EMACS.
