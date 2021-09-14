# ドキュメントテンプレート

<!---
  original document: 0.13.15:docs/documentation_templates.md
  git diff 0.13.15 HEAD -- docs/documentation_templates.md | cat
-->

このページでは、新しいキーマップやキーボードを QMK に提出する際に使うべきテンプレートをまとめています。

## キーマップ `readme.md` テンプレート :id=keyboard-readmemd-template

ほとんどのキーマップには、レイアウトを表す画像があります。画像を作成するには、[Keyboard Layout Editor](https://keyboard-layout-editor.com) を使うことができます。画像は [Imgur](https://imgur.com) や別のホスティングサービスにアップロードし、プルリクエストに画像を含めないでください。

画像の下には、キーマップを理解してもらうための簡単な説明文を書いてください。

```
![Clueboard Layout Image](https://i.imgur.com/7Capi8W.png)

# Default Clueboard Layout

This is the default layout that comes flashed on every Clueboard. For the most
part it's a straightforward and easy to follow layout. The only unusual key is
the key in the upper left, which sends Escape normally, but Grave when any of
the Ctrl, Alt, or GUI modifiers are held down.
```

## キーボード `readme.md` テンプレート

```
# Planck

![Planck](https://i.imgur.com/q2M3uEU.jpg)

A compact 40% (12x4) ortholinear keyboard kit made and sold by OLKB and Massdrop. [More info on qmk.fm](https://qmk.fm/planck/)

* Keyboard Maintainer: [Jack Humbert](https://github.com/jackhumbert)
* Hardware Supported: Planck PCB rev1, rev2, rev3, rev4, Teensy 2.0
* Hardware Availability: [OLKB.com](https://olkb.com), [Massdrop](https://www.massdrop.com/buy/planck-mechanical-keyboard?mode=guest_open)

Make example for this keyboard (after setting up your build environment):

    make planck/rev4:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
```
