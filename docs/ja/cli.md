# QMK CLI

このページはQMK CLIをセットアップおよび使う方法について説明します。

# 概要

QMK CLI はQMKキーボードの構築と操作が簡単になります。QMKファームウェアの取得とコンパイル、キーマップの作成などのようなタスクを簡単に合理化するためのコマンドを多く提供します。

* [グローバル CLI](#global-cli)
* [ローカル CLI](#local-cli)
* [CLI コマンド](#cli-commands)

# 必要条件

CLI はPython 3.5以上を必要とします必要条件の数を少なくしようとしていますが、[`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt)にリストされているパッケージもインストールする必要があります。

# グローバル CLI

QMKは、QMKビルド環境のセットアップ、QMKの操作、および`qmk_firmware`の複数のコピーの操作を容易にできるインストール可能なCLIを提供します。これを定期的にインストールおよび更新することをお勧めします。

## Homebrewを使ったインスト―ル (macOS, some Linux)

[Homebrew](https://brew.sh)をインストールしている場合は、タップしてQMKをインストールすることができます:

```
brew tap qmk/qmk
brew install qmk
export QMK_HOME='~/qmk_firmware' # Optional, set the location for `qmk_firmware`
qmk setup  # This will clone `qmk/qmk_firmware` and optionally set up your build environment
```

## easy_install あるいは pip を使ってインストール

システムが上記にリストされていない場合は、QMKを手動でインストールすることができます。最初に、python 3.5 (以降)をインストールしていて、pipをインストールされていることを確認してください。次に以下のコマンドを使ってQMKをインストールします:

```
pip3 install qmk
export QMK_HOME='~/qmk_firmware' # Optional, set the location for `qmk_firmware`
qmk setup  # This will clone `qmk/qmk_firmware` and optionally set up your build environment
```

## 他のオペレーティングシステムのためのパッケージ化

より多くのオペレーティングシステム用に`qmk` パッケージをさくせいおよび保守する人を探しています。OS用のパッケージを作成する場合は、以下のガイドラインに従ってください:

* これらのガイドラインと矛盾する場合は、OSのベストプラクティスに従ってください
   * 逸脱する場合は、理由をコメントに文章化してください。
* virtualenv を使ったインストール
* 環境変数 `QMK_HOME` を設定して、ファームウェアソースを`~/qmk_firmware`以外のどこかにチェックアウトするようにユーザに指示します。

# ローカルCLI

グローバル CLIを使いたくない場合は、`qmk_firmware` に同梱されたローカルCLIがあります。`qmk_firmware/bin/qmk`で見つけることができます。任意のディレクトリから `qmk` コマンドを実行でき、常に `qmk_firmware` のコピー上で動作します。

**例**:

```
$ ~/qmk_firmware/bin/qmk hello
Ψ Hello, World!
```

## ローカル CLI の制限

グローバル CLI と比較して、ローカル CLI には幾つかの制限があります:

* ローカルCLIは `qmk setup` あるいは `qmk clone` をサポートしません。
* 複数のリポジトリがクローンっされている場合でも、ローカル CLI は常に `qmk_firmware` ツリー上で動作します。
* ローカル CLI は virtualenv で動作しません。そのため依存関係が競合する可能性があります

# CLI コマンド

## `qmk compile`

このコマンドにより、任意のディレクトリからファームウェアをコンパイルすることができます。JSON export を<https://config.qmk.fm> からコンパイルするか、レポジトリ内でキーマップをコンパイルすることができます。

**Configurator Exports の使用法**:

```
qmk compile <configuratorExport.json>
```

**Keymaps の使い方**:

```
qmk compile -kb <keyboard_name> -km <keymap_name>
```

## `qmk cformat`

このコマンドは clang-format を使って C コードを整形します。全てのコア コードを整形するために引数無しで実行するか、特定のファイル上で実行するためにコマンドライン上でファイル名を渡します。

**使用法**:

```
qmk cformat [file1] [file2] [...] [fileN]
```

## `qmk config`

このコマンドによりQMKの挙動を設定することができます完全な`qmk config`ドキュメントについては、[CLI 設定](cli_configuration.md)を見てください。

**使用法**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk docs`

このコマンドは、ドキュメントを参照または改善するために使うことができるローカルHTTPサーバを起動します。デフォルトのポートは 8936 です。

**使用法**:

```
qmk docs [-p PORT]
```

## `qmk doctor`

このコマンドは環境を調査し、潜在的なビルドあるいはフラッシュの問題について警告します。

**使用法**:

```
qmk doctor
```

## `qmk list_keyboards`

このコマンドは現在 `qmk_firmware` で定義されている全てのキーボードをリスト化します。

**使用法**:

```
qmk list_keyboards
```

## `qmk new-keymap`

このコマンドは、キーボードの既存のデフォルトのキーマップに基づいて新しいキーマップを作成します。

**使用法**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk pyformat`

このコマンドは`qmk_firmware`内のpythonコードを整形します。

**使用法**:

```
qmk pyformat
```

## `qmk pytest`

このコマンドはpythonのテストスィートを実行します。pythonコードに変更を加えた場合、これの実行が成功することを確認する必要があります。

**使用法**:

```
qmk pytest
```
