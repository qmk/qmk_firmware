# Default layout

This is the default layout for the Laptreus

## Flashing

**NOTE**: Make sure you don't have a second QMK keyboard plugged in when you do this!

First, connect your laptreus via the USB charging cable (standard micro USB)

To compile and flash to the board:

    make laptreus:default:avrdude

To just compile:

    make laptreus:default

Then use QMK toolbox to write the file
