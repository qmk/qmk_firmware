# QMK ドキュメントを異なる言語に翻訳する方法

ルートフォルダ (`docs/`) にある全てのファイルは英語でなければなりません - 他の全ての言語は、ISO 639-1 言語コードと、それに続く`-`と適切な国コードのサブフォルダにある必要があります。[一般的なもののリストはここで見つかります](https://www.andiamo.co.uk/resources/iso-language-codes/)。このフォルダが存在しない場合、作成することができます。翻訳された各ファイルは英語バージョンと同じ名前でなければなりません。そうすれば正常に元の状態に戻すことができます。

`_summary.md`ファイルはこのフォルダの中に存在し、各ファイルへのリンクのリスト、翻訳された名前、言語フォルダに続くリンクが含まれている必要があります。

    * [QMK简介](zh-cn/getting_started_introduction.md)

新しい言語の翻訳が完了したら、以下のファイルも修正する必要があります:

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)
各行は、`:us:`の形式で国フラグと、それに続く独自の言語で表される名前を含む必要があります:

       - [:cn: 中文](/zh-cn/)
   
* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)
`placeholder` と `noData` の両方のオブジェクトは、文字列で言語フォルダの辞書エントリが必要です:

       '/zh-cn/': '没有结果!',
   
## 翻訳のプレビュー

プルリクエストを開く前に、Python 3がインストールされている場合は`docs/`フォルダ内で以下のコマンドを実行して、追加したものをプレビューすることができます。

    python -m http.server 9000

http://localhost:9000/ に移動します - 右上の "Translations" メニューから新しい言語を選択することができるはずです。

作業に満足したら、遠慮なくプルリクエストを開いてください！
