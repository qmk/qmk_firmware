# crkbd用 薙刀式日本語入力キーマップ

薙刀式日本語入力をQMKで実現します。薙刀式v11完成版に準拠しています。
Windows用の編集モードは実装が完了しました。編集モードの記号を入力するためには
1. config.hで`#define NAGINATA_EDIT_MODE_WIN`または`#define NAGINATA_EDIT_MODE_MAC`を選択。
2. [WinCompose](http://wincompose.info/)をインストール。
macOSでの編集モードは記号の入力は未対応です。

### 薙刀式とは

【カタナ式ファミリー】カナ配列「薙刀式」
http://oookaworks.seesaa.net/article/456099128.html

### 主な機能

|キー|機能|
|----|----|
|H+J|同時押しで薙刀式入力へ切り替え|
|F+G|同時押しで英字入力へ切り替え|
|ADJUST+BSPC|QWERTY配列へ切り替え|
|ADJUST+右ALT|Eucalyn配列へ切り替え|
|ADJUST+右CMD|Eucalyn配列改へ切り替え|
|親指中央キー|単押しでスペース、他のキーと同時押しでシフト|

### 他キーボードへの移植の指針

1. naginata.cとnaginata.hをコピーする。
2. rules.mkでnaginata.cをSRCに追加する。
3. 編集モードを使用する場合は、config.hに`#define NAGINATA_EDIT_MODE_WIN`または`#define NAGINATA_EDIT_MODE_MAC`を追加する。
4. keymap.cの`// 薙刀式`で囲まれた部分を移植する。
