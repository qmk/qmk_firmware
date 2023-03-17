# Grave Escape

<!---
  original document: 0.15.12:docs/feature_grave_esc.md
  git diff 0.15.12 HEAD -- docs/feature_grave_esc.md | cat
-->

*译注：Grave键即标准键盘中Tab键上方的 <code>&#96;</code> 键，该符号用于英法语等西语体系，辅助调整发音，中文中没有对应概念；Escape即Esc键*

若你使用60%或其它没有Fn键配列的键盘，会留意到没有独立的Escape键。Grave Escape功能可以让Grave键(<code>&#96;</code>及`~`)与Escape共享一个按键

## 使用方法

在配列中使用 `QK_GESC` 替换 `KC_GRAVE` （一般都在`1`键左边）。默认点击会输出 `KC_ESC`，按下Shift或GUI键时，点击会输出 `KC_GRV`

## 操作系统视角

假如翠花按下GESC键，系统接收到的是KC_ESC字符。若翠花按住Shift再按下GESC，将输出 `~` 或是反引号。若翠花按住GUI/CMD/Win键，将仅输出<code>&#96;</code>字符

## 键码

|键       |别名       |描述                                                               |
|---------|-----------|------------------------------------------------------------------|
|`QK_GESC`|`GRAVE_ESC`|单击输出Escape, 按住Shift或GUI时输出<code>&#96;</code>               |

### 须留意

在macOS上 Command+<code>&#96;</code>默认行为是“移动焦点到下一个窗口”，因此不会输出反引号。另外，即便在键盘配置中更改过快捷键，终端程序(Terminal)也通常会将这个操作视为循环切换窗口

## 配置

有几种键组合可以变更这种行为，如Windows下的Control+Shift+Escape、macOS下的Command+Option+Escape。若要调整，可以在 `config.h` 中通过 `#define` 配置

|定义                      |描述                                      |
|--------------------------|-----------------------------------------|
|`GRAVE_ESC_ALT_OVERRIDE`  |按住Alt时输出Escape                       |
|`GRAVE_ESC_CTRL_OVERRIDE` |按住Control时输出Escape                   |
|`GRAVE_ESC_GUI_OVERRIDE`  |按住GUI时输出Escape                       |
|`GRAVE_ESC_SHIFT_OVERRIDE`|按住Shift时输出Escape                     |
