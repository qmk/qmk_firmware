# Planck Ortho 4x12 Unicode Futhark Rune layout

![Planck Futhark Layout Image](https://i.imgur.com/ocILTZ3.png)

* Layout Maintainer: [trguhq](https://github.com/trguhq)

Types unicode runes on ortholinear QMK keyboard. Legacy Latin letter
layers left for user but have been marked red as irrelevant.

## OS specific

With both modifiers (either side of spacebar) selected, layer 6
lets you select which OS mode to use with the first vertical column
of keys:

1. macOS
2. Linux
3. Windows Unicode
4. Windows WinCompose

See [QMK docs](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_unicode.md) for details.

### macOS

On macOS this will have to be enabled in keyboard settings as a 
Unicode Hex Input Keyboard Source and selected under the
keyboard layouts icon on the menu bar.

### Linux

Uses IBus or GTK.

### Windows

Either create the needed EnableHexNumpad registry key for Windows Unicode
entry, or (recommended) install WinCompose.
