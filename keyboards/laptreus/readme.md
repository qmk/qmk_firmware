# Laptreus

TODO: Insert cool photo

Laptreus is a 40% bluetooth keyboard in the style of the Atreus, which is specifically designed to sit atop your laptop (probably mac) keyboard.

## Flashing

**NOTE**: Make sure you don't have a second QMK keyboard plugged in when you do this!

To compile and flash to the board:

    make laptreus:debug:avrdude

To just compile:

    make laptreus:debug

Then use QMK toolbox to write the file
