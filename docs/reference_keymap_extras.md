# Language-specific Keycodes

Keyboards are able to support a wide range of languages. However, this support is not actually achieved within the keyboard itself - instead, it sends numerical codes, which the operating system maps to the appropriate characters depending on the user's configured keyboard layout. By default (and per the HID spec), this is the US ANSI layout. For example, when a Swedish person presses the key with the `å` character printed on it, the keyboard is *actually* sending the keycode for `[`.

Obviously, this can get confusing, so QMK provides language-specific keycode aliases for many keyboard layouts. These won't do much on their own - you still have to set the matching keyboard layout in your OS settings. Think of them more as keycap labels for your keymap.

Simply `#include` one of the keycode headers below at the top of your `keymap.c`, and assign the keycodes defined in the header in place of the `KC_` prefixed ones.

## Sendstring Support

By default, `SEND_STRING()` assumes a US ANSI keyboard layout is set. If you are using a different layout, you can include one of the Sendstring LUT headers below in your `keymap.c` to override the lookup tables used for mapping ASCII characters to keycodes. You do not need to include the corresponding `keymap_*.h` header, as it is implicit when including the Sendstring header.

An important thing to note here is that `SEND_STRING()` only operates on [ASCII text](https://en.wikipedia.org/wiki/ASCII#Character_set). This means that you cannot pass it a string containing Unicode characters - this unfortunately includes accented characters that may be present in your desired layout.  
Many layouts make certain characters, such as Grave or Tilde, available only as [dead keys](https://en.wikipedia.org/wiki/Dead_key), so you must add a space immediately after it in the string you want to send, to prevent it from potentially combining with the next character.  
Certain other layouts have no Sendstring header as they do not use a Latin-derived alphabet (for example Greek and Russian), and thus there is no way to input most of the ASCII character set.

## Header Files

These headers are located in [`quantum/keymap_extras/`](https://github.com/qmk/qmk_firmware/tree/master/quantum/keymap_extras).

|Layout                           |Keycodes Header                  |Sendstring LUT Header               |
|---------------------------------|---------------------------------|------------------------------------|
|Canadian Multilingual (CSA)      |`keymap_canadian_multilingual.h` |`sendstring_canadian_multilingual.h`|
|Croatian                         |`keymap_croatian.h`              |`sendstring_croatian.h`             |
|Czech                            |`keymap_czech.h`                 |`sendstring_czech.h`                |
|Czech (macOS, ANSI)              |`keymap_czech_mac_ansi.h`        |`sendstring_czech_mac_ansi.h`       |
|Czech (macOS, ISO)               |`keymap_czech_mac_iso.h`         |`sendstring_czech_mac_iso.h`        |
|Danish                           |`keymap_danish.h`                |`sendstring_danish.h`               |
|Dutch (Belgium)                  |`keymap_belgian.h`               |`sendstring_belgian.h`              |
|English (Ireland)                |`keymap_irish.h`                 |                                    |
|English (UK)                     |`keymap_uk.h`                    |`sendstring_uk.h`                   |
|English (US Extended)            |`keymap_us_extended.h`           |                                    |
|English (US International)       |`keymap_us_international.h`      |`sendstring_us_international.h`     |
|English (US International, Linux)|`keymap_us_international_linux.h`|                                    |
|Estonian                         |`keymap_estonian.h`              |`sendstring_estonian.h`             |
|Farsi                            |`keymap_farsi.h`                 |                                    |
|Finnish                          |`keymap_finnish.h`               |`sendstring_finnish.h`              |
|French                           |`keymap_french.h`                |`sendstring_french.h`               |
|French (AFNOR)                   |`keymap_french_afnor.h`          |`sendstring_french_afnor.h`         |
|French (BÉPO)                    |`keymap_bepo.h`                  |`sendstring_bepo.h`                 |
|French (Belgium)                 |`keymap_belgian.h`               |`sendstring_belgian.h`              |
|French (Canada)                  |`keymap_canadian_french.h`       |`sendstring_canadian_french.h`      |
|French (Switzerland)             |`keymap_swiss_fr.h`              |`sendstring_swiss_fr.h`             |
|French (macOS, ISO)              |`keymap_french_mac_iso.h`        |`sendstring_french_mac_iso.h`       |
|German                           |`keymap_german.h`                |`sendstring_german.h`               |
|German (Switzerland)             |`keymap_swiss_de.h`              |`sendstring_swiss_de.h`             |
|German (macOS)                   |`keymap_german_mac_iso.h`        |`sendstring_german_mac_iso.h`       |
|German (Neo2)                    |`keymap_neo2.h`                  |                                    |
|Greek                            |`keymap_greek.h`                 |                                    |
|Hebrew                           |`keymap_hebrew.h`                |                                    |
|Hungarian                        |`keymap_hungarian.h`             |`sendstring_hungarian.h`            |
|Icelandic                        |`keymap_icelandic.h`             |`sendstring_icelandic.h`            |
|Italian                          |`keymap_italian.h`               |`sendstring_italian.h`              |
|Italian (macOS, ANSI)            |`keymap_italian_mac_ansi.h`      |`sendstring_italian_mac_ansi.h`     |
|Italian (macOS, ISO)             |`keymap_italian_mac_iso.h`       |`sendstring_italian_mac_iso.h`      |
|Japanese                         |`keymap_japanese.h`              |`sendstring_japanese.h`             |
|Korean                           |`keymap_korean.h`                |                                    |
|Latvian                          |`keymap_latvian.h`               |`sendstring_latvian.h`              |
|Lithuanian (ĄŽERTY)              |`keymap_lithuanian_azerty.h`     |`sendstring_lithuanian_azerty.h`    |
|Lithuanian (QWERTY)              |`keymap_lithuanian_qwerty.h`     |`sendstring_lithuanian_qwerty.h`    |
|Norwegian                        |`keymap_norwegian.h`             |`sendstring_norwegian.h`            |
|Polish                           |`keymap_polish.h`                |                                    |
|Portuguese                       |`keymap_portuguese.h`            |`sendstring_portuguese.h`           |
|Portuguese (macOS, ISO)          |`keymap_portuguese_mac_iso.h`    |`sendstring_portuguese_mac_iso.h`   |
|Portuguese (Brazil)              |`keymap_brazilian_abnt2.h`       |`sendstring_brazilian_abnt2.h`      |
|Romanian                         |`keymap_romanian.h`              |`sendstring_romanian.h`             |
|Russian                          |`keymap_russian.h`               |                                    |
|Serbian                          |`keymap_serbian.h`               |                                    |
|Serbian (Latin)                  |`keymap_serbian_latin.h`         |`sendstring_serbian_latin.h`        |
|Slovak                           |`keymap_slovak.h`                |`sendstring_slovak.h`               |
|Slovenian                        |`keymap_slovenian.h`             |`sendstring_slovenian.h`            |
|Spanish                          |`keymap_spanish.h`               |`sendstring_spanish.h`              |
|Spanish (Dvorak)                 |`keymap_spanish_dvorak.h`        |`sendstring_spanish_dvorak.h`       |
|Spanish (Latin America)          |`keymap_spanish_latin_america.h` |`sendstring_spanish_latin_america.h`|
|Swedish                          |`keymap_swedish.h`               |`sendstring_swedish.h`              |
|Swedish (macOS, ANSI)            |`keymap_swedish_mac_ansi.h`      |                                    |
|Swedish (macOS, ISO)             |`keymap_swedish_mac_iso.h`       |                                    |
|Swedish Pro (macOS, ANSI)        |`keymap_swedish_pro_mac_ansi.h`  |                                    |
|Swedish Pro (macOS, ISO)         |`keymap_swedish_pro_mac_iso.h`   |                                    |
|Turkish (F)                      |`keymap_turkish_f.h`             |`sendstring_turkish_f.h`            |
|Turkish (Q)                      |`keymap_turkish_q.h`             |`sendstring_turkish_q.h`            |
|Ukrainian                        |`keymap_ukrainian.h`             |                                    |

There are also a few which are not quite language-specific, but useful if you are not using a QWERTY layout:

|Layout             |Keycodes Header             |Sendstring LUT Header           |
|-------------------|----------------------------|--------------------------------|
|Colemak            |`keymap_colemak.h`          |`sendstring_colemak.h`          |
|Dvorak             |`keymap_dvorak.h`           |`sendstring_dvorak.h`           |
|Dvorak (French)    |`keymap_dvorak_fr.h`        |`sendstring_dvorak_fr.h`        |
|Dvorak (Programmer)|`keymap_dvorak_programmer.h`|`sendstring_dvorak_programmer.h`|
|Norman             |`keymap_norman.h`           |`sendstring_norman.h`           |
|Plover             |`keymap_plover.h`           |                                |
|Plover (Dvorak)    |`keymap_plover_dvorak.h`    |                                |
|Workman            |`keymap_workman.h`          |`sendstring_workman.h`          |
|Workman (ZXCVM)    |`keymap_workman_zxcvm.h`    |`sendstring_workman_zxcvm.h`    |
