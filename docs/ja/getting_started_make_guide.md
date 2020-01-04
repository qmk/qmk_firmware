# より詳細な `make` 手順

<!---
  original document: 7494490d6:docs/getting_started_make_guide.md
  git diff 7494490d6 HEAD -- docs/getting_started_make_guide.md | cat
-->

`make` コマンドの完全な構文は `<keyboard_folder>:<keymap>:<target>` です:

* `<keyboard_folder>` はキーボードのパスです。例えば、`planck`
   * 全てのキーボードをコンパイルするには `all` を使います。
   * リビジョンをコンパイルするためのパスを指定します。例えば `planck/rev4` あるいは `planck/rev3`
   * キーボードにフォルダが無い場合は、省略することができます
   * デフォルトのフォルダをコンパイルする場合は、省略することができます
* `<keymap>` はキーマップの名前です。例えば、`algernon`
   * 全てのキーマップをコンパイルするには `all` を使います。
* `<target>` の詳細は以下で説明します。

`<target>` は以下を意味します
* target が指定されない場合は、以下の `all` と同じです
* `all` は指定された全てのキーボード/リビジョン/キーマップの組み合わせをコンパイルします。例えば、`make planck/rev4:default` は1つの .hex を生成しますが、`make planck/rev4:all` は planck で利用可能な全てのキーマップについて hex を生成します。
* `flash`、`dfu`、`teensy`、`avrdude`、`dfu-util` または `bootloadHID` はファームウェアをコンパイルし、キーボードにアップロードします。コンパイルが失敗すると、何もアップロードされません。使用するプログラムはキーボードに依存します。ほとんどのキーボードでは `dfu` ですが、ChibiOS キーボードについては `dfu-util` 、標準的な Teensys については `teensy` です。キーボードに使うべきコマンドを見つけるには、キーボード固有の readme をチェックしてください。
* **注意**: 一部のオペレーティングシステムはこれらのコマンドが機能するためには root アクセスが必要です。そのため、例えば `sudo make planck/rev4:default:flash` を実行する必要があります。
* `clean`、全てをゼロからビルドするためにビルド出力フォルダを掃除します。説明できない問題がある場合は、通常のコンパイルの前にこれを実行してください。

target の後の make コマンドの最後に追加のオプションを追加することもできます

