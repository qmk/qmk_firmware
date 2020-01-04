# QMK CLI 設定

<!---
  original document: d598f01cb:docs/cli_configuration.md
  git diff d598f01cb HEAD -- docs/cli_configuration.md | cat
-->

このドキュメントは `qmk config` がどのように動作するかを説明します。

# はじめに

QMK CLI の設定はキーバリューシステムです。各キーはピリオドで区切られたサブコマンドと引数名で構成されます。これにより、設定キーと設定された引数の間で簡単かつ直接的な変換が可能になります。

## 簡単な例

例として、`qmk compile --keyboard clueboard/66/rev4 --keymap default` コマンドを見てみましょう。

設定から読み取ることができる2つのコマンドライン引数があります:

* `compile.keyboard`
* `compile.keymap`

これらを設定してみましょう:

```
$ qmk config compile.keyboard=clueboard/66/rev4 compile.keymap=default
compile.keyboard: None -> clueboard/66/rev4
compile.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

これで、毎回キーボードとキーマップを設定することなく、`qmk compile` を実行することができます。

## ユーザデフォルトの設定

複数のコマンド間で設定を共有したい場合があります。例えば、いくつかのコマンドは引数 `--keyboard` を受け取ります。全てのコマンドでこの値を設定する代わりに、その引数を受け取る全てのコマンドで使われるユーザ値を設定することができます。

例:

```
$ qmk config user.keyboard=clueboard/66/rev4 user.keymap=default
user.keyboard: None -> clueboard/66/rev4
user.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# CLI ドキュメント (`qmk config`)

`qmk config` コマンドは基礎となる設定とやり取りするために使われます。引数無しで実行すると、現在の設定を表示します。引数が指定された場合、それらは設定トークンと見なされます。設定トークンは以下の形式の空白を含まない文字列です:

    <subcommand|general|default>[.<key>][=<value>]

## 設定値の設定

設定キーに等号 (=) を入れることで、設定値を設定することができます。キーは常に完全な `<section>.<key>` 形式である必要があります。

例:

```
$ qmk config default.keymap=default
default.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## 設定値の読み込み

設定全体、単一のキー、あるいはセクション全体の設定値を読み取ることができます。1つ以上の値を表示するために複数のキーを指定することができます。

### 全体の構成例

    qmk config

### セクション全体の例

    qmk config compile

### 単一キーの例

    qmk config compile.keyboard

### 複数キーの例

    qmk config user compile.keyboard compile.keymap

## 設定値の削除

設定値を特別な文字列 `None` に設定することで、設定値を削除することができます。

例:

```
$ qmk config default.keymap=None
default.keymap: default -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## 複数の操作

複数の読み込みおよび書き込み操作を1つのコマンドに組み合わせることができます。それらは順番に実行および表示されます:

```
$ qmk config compile default.keymap=default compile.keymap=None
compile.keymap=skully
compile.keyboard=clueboard/66_hotswap/gen1
default.keymap: None -> default
compile.keymap: skully -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# ユーザ設定オプション

| キー | デフォルト値 | 説明 |
|-----|---------------|-------------|
| user.keyboard | None | キーボードのパス (例: `clueboard/66/rev4`) |
| user.keymap | None | キーマップ名 (例: `default`) |
| user.name | None | ユーザの github のユーザ名。 |

# 全ての設定オプション

| キー | デフォルト値 | 説明 |
|-----|---------------|-------------|
| compile.keyboard | None | キーボードのパス (例: `clueboard/66/rev4`) |
| compile.keymap | None | キーマップ名 (例: `default`) |
| hello.name | None | 実行時の挨拶の名前 |
| new_keyboard.keyboard | None | キーボードのパス (例: `clueboard/66/rev4`) |
| new_keyboard.keymap | None | キーマップ名 (例: `default`) |
