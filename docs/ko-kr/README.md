# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## QMK Firmware 란?

QMK(*Quantum Mechanical Keyboard 양자 기계식 키보드*)란 QMK 컴워어, QMK 툴박스, qmk.fm 를 관리하고 있는 오픈소스 커뮤니티 입니다. QMK펌웨어는 [tmk\_keyboard](http://github.com/tmk/tmk_keyboard)를 바탕으로 만들어진 키보드펌웨어이며, Atmel AVR컨트롤러와 [OLKB 제품군](http://olkb.com) [ErgoDox EZ](http://www.ergodox-ez.com), 그리고 [Clueboard 제품군](http://clueboard.co/) 이용할때 매우 편리합니다. 또한 QMK는 ChibiOS를 사용하여 ARM기반의 컨트롤러로도 사용할수 있습니다. 마지막으로 QMK는 커스텀회로와 핸드와이어드 키보드을 작동시키는데에도 사용가능합니다.


## 설치하기

만약 당신이 QMK에 키보드, 키맵, 또는 새로운 기능을 추가하고싶다면, 가장쉬운 방법은 Github를 통해 [저장소(REPO)를 추가하고]((https://github.com/qmk/qmk_firmware#fork-destination-box)) 로컬에서 변화 또는 수정하고, [PULL REQUEST](https://github.com/qmk/qmk_firmware/pulls)을 통해 업로드 할수 있습니다.

또다른 방법으로는, 직접 파일들 로컬로 다운로드 하거나([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), git (`git@github.com:qmk/qmk_firmware.git`), https (`https://github.com/qmk/qmk_firmware.git`)을 통해 클론을 만들수 있습니다.

## 컴파일

먼저 컴파일을 하기전 AVR 이나 ARM [개발환경](getting_started_build_tools.md)을 구축해야 합니다. 모든준비가 끝났다면 `make`를 다음과 같이 키보드와 키맵을 선택하여 컴파일 할 수 있습니다.

    make planck/rev4:default

이 커맨드는 `rev4`버전의 `planck`를 `default`키맵으로 컴파일 할것입니다. 다만 모든 키보드는 파일, 수정본 또는 세부프로젝트를 가지고있지 않음으로 수정본 부분을 생략될수 있습니다.

    make preonic:default

## 커스터마이징

QMK는 사용할 수 있는 매우 다양한 [기능](features.md)과 체계화된 [참고자료](http://docs.qmk.fm)들이 있습니다. 그중 대부분은 [키맵](keymap.md)을 수정하거나 [키코드](keycodes.md)를 변경하는데에 특화되어 있습니다.
