# Установка инструментов для сборки

Данная страница описывает процесс установки окружения для сборки QMK. Эти инструкции относятся к процессорам AVR (таким как atmega32u4).

<!-- FIXME: Нужно написать и добавить куда-нибудь инструкции для ARM. -->

**Примечание:** Если вы здесь впервые, ознакомьтесь с [Руководством для полных новичков](ru-ru/newbs.md).

Прежде, чем продолжить, убедитесь, что у вас обновлены подмодули (сторонние библиотеки), выполнив `make git-submodule`.

## Linux

Чтобы всегда быть уверенными, что у вас установлены последние версии ПО, можно просто выполнить команду `sudo util/qmk_install.sh`. Она должна установить все необходимые зависимости. **Это выполнит `apt-get upgrade`.**

Вы также можете устанавливать все вручную, но в данной документации список требований может не всегда быть актуальным.

Текущие требования представлены ниже, но не все они могут быть необходимы, так как зависят от того, что вы делаете. Также стоит отметить, что в некоторых системах не все зависимости доступны в виде пакетов, или они могут называться по-другому.

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

Установите все зависимости при помощи вашего любимого менеджера пакетов.

Пример для Debian / Ubuntu:

    sudo apt-get update
    sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi

Пример для Fedora / Red Hat:

    sudo dnf install gcc unzip wget zip dfu-util dfu-programmer avr-gcc avr-libc binutils-avr32-linux-gnu arm-none-eabi-gcc-cs arm-none-eabi-binutils-cs arm-none-eabi-newlib
    
Пример для Arch / Manjaro:

    pacman -S base-devel gcc unzip wget zip avr-gcc avr-binutils avr-libc dfu-util arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib git dfu-programmer dfu-util

## Nix

