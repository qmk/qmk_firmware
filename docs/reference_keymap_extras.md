# Language-specific Keycodes

Keyboards are able to support a wide range of languages. However, they do not send the actual characters produced by pressing their keys - instead, they send numerical codes. In the USB HID spec, these are called "usages", although they are more often referred to as "scancodes" or "keycodes" when in the context of keyboards.
Less than 256 usages are defined in the HID Keyboard/Keypad usage page, and some of those do nothing on modern operating systems. So, how is this language support achieved?

In a nutshell, the operating system maps the usages it receives to the appropriate character based on the user's configured keyboard layout. For example, when a Swedish person presses the key with the `å` character printed on it, the keyboard is *actually* sending the keycode for `[`.

Obviously, this could get confusing, so QMK provides language-specific keycode aliases for many keyboard layouts. These won't do much on their own - you still have to set the matching keyboard layout in your OS settings. Think of them more as keycap labels for your keymap.

To use these, simply `#include` the corresponding [header file](https://github.com/qmk/qmk_firmware/tree/master/quantum/keymap_extras) in your `keymap.c`, and add the keycodes defined in them in place of the `KC_` prefixed ones:

|Layout                     |Header                          |
|---------------------------|--------------------------------|
|Canadian Multilingual (CSA)|`keymap_canadian_multilingual.h`|
|Croatian                   |`keymap_croatian.h`             |
|Czech                      |`keymap_czech.h`                |
|Danish                     |`keymap_danish.h`               |
|Dutch (Belgium)            |`keymap_belgian.h`              |
|English (Ireland)          |`keymap_irish.h`                |
|English (UK)               |`keymap_uk.h`                   |
|English (US International) |`keymap_us_international.h`     |
|Estonian                   |`keymap_estonian.h`             |
|Finnish                    |`keymap_finnish.h`              |
|French                     |`keymap_french.h`               |
|French (AFNOR)             |`keymap_french_afnor.h`         |
|French (BÉPO)              |`keymap_bepo.h`                 |
|French (Belgium)           |`keymap_belgian.h`              |
|French (Switzerland)       |`keymap_fr_ch.h`                |
|French (macOS, ISO)        |`keymap_french_osx.h`           |
|German                     |`keymap_german.h`               |
|German (Switzerland)       |`keymap_german_ch.h`            |
|German (macOS)             |`keymap_german_osx.h`           |
|German (Neo2)*             |`keymap_neo2.h`                 |
|Greek*                     |`keymap_greek.h`                |
|Hebrew*                    |`keymap_hebrew.h`               |
|Hungarian                  |`keymap_hungarian.h`            |
|Icelandic                  |`keymap_icelandic.h`            |
|Italian                    |`keymap_italian.h`              |
|Italian (macOS, ANSI)      |`keymap_italian_osx_ansi.h`     |
|Italian (macOS, ISO)       |`keymap_italian_osx_iso.h`      |
|Japanese                   |`keymap_jp.h`                   |
|Korean                     |`keymap_korean.h`               |
|Latvian                    |`keymap_latvian.h`              |
|Lithuanian (ĄŽERTY)        |`keymap_lithuanian_azerty.h`    |
|Lithuanian (QWERTY)        |`keymap_lithuanian_qwerty.h`    |
|Norwegian                  |`keymap_norwegian.h`            |
|Polish                     |`keymap_polish.h`               |
|Portuguese                 |`keymap_portuguese.h`           |
|Portuguese (macOS, ISO)    |`keymap_portuguese_osx_iso.h`   |
|Portuguese (Brazil)        |`keymap_br_abnt2.h`             |
|Romanian                   |`keymap_romanian.h`             |
|Russian*                   |`keymap_russian.h`              |
|Serbian*                   |`keymap_serbian.h`              |
|Serbian (Latin)            |`keymap_serbian_latin.h`        |
|Slovak                     |`keymap_slovak.h`               |
|Slovenian                  |`keymap_slovenian.h`            |
|Spanish                    |`keymap_spanish.h`              |
|Spanish (Dvorak)           |`keymap_spanish_dvorak.h`       |
|Swedish                    |`keymap_swedish.h`              |
|Turkish (F)                |`keymap_turkish_f.h`            |
|Turkish (Q)                |`keymap_turkish_q.h`            |

There are also a few which are not quite language-specific, but useful if you are not using a QWERTY layout:

|Layout             |Header                  |
|-------------------|------------------------|
|Colemak            |`keymap_colemak.h`      |
|Dvorak             |`keymap_dvorak.h`       |
|Dvorak (French)    |`keymap_dvorak_fr.h`    |
|Dvorak (Programmer)|`keymap_dvp.h`          |
|Norman             |`keymap_norman.h`       |
|Plover*            |`keymap_plover.h`       |
|Plover (Dvorak)*   |`keymap_plover_dvorak.h`|
|Steno*             |`keymap_steno.h`        |
|Workman            |`keymap_workman.h`      |
|Workman (ZXCVM)    |`keymap_workman_zxcvm.h`|

## Sendstring Support

By default, `SEND_STRING()` assumes a US ANSI keyboard layout is set. If you are using a different layout, you can also `#include "sendstring_*.h"` (as above) in your keymap to override the lookup tables used for mapping ASCII characters to keycodes.

An important thing to note here is that `SEND_STRING()` only operates on [ASCII text](https://en.wikipedia.org/wiki/ASCII#Character_set). This means that you cannot pass it a string containing Unicode characters - this unfortunately includes accented characters that may be present in your desired layout.  
Many layouts make certain characters, such as Grave or Tilde, available only as [dead keys](https://en.wikipedia.org/wiki/Dead_key), so you must add a space immediately after it in the string you want to send, to prevent it from potentially combining with the next character.  
Certain other layouts have no Sendstring header as they do not use a Latin-derived alphabet (for example Greek and Russian), and thus there is no way to input most of the ASCII character set. These are marked above with a `*`.
