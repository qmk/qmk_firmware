# 初めてのファームウェアを構築する(コマンドライン版)

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.44:docs/newbs_building_firmware.md
  git diff 0.9.44 HEAD -- docs/newbs_building_firmware.md | cat
-->

ビルド環境をセットアップしたので、カスタムファームウェアのビルドを開始する準備ができました。
ガイドのこのセクションでは、ファイルマネージャ、テキストエディタ、ターミナルウィンドウの3つのプログラム間を行き来します。
キーボードファームウェアが完成して満足するまで、この3つすべてを開いたままにします。

## 新しいキーマップを作成する

独自のキーマップを作成するには、`default` キーマップのコピーを作成する必要があります。最後のステップでビルド環境を設定した場合は、QMK CLI を使って簡単に行うことができます:

    qmk new-keymap

もし環境が設定されていない場合や、複数のキーボードを所持している場合は、キーボード名を指定することができます:

    qmk new-keymap -kb <keyboard_name>

そのコマンドの出力を見ると、次のようになっているはずです:

    Ψ <github_username> keymap directory created in: /home/me/qmk_firmware/keyboards/clueboard/66/rev3/keymaps/<github_username>

これがあなたの新しい `keymap.c` ファイルの場所です。

## あなたの好みのテキストエディタで `keymap.c` を開く

テキストエディタで `keymap.c` ファイルを開きます。
このファイル内には、キーボードの動作を制御する構造があります。
`keymap.c`の上部には、キーマップを読みやすくする定義と列挙型があります。
さらに下には、次のような行があります:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

この行はレイヤーのリストの開始を表わしています。
その下には、`LAYOUT` を含む行があり、これらの行はレイヤーの開始を表わしています。
その行の下には、そのレイヤーを構成するキーのリストがあります。

!> キーマップファイルを編集するときは、カンマを追加したり削除したりしないように注意してください。そうするとファームウェアのコンパイルができなくなり、余分であったり欠落していたりするカンマがどこにあるのかを容易に把握できない場合があります。

## 好みに合わせてレイアウトをカスタマイズ

納得のいくまでこのステップを繰り返します。
気になる点をひとつづつ変更して試すのもよし、全部作りなおすのもよし。
あるレイヤー全体が必要ない場合はレイヤーを削除することもでき、必要があれば、合計 32 個までレイヤーを追加することもできます。
QMK にはたくさんの機能があり、完全なリストは左側のサイドバーの「QMK を使う」の下を調べてください。ここから始めるために、簡単に使える機能をいくつか紹介します:

* [基本的なキーコード](ja/keycodes_basic.md)
* [Quantum キーコード](ja/quantum_keycodes.md)
* [グレイブ エスケープ](ja/feature_grave_esc.md)
* [マウスキー](ja/feature_mouse_keys.md)

?> キーマップがどのように機能するかを感じながら、各変更を小さくしてください。大きな変更は、発生する問題のデバッグを困難にします。

## ファームウェアをビルドする :id=build-your-firmware

キーマップの変更が完了したら、ファームウェアをビルドする必要があります。これを行うには、ターミナルウィンドウに戻り、コンパイルコマンドを実行します:

    qmk compile

もし環境が設定されていない場合や、複数のキーボードを所持している場合は、キーボードやキーマップを指定することができます:

    qmk compile -kb <keyboard> -km <keymap>

これがコンパイルされる間、どのファイルがコンパイルされているかを知らせる多くの出力が画面に表示されます。
次のような出力で終わるはずです:

```
Linking: .build/planck_rev5_default.elf                                                             [OK]
Creating load file for flashing: .build/planck_rev5_default.hex                                     [OK]
Copying planck_rev5_default.hex to qmk_firmware folder                                              [OK]
Checking file size of planck_rev5_default.hex                                                       [OK]
 * The firmware size is fine - 27312/28672 (95%, 1360 bytes free)
```

## ファームウェアを書きこむ

[「ファームウェアを書きこむ」](ja/newbs_flashing.md) に移動して、キーボードに新しいファームウェアを書き込む方法を学習します。
