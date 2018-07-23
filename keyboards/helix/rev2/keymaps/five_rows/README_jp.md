# Keymap for 5 rows Helix keyboard

本キーマップは、Helix キーボードの5行版専用のキーマップです。

普通のキーボード使用者が、Helix キーボードを使うときになるべく違いが少なく戸惑いが少なくなるように意図したキーマップです。（意図通り成功しているかどうかは使用する人の判断で、、、)

## キー配置
以下に、Qwerty配列時の、文字配列の図を示します。

![fig1](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/662082b66231eb8d1f45776d813c57f29d445e68/helix-five_rows_r2.png)

## レイヤー

|優先順位|番号|名称|内容|
| ---- | ---- | --- | --- |
|高い|16|Adjust|機能キー（紫）|
||4|Extra char|記号類（赤）|
||3|Function|ファンクションキー類（青）|
||2|Dvorak|Dvorak配列|
||1|Colemak|Colemak配列|
|低い|0|Qwerty|QWERTY配列（ベース）|

Qwerty/Colemak/Dvorak の各レイヤーは、後述する、Ajuest キーによる選択で、いずれか一つだけが有効になり、標準のキーマップとなります。

Adjust レイヤーは、Adjust キーを押している間だけ有効になり、標準のキーマップの上にかぶさるように一部のキーが置き換わります。

Function レイヤーは、Fn キーを押している間だけ有効になり、標準のキーマップの上にかぶさるように一部のキーが置き換わります。

Extra レイヤーは、Enter キーを一定時間(0.1秒)以上押していると押している間だけ有効になり、標準のキーマップの上にかぶさるように一部のキーが置き換わります。
このため、Enterキーで Enter を入力するには、Enterキーを押して短時間ですぐ離してください。

### Adjust レイヤー
Ajust レイヤーは、Helix の標準キーマップ "default" から F1,F2..F12 を除き、右側にあった機能キーを
左側にも追加したものとなっています。

LEDコントロール、Mac/Win モードの切り替え、Qwerty配列, Colemak配列, Dvorak配列の切り替えが行えます。

### MacモードとWinモード
キーボードには、Mac モードと、Win モードの二つのモードがあります。

現在のモードはOLEDにアイコンとして表示されます。
(以下の指定キーは、Qwerty配列時の文字を使ってキーを表示しています）

|コマンド|指定キー|コード|
| ---- | ---- | --- |
|Macモード|Adjust + g(Qwerty)|AG_NORM|
|Winモード|Adjust + h(Qwerty)|AG_SWAP|
|        |Adjust + t(Qwerty)|       |

Mac モードと Win モードでは、AltキーとWin(GUI)キーが入れ替わります。

Mac モードでは、上の配列図の「英数キー」と「かなキー」で英語モードと日本語モードの切り替えができます。。

Winモードでは、該当のキーはどちらも共に Alt + `（日本語IMEの切り替え）として入力されます。

### LEDコントロール

バックライトやUnderglowをコントロールするにはAdjustレイヤーにある機能キーを使います。
(以下の指定キーは、Qwerty配列時の文字を使ってキーを表示しています）

|コマンド|指定キー|コード|
| ---- | ---- | --- |
|オン／オフ|Adjust + ,(Qwerty)|RGB_TOG|
|      |Adjust + v(Qwerty)|       |
|モード切り替え|Adjust + Right option |RGB_SMOD|
|           |Adjust + c(Qwerty)|       |
|色相 +|Adjust + .(Qwerty)|RGB_HUI|
|     |Adjust + Left Control|       |
|色相 -|Adjust + menu|RGB_HUD|
|     |Adjust + Left Shift  |       |
|彩度 +|Adjust + /(Qwerty)   |RGB_SAI|
|     |Adjust + a(Qwerty)   |       |
|彩度 -|Adjust + 右手Fnの左側|RGB_SAD|
|     |Adjust + z(Qwerty)  |       |
|明度 +|Adjust + Right Shift|RGB_VAI|
|     |Adjust + s(Qwerty)  |       |
|明度 -|Adjust + 右手Fnの右側|RGB_VAD|
|     |Adjust + x(Qwerty)  |       |
|リセット|Adjust + w|RGBRST|

### 文字配列選択
Qwerty, Colemak, Dvorak それぞれの文字配列の選択は以下のキーを使います。

|選択配列|指定キー|
| ---- | ---- |
|Qwerty | Adjust + j(Qwerty) |
|       | Adjust + 5|
|Calemak| Adjust + k(Qwerty) |
|       | Adjust + 4|
|Dvorak | Adjust + l(Qwerty) |
|       | Adjust + 3|

## 備考
本キーマップは、通常のキーボードの主要部分のホームポジション周辺をなるべくそのまま踏襲する方針で作成しました。
変更点は以下の通りです。

 * 右手小指により多く割り当たっていた5つの記号と左上の1つの記号を中央に集め人差し指の担当とする。
 * Enter キーを親指担当として中央手前に移動。
 * Control キーを左右共にホームポジションの行に移動。
 * 左手親指に BackSpace キーを割り当てる。

![fig2](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/9979482e9aa0b25962fad9ee634cd1c23cef1751/five_rows_making.jpg)
