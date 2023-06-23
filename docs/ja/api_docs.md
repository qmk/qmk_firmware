# QMK API

<!---
  original document: 0.13.15:docs/api_docs.md
  git diff 0.13.15 HEAD -- docs/api_docs.md | cat
-->

このページは QMK API の使い方を説明します。もしあなたがアプリケーション開発者であれば、全ての [QMK](https://qmk.fm) キーボードのファームウェアをコンパイルするために、この API を使うことができます。

## 概要

このサービスは、カスタムキーマップをコンパイルするための非同期 API です。API に 何らかの JSON を POST し、定期的に状態をチェックし、ファームウェアのコンパイルが完了していれば、結果のファームウェアと(もし希望すれば)そのファームウェアのソースコードをダウンロードすることができます。

#### JSON ペイロードの例:

```json
{
  "keyboard": "clueboard/66/rev2",
  "keymap": "my_awesome_keymap",
  "layout": "LAYOUT_all",
  "layers": [
    ["KC_GRV","KC_1","KC_2","KC_3","KC_4","KC_5","KC_6","KC_7","KC_8","KC_9","KC_0","KC_MINS","KC_EQL","KC_GRV","KC_BSPC","KC_PGUP","KC_TAB","KC_Q","KC_W","KC_E","KC_R","KC_T","KC_Y","KC_U","KC_I","KC_O","KC_P","KC_LBRC","KC_RBRC","KC_BSLS","KC_PGDN","KC_CAPS","KC_A","KC_S","KC_D","KC_F","KC_G","KC_H","KC_J","KC_K","KC_L","KC_SCLN","KC_QUOT","KC_NUHS","KC_ENT","KC_LSFT","KC_NUBS","KC_Z","KC_X","KC_C","KC_V","KC_B","KC_N","KC_M","KC_COMM","KC_DOT","KC_SLSH","KC_RO","KC_RSFT","KC_UP","KC_LCTL","KC_LGUI","KC_LALT","KC_MHEN","KC_SPC","KC_SPC","KC_HENK","KC_RALT","KC_RCTL","MO(1)","KC_LEFT","KC_DOWN","KC_RIGHT"],
    ["KC_ESC","KC_F1","KC_F2","KC_F3","KC_F4","KC_F5","KC_F6","KC_F7","KC_F8","KC_F9","KC_F10","KC_F11","KC_F12","KC_TRNS","KC_DEL","BL_STEP","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","_______","KC_TRNS","KC_PSCR","KC_SCRL","KC_PAUS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(2)","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_PGUP","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(1)","KC_LEFT","KC_PGDN","KC_RGHT"],
    ["KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","QK_BOOT","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(2)","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(1)","KC_TRNS","KC_TRNS","KC_TRNS"]
  ]
}
```

ご覧のとおり、ペイロードにはファームウェアを作成および生成するために必要なキーボードの全ての側面を記述します。各レイヤーは QMK キーコードの1つのリストで、キーボードの `LAYOUT` マクロと同じ長さです。もしキーボードが複数の `LAYOUT` マクロをサポートする場合、どのマクロを使うかを指定することができます。

## コンパイルジョブのサブミット

キーマップをファームウェアにコンパイルするには、単純に JSON を `/v1/compile` エンドポイントに POST します。以下の例では、JSON ペイロードを `json_data` という名前のファイルに配置しています。

```
$ curl -H "Content-Type: application/json" -X POST -d "$(< json_data)" https://api.qmk.fm/v1/compile
{
  "enqueued": true,
  "job_id": "ea1514b3-bdfc-4a7b-9b5c-08752684f7f6"
}
```

## 状態のチェック

キーマップをサブミットした後で、簡単な HTTP GET 呼び出しを使って状態をチェックすることができます:

```
$ curl https://api.qmk.fm/v1/compile/ea1514b3-bdfc-4a7b-9b5c-08752684f7f6
{
  "created_at": "Sat, 19 Aug 2017 21:39:12 GMT",
  "enqueued_at": "Sat, 19 Aug 2017 21:39:12 GMT",
  "id": "f5f9b992-73b4-479b-8236-df1deb37c163",
  "status": "running",
  "result": null
}
```

これは、ジョブをキューに入れることに成功し、現在実行中であることを示しています。5つの状態がありえます:

* **failed**: なんらかの理由でコンパイルサービスが失敗しました。
* **finished**: コンパイルが完了し、結果を見るには `result` をチェックする必要があります。
* **queued**: キーマップはコンパイルサーバが利用可能になるのを待っています。
* **running**: コンパイルが進行中で、まもなく完了するはずです。
* **unknown**: 深刻なエラーが発生し、[バグを報告](https://github.com/qmk/qmk_compiler/issues)する必要があります。

## 完了した結果を検証

コンパイルジョブが完了したら、`result` キーをチェックします。このキーの値は幾つかの情報を含むハッシュです:

* `firmware_binary_url`: 書き込み可能なファームウェアの URL のリスト
* `firmware_keymap_url`: `keymap.c` の URL のリスト
* `firmware_source_url`: ファームウェアの完全なソースコードの URL のリスト
* `output`: このコンパイルジョブの stdout と stderr。エラーはここで見つけることができます。
