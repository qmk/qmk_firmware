# purple-rw Keymap for Planck

This keymap is compatible with the [34-key layout v2](http://www.keyboard-layout-editor.com/#/gists/4aecf33eb403ba4a3a64b890dc8efb09).
Only 34 keys (3x5+2 each hand) are really needed.
Additional keys are for conveninence, but limited by available keycaps.
Mod-taps are avoided to eliminate wrong keycode when typing fast.
Designed for use with macOS in mind, with US/English layout.

## Design

My first design requires mostly 3x6+3 keys on each hand.  Besides the standard
symbols in the base layer, all the rest of symbols and number keys are in one
layer.  Modifiers are on the forth/bottom row, so no mod-tap is needed.

Since I move onto keyboards with only 5 columns each hand, I revised my design
to put all the number keys in a different layer.  Home-row modifiers are used,
and mod-tap is used on all the thumb keys.  `Backspace` and `Shift` on one
thumb key, and `Space` and `Symbol layer` on another.  I often get mistype
when entering commands such as "ls -a".  I tried disabling key repeat on
`Space`, and put a repeatable `Space` key in another layer, but that is
cumbersome.  Same for the `Backspace` key.  And I'm not able to find a good
timing setup for home-row mod, so once a while I still get modifiers triggered
unintentonally.

I accidentally learnt about callum's layout, so I'd like to give no-mod-tap
another try.  One thing I don't like in callum's layout is that number keys
are in a 2-thumb layer.  I type numbers a bit often, so I combine them with
the symbols.  If a keyboard has only 10 columns, then 6 lesser-used symbols
need to be accessed through a 2-thumb layer.

Numbers and symbols are placed mostly according to their frequency used in
computer languages, based on Xah Lee's data [here](http://xahlee.info/comp/computer_language_char_distribution.html).
I have also considered design principles mentioned by Pascal Getreuer [here](https://getreuer.info/posts/keyboards/symbol-layer/index.html).
