# Unicode サポート

<!---
  original document: 0.10.53:docs/feature_unicode.md
  git diff 0.10.53 HEAD -- docs/feature_unicode.md | cat
-->

Unicode 文字はキーボードから直接入力することができます！ただし幾つかの制限があります。

キーボードで Unicode サポートを有効にするには、以下の事をする必要があります:

1. サポートされている Unicode 実装のいずれかを選択します: [Basic Unicode](#basic-unicode)、[Unicode Map](#unicode-map)、[UCIS](#ucis)。
2. オペレーティングシステムとセットアップに最適な[入力モード](#input-modes)を見つけます。
3. コンフィギュレーションに適切な入力モード(または複数のモード)を[設定](#setting-the-input-mode)します。
4. キーマップに Unicode キーコードを追加します。


## 1. メソッド :id=methods

QMK は、Unicode 入力を有効にし、キーマップに Unicode 文字を追加するための3つの異なる方法をサポートします。それぞれに柔軟性と使いやすさの点で長所と短所があります。あなたの使い方に最適なものを選んでください。

ほとんどのユーザには Basic Unicode で十分です。ただし、サポートされる文字の範囲が広い(絵文字、珍しい記号など)ことが必要な場合には、Unicode Map を使う必要があります。

<br>

### 1.1. Basic Unicode :id=basic-unicode

多少制限はありますが、最も使いやすい方法です。Unicode 文字をキーコードとしてキーマップ自体に格納するため、`0x7FFF` までのコードポイントのみをサポートします。これは、ほとんどの現代言語(東アジアを含む)の文字と記号を対象としますが、絵文字は対象外です。

以下を `rules.mk` に追加します:

```make
UNICODE_ENABLE = yes
```

次に、`UC(c)` キーコードをキーマップに追加します。ここで、_c_ は目的の文字のコードポイントです (できれば16進数で最大4桁の長さが望ましいです)。例えば、`UC(0x40B)` は [Ћ](https://unicode-table.com/en/040B/) を出力し、`UC(0x30C4)` は [ツ](https://unicode-table.com/en/30C4) を出力します。

<br>

### 1.2. Unicode Map :id=unicode-map

このメソッドは、標準の文字の範囲に加えて、絵文字、古代文字、珍しい記号なども対象にしています。実際、可能な全てのコードポイント(`0x10FFFF`まで)がサポートされています。Unicode 文字は独立のマッピングテーブルに格納されています。キーマップファイルに `unicode_map` 配列を維持する必要があります。これには最大 16384 エントリを含めることができます。

以下を `rules.mk` に追加します:

```make
UNICODEMAP_ENABLE = yes
```

次に、`X(i)` キーコードをキーマップに追加します。ここで _i_ はマッピングテーブル内の目的の文字のインデックスです。これは数値にできますが、インデックスを列挙型に保持し、名前でアクセスすることをお勧めします。

```c
enum unicode_names {
    BANG,
    IRONY,
    SNEK
};

const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};
```

そして、キーマップで `X(BANG)`、`X(SNEK)` などを使うことができます。

#### 小文字と大文字

文字は å や Å のような小文字と大文字のペアで提供されることがあります。これらの文字を入力しやすくするために、キーマップで `XP(i, j)` を使うことができます。ここで、_i_ および _j_ はそれぞれ小文字と大文字のマッピングテーブルのインデックスです。キーを押した時に、シフトを押したままか Caps Lock をオンにしている場合は、2番目(大文字)の文字が挿入されます; そうでなければ最初(小文字)バージョンが出力されます。

これは特殊文字がある国際レイアウトのためのキーマップを作成している時に最も役立ちます。別々のキーに文字の小文字および大文字バージョンを置く代わりに、`XP()` を使ってそれら両方を同じキーに持つことができます。これは Unicode キーを通常のアルファベットと混ぜるのに役立ちます。

キーコードのサイズの制約により、_i_ と _j_ はそれぞれ `unicode_map` の最初の128文字のうち1つだけを参照できます。別の言い方をすると、0 ≤ _i_ ≤ 127 かつ 0 ≤ _j_ ≤ 127 です。これはほとんどのユースケースで十分ですが、インデックス計算をカスタマイズしたい場合は、[`unicodemap_index()`](https://github.com/qmk/qmk_firmware/blob/71f640d47ee12c862c798e1f56392853c7b1c1a8/quantum/process_keycode/process_unicodemap.c#L36) 関数をオーバーライドすることができます。これにより、例えば Shift/Caps の代わりに Ctrl をチェックすることもできます。

<br>

### 1.3. UCIS :id=ucis

この方法も全ての可能なコードポイントをサポートします。Unicode Map の方法と同様に、キーマップファイル内にマッピングテーブルを保持する必要があります。ただし、この機能のための組み込みのキーコードはありません — この機能を起動するカスタムキーコードあるいは関数を作成する必要があります。

以下を `rules.mk` に追加します:

```make
UCIS_ENABLE = yes
```

次に、キーマップファイルでこのようにテーブルを定義します:

```c
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop", 0x1F4A9),                // 💩
    UCIS_SYM("rofl", 0x1F923),                // 🤣
    UCIS_SYM("cuba", 0x1F1E8, 0x1F1FA),       // 🇨🇺
    UCIS_SYM("look", 0x0CA0, 0x005F, 0x0CA0), // ಠ_ಠ
);
```

デフォルトでは、各テーブルエントリの長さは、最大3コードポイントです。この番号は `#define UCIS_MAX_CODE_POINTS n` を `config.h` ファイルに追加することで変更できます。

UCIS 入力を使うには、`qk_ucis_start()` を呼び出します。次に、文字のニーモニック ("rofl" など) を入力し、Space か Enter か Esc を押します。QMK は "rofl" テキストを消去し、笑っている絵文字を挿入するはずです。

#### カスタマイズ

この機能をカスタマイズするためにキーマップで定義できる幾つかの関数があります。

* `void qk_ucis_start_user(void)` – これは "start" 関数を呼び出す時に実行され、フィードバックを提供するために使うことができます。デフォルトでは、キーボードの絵文字を入力します。
* `void qk_ucis_success(uint8_t symbol_index)` – これは入力が何かに一致して完了した時に実行されます。デフォルトでは何もしません。
* `void qk_ucis_symbol_fallback (void)` – これは入力が何にも一致しない時に実行されます。デフォルトでは、入力を Unicode コードとして試そうとします。

[`process_ucis.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_ucis.c) でこれらの関数のデフォルトの実装を見つけることができます。


## 2. Input モード :id=input-modes

QMK での Unicode の入力は、マクロのように、OS への一連の文字列を入力することで動作します。残念ながら、これが行われる方法はプラットフォームによって異なります。特に各プラットフォームでは Unicode 入力を引き起こすために、異なるキーの組み合わせが必要です。従って、対応する入力モードが QMK で設定されなければなりません。

以下の入力モードが利用可能です:

* **`UC_MAC`**: macOS の組み込み Unicode 16進数入力。`0x10FFFF` までのコードポイント(全ての利用可能なコードポイント)をサポートします。

  有効にするには、_システム環境設定 > キーボード > 入力ソース_ に移動し、(_その他_ の下の) _Unicode 16進数入力_ をリストに追加し、次にメニューバーの入力ドロップダウンからそれをアクティブにします。
  デフォルトでは、このモードは Unicode 入力のために左 Option キー (`KC_LALT`) を使いますが、これは他のキーで [`UNICODE_KEY_MAC`](#input-key-configuration) を定義することで変更できます。

  !> _Unicode 16進数入力_ 入力ソースの使用は、Option + 左矢印および Option + 右矢印 のような、幾つかの Option ベースのショートカットを無効にするかもしれません。

  !> `UC_OSX` は `UC_MAC` の非推奨のエイリアスで、QMK の将来のバージョンで削除されます。全ての新しいキーマップは、`UC_MAC` を使うべきです。

* **`UC_LNX`**: Linux の組み込み IBus Unicode 入力。`0x10FFFF` までのコードポイント(全ての利用可能なコードポイント)をサポートします。

  デフォルトで有効になっていて、IBus が有効になったディストリビューションのほとんどどれでも動作します。IBus が無い場合、このモードは GTK アプリ下で動作しますが、他の場所ではほとんど動作しません。
  デフォルトでは、このモードは Unicode 入力を開始するために Ctrl+Shift+U (`LCTL(LSFT(KC_U))`) を使いますが、これは他のキーコードで [`UNICODE_KEY_LNX`](#input-key-configuration) を定義することで変更できます。これは、Ctrl+Shift+U の挙動が Ctrl+Shift+E に統合された IBus バージョン 1.5.15 以上を必要とするかもしれません。

* **`UC_WIN`**: _(非推奨)_ Windows の組み込み16進数テンキー Unicode 入力。`0xFFFF` までのコードポイントをサポートします。

  有効にするには、`HKEY_CURRENT_USER\Control Panel\Input Method` の下に、`EnableHexNumpad` という名前の `REG_SZ` 型のレジストリキーを作成し、その値を `1` に設定します。これは、管理者権限でコマンドラインプロンプトから `reg add "HKCU\Control Panel\Input Method" -v EnableHexNumpad -t REG_SZ -d 1` を実行することでできます。その後再起動します。
  信頼性と互換性の問題から、このモードはお勧めできません; 代わりに `UC_WINC` モードを使ってください。

* **`UC_BSD`**: _(未実装)_ BSD での Unicode 入力。現時点では実装されていません。BSD ユーザでサポートを追加したい場合は、[GitHub で issue を開いて](https://github.com/qmk/qmk_firmware/issues)ください。

* **`UC_WINC`**: [WinCompose](https://github.com/samhocevar/wincompose) を使った Windows Unicode 入力。v0.9.0 の時点で、`0x10FFFF` までのコードポイント(全ての利用可能なコードポイント)をサポートします。

  有効にするには、[最新のリリース](https://github.com/samhocevar/wincompose/releases/latest)をインストールします。インストールすると、起動時に WinCompose が自動的に実行されます。このモードはアプリがサポートする全てのバージョンの Windows で確実に動作します。
  デフォルトでは、このモードは Compose キーとして右 Alt (`KC_RALT`) を使いますが、これは WinCompose 設定と他のキーで [`UNICODE_KEY_WINC`](#input-key-configuration) を定義することで変更できます。


## 3. 入力モードの設定 :id=setting-the-input-mode

目的の入力モードを設定するには、以下の定義を `config.h` に追加します:

```c
#define UNICODE_SELECTED_MODES UC_LNX
```

この例では、キーボードのデフォルトの入力モードを `UC_LNX` に設定します。これは、`UC_MAC` か `UC_WINC` か[上記](#input-modes)に列挙されている他のモードのいずれかに置き換えることができます。手動で別のモード([下記](#keycodes)を見てください)に切り替えない限り、キーボードは起動時に選択したモードを自動的に使います。

複数の入力モードを選択することもできます。これにより、`UC_MOD`/`UC_RMOD` キーコードを使ってそれらを簡単に切り替えることができます。

```c
#define UNICODE_SELECTED_MODES UC_MAC, UC_LNX, UC_WINC
```

値はカンマで区切られていることに注意してください。キーボードは最後に使われた入力モードを記憶し、次の電源投入時にそれを使い続けます。`config.h` に `#define UNICODE_CYCLE_PERSIST false` を追加することで、これを無効にして常にリストの最初のモードで開始するように強制できます。

#### キーコード

以下のキーコードを使って、いつでも入力モードを切り替えることができます。これらをキーマップに追加すると、`UNICODE_SELECTED_MODES` に列挙されていないモードを含む特定の入力モードに素早く切り替えることができます。

| キーコード             |エイリアス | 入力モード   | 説明                                                               |
|------------------------|-----------|--------------|--------------------------------------------------------------------|
| `UNICODE_MODE_FORWARD` | `UC_MOD`  | リストの次へ | 選択したモードを切り替えます。Shift が押された場合は逆方向         |
| `UNICODE_MODE_REVERSE` | `UC_RMOD` | リストの前へ | 逆方向に選択したモードを切り替えます。Shift が押された場合は順方向 |
| `UNICODE_MODE_MAC`     | `UC_M_MA` | `UC_MAC`     | macOS 入力に切り替え                                               |
| `UNICODE_MODE_LNX`     | `UC_M_LN` | `UC_LNX`     | Linux 入力に切り替え                                               |
| `UNICODE_MODE_WIN`     | `UC_M_WI` | `UC_WIN`     | Windows 入力に切り替え                                             |
| `UNICODE_MODE_BSD`     | `UC_M_BS` | `UC_BSD`     | BSD 入力に切り替え _(未実装)_                                      |
| `UNICODE_MODE_WINC`    | `UC_M_WC` | `UC_WINC`    | WinCompose を使う Windows 入力に切り替え                           |

コード内で `set_unicode_input_mode(x)` を呼び出すことで、入力モードを切り替えることもできます。ここで、_x_ は上記の入力モード定数のいずれか (例えば、`UC_LNX`) です。

?> `matrix_init_user()` または同様の関数の中で `set_unicode_input_mode()` を呼び出すよりも、`UNICODE_SELECTED_MODES` を使うほうが望ましいです。Unicode システムとの統合性が高く、EEPROM への不要な書き込みを回避できるという利点があるからです。

#### オーディオフィードバック

キーボードで[オーディオ機能](ja/feature_audio.md)を有効にした場合、上記のキーを押したときにメロディーを再生するように設定できます。そのようにして、入力モードを切り替えた時になんらかのオーディオフィードバックを得ることができます。

例えば、`config.h` ファイルに下記の定義を追加することができます:

```c
#define UNICODE_SONG_MAC  AUDIO_ON_SOUND
#define UNICODE_SONG_LNX  UNICODE_LINUX
#define UNICODE_SONG_BSD  TERMINAL_SOUND
#define UNICODE_SONG_WIN  UNICODE_WINDOWS
#define UNICODE_SONG_WINC UNICODE_WINDOWS
```


## 追加のカスタマイズ

Unicode は大規模で多目的な機能のため、システムでより適切に動作するようにカスタマイズできるオプションが幾つかあります。

### 入力関数の開始と終了

プラットフォームで Unicode 入力を開始および終了する機能は、ローカルで上書きできます。可能な用途には、デフォルトキーを使用しない場合の入力モードの挙動のカスタマイズ、あるいは Unicode 入力への視覚/音声フィードバックの追加があります。

* `void unicode_input_start(void)` – これはプラットフォームに Unicode 入力モードの入力を指示する初期シーケンスを送信します。例えば、Windows では左 Alt キーの後に Num+ を押したままにし、Linux では `UNICODE_KEY_LNX` の組み合わせ(デフォルト: Ctrl+Shift+U) を押します。
* `void unicode_input_finish(void)` – これは、例えば Space を押すか Alt キーを放すなどして、Unicode 入力モードを終了するために呼ばれます。

[`process_unicode_common.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_unicode_common.c) でこれらの関数のデフォルトの実装を見つけることができます。

### 入力キーの設定

`config.h` に対応する定義を追加することで、macOS、Linux、WinCompose で Unicode 入力を引き起こすために使われるキーをカスタマイズできます。デフォルト値はプラットフォームのデフォルト設定に一致するため、Unicode 入力が動作しない、あるいは(例えば左あるいは右 Alt を解放するために)異なるキーを使いたい場合以外はこれを変更する必要はありません。

| 定義               | 型         | 既定値             | 例                                          |
|--------------------|------------|--------------------|---------------------------------------------|
| `UNICODE_KEY_MAC`  | `uint8_t`  | `KC_LALT`          | `#define UNICODE_KEY_MAC  KC_RALT`          |
| `UNICODE_KEY_LNX`  | `uint16_t` | `LCTL(LSFT(KC_U))` | `#define UNICODE_KEY_LNX  LCTL(LSFT(KC_E))` |
| `UNICODE_KEY_WINC` | `uint8_t`  | `KC_RALT`          | `#define UNICODE_KEY_WINC KC_RGUI`          |


## Unicode 文字列の送信

QMK は、Unicode 入力をプログラムでホストに送信できるようにする幾つかの関数を提供します:

### `send_unicode_string()`

この関数は、`send_string()` によく似ていますが、UTF-8 文字を直接入力できます。選択された入力モードでもサポートされている場合は、全てのコードポイントをサポートします。`keymap.c` ファイルが UTF-8 エンコーディングを使ってフォーマットされていることを確認してください。

```c
send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
```

使用例には、[Macros](ja/feature_macros.md) で説明されているように、キーが押された時に Unicode 文字列を送信することが含まれます。

## 追加の言語サポート

`quantum/keymap_extras` には、様々な言語ファイルがあります — これらは Colemak または BÉPO のような代替レイアウトのファイルと同じように動作します。これらの言語ヘッダのいずれかを `#include` すると、その言語/国のレイアウトに固有のキーコードにアクセスできます。このようなキーコードは、2文字の国/言語コードの後に、アンダースコアとキーが対応する4文字の略語が続くことで定義されます。例えば、キーマップに `keymap_french.h` を含め、`FR_UGRV` を使うと、ネイティブのフランス語 AZERTY レイアウトを使うシステムで入力すると、`ù` が出力されます。

マシンで使うプライマリシステムレイアウトが US ANSI と異なる場合、これらの言語固有のキーコードを使うと、QMK キーマップが実際に画面に出力されるものとより一致するようになります。ただし、これらのキーコードは、内部の対応するデフォルトの US キーコードのエイリアスに過ぎず、キーボードで使われる HID プロトコル自体は本質的に US ANSI に基づいていることに注意してください。


## Windows での国際文字

### AutoHotkey

この方法はキーボード自体で Unicode サポートを必要としませんが、代わりにバックグラウンドで [AutoHotkey](https://autohotkey.com) が実行されていることを当てにします。

最初にプログラムで使われていないモディファイアの組み合わせを選択する必要があります。
Ctrl+Alt+Win はあまり広く使われていないため、これに最適なはずです。
mod-tab コンボ `LCAG_T` 用に定義されたマクロがあります。
この mod-tab マクロをキーボードのキーに追加します。例えば: `LCAG_T(KC_TAB)`。
これにより、キーを押してすぐ放すとキーはタブキーのように振る舞いますが、他のキーと一緒に使うとモディファイアに変わります。

AutoHotkey のデフォルトのスクリプトで、カスタムホットキーを定義できます。

    <^<!<#a::Send, ä
    <^<!<#<+a::Send, Ä

上のホットキーは、CtrlAltGui と CtrlAltGuiShift + 文字 a の組み合わせです。
この組み合わせが押されると、AutoHotkey は `Send, ` の右側にあるテキストを挿入します。

### 米国インターナショナル

システム上で米国インターナショナルレイアウトを有効にすると、文字にアクセントをつけるために区切り文字を使います。例えば、"\`a" は à になります。
これを有効にする方法は[ここ](https://support.microsoft.com/en-us/help/17424/windows-change-keyboard-layout)で見つかります。
