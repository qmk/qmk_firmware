# ハードウェア

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: c9e3fa6f7:docs/hardware.md
  git diff c9e3fa6f7 HEAD -- docs/hardware.md | cat
-->

QMK は様々なハードウェア上で実行できます。あなたの使っているマイコンが、[LUFA](http://www.fourwalledcubicle.com/LUFA.php) や [ChibiOS](http://www.chibios.com) に対応していれば、そのハードウェア上で QMK を動かすことができるはずです。このセクションでは様々なハードウェア上で QMK を実行し、通信する方法を探ります。

* [キーボードガイドライン](ja/hardware_keyboard_guidelines.md)
* [AVR マイコン](ja/hardware_avr.md)
* ARM マイコン (TBD)
* [ドライバー](ja/hardware_drivers.md)
