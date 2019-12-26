# Quantum Mechanical Keyboard Firmware

<!---
  original document: eae21eed7:docs/README.md
  git diff eae21eed7 HEAD docs/README.md | cat
-->

[![現在のバージョン](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![ビルド状態](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![ドキュメントの状態](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub 貢献者](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub フォーク](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## QMK ファームウェアとは何か？

QMK (*Quantum Mechanical Keyboard*)は QMK ファームウェア、QMK ツールボックス、qmk.fm およびそれらのドキュメントを保守するオープンソースコミュニティです。QMK ファームウェアは[tmk\_keyboard](http://github.com/tmk/tmk_keyboard) を元にしたキーボードファームウェアで、Atmel AVR コントローラ、より具体的には [OLKB 製品](http://olkb.com)、[ErgoDox EZ](http://www.ergodox-ez.com) キーボードおよび [Clueboard 製品](http://clueboard.co/) のための幾つかの便利な機能を持ちます。また、ChibiOS を使って ARM チップに移植されています。これを使ってあなたの作った手配線のキーボードあるいはカスタムキーボード PCB で作ったキーボードを動かすことができます。

## 入手方法

QMK のキーマップ、キーボード、機能に貢献をする予定がある場合、最も簡単なのは、[Github を介してリポジトリをフォークし](https://github.com/qmk/qmk_firmware#fork-destination-box)、リポジトリをあなたの開発環境にクローンして変更を加え、それらをプッシュし、[プルリクエスト](https://github.com/qmk/qmk_firmware/pulls)を開くことです。

それ以外の場合は、`git clone https://github.com/qmk/qmk_firmware` を介して直接クローンすることができます。zip または tar ファイルをダウンロードしないでください。コンパイルするためのサブモジュールをダウンロードするために git リポジトリが必要です。

## コンパイル方法

コンパイルをする前に、AVR または ARM 開発のための[環境をインストール](ja/getting_started_build_tools.md)する必要があります。それが完了したら、`make` コマンドを使用して、以下の表記でキーボードとキーマップをビルドします。

    make planck/rev4:default

これは、`planck` の `rev4` リビジョンを `default` キーマップでビルドします。全てのキーボードにリビジョン(サブプロジェクトまたはフォルダとも呼ばれます)があるわけではありません。その場合は省略されます:

    make preonic:default

## カスタマイズ方法

QMK には、探求すべき多くの[機能](ja/features.md)と、深堀りするための[リファレンス ドキュメント](http://docs.qmk.fm)がたくさんあります。ほとんどの機能は[キーマップ](ja/keymap.md)を変更し、[キーコード](ja/keycodes.md)を変更することで活用されます。
