# Sering Ditanya Rupa-Rupa

## Bagaimana Saya Mengetes Papan Ketik Saya? :id=testing

Mengetes papan ketik anda biasanya sangat mudah. Ketuk setiap tombol dan pastikan tombol tersebut mengirim kode tombol yang anda harapkan. Anda bisa menggunakan mode tes [Konfigurator QMK](https://config.qmk.fm/#/test/) untuk memeriksa papan ketik anda, walaupun papan ketik tersebut tidak menjalankan QMK.

## Pertimbangan Keselamatan

Kemungkinan besar anda tidak ingin papan ketik anda "*brick*" yang membuat tidak mungkin untuk menulis ulang perangkat tegar ke papan ketik tersebut. Berikut ada beberapa hal yang mungkin terlalu berisiko.

- Bila papan ketika anda tidak memiliki tombol RESET, maka untuk memindahkan mode papan ketik ke DFU, anda harus mengetuk tombol fisik yang ada pada PCB. Hal ini berarti anda harus melepas sekrup pada bagian bawah.
- Bermain-main dengan `tmk_core` ataupun berkas berkas yang berkaitan bisa jadi membuat papan ketik tidak dapat digunakan.
- Berkas `.hex` yang terlalu besar bisa menyebabkan masalah. `make dfu` akan menghapus blok memori, mengetes ukuran (urutan yang salah), yang menghasilkan galat dan menyebabkan gagal *flash* dan pada akhirnya papan ketik akan berada pada mode DFU tanpa tindak lanjut.
  - Pastikan ukuran maksimal berkas `.hex` pada Planck dlsb adalah 7000h (28672 desimal).

```
Linking: .build/planck_rev4_cbbrowne.elf                                                            [OK]
Creating load file for Flash: .build/planck_rev4_cbbrowne.hex                                       [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22396       0   22396    577c planck_rev4_cbbrowne.hex
```

  - Ukuran berkas diatas adalah 22396/577ch yang berarti kurang dari 28672/7000h
  - Selama anda memiliki berkas `.hex` alternatif untuk papan ketik yang sama, anda bisa menggunakannya.
  - Beberapa opsi yang mungkin anda tentukan pada berkas `Makefile` untuk papan ketik anda, misalkan `BOOTMAGIC_ENABLE`, `MOUSEKEY_ENABLE`, `EXTRAKEY_ENABLE`, `CONSOLE_ENABLE`, `API_SYSEX_ENABLE`, akan menggunakan memori lebih.
- Peralatan-peralatan yang menyangkut DFU /tidak/ memperkenankan anda untuk menulis secara langsung ke *bootloader*, sehingga risiko yang anda hadapi tidak terlalu besar.
- EEPROM memiliki umur hidup 100.000 siklus tulis. Anda tidak seharusnya menulis ulang piranti tegar berulang-ulang dan terus-menerus. Hal semacam itu akan membunuh EEPROM cepat atau lambat.

## NKRO Tidak Berfungsi
Hal pertama kali yang harus anda lakukan adalah menambah opsi `NKRO_ENABLE` pada **`Makefile`**

Coba perintah `Magic` **N** (bawaan merupakan `LShift+RShift+N`) saat **NKRO** masih tidak berfungsi. Anda dapat menggunakan perintah ini untuk beralih sementara ke mode **NKRO** maupun **6KRO**. Pada beberapa keadaan dimana **NKRO** tidak berfungsi dan anda masih harus berpindah ke mode **6KRO**, misalkan saat anda berada pada BIOS.

Bila perangkat tegar anda dibangun menggunakan opsi `BOOTMAGIC_ENABLE`, anda harus menyalakannya secara manual dengan perintah `BootMagic` **N** (bawaan merupakan `Space+N`). Pengaturan ini tersimpan pada EEPROM dan terbawa setelah siklus nyala-mati.

https://github.com/tmk/tmk_keyboard#boot-magic-configuration---virtual-dip-switch


## TrackPoint Membutuhkan Sirkuit Reset (Dukungan Tetikus PS/2)

Tanpa sirkuit reset, anda akan mendapatkan hasil yang tidak konsisten karena inisialisasi perangkat keras yang tidak tepat. Silakan lihat skematik sirkuit TPM754:

- https://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- https://www.mikrocontroller.net/attachment/52583/tpm754.pdf


## Tidak Dapat Membaca Matriks diatas 16.

Gunakan `1UL<<16` (bukan `1<<16`) pada `read_cols()` pada [matrix.h] bila kolom yang anda gunakan lebih dari 16.

Pada C, `1` merupakan salah satu data tipe [int] yang merupakan [16 bit] dalam konteks AVR. Jadi, anda tidak dapat menggeser data ke kiri lebih dari 15. Sehingga, perhitungan `1<<16` akan menghasilkan 0. Untuk menyiasati hal ini, anda harus menggunakan tipe data [unsigned long] dengan `1UL`.

https://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279

## Tombol Tambahan Khusus Tidak Berfungsi (Tombol Sistem dan Pengendali Audio)

You need to define `EXTRAKEY_ENABLE` in `rules.mk` to use them in QMK.
Untuk menggunakannya pada QMK, anda harus menetapkan `EXTRAKEY_ENABLE` pada `rules.mk`.

```
EXTRAKEY_ENABLE = yes          # Audio control and System control
```

## Wake from Sleep Doesn't Work

Pada Windows, centang pengaturan `Allow this device to wake the computer` pada label **Power Management** di **Device Manager**. Juga pastikan untuk memeriksa pengaturan BIOS anda. Pengetukan tombol manapun saat *sleep* seharusnya menyalakan inang.

## Menggunakan Arduino?

**Harap diperhatikan bahwa skema penamaan Arduino berbeda dengan skema penamaan *chip* yang sebenarnya.** Sebagai contoh, pin Arduino `D0` bukan merupakan `PD0` pada ATMega32u4. Periksa sirkuit dan skematiknya.

- https://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- https://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Arduino Leonardo dan micro menggunakan **ATMega32U4** dan dapat digunakan untuk TMK, walaupun *bootloader* Arduino bisa jadi masalah.

## Menyalakan JTAG

Secara bawaan, antarmuka pengawakutuan JTAG dimatikan sesaat setelah papan ketik menyala. Kontroler mikro yang mampu menggunakan JTAG dikirim oleh produsen dengan tambahan set sekring `JTAGEN` dengan mengambil alih pin-pin tertentu pada kontroler mikro yang digunakan oleh papan ketik untuk matriks tombol, LED, dll.

Bila anda tetap ingin menggunakan JTAG, tambahkan baris berikut pada `config.h` anda:

```c
#define NO_JTAG_DISABLE
```

## Kompatibilitas USB 3

Beberapa masalah dapat diselesaikan dengan menggunakan porta USB 2.0, bukan USB 3.x.


## Kompatibilitas Mac
### OS X 10.11 dan Hub
Lihat sini: https://geekhack.org/index.php?topic=14290.msg1884034#msg1884034


## Masalah pada BIOS (UEFI), Setup/Resume (*Sleep* & *Wake*) Siklus Nyala

Beberapa orang melaporkan bahwa papan ketik mereka tidak berfungsi pada BIOS dan/atau setelah *resume* (siklus nyala).

Sayangnya, saat dokumen ini dibuat, akar dari permasalahan tersebut masih belum jelas. Namun, beberapa opsi bangun agaknya berhubungan dengan masalah tersebut. Pada `Makefile`, silakan coba untuk menon-aktifkan opsi seperti `CONSOLE_ENABLE`, `NKRO_ENABLE`, `SLEEP_LED_ENABLE`, dan/atau lainnya.

Info lebih lanjut:
- https://github.com/tmk/tmk_keyboard/issues/266
- https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778
