# Quantum Mechanical Keyboard Firmware

[![Version Actual](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Estado del Build](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Estado de la Documentación](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![Contribuyentes en GitHub](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![Forks de GitHub](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## ¿Qué es el Firmware QMK?

QMK (*Quantum Mechanical Keyboard*) es una comunidad de código libre que mantiene el Firmware QMK, el Toolbox QMK, qmk.fm, y esta documentación. El Firmware QMK es un firmware para teclados basado en [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) con algunas funcionalidades útiles de los controladores Atmel AVR, y más específicamente, la [línea de productos OLKB](http://olkb.com), el teclado [ErgoDox EZ](http://www.ergodox-ez.com), y la [línea de productos Clueboard](http://clueboard.co/). También ha sido traducido a chips ARM con ChibiOS. Puedes usarlo para controlar tus propios teclados cableados a mano o con PCBs personalizados.

## ¿Cómo obtenerlo?

Si planeas contribuir con una distribución de teclado (keymap), o con funcionalidades a QMK, la forma más fácil de hacerlo es [haciendo un fork del repo a través de Github](https://github.com/qmk/qmk_firmware#fork-destination-box), clonar el repo localmente para hacer tus cambios, hacerles push, y luego abrir un [Pull Request](https://github.com/qmk/qmk_firmware/pulls) desde tu fork.

Si no, puedes descargarlo directamente ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), clonarlo por git (`git@github.com:qmk/qmk_firmware.git`), o por https (`https://github.com/qmk/qmk_firmware.git`).

## ¿Cómo compilar?

Antes de poder compilar, necesitarás [instalar un ambiente](getting_started_build_tools.md) para desarrollo AVR y/o ARM. Una vez esto esté completado, usarás el comando `make` para construir un teclado y una distribución de teclado (keymap) con la siguiente notación:

    make planck/rev4:default

Esto construirá la revisión `rev4` de `planck` con la distribución de teclado (keymap) `default`. No todos los teclados tienen revisiones (también llamados subproyectos o carpetas), en esos casos, puede ser omitido.

    make preonic:default

## ¿Cómo personalizar?

QMK tiene muchas [funcionalidades](features.md) para explorar, y una buena cantidad de [documentación de referencia](http://docs.qmk.fm) para consumimr. La mayoría de las funcionalidades son aprovechadas al modificar tu distribución de teclado [keymap](keymap.md), y cambiando los [códigos de los caracteres](keycodes.md).
