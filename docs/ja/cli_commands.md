# QMK CLI コマンド

<!---
  original document: 0.9.19:docs/cli_command.md
  git diff 0.9.19 HEAD -- docs/cli_command.md | cat
-->

# ユーザー用コマンド

## `qmk compile`

このコマンドにより、任意のディレクトリからファームウェアをコンパイルすることができます。<https://config.qmk.fm> からエクスポートした JSON をコンパイルするか、リポジトリ内でキーマップをコンパイルするか、現在の作業ディレクトリでキーボードをコンパイルすることができます。

このコマンドはディレクトリを認識します。キーボードやキーマップのディレクトリにいる場合、自動的に KEYBOARD や KEYMAP を入力します。

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

**指定したキーマップをサポートする全てのキーボードをビルドする場合の使い方**:

```
qmk compile -kb all -km <keymap_name>
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
Ψ Compiling keymap with make gh60/satan:colemak
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
違うブートローダを指定するには、`-bl <bootloader>` を使ってください。利用可能なブートローダの詳細については、[ファームウェアを書き込む](ja/flashing.md)を見てください。

このコマンドはディレクトリを認識します。キーボードやキーマップのディレクトリにいる場合、自動的に KEYBOARD や KEYMAP を入力します。

**Configurator Exports での使い方**:

```
qmk flash <configuratorExport.json> -bl <bootloader>
```

**キーマップでの使い方**:

```
qmk flash -kb <keyboard_name> -km <keymap_name> -bl <bootloader>
```

**ブートローダの列挙**

```
qmk flash -b
```

## `qmk config`

このコマンドにより QMK の挙動を設定することができます。完全な `qmk config` のドキュメントについては、[CLI 設定](ja/cli_configuration.md)を見てください。

**使用法**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
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

## `qmk info`

QMK のキーボードやキーマップに関する情報を表示します。キーボードに関する情報を取得したり、レイアウトを表示したり、基礎となるキーマトリックスを表示したり、JSON キーマップをきれいに印刷したりするのに使用できます。

**使用法**:

```
qmk info [-f FORMAT] [-m] [-l] [-km KEYMAP] [-kb KEYBOARD]
```

このコマンドはディレクトリを認識します。キーボードやキーマップのディレクトリにいる場合、自動的に KEYBOARD や KEYMAP を入力します。

**例**:

キーボードの基本情報を表示する:

    qmk info -kb planck/rev5

キーボードのマトリクスを表示する:

    qmk info -kb ergodox_ez -m

キーボードの JSON キーマップを表示する:

    qmk info -kb clueboard/california -km default

## `qmk json2c`

QMK Configurator からエクスポートしたものから keymap.c を生成します。

**使用法**:

```
qmk json2c [-o OUTPUT] filename
```

## `qmk list-keyboards`

このコマンドは現在 `qmk_firmware` で定義されている全てのキーボードを列挙します。

**使用法**:

```
qmk list-keyboards
```

## `qmk list-keymaps`

このコマンドは指定されたキーボード(とリビジョン)の全てのキーマップを列挙します。

このコマンドはディレクトリを認識します。キーボードのディレクトリにいる場合、自動的に KEYBOARD を入力します。

**使用法**:

```
qmk list-keymaps -kb planck/ez
```

## `qmk new-keymap`

このコマンドは、キーボードの既存のデフォルトのキーマップに基づいて新しいキーマップを作成します。

このコマンドはディレクトリを認識します。キーボードやキーマップのディレクトリにいる場合、自動的に KEYBOARD や KEYMAP を入力します。

**使用法**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

---

# 開発者用コマンド

## `qmk format-c`

このコマンドは clang-format を使って C コードを整形します。

引数無しで実行すると、変更された全てのコアコードを整形します。デフォルトでは `git diff` で `origin/master` をチェックし、ブランチは `-b <branch_name>` を使って変更できます。

`-a` で全てのコアコードを整形するか、コマンドラインでファイル名を渡して特定のファイルに対して実行します。

**指定したファイルに対する使い方**:

```
qmk format-c [file1] [file2] [...] [fileN]
```

**全てのコアファイルに対する使い方**:

```
qmk format-c -a
```

**origin/master で変更されたファイルのみに対する使い方**:

```
qmk format-c
```

**branch_name で変更されたファイルのみに対する使い方**:

```
qmk format-c -b branch_name
```

## `qmk docs`

このコマンドは、ドキュメントを参照または改善するために使うことができるローカル HTTP サーバを起動します。デフォルトのポートは 8936 です。

**使用法**:

```
qmk docs [-p PORT]
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

## `qmk format-py`

このコマンドは `qmk_firmware` 内の python コードを整形します。

**使用法**:

```
qmk format-py
```

## `qmk pytest`

このコマンドは python のテストスィートを実行します。python コードに変更を加えた場合、これの実行が成功することを確認する必要があります。

**使用法**:

```
qmk pytest
```
