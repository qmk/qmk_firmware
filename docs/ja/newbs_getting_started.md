<!---
  original document: docs/newbs_getting_started.md
  $ git show 161d469:docs/newbs_getting_started.md
-->

# イントロダクション

あなたのキーボードに入っているプロセッサは、コンピュータのプロセッサと大して違わないものです。
このキーボードのプロセッサで走るソフトウェアは、タイピングに反応しキーが押されている否かのキーボードの状況をコンピュータに通知します。
QMK は、この役割をはたすためのソフトウェアです。
カスタマイズしたキーマップを作成することは、自分のキーボードのためのプログラムを作成するのと同じことです。

QMK は、簡単なことは簡単に、そして、難しいことを可能なことにすることで、あなたの手にたくさんのパワーをもたらします。
パワフルなキーマップを作るために難しいプログラムは不要です。シンプルな文法に従うだけでOKです。

# はじめに

キーマップをビルドする前に、複数のソフトウェアをインストールして必要な環境を構築する必要があります。
この作業を一度実行すれば、どのキーボードのファームウェアもコンパイルできます。

もし、GUI で作業をしたい場合、オンラインで作業できる [QMK Configurator](https://config.qmk.fm) を使ってください。
使い方は [Building Your First Firmware using the online GUI](newbs_building_firmware_configurator.md) を参照してください。

## ソフトウェアのダウンロード

### テキストエディタ

GUI を使わない場合、プレーンテキストを編集・保存できるエディタが必要です。
Windows の場合、Notepad が使えます。Linux の場合、gedit が使えます。
どちらもシンプルですが機能的なエディタです。
macOS を使っているなら、デフォルトの TextEdit.app が使えますが、ファイルのフォーマットをプレーンテキストに指定してください。

[Sublime Text](https://www.sublimetext.com/) や [VS Code](https://code.visualstudio.com/) のようなエディタも使えます。プログラミングやコード編集には、これがベストだと思います。

?> どのエディタを使えば良いか分からない場合、Laurence Bradford が書いたこの記事 [a great introduction](https://learntocodewith.me/programming/basics/text-editors/) を読んでください。

### QMK Toolbox

QMK Tookbox は、Windows と macOS で使える GUI を備えたプログラムで、キーボードのプログラミングとデバッグの両方ができます。
このプログラムは、キーボードにファームウェアを書き込んだりデバッグメッセージを確認する際に、かけがえのないものになるはずです。

[QMK Toolbox の最新版](https://github.com/qmk/qmk_toolbox/releases/latest)

* Windows 版: `qmk_toolbox.exe` (portable) または `qmk_toolbox_install.exe` (installer)
* macOS 版: `QMK.Toolbox.app.zip` (portable) または `QMK.Toolbox.pkg` (installer)

## 環境構築

私たちは、QMK を可能な限り簡単に準備できるように努力しています。
Linux か Unix 環境を用意して、それから QMK をインストールします。

?> もし、Linux か Unix のコマンドを使ったことがない場合、こちらで各種コマンドや基本的な概念を学んでください。これらの教材で QMK を使うのに必要なことを学ぶことができます。

[Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)<br>
[Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

MSYS2 と Git をインストールしてください。

* [MSYS2 homepage](http://www.msys2.org) の手順に従って MSYS2 をインストールします。
* MSYS2 の画面を閉じて、新しい MSYS2 MinGW 64-bit のターミナル画面を開きます。
* `pacman -S git` を実行して Git をインストールします。

### macOS

[Homebrew homepage](https://brew.sh) の手順に従って Homebrew をインストールしてください。

Homebrew をインストールしたら、以下の _QMK の準備_ に進み、インストールスクリプトを実行して他のパッケージもインストールしてください。

### Linux

Git のインストールが必要です。既にインストールされている可能性は高いですが、そうでない場合、次のコマンドでインストールできます。

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch: `pacman -S git`

?> 上記の方法に加えて、Docker を使うことも可能です。[詳細はこちらをクリックしてください](getting_started_build_tools.md#docker)。

## QMK の設定

Linx/Unix 環境が準備できたら QMK のダウンロードの準備は完了です、Git の `clone` コマンドを実行して QMK のリポジトリを clone します。ターミナルか MSYS2 を立ち上げて、次の2つのコマンドを実行します。

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

> 既に [GitHub の使いかた](getting_started_github.md)を知っているなら、clone ではなく fork を勧めます。この一文の意味が分からない場合、このメッセージは無視してかまいません。

QMK には、必要な残りの設定を手助けするスクリプトが含まれています。
セットアップ作業を完了させるため、次のコマンドを実行します。

    util/qmk_install.sh

## 環境構築の確認

これで QMK を使う環境が用意できましたので、キーボードのファームウェアをビルドできます。
試しに、あなたのキーボードのデフォルトのキーマップをビルドするため、次のコマンドを実行してください。

    make <keyboard>:default

例）Clueboard 66% のファームウェアをビルドする

    make clueboard/66/rev3:default

次のようなメッセージが大量に表示されます。

```
Linking: .build/clueboard_66_rev3_default.elf                                     [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex             [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                      [OK]
Checking file size of clueboard_66_rev3_default.hex                               [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# キーマップの作成

これであなた専用のキーマップを作成する準備ができました！
次は [Building Your First Firmware](newbs_building_firmware.md) で専用のキーマップを作成します。
