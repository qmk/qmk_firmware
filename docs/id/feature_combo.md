# Kombo

Fitur kombo merupakan solusi pengetikan seperti akord / kunci pada gitar untuk menambahkan aksi khusus. Fitur ini memperkenankan anda untuk menekan beberapa tombol bersamaan dan menghasilkan efek yang berbeda. Sebagai contoh, menekan `A` dan `S` secara bersamaan dalam tenggat waktu tertentu, akan mengirimkan `ESC` atau bahkan hal hal kompleks lainnya.

Untuk mengaktifkan fitur ini, anda harus menambah `COMBO_ENABLE = yes` pada `rules.mk` anda.

Sebagai tambahan, pada `config.h`, anda harus menentukan jumlah kombo yang akn anda gunakan dengan menambah `#define COMBO_COUNT x` dimana `x` merupakan jumlah kombo yang akan anda gunakan.
<!-- At this time, this is necessary -->

Dan juga, secara bawaan, tempo pengetukan untuk kombo disamakan dengan nilai `TAPPING_TERM` (bawaan 200 pada banyak papan ketik). Namun anda dapat menentukan nilai yang berbeda dengan mendefinisikannya pada `config.h` anda. Sebagai contoh, `#define COMBO_TERM 300` akan mengatur tenggat waktu untuk kombo ke 300 mili detik.

Lalu, pada berkas `keymap.c` anda, anda harus mendefinisikan rentetan tombol yang diakhiri dengan `COMBO_END` dan sebuah struktur untuk mendaftar semua kombinasi tombol dan aksi keluarannya.

```c
const uint16_t PROGMEM test_combo[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, KC_ESC)};
```

Kode tersebut mengirim `Escape` bila anda menekan tombol `A` dan `B` pada waktu yang kurang lebih bersamaan.

!> Cara ini hanya bisa mengirim [kode tombol dasar](id/keycodes_basic.md). Lihat contoh untuk penggunaan lebih lanjut.

## Contoh

Bila anda ingin memiliki beberapa kombo yang, anda seharusnya menggunakannya seperti berikut:

```c
enum combos {
  AB_ESC,
  JK_TAB
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB)
};
```

Untuk implementasi yang lebih mendalam dan rumit, anda dapat menggunakan fungsi `process_combo_event` untuk menambah penanganan khusus pada kode anda.

```c
enum combo_events {
  ZC_COPY,
  XV_PASTE
};

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case ZC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}
```

Kode di atas akan mengirim `Ctrl+C` bila anda menekan `Z` dan `C`, `Ctrl+V` bila anda menekan `X` dan `V`. Anda juga dapat mengubah kode tersebut untuk berpindah *layer*, memainkan suara, ataupun mengubah pengaturan.

## Konfigurasi Tambahan

Bila anda menggunakan kombo yang panjang, anda akan mungkin mengalami beberapa permasalahan yang disebabkan karena struktur data yang digunakan oleh fitur ini tidak cukup.

Maka dari itu, anda dapat menggunakan `#define EXTRA_LONG_COMBOS`  atau `#define EXTRA_EXTRA_LONG_COMBOS`  pada berkas `config.h` anda.

Anda juga dapat mengaktifkan tombol aksi dengan mendefinisikan `COMBO_ALLOW_ACTION_KEYS`.

## Kode Tombol

Anda dapat mengaktifkan, menonaktifkan, ataupun memindah fitur saat papan ketik sedang digunakan. Hal ini berguna bila anda ingin mematikan fitur ini sementara misalkan saat memainkan gim.

|Kode Tombol |Deskripsi                        |
|------------|---------------------------------|
|`CMB_ON`    |Nyalakan fitur kombo             |
|`CMB_OFF`   |Matikan fitur kombo              |
|`CMB_TOG`   |Pindah fitur kombo (nyala/mati)  |

## Fungsi yang dapat digunakan pengguna 

Sebagai tambahan dari kode tombol di atas, ada beberapa fungsi yang bisa anda gunakan untuk mengatur atau memeriksa status dari fitur ini:

|Fungsi                |Deskripsi                                               |
|----------------------|--------------------------------------------------------|
| `combo_enable()`     | Nyalakan fitur kombo                                   |
| `combo_disable()`    | Matikan fitur kombo dan bersihkan boper kombo          |
| `combo_toggle()`     | Pindah status fitur kombo                              |
| `is_combo_enabled()` | Kembalikan status fitur kombo (`true` atau `false`)    |
