# QMK 環境の構築

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.44:docs/newbs_getting_started.md
  git diff 0.9.44 HEAD -- docs/newbs_getting_started.md | cat
-->

キーマップをビルドする前に、いくつかのソフトウェアをインストールしてビルド環境を構築する必要があります。
ファームウェアをコンパイルするキーボードの数に関わらず、この作業を一度だけ実行する必要があります。

## 1. ソフトウェアのダウンロード

始めるために必要なソフトウェアがいくつかあります。

### テキストエディタ

**プレーンテキスト** ファイルを編集して保存できるプログラムが必要です。
Windows の場合、メモ帳が使えます。Linux の場合、gedit が使えます。どちらもシンプルですが機能的なテキストエディタです。
macOS では、デフォルトのテキストエディットアプリに注意してください。_フォーマット_ メニューから _標準テキストにする_ を選択しない限り、プレーンテキストとして保存されません。

[Sublime Text](https://www.sublimetext.com/) や [VS Code](https://code.visualstudio.com/) のような専用のテキストエディタをダウンロードしてインストールすることもできます。これらのプログラムはコードを編集するために特別に作成されているため、これはプラットフォームに関係なくベストな方法です。

?> どのエディタを使えば良いか分からない場合、Laurence Bradford が書いたこの記事 [a great introduction](https://learntocodewith.me/programming/basics/text-editors/) を読んでください。

### QMK Toolbox

QMK Toolbox は、Windows と macOS で使える GUI を備えたプログラムで、カスタムキーボードのプログラミングとデバッグの両方ができます。
このプログラムは、キーボードに簡単にファームウェアを書き込んだり、出力されるデバッグメッセージを確認する際に、かけがえのないものであることがわかるでしょう。

[QMK Toolbox の最新版](https://github.com/qmk/qmk_toolbox/releases/latest)

* Windows 版: `qmk_toolbox.exe` (portable) または `qmk_toolbox_install.exe` (installer)
* macOS 版: `QMK.Toolbox.app.zip` (portable) または `QMK.Toolbox.pkg` (installer)

### Unix ライクな環境

Linux や macOS には既に実行可能な unix シェルが付属しています。ビルド環境を構築するだけで済みます。

Windows では、MSYS2 や WSL をインストールして、これらの環境を使う必要があります。MSYS2 の構築手順を以下に示します。

## 2. ビルド環境を準備する :id=set-up-your-environment

私たちは、QMK を可能な限り簡単に構築できるように努力しています。
Linux か Unix 環境を用意するだけで、QMK に残りをインストールさせることができます。

?> もし、Linux か Unix のコマンドを使ったことがない場合、こちらで基本的な概念や各種コマンドを学んでください。これらの教材で QMK を使うのに必要なことを学ぶことができます:<br>
[Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)<br>
[Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

MSYS2 と Git と QMK CLI のインストールが必要です。

[MSYS2 homepage](http://www.msys2.org) のインストール手順に従ってください。開いている MSYS2 の全ターミナル画面を閉じて、新しい MinGW 64-bit ターミナル画面を開きます。**注意: これはインストールが完了した時に開く MSYS ターミナルと同じ *ではありません*。**

それから、次のように実行します:

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip
    python3 -m pip install qmk

### macOS

Homebrew のインストールが必要です。[Homebrew homepage](https://brew.sh) の手順に従ってください。

Homebrew をインストールした後で、以下のコマンドを実行します:

    brew install qmk/qmk/qmk

### Linux

Git と Python をインストールする必要があります。両方とも既にインストールされている可能性は高いですが、そうでない場合、次のコマンドのいずれかでそれらをインストールできます:

* Debian / Ubuntu / Devuan: `sudo apt install git python3 python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum install git python3 python3-pip`
* Arch / Manjaro: `sudo pacman -S git python python-pip python-setuptools libffi`

グローバル CLI をインストールして、システムをブートストラップします:

`python3 -m pip install --user qmk` (Arch ベースのディストリビューションでは AUR から `qmk` パッケージを試すこともできます(**メモ**: コミュニティメンバーによって保守されています): `yay -S qmk`)

### FreeBSD

Git と Python をインストールする必要があります。両方とも既にインストールされている可能性は高いですが、そうでない場合、次のコマンドを実行してそれらをインストールします:

    pkg install git python3

ローカルにインストールした Python パッケージが利用できるように、`$HOME/.local/bin` が `$PATH` に追加されていることを確認してください。

インストール完了後、QMK CLI をインストールできます:

    python3 -m pip install --user qmk

## 3. QMK の設定を行う :id=set-up-qmk

QMK のインストール後に、このコマンドで設定できます:

    qmk setup

ほとんどの場合、全てのプロンプトに Yes と答えます。

?>**Debian、Ubuntu、それらの派生に関する注意**:
次のようなエラーが表示される可能性があります: `bash: qmk: command not found`.
これは Debian の Bash 4.4 リリースで導入された [バグ](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155) で、`$HOME/.local/bin` が PATH から削除されました。このバグは後に Debian や Ubuntu で修正されました。
残念なことに、Ubuntu はこのバグを再導入し、[まだ修正していません](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562)。
幸い、修正は簡単です。これをあなたのユーザで実行します: `echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc`

?>**FreeBSD に関する注意**:
まず、`root` 以外のユーザで `qmk setup` を実行することをお勧めしますが、これはおそらく `pkg` を使って基本システムにインストールする必要があるパッケージを識別します。
しかし、特権のないユーザで実行すると、インストールはおそらく失敗します。
基本的な依存関係を手動でインストールするには、`./util/qmk_install.sh` を `root` として実行するか、`sudo` をつけて実行します。
それが完了したら、`qmk setup` を再実行して設定と確認を完了させます。

?> 既に [GitHub の使いかた](ja/getting_started_github.md)を知っているなら、fork を作成し、`qmk setup <github_username>/qmk_firmware` を使って個人用の fork から clone することをお勧めします。この一文の意味が分からない場合、このメッセージは無視してかまいません。

## 4. ビルド環境の確認

これで QMK のビルド環境が用意できたので、キーボードのファームウェアをビルドできます。
キーボードのデフォルトキーマップをビルドすることから始めます。次の形式のコマンドでビルドできるはずです。

    qmk compile -kb <keyboard> -km default

例えば、Clueboard 66% のファームウェアをビルドする場合:

    qmk compile -kb clueboard/66/rev3 -km default

大量の出力の最後に次のように出力されると完了です:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

## 5. ビルド環境の設定(オプション)

ビルド環境を設定してデフォルトを設定することで、QMK での作業をあまり面倒くさくないようにすることができます。今からやりましょう！

QMK を初めて使うほとんどの人は、キーボードを1つしか持っていません。`qmk config` コマンドでこのキーボードをデフォルトとして設定できます。例えば、デフォルトのキーボードを `clueboard/66/rev4` に設定するには:

    qmk config user.keyboard=clueboard/66/rev4

デフォルトキーマップ名を設定することもできます。ほとんどの人はここで GitHub ユーザ名を使いますが、そうすることをお勧めします。

    qmk config user.keymap=<github_username>

この後、これらの引数をオフにして、次のようにキーボードをコンパイルできます:

    qmk compile

# キーマップの作成

これであなた専用のキーマップを作成する準備ができました！
次は [初めてのファームウェアの構築](ja/newbs_building_firmware.md) で専用のキーマップを作成します。
