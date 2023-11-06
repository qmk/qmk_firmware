# Levinson

## Colors

- https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md
  - main docs.
- https://github.com/qmk/qmk_firmware/blob/master/quantum/color.h
  - list of colors
- https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight.h
  - list of functions for RGB manipulation

## Troubleshooting

- When in doubt, flash both sides of the keyboard. For some reason that helps with LEDs and reponsiveness.
    - `cd qmk_firmware && make keebio/levinson/rev2:issmirnov:dfu-split-right`
