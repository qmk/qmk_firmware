# QMK CLI 開発

<!---
  original document: 0.9.19:docs/cli_development.md
  git diff 0.9.19 HEAD -- docs/cli_development.md | cat
-->

このドキュメントは、新しい `qmk`  サブコマンドを書きたい開発者に役立つ情報が含まれています。

# 概要

QMK CLI は git で有名になったサブコマンドパターンを使って動作します。メインの `qmk` スクリプトは単に環境をセットアップし、実行する正しいエントリポイントを選択するためにあります。各サブコマンドは、何らかのアクションを実行しシェルのリターンコード、または None を返すエントリーポイント (`@cli.subcommand()` で修飾されます)を備えた自己完結型のモジュールです。

## 開発者モード:

キーボードを保守、あるいは QMK に貢献したい場合は、CLI の「開発者」モードを有効にすることができます:

`qmk config user.developer=True`

これにより利用可能な全てのサブコマンドが表示されます。
**注意:** 追加で必要なものをインストールする必要があります:
```bash
python3 -m pip install -r requirements-dev.txt
```

# サブコマンド

[MILC](https://github.com/clueboard/milc) は、`qmk` が引数の解析、設定、ログ、およびほかの多くの機能を処理するために使用する CLI フレームワークです。グルーコードを書くために時間を無駄にすることなく、ツールの作成に集中できます。

ローカル CLI 内のサブコマンドは、常に `qmk_firmware/lib/python/qmk/cli` で見つかります。

サブコマンドの例を見てみましょう。これは `lib/python/qmk/cli/hello.py` です:

```python
"""QMK Python Hello World

This is an example QMK CLI script.
"""
from milc import cli


@cli.argument('-n', '--name', default='World', help='Name to greet.')
@cli.subcommand('QMK Hello World.')
def hello(cli):
    """Log a friendly greeting.
    """
    cli.log.info('Hello, %s!', cli.config.hello.name)
```

最初に `milc` から `cli` をインポートします。これが、ユーザとやり取りをし、スクリプトの挙動を制御する方法です。`@cli.argument()` を使って、コマンドラインフラグ `--name` を定義します。これは、ユーザが設定できる `hello.name` (そして対応する `user.name`) という名前の設定変数も作成し、引数を指定する必要が無くなります。`cli.subcommand()` デコレータは、この関数をサブコマンドとして指定します。サブコマンドの名前は関数の名前から取られます。

関数の中に入ると、典型的な "Hello, World!" プログラムが見つかります。`cli.log` を使って、基礎となる [ロガーオブジェクト](https://docs.python.org/3.6/library/logging.html#logger-objects) にアクセスし、その挙動はユーザが制御できます。またユーザが指定した名前の値に `cli.config.hello.name` でアクセスします。`cli.config.hello.name` の値は、ユーザが指定した `--name` 引数を調べることで決定されます。指定されていない場合、`qmk.ini` 設定ファイルの中の値が使われ、どちらも指定されていない場合は `cli.argument()`  デコレータで指定されたデフォルトが代用されます。

# ユーザとの対話処理

MILC と QMK CLI にはユーザとやり取りするための幾つかの便利なツールがあります。これらの標準ツールを使うと、テキストに色を付けて対話し易くし、ユーザはその情報をいつどのように表示および保存するかを制御することができます。

## テキストの表示

サブコマンド内でテキストを出力するための2つの主な方法があります- `cli.log` と `cli.echo()`。それらは似た方法で動作しますが、ほとんどの一般的な目的の出力には `cli.log.info()` を使うことをお勧めします。

特別なトークンを使用してテキストを色付けし、プログラムの出力を理解しやすくすることができます。以下の[テキストの色付け](#colorizing-text)を見てください。

これらの両方の方法は python の [printf 形式の文字列書式化](https://docs.python.org/3.6/library/stdtypes.html#old-string-formatting) を使った組み込みの文字列書式化をサポートします。テキスト文字列内で`%s` と `%d` のようなトークンを使い、引数で値を渡すことができます。例として、上記の Hello、World プログラムを見てください。

書式演算子 (`%`) を直接使わないでください、常に引数で値を渡します。

### ログ (`cli.log`)

`cli.log` オブジェクトは[ロガーオブジェクト](https://docs.python.org/3.6/library/logging.html#logger-objects)へのアクセスを与えます。ログ出力を設定し、ユーザに各ログレベルの素敵な絵文字(またはターミナルが unicode をサポートしない場合はログレベル名)を表示します。このようにして、ユーザは何か問題が発生した時に最も重要なメッセージを一目で確認することができます。

デフォルトのログレベルは `INFO` です。ユーザが `qmk -v <subcommand>` を実行すると、デフォルトのログレベルは `DEBUG` に設定されます。

| 関数 | 絵文字 |
|----------|-------|
| cli.log.critical | `{bg_red}{fg_white}¬_¬{style_reset_all}` |
| cli.log.error | `{fg_red}☒{style_reset_all}` |
| cli.log.warning | `{fg_yellow}⚠{style_reset_all}` |
| cli.log.info | `{fg_blue}Ψ{style_reset_all}` |
| cli.log.debug | `{fg_cyan}☐{style_reset_all}` |
| cli.log.notset | `{style_reset_all}¯\\_(o_o)_/¯` |

### 出力 (`cli.echo`)

場合によっては単にログシステムの外部でテキストを出力する必要があります。これは、固定データを出力したり、ログに記録してはいけない何かを書きだす場合に適しています。ほとんどの場合、`cli.echo` よりも `cli.log.info()` を選ぶべきです。

### テキストの色付け

テキスト内に色トークンを含めることで、テキストの出力を色付けすることができます。情報を伝えるためではなく、強調するために色を使います。ユーザは色を無効にできることを覚えておいてください。色を無効にした場合でもサブコマンドは引き続き使えるようにしてください。

背景色を設定するのは、あなたがやっていることに不可欠ではない限り、通常は避けるべきです。ユーザは、ターミナルの色に関しては多くの好みを持つため、あなたは黒と白のどちらの背景に対してもうまく機能する色を選択する必要があることを覚えておいてください。

'fg' という接頭辞の付いた色は、前景(テキスト)色に影響します。'bg' という接頭辞の付いた色は、背景色に影響します。

| 色 | 背景 | 拡張背景 | 前景 | 拡張前景 |
|-------|------------|---------------------|------------|--------------------|
| 黒 | {bg_black} | {bg_lightblack_ex} | {fg_black} | {fg_lightblack_ex} |
| 青 | {bg_blue} | {bg_lightblue_ex} | {fg_blue} | {fg_lightblue_ex} |
| シアン | {bg_cyan} | {bg_lightcyan_ex} | {fg_cyan} | {fg_lightcyan_ex} |
| 緑 | {bg_green} | {bg_lightgreen_ex} | {fg_green} | {fg_lightgreen_ex} |
| マゼンタ | {bg_magenta} | {bg_lightmagenta_ex} | {fg_magenta} | {fg_lightmagenta_ex} |
| 赤 | {bg_red} | {bg_lightred_ex} | {fg_red} | {fg_lightred_ex} |
| 白 | {bg_white} | {bg_lightwhite_ex} | {fg_white} | {fg_lightwhite_ex} |
| 黄 | {bg_yellow} | {bg_lightyellow_ex} | {fg_yellow} | {fg_lightyellow_ex} |

ANSI 出力の挙動を変更するために使うことができる制御シーケンスもあります。

| 制御シーケンス | 説明 |
|-------------------|-------------|
| {style_bright} | テキストを明るくする |
| {style_dim} | テキストを暗くする |
| {style_normal} | テキストを通常にする (`{style_bright}` または `{style_dim}` のどちらでもない) |
| {style_reset_all} | 全てのテキストの属性をデフォルトに再設定する(これは自動的に全ての文字列の最後に自動的に追加されます。) |
| {bg_reset} | 背景色をユーザのデフォルトに再設定します。 |
| {fg_reset} | 背景色をユーザのデフォルトに再設定します。 |

# 引数と設定

QMK は引数の解析と設定の詳細をあなたの代わりに処理します。新しい引数を追加すると、サブコマンドの名前と引数の長い名前に基づいて設定ツリーに自動的に組み込まれます。属性形式のアクセス (`cli.config.<subcommand>.<argument>`) あるいは辞書形式のアクセス (`cli.config['<subcommand>']['<argument>']`) を使って、`cli.config` 内のこの設定にアクセスすることができます。

内部では、QMK は [設定ファイルのパーサ](https://docs.python.org/3/library/configparser.html) を使って設定を格納します。これにより、人間が編集可能な方法で設定を表す簡単で分かり易い方法を提供します。この設定へのアクセスをラップして、設定ファイルのパーサーが通常持たない幾つかの機能を提供しています。

## 設定値の読み込み

通常期待される全ての方法で `cli.config` とやり取りすることができます。例えば、`qmk compile` コマンドは `cli.config.compile.keyboard` からキーボード名を取得します。値がコマンドライン、環境変数あるいは設定ファイルからきたものであるかどうかを知る必要はありません。

繰り返しもサポートされます:

```
for section in cli.config:
    for key in cli.config[section]:
        cli.log.info('%s.%s: %s', section, key, cli.config[section][key])
```

## 設定値の設定

通常の方法で設定値を設定することができます。

辞書形式:

```
cli.config['<section>']['<key>'] = <value>
```

属性形式:

```
cli.config.<section>.<key> = <value>
```

## 設定値の削除

通常の方法で設定値を削除することができます。

辞書形式:

```
del(cli.config['<section>']['<key>'])
```

属性形式:

```
del(cli.config.<section>.<key>)
```

## 設定ファイルの書き方

設定は変更しても書き出されません。ほとんどのコマンドでこれをする必要はありません。ユーザに `qmk config` を使って設定を慎重に変更させることをお勧めします。

設定を書き出すために `cli.save_config()` を使うことができます。

## 設定からの引数の除外

一部の引数は設定ファイルに反映すべきではありません。これらは引数を作成する時に `arg_only=True` を追加することで除外することができます。

例:

```
@cli.argument('-o', '--output', arg_only=True, help='File to write to')
@cli.argument('filename', arg_only=True, help='Configurator JSON file')
@cli.subcommand('Create a keymap.c from a QMK Configurator export.')
def json_keymap(cli):
    pass
```

`cli.args` を使ってのみこれらの引数にアクセスすることができます。例えば:

```
cli.log.info('Reading from %s and writing to %s', cli.args.filename, cli.args.output)
```

# テスト、リントおよびフォーマット

nose2、flake8 および yapf を使ってコードをテスト、リントおよびフォーマットします。これらのテストを実行するために `pytest` と `format-py` サブコマンドを使うことができます。

### テストとリント

    qmk pytest

### フォーマット

    qmk format-py

## フォーマットの詳細

[yapf](https://github.com/google/yapf) を使ってコードを自動的にフォーマットします。フォーマットの設定は `setup.cfg` の `[yapf]` セクションにあります。

?> ヒント- 多くのエディタは yapf をプラグインとして使って、入力したコードを自動的にフォーマットすることができます。

## テストの詳細

テストは `lib/python/qmk/tests/` にあります。このディレクトリに単体テストと統合テストの両方があります。コードの単体テストと統合テストの両方を書いてほしいですが、一方のみ書く場合は統合テストを優先してください。

PR にテストの包括的なセットが含まれない場合は、次のようなコメントをコードに追加して、他の人が手助けできるようにしてください:

    # TODO(unassigned/<your_github_username>): Write <unit|integration> tests

[nose2](https://nose2.readthedocs.io/en/latest/getting_started.html) を使ってテストを実行します。テスト関数でできることの詳細については、nose2  のドキュメントを参照してください。

## リントの詳細

flake8 を使ってコードをリントします。PR を開く前に、コードは flake8 をパスしなければなりません。これは `qmk pytest` を実行するときにチェックされ、PR を登録したときに CI によってチェックされます。
