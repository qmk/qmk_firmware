# 言語固有のキーコード

<!---
  original document: 0.9.55:docs/reference_keymap_extras.md
  git diff 0.9.55 HEAD -- docs/reference_keymap_extras.md | cat
-->

キーボードは多くの言語をサポートすることができます。ただし、それらはキーを押したことで生成される実際の文字を送信しません - 代わりに数字のコードを送信します。USB HID の仕様ではそれらは "usages" と呼ばれますが、キーボードの文脈では「スキャンコード」あるいは「キーコード」と呼ばれることが多いです。
HID Keyboard/Keypad usage ページでは 256 未満の usage が定義されており、それらの一部は現在のオペレーティングシステムでは機能しません。では、この言語のサポートはどのようにして実現されるのでしょうか？

簡単に言うと、オペレーティングシステムはユーザが設定したキーボードレイアウトに基づいて受け取った usage を適切な文字にマップします。例えば、スウェーデン人がキーボードの `å` という文字が刻印されたキーを押すと、キーボードは *実際には* `[` のキーコードを送信します。

明らかにこれは混乱する可能性があるため、QMK は多くのキーボードレイアウトのために言語固有のキーコードのエイリアスを提供します。これらはそれだけでは何もしません - さらに OS の設定で対応するキーボードレイアウトを設定する必要があります。それらをキーマップのキーキャップラベルと考えてください。

これらを使うには、`keymap.c` で対応する [ヘッダファイル](https://github.com/qmk/qmk_firmware/tree/master/quantum/keymap_extras) を `#include` し、それらで定義されているキーコードを `KC_` プリフィクスの代わりに追加します:

| レイアウト                  | ヘッダファイル                   |
|-----------------------------|----------------------------------|
| Canadian Multilingual (CSA) | `keymap_canadian_multilingual.h` |
| Croatian                    | `keymap_croatian.h`              |
| Czech                       | `keymap_czech.h`                 |
| Danish                      | `keymap_danish.h`                |
| Dutch (Belgium)             | `keymap_belgian.h`               |
| English (Ireland)           | `keymap_irish.h`                 |
| English (UK)                | `keymap_uk.h`                    |
| English (US International)  | `keymap_us_international.h`      |
| Estonian                    | `keymap_estonian.h`              |
| Finnish                     | `keymap_finnish.h`               |
| French                      | `keymap_french.h`                |
| French (AFNOR)              | `keymap_french_afnor.h`          |
| French (BÉPO)               | `keymap_bepo.h`                  |
| French (Belgium)            | `keymap_belgian.h`               |
| French (Switzerland)        | `keymap_fr_ch.h`                 |
| French (macOS, ISO)         | `keymap_french_osx.h`            |
| German                      | `keymap_german.h`                |
| German (Switzerland)        | `keymap_german_ch.h`             |
| German (macOS)              | `keymap_german_osx.h`            |
| German (Neo2)*              | `keymap_neo2.h`                  |
| Greek*                      | `keymap_greek.h`                 |
| Hebrew*                     | `keymap_hebrew.h`                |
| Hungarian                   | `keymap_hungarian.h`             |
| Icelandic                   | `keymap_icelandic.h`             |
| Italian                     | `keymap_italian.h`               |
| Italian (macOS, ANSI)       | `keymap_italian_osx_ansi.h`      |
| Italian (macOS, ISO)        | `keymap_italian_osx_iso.h`       |
| Japanese                    | `keymap_jp.h`                    |
| Korean                      | `keymap_korean.h`                |
| Latvian                     | `keymap_latvian.h`               |
| Lithuanian (ĄŽERTY)         | `keymap_lithuanian_azerty.h`     |
| Lithuanian (QWERTY)         | `keymap_lithuanian_qwerty.h`     |
| Norwegian                   | `keymap_norwegian.h`             |
| Polish                      | `keymap_polish.h`                |
| Portuguese                  | `keymap_portuguese.h`            |
| Portuguese (macOS, ISO)     | `keymap_portuguese_osx_iso.h`    |
| Portuguese (Brazil)         | `keymap_br_abnt2.h`              |
| Romanian                    | `keymap_romanian.h`              |
| Russian*                    | `keymap_russian.h`               |
| Serbian*                    | `keymap_serbian.h`               |
| Serbian (Latin)             | `keymap_serbian_latin.h`         |
| Slovak                      | `keymap_slovak.h`                |
| Slovenian                   | `keymap_slovenian.h`             |
| Spanish                     | `keymap_spanish.h`               |
| Spanish (Dvorak)            | `keymap_spanish_dvorak.h`        |
| Swedish                     | `keymap_swedish.h`               |
| Turkish (F)                 | `keymap_turkish_f.h`             |
| Turkish (Q)                 | `keymap_turkish_q.h`             |

言語固有でないものもありますが、QWERTY レイアウトを使っていない場合に役立ちます:

| レイアウト          | ヘッダファイル           |
|---------------------|--------------------------|
| Colemak             | `keymap_colemak.h`       |
| Dvorak              | `keymap_dvorak.h`        |
| Dvorak (French)     | `keymap_dvorak_fr.h`     |
| Dvorak (Programmer) | `keymap_dvp.h`           |
| Norman              | `keymap_norman.h`        |
| Plover*             | `keymap_plover.h`        |
| Plover (Dvorak)*    | `keymap_plover_dvorak.h` |
| Steno*              | `keymap_steno.h`         |
| Workman             | `keymap_workman.h`       |
| Workman (ZXCVM)     | `keymap_workman_zxcvm.h` |

## Sendstring サポート

デフォルトでは、`SEND_STRING()` は US ANSI キーボードレイアウトが設定されたと見なします。別のレイアウトを使っている場合は、キーマップで(上記のように)`#include "sendstring_*.h"` して、ASCII 文字をキーコードにマッピングするために使われるルックアップテーブルを上書きすることができます。

ここで注意すべき重要な点は、`SEND_STRING()` は [ASCII 文字](https://en.wikipedia.org/wiki/ASCII#Character_set) でのみ機能するということです。これは、ユニコード文字を含む文字列を渡すことができないことを意味します - 残念ながら、これには希望のレイアウトに存在する可能性のあるアクセント付き文字が含まれています。
多くのレイアウトでは、Grave または Tilde などの特定の文字を[デッドキー](https://en.wikipedia.org/wiki/Dead_key)としてのみ使えるようにしています。そのため、デッドキーが次の文字と潜在的に結合されることを防ぐためには、送信したい文字列の中のデッドキーのすぐ後にスペースを追加する必要があります。
ラテン語由来のアルファベットを使わない(例えば、ギリシャ語やロシア語のような)他のレイアウトには、Sendstring ヘッダーがありません。従って ASCII 文字セットのほとんどを入力する方法がありません。これらは上記で `*` でマークされています。
