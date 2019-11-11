# Quantum メカニカル キーボード ファームウェア

[![現在のバージョン](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![ビルド状態](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![ドキュメントの状態](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub貢献者](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub フォーク](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## QMK ファームウェアとは何か？

QMK (*Quantum Mechanical Keyboard*)は QMK ファームウェア、QMK ツールボックス、qmk.fm およびそれらのドキュメントを保守するオープンソースコミュニティです。QMK ファームウェアは[tmk\_keyboard](http://github.com/tmk/tmk_keyboard) を元にしたキーボード ファームウェアで、Atmel AVR コントローラ、より具体的には[OLKB product line](http://olkb.com)、[ErgoDox EZ](http://www.ergodox-ez.com) キーボードおよび [Clueboard product line](http://clueboard.co/)のための幾つかの便利な機能を持ちます。また、ChibiOS を使って ARM チップに移植されています。これを使ってあなたの作った手配線のキーボードあるいはカスタムキーボードPCBで作ったキーボードを動かすことができます。

## 入手方法

キーマップ、キーボードあるいはQMKへの機能に貢献をする予定がある場合、最も簡単なのは、[Githubを介してレポジトリをフォークし](https://github.com/qmk/qmk_firmware#fork-destination-box)、レポジトリをあなたの開発環境にクローンして変更を加え、それらをプッシュし、[プルリクエスト](https://github.com/qmk/qmk_firmware/pulls)を開くことです。

それ以外の場合は、直接ダウンロード([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master))するか、あるいは git (`git@github.com:qmk/qmk_firmware.git`) または https (`https://github.com/qmk/qmk_firmware.git`) を介してクローンすることができます。

## コンパイル方法

コンパイルをする前に、AVR または ARM 開発のための[環境をインスト―ル](getting_started_build_tools.md)する必要があります。それが完了したら、`make` コマンドを使用して、以下の表記でキーボードとキーマップをビルドします。

    make planck/rev4:default

これは、`planck` の `rev4` リビジョンを `default` キーマップでビルドします。全てのキーボードにリビジョン(サブプロジェクトまたはフォルダとも呼ばれます)があるわけではありません。その場合は省略されます:

    make preonic:default

## カスタマイズ方法

QMK には、探求すべき多くの[機能](features.md)と、深堀りするための[リファレンス ドキュメント](http://docs.qmk.fm)がたくさんあります。ほとんどの機能は[キーマップ](keymap.md)を変更し、[キーコード](keycodes.md)を変更することで活用されます。
