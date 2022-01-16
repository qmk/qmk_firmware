# 特定语言键码

键盘有能力支持相当广泛的语言。然而，这种支持通常并非来自键盘内部，键盘发送数字编码，然后操作系统根据用户定义的键盘布局映射为对应的字符。键盘布局（对于每个HID规范）默认为 US ANSI 布局。举个例子，当一个瑞典人按下 `å` 字符，键盘实际发送的是 `[`。

显然，这会让人们感到困惑，所以 QMK 提供了特定语言键码作为各种不同键盘布局的别名。这些工作不会自发完成，你仍然需要在你的系统设置中配置键盘布局。你可以把它们看作是你的键映射的键帽标签。

在你的 `keymap.c` 文件顶部，通过 `#include` 引入下方键码头文件之一，并为头文件中定义的以 `KC_` 为前缀的键码赋值。

## Sendstring 支持

默认情况下， `SEND_STRING()` 假定设置的是 US ANSI 键盘布局。如果你使用的是不同的键盘布局，可以在你的 `keymap.c` 文件内，导入一个 Sendstring LUT 头部文件，用以覆盖从 ASCII 字符到键码的映射表。你无需导入类似 `keymap_*.h` 的头文件，因为在你导入 Sendstring 头文件的时候，已经隐式导入了。

