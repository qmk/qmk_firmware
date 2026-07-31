# Sweep Cat

![Sweep Cat v2](https://raw.githubusercontent.com/smallwat3r/sweep-cat/main/images/v2.png)

A 30-key split keyboard based on [David Philip Barr's Sweep 2.2](https://github.com/davidphilipbarr/Sweep),
designed by [@smallwat3r](https://github.com/smallwat3r). Each half is a column-staggered 3x5 grid with
the four top-row corner keys removed, plus a two-key thumb cluster — 13 keys and 2 thumb keys per half.

Both halves are driven by a Pro Micro (or a compatible drop-in) wired with one switch per pin, and the
halves talk to each other over a TRRS cable on `D2`. The revisions are electrically identical; v2 only
adds splay to the two outermost columns (8° on the pinky, 3° on the ring finger).

## Keyboard Info

* Keyboard Maintainer: [smallwat3r](https://github.com/smallwat3r)
* Hardware Supported: Sweep Cat v1, Sweep Cat v2
* Hardware Availability: [Gerber and KiCad files](https://github.com/smallwat3r/sweep-cat)

Make examples for this keyboard (after setting up your build environment):

    make smallwat3r/sweep_cat/v1:default
    make smallwat3r/sweep_cat/v2:default

Flashing example for this keyboard:

    make smallwat3r/sweep_cat/v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the
[make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to
QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Default Keymap

With only 30 keys there is no room for `Q`, `T`, `Y` and `P` on the base layer, so the default keymap
puts them on the navigation layer, roughly where they would sit on a full 3x5 grid. It is meant as a
starting point — most builders will want to replace it with their own layout.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key on the left half (or the top right key on the right
  half) and plug in the controller on that side.
* **Physical reset button**: Briefly press the reset button soldered on the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured. In the default keymap
  this is the bottom left key of the navigation layer.
