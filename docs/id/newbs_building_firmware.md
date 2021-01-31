# Membangun Perangkat Tegar Pertama Anda

Setelah anda selesai mempersiapkan lingkungan bangun anda, anda siap untuk membangun perangkat tegar *custom*. Pada bab ini, kita akan berpindah pindah antara 3 program yaitu manajer berkas, penyunting teks, dan jendela terminal. Biarkan ketiga program tersebut selalu terbuka sampai anda selesai membangun dan cukup puas dengan hasil perangkat tegar anda.

## Buat Tata Letak Baru

Untuk membuat tata letak anda sendiri, anda harus membuat salinan dari tata letak `default`. Bila anda mengkonfigurasi lingkungan bangun anda pada langkah terakhir sebelumnya, anda dapat menyalin `default` dengan antarmuka baris perintah QMK:

    qmk new-keymap

Bila anda tidak mengkonfigurasi lingkungan bangun anda, atau anda memiliki beberapa papan ketik, anda dapat menetukan nama papan ketik dengan::

    qmk new-keymap -kb <keyboard_name>

Mohon perhatikan keluaran dari perintah sebelumnya. Anda seharusnya akan melihat sesuatu seperti berikut:

    Ψ <nama_pengguna_github> keymap directory created in: /home/me/qmk_firmware/keyboards/clueboard/66/rev3/keymaps/<nama_pengguna_github>

Disitulah letak berkas `keymap.c` anda.

## Buka `keymap.c` Pada Penyunting Teks

Buka berkas `keymap.c` anda pada sebuah penyunting teks. Pada berkas ini, anda akan menemukan struktur yang menentukan bagaimana papan ketik anda berjalan. Pada bagian atas `keymap.c`, bisa jadi, ada beberapa `#define` dan `enum` yang membuat tata letak lebih mudah dibaca. Lebih lanjut ke bawah, anda akan menemukan sebuah baris yang mirip seperti berikut: 

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

Baris inilah yang mengindikasikan dimana *layer* dimulai. Pada bagian bawahnya, anda akan menumkan beberapa baris yang berisi `LAYOUT`. Baris-baris ini lah yang mengindikasikan mulainya sebuah *layer*. Di bawah baris itu merupakan senarai tombol yang berkumpul menjadi sebuah *layer* tertentu.

!> Saat anda menyunting berkas tata letak, harap berhati-hati dengan tidak menambah maupun mengurangi koma sembarangan. Bila anda telanjur mengubah, hal ini dapat menggagalkan kompilasi perangkat tegar anda. Terlebih lagi, mencari dimana letak koma yang hilang ataupun berlebih agak menjemukan.

## Sesuaikan Tata Letak Seperti Yang Anda Inginkan

Untuk menyelesaikan langkah ini, sangat bergantung dengan anda. Ubah satu bagian yang mengganggu atau buat ulang semuanya. Anda dapat menghapus *layer* bila anda tidak menggunakannya. Bisa juga anda menambah *layer* hingga 32 *layer*. QMK memiliki banyak fitur yang bisa anda eksplorasi pada batang samping bagian "Menggunakan QMK". Untuk memulai, berikut beberapa fitur yang mudah digunakan:

* [Kunci Tombol Dasar](id/keycodes_basic.md)
* [Kunci Tombol Quantum](id/quantum_keycodes.md)
* [*Grave/Escape*](id/feature_grave_esc.md)
* [Tombol Tetikus](id/feature_mouse_keys.md)

?> Bila anda sedang membiasakan diri dengan cara kerja tata letak, usahakan agar setiap perubahan pada tata letak anda tidak terlalu banyak. Perubahan yang sangat banyak akan membuat proses pengawakutuan menjadi lebih susah.

## Build Your Firmware :id=build-your-firmware
## Bangun Perangkat Tegar Anda :id=build-your-firmware

Setelah semua perubahan yang anda lakukan pada tata letak sudah selesai, anda harus membangun perangkat tegar tersebut. Untuk melakukan hal tersebut, silakan anda kembali ke jendela terminal dan jalankan perintah kompilasi berikut:

    qmk compile

Bila anda tidak mengkonfigurasi lingkungan anda, atau anda memiliki beberapa papan ketik, anda dapat menentukan papan ketik dan/atau tata letak:

    qmk compile -kb <keyboard> -km <keymap>

Saat kompilasi terjadi, anda akan melihat banyak keluaran pada layar yang menginformasikan anda tentang berkas mana saja yang sedang dikompilasi. Proses ini seharusnya berakhir dengan keluaran mirip seperti berikut:

```
Linking: .build/planck_rev5_default.elf                                                             [OK]
Creating load file for flashing: .build/planck_rev5_default.hex                                     [OK]
Copying planck_rev5_default.hex to qmk_firmware folder                                              [OK]
Checking file size of planck_rev5_default.hex                                                       [OK]
 * The firmware size is fine - 27312/28672 (95%, 1360 bytes free)
```

## *Flash* Perangkat Tegar Anda

Mohon untuk membuka [*flashing* perangkat tegar](id/newbs_flashing.md) untuk belajar bagaimana membakar perangkat tegar anda ke papan ketik anda.
