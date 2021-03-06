# crkbd用 親指シフトキーマップ (NICOLA配列)

ソフトウェアをインストールせずにキーボードのみで親指シフトするためのキーマップです。

```make crkbd/rev1/common:nicola2:flash```

### 主な機能

|キー|機能|
|----|----|
|親指中央キー|親指シフトのシフトキー|
|RAISE+左親指シフトキー|英字入力へ切り替え|
|LOWER+右親指シフトキー|親指シフト入力へ切り替え|
|ADJUST+BSPC|QWERTY配列へ切り替え|
|ADJUST+ENT|Eucalyn配列へ切り替え|

### 他キーボードへの移植の指針

1. nicola.cとnicola.hをコピーする。
2. rules.mkでnicola.cをSRCに追加する。
3. keymap.cの`// NICOLA親指シフト`で囲まれた部分を移植する。
