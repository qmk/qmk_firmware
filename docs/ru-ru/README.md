# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## Что такое QMK Firmware?

QMK (*Quantum Mechanical Keyboard*) — это open source сообщество, которое разрабатывает QMK Firmware, QMK Toolbox, qmk.fm и эту документацию. QMK Firmware — это прошивка для клавиатур, основанная на [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) с множеством полезных функций для Atmel AVR микроконтроллеров, а именно, для продуктов компаний [OLKB](http://olkb.com), [ErgoDox EZ](http://www.ergodox-ez.com) и [Clueboard](http://clueboard.co/). Она также была портирована на чипы ARM при помощи ChibiOS. Вы можете использовать ее для своей собранной вручную клавиатуры или имеющей нестандартную печатную плату.

## Как скачать

Если вы собираетесь добавить раскладку, клавиатуру или новые функции в QMK, самым простым способом реализовать это будет [сделать fork репозитория на GitHub](https://github.com/qmk/qmk_firmware#fork-destination-box), выполнить клонирование вашего репозитория локально для внесения изменений, сделать их push, а затем открыть [Pull Request](https://github.com/qmk/qmk_firmware/pulls) из вашего fork.

Также вы можете либо скачать напрямую ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), либо клонировать через git (`git@github.com:qmk/qmk_firmware.git`) или https (`https://github.com/qmk/qmk_firmware.git`).

## Как скомпилировать

Перед компиляцией вам необходимо [настроить окружение](ru-ru/getting_started_build_tools.md) разработчика для AVR или/и ARM. После этого используйте команду `make` со следующим синтаксисом, чтобы собрать клавиатуру и раскладку:

    make planck/rev4:default

Данная команда соберет ревизию `rev4` клавиатуры `planck` с раскладкой `default`. Не все клавиатуры имеют ревизии (они также называются subprojects или folders), в этом случае она может быть опущена:

    make preonic:default

## Как настроить

QMK обладает множеством [функций](ru-ru/features.md) для исследования, и хорошей отправной точкой для знакомства с ними может стать [справочная документация](http://docs.qmk.fm). Большинством функций можно воспользоваться модифицируя [раскладку](ru-ru/keymap.md) и изменяя [коды клавиш](ru-ru/keycodes.md).
