# コーディング規約 (C)

<!---
  original document: 0.13.15:docs/coding_conventions_c.md
  git diff 0.13.15 HEAD -- docs/coding_conventions_c.md | cat
-->

私たちのスタイルのほとんどはかなり理解しやすいですが、現時点では完全に一貫しているわけではありません。変更箇所周辺のコードのスタイルと一致させる必要がありますが、そのコードに一貫性が無い場合や不明瞭な場合は以下のガイドラインに従ってください:

* 4つのスペース (ソフトタブ) を使ってインデントします。
* 修正版 One True Brace Style を使います。
   * 開き括弧: ブロックを開始する文と同じ行の最後
   * 閉じ括弧: ブロックを開始した文と同じ字下げ
   * Else If: 行の先頭に閉じ括弧を置き、次の開き括弧を同じ行の最後に置きます。
   * 省略可能な括弧: 常に括弧を付け加えます。
      * 良い: if (condition) { return false; }
      * 悪い: if (condition) return false;
* C 形式のコメントの使用を推奨します: `/* */`
   * コメントを機能を説明するストーリーと考えて下さい。
   * 特定の決定がなされた理由を充分なコメントで説明してください。
   * 分かり切ったコメントは書かないでください。
   * 分かり切ったコメントであるか確信できない場合は、コメントを含めてください。
* 一般的に、行を折り返さないで、必要なだけ長くすることができます。行を折り返すことを選択した場合は、76列を超えて折り返さないでください。
* 古い形式のインクルードガード (`#ifndef THIS_FILE_H`、`#define THIS_FILE_H`、...、`#endif`) ではなく、ヘッダファイルの先頭で `#pragma once` を使います。
* プリプロセッサ if の両方の形式を受け付けます: `#ifdef DEFINED` と `#if defined(DEFINED)`
   * どちらがいいかわからない場合は、`#if defined(DEFINED)` 形式を使ってください。
   * 複数の条件 `#if` に移行する場合を除き、既存のコードを別のスタイルに変更しないでください。
* プリプロセッサディレクティブをインデントする方法(あるいはするかどうか)を決定する時は、以下の事に留意してください:
   * 一貫性よりも読みやすさが重要です。
   * ファイルの既存のスタイルに従ってください。ファイルのスタイルが混在している場合は、修正しようとしているセクションに適したスタイルに従ってください。
   * インデントする時は、ハッシュを行の先頭に置き、`#` と `if` の間に空白を追加します。`#` の後ろに4つスペースを入れて開始します。
   * 周りの C コードのインデントレベルに従うか、プリプロセッサのディレクティブに独自のインデントレベルを設定することができます。コードの意図を最もよく伝えるスタイルを選択してください。

わかりやすいように例を示します:

```c
/* Enums for foo */
enum foo_state {
    FOO_BAR,
    FOO_BAZ,
};

/* Returns a value */
int foo(void) {
    if (some_condition) {
        return FOO_BAR;
    } else {
        return -1;
    }
}
```

# clang-format を使った自動整形

[Clang-format](https://clang.llvm.org/docs/ClangFormat.html) は LLVM の一部で、誰もが手動で整形するほど暇ではないため、コードを自動整形することができます。私たちは、上記のコーディング規約のほとんどを適用する設定ファイルを提供しています。空白と改行のみを変更するため、省略可能な括弧は自分で付け加えることを忘れないでください。

Windows で clang-format を入手するには [full LLVM インストーラ](https://llvm.org/builds/)を使い、Ubuntu では `sudo apt install clang-format` を使ってください。

コマンドラインから実行する場合、オプションとして `-style=file` を渡すと、QMK ルートディレクトリ内の .clang-format 設定ファイルを自動的に見つけます。

VSCode を使う場合は、標準の C/C++ プラグインが clang-format をサポートしますが、その他にも [独立した拡張機能](https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.ClangFormat) があります。

幾つかのコード (LAYOUT マクロのような)が clang-format によって破壊されるため、これらのファイルで clang-format を実行しないか、整形したくないコードを `// clang-format off` と `// clang-format on` で囲みます。
