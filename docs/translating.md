# Translating the different parts of QMK

English is the primary language in most of QMK, but there's no reason it should be the only! The `en` tag is used for English because the docs we have currently have been written by a wide range of English speakers, so it would be difficult to determine their exact locale. All others should follow IETF's BCP 47 [language tags](https://www.w3.org/International/articles/language-tags/), where the shortest language tag is preferred, without causing confusion. Tags may be made more specific in the future if additional languages are added. All language tags in QMK should be lowercase.

## How to translate the QMK docs

All files in the root folder (`docs/`) should be in English - all other languages should be in subfolders named using their language tag. If this folder doesn't exist, you may create it. Each of the translated files should have the same name as the English version, so things can fall back successfully.

A `_summary.md` file should exist in this folder with a list of links to each file, with a translated name, and link preceded by the language folder:

    * [QMK简介](zh-cn/getting_started_introduction.md)

Once you've finished translating a new language, you'll also need to modify the following files:

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)  
  Each line should contain a country flag in the format `:us:` followed by the name represented in its own language:  
  
      - [:cn: 中文](/zh-cn/)

* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)  
  Both `placeholder` and `noData` objects should have a dictionary entry for the language folder in a string:  
  
      '/zh-cn/': '没有结果!',

### Previewing the translations

Before opening a pull request, you can preview your additions if you have Python 3 installed by running this command in the `docs/` folder:

    python -m http.server 9000

and navigating to http://localhost:9000/ - you should be able to select your new language from the "Translations" menu at the top-right.

Once you're happy with your work, feel free to open a pull request!

## How to add translations of the qmk.fm website

Each language should have its own folder in `_i18n/`, named using their language tag.

Permalinks should be generated automatically from the filename, but need to be set manually for `index.md` pages. The `lang` variable should be set on all pages. Both of these, along with `title` (used in `<title>` in the head, and other metadata) are examplified in the front matter (put at the top of the file) here:

    ---
    title: "QMK固件"
    permalink: /zh-cn/
    lang: "zh-cn"
    ---

A `summary.md` is needed to render the sidebar content - `_includes/en_sidebar.md` should be used as the template. Links should be relativised with the language preceding it: `/zh-cn/support`.

The `_data/strings.yml` file also needs to have an entry for the language:

      zh-cn: &DEFAULT_ZH_CN
        <<: *DEFAULT_EN
        language_name: "中文"
        language: "官话"
        qmk_firmware: "QMK固件"

The `<<: *DEFAULT_EN` allows `zh-cn` to inherit all values from the English entry, and the keys following it override those. It's recommended to translate all entries for full coverage.

## How to add translations to the QMK Configurator

1. Copy the [en/](https://github.com/qmk/qmk_configurator/tree/master/src/i18n/en) folder
2. Rename it using the appropriate language tag
3. Edit each variable in the `.js` files to the appropriate word/phrase 
4. Edit the main [index.js](https://github.com/qmk/qmk_configurator/blob/master/src/i18n/index.js) to include
   ```js
   import <tag> from './<tag>';
   ```
   and
   ```js
     ...<tag>,
   ``` 
   in the correct spots, with `<tag>` replaced with your language tag/folder name.  
5. Open a [Pull Request](https://github.com/qmk/qmk_configurator/pulls)!