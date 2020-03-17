# カスタムマトリックス

QMKは、デフォルトのマトリックススキャンルーチンを独自のコードで補完または置換するメカニズムを提供します。

この機能を使用する理由は次のとおりです:

* キーボードのスイッチとMCUピンの間に追加のハードウェアがある場合
  * I/O マルチプレクサ
  * ラインデコーダー
* 一般的ではないキースイッチマトリクス
  * `COL2ROW` と `ROW2COL` の同時使用

## 前提条件

カスタムマトリックスの実装には、通常、追加のソースファイルのコンパイルが含まれます。
一貫性を保つために、このソースファイルのファイル名は `matrix.c` とすることをお勧めします。

あなたのキーボードディレクトリに新しいファイルを追加します:
```text
keyboards/<keyboard>/matrix.c
```

そして、新しいファイルのコンパイルを指定するため、以下を `rules.mk` に追加します
```make
SRC += matrix.c
```

## マトリクスコードの一部補完

カスタムマトリックスを実装する際、さまざまなスキャン機能のデフォルト実装を提供している定型コードは削減します。

設定するには、以下を `rules.mk` に追加します：
```make
CUSTOM_MATRIX = lite
```

そして、キーボードディレクトリの `matrix.c` ファイルに次の関数を実装します。

```c
void matrix_init_custom(void) {
    // TODO: ここでハードウェアの初期化をする
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: ここで、マトリクススキャンを行なう

    return matrix_has_changed;
}
```


## マトリクスコードの完全置換

スキャンルーチンをさらに変更する必要がある場合は、完全なスキャンルーチンを実装することを選択できます。

設定するには、以下を `rules.mk` に追加します：
```make
CUSTOM_MATRIX = yes
```

そして、キーボードディレクトリの `matrix.c` ファイルに次の関数を実装します。

```c
matrix_row_t matrix_get_row(uint8_t row) {
    // TODO: 要求された行データを返します
}

void matrix_print(void) {
    // TODO: printf() を使って現在のマトリクスの状態をコンソールにダンプします
}

void matrix_init(void) {
    // TODO: ここでハードウェアとグローバルマトリックスの状態を初期化します

    // ハードウェアによるデバウンスがない場合 - 設定されているデバウンスルーチンを初期化します
    debounce_init(MATRIX_ROWS);

    // 正しいキーボード動作のためにこれを呼び出す*必要があります*
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool matrix_has_changed = false;

    // TODO: ここにマトリクススキャンルーチンを追加します

    // ハードウェアによるデバウンスがない場合 - 設定されているデバウンスルーチンを使用します
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    // 正しいキーボード動作のためにこれを呼び出す*必要があります*
    matrix_scan_quantum();

    return matrix_has_changed;
}
```

また、次のコールバックのデフォルトも提供します。

```c
__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}
```
