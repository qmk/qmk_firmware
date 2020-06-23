# デバウンスアルゴリズム

<!---
  original document: 0.9.19:docs/feature_debounce_type.md
  git diff 0.9.19 HEAD -- docs/feature_debounce_type.md | cat
-->

QMK はデバウンスアルゴリズムを介して複数のデバウンスアルゴリズムをサポートします。

どのデバウンスメソッドが呼ばれるかのロジックは下記のとおりです。rules.mk で設定された様々な定義をチェックします

```
DEBOUNCE_DIR:= $(QUANTUM_DIR)/debounce
DEBOUNCE_TYPE?= sym_g
ifneq ($(strip $(DEBOUNCE_TYPE)), custom)
    QUANTUM_SRC += $(DEBOUNCE_DIR)/$(strip $(DEBOUNCE_TYPE)).c
endif
```

# デバウンスの選択

| DEBOUNCE_TYPE | 説明 | 他に必要なもの |
| -------------    | ---------------------------------------------------  | ----------------------------- |
| 未定義 | デフォルトのアルゴリズム、現在のところ sym_g を使います | 無し |
| custom | 独自のデバウンスコードを使います | ```SRC += debounce.c``` 独自の debounce.c を追加し、必要な関数を実装します |
| anything_else | quantum/debounce/* から他のアルゴリズムを使います | 無し |

**分割キーボードについて**:
デバウンスコードは分割キーボードと互換性があります。

# 独自のデバウンスコードの使用
* ```DEBOUNCE_TYPE = custom``` を設定します。
* ```SRC += debounce.c``` を追加します。
* 独自の ```debounce.c``` を追加します。例については、```quantum/debounce``` にある現在の実装をみてください。
* デバウンスは生のマトリックススキャンごとに発生します。
* MATRIX_ROWS ではなく num_rows を使って、分割キーボードが正しくサポートされるようにします。

# 含まれるデバウンスメソッド間での変更
独自の debounce.c を含むことで独自のコードを使うか、または含まれている他のコードに切り替えることができます。
含まれるデバウンスメソッドは以下の通りです:
* eager_pr - 行ごとにデバウンスします。状態が変化すると、応答は即座に行われ、その後その行にそれ以上入力が無い ```DEBOUNCE``` ミリ秒の間、行をロックします。
For use in keyboards where refreshing ```NUM_KEYS``` 8-bit counters is computationally expensive / low scan rate, and fingers usually only hit one row at a time. これは ErgoDox モデルに適しています; マトリックスは90度回転しているため、その「行」は実際には「列」であり、通常の使用では各指は一度に1つの「行」にしか当たりません。
* eager_pk - キーごとにデバウンスします。状態が変化すると、応答は即座に行われ、その後そのキーにそれ以上入力が無い ```DEBOUNCE``` ミリ秒の間、行をロックします。
* sym_g - キーボードごとにデバウンスします。状態が変化すると、グローバルタイマが設定されます。```DEBOUNCE``` ミリ秒の間何も起きなければ、全ての入力の変更がプッシュされます。
* sym_pk - キーごとにデバウンスします。状態が変化すると、キーごとのタイマーが設定されます。```DEBOUNCE``` ミリ秒の間何も起きなければ、キーの状態の変更がプッシュされます。


