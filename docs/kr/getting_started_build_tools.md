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

이 방법을 가장 추천합니다. 만약 홈브루가 없다면 커맨드라인 환경에서 매우편한 [Homebrew](http://brew.sh/)를 다운받는 것을 추천합니다. 참고로 `avr-gcc@7`를 설치하는 중 `make`과 `make install`는 대개 20분 넘게 걸리고 CPU 사용량이 높아집니다.

## msys2를 사용하는 윈도우 (추천)
윈도우 비스타 부터 최신버젼까지 가장추천되는 환경은 [msys2](http://www.msys2.org)를 이용하는 것입니다. (윈도우 7과 윈도우 10에서 모두 테스트되었음)

* 이 사이트에 있는 설명을 이용해 msys2를 설치하세요: http://www.msys2.org
* ``MSYS2 MingGW 64-bit`` 를 여세요
* QMK폴더로 이동하세요. c드라이브 루트에 있는경우:
 * `$ cd /c/qmk_firmware`
* `util/qmk_install.sh`을 실행시키고 나오는데요 따라하세요

### 크리에이터 업데이트
만약 당신의 윈도우 10이 크리에이터 업데이트 버전 또는 더 높은 버전이라면 바로 컴파일과 프로그램 업로드(flashing)를 할 수 있습니다. 크리에이터 업데이트 전 버전이라면 컴파일만 가능합니다. 만약 당신이 잘 모르겠거나 업데이트된 버전이 아니라면 [Instructions](https://support.microsoft.com/en-us/instantanswers/d4efb316-79f0-1aa1-9ef3-dcada78f3fa0/get-the-windows-10-creators-update)를 확인해 보십시오.

### 리눅스용 윈도우 하위 시스템 사용 (Windows10 Subsystem for Linux)
크리에이터 업데이트에 추가로 만약 당신이 리눅스용 윈도우 하위 시스템이 필요하다면 이 링크에서 다운받으십시오: [Instructions](http://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/)
만약 당신이 이미 리눅스용 윈도우 하위 시스템을 Anniversary업데이트를 통해 받았다면 이 링크에서 16.04LTS로 업데이트 하는것을 추천합니다. 왜냐하면 업데이트 없이는 일부키보드가 14.04LTS에 포함되있는 도구들로 컴파일되지 않을수 있기때문입니다 : [Upgrade](https://betanews.com/2017/04/14/upgrade-windows-subsystem-for-linux/)


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

### Some Important Things to Keep in Mind
* You can run `util/wsl_install.sh` again to get all the newest updates.
* Your QMK repository need to be on a Windows file system path, since WSL can't run executables outside it.
* The WSL Git is **not** compatible with the Windows Git, so use the Windows Git Bash or a windows Git GUI for all Git operations
* You can edit files either inside WSL or normally using Windows, but note that if you edit makefiles or shell scripts, make sure you are using an editor that saves the files with Unix line endings. Otherwise the compilation might not work.

## Windows (Vista and Later) (Deprecated)

These are the old instructions for Windows Vista and later. We recommend you use [MSYS2 as outlined above](#windows-with-msys2-recommended).

1. If you have ever installed WinAVR, uninstall it.
2. Install [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe). Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**.
3. If you are going to flash Infinity based keyboards you will need to install dfu-util, refer to the instructions by [Input Club](https://github.com/kiibohd/controller/wiki/Loading-DFU-Firmware).
4. Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The scripts depend on the default location.
5. Clone this repository. [This link will download it as a zip file, which you'll need to extract.](https://github.com/qmk/qmk_firmware/archive/master.zip) Open the extracted folder in Windows Explorer.
6. Open the `\util` folder.
7. Double-click on the `1-setup-path-win` batch script to run it. You'll need to accept a User Account Control prompt. Press the spacebar to dismiss the success message in the command prompt that pops up.
8. Right-click on the `2-setup-environment-win` batch script, select "Run as administrator", and accept the User Account Control prompt. This part may take a couple of minutes, and you'll need to approve a driver installation, but once it finishes, your environment is complete!

If you have trouble and want to ask for help, it is useful to generate a *Win_Check_Output.txt* file by running `Win_Check.bat` in the `\util` folder.

## Docker

If this is a bit complex for you, Docker might be the turnkey solution you need. After installing [Docker CE](https://docs.docker.com/install/#supported-platforms), run the following command from the `qmk_firmware` directory to build a keyboard/keymap:
```bash
util/docker_build.sh keyboard:keymap
# For example: util/docker_build.sh ergodox_ez:steno
```
This will compile the desired keyboard/keymap and leave the resulting `.hex` or `.bin` file in the QMK directory for you to flash. If `:keymap` is omitted, the `default` keymap is used. Note that the parameter format is the same as when building with `make`.

You can also start the script without any parameters, in which case it will ask you to input the build parameters one by one, which you may find easier to use:
```bash
util/docker_build.sh
# Reads parameters as input (leave blank for defaults)
```

There is also support for building _and_ flashing the keyboard straight from Docker by specifying the `target` as well:
```bash
util/docker_build.sh keyboard:keymap:target
# For example: util/docker_build.sh planck/rev6:default:dfu-util
```
If you're on Linux, this should work out of the box. On Windows and macOS, it requires [Docker Machine](http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos/) to be running. This is tedious to set up, so it's not recommended; use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) instead.

!> Docker for Windows requires [Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v) to be enabled. This means that it cannot work on versions of Windows which don't have Hyper-V, such as Windows 7, Windows 8 and **Windows 10 Home**.

## Vagrant
If you have any problems building the firmware, you can try using a tool called Vagrant. It will set up a virtual computer with a known configuration that's ready-to-go for firmware building. OLKB does NOT host the files for this virtual computer. Details on how to set up Vagrant are in the [vagrant guide](getting_started_vagrant.md).
