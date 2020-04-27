# レイアウト: 複数のキーボードでキーマップを使用

<!---
  original document: 0.8.134:docs/feature_layouts.md
  git diff 0.8.134 HEAD -- docs/feature_layouts.md | cat
-->

`layouts/` フォルダは、様々なキーボードに適用できる異なる物理キーレイアウトを含みます。

```
layouts/
+ default/
| + 60_ansi/
| | + readme.md
| | + layout.json
| | + a_good_keymap/
| | | + keymap.c
| | | + readme.md
| | | + config.h
| | | + rules.mk
| | + <keymap folder>/
| | + ...
| + <layout folder>/
+ community/
| + <layout folder>/
| + ...
```

`layouts/default/` と `layouts/community/` は、レイアウト "repositories" の2つの例です - 現在のところ、`default` は全てのユーザが参照として使うレイアウトに関する全ての情報、`default_<layout>` という名前の1つのデフォルトのキーマップを含みます。`community` は全ての共有キーマップを含み、最終的な目的はユーザが `layouts/` にクローンするために個々のリポジトリに分割することです。QMK は `layouts/` 内のすべてのフォルダを検索するため、ここに複数のリポジトリを持つことができます。

各レイアウトフォルダは、レイアウトの物理的な側面に基づいて、最も一般的な方法で(`[a-z0-9_]`)という名前が付けられ、キーボードで定義されるレイアウトと一緒に `readme.md` を含みます。

```md
# 60_ansi

   LAYOUT_60_ansi
```

新しい名前は既存のレイアウトで設定された標準に準拠しようと努力する必要があり、PR/Issue で議論することができます。

## レイアウトのサポート

キーボードがレイアウトをサポートするために、変数は `<keyboard>.h` で定義し、引数/キー (できれば物理レイアウト)の数に一致する必要があります。

    #define LAYOUT_60_ansi KEYMAP_ANSI

レイアウトの名前は以下の正規表現に一致しなければなりません: `[a-z0-9_]+`

フォルダ名はキーボードの `rules.mk` に追加する必要があります:

    LAYOUTS = 60_ansi

`LAYOUTS` は任意のキーボードフォルダレべルの `rules.mk` に設定することができます:

    LAYOUTS = 60_iso

ただし、`LAYOUT_<layout>` 変数は `<folder>.h` でも定義する必要があります。

## キーマップの作成

以下の形式でコマンドを使ってキーボードキーマップを作成できるはずです:

    make <keyboard>:<layout>

### レイアウトの競合
キーボードが複数のレイアウトオプションをサポートする場合、

    LAYOUTS = ortho_4x4 ortho_4x12

そして、両方のオプションについてレイアウトが存在する場合、
```
layouts/
+ community/
| + ortho_4x4/
| | + <layout>/
| | | + ...
| + ortho_4x12/
| | + <layout>/
| | | + ...
| + ...
```

FORCE_LAYOUT 引数はどのレイアウトを作成するかを指定するために使うことができます

    make <keyboard>:<layout> FORCE_LAYOUT=ortho_4x4
    make <keyboard>:<layout> FORCE_LAYOUT=ortho_4x12

## キーボードに依存しないレイアウトを作成するためのヒント

### Includes

`#include "planck.h"` を使う代わりに、コンパイルされるどのような `<keyboard>.h` (`<folder>.h` はここで含めるべきではありません)ファイルでも含めるために、この行を使うことができます:

    #include QMK_KEYBOARD_H

キーボード固有のコードを保持したい場合は、これらの変数を使って `#ifdef` 文でエスケープすることができます:

* `KEYBOARD_<folder1>_<folder2>`

例えば:

```c
#ifdef KEYBOARD_planck
    #ifdef KEYBOARD_planck_rev4
        planck_rev4_function();
    #endif
#endif
```

名前は小文字でキーボード/リビジョンのフォルダ/ファイル名と正確に一致することに注意してください。

### キーマップ

同じレイアウトで分割および非分割キーボードをサポートするためには、キーマップでキーボード非依存の `LAYOUT_<layout name>` マクロを使う必要があります。例えば、Let's Split および Planck が同じレイアウトを共有するには、`LAYOUT_planck_grid` の代わりに `LAYOUT_ortho_4x12` を使うか、C 配列の場合は単に `{}` を使う必要があります。
