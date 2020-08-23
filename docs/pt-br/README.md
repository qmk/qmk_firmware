# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## O que é o firmware QMK?
QMK (*Quantum Mechanical Keyboard*) é uma comunidade de código aberto que mantém o QMK Firmware, o QMK Toolbox, qmk.fm e suas documentações. O QMK Firmware é um software embarcado ("firmware") de teclado baseado no [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) com alguns recursos úteis para os controladores Atmel AVR e, mais especificamente, na [linha de produtos OLKB](http://olkb.com), o teclado [ErgoDox EZ](http://www.ergodox-ez.com) e a [linha de produtos Clueboard](http://clueboard.co/). Também foi portado para chips ARM usando o ChibiOS. Você pode usá-lo no seu próprio teclado com fio ou personalizado.

## Como obter e usar o QMK

Se você planeja contribuir com um _keymap_ ("mapa de teclas"), teclado ou recursos para o QMK, o jeito mais fácil é [percorrer o repositório através do GitHub](https://github.com/qmk/qmk_firmware#fork-destination-box) e clonar seu repositório localmente para fazer suas alterações, dê um _push_ nelas e abra uma [_Pull request_](https://github.com/qmk/qmk_firmware/pulls) no seu fork.

Caso contrário, você pode cloná-lo diretamente com `git clone https://github.com/qmk/qmk_firmware`. Não faça o download dos arquivos zip ou tar; é necessário um repositório git para baixar os submódulos para compilar.

## Como compilar

Antes de compilar, você precisará [instalar um ambiente específico](getting_started_build_tools.md) para o desenvolvimento em plataforma AVR e/ou ARM; vez que isto for feito, você usará o comando `make` para criar um teclado e um mapa de teclas com a seguinte notação:

    make planck/rev4:default

Isso compilaria a revisão `rev4` do teclado ` planck` com o mapa de teclas `default`. Nem todos os teclados têm revisões (também chamadas de _subprojects_ ou _folders_); nesse caso, a revisão pode ser omitida:

    make preonic:default

## Como personalizar

O QMK tem muitos [recursos](features.md) para explorar e uma boa quantidade de [documentação de referência](http://docs.qmk.fm) para explorar. A maioria dos recursos é aproveitada modificando seu [keymap](keymap.md) e alterando os [keycodes](keycodes.md).
