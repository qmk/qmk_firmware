# Debug layout

This layout is expressly for debugging to see if your keys are working.

## Flashing

**NOTE**: Make sure you don't have a second QMK keyboard plugged in when you do this!

To compile and flash to the board:

    make laptreus:debug:avrdude

To just compile:

    make laptreus:debug

Then use QMK toolbox to write the file

# Testing

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

## Step 1: Get all the letters to output _something_

For lines that look like this:

    a1bc efg ijkl

* Option 1: Bent pin - Pull out the switch in those spots, probably the pin got bent when you inserted it into the hotswap socket. Gently bend the pin straight and re-insert.
* Option 2: Broken joint on hotswap - If the pin looks okay, try connecting the two metal plated holes underneath the hotswap holes to see if the letter comes out. If it does, reflow (aka, apply some flux to both pads and reheat) the solder joint.
* Option 3: Diode is backwards - If connecting the two metal pins didn't work, double check that the diode is the right direction. This may also need to be reflowed.
* Option 4: ??? - Hop in [the discord]() and let's chat!

## Step 2: Correct double letters

Once you have all the keys outputting _anything_, flash the default layout and do the same thing. If everything is working, your layout will look something like this:

    qwertyuiop
    asdfghjkl;'
    zxcvbnm,./

**Note**: Don't worry about hitting the backspace or command keys

### Duplicate letters

For lines that look like this:

    qwertyyuiop (double y)

* Option 1: Bent pin - Pull out the switch in those spots, probably the pin got bent when you inserted it into the hotswap socket. Gently bend the pin straight and re-insert.
* Option 2: Switch is broken - Try connecting the two metal plated holes underneath the hotswap holes to see if the letter comes out just once. If it does, the switch is broken and should be replaced. If you don't have another switch, you _may_ be able to unbend the leaf inside the switch, but it's really tricky.

### Second letter sent (same row)

For lines that look like this:

    qwertyyuiop (t sent t AND y)

* Option 1: ??? - I can't imagine how this would happen with this layout, but let me know if it does!

### Second letter sent (same column)

For lines that look like this:

    qwertgyuiop (t sent t AND g)
    qwertgbyuiop (t sent t AND g AND b)

* Option 1: Diodes are backwards - Some of the diodes on this column are backwards, you can use a diode tester to confirm the direction, or just check them with a magnifying glass and switch them if needed.
* Option 2: ???
