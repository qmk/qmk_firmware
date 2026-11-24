# RP2040-Zero：使用不带预设引脚的通用 RP2040 板级定义
BOARD = GENERIC_RP_RP2040

# WS2812 用 RP2040 的 PIO 驱动（不受 Flash 缓存抖动影响，时序稳定）
WS2812_DRIVER = vendor

# VIA 在线改键
VIA_ENABLE = yes

LTO_ENABLE = yes

# 板载单灯 GP16 的独立 PIO 驱动（QMK 只会自动编译与文件夹同名的 mks3_numpad.c，
# 其它 .c 必须显式列出，否则链接时报 undefined reference）
SRC += gp16_led.c
