ToyKeeper's Keychron V1/Q1 Layout
=================================

A relatively straightforward 75% layout with some extras.


## At A Glance

Here's my Keychron V1 with some "AF SA" profile keycaps:
![Keychron V1](http://toykeeper.net/keyboard/qmk/keychron-v1/front.2.jpg)

This is the layout internally, showing all the functions for each key:
![TK V1](http://toykeeper.net/keyboard/qmk/tk-v1-q1.png)

This layout diagram can be edited [here](http://www.keyboard-layout-editor.com/#/gists/cd13a756e9e519476489ab21df8140ba).


## Core Features

Most of the features are shared by all my keymaps.  Check my
[user dir](../../../../../../users/toykeeper)
for the details.

Everything below is specific to this particular model of hardware.


## Hardware-Specific Notes

Things which differ from other models:

  * F1-F12 row
    * The user can choose whether the F1-F12 row emits normal keycodes or more
      fancy keycodes.  The default is "fancy" keycodes, but they can change
      this by pressing the F-Lock key.

  * Dipswitch
    * Two core layouts can be saved for easy access with the dipswitch.  Each
      dipswitch position is treat as a "save slot".  Any time the user changes
      the core layout via a hotkey, it is saved to the current slot.  Then it
      can be activated later simply by flipping the switch to that position.

  * Knob
    * Turn for mouse wheel up/down, or Star + turn for mouse wheel left/right.
    * Tap for Mute

  * Muscle-memory-compatible with 65% layouts.  If you're accustomed to having
    Esc next to the "1" key, it still works on this layout.

  * Home/PgUp/PgDn/End keys are shifted up one row, because this hardware is
    missing a key where the bottom of that set should be.  This is awkward, but
    the best I could do with a key missing.


## Known Issues

* Reflashing frequently fails on this model.  If it fails, run qmk flash again
  and again until it works.  It may help to turn off RGB lighting first,
  because the LEDs seem to draw enough power to interfere with ROM flashing.
  It may also help to install some extra udev rules from the QMK utils/ dir.

* A missing key (above the right arrow) makes part of the layout awkward.


## More Pics

StarLock (Fn2 Lock) activated:
![StarLock](http://toykeeper.net/keyboard/qmk/keychron-v1/starlock.1.jpg)

A bit closer:
![Detail](http://toykeeper.net/keyboard/qmk/keychron-v1/starlock.3.jpg)

Fn1 (Moon) activated:
![Fn1 Detail](http://toykeeper.net/keyboard/qmk/keychron-v1/fn1.1.jpg)

Fn3 (swirl) activated:
![Fn3 Detail](http://toykeeper.net/keyboard/qmk/keychron-v1/fn3.1.jpg)

Side view, showing the keycap profile:
![Side View](http://toykeeper.net/keyboard/qmk/keychron-v1/side.1.jpg)


