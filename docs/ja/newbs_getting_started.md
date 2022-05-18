# QMK 環境の構築

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.13.20:docs/newbs_getting_started.md
  git diff 0.13.20 HEAD -- docs/newbs_getting_started.md | cat
-->

キーマップをビルドする前に、いくつかのソフトウェアをインストールしてビルド環境を構築する必要があります。
ファームウェアをコンパイルするキーボードの数に関わらず、この作業を一度だけ実行する必要があります。

## 1. 前提条件

始めるために必要なソフトウェアがいくつかあります。

* [テキストエディタ](ja/newbs_learn_more_resources.md#text-editor-resources)
  * プレーンテキストファイルを編集して保存できるプログラムが必要です。多くの OS に付属するデフォルトのエディタはプレーンテキストファイルを保存しないため、選択したエディタがプレーンテキストファイルを保存することを確認する必要があります。
* [Toolbox (オプション)](https://github.com/qmk/qmk_toolbox)
  * Windows と macOS で使える GUI を備えたプログラムで、カスタムキーボードのプログラミングとデバッグの両方ができます。

?> もし、Linux か Unix のコマンドを使ったことがない場合、こちらで基本的な概念や各種コマンドを学んでください。[これらの教材](ja/newbs_learn_more_resources.md#command-line-resources)で QMK を使うのに必要なことを学ぶことができます。

## 2. ビルド環境を準備する :id=set-up-your-environment

私たちは、QMK を可能な限り簡単に構築できるように努力しています。Linux か Unix 環境を用意するだけで、QMK に残りをインストールさせることができます。

<!-- tabs:start -->

### ** Windows **

QMK は、MSYS2、CLI、および必要な全ての依存関係のバンドルを保守しています。また、正しい環境で直接起動するための便利な `QMK MSYS` ターミナルショートカットも提供しています。

#### 前提条件

[QMK MSYS](https://msys.qmk.fm/) をインストールする必要があります。最新リリースは[ここ](https://github.com/qmk/qmk_distro_msys/releases/latest)から入手できます。

または、MSYS2 を手動でインストールしたい場合、次のセクションでプロセスを説明します。

<details>
  <summary>手動インストール</summary>

?> `QMK MSYS` を使う場合、次のステップは無視してください。

#### 前提条件

MSYS2 と Git と Python をインストールする必要があります。https://www.msys2.org のインストール手順に従ってください。

MSYS2 をインストールしたら、開いている MSYS の全ターミナル画面を閉じて、新しい MinGW 64-bit ターミナル画面を開きます。

!> **注意:** MinGW 64-bit ターミナルは、インストールが完了した時に開く MSYS ターミナルと*同じではありません*。プロンプトには、「MSYS」ではなく、紫色のテキストで「MINGW64」と表示されます。違いについての詳細は[このページ](https://www.msys2.org/wiki/MSYS2-introduction/#subsystems)を参照してください。

それから、次のように実行します:

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip

#### インストール

次のコマンドを実行して、QMK CLI をインストールします:

    python3 -m pip install qmk

</details>

### ** macOS **

QMK は CLI と全ての必要な依存関係を自動的にインストールする Homebrew tap と formula を保守しています。

#### 前提条件

Homebrew のインストールが必要です。https://brew.sh の手順に従ってください。

#### インストール

次のコマンドを実行して、QMK CLI をインストールします:

    brew install qmk/qmk/qmk

### ** Linux/WSL **

?> **WSL ユーザーへの注意**: デフォルトでは、インストールプロセスは QMK リポジトリを WSL ホームディレクトリに clone しますが、手動で clone した場合、Windows ファイルシステムではなく、WSL インスタンス内にある(つまり `/mnt` 内にない)ことを確認してください。これは、現在アクセスが[非常に遅い](https://github.com/microsoft/WSL/issues/4197)ためです。

#### 前提条件

Git と Python をインストールする必要があります。両方とも既にインストールされている可能性は高いですが、そうでない場合、次のコマンドのいずれかでそれらをインストールできます:

* Debian / Ubuntu / Devuan: `sudo apt install -y git python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum -y install git python3-pip`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git python-pip libffi`
* Void: `sudo xbps-install -y git python3-pip`
* Solus: `sudo eopkg -y install git python3`
* Sabayon: `sudo equo install dev-vcs/git dev-python/pip`
* Gentoo: `sudo emerge dev-vcs/git dev-python/pip`

#### インストール

次のコマンドを実行して、QMK CLI をインストールします:

    python3 -m pip install --user qmk

#### コミュニティパッケージ

これらのパッケージはコミュニティメンバーによって保守されているため、最新ではないか、完全には機能しない可能性があります。問題が発生した場合は、それぞれのメンテナに報告してください。

Arch ベースのディストリビューションでは、公式リポジトリから CLI をインストールできます(注意: 執筆時点では、このパッケージは一部の依存関係をオプションとしてマークしていますが、そうではありません):

    sudo pacman -S qmk

AUR から `qmk-git` パッケージを試すこともできます:

    yay -S qmk-git

###  ** FreeBSD **

#### インストール

次のコマンドを実行して、QMK CLI の FreeBSD パッケージをインストールします:

    pkg install -g "py*-qmk"

注意: インストールの最後に表示された指示に従うことを忘れないでください(再度表示するには、`pkg info -Dg "py*-qmk"` を使ってください)。

<!-- tabs:end -->

## 3. QMK の設定を行う :id=set-up-qmk

<!-- tabs:start -->

### ** Windows **

QMK のインストール後に、このコマンドで設定できます:

    qmk setup

ほとんどの場合、全てのプロンプトに `y` と答えます。

### ** macOS **

QMK のインストール後に、このコマンドで設定できます:

    qmk setup

ほとんどの場合、全てのプロンプトに `y` と答えます。

### ** Linux/WSL **

QMK のインストール後に、このコマンドで設定できます:

    qmk setup

ほとんどの場合、全てのプロンプトに `y` と答えます。

?>**Debian、Ubuntu、それらの派生に関する注意**:
次のようなエラーが表示される可能性があります: `bash: qmk: command not found`.
これは Debian の Bash 4.4 リリースで導入された[バグ](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155)で、`$HOME/.local/bin` が PATH から削除されました。このバグは後に Debian や Ubuntu で修正されました。
残念なことに、Ubuntu はこのバグを再導入し、[まだ修正していません](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562)。
幸い、修正は簡単です。これをあなたのユーザで実行します: `echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc`

###  ** FreeBSD **

QMK のインストール後に、このコマンドで設定できます:

    qmk setup

ほとんどの場合、全てのプロンプトに `y` と答えます。

<!-- tabs:end -->

?> qmk ホームフォルダは、セットアップ時に `qmk setup -H <path>` を使って指定し、[cli 構成](ja/cli_configuration.md?id=single-key-example)と変数 `user.qmk_home` を使って変更できます。利用可能な全てのオプションについては、`qmk setup --help` を実行します。

?> 既に GitHub の使い方を知っている場合、[これらの手順に従うことをお勧めします](ja/getting_started_github.md)。そして `qmk setup <github_username>/qmk_firmware` を使って個人用の fork から clone します。この一文の意味が分からない場合、このメッセージは無視してかまいません。

## 4. ビルド環境の確認

これで QMK のビルド環境が用意できたので、キーボードのファームウェアをビルドできます。キーボードのデフォルトキーマップをビルドすることから始めます。次の形式のコマンドでビルドできるはずです:

    qmk compile -kb <keyboard> -km default

例えば、Clueboard 66% のファームウェアをビルドする場合、次のようにします:

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

これであなた専用のキーマップを作成する準備ができました！次は[初めてのファームウェアの構築](ja/newbs_building_firmware.md)で専用のキーマップを作成します。
