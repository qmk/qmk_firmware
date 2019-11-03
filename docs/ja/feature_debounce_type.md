# デバウンス アルゴリズム

QMKはデバウンス アルゴリズムを通じて複数のデバウンス アルゴリズムをサポートします。

どのデバウンス メソッドが呼ばれるかのロジックは下記のとおりです。rules.mkで設定された様々な定義をチェックします

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
| 未定義 | デフォルトのアルゴリズム、現在のところ sym_gを使います | 無し |
| custom | 独自のdebounce.cを使います | ```SRC += debounce.c``` 独自のdebounce.cを追加し、必要な関数を実装します |
| anything_else | quantum/debounce/* から他のアルゴリズムを使います | 無し |

**Regarding split keyboards**:
デバウンス コードは分割キーボードと互換性があります。

# 独自のデバウンス コードを使います
* ```DEBOUNCE_TYPE = custom ```を設定します。
* Add ```SRC += debounce.c```
* 独自の```debounce.c```を追加します。例については、```quantum/debounce``` にある現在の実装をみてください。
* デバウンスは生のマトリックス スキャンごとに発生します。
* MATRIX_ROWSではなくnum_rowsを使って、分割キーボードが正しくサポートされるようにします。

# 含まれるデバウンス メソッド間での変更
独自のdebounce.cを含むことで、独自のコードを使うかあるいは含まれている他のコードに切り替えることができます。
含まれるデバウンス メソッドは以下の通りです:
* eager_pr - 行ごとにデバウンスします。状態が変化すると、応答は即座に行われ、その後その行にそれ以上入力が無いという```DEBOUNCE_DELAY```ミリ秒行をロックします。
For use in keyboards where refreshing ```NUM_KEYS``` 8-bit counters is computationally expensive / low scan rate, and fingers usually only hit one row at a time. This could be
appropriate for the ErgoDox models; the matrix is rotated 90°, and hence its "rows" are really columns, and each finger only hits a single "row" at a time in normal use.
* eager_pk - キーごとにデバウンスします。状態が変化すると、応答は即座に行われ、その後そのキーにそれ以上入力が無いという```DEBOUNCE_DELAY```ミリ秒行をロックします。
* sym_g - キーボードごとにデバウンスします。状態が変化すると、グローバルタイマが設定されます。```DEBOUNCE_DELAY``` ミリ秒の間何も起きなければ、全ての入力の変更がプッシュされます。


