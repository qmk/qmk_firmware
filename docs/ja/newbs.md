# QMK 初心者ガイド

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: adf4acf59:docs/newbs.md
  git diff adf4acf59 HEAD docs/newbs.md | cat
-->

QMK は、メカニカルキーボード用の強力なオープンソースファームウェアです。
QMK を使用して、シンプルかつ強力な方法でキーボードをカスタマイズできます。
完全な初心者からプログラマーに至るまで、あらゆるスキルレベルの人々が QMK を使用してキーボードをカスタマイズしています。
このガイドは、あなたのスキルにかかわらず、同じことを行う手助けをします。

お使いのキーボードで QMK を実行できるかどうか不明ですか？
もし作成したキーボードがメカニカルキーボードの場合、実行できる可能性が高いです。
QMK は[多くの趣味のキーボード](http://qmk.fm/keyboards/)をサポートしているため、もし現在のキーボードで QMK を実行できない場合でも、ニーズに合ったキーボードを見つけるのに問題はないはずです。

## 概要

このガイドには7つの主要なセクションがあります。

* [はじめに](ja/newbs_getting_started.md)
* [コマンドラインを使用して初めてのファームウェアを構築する](ja/newbs_building_firmware.md)
* [オンライン GUI を使用して初めてのファームウェアを構築する](ja/newbs_building_firmware_configurator.md)
* [ファームウェアを書きこむ](ja/newbs_flashing.md)
* [テストとデバッグ](ja/newbs_testing_debugging.md)
* [QMK における Git 運用作法](ja/newbs_git_best_practices.md)
* [さらに学ぶための学習リソース](ja/newbs_learn_more_resources.md)

このガイドは、これまでソフトウェアをコンパイルしたことがない人を支援することに特化しています。
その観点から選択と推奨を行います。
これらの手順の多くには代替方法があり、これらの代替方法のほとんどをサポートしています。
タスクを達成する方法について疑問がある場合は、[案内を求めることができます](ja/getting_started_getting_help.md)。

## 追加のリソース(英語)

* [Thomas Baart's QMK Basics Blog](https://thomasbaart.nl/category/mechanical-keyboards/firmware/qmk/qmk-basics/) – 新規ユーザ視点から見た QMK ファームウェアの基本的な使用方法をカバーしたユーザ作成のブログ。

## 追加のリソース(日本語)

_日本語のリソース情報を募集中です。_
