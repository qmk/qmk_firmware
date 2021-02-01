# Menge-*flash* Papan Ketik Anda

Setelah anda membangun perangkat tegar *custom* anda, anda mungkin ingin menge-*flash* papan ketik anda. 

## Pindah Papan Ketik Anda Ke Mode DFU (*Bootloader*)

Agar anda dapat menge-*flash* perangkat tegar *custom* and, anda harus mengubah papan ketik anda ke mode *flash* khusus. Saat pada mode ini, anda tidak akan dapat menggunakannya. Hal yang wajib diperhatikan adalah, anda tidak boleh melepas sambungan papan ketik anda dari komputer agar proses *flash* tidak terinterupsi.

Yang patut diperhatikan adalah, papan ketik yang berbeda, memiliki cara yang berbeda agar dapat berpindah ke moda khusus ini. Bila PCB anda menjalankan QMK, TMK, atau PS2AVRGB (Bootmapper Client) dan anda tidak diberikan instruksi khusus, coba langkah-langkah berikut, secara runut:

* Tahan kedua tombol *shift* dan tekan `Pause`
* Tahan kedua tombol *shift* dan tekan `B`
* Lepas sambungkan papan ketika anda, tekan spasi dan `B` secara bersamaan, lalu sambungkan ke komputer, dan tunggu satu detik sebelum melepas kedua tombol tersebut
* Lepas sambungan papan ketik, anda, tekan tombol kiri yang paling atas atau paling bawah (biasanya Escape atau Kontrol Kiri) dan sambungkan ke komputer
* Tekan tombol  `RESET` fisik, biasanya terletak pada bagian bawah PCB
* Cari pin *header*  pada PCB yang dilabeli dengan `RESET` dan `GND` lalu arus-pendekkan keduanya saat PCB tersambung dengan komputer

