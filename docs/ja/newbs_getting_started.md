# イントロダクション

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 161d469:docs/newbs_getting_started.md
  git diff 161d469 HEAD -- docs/newbs_getting_started.md | cat
-->

キーボードにはプロセッサが入っており、それはコンピュータに入っているものと大して違わないものです。
このプロセッサでは、キーボードのボタンの押し下げの検出を担当しキーボードのどのボタンが押されている/離されているかのレポートをコンピュータに送信するソフトウェアが動作しています。
QMK は、そのソフトウェアの役割を果たし、ボタンの押下を検出しその情報をホストコンピュータに渡します。
カスタムキーマップを作るということは、キーボード上で動くプログラムを作るということなのです。

QMK は、簡単なことは簡単に、そして、難しいことを可能なことにすることで、あなたの手にたくさんのパワーをもたらします。
パワフルなキーマップを作るためにプログラムを作成する方法を知る必要はありません。いくつかのシンプルな文法に従うだけで OK です。

# はじめに

キーマップをビルドする前に、いくつかのソフトウェアをインストールしてビルド環境を構築する必要があります。
ファームウェアをコンパイルするキーボードの数に関わらず、この作業を一度だけ実行する必要があります。

もし、GUI で作業をしたい場合、オンラインで作業できる [QMK Configurator](https://config.qmk.fm) を使ってください。
使い方は [オンライン GUI を使用して初めてのファームウェアを構築する](ja/newbs_building_firmware_configurator.md) を参照してください。

## ソフトウェアのダウンロード

### テキストエディタ

GUI を使わない場合、プレーンテキストを編集・保存できるエディタが必要です。
Windows の場合、メモ帳が使えます。Linux の場合、gedit が使えます。
どちらもシンプルですが機能的なテキストエディタです。
macOS では、デフォルトのテキストエディットアプリに注意してください。_フォーマット_ メニューから _標準テキストにする_ を選択しない限り、プレーンテキストとして保存されません。

[Sublime Text](https://www.sublimetext.com/) や [VS Code](https://code.visualstudio.com/) のような専用のテキストエディタをダウンロードしてインストールすることもできます。これらのプログラムはコードを編集するために特別に作成されているため、これはプラットフォームに関係なくベストな方法です。

?> どのエディタを使えば良いか分からない場合、Laurence Bradford が書いたこの記事 [a great introduction](https://learntocodewith.me/programming/basics/text-editors/) を読んでください。

### QMK Toolbox

QMK Toolbox は、Windows と macOS で使える GUI を備えたプログラムで、カスタムキーボードのプログラミングとデバッグの両方ができます。
このプログラムは、キーボードに簡単にファームウェアを書き込んだり、出力されるデバッグメッセージを確認する際に、かけがえのないものであることがわかるでしょう。

[QMK Toolbox の最新版](https://github.com/qmk/qmk_toolbox/releases/latest)

* Windows 版: `qmk_toolbox.exe` (portable) または `qmk_toolbox_install.exe` (installer)
* macOS 版: `QMK.Toolbox.app.zip` (portable) または `QMK.Toolbox.pkg` (installer)

## 環境構築 :id=set-up-your-environment

私たちは、QMK を可能な限り簡単に構築できるように努力しています。
Linux か Unix 環境を用意するだけで、QMK に残りをインストールさせることができます。

?> もし、Linux か Unix のコマンドを使ったことがない場合、こちらで基本的な概念や各種コマンドを学んでください。これらの教材で QMK を使うのに必要なことを学ぶことができます。

[Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)<br>
[Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

MSYS2 と Git のインストールが必要です。

* [MSYS2 homepage](http://www.msys2.org) の手順に従って MSYS2 をインストールします。
* 開いている MSYS2 の全ターミナル画面を閉じて、新しい MSYS2 MinGW 64-bit のターミナル画面を開きます。
* `pacman -S git` を実行して Git をインストールします。

### macOS

[Homebrew homepage](https://brew.sh) の手順に従って Homebrew をインストールしてください。

Homebrew をインストールしたら、以下の _QMK の設定_ に進んでください。そのステップでは、他のパッケージをインストールするスクリプトを実行します。

### Linux

Git のインストールが必要です。既にインストールされている可能性は高いですが、そうでない場合、次のコマンドでインストールできます。

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch: `pacman -S git`

?> 全てのプラットフォームにおいて、Docker を使うことも可能です。[詳細はこちらをクリックしてください](ja/getting_started_build_tools.md#docker)。

## QMK の設定 :id=set-up-qmk

Linux/Unix 環境が準備できたら QMK のダウンロードの準備は完了です。Git を使用して QMK のリポジトリを「クローン」することで QMK をダウンロードします。ターミナルか MSYS2 MinGW ウィンドウを開いて、このガイドの残りの部分では開いたままにします。そのウィンドウ内で、次の2つのコマンドを実行します。

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

?> 既に [GitHub の使いかた](ja/getting_started_github.md)を知っているなら、clone ではなく fork を勧めます。この一文の意味が分からない場合、このメッセージは無視してかまいません。

QMK には、必要な残りの設定を手助けするスクリプトが含まれています。
セットアップ作業を完了させるため、次のコマンドを実行します。

    util/qmk_install.sh

## ビルド環境の確認

これで QMK のビルド環境が用意できましたので、キーボードのファームウェアをビルドできます。
キーボードのデフォルトキーマップをビルドすることから始めます。次の形式のコマンドでビルドできるはずです。

    make <keyboard>:default

例）Clueboard 66% のファームウェアをビルドする

    make clueboard/66/rev3:default

大量の出力の最後に次のように出力されると完了です。

```
Linking: .build/clueboard_66_rev3_default.elf                                     [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex             [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                      [OK]
Checking file size of clueboard_66_rev3_default.hex                               [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# キーマップの作成

これであなた専用のキーマップを作成する準備ができました！
次は [Building Your First Firmware](ja/newbs_building_firmware.md) で専用のキーマップを作成します。
