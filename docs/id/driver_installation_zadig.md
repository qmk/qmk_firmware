# Pemasangan Penggerak *Bootloader* dengan Zadig

QMK membawakan dirinya kepada komputer inang sebagai piranti papan ketik HID sehingga tidak membutuhkan penggerak khusus. Namun, agar dapat menge-*flash* papan ketik anda pada Windows, piranti *bootloader* yang muncul saat anda mereset papan ketik anda sering kali **membutuhkan** penggerak khusus.

Tentu ada pengecualian: *bootloader* Caterina yang sering kali ada pada Pro Micro dan HalfKay yang terdapat pada Teensy buatan PJRC. Keduanya menunjukkan diri sebagai piranti porta serial dan HID generik sehingga tidak membutuhkan sebuah penggerak.

Kami merekomendasikan penggunaan utilitas [Zadig](https://zadig.akeo.ie). Bila anda mengatur lingkungan pengembangan dengan MSYS2, skrip `qmk_install.sh` akan memasangkannya untuk anda.

## Pemasangan

Pindah papan ketik anda ke mode *bootloader*, bisa dengan menekan kode tombol `RESET` (yang mungkin ada pada *layer* berbeda) atau dengan menenkan saklar reset yang biasanya terletak pada bagian bawah papan. Bila papan ketik anda tidak memiliki keduanya, silakan coba untuk menahan `Escape` atau `Space`+`B` saat anda menyambungkannya ke komputer inang (lihat [*Bootmagic*](id/feature_bootmagic.md) untuk detail lebih lanjut). Beberapa papan ketik menggunakan fitur [Command](id/feature_command.md) yang mengharuskan anda untuk menahan *Shift* Kiri + *Shift* Kanan + `B` atau *Shift* Kiri + *Shift* Kanan + `Escape` kapanpun saat papan ketik anda tersambung pada komputer inang.

Beberapa papan ketik mungkin memiliki instruksi khusus untuk berpindah ke *bootloader*. Sebagai contoh, tombol [*Bootmagic Lite*](id/feature_bootmagic.md#bootmagic-lite) (bawaan: `Escape`) mungkin ada pada tombol yang berbeda, mis. *Control* Kiri; atau kombinasi *magic* untuk *Command* (bawaan: *Shift* Kiri + *Shift* Kanan) mengharuskan anda untuk menahan tombol lain. mis, *Control* Kiri + *Control* Kanan. Silakan pelajari berkas README papan ketik anda bila anda tidak yakin.

Untuk mengubah sebuah piranti ke mode *bootloader* dengan USBaspLoader, ketuk tombol `RESET` sembari menahan tombol `BOOT`. Bisa juga dengan menahan `BOOT` sembari menyambungkan papan ketik ke komputer inang.

Seharusnya, Zadig akan secara otomatis mendeteksi piranti *bootloader*. Namun, kadang kala anda harus memeriksa **Options → List All Devices** dan memilih piranti pada *dropdown.*

!> Bila Zadig menampilkan satu piranti atau lebih dengan penggerak `HidUsb`, papan ketik anda mungkin tidak berada pada mode *bootloader*. Panah akan berwarna oranye dan anda akan diminta untuk mengkonfirmasi pengubahan penggerak sistem. **JANGAN** lanjutkan bila terjadi hal semacam ini.

Bila panah berwarna hijau, pilih penggerak, dan klik **Install Driver**. Silakan lihat [daftar-daftar *bootloader* yang dikenal](#list-of-known-bootloaders) untuk penggerak yang harus dipasang.

![Zadig with a bootloader driver correctly installed](https://i.imgur.com/b8VgXzx.png)

Terakhir, lepas dan sambung papan ketik untuk memastikan penggerak baru sudah termuat. Bila anda menggunakan QMK Toolbox untuk menge-*flash*, tutup aplikasi tersebut dan jalankan ulang. Sering kali, QMK Toolbox gagal mendeteksi perubahan penggerak.

## Pemulihan dari Pemasangan Piranti yang Salah

Bila anda menemukan diri anda tidak dapat mengetik lagi dengan papan ketik anda, bisa jadi anda tanpa sengaja mengganti penggerak papan ketik anda dengan *bootloader*. Hal ini bisa terjadi bila papan ketik tidak sedang dalam mode *bootloader*. Anda dapat mengkonfirmasi hal ini secara mudah pada Zadig. Sebuah papan ketik yang normal memiliki penggerak `HidUsb` terpasang pada semua antar-mukanya.

![A healthy keyboard as seen by Zadig](https://i.imgur.com/Hx0E5kC.png)

Buka *Device Manager* dan cari sebuah piranti yang mirip dengan papan ketik anda.

![The board with the wrong driver installed, in Device Manager](https://i.imgur.com/L3wvX8f.png)

Klik kanan papan ketik tersebut dan tekan ***Uninstall device***. Dan jangan lupa untuk memastikan untuk mencentang ***Delete the driver software for this device*** terlebih dahulu.

![The Device Uninstall dialog, with the "delete driver" checkbox ticked](https://i.imgur.com/aEs2RuA.png)

Klik ***Action → Scan for hardware changes***. Sekarang, seharusnya anda sudah dapat mengetik kembali. Pastikan pada Zadig bahwa piranti papan ketik menggunakan penggerak `HidUsb`. Bila memang demikian adanya, seharusnya permasalah ini sudah selesai dan papan ketik anda sudah berfungsi sebagaimana mestinya lagi. Bila tidak demikian, mohon ulangi proses sebelumnya sampai Zadig melaporkan penggunaan penggerak yang tepat.

?> Jangan lupa untuk me-*reboot* komputer anda agar Windows memperhatikan perubahan penggerak.

## Daftar *Bootloader* yang Dikenal

Berikut merupakan daftar dari piranti *bootloader* yang dikenal beserta VID dan PIDnya. Tidak lupa dengan penggerak yang sesuai untuk menge-*flash* QMK. Harap catat bahwa penggerak `usbser` dan `HidUsb` sudah termasuk pada Windows dan tidak dapat ditentukan menggunakan Zadig. Bila piranti anda memiliki penggerak yang salah, anda harus menggunakan *Device Manager* untuk melepas pemasangan penggerak tersebut sebagaimana yang sudah dijelaskan pada bagian sebelumnya.

Nama piranti disini merupakan nama yang muncul pada Zadig dan mungkin tidak sama dengan apa yang ditampilkan pada QMK Toolbox maupun Device Manager.

|*Bootloader* |Nama Piranti                  |VID/PID       |Penggerak|
|-------------|------------------------------|--------------|---------|
|`atmel-dfu`  |ATmega16u2 DFU                |`03EB:2FEF`   |libusb0  |
|`atmel-dfu`  |ATmega32U2 DFU                |`03EB:2FF0`   |libusb0  |
|`atmel-dfu`  |ATm16U4 DFU V1.0.2            |`03EB:2FF3`   |libusb0  |
|`atmel-dfu`  |ATm32U4DFU                    |`03EB:2FF4`   |libusb0  |
|`atmel-dfu`  |*none* (AT90USB64)            |`03EB:2FF9`   |libusb0  |
|`atmel-dfu`  |AT90USB128 DFU                |`03EB:2FFB`   |libusb0  |
|`qmk-dfu`    |(nama papan ketik) Bootloader |As `atmel-dfu`|libusb0  |
|`halfkay`    |*none*                        |`16C0:0478`   |HidUsb   |
|`caterina`   |Pro Micro 3.3V                |`1B4F:9203`   |usbser   |
|`caterina`   |Pro Micro 5V                  |`1B4F:9205`   |usbser   |
|`caterina`   |LilyPadUSB                    |`1B4F:9207`   |usbser   |
|`caterina`   |Pololu A-Star 32U4 Bootloader |`1FFB:0101`   |usbser   |
|`caterina`   |Arduino Leonardo              |`2341:0036`   |usbser   |
|`caterina`   |Arduino Micro                 |`2341:0037`   |usbser   |
|`caterina`   |Adafruit Feather 32u4         |`239A:000C`   |usbser   |
|`caterina`   |Adafruit ItsyBitsy 32u4 3V    |`239A:000D`   |usbser   |
|`caterina`   |Adafruit ItsyBitsy 32u4 5V    |`239A:000E`   |usbser   |
|`caterina`   |Arduino Leonardo              |`2A03:0036`   |usbser   |
|`caterina`   |Arduino Micro                 |`2A03:0037`   |usbser   |
|`bootloadHID`|HIDBoot                       |`16C0:05DF`   |HidUsb   |
|`USBasp`     |USBasp                        |`16C0:05DC`   |libusbK  |
|`apm32-dfu`  |APM32 DFU ISP Mode            |`314B:0106`   |WinUSB   |
|`stm32-dfu`  |STM32 BOOTLOADER              |`0483:DF11`   |WinUSB   |
|`kiibohd`    |Kiibohd DFU Bootloader        |`1C11:B007`   |WinUSB   |
|`stm32duino` |Maple 003                     |`1EAF:0003`   |WinUSB   |
