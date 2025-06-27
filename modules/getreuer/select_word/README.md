# Select Word

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/select_word</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/select-word">https://getreuer.info/posts/keyboards/select-word</a>
</td></tr>
</table>

This is a community module adaptation of [Select
Word](https://getreuer.info/posts/keyboards/select-word) for selecting words and
lines, assuming conventional text editing hotkeys. 

## Use

Add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/select_word"]
}
```

Then use one or more of the following keycodes in your layout:

| Keycode            | Short alias | Description                                            |
|--------------------|-------------|--------------------------------------------------------|
| `SELECT_WORD`      | `SELWORD`   | Forward word selection. Or with Shift, line selection. |
| `SELECT_WORD_BACK` | `SELWBAK`   | Backward word selection.                               |
| `SELECT_WORD_LINE` | `SELLINE`   | Line selection.                                        |

Press `SELWORD` to select the current word. Press it again to extend the
selection to the following word. The effect is similar to word selection (`W`)
in the [Kakoune editor](https://kakoune.org). Or for line selection, press
`SELWORD` with shift to select the current line, and press it again to extend
the selection to the following line.

## Mac hotkeys

Different hotkeys are needed to perform word and line selection on Mac OS. There
are several ways that Select Word can be configured to send the appropriate
hotkeys:

* To hardcode to Mac hotkeys, define in your `config.h` file:

  ~~~{.c}
  #define SELECT_WORD_OS_MAC
  ~~~

* If [OS Detection](https://docs.qmk.fm/features/os_detection) is enabled,
  Select Word uses it determine which kind of hotkeys to send. 

* For direct control, define in `config.h`:

  ~~~{.c}
  #define SELECT_WORD_OS_DYNAMIC
  ~~~

  Then in `keymap.c`, define the callback `select_word_host_is_mac()`. Return
  true for Mac hotkeys, false for Windows/Linux.

See the [Select Word
documentation](https://getreuer.info/posts/keyboards/select-word) for further
configuration options and details.

