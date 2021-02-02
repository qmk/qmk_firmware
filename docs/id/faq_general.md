# Soal Sering Ditanya

## Apa itu QMK?

[QMK](https://github.com/qmk), merupakan kependekan dari *Quantum Mechanical Keyboard*, merupakan kelompok orang orang yang membangun peralatan untuk papan ketik *custom*. Kami memulai dengan [perangkat tegar QMK](https://github.com/qmk/qmk_firmware) yang merupakan cabang dari [TMK](https://github.com/tmk/tmk_keyboard).

## Saya Tidak Tahu Mulai Dari Mana!

Bila begitu adanya, maka anda harus memulai dengan [Panduan Pemula](id/newbs). Ada banyak informasi yang bagus disana dan dokumentasi tersebut mencakup semua yang anda butuhkan untuk memulai.

Bila masih mengalami masalah, silakan gunakan [Konfigurator QMK](https://config.qmk.fm). Konfigurator tersebut akan mengurus hampir semua yang anda butuhkan.

## Bagaimana Saya Menge-*flash* Perangkat Tegar Yang Sudah Saya Bangun?

Pertama, silakan buka [Laman Sering Ditanya Kompilasi dan/atau Penge-*flash*-an](id/faq_build.md). Ada banyak informasi menyangkut permasalahan adan penyelesaian yang umum disana.

## Bilamana Saya Memiliki Masalah Yang Tidak Ada Disini?

Tentu bukan menjadi soal. Silakan [buka laman masalah kami pada GitHub](https://github.com/qmk/qmk_firmware/issues) untuk memeriksa apakah ada orang lain yang mengalami hal yang sama. Namun, pastikan permasalahan anda tidak sekedar mirip, tetapi benar benar sama.

Bila anda tidak dapat menemukan apapun, silakan buka [masalah baru](https://github.com/qmk/qmk_firmware/issues/new)!

## Bilamana Saya Menemukan Kutu?

Lalu buka sebuah [masalah](https://github.com/qmk/qmk_firmware/issues/new) dan bila anda tahu bagaimana cara mengawakutunya, silakan buka Permintaan Tarik pada GitHub yang berisi pemecahan masalahnya.

## Namun `git` dan `GitHub` seram!

Tidak usah kuatir, kami sudah membuat beberapa [Panduan](id/newbs_git_best_practices.md) tentang bagaimana memulai dalam menggunakan `git` dan GitHub agar pengembangan lebih mudah.

Sebagai tambahan, anda dapat mencari tautan mengenai `git` dan GitHub [disini](id/newbs_learn_more_resources.md).

## Saya Memiliki Sebuah Papan Ketik Yang Ingin Saya Dukung

Luar Biasa! Silakan buka Permintaan Tarik untuk papan ketik tersebut. Kita akan mengulas kodenya dan menggabungkannya!

### What if I want to brand it with `QMK`?
### Bilamana Saya Ingin Memberinya Merk `QMK`?

Luar Biasa! Kami akan dengan senang hati membantu anda!

Bahkan, kami memiliki [sebuah laman tersendiri](https://qmk.fm/powered) yang berisi tentang tata-cara penambahan merk QMK pada laman anda dan papan ketik. Laman tadi mencakup lebih kurang semua yang anda butuhkan (pengetahuan dan gambar) untuk mendukung QMK.

Bila anda memiliki pertanyaan mengenai hal ini, buka sebuah permasalahan atau berkunjung ke [Discord](https://discord.gg/Uq7gcHh).

## Apa Perbedaan Antara QMK dan TMK?

TMK pada mulanya didesain dan diimplementasikan oleh [Jun Wako](https://github.com/tmk). QMK pada awalnya merupakan cabang dari TMK untuk Planck oleh [Jack Humbert](https://github.com/jackhumbert). Setelah beberapa waktu berjalan, cabang milik Jack menyimpang cukup jauh dibandingkan TMK sehingga pada 2015, Jack memutuskan untuk menamakan cabangnya sebagai QMK.

Dari sudut pandang teknis, QMK dibangun di atas TMK dengan menambahkan beberapa fitur baru. Terutama, QMK menambah jumlah kode tombol yang tersedia dan menggunakan kode tombol tersebut untuk mengimplementasikan fitur lanjutan seperti `S()`, `LCTL()`, dan `MO()`. Anda dapat melihat daftar lengkap dari kode tombol ini pada [Kode Tombol](id/keycodes.md).

Dari sudut pandang manajemen proyek dan komunitas, Jun Wako memelihara semua papan ketik yang secara resmi didukung oleh TMK, dengan beberapa bantuan dari komunitas. Ada juga cabang yang dipelihara oleh komunitas dan bisa juga membuat cabang tersendiri untuk papan ketik lain. Pun halnya dengan tata letak bawaan yang disediakan, tidak begitu banyak tersedia. Pengguna biasanya tidak berbagi tata letak dengan pengguna lainnya. QMK mendorong berbagi pengaturan papan ketik dan tata letak melalui lumbung yang dipelihara terpusat yang menerima semua Permintaan Tarik yang mengikuti standar kualitas. Konfigurasi papan ketik dan/atau tata letak ini biasanya dipelihara oleh komunitas. Namun, tim QMK juga akan membantu bila dibutuhkan.

Kedua pendekatan diatas memiliki keuntungan dan kerugian masing masing. Terlebih lagi, alur kode juga secara bebas loncat dari TMK dan QMK bila kondisi memintanya.