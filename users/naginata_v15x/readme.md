# 薙刀式カナ配列キーマップ

薙刀式カナ配列による入力をQMKで実現します。薙刀式v15快速版(v15 D版)に準拠しています。
編集モードも実装していますが、
編集モードでの記号入力方式がOSによって異なるので、
使用するOS(Windows、MacOS、Linux)によって切り替え る必要があります。
切り替えは再コンパイル不要で、動的に切り替えられます。

## 薙刀式とは

【薙刀式】v15の名称を「快速版」にする予定
http://oookaworks.seesaa.net/article/499580730.html

## OSの設定

1. Windowsの場合は[WinCompose](http://wincompose.info/)をインストールする。
2. MacOSの場合は、Karabiner-Elementsをインストールして、 unicode_hex_input_switcher.json を ~/.config/karabiner/assets/complex_modifications/ において、Karabiner-Elementsの設定で有効にする。

## QMKファームウェアの設定

独自拡張として、標準のシフト&スペースに加えて、シフト&エンターキーを追加しました。
NG_SHFT2をキーマップに配置すると、単押しならエンター、
同時押しで薙刀式のシフトキーとして機能します。

OLEDが有効な場合には左側のOLEDには、
日本語入力モードに応じて「かな」または「ABC」と表紙されます。
右側のOLEDには薙刀式のロゴが表示されます。薙刀式のロゴは大岡俊彦氏に帰属します。

ファームウェアサイズが大きいので、
サイズを小さくするために、編集モードや固有名詞をオフにできます。
オフにする場合は、自身のkeymapフォルダのconfig.hに下を定義してください。
```
#define NG_NO_HENSHU
#define NG_NO_KOYUMEISHI
```

## キーボードの切り替え操作

以下の機能を動的に切り替えることができます。
設定内容はEEPROMに記録されるので、
キーボードを取り外しても設定は保存されています。

| 設定項目 | 設定 | キーコード | 関数呼び出し | 
|---|---|---|---|
| OS切り替え            | Windows  | NGSW_WIN  | switchOS(NG_WIN)  | 
|                       | MacOS    | NGSW_MAC  | switchOS(NG_MAC)  | 
|                       | Linux    | NGSW_LNX  | switchOS(NG_LNX)  | 
| MacOSのライブ変換対応 | ON/OFFトグル   | NG_MLV   | mac_live_conversion_toggle()  | 
| 縦書き、横書き        | ON/OFFトグル   | NG_TAYO    | tategaki_toggle()  | 
| 後置シフト            | ON/OFFトグル   | NG_KOTI  | kouchi_shift_toggle()  | 
| 現在設定の出力        |   | NG_SHOS   | ng_show_os()  | 

本家のDvorakJ版薙刀式は前置シフトですが、
後置シフトも有効にできます。

MacOSでライブ変換が有効な場合、
記号入力で変換操作が不要なので、ライブ変換対応をオンにしてください。

OLEDをオンにしているときは、設定の状態がOLEDに表示されます。
 * 1行目 OS設定。Windows、Mac、Linuxの頭文字です。
 * 2行目 縦書き(T)、横書き(Y)
 * 3行目 後置シフト(Kでオン)
 * 4行目 ライブ変換(Lでオン)
