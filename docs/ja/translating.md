# QMK ドキュメントを翻訳する

<!---
  original document: 0.9.51:docs/translating.md
  git diff 0.9.51 HEAD -- docs/translating.md | cat
-->

ルートフォルダ (`docs/`) にある全てのファイルは英語でなければなりません - 他の全ての言語は、ISO 639-1 言語コードと、それに続く`-`と関連する国コードのサブフォルダにある必要があります。[一般的なもののリストはここで見つかります](https://www.andiamo.co.uk/resources/iso-language-codes/)。このフォルダが存在しない場合、作成することができます。翻訳された各ファイルは英語バージョンと同じ名前でなければなりません。そうすることで、正常にフォールバックできます。

`_summary.md` ファイルはこのフォルダの中に存在し、各ファイルへのリンクのリスト、翻訳された名前、言語フォルダに続くリンクが含まれている必要があります。

```markdown
 * [QMK简介](zh-cn/getting_started_introduction.md)
```

他の docs ページへの全てのリンクにも、言語のフォルダが前に付いている必要があります。もしリンクがページの特定の部分(例えば、特定の見出し)への場合、以下のように見出しに英語の ID を使う必要があります:

```markdown
[建立你的环境](zh-cn/newbs-getting-started.md#set-up-your-environment)

## 建立你的环境 :id=set-up-your-environment
```

新しい言語の翻訳が完了したら、以下のファイルも修正する必要があります:

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)
各行は、[GitHub emoji shortcode](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md#country-flag) の形式で国フラグと、それに続く言語で表される名前を含む必要があります。

  ```markdown
   - [:cn: 中文](/zh-cn/)
  ```

* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)
`placeholder` と `noData` の両方のオブジェクトは、文字列で言語フォルダの辞書エントリが必要です:

  ```js
  '/zh-cn/': '没有结果!',
  ```

   サイドバーの「QMK ファームウェア」の見出しリンクを設定するために、`nameLink` オブジェクトも以下のように追加される必要があります:

  ```js
  '/zh-cn/': '/#/zh-cn/',
  ```

   また、`fallbackLanguages` リストに言語フォルダを追加して、404 ではなく英語に適切にフォールバックするようにしてください:

  ```js
  fallbackLanguages: [
    // ...
    'zh-cn',
    // ...
  ],
  ```

## 翻訳のプレビュー

ドキュメントのローカルインスタンスをセットアップする方法については、[ドキュメントのプレビュー](ja/contributing.md#previewing-the-documentation)を見てください - 右上の "Translations" メニューから新しい言語を選択することができるはずです。

作業に満足したら、遠慮なくプルリクエストを開いてください！
