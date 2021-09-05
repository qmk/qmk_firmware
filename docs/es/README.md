# Firmware Quantum Mechanical Keyboard

[![Versión actual](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Estado de la documentación](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![Contribuyentes en GitHub](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![Forks en GitHub](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## ¿Qué es el firmware QMK?

QMK (*Quantum Mechanical Keyboard*) es una comunidad open source que mantiene el firmware QMK, QMK Toolbox, qmk.fm, y estos documentos. El firmware QMK es un firmware para teclados basado en [tmk\_keyboard](https://github.com/tmk/tmk_keyboard) con algunas características útiles para controladores Atmel AVR, y más específicamente, la [línea de productos OLKB](https://olkb.com), el teclado [ErgoDox EZ](https://www.ergodox-ez.com), y la [línea de productos Clueboard](https://clueboard.co/). También ha sido portado a chips ARM chips usando ChibiOS. Lo puedes utilizar para manejar tu propio teclado ya sea cableado a mano o basado en una PCB personalizada.

## Cómo conseguirlo

Si estás pensando en contribuir con un keymap, teclado, or característica a QMK, la manera más sencilla es hacer un [fork del repositorio en GitHub](https://github.com/qmk/qmk_firmware#fork-destination-box), y clonar tu repositorio localmente para hacer los cambios, subirlos, y abir un [Pull Request](https://github.com/qmk/qmk_firmware/pulls) desde tu fork.

De cualquier manera, también puedes descargarlo directamente en formatos ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), o clonarlo via git (`git@github.com:qmk/qmk_firmware.git`), o https (`https://github.com/qmk/qmk_firmware.git`).

## Cómo compilar

Antes de poder compilar, necesitarás [instalar un entorno](es/getting_started_build_tools.md) para el desarrollo de AVR y/o ARM. Una vez hayas completado este paso, usarás el comando `make` para compilar un teclado y keymap con la siguiente notación:

    make planck/rev4:default

Este ejemplo compilaría la revisión `rev4` del teclado `planck` con el keymap `default`. No todos los teclados tienen revisiones (también llamados subproyectos o carpetas), en ese caso, se puede omitir:

    make preonic:default

## Cómo personalizar

QMK tiene montones de [características](es/features.md) para explorar, y una buena cantidad de [documentación de referencia](https://docs.qmk.fm) en la que sumergirse. Se pueden sacar provecho de la mayoría de las características modificando tu [keymap](es/keymap.md), y cambiando los [keycodes](es/keycodes.md).
