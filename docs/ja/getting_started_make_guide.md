# より詳細な `make` 手順

<!---
  original document: 0.12.43:docs/getting_started_make_guide.md
  git diff 0.12.43 HEAD -- docs/getting_started_make_guide.md | cat
-->

`make` コマンドの完全な構文は `<keyboard_folder>:<keymap>:<target>` です:

* `<keyboard_folder>` はキーボードのパスです。例えば、`planck`
   * 全てのキーボードをコンパイルするには `all` を使います。
   * リビジョンを選択してコンパイルするためのパスを指定します。例えば `planck/rev4` あるいは `planck/rev3`
   * キーボードにフォルダが無い場合は、省略することができます
   * デフォルトのフォルダをコンパイルする場合は、省略することができます
* `<keymap>` はキーマップの名前です。例えば、`algernon`
   * 全てのキーマップをコンパイルするには `all` を使います。
* `<target>` の詳細は以下で説明します。

`<target>` は以下を意味します
* target が指定されない場合は、以下の `all` と同じです
* `all` は指定されたキーボード/リビジョン/キーマップの可能な全ての組み合わせのコンパイルを行います。例えば、`make planck/rev4:default` は1つの .hex を生成しますが、`make planck/rev4:all` は planck で利用可能な全てのキーマップについて hex を生成します。
* `flash`、`dfu`、`teensy`、`avrdude`、`dfu-util`、`bootloadHID` はファームウェアをコンパイルし、キーボードにアップロードします。コンパイルが失敗すると、何もアップロードされません。使用するプログラマはキーボードに依存します。ほとんどのキーボードでは `dfu` ですが、ChibiOS キーボードについては `dfu-util` 、標準的な Teensy については `teensy` を使います。キーボードに使うコマンドを見つけるには、キーボード固有の readme をチェックしてください。
  利用可能なブートローダの詳細は[ファームウェアの書き込み](ja/flashing.md)ガイドを参照してください。
  * **Note**:  一部のオペレーティングシステムでは、これらのコマンドが機能するためには特権アクセスが必要です。これは、root アクセスなしでこれらにアクセスするために [`udev ルール`](ja/faq_build.md#linux-udev-rules) を設定するか、あるいは root アクセスでコマンドを実行する (`sudo make planck/rev4:default:flash`) 必要があるかもしれないことを意味します。
* `clean` は、全てをゼロからビルドするためにビルド出力フォルダを掃除します。説明できない問題がある場合は、通常のコンパイルの前にこれを実行してください。
* `distclean` は、.hex ファイルと .bin ファイルを削除します。

次のターゲットは開発者向けです:

* `show_path` ソースとオブジェクトファイルのパスを表示します。
* `dump_vars` makefile 変数をダンプします。
* `objs-size` 個々のオブジェクトファイルのサイズを表示します。
* `show_build_options` 'rules.mk' のオプションセットを表示します。
* `check-md5` 生成されたバイナリファイルの md5 チェックサムを表示します。

make コマンドの最後、つまり target の後に追加のオプションを追加することもできます

* `make COLOR=false` - カラー出力をオフ
* `make SILENT=true` - エラー/警告以外の出力をオフ
* `make VERBOSE=true` - 全ての gcc のものを出力 (デバッグする必要が無い限り面白くありません)
* `make VERBOSE_LD_CMD=yes` - -v オプションを指定して ld コマンドを実行します。
* `make VERBOSE_AS_CMD=yes` - -v オプションを指定して as コマンドを実行します。
* `make VERBOSE_C_CMD=<c_source_file>` - 指定された C ソースファイルをコンパイルするときに -v オプションを追加します。
* `make DUMP_C_MACROS=<c_source_file>` - 指定された C ソースファイルをコンパイルするときにプリプロセッサマクロをダンプします。
* `make DUMP_C_MACROS=<c_source_file> > <logfile>` - 指定された C ソースファイルをコンパイルするときにプリプロセッサマクロを `<logfile>` にダンプします。
* `make VERBOSE_C_INCLUDE=<c_source_file>` - 指定された C ソースファイルをコンパイルするときにインクルードされるファイル名をダンプします。
* `make VERBOSE_C_INCLUDE=<c_source_file> 2> <logfile>` - 指定された C ソースファイルをコンパイルするときにインクルードされるファイル名を `<logfile>` にダンプします。

make コマンド自体にもいくつかの追加オプションがあります。詳細は `make --help` を入力してください。最も有用なのはおそらく `-jx` です。これは複数の CPU を使ってコンパイルしたいことを指定し、`x` は使用したい CPU の数を表します。設定すると、特に多くのキーボード/キーマップをコンパイルしている場合は、コンパイル時間を大幅に短縮することができます。通常は、コンパイル中に他の作業を行うための余裕をもたせるために、持っている CPU の数より1つ少ない値に設定します。全てのオペレーティングシステムと make バージョンがオプションをサポートしているわけではないことに注意してください。

コマンドの例を幾つか示します

* `make all:all` は、全てをビルドします (全てのキーボードフォルダ、全てのキーマップ)。`root` から単に `make` を実行すると、これを実行します。
* `make ergodox_infinity:algernon:clean` は、Ergodox Infinity キーボードのビルド出力を掃除します。
* `make planck/rev4:default:flash COLOR=false` カラー出力なしでキーマップをビルドしアップロードします。

## `rules.mk` オプション

無効にするにはこれらの変数を `no` に設定します。有効にするには `yes` に設定します。

`BOOTMAGIC_ENABLE`

これにより、1つのキーとソルトキー(デフォルトではスペース)を押し続けることで、電力が失われても持続する様々な EEPROM 設定へアクセスできます。誤って設定が変更されることが多く、デバッグするのが難しい混乱した結果を生成するため、これを無効にしておくことをお勧めします。ヘルプセッションで発生する、より一般的な問題の1つです。

`MOUSEKEY_ENABLE`

これにより、キーコード/カスタム関数を介して、カーソルの動きとクリックを制御することができます。

`EXTRAKEY_ENABLE`

これにより、システムとオーディオ制御キーコードを使うことができます。

`CONSOLE_ENABLE`

これにより、[`hid_listen`](https://www.pjrc.com/teensy/hid_listen.html) を使って読むことができるメッセージを出力することができます。

デフォルトで、全てのデバッグ( *dprint* ) 出力 ( *print*、*xprintf* )、およびユーザ出力 ( *uprint* ) メッセージが有効になります。これにより、フラッシュメモリの大部分が消費され、キーボードの .hex ファイルが大きすぎてプログラムできなくなるかもしれません。

デバッグメッセージ( *dprint* ) を無効にし、.hex ファイルのサイズを小さくするには、`config.h` に `#define NO_DEBUG` を含めます。

出力メッセージ( *print*、*xprintf* )とユーザ出力( *uprint* ) を無効にし、.hex のファイルサイズを小さくするには、`config.h` に `#define NO_PRINT` を含めます。

出力メッセージ ( *print*、*xprintf* ) を無効にし、ユーザメッセージ ( *uprint* )を**そのままにする**には、`config.h` に `#define USER_PRINT` を含めます(この場合は、`#define NO_PRINT` も含めないでください)。

テキストを見るには、`hid_listen` を開き、出力メッセージを見るのを楽しんでください。

**注意:** キーマップコード以外の *uprint* メッセージを含めないでください。QMK システムフレームワーク内で使うべきではありません。さもないと、他の人の .hex ファイルが肥大化します。

`COMMAND_ENABLE`

これはマジックコマンドを有効にし、通常はデフォルトのマジックキーの組み合わせ `LSHIFT+RSHIFT+KEY` で起動されます。マジックコマンドは、デバッグメッセージ (`MAGIC+D`) の有効化や NKRO の一時的な切り替え (`MAGIC+N`) を含みます。

`SLEEP_LED_ENABLE`

コンピュータがスリープの間に LED がブレスできるようにします。ここでは Timer1 が使われます。この機能は大部分が未使用でテストされておらず、更新もしくは抽象化が必要です。

`NKRO_ENABLE`

これにより、キーボードはホスト OS に最大 248 個のキーが同時に押されていることを伝えることができます (NKRO 無しのデフォルトは 6 です)。NKRO は、`NKRO_ENABLE` が設定されていたとしても、デフォルトではオフです。config.h に `#define FORCE_NKRO` を追加するか、`MAGIC_TOGGLE_NKRO` をキーにバインドしてキーを押すことで、NKRO を強制することができます。

`BACKLIGHT_ENABLE`

これはスイッチ内の LED のバックライトを有効にします。`config.h` 内に以下を入れることでバックライトピンを指定することができます:

    #define BACKLIGHT_PIN B7

`MIDI_ENABLE`

キーボードで MIDI の送受信を有効にします。MIDI 送信モードに入るためにキーコード `MI_ON` を使うことができ、オフにするために `MI_OFF` を使うことができます。これはほとんどテストされていない機能ですが、詳細については `quantum/quantum.c` ファイルで見つけることができます。

`UNICODE_ENABLE`

これによりキーマップで `UC(<code point>)` を使って Unicode 文字を送信することができます。`0x7FFF` までのコードポイントがサポートされます。これはほとんどの現代言語の文字と記号を対象にしますが、絵文字は対象外です。

`UNICODEMAP_ENABLE`

これによりキーマップで `X(<map index>)` を使って Unicode 文字を送信することができます。キーマップファイル内にマッピングテーブルを保持する必要があります。可能な全てのコードポイント( `0x10FFFF` まで)がサポートされます。

`UCIS_ENABLE`

これにより、送信したい文字に対応するニーモニックを入力することで Unicode 文字を送信することができます。キーマップファイル内にマッピングテーブルを保持する必要があります。可能な全てのコードポイント( `0x10FFFF` まで)がサポートされます。

詳細と制限については、[Unicode ページ](ja/feature_unicode.md)を見てください。

`AUDIO_ENABLE`

C6 ピン(抽象化が必要)でオーディオ出力できます。詳細は[オーディオページ](ja/feature_audio.md)を見てください。

`VARIABLE_TRACE`

これを使って変数の値の変更をデバッグします。詳細についてはユニットテストのページの[変数のトレース](ja/unit_testing.md#tracing-variables)のセクションを見てください。

`API_SYSEX_ENABLE`

これにより Quantum SYSEX API を使って文字列を(どこかに？)送信することができます

`KEY_LOCK_ENABLE`

これは[キーロック](ja/feature_key_lock.md)を有効にします。

`SPLIT_KEYBOARD`

分割キーボード (let's split や bakingpy's boards のようなデュアル MCU) のサポートを有効にし、quantum/split_common にある全ての必要なファイルをインクルードします

`SPLIT_TRANSPORT`

ARM ベースの分割キーボード用の標準分割通信ドライバはまだ無いため、これらのために `SPLIT_TRANSPORT = custom` を使わなければなりません。カスタムの実装が使われるようにすることで、標準の分割キーボード通信コード(AVR 固有)が含まれないようにします。

`CUSTOM_MATRIX`

デフォルトのマトリックス走査ルーチンを独自のコードで置き換えます。詳細については、[カスタムマトリックスページ](ja/custom_matrix.md)を見てください。

`DEBOUNCE_TYPE`

デフォルトのキーデバウンスルーチンを別のものに置き換えます。`custom` の場合、独自の実装を提供する必要があります。

## キーマップごとに Makefile オプションをカスタマイズ

あなたのキーマップディレクトリに `rules.mk` というファイルがある場合、そのファイルで設定した全てのオプションは、あなたのキーボードの他の `rules.mk` オプションよりも優先されます。

あなたのキーボードの `rules.mk` に `BACKLIGHT_ENABLE = yes` があるとします。あなたの特定のキーボードでバックライトが無いようにするには、`rules.mk` というファイルを作成し、`BACKLIGHT_ENABLE = no` を指定します。
