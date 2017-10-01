# callum’s planck layout

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

We have five layers. A `BASE` layer, in colemak; a `MOVE` layer, with an arrow
cluster, other movement keys, and hotkeys; a `SYMB` layer, with numbers and
symbols; a `FUNC` layer, with function keys and media keys; and a `MORE` layer,
with stuff that doesn’t fit anywhere else. The `MORE` layer is activated by
holding the Move and Symb keys simultaniously.
