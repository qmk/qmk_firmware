# replicaJunction - Atreus Layout #

This layout is designed to make the absolute most out of the Atreus 40% keyboard.

I was enchanted with the idea of the Atreus keyboard after using my Ergodox for several months. I wanted something of a similar form factor that was easily portable, so I could bring and transport a keyboard to my workplace without much hassle. After building the Atreus keyboard, though, I realized very quickly that the 40% form factor requires a lot more creativity than a full-size keyboard (even one as strangely-shaped as the Ergodox).

The default Atreus keyboard layout provides all the necessary keys in order to function with the keyboard, but as a programmer, I needed quicker access to just about everything. I noticed that the default layer didn't include any dual-role keys, and so I started on my journey to build my perfect layout for the Atreus.

I won't claim that this layout is perfect for everyone. It does make several significant changes from the "normal" Atreus layout. In my own use, though, I've found this keyboard turbocharges my Atreus, and gives it the power of a full-size keyboard without the size.

## Base Layer ##

![Atreus base layout](atreus-replica-base.png)

The letters on this layout are arranged in the [Colemak Mod-DH layout](https://colemakmods.github.io/mod-dh/).

Note that there are four dual-purpose keys: Shift (Backspace), Ctrl (Delete), Alt (Enter), and Space (Number layer). In QMK, these dual-role keys can be made to hold their primary key by double-tapping the key and holding on the second tap. For example, if I wanted to insert a long string of Spaces, I would tap the Space key, then tap it again and hold. A single press and hold would trigger the secondary function of the key instead.

There is still one blank key on this layout. I haven't decided what to use it for yet. On my keyboard, I have this assigned to another Shift key.

## Extend Layer ##

![Atreus extend layer](atreus-replica-extend.png)

This layout is designed primarily for keyboard navigation. Arrow keys are easily accessible under the right hand (a welcome change from the original Atreus layout, which places them under the left hand), along with Home/End and PgUp/PgDn.

Modifiers are also placed under the home row of the left hand. One of the single keyboard actions I use most is Shift+Ctrl+Left/Right to select a whole word; this layer makes those keypresses simple by adding the Ctrl and Shift keys in easy-to-reach locations. In fact, I liked this idea so much that I added double modifiers in the row beneath it, so I can now press Ctrl+Shift with a single key instead of pressing both keys individually. Using this layer takes some practice to remember which modifiers are under which fingers, but it makes for much less awkward hand motions when using modifiers on a regular basis.

The Space key exists to prevent going from this layer directly into the Number layer.

## Number and Symbol Layer ##

![Atreus number and symbol layer](atreus-replica-num.png)

This layer provides the only way of accessing number keys on this keyboard, since it's too small for its own number row. Note that even though they are laid out in the number pad fashion, they send the "regular" number keystrokes. Games and programs that specifically use NumPad keys are not supported in this layout at the moment.

This layer also provides plenty of symbol shortcuts. Most of these can be accessed through other means (like Shift+8 for the asterisk), but having shortcut keys to them makes for one less keypress, which adds up quickly when using these symbols on a regular basis. I've been through many revisions of this concept on my Ergodox as well as the Atreus, and I've finally arrived at this layout as the one that provides the symbols I need most frequently in places I can think to expect them. The Ordinary layout from the Ergodox-EZ keyboard in this repository was a large influence in this design.

## Function Layer ##

![Atreus function layer](atreus-replica-function.png)

Function keys (F1-F12) are on this layer, as well as some more generic "functions" such as media keys. I've also set up a mirror image of the arrows from the Extend layer in case I need to use these with my left hand, but I don't do this very often.

The reset key is on this layer, as well as a toggle from Colemak to QWERTY and back. The QWERTY layer is not currently documented (nor is a small "gaming" layer that adds mouse keys on top of QWERTY).