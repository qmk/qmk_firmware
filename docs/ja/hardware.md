# ハードウェア

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: c9e3fa6f7:docs/hardware.md
  git diff c9e3fa6f7 HEAD -- docs/hardware.md | cat
-->

QMKは様々なハードウェア上で実行できます。あなたの使っているマイコンが、[LUFA](http://www.fourwalledcubicle.com/LUFA.php)や[ChibiOS](http://www.chibios.com)に対応していれば、そのハードウェア上でQMKを動かすことができるはずです。このセクションでは様々なハードウェア上でQMKを実行し、コミュニケーションする方法を探ります。

* [キーボードガイドライン](hardware_keyboard_guidelines.md)
* [AVRマイコン](hardware_avr.md)
* ARMマイコン (TBD)
* [ドライバー](hardware_drivers.md)
