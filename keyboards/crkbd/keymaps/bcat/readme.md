# bcat's Corne layout

This is my favorite split ergo layout for typing, featuring the traditional
four ortho/ergo layers (Default, Lower, Raise, Adjust). It is loosely inspired
by the default Planck (numbers on Lower, symbols on Raise) and Crkbd (Space on
left, Enter on right) layouts, but has since been redesigned heavily according
to the principles described below:

* Since most of the modifiers are on the left half, keys frequently pressed
together with mods (e.g., numbers, function keys, etc.) are on the Raise layer
activated by the right thumb.

* Navigation can be done on the right half alone, to enable simultaneous
left-handed mousing. Additionally, Web pages can be scrolled with Space or
Shift+Space on the left half alone, to enable taking notes with the right hand
at the same time.

* Other than Right Shift (which I seldom use), mods aren't rebound on layers.

* Backspace is bound in the same place on every layer to avoid having to let go
of layer-switch keys to correct mistakes.

## Default layer

![Default layer layout](https://i.imgur.com/s1LDlSQ.png)

([KLE](http://www.keyboard-layout-editor.com/#/gists/08d9827d916662a9414f48805aa895a5))

* The alpha keys are a standard QWERTY layout, no funny business there.

* Tab and Backspace in familiar locations from my row-staggered boards (almost
all of which use HHKB-style split backspace).

* Likewise, the Ctrl key is in the same place as on my row-staggered boards
(where I've been remapping Caps Lock as Ctrl since before even using QMK).

* There are two shift keys, because I do use Right Shift on occasion (even
though I'm predominately a Left Shift-er).

* Lower and Raise layer-switch keys are below the left and right thumb,
respectively, when resting my fingers on the home row.

* Space and Enter are on the big thumb keys so they're easy to press.

* Alt is on the left so I can navigate back (Alt+Raise+H) and forward
(Alt+Raise+L) having to uncomfortably hit two thumb keys on the same half. This
puts Super on the right by the process of elimination.

* Escape shares a mod-tap key with Ctrl, which is convenient for Vim, but not
something I'm totally in love with, as even after tweaking `TAPPING_TERM` I
still get occasional spurious Esc taps. (I might move Esc up a key and put Tab
on a layer, but that'd take some getting used to....)

## Lower layer

![Lower layer layout](https://i.imgur.com/rDlSmrA.png)

([KLE](http://www.keyboard-layout-editor.com/#/gists/c3fba5eaa2cd70fdfbdbc0f9e34d3bc0))

* This could also be called the "symbol layer".

* Shifted numbers are bound in their usual positions on the top row.

* Hyphen/Underscore and Equals/Plus are in the right index and middle finger
columns for easy reach. They share the same relative position as on a
row-staggered keyboard, and the shifted versions are physically above the
unshifted versions as a mnemonic device.

* Brackets and braces are placed below the parens for easy recall. Once again,
the shifted versions are on the home row and the unshifted versions are on the
bottom row.

* Forward Slash/Pipe and Backtick/Tilde fill out the remaining positions on the
right half, with the same relative positions as on a row-staggered HHKB layout.

* Caps Lock is bound in the same position as on an HHKB, for lack of an obvious
better location.

* Some extra keys are placed on the bottom row of the left half, ensuring every
key on a TKL has a binding.

* The left-half home row is reversed for future use. (It's free real estate.)

## Raise layer

![Raise layer layout](https://i.imgur.com/cVoKygg.png)

([KLE](http://www.keyboard-layout-editor.com/#/gists/08b44355d4ca85d294bad9e2821f91d7))

* This could also be called the "number layer".

* Unshifted numbers are bound in their usual positions on the top row.

* Arrow keys are on VIM-style HJKL keys.

* Home/End and Page Up/Page Down are in the same column as the arrow keys, but
translated down one row. (This means that the comma and period keys are not
bound on the number layer, which makes data entry a bit funky. I might add a
dedicated numpad layer to compensate.)

* Function keys F1–F10 take up most of remaining space on the left half, with
F11 and F12 spilling over to the right half. (This puts the most used function
keys (F1–F5) on the home row.)

* Insert and Delete are on the rightmost column, because there didn't seem to
be a better place to put them.

## Adjust layer

![Adjust layer layout](https://i.imgur.com/LEHM4DU.png)

([KLE](http://www.keyboard-layout-editor.com/#/gists/77e7572e077b36a23eb2086017e16fee))

* Media keys are centered around the ESDF cluster, just like I arrange them on
row-staggered keyboards. (It's even more sensible on with columnar stagger.)

* The navigation and Enter keys are replaced by RGB controls. Again, this
mirrors the positioning I use on my row-staggered keyboards.

* Finally, reset keys live at the top-left corner of the right half where it's
reasonably hard to press them by accident.
