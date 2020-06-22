# QMK キーボードガイドライン

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.0:docs/hardware_keyboard_guidelines.md
  git diff 0.9.0 HEAD -- docs/hardware_keyboard_guidelines.md | cat
-->

QMK は開始以来、コミュニティにおけるキーボードの作成や保守に貢献しているあなたのような人たちのおかげで飛躍的に成長しました。私たちが成長するにつれて、うまくやるためのいくつかのパターンを発見しました。他の人たちがあなたの苦労の恩恵を受けやすくするため、それにあわせてもらえるようお願いします。

## あなたのキーボード/プロジェクトの名前を決める

キーボードの名前は全て小文字で、アルファベット、数字、アンダースコア(`_`)のみで構成されています。アンダースコア(`_`)で始めてはいけません。スラッシュ(`/`)はサブフォルダの区切り文字として使用されます。

`test`、`keyboard`、`all` はmakeコマンド用に予約されており、キーボードまたはサブフォルダ名として使用することは出来ません。

正しい例:

* `412_64`
* `chimera_ortho`
* `clueboard/66/rev3`
* `planck`
* `v60_type_r`

## サブフォルダ

QMK では、まとめるためや同じキーボードのリビジョン間でコードを共有するためにサブフォルダを使用します。フォルダは最大4階層までネストできます。

    qmk_firmware/keyboards/top_folder/sub_1/sub_2/sub_3/sub_4

サブフォルダ内に `rules.mk` ファイルが存在するとコンパイル可能なキーボードとして見なされます。QMK Configurator から使用できるようになり、`make all` でテストされます。同じメーカーのキーボードをまとめるためにフォルダを使用している場合は `rules.mk` ファイルを置いてはいけません。

例:

Clueboard は、サブフォルダをまとめるためとキーボードのリビジョン管理の両方のために使用しています。

