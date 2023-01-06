# 分体式键盘 

QMK 固件的硬件库中存在不少“分体”键盘。它们使用2个主控，其中一侧通过USB连接到电脑，并经过一根 TRRS 音频线（或者类似的线材）使用串行通信或 I<sup>2</sup>C 方式连接到另一侧。

分体式键盘有很多好处，但需要增加一些额外的设置工作。

QMK 固件中有一个可供任何主控板使用的通用实现，也有许多具体主控板的实现。

在此，我们将主要讨论Let's Split键盘和其他键盘所使用的通用实现。

!> ARM 分体式键盘在使用'serial'（串行通信）和'serial_usart'驱动程序时支持大多数QMK子系统。目前不支持I2C slave。

!> 双方必须使用相同系列的MCU，例如两个Pro Micro 兼容控制器或两个Blackpill。目前还无法混用AVR和ARM主控，因为ARM与AVR使用互不兼容的方法进行串行通信。此外，Blackpill使用3.3v逻辑，而atmega32u4使用5v逻辑。

## 兼容性一览

| 通信方式                       | AVR                | ARM                |
|-------------------------------|--------------------|--------------------|
| ['串行通信'](serial_driver.md) | :heavy_check_mark: | :white_check_mark: <sup>1</sup> |
| I2C                           | :heavy_check_mark: |                    |

注意：

1. 关于软件和硬件的限制，都在 [串行通信驱动文档](serial_driver.md)中有详细说明.

## 硬件配置

这里假定你使用了两个Pro Micro兼容控制器，并使用TRRS音频插口连接两侧。

### 硬件需求

除了每一侧键盘矩阵的二极管和按键开关外，你还需要2个TRRS插座和1根TRRS线。

你也可以使用任何一种至少有3根线芯的线缆和插座。

如果你希望使用 I<sup>2</sup>C 进行通信，你需要一根至少有4根线芯的线缆和2个 4.7kΩ 上拉电阻.

#### 考虑事项 

最常用的连接是TRRS线和插孔。这些线材提供了4根线芯且容易获得，因此十分适合在分体式键盘上使用。

但是，其中一条线连接VCC引脚，因此线材并不能热插拔。在拔掉和插入TRRS线材之前，你应该始终将主控板与USB断开，否则你可能会使控制器短路，或者更糟。

另一个选择是使用电话线（如老式的RJ-11/RJ-14电缆）。请确保你使用的是真正支持4条线芯的。 

你还可以使用USB线、SATA线，甚至4根普通的导线，它们都可以用于在主控板之间通信。

!> 使用USB线在主控板之间进行通信也是可行的，但这根连接线可能被误用于连接电脑USB接口，且有可能使键盘短路。所以，并不建议使用USB线来连接分体式键盘。 

### 串行通信接线

把TRS/TRRS线材的3根线接到两侧Pro Micro的GND、VCC和D0/D1/D2/D3（又称PD0/PD1/PD2/PD3）上。

?> 注意：这里使用的引脚实际上是根据下面的 `SOFT_SERIAL_PIN` 设置的。

<img alt="sk-pd0-connection-mono" src="https://user-images.githubusercontent.com/2170248/92296488-28e9ad80-ef70-11ea-98be-c40cb48a0319.JPG" width="48%"/>
<img alt="sk-pd2-connection-mono" src="https://user-images.githubusercontent.com/2170248/92296490-2d15cb00-ef70-11ea-801f-5ace313013e6.JPG" width="48%"/>

### I<sup>2</sup>C 接线

把TRRS线材的4根线接到两侧Pro Micros的GND、VCC、SCL和SDA（又分别称作PD0/Pin 3和PD1/Pin 2）上。

上拉电阻可以放在任何一侧。如果你想独立使用两侧，在两侧都接上拉电阻，一共4个电阻。

请注意，无论放置位置和数量如何，连接系统的总电阻应该在 2.2k-10kΩ 的规格范围内，而4.7kΩ最为“理想”。

