# Quantum Mechanical Keyboard Firmware

[docs](https://docs.qmk.fm)
[repo](https://github.com/qmk/qmk_firmware)
[tool](https://config.qmk.fm/#/crkbd/rev1/LAYOUT_split_3x6_3)

## Layout

Layer 0

![scrn-2023-10-11-09-20-14](https://github.com/freddiehaddad/qmk_firmware/assets/6127369/1bb0e022-b4c7-4910-b64f-04d32c20bd73)

Layer 1

![scrn-2023-10-11-09-20-35](https://github.com/freddiehaddad/qmk_firmware/assets/6127369/62beb3ac-dce6-4e4e-b1f9-430ce2b7f2d0)

Layer 2

![scrn-2023-10-11-13-07-25](https://github.com/freddiehaddad/qmk_firmware/assets/6127369/301472ce-9186-42c6-b6d8-c718b3fd702b)

Layer 3

![scrn-2023-10-11-09-20-57](https://github.com/freddiehaddad/qmk_firmware/assets/6127369/578d6363-e3c2-4865-8b49-bf1e8adbf655)

## Installation

```text
echo "PATH=$PATH:$HOME/.local/bin" >> $HOME/.zshrc
python3 -m pip install --user qmk
```

## Configuration

```text
qmk setup -H $HOME/projects/git/qmk_firmware freddiehaddad/qmk_firmware
qmk new-keymap --keyboard crkbd --keymap freddiehaddad
qmk config user.keyboard=crkbd
qmk config user.keymap=freddiehaddad
```

## Flashing

```text
qmk compile --clean
qmk flash --bootloader dfu
```

## Miscellaneous

```text
# generate keymap.json
qmk c2json --keyboard crkbd --keymap freddiehaddad --output keymap.json keymap.c
```
