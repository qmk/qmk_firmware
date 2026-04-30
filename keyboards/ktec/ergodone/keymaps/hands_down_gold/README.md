# Hands Down Gold Keymap for ErgoDone

这是 K.T.E.C. ErgoDone 键盘的 **Hands Down Gold** 键位布局实现。

## Hands Down Gold 是什么？

**Hands Down Gold** 是一个高度优化的键盘布局，设计用于在分体人体工学键盘上舒适地长时间输入。它基于语言学原理和人体工学统计学：

- 通过智能按键分布减少手指应力
- 最小化同手指二连击（awkward repeated finger uses）
- 针对英文优化，支持滚动输入模式
- 支持和弦和自适应按键码等高级功能

更多信息：https://sites.google.com/alanreiser.com/handsdown

## 布局概览

### 基础层（Hands Down Gold）

```
,--------------------------------------------------.    ,--------------------------------------------------.
|  ~   |  1  |  2  |  3  |  4  |  5  | ESC  |    | ESC |  6  |  7  |  8  |  9  |  0  |  =   |
|------+-----+-----+-----+-----+-----+------|    |-----+-----+-----+-----+-----+-----+------|
| Tab  |  J  |  G  |  M  |  P  |  V  | Del  |    | Bksp|  :  |  .  |  /  |  '  |  ?  | Ent  |
|------+-----+-----+-----+-----+-----|      |    |     |-----+-----+-----+-----+-----+------|
| Caps |Ctrl |Gui  |Alt  |Shift| D   |------|    |-----| A   |Shift|Alt  |Gui  |Ctrl |  B   |
|      | R   | S   | N   | D   | B   |      |    |     | , * | *   | *   | *   | *   |      |
|------+-----+-----+-----+-----+-----+ Esc  |    | Del +-----+-----+-----+-----+-----+------|
| Lsft |  X  |  F  |  L  |  C  |  W  |      |    |     |  U  |  O  |  Y  |  K  |  Q  | Rsft |
`------+-----+-----+-----+-----+-----+------'    `-----+-----+-----+-----+-----+-----+------'
   | Esc |  [  |  ]  |  -  | Sym |                      | Num |  -  |  [  |  ]  | Esc |
   `----------------------------------'                  `----------------------------------'
                                   ,-------------.  ,-------------.
                                   | Del  | Bksp |  | Bksp | Del  |
                            ,------+------+------|  |------+------+------.
                            |      |      | Intl |  | Arr  |      |      |
                            | Num  | Sym  |------|  |------| Bksp | Sym  |
                            |      |      |  F   |  |      |      |      |
                            `------+------+------'  `------+------+------'
```

### 层级说明

| 层级 | 名称 | 功能描述 |
|------|------|--------|
| 0 | Base | Hands Down Gold 优化布局，修饰键在主行 |
| 1 | Symbols | 括号、运算符和常见符号 |
| 2 | Numpad | 数字盘（Benford定律分布，最常见数字在主行） |
| 3 | Function Keys | F1-F12 和特殊功能 |
| 4 | Mouse | 鼠标控制和指针移动 |
| 5 | Arrow Keys | 导航和方向键 |
| 6 | International | 重音字符（可扩展） |

## 构建和刷写

### 前置条件
- QMK 固件已安装：https://docs.qmk.fm/newbs_getting_started
- ErgoDone 键盘和 USB 数据线

### 构建
```bash
qmk compile -kb ktec/ergodone -km hands_down_gold
```

### 刷写
```bash
qmk flash -kb ktec/ergodone -km hands_down_gold
```

提示时，按下 ErgoDone 底部的复位按钮。

## 主要特性

✅ 优化的字母分布 - 高频字母放置以减少手指移动  
✅ 修饰键在主行 - 通过 mod-tap 按键减少小指应力  
✅ 多层支持 - 轻松访问符号、数字和功能  
✅ VIA 支持 - 兼容 VIA 网页配置工具  
✅ 人体工学设计 - 减少长时间输入时的疲劳  

## 自定义

通过编辑 `keymap.c` 可进一步自定义：

- **更改字母位置**：修改基础层
- **添加更多符号**：扩展符号层
- **添加国际字符**：编辑国际字符层
- **调整修饰符**：修改 mod-tap 按键（例如 `LCTL_T(KC_R)`）

## 参考资源

- [Hands Down 官方网站](https://sites.google.com/alanreiser.com/handsdown)
- [QMK 文档](https://docs.qmk.fm/)
- [ErgoDone 键盘](https://github.com/ktec-hq/ErgoDone)

## 致谢

布局设计：Alan Reiser  
ErgoDone 适配：sprite91  
基于：https://github.com/neonfuzz/HandsDown