* `make COLOR=false` - カラー出力をオフ
* `make SILENT=true` - エラー/警告以外の出力をオフ
* `make VERBOSE=true` - 全ての gcc のものを出力 (デバッグする必要が無い限り面白くありません)
* `make EXTRAFLAGS=-E` - コンパイルせずにコードを前処理 (#define コマンドをデバッグしようとする場合に便利)

make コマンド自体にもいくつかの追加オプションがあります。詳細は `make --help` を入力してください。最も有用なのはおそらく `-jx` です。これは複数の CPU を使ってコンパイルしたいことを指定し、`x` は使用したい CPU の数を表します。設定すると、特に多くのキーボード/キーマップをコンパイルしている場合は、コンパイル時間を大幅に短縮することができます。通常は、コンパイル中に他の作業を行うための余裕をもたせるために、使用している CPU の数より1つ少ない値に設定します。全てのオペレーティングシステムと make バージョンがオプションをサポートしているわけではないことに注意してください。

コマンドの幾つかの例です

* `make all:all` 全てをビルドします (全てのキーボードフォルダ、全てのキーマップ)。`root` から単に `make` を実行すると、これを実行します。
* `make ergodox_infinity:algernon:clean` は、Ergodox Infinity キーボードのビルド出力を消去します。
* `make planck/rev4:default:flash COLOR=false` カラー出力なしでキーマップをビルドしアップロードします。

## `rules.mk` オプション

無効にするにはこれらの変数を `no` に設定します。有効にするには `yes` に設定します。

`BOOTMAGIC_ENABLE`

これにより、キーとソルトキー(デフォルトではスペース)を保持し、電力が失われても持続する様々な EEPROM 設定へアクセスできます。誤って設定が変更されることが多く、デバッグするのが難しい混乱した結果を生成するため、これを無効にしておくことをお勧めします。ヘルプセッションで発生する、より一般的な問題の1つです。

`MOUSEKEY_ENABLE`

これにより、キーコード/カスタム関数を介して、カーソルの動きとクリックを制御することができます。

`EXTRAKEY_ENABLE`

これにより、システムとオーディオ制御キーコードを使うことができます。

`CONSOLE_ENABLE`

これにより、[`hid_listen`](https://www.pjrc.com/teensy/hid_listen.html) を使って読むことができるメッセージを出力することができます。

デフォルトで、全てのデバッグ( *dprint* ) 出力 ( *print*、*xprintf* )、およびユーザ出力 ( *uprint* ) メッセージが有効になります。これにより、書き込み領域の大部分が消費され、キーボードの .hex ファイルを実行するにはあまりに大きくしてしまうかもしれません。

デバッグメッセージ( *dprint* ) を無効にし、.hex ファイルのサイズを小さくするには、`config.h` に `#define NO_DEBUG` を含めます。

出力メッセージ( *print*、*xprintf* )とユーザ出力( *uprint* ) を無効にし、.hex のファイルサイズを小さくするには、`config.h` に `#define NO_PRINT` を含めます。

出力メッセージ ( *print*、*xprintf* ) を無効にし、ユーザメッセージ ( *uprint* )を**そのままにする**には、`config.h` に `#define USER_PRINT` を含めます(この場合は、`#define NO_PRINT` も含めないでください)。

テキストを見るには、`hid_listen` を開き、出力メッセージを見るのを楽しんでください。

**注意:** キーマップコード以外には、*uprint* メッセージを含めないでください。QMK システムフレームワーク内で使うべきではありません。そうでなければ、他の人の .hex ファイルが肥大化します。

`COMMAND_ENABLE`

これは、通常はデフォルトのマジックキーコマンド `LSHIFT+RSHIFT+KEY` で起動されるマジックコマンドを有効にします。マジックコマンドは、デバッグメッセージ (`MAGIC+D`) あるいは NKRO の一時的な切り替え (`MAGIC+N`) の有効化を含みます。

`SLEEP_LED_ENABLE`

コンピュータがスリープの間に LED がブレスできるようにします。Timer1 が使われます。This feature is largely unused and untested, and needs updating/abstracting.

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

詳細と制限については、[Unicodeページ](ja/feature_unicode.md) を見てください。

`BLUETOOTH_ENABLE`

これによりキーコードをワイヤレスで送信するために Bluefruit EZ-key と連動することができます。D2 と D3 ピンを使います。

`AUDIO_ENABLE`

This allows you output audio on the C6 pin (needs abstracting). 詳細は[オーディオページ](ja/feature_audio.md)を見てください。

`FAUXCLICKY_ENABLE`

クリック音のあるスイッチをエミュレートするためにブザーを使います。チェリー青スイッチの安っぽい模倣。デフォルトでは、`AUDIO_ENABLE` と同じ C6 ピンを使います。

`VARIABLE_TRACE`

これを使って変数の値の変更をデバッグします。詳細についてはユニットテストのページの[トレース変数](ja/unit_testing.md#tracing-variables)のセクションを見てください。

`API_SYSEX_ENABLE`

これにより文字列を送信するために Quantum SYSEX API を使うことができます (どこに？)

`KEY_LOCK_ENABLE`

これは [key lock](ja/feature_key_lock.md) を有効にします。

`SPLIT_KEYBOARD`

分割キーボード (let's split や bakingpy's boards のようなデュアル MCU) のサポートを有効にし、quantum/split_common にある全ての必要なファイルをインクルードします

`SPLIT_TRANSPORT`

ARM ベースの分割キーボード用の標準分割通信ドライバはまだ無いため、これらのために `SPLIT_TRANSPORT = custom` が使われる必要があります。カスタムの実装が使われるようにすることで、標準の分割キーボード通信コード(AVR 固有)が含まれないようにします。

`CUSTOM_MATRIX`

デフォルトのマトリックス走査ルーチンを独自のコードで置き換えます。matrix_init() および matrix_scan() の独自の実装を提供する必要があります。

`DEBOUNCE_TYPE`

デフォルトのキーデバウンスルーチンを別のものに置き換えます。`custom` の場合、独自の実装を提供する必要があります。

## キーマップごとに Makefile オプションをカスタマイズ

キーマップディレクトリに `rules.mk` というファイルがある場合、そのファイルで設定した全てのオプションは、特定のキーボードの他の `rules.mk` オプションよりも優先されます。

キーボードの `rules.mk` に `BACKLIGHT_ENABLE = yes` があるとします。特定のキーボードでバックライトが無いようにするには、`rules.mk` というファイルを作成し、`BACKLIGHT_ENABLE = no` を指定します。
