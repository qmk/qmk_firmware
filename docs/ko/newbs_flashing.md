# 키보드 플래시

이제 빌드했던 커스텀 펌웨어 파일을 당신의 키보드에 플래시할 차례입니다.

## 키보드를 DFU (Bootloader) Mode로 놓기

커스텀 펌웨어를 플래시하기 위해 처음으로 반드시 특별한 플래시 모드로 키보드를 놓아야 합니다. 이 모드에 있는 동안에는 키보드를 타이핑 하거나 또는 다른 걸 사용할 수 없을 것입니다. 펌웨어가 쓰여지는 동안에는 키보드 연결을 끊거나 플래싱 과정을 막는 행위를 하지 않는 것이 매우 중요합니다.

여럿 키보드들은 이 특별한 모드로 진입하기 위해 다른 방법을 가지고 있습니다. PCB가 현재 QMK, TMK 또는 PS2AVRGB (Bootmapper Client)로 실행되고 있고 구체적인 지시사항을 받지 못한경우, 다음을 순서대로 시도해보세요:

* 양쪽 shift키를 누른 채로 `Pause`키 누름
* 양쪽 shift키를 누른 채로 `B`키 누름
* 키보드의 연결을 끊고, 스페이스바와 `B`키를 동시에 누른 채로, 키보드를 연결하고 키를 놓기 전 잠시 대기
* 키보드의 연결을 끊고, 왼쪽에 놓인 가장 높이 또는 아래에 있는 키(보통 Esc나 왼쪽 Ctrl키)를 누른 채로 키보드를 연결
* 물리적 `RESET`버튼 누름, 보통 PCB 아래쪽에 위치
* PCB에 `RESET`과 `GND`로 라벨링 된 헤더 핀을 찾고, PCB가 연결된 동안 함께 쇼트 시킴

위의 모든 것을 시도해 보았으나 아무 소용이 없고, 보드의 메인 칩이 `STM32`라고 표시되어 있다면, 이건 약간 더 복잡할 수도 있습니다. 일반적으로 가장 좋은 방법은 도움을 위해 [디스코드](https://discord.gg/Uq7gcHh)에 물어보는 것입니다. 보드에 대한 몇 가지 사진을 물어볼 수 있을 겁니다 -- 미리 준비해 둔다면 진행하는 데 도움이 될 것입니다!

그렇지 않으면, QMK Toolbox에 다음과 유사한 노란색 메시지가 표시됩니다. 

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
```

그리고 이 부트로더 장치가 장치 관리자, 시스템 정보 앱, 또는 `lsusb`에도 제시될 것입니다.

## QMK Toolbox로 키보드 플래시

키보드를 플래시할 수 있는 아주 간단한 방법인 [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)가 있습니다.

하지만, Toolbox가 현재 Windows와 macOS에서만 사용할 수 있습니다. Linux를 사용하고 있다면 (또는 단지 커맨드 라인으로 펌웨어를 플래시 하길 원한다면), [커맨드 라인으로 키보드 플래시](ko/#flash-your-keyboard-from-the-command-line) 절로 넘어가세요.

### QMK Toolbox으로 파일 로드하기

QMK Toolbox 응용프로그램을 여는 걸 시작하세요. Finder 또는 Explorer에서 펌웨어 파일을 찾고 싶을 것입니다. 키보드 펌웨어가 두 포맷-`.hex`나 `.bin` 중 하나로 있을 것입니다. QMK는 루트 `qmk_firmware` 디렉토리에 키보드에 적합한 하나를 복사하는 걸 시도합니다.
 
Windows 또는 macOS를 사용하고 있다면, Explorer나 Finder에서 현재 폴더를 쉽게 열 수 있는 커맨드가 있습니다.

<!-- tabs:start -->

#### ** Windows **

```
start .
```

#### ** macOS **

```
open .
```

<!-- tabs:end -->

펌웨어 파일은 항상 다음의 이름 포맷을 따릅니다:

```
<keyboard_name>_<keymap_name>.{bin,hex}
```

에를들어, `planck/rev5`의 `default` 키맵은 이 파일명을 가질 것입니다:

```
planck_rev5_default.hex
```

펌웨어 파일을 찾았으면, QMK Toolbox의 "Local file" 상자로 끌어다 놓거나, "Open"을 클릭하고 펌웨어 파일이 저장된 위치로 이동하세요.

### 키보드 플래시하기

QMK Toolbox의 `Flash` 버튼을 클릭하세요. 다음을 따르는 유사한 출력을 볼 수 있을 것입니다:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
*** Attempting to flash, please don't remove device
>>> dfu-programmer.exe atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer.exe atmega32u4 flash "D:\Git\qmk_firmware\gh60_satan_default.hex"
    Checking memory from 0x0 to 0x3F7F...  Empty.
    0%                            100%  Programming 0x3F80 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x3F80 bytes written into 0x7000 bytes memory (56.70%).
>>> dfu-programmer.exe atmega32u4 reset
    
*** DFU device disconnected: Atmel Corp: ATmega32U4 (03EB:2FF4:0000)
```

## 커맨드 라인으로 키보드 플래시

이것은 이전과 비교하면 꽤 단순하게 만들어져 있습니다. 펌웨어를 컴파일과 플래시 할 준비가 되어있을 때, 터미널 창을 열어 플래시 커맨드를 실행하세요:

    qmk flash

[빌드 환경 구성](ko/newbs_getting_started.md)절에 따라 키보드/키맵의 이름을 CLI에서 구성하지 않았다면, 또는 여러개의 키보드를 가지고 있다면, 키보드와 키맵의 이름을 특정지을 수 있습니다:

    qmk flash -kb <my_keyboard> -km <my_keymap>

이것은 키보드의 구성을 체크하고, 특정 부트로더를 기반으로 하여 플래시를 시도할 것입니다. 이는 여러분이 어떤 부트로더를 키보드에서 사용하는 지 알 필요가 없는 것입니다. 단지 커맨드를 실행하고, 커맨드가 무거운 일을 하게 두면 됩니다.

하지만, 이는 키보드에 의해 설정되는 부트로더에 의존한다는 것입니다. 이 정보가 구성되어 있지 않거나, 플래시할 지원되는 대상이 아닌 보드를 사용중이라면, 다음의 에러가 보일 것입니다:

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

이 경우에는, 다시 돌아가서 부트로더를 특정지어야 할 것입니다. [펌웨어 플래시](ko/flashing.md) 가이드에서 자세한 사항을 볼 수 있습니다.

## 이제 테스트 해보세요!

축하드려요! 커스텀 펌웨어가 키보드에 프로그래밍되어 이제 테스트를 할 준비가 되었습니다!

약간의 운이 있으면 모든 것이 완벽하게 작동하지만, 그렇지 않은 경우 무엇이 잘못되었는지 파악하는 데 도움이 되는 단계가 있습니다. 
키보드를 테스트하는 것은 보통 꽤 직관적입니다. 각 모든 키를 눌러서 기대한대로 키가 전송하는지 확인하세요. QMK를 실행중이지 않더라도, [QMK Configurator](https://config.qmk.fm/#/test/)의 테스트 모드에서 키보드를 확인해볼 수 있습니다.

아직도 잘 작동하지 않나요? 더 많은 정보를 위해 FAQ 토픽을 찾아보거나, [우리와 Discord에서 채팅](https://discord.gg/Uq7gcHh)하세요.
