# QMK キーボードガイドライン

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: c9e3fa6f7:docs/hardware_keyboard_guidelines.md
  git diff c9e3fa6f7 HEAD -- docs/hardware_keyboard_guidelines.md | cat
-->

QMKは開始以来、コミュニティにおけるキーボードの作成や保守に貢献しているあなたのような人たちのおかげで飛躍的に成長しました。私たちが成長するにつれて、うまくやるためのいくつかのパターンを発見しました。他の人たちがあなたの苦労の恩恵を受けやすくするため、それにあわせてもらえるようお願いします。

## あなたのキーボード/プロジェクトの名前を決める

キーボードの名前は全て小文字で、アルファベット、数字、アンダースコア(`_`)のみで構成されています。アンダースコア(`_`)で始めてはいけません。スラッシュ(`/`)はサブフォルダの区切り文字として使用されます。

`test`、`keyboard`、`all`はmakeコマンドように予約されており、キーボードまたはサブフォルダ名として使用することは出来ません。

正しい例:

* `412_64`
* `chimera_ortho`
* `clueboard/66/rev3`
* `planck`
* `v60_type_r`

## サブフォルダ

QMKでは、整理するためやキーボードのリビジョン間でコードを共有するためにサブフォルダを使用します。フォルダは最大4階層までネストできます。

    qmk_firmware/keyboards/top_folder/sub_1/sub_2/sub_3/sub_4

サブフォルダ内に`rules.mk`ファイルが存在する場合、コンパイル可能なキーボードとして見なされます。QMKコンフィギュレータから使用できるようになり、`make all`でテストされます。同じメーカーのキーボードをまとめるためにフォルダを使用している場合は`rules.mk`ファイルを置いてはいけません。

例:

Clueboardは、サブフォルダを整理とキーボードのリビジョン管理の両方のために使用しています。

