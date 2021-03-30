pvinis' keymap
==============

This is a getting-used-to keymap for the [ErgoDox EZ][ez]. It's very much a work in progress.

[ez]: https://ergodox-ez.com/

## Table of Contents

* [Todo](#todo)
* [Layouts](#layouts)
  - [Base layer](#base-layer)
  - [Beginner layer](#beginner-layer)
  - [QWERTY layer](#qwerty-layer)
  - [CARPALX layer](#carpalx-layer)
  - [System Control layer](#system-control-layer)
  - [Template layers](#template-layers)
* [Building](#building)

# Todo

- [ ] Generate images from keymap
- [ ] Implement algernon's heatmap
- [ ] Implement `KC_POP`

# Layouts

## Base layer

This is the base layer that contains the common buttons of all keymaps. Right now, it has the top left button as a `flash` button when it's tapped 4 times, and the two thumb islands. The islands contain the `space` and `enter` keys on the right, the `backspace` and `shift` on the left, and all the 1x1 keys are just layer switches.
Every time I connect the keyboard, I press the `BEGIN` layer switch, and then start typing.
Recently, I added a few application "shortcuts", that basically call `ctrl`+`alt`+`cmd`+`<key>`, and `<key>` is `S` for Slack, `X` for Xcode, `M` for Messenger. Using [Hammerspoon][hammerspoon], I show/hide the application.

[hammerspoon]: http://www.hammerspoon.org/

## Beginner layer

This is a basic keymap I use right now until I'm comfortable typing on the Ergodox. Currently uses a QWERTY layout, and the `([{}])` on the middle keys. Not a perfect layout, and its going to go away at some point, but for now thats my daily driver.

## QWERTY layer

This is basically the same as the `BEGIN` layer, but it might go away. I'm not using it, but I should have a QWERTY layout on the keyboard, in case someone else wants to try it out, or if I completely forget how keyboards work! At some point, this and the `BEGIN` layer will become one.

## CARPALX layer

This is here as a placeholder. I want to transition to [Carpalx QGMLWY][carpalx] or [White][white] at some point. They both look very interesting and more comfortable to type on, but after I'm confident with typing on the Ergodox.

[carpalx]: http://mkweb.bcgsc.ca/carpalx/?full_optimization
[white]: https://github.com/mw8/white_keyboard_layout

## System Control layer

This one is a layer that, in time, will have controls like mouse movement, volume up/down, mute, sleep, restart, shutdown, etc.

## Template layers

I have two commented out layers that are just templates, so I can easily create a new layer.

# Building

```
$ git clone https://github.com/qmk/qmk_firmware.git
$ cd qmk_firmware/keyboards/ergodox/keymaps/pvinis
$ make
```
