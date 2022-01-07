# 充分利用AVR

<!---
  original document: 0.15.12:docs/squeezing_avr.md
  git diff 0.15.12 HEAD -- docs/squeezing_avr.md | cat
-->

AVR对空间限制极其严格，随着QMK的持续开发，无法再适应这些限制，所以对AVR的支持可能会成为历史。

话说回来，如果想要减小固件编译后的大小，你可以采取如下操作：

## `rules.mk` 配置
第一步，也是非常关键的一步，允许*连接时间优化*(link time optimizatio)，在rules.mk中添加如下配置：

```make
LTO_ENABLE = yes
```
打开此配置后，会让最后的编译操作花费更长的时间，但是生成的编译文件会更小。同时还会禁用*活动方法*(Action Functions)和*活动宏*(Action Macros)，两者都已不建议使用。

在大多数情形下，这都将节省很多空间。

除此之外，还可以禁用某些额外系统，比如：

```make
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
```
这会禁用一些你可能用不到的功能，比如媒体按键或系统音量控制等。

如果节省的空间还不够，还可以禁用这些额外功能：

```make
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
```
这些功能默认是打开的，但可能用不到，关闭前最好认真检查一下是否有用到。

其中最占空间的是"magic"(QMK magic 键码)，它控制NKRO切换、GUI和ALT/CTRL交换等，禁用的话这些都将无法生效。

## `config.h` 配置

如果上面的配置都完成了，而且你不想关闭RGB、Audio、OLED等功能。那你还可以在 `config.h`增加一些额外配置来减小空间。

首先是*锁定键*(Lock Key)支持。如果你拥有Cherry MX Lock开关（真不错！），但是你不想用，更有可能是你根本没有。这种情况， `config.h`中添加：

```c
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
```
Oneshots配置。如果你没有用到这些功能， 可以在`config.h`中禁用：

```c
#define NO_ACTION_ONESHOT
```
tapping keys配置 (mod tap、 layer tap等)，也可以在`config.h`中禁用：
```c
#define NO_ACTION_TAPPING
```
## Audio音频配置

如果你使用到了音频功能，默认包含音乐模式(music mode)功能，它会将矩阵位置转换为音符，虽然挺不错的，但你可能根本用不到它。

如果不用，可以在 `config.h`中禁用：

```c
#define NO_MUSIC_MODE
```
同时修改 `rules.mk`：
```make
MUSIC_ENABLE = no
```

## Layers层配置

*层*也有很多配置来减少固件空间，所有配置在`config.h`。

比如限制*层*的数量，假如使用的层数小于8，可以这样配置：

```c
#define LAYER_STATE_8BIT
```
如果不超过16的话：

```c
#define LAYER_STATE_16BIT
```
如果没有使用到*层*，甚至可以直接把它关闭掉：

```c
#define NO_ACTION_LAYER
```


## OLED显示器配置

你可以通过不使用`sprintf` 或 `snprintf`来节省一大块空间。这些方法会占用约1.5kB的固件空间，而且是可变的。比如WPM就会占用非常多。

你可以将这些代码：

```c
    // OLD CODE
    char wpm_str[4] = {0};
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write(wpm_str, ' '), false);
```
替换为这些：
```c
    // NEW CODE
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
```
将会输出 `WPM:   5`.  

也可以这样做： 

```c
    // NEW CODE
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
```
将会输出 `WPM: 005`.

## RGB配置

如果你的板子使用了GRB，无论是RGB灯（底灯）还是RGB矩阵（按键灯）都需要很多配置去定义不同的动效。有一些键盘默认允许大量的动效，所以可以通过禁用你不需要的动效来节省点空间。

对于RGB灯，你可以在 `config.h`中禁用如下配置：

```c
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE
```

对于RGB矩阵，也需要明确哪些是需要的，对于不需要的，可以在 `config.h`中禁用：

```c
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN

#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
```

# 最后想说

如果你做完了上面所有的设置，编译文件仍然太大，那么你不妨尝试一下ARM控制器（是时候了！）。不过，因为硅短缺和供应链等问题，可能现在很难获得价格便宜的，做好超出预算的准备。

 -- Drashna

这里列举一些ARM控制器的Pro Micro板子：

* [Proton C](https://qmk.fm/proton-c/) (缺货)
* [Bonsai C](https://github.com/customMK/Bonsai-C) (开源, DIY/PCBA)
* [Raspberry Pi 2040](https://www.sparkfun.com/products/18288) (当前不支持, 没有ETA)

还有一些非Pro Micro的板子也能兼容。比较流行的有：

* [WeAct Blackpill F411](https://www.aliexpress.com/item/1005001456186625.html) (~$6 刀)
