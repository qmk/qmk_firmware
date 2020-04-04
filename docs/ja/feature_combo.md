# コンボ

<!---
  original document: 0.8.94:docs/feature_combo.md
  git diff 0.8.94 HEAD -- docs/feature_combo.md | cat
-->

コンボ機能は、カスタムアクションを追加するためのコード型の解決方法です。同時に複数のキーを押して、異なる効果を生み出すことができます。例えば、タッピング期間内で `A` と `S` を押すと、代わりに `ESC` を押します。あるいはもっと複雑なタスクを実行させることができます。

この機能を有効にするには、`rules.mk` に `COMBO_ENABLE = yes` を追加する必要があります。

さらに、`config.h` で、`#define COMBO_COUNT 1` (1を使っている番号で置き換えます)を追加して、使用するコンボの数を指定する必要があります。
<!-- At this time, this is necessary -->

また、デフォルトでは、コンボのタップ期間は `TAPPING_TERM` と同じ値に設定されます (ほとんどのキーボードではデフォルトで 200)。ただし、`config.h` で定義することにより異なる値を指定することができます。例えば: `#define COMBO_TERM 300` はコンボのためのタイムアウト期間を 300ms に設定します。

次に、`keymap.c` ファイルに、`COMBO_END` で終了するキーのシーケンス、およびキーの組み合わせをリストする構造、その結果のアクションを定義する必要があります。

```c
const uint16_t PROGMEM test_combo[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, KC_ESC)};
```

これは、A と B のキーを押した場合に、"Escape" を送信します。

!> このメソッドは[基本的なキーコード](ja/keycodes_basic.md)のみをサポートします。詳細な制御については例を見てください。

## 例

リストを追加したい場合は、以下のようなものを使います:

```c
enum combos {
  AB_ESC,
  JK_TAB
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB)
};
```

より複雑な実装のために、カスタム処理を追加するために `process_combo_event` 関数を使うことができます。

```c
enum combo_events {
  ZC_COPY,
  XV_PASTE
};

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case ZC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}
```

これは、Z と C を押すと Ctrl+C を送信し、X と V を押すと Ctrl+V を送信します。ただしレイヤーを変更したり音を再生したりあるいは設定を変更したりするようにこれを変更することができます。

## 追加の設定

長いコンボあるいはさらに長いコンボを使っている場合、あなたのしていることを構造が対応するのに十分な大きさで無いかもしれないため、問題が発生するかもしれません。

この場合、`config.h` ファイルに `#define EXTRA_LONG_COMBOS` または `#define EXTRA_EXTRA_LONG_COMBOS` のどちらかを追加することができます。

`COMBO_ALLOW_ACTION_KEYS` を定義することでアクションキーを有効にすることもできます。

## キーコード

その場でコンボ機能を有効、無効および切り替えすることができます。ゲームなどで、一時的にそれらを無効にする必要がある場合に便利です。

| キーコード | 説明 |
|----------|---------------------------------|
| `CMB_ON` | コンボ機能をオンにします |
| `CMB_OFF` | コンボ機能をオフにします |
| `CMB_TOG` | コンボ機能をオンとオフに切り替えます |

## ユーザコールバック

キーコードに加えて、状態を設定または状態をチェックするために使うことができる幾つかの関数があります:

| 関数 | 説明 |
|-----------|--------------------------------------------------------------------|
| `combo_enable()` | コンボ機能を有効にします |
| `combo_disable()` | コンボ機能を無効にし、コンボバッファをクリアします |
| `combo_toggle()` | コンボ機能の状態を切り替えます |
| `is_combo_enabled()` | コンボ機能の状態を返します (true か false) |
