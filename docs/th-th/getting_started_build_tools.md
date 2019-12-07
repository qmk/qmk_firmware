# ติดตั้ง Build Tools

คู่มือหน้านี้อธิบายการเตรียม Build Environment เพื่อใช้งาน QMK ซึ่งรวมถึง AVR Processors (เช่น atmega32u4).

<!-- FIXME: We should have ARM instructions somewhere. -->

**Note:** ถ้าไม่เคยอ่านมาก่อน โปรดอ่าน [ไกด์สำหรับมือใหม่](newbs.md)

ก่อนจะทำอะไรต่อ เช็คว่า Submodules ต่างๆ​ อัปเดตเป็นเวอร์ชั่นล่าสุดแล้ว โดยการรัน `make git-submodule`

## Linux

เพิ่อให้แน่ใจว่าเป็นเวอร์ชั่นล่าสุด รันคำสั่ง `sudo util/qmk_install.sh` ซึ่งจะติดตั้ง Dependencies ทั้งหมดที่ต้องการ **คำสั่งจะรัน `apt-get upgrade`** หรือคุณจะลงมือติดตั้งทุกอย่างเองก็ได้ ซึ่งแพคเกจทั้งหมดมีดังนี้

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

อาจมีแพคเกจบางตัวที่ไม่ต้องใช้ ขึ้นกับการใช้งาน

ลงแพจเกจเหล่านี้ผ่าน Package Manager

ตัวอย่างสำหรับ Debian / Ubuntu:

    sudo apt-get update
    sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi

ตัวอย่างสำหรับ Fedora / Red Hat:

    sudo dnf install gcc unzip wget zip dfu-util dfu-programmer avr-gcc avr-libc binutils-avr32-linux-gnu arm-none-eabi-gcc-cs arm-none-eabi-binutils-cs arm-none-eabi-newlib

ตัวอย่างสำหรับ Arch / Manjaro:

    pacman -S base-devel gcc unzip wget zip avr-gcc avr-binutils avr-libc dfu-util arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib git dfu-programmer dfu-util

## Nix

