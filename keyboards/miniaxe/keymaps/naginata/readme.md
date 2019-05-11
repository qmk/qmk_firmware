# miniaxe用 薙刀式日本語入力キーマップ

薙刀式日本語入力をQMKで実現します。薙刀式v11完成版に準拠しています。
最新のコードはcrkbd用を参照 [crkbd用薙刀式キーマップ](https://github.com/eswai/qmk_firmware/tree/master/keyboards/crkbd/keymaps/naginata)

### 薙刀式とは

【カタナ式ファミリー】カナ配列「薙刀式」
http://oookaworks.seesaa.net/article/456099128.html

### 主な機能

|キー|機能|
|----|----|
|RAISE|単押しで薙刀式入力へ切り替え|
|LOWER|単押しで英字入力へ切り替え|
|親指内側キー|単押しでスペース、他のキーと同時押しでシフト|

### 他キーボードへの移植の指針

1. rules.mkでnicola.cをSRCに追加する。
2. keymap.cの`// 薙刀式`で囲まれた部分を移植する。
