# QMK のコードの理解

<!---
  original document: 0.9.55:docs/understanding_qmk.md
  git diff 0.9.55 HEAD -- docs/understanding_qmk.md | cat
-->

このドキュメントでは、QMK ファームウェアがどのように機能するかを非常に高いレベルから説明しようとしています。基本的なプログラミングの概念を理解していることを前提としていますが、(実例を示す必要がある場合を除き) C に精通していることを前提にはしていません。以下のドキュメントの基本的な知識があることを前提としています。

* [入門](ja/getting_started_introduction.md)
* [キーボードがどのように動作するか](ja/how_keyboards_work.md)
* [FAQ](ja/faq.md)

## スタートアップ

QMK は他のコンピュータプログラムと何ら変わりないと考えることができます。開始され、タスクを実行し、そして終了します。プログラムのエントリーポイントは、他の C プログラムと同様に、`main()` 関数です。ただし、QMK を初めて触る人は、`main()` 関数が複数の場所に現れるため、混乱するかもしれません。また、どれを見ればよいか分かりにくいかもしれません。

複数ある理由は、QMK は様々なプラットフォームをサポートするからです。最も一般的なプラットフォームは `lufa` です。これは atmega32u4 のような AVR プロセッサ上で実行されます。また、`chibios` および `vusb` もサポートします。

ここでは AVR プロセッサに焦点を当てます。これは `lufa` プラットフォームを使います。`main()` 関数は [tmk_core/protocol/lufa/lufa.c](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/protocol/lufa/lufa.c#L1028) にあります。関数にざっと目を通すと、(ホストへの USB も含めて)設定された全てのハードウェアが初期化され、プログラムのコア部分が [`while(1)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/protocol/lufa/lufa.c#L1069) で開始されることが分かります。これが[メインループ](#the-main-loop)です。

## メインループ

コードのこの部分は、同じ命令セットを永久にループ処理するため、「メインループ」と呼ばれます。ここはキーボードに必要なことを実行させる関数を QMK が呼び出す場所です。一見、多くの機能を持つように見えるかもしれませんが、大抵の場合、コードは `#define` によって無効にされます。

```
    keyboard_task();
```

ここで、全てのキーボードの固有の機能が実行されます。`keyboard_task()` のソースコードは [tmk_core/common/keyboard.c](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/common/keyboard.c#L216) にあり、マトリックスの変化を検知し、LED の状態をオンオフする責任があります。

`keyboard_task()` に以下を処理するコードがあります:

* [マトリックスのスキャン](#matrix-scanning)
* マウスの処理
* シリアルリンク
* ビジュアライザ
* キーボードの状態の LED (Caps Lock, Num Lock, Scroll Lock)

#### マトリックスのスキャン

マトリックスのスキャンはキーボードファームウェアのコアの機能です。これは今どのキーが押されているかを検知するプロセスであり、キーボードはこの機能を1秒間に何度も何度も実行します。ファームウェアの CPU 時間の 99% はマトリックスのスキャンに費やされていると言っても過言ではありません。

実際のマトリックスの検知には様々な方法がありますが、それはこのドキュメントの対象外です。マトリックスのスキャンをブラックボックスとして扱っても問題ありません。マトリックスの現在の状態を求めると、以下のようなデータ構造を取得します:


```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

これは 4行x5列のテンキー(訳注: 5行x4列の間違いと思われます)のマトリックスを表す直接的な表現のデータ構造です。キーが押されると、マトリックス内のそのキーの位置が、 `0` ではなく `1` として返されます。

マトリックスのスキャンは1秒間に何度も実行されます。正確なレートは様々ですが、知覚できるような遅延を避けるために、秒間に少なくとも10回実行します。

##### マトリックスから物理的なレイアウトへのマップ

キーボード上の各スイッチの状態が分かると、それをキーコードへマップする必要があります。QMK ではキーコードへのマップは C マクロを使うことで行われ、C マクロにより物理的なレイアウトの定義はキーコードの定義から分離されています。(訳注：「キーコードの定義」は「キーコードのマトリクス配列による定義」と思われる)

キーボードレベルで、キーボードのマトリックスを物理キーにマップする C マクロ (一般的には、`LAYOUT()` という名前)を定義します。マトリックスにスイッチがない場所がある場合、このマクロを使って KC_NO を事前に埋め込むことができ、キーマップの定義を扱いやすくすることができます。以下は、テンキー用の `LAYOUT()` マクロです:

```c
#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k33, \
    k40,      k42 \
) { \
    { k00, k01, k02, k03, }, \
    { k10, k11, k12, k13, }, \
    { k20, k21, k22, KC_NO, }, \
    { k30, k31, k32, k33, }, \
    { k40, KC_NO, k42, KC_NO } \
}
```

`LAYOUT()` マクロの2つ目のブロックが、上記のマトリックススキャン配列とどのように一致しているかに注目してください。このマクロはマトリックスのスキャン配列をキーコードにマップするものです。ただし、17キーのテンキーを見ると、マトリックスにはスイッチが置けるが、キーが大きいために実際にはスイッチが無い箇所が3つあることが分かります。これらのスペースに `KC_NO` を設定したので、キーマップ定義には必要ありません。

このマクロを使って、少し変わったマトリックスのレイアウト、例えば [Clueboard rev 2](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/66/rev2/rev2.h) を扱うこともできます。その説明はこのドキュメントの範囲外です。

##### キーコードの割り当て

キーマップレべルでは、上記の `LAYOUT()` マクロを使って、物理的な場所からマトリックスの場所にマッピングします。以下のようになります:

```
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
  KC_P4,   KC_P5,   KC_P6, \
  KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
  KC_P0,            KC_PDOT)
}
```

これら全ての引数が、前のセクションの `LAYOUT()` マクロの前半とどのように一致しているかについて注目してください。このようにして、キーコードを取得して、それを前述のマトリックススキャンにマップします。

##### 状態変更の検知

上記のマトリックススキャンはある時点のマトリックスの状態を伝えますが、コンピュータは変更のみを知りたいだけで、現在の状態を気にしません。QMK は最後のマトリックススキャンの結果を格納し、このマトリックスから結果を比較して、いつキーが押されたか放されたかを決定します。

例を見てみましょう。キーボードスキャンループの途中に移動して、前のスキャンが以下のようになっていることがわかったとします:

```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