สำหรับ [NixOS](https://nixos.org/) หรือใช้ Nix บน Linux ทรือ macOS, รัน `nix-shell` จาก repository root

โดยจะทำการดาวน์โหลดคอมไพเลอร์สำหรับ AVR และ ARM ถ้าไม่ต้องการทั้งคู่ ให้ปิดผ่าน Arguments `avr` หรือ `arm` เช่น

    nix-shell --arg arm false # ปิดการดาวน์โหลด ARM Compiler

## macOS
ติดตั้ง [homebrew](http://brew.sh/) แล้วใช้คำสั่งเหล่านี้:

    brew tap osx-cross/avr
    brew tap PX4/homebrew-px4
    brew update
    brew install avr-gcc@8
    brew link --force avr-gcc@8
    brew install dfu-programmer
    brew install dfu-util
    brew install gcc-arm-none-eabi
    brew install avrdude

ช่วง `make` กับ `make install` ในขณะที่ติดตั้ง `avr-gcc@8` อาจใช้ CPU มาก และใช้เวลาเกินกว่า 20 นาที

## Windows ผ่าน msys2 (แนะนำ)

วิธีที่ดีที่สุดสำหรับ Windows Vista ขึ้นไปคือ [msys2](http://www.msys2.org) (ทดสอบบน Windows 7 และ Windows 10 แล้ว)

* ติดตั้ง msys2 จาก http://www.msys2.org
* เปิด ``MSYS2 MingGW 64-bit`` ผ่าน shortcut
* เข้าไปยัง QMK repository เช่น ถ้า QMK อยู่ที่ `C:\qmk_firmware`
 * `$ cd /c/qmk_firmware`
* รัน `util/qmk_install.sh` แล้วทำตามคำสั่ง

## Windows 10 (เลิกใช้)
ต่อไปนี้คือวิธีติดตั้งเก่าสำหรับ Windows 10 เราแนะนำให้คุณใช้วิธี MSYS2 ด้านบนแทน

### Creators Update
ถ้ามี Windows 10 ที่มี Creators Update หรือใหม่กว่า คุณสามารถ Build และ Flash Firmware ได้โดยตรง แต่ถ้ายังไม่มี Creators Update จะทำได้แค่ Build อย่างเดียว อ่าน[วิธีติดตั้ง](https://support.microsoft.com/en-us/instantanswers/d4efb316-79f0-1aa1-9ef3-dcada78f3fa0/get-the-windows-10-creators-update).

### Windows Subsystem for Linux
นอกจาก Creators Update ต้องมี Windows 10 Subystem for Linux ด้วย [วิธีติดตั้ง](http://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/) และ[อัปเกรด](https://betanews.com/2017/04/14/upgrade-windows-subsystem-for-linux/) เป็นรุ่น 16.04LTS เพราะบาง Keyboard คอมไพล์บน 14.04LTS ไม่ได้

### Git
(ข้ามส่วนนี้ไปถ้าทำการ Clone repository ผ่าน Git แล้ว)

เพื่อทำการ Clone repository ให้ใช้ Git for Windows (**ไม่ใช้** WSL Git) [ดาวน์โหลด Git](https://git-scm.com/download/win) แล้ว[ติดตั้ง](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup) และถ้าจะ Contribute ให้ทำการเซ็ตอัป e-mail และ username ด้วย

เมื่อติดตั้ง Git แล้ว เปิด Git Base แล้วเปลี่ยน Directory ไปยังจุดที่ต้องการโคลนโค้ด QMK เช่น `C:\download` ให้ใชง `cd /c/download` (ใช้ forward slash `/`) แล้วรัน `git clone --recurse-submodules https://github.com/qmk/qmk_firmware` คำสั่งจะสร้างโฟลเดอร์ `qmk_firmware` ขึ้นมา

### Toolchain Setup
วิธี Toolchain setup ทำผ่าน Windows Subsystem for Linux

1. เปิด "Bash On Ubuntu On Windows" จาก start menu
2. ไปที่ directory ที่โคลนโค้ด `qmk_firmware` ซึ่งจะขึ้นตันด้วย `/mnt/` ใน WSL เช่น `cd /mnt/c/path/to/qmk_firmware` ถ้าอยู่ที่ `C:\path\to\qmk_firmware
3. รัน `util/wsl_install.sh` แล้วทำตามคำสั่ง
4. เปิดและเปิด "Bash On Ubuntu On Windows" ใหม่

### ข้อควรสำคัญ
* รัน `util/wsl_install.sh` เพื่อรับอัพเดตล่าสุด
* QMK repository ต้องอยู่บน Windows file system path เนื่องจาก WSL ไม่สามารถรัน exe ข้างนอกได้
* WSL Git ไม่เข้ากันกับ Windows Git ให้ใช้ Windows Git Bash หรือ Git GUI สำหรับทุกคำสั่ง Git
* ถ้าต้องการแก้ไขไฟล์ให้ระวัง Line ending เพราะไฟล์ต่างๆ เป็น Unix line endings

## Docker

ถ้าใช้ [Docker](https://docs.docker.com/install/#supported-platforms) ให้รันคำสั่งจาก `qmk_firmware` directory เพื่อ build keyboard/keymap:
```bash
util/docker_build.sh keyboard:keymap
# ตัวอย่าง: util/docker_build.sh ergodox_ez:steno
```
คำสั่งนี้จะทำการคอมไพล์ keyboard/keymap และได้เป็นไฟล์ `.hex` or `.bin` สำหรับ flash ถ้าเว้น `:keymap` ด้านหลัง จะใช้ `default` keymap สังเกตว่า Parameter จะหน้าตาเหมือน Build ด้วยคำสั่ง `make`

หรือถ้ารันโดยไม่ใช้ Parameter เลย จะสามารถพิมพ์ชี่อ keyboard/keymap ตามลงไปได้
```bash
util/docker_build.sh
```

ถ้าจะ Build แล้ว Flash ผ่าน Docker ให้กำหนด `target` ต่อท้าย:
```bash
util/docker_build.sh keyboard:keymap:target
# ตัวอย่าง: util/docker_build.sh planck/rev6:default:dfu-util
```

!> การใช้ Docker for Windows ต้องเปิด [Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v) ซึ่งไม่มีบน Windows 7 Windows 8 และ **Windows 10 Home**

## Vagrant
อ่าน [วิธีติดตั้งผ่าน Vagrant](getting_started_vagrant.md).
