# Keyball39 miniZoneファームウェア

[miniZone](https://github.com/takashicompany/minizone)で開発したファームウェアの実装をKeyball39に流用したものです。

<!--
https://user-images.githubusercontent.com/4215759/162611440-2bb0ec75-2dbf-48b8-8c0d-54c8666c1aff.mp4
-->

https://github.com/takashicompany/qmk_firmware/assets/4215759/fcb52261-c998-403f-87d8-aca8a3f2261d

上述の動画と同様にトラックボールを動かした際に一定時間、トラックボールレイヤー(デフォルトでは7番目...index6のレイヤー)が有効になります。  

## ファームウェアの書き込み

ファイルは[こちら](https://github.com/takashicompany/qmk_firmware/releases/download/keyball-remap-qmk022/keyball_keyball39_takashicompany.hex)からダウンロードできます。

[Pro Micro Web Updater](https://sekigon-gonnoc.github.io/promicro-web-updater/index.html)や[QMK Toolbox](https://kbd.dailycraft.jp/claw44/buildguide/10_firmware/toolbox/)でファームウェアをPro Microに書き込んでください。

または、[当ブランチ](https://github.com/takashicompany/qmk_firmware/tree/keyball)を `git checkout` するかダウンロードした後に、以下のコマンドを実行することでファームウェアのビルドと書き込みが可能です。

```
make keyball/keyball39:takashicompany:flash
```

## Remapでのマウスキーの書き込みについて

当ファームウェアはRemapに対応しております。  
レイヤー数は7となります。

<img src="https://github.com/takashicompany/qmk_firmware/assets/4215759/64da22ab-edbf-442f-8dd1-d6b6a4848bbc" width="600px"/>


|キー|RemapでのKeycode|Code(hex)|説明|
|:--|:--|:--|:--|
|マウスボタン1|User 0|0x5DAF|主に左クリックが設定されていることが多い。|
|マウスボタン2|User 1|0x5DB0|主に右クリックが設定されていることが多い。|
|マウスボタン3|User 2|0x5DB1|OSやPCの設定に依存。|
|スクロールボタン|User 3|0x5DB2|このキーを押している際はトラックボールの入力はスクロールとして扱われる。|
|レイヤー変更しきい値減少|User4|0x5DB4|トラックボールレイヤーを有効にするためのトラックボール必要移動量のしきい値を下げる。最小は5。|
|レイヤー変更しきい値増加|User5|0x5DB3|トラックボールレイヤーを有効にするためのトラックボール必要移動量のしきい値を上げる。|
|縦スクロール方向の反転|User6|0x5DB5?|スクロールボタンを押した際のトラックボールの縦スクロールの方向を反転します。|
|横スクロール方向の反転|User7|0x5DB6?|スクロールボタンを押した際のトラックボールの横スクロールの方向を反転します。|

設定値はOLED上に表示されます。  
<img src="https://user-images.githubusercontent.com/4215759/193409514-c4b5b214-efa1-4ac8-bf06-c3d4938a1343.jpg" width="600px"/>

## その他

- 当ファームウェア、ソースコードを使用したことでの不利益や故障などは責任は負いかねます。
