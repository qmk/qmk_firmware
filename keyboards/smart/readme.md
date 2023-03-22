# 智芯云 QMK 固件

采用智芯云（i-chip)为QMK定制的芯片套件，实现USB,BLE,2.4G三模键盘。

* 维护支持: [Jacky](https://github.com/JackyJia73/qmk_firmware) ，[智芯云](http://www.i-chip.cn/)

## 编译方法

设置好编译环境后, 使用以下指令(以smart80键盘为例):

     qmk compile -kb smart/smart80 -km via



## 烧录
1. 按住ESC，插上USB接口。
2. 点击电脑弹出窗口，按网页提示选择正确bin文件烧录。  


参考[build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) 和 [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) 。
新手[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).