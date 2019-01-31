# Keymap for Ergo42

## 概要

Ergo42 用キーマップです。

- JIS 配列
- 独立した Windows 配列/MacOS 配列レイヤー
- 普通のキーボード配列に似せた最下段キー
- 逆 T 字 (凸型) 配列の矢印キー

## レイアウト

![keyboard-layout](https://user-images.githubusercontent.com/1042121/45888288-aa35ed00-bdf8-11e8-8741-71fe9a0fadc6.png)

## Windows モード/MacOS モード

|モード        |キー        |
|--------------|------------|
|Windows モード|Function + g|
|MacOS モード  |Function + b|

モードを切り替えることで下記のキーが切り替わります。

|Windows     |MacOS       |
|------------|------------|
|Alt         |Command(GUI)|
|Windows(GUI)|Option(Alt) |
|Menu(App)   |Command(GUI)|
|無変換      |英数        |
|変換        |かな        |
|半角/全角   |Caps        |

## レイヤー

|No.|名称    |内容                      |
|---|--------|--------------------------|
| 4 |Function|モード切替, メディア      |
| 3 |Raise   |数字, ファンクションキー  |
| 2 |Lower   |記号, Home/End, PgUp/PgDn |
| 1 |MacOS   |MacOS 配列                |
| 0 |Windows |Windows 配列              |

電源 ON により No.0 の Windows レイヤーが有効になります。

## Windows/MacOS レイヤー

Windows モード/MacOS モードの標準レイヤー。

## Raise/Lower レイヤー

Raise キーまたは Lower キーを押している間だけ有効になるレイヤー。

普通のキーボードの最上段キー (数字/記号) に加えて、標準レイヤーに入らなかった記号キーが3つ (`[{`, `]}`, `\_`) 入っています。  
括弧キー `[{`, `]}` は `(`, `)` を加えて、左右対称に配置しました。

## Function レイヤー

Function キーを押している間だけ有効になるレイヤー。

Windows モード/MacOS モードの切り替え、メディア系の操作、標準レイヤーに入らなかった機能キーのレイヤーです。

