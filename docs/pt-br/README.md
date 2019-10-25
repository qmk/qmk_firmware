# Quantum Mechanical Keyboard Firmware

[![Versão atual](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Status de construção](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Status de documento](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![Contribuidores e contribuidoras Github](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![Forks Github](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## O que é QMK Firmware ?

QMK (_Quantum Mechanical Keyboard_) é uma comunidade de fonte aberta que mantém o firmware QMK, QMK Toolbox (_"Caixa de ferramentas"_), qmk.fm, e as documentações. QMK Firmware é um firmware de teclados baseado em [tmk_keyboard](http://github.com/tmk/tmk_keyboard) com funcionalidades úteis para controladores Atmel AVR, especificamente para [produtos de OLKB](http://olkb.com), o teclado [ErgoDox EZ](http://www.ergodox-ez.com), e para [produtos de Clueboard](http://clueboard.co/). QMK também foi portado para processadores ARM que usam ChibiOS. Você pode usá para controlar seus teclados soldados manualmente ou personalizar o PCB do seu teclado.

## Como conseguir

Se você está pensando em contribuir um mapa de teclado, teclado, ou funcionalidades à QMK, a coise mais fácil para fazer e [fork o repo no Github](https://github.com/qmk/qmk_firmware#fork-destination-box), e clone o repo localmente para fazer mudanças. Você pode empurrar mudanças e depois abrir um [Pull Request](https://github.com/qmk/qmk_firmware/pulls) do seu fork.

Caso contrário, você pode baixar diretamente ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)) ou clone com git com ssh (`git@github.com:qmk/qmk_firmware.git`), ou https (`https://github.com/qmk/qmk_firmware.git`)

## Como compilar

Antes de poder compilar, você precisa [instalar um ambiente](getting_started_build_tools.md) para desenvolvimento de AVR e/ou ARM. Depois, você pode usar o comando `make` para compilar o teclado e mapa de teclado com o seguinte formato:

    make planck/rev4:default

Esse comando compila a revisão `rev4` do teclado `planck` com o mapa `default`. Nem todos os teclados tem revisãos (também chamado subprojeto ou pasta, ou em inglês, "subprojects" ou "folders"). Neste caso, pode ser omitido:

    make preonic:default

## Como personalizar

QMK tem muitas funcionalidades para explorar e bastante de [documentação](http://docs.qmk.fm). Para aproveitar a maioria das funcionalidades, modificar seu [mapa de teclado](keymap.md) ou seus [keycodes](keycodes.md).
