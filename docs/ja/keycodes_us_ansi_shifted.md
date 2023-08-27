# US ANSI シフト記号

<!---
  original document: 0.13.23:docs/keycodes_us_ansi_shifted.md
  git diff 0.13.23 HEAD -- docs/keycodes_us_ansi_shifted.md | cat
-->
これらのキーコードは、標準の US ANSI 配列のキーボードで「シフトされる」文字に対応します。これらのキーコードは自身のキーコードを持たず、`LSFT(kc)` の単なるショートカットであり、記号自体ではなく Shift キー抜きのキーコードと左 Shift キーを送信します。

## 注意書き

残念ながら、これらのキーコードは、モッドタップやレイヤータップの中で使えません。キーコードで指定されたモディファイアは無視されるからです。

さらに、Windows でリモートデスクトップ接続を使う場合に、問題が発生する場合があります。なぜならば、これらのコードは Shift キーを非常に速く送信するため、リモートデスクトップがコードを見落とすかもしれないからです。

この問題を解決するには、リモートデスクトップ接続を開いて「オプションの表示」をクリックし、「ローカル リソース」タブを開きます。キーボードセクションでドロップダウンを「このコンピュータ」に変更します。これで問題が解決され、文字が正しく機能するようになります。

## キーコード

|キー                    |エイリアス         |説明       |
|------------------------|-------------------|-----------|
|`KC_TILDE`              |`KC_TILD`          |`~`        |
|`KC_EXCLAIM`            |`KC_EXLM`          |`!`        |
|`KC_AT`                 |                   |`@`        |
|`KC_HASH`               |                   |`#`        |
|`KC_DOLLAR`             |`KC_DLR`           |`$`        |
|`KC_PERCENT`            |`KC_PERC`          |`%`        |
|`KC_CIRCUMFLEX`         |`KC_CIRC`          |`^`        |
|`KC_AMPERSAND`          |`KC_AMPR`          |`&`        |
|`KC_ASTERISK`           |`KC_ASTR`          |`*`        |
|`KC_LEFT_PAREN`         |`KC_LPRN`          |`(`        |
|`KC_RIGHT_PAREN`        |`KC_RPRN`          |`)`        |
|`KC_UNDERSCORE`         |`KC_UNDS`          |`_`        |
|`KC_PLUS`               |                   |`+`        |
|`KC_LEFT_CURLY_BRACE`   |`KC_LCBR`          |`{`        |
|`KC_RIGHT_CURLY_BRACE`  |`KC_RCBR`          |`}`        |
|`KC_PIPE`               |                   |`\|`       |
|`KC_COLON`              |`KC_COLN`          |`:`        |
|`KC_DOUBLE_QUOTE`       |`KC_DQUO`, `KC_DQT`|`"`        |
|`KC_LEFT_ANGLE_BRACKET` |`KC_LABK`, `KC_LT` |`<`        |
|`KC_RIGHT_ANGLE_BRACKET`|`KC_RABK`, `KC_GT` |`>`        |
|`KC_QUESTION`           |`KC_QUES`          |`?`        |
