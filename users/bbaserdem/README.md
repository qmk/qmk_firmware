# Overview

I have mostly ortholinear keyboards, which share a lot of functions.

## Current keyboards

* [Bigseries](../../keyboards/bigseries/1key/keymaps/bbaserdem)
* [Gherkin](../../keyboards/40percentclub/gherkin/keymaps/bbaserdem)
* [Let's Split Eh](../../keyboards/lets_split_eh/keymaps/bbaserdem)
* [Planck (rev 4, light and rev6)](../../keyboards/planck/keymaps/bbaserdem)
* [XD75](../../keyboards/xd75/keymaps/bbaserdem)

Unfortunately, the output on my bigswitch pcb broke,
and the producer woodkeys is AWOL, (along with my 200$ for the APX case)
thus I cannot really test it out.
Also, I'm using my planck all the time,
and am not testing the other layouts for bugs.

## Planned keyboards

* [Let's Split](../../keyboards/lets_split/keymaps/bbaserdem)
I have two proton C's, and i want to build a board that uses choc low switches.
I have the pcb for it, but I do need a case to solder in the switches.
For which, I have not seen anything.
* [Infinity Ergodox](../../keyboards/ergodox_infinity/keymaps/bbaserdem)
I have this at hand, but never could get the LED display to work.


# Layout

I use Linux, so my setup reflects this a bit.
Optimized for software implementation of Dvorak and Turkish F layouts.

* **Base**: Base layer.
* **Game**: Brings arrow keys to the main cluster, comfortable for gaming.
* **Numeric**: Has numericals and symbols.
* **Function**: Media and function keys.
* **Mouse**: Manipulates mouse. Can be locked.
* **Music** Allows playing sounds.

I do want to implement a unicode layer for character input,
but I don't know how to get ibus to play nice with software level keymapping.

# Functionality

I try to implement layer indicators on all my keyboards if I can.
Still waiting on planck rgb daughter board.

# Shoutout

Shoutout to drashna for getting the userspace shenanigans started;
all my code is pretty much inspired from his.
Also a big shoutout to Alison Oğuz and Veysi Erkcan Özcan,
for getting me started with the C language,
and taught me coding.
