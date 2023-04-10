ToyKeeper's Keychron Q65 Layout
===============================

A 69% layout with some extras.
(69% = 65% plus 4 keys and a knob on the left side for symmetry)


## At A Glance

Here's my Keychron Q65 with MT3 profile black+purple keycaps:
![Keychron Q65](https://i.imgur.com/pQcKpFL.jpg)

This is the layout internally, showing all the functions for each key:
![TK Q65](https://i.imgur.com/a3kwQzG.png)

This layout diagram can be edited
[here](http://www.keyboard-layout-editor.com/#/gists/9e5289cc338d78520da1495d697ed72a).


## Core Features

Most of the features are shared by all my keymaps.  Check my
[user dir](../../../../../../users/toykeeper)
for the details.

Everything below is specific to this particular model of hardware.


## Hardware-Specific Notes

Things which differ from other models:

  * Macro column
    * The left side has 4 extra keys and a knob.
    * The extra column has several different modes, indicated by color.
      * Blank: Base layer.  App launchers and dynamic macro playback.
      * Hold Moon: App close (F14), app launcher (F13), and dynamic macro recording.
      * Moon layer: F15 to F18 (lower / raise / pin / group window)
      * Star layer: F19 to F22
      * Mouse layer: Button 1/2/3 and Warp (F23)
    * To activate a macro column mode, hold a layer key (or none) and press the knob.
    * Muscle memory makes Macro Key 1 (bottom) easy to hit by accident, so it
      has a non-destructive function and doubles as a second Moon key when
      held.

  * Dipswitch
    * Two core layouts can be saved for easy access with the dipswitch.  Each
      dipswitch position is treat as a "save slot".  Any time the user changes
      the core layout via a hotkey, it is saved to the current slot.  Then it
      can be activated later simply by flipping the switch to that position.

  * Knob
    * Turn for mouse wheel up/down, or Star + turn for mouse wheel left/right.
    * Tap to change mode for the extra column.


## Known Issues

* Reflashing frequently fails on this model.  If it fails, run qmk flash again
  and again until it works.  It may help to turn off RGB lighting first,
  because the LEDs seem to draw enough power to interfere with ROM flashing.
  It may also help to install some extra udev rules from the QMK utils/ dir.


## More Pics

![Keychron Q65](https://i.imgur.com/RtwSV6V.jpg)
![Keychron Q65](https://i.imgur.com/ewCJIun.jpg)
![Keychron Q65](https://i.imgur.com/P3XALA7.jpg)
![Keychron Q65](https://i.imgur.com/UIzoxXF.jpg)

