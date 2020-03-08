# タップダンス: 1つのキーが3つ、5つまたは100の異なる動作をします

<!---
  original document: 634b277b0:docs/feature_tap_dance.md
  git diff 634b277b0 HEAD -- docs//feature_tap_dance.md | cat
--> 

## イントロダクション

セミコロンキーを1回叩くと、セミコロンが送信されます。2回素早く叩くと、コロンが送信されます。3回叩くと、あなたのキーボードのLEDが激しく踊るように明滅します。これは、タップダンスでできることの一例です。それは、コミュニティが提案したとても素敵なファームウェアの機能の1つで、[algernon](https://github.com/algernon) がプルリクエスト [#451](https://github.com/qmk/qmk_firmware/pull/451) で考えて作ったものです。algernon が述べる機能は次の通りです:

この機能を使うと、特定のキーが、タップした回数に基づいて異なる振る舞いをします。そして、割り込みがあった時は、割り込み前に上手く処理されます。

## `ACTION_FUNCTION_TAP` との比較について

`ACTION_FUNCTION_TAP` はタップダンスに似た機能を提供しますが、注目すべきいくつかの重要な違いがあります。違いを確認するため、いくつかの設定を調べてみましょう。1つのキーを1回タップすると `Space` キーが送信され、2回タップすると `Enter` キーが送信されるよう設定します。

`ACTION_FUNCTION_TAP` では、これを設定するのはかなり大変で、キーの順番が割り込まれた時に割り込んだキーが最初に送られるという問題に直面します。例えば、`SPC a` は、もし `SPC` と `a` が `TAPPING_TERM` で設定した時間内に両方とも入力された場合、結果として `a SPC` が送信されます。タップダンス機能を使う場合、正しく `SPC a` が送信されます（`TAPPING_TERM` で設定した時間内に `SPC` と `a` を入力した場合であっても）。

割り込みを正しくハンドリングして目的を達成するため、タップダンスの実装ではシステムの2つの部分をフックします: `process_record_quantum()` とマトリックススキャンです。この2つの部分については以下で説明しますが、今注意すべき点は、マトリックススキャンでは、キーが押されていない時でもタップのシーケンスをタイムアウトにできる必要があるということです。そうすれば、`TAPPING_TERM` の時間が経過した後、`SPC` だけがタイムアウトになって登録されます。

## タップダンスの使い方

一般論は十分です。タップダンスの実際の使い方を見てみましょう！

最初に、あなたの `rules.mk` ファイルで `TAP_DANCE_ENABLE=yes` と設定する必要があります。なぜならば、デフォルトでは無効になっているからです。これでファームウェアのサイズが1キロバイトほど増加します。

オプションで、あなたの `config.h` ファイルに次のような設定を追加して、`TAPPING_TERM` の時間をカスタマイズしたほうが良いです。

```
#define TAPPING_TERM 175
```

`TAPPING_TERM` の時間は、あなたのタップダンスのキーのタップとタップの間の時間として許可された最大の時間で、ミリ秒単位で計測されます。例えば、もし、あなたがこの上にある `#define` ステートメントを使い、1回タップすると `Space` が送信され、2回タップすると `Enter` が送信されるタップダンスキーをセットアップした場合、175ミリ秒以内に2回キーをタップすれば `ENT` だけが送信されるでしょう。もし、1回タップしてから175ミリ秒以上待ってからもう一度タップすると、`SPC SPC` が送信されます。

次に、いくつかのタップダンスのキーを定義するためには、`TD()` マクロ — `F()` マクロに似ています — を使うのが最も簡単です。これは数字を受け取り、この数字は後で `tap_dance-actions` 配列のインデックスとして使われます。

その後、`tap_dance_actions` 配列を使って、タップダンスキーを押した時のアクションを定義します。現在は、5つの可能なオプションがあります:

* `ACTION_TAP_DANCE_DOUBLE(kc1, kc2)`: 1回タップすると `kc1` キーコードを送信し、2回タップすると `kc2` キーコードを送信します。キーを押し続けているときは、適切なキーコードが登録されます: キーを押し続けた場合は `kc1`、一度タップしてから続けてもう一度キーを押してそのまま押し続けたときは、 `kc2` が登録されます。
* `ACTION_TAP_DANCE_LAYER_MOVE(kc, layer)`: 1回タップすると `kc` キーコードが送信され、2回タップすると `layer` レイヤーに移動します(これは `TO` レイヤーキーコードのように機能します)。
    * この機能は `ACTION_TAP_DANCE_DUAL_ROLE` と同じですが、機能が明確になるように関数名を変更しました。どちらの関数名でも実行できます。
* `ACTION_TAP_DANCE_LAYER_TOGGLE(kc, layer)`: 1回タップすると `kc` キーコードが送信され、2回タップすると `layer` の状態をトグルします(これは `TG` レイヤーキーコードのように機能します)。
* `ACTION_TAP_DANCE_FN(fn)`: ユーザーキーマップに定義した指定の関数が呼び出されます。タップダンス実行の回数分タップすると、最後の時点で呼び出されます。
* `ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)`: タップする度にユーザーキーマップに定義した最初の関数が呼び出されます。タップダンスの実行が終わった時点で2番目の関数が呼び出され、タップダンスの実行をリセットするときに最後の関数が呼び出されます。
* `ACTION_TAP_DANCE_FN_ADVANCED_TIME(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn, tap_specific_tapping_term)`: これは `ACTION_TAP_DANCE_FN_ADVANCED` と同じように機能します。しかし、`TAPPING_TERM` で事前に定義した時間に代えて、カスタマイズしたタップ時間を使えます。

最初のオプションで、1つのキーに2つの役割を持たせる大抵のケースには十分です。例えば、`ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT)` は、1回タップすると `Space` を送信し、2回タップすると `Enter` を送信します。

!> ここでは [基本的なキーコード](ja/keycodes_basic.md) だけがサポートされていることを覚えておいてください。カスタムキーコードはサポートされていません。

最初のオプションに似ていますが、2番目のオプションは単純なレイヤー切替のケースに適しています。

これ以上に複雑なケースの場合、3番目か4番目のオプションを使います。（以下でそれらの例を列挙します）

最後に、5番目のオプションは、もし、タップダンスキーをコードに追加した後、非タップダンスキーが奇妙な振る舞いを始めた時に特に役に立ちます。ありうる問題は、あなたがタップダンスキーを使いやすくするために `TAPPING_TERM` の時間を変更した結果、その他のキーが割り込みを処理する方法が変わってしまったというものです。


## 実装の詳細

さて、説明の大部分はここまでです！ 以下に挙げているいくつかの例に取り組むことができるようになり、あなた自身のタップダンスの機能を開発できるようになります。しかし、もし、あなたが裏側で起きていることをより深く理解したいのであれば、続けてそれが全てどのように機能するかの説明を読みましょう！

メインエントリーポイントは、`process_tap_dance()` で、`process_record_quantum()` から呼び出されます。これはキーを押すたびに実行され、ハンドラは早期に実行されます。この関数は、押されたキーがタップダンスキーがどうか確認します。
もし、押されたキーがタップダンスキーではなく、かつ、タップダンスが実行されていたなら、最初にそれを処理し、新しく押されたキーをキューに格納します。
もし、押されたキーがタップダンスキーであるなら、既にアクティブなタップダンスと同じキーか確認します（もしアクティブなものがある場合、それと）。
異なる場合、まず、古いタップダンスを処理し、続いて新しいタップダンスを登録します。
同じ場合、カウンタの値を増やし、タイマーをリセットします。

このことは、あなたは再びキーをタップするまでの時間として `TAPPING_TERM` の時間を持っていることを意味します。そのため、あなたは1つの `TAPPING_TERM` の時間内に全てのタップを行う必要はありません。これにより、キーの反応への影響を最小限に抑えながら、より長いタップ回数を可能にします。 

次は `matrix_scan_tap_dance()` です。この関数はタップダンスキーのタイムアウトを制御します。

柔軟性のために、タップダンスは、キーコードの組み合わせにも、ユーザー関数にもなることができます。後者は、より高度なタップ回数の制御や、LED を点滅させたり、バックライトをいじったり、等々の制御を可能にします。これは、1つの共用体と、いくつかの賢いマクロによって成し遂げられています。

# 実装例

## シンプルな実装例

ここに1つの定義のための簡単な例があります。

1. `rules.mk` に `TAP_DANCE_ENABLE = yes` を追加します。
2. `config.h` ファイル（`qmk_firmware/keyboards/planck/config.h` からあなたのキーマップディレクトリにコピーできます）に `#define TAPPING_TERM 200` を追加します。
3. `keymap.c` ファイルに変数とタップダンスの定義を定義し、それからキーマップに追加します。

```c
// タップダンスの宣言
enum {
  TD_ESC_CAPS = 0
};

// タップダンスの定義
qk_tap_dance_action_t tap_dance_actions[] = {
  // 1回タップすると Escape キー、2回タップすると Caps Lock。
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// ほかの宣言もカンマで区切ってここに記述します
};

// レイヤー定義で、キーコードの代わりにタップダンスキーを追加します
TD(TD_ESC_CAPS)
```

## 複雑な実装例

このセクションでは、いくつかの複雑なタップダンスの例を詳しく説明します。
例で使われている全ての列挙型はこのように宣言します。

```c
// 全ての例のための列挙型定義
enum {
 CT_SE = 0,
 CT_CLN,
 CT_EGG,
 CT_FLSH,
 X_TAP_DANCE
};
```
### 例1: 1回タップすると `:` を送信し、2回タップすると `;` を送信する

```c
void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  } else {
    register_code (KC_SCLN);
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_SCLN);
  }
}

// 全てのタップダンス関数はここに定義します。ここでは1つだけ示します。
qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
};
```

### 例2: 100回タップした後に "Safety Dance!" を送信します

```c
void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 100) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg)
};
```

### 例3: 1つずつ LED を点灯させてから消灯する

```c
// タップする毎に、LED を右から左に点灯します。
// 4回目のタップで、右から左に消灯します。
void dance_flsh_each(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    ergodox_right_led_3_on();
    break;
  case 2:
    ergodox_right_led_2_on();
    break;
  case 3:
    ergodox_right_led_1_on();
    break;
  case 4:
    ergodox_right_led_3_off();
    _delay_ms(50);
    ergodox_right_led_2_off();
    _delay_ms(50);
    ergodox_right_led_1_off();
  }
}

// 4回目のタップで、キーボードをフラッシュ状態にセットします。
void dance_flsh_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 4) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

// もしフラッシュ状態にならない場合、LED を左から右に消灯します。
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
  ergodox_right_led_1_off();
  _delay_ms(50);
  ergodox_right_led_2_off();
  _delay_ms(50);
  ergodox_right_led_3_off();
}

// 全てのタップダンス関数を一緒に表示しています。この例3は "CT_FLASH" です。
qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_SE]  = ACTION_TAP_DANCE_DOUBLE (KC_SPC, KC_ENT)
 ,[CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
 ,[CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg)
 ,[CT_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED (dance_flsh_each, dance_flsh_finished, dance_flsh_reset)
};
```

### 例4: クアッドファンクションのタップダンス

[DanielGGordon](https://github.com/danielggordon) によるもの

キーを押す回数と、キーを押し続けるかタップするかによって、1つのキーに4つ（またはそれ以上）の機能を持たせることができるようになります。

以下に例をあげます:
*  1回タップ = `x` を送信
*  押し続ける = `Control` を送信
*  2回タップ = `Escape` を送信
*  2回タップして押し続ける = `Alt` を送信

## 準備

'クアッドファンクションのタップダンス' を利用できるようにするには、いくつかのものが必要になります。

`keymap.c` ファイルの先頭、つまりキーマップの前に、以下のコードを追加します。

```c
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //シングルタップを2回送信
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

// タップダンスの列挙型
enum {
  X_CTL = 0,
  SOME_OTHER_DANCE
};

int cur_dance (qk_tap_dance_state_t *state);

//xタップダンスのための関数。キーマップで利用できるようにするため、ここに置きます。
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

```

次に、`keymap.c` ファイルの末尾に、次のコードを追加する必要があります。

```c
/* 実行されるタップダンスの種類に対応する整数を返します。
 *
 * タップダンスの状態を判別する方法: 割り込みと押下。
 *
 * 割り込み:
 *   タップダンスの状態が「割り込み」の場合、他のキーがタップ時間中に押されたことを意味します。
 *   これは通常、キーを「タップ」しようとしていることを示します。
 *
 * 押下:
 *   キーがまだ押されているかどうか。この値が true の場合、タップ時間が終了したことを意味しますが、
 *   キーはまだ押されたままです。これは通常、キーが「ホールド」されていることを意味します。
 *
 * タップダンスに関して、qmk ソフトウェアで現在不可能なことの1つは、"permissive hold" 機能を
 * 模倣することです。
 * 一般に、高度なタップダンスは一般的に入力される文字で使われた場合にうまく機能しません。
 * 例えば "A" の場合。タップダンスは文字の入力中に入力しない文字以外のキーで使うのが最適です。
 *
 * 高度なタップダンスを配置するのに適した場所:
 *   z、q、x、j、k、v、b、ファンクションキー、home/end、コンマ、セミコロン
 *
 * タップダンスキーの「最適な配置場所」の基準:
 *   文章中で頻繁に入力するキーでないこと
 *   ダブルタップに頻繁に使われるキーでないこと。例えば、'tab' はターミナルやウェブフォームで
 *   しばしばダブルタップされます。そのため、タップダンスでは 'tab' は良い選択ではありません。
 *   一般的な単語で2回続けて使われる文字でないこと。例えば 'pepper' 中の 'p'。もしタップダンス機能が
 *   文字 'p' に存在する場合、'pepper' という単語は入力するのが非常にいらだたしいものになるでしょう。
 *
 * 3つ目の点については、'DOUBLE_SINGLE_TAP' が存在しますが、これは完全にはテストされていません
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //キーは割り込まれていませんが、まだ押し続けられています。'HOLD' を送信することを意味します。
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP は "pepper" と入力することと、'pp' と入力したときに実際に
     * ダブルタップしたい場合とを区別するためのものです。
     * この戻り値の推奨されるユースケースは、'ダブルタップ' 動作やマクロではなく、
     * そのキーの2つのキー入力を送信したい場合です。
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //誰も同じ文字を3回入力しようとしていないと仮定します(少なくとも高速には)。
  //タップダンスキーが 'KC_W' で、"www." と高速に入力したい場合、ここに例外を追加して
  //'TRIPLE_SINGLE_TAP' を返し、'DOUBLE_SINGLE_TAP' のようにその列挙型を定義する
  //必要があります。
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //マジックナンバー。いつかこのメソッドはより多くの押下に対して機能するよう拡張されるでしょう
}

//'x' タップダンスの 'tap' のインスタンスをインスタンス化します
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_X); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_TAP: register_code(KC_ESC); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //最後の case は高速入力用です。キーが `f` であると仮定します:
    //例えば、`buffer` という単語を入力するとき、`Esc` ではなく `ff` を送信するようにします。
    //高速入力時に `ff` と入力するには、次の文字は `TAPPING_TERM` 以内に入力する必要があります。
    //`TAPPING_TERM` はデフォルトでは 200ms です。
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_X); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_ESC); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [X_CTL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};
```

これで、キーマップのどこでも簡単に `TD(X_CTL)` マクロが使えます。

もし、この機能をユーザスペースで実現したい場合、 [DanielGGordon](https://github.com/qmk/qmk_firmware/tree/master/users/gordon) がユーザスペースでどのように実装しているか確認してください。

> この設定の "hold" は、タップダンスのタイムアウト（`ACTION_TAP_DANCE_FN_ADVANCED_TIME` 参照）の **後** に起こります。即座に "hold" を得るためには、条件から `state->interrupted` の確認を除きます。結果として、複数回のタップのための時間をより多く持つことで快適な長いタップの期限を使うことができ、そして、"hold" のために長く待たないようにすることができます(2倍の `TAPPING TERM` で開始してみてください)。

### 例5: タップダンスを高度なモッドタップとレイヤータップキーに使う :id=example-5-using-tap-dance-for-advanced-mod-tap-and-layer-tap-keys

タップダンスは、タップされたコードが基本的なキーコード以外の場合に、 `MT()` と `LT()` マクロをエミュレートするのに利用できます。これは、通常 `Shift` を必要とする '(' や '{' のようなキーや、`Control + X` のように他の修飾されたキーコードをタップされたキーコードとして送信することに役立ちます。

あなたのレイヤーとカスタムキーコードの下に、以下のコードを追加します。

```c
//タップダンスのキーコード
enum td_keycodes { 
  ALT_LP //例: 押していると `LALT`、タップすると `(`。それぞれのタップダンスの追加のキーコードを追加します
};

//必要な数のタップダンス状態を含むタイプを定義します
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

//タップダンスの状態の型のグローバルインスタンスを作ります
static td_state_t td_state;

//タップダンス関数を宣言します:

//現在のタップダンスの状態を特定するための関数
int cur_dance (qk_tap_dance_state_t *state);

//それぞれのタップダンスキーコードに適用する `finished` と `reset` 関数
void altlp_finished (qk_tap_dance_state_t *state, void *user_data);
void altlp_reset (qk_tap_dance_state_t *state, void *user_data);
```

キーレイアウト（`LAYOUT`）の下に、タップダンスの関数を定義します。

```c
// 返却するタップダンス状態を特定します
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_SINGLE_TAP; }
  else { return 3; } // 上記で返却する最大の状態の値より大きい任意の数
}
 
// 定義する各タップダンスキーコードのとりうる状態を制御します:

void altlp_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LALT)); // レイヤータップキーの場合、ここでは `layer_on(_MY_LAYER)` を使います
      break;
    case DOUBLE_SINGLE_TAP: // タップ時間内に2つの括弧 `((` の入れ子を可能にします
      tap_code16(KC_LPRN);
      register_code16(KC_LPRN);
  }
}

void altlp_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LALT)); // レイヤータップキーの場合、ここでは `layer_off(_MY_LAYER)` を使います
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LPRN);
  }
}

// 各タップダンスキーコードの `ACTION_TAP_DANCE_FN_ADVANCED()` を定義し、`finished` と `reset` 関数を渡します
qk_tap_dance_action_t tap_dance_actions[] = {
  [ALT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset)
};
```

それぞれのタップダンスキーコードをキーマップに含めるときは、`TD()` マクロでキーコードをラップします。例: `TD(ALT_LP)`

### 例6: タップダンスを一時的なレイヤー切り替えとレイヤートグルキーに使う

タップダンスは、MO(layer) と TG(layer) 機能を模倣することにも使用できます。この例では、1回タップすると `KC_QUOT` 、1回押してそのまま押し続けたら `MO(_MY_LAYER)` 、2回タップしたときは `TG(_MY_LAYER)` として機能するキーを設定します。

最初のステップは、あなたの `keymap.c` ファイルの最初のあたりに以下のコードを追加します。

```c
typedef struct {
  bool is_press_action;
  int state;
} tap;

//必要な数のタップダンス状態のタイプを定義します
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

enum {
  QUOT_LAYR = 0  //カスタムタップダンスキー。他のタップダンスキーはこの列挙型に追加します
};

//タップダンスキーで使われる関数を宣言します

//全てのタップダンスに関連する関数
int cur_dance (qk_tap_dance_state_t *state);

//個別のタップダンスに関連する関数
void ql_finished (qk_tap_dance_state_t *state, void *user_data);
void ql_reset (qk_tap_dance_state_t *state, void *user_data);
```

あなたの `keymap.c` ファイルの最後の方に以下のコードを追加します。

```c
//現在のタップダンスの状態を決定します
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

//この例のタップダンスキーに関連付けられた "tap" 構造体を初期化します
static tap ql_tap_state = {
  .is_press_action = true,
  .state = 0
};

//タップダンスキーの動作をコントロールする関数
void ql_finished (qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state) {
    case SINGLE_TAP: 
      tap_code(KC_QUOT); 
      break;
    case SINGLE_HOLD: 
      layer_on(_MY_LAYER); 
      break;
    case DOUBLE_TAP: 
      //レイヤーが既にセットされているか確認します
      if (layer_state_is(_MY_LAYER)) {
        //レイヤーが既にセットされていたら、オフにします。
        layer_off(_MY_LAYER);
      } else { 
        //レイヤーがセットされていなかったら、オンにします。
        layer_on(_MY_LAYER);
      }
      break;
  }
}

void ql_reset (qk_tap_dance_state_t *state, void *user_data) {
  //キーを押し続けていて今離したら、レイヤーをオフに切り替えます。
  if (ql_tap_state.state==SINGLE_HOLD) {
    layer_off(_MY_LAYER);
  }
  ql_tap_state.state = 0;
}

//タップダンスキーを機能に関連付けます
qk_tap_dance_action_t tap_dance_actions[] = {
  [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};
```

上記のコードは、前の例で使われたコードに似ています。注意する1つのポイントは、必要に応じてレイヤーを切り替えられるように、どのレイヤーがアクティブになっているかいつでも確認できる必要があることです。これを実現するために、引数で与えられた `layer` がアクティブなら `true` を返す `layer_state_is( layer )`  を使います。

`cur_dance()` と `ql_tap_state` の使い方は、上の例と似ています。

`ql_finished` 関数における `case:SINGLE_TAP` は、上の例と似ています。`case:SINGLE_HOLD` は、`ql_reset()` と連動してタップダンスキーを押している間 `_MY_LAYER` に切り替わり、キーを離した時に `_MY_LAYER` から離れます。これは、`MO(_MY_LAYER)` に似ています。`case:DOUBLE_TAP` は、`_MY_LAYER` がアクティブレイヤーかどうかを確認することによって動きます。そして、その結果に基づいてレイヤーのオン・オフをトグルします。これは `TG(_MY_LAYER)` に似ています。

`tap_dance_actions[]` は、上の例に似ています。 `ACTION_TAP_DANCE_FN_ADVANCED()` の代わりに `ACTION_TAP_DANCE_FN_ADVANCED_TIME()` を使ったことに注意してください。
この理由は、私は、非タップダンスキーを使うにあたり `TAPPING_TERM` が短い(175ミリ秒以内)方が好きなのですが、タップダンスのアクションを確実に完了させるには短すぎるとわかったからです——そのため、ここでは時間を275ミリ秒に増やしています。

最後に、このタップダンスキーを動かすため、忘れずに `TD(QUOT_LAYR)` を `keymaps[]` に加えてください。 
