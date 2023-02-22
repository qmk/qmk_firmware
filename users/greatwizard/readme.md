# GreatWizard Userspace

## Features

- ⌨️ Switchable and persistent base layers: Qwerty, Workman, Workman, Colemak, Dvorak, 🎮 Game
- ⌨️ Programmer flavored base layers available
- 💃🕺 Tap Dances
- 🆙 Auto Shift
- 👨‍💻 One shot keys git commands layer
- 🌈 RGB Underglow lights based on the layer
- ⚙️ Rotary encoder for volume level and next/previous media
- 🗜️ Enable link time optimization

## Community Layouts

- [ortholinear 4x12](https://github.com/qmk/qmk_firmware/tree/master/layouts/community/ortho_4x12/greatwizard)
- [ortholinear 5x12](https://github.com/qmk/qmk_firmware/tree/master/layouts/community/ortho_5x12/greatwizard)

## Build Options

### Layers

- `LAYERS_ORTHO`: add Lower, Raise and Adjust layers/keycodes
- `LAYERS_PROGRAMMER`: add Programmer layers/keycodes
- `LAYER_GAME`: add Game layer/keycode
- `LAYER_GIT`: add GIT layer/keycode
- `LAYER_FN`: add Fn layer/keycode

### Tap Dances

- `TAP_DANCE_LALT_GIT`: Double tap on LGUI to use the one shot keys git commands layer
- `TAP_DANCE_LSFT_CAPS`: Double tap on LSHIFT to set Caps Lock
