# QMK 환경 설정

키맵을 빌드하기 전에, 환경 설정을 위해서 몇가지 소프트웨어의 설치가 필요합니다. 이 작업은 펌웨어를 컴파일하려는 키보드의 수와 상관없이 한 번만 수행하면 됩니다.

## 1. 사전 준비사항

시작하기 전에 필요한 몇 가지 소프트웨어가 있습니다.

* [텍스트 편집기](ko/newbs_learn_more_resources.md#text-editor-resources)
  * 플레인 텍스트 파일을 수정하고 저장하는데 필요할 것입니다. 많은 OS에서 탑재되어 있는 기본 편집기는 플레인 텍스트 파일을 저장하지 않으므로, 당신이 선택한 편집기가 저장이 되는지 확인해야 합니다.
* [Toolbox (선택사항)](https://github.com/qmk/qmk_toolbox)
  * Windows와 macOS를 위한 그래픽 프로그램으로 커스텀 키보드를 프로그래밍하고 디버깅을 할 수 있습니다.

?> Linux/Unix 커맨드 라인에서 작업한 적이 없다면, 배워야 하는 몇 가지 기본 개념과 커맨드가 있습니다. [이 자원들](ko/newbs_learn_more_resources.md#command-line-resources)에서 QMK를 잘 작동할 수 있는 것들을 당신에게 가르쳐 줄 것입니다. 

## 2. 빌드 환경 준비 :id=set-up-your-environment

QMK를 최대한 쉽게 설정할 수 있도록 만들었습니다. 단지 Linux 또는 Unix 환경만 준비하면, QMK가 나머지를 설치합니다.

<!-- tabs:start -->

### ** Windows **

QMK는 CLI와 모든 필요한 종속 파일을 묶은 MSYS2로 유지 관리합니다. 또한 편리한 `QMK MSYS` 터미널 바로가기를 제공하여 올바른 환경에서 바로 부팅됩니다.

#### 사전 준비사항

[QMK MSYS](https://msys.qmk.fm/)를 설치해야 합니다. 최신 릴리스는 [여기](https://github.com/qmk/qmk_distro_msys/releases/latest)에 있습니다.

다른 대안으로, 만약에 수동으로 MSYS2를 설치한다면, 다음의 절에서 그 과정을 따라가면 됩니다.

<details>
  <summary>수동 설치</summary>

?> `QMK MSYS`를 사용한다면 이 스텝들은 무시해도 됩니다.

#### 사전 준비사항

MSYS2, Git, 그리고 Python을 설치할 필요가 있습니다. 다음의 설치 지침을 따르세요 https://www.msys2.org.

MSYS2가 설치되면, 열려진 MSYS 터미널을 모두 닫고 새 MinGW 64-bit 터미널을 여세요.

!> **노트:** MinGW 64-bit 터미널은 설치하가 완료되고 열리는 MSYS 터미널과 *같지 않습니다*. 프롬프트에는 "MSYS" 대신 보라색 텍스트로 "MINGW64" 라고 말할 것입니다. 
차이점에 대한 자세한 내용 [이 페이지](https://www.msys2.org/wiki/MSYS2-introduction/#subsystems)에서 볼 수 있습니다.

그런 다음, 따르는 커맨드를 실행하세요:

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip

#### 설치

다음을 실행하여 QMK CLI를 설치하세요:

    python3 -m pip install qmk

</details>

### ** macOS **

QMK는 CLI와 모든 필요한 종속 파일 자동으로 설치하는 Homebrew tab과 formula로 유지 관리합니다.

#### 사전 준비사항

Homebrew를 설치할 필요가 있습니다. 다음의 지침을 따르세요 https://brew.sh.

#### Installation

다음을 실행하여 QMK CLI를 설치하세요:

    brew install qmk/qmk/qmk

### ** Linux/WSL **

?> **WSL 유저에 대한 노트**: 기본적으로는, 설치 과정에서는 WSL의 home 디렉토리에 QMK 레포지토리를 복제할 것이지만, 만약에 수동으로 복제하는 경우, 윈도우 파일시스템 (다시 말해, `/mnt`)에서는 현재 접근이 [매우 느리게 됨](https://github.com/microsoft/WSL/issues/4197)으로 그 대신 WSL 인스턴스 안에 경로가 위치하는지 확인하세요.

#### 사전 준비사항

Git과 Python을 설치할 필요가 있습니다. 이미 둘 다 가지고 있을 가능성이 높지만, 그렇지 않다면 다음의 따르는 커맨드 중 하나로 설치해야 합니다:

* Debian / Ubuntu / Devuan: `sudo apt install -y git python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum -y install git python3-pip`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git python-pip libffi`
* Void: `sudo xbps-install -y git python3-pip`
* Solus: `sudo eopkg -y install git python3`
* Sabayon: `sudo equo install dev-vcs/git dev-python/pip`
* Gentoo: `sudo emerge dev-vcs/git dev-python/pip`

#### 설치

다음을 실행하여 QMK CLI를 설치하세요:

    python3 -m pip install --user qmk

#### 커뮤니티 패키지

이 패키지는 커뮤니티 멤버들에 의해 유지가 되므로, 업데이트가 되어 있지 않거나 완전한 기능을 하지 않을 수 있습니다. 만약에 문제가 발생하면, 해당 관리자에게 보고해주시길 바랍니다.

Arch-based distro는 공식 레포지토리에서 CLI를 설치할 수 있습니다 (노트: 지금 쓰여있는 이 패키지에 대한 일부 디펜던시는 선택사항이 아닙니다):

    sudo pacman -S qmk

또한 AUR에서 `qmk-git` 패키지를 이용할 수도 있습니다:

    yay -S qmk-git

###  ** FreeBSD **

#### Installation

다음을 실행하여 QMK CLI용 FreeBSD 패키지를 설치하세요:

    pkg install -g "py*-qmk"

노트: 설치 마지막에서 인쇄되는 지침을 따르는 것을 잊지 마세요. (다시 보려면 `pkg info -Dg "py*-qmk"`를 사용하세요.)

<!-- tabs:end -->

## 3. QMK Setup 실행 :id=set-up-qmk

<!-- tabs:start -->

### ** Windows **

QMK 설치 후 이 커맨드로 설정하세요:

    qmk setup

대부분 경우에서 모든 프롬프트에 'y'로 답하기 원할 것입니다.

### ** macOS **

QMK 설치 후 이 커맨드로 설정하세요:

    qmk setup

대부분 경우에서 모든 프롬프트에 'y'로 답하기 원할 것입니다.

### ** Linux/WSL **

QMK 설치 후 이 커맨드로 설정하세요:

    qmk setup

대부분 경우에서 모든 프롬프트에 'y'로 답하기 원할 것입니다.

?>**Debian, Ubuntu 그리고 이러한 계열에 대한 노트**
가능합니다, 다음과 같이 말하는 에러를 얻을 수 있다는 걸요: `bash: qmk: command not found`.
이것은 Debian의 [버그](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155)로, Bash 4.4 릴리스에서 PATH 중 `$HOME/.local/bin`를 제거하여 발생합니다. 이 버그는 차후 Debian과 Ubuntu에서 해결이 되었었습니다.
안타깝게도, Ubuntu에서 이 버그는 다시 도입이 되었고 [아직 고치는 중](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562)입니다.
다행이도, 고치는 것은 쉽습니다. 당신의 계정으로 이 것을 실행하세요: `echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc`

###  ** FreeBSD **

QMK 설치 후 이 커맨드로 설정하세요:

    qmk setup

대부분 경우에서 모든 프롬프트에 'y'로 답하기 원할 것입니다.

<!-- tabs:end -->

?> qmk home 폴더는 설정에서 `qmk setup -H <path>`를 사용하여 지정될 수 있고, 이후에는 [cli 구성](ko/cli_configuration.md?id=single-key-example)과 `user.qmk_home` 변수를 사용하여 수정될 수 있습니다. 모든 가능한 옵션은 `qmk setup --help`를 실행하세요.

?> Github를 어떻게 사용하는지 이미 알고있다면, [다음의 지시사항을 따르는 것을 추천](ko/getting_started_github.md)하며, 여러분의 개인계정으로 포크하여 `qmk setup <github_username>/qmk_firmware` 으로 복제하세요. 만약 이것이 무엇은 의미하는 지 모르겠다면, 이 메시지를 무시해도 됩니다.

## 4. 환경 빌드 테스트

이제 QMK 빌드 환경이 설정이 되어, 당신의 키보드를 위한 펌웨어를 빌드할 수 있습니다. 키보드의 기본 키맵을을 빌드를 시도하여 시작하세요. 다음의 형식의 커맨드로 이를 수행할 수 있어야 합니다:

    qmk compile -kb <keyboard> -km default

예를 들면, Clueboard 66% 를 위한 펌웨어를 빌드하기 위해선 이렇게 사용합니다:

    qmk compile -kb clueboard/66/rev3 -km default
    
이것이 완료되면 이것과 비슷하게 끝나는 많은 출력이 있어야 합니다:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# 키맵 빌드하기

이제 자신의 개인 키맵을 만들 준비가 되었습니다! 이를 위해 [첫 펌웨어 빌드하기](ko/newbs_building_firmware.md)로 이동하세요.
