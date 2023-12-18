# Word Per Minute (WPM) の計算

<!---
  original document: 0.9.0:docs/feature_wpm.md
  git diff 0.9.0 HEAD -- docs/feature_wpm.md | cat
-->

WPM 機能は、キーストローク間の時間から1分あたりの平均（移動平均）単語数を計算し、様々な用途で利用できるようにします。

`rules.mk` に以下を追加することで WPM システムを有効にします:

    WPM_ENABLE = yes

ソフトシリアルを使っている分割キーボードについては、計算された WPM スコアがマスター側とスレーブ側で利用可能です。

## 公開関数

`uint8_t get_current_wpm(void);`
この関数は符号なし整数で現在の WPM を返します。


## WPM 計算のためのカスタマイズ化されたキー

デフォルトでは、WPM スコアは文字、空白、およびいくつかの句読点のみを含みます。WPM の計算に含むとみなす文字セットを変更したい場合は、`wpm_keycode_user(uint16_t keycode)` を実装し、計算に含めたい文字について true を返し、計算しない特定のキーコードに false を返すようにします。
