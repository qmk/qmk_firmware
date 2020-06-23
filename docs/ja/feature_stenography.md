# QMK での速記 :id=stenography-in-qmk

<!---
  original document: 0.9.19:docs/feature_stenography.md
  git diff 0.9.19 HEAD -- docs/feature_stenography.md | cat
-->

[速記](https://en.wikipedia.org/wiki/Stenotype)は裁判所のレポート、字幕および耳が不自由な人のための文字起こしで最もよく使われる記述方法です。速記では単語はスペル、音声およびショートカット(要約)ストロークの混合音節で音節化されます。プロの速記者は、標準的なタイピングで通常見られる負担を掛けずに、はるかに少ないエラー(>99.9%の精度)で、200-300 WPM に到達できます。

[Open Steno Project](http://www.openstenoproject.org/)は、速記ストロークを単語とコマンドにリアルタイム変換を提供する Plover と呼ばれるオープンソースプログラムを構築しました。確立された辞書とサポートがあります。

## QWERTY キーボードを使った Plover :id=plover-with-qwerty-keyboard

Plover は全ての標準的な QWERTY キーボードで動作しますが、キーボードが NKRO (n-キーロールオーバー)をサポートする場合は Plover が一度に押された全てのキーを分かるようにするとより効率的です。Plover 用のキーマップの例は `planck/keymaps/default` で見つかります。`PLOVER` レイヤーに切り替えると、数字バーをサポートするためにキーボードの位置が調整されます。

QMK で Plover を使うには、NKRO を有効にし、標準レイアウト以外のものがある場合はオプションでレイアウトを調整します。複数のキーを押しやすくするために、なんらかの速記フレンドリなキーキャップを購入することもできます。

## Steno プロトコルを使った Plover :id=plover-with-steno-protocol

Plover は幾つかの速記マシンの言語も理解します。QMK は2つの言語、TX Bolt と GeminiPR を話すことができます。レイアウトの例は `planck/keymaps/steno` で見つけることができます。

QMKが steno プロトコルを使って Plover と話す場合は、Plover は入力としてキーボードを使いません。標準のキーボードと速記キーボードを行き来したり、あるいは Plover をアクティブ/非アクティブにする必要なく Plover から標準のレイヤーに切り替えることができることを意味します。

このモードでは、Plover はシリアルポートを介して速記マシンと通信すると想定しているため、QMK はオペレーティングシステムに対してキーボードに加えて仮想シリアルポートとして存在しています。デフォルトでは、QMK は TX Bolt プロトコルを話しますが、GeminiPR に切り替えることができます; 最後に使われたプロトコルが不揮発性メモリに格納されるため QMK は再起動時に同じプロトコルを使います。

> 注意: ハードウェアの制限により、仮想シリアルポートとマウスエミュレーションの両方を同時に実行することができないかもしれません。

### TX Bolt :id=tx-bolt

TX Bolt は可変サイズ(1-5バイト)のパケットで非常に単純なプロトコルを介して24個のキーのステータスを通信します。

### GeminiPR :id=geminipr

GeminiPR は42個のキーを6バイトのパケットにエンコードします。TX Bolt は標準的な速記に必要な全てを含んでいますが、GeminiPR は英語ではない速記のサポートを含む、より多くのオプションにも開け放たれています。

## 速記のための QMK の設定 :id=configuring-qmk-for-steno

最初にキーマップの Makefile で速記を有効にします。競合を避けるために、マウスキー、追加キーあるいはその他の USB エンドポイントを無効にする必要もあります。幾つかのプロセッサの内蔵の USB スタックは一定数の USB エンドポイント のみをサポートし、速記のために必要とされる仮想シリアルポートはそれらのうちの3つを使います。

```makefile
STENO_ENABLE = yes
MOUSEKEY_ENABLE = no
```

キーマップで Plover 用の新しいレイヤーを作成します。`keymap_steno.h` を含む必要があります。例については `planck/keymaps/steno/keymap.c` を見てください。レイヤーに切り替えるためのキーとレイヤーから抜けるためのキーを作成することを忘れないでください。その場でモードを切り替えたい場合は、キーコード `QK_STENO_BOLT` および `QK_STENO_GEMINI` を使うことができます。プロトコルのうちの1つのみを使う場合は、初期化関数の中でそれをセットアップすることができます:

```c
void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI); // あるいは STENO_MODE_BOLT
}
```

キーボードを書き込んだら、Plover を起動します。'Configure...' ボタンをクリックします。'Machine' タブの中で目的のプロトコルに対応する速記マシンを選択します。このタブの 'Configure...' ボタンをクリックし、シリアルポートを入力するか 'Scan' をクリックします。ボーレートは 9600 で問題ありません (ただし、115200まで問題無く設定することができます)。(Data Bits: 8, Stop Bits: 1, Parity: N, no flow control) 以外はデフォルトの設定を使います。

ディスプレイタブで 'Open stroke display' をクリックします。Plover を無効にするとキーボードでキーを押すことができるはずで、ストローク表示ウィンドウにそれらが表示されるはずです。キーマップが正しくセットアップされたことを確認するためにこれを使ってください。これで速記をする準備ができました！

## 速記の学習 :id=learning-stenography

* [Plover を学ぶ！](https://sites.google.com/site/learnplover/)
* [QWERTY 速記](http://qwertysteno.com/Home/)
* [Steno Jig](https://joshuagrams.github.io/steno-jig/)
* Plover の[速記学習](https://github.com/openstenoproject/plover/wiki/Learning-Stenography) wiki のより多くのリソース

## Interfacing with the code :id=interfacing-with-the-code

steno コードには3つの捕捉可能なフックがあります。これらの関数を定義した場合、処理の特定のポイントでそれらが呼び出されます; それらが true を返す場合処理が継続され、そうでなければあなたが物事を処理すると想定します。

```c
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]);
```

この関数はコードが送信されようとしている時に呼ばれます。モードは `STENO_MODE_BOLT` あるいは `STENO_MODE_GEMINI` のいずれかです。This represents the actual chord that would be sent via whichever protocol. 提供されるコードを修正して送信されるものを変更することができます。通常の送信プロセスにしたい場合は true を返すのを忘れないでください。

```c
bool process_steno_user(uint16_t keycode, keyrecord_t *record) { return true; }
```

この関数はキーが押されるとキーが処理される前に呼び出されます。キーコードは `QK_STENO_BOLT`、`QK_STENO_GEMINI` あるいは `STN_*` キー値のいずれかでなければなりません。

```c
bool postprocess_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[6], int8_t pressed);
```

この関数はキーが処理された後、ただしコードを送信するかどうかを決める前に呼び出されます。`IS_PRESSED(record->event)` が false で、`pressed` が 0 または 1 の場合は、コードはまもなく送信されますが、まだ送信されてはいません。ここが steno コードあるいはキーのライブ表示などのフックを配置する場所です。


## Keycode Reference :id=keycode-reference

`keymap_steno.h` で定義されています。

> 注意: TX Bolt はキーの完全なセットをサポートしません。QMK での TX Bolt の実装は、GeminiPR キーを最も近い TX Bolt キーにマップします。そのため1つのキーマップが両方で動作します。

| GeminiPR | TX Bolt | Steno Key |
|--------|-------|-----------|
| `STN_N1` | `STN_NUM` | Number bar #1 |
| `STN_N2` | `STN_NUM` | Number bar #2 |
| `STN_N3` | `STN_NUM` | Number bar #3 |
| `STN_N4` | `STN_NUM` | Number bar #4 |
| `STN_N5` | `STN_NUM` | Number bar #5 |
| `STN_N6` | `STN_NUM` | Number bar #6 |
| `STN_N7` | `STN_NUM` | Number bar #7 |
| `STN_N8` | `STN_NUM` | Number bar #8 |
| `STN_N9` | `STN_NUM` | Number bar #9 |
| `STN_NA` | `STN_NUM` | Number bar #A |
| `STN_NB` | `STN_NUM` | Number bar #B |
| `STN_NC` | `STN_NUM` | Number bar #C |
| `STN_S1` | `STN_SL` | `S-` upper |
| `STN_S2` | `STN_SL` | `S-` lower |
| `STN_TL` | `STN_TL` | `T-` |
| `STN_KL` | `STN_KL` | `K-` |
| `STN_PL` | `STN_PL` | `P-` |
| `STN_WL` | `STN_WL` | `W-` |
| `STN_HL` | `STN_HL` | `H-` |
| `STN_RL` | `STN_RL` | `R-` |
| `STN_A` | `STN_A` | `A` vowel |
| `STN_O` | `STN_O` | `O` vowel |
| `STN_ST1` | `STN_STR` | `*` upper-left |
| `STN_ST2` | `STN_STR` | `*` lower-left |
| `STN_ST3` | `STN_STR` | `*` upper-right |
| `STN_ST4` | `STN_STR` | `*` lower-right |
| `STN_E` | `STN_E` | `E` vowel |
| `STN_U` | `STN_U` | `U` vowel |
| `STN_FR` | `STN_FR` | `-F` |
| `STN_PR` | `STN_PR` | `-P` |
| `STN_RR` | `STN_RR` | `-R` |
| `STN_BR` | `STN_BR` | `-B` |
| `STN_LR` | `STN_LR` | `-L` |
| `STN_GR` | `STN_GR` | `-G` |
| `STN_TR` | `STN_TR` | `-T` |
| `STN_SR` | `STN_SR` | `-S` |
| `STN_DR` | `STN_DR` | `-D` |
| `STN_ZR` | `STN_ZR` | `-Z` |
| `STN_FN` | (GeminiPR のみ) |
| `STN_RES1` | (GeminiPR のみ) |
| `STN_RES2` | (GeminiPR のみ) |
| `STN_PWR` | (GeminiPR のみ) |

