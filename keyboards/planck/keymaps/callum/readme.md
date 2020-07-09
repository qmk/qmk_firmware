# callum's planck layout

This is a layout for the grid planck, built with a few ideals in mind:

- Consistent and minimal response times should be maintained. Keys that react
  differently depending on whether they are tapped or held, keys that react
  differently if they are double tapped, etc. should be avoided – they
  inevitably send their keycode later than a normal key – interrupting the
  immediate feedback from the screen. Therefore we restrict ourselves to
  chording as our only means of getting more than one symbol out of a single
  physical key.

- The hands should never need to leave the home position. The usual culprit for
  this is the arrow cluster, so the arrow cluster should be as close to home as
  possible.

- There should be two of every modifier (one on each side), otherwise certain
  long key combinations become hard to make.

- It should be possible to do things you might want to do while using the mouse
  with only the left hand (e.g. change tabs, navigate back or forwards in
  browser history).

- Symbols should be arranged so that the most frequently used are easiest to
  reach. This includes numbers, and lower numbers are more commonly used than
  higher ones. (number arrangement borrowed from [dustypomeleau's minidox
  layout][].

[dustypomeleau's minidox layout]: https://github.com/qmk/qmk_firmware/tree/master/keyboards/minidox/keymaps/dustypomerleau
[keymap.c]: keymap.c
