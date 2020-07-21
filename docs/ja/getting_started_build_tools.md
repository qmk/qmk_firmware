# ビルドツールのインストール

<!---
  original document: 5a02cc00a:docs/getting_started_build_tools.md
  git diff 5a02cc00a HEAD -- docs/getting_started_build_tools.md | cat
-->

このページは QMK のためのビルド環境のセットアップを説明します。これらの手順は (atmega32u4 のような) AVR プロセッサを対象としてします。

<!-- FIXME: We should have ARM instructions somewhere. -->

**注意:** ここが初めての場合は、[QMK 初心者ガイド](ja/newbs.md)ページを調べてください。

続ける前に、`make git-submodule` を実行して、サブモジュール(サードパーティライブラリ)が最新であることを再確認してください。

## Linux

常に最新の状態を保つためには、単に `sudo util/qmk_install.sh` を実行してください。全ての必要な依存関係が常にインストールされるはずです。**これは `apt-get upgrade` を実行します。**

手動でインストールすることもできますが、このドキュメントは常に全ての要件を満たしているとは限りません。

現在の要件は以下の通りですが、何をしようとしているかによっては全てが必要とは限りません。また、一部のシステムではパッケージとして全ての依存関係が利用できるとは限らず、あるいは名前が異なる場合があるかもしれません。

```
build-essential
gcc
unzip
wget
zip
gcc-avr
binutils-avr
avr-libc
dfu-programmer
dfu-util
gcc-arm-none-eabi
binutils-arm-none-eabi
libnewlib-arm-none-eabi
git
```

好みのパッケージマネージャを使って依存関係をインストールします。

Debian / Ubuntu の例:

    sudo apt-get update
    sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi

Fedora / Red Hat の例:

    sudo dnf install gcc unzip wget zip dfu-util dfu-programmer avr-gcc avr-libc binutils-avr32-linux-gnu arm-none-eabi-gcc-cs arm-none-eabi-binutils-cs arm-none-eabi-newlib

Arch / Manjaro の例:

    pacman -S base-devel gcc unzip wget zip avr-gcc avr-binutils avr-libc dfu-util arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib git dfu-programmer dfu-util

## Nix

