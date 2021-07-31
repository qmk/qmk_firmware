# US ANSI シフト記号

これらのキーコードは、スタンダードな US ANSI 配列のキーボードで「Shift キーと一緒に押した」文字列に一致します。これらのキーコードは、自身のキーコードを持たず、記号自体でもありません。`LSFT(kc)` のシンプルなショートカットで、Shift キー抜きのキーコードと左 Shift キーを送信するものです。

## 注意書き

不運なことに、これらのキーコードは、モッドタップやレイヤータップの中で使えません。モディファイヤが、無視されるキーコードを規定しているからです。

さらに、Windows のリモートデスクトップ接続中に課題に出くわすかもしれません。なぜならば、これらのコードは Shift キーを非常に速く送信するため、リモートデスクトップソフトがコードを見落とすかもしれないからです。

この問題を解決するには、リモートデスクトップ接続を開いて「オプションの表示」をクリックし、「ローカルリソース」タブを開きます。そのタブの中のキーボードセクションのドロップダウンリストを「このコンピュータ」に変更します。これで問題が解決され、文字列が正しく機能するようになります。

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
