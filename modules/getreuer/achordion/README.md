# Achordion

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/achordion</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/achordion">https://getreuer.info/posts/keyboards/achordion</a>
</td></tr>
</table>

This is a community module adaptation of
[Achordion](https://getreuer.info/posts/keyboards/achordion), a customizable
"opposite hands" rule implementation for tap-hold keys. Achordion is the
predecessor of QMK core feature [Chordal
Hold](https://docs.qmk.fm/tap_hold#chordal-hold).

Add the following to your `keymap.json` to use Achordion:

```json
{
    "modules": ["getreuer/achordion"]
}
```

Optionally, Achordion can be customized through several callbacks and config
options. See the [Achordion
documentation](https://getreuer.info/posts/keyboards/achordion) for how to do
that and further details.

