# Translating the QMK Docs

All files in the root folder (`docs/`) should be in English - all other languages should be in subfolders with the ISO 639-1 language codes, followed by `-` and the country code where relevant. [A list of common ones can be found here](https://www.andiamo.co.uk/resources/iso-language-codes/). If this folder doesn't exist, you may create it. Each of the translated files should have the same name as the English version, so things can fall back successfully.

A `_summary.md` file should exist in this folder with a list of links to each file, with a translated name, and link preceded by the language folder:

```markdown
 * [QMK简介](zh-cn/getting_started_introduction.md)
```

All links to other docs pages must also be prefixed with the language folder. If the link is to a specific part of the page (ie. a certain heading), you must use the English ID for the heading, like so:

```markdown
[建立你的环境](zh-cn/newbs-getting-started.md#set-up-your-environment)

## 建立你的环境 :id=set-up-your-environment
```

Once you've finished translating a new language, you'll also need to modify the following files:

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)  
  Each line should contain a country flag as a [GitHub emoji shortcode](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md#country-flag) followed by the name represented in its own language:

  ```markdown
   - [:cn: 中文](/zh-cn/)
  ```

* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)  
  Both `placeholder` and `noData` objects should have a dictionary entry for the language folder in a string:

  ```js
  '/zh-cn/': '没有结果!',
  ```

  The `nameLink` object, for setting the "QMK Firmware" heading link in the sidebar, must also be added to:

  ```js
  '/zh-cn/': '/#/zh-cn/',
  ```

  And make sure to add the language folder in the `fallbackLanguages` list, so it will properly fall back to English instead of 404ing:

  ```js
  fallbackLanguages: [
    // ...
    'zh-cn',
    // ...
  ],
  ```

## Previewing the Translations

See [Previewing the Documentation](contributing.md#previewing-the-documentation) for how to set up a local instance of the docs - you should be able to select your new language from the "Translations" menu at the top-right.

Once you're happy with your work, feel free to open a pull request!
