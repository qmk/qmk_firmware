# Quantum Mechanical Keyboard Firmware

[![Aktuelle Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## Was ist QMK Firmware?

QMK (* Quantum Mechanical Keyboard *) ist eine Open-Source-Community, welche die QMK-Firmware, die QMK-Toolbox, [qmk.fm](https://qmk.fm) und diese Dokumententation betreut. QMK-Firmware ist eine Weiterentwicklung der [tmk\_keyboard](http://github.com/tmk/tmk_keyboard)-Tastatur-Firmware mit vielen nützlichen Zusatzfunktionen für Atmel AVR-Prozessoren. Ursprünglich wurde sie für Produkte von [OLKB](http://olkb.com), das [ErgoDox EZ](http://www.ergodox-ez.com) und das [Clueboard](http://clueboard.co/) entwickelt. Im Laufe der Zeit wurde sie mit Hilfe von [ChibiOS](http://chibios.org) auch für die ARM-Architektur angepasst. Dadurch ist es inzwischen möglich auch handverdrahtete Tastaturen und selbst geätzte PCBs mit QMK zu verwenden.

## Bezugsquelle für QMK

Wenn Du vorhast deine Tastatur, Tastaturbelegung  oder Features zu QMK beizusteuern geht das am einfachsten indem Du das [Repository auf Github](https://github.com/qmk/qmk_firmware#fork-destination-box) forkst, die Änderungen in deinem lokalen Repo vornimmst und anschließend einen [Pull Request](https://github.com/qmk/qmk_firmware/pulls) einreichst.

Ansonsten kannst du es als [zip](https://github.com/qmk/qmk_firmware/zipball/master) oder [tar](https://github.com/qmk/qmk_firmware/tarball/master) herunterladen, oder es direkt via git klonen (`git clone git@github.com:qmk/qmk_firmware.git` bzw. `git clone https://github.com/qmk/qmk_firmware.git`).


## Anleitung fürs Kompilieren

Bevor Du in der Lage bist die Firmware zu kompilieren musst du eine [Entwicklungsumgebung](getting_started_build_tools.md) für AVR und/oder ARM aufsetzen. Danach kannst Du mit dem `make` Befehl eine Keymap für deine Tastatur erzeugen. Die Notation dafür ist:

    make planck/rev4:default

Dies generiert die Revision `rev4` für eine Tastatur vom Type `planck` mit der `default` Tastaturbelegung. Nicht alle Tastaturen haben Revisionen (auch bekannt als Subprojekt oder Unterordner) weswegen dies auch ausgelassen werden kann:

    make preonic:default

## Möglichkeiten der Anpassung

QMK hat viele [Features](features.md) die es zu entdecken gibt. In der [Dokumentation](https://docs.qmk.fmk) kannst Du dir einen Überblick verschaffen. Die meisten Features basieren darauf die [Tastaturbelegung](keymap.md) anzupassen und das Verhalten der [Keycodes](keycodes.md) zu verändern.
