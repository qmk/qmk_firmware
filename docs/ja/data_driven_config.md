# データ駆動型コンフィギュレーション

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.12.7:docs/data_driven_config.md
  git diff 0.12.7 HEAD -- docs/data_driven_config.md | cat
-->

このページでは、QMK のデータ駆動型 JSON コンフィギュレーションシステムがどのように動作するかを説明します。これは、QMK 自体に取り組みたい開発者を対象としています。

## ヒストリー

これまで、QMK は、`rules.mk` と `config.h` の2つのメカニズムを組み合わせてコンフィギュレーションされてきました。
この方法は、QMK がほんの一握りのキーボードをサポートしていたときは上手く機能していましたが、今では、サポートするキーボードは1500近くまで成長しました。
`keyboards` の下だけで6000個の設定ファイルがあることが推定されます。
これらのファイルの自由形式の性質と、重複を避けるために人々が使用してきたユニークなパターンが継続的なメンテナンスを困難にしており、また、多くのキーボードが時代遅れで時には理解が難しいパターンに従っています。

また、CLI に慣れていない人に QMK のパワーを提供することにも取り組んでおり、VIA などの他のプロジェクトでは、プログラムをインストールするのと同じくらい簡単に QMK を使用できるように取り組んでいます。
これらのツールには、ユーザーが QMK を最大限に活用できるように、キーボードのレイアウト方法や使用可能なピンと機能に関する情報が必要です。
その第一歩として `info.json` を導入しました。
QMK API は、これら3つの情報源（`config.h`、` rules.mk`、および `info.json`）を、エンドユーザーツールが使用できる信頼できる単一の情報源に結合するための取り組みです。

これで、`info.json`から `rules.mk` と `config.h` の値を生成することがサポートされ、信頼できる単一の情報源を持つことができます。
これにより、自動化されたツールを使用してキーボードを保守できるため、時間と保守作業を大幅に節約できます。

## 概要

C 側では何も変わりません。
新しいルールを作成したり、定義したりする必要がある場合は、同じプロセスに従います。

1. `docs/config_options.md` に追加します。
1. 適切なコアファイルにデフォルトを設定します。
1. 必要に応じて ifdef 文を追加します。

次に、新しい構成のサポートを `info.json` に追加する必要があります。
基本的なプロセスは次のとおりです。

1. `data/schemas/keyboards.jsonschema` のスキーマに追加します
1. `data/maps` にマッピングを追加します
1. （オプションおよび非推奨）構成を抽出/生成するコードを追加します。
   * `lib/python/qmk/info.py`
   * `lib/python/qmk/cli/generate/config_h.py`
   * `lib/python/qmk/cli/generate/rules_mk.py`

## info.json にオプションを追加する

このセクションでは、info.json に `config.h`/`rules.mk` の値のサポートを追加することについて説明します。

### スキーマに追加する

QMK では、[jsonschema](https:json-schema.org) のファイルを `data/schemas` に保持しています。
キーボード固有の `info.json` ファイルに入る値は `keyboard.jsonschema` に保持されています。
エンドユーザーが編集できるようにしたい値はすべてここに入れなければなりません。

場合によっては、新しいトップレベルキーを追加するだけで済みます。
従うべきいくつかの例は、 `keyboard_name`、`maintainer`、 `processor`、および `url` です。
これは、オプションが自己完結型で、他のオプションと直接関係がない場合に適しています。

その他の場合、1つの `object` の中に、似ているオプションを集める必要があります。
これは、機能のサポートを追加する場合に特に当てはまります。
このために従うべきいくつかの例は、`indicators`、`matrix_pins`、および `rgblight` です。
新しいオプションを統合する方法がわからない場合は、[問題を開く](https://github.com/qmk/qmk_firmware/issues/new?assignees=&labels=cli%2C+python&template=other_issues.md&title=)か、[Discord で #cli に参加](https://discord.gg/heQPAgy)して、そこで会話を始めてください。

### マッピングを追加する

ほとんどの場合、単純なマッピングを追加することができます。
これらは `data/mappings/info_config.json` と `data/mappings/info_rules.json` に JSON ファイルとして保持され、それぞれ `config.h` と `rules.mk` のマッピングを制御します。
各マッピングは `config.h` または `rules.mk` 変数名をキーとし、値は以下のキーを持つハッシュです。

* `info_key`: (必須）この値の `info.json` 内の場所。 下記参照。
* `value_type`: (オプション）デフォルトは `str`。 この変数の値の形式。 下記参照。
* `to_json`: (オプション）デフォルトは `true`。 このマッピングを info.json から除外するには、`false` に設定します
* `to_c`: (オプション）デフォルトは `true`。 このマッピングを config.h から除外するには、`false` に設定します
* `warn_duplicate`: (オプション）デフォルトは `true`。 値が両方の場所に存在する場合に警告をオフにするには、`false` に設定します

#### Info Key

info.json 内の変数をアドレス指定するために JSON ドット表記を使用します。
たとえば、`info_json["rgblight"]["split_count"]` にアクセスするには、`rgblight.split_count` を指定します。
これにより、深くネストされたキーを単純な文字列でアドレス指定できます。

内部では [Dotty Dict](https://dotty-dict.readthedocs.io/en/latest/) を使用しています。これらの文字列がオブジェクトアクセスに変換される方法についてはそのドキュメントを参照してください。

#### Value Types

デフォルトでは、すべての値を単純な文字列として扱います。
値がより複雑な場合は、次のいずれかのタイプを使用してデータをインテリジェントに解析できます。

* `array`: 文字列のコンマ区切りの配列
* `array.int`: 整数のコンマ区切り配列
* `int`: 整数
* `hex`: 16進数としてフォーマットされた数値
* `list`: 文字列のスペース区切りの配列
* `mapping`: キーと値のペアのハッシュ

### 抽出するコードを追加する

ほとんどのユースケースは、上記のマッピングファイルによって解決できます。
できない場合は、代わりに設定値を抽出するコードを書くことができます。

QMK が完全な `info.json` を生成するときはいつでも、`config.h` と `rules.mk` から情報を抽出します。
あなたの新しい設定値のためのコードを `lib/python/qmk/info.py` に追加する必要があります。
通常、これは、新しい `_extract_<feature>()` 関数を追加してから、 `_extract_config_h()` または `_extract_rules_mk()` のいずれかで関数を呼び出すことを意味します。

このファイルの編集方法がわからない場合、または Python に慣れていない場合は、[issue を開く](https://github.com/qmk/qmk_firmware/issues/new?assignees=&labels=cli%2C+python&template=other_issues.md&title=）か [Discord で #cli に参加](https://discord.gg/heQPAgy)すると、この部分を誰かが手伝ってくれるでしょう。

### 生成するコードを追加する

パズルの最後のピースは、ビルドシステムに新しいオプションを提供することです。
これは、2つのファイルを生成することによって行われます。

* `.build/obj_<keyboard>_<keymap>/src/info_config.h`
* `.build/obj_<keyboard>_<keymap>/src/rules.mk`

この2つのファイルは、次のコードによって生成されます。

* `lib/python/qmk/cli/generate/config_h.py`
* `lib/python/qmk/cli/generate/rules_mk.py`

`config.h`値の場合、ルール用の関数を記述し、その関数を `generate_config_h()` で呼び出す必要があります。

`rules.mk` の新しいトップレベルの `info.json` キーがある場合は、`lib/python/qmk/cli/generate/rules_mk.py` の上部にある `info_to_rules` にキーを追加するだけです。
それ以外の場合は、`generate_rules_mk()` で機能の新しい if ブロックを作成する必要があります。
