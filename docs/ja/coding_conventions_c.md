# コーディング規約 (C)

<!---
  original document: 0.9.19:docs/coding_conventions_c.md
  git diff 0.9.19 HEAD -- docs/coding_conventions_c.md | cat
-->

私たちのスタイルはほとんどは簡単に理解できますが、現時点では完全に一貫しているわけではありません。変更を囲むコードのスタイルと一致させる必要がありますが、そのコードに一貫性が無い場合や不明瞭な場合は以下のガイドラインに従ってください:

* 4 (4) つのスペース (soft tabs) を使ってインデントします
* 修正 One True Brace スタイルを使います
   * 括弧開き: ブロックを開始する命令文と同じ行の最後
   * 括弧閉じ: ブロックを開始する命令文の最初の文字と並ぶ
   * それ以外の場合: 行の先頭に括弧閉じを置き、次の括弧開きを同じ行の最後に置きます。
   * オプションの括弧: 常にオプションの括弧を含みます
      * 良い: if (condition) { return false; }
      * 悪い: if (condition) return false;
* C 形式のコメントの使用をお勧めします: `/* */`
   * それらを機能の説明をするストーリーと考えて下さい
   * それらを自由に使って特定の決定がされた理由を説明してください
   * 明白なコメントは書かないでください
   * 分かり切ったコメントであるか確信できない場合は、コメントを含めてください
* 一般的に、行を折り返さないで、必要なだけ長くすることができます。行を折り返すことを選択した場合は、76列を超えて折り返さないでください。
* 古い形式のインクルード ガード (`#ifndef THIS_FILE_H`、`#define THIS_FILE_H`、...、`#endif`) ではなく、ヘッダファイルの先頭で `#pragma once` を使います
* プリプロセッサ if の両方の形式を受け付けます: `#ifdef DEFINED` と `#if defined(DEFINED)`
   * どちらを好むか分からない場合は、`#if defined(DEFINED)` 形式を使ってください。
   * 複数の条件 `#if` に移動する場合を除き、既存のコードを別のスタイルに変更しないでください。
* プリプロセッサディレクティブをインデントする方法 (あるいはするかどうか)を決定する時は、以下の事に留意してください:
   * 一貫性よりも読みやすさが重要です。
   * ファイルの既存のスタイルに従ってください。ファイルが混在する場合は、修正しようとしているセクションに適したスタイルに従ってください。
   * インデントする時は、ハッシュを行の先頭に置き、`#` と `if` の間に空白を追加します。`#` の後ろの4つのスペースから始めます。
   * 周りの C コードのインデントレベルに従うか、プリプロセッサのディレクティブに独自のインデントレベルを設定することができます。コードの意図を最もよく伝えるスタイルを選択してください。

参照しやすいように例を示します:

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

[Clang-format](https://clang.llvm.org/docs/ClangFormat.html) は LLVM の一部で、誰もが手動でそれを行う時間がないため、コードを自動的に整形することができます。上記のコーディング規約のほとんどを適用する設定ファイルを提供します。空白と改行のみを変更するため、オプションの括弧を自分自身で含めることを忘れないでください。

Windows で clang-format を取得するために [full LLVM インストーラ](http://llvm.org/builds/)を使うか、Ubuntu で `sudo apt install clang-format` を使ってください。

コマンドラインから実行する場合、オプションとして `-style=file` を渡すと、QMK ルートディレクトリ内の .clang-format 設定ファイルを自動的に見つけます。

VSCode を使う場合は、標準の C/C++ プラグインが clang-format をサポートしますが、代わりに [separate extension](https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.ClangFormat) があります。

幾つかの事 (LAYOUT マクロのような)が clang-format によって破壊されるため、これらのファイルで実行しないか、傷つきやすいコードを `// clang-format off` と `// clang-format on` で囲みます。
