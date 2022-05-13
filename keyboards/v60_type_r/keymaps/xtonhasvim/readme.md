KB Paradise V60 Type R Xton Has Vim! Layout
======================

If you don't look closely, this layout mimics the default layout fairly well. Care
is taken to match the FN layer to the keycaps that the TypeR comes with. I wrote this layout 
for a keyboard that I'm giving my intern as a parting gift and wanted it to be as easy to learn
as possible.

The key differences:

- Holding capslock down activates the movement layer, much like the vimouse layout except that I'm using the xtonhasvim movement layer.
- Capslock+return (or right-control) activates vim mode!

## Keymap Notes

- Alternate underglow modes are not supported. Instead the underglow is used to indicate state. It can be turned off and dimmed. Polestar underglow LEDs are not individually addressable, sadly.

### Build

To build this keymap, simply run `make v60_type_r:xtonhasvim` from the root project directory. Flash using QMK Toolbox
