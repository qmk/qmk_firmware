# QMK Configurator: Step by Step

이 페이지에서는 QMK Configurator로 펌웨어를 빌드하는 스텝을 설명합니다.

## 스텝 1: 키보드를 선택하기

드롭 다운 박스를 클릭하고 키맵을 생성하고 싶은 키보드를 선택하세요.

?> 키보드가 몇가지 버전이 있다면, 올바른 것을 선택하였는지 확인하세요.

이것은 중요한 것이므로 다시 말씀드립니다:

!> **올바른 버전을 선택하였는지 꼭 확인하세요!**

당신의 키보드가 QMK로 구동되는 것으로 광고되었지만 목록에 없다면, 개발자가 아직 키보드에 적용하지 않았거나 아직 병합할 기회가 없었을 가능성이 있습니다. [qmk_firmware](https://github.com/qmk/qmk_firmware/issues)에 특별한 키보드에 대해 지원을 요청하는 이슈를 제기하거나, 아무런 반응이 없다면 [Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard)를 요청하세요. 제조업체의 자체 GitHub 계정에 있는 QMK 기반 키보드도 있습니다. 그 점에 대해서도 한 번 더 확인하세요. <!-- FIXME(skullydazed): This feels too wordy and I'm not sure we want to encourage these kinds of issues. Also, should we prompt them to bug the manufacutrer? -->

## 스텝 2: 키보드 레이아웃 선택하기

생성하려는 키맵을 가장 잘 제시하는 레이아웃을 선택하세요. 일부 키보드는 충분한 레이아웃이나 올바른 레이아웃이 아직 정의되지 않을 수 있습니다. 이러한 것들은 미래에 지원이 될 것입니다. 

!> 가끔은 실제 빌드하려고 지원하는 레이아웃이 없습니다. 그러한 경우에는 `LAYOUT_all`을 선택하세요.

## 스텝 3: 키맵 이름짓기

이 키맵을 원하는 대로 불러보세요.

?> 컴파일링을 할 때 이슈가 발생하는 경우, 이름이 이미 QMK repo에 존재하는 것이므로 바꾸는 게 좋습니다.

## 스텝 4: 키맵 정의하기

Keycode Entry는 3가지 방법으로 수행합니다:

1. 드래그 앤 드롭
2. 레이아웃의 빈 지점을 클릭하고, 원하는 키코드를 클릭하기
3. 레이아웃의 빈 지점을 클릭하고, 키보드의 물리적 키를 누르기

키 위로 마우스를 가져가면 짧은 안내문이 해당 키코드가 하는 일을 알려 줄 것입니다. 자세한 설명은 다음을 참조하세요:

* [초급용 키코드 참조](ko/keycodes_basic.md)
* [고급용 키코드 참조](ko/feature_advanced_keycodes.md)

!> 선택한 레이아웃이 실제 빌드와 일치하지 않는다면 사용하지 않는 키는 비워두도록 하세요. 사용 중인 키가 확실하지 않은 경우, 이를테면 백스페이스 키가 하나 있지만 `LAYOUT_all`에는 키가 2개 있다면, 두 위치에 같은 키코드를 입력하세요.

## 스텝 5: 차후 변경을 위해 키맵 저장하기

키맵에 만족하거나 단지 나중에 작업을 진행한다면, `Download this QMK Keymap JSON File` 버튼을 누르세요. 컴퓨터에 여러분의 키맵을 저장할 것입니다. 차후에 `Upload a QMK Keymap JSON File` 버튼을 누름으로 이 .json 파일을 불러올 수 있습니다.

!> **주의:** 이것은 kbfirmware.com 또는 어떠한 다른 도구에서 사용되는 .json 파일의 같은 타입이 아닙니다. 만약에 이러한 도구들로 이를 사용한다면, 또는 이러한 도구의 .json 파일로 QMK Configurator를 사용한다면, 문제가 발생할 것입니다.

## 스텝 6: 펌웨어 파일을 컴파일하기

녹색 `Compile` 버튼을 누르세요.

컴파일이 완료되면, 녹색 `Download Firmware` 버튼을 누를 수 있을 것입니다.

## 다음 스텝: 키보드 플래시하기

[펌웨어 플래시](ko/newbs_flashing.md)를 참고해주세요.
