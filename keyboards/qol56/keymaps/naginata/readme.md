# QOL56用 薙刀式日本語入力キーマップ

薙刀式日本語入力をQMKで実現します。薙刀式v11完成版に準拠しています。
Windows用の編集モード1、2(ただし横書き用に修正)は実装が完了しました。編集モードの記号を使用するには、

1. Windowsのキーボード設定を106キーボードにする。
2. config.hで`#define NAGINATA_EDIT_MODE_WIN`を有効にする。(デフォルト)
3. keymap.cで`set_unicode_input_mode(UC_WINC);`を有効にする。(デフォルト)
4. [WinCompose](http://wincompose.info/)をインストールする。

macOSでの編集モードはカーソル移動など一部に対応しますが、Unicode入力にはUnicode Hex Inputへマウスを使って切り替えが必要で実用的ではないため、不完全です。

### 薙刀式とは

【カタナ式ファミリー】カナ配列「薙刀式」
http://oookaworks.seesaa.net/article/456099128.html

### 他キーボードへの移植の指針

1. naginata.cとnaginata.hをコピーする。
2. rules.mkでnaginata.cをSRCに追加する。
3. config.h, keymap.cの`// 薙刀式`で囲まれた部分を移植する。

### キーマップ

![My keymap](keymap.svg "QOL56")