KMAC keyboard firmware
======================

A Korean custom keyboard designed by Byungho Kim and the KBDMania community.

## Supported models

All the tenkeyless models should be supported.

## Bootloader

The PCB is hardwired to run the bootloader if the key at the `Caps Lock` position is held down when connecting the keyboard.

It is also possible to use Boot Magic and Command to access the bootloader.

## Quantum MK Firmware

For the full Quantum feature list, see the [documentation](https://docs.qmk.fm).

## Building

The KMAC are available with two different PCB layouts, a winkey version and a winkeyless version. A default keymap are provided for each versions of the PCB.

Depending on which PCB and keymap you would like to use, you will have to compile the firmware slightly differently. All of the commands should be run in the [keyboards/kmac](/keyboards/kmac) folder.

### Winkey keymap

The [default keymap](keymaps/default) are designed for the winkey version of the PCB.

### Winkeyless Keymap

A [keymap](keymaps/winkeyless) for the winkeyless version of the PCB are also provided.

### Custom keymaps

To define your own keymap, copy one of the [existing keymap](keymaps) folders and give it the name of your keymap. Then check the [keymap documentation](https://docs.qmk.fm/Keymap.html) for details on how to modify the keymap.

To make it easy to define keymaps for the different versions of the PCB two macros are provided.

| PCB            | Macro                 |
| -------------- | --------------------- |
| Winkey PCB     | `KEYMAP()`            |
| Winkeyless PCB | `KEYMAP_WINKEYLESS()` |

To build the firmware with a custom keymap, run `make <keymap name>`
