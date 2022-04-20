# PROG-QGMLWB

The prog-qgmlwb layout is a QMK firmware layout for the Planck keyboard.

For letter placement, the layout uses the optimized QGMLWB layout from the [Carpalx project](http://mkweb.bcgsc.ca/carpalx).

> The carpalx project introduces a quantitative model for typing effort and applies it to (a) evaluate QWERTY and popular alternatives, such as Dvorak and Colemak and (b) find the keyboard layouts that minimize typing effort for a given set of input documents.

Carpalx named "QGMLWB" as the fully optimized layout according to the English alphabet, with an effort reduction of approximately 44.4%.

The programming part of the name is inspired by the modified version of Dvorak, [Programmer Dvorak](http://programmer-dvorak.appspot.com), where the symbols have been adjusted logically for developers.

The final layout swaps some Dvorak symbols and combines them with the QGMLWB letters, giving it the name **prog-qgmlwb**.

The layout includes an English and Norwegian layer, whereas the Norwegian one only adds the three letters; æ, ø, and å.

## Typing layers

![Typing layers](https://i.imgur.com/Ox0a87l.png)

## Adjust layer

![Adjust layer](https://i.imgur.com/RqHRlSI.png)

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

```bash
./scripts/flash.sh --init --no-compile
```

### Compile and flash keyboard

- QMK toolbox

```bash
./scripts/flash.sh
```

- Terminal

```bash
./scripts/flash.sh -f
```

Change the `pcb` and `bootloader` variables in `scripts/config.sh` if it does not match your keyboard.

## QMK documentation

Found in the QMK docs: <https://docs.qmk.fm>

## Printing layout

This keymap uses macros such that [qmk configurator](https://config.qmk.fm) cannot match its behavior. Instead, the images are designed using the [pimpmykeyboard layout editor](http://www.keyboard-layout-editor.com). The folder `print_layouts` contains the image source JSON files that can be imported into the editor using the `Raw Data` field.

## Future additions

Features disabled due to the lack of storage space in the Planck PCB version 5:

- Audio
- Plover mode
