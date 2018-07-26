# swedish-lindhe ErgoDox (EZ) keymap

This is a setup that is very useful for me. It may or may not be for
you. I will use it in conjunction with the A5 overlayed sv_SE layout.

The layout is subject to change (in particular I'm thinking about adding
a macro recording feature), but it have not changed much the past year
or two so you can expect it to be stable enough to learn it.

A5: http://aoeu.info/s/dvorak/svorak
My xkb map: https://github.com/lindhe/dotfiles/blob/master/usr/share/X11/xkb/symbols/se-A5

The most major points:
======================

I think the layout image can be found on
[www.keyboard-layout-editor.com](http://www.keyboard-layout-editor.com/#/gists/d84bc5915707cb30a4f9f754e06ecea3)

L0:
---

* Easily accessible F11 key for fullscreening
* Print screen
* Middle mouse button for X-paste
* Improved reachability of meta buttons (LCtrl, LALt, AltGr, LGui etc.)
* Cluster Page Up/Down + Home/End by the right thumb
* Vim-like arrow layout in right bottom row

* Set media layer toggle to right thumb (Enter)
* Set apostrophe on LCtl (putting it next to some other small
  characters)

L1:
---

* Full function key layout
* Teensy button

L2:
---

* Improved media buttons layout (close by the jkl; Vim binding)
* Improved layout of emulated mouse buttons

LED behaviour to binary+CAPS
============================

The ErgoDox LEDs on this layout is using the two rightmost LEDs as the
two LSB in a two digit binary number, representing layer 0, 1, 2 and 3.
The leftmost byte/LED indicates CAPS status.
