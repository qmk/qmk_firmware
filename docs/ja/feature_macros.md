# マクロ

<!---
  original document: 0.9.43:docs/feature_macros.md
  git diff 0.9.43 HEAD -- docs/feature_macros.md | cat
-->

マクロにより、1つのキーを押すだけで複数のキーストロークを送信することができます。QMK にはマクロを定義し使う方法が幾つかあります。これらはなんでもすることができます: よく使うフレーズの入力、コピーペースト、反復的なゲームの動き、あるいはコードを書くことさえ手助けします。

!> **セキュリティの注意**: マクロを使って、パスワード、クレジットカード番号、その他の機密情報のいずれも送信することが可能ですが、それは非常に悪い考えです。あなたのキーボードを手に入れた人は誰でもテキストエディタを開いてその情報にアクセスすることができます。

## 新しい方法: `SEND_STRING()` と `process_record_user`

単語またはフレーズを入力するキーが欲しい時があります。最も一般的な状況のために `SEND_STRING()` を提供しています。これは文字列(つまり、文字のシーケンス)を入力します。簡単にキーコードに変換することができる全ての ASCII 文字がサポートされています (例えば、`qmk 123\n\t`)。

以下は2キーのキーボードのための `keymap.c` の例です:

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // キーコード QMKBEST が押された時
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // キーコード QMKBEST が放された時
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {QMKBEST, KC_ESC},
        // ...
    },
};
```

ここで起きることは以下の通りです:
最初に他のキーコードで使用されていない範囲で新しいカスタムキーコードを定義します。
次に、`process_record_user` 関数を使います。これはキーが押されるか放されるたびに呼び出され、カスタムキーコードがアクティブかどうかを確認します。
アクティブな場合、`SEND_STRING` マクロ (これは C プロセッサのマクロで、QMK のマクロと混同しないでください)を介して文字列 `"QMK is the best thing ever!"` をコンピュータに送信します。
呼び出し元に、処理したばかりのキー押下を通常通り(機能を置き換えたり変更したりしなかったので)処理し続けるよう指示するため、`true` を返します。
最後に、最初のボタンがマクロをアクティブにし、2番目のボタンが単なるエスケープボタンになるようにキーマップを定義します。

複数のマクロを追加することもできます。
以下のように、別のキーコードを追加し、switch 文に別の case ラベルを追加することで、それを行うことができます:

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    MY_OTHER_MACRO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // キーコード QMKBEST が押された時
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // キーコード QMKBEST が放された時
        }
        break;

    case QMKURL:
        if (record->event.pressed) {
            // キーコード QMKURL が押された場合
            SEND_STRING("https://qmk.fm/\n");
        } else {
            // キーコード QMKURL が放された場合
        }
        break;

    case MY_OTHER_MACRO:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("ac")); // 全てを選択しコピーします
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {MY_CUSTOM_MACRO, MY_OTHER_MACRO},
        // ...
    },
};
```

### 高度なマクロ

`process_record_user()` 関数のほかに、`post_process_record_user()` 関数があります。これは `process_record` の後に実行され、キーストロークが送信された後の処理に使用できます。これは例えば、通常のキーの前に押され、通常のキーの後で放されるキーがほしい場合に便利です。

この例では、通常のキー入力を変更して、キーストロークが通常送信される前に `F22` が押されるようにし、キーが放された__後にのみ__ `F22` キーを放します。

```c
static uint8_t f22_tracker;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: // F22 をスキップする方法に注意してください
    case KC_F23 ... KC_EXSEL: //exsel は修飾キーの直前のキーです
      if (record->event.pressed) {
        register_code(KC_F22); //これは F22 を押したことを送信することを意味します
        f22_tracker++;
        register_code(keycode);
        return false;
      }
      break;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: // F22 をスキップする方法に注意してください
    case KC_F23 ... KC_EXSEL: //exsel は修飾キーの直前のキーです
      if (!record->event.pressed) {
        f22_tracker--;
        if (!f22_tracker) {
            unregister_code(KC_F22); //これは F22 を放したことを送信することを意味します
        }
      }
      break;
  }
}
```