Bila anda masih gagal walaupun sudah mencoba langkah-langkah di atas dan *chip* pada papan bertanda `STM32`, maka hal ini akan menjadi lebih rumit. Pada umumnya, langkah yang paling bijak adalah bertanya pada [Discord](https://discord.gg/Uq7gcHh). Sangat mungkin beberapa foto dari papan anda akan diminta. 

Namun, bila papan anda tidak terpasang `STM32`, anda seharusnya akan melihat pesan semacam berikut dengan fonta warna kuning pada QMK Toolbox anda:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
```

dan *bootloader* perangkat ini akan juga muncul pada Device Manager, System Information.app, atau `lsusb`.

## Mengeflash Papan Ketik Anda dengan QMK Toolbox

Cara paling mudah untuk menge-*flash* papan ketik anda adalah dengan menggunakan [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).

However, the Toolbox is currently only available for Windows and macOS. If you're using Linux (or just wish to flash the firmware from the command line), skip to the [Flash your Keyboard from the Command Line](#flash-your-keyboard-from-the-command-line) section.

Namun, saat ini Toolbox tersebut hanya tersedia pada Windows dan macOS. Bila anda menggunakan Linux (atau anda hanya ingin menggunakan perintah baris untuk menge-*flash*), silakan lompati bagian ini menuju [Menge-*flash* Papan Ketik Anda dari Perintah Baris](#flash-your-keyboard-from-the-command-line).

### Muat Berkas ke QMK Toolbox

Mulai dengan menjalankan aplikasi QMK Toolbox. Jangan lupa untuk memindahkah berkas perangkat tegar pada tempat yang mudah dijangkau pada Finder maupun Explorer. Format dari berkas perangkat tegar untuk papan ketik anda merupakan salah satu dar `.hex` atau `.bin`. QMK mencoba untuk menyalin berkas yang tepat untuk papan ketik anda ke direktori *root* `qmk_firmware`.

Bila anda menggunakan Windows maupun macOS, ada perintah yang bisa anda gunakan untuk membuka direktori tempat anda berada saat ini di Explorer maupun Finder.

<!-- tabs:start -->

#### ** Windows **

```
start .
```

#### ** macOS **

```
open .
```

<!-- tabs:end -->

Berkas perangkat tegar selalu mengikuti format penamaan berikut:

```
<nama_papan_ketik>_<nama_tata_letak>.{bin,hex}
```

Sebagai contoh, `planck/rev5` dengan tata letak tombol `default` akan memiliki nama berkas sebagai berikut:

```
planck_rev5_default.hex
```

Setelah anda menemukan berkas perangkat tegar anda, silakan seret berkas tersebut ke kotak "*Local file*" pada QMK Toolbox. Atau, anda juga bisa mengeklik "*Open*" lalu navigasi ke tempat anda menaruh berkas perangkat tegar tadi.

### Menge-*flash* Papan Ketik Anda

Klik tombol `Flash` pada QMK Toolbox. Anda akan melihat keluaran yang mirip seperti berikut:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
*** Attempting to flash, please don't remove device
>>> dfu-programmer.exe atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer.exe atmega32u4 flash "D:\Git\qmk_firmware\gh60_satan_default.hex"
    Checking memory from 0x0 to 0x3F7F...  Empty.
    0%                            100%  Programming 0x3F80 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x3F80 bytes written into 0x7000 bytes memory (56.70%).
>>> dfu-programmer.exe atmega32u4 reset
    
*** DFU device disconnected: Atmel Corp: ATmega32U4 (03EB:2FF4:0000)
```

## Menge-*flash* Papan Ketik Anda dari Baris Perintah

Langkah ini sudah dibuat sedemikian rupa agar jauh lebih mudah bila dibandingkan dengan waktu awal kali proyek ini dimulai. Bila anda sudah siap untuk mengompilasi dan menge-*flash* perangkat tegar anda, buka jendela terminal anda dan jalankan perintah *flash*:

    qmk flash

Bila anda belum mengkonfigurasi papan ketik dan/atau tata letak bawaan anda pada antarmuka baris perintah, atau anda memiliki beberapa papan ketik, anda dapat menentukan papan ketik dan tata letak dengan:

    qmk flash -kb <my_keyboard> -km <my_keymap>

Perintah diatas akan memeriksa konfigurasi papan ketik dan mencoba untuk menge-*flash*-nya berdasarkan *bootloader* yang sudah ditentukan. Hal ini juga berarti anda tidak perlu tahu *bootloader* mana yang digunakan oleh papan ketik anda. Cukup jalankan perintah tadi dan biarkan waktu berbicara.

Namun, konfigurasi semacam ini bergantung atas ditentukannya *bootloader*. Bila pengaturan ini belum ditetapkan atau anda menggunakan papan ketik yang tidak mendukung perintah tadi, anda akan melihat galat semacam ini:

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

Bila hal ini yang terjadi, anda harus menentukan *bootloader* secara manual. Silakan lihat panduan [Menge-*flash* Perangkat Tegar](flashing.md) untuk keterangan lebih lanjut.

## Testing

Saat ini, papan ketik anda sudah diprogram menggunakan perangkat tegar *custom* anda dan anda sudah siap untuk mencobanya.

Bila anda beruntung, semua akan berjalan sesuai dengan harapan. Namun, bila tidak, ada beberapa langkah yang akan membantu anda untuk menentukan apa yang salah.
Testing papan ketik anda biasanya cukup sederhana. Cukup tekan setiap tombol dan pastikan tombol tersebut mengirimkan kode tombol yang diharapkan. Anda bisa menggunakan mode tes [Konfigurator QMK](https://config.qmk.fm/#/test) untuk memeriksa papan ketik anda, walau papan ketik tersebut tidak menggunakan QMK.

Bila masih tidak berfungsi, silakan ramban topik Pertanyaan yang Sering Ditanya atau [mengobrol dengan kami pada Discord](https://discord.gg/Uq7gcHh).