#  Kunai16/Kunai16c用 薙刀式日本語入力キーマップ

薙刀式日本語入力をQMKで実現します。薙刀式v12究極版(仮)に準拠しています。
Windows用の編集モード1、2(ただし横書き用に修正)は実装が完了しました。編集モードの記号を使用するには、

1. Windowsのキーボード設定を106キーボードにする。
2. config.hで`NAGINATA_EDIT_MAC`コメントアウトし、`#define NAGINATA_EDIT_MODE_WIN`を有効にする。
3. [WinCompose](http://wincompose.info/)をインストールする。

macOSでの編集モードはカーソル移動など一部に対応しますが、Unicode入力にはUnicode Hex Inputへマウスを使って切り替えが必要で実用的ではないため、不完全です。

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
|ADJUST+右CMD|WORKMAN配列へ切り替え|
|親指中央キー|単押しでスペース、他のキーと同時押しでシフト|

### 他キーボードへの移植の指針

1. naginata.cとnaginata.hをコピーする。
2. rules.mkでnaginata.cをSRCに追加する。
3. config.h, keymap.cの`// 薙刀式`で囲まれた部分を移植する。

より詳細な手順は[QMKで自作キーボードを親指シフト/薙刀式へ拡張する](http://eswai.hatenablog.com/entry/2019/12/09/001009)をごらんくだい。
