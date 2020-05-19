# レイアウト: 複数のキーボードで1つのキーマップを使用

<!---
  original document: 0.8.134:docs/feature_layouts.md
  git diff 0.8.134 HEAD -- docs/feature_layouts.md | cat
-->

`layouts/` フォルダは、様々なキーボードに適用できる色々な物理キーレイアウトを含みます。

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

`layouts/default/` と `layouts/community/` は、レイアウト「repositories」の2つの例です。現在のところ、`default` にはユーザの参考用に、レイアウトに関する全ての情報および、`default_<layout>` という名前の1つのデフォルトのキーマップが含まれています。`community` には全ての共有キーマップが含まれており、それらはユーザが `layouts/` にクローンするための別のリポジトリに分割することを最終的な目的としていますQMK は `layouts/` 内のすべてのフォルダを検索するため、ここに複数のリポジトリを持つことができます。

各レイアウトフォルダは、レイアウトの物理的な側面に基づいて、可能な限り一般的な名称で(`[a-z0-9_]`)という名前が付けられ、キーボードで定義されるレイアウトと一緒に `readme.md` を含みます。

```md
# 60_ansi

   LAYOUT_60_ansi
```

新しい名前は既存のレイアウトで設定された標準に準拠しようと努力する必要があり、必要に応じて PR/Issue で議論することができます。

## レイアウトのサポート

キーボードがレイアウトをサポートするために、変数は `<keyboard>.h` で定義し、引数/キー (できれば物理レイアウト)の数に一致している必要があります。

    #define LAYOUT_60_ansi KEYMAP_ANSI

レイアウトの名前は次の正規表現に一致しなければなりません: `[a-z0-9_]+`

フォルダ名はキーボードの `rules.mk` に追加する必要があります:

    LAYOUTS = 60_ansi

`LAYOUTS` は任意のキーボードフォルダレべルの `rules.mk` に設定することができます:

    LAYOUTS = 60_iso

ただし、`LAYOUT_<layout>` 変数は `<folder>.h` でも定義する必要があります。

## キーマップのビルド

以下の形式でコマンドを使ってキーボードキーマップを作成できるはずです:

    make <keyboard>:<layout>

### レイアウトの競合
キーボードが複数のレイアウトオプションをサポートし、

    LAYOUTS = ortho_4x4 ortho_4x12

なおかつ両方のオプションについてレイアウトが存在する場合、
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

FORCE_LAYOUT 引数はどのレイアウトをビルドするかを指定するために使うことができます

    make <keyboard>:<layout> FORCE_LAYOUT=ortho_4x4
    make <keyboard>:<layout> FORCE_LAYOUT=ortho_4x12

## キーボードに依存しないレイアウトを作成するためのヒント

### インクルード

`#include "planck.h"` を使う代わりに、以下の行を使ってコンパイルされる `<keyboard>.h` (`<folder>.h` はここでインクルードすべきではありません)ファイルをインクルードすることができます:

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

同じレイアウトで分割および非分割キーボードをサポートするためには、キーマップでキーボード非依存の `LAYOUT_<layout name>` マクロを使う必要があります。例えば、Let's Split および Planck が同じレイアウトを共有するには、`LAYOUT_planck_grid` や C 配列の場合の単なる `{}` の代わりに、`LAYOUT_ortho_4x12` を使う必要があります。