### タップ、ダウン、アップ

`Ctrl` あるいは `Home` など、ソースコードに文字列として表記できないキーをマクロで使うこともできます。
以下のようにラップすることで任意のコードを送信することができます:

* `SS_TAP()` キーを押して放します。
* `SS_DOWN()` キーを押します (ただし、放しません)。
* `SS_UP()` キーを放します。

例えば:

    SEND_STRING(SS_TAP(X_HOME));

`KC_HOME` をタップします - プリフィックスが `X_` で `KC_` ではないことに注意してください。以下のように、他の文字列と組み合わせることもできます:

    SEND_STRING("VE"SS_TAP(X_HOME)"LO");

これは "VE" に続けて `KC_HOME` をタップ、そして "LO" (新しい行の場合は "LOVE" と綴る)を送信します。

文字列に遅延を追加することもできます:

* `SS_DELAY(msecs)` は指定されたミリ秒だけ遅らせます。

例えば:

    SEND_STRING("VE" SS_DELAY(1000) SS_TAP(X_HOME) "LO");

これは "VE" 、1秒の遅延、`KC_HOME` をタップ、"LO" (新しい行の場合は "LOVE" と綴るが、中間に遅延がある) を送信します。

使用できるモッドショートカットもいくつかあります:

* `SS_LCTL(文字列)`
* `SS_LSFT(文字列)`
* `SS_LALT(文字列)`、`SS_LOPT(文字列)`
* `SS_LGUI(文字列)`、`SS_LCMD(文字列)`、`SS_LWIN(文字列)`
* `SS_RCTL(文字列)`
* `SS_RSFT(文字列)`
* `SS_RALT(文字列)`、`SS_ROPT(文字列)`、`SS_ALGR(文字列)`
* `SS_RGUI(文字列)`、`SS_RCMD(文字列)`、`SS_RWIN(文字列)`

これらはそれぞれの修飾キーを押し、指定された文字列を送信してから、修飾キーを解放します。
それらは以下のように使うことができます:

    SEND_STRING(SS_LCTL("a"));

これは、左 Control +`a` (左 Control をダウンし、`a`、左 Control をアップ)を送信します - それらは文字列(例えば `"k"`)であり、`X_K` キーコードでは無いことに注意してください。

### 代替キーマップ

デフォルトでは、QWERTY レイアウトの US キーマップを想定しています; それを変更したい場合(例えば OS がソフトウェア Colemak を使う場合)、キーマップのどこかに以下を含めます:

    #include <sendstring_colemak.h>

### メモリ内の文字列

何らかの理由で文字列を操作していて、(リテラル、文字列定数の代わりに)生成したばかりのものを出力する必要がある場合は、以下のように `send_string()` を使うことができます:

```c
char my_str[4] = "ok.";
send_string(my_str);
```

上で定義したショートカットは `send_string()` では動作しないですが、必要に応じて別の行に分けることができます:

```c
char my_str[4] = "ok.";
SEND_STRING("I said: ");
send_string(my_str);
SEND_STRING(".."SS_TAP(X_END));
```


## 高度なマクロ関数

マクロの生成に役立つ関数が幾つかあります。マクロの中にかなり高度なコードを書くことができますが、機能が複雑になりすぎる場合は、代わりにカスタムキーコードを定義することをお勧めします。マクロはシンプルにしなければなりません。

?> 追加の機能として、[便利な関数](ja/ref_functions.md) の中で説明される関数を使うこともできます。例えば `reset_keyboard()` によりマクロの一部としてキーボードをリセットすることができます。

### `record->event.pressed`

これでスイッチが押されているか放されているかどうかをテストすることができます。以下が例です。

```c
    if (record->event.pressed) {
        // キーダウン時
    } else {
        // キーアップ時
    }
```

### `register_code(<kc>);`

これはコンピュータに `<kc>` キーダウンイベントを送信します。例として `KC_ESC`、`KC_C`、`KC_4` や、`KC_LSFT` と `KC_LGUI` のような修飾キーなどもあります。

### `unregister_code(<kc>);`

