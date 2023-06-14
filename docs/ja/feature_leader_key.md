# リーダーキー: 新しい種類のモディファイア

<!---
  original document: 0.13.24:docs/feature_leader_key.md
  git diff 0.13.24 HEAD -- docs/feature_leader_key.md | cat
-->

もしあなたが Vim を使ったことがある場合、リーダーキーは何であるかを知っています。そうでなければ、素晴らしい概念を発見しようとしています。:) 例えば、Alt+Shift+W を押す(3つのキーを同時に押す)代わりに、キーの_シーケンス_を押すことができたらどうでしょう？つまり、特別なモディファイア (リーダーキー)を押して、続けて W と C を押すと (単純にキーを高速に繋げます)、何かが起こります。

それが `KC_LEAD` の機能です。以下は例です:

1. リーダーキーとして使いたいキーボードのキーを選択します。それにキーコード `KC_LEAD` を割り当てます。このキーはこのためだけの専用です -- 単一アクションのキーで、他の用途には使うことができません。
2. `config.h` に `#define LEADER_TIMEOUT 300` という行を追加します。これによって `KC_LEAD` キーのタイムアウトを設定します。具体的には、`KC_LEAD` キーを押してからリーダーキーのシーケンスを完了するまで一定の時間しかありません。ここでの `300` はそれを300msに設定します。この値を増やして、シーケンスを入力する時間を増やすことができます。ただし、この時間中に押されたキーは全て途中で遮られ、送信されません。そのためこの値は小さくしておいたほうが良いかもしれません。
   * デフォルトでは、このタイムアウトは、`KC_LEAD` を押してからシーケンス全体が完了するまでに掛かる時間です。これは一部の人にとっては非常に短いかもしれません。そのため、このタイムアウトを増やしたほうが良い場合もあります。必要に応じて、`LEADER_PER_KEY_TIMING` オプションを有効にしたほうが良い場合もあります。これは各キーがタップされる度にタイムアウトまでの時間をリセットする機能です。これにより、タイムアウト時間を短くしつつも、比較的長いシーケンスを使うことができます。このオプションを有効にするには、`config.h` に `#define LEADER_PER_KEY_TIMING` を追加します。
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

ご覧のとおり、幾つかの関数があります。`SEQ_ONE_KEY` を単一キーシーケンス (リーダーの後に1つのキーのみ)に使い、より長いシーケンスについては `SEQ_TWO_KEYS`、`SEQ_THREE_KEYS` から `SEQ_FIVE_KEYS` を使うことができます。

これらはそれぞれ1つ以上のキーコードを引数として受け付けます。これは重要な点です: **キーボードの任意のレイヤー**のキーコードを使うことができます。当たり前ですが、リーダーマクロが発動するにはそのレイヤーがアクティブである必要があります

## `rules.mk` にリーダーキーサポートを追加

リーダーキーのサポートを追加するには、単純にキーマップの `rules.mk` に1行を追加します:

```make
LEADER_ENABLE = yes
```

## リーダーキーのキーごとのタイミング

長いリーダーキー文字列のためや 200wpm のタイピングスキルが無い場合に、非常に長いタイムアウト時間に頼るのではなく、キーを押すごとに入力を完了するまでの時間を増やす機能を使用することができます。これは、リーダーキーを使ってタップダンスを再現する場合に非常に役立ちます (C, C, C のような同じキーを複数回タップする場合)。

これを有効にするには、以下を `config.h` に配置します:
```c
#define LEADER_PER_KEY_TIMING
```

この後、`LEADER_TIMEOUT` を 300ms 未満に下げることをお勧めします。

```c
#define LEADER_TIMEOUT 250
```

これで、リーダーキーのタイムアウト時間を 1000ms に設定することなく以下のようなことが可能になると思われます。

```c
SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
  SEND_STRING("Per key timing is great!!!");
}
```

## リーダーキーの無限タイムアウト

リーダーキーが、シーケンスの残りのキーのような快適な場所にない場合があります。リーダーキーが右上の外側のキーの1つである場合、リーダーキーに届くように手の位置を変えなければならないことがあります。
これにより、シーケンスの大部分をすばやく入力できたとしても、シーケンス全体を時間通りに入力するのが難しい場合があります。例えば、シーケンスが `Leader + asd` の場合、手をホーム行に置けば `asd` を素早く打つのは非常に簡単です。しかし、リーダーキーに届くようにホーム行から手を移動し、戻った後、時間内にシーケンスを開始することはできません。
この状況が手に与えるストレスを取り除くために、リーダーキーだけに無限のタイムアウトを有効にすることができます。つまり、リーダーキーを押した後、シーケンスの残りを開始するまでの時間が無限になり、シーケンスの残りを快適に入力するための最適な位置に手を置くことができます。
この無限のタイムアウトはリーダーキーにのみ影響するため、前述の `Leader + asd` の例では、`Leader` と `a` の間に無限の時間があります。ただし、シーケンスを開始すると、(グローバルまたはキーごとに)設定したタイムアウトは正常に機能します。
このようにして、非常に短い `LEADER_TIMEOUT` を設定できますが、それでも手を置く時間は十分にあります。

これを有効にするには、以下を `config.h` に配置します:
```c
#define LEADER_NO_TIMEOUT
```

## 厳密なキー処理

デフォルトでは、リーダーキー機能は、リーダーシーケンスの確認時に [`モッドタップ`](ja/mod_tap.md) および [`レイヤータップ`](ja/feature_layers.md#switching-and-toggling-layers) 機能からのキーコードをフィルターします。つまり、`LT(3, KC_A)` を使っている場合、`LT(3, KC_A)` ではなくシーケンスの `KC_A` として取り出され、新しいユーザにとってより期待される動作を提供します。

ほとんどの場合これで問題ありませんが、シーケンスでキーコード全体(例えば、上の例での `LT(3, KC_A)`) を指定したい場合は、`config.h` ファイルに `#define LEADER_KEY_STRICT_KEY_PROCESSING` を追加することこのような機能を有効にすることができます。これでフィルタリングが無効になり、キーコード全体を指定する必要があります。

## カスタマイズ

リーダーキー機能には、リーダーキー機能の動作にいくらかのカスタマイズを追加する方法があります。リーダーキー機能のプロセスの特定の部分で呼び出すことができる2つの関数、`leader_start()` と `leader_end()` です。

`KC_LEAD` キーがタップされた時に `leader_start()` 関数が呼ばれ、リーダーシーケンスが完了するか、リーダータイムアウトの時間に達した時に `leader_end()` 関数が呼ばれます。

リーダーシーケンスにフィードバック(ビープまたは音楽を再生するなど)を追加するために、これらの関数をコード (通常 は`keymap.c`)に追加することができます。

```c
void leader_start(void) {
  // シーケンスの開始
}

void leader_end(void) {
  // シーケンスの終了 (成功しない/失敗を検知)
}
```

### 例

この例では、リーダーシーケンスを開始するために `KC_LEAD` を押すとマリオの "One Up" 音が再生され、正常に完了した場合は "All Star" が再生され、失敗した場合は "Rick Roll" を再生されます。

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
