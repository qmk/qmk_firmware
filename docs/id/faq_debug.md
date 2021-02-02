# Sering Ditanya Pengawakutuan

Laman ini memperjelas beberapa pertanyaan umum yang sering ditanyakan pengguna saat melakukan *troubleshoot* pada papan ketik mereka.

# Pengawakutuan :id=debugging

Papan ketik anda akan memberikan informasi keluaran bila anda menyalakan `CONSOLE_ENABLE = yes` pada `rules.mk` anda. Secara bawaan, keluaran dari pengaturan ini sangat terbatas, namun anda dapat menyalakan mode pengawakutuan untuk meningkatkan informasi yang dikeluarkan. Gunakan kode tombol `DEBUG` pada tata letak anda dan juga gunakan fitur [Perintah](id/feature_command.md) untuk menyalakan mode pengawakutuan. Atau, tambahkan baris-baris kode berikut ke tata letak anda.

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

## Peralatan-Peralatan Pengawakutuan

Ada dua peralatan yang berbeda yang dapat anda gunakan untuk megawakutu papan ketik anda.

### Pengawakutuan Dengan QMK Toolbox

Untuk platform yang didukung, [QMK Toolbox](https://github.com/qmk/qmk_toolbox) dapat digunakan untuk menunjukkan pesan pengawakutuan dari papan ketik anda.

### Pengawakutuan dengan `hid_listen`

Bilamana anda memilih solusi berbasis terminal, anda dapat menggunakan [`hid_listen`](https://www.pjrc.com/teensy/hid_listen.html) yang disediakan oleh PJRC untuk menampilkan pesan-pesan pengawakutuan. Berkas biner yang sudah terbangun untuk Windows, macOS, dan Linux juga tersedia.

## Mengirim Pesan Pengawakutuan Anda Sendiri

Ada kalanya, mencetak pesan pengawakutuan dari [kode *custom*](id/custom_quantum_functions.md) yang anda tulis sendiri juga berguna. Untuk melakukan hal tersebut cuku mudah. Cukup dimulai dengan menambah `print.h` pada bagian atas berkas tata letak anda (`keymap.c`):

```c
#include "print.h"
```

Setelah it, anda dapat menggunakan beberapa fungsi cetak yang berbeda:

* `print("string")`: Cetak string sederhana
* `uprintf("%s string", var)`: Cetak string terformat
* `dprint("string")`: Cetak string sederhana namun hanya jika mode pengawakutuan diaktifkan
* `dprintf("%s string", var)`: Cetak string terformat namun hanya jika mode pengawakutuan dinyalakan

## Contoh-contoh pengawakutuan

Berikut merupakan kumpulan contoh pengawakutuan yang digunakan di dunia nyata. Sebagai informasi utama, silakan mengacu pada [Pengawakutuan dan/atau *Troubleshoot* QMK](id/faq_debug.md).

### Pada posisi matriks mana penekanan tombol ini?

Saat melakukan porting maupun saat melakukan diagnosis terhadap masalah pcb, mengetahui apakah sebuah penankanan tombol benar benar dipindai dengan benar. Untuk menyalakan pencatatan log pada skenario ini, beberapa baris kode berikut pada `keymap.c` tata letak anda

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, kolom: %u, baris: %u, tertekan: %b, waktu: %u, interupsi: %b, jumlah: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}
```

Contoh keluaran
```text
Waiting for device:.......
Listening:
KL: kc: 169, kolom: 0, baris: 0, tertekan: 1
KL: kc: 169, kolom: 0, baris: 0, tertekan: 0
KL: kc: 174, kolom: 1, baris: 0, tertekan: 1
KL: kc: 174, kolom: 1, baris: 0, tertekan: 0
KL: kc: 172, kolom: 2, baris: 0, tertekan: 1
KL: kc: 172, kolom: 2, baris: 0, tertekan: 0
```

### Berapa lama waktu yang dibutuhkan untuk memindai sebuah penekanan tombol?

Saat memeriksa masalah performa, diketahuinya frekuensi pemindaian matriks tombol bisa sangat berguna. Untuk menyalakan pencatatan log pada skenario ini, tambahkan kode berikut pada `config.h` tata letak anda

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Contoh keluaran
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```

## `hid_listen` Tidak mengenali piranti

Saat konsol pengawakutuan piranti anda tidak siap, anda akan melihat hal semacam ini:

```
Waiting for device:.........
```

Setelah piranti disambungkan dan *hid_listen* menemukannya, anda akan mendapatkan pesan sebagai berikut:

```
Waiting for new device:.........................
Listening:
```

Bila anda tidak bisa mendapatkan pesan 'Listening:', silakan coba membangun perangkat tegar anda dengan `CONSOLE_ENABLE=yes` pada [Makefile] anda.

Mungkin anda juga membutuhkan privilese khusu untuk mengakses piranti pada sistem operasi sepert Linux. Silakan coba `sudo hid_listen`.

## Can't Get Message on Console
## Tidak Menerima Pesan pada Konsol
Periksa:
- *hid_listen* melihat piranti anda. Lihat diatas.
- Nyalakan pengawakutuan dengan menekan **Magic**+d. Lihat [*Magic Commonads*](https://github.com/tmk/tmk_keyboard#magic-commands).
- Set `debug_enable=true`. Lihat [Pengawakutuan](#debugging)
- Coba gunakan fungsi `print`, bukan *debug print*. alihat **common/print.h**.
- Lepaskan sambungan piranti lain yang juga memiliki fungsi konsol. Lihat [*Issue* #97](https://github.com/tmk/tmk_keyboard/issues/97).
