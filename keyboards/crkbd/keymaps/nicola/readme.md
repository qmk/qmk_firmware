# (旧)crkbd用 親指シフトキーマップ (NICOLA配列)

ソフトウェアをインストールせずにキーボードのみで親指シフトするためのキーマップです。

薙刀式のコードをベースに親指シフトを書き直しました。
[新NICOLA親指シフトキーマップ](https://github.com/eswai/qmk_firmware/tree/master/keyboards/crkbd/keymaps/nicola2)

### 主な機能

|キー|機能|
|----|----|
|RAISE|単押しで親指シフト入力へ切り替え|
|LOWER|単押しで英字入力へ切り替え|
|ADJUST+BSPC|QWERTY配列へ切り替え|
|ADJUST+ENT|Eucalyn配列へ切り替え|
|親指中央キー|親指シフトのシフトキー|


### 他キーボードへの移植の指針

rules.mkでnicola.cをSRCに追加する。
`// 親指シフト`で囲まれた部分を移植する。

* 親指シフトレイヤー番号の定義
* 親指シフトシフトキーの定義
* 親指シフトレイヤーのキーマップ定義(英字キーマップにかかわらずQWERTYで)
* 親指シフト入力のコード1を関数の外へコピー
* 親指シフト入力のコード2をprocess_record_user内にコピー