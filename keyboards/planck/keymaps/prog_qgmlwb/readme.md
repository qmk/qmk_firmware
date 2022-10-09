# PROG-QGMLWB

The prog-qgmlwb layout is a QMK firmware layout for the Planck keyboard.

For letter placement, the layout uses the optimized QGMLWB layout from the [Carpalx project](http://mkweb.bcgsc.ca/carpalx).

> The carpalx project introduces a quantitative model for typing effort and applies it to (a) evaluate QWERTY and popular alternatives, such as Dvorak and Colemak and (b) find the keyboard layouts that minimize typing effort for a given set of input documents.

Carpalx named "QGMLWB" as the fully optimized layout according to the English alphabet, with an effort reduction of approximately 44.4%.

The programming part of the name is inspired by the modified version of Dvorak, [Programmer Dvorak](http://programmer-dvorak.appspot.com), where the symbols have been adjusted logically for developers.

The final layout swaps some Dvorak symbols and combines them with the QGMLWB letters, giving it the name **prog-qgmlwb**.

The layout includes an English and Norwegian layer, whereas the Norwegian one only adds the three letters; æ, ø, and å.

## Typing layers

![Typing layers](https://i.imgur.com/QaHnqW8.png)

## Adjust layer

![Adjust layer](https://i.imgur.com/63I69P0.png)

## Usage

### Clone the QMK Firmware repo

```bash
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git <path/name>
```

### Move into this keymap

```bash
cd <path/name>/keyboards/planck/keymaps/prog_qgmlwb
```

### Initialize QMK the first time

Set default keyboard:

```bash
qmk config user.keyboard=planck/<rev>
```

Set default keymap:

```bash
qmk config user.keymap=prog_qgmlwb
```

Initialize libraries:

```bash
qmk setup
```

### Compile and flash the keyboard

```bash
qmk compile
qmk flash
```

## QMK documentation

Found in the QMK docs: <https://docs.qmk.fm>

## Printing layout

This keymap uses macros such that [qmk configurator](https://config.qmk.fm) cannot match its behavior. The images was designed using [Figma](https://figma.com).

## Future additions

Features disabled due to the lack of storage space in the Planck PCB version 5:

- Audio
- Plover mode
- Use alt codes to fix missing characters in the english layout
- Improve documentation of code and readme files
- Reimplement right version of modifier keys through raise+space
