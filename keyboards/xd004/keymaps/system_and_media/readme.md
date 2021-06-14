# Slightly more advanced keymap for XD004 PCB

A somehow more useful keymap, allowing one to move across virtual desktops on Windows, etc.

It also has a 'Super Alt-F4' key for Windows that, when tapped does Alt-F4, unless two consecutive taps are less than 300ms apart, in which case the second tap becomes Enter. This allows you to close all apps doing taps, and then when the System shutdown window arrives you do a second quick tap and it will type enter, thus shutting down the computer.

## Build

To build the keymap, simply run `make xd004:system_and_media`.
