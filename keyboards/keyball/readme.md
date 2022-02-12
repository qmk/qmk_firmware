# Keyball series

This directory includes source code of Keyball keyboard seriers:

| Name          | Description
|---------------|-------------------------------------------------------------
|[Keyball46](./keyball46)|A split keyboard with 46 vertically staggered keys and 34mm track ball.
|[Keyball61](./keyball61)|A split keyboard with 61 vertically staggered keys and 34mm track ball.
|[Keyball39](./keyball39)|A split keyboard with 39 vertically staggered keys and 34mm track ball.

* Keyboard Designer: [@Yowkees](https://twitter.com/Yowkees)  
* Hardware Supported: ProMicro like footprint
* Hardware Availability: <https://shirogane-lab.com/>

See each directories for each keyboards in a table above.

## How to build

1. Check out this repository.

    ```console
    $ git clone https://github.com/Yowkees/keyball.git keyball
    ```

2. Check out [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware/) repository in another place.

    ```console
    $ git clone https://github.com/qmk/qmk_firmware.git --depth 1 --recurse-submodules --shallow-submodules -b 0.15.13 qmk
    ```

    Currently Keyball firmwares are verified to compile with QMK 0.15.13

3. Create a symbolic link to this `keyball/` directory from [qmk/qmk_firmware]'s `keyboards/` directory.

    ```console
    $ ls
    keyball/ qmk/

    $ cd qmk/keyboards
    $ ln -s ../../keyball/qmk_firmware/keyboards/keyball keyball
    $ ls keyball/
    drivers/  keyball46/  keyball61/  lib/  readme.md
    $ cd ..
    ```

4. `make` your Keyball firmwares.

    ```console
    $ make -j8 SKIP_GIT=yes keyball/keyball61:default
    ```

## How to create your keymap

(to be documented)
