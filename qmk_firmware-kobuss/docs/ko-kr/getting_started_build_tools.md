# 컴파일 도구 설치

이 페이지는 QMK 컴파일 환경을 설치하는 방법을 설명합니다. 이 페이지는 AVR 프로세서들(예를 들면 atmega32u4와 비슷한)을 위한 가이드를 제공합니다

<!-- FIXME: We should have ARM instructions somewhere. -->


**노트:** 만약 당신이 처음 시작한다면 [입문자를 위한 가이드](newbs.md)페이지를 확인하세요.

계속하기전에 당신의 서브모듈(외부라이브러리)이 최신인지 `make git-submodule`을 사용하여 확인하세요.

## 리눅스

당신이 항상 최신 파일을 가지고 있는지는 `sudo util/qmk_install.sh`을 이용하여 간단히 확인할 수 있습니다. 이 명령어는 당신이 필요한 모든 속성물(dependencies)를 설치할 것입니다. **이 명령어는 `apt-get upgrade`를 사용합니다**

또한 당신의 직접 필요한 것들을 설치할 수도 있습니다. 하지만 이 자료는 항상 최신의 자료을 가지고 있지 않습니다.

현재로써 필요한 것은 다음과 같습니다. 하지만 당신이 하는 작업에 따라 당신은 다음 패키지를 다 쓰지 않을 수도 있습니다. 또한 환경에 따라 모든 다음 패키지는 다른이름으로 존재하거나, 없을 수도 있습니다.

```
build-essential
gcc
unzip
wget
zip
gcc-avr
binutils-avr
avr-libc
dfu-programmer
dfu-util
gcc-arm-none-eabi
binutils-arm-none-eabi
libnewlib-arm-none-eabi
git
```

당신이 사용하는 패키지 매니져에서 이러한 방법으로 설치하십시요.

데비안 / 우분투 예시:

    sudo apt-get update
    sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi

페도라 / 레드햇 예시:

    sudo dnf install gcc unzip wget zip dfu-util dfu-programmer avr-gcc avr-libc binutils-avr32-linux-gnu arm-none-eabi-gcc-cs arm-none-eabi-binutils-cs arm-none-eabi-newlib
    
아치 / 맨자로(Manjaro) 예시:

    pacman -S base-devel gcc unzip wget zip avr-gcc avr-binutils avr-libc dfu-util arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib git dfu-programmer dfu-util

## 닉스 (NIX)

