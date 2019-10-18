# Quantum Mechanical Keyboard Firmware

[![เวอร์ชันปัจจุบัน](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## QMK Firmware คืออะไร?

QMK (*Quantum Mechanical Keyboard*) คือคอมมูนิตี้โอเพ่นซอร์สที่ดูแลโปรเจกต์ QMK Firmware, QMK Toolbox, qmk.fm, และเอกสารนี้ ซึ่ง QMK Firmware คือเฟิร์มแวร์ที่ต่อยอดมาจาก [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) ที่เพิ่มฟีเจอร์สำหรับ Atmel AVR เช่นคีย์บอร์ดจาก [OLKB](http://olkb.com), [ErgoDox EZ](http://www.ergodox-ez.com), และ [Clueboard](http://clueboard.co/) นอกจากนี้ยังสามารถใช้กับชิป ARM ด้วย ChibiOS หรือจะเป็นคีย์บอร์ดแบบ Handwired (ทำมือ) ก็สามารถใช้ได้เช่นกัน

## วิธีใช้

ถ้าต้องการเพิ่มคีย์แมป (Keymap), คียบอร์ดใหม่ หรือฟีเจอร์ใหม่ให้กับ QMK ให้ทำการ [Fork โปรเจกต์ผ่าน Github](https://github.com/qmk/qmk_firmware#fork-destination-box) แล้ว Clone ไปแก้ไข จากนั้น Push และเปิด [Pull Request](https://github.com/qmk/qmk_firmware/pulls) จาก Fork ของคุณ

หรือถ้าต้องการใช้งาน ให้ดาวน์โหลดโดยตรง ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)) หรือ Clone ด้วย Git (`git@github.com:qmk/qmk_firmware.git`) / https (`https://github.com/qmk/qmk_firmware.git`)

## วิธีคอมไพล์

ก่อนที่จะคอมไพล์ได้ต้อง [ติดตั้ง Build Tool](getting_started_build_tools.md) สำหรับ AVR และ/หรือ ARM เมื่อติดตั้งครบแล้วจะสามารถใช้คำสั่ง `make` เพื่อ Build คีย์บอร์ดและคีย์แมป เช่น

    make planck/rev4:default

จะเป็นการ Build คีย์บอร์ด `planck` รุ่น `rev4` และใช้คีย์แมป `default` ถ้าคีย์บอร์ดที่ใช้ไม่มีชื่อรุ่นหรือโปรเจกต์ย่อย ให้เว้นรุ่นได้ เช่น

    make preonic:default

จะเป็นการ Build คีย์บอร์ด `preonic` และใช้คีย์แมป `default`

## วิธีการปรับแต่ง

QMK มี[ฟีเจอร์](features.md)ให้ใช้มากมาย สามารถดูเอกสารและข้อมูลทั้งหมดได้ที่ http://docs.qmk.fm ซื่งส่วนมากจะเป็นการปรับแต่งหรือเพิ่ม[คีย์แมป](keymap.md) และแก้ไข[คีย์โค้ด (Keycodes)](keycodes.md)
