QMK Firmware
============

This is my personal fork of the QMK firmware that I did in order to fix
keybindings on the Keebio Iris Rev5.

Setup
-----

These are steps to prepare to flash the Keebio Iris firmware.

1.  Set-up the QMK firmware utility.

    ```sh
    cd ./this/repo
    dnf install libusb-devel
    qmk setup
    ```

2.  Configure specific settings for QMK.

    ```sh
    qmk config user.keyboard=keebio/iris/rev5
    qmk config user.keymap=spacez320
    ```

Usage
-----

To actually compile QMK firmware for the Keebio Iris:

```sh
# Override QMK config settings and compile the default layout.
qmk compile -kb keebio/iris/rev5 -km default

# Use the QMK config settings and compile the custom `spacez320` layout.
qmk compile
```

Using keymap `spacez320` the file to edit is
`keyboards/keebio/iris/keymaps/spacez320/keymap.c`.

Theoretically after this you can run `qmk flash`, however I was not able to get
this to work from the command-line and instead has to resort to using the QMK
Toolbox on MacOSX.
