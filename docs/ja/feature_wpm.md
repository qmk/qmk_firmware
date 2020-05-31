# Word Per Minute (WPM) の計算

<!---
  original document: 0.9.0:docs/feature_wpm.md
  git diff 0.9.0 HEAD -- docs/feature_wpm.md | cat
-->

WPM 機能は1分あたりの平均単語数を計算するためにキーストローク間の時間を使い、様々な目的のためにこれを利用可能にします。

`rules.mk` に以下を追加することで WPM システムを有効にします:

    WPM_ENABLE = yes

ソフトシリアルを使っている分割キーボードについては、計算された WPM スコアがマスター側とスレーブ側で利用可能です。

## Public 関数

`uint8_t get_current_wpm(void);`
この関数は unsigned integer として現在の WPM を返します。


## WPM 計算のためのカスタマイズ化されたキー

デフォルトでは、WPM スコアは単語、文字、空白、幾つかの句読点のみを含みます。WPM の計算の部分として見なされる文字のセットを変更したい場合は、`wpm_keycode_user(uint16_t keycode)` を実装し、計算に含めたい文字について true を返し、カウントしない特定のキーコードに false を返すようにします。
