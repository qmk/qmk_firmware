# crkbd用 親指シフトキーマップ (NICOLA配列)

キーボードのみで親指シフトするためのキーマップです。
[XD64 VER3.0 split spacebar 用 親指シフトキーマップ ](https://github.com/sadaoikebe/qmk_firmware/tree/master/keyboards/xd64/keymaps/nicola)を、crkbdへ移植しました。
[crkbd用 親指シフトキーマップ](https://github.com/eswai/qmk_firmware/tree/master/keyboards/crkbd/keymaps/nicola2)のキー押下が重なっていたら同時押しと判定するのではなく、NICOLA規格に則った同時押し判定が実装されています。

```make crkbd/rev1/common:nicola3:flash```

### 主な機能

|キー|機能|
|----|----|
|親指中央キー|親指シフトのシフトキー|
|RAISE+左親指シフトキー|英字入力へ切り替え|
|LOWER+右親指シフトキー|親指シフト入力へ切り替え|
