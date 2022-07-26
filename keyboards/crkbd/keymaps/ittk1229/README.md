# ittk1229

[Corne Cherry Light](https://shop.yushakobo.jp/products/corne-cherry-light)
用のキーマップ設定ファイル

![keymaps](https://user-images.githubusercontent.com/95482635/179759383-c1657d81-a044-4806-bb2b-5e1006ff4e04.jpg)

## Features

### Default レイヤー

アルファベットを入力するためのレイヤー

-   `Raise`を短く押すと IME を ON に、`Lower`を短く押すと IME を OFF にできる
-   `Enter`は他のキーと組み合わせて押すと`Ctrl`に、`Space`は他のキーと組み合わせて押すと`Shift`になる
-   Esc, Tab, Win, Del がレイヤーを変えずに利用できる
-   [EUCALYN 配列](https://eucalyn.hatenadiary.jp/entry/about-eucalyn-layout)を少し改変した配列になっている
    -   vim で移動に用いる`hjkl`を横一列に並べた
    -   日本語を入力する上で比較的登場回数の多い`n`を小指から中指の位置に移動した

### Lower レイヤー

数字の入力と移動を行うためのレイヤー

-   矢印キー`←↓↑→`と`Home`, `PageUp`, `PageDown`, `End`がそれぞれ横一列に並んでおり、vim の`hjkl`と同じ感覚で使える

### Raise レイヤー

記号を入力するためのレイヤー

-   役割の近い記号が近くに配置されていて覚えやすい
-   `^{}$`が横一列に並んでおり、vimの大きな移動が`hjkl`と同じような感覚でできる
-   上下の移動は逆になっているので注意
    -   `^`: 行頭へ移動
    -   `{`: 一段落上へ移動
    -   `}`: 一段落下へ移動
    -   `$`: 行末へ移動

### Adjust レイヤー

その他のキーを割り当てるためのレイヤー

-   `Raise`と`Lower` の同時押しで出現
-   デフォルトでは F キー、スクリーンショット、`CapsLock`が割り当てられている
-   `CapsLock`が、US 配列と同じ仕様になっている
    -   押すと単に大文字小文字が切り替わる

### References

[QMK Firmware で Raise/Lower と変換/無変換を同じキーに割り当てる - Okapies' Archive](https://okapies.hateblo.jp/entry/2019/02/02/133953)

[QMK firmware の Tap Hold の動作を改善する – akakyouryuu](https://akakyouryuu.com/qmk-firmware%E3%81%AEtap-hold%E3%81%AE%E5%8B%95%E4%BD%9C%E3%82%92%E6%94%B9%E5%96%84%E3%81%99%E3%82%8B/)
