@pierrec83's keymap for the gherkin
===

A usable keymap for the gherkin's 30 keys layout, somewhat in sync with my Kyria keymap.

This keymap is more or less an adaptation of my Kyria keymap which sacrifices some convenience but retains most functionality.

Features
---
* Mouse keys with constants tuned so the keyboard usable for me as my sole pointing device
* Homerow layers activation
* Minimal side-index motion thanks to workman base layer and similar principles in other layers
* Two symbol layers, both activated with one homerow key and either another key on the same hand's homerow or a key from the other hand
* Mousing around, including left and right clicking can be done either one-handed or fully on the homerow with both hands
* Easy chaining of common command line or vim patterns, such as `~/`, `()`, `ESC : w ENTER` etc.
* Common OS shortcuts like switching workspaces on gnome or MacOS easily accessible (for the shortcuts I use. This may not apply to others)

Instructions to update the keymap
---

For now, I am still more comfortable updating the keymap through the qmk configurator as I don't trust myself to manually keep comments describing the keymap in sync with the code itself. This means that my keymap.c is generated and not really readable. For a readble view of my keymap, one must import keymap.json into [qmk configurator](https://config.qmk.fm) and use the web UI or print it.

To update the keymap,
* Load keymap.json into qmk configurator
* Perform any edits
* Export the keymap. This should save a json file in `~/Downloads/pierrec83.json` or equivalent for your OS
* From the root of qmk_firmware, move the keymap to its destination:
```
mv ~/Downloads/pierrec83.json keyboards/40percentclub/gherkin/keymaps/pierrec83/keymap.json
```
* Flash the firmware (for instance, if left hand is plugged):
```
qmk flash -kb 40percentclub/gherkin -km pierrec83
```

Author
---
I am @pierrec83 on Twitter, @pierrechevalier83 on github. I chose the shorter nickname for my keymap.
