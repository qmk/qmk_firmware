# PROG_QGMLWB

A qmk firmware layout for the planck keyboard

## Usage

### Clone QMK Firmware repo fork

```bash
git clone --recurse-submodules https://github.com/davidkristoffersen/qmk_firmware.git <path/name>
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

## QMK configurator

This keymap uses macros such that qmk configurator cannot exactly match its behavior.  
The file `build/layers.json` is used for printing the keymap.

## Print layout

The folder `print_layouts` contain all layouts designed using pimpmykeyboard's layout editor.  
Each file can be imported into the editor using the `Raw Data` field