Если вы используете [NixOS](https://nixos.org/), или у вас установлена Nix в Linux или macOS, выполните `nix-shell` из корня репозитория, чтобы настроить окружение для сборки.

По умолчанию, это скачает компиляторы для AVR и ARM. Если вам не нужны они оба, отключите `avr` или `arm` с помощью аргумента, например:

    nix-shell --arg arm false

## macOS

Если вы пользуетесь [Homebrew](https://brew.sh/), вы можете использовать следующие команды:

    brew tap osx-cross/avr
    brew tap PX4/homebrew-px4
    brew update
    brew install avr-gcc@8
    brew link --force avr-gcc@8
    brew install dfu-programmer
    brew install dfu-util
    brew install gcc-arm-none-eabi
    brew install avrdude

Данный метод является рекомендуемым. Если у вас нет Homebrew, [установите его!](https://brew.sh/) Он очень сильно пригодится тем, кто работает с командной строкой. Стоит отметить, что часть с `make` и `make install` во время установки `avr-gcc@8` из Homebrew может занимать более 20 минут и сильно нагружать CPU.

## Windows с MSYS2 (рекомендуется)

Наилучшим окружение для Windows Vista и всех последующих версий (тестировалось с 7 и 10) является [MSYS2](https://www.msys2.org).

* Для установки MSYS2, скачайте его и следуйте дальнейшим указаниям отсюда: https://www.msys2.org
* Откройте ``MSYS2 MingGW 64-bit`` ярлык
* Перейдите в свой репозиторий QMK. Например, если он находится в корне вашего диска C:
  * `$ cd /c/qmk_firmware`
* Запустите `util/qmk_install.sh` и следуйте подсказкам

## Windows 10 (устарело)

Это устаревшие инструкции для Windows 10. Мы рекомендуем использовать [MSYS2, как сказано выше](#windows-с-msys2-рекомендуется).

### Обновление для дизайнеров (Creators Update)

Если у вас Windows 10 с Обновлением для дизайнеров или новее, вы можете собрать прошивку и прошить ей напрямую. До Обновления для дизайнеров было возможно только собрать прошивку. Если у вас его еще нет, или вы не уверены, следуйте [этим инструкциям](https://support.microsoft.com/en-us/instantanswers/d4efb316-79f0-1aa1-9ef3-dcada78f3fa0/get-the-windows-10-creators-update).

### Подсистема Windows для Linux (Windows Subsystem for Linux, WSL)

В дополнение к Обновлению для дизайнеров вам необходима подсистема Windows для Linux, поэтому установите ее, следуя [иснтрукциям здесь](https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/). Если у вас уже есть подсистема Windows для Linux из Юбилейного обновления (Anniversary update), рекомендуется ее [обновить](https://betanews.com/2017/04/14/upgrade-windows-subsystem-for-linux/) до 16.04LTS, потому что некоторые клавиатуры не компилируются с набором инструментов из 14.04LTS. Стоит отметить, что вы четко должны понимать, что вы делаете, если выбрали метод `sudo do-release-upgrade`.

### Git

Если вы уже клонировали репозиторий в файловую систему Windows, вы можете пропустить данную секцию.

Вам нужно клонировать репозиторий в файловую систему Windows при помощи обычного Git для Windows, а **не** WSL Git. Так что, если вы ещё не установили Git, [скачайте](https://git-scm.com/download/win) и установите его. Затем [настройте его](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup). Важно указать свой адрес электронной почты и имя пользователя, особенно если вы планируете вносить свой вклад в проект.

Как только Git будет установлен, откройте командную строку Git Bash и поменяйте директорию на ту, в которую хотите клонировать QMK; обратите внимание, что вы должны использовать косую черту, и что доступ к вашему диску C осуществляется примерно так: `/c/path/to/where/you/want/to/go`. Затем выполните `git clone --recurse-submodules https://github.com/qmk/qmk_firmware`, это создаст новую папку `qmk_firmware` в текущей директории.

### Установка инструментов (Toolchain)

Установка инструментов (Toolchain) осуществляется через подсистему Windows для Linux, и процесс полностью автоматизирован. Если вы хотите выполнить установку вручную, то не существует никакой другой инструкции помимо самого скрипта. Однако, вы всегда можете открыть ишью и запросить дополнительную информацию.

1. Откройте "Bash On Ubuntu On Windows" в меню Пуск.
2. Перейдите в папку, в которую клонирована `qmk_firmware`. Обратите внимание, что пути начинаются с `/mnt/` в WSL, так что вы должны написать, например, `cd /mnt/c/path/to/qmk_firmware`.
3. Запустите `util/wsl_install.sh` и следуйте инструкциям на экране.
4. Закройте окно командной строки Bash, и откройте его снова.
5. Все готово, чтобы скомпилировать прошивку и прошить ей!

### Несколько важных вещей, которые надо запомнить

* Вы можете запустить `util/wsl_install.sh` еще раз, чтобы установить все последние обновления.
* Ваш репозиторий QMK должен находиться в файловой системе Windows, поскольку WSL не может запускать выполняемые файлы извне.
* WSL Git **не** совместим с Windows Git, поэтому используйте Windows Git Bash или Windows Git GUI для всех операций с Git.
* Вы можете изменять файлы как внутри WSL, так и просто через Windows. Но обратите внимание, что если вы изменяете makefiles или сценарии командной строки, вы должны убедиться, что используете текстовый редактор, который сохраняет файлы с переводом строки в стиле Unix (Unix line endings). В противном случае компиляция может не работать.

## Docker

Если это немного сложновато для вас, Docker может стать готовым решением, которое вы ищите. После установки [Docker CE](https://docs.docker.com/install/#supported-platforms) выполните следующую команду из директории `qmk_firmware`, чтобы собрать клавиатуру/раскладку:

```bash
util/docker_build.sh keyboard:keymap
# Например: util/docker_build.sh ergodox_ez:steno
```

Это скомпилирует указанную клавиатуру/раскладку и создаст для вас `.hex` или `.bin` файл с результатом, готовым к процессу прошивки, в директории QMK. Если опустить `:keymap`, будет использована раскладка `default`. Заметьте, что формат параметров такой же, как и в случае сборки командой `make`.

Вы также можете запустить скрипт без параметров. Тогда он попросит вас ввести поочередно параметры сборки. Возможно, вам это покажется более удобным:

```bash
util/docker_build.sh
# Читает параметры из пользовательского ввода (оставьте пустым для значений по умолчанию)
```

Также имеется поддержка сборки _и_ прошивки клавиатуры прямо из Docker. Для этого укажите еще один параметр `target`:

```bash
util/docker_build.sh keyboard:keymap:target
# Например: util/docker_build.sh planck/rev6:default:dfu-util
```

Если вы используете Linux, это должно работать прямо из коробки. На Windows и macOS это требует запуска [Docker Machine](http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos/). Ее довольно утомительно настраивать, поэтому мы не рекомендуем это; используйте вместо этого [QMK Toolbox](https://github.com/qmk/qmk_toolbox).

!> Docker для Windows требует включения [Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v). Это означает, что он не работает на версиях Windows без Hyper-V, например, на Windows 7, Windows 8 и **Windows 10 Home**.

## Vagrant

Если у вас возникли проблемы при сборке прошивки, вы можете попробовать установить инструмент под названием Vagrant. Он сконфигурирует виртуальный компьютер с такими параметрами, которые подходят для сборки прошивки. У OLKB НЕТ файлов такого виртуально компьютера. Подробности о том, как настроить Vagrant, можно найти в [Руководстве по Vagrant](ru-ru/getting_started_vagrant.md).
