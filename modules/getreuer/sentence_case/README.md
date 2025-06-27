# Sentence Case

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/sentence_case</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/sentence-case">https://getreuer.info/posts/keyboards/sentence-case</a>
</td></tr>
</table>

This is a community module adaptation of [Sentence
Case](https://getreuer.info/posts/keyboards/sentence-case) to automatically
capitalize the first letter of sentences. This reduces how often you need to use
the Shift keys, which is convenient particularly if you use home row mods or
Auto Shift.

Add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/sentence_case"]
}
```

NOTE: One-shot keys must be enabled.

Then, simply type as usual but without shifting at the start of sentences. The
feature detects when new sentences begin and capitalizes automatically.

In detecting new sentences, Sentence Case matches patterns like

    "a. a"
    "a.  a"
    "a? a"
    "a!' 'a"

but not

    "a... a"
    "a.a. a"

Additionally by default, abbreviations "`vs.`" and "`etc.`" are exceptionally
detected as not real sentence endings. 

Sentence Case is on by default. The following keycodes change its status. Use
function `is_sentence_case_on()` to query its status.

| Keycode                | Description               |
|------------------------|---------------------------|
| `SENTENCE_CASE_ON`     | Turn Sentence Case on.    |
| `SENTENCE_CASE_OFF`    | Turn Sentence Case off.   |
| `SENTENCE_CASE_TOGGLE` | Toggle Sentence Case.     |

Optionally, you can use the callback `sentence_case_check_ending()` to define
other exceptions, and there are callbacks and config options to customize
Sentence Case. See the [Sentence Case
documentation](https://getreuer.info/posts/keyboards/sentence-case) for details.

