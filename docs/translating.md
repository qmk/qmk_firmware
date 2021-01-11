# How to translate the QMK docs into different languages

All files in the root folder (`docs/`) should be in English - all other languages should be in subfolders with the ISO 639-1 language codes, followed by `-` and the country code where relevant. [A list of common ones can be found here](https://www.andiamo.co.uk/resources/iso-language-codes/). If this folder doesn't exist, you may create it. Each of the translated files should have the same name as the English version, so things can fall back successfully.

A `_summary.md` file should exist in this folder with a list of links to each file, with a translated name, and link preceded by the language folder:

    * [QMK简介](zh-cn/getting_started_introduction.md)

Once you've finished translating a new language, you'll also need to modify the following files:

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)  
  Each line should contain a country flag in the format `:us:` followed by the name represented in its own language:  
  
      - [:cn: 中文](/zh-cn/)

* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)  
  Both `placeholder` and `noData` objects should have a dictionary entry for the language folder in a string:  
  
      '/zh-cn/': '没有结果!',

## Previewing the translations

Before opening a pull request, you can preview your additions if you have Python 3 installed by running this command in the `docs/` folder:

    python -m http.server 9000

and navigating to http://localhost:9000/ - you should be able to select your new language from the "Translations" menu at the top-right.

Once you're happy with your work, feel free to open a pull request!
