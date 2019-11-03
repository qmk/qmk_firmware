# 動的マクロ: ランタイム内のマクロの記録および再生

QMKはその場で作られた一時的なマクロをサポートします。これらを動的マクロと呼びます。それらはユーザがキーボードから定義し、キーボードのプラグを抜くか再起動すると失われます。

1つまたは2つのマクロを保存でき、それらは合計128のキーを押すことができます。RAMを代償にしてサイズを増やすことができます。

それらを有効にするには、最初に新しい要素を `keycodes` enum の最後に追加します — `DYNAMIC_MACRO_RANGE`:

```c
enum keycodes {
	QWERTY = SAFE_RANGE,
	COLEMAK,
	DVORAK,
	PLOVER,
	LOWER,
	RAISE,
	BACKLIT,
	EXT_PLV,
	DYNAMIC_MACRO_RANGE,
};
```

`keycodes` enum は僅かに異なる名前を持つかもしれません。`dynamic_macros.h`はその後に幾つかのキーコードをさらに追加するため、`DYNAMIC_MACRO_RANGE` を最後の要素として追加する必要があります。

その下に、`dynamic_macro.h` ヘッダを含めます:

```c
	#include "dynamic_macro.h"`
```

以下のキーをキーマップに追加します:

* `DYN_REC_START1` — マクロ 1 の記録を開始します、
* `DYN_REC_START2` — マクロ 2 の記録を開始します、
* `DYN_MACRO_PLAY1` — マクロ 1 を再生します、
* `DYN_MACRO_PLAY2` — マクロ 2 を再生します、
* `DYN_REC_STOP` — 現在記録されているマクロを終了します。

以下のコードを`process_record_user()` 関数の最初に追加します:

```c
	if (!process_record_dynamic_macro(keycode, record)) {
		return false;
	}
```

それが必要な全てのはずです。マクロの記録を開始するには、`DYN_REC_START1` または `DYN_REC_START2`のどちらかを押します。記録を終了するには、`DYN_REC_STOP` レイヤ ボタンを押します。マクロを再生するには、`DYN_MACRO_PLAY1` あるいは `DYN_MACRO_PLAY2` のどちらかを押します。

マクロの一部としてマクロを再生することができることに注意してください。マクロ 1 を記録中にマクロ 2 を再生することは、その逆もまた同様に問題ありません。ただし、再帰的なマクロ、つまりマクロ 1 を再生するマクロ 1 は作成しないでください。これを行い、キーボードが反応しなくなる場合は、キーボードを取り外し再び接続します。

動的マクロの以前のバージョンのユーザの場合: 専用の`DYN_REC_STOP`キーを使わずに動的マクロ キーへのアクセスに使われるレイヤ修飾子のみを使ってマクロの記録を終了することも可能です。この動作に戻したい場合は、上のコードの代わりに以下のコードを使ってください:

```c
	uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);

	if (!process_record_dynamic_macro(macro_kc, record)) {
		return false;
	}
```

記録中にキーを押すたびにLEDが点滅し始める場合は、マクロバッファにマクロ用の空間がもう無いことを意味します。マクロを収めるには、他のマクロを短くする(それらは同じバッファを共有します)か、`DYNAMIC_MACRO_SIZE` プリプロセッサ マクロ (デフォルト値:  128; ヘッダ内のコメントを読んでください) を設定することでバッファサイズを増やします。

動的マクロの内部の詳細については、`dynamic_macro.h` ヘッダ内のコメントを読んでください。
