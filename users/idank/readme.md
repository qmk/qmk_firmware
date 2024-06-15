This directory enables trackball / trackpoint functionality based on command
line flags, regardless of the keyboard/keymap used.

## Examples

```
# build corne with via, enable trackball with rgb rainbow effect, and set the
# trackball rotation for the thumb position.
make crkbd/rev1:via -j8 -e USER_NAME=idank -e POINTING_DEVICE=trackball -e TRACKBALL_RGB_RAINBOW=yes -e POINTING_DEVICE_POSITION=thumb

# build lily58 with via, enable trackball, no rainbow, convert firmware to
# rp2040 board.
make lily58/rev1:via:flash -e USER_NAME=idank -e POINTING_DEVICE=trackball -e TRACKBALL_RGB_RAINBOW=no -e POINTING_DEVICE_POSITION=right -e CONVERT_TO=rp2040_ce -j8

# build corne with via, enable trackpoint
make crkbd/rev1:via -j8 -e USER_NAME=idank -e POINTING_DEVICE=trackpoint
```
