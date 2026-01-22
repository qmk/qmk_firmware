**OS設定や縦書き横書きを動的に変更できるV13uをリリースしました。
[V13u](https://github.com/eswai/qmk_firmware/tree/master/keyboards/crkbd/keymaps/naginata_v13u)がおすすめです。
今後はV13uをベースに更新していく予定です。**

# crkbd用 薙刀式カナ配列キーマップ

薙刀式カナ配列による入力をQMKで実現します。薙刀式v13完成版に準拠しています。
Windows用の編集モードも実装しています。編集モードの記号入力を使用するには以下の設定をしてください。

1. Windowsのキーボード設定を106キーボードにする。
2. [WinCompose](http://wincompose.info/)をインストールする。

MacOS, iOSで使うためには

1. config.hで`NAGINATA_EDIT_WIN`と`#define UNICODE_SELECTED_MODES UC_WINC`をコメントアウトし、`#define NAGINATA_EDIT_MODE_MAC`を有効にしてください。
2. ライプ変換を使っている場合は`#define MAC_LIVE_CONVERSION`を有効にしてください。
   動的にライブ変換対応をオンオフすることもできます。
   カスタムキーを定義して、mac_live_conversion_toggle(), mac_live_conversion_on(), mac_live_conversion_off()を呼びし出してください。
3. naginata_dictionary.plistを使って辞書登録してください。

Linuxでの入力にも対応しました。
編集モードも対応しています。`#define NAGINATA_EDIT_LINUX`と`#define UNICODE_SELECTED_MODES UC_LNX`を有効にしてください。

標準では本家の通り縦書きのためのカーソル移動方向になっていますが、
横書き用にするにはconfig.hの`NAGINATA_TATEGAKI`をコメントアウトし、
`NAGINATA_YOKOGAKI`を有効にしてください。

デフォルトでは本家DvorakJと同様にシフトは前置ですが、
`NAGINATA_KOUCHI_SHIFT`を有効にすると後置シフトも有効になります。
親指シフトになれた方は後置シフトを有効にしたほうが快適でしょう。

独自拡張として、標準のシフト&スペースに加えて、シフト&エンターキーを追加しました。
NG_SHFT2をキーマップに配置すると、単押しならエンター、同時押しで薙刀式のシフトキーとして機能します。

OLEDが有効な場合には左側のOLEDには、日本語入力モードに応じて「かな」または「ABC」と表紙されます。
右側のOLEDには薙刀式のロゴが表示されます。薙刀式のロゴは大岡俊彦氏に帰属します。

ファームウェアのコンパイル、書き込みは以下のコマンドです。

```make crkbd/rev1/common:naginata_v13:flash```


### 薙刀式とは

【薙刀式】v13完成版、発表。
http://oookaworks.seesaa.net/article/479173898.html

### キーマップ

![My keymap](keymap.svg "Crkbd")

