# MiniAxe用 薙刀式カナ配列キーマップ

薙刀式カナ配列による入力をQMKで実現します。薙刀式v12究極版に準拠しています。
Windows用の編集モードも実装しています。編集モードの記号入力を使用するには以下の設定をしてください。

1. Windowsのキーボード設定を106キーボードにする。
2. [WinCompose](http://wincompose.info/)をインストールする。

MacOS, iOSで使うためには

1. config.hで`NAGINATA_EDIT_WIN`をコメントアウトし、`#define NAGINATA_EDIT_MODE_MAC`を有効にしてください。
2. ライプ変換を使っている場合は`#define MAC_LIVE_CONVERSION`を有効にしてください。
   動的にライブ変換対応をオンオフすることもできます。
   カスタムキーを定義して、mac_live_conversion_toggle(), mac_live_conversion_on(), mac_live_conversion_off()を呼びし出してください。
3. naginata_dictionary.plistを使って辞書登録してください。

標準では本家の通り縦書きのためのカーソル移動方向になっていますが、
横書き用にするにはconfig.hの`NAGINATA_TATEGAKI`をコメントアウトし、
`NAGINATA_YOKOGAKI`を有効にしてください。

### 薙刀式とは

【カタナ式ファミリー】カナ配列「薙刀式」
http://oookaworks.seesaa.net/article/456099128.html
