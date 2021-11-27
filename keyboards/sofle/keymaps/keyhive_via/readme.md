# Only compatible with sofle/keyhive firmware which adds an extra column of keys for encoder mapping.

![SofleKeyboard version 2.1 RGB Keyhive](https://i.imgur.com/Oa6spvZ.png)

# Configuring VIA App

VIA will not auto-recognize the keyboard with this firmware. You must install the new layout:

1. In the VIA app, select `File > Import Keymap` from the menu.
2. Navigate to `qmk_firmware/keyboards/sofle/keymaps/keyhive_via/` and open `via_layout.json`

# Using with VIA
* The default layouts should be loaded automatically.
* Layouts can be backed up in VIA in the SAVE+LOAD section.
* It is a good idea to Save Current Layout after you decide on your mapping.

# Custom Features:

### Rotary Encoder and VIA Features:
* Fully remappable. Left encoder controls volume up/down/mute. Right encoder PGUP/PGDOWN.
* Allows for live remapping of per-layer rotary encoder functions in VIA.
* VIA support with **keyhive_via** keymap.