만약 당신이 [NixOS](https://nixos.org/)를 사용중이거나 NIX를 리눅스 또는 맥에서 사용중이라면 `nix-shell`를 root 디렉토리에서 사용하여 컴파일 환경의 구축할 수 있습니다.

기본적으로 다음 커맨드는 AVR과 ARM 컴파일러를 설치할것입니다. 만약 필요 없다면 `avr` 또는 `arm`을 인수에서 해제할 수 있습니다.

    nix-shell --arg arm false

## 맥
당신이 홈브루([homebrew](http://brew.sh/))를 사용한다면, 다음을 입력하세요.

    brew tap osx-cross/avr
    brew tap PX4/homebrew-px4
    brew update
    brew install avr-gcc@7
    brew link --force avr-gcc@7
    brew install dfu-programmer
    brew install dfu-util
    brew install gcc-arm-none-eabi
    brew install avrdude

이 방법을 가장 추천합니다. 만약 홈브루가 없다면 커맨드라인 환경에서 매우 편한 [Homebrew](http://brew.sh/)를 다운받는 것을 추천합니다. 참고로 `avr-gcc@7`를 설치하는 중 `make`과 `make install`는 대개 20분 넘게 걸리고 CPU 사용량이 높아집니다.

## msys2를 사용하는 윈도우 (추천)
윈도우 비스타 부터 최신버젼까지 가장추천되는 환경은 [msys2](http://www.msys2.org)를 이용하는 것입니다. (윈도우 7과 윈도우 10에서 모두 테스트되었음)

* 이 사이트에 있는 설명을 이용해 msys2를 설치하세요: http://www.msys2.org
* ``MSYS2 MingGW 64-bit`` 를 여세요
* QMK폴더로 이동하세요. c드라이브 루트에 있는경우:
 * `$ cd /c/qmk_firmware`
* `util/qmk_install.sh`을 실행시키고 나오는데요 따라하세요

### 크리에이터 업데이트
만약 당신의 윈도우 10이 크리에이터 업데이트 버전 또는 더 높은 버전이라면 바로 컴파일과 프로그램 업로드(flashing)를 할 수 있습니다. 크리에이터 업데이트 전 버전이라면 컴파일만 가능합니다. 만약 당신이 잘 모르겠거나 업데이트된 버전이 아니라면 [이 링크](https://support.microsoft.com/en-us/instantanswers/d4efb316-79f0-1aa1-9ef3-dcada78f3fa0/get-the-windows-10-creators-update)를 확인해 보십시오.

### 리눅스용 윈도우 하위 시스템 사용 (Windows10 Subsystem for Linux)
크리에이터 업데이트에 추가로 만약 당신이 리눅스용 윈도우 하위 시스템이 필요하다면 이 링크에서 다운받으십시오: [설명](http://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/)

만약 당신이 이미 리눅스용 윈도우 하위 시스템을 Anniversary업데이트를 통해 받았다면 이 링크에서 16.04LTS로 업데이트 하는것을 추천합니다. 왜냐하면 업데이트 없이는 일부키보드가 14.04LTS에 포함되있는 도구들로 컴파일되지 않을수 있기때문입니다 : [WSL 업데이트](https://betanews.com/2017/04/14/upgrade-windows-subsystem-for-linux/)


### Git
만약 당신이 이미 파일을 로컬로 복제하였다면 이 섹션을 무시하십시요.

당신은 파일을 기본적인 git을 사용하여 로컬로 복제해야 합니다. **주의, WSL Git을 사용하면 안됩니다** [Git](https://git-scm.com/download/win) 이 링크에서 git을 다운받고 설치하십시오.
그리고 [기본설정](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup), 유저네임과 이메일을 설정하는 것은 만약 당신이 온라인에 기여할 계획이라면 매우 중요합니다.

Git의 설치가 완료되었다면 Git Bash커맨드을 열고 당신의 복제 QMK파일이 있는 위치로 이동하고 `git clone --recurse-submodules https://github.com/qmk/qmk_firmware`를 실행 시키십니오. 이 커맨드는 새로운 `qmk_firmware`폴더를 이미 존재하는 것의 하위 폴더설정으로 생성할 것입니다.

### 도구(Toolchain) 설정
기본적으로 도구설정은 리눅스용 윈도우 하위 시스템이 설치될때 자동으로 설정됩니다. 하지만 수동적으로 하고 싶다면 여기 설명이 있습니다. (If you want to do everything manually, there are no other instructions than the scripts themselves, but you can always open issues and ask for more information. )

1. "Bash On Ubuntu On Windows" 을 실행시키십시오.
2. 당신이 `qmk_firmware`를 복제한 위치로 가십시오. WSL(리눅스용 윈도우 하위 시스템 사용)에서 `/mnt/`로 시작되는 패스를 찾으십시오. 즉 당신은 다음과 같은 형식으로 입력해야 합니다. `cd /mnt/c/path/to/qmk_firmware`  (Note that the paths start with `/mnt/`in the WSL, so you have to write for example `cd /mnt/c/path/to/qmk_firmware`.)
3. `util/wsl_install.sh`를 실행시키고 화면에 나오는 지시를 따르십니오.
4. Bash command window를 재실행 시키십시오.
5. 이로써 당신은 컴파일과 프로그램 업로드(flashing)을 위한 준비가 모두 끝났습니다.

### 중요한 참고사항
*`util/wsl_install.sh` 명령어를 다시 실행시켜 최신 업데이트를 다운받을 수 있습니다.
* QMK 폴더의 위치는 윈도우 파일시스템을 기반으로 해야 됩니다. WSL는 외부실행파일를 작동 시킬수 없기 때문이죠.
* WSL의 Git은 윈도우용 Git과 **호환되지 않습니다**
* 파일을 수정하는 것은 WSL안과 밖에서 모두 가능합니다 하지만 만약 .makefile 혹은 .sh를 수정한다면 유닉스 라인엔딩(Unix line endings)을 지원하는 에디터를 사용하는지 확인하십이오. 그렇지 않다면 컴파일이 되지않을 수도 있습니다.

## 윈두우 (비스타 혹은 더 최신) (비추천)

이 섹션은 윈도우 비스타 혹은 더 최신버젼을 위한 오래된 설명입니다. [MSYS2](#windows-with-msys2-recommended)를 사용하는 것을 더 추천합니다.

1. WinAVR을 설치하였다면 먼저 삭제하십시오.
2. [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe)을 설치하십시오. (Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**)
3. 만약 당신이 Infinity을 기반으로 하는 키보드에 프로그램 업로드를(flashing) 할거라면 dfu-util을 설치해야 합니다, [Input Club](https://github.com/kiibohd/controller/wiki/Loading-DFU-Firmware) 를 참고 하십시오.
4. [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download)를 설치하십시오. 설치중 윈도우화면에서 GUI 추가 설치 옵션을 해재하십니오. **기본 설치 위치를 바꾸지 마십시오.** 이 명령어는 기본위치를 기반으로 하고 있습니다.
5. 레파지토리를 복제하십시오. [이 링크로 압축파일을 받고 앞축해제 하십시오.](https://github.com/qmk/qmk_firmware/archive/master.zip) 윈도우 탐색기에서 다운받은 파일을 여십시오.
6. `\util` 폴더를 여십시오.
7. `1-setup-path-win` .bat파일을 더블클릭해서 실행시키시오. 유저 계정 설정 변경을 허용해야될 수도 있습니다. 스페이스바를 눌러 설치가 성공적으로 완료되었다는 메세지를 닫을 수 있습니다.
8. `2-setup-environment-win` .bat파일에 우클릭해서 '관리자 권한으로 실행'으로 실행시키십시오. 이 작업을 꽤 오래 걸릴 수도 있습니다. 또한 드라이버 설정을 승인해야 될 수도 있습니다. 하지만 이 모든것이 끝나면 당신의 시스템의 설정이 모두 끝났습니다.

만약 이 작업을 하는데에 문제가 있어 도움받고 싶다면 *Win_Check_Output.txt*을 생성하는 것이 도움이 될것입니다. 이 파일은 `Win_Check.bat`을 `\util`폴더에서 실행시켜 생성할 수 있습니다.

## 도커(Docker)
만약 위작업들이 당신에게 좀 어렵게 느껴졌다면 도커(Docker)가 당신을 위한 최선일 수도 있습니다(의역). [Docker CE](https://docs.docker.com/install/#supported-platforms)를 설치한뒤 아래 커맨드를 `qmk_firmware` 디랙토리에서 실행시켜 키보드 또는 키맵을 생성시킵니다.
```bash
util/docker_build.sh keyboard:keymap
# 예: util/docker_build.sh ergodox_ez:steno
```
이 커맨드는 원하는 키보드 또는 키맵을 컴파일하고 `.hex`또는 `.bin`파일을 프로그램 업로드를(flashing) 위해 QMK디랙토리에 생성할것입니다. 만약 `:keymap`이 생략된다면 `default`이 기본을로 사용됩니다. 참고로 여기서 사용되는 인수는 `make` 커맨드를 사용하여 컴파일할때와 동일합니다.


또한 스크립트를 그냥 아무 인수 없이도 사용가능합니다. 그렇게 된다면 프로그램은 하나씩 자동으로 인수입력을 요구 할것입니다. 어쩌면 이방법이 더 쉬울 수도 있습니다.
```bash
util/docker_build.sh
# 인수을 입력받습니다.(아무것도 쓰지 않고 놔두는면 기본값으로 설정됩니다)
```

다음과 같이 `target`를 사용하여 컴파일과 프로그램 업로드(flashing)을 동시에 할수도 있습니다.
```bash
util/docker_build.sh keyboard:keymap:target
# 예: util/docker_build.sh planck/rev6:default:dfu-util
```
만약 당시이 리눅스를 사용한다면 이 커맨드들은 추가 설정 없이 바로 작동할 것입니다. 하지만 위도우 또는 맥 환경에서는 [Docker Machine](http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos/)를 사용하여야 이 커맨드들을 사용가능합니다. Docker Machine설정은 꽤 지루하고 짜증남으로 추천하지 않고 [QMK Toolbox](https://github.com/qmk/qmk_toolbox)를 사용하는 것을 추천합니다.

!> 윈도우에서 독커는 [Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v)을 활성화 설정하여야 사용가능합니다. 즉, 도커는 Hyper-V를 지원하지 않는 윈도우 7, 윈도우 8, 그리고 **윈도우 10 홈**과 같은 윈도우 버전에서 사용할수 없다는 것을 의미합니다.

## Vagrant
만약 컴웨어를 사용하는데 문제가 있다면 Vagrant라는 이름의 툴을 사용해 볼 수 있습니다. 이 툴은 가상환경을 세팅해줌과 동시에 컴웨어를 사용하는데에 필요한 모든 설정을 해줄 것입니다. OLKB는 가상환경에 파일을 호스팅하지 않습니다. [Vagrant 가이드](getting_started_vagrant.md)에서 더 많은 정보를 확인할 수 있습니다.
