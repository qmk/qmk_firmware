# Twey's Home Configuration
## Layers
- Layer 0: Non-ANSI Dvorak layout, with modified modifiers — all
  modifiers on thumb keys, as well as return and space.
- Layer 1: Default symbol layout.
- Layer 2: Default media/mouse layout.
- Layer 3: Plover-oriented stenography layer.

## Unusual features
The Plover key (top right key on the left half) also sends my Plover
‘toggle’ chord (SH-FT) when pressed, as well as toggling the steno
layer, so you can toggle between steno and typing modes with a single
keypress.

If you want to use this feature, you'll need to add:

    "SH-FT": "{PLOVER:TOGGLE}"

to your Plover dictionary.