現在のスキャンが完了すると、以下のように見えるとします:

```
{
    {1,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

キーマップと比較すると、押されたキーが KC_NLCK であることが分かります。ここから、`process_record` 関数群を呼び出します。

<!-- FIXME: Magic happens between here and process_record -->

##### Process Record

`process_record()` 関数自体は一見簡単に見えますが、その内部は QMK の様々なレベルで機能を上書きするためのゲートウェイが隠されています。キーボード/キーマップレベルの機能について調べる必要があるときは、以下に列挙した一連のイベントを手引帳として使います。`rules.mk` またはほかの場所で設定されたオプションに応じて、最終的なファームウェアに以下の関数のサブセットのみが含まれます。

* [`void process_record(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/common/action.c#L172)
   * [`bool process_record_quantum(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L206)
      * [このレコードをキーコードにマップする](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L226)
      * [`void velocikey_accelerate(void)`](https://github.com/qmk/qmk_firmware/blob/c1c5922aae7b60b7c7d13d3769350eed9dda17ab/quantum/velocikey.c#L27)
      * [`void preprocess_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_tap_dance.c#L119)
      * [`bool process_key_lock(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_key_lock.c#L62)
      * [`bool process_clicky(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_clicky.c#L79)
      * [`bool process_haptic(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/2cee371bf125a6ec541dd7c5a809573facc7c456/drivers/haptic/haptic.c#L216)
      * [`bool process_record_kb(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/card/card.c#L20)
         * [`bool process_record_user(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/card/keymaps/default/keymap.c#L58)
      * [`bool process_midi(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_midi.c#L81)
      * [`bool process_audio(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_audio.c#L19)
      * [`bool process_steno(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_steno.c#L160)
      * [`bool process_music(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_music.c#L114)
      * [`bool process_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_tap_dance.c#L141)
      * [`bool process_unicode_common(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicode_common.c#L169) は、以下のいずれかを呼び出します:
         * [`bool process_unicode(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicode.c#L20)
         * [`bool process_unicodemap(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicodemap.c#L46)
         * [`bool process_ucis(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_ucis.c#L95)
      * [`bool process_leader(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_leader.c#L51)
      * [`bool process_combo(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_combo.c#L115)
      * [`bool process_printer(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_printer.c#L77)
      * [`bool process_auto_shift(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_auto_shift.c#L94)
      * [`bool process_terminal(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_terminal.c#L264)
      * [Quantum 固有のキーコードを識別して処理する](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L291)

この一連のイベントの中の任意のステップで (`process_record_kb()` のような)関数は `false` を返して、以降の処理を停止することができます。

この呼び出しの後で、`post_process_record()` が呼ばれます。これはキーコードが通常処理された後に実行する必要がある追加のクリーンアップを処理するために使うことができます。

* [`void post_process_record(keyrecord_t *record)`]()
   * [`void post_process_record_quantum(keyrecord_t *record)`]()
      * [このレコードをキーコードにマップする]()
      * [`void post_process_clicky(uint16_t keycode, keyrecord_t *record)`]()
      * [`void post_process_record_kb(uint16_t keycode, keyrecord_t *record)`]()
         * [`void post_process_record_user(uint16_t keycode, keyrecord_t *record)`]()

<!--
#### Mouse Handling

FIXME: This needs to be written

#### Serial Link(s)

FIXME: This needs to be written

#### Visualizer

FIXME: This needs to be written

#### Keyboard state LEDs (Caps Lock, Num Lock, Scroll Lock)

FIXME: This needs to be written

-->
