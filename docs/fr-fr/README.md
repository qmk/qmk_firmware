# Quantum Mechanical Keyboard Firmware

[![Version courante](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Statut du build](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Statut de la doc](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![Contributeurs GitHub](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![Forks GitHub](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## Qu'est-ce que QMK Firmware ?

QMK (*Quantum Mechanical Keyboard*) est une communauté open source qui maintient le firmware QMK, la QMK Toolbox (*Boite à outil*), qmk.fm et leurs documentations. QMK Firmware est un firmware dédié aux claviers qui est basé sur [tmk\_keyboard](https://github.com/tmk/tmk_keyboard). Il offre des fonctionnalités très utiles pour les contrôleurs Atmel AVR, et, plus spécifiquement pour [les produits d'OLKB](https://olkb.com), le clavier [ErgoDox EZ](https://www.ergodox-ez.com), et pour les [produits Clueboard](https://clueboard.co/). Il prend désormais aussi en charge les processeurs ARM qui utilisent ChibiOS. Vous pouvez l'utiliser pour contrôler un clavier personnalisé soudé à la main ou alors sur un clavier avec un PCB personnalisé.

## Comment l'obtenir

Si vous souhaitez contribuer à une disposition de clavier (keymap), ou à des fonctionnalités de QMK alors le plus simple est de [forker le dépôt avec GitHub](https://github.com/qmk/qmk_firmware#fork-destination-box) puis cloner le dépôt localement pour y faire des changements. Vous pourrez pousser vos changements sur GitHub puis ouvrir un [Pull Request](https://github.com/qmk/qmk_firmware/pulls) depuis votre fork GitHub.

Sinon, vous pouvez aussi le télécharger directement en ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), ou le cloner avec git en ssh (`git@github.com:qmk/qmk_firmware.git`), ou https (`https://github.com/qmk/qmk_firmware.git`).

## Comment le compiler

Avant d'être prêt à compiler vous allez devoir [installer un environnement](fr-fr/getting_started_build_tools.md) pour les développements AVR et/ou ARM. Une fois ceci fait, vous pourrez utiliser la commande `make` pour compiler le clavier et la disposition avec une commande de ce type :

    make planck/rev4:default

Cette commande compilera la révision `rev4` du clavier `planck` avec la disposition `default`. Notez que tous les claviers n'ont pas forcément de révisions (aussi appelées sous-projects ou dossiers, ou en anglais « subprojects » ou « folder »). Cette option peut donc être omise :

    make preonic:default

## Comment le personnaliser

QMK a beaucoup de [fonctionnalités](fr-fr/features.md) à explorer, et [une documentation](https://docs.qmk.fm) très abondante que vous pourrez parcourir. La plupart des fonctionnalités vous permettrons de modifier vos [dispositions](fr-fr/keymap.md) (keymaps) et de changer [les codes de caractères](fr-fr/keycodes.md) (keycodes).
