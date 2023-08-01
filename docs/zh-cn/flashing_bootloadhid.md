# BootloadHID刷写指引及资料

<!---
  original document: 0.15.12:docs/flashing_bootloadhid.md
  git diff 0.15.12 HEAD -- docs/flashing_bootloadhid.md | cat
-->

ps2avr(GB)基于一片ATmega32A微控制器及特殊的bootloader，无法使用常规的QMK方法进行刷写。

常规刷写过程：

1. 使用如下任一方式进入bootloader模式：
    * 点击 `QK_BOOT` 键码（一些设备上不管用）
    * 在按住“盐键”（salt key）时插入键盘（该键一般会在键盘使用说明上写明）
2. 等待操作系统识别到设备
3. 将.hex文件刷写进去
4. 重置设备到应用模式（可能会自动进行）

## 用于bootloadHID刷写的构建目标

?> 使用QMK安装脚本，具体[参见这里](zh-cn/newbs_getting_started.md)，所需的bootloadHID工具应自动被安装上。

若希望通过命令行进行刷写，通过如下命令指定 `:bootloadhid` 构建目标：

    make <keyboard>:<keymap>:bootloadhid

## 基于图形化界面的刷写方法

### Windows
1. 下载[HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash)
2. 重置键盘
3. 确认VID为 `16c0` 且PID为 `05df`
4. 点击 `查找设备（Find Device）` 并确认目标键盘可见
5. 点击 `打开.hex文件（Open .hex File）` 并定位到你创建的.hex文件
6. 点击 `刷写设备（Flash Device）` 并等待刷写完毕

## 在命令行中进行刷写

1. 重置键盘 
2. 通过输入 `bootloadHID -r` 并追加 `.hex` 文件的路径进行主控板的刷写

### Windows系统上手动安装
针对MSYS2:
1. 下载BootloadHID固件包：https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz
2. 使用合适的工具解压，如7-Zip
3. 将解压出的 `commandline/bootloadHID.exe` 拷贝至MSYS目录下，一般是 `C:\msys64\usr\bin`

针对Windows本地环境刷写，`bootloadHID.exe` 可以直接在非MSYS2环境下执行。

### Linux系统上手动安装
1. 安装libusb开发依赖项：
    ```bash
    # 该操作具体取决于系统 - Debian下可以这样
    sudo apt-get install libusb-dev
    ```
2. 下载BootloadHID固件包：
    ```
    wget https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz -O - | tar -xz -C /tmp
    ```
3. 构建bootloadHID可执行程序：
    ```
    cd /tmp/bootloadHID.2012-12-08/commandline/
    make
    sudo cp bootloadHID /usr/local/bin
    ```

### MacOS系统上手动安装
1. 执行以下命令安装Homebrew：
    ```
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    ```
2. 安装以下包：
    ```
    brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
    ```