<img alt="sk-i2c-connection-mono" src="https://user-images.githubusercontent.com/2170248/92297182-92b98580-ef77-11ea-9d7d-d6033914af43.JPG" width="50%"/>

## 固件配置

在 `rules.mk` 文件中加入下列内容以激活分体功能： 

```make
SPLIT_KEYBOARD = yes
```

如果你使用自定义的通信方式，那么还需要添加：

```make
SPLIT_TRANSPORT = custom
```

### 设置左右手

默认情况下，固件不知道哪边是哪边；因此需要一些辅助设置。有几种方法可以做到这一点，按优先顺序列出。

#### 通过管脚设置左右手

固件可以设置为读取主控上的一个引脚来确定左右手。要做到这一点，请将以下内容添加到你的 `config.h` 文件：

```c
#define SPLIT_HAND_PIN B7
```

这将读取指定的引脚。默认情况下，如果它是高电平，那么控制器就认为它是左手；如果它是低电平，就认为它是右手。

可以在 `config.h` 文件中添加以下代码来翻转上述设置：

```c
#define	SPLIT_HAND_PIN_LOW_IS_LEFT
```

#### 通过矩阵设置左右手

你可以配置固件来读取控制器上的按键矩阵引脚以确定左右手。要做到这一点，请将以下内容添加到你的 `config.h` 文件：

```c
#define SPLIT_HAND_MATRIX_GRID D0, F1
```

第一个引脚是输出引脚，第二个是输入引脚。

有些键盘的按键矩阵中有一些未使用的交叉点。可以在这里使用其中一个未使用的交叉点来判断左右手。

通常情况下，有二极管连接两个引脚的一侧判断为左。如果你加上下面的定义，它将被判断为右边。

```c
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
```

请注意，在未使用的交叉点上添加一个二极管将随时提醒固件在该点上有一个键被按住。你可以通过定义`MATRIX_MASKED`并在键盘配置中定义`matrix_row_t matrix_mask[MATRIX_ROWS]`数组来指示qmk忽略该交叉点。单个值的每一位（从最低有效位开始）用来告诉qmk是否注意该交叉点的按键。

虽然`MATRIX_MASKED`不是成功使用`SPLIT_HAND_MATRIX_GRID`的必要条件，但如果没有它，在连接键盘到电脑之后，你可能会遇到程序卡死的问题。因为矩阵总是报告至少有一个按键。

#### 通过EEPROM设置左右手

该方法通过设置持久性存储（`EEPROM`）中的一个标志来设置键盘的左右侧。该标志在控制器第一次启动时被检查，并判断键盘是哪一侧，以及如何确定键盘布局的方向。

要启用这个方法，请在你的`config.h`文件中添加以下内容。

```c
#define EE_HANDS
```

接下来，你需要对EEPROM文件进行一次写入，以便在两侧主控上分别设置左右手。你可以在刷入固件的同时，用下面的bootloader目标手动完成这个工作。

* AVR 主控和 Caterina bootloader (例如 Pro Micro)：
  * `:avrdude-split-left`
  * `:avrdude-split-right`
* AVR 主控和 Amtel DFU 或 DFU 兼容 bootloader (例如 Elite-C)：
  * `:dfu-split-left`
  * `:dfu-split-right`
* ARM 主控和 DFU 兼容 bootloader (例如 Proton-C)：
  * `:dfu-util-split-left`
  * `:dfu-util-split-right`
* ARM 主控和 UF2 兼容 bootloader：
  * `:uf2-split-left`
  * `:uf2-split-right`

例：

```
make crkbd:default:avrdude-split-left
```

?> 使用 `dfu-util` 的 ARM 控制器在设置左右手后需要重置 EEPROM。可以通过`EE_CLR`键码或[Bootmagic Lite](feature_bootmagic.md)完成。使用模拟EEPROM的主控在刷写固件时总是需要左右侧参数。

?> [QMK Toolbox]() 也可以用来刷入 EEPROM 的左右手设置。将控制器置于 bootloader 模式，选择菜单选项 Tools -> EEPROM -> Set Left/Right Hand。

