# Documentation Capabilities

This page lays out the capabilities used by the QMK Firmware documentation, in order to aid future transitions to other page generators. Focuses mainly on things other than normal Markdown, as it's assumed that markdown generators should still function accordingly.

## Overall capabilities

Unrelated to styling, high-level tech.

* I18n -- translations to other languages: [_langs.md](_langs.md)
* Sidebar -- listing of pages by category: [_summary.md](_summary.md)
* Title anchors -- `:id=some-anchor-name`, used for direct linking to sections
    * Links to anchors:
        * Style 1: [early initialization](platformdev_chibios_earlyinit.md?id=board-init)
        * Style 2: [early initialization](platformdev_chibios_earlyinit.md#board-init)
        * Links to anchors on the same page, i.e. [Emoji](#emoji)
* Specifying CNAME for root domain -- `docs.qmk.fm`
* Moved pages, see `index.html`
* Text search
* Footnotes [like this][1]

<!-- Comments should not show up -->

<!-- Nor should
     multiline
     
     comments with
     
     newlines show up -->
     
     
### Dividing lines

---

<hr>

<hr/>

### Images

![QMK Color Wheel with HSV Values](https://i.imgur.com/vkYVo66.jpg)

<img src="gitbook/images/color-wheel.svg" alt="HSV Color Wheel" width="250"/>

### Lists

Newlines with `<br>`:

Line one<br>
Line two<br/>
Line three

Nested dotted:

* The PR is complete and ready to merge
* GitHub checks for the PR are green whenever possible
    * A "red" check may be disregarded by maintainers if the items flagged are unrelated to the change proposed in the PR
        * Modifications to existing files should not need to add license headers to pass lint, for instance.
        * If it's not directly related to your PR's functionality, prefer avoiding making a change.

Nested dashed:

- The PR is complete and ready to merge
- GitHub checks for the PR are green whenever possible
    - A "red" check may be disregarded by maintainers if the items flagged are unrelated to the change proposed in the PR
        - Modifications to existing files should not need to add license headers to pass lint, for instance.
        - If it's not directly related to your PR's functionality, prefer avoiding making a change.

Nested numbered:

1. The PR is complete and ready to merge
1. GitHub checks for the PR are green whenever possible
    1. A "red" check may be disregarded by maintainers if the items flagged are unrelated to the change proposed in the PR
        1. Modifications to existing files should not need to add license headers to pass lint, for instance.
        1. If it's not directly related to your PR's functionality, prefer avoiding making a change.
        
Nested mixed:

1. Add it to the schema in `data/schemas/keyboards.jsonschema`
1. Add a mapping in `data/maps`
1. (optional and discouraged) Add code to extract/generate it to:
  * `lib/python/qmk/info.py`
  * `lib/python/qmk/cli/generate/config_h.py`
  * `lib/python/qmk/cli/generate/rules_mk.py`

### Emoji :id=emoji

#### Direct:

👍🎉 First off, thanks for taking the time to read this and contribute! 🎉👍

#### As colon-name-colon:

:heavy_check_mark: : works and was tested

:o: : does not apply

:x: : not supported by MCU

### XML Entities

[`clueboard`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard)  &larr; This is the organization folder, there's no `rules.mk` file

1&ndash;4

Command+<code>&#96;</code>

## Styling

### CSS-ish

<b style="font-size:150%">This is 150% of normal sizing, and bold!</b>


### Tables

| Column A | Column B |
|----------|----------|
| Left     | Right    |

### Indented sections

> Indent without any sort of marker

?> Query, this?

!> Notification, damnit!

### Keyboard keys

<kbd>,</kbd>

<kbd>Right Alt</kbd>+<kbd>Right Shift</kbd>

1. Click <kbd>File</kbd> > <kbd>New</kbd> > <kbd>Makefile Project with Existing Code</kbd>

1. Click <kbd><kbd>File</kbd> > <kbd>Preferences ></kbd> > <kbd>Settings</kbd> </kbd>

1. Hit Ctrl-<code>&#96;</code> (Grave) to bring up the terminal or go to <kbd><kbd>View</kbd> > <kbd>Terminal</kbd></kbd> (command `workbench.action.terminal.toggleTerminal`). A new terminal will be opened if there isn‘t one already.

   This should start the terminal in the workspace's folder (so the `qmk_firmware` folder), and then you can compile your keyboard. 


### Code Blocks

Inline code with tag: <code>test</code>

Inline code with backticks: `test`

    This is preformatted
    Indented by 4 spaces
    The letters lined up

```c
int c_code(void) {
    return -1;
}
```

```makefile
ifeq ($(BUILD),)
     CHUNDER_REQUIRED = yes
endif
```

```python
from pathlib import Path

p = Path('/path/to/qmk_firmware')
```

```json
{
    "a": "b",
    "c": 4,
    "d": {
        "e": [
            0, 1, 2, 3
        ]
    }
}
```

```diff
 #undef RGBLIGHT_LED_COUNT
+#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
+#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
 #define RGBLIGHT_LED_COUNT 12
 #define RGBLIGHT_HUE_STEP 8
 #define RGBLIGHT_SAT_STEP 8
```

Indented code as part of a list:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Teensy Loader Command Line](https://www.pjrc.com/teensy/loader_cli.html) / `:teensy` target in QMK (recommended command line)
  ```
  teensy_loader_cli -v -mmcu=<mcu> <filename>
  ```


### Sub/Superscript

<sub>This is subscripted, apparently.</sub>

<sup>This is superscripted, apparently.</sup>

I<sup>2</sup>C

T<sub>0H</sub>, T<sub>0L</sub>

### Tabs

Tabs are based on section headers, with `**` enclosing the tab title.

<!-- tabs:start -->

#### ** Tab one **

Content one

<!-- tabs:start -->

##### ** Nested one **

Nested content one

##### ** Nested two **

Nested content two

<!-- tabs:end -->

#### ** Tab two **

Content two

#### ** Tab three **

Content three

<!-- tabs:end -->

## Details sections

Expandable:

<details>
    <summary>Some summary text that shows up before expanding</summary>

!> Embedded notification!

This is some inner content.
</details>

  [1]: https://en.wikipedia.org/wiki/Eclipse_(software)

## Embed

[example embed](__capabilities_inc.md ':include')
