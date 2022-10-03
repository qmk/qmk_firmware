# QMK Configurator에서 키보드 지원

이 페이지에서는 [QMK Configurator](https://config.qmk.fm/)에서 올바르게 키보드를 지원하는 방법을 다룹니다.


## 어떻게 Configurator가 키보드를 이해하고 있을까

Configurator가 키보드를 이해하는 방법을 알기 위해서, 먼저 레이아웃 메크로를 반드시 이해해야 합니다. 다음의 연습에서, 우리는 `numpad`로 부를, 17-key 숫자키패드 PCB를 상상할 것입니다. 

```
|---------------|
|NLk| / | * | - |
|---+---+---+---|
|7  |8  |9  | + |
|---+---+---|   |
|4  |5  |6  |   |
|---+---+---+---|
|1  |2  |3  |Ent|
|-------+---|   |
|0      | . |   |
|---------------|
```

?> 레이아웃 매크로에 대해 더 알고 싶으시면, [QMK 이해하기: Matrix Scanning](ko/understanding_qmk.md?id=matrix-scanning)과 [QMK 이해하기: Matrix to Physical Layout Map](ko/understanding_qmk.md?id=matrix-to-physical-layout-map)를 보세요.

Configurator의 API는 키보드의 `.h` 파일을 `qmk_firmware/keyboards/<keyboard>/<keyboard>.h` 에서 읽습니다. 우리의 키패드는,`qmk_firmware/keyboards/numpad/numpad.h`에 파일이 있을겁니다:

```c
#pragma once

#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22,      \
    k30, k31, k32, k33, \
    k40,      k42       \
  ) { \
    { k00, k01,   k02, k03   }, \
    { k10, k11,   k12, k13   }, \
    { k20, k21,   k22, KC_NO }, \
    { k30, k31,   k32, k33   }, \
    { k40, KC_NO, k42, KC_NO }  \
}
```

QMK는 스위치가 없는 스위치 행렬의 위치를 지정하기 위해 `KC_NO` 를 사용합니다. 가끔은, 디버그가 필요한 경우 `XXX`, `___` 또는 `____` 으로 사용하는 데, 이러한 부분을 더 쉽게 읽을 수 있도록 약어로 사용합니다. 이는 보통은 `.h` 파일의 시작 부분 근처에서 정의합니다.

```c
#pragma once

#define XXX KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22,      \
    k30, k31, k32, k33, \
    k40,      k42       \
  ) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, XXX }, \
    { k30, k31, k32, k33 }, \
    { k40, XXX, k42, XXX }  \
}
```

!> 이러한 사용법은, 거의 항상 `KC_NO` 에 `XXXXXXX` (7개의 대문자 X)를 사용하고 `KC_TRNS` 에 `_______` (7개의 밑줄)을 사용하는 키맵 매크로와는 다릅니다.

!> 사용자의 혼란을 방지하기 위해, `KC_NO` 의 사용이 선호됩니다. 

이 레이아웃 매크로는 Configurator에게 키보드가 17키가 있고, 5개의 행과 4개의 열로 배치되어 있다고 말해줍니다. 스위치 위치는 `k<행><열>` 으로, 0부터 시작하여 나타냅니다. 이름 그 자체는 사실 중요하진 않지만, 키맵에서 키코드를 수신하는 상단 섹션과 행렬에서 각 키의 위치를 지정하는 하단 섹션 사이가 서로 일치해야 합니다.

물리적 키보드의 형태로 보여주기 위해서, 키의 물리적 위치와 크기를 스위치 행렬에 연결하는 방법을 Configurator에 알려주는 JSON 파일을 빌드할 필요가 있습니다.

## JSON 파일 빌드하기

JSON 파일을 빌드하는 가장 쉬운 방법은 레이아웃을 [키보드 레이아웃 에디터](www.keyboard-layout-editor.com/) ("KLE")에서 빌드하고, 이 Raw Data를 QMK 도구에 제공하여 KLE의 데이터를 Configurator가 읽고 사용하도록 JSON으로 변환하는 것입니다. KLE는 기본적으로 숫자패드 레이아웃으로 열리므로, 단지 Getting Started 지시사항을 삭제하고, 남은 것을 사용하면 됩니다. 

원하는 레이아웃이 되면, KLE의 Raw Data 탭으로 이동하고, 내용을 복사하세요:

```
["Num Lock","/","*","-"],
["7\nHome","8\n↑","9\nPgUp",{h:2},"+"],
["4\n←","5","6\n→"],
["1\nEnd","2\n↓","3\nPgDn",{h:2},"Enter"],
[{w:2},"0\nIns",".\nDel"]
```

이 데이터를 우리의 JSON으로 변환하기 위해, [QMK KLE-JSON Converter](https://qmk.fm/converter/)으로 이동하여, Raw Data를 Input에 붙이고, Convert 버튼을 클릭하세요. 잠시 후에, JSON 데이터가 Output field에 나타날 것입니다. 내용을 새 텍스트 문서에 복사를 하여, 문서의 이름을 `info.json`으로 하고, `numpad.h`가 포함된 같은 폴더에 저장하세요.

`keyboard_name` 개체를 사용해서 키보드의 이름을 설정하세요. 설명을 위해, 각 키의 개체를 자체 줄에 넣을 것입니다. 이는 파일을 더 인간이 쉽게 읽도록 만들기 위함으로, Configurator의 기능에는 영향을 끼치지 않습니다.

```json
{
    "keyboard_name": "Numpad",
    "url": "",
    "maintainer": "qmk",
    "tags": {
        "form_factor": "numpad"
    },
    "layouts": {
        "LAYOUT": {
            "layout": [
                {"label":"Num Lock", "x":0, "y":0},
                {"label":"/", "x":1, "y":0},
                {"label":"*", "x":2, "y":0},
                {"label":"-", "x":3, "y":0},
                {"label":"7", "x":0, "y":1},
                {"label":"8", "x":1, "y":1},
                {"label":"9", "x":2, "y":1},
                {"label":"+", "x":3, "y":1, "h":2},
                {"label":"4", "x":0, "y":2},
                {"label":"5", "x":1, "y":2},
                {"label":"6", "x":2, "y":2},
                {"label":"1", "x":0, "y":3},
                {"label":"2", "x":1, "y":3},
                {"label":"3", "x":2, "y":3},
                {"label":"Enter", "x":3, "y":3, "h":2},
                {"label":"0", "x":0, "y":4, "w":2},
                {"label":".", "x":2, "y":4}
            ]
        }
    }
}
```

`layouts` 객체는 키보드의 물리적인 레이아웃을 제시하는 데이터를 담고 있습니다. `LAYOUT` 객체를 가지는 것은, `numpad.h`에서 오는 레이아웃 매크로의 이름을 맞추는 데 필요합니다. `LAYOUT` 객체는 스스로 `layout`이라는 이름으로 객체를 가지는데, 이는 키보드의 각 물리적인 키의 JSON 객체를 담고 있습니다. 다음의 포맷을 따릅니다:

```
  The name of the key. Not displayed in the Configurator.
  |
  |                   The key's X-axis location, in key units from the
  |                   | keyboard's left edge.
  |                   |
  |                   |      The key's Y-axis location, in key units from
  |                   |      | the keyboard's top (rear-facing) edge.
  ↓                   ↓      ↓
{"label":"Num Lock", "x":0, "y":0},
```

또한 일부 객체는 `"w"`와 `"h"` 키를 가질 것인데, 이는 각각 키의 너비와 높이를 제시합니다.

?> `info.json` 파일에 대한 더 많은 정보는, [`info.json` Format](reference_info_json.md)을 보세요.


## Configurator가 키를 프로그램하는 방법

Configurator의 API는 레이아웃 매크로와 제공한 JSON 파일을 사용하여, 순차적으로 각 특정키에 연결되는, 시각적 개체가 있는 키보드의 시각적 표현을 생성합니다:

key in layout macro | JSON object used
:---: | :----
k00   | {"label":"Num Lock", "x":0, "y":0}
k01   | {"label":"/", "x":1, "y":0}
k02   | {"label":"*", "x":2, "y":0}
k03   | {"label":"-", "x":3, "y":0}
k10   | {"label":"7", "x":0, "y":1}
k11   | {"label":"8", "x":1, "y":1}
k12   | {"label":"9", "x":2, "y":1}
k13   | {"label":"+", "x":3, "y":1, "h":2}
k20   | {"label":"4", "x":0, "y":2}
k21   | {"label":"5", "x":1, "y":2}
k22   | {"label":"6", "x":2, "y":2}
k30   | {"label":"1", "x":0, "y":3}
k31   | {"label":"2", "x":1, "y":3}
k32   | {"label":"3", "x":2, "y":3}
k33   | {"label":"Enter", "x":3, "y":3, "h":2}
k40   | {"label":"0", "x":0, "y":4, "w":2}
k42   | {"label":".", "x":2, "y":4}

사용자가 Configurator안에 있는 상단좌측의 키를 선택하고, 이를 Num Lock으로 할당할 때, Configurator는 첫 번째 키에 `KC_NUM`으로 키맵 파일을 빌드하고, 그러한 방식으로 키맵이 빌드됩니다.`label`키는 사용되지 않습니다; 단지 `info.json` 파일을 디버깅할 때 특정 키를 식별하는 경우 사용자가 참조하도록 합니다.


## Issues and Hazards

현재는, Configurator가 키를 회전시킨 것이나 직사각형이 아닌 키들, 이를테면 ISO 배열의 Enter와 같은 것을 지원하지 않습니다. 또한, 키들은 "행"에서 수직으로 오프셋된 키 &mdash; [TKC1800](https://github.com/qmk/qmk_firmware/tree/4ac48a61a66206beaf2fdd5f2939d8bbedd0004c/keyboards/tkc1800/)과 같은 1800 레이아웃의 화살표 키가 두드러지는 예제 &mdash; 는 `info.json` 파일의 기여자가 조정하지 않는 경우 KLE-to-JSON Converter를 혼동합니다.

### Workarounds

#### 직사각형이 아닌 키들

ISO 엔터키는, QMK custom이 영숫자의 키 블록의 오른쪽 가장자리와 정렬이 되도록, 너비 1.25u에 높이 2u인 직사각형 키로 표시됩니다.

![](https://i.imgur.com/JKngtTw.png)  
*QMK Configurator로 렌더링된, 기본 ISO 레이아웃의 60% 키보드.*

#### Vertically-offset keys

수직으로 오프셋된 키는, 오프셋이 되지 않은 것처럼 KLE에 배치가 되고 변환된 JSON 파일에서 필요에 따라 Y 값을 편집합니다.

![](https://i.imgur.com/fmDvDzR.png)  
*키보드 레이아웃 에디터로 렌더링 된, 방향키에 대해 수직 오프셋이 없이 적용한 1800 레이아웃 키보드*

![](https://i.imgur.com/8beYMBR.png)  
*키보드의 JSON파일의 방향키에 대해 수직으로 오프셋하는데 필요한 변경사항을 보여주는 유닉스 diff 파일* 