当使用`EE_CLR`键重新初始化EEPROM，或使用`eeconfig_init()`函数时，该设置不会改变。但是，如果在固件的内置选项之外重置EEPROM（比如刷入一个覆盖`EEPROM`的文件，例如[QMK工具箱]()的 "Reset EEPROM"按钮，那么需要用`EEPROM`文件重新刷写主控。

你可以在QMK固件库（[这里](https://github.com/qmk/qmk_firmware/tree/master/quantum/split_common)）中找到`EEPROM`文件。

#### 通过 `#define` 设置左右手

你可以在编译时设置左右手。要做到这一点，请将以下内容添加到你的 `config.h` 文件：

```c
#define MASTER_RIGHT
```

或者

```c
#define MASTER_LEFT
```

如果两者都没有定义，则默认为`MASTER_LEFT`。


### 通信设置

考虑到分体式键盘的多样性，你可以在`config.h`文件中配置一些额外选项。

```c
#define USE_I2C
```

该选项将激活 I<sup>2</sup>C 通信支持（仅限AVR）。

```c
#define SOFT_SERIAL_PIN D0
```

这设置了用于串行通信的引脚。如果你不使用串行通信，你应该不需要定义这个。 

但是，如果你在主控板上同时使用串行通信和 I<sup>2</sup>C ，你仍需要设置串行通信，并将引脚设置为 D0 或 D1 以外的引脚（因为它们已经被用于 I<sup>2</sup>C 通信）。

```c
#define SELECT_SOFT_SERIAL_SPEED {#}`
```

这个值控制着串行的通信速度。如果你在串行通信方面遇到问题，你可以改变这个值。默认值是1，可能的值包括：

* **`0`**： 大约 189kbps (试验)
* **`1`**： 大约 137kbps (默认)
* **`2`**： 大约 75kbps
* **`3`**： 大约 39kbps
* **`4`**： 大约 26kbps
* **`5`**： 大约 20kbps

```c
#define FORCED_SYNC_THROTTLE_MS 100
```

设置强制从主侧到从侧进行数据同步前的最大毫秒数。在正常情况下只要数据发生变化就会发生同步，为了安全起见，如果自上次同步以来没有检测到任何变化，就会在这个毫秒数之后进行数据传输。

```c
#define SPLIT_MAX_CONNECTION_ERRORS 10
```

设置主侧部件在判断认为没有连接从侧部件之前的最大通信失败次数（每个扫描周期一次）。设置之后，可以在没有连接从侧的情况下使用主侧。

设置为0可完全禁用断联检查。

```c
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
```

在通信被标记为断开后（见上面的`SPLIT_MAX_CONNECTION_ERRORS`），主侧应该间隔多长时间再重新尝试与从侧通信（以毫秒为单位）。

从上次尝试之后，每过一段时间就允许一次通信尝试。如果该尝试成功，则连接正常。

设置为0可以在断开连接时禁用这种通信。这可以为你节省几个字节的固件大小。

### 文件同步设置

以下同步选项增加了左右侧通信协议的开销，启用后可能会对矩阵扫描速度产生负面影响。这些选项可以通过在你的`config.h`文件中添加所选的选项来启用。

```c
#define SPLIT_TRANSPORT_MIRROR
```

将主侧矩阵的情况传输到从侧，以便从侧了解主侧按下了哪些键。这个功能的目的是支持按键事件改变键盘的外观（例如，RGB对按键的反应）。

```c
#define SPLIT_LAYER_STATE_ENABLE
```

在分体式键盘的两侧之间可以同步层的状态。这个功能的主要目的是支持使用诸如OLED显示当前活动层。

```c
#define SPLIT_LED_STATE_ENABLE
```

在分体式键盘的两侧之间同步主机LED状态（大写锁定、数字锁定等）。这个功能的主要目的是支持使用诸如OLED显示主侧LED状态的功能。

```c
#define SPLIT_MODS_ENABLE
```

把修饰键的状态（正常、弱和单发）传输到分体式键盘的副侧。这个功能的目的是支持修饰键改变键盘外观（例如在OLED屏幕上显示状态）。

```c
#define SPLIT_WPM_ENABLE
```

把当前的WPM传输到分体式键盘的副侧。这个功能的目的是支持WPM的外观使用（例如在OLED屏幕上显示当前值）。

```c
#define SPLIT_OLED_ENABLE
```

把当前的OLED开/关状态传输到分体式键盘的副侧。这个功能的目的是支持状态（仅开/关状态）同步。

```c
#define SPLIT_ST7565_ENABLE
```

把当前的ST7565开/关状态传输到分体式键盘的副侧。这个功能的目的是支持状态（仅开/关状态）同步。

```c
#define SPLIT_POINTING_ENABLE
```

把指向性设备的状态传输到分体式键盘的副侧。这个功能的目的是在副端使用指向性设备。

!> 在[pointing device documentation](feature_pointing_device.md?id=split-keyboard-configuration)中概述了`SPLIT_POINTING_ENABLE`的额外必要配置。

### 双方的自定义数据同步 :id=custom-data-sync

QMK的分体式键盘通信允许在键盘和用户层面进行任意的数据传输。这是以远程过程调用实现的：主侧在从侧调用一个函数，能够自主侧向从侧发送数据，在从侧进行处理，并自从侧向主侧发送数据。

为了利用这一点，键盘或用户/键位表中可以定义一个以逗号分隔的 _transaction ID_ 列表：

```c
// 键盘级别数据同步：
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_SYNC_A, KEYBOARD_SYNC_B
// 用户级别：
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_A, USER_SYNC_B, USER_SYNC_C
```

这些 _transaction ID_ 需要在通信中配置一个从侧的处理函数。例如：

```c
typedef struct _master_to_slave_t {
    int m2s_data;
} master_to_slave_t;

typedef struct _slave_to_master_t {
    int s2m_data;
} slave_to_master_t;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    slave_to_master_t *s2m = (slave_to_master_t*)out_data;
    s2m->s2m_data = m2s->m2s_data + 5; // whatever comes in, add 5 so it can be sent back
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}
```

然后，主侧可以调用从侧处理程序——为了使正常的键盘功能受到最小的影响，不宜在这里设置任何试图同步数据的键盘或用户级代码。

```c
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            master_to_slave_t m2s = {6};
            slave_to_master_t s2m = {0};
            if(transaction_rpc_exec(USER_SYNC_A, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprintf("Slave value: %d\n", s2m.s2m_data); // this will now be 11, as the slave adds 5
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
```

!> 建议两侧之间的所有数据同步安排在主控方的 _housekeeping task_ 期间。这可以确保在发生故障时及时重试。

如果只需要单向的数据传输，可以使用下面的辅助方法：

```c
bool transaction_rpc_exec(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
bool transaction_rpc_send(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer);
bool transaction_rpc_recv(int8_t transaction_id, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
```

默认情况下，传输的数据被限制为每个最大32字节。如果需要，可以改变这些大小：

```c
// 主到副：
#define RPC_M2S_BUFFER_SIZE 48
// 副到主：
#define RPC_S2M_BUFFER_SIZE 48
```

###  硬件配置选项

你可能需要根据硬件的设计方式配置下面的内容：

```c
#define MATRIX_ROW_PINS_RIGHT { <row pins> }
#define MATRIX_COL_PINS_RIGHT { <col pins> }
```

这允许你为右边的矩阵指定一组不同的引脚。如果你的键盘左右手两侧形状不同，需要不同的配置（比如Keebio的Quefrency），你需要设置这个功能。左右矩阵的引脚数量必须相同，如果你一侧的开发板的行或列数量不同，请用`NO_PIN`占据多余的空间，并确保将未使用的行或列加入你的矩阵。

```c
#define DIRECT_PINS_RIGHT { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }
```

这允许你为右侧指定一组不同的直连引脚。

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
```

这允许你为右侧指定一组不同的编码器引脚。

```c
#define RGBLIGHT_SPLIT
```

该选项可以使分体式键盘的主控板之间的RGB灯模式同步。这适用于RGB LED直接与主控连接（也就是说，它们没有使用TRRS电缆上的“额外数据”选项）的键盘。

```c
#define RGBLED_SPLIT { 6, 6 }
```

这设置了有多少个LED直接连接到每个控制器。 第一个数字是左边的，第二个数字是右边的。 

?> 这个设置意味着 `RGBLIGHT_SPLIT`已经启用，如果没有启用，将强行启用它。

```c
#define SPLIT_USB_DETECT
```

启用这个选项会改变启动行为，以监听一个活跃的USB通信来决定哪个部分是主侧，哪个部分是从侧。启用这个选项后，如果有USB通信，那么这一半就认为自己是主侧，否则就认为自己是从侧。

如果没有这个选项，主侧能够检测物理USB连接上的电压的那一半（VBUS检测）。

在ChibiOS/ARM上默认是启用的。

?> 该设置将影响通过电池供电的能力。

```c
#define SPLIT_USB_TIMEOUT 2000
```
这设置了使用 `SPLIT_USB_DETECT`时，检测主/从侧的最大超时。

```c
#define SPLIT_USB_TIMEOUT_POLL 10
```
这设置了使用 `SPLIT_USB_DETECT`时，检测主/从侧的轮训频率。

```c
#define SPLIT_WATCHDOG_ENABLE
```

这将在从侧启用软件看门狗，如果在`SPLIT_WATCHDOG_TIMEOUT`内没有成功的通信发生，将重新启动键盘。在某些情况下，当`SPLIT_USB_DETECT`要求双方都作为从机时，这可能特别有用。

```c
#define SPLIT_WATCHDOG_TIMEOUT 3000
```

这设置了使用 `SPLIT_WATCHDOG_ENABLE`时，从侧等待来自主侧通信的最大超时。

## 硬件方面的考虑和修改

主/从授权是通过检测VBUS连接上的电压或等待USB通信（`SPLIT_USB_DETECT`）实现的。Pro Micro板可以实现VBUS检测，因此可以选择使用或不使用`SPLIT_USB_DETECT`。

许多ARM板，但不是全部，不支持VBUS检测。因为ARM开发板常常缺乏VBUS检测功能，所以`SPLIT_USB_DETECT`在ARM目标上被自动定义（当ChibiOS为目标时）。

### Teensy 开发板

Teensy 开发板缺乏VBUS检测，必须定义`SPLIT_USB_DETECT`。对于Teensy 2.0和Teensy++ 2.0，你可以通过简单的硬件修改来增加VBUS检测，所以你不需要`SPLIT_USB_DETECT`选项。

你只需要几样东西就可以了。

* 一把刀（最好是x-acto刀片）
* 一个焊台或热风枪焊台
* 一个适当的肖特基二极管，如[PMEG2005EH](https://www.digikey.com/en/products/detail/nexperia-usa-inc/PMEG2005EH,115/1589924)

你需要切断Teensy背面5V和中心焊盘之间的线路。

然后，你需要把二极管从5V焊盘焊接到中心焊盘上。

你可能需要使用上面的稳压器块的5V焊盘，因为焊盘太小，而且放在一起太近，无法正确放置肖特基二极管。

![Teensy++ 2.0](https://i.imgur.com/BPEC5n5.png)

## 其他资源

Nicinabox为Let's Split键盘提供了一份[非常好的详细指南](https://github.com/nicinabox/lets-split-guide)，其中涵盖了你需要知道的大部分内容，包括故障排除信息。

但是，该文档的RGB灯部分已经过时了，因为它是在QMK固件中加入RGB Split代码之前很久才写的。取而代之的是，将每个灯条直接连接到控制器上。

<!-- I may port this information later, but for now ... it's very nice, and covers everything -->
