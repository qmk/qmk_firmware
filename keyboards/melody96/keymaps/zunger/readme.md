* The "Cadet-Style" keymap for the melody96.
* Author: Yonatan Zunger (zunger@gmail.com)

This is an experimental keymap being used both for practical reasons (as my daily driver) and to
work out the ideas of a "space-cadet-style" keyboard which can type text and mathematical symbols
with equal ease. It's designed for anyone who frequently needs to do this outside of a LaTeX
environment, or for anyone who loves the old "Space Cadet" keyboard! And it works at its best when
you have actual Cadet keycaps (like SA Symbolics) installed, because those keycaps will actually
show what you get.

The core idea of this keyboard is that, in addition to a QWERTY base layer and a function layer, it
supports two additional base layers -- the GREEK layer (the analogue of the Space Cadet "Greek," or
"Front," keys) and the CADET layer (the analogue of the Space Cadet "Top" keys). These layers use
Unicode to generate all of the mathematical symbols you can find on a traditional Space Cadet
layout, plus a bunch of extras.

Because Unicode can't be encoded using the traditional USB HID protocol, QMK does some clever but
horrifying things to fool your OS. One consequence of this is that the shift key needs to be handled
by the keyboard firmware, not the host OS. To handle this, we have two additional layers --
SHIFTGREEK and SHIFTCADET -- and handle the flipping between all of these layers here in the
firmware.

*The simple bit: Using this layout on a Melody96*

At the core of this layout are three special modifier keys and two special lock keys:

* The GREEK key, to the right of the spacebar, activates the GREEK layer. GREEK+SHIFT activates
  SHIFTGREEK. These keys generate Greek letters on the letter keys (thus the name), and a few
  mathematical symbols on other keys. They correspond to the notations on the front of traditional
  Space Cadet keys; if your capset doesn't include those (alas, most don't), they're the "pretty
  obvious" mappings.
* The CADET key, to the right of GREEK, activates the CADET layer. These are the symbols above the
  letters on a Space Cadet layout. CADET+SHIFT activates the SHIFTCADET layer, with even more
  symbols.
* The FUNCTION key, to the right of CADET, activates the function layer. This is where you have a
  reset mechanism, a selector for which Unicode input type you want, and so on.

Additionally, GREEK+ALT is equivalent to CADET. This is handy for other keyboards where you don't
have room for this many modifiers.

The lock keys are:

* Caps lock, if you use it, will also act as a "shift lock" for the Greek and Cadet layers. Shift
  lock is slightly different, in that while it is engaged shift will _dis_engage it; that's actually
  pretty useful when typing math.
* An additional "layer lock" key, by default where "num lock" usually goes, will lock the choice of
  base layer. To use it, hold down any invocation of the GREEK or CADET layers, or none at all, and
  hit lock; it will then put you in that layer. The corresponding modifier key will then toggle you
  back to the QWERTY layer. (So for example, if you hit GREEK+LAYER_LOCK and release them, you're
  now typing in Greek; the GREEK modifier would cause you to type QWERTY momentarily. To go back to
  ordinary QWERTY mode, you'd just hit LAYER_LOCK again with no modifiers held)

To see the full layout, check out the big comment in keymap.c.

*A less-simple bit: Adapting this to other keyboards*

This is really a canary for generic Cadet implementations. Before this can be made generic, a few
things will have to happen:

(1) Instead of a fixed keymap, this has to be refactored into some kind of array showing the
mappings of QWERTY-layer keys onto the appropriate code points in the GREEK and CADET layers, and
some preprocessor magic needs to auto-transform this plus a traditional keymap for the QWERTY layer
into keymaps for all five of the core layers. (Function layers would presumably be handled on a
per-keyboard basis)

(2) The standard mapping of those should have some #define's to control things like whether there
are physical F-keys (you would probably want to move superscript and subscripts onto the numbers if
there weren't, and figure out what to do with the non-numeric super/sub keys), whether you actually
want to enable GREEK+ALT=CADET, and so on;

(3) There should be support for controlling indicator LEDs based on the base layer selection,
caps/shift lock state, and layer lock state, as well as for triggering audio on transitions;

(4) All the core fancy logic in process_record_user which implements the layer handling should be
factored out into its own function, so that keyboards can easily reuse that, too.

This is a lovely TODO for future work, and could be particularly fun to go along with new releases
of SA Symbolics and the like. Anyone interested in such things, ping me!
