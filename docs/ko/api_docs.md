# QMK API

이 페이지에서는 QMK API를 사용하는 것을 설명합니다. 어플리케이션 개발자라면 이 API를 사용하여 어떠한 [QMK](https://qmk.fm) 키보드에 펌웨어를 컴파일 할 수 있을 것입니다.

## 개요

이 서비스는 사용자 정의 키맵을 컴파일하기 위한 비동기 API 입니다. 일부 JSON을 API에 진단 테스트(POST)를 하고, 주기적으로 상태를 확인하고, 펌웨어의 컴파일링이 완료되면 결과로 얻는 펌웨어와 (원한다면) 해당 펌웨어의 소스코드를 다운로드 할 수 있을 것입니다.

#### JSON 페이로드 예제:

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

보이는 것과 같이 페이로드는 만들기 위한 키보드의 모든 필요한 측면과 펌웨어를 생성하는 것을 나타내고 있습니다. 각 레이어는 키보드의 `LAYOUT` 매크로와 같은 길이의 QMK 키코드 단일 목록 입니다. 키보드가 만약 여러개의 `LAYOUT` 매크로를 지원하는 경우 어떤 매크로를 사용할지 특정할 수 있습니다.

## 컴파일 작업 제출

키맵을 펌웨어로 컴파일하기 위해 간단히 JSON 파일을 `/v1/compile` 끝부분에서 진단 테스트를 합니다. 따라오는 예제에서 우리는 JSON 페이로드를 `json_data` 이라는 파일에 배치했습니다.

```
$ curl -H "Content-Type: application/json" -X POST -d "$(< json_data)" https://api.qmk.fm/v1/compile
{
  "enqueued": true,
  "job_id": "ea1514b3-bdfc-4a7b-9b5c-08752684f7f6"
}
```

## 상태 확인

키맵을 제출하고 난 이후에는 간단한 HTTP GET을 불러 상태를 확인할 수 있습니다:

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

이것은 작업이 대기열을 통과하였고 현재 실행 중임을 보여줍니다. 5가지의 가능한 상태들이 있습니다:

* **failed**: 컴파일링 서비스에 관한 무언가가 망가짐.
* **finished**: 컴파일 작업이 완료되었고 `result`를 확인하여 결과 확인을 해야함.
* **queued**: 키맵이 컴파일 서버가 가능한 상태가 되기까지 대기중.
* **running**: 컴파일 작업이 진행중이고 곧 완료되어야 함.
* **unknown**: 심각한 오류가 발생하여 [버그 신고](https://github.com/qmk/qmk_compiler/issues).

## 완료된 결과 검토

일단 컴파일 작업이 완료되면 `result`키를 확인할 것입니다. 이 키의 값은 정보의 여러 키 비트를 포함하는 해시입니다:

* `firmware_binary_url`: 펌웨어 플래시가 가능한 URL 목록
* `firmware_keymap_url`: `keymap.c`의 URL 목록
* `firmware_source_url`: 전체 펌웨어 소스코드의 URL 목록
* `output`: 이 컴파일 작업의 stdout과 stderr. 오류는 여기서 찾을 수 있을 것입니다.
