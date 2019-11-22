# 初めてのファームウェアを構築する(コマンドライン版)

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: ed0575fc8:docs/newbs_building_firmware.md
  git diff ed0575fc8 HEAD docs/newbs_building_firmware.md | cat
-->

ビルド環境をセットアップしたので、カスタムファームウェアのビルドを開始する準備ができました。
ガイドのこのセクションでは、ファイルマネージャ、テキストエディタ、ターミナルウィンドウの3つのプログラム間を行き来します。
キーボードファームウェアが完成して満足するまで、この3つすべてを開いたままにします。

ガイドの最初の部分を読んだ後でターミナルウィンドウを閉じて再度開いていた場合は、ターミナルが正しいディレクトリにあるように `cd qmk_firmware` を忘れないでください。

## キーマップフォルダに移動する

あなたのキーボードの `keymaps`フォルダに移動することから始めます。

macOS または Windows を使用している場合は、キーマップフォルダを簡単に開くために使用できるコマンドがあります。

### macOS:

``` open keyboards/<keyboard_folder>/keymaps ```

### Windows:

``` start .\\keyboards\\<keyboard_folder>\\keymaps ```

## `default` キーマップのコピーを作成する

`keymaps` フォルダを開いたら、`default`フォルダのコピーを作成します。
フォルダには、あなたの GitHub でのユーザー名と同じ名前を付けることを強くお勧めしますが、小文字、数字、アンダースコアのみが含まれている限り、任意の名前を使用できます。

この手順を自動化するために、`new_keymap.sh`スクリプトを実行する方法もあります。

`qmk_firmware/util` ディレクトリに移動して、次を入力します。

```
./new_keymap.sh <keyboard path> <username>
```

たとえば、John という名前のユーザーが 1up60hse の新しいキーマップを作成しようとするには、次のように入力します。

```
./new_keymap.sh 1upkeyboards/1up60hse john
```

## あなたの好みのテキストエディタで `keymap.c` を開く

`keymap.c`を開きます。
このファイル内には、キーボードの動作を制御する構造があります。
`keymap.c`の上部には、キーマップを読みやすくする `define` と `enum` があります。
さらに下には、次のような行があります。

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

この行はレイヤーのリストの開始を表わしています。
その下には、`LAYOUT` または `KEYMAP` のいずれかを含む行があり、これらの行はレイヤーの開始を表わしています。
その行の下には、その特定のレイヤーを構成するキーのリストがあります。

!> キーマップファイルを編集するときは、カンマを追加したり削除したりしないように注意してください。そうするとファームウェアのコンパイルができなくなり、余分であったり欠落していたりするカンマがどこにあるのかを容易に把握できない場合があります。

## 好みに合わせてレイアウトをカスタマイズ

納得のいくまでこのステップを繰り返します。
気になる点をひとつづつ変更して試すのもよし、全部作りなおすのもよし。
あるレイヤー全体が必要ない場合はレイヤーを削除することもでき、必要があれば、合計 32 個までレイヤーを追加することもできます。
ここで定義できる内容については、次のドキュメントを参照してください。

* [キーコード](ja/keycodes.md)
* [機能](ja/features.md)
* [FAQ](ja/faq.md)

?> キーマップがどのように機能するかを感じながら、各変更を小さくしてください。大きな変更は、発生する問題のデバッグを困難にします。

## ファームウェアをビルドする

キーマップの変更が完了したら、ファームウェアをビルドする必要があります。これを行うには、ターミナルウィンドウに戻り、ビルドコマンドを実行します:

    make <my_keyboard>:<my_keymap>

たとえば、キーマップの名前が "xyverz" で、rev5 planck のキーマップを作成している場合、次のコマンドを使用します:

    make planck/rev5:xyverz

これがコンパイルされる間、どのファイルがコンパイルされているかを知らせる多くの出力が画面に表示されます。
次のような出力で終わるはずです。

```
Linking: .build/planck_rev5_xyverz.elf                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                               [OK]
Checking file size of planck_rev5_xyverz.hex                                        [OK]
 * File size is fine - 18392/28672
```

## ファームウェアを書きこむ

[「ファームウェアを書きこむ」](ja/newbs_flashing.md) に移動して、キーボードに新しいファームウェアを書き込む方法を学習します。