[NixOS](https://nixos.org/) の場合、あるいは Linux または MacOS に Nix をインストールした場合は、ビルド環境を取得するためにリポジトリのルートで `nix-shell` を実行します。

デフォルトでは、これは AVR と ARM の両方のためのコンパイラをダウンロードします。両方が必要ではない場合は、`avr` あるいは `arm` 引数を無効にします。例えば:

    nix-shell --arg arm false

## macOS
[Homebrew](http://brew.sh/) を使っている場合は、以下のコマンドを使うことができます:

    brew tap osx-cross/avr
    brew tap osx-cross/arm
    brew update
    brew install avr-gcc@8
    brew link --force avr-gcc@8
    brew install dfu-programmer
    brew install dfu-util
    brew install arm-gcc-bin@8
    brew link --force arm-gcc-bin@8
    brew install avrdude

これはお勧めの方法です。homebrew が無い場合は、[インストールしてください！](http://brew.sh/) コマンドラインで作業する人にとってとても価値があります。`avr-gcc@8` の homebrew でのインストール中、`make` と `make install` 部分は20分以上かかり、CPU使用率が高くなることに注意してください。

## msys2 を使った Windows (推奨) :id=windows-with-msys2-recommended

Windows Vista 以降のバージョン(7および10でテスト済み)について、使用するのに最適な環境は [msys2](http://www.msys2.org) です。

* msys2 をダウンロードし、こちらの指示に従ってインストールしてください: http://www.msys2.org
* ``MSYS2 MingGW 64-bit`` のショートカットを開きます
* QMK リポジトリに移動します。例えば、c ドライブのルートにある場合:
* `$ cd /c/qmk_firmware`
* `util/qmk_install.sh` を実行し、指示に従います

## Windows 10 (非推奨)
Windows 10 の古い手順です。[上記の概要のように MSYS2](#windows-with-msys2-recommended) を使うことをお勧めします。

### Creators Update
Creators Update 以降の Windows 10 の場合、ファームウェアを直接ビルドして書き込むことができます。Creators Update の前は、ビルドだけが可能でした。まだそうではないか、不明な場合は、[これらの指示](https://support.microsoft.com/en-us/instantanswers/d4efb316-79f0-1aa1-9ef3-dcada78f3fa0/get-the-windows-10-creators-update)に従ってください。

### Linux 用の Windows Subsystem
Creators Update に加えて、Linux 用の Windows 10 Subystem が必要ですので、[これらの指示](http://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/)に従ってインストールしてください。Anniversary update からの Linux 用の Windows 10 Subsystem が既にある場合、一部のキーボードは 14.04LTS に含まれるツールチェーンを使ってコンパイルしないため、16.04LTS に[アップグレード](https://betanews.com/2017/04/14/upgrade-windows-subsystem-for-linux/)することをお勧めします。`sudo do-release-upgrade` メソッドを選択した場合は、自分が何をしているかを知る必要があることに注意してください。

### Git
すでに Windows ファイルシステムにリポジトリをクローンしている場合は、この章を無視することができます。

WSL Git では**なく**、Windows 用の通常の Git を使って Windows ファイルシステムにリポジトリをクローンする必要があります。以前に Git をインストールしたことが無ければ、[ダウンロード](https://git-scm.com/download/win)し、インストールしてください。次に[セットアップします](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup)。特に貢献する予定がある場合は、eメールとユーザ名をセットアップすることが重要です。

Git がインストールされたら、Git Bash コマンドを開き、QMK をクローンしたい場所へディレクトリを変更します: スラッシュを使う必要があり、c ドライブは `/c/path/to/where/you/want/to/go` のようにアクセスされることに注意してください。次に、`git clone --recurse-submodules https://github.com/qmk/qmk_firmware` を実行します。これは現在のフォルダのサブディレクトリとして新しいフォルダ `qmk_firmware` を作成します。

### ツールチェーンのセットアップ
ツールチェーンのセットアップは Linux 用の Windows サブシステムを介して行われ、手順は完全に自動化されています。全てを手動で行いたい場合は、スクリプト以外の手順はありませんが、常に issue を開いて詳細情報を求めることができます。

1. スタートメニューから "Bash On Ubuntu On Windows" を開いてください。
2. クローンした `qmk_firmware` ディレクトリに移動します。パスは WSL 内で `/mnt/` から始まることに注意してください。つまり、例えば `cd /mnt/c/path/to/qmk_firmware` と書く必要があります。
3. `util/wsl_install.sh` を実行し、画面上の手順に従います。
4. Bash コマンドウィンドウを閉じ、再び開きます。
5. ファームウェアをコンパイルし書き込む準備ができました！

### 心に留めておくべき幾つかの重要なこと
* 全ての最新の更新を取得するために `util/wsl_install.sh` を再実行することができます。
* WSL は外部で実行可能ファイルを実行できないため、QMK リポジトリは Windows ファイルシステム上にある必要があります。
* WSL Git は Windows の Git と互換性が**無い**ため、全ての Git 操作には、Windows Git Bash あるいは windows Git GUI を使ってください。
* WSL 内あるいは普通に Windows を使ってファイルを編集できますが、makefile あるいはシェルスクリプトを編集する場合は、行末をUnix形式にしてファイルを保存するエディタを使うようにしてください。そうでなければコンパイルは機能しないかもしれません。

## Docker

これが少し複雑な場合は、Docker があなたが必要とするすぐに使える解決法かもしれません。[Docker CE](https://docs.docker.com/install/#supported-platforms) をインストールした後で、キーボード/キーマップをビルドするために `qmk_firmware` ディレクトリから以下のコマンドを実行します:
```bash
util/docker_build.sh keyboard:keymap
# 例えば: util/docker_build.sh ergodox_ez:steno
```
これは目的のキーボード/キーマップをコンパイルし、結果として書き込み用に `.hex` あるいは `.bin` ファイルを QMK ディレクトリの中に残します。`:keymap` が省略された場合は全てのキーマップが使われます。パラメータの形式は、`make` を使ってビルドする時と同じであることに注意してください。

スクリプトをパラメータ無しで開始することもできます。この場合、1つずつビルドパラメータを入力するように求められます。これが使いやすいと思うかもしれません:
```bash
util/docker_build.sh
# パラメータを入力として読み込みます (空白にすると全てのキーボード/キーマップ)
```

`target` を指定することで Docker から直接キーボードをビルドし_かつ_書き込むためのサポートもあります。
```bash
util/docker_build.sh keyboard:keymap:target
# 例えば: util/docker_build.sh planck/rev6:default:flash
```
Linux を使っている場合は、これはそのままで動作するはずです。Windows と macOS では、実行するのに [Docker Machine](http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos/) が必要です。これはセットアップが面倒なので、お勧めではありません: 代わりに [QMK Toolbox](https://github.com/qmk/qmk_toolbox) を使ってください。

!> Docker for Windows は[Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v) を有効にする必要があります。これは、Windows 7、Windows 8 および **Windows 10 Home** のような Hyper-V を搭載していない Windows のバージョンでは機能しないことを意味します。

## Vagrant
ファームウェアをビルドするのに問題がある場合は、Vagrant と呼ばれるツールを試してみることができます。それは、ファームウェアをビルドする準備ができた既知の構成を搭載した仮想コンピュータをセットアップします。OLKB はこの仮想コンピュータのためのファイルをホストしません。Vagrant をセットアップする方法の詳細は、[vagrant ガイド](ja/getting_started_vagrant.md)にあります。
