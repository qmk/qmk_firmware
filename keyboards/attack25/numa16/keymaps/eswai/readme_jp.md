# The numATTACK16 Universal Layout
## 配列

### Default Layer

```
 ,-----------------------.                         
 |  7  |  8  |  9  |  -  |  - momentary on...RGB Layer
 |-----+-----+-----+-----|
 |  4  |  5  |  6  |  +  |  + momentary on...FN Layer
 |-----+-----+-----+-----|
 |  1  |  2  |  3  |  *  |  * momentary on...BLED Layer
 |-----+-----+-----+-----|
 |  0  |  .  | Ent |  /  |  / momentary on...BLED Layer
 `------------------------
```

### FN Layer

```
 ,-----------------------.             
 |  F7 |  F8 |  F9 | F10 |
 |-----+-----+-----+-----|
 |  F4 |  F5 |  F6 |     |
 |-----+-----+-----+-----|
 |  F1 |  F2 |  F3 |     |
 |-----+-----+-----+-----|
 |     |     |     |     |
 `------------------------
```
 
### FN2 Layer

```
 ,-----------------------.             
 | Num |  /  |  *  | STab|
 |-----+-----+-----+-----|
 | Esc |     |WinMc| Tab |
 |-----+-----+-----+-----|
 |     |     |     | BS  |
 |-----+-----+-----+-----|
 |     |     |     |     |
 `------------------------
```
 ### RGB Layer

```
 ,-----------------------.             
 | TOG | MODF| HINC|     |             
 |-----+-----+-----+-----|
 | RST | MODR| HDEC|     |
 |-----+-----+-----+-----|
 | SAI |     | VAI |     |
 |-----+-----+-----+-----|
 | SAD |     | VAD |     |
 `------------------------
```

 ### BL Layer

```
 ,-----------------------.             
 | TOG | BLON| INC |STEP |             
 |-----+-----+-----+-----|
 | MODE|BLOFF| DEC |     |
 |-----+-----+-----+-----|
 |     |     |     |     |
 |-----+-----+-----+-----|
 |     |     |     |     |
 `------------------------
```

## コンパイルの仕方

コンパイルは、qmk_firmware のトップディレクトリで行います。

```
$ cd qmk_firmware
```
qmk_firmwareでは各キーボードのコンパイルは、`<キーボード名>:<キーマップ名>`という指定で行います。

```
$ make attack25/numa16:default
```

キーボードへの書き込みまで同時に行うには下記のように`:avrdude`を付けます。

```
$ make attack25/numa16:default:avrdude
```

コンパイル結果と中間生成物を消去したい場合は以下のようにします。

```
$ make attack25/numa16:default:clean
```

## カスタマイズ

コマンドラインからオプションを指定してビルドすることが出来ます。

```
### NumATTACK16 keyboard 'default' keymap: convenient command line option
##    make ATTACK25=<options> attack25/numa16:defualt
##    option= smd | back | under | na | ios
##    ex.
##      make ATTACK25=under    attack25/numa16:defualt
##      make ATTACK25=under,ios attack25/numa16:defualt
##      make ATTACK25=back     attack25/numa16:default
##      make ATTACK25=back,na  attack25/numa16:default
##      make ATTACK25=back,ios attack25/numa16:default
##      make ATTACK25=smd,back,ios attack25/numa16:default

```

## カスタマイズに使用できるオプションについて

```
smd...SMD版の場合（MCUが32u2になります）
back...バックライトLEDを有効にする場合（キーキャップ側を照らすインスイッチLEDを実装した場合）
under...アンダーグロウLEDを有効にする場合（底面側を照らす5個のLEDを実装した場合）
na...RGBのアニメーションをオフにする場合
ios...iPad/iPhoneなどのiOS機器に接続する場合（消費電力を制限します）

```

## カスタマイズを使用したビルドコマンド例

make ATTACK25=smd,under attack25/numa16:default
アンダーグロウLEDを有効にするオプションを付与してdefaultキーマップのファームをビルドします

