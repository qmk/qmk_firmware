# Soal Sering Ditanyakan Dalam Membangun QMK

Laman ini meliputi pertanyaan pertanyaan mengenai pembangunan QMK. Bila anda belum membaca panduan [Pengaturan Lingkungan Bangun](id/getting_started_build_tools.md) dan [Instruksi *Make*](id/getting_started_make_guide.md), silakan anda baca kedua laman terlebih dahulu.

## Tidak Dapat Memprogram pada Linux

Anda membutuhkan permisi khusu untuk mengoperasikan sebuah piranti. Untuk pengguna Linux, silakan lihat instruksi terkait aturan aturan `udev` berikut. Bila anda masih mengalami masalah dengan `udev`, salah satu cara pintasnya adalah dengan menggunakan `sudo`. Bila anda tidak familiar dengan perintah ini, silakan membaca manual dengan `man sudo` atau lihat [laman berikut](https://linux.die.net/man/8/sudo).

Contoh dalam menggunakan `sudo` bila kontroller mikro yang anda gunakan adalah ATMega32u4:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

atau:

    $ sudo make <keyboard>:<keymap>:flash

Dan harap diperhatikan bahwa menjalankan `make` dengan `sudo` biasanya ***tidak*** disarankan dan anda diharapkan untuk menggunakan metoda bagian awal bila memungkinkan.

### Aturan `udev` pada Linux :id=linux-udev-rules

Pada Linux, anda membutuhkan privilese yang sesuai untuk berkomunikasi dengan *bootloader* piranti. Anda dapat menggunakan `sudo` saat menge-*flash* perangkat tegar (walaupun tidak kami rekomendasikan) atau menyalin [berkas ini](https://github.com/qmk/qmk_firmware/tree/master/util/udev/50-qmk.rules) ke `/etc/udev/rules.d/`.

Setelah anda tambahkan, jalankan perintah berikut:

```
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**Catatan:** Versi lama dari ModemManager (<1.12) hanya memungkinkan penyaringan pada mode tegas. Perintah berikut dapat memutakhirkan pengaturan tersebut:

```
printf '[Service]\nExecStart=\nExecStart=/usr/sbin/ModemManager --filter-policy=default' | sudo tee /etc/systemd/system/ModemManager.service.d/policy.conf
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
```

### Perangkat serial tidak terdeteksi pada moda *bootloader* pada Linux
Make sure your kernel has appropriate support for your device. If your device uses USB ACM, such as
Pro Micro (Atmega32u4), make sure to include `CONFIG_USB_ACM=y`. Other devices may require `USB_SERIAL` and any of its sub options.
Pastikan kernel anda memiliki dukungan yang layak untuk piranti anda. Bila piranti anda menggunakan USB ACM, seperti Pro Micro (ATMega32u4), maka pastikan untuk mengikutsertakan `CONFIG_USB_ACM=y`. Piranti lain mungkin membutuhkan `USB_SERIAL` dan semua sub-pilihannya.

## Piranti Tidak Dikenal untuk *Bootloader* DFU

Permasalah yang sering ditemui saat menge-*flash* papan ketik pada Windows biasanya terjadi karena pemasangan penggerak yang salah untuk *bootloader*. Bisa juga malah tidak terpasang sama sekali.

Menjalankan ulang skrip pemasangan QMK (`./util/qmk_install.sh` dari direktori `qmk_firmware` pada MSYS2 atau WSL) atau memasang ulang QMK Toolbox bisa jadi menyelesaikan masalah. Cara lain adalah anda mengunduh dan menjalankan [`qmk_driver_installer`](https://github.com/qmk/qmk_driver_installer) secara manual.

Bila masih tidak dapat mengenali piranti, maka anda perlu mengunduh dan menjalankan Zadig. Lihat [Pemasangan Penggerak *Bootloader* dengan Zadig](id/driver_installation_zadig.md) untuk keterangan lebih lanjut.

## USB VID dan PID
Anda dapat menggunakan ID manapun yang anda inginkan dengan menyunting `config.h`. Penggunaan ID yang, kiranya, tidak digunakan bisa jadi tidak bermasalah.

Kebanyakan papan ketik yang menggunakan QMK menggunakan `0xFEED` sebagai ID vendor. Anda harus melihat papan ketik lain bila anda ingin menggunakan ID produk yang unik.

Juga lihat tautan berikut.
https://github.com/tmk/tmk_keyboard/issues/150

Anda juga dapat membeli VID:PID yang unik disini. Walaupun kami kira, anda tidak tidak perlu melakukannya untuk kebutuhan personal.
- https://www.obdev.at/products/vusb/license.html
- https://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

### Saya baru saja menge-*flash* papan ketik saya dan sekarang papan ketik tersebut tidak mengirimkan apapun saat ditekan - papan ketik tersebut juga menggunakan ARM (planck revisi 6, clueboard60, hs60v2, dll...) (Februari 2019) 
Dikarenakan cara kerja EEPROM pada chip berbasis ARM, pengaturan yang tersimpan bisa jadi tidak lagi valid. Hal ini berpengaruh pada *layer* bawaan, dan *bisa jadi*, pada situasi yang masih kami pelajari, membuat papan ketik tidak lagi dapat digunakan. Melakukan reset pada EEPROM akan membenahi situasi ini.

[Planck rev6 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) dapat digunakan untuk memaksa reset pada eeprom. Setelah menge-*flash* citra ini, *flash* perangkat tegar anda lagi yang seharusnya mengembalikan papan ketik anda ke kondisi _normal_.
[Preonic rev3 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

Bila *bootmagic* difungsikan dalam bentuk apapun (*full* atau *lite*), anda seharusnya dapat menggunakan langkah langkah yang ada pada [dokumentasi *Bootmagic*](id/feature_bootmagic.md).