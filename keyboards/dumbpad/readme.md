# dumbpad

![dumbpad](https://i.imgur.com/sS3fq1Z.jpg)

A 4x4 macro/numpad with rotary encoder.

Keyboard Maintainer: [imchipwood](https://github.com/imchipwood)

PCB repository: https://github.com/imchipwood/dumbpad

Available Layouts:

- LAYOUT - single encoder on the left side
- LAYOUT_right - single encoder on the right side (PCB flipped over)
- LAYOUT_dualencoder - two encoders (top or bottom, both supported)

Make example for this keyboard for <layout>, <keymap> (after setting up your build environment):

`make dumbpad/<layout>:<keymap>`
				
Make example for this keyboard for v0x PCB, default keymap:

`make dumbpad:default`

Make example for v1x PCB with encoder on right, default keymap:

`make dumbpad/v1x_right:default_right`

Program with:

`make dumbpad/<layout>:<keymap>:avrdude`

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
