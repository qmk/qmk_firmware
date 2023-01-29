# 첫 펌웨어 빌드

이제 당신의 빌드 환경을 설정하였고 커스텀 펌웨어를 빌드를 시작할 준비가 되었습니다. 안내사항의 이 절에서는 3개의 프로그램- 파일 관리자, 텍스트 편집기, 그리고 터미널 윈도우 사이를 왔다 갔다 할 것입니다. 키보드 펌웨어에 만족할 때까지는 3개를 모두 열어두세요.

## 기본 빌드 환경 구성 (선택사항)

빌드 환경에서 기본값을 구성할 수 있으며 이는 QMK 작업을 덜 지루하게 합니다. 지금 시작해보도록 하죠!

QMK를 처음 접하는 대부분의 사람들은 키보드를 1개 가지고 있습니다. `qmk config` 커맨드로 이 키보드를 기본값으로 설정할 수 있습니다. 예를 들어, 당신의 키보드를 `clueboard/66/rev4`로 기본값을 설정하려면:

    qmk config user.keyboard=clueboard/66/rev4

?> 키보드 옵션은 키보드 디렉토리에 대한 상대 경로이며, 위의 예시에서는 `qmk_firmware/keyboards/clueboard/66/rev4`에서 찾을 수 있을 것입니다. 확실하지 않다면 지원되는 키보드의 전체 목록을 `qmk list-keyboards`으로 볼 수 있습니다. (한국어 추가설명) 동일한 키보드에 대해 중복되는 항목이 있을 수 있습니다. 위의 예시에서는 clueboard의 66키보드에도 하위 버전이 rev1부터 rev4까지 존재합니다. 이는 각 키보드 별로 기능을 업데이트 해서 발전된 버전이거나, 또는 키보드 배열 차이로 인해 다른 버전을 둔 것일 수 있습니다. 이 부분에 대해서는 Github qmk_firmware 레포지토리에서 확인하시길 바랍니다.

또한 기본 키멥 이름을 지정할 수 있습니다. 대부분의 사람들은 이전 단계에서 온 키맵의 이름을 Github 사용자 이름으로 사용합니다:

    qmk config user.keymap=<github_username>

## 새로운 키맵 생성

나만의 키맵을 생성하기 위해 `default` 키맵의 복사본을 생성하길 원할 것입니다. 지난 스텝에서 개인 빌드 환경을 구성하였다면 QMK CLI로 손쉽게 할 수 있습니다:

    qmk new-keymap

만약에 환경을 구성하지 않았다면, 또는 여러개의 키보드를 가지고 있다면, 키보드의 이름을 특정지을 수 있습니다:

    qmk new-keymap -kb <keyboard_name>

해당 커맨드로 출력되는 것을 눈여겨 보면, 다음과 같은 내용이 표시되어야 합니다:

    Ψ <github_username> keymap directory created in: /home/me/qmk_firmware/keyboards/clueboard/66/rev3/keymaps/<github_username>

이것은 새로운 `keymap.c` 파일이 그 위치에 있다는 것입니다.

## 가장 선호하는 텍스트 에디터로 `keymap.c` 열기

여러분의 `keymap.c` 파일을 텍스트 에디터로 열어보세요. 이 파일 안에서 키보드가 어떻게 동작하도록 제어하는 구조를 찾을 수 있습니다. `keymap.c` 상단에는 키맵을 읽기 쉽게 만들어진 몇 가지 define과 enum이 있을 수 있습니다. 아래로 내려가면 다음과 같이 보이는 라인이 있습니다:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

이 라인은 Layer들의 목록이 시작되는 것을 지시합니다. 아래에서 `LAYOUT` 을 포함하는 라인을 찾을 것이고, 이 라인들은 layer의 시작을 나타냅니다. 그 아래의 라인에는 특정 레이어를 구성하는 키들의 목록이 있습니다.

!> 키맵 파일을 수정할 때 어떠한 쉼표(, comma)를 추가하거나 삭제하지 않도록 주의하세요. 그러한 행동을 한다면 펌웨어가 컴파일되는 것을 막을 것이며 여분의 쉼표 또는 누락된 쉼표가 어디에 있는지 파악하는 게 쉽지 않을 수 있습니다.

## 원하는대로 레이아웃 사용자 정의하기

이 스텝을 어떻게 완료할지는 전적으로 당신에게 달려 있습니다. 하나의 변화로 버그를 일으키거나, 완전히 모든 걸 재작업해야 합니다. 모든 layer가 더 이상 필요하지 않다면 지울 수도 있으며, 또는 최대 32개의 layer를 추가할 수 있습니다. QMK 안에는 많은 기능들이 있으며, 왼쪽 사이드바의 아래에 있는 "QMK 사용"을 탐색하여 전체 항목을 보면 됩니다. 시작하기 위해 여기 몇 가지 사용하기 쉬운 기능이 있습니다:

* [기본 키코드](ko/keycodes_basic.md)
* [Quantum 키코드](ko/quantum_keycodes.md)
* [그레이브/이스케이프](ko/feature_grave_esc.md)
* [마우스 키](ko/feature_mouse_keys.md)

?> 키맵이 작동하는 방식에 대한 느낌을 얻는 동안, 변경사항을 작게 유지하세요. 변경사항이 크면 발생하는 어떤 문제들에 대한 디버깅을 하기에 더 어렵습니다.

## 펌웨어 빌드하기 :id=build-your-firmware

키맵 변경을 완전히 끝냈다면 펌웨어를 빌드할 필요가 있을 것입니다. 그렇게 하려면 터미널 윈도우로 다시 돌아가서 컴파일 커맨드를 실행하세요:

    qmk compile
    
만약에 환경을 구성하지 않았다면, 또는 여러개의 키보드를 가지고 있다면, 키보드의 이름을 특정지을 수 있습니다:

    qmk compile -kb <keyboard> -km <keymap>

이 컴파일로 많은 출력이 화면에 표시될 것이고, 어떤 파일들이 컴파일되고 있는 중인지에 대한 정보를 줍니다. 이것과 비슷하게 보인다면 다음으로 출력이 끝나야합니다:

```
Linking: .build/planck_rev5_default.elf                                                             [OK]
Creating load file for flashing: .build/planck_rev5_default.hex                                     [OK]
Copying planck_rev5_default.hex to qmk_firmware folder                                              [OK]
Checking file size of planck_rev5_default.hex                                                       [OK]
 * The firmware size is fine - 27312/28672 (95%, 1360 bytes free)
```

## 펌웨어 플래시

[펌웨어 플래시](ko/newbs_flashing.md)로 이동하여 새로운 펌웨어를 어떻게 키보드에 쓰는 지 배워 보세요.
