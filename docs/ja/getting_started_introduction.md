# はじめに

<!---
  original document: d598f01cb:getting_started_introduction.md
  git diff d598f01cb HEAD getting_started_introduction.md | cat
-->

このページでは、QMK プロジェクトで作業するために知っておくべき基本的な情報について説明しようと思います。Unix シェルの操作に精通していることを前提としていますが、C について、または make を使ったコンパイルについて精通しているとは想定していません。

## 基本的な QMK の構造

QMK は [Jun Wako](https://github.com/tmk) の [tmk_keyboard](https://github.com/tmk/tmk_keyboard) プロジェクトのフォークです。変更された元の TMK コードは、`tmk_core` フォルダで見つけることができます。プロジェクトへの QMK の追加は、`quantum` フォルダで見つけることができます。キーボードプロジェクトは `handwired` および `keyboard` フォルダで見つけることができます。

### ユーザスペースの構造

`users` フォルダ内は各ユーザのためのディレクトリです。これはユーザがキーボード間で使うかもしれないコードを置くためのフォルダです。詳細は[ユーザスペース機能](ja/feature_userspace.md) のドキュメントを見てください。

### キーボードプロジェクトの構造

`keyboards` フォルダ、そのサブフォルダ `handwired`、ベンダと製品のサブディレクトリ (例えば、`clueboard`) の中には、各キーボードプロジェクトのためのディレクトリ (例えば `qmk_firmware/keyboards/clueboard/2x1800`) があります。その中には、以下の構造があります:

* `keymaps/`: ビルドできる様々なキーマップ
* `rules.mk`: デフォルトの "make" オプションを設定するファイル。このファイルを直接編集しないでください。代わりにキーマップ固有の `rules.mk` を使ってください。
* `config.h`: デフォルトのコンパイル時のオプションを設定するファイル。このファイルを直接編集しないでください。代わりにキーマップ固有の `config.h` を使ってください。
* `info.json`: QMK Configurator のためのレイアウトの設定に使われるファイル。詳細は [Configurator サポート](ja/reference_configurator_support.md)を見てください。
* `readme.md`: キーボードの簡単な概要
* `<keyboardName>.h`: このファイルは、キーボードのスイッチマトリックスに対してキーボードレイアウトが定義されるファイルです。
* `<keyboardName>.c`: このファイルには、キーボードのためのカスタムコードがあります。

プロジェクトの構造についての詳細は、[QMK キーボードガイドライン](ja/hardware_keyboard_guidelines.md)を見てください。

### キーマップ構造

全てのキーマップフォルダには、以下のファイルがあります。`keymap.c` だけが必須で、残りのファイルが見つからない場合は、デフォルトのオプションが選択されます。

* `config.h`: キーマップを設定するためのオプション
* `keymap.c`: 全てのキーマップコード。必須
* `rules.mk`: 有効になっている QMK の機能
* `readme.md`: キーマップの説明。他の人が使う方法および機能の説明。imgur のようなサービスに画像をアップロードしてください。

# `config.h` ファイル

3つの `config.h` の場所が考えられます:

* キーボード (`/keyboards/<keyboard>/config.h`)
* ユーザスペース (`/users/<user>/config.h`)
* キーマップ (`/keyboards/<keyboard>/keymaps/<keymap>/config.h`)

ビルドシステムは自動的に上の順に config ファイルを取得します。前の `config.h` で設定された設定を上書きしたい場合は、変更したい設定の準備のために最初に定型コードを置く必要があります。

```
#pragma once
```

次に、前の `config.h` ファイルの設定を上書きするために、設定を `#undef` し再び `#define` する必要があります。

定型コードと設定は、以下のようになります:

```
#pragma once

// ここに上書きします！
#undef MY_SETTING
#define MY_SETTING 4
```