* [`qmk_firmware`](https://github.com/qmk/qmk_firmware/tree/master)
  * [`keyboards`](https://github.com/qmk/qmk_firmware/tree/master/keyboards)
    * [`clueboard`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard)  &larr; これはまとめるためのフォルダです。 `rules.mk` ファイルはありません。
      * [`60`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/60)  &larr; これはコンパイルできるキーボードです。`rules.mk` が存在します。
      * [`66`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66) &larr; これもコンパイルできるキーボードです。 デフォルトのリビジョンとして `DEFAULT_FOLDER` に `rev3` を指定しています。
        * [`rev1`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev1) &larr; コンパイル可能: `make clueboard/66/rev1`
        * [`rev2`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev2) &larr; コンパイル可能: `make clueboard/66/rev2`
        * [`rev3`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev3) &larr; コンパイル可能: `make clueboard/66/rev3` もしくは `make clueboard/66`

## キーボードのフォルダ構成

キーボードは `qmk_firmware/keyboards/` 内にあり、前のセクションで説明したようにフォルダ名はキーボードの名前にする必要があります。このフォルダ内にはいくつかのファイルがあります。

* `readme.md`
* `info.json`
* `config.h`
* `rules.mk`
* `<keyboard_name>.c`
* `<keyboard_name>.h`

### `readme.md`

全てのプロジェクトにはどのようなキーボードなのか、誰が設計したか、どこで入手できるかを説明する `readme.md` ファイルが必要です。もしあれば、メーカーの Web サイトなどの詳しい情報へのリンクも含める必要があります。[キーボード readme テンプレート](ja/documentation_templates.md#keyboard-readmemd-template)を参考にして下さい。

### `info.json`

このファイルは [QMK API](https://github.com/qmk/qmk_api) から使用されます。[QMK Configurator](https://config.qmk.fm/) が必要とするキーボードの情報が含まれています。ここでメタデータを設定することもできます。詳しくは [info.json 形式](ja/reference_info_json.md) を参照して下さい。

### `config.h`

全てのプロジェクトには、マトリックスサイズ、製品名、USB VID/PID、説明、その他の設定などが含まれた `config.h` ファイルが必要です。一般に、このファイルを使用して常に機能するキーボードの重要な情報やデフォルトを設定します。

また、`config.h` ファイルはサブフォルダにも置くことができ、その読み込み順は以下の通りです。

* `keyboards/top_folder/config.h`
  * `keyboards/top_folder/sub_1/config.h`
    * `keyboards/top_folder/sub_1/sub_2/config.h`
      * `keyboards/top_folder/sub_1/sub_2/sub_3/config.h`
        * `keyboards/top_folder/sub_1/sub_2/sub_3/sub_4/config.h`
          * `users/a_user_folder/config.h`
          * `keyboards/top_folder/keymaps/a_keymap/config.h`
        * `keyboards/top_folder/sub_1/sub_2/sub_3/sub_4/post_config.h`
      * `keyboards/top_folder/sub_1/sub_2/sub_3/post_config.h`
    * `keyboards/top_folder/sub_1/sub_2/post_config.h`
  * `keyboards/top_folder/sub_1/post_config.h`
* `keyboards/top_folder/post_config.h`

`post_config.h` ファイルは、`config.h` ファイルで指定された内容に応じて、追加の後処理を行うために使用することができます。
例えば、キーマップレベルの `config.h` ファイルで `IOS_DEVICE_ENABLE` マクロを以下のように定義すると、`post_config.h` ファイルでより詳細な設定を行うことができます。

* `keyboards/top_folder/keymaps/a_keymap/config.h`
  ```c
  #define IOS_DEVICE_ENABLE
  ```
* `keyboards/top_folder/post_config.h`
  ```c
  #ifndef IOS_DEVICE_ENABLE
    // USB_MAX_POWER_CONSUMPTION value for this keyboard
    #define USB_MAX_POWER_CONSUMPTION 400
  #else
    // fix iPhone and iPad power adapter issue
    // iOS device need lessthan 100
    #define USB_MAX_POWER_CONSUMPTION 100
  #endif
  
  #ifdef RGBLIGHT_ENABLE
    #ifndef IOS_DEVICE_ENABLE
      #define RGBLIGHT_LIMIT_VAL 200
      #define RGBLIGHT_VAL_STEP 17
    #else
      #define RGBLIGHT_LIMIT_VAL 35
      #define RGBLIGHT_VAL_STEP 4
    #endif
    #ifndef RGBLIGHT_HUE_STEP
      #define RGBLIGHT_HUE_STEP 10
    #endif
    #ifndef RGBLIGHT_SAT_STEP
      #define RGBLIGHT_SAT_STEP 17
    #endif
  #endif
  ```

?> 上記の例のように `post_config.h` でオプションを定義する場合、キーボードやユーザレベルの `config.h` で同じオプションを定義してはいけません。

### `rules.mk`

このファイルが存在するということは、フォルダがキーボードであり、`make` コマンドで使用できることを意味します。ここでキーボードのビルド環境を構築し、デフォルトの機能を設定します。

`rules.mk` ファイルはサブフォルダにも置くことができ、その読み込み順は以下の通りです。

* `keyboards/top_folder/rules.mk`
  * `keyboards/top_folder/sub_1/rules.mk`
    * `keyboards/top_folder/sub_1/sub_2/rules.mk`
      * `keyboards/top_folder/sub_1/sub_2/sub_3/rules.mk`
        * `keyboards/top_folder/sub_1/sub_2/sub_3/sub_4/rules.mk`
          * `keyboards/top_folder/keymaps/a_keymap/rules.mk`
          * `users/a_user_folder/rules.mk`
* `common_features.mk`

`rules.mk` ファイルに書かれた多くの設定は `common_features.mk` によって解釈され、必要なソースファイルやコンパイラのオプションが設定されます。

?> 詳しくは `build_keyboard.mk` と `common_features.mk` を見てください。

### `<keyboard_name.c>`

ここではキーボードのカスタマイズされたコードを記述します。通常、初期化してキーボードのハードウェアを制御するコードを記述します。キーボードが LED やスピーカー、その他付属ハードウェアのないキーマトリックスのみで構成されている場合は空にできます。

通常、以下の関数がこのファイルで定義されます。

* `void matrix_init_kb(void)`
* `void matrix_scan_kb(void)`
* `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* `void led_set_kb(uint8_t usb_led)`

### `<keyboard_name.h>`

このファイルはキーボードのマトリックスを定義するために使用されます。配列をキーボードの物理的なスイッチマトリックスに変換する C マクロを最低限1つ定義する必要があります。複数のレイアウトでキーボードを構築出来る場合は、追加のマクロを定義しなければいけません。

レイアウトが1つしかない場合は、このマクロは `LAYOUT` とします。

複数のレイアウトを定義する場合、物理的に構成することが出来なくとも、マトリックス上で全てのスイッチ位置をサポートする `LAYOUT_all` という名前の基本となるレイアウトが必要です。これは `default` キーマップで使用すべきマクロです。次に、他のレイアウトマクロを使用する `default_<layout>` といった追加のキーマップを用意します。これによって、他の人が定義されたレイアウトを使いやすくなります。

レイアウトマクロの名前は全て小文字で、先頭の `LAYOUT` だけ大文字です。

例として、ANSI と ISO をサポートする 60% PCB がある場合、以下のようにレイアウトとキーマップを定義出来ます。

| レイアウト名 | キーマップ名 | 説明 |
|-------------|-------------|-------------|
| LAYOUT_all | default | ISO と ANSI のどちらもサポートしたレイアウト |
| LAYOUT_ansi | default_ansi | ANSI レイアウト |
| LAYOUT_iso | default_iso | ISO レイアウト |

## 画像/ハードウェアのファイル

リポジトリのサイズを小さく保つために、いくつかの例外を除いて、どの形式のバイナリファイルも受け入れないようになりました。外部の場所（<https://imgur.com>など）でホストして、`readme.md` でリンクすることをおすすめします。

ハードウェアのファイル(プレートやケース、PCB など)は [qmk.fm リポジトリ](https://github.com/qmk/qmk.fm)に提供でき、[qmk.fm](http://qmk.fm) で利用可能になります。ダウンロード出来るファイルは `/<keyboard>/`（名前は上記と同じ形式）に保存され、`http://qmk.fm/<keyboard>/` で提供されます。ページは `/_pages/<keyboard>/` から生成されて、同じ場所で提供されます（ .mdファイルはJekyllを通して .htmlファイル変換されます）。`lets_split` ファイルを参照して下さい。

## キーボードのデフォルト設定

QMK が提供する機能の量を考えれば、新しいユーザーが混乱するのは当たり前です。キーボードのデフォルトファームウェアをまとめるなら、有効にする機能とオプションをハードウェアのサポートに必要な最低限のセットにすることをおすすめします。特定の機能に関するおすすめは以下の通りです。

### ブートマジックとコマンド

[ブートマジック](ja/feature_bootmagic.md) と[コマンド](ja/feature_command.md)は、ユーザーがキーボードを明白でない方法で制御出来るようにする2つの関連機能です。いずれかの機能を有効にする場合、この機能をどのように提供するかについて、よく考えることをおすすめします。この機能が必要なユーザーは、あなたのキーボードを最初のプログラムできるキーボードとして使用している初心者に影響を与えることなく、個人的なキーマップ内で有効に出来ることを覚えておきましょう。

新規ユーザーが遭遇する最も多い問題は、キーボードを接続している間に間違えてブートマジックをトリガーしてしまうことです。キーボードの下を持っているとき、知らない間に Alt とスペースバーを押して、これらのキーが交換されてしまったことに気づきます。デフォルトではこの機能を無効にすることをおすすめしますが、有効にする場合は、キーボードを接続している間に押し間違えないキーへ `BOOTMAGIC_KEY_SALT` を設定することを検討して下さい。

キーボードに2つの Shift キーがない場合は、`COMMAND_ENABLE = no` を指定していても `IS_COMMAND` が動作するデフォルトを設定しておくべきです。ユーザーがコマンドを有効化したときに使用するデフォルトが与えられます。

## カスタムキーボードプログラミング

[機能のカスタマイズ](ja/custom_quantum_functions.md)にあるようにキーボードのカスタム関数を定義できます。ユーザーも同様にその動作をカスタマイズしたいかもしれないということと、ユーザーにそれを可能にすることを忘れないで下さい。 `process_record_kb()`のようなカスタム関数を提供している場合、関数がその関数の `_user()` 版を呼び出すことを確認して下さい。また、その関数の`_user()` 版の戻り値を確認して、user が `true` を返した場合のみカスタムコードを実行しなければいけません。

## 生産しない/手配線 プロジェクト

プロトタイプや手配線によるものなど QMK を使用するどんなプロジェクトも受け入れますが、`/keyboards/` フォルダが乱雑になるのを防ぐために、`/keyboards/handwired/` を用意しています。いつかプロトタイプのプロジェクトが製品のプロジェクトになった時点でメインの `/keyboards/` フォルダへ移動します！

## エラーとしての警告

キーボードを開発するときは、全ての警告がエラーとして扱われることに注意して下さい。小さな警告が蓄積されて、将来大きなエラーを引き起こす可能性があります。(そして、警告を放っておくのは良くない習慣です)

## 著作権表示

別のプロジェクトを元にしてキーボードの設定をするものの同じコードを使用しない場合は、ファイル上部にある著作権表示を次の形式に従って自分の名前を表示するよう、更新して下さい。

    Copyright 2017 Your Name <your@email.com>


他の人のコードを修正し、その変更が些細な部分のみであれば、著作権表示の名前をそのままにしておかないといけません。ファイルに対して重要な作業を行った場合、以下のようにあなたの名前を追加します。

    Copyright 2017 Their Name <original_author@example.com> Your Name <you@example.com>

年はファイルが作成された最初の年にします。後年にそのファイルに対して作業が行われた場合、次のように2つ目の年を追加して反映することが出来ます。

    Copyright 2015-2017 Your Name <you@example.com>

## ライセンス

QMK のコア部分は [GNU General Public License](https://www.gnu.org/licenses/licenses.en.html) でライセンスされます。AVR マイコン用のバイナリを提供する場合は、[GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) か、[GPLv3](https://www.gnu.org/licenses/gpl.html) のどちらかから選択出来ます。ARM マイコン用のバイナリを提供する場合は、 [ChibiOS](http://www.chibios.org) の GPLv3 ライセンスに準拠するため、[GPL Version 3](https://www.gnu.org/licenses/gpl.html) を選択しなければいけません。

[uGFX](https://ugfx.io) を使用している場合は、[uGFX License](https://ugfx.io/license.html) に準拠する必要があります。uGFX を利用したデバイスを販売するには個別に商用ライセンスを取得しなければいけません。

## 技術的な詳細

キーボードを QMK で動作させるための詳細は[ハードウェア](ja/hardware.md)を参照して下さい！
