# Tombol Pemuka: *Modifier* Baru

Bila anda pernah menggunakan VIm, tentu anda tahu apa itu tombol pemukan. Namun, bila tidak, anda akan mendapati sebuah konsep yang sangat menarik. Sebagai contoh, anda tidak perlu menekan *Alt+Shift+W* (menekan tiga tombol bersamaan) namun anda hanya perlu menekan _rentetan_ tombol. Jadi anda hanya perlu menekan *modifier* khusus kami (tombol pemuka), diikut dengan W dan C (atau hanya rentetan cepat) dan sesuatu akan terjadi.

Hal semacam itulah yang dilakukan oleh `KC_LEAD`. Berikut contohnya:

1. Pilih sebuah tombol pada papan ketik anda yang ingin anda gunakan sebagai tombol Pemuka. Tetapkan tombol ini agar menggunakan `KC_LEAD`. Tombol ini akan didedikasikan hanya untuk fitur ini.
2. Ikut sertakan baris `#define LEADER_TIMEOUT 300` pada `config.h` anda. Pengikutsertaan ini mengatur tenggat waktu untuk tombol `KC_LEAD`. Bila anda menekan tombol `KC_LEAD` anda hanya memiliki waktu tertentu untuk menyelesaikan rentetan tombol pemuka. `300` disini mengatur waktu tersebut ke 300milidetik dan anda dapat mengaturnya sesuai dengan kebutuhan anda. Namun, semua tombol yang ditekan pada waktu ini akan dicegat (tidak akan dikirim), sehingga anda pada umumnya menginginkan nilai tersebut agak rendah.
   * Secara bawaan, nilai ini merupakan lamanya setelah anda menekan `KC_LEAD` untuk menyelesaikan seluruh rentetan anda. Lama penyelesaian ini bisa sangat cepat bagi beberapa orang. Jadi, anda mungkin berminat untuk meningkatkan jeda ini. Cara lain adalah dengan menyalakan opsi `LEADER_PER_KEY_TIMING` yang mereset jeda setiap sebuah tombol diketuk. Opsi ini memperkenankan anda untuk menggunakan nilai jeda yang rendah namun tetap dapat menggunakan rentetan lebih panjang. Untuk menyalakan opsi ini, tambahkan `#define LEADER_PER_KEY_TIMING` ke `config.h` anda.
3. Pada fungsi `matrix_scan_user`, tambahkan sesuatu yang mirip seperti berikut:

```c
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // Apapun yang dapat anda lakukan dengan makro
      SEND_STRING("QMK unyu aned uwuwuwuwuwu");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
```

Sebagaimana yang anda lihat, anda memiliki beberapa fungsi. Anda dapat menggunakan `SEQ_ONE_KEY` untuk rentetan satu tombol (tombol pemuka diikut hanya satu tombol), `SEQ_TWO_KEYS`, `SEQ_THREE_KEYS`, `SEQ_FOUR_KEYS`, dan `SEQ_FIVE_KEYS`.

Setiap fungsi tadi, menerima satu atau lebih argumen. Yang patut anda perhatikan adalah, anda dapat menggunakan kode tombol pada ***layer* manapun pada papan ketik anda**. Tentunya *layer* tersebut harus aktif terlebih dahulu.

## Menambah Dukungan Tombol Pemuka pada `rules.mk`

Untuk menambah dukungan untuk tombol pemuka, anda hanya perlu menambah satu barus pada `rules.mk` tata letak anda.

```make
LEADER_ENABLE = yes
```

## Pengaturan Waktu Tiap Tombol pada Tombol Pemuka

Rather than relying on an incredibly high timeout for long leader key strings or those of us without 200wpm typing skills, we can enable per key timing to ensure that each key pressed provides us with more time to finish our stroke. This is incredibly helpful with leader key emulation of tap dance (read: multiple taps of the same key like C, C, C).
Anda dapat menggunakan tenggat waktu per tombol agar dapat memastikan tiap tombol dapat ditekan untuk menyelesaikan rentetan anda. Pengaturan ini sangat berguna dengan emulasi 

Untuk mengaktifkan pengaturan ini, tambahkan baris berikut pada `config.h` anda:
```c
#define LEADER_PER_KEY_TIMING
```

Setelah itu, disarankan untuk menurunkan nilai `LEADER_TIMEOUT` lebih rendah dari 300milidetik.

```c
#define LEADER_TIMEOUT 250
```

Sekarang, hal semacam ini tidak terasa tidak mungkin tanpa tenggat waktu 1000milidetik.

```c
SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
  SEND_STRING("tenggat waktu per tombol enak aned!!!");
}
```

## Pemrosesan Tombol Secara Tegas

Secara bawaan, fitur tombol pemuka akan menyaring kode tombol dari [Mod-Ketuk](id/mod_tap.md) dan [*Layer*-Ketuk](id/feature_layers.md#switching-and-toggling-layers) saat memeriksa rentetan tombol pemuka. Hal ini berarti bila anda menggunakan `LT(3, KC_A)`, fitur tombol pemuka akan memilih `KC_A` untuk rentetan yang digunakan, bukan `LT(3, KC_A)`. Hal ini memberikan jaminan pada pengguna baru mengenai perilaku yang mudah ditebak.

Walaupun hal semacam ini baik baik saja pada kondisi pada umumnya, bila anda ingin menggunakan kode tombol seutuhnya (misalkan `LT(3, KC_A)` dari contoh di atas) pada rentetan yang anda gunakan, anda dapat melakukan hal itu dengan menambah `#define LEADER_KEY_STRICT_KEY_PROCESSING` pada `config.h` anda. Pendefinisian tadi akan menon-aktifkan penyaringan dan anda harus menentukan kode tombol seutuhnya (mis. `LT(3, KC_A)`).

## *Customization*

Fitur tombol pemuka memiliki beberapa kustomasi tambahan menyoal bagaimana fitur ini berfungsi. Fitur ini memiliki dua fungsi yang dapat dipanggil pada bagian tertentu dari proses. Keduanya adalah `leader_start()` dan `leader_end()`.

Fungsi `leader_start()` dipanggil ketika anda mengetuk tombol `KC_LEAD` dan fungsi `leader_end()` dipanggil saat rentetan pemuka selesai atau tenggat waktu sudah habis.

Anda dapat menambah fungsi-fungsi berikut pada kode anda (biasanya `keymap.c`) untuk menambah umpan balik dari rentetan pemuka (mis. bunyi bunyian atau musik).

```c
void leader_start(void) {
  // rentetan dimulai
}

void leader_end(void) {
  // rentetan selesai
}
```

### Contoh

Contoh ini akan memainkan suara "One Up" pada gim Mario saat anda menekan `KC_LEAD` untuk memulai rentetan pemuka. Selain itu, contoh juga akan memainkan "All Star" bila anda berhasil menyelesaikan rentetan atau memainkan "Rick Roll" bila anda gagal.

```c
bool did_leader_succeed;
#ifdef AUDIO_ENABLE
float leader_start[][2] = SONG(ONE_UP_SOUND );
float leader_succeed[][2] = SONG(ALL_STAR);
float leader_fail[][2] = SONG(RICK_ROLL);
#endif
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    SEQ_ONE_KEY(KC_E) {
      // Anything you can do in a macro.
      SEND_STRING(SS_LCTL(SS_LSFT("t")));
      did_leader_succeed = true;
    } else 
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
      did_leader_succeed = true;
    }
    leader_end();
  }
}

void leader_start(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start);
#endif
}

void leader_end(void) {
  if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_succeed);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_fail);
#endif
  }
}
```
