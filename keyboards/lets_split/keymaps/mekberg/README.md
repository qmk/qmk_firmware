# Let's Mekberg!

This is my take on a Swedish 40% layout in a split format. The priority is to have the most highly used keys opposite the modifier to make chording simpler. In other words, if the layer modifier is on the left half, the most used keys should be bound on the right half.

## Layers

### Default

The default layer has normal alpha layout with the addition of Swedish letters, causing Enter to move down one key and backspace to take the place of the right space. The enter key also doubles as Shift when held.

2nd row left modifier has been bound to both Ctrl and Tab with modtap (hold for Ctrl, tap for Tab).

Delete is available on all non-default layers, positioned on the upper right corner key.

### Raise

The raised layer has all the symbols and special characters predefined. As much as possible, there should be no need to use additional modifiers.

Arrow keys have been disabled on this layer to avoid accidental misclicks when pressing the Raise key.

#### macOS / Windows variants

Because macOS and Windows expect quite different keycodes to produce the same special characters (for example '{' or  '|'), there are two different layers, one for each OS. To toggle either macOS (default) and Windows layouts within the RAISE layer, press SPECIAL + W for Windows or SPECIAL + M for macOS.

### Lower

The lower layer focuses on numbers, with a numpad-like layout on the right and F-keys in a homerow-centric layout on the left.

### Special

The special layer has Reset and EEP Reset keys on the left half, along with media and volume controls. On the right half it has movement keys starting in the IJKL cluster. Additionally, custom macOS Sleep and Lock Screen keys can be found on the right half on this layer.

## Configuration

### PERMISSIVE_HOLD

This option is used because otherwise modtap functions would fail to trigger. This increases reliability for me.

### EE_HANDS

Prepared for EEPROM settings and different keymaps depending on USB port connected, but default master side remains left regardless.

## Building

Clean the build environment:

```shell
make clean
```

Build and flash left side:

```shell
make lets_split/rev2:mekberg:avrdude-split-left
```

Then do the same for the right side:

```shell
make lets_split/rev2:mekberg:avrdude-split-right
```
