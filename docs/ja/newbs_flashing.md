# ファームウェアを書き込む

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.12.45:docs/newbs_flashing.md
  git diff 0.12.45 HEAD -- docs/newbs_flashing.md | cat
-->

カスタムファームウェアは出来たので、いよいよキーボードへの書き込み(フラッシュ)です。

## キーボードを DFU (Bootloader) モードにする

カスタムファームウェアを書き込むには、最初にキーボードを普段とは違う特別な状態、フラッシュモードにする必要があります。
このモードでは、キーボードはキーボードとしての機能を果たしません。
ファームウェアの書き込み中にキーボードのケーブルを抜いたり、書き込みプロセスを中断したりしないことが非常に重要です。

キーボードによって、この特別なモードに入る方法は異なります。
PCB が現在 QMK、TMK、PS2AVRGB (Bootmapper Client) を実行しており、キーボードメーカーから具体的な指示が与えられていない場合は、次を順番に試してください。

* 両方のシフトキーを押しながら、`Pause` キーを押す
* 両方のシフトキーを押しながら、`B` キーを押す
* キーボードのケーブルを抜いて、スペースバーと `B` を同時に押しながら、キーボードを再び接続し、1秒待ってからキーを放す
* キーボードのケーブルを抜いて、左上か左下のキー(通常は Escape か左 Control)を押しながらキーボードを接続する
* 通常、PCB の裏側に付けられている物理的な `RESET` ボタンを押す
* PCB 上の `RESET` か `GND` のラベルの付いたヘッダピンを探し、PCB 接続中にそれらを互いにショートする

上記を全て試してもうまくいかず、基板のメインチップに `STM32` と表示されている場合、これは少し複雑になる可能性があります。通常、最善の方法は [Discord](https://discord.gg/Uq7gcHh) で助けを求めることです。おそらく基板の写真をいくつか求められるでしょう。あらかじめそれらを準備することができれば物事を進めるのに役立ちます！

それ以外の場合は、QMK Toolbox で次のような黄色のメッセージが表示されます:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
```

そして、このブートローダデバイスはデバイスマネージャーやシステム情報.app、`lsusb` にも表示されます。

## QMK Toolbox を使ってキーボードに書き込む

キーボードに書き込む最も簡単な方法は [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) を使うことです。

ただし、QMK Toolbox は、現在は Windows と macOS でしか使えません。
Linux を使用している場合(および、コマンドラインでファームウェアを書き込みたい場合)は、[コマンドラインからキーボードを書き込む](#flash-your-keyboard-from-the-command-line)節まで進んでください。

### QMK Toolbox にファイルをロードする

まず QMK Toolbox アプリケーションを起動します。
Finder またはエクスプローラーでファームウェアのファイルを探します。
キーボードのファームウェアは `.hex` または `.bin` のどちらかの形式です。
ビルド時に QMK は、キーボードに適した形式のものを `qmk_firmware` のトップフォルダにコピーしているはずです。

Windows か macOS を使用している場合、現在のフォルダをエクスプローラーか Finder で簡単に開くためのコマンドがあります。

<!-- tabs:start -->

#### ** Windows **

```
start .
```

#### ** macOS **

```
open .
```

<!-- tabs:end -->

ファームウェアファイルは常に以下の命名形式に従っています:

```
<keyboard_name>_<keymap_name>.{bin,hex}
```

例えば、`plank/rev5` の `default` キーマップのファイル名は以下のようになります:

```
planck_rev5_default.hex
```

ファームウェアファイルを見つけたら、QMK Toolbox の "Local file" ボックスにドラッグするか、"Open" をクリックしてファームウェアファイルが格納されている場所を指定します。

### キーボードへの書き込み

QMK Toolbox の `Flash` ボタンをクリックします。次のような出力が表示されます。

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
*** Attempting to flash, please don't remove device
>>> dfu-programmer.exe atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer.exe atmega32u4 flash "D:\Git\qmk_firmware\gh60_satan_default.hex"
    Checking memory from 0x0 to 0x3F7F...  Empty.
    0%                            100%  Programming 0x3F80 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x3F80 bytes written into 0x7000 bytes memory (56.70%).
>>> dfu-programmer.exe atmega32u4 reset
    
*** DFU device disconnected: Atmel Corp: ATmega32U4 (03EB:2FF4:0000)
```

## コマンドラインでファームウェアを書き込む :id=flash-your-keyboard-from-the-command-line

これは、以前のものと比較して非常に単純になりました。
ファームウェアをコンパイルして書き込む準備ができたら、ターミナルウィンドウを開いて書き込みコマンドを実行します:

    qmk flash

もし CLI でキーボードやキーマップ名を設定していない場合や、複数のキーボードを持っている場合、キーボードとキーマップを指定することができます:

    qmk flash -kb <my_keyboard> -km <my_keymap>

これはキーボードの設定を確認し、指定されたブートローダに基づいて書き込もうとします。これはどのブートローダをキーボードが使っているか知る必要がないことを意味します。単にコマンドを実行し、コマンドに重い仕事をさせましょう。

ただし、これはキーボードごとに設定されているブートローダに依存します。
もし、この情報が設定されていない場合、または、使用しているキーボードが、ファームウェア書き込みでサポートされているターゲットを持っていない場合、次のエラーが表示されます:

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

この場合、あなたは明示的にブートローダを指定する方法を使わなければなりません。詳細は、[ファームウェアのフラッシュ](ja/flashing.md)ガイドを参照してください。

## テストしましょう！

おめでとうございます！カスタムファームウェアがキーボードにプログラムされ、テストする準備ができました！

少し運が良ければ全てが完璧に機能しますが、そうでない場合は何が問題なのかを理解するのに役立つ手順があります。
通常、キーボードのテストは非常に簡単です。全てのキーをひとつずつ押して、期待するキーが送信されることを確認します。例え QMK で動作していない場合でも、[QMK Configurator](https://config.qmk.fm/#/test/) のテストモードを使用すると、キーボードをチェックできます。

まだ動作しませんか？詳細については FAQ トピックを参照するか、[Discord でチャット](https://discord.gg/Uq7gcHh)してください。
