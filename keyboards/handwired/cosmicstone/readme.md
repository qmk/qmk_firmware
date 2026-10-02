<img src="https://github.com/comicrocharly/cosmicstone/raw/main/pics/Readme_Pic.png" alt="Cosmicstone" width="900">

# Cosmicstone

Cosmicstone is my personal tailored split keyboard.
It is powered by the powerful QMK firmware.
Designed in [Cosmos Keyboard Generator](https://github.com/tomasz-lech/cosmos), inspired by [Charybdis](https://github.com/qmk/qmk_firmware/tree/master/keyboards/bastardkb/charybdis).

It features a split ergonomic design, a thumb-cluster trackball, a rotary encoder, an OLED screen and hotswap sockets.

Cosmicstone was born from the necessity of building a custom ergonomic split keeb, comfortable for my hand size, and my taste adapted to the Thinkpad Trackpoint.
Trackball functions are inherited from the Charybdis source and integrated in the keymap.

Every component was sourced on AliExpress, the case is fully 3D printed, hand-wired and built cheaply and conveniently.

### How to compile

1. Download QMK MSYS
2. In QMK MSYS run `qmk setup` and pull the keyboard database
3. Clone this repo in `/qmk_firmware/keyboards/`
4. Run `qmk compile -kb cosmicstone -km default`

> **Note (current QMK CLI):** steps 1–2 describe the legacy *QMK MSYS*
> environment. The modern equivalent is the QMK CLI, installed with
> `pipx install qmk` (or `pip install qmk`) on Linux, macOS and Windows.
> No separate setup step is needed: the keyboard database is downloaded
> automatically at the first compile.

The full `default` keymap from the standalone Cosmicstone repository
(step 3) depends on the community modules `Bastardkb/argos` and
`Bastardkb/bk_pointing_device` (declared in its
`keymaps/default/keymap.json`). They live outside the QMK firmware tree,
so before the first compile they must be available in your external
userspace (the QMK CLI looks in `~/qmk_userspace/` by default):

```sh
mkdir -p ~/qmk_userspace/modules
git clone https://github.com/Bastardkb/qmk_modules.git ~/qmk_userspace/modules/Bastardkb
```

Then run `qmk compile -kb cosmicstone -km default` from the firmware
root (e.g. `~/qmk_firmware`); the build system picks the modules up from
`~/qmk_userspace/modules/Bastardkb/` automatically.
