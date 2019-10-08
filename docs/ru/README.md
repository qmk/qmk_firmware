# Quantum Mechanical Keyboard Firmware

[![Текущая версия](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Статус сборки](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Статус документов](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub участники](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## Что такое QMK Firmware?

QMK (*Quantum Mechanical Keyboard*) это сообщество с открытым исходным кодом, которое поддерживает QMK Firmware, QMK Toolbox, qmk.fm, и эти документы. QMK Firmware прошивка клавиатуры на основе [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) с некоторыми полезными функциями для Atmel AVR контроллеров, и, более конкретно, [OLKB product line](http://olkb.com), [ErgoDox EZ](http://www.ergodox-ez.com) клавиатура, и [Clueboard product line](http://clueboard.co/). Он также был портирован на ARM чипсеты с использованием ChibiOS. Вы можете использовать его для усиления собственноручно созданной или пользовательской клавиатуры PCB.

## Как получить

Если вы планируете внести раскладку, клавиатуру, или особенности QMK, проще всего сделать [форк нашего репозитория на Github](https://github.com/qmk/qmk_firmware#fork-destination-box), клонировать его локально - для внесения изменений, добавить их, и затем открыть [Pull Request](https://github.com/qmk/qmk_firmware/pulls) из своего форка.

Иначе, Вы можете скачать его напрямую ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), или клонировать его через Git (`git@github.com:qmk/qmk_firmware.git`), или https (`https://github.com/qmk/qmk_firmware.git`).

## Как скомпилировать

Прежде чем вы сможете скомпилировать, вам нужно будет [установить и настроить окружение](getting_started_build_tools.md) для AVR и/или ARM разработки. Как только все будет готово, вам надо использовать команду `make`  для создания билда клавиуатуры и раскладки, со следующими нотациями:

    make planck/rev4:default

Это создаст билд `rev4` ревизии из `planck` с `default` раскладкой. Не все клавиатуры имеют ревизии (также называется подпроектами или папками), в таком случае, это можно опустить:

    make preonic:default

## Как настроить

QMKимеет много [функции](features.md) для исследования, и много [справочной документации](http://docs.qmk.fm) для изучения. Большинство функций используются путем изменения вашей [раскладки](keymap.md), и изменением
 [кодов клавиш](keycodes.md).