需要注意的一点是， `SEND_STRING()` 只作用于 [ASCII 文本](https://en.wikipedia.org/wiki/ASCII#Character_set)。这意味着你不能将包含Unicode字符（不幸的是，可能恰好是一些你想要的键盘布局中的重音字符）的字符串传递给它。

（译注：重音符号，即 accented characters，在一些语言中，如希腊语，需要使用到变音字母，如：à、è等）

很多键盘布局可以直接通过 [dead keys](https://en.wikipedia.org/wiki/Dead_key) 打出例如 Grave 或 Tilde 字符，你需要先发送你想要的字符，然后紧跟一个空格键，来避免和下一个字符形成可能的组合。

（译注：一些常见的重音符号，**◌́** – [acute](https://en.wikipedia.org/wiki/Acute_accent) 、**◌̀** – [grave](https://en.wikipedia.org/wiki/Grave_accent)、**◌̂** – [circumflex](https://en.wikipedia.org/wiki/Circumflex_accent)、**◌̌** – [caron](https://en.wikipedia.org/wiki/Caron)、**◌̋** – [double acute](https://en.wikipedia.org/wiki/Double_acute_accent)、**◌̏** – [double grave](https://en.wikipedia.org/wiki/Double_grave_accent)、**◌̃** – [tilde](https://en.wikipedia.org/wiki/Tilde)）

某些键盘布局没有对应的 Sendstring 头文件，因为它们不使用*拉丁衍生*字母表（例如希腊语和俄语），因此没有办法输入大部分ASCII字符集。

## 头文件

这些头文件所在目录： [`quantum/keymap_extras/`](https://github.com/qmk/qmk_firmware/tree/master/quantum/keymap_extras)。

| 键盘布局                               | 键码头文件                        | Sendstring LUT 头文件                |
| -------------------------------------- | --------------------------------- | ------------------------------------ |
| 加拿大 Canadian Multilingual (CSA)     | `keymap_canadian_multilingual.h`  | `sendstring_canadian_multilingual.h` |
| 克罗地亚语 Croatian                    | `keymap_croatian.h`               | `sendstring_croatian.h`              |
| 捷克语 Czech                           | `keymap_czech.h`                  | `sendstring_czech.h`                 |
| 丹麦语 Danish                          | `keymap_danish.h`                 | `sendstring_danish.h`                |
| 荷兰语 Dutch (Belgium)                 | `keymap_belgian.h`                | `sendstring_belgian.h`               |
| 英语 English (Ireland)                 | `keymap_irish.h`                  |                                      |
| 英语 English (UK)                      | `keymap_uk.h`                     | `sendstring_uk.h`                    |
| 英语 English (US Extended)             | `keymap_us_extended.h`            |                                      |
| 英语 English (US International)        | `keymap_us_international.h`       | `sendstring_us_international.h`      |
| 英语 English (US International, Linux) | `keymap_us_international_linux.h` |                                      |
| 爱沙尼亚语 Estonian                    | `keymap_estonian.h`               | `sendstring_estonian.h`              |
| 芬兰语 Finnish                         | `keymap_finnish.h`                | `sendstring_finnish.h`               |
| 法语 French                            | `keymap_french.h`                 | `sendstring_french.h`                |
| 法语 French (AFNOR)                    | `keymap_french_afnor.h`           | `sendstring_french_afnor.h`          |
| 法语 French (BÉPO)                     | `keymap_bepo.h`                   | `sendstring_bepo.h`                  |
| 法语 French (Belgium)                  | `keymap_belgian.h`                | `sendstring_belgian.h`               |
| 法语 French (Switzerland)              | `keymap_fr_ch.h`                  | `sendstring_fr_ch.h`                 |
| 法语 French (macOS, ISO)               | `keymap_french_osx.h`             | `sendstring_french_osx.h`            |
| 德语 German                            | `keymap_german.h`                 | `sendstring_german.h`                |
| 德语 German (Switzerland)              | `keymap_german_ch.h`              | `sendstring_german_ch.h`             |
| 德语 German (macOS)                    | `keymap_german_osx.h`             | `sendstring_german_osx.h`            |
| 德语 German (Neo2)                     | `keymap_neo2.h`                   |                                      |
| 希腊语 Greek                           | `keymap_greek.h`                  |                                      |
| 希伯来语 Hebrew                        | `keymap_hebrew.h`                 |                                      |
| 匈牙利语 Hungarian                     | `keymap_hungarian.h`              | `sendstring_hungarian.h`             |
| 冰岛语 Icelandic                       | `keymap_icelandic.h`              | `sendstring_icelandic.h`             |
| 意大利语 Italian                       | `keymap_italian.h`                | `sendstring_italian.h`               |
| 意大利语 Italian (macOS, ANSI)         | `keymap_italian_osx_ansi.h`       | `sendstring_italian_osx_ansi.h`      |
| 意大利语 Italian (macOS, ISO)          | `keymap_italian_osx_iso.h`        | `sendstring_italian_osx_iso.h`       |
| 日语 Japanese                          | `keymap_jp.h`                     | `sendstring_jis.h`                   |
| 韩语 Korean                            | `keymap_korean.h`                 |                                      |
| 拉脱维亚语 Latvian                     | `keymap_latvian.h`                | `sendstring_latvian.h`               |
| 立陶宛语 Lithuanian (ĄŽERTY)           | `keymap_lithuanian_azerty.h`      | `sendstring_lithuanian_azerty.h`     |
| 立陶宛语 Lithuanian (QWERTY)           | `keymap_lithuanian_qwerty.h`      | `sendstring_lithuanian_qwerty.h`     |
| 挪威语 Norwegian                       | `keymap_norwegian.h`              | `sendstring_norwegian.h`             |
| 波兰语 Polish                          | `keymap_polish.h`                 |                                      |
| 葡萄牙语 Portuguese                    | `keymap_portuguese.h`             | `sendstring_portuguese.h`            |
| 葡萄牙语 Portuguese (macOS, ISO)       | `keymap_portuguese_osx_iso.h`     | `sendstring_portuguese_osx_iso.h`    |
| 葡萄牙语 Portuguese (Brazil)           | `keymap_br_abnt2.h`               | `sendstring_br_abnt2.h`              |
| 罗马尼亚语 Romanian                    | `keymap_romanian.h`               | `sendstring_romanian.h`              |
| 俄语 Russian                           | `keymap_russian.h`                |                                      |
| 塞尔维亚语 Serbian                     | `keymap_serbian.h`                |                                      |
| 塞尔维亚语 Serbian (Latin)             | `keymap_serbian_latin.h`          | `sendstring_serbian_latin.h`         |
| 斯洛伐克语 Slovak                      | `keymap_slovak.h`                 | `sendstring_slovak.h`                |
| 斯洛维尼亚语 Slovenian                 | `keymap_slovenian.h`              | `sendstring_slovenian.h`             |
| 西班牙语 Spanish                       | `keymap_spanish.h`                | `sendstring_spanish.h`               |
| 西班牙语 Spanish (Dvorak)              | `keymap_spanish_dvorak.h`         | `sendstring_spanish_dvorak.h`        |
| 瑞典语 Swedish                         | `keymap_swedish.h`                | `sendstring_swedish.h`               |
| 瑞典语 Swedish (macOS, ANSI)           | `keymap_swedish_osx_ansi.h`       |                                      |
| 瑞典语 Swedish (macOS, ISO)            | `keymap_swedish_osx_iso.h`        |                                      |
| 瑞典语 Swedish Pro (macOS, ANSI)       | `keymap_swedish_pro_osx_ansi.h`   |                                      |
| 瑞典语 Swedish Pro (macOS, ISO)        | `keymap_swedish_pro_osx_iso.h`    |                                      |
| 土耳其语 Turkish (F)                   | `keymap_turkish_f.h`              | `sendstring_turkish_f.h`             |
| 土耳其语 Turkish (Q)                   | `keymap_turkish_q.h`              | `sendstring_turkish_q.h`             |

这里还有一些不是完全特定语言的，如果你不使用 QWERTY 布局会用到：

| 布局                | 键码头文件               | Sendstring LUT 头文件        |
| ------------------- | ------------------------ | ---------------------------- |
| Colemak             | `keymap_colemak.h`       | `sendstring_colemak.h`       |
| Dvorak              | `keymap_dvorak.h`        | `sendstring_dvorak.h`        |
| Dvorak (French)     | `keymap_dvorak_fr.h`     | `sendstring_dvorak_fr.h`     |
| Dvorak (Programmer) | `keymap_dvp.h`           | `sendstring_dvp.h`           |
| Norman              | `keymap_norman.h`        | `sendstring_norman.h`        |
| Plover              | `keymap_plover.h`        |                              |
| Plover (Dvorak)     | `keymap_plover_dvorak.h` |                              |
| Steno               | `keymap_steno.h`         |                              |
| Workman             | `keymap_workman.h`       | `sendstring_workman.h`       |
| Workman (ZXCVM)     | `keymap_workman_zxcvm.h` | `sendstring_workman_zxcvm.h` |
