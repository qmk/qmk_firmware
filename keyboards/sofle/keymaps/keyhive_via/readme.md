# Only compatible with sofle/keyhive firmware which adds an extra column of keys for encoder mapping.

![SofleKeyboard version 2.1 RGB Keyhive](https://i.imgur.com/Oa6spvZ.png)

# Configuring VIA / Vial App

This firmware will not auto-recognize until [PR #1060](https://github.com/the-via/keyboards/pull/1060) is accepted to the VIA keyboard database. For now you must install the new layout:

1. Download [keyhive_sofle_rgb.json](https://raw.githubusercontent.com/the-via/keyboards/48372baae5ab451d752988121fa4f1dd47b2c1ce/src/sofle/keyhive_sofle_rgb.json).
2. In the VIA app, select `File > Import Keymap` from the menu.
3. Open the file you just downloaded.

**You'll have to do this every time you use VIA or Vial until the PR is accepted.**

# Using with VIA
* The default layouts should be loaded automatically.
* Layouts can be backed up in VIA in the SAVE+LOAD section.
* It is a good idea to Save Current Layout after you decide on your mapping.

# Custom Features:

### Rotary Encoder and VIA Features:
* Fully remappable. Left encoder controls volume up/down/mute. Right encoder PGUP/PGDOWN.
* Allows for live remapping of per-layer rotary encoder functions in VIA.
* VIA support with **keyhive_via** keymap.