`register_code` 関数と対応して、これは `<kc>` キーアップイベントをコンピュータに送信します。これを使わない場合、キーは送信されるまで押し続けられます。

### `tap_code(<kc>);`

これは `register_code(<kc>)` を送信し、その後 `unregister_code(<kc>)` を送信します。押下とリリースイベントの両方を送信する場合に便利です (押し続けるのではなく、キーを"タップ"する)。

タップの登録(解除)に問題がある場合、`config.h` ファイルで `#define TAP_CODE_DELAY 100` を設定することで、登録イベントと解除イベントの間に遅延を追加することができます。値はミリ秒です。

### `register_code16(<kc>);`、`unregister_code16(<kc>);`、`tap_code16(<kc>);`

これらの関数は対応する通常の関数と同様に機能しますが、修飾キーで修飾されたキーコードを使うことができます (Shift、Alt、Control、GUI を適用)。

例えば、修飾キーを押して(`register_code()`して)、キーコードを押す(`register_code()`する)代わりに、`register_code16(S(KC_5));` を使うことができます。

### `clear_keyboard();`

これは現在押されている全ての修飾キーとキーをクリアします。

### `clear_mods();`

これは現在押されている全ての修飾キーをクリアします。

### `clear_keyboard_but_mods();`

これは現在押されている修飾キー以外の全てのキーをクリアします。

## 高度な例:

### スーパー ALT↯TAB

このマクロは `KC_LALT` を登録し、`KC_TAB` をタップして、1000ms 待ちます。キーが再度タップされると、別の `KC_TAB` が送信されます; タップが無い場合、`KC_LALT` が登録解除され、ウィンドウを切り替えることができます。

```c
bool is_alt_tab_active = false;    # keymap.c の先頭付近にこれを追加します
uint16_t alt_tab_timer = 0;        # すぐにそれらを使います

enum custom_keycodes {             # 素晴らしいキーコードを用意してください
  ALT_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               # これはキーコードを利用したつまらない作業のほとんどを行います。
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {     # とても重要なタイマー
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
```

---

## **(非推奨)** 古い方法: `MACRO()` と `action_get_macro`

!> これは TMK から継承されており、更新されていません - 代わりに `SEND_STRING` と `process_record_user` を使うことをお勧めします。

デフォルトでは、QMK はマクロが無いことを前提としています。マクロを定義するには、`action_get_macro()` 関数を作成します。例えば:

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
            case 1:
                return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
        }
    }
    return MACRO_NONE;
};
```

これは割り当てられているキーが押された時に実行される2つのマクロを定義します。キーが放された時にそれらを実行したい場合は、if 文を変更することができます。

    if (!record->event.pressed) {

### マクロコマンド

マクロは以下のコマンドを含めることができます:

* I() はストロークの間隔をミリ秒単位で変更します。
* D() はキーを押します。
* U() はキーを放します。
* T() はキーをタイプ(押して放す)します。
* W() は待ちます (ミリ秒)。
* END 終了マーク。

### マクロをキーにマッピングする

マクロを呼び出すにはキーマップ内で `M()` 関数を使います。例えば、2キーのキーボードのキーマップは以下の通りです:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        M(0), M(1)
    ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
            case 1:
                return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
        }
    }
    return MACRO_NONE;
};
```

左側のキーを押すと、"Hi!" を入力し、右側のキーを押すと "Bye!" を入力します。

### マクロに名前を付ける

キーマップを読みやすくしながらキーマップから参照したいマクロがたくさんある場合は、ファイルの先頭で `#define` を使って名前を付けることができます。

```c
#define M_HI M(0)
#define M_BYE M(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        M_HI, M_BYE
    ),
};
```


## 高度な例:

### 単一キーのコピーと貼り付け

この例は、押された時に `Ctrl-C` を送信し、放される時に `Ctrl-V` を送信するマクロを定義します。

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case 0: {
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(C), U(LCTL), END  );
            } else {
                return MACRO( D(LCTL), T(V), U(LCTL), END  );
            }
            break;
        }
    }
    return MACRO_NONE;
};
```
