# crkbd用 薙刀式カナ配列キーマップ

薙刀式カナ配列による入力をQMKで実現します。薙刀式v15に準拠しています。

ファームウェアのコンパイル、書き込みは以下のコマンドです。

```qmk flash -kb crkbd -km naginata_v15```

薙刀式のコードは次に集約しました。
https://github.com/eswai/qmk_firmware/tree/master/users/naginata_v15

## 編集モードを使う場合

1. Windowsの場合は[WinCompose](http://wincompose.info/)をインストールする。
2. MacOSの場合は、Karabiner-Elementsをインストールして、 unicode_hex_input_switcher.json を ~/.config/karabiner/assets/complex_modifications/ において、Karabiner-Elementsの設定で有効にする。

## キーボードの切り替え操作

以下の機能を動的に切り替えることができます。
設定内容はEEPROMに記録されるので、
キーボードを取り外しても設定は保存されています。

| 設定項目 | 設定 | キー | キーコード | 
|---|---|---|---|
| OS切り替え            | Windows  | Raise + Q  | NGSW_WIN  | 
|                       | MacOS    | Raise + A  | NGSW_MAC | 
|                       | Linux    | Raise + Z  | NGSW_LNX | 
| MacOSのライブ変換対応 | ON/OFFトグル   | Raise + Tab  | NG_MLV | 
| 縦書き、横書き        | ON/OFFトグル   | Raise + Control  | NG_TAYO | 
| 後置シフト            | ON/OFFトグル   | Raise + Escape  | NG_KOTI | 
| 現在設定の出力        |   | Raise + W  | NG_SHOS | 

OLEDをオンにしているときは、設定の状態がOLEDに表示されます。
 * 1行目 OS設定。Windows、Mac、Linuxの頭文字です。
 * 2行目 縦書き(T)、横書き(Y)
 * 3行目 後置シフト(Kでオン)
 * 4行目 ライブ変換(Lでオン)

## キーマップ

![My keymap](keymap.svg "Crkbd")

OLED

![OLED](https://i.imgur.com/0RiOER9.jpg)


