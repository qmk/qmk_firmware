# Aurora Lily58's Default Keymap
_This keymap is a copy of the [Lily58 default keymap](https://github.com/qmk/qmk_firmware/tree/master/keyboards/lily58/keymaps/default), with slight modifications._

A simple default keymap for the Aurora Lily58
=============================================

Keymaps in general are quite personal, so it is difficult to come up with a default that will suit every user. We hope this keymap serves as a good starting point for your own - although it should be fairly usable out-of-the-box.

What do all these layers do?
----------------------------

### Layer 0: Base layer

![Layer 0](https://i.imgur.com/sq8Rql7h.png)

This is where your basic letters live.

The homing thumb fingers are used to access the different layers.

* The homing left thumb finger gives access to the Symbols (or lower) layer
* The homing right thumb finger gives access to the Navigation (or raise) layer
* Pressing both homing thumb fingers gives access to the Adjust layer

### Layer 1: Lower

![Layer 1](https://i.imgur.com/baSE2OJh.png)

The Lower layer gives access to the F keys on the second row, and shifted number keys on the home row. It also provides some shifted symbol keys.

### Layer 2: Raise

![Layer 2](https://i.imgur.com/CRnDa6Nh.png)

The Raise layer gives access the arrow keys on the right hand, in addition to some unshifted symbols. The left hand provides an alternative set of F keys, while the second row provides an alternative set of number keys.

### Layer 3: Adjust

![Layer 3](https://i.imgur.com/QbCiTcyh.png)

The Adjust layer exposes RGB adjustment keys on the right hand.

Where is the keymap.c?
----------------------

The keymap.c file is not published to the repository. It is generated from `keymap.json` by the build system.

This avoids duplicating information and allow users to edit their keymap from the QMK Configurator web interface.

How do I edit and update the keymap?
------------------------------------

The `keymap.json` file is generated from the QMK Configurator interface and formatted for better readability in the context of the Ferris keyboard.

To edit it, you may:
* Edit it directly from a text editor.
* Edit it from the QMK Configurator.

If you decide to use the latter workflow, here are the steps to follow:

* From the [QMK Configurator](https://config.qmk.fm/#/splitkb/aurora/lily58/rev1/LAYOUT), hit the "import QMK keymap json file" button (it has a drawing with an up arrow on it).
* Browse to the location of your keymap (for example, `<your qmk repo>/keyboards/splitkb/aurora/lily58/keymaps/default/keymap.json`)
* Perform any modification to the keymap in the web UI
* Export the keymap to your downloads folder, by hitting the "Export QMK keymap json file" button (it has a drawing with a down arrow on it)
* Replace your original keymap with the one you just downloaded

_**Note:** At the time of writing (the 24th of October 2022), not every feature used in the default keymap is supported by the QMK Configurator. You cannot yet upload the default `keymap.json` due to a file format mismatch - use the "Load Default" button to load the default keymap instead. Additionally, custom configuration options are still being worked on: if your keymap depends on them, please compile your firmware offline for now._

I want to do more than the JSON format supports!
-------------------------------------------------

While the `json` format is easy to use, it does lack certain functionality - most notably custom OLED or encoder behaviour.

To add this, you need to convert it to the `c` format. Do keep in mind that this is generally a one-way operation.

First, from the root of your qmk repo, move to your keymap folder

```bash
cd ./keymaps/splitkb/aurora/lily58/my_personal_keymap
```

Next, convert your `keymap.json` to a `keymap.c`

```bash
qmk json2c -o keymap.c keymap.json
```

You can add custom C code to the newly generated `keymap.c` file. Do note that you have to use **either** a C file **or** a JSON file - you cannot do both!  
**If a JSON file is present, the C file is ignored.**