* [`qmk_firmware`](https://github.com/qmk/qmk_firmware/tree/master)
  * [`keyboards`](https://github.com/qmk/qmk_firmware/tree/master/keyboards)
    * [`clueboard`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard)  &larr; これはまとめるためのフォルダです。 `rules.mk`ファイルはありません。
      * [`60`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/60)  &larr; これはコンパイルできるキーボードです。`rules.mk`が存在します。
      * [`66`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66) &larr; これもコンパイルできるキーボードです。 デフォルトのリビジョンとして`DEFAULT_FOLDER`に`rev3`を指定しています。
        * [`rev1`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev1) &larr; コンパイル可能: `make clueboard/66/rev1`
        * [`rev2`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev2) &larr; コンパイル可能: `make clueboard/66/rev2`
        * [`rev3`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev3) &larr; コンパイル可能: `make clueboard/66/rev3` もしくは `make clueboard/66`

## キーボードのフォルダ構成

キーボードは`qmk_firmware/keyboards/`内にあって、前のセクションで説明したように、フォルダ名はキーボードの名前にする必要があります。このフォルダ内にはいくつかのファイルがあります。

* `readme.md`
* `info.json`
* `config.h`
* `rules.mk`
* `<keyboard_name>.c`
* `<keyboard_name>.h`

### `readme.md`

全てのプロジェクトにはどのようなキーボードなのか、誰が設計したか、どこで入手できるかを説明する`readme.md`ファイルが必要です。もしあるなら、メーカーのWebサイトなどの詳しい情報へのリンクも含める必要があります。[キーボード readme テンプレート](documentation_templates.md#keyboard-readmemd-template)を参考にして下さい。

### `info.json`

このファイルは[QMK API](https://github.com/qmk/qmk_api)から使用されます。[QMK Configurator](https://config.qmk.fm/)が必要とするキーボードの情報が含まれています。ここでメタデータを設定することもできます。詳しくは[info.json 形式](reference_info_json.md)を参照して下さい。

### `config.h`

全てのプロジェクトには、マトリクスサイズ、製品名、USB VID/PID、説明、その他の設定などが含まれた`config.h`が必要です。一般に、このファイルを使用して通常、機能するキーボードの重要な情報やデフォルトを設定します。

### `rules.mk`

このファイルが存在するということは、フォルダがキーボードであり、`make`コマンドで使用できることを意味します。ここでキーボードのビルド環境を構築し、デフォルトの機能を設定します。

### `<keyboard_name.c>`

ここではキーボードのカスタマイズされたコードを記述します。通常、初期化してキーボードのハードウェアを制御するコードを記述します。キーボードがLEDやスピーカー、その他の付属ハードウェアのないキーマトリクスのみで構成されている場合は空白にできます。

通常、以下の関数がこのファイルで定義されます。

* `void matrix_init_kb(void)`
* `void matrix_scan_kb(void)`
* `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* `void led_set_kb(uint8_t usb_led)`

### `<keyboard_name.h>`

このファイルはキーボードのマトリクスを定義するために使用されます。配列をキーボードの物理的なスイッチマトリクスに変換するCマクロを最低限1つ定義する必要があります。複数のレイアウトでキーボードを構築出来る場合は、追加のマクロを定義しなければいけません。

レイアウトが1つしかない場合は、このマクロを`LAYOUT`とします。

複数のレイアウトを定義する場合、物理的に構成することが出来なくとも、マトリクス上で全てのスイッチ位置をサポートする`LAYOUT_all`という名前の基本となるレイアウトが必要です。これは`default`キーマップで使用すべきマクロです。次に、他のレイアウトマクロを使用する`default_<layout>`といった追加のキーマップを用意します。これによって、他の人が定義されたレイアウトを使いやすくなります。

レイアウトマクロの名前は全て小文字で、先頭の`LAYOUT`だけ大文字です。

例として、ANSIとISOをサポートする60% PCBがある場合、以下のようにレイアウトとキーマップを定義出来ます。

| レイアウト名 | キーマップ名 | 説明 |
|-------------|-------------|-------------|
| LAYOUT_all | default | ISOとANSIのどちらもサポートしたレイアウト |
| LAYOUT_ansi | default_ansi | ANSIレイアウト |
| LAYOUT_iso | default_iso | ISOレイアウト |

## 画像/ハードウェアのファイル

リポジトリのサイズを小さく保つために、いくつかの例外を除いて、どの形式のバイナリファイルも受け入れないようになりました。外部の場所（<https://imgur.com>など）でホストして、`readme.md`でリンクすることをオススメします。

ハードウェアのファイル(プレートやケース、PCBなど)は[qmk.fm リポジトリ](https://github.com/qmk/qmk.fm)に提供でき、[qmk.fm](http://qmk.fm)で利用可能になります。ダウンロード出来るファイルは`/<keyboard>/`（名前は上記と同じ形式）に保存され、`http://qmk.fm/<keyboard>/`で提供されます。ページは`/_pages/<keyboard>/`から生成されて、同じ場所で提供されます。（.mdファイルはJekyllを通して.htmlファイル変換されます）`lets_split`ファイルを参照して下さい。

## キーボードのデフォルト設定

QMKが提供する機能の量を考えれば、新しいユーザーが混乱するのは当たり前です。キーボードのデフォルトファームウェアをまとめるなら、有効にする機能とオプションをハードウェアのサポートに必要最低限とすることをオススメします。特定の機能に関するオススメは以下の通りです。

### Bootmagic と コマンド

[Bootmagic](feature_bootmagic.md)と[コマンド](feature_command.md)は、ユーザーがキーボードを明白でない方法で制御出来るようにする2つの機能です。いずれかの機能を有効にするかどうか、またはこの機能をどのように提供するかについて、よく考えることをオススメします。この機能が本当に必要なユーザーは、最初のプログラムできるキーボードとして使用している初心者に影響を与えることなく、個人的なキーマップ内で有効に出来る人たちであることを覚えておきましょう。

新規ユーザーが遭遇する最も多い問題は、キーボードを接続している間に間違えてBootmagicをトリガーしてしまうことです。キーボードの下を持っているとき、知らない間にAltとスペースバーを押して、これらのキーが交換されてしまったことに気づきます。デフォルトではこの機能を無効にすることをオススメしますが、有効にする場合は、キーボードを接続している間に押し間違えないキーへ`BOOTMAGIC_KEY_SALT`を設定することを検討して下さい。

キーボードに2つのShiftキーがない場合は、`COMMAND_ENABLE = no`を指定していても`IS_COMMAND`が動作するデフォルトを設定しておくべきです。ユーザーがコマンドを有効化したときに使用するデフォルトが与えられます。

## カスタムキーボードプログラミング

[機能のカスタマイズ](custom_quantum_functions.md)にあるようにキーボードの機能をカスタマイズできます。ユーザーも同様にその動作をカスタマイズすることを忘れないで下さい。`process_record_kb()`のようなカスタマイズされた関数を提供している場合、関数が`_user()`を呼び出すことを確認して下さい。また、`_user()`の戻り値を確認して、ユーザーが`true`を返した場合のみカスタマイズされたコードを実行しなければいけません。

## 生産しない/手配線 プロジェクト

プロトタイプや手配線によるものなどQMKを使用するどんなプロジェクトも受け入れますが、`/keyboards/`フォルダが乱雑になるのを防ぐために、`/keyboards/handwired/`を用意しています。いつかプロトタイプのプロジェクトが製品のプロジェクトになった時点でメインの`/keyboards/`フォルダへ移動します！

## エラーとしての警告

キーボードを開発するときは、全ての警告がエラーとして扱われることに注意して下さい。小さな警告が蓄積されて、将来大きなエラーを引き起こす可能性があります。(そして、警告を放っておくのは良くない習慣です)

## 著作権表示

別のプロジェクトを元にしてキーボードの設定をするものの同じコードを使用しない場合は、ファイル上部にある著作権表示を次の形式に従って自分の名前を表示するよう、更新して下さい。

    Copyright 2017 Your Name <your@email.com>


他の人のコードを修正し、その変更が些細な部分のみであれば、著作権表示に名前を残しておかないといけません。ファイルに対して重要な作業を行った場合、以下のようにあなたの名前を追加します。

    Copyright 2017 Their Name <original_author@example.com> Your Name <you@example.com>

年はファイルが作成された最初の年にします。後年にそのファイルに対して作業が行われた場合、次のように2つ目の年を追加して反映することが出来ます。

    Copyright 2015-2017 Your Name <you@example.com>

## ライセンス

QMKのコア部分は[GNU General Public License](https://www.gnu.org/licenses/licenses.en.html)でライセンスされます。AVRマイコン用のバイナリを提供する場合は、[GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)か、[GPLv3](https://www.gnu.org/licenses/gpl.html)のどちらかから選択出来ます。ARMマイコン用のバイナリを提供する場合は、 [ChibiOS](http://www.chibios.org)のGPLv3ライセンスに準拠するため、[GPL Version 3](https://www.gnu.org/licenses/gpl.html)を選択しなければいけません。

[uGFX](https://ugfx.io)を使用している場合は、[uGFX License](https://ugfx.io/license.html)に準拠する必要があります。uGFXを利用したデバイスを販売するには個別に商用ライセンスを取得しなければいけません。

## 技術的な詳細

キーボードをQMKで動作させるための詳細は[ハードウェア](hardware.md)を参照して下さい！
