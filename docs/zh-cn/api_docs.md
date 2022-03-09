# QMK API

<!---
  original document: 0.15.12:docs/api_docs.md
  git diff 0.15.12 HEAD -- docs/api_docs.md | cat
-->

本章节详述了QMK API的使用方法，若您是应用开发者，使用这套API可以实现[QMK](https://qmk.fm)键盘固件的编译支持。

## 总览

本服务提供了一套用于编译自定义键映射的异步API，通过POST方式发送JSON参数到API，定期检查执行状态，待固件编译完成后，即可下载生成的固件文件和固件的源文件（如果需要的话）。

#### 荷载JSON参数示例：

```json
{
  "keyboard": "clueboard/66/rev2",
  "keymap": "my_awesome_keymap",
  "layout": "LAYOUT_all",
  "layers": [
    ["KC_GRV","KC_1","KC_2","KC_3","KC_4","KC_5","KC_6","KC_7","KC_8","KC_9","KC_0","KC_MINS","KC_EQL","KC_GRV","KC_BSPC","KC_PGUP","KC_TAB","KC_Q","KC_W","KC_E","KC_R","KC_T","KC_Y","KC_U","KC_I","KC_O","KC_P","KC_LBRC","KC_RBRC","KC_BSLS","KC_PGDN","KC_CAPS","KC_A","KC_S","KC_D","KC_F","KC_G","KC_H","KC_J","KC_K","KC_L","KC_SCLN","KC_QUOT","KC_NUHS","KC_ENT","KC_LSFT","KC_NUBS","KC_Z","KC_X","KC_C","KC_V","KC_B","KC_N","KC_M","KC_COMM","KC_DOT","KC_SLSH","KC_RO","KC_RSFT","KC_UP","KC_LCTL","KC_LGUI","KC_LALT","KC_MHEN","KC_SPC","KC_SPC","KC_HENK","KC_RALT","KC_RCTL","MO(1)","KC_LEFT","KC_DOWN","KC_RIGHT"],
    ["KC_ESC","KC_F1","KC_F2","KC_F3","KC_F4","KC_F5","KC_F6","KC_F7","KC_F8","KC_F9","KC_F10","KC_F11","KC_F12","KC_TRNS","KC_DEL","BL_STEP","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","_______","KC_TRNS","KC_PSCR","KC_SLCK","KC_PAUS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(2)","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_PGUP","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(1)","KC_LEFT","KC_PGDN","KC_RGHT"],
    ["KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","RESET","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(2)","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(1)","KC_TRNS","KC_TRNS","KC_TRNS"]
  ]
}
```

如上可见，荷载参数里有用于生成固件文件的所有键盘信息。每一个层定义都包含了与键盘 `LAYOUT` 宏定义一致的QMK键码列表数据，若该键盘有多个支持的 `LAYOUT` 宏定义，也可以指定使用的是哪一个。

## 提交一个编译job

若要将键映射配置编译成固件文件，仅需将JSON参数通过POST发送至 `/v1/compile` 节点。下面的示例中我们假设JSON荷载参数已存放在 `json_data` 文件中。

```
$ curl -H "Content-Type: application/json" -X POST -d "$(< json_data)" https://api.qmk.fm/v1/compile
{
  "enqueued": true,
  "job_id": "ea1514b3-bdfc-4a7b-9b5c-08752684f7f6"
}
```

## 检查状态

键映射配置提交后，可以简单地通过 HTTP GET 请求来查询job状态：

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

这份信息告诉我们编译job已经提交到队列中且正在执行。job的状态有5种：

* **failed（失败）**: 编译服务出现问题。
* **finished（完成）**: 编译已完成，`result` 字段中保存了编译结果。
* **queued（排队中）**: 键映射job在等待可用的编译服务器。
* **running（执行中）**: 编译进行中，应当很快就会结束。
* **unknown（未知）**: 出现了较严重的错误，请给我们[提交一个bug](https://github.com/qmk/qmk_compiler/issues).

## 确认编译产出

编译job完成后请查看 `result` 字段，该字段下保存了如下信息项的哈希表数据：

* `firmware_binary_url`: 用于刷写的固件文件URL列表
* `firmware_keymap_url`: `keymap.c` 文件URL列表
* `firmware_source_url`: 完整的固件源代码URL列表
* `output`: 编译job的stdout及stderr输出信息，所有错误信息都会在这里。
