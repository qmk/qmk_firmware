# リーダーキー: 新しい種類のモディファイア

<!---
  original document: 0.8.134:docs/feature_leader_key.md
  git diff 0.8.134 HEAD -- docs/feature_leader_key.md | cat
-->

もしあなたが Vim を使ったことがある場合、リーダーキーは何であるかを知っています。そうでなければ、素晴らしい概念を発見しようとしています。:) 例えば、Alt+Shift+W を押す(3つのキーを同時に押す)代わりに、キーの_シーケンス_を押すとどうなりますか？つまり、特別なモディファイア (リーダーキー)を押して、続けて W と C を押します (単純にキーを高速に繋げます)。そして何かが起こります。

それが `KC_LEAD` の機能です。以下は例です:

1. リーダーキーとして使いたいキーボードのキーを選択します。それをキーコード `KC_LEAD` に割り当てます。このキーはこのためだけの専用です -- 単一のアクションキーで、他には使うことができません。
2. `config.h` 内に `#define LEADER_TIMEOUT 300` の行を含めます。これは `KC_LEAD` キーのタイムアウトを設定します。具体的には、`KC_LEAD` キーを押した場合、リーダーキーのシーケンスを完了するためには一定の時間しかありません。ここでの `300` はそれを300msに設定します。この値を増やして、シーケンスがヒットする時間を増やすことができます。ただし、このタイムアウト中に押された全てのキーは全て途中で捉えられ、送信されません。そのためこの値を小さくしておきたいかもしれません。.
   * デフォルトでは、このタイムアウトは、`KC_LEAD` を押した後にシーケンス全体が完了するまでどれだけ掛かるかの時間です。これは一部の人にとっては非常に低いかもしれません。そのため、このタイムアウトを増やしたほうが良いかもしれません。オプションで、`LEADER_PER_KEY_TIMING` オプションを有効にしたほうが良いかもしれません。これは各キーがタップされた後でタイムアウトを再設定します。これにより、ここでは低い値を設定しておき、より長いシーケンスを使うことができます。このオプションを有効にするには、`config.h` に `#define LEADER_PER_KEY_TIMING` を追加します。
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
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
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

ご覧のとおり、幾つかの機能があります。`SEQ_ONE_KEY` を単一キーシーケンス (リーダーの後に1つのキーのみ)に使い、より長いシーケンスについては `SEQ_TWO_KEYS`、`SEQ_THREE_KEYS` から `SEQ_FIVE_KEYS` を使うことができます。

これらはそれぞれ1つ以上のキーコードを引数として受け付けます。これは重要な点です: **キーボードの任意のレイヤー**からキーコードを使うことができます。リーダーマクロが発火するには、明らかにそのレイヤーがアクティブである必要があります。

## `rules.mk` にリーダーキーサポートを追加

リーダーキーのサポートを追加するには、単純にキーマップの `rules.mk` に1行を追加します:

```make
LEADER_ENABLE = yes
```

## リーダーキーのキーごとのタイミング

信じられないほど長いリーダーキー文字列についての高いタイムアウトや、200wpm のタイピングスキルの無い私たちに依存するのではなく、押された各キーがストロークを完了するのにより多くの時間を提供できるようにするために各キーごとにタイミングを有効にすることができます。これは、タップダンスのリーダーキーエミュレーションで非常に役立ちます (C, C, C のような同じキーの複数のタップ)。

これを有効にするには、以下を `config.h` に配置します:
```c
#define LEADER_PER_KEY_TIMING
```

この後、`LEADER_TIMEOUT` を300ms未満に下げることをお勧めします。

```c
#define LEADER_TIMEOUT 250
```

これで、1000ms のリーダーキータイムアウト無しに行うことが可能に思われます。

```c
SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
  SEND_STRING("Per key timing is great!!!");
}
```

## 厳密なキー処理

デフォルトでは、リーダーキー機能は、リーダーシーケンスの確認時に [`モッドタップ`](mod_tap.md) および [`レイヤータップ`](feature_layers.md#switching-and-toggling-layers) 機能からのキーコードをフィルターします。つまり、`LT(3, KC_A)` を使っている場合、シーケンスの `KC_A` として取り出され、`LT(3, KC_A)` ではなく、新しいユーザにとってより期待される動作を提供します。

ほとんどの場合これで問題ありませんが、シーケンスでキーコード全体(例えば、上の例での `LT(3, KC_A)`) を指定したい場合は、`config.h` ファイルに `#define LEADER_KEY_STRICT_KEY_PROCESSING` を追加することで行えます。これでフィルタリングが無効になり、キーコード全体を指定する必要があります。

## カスタマイズ

リーダーキー機能には、リーダーキー機能の動作にいくらかのカスタマイズを追加する方法があります。プロセスの特定の部分で呼び出すことができる2つの関数があります。つまり、`leader_start()` と `leader_end()` です。

`KC_LEAD` キーがタップされた時に `leader_start()` 関数が呼ばれ、リーダーシーケンスが完了するか、リーダータイムアウトがヒットした時に `leader_end()` 関数が呼ばれます。

リーダーシーケンスにフィードバックを追加するために、これらの関数をコード (通常 は`keymap.c`)に追加することができます (ビープまたは音楽を再生するなど)。

```c
void leader_start(void) {
  // シーケンスの開始
}

void leader_end(void) {
  // シーケンスの終了 (成功/失敗の検知無し)
}
```

### 例

この例では、リーダーシーケンスを開始するために `KC_LEAD` を押すとマリオの "One Up" 音が再生され、正常に完了した場合は "All Star" を再生され、失敗した場合は "Rick Roll" を再生します。

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
      SEND_STRING(SS_LCTL(SS_LSFT("t")));
      did_leader_succeed = true;
    } else
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
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
