# QMK CLI

<!---
  original document: 79e6b7866:docs/cli.md
  git diff 79e6b7866 HEAD -- docs/cli.md | cat
-->

このページは QMK CLI のセットアップと使用方法について説明します。

# 概要

QMK CLI を使用すると QMK キーボードの構築と作業が簡単になります。QMK ファームウェアの取得とコンパイル、キーマップの作成などのようなタスクを簡素化し合理化するためのコマンドを多く提供します。

* [グローバル CLI](#global-cli)
* [ローカル CLI](#local-cli)
* [CLI コマンド](#cli-commands)

# 必要事項

CLI は Python 3.5 以上を必要とします。我々は必要事項の数を少なくしようとしていますが、[`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt) にリストされているパッケージもインストールする必要があります。

# グローバル CLI :id=global-cli

QMK は、QMK ビルド環境のセットアップ、QMK の操作、および `qmk_firmware` の複数のコピーの操作を容易にできるインストール可能な CLI を提供します。これを定期的にインストールおよび更新することをお勧めします。

## Homebrew を使ったインストール (macOS、いくつかの Linux)

[Homebrew](https://brew.sh) をインストールしている場合は、タップして QMK をインストールすることができます:

```
brew tap qmk/qmk
brew install qmk
export QMK_HOME='~/qmk_firmware' # オプション、`qmk_firmware` の場所を設定します
qmk setup  # これは `qmk/qmk_firmware` をクローンし、オプションでビルド環境をセットアップします
```

## easy_install あるいは pip を使ってインストール

上のリストにあなたのシステムがない場合は、QMK を手動でインストールすることができます。最初に、python 3.5 (以降)をインストールしていて、pip をインストールしていることを確認してください。次に以下のコマンドを使って QMK をインストールします:

```
pip3 install qmk
export QMK_HOME='~/qmk_firmware' # オプション、`qmk_firmware` の場所を設定します
qmk setup  # これは `qmk/qmk_firmware` をクローンし、オプションでビルド環境をセットアップします
```

## 他のオペレーティングシステムのためのパッケージ

より多くのオペレーティングシステム用に `qmk` パッケージを作成および保守する人を探しています。OS 用のパッケージを作成する場合は、以下のガイドラインに従ってください:

* これらのガイドラインと矛盾する場合は、OS のベストプラクティスに従ってください
   * 逸脱する場合は、理由をコメントに文章化してください。
* virtualenv を使ってインストールしてください
* 環境変数 `QMK_HOME` を設定して、ファームウェアソースを `~/qmk_firmware` 以外のどこかにチェックアウトするようにユーザに指示してください。

# ローカル CLI :id=local-cli

グローバル CLI を使いたくない場合は、`qmk_firmware` に付属のローカル CLI があります。`qmk_firmware/bin/qmk` で見つけることができます。任意のディレクトリから `qmk` コマンドを実行でき、常に `qmk_firmware` のコピー上で動作します。

**例**:

```
$ ~/qmk_firmware/bin/qmk hello
Ψ Hello, World!
```

## ローカル CLI の制限

グローバル CLI と比較して、ローカル CLI には幾つかの制限があります:

* ローカル CLI は `qmk setup` あるいは `qmk clone` をサポートしません。
* 複数のリポジトリがクローンされている場合でも、ローカル CLI は常に `qmk_firmware` ツリー上で動作します。
* ローカル CLI は virtualenv で動作しません。そのため依存関係が競合する可能性があります

# CLI コマンド :id=cli-commands

## `qmk cformat`

このコマンドは clang-format を使って C コードを整形します。引数無しで実行して全てのコアコードを整形するか、コマンドラインでファイル名を渡して特定のファイルに対して実行します。

**使用法**:

```
qmk cformat [file1] [file2] [...] [fileN]
```

## `qmk compile`

このコマンドにより、任意のディレクトリからファームウェアをコンパイルすることができます。<https://config.qmk.fm> からエクスポートした JSON をコンパイルするか、リポジトリ内でキーマップをコンパイルするか、現在の作業ディレクトリでキーボードをコンパイルすることができます。

**Configurator Exports での使い方**:

```
qmk compile <configuratorExport.json>
```

**キーマップでの使い方**:

```
qmk compile -kb <keyboard_name> -km <keymap_name>
```

**キーボードディレクトリでの使い方**:  

default キーマップのあるキーボードディレクトリ、キーボードのキーマップディレクトリ、`--keymap <keymap_name>` で与えられるキーマップディレクトリにいなければなりません。
```
qmk compile
```

**例**:
```
$ qmk config compile.keymap=default
$ cd ~/qmk_firmware/keyboards/planck/rev6
$ qmk compile
Ψ Compiling keymap with make planck/rev6:default
...
```
あるいはオプションのキーマップ引数を指定して

```
$ cd ~/qmk_firmware/keyboards/clueboard/66/rev4
$ qmk compile -km 66_iso
Ψ Compiling keymap with make clueboard/66/rev4:66_iso
...
```
あるいはキーマップディレクトリで

```
$ cd ~/qmk_firmware/keyboards/gh60/satan/keymaps/colemak
$ qmk compile
Ψ Compiling keymap with make make gh60/satan:colemak
...
```

**レイアウトディレクトリでの使い方**:  

`qmk_firmware/layouts/` 以下のキーマップディレクトリにいなければなりません。
```
qmk compile -kb <keyboard_name>
```

**例**:
```
$ cd ~/qmk_firmware/layouts/community/60_ansi/mechmerlin-ansi
$ qmk compile -kb dz60
Ψ Compiling keymap with make dz60:mechmerlin-ansi
...
```

## `qmk flash`

このコマンドは `qmk compile` に似ていますが、ブートローダを対象にすることもできます。ブートローダはオプションで、デフォルトでは `:flash` に設定されています。
違うブートローダを指定するには、`-bl <bootloader>` を使ってください。利用可能なブートローダの詳細については、<https://docs.qmk.fm/#/ja/flashing>
を見てください。

**Configurator Exports での使い方**:

```
qmk flash <configuratorExport.json> -bl <bootloader>
```

**キーマップでの使い方**:

```
qmk flash -kb <keyboard_name> -km <keymap_name> -bl <bootloader>
```

**ブートローダのリスト**

```
qmk flash -b
```

## `qmk config`

このコマンドにより QMK の挙動を設定することができます。完全な `qmk config` のドキュメントについては、[CLI 設定](ja/cli_configuration.md)を見てください。

**使用法**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk docs`

このコマンドは、ドキュメントを参照または改善するために使うことができるローカル HTTP サーバを起動します。デフォルトのポートは 8936 です。

**使用法**:

```
qmk docs [-p PORT]
```

## `qmk doctor`

このコマンドは環境を調査し、潜在的なビルドあるいは書き込みの問題について警告します。必要に応じてそれらの多くを修正できます。

**使用法**:

```
qmk doctor [-y] [-n]
```

**例**:

環境に問題がないか確認し、それらを修正するよう促します:

    qmk doctor

環境を確認し、見つかった問題を自動的に修正します:

    qmk doctor -y

環境を確認し、問題のみをレポートします:

    qmk doctor -n

## `qmk json2c`

QMK Configurator からエクスポートしたものから keymap.c を生成します。

**使用法**:

```
qmk json2c [-o OUTPUT] filename
```

## `qmk kle2json`

このコマンドにより、生の KLE データから QMK Configurator の JSON へ変換することができます。絶対パスあるいは現在のディレクトリ内のファイル名のいずれかを受け取ります。デフォルトでは、`info.json` が既に存在している場合は上書きしません。上書きするには、`-f` あるいは `--force` フラグを使ってください。

**使用法**:

```
qmk kle2json [-f] <filename>
```

**例**:

```
$ qmk kle2json kle.txt 
☒ File info.json already exists, use -f or --force to overwrite.
```

```
$ qmk kle2json -f kle.txt -f
Ψ Wrote out to info.json
```

## `qmk list-keyboards`

このコマンドは現在 `qmk_firmware` で定義されている全てのキーボードをリスト化します。

**使用法**:

```
qmk list-keyboards
```

## `qmk list-keymaps`

このコマンドは指定されたキーボード(とリビジョン)の全てのキーマップをリスト化します。

**使用法**:

```
qmk list-keymaps -kb planck/ez
```

## `qmk new-keymap`

このコマンドは、キーボードの既存のデフォルトのキーマップに基づいて新しいキーマップを作成します。

**使用法**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk pyformat`

このコマンドは `qmk_firmware` 内の python コードを整形します。

**使用法**:

```
qmk pyformat
```

## `qmk pytest`

このコマンドは python のテストスィートを実行します。python コードに変更を加えた場合、これの実行が成功することを確認する必要があります。

**使用法**:

```
qmk pytest
```
