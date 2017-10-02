Kona Classic keyboard firmware
======================

##Kona Classic

The Kona Classic is a 60% layout + left Function keys. Using a Teensy as the controller, the Kona Classic is provided as a do-it-yourself kit for left f-key enthusiasts.

Layouts that are preconfigured are shown here:
![Kona Clasic PCB Supported Layouts](KonaClassicFirmwareLayouts.png)

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/doc/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/KonaClassic folder.
Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use
the Teensy Loader to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make`.

### Other Keymaps

To build the firmware binary hex file with a keymap just do `make` with `keymap` option like:

```
$ make keymap=[default|jack|<name>]
```

Keymaps follow the format **__keymap.c__** and are stored in folders in the `keymaps` folder, eg `keymaps/my_keymap/`
