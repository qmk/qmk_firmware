# リーダー キー: 新しい種類の修飾子

Vimを使ったことがある場合、リーダー キーとは何かを知っています。そうでなければ、素晴らしい概念を発見しようとしています。:) 例えば、Alt+Shift+W を押す(3つのキーを同時に押す)代わりに、キーの_シーケンス_を押すとどうなりますか？つまり、特別な修飾子 (リーダー キー)を押して、続けてWとCを押します (単なるキーの高速な連続)。そして何かが起こります。

それが`KC_LEAD`の機能です。以下は例です:

1. リーダー キーとして使いたいキーボードのキーを選択します。それをキーコード `KC_LEAD` に割り当てます。このキーはこれのための専用です -- 単一のアクションキーで、他には使うことができません。
2. `config.h`に`#define LEADER_TIMEOUT 300`の行を含めます。これは `KC_LEAD` キーのタイムアウトを設定します。具体的には、`KC_LEAD` キーを押した場合、リーダー キーのシーケンスを完了するためには一定の時間しかありません。ここでの`300`はそれを300msに設定します。この値を増やして、シーケンスがヒットする時間を増やすことができます。ただし、このタイムアウト中に押された全てのキーは全て途中で捉えられ、送信されません。そのためこの値を小さくしておきたいかもしれません。.
   * デフォルトでは、このタイムアウトは、`KC_LEAD`を押した後にシーケンス全体が完了するまでどれだけ掛かるかの時間です。これは一部の人にとっては非常に低いかもしれません。そのため、このタイムアウトを増やしたいかもしれません。オプションで、`LEADER_PER_KEY_TIMING` オプションを有効にしたいかもしれません。これは各キーがタップされた後でタイムアウトを再設定します。これにより、ここでは低い値を設定しておき、より長いシーケンスを使うことができます。このオプションを有効にするには、`config.h`に`#define LEADER_PER_KEY_TIMING`を追加します。
3. `matrix_scan_user` 関数の中で、以下のようなものを追加します:

```c
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // マクロ内でできること
      SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTRL("a")SS_LCTRL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com"SS_TAP(X_ENTER));
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
```

ご覧のとおり、幾つかの機能があります。`SEQ_ONE_KEY`を単一キー シーケンス (リーダーの後に1つのキーのみ)に使い、より長いシーケンスについては`SEQ_TWO_KEYS`, `SEQ_THREE_KEYS`から`SEQ_FIVE_KEYS`を使うことができます。

これらはそれぞれ1つ以上のキーコードを引数として受け付けます。これは重要な点です: **キーボードの任意のレイヤ**.からキーコードを使うことができます。明らかにリーダーマクロが発火するには、そのレイヤがアクティブである必要があります。

## `rules.mk`にリーダーキーサポートを追加

リーダーキーのサポートを追加するには、単純にキーマップの`rules.mk`に1行を追加します:

```make
LEADER_ENABLE = yes
```

## リーダーキーのキーごとのタイミング

Rather than relying on an incredibly high timeout for long leader key strings or those of us without 200wpm typing skills, we can enable per key timing to ensure that each key pressed provides us with more time to finish our stroke. これは、タップダンスのリーダーキーエミュレーションで非常に役立ちます (C, C, C のような同じキーの複数のタップ)。

これを有効にするには、以下を`config.h`に配置します:
```c
#define LEADER_PER_KEY_TIMING
```

この後、`LEADER_TIMEOUT`を300ms未満に下げることをお勧めします。

```c
#define LEADER_TIMEOUT 250
```

Now, something like this won't seem impossible to do without a 1000MS leader key timeout:

```c
SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
  SEND_STRING("Per key timing is great!!!");
}
```

## 厳密なキー処理

By default, the Leader Key feature will filter the keycode out of [`Mod-Tap`](feature_advanced_keycodes.md#mod-tap) and [`Layer Tap`](feature_advanced_keycodes.md#switching-and-toggling-layers) functions when checking for the Leader sequences. That means if you're using `LT(3, KC_A)`, it will pick this up as `KC_A` for the sequence, rather than `LT(3, KC_A)`, giving a more expected behavior for newer users.

While, this may be fine for most, if you want to specify the whole keycode (eg, `LT(3, KC_A)` from the example above) in the sequence, you can enable this by added `#define LEADER_KEY_STRICT_KEY_PROCESSING` to your `config.h` file.  This well then disable the filtering, and you'll need to specify the whole keycode.

## カスタム化

The Leader Key feature has some additional customization to how the Leader Key feature works.  プロセスの特定の部分で呼び出すことができる2つの関数があります。つまり、`leader_start()` と `leader_end()` です。

`KC_LEAD`キーがタップされた時に`leader_start()`関数が呼ばれ、リーダー シーケンスが完了するか、リーダー タイムアウトがヒットした時に`leader_end()`関数が呼ばれます。

リーダー シーケンスにフィードバックを追加するために、これらの関数をコード (通常は`keymap.c`)に追加することができます (ビープまたは音楽を再生するなど)。

```c
void leader_start(void) {
  // シーケンスの開始
}

void leader_end(void) {
  // シーケンスの終了 (成功/失敗の検知無し)
}
```

### 例

この例では、リーダーシーケンスを開始するために`KC_LEAD`を押すとマリオの"One Up"音が再生され、正常に完了した場合は"All Star"を再生され、失敗した場合は"Rick Roll"を再生します。

```c
bool did_leader_succeed;
#ifdef AUDIO_ENABLE
float leader_start[][2] = SONG(ONE_UP_SOUND );
float leader_succeed[][2] = SONG(ALL_STAR);
float leader_fail[][2] = SONG(RICK_ROLL);
#endif
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    SEQ_ONE_KEY(KC_E) {
      // マクロ内でできること
      SEND_STRING(SS_LCTRL(SS_LSFT("t")));
      did_leader_succeed = true;
    } else
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(SS_LGUI("r")"cmd"SS_TAP(KC_ENTER)SS_LCTRL("c"));
      did_leader_succeed = true;
    }
    leader_end();
  }
}

void leader_start(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start);
#endif
}

void leader_end(void) {
  if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_succeed);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_fail);
#endif
  }
}
```
