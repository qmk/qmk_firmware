# Debug layout

This layout is expressly for debugging to see if your keys are working.

## Flashing

**NOTE**: Make sure you don't have a second QMK keyboard plugged in when you do this!

To compile and flash to the board:

    make laptreus:debug:avrdude

To just compile:

    make laptreus:debug

Then use QMK toolbox to write the file

## Testing

Now that you've got the image flashed, do the following:

* Open a new text document
* Click each key in order and hit enter (with the other keyboard) between each line
* For any keys that don't register, hit space (with the other keyboard) and continue on
* You'll end up with something looking like this:

    a1bcdefghijkl
    a2bcdefghijkl
    a3bcdefghijkl
    a4bcdefghijkl

But almost certainly it won't be perfect, so lets go through some scenarios:

### Blank letter

For lines that look like this:

    a1bc efg ijkl

* Option 1: Bent pin - Pull out the switch in those spots, probably the pin got bent when you inserted it into the hotswap socket. Gently bend the pin straight and re-insert.
* Option 2: Broken joint on hotswap - If the pin looks okay, try connecting the two metal plated holes underneath the hotswap holes to see if the letter comes out. If it does, reflow (aka, apply some flux to both pads and reheat) the solder joint.
* Option 3: Diode is backwards - TODO
* Option 4: Something else - Hop in the discord and let's chat!

### Duplicate letter

For lines that look like this:

    a1bccdefghijkl (double c)

* Option 1: TODO

### Second letter sent (same row)

For lines that look like this:

    a1bcddefghijkl (c sent c AND d)

* Option 1: TODO
