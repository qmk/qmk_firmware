# crkbd用 薙刀式カナ配列キーマップ

薙刀式カナ配列による入力をQMKで実現します。薙刀式v15（仮安定版）に準拠しています。
編集モードも実装していますが、
編集モードでの記号入力方式がOSによって異なるので、
使用するOS(Windows、MacOS、Linux)によって切り替える必要があります。
切り替えは再コンパイル不要で、動的に切り替えられます。

## 薙刀式とは

【薙刀式】v15（仮安定版）: 大岡俊彦の作品置き場
http://oookaworks.seesaa.net/article/492480494.html
## OSの設定

1. OSのキーボード設定を日本語106キーボードにする。
2. Windowsの場合は[WinCompose](http://wincompose.info/)をインストールする。
3. MacOSの場合は、ユーザー辞書にnaginata_dictionary.plistを登録する。(Big Surではユーザー辞書の入力に数字が使えなくなったので辞書を作り直しました。)

## QMKファームウェアの設定

独自拡張として、標準のシフト&スペースに加えて、シフト&エンターキーを追加しました。
NG_SHFT2をキーマップに配置すると、単押しならエンター、
同時押しで薙刀式のシフトキーとして機能します。

OLEDが有効な場合には左側のOLEDには、
日本語入力モードに応じて「かな」または「ABC」と表紙されます。
右側のOLEDには薙刀式のロゴが表示されます。薙刀式のロゴは大岡俊彦氏に帰属します。

ファームウェアのコンパイル、書き込みは以下のコマンドです。

```make crkbd/rev1/common:naginata_v15:flash```

薙刀式のコードは次に集約しました。
https://github.com/eswai/qmk_firmware/tree/master/users/naginata_v15

## キーボードの切り替え操作

以下の機能を動的に切り替えることができます。
設定内容はEEPROMに記録されるので、
キーボードを取り外しても設定は保存されています。

| 設定項目 | 設定 | キー | キーコード | 関数呼び出し | 
|---|---|---|---|---|
| OS切り替え            | Windows  | Raise + Q  | NGSW_WIN  | switchOS(NG_WIN)  | 
|                       | MacOS    | Raise + A  | NGSW_MAC  | switchOS(NG_MAC)  | 
|                       | Linux    | Raise + Z  | NGSW_LNX  | switchOS(NG_LNX)  | 
| MacOSのライブ変換対応 | ON/OFFトグル   | Raise + Tab  | NG_MLV   | mac_live_conversion_toggle()  | 
| 縦書き、横書き        | ON/OFFトグル   | Raise + Control  | NG_TAYO    | tategaki_toggle()  | 
| 後置シフト            | ON/OFFトグル   | Raise + Escape  | NG_KOTI  | kouchi_shift_toggle()  | 
| 現在設定の出力        |   | Raise + W  | NG_SHOS   | ng_show_os()  | 

本家のDvorakJ版薙刀式は前置シフトですが、
後置シフトも有効にできます。

MacOSでライブ変換が有効な場合、
記号入力で変換操作が不要なので、ライブ変換対応をオンにしてください。

OLEDをオンにしているときは、設定の状態がOLEDに表示されます。
 * 1行目 OS設定。Windows、Mac、Linuxの頭文字です。
 * 2行目 縦書き(T)、横書き(Y)
 * 3行目 後置シフト(Kでオン)
 * 4行目 ライブ変換(Lでオン)

## キーマップ

![My keymap](keymap.svg "Crkbd")

OLED

![OLED](https://i.imgur.com/0RiOER9.jpg)


