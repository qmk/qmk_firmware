# QMK Configurator

[![QMK Configurator Screenshot](https://i.imgur.com/anw9cOL.png)](https://config.qmk.fm/)

The [QMK Configurator](https://config.qmk.fm) is an online graphical user interface that generates QMK Firmware `.hex` or `.bin` files.

It should be noted that Configurator cannot produce firmwares for keyboards using a different controller than they were designed for, i.e. an RP2040 controller on a board designed for pro micro. You will have to use the command line [converters](feature_converters#supported-converters) for this.

Watch the [Video Tutorial](https://www.youtube.com/watch?v=-imgglzDMdY). Many people find that is enough information to start programming their own keyboard.

The QMK Configurator works best with Chrome or Firefox.

::: warning
**Note: Files from other tools such as Keyboard Layout Editor (KLE), or kbfirmware will not be compatible with QMK Configurator. Do not load them, do not import them. QMK Configurator is a DIFFERENT tool.**
:::

Please refer to [QMK Configurator: Step by Step](configurator_step_by_step).
