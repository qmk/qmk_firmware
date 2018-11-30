# 量子力學鍵盤固件

[![當前版本](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![築邦](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![不和諧](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![文檔狀態](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub的貢獻者](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub的叉](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## 什麼是QMK固件？

QMK(*量子力學鍵盤*)是一個開源社區維護QMK固件，QMK工具箱，qmk.fm這些文檔。 QMK固件是根據[tmk\_keyboard](http://github.com/tmk/tmk_keyboard) 具有用於愛特梅爾AVR控制器一些有用的功能鍵盤固件，並且更具體地，[OLKB產品線](https://olkb.com)時，[ergodox EZ](http://www.ergodox-ez.com)鍵盤，並且[Clueboard產品線](http://clueboard.co/)。它也被移植到使用ChibiOS ARM芯片。你可以用它來驅動你自己的手，有線或自定義鍵盤PCB。

## 如何得到它

如果你打算貢獻鍵盤佈局，鍵盤或功能QMK，最容易做的事情是[叉通過Github上爬行](https://github.com/qmk/qmk_firmware#fork-destination-box)，和克隆你爬在本地進行更改，推動他們，然後打開從你的叉子[拉請求](https://github.com/qmk/qmk_firmware/pulls)。

否則，您可以直接下載([拉鍊](https://github.com/qmk/qmk_firmware/zipball/master) [焦油](https://github.com/qmk/qmk_firmware/tarball/master))，或者通過GIT中克隆它(`git@github.com:qmk/qmk_firmware.git`)或HTTP(`https://github.com/qmk/qmk_firmware.git`)。

## 如何編譯

你可以編譯之前，你需要[安裝環境](getting_started_build_tools.md)用於AVR或/和ARM開發。一旦完成，你會使用`make`命令建立一個鍵盤並用以下符號鍵盤佈局

    make planck/rev4:default

這將建立`rev4` `planck`的修訂與`default`鍵盤映射。並非所有鍵盤有一個修訂版(也稱為子項目或文件夾)，在這種情況下，它可以被省略：

    make preonic:default

## 如何自定義

QMK有很多[特點](features.md)探索和很好的協議[參考文獻](http://docs.qmk.fm)挖通的。大部分功能通過修改[鍵盤映射(keymap.md)，並改變[鍵碼](keycodes.md)冤大頭。
