# Details

This page contains details that are no longer relevant to the License Clarification effort.

## Small Contributions

Smaller contributions that don't need to sign off on the license change.

Username | # Lines | Files | 
---------|---------|-------|
@AGausmann | 3 | quantum/process_keycode/process_midi.c |
@Chipairon | 2 | quantum/keymap_extras/keymap_spanish.h | 
@coderkun | 5 | quantum/process_keycode/process_unicode.c | 
@fernandodeperto | 3 | quantum/keymap_extras/keymap_nordic.h | 
@jeebak | 8 | quantum/audio/audio_pwm.c | 
@Keller-Laminar | 1 | quantum/keymap_extras/keymap_dvorak.h | 
kevin at letord.fr | 1 | quantum/keymap_extras/keymap_french.h | 
@ofpies | 3 | quantum/config_common.h<br>quantum/quantum.c | 
@MagicianVivi | 2 | quantum/keymap_extras/keymap_bepo.h | 
@NoahAndrews | 1 | quantum/template/template.h | 
@robertdale | 6 | quantum/process_keycode/process_music.c | 
@scott-t-wilson | 3 | quantum/rgblight.c<br>quantum/rgblight.h | 
@skullydazed | 2 | quantum/rgblight.c | 
@yoyoerx | 6 | quantum/matrix.c<br>quantum/template/template.c | 

# Single Author Files

These are the single author files that still need to have their license clarified.

* quantum/dynamic_macro.h: @Vifon
* quantum/pincontrol.h: @wez
* quantum/keymap_extras/keymap_canadian_multilingual.h: @DidierLoiseau
* quantum/keymap_extras/keymap_jp.h: @h-youhei
* quantum/keymap_extras/keymap_unicode_cyrillic.h: @kuel
* quantum/keymap_extras/keymap_russian.h: @kuel

# Multi Author Files

Each file listed below has more than one author and needs to have copyright resolved. The number of lines contributed by each author is shown as determined by:

```git blame <file> | cut -f 2 -d '(' | cut -f 1 -d '2' | sort | uniq -c | sed 's/^ */* /'```

## quantum/config_common.h 

* 24 Eric Tang
* 2 Fred Sundvik
* 58 Jack Humbert
* 1 ofples

## quantum/keycode_config.h 

* 5 IBNobody
* 20 Jack Humbert
* 1 fredizzimo

## quantum/keymap.h 

* 39 Jack Humbert
* 6 Wilba6582
* 8 fredizzimo

## quantum/keymap_common.c 

* 1 Fred Sundvik
* 162 Jack Humbert
* 11 Wilba6582
* 3 fredizzimo

## quantum/light_ws2812.c 

* 163 Jack Humbert
* 168 Yang Liu

## quantum/light_ws2812.h 

* 11 Jack Humbert
* 70 Yang Liu

## quantum/matrix.c 

* 3 Erez Zukerman
* 15 Eric Tang
* 239 IBNobody
* 152 Jack Humbert
* 2 fredizzimo
* 2 yoyoerx

## quantum/quantum.c 

* 38 Erez Zukerman
* 96 Eric Tang
* 49 Gergely Nagy
* 68 IBNobody
* 4 Jack & Erez
* 561 Jack Humbert
* 2 Ofer Plesser
* 14 Pavlos Vinieratos
* 2 Priyadi Iman Nurcahyo
* 12 Smilliam
* 52 TerryMathews
* 12 Wojciech Siewierski

## quantum/quantum.h 

* 23 Erez Zukerman
* 4 Eric Tang
* 1 Fred Sundvik
* 3 Gergely Nagy
* 86 Jack Humbert
* 2 Pavlos Vinieratos
* 5 fredizzimo

## quantum/quantum_keycodes.h 

* 2 Erez Zukerman
* 2 Jack Humbert
* 313 Wilba6582

## quantum/rgblight.c 

* 13 Erez Zukerman
* 5 Eric Tang
* 39 Fred Sundvik
* 101 Jack Humbert
* 311 Jordi Orlando
* 1 Scott Wilson
* 147 Yang Liu
* 2 skullY

## quantum/rgblight.h 

* 3 Erez Zukerman
* 2 Eric Tang
* 6 Fred Sundvik
* 12 Jack Humbert
* 2 Scott Wilson
* 80 Yang Liu

## quantum/api/api_sysex.c 

* 44 Fred Sundvik
* 13 Jack Humbert

## quantum/audio/audio.c 

* 318 IBNobody
* 164 Jack Humbert

## quantum/audio/audio.h 

* 15 IBNobody
* 76 Jack Humbert

## quantum/audio/audio_pwm.c 

* 642 IBNobody
* 1 Jack Humbert

## quantum/audio/song_list.h 

* 101 IBNobody
* 16 Jack Humbert
* 8 JeeBak Kim

## quantum/audio/voices.c 

* 24 IBNobody
* 256 Jack Humbert

## quantum/audio/voices.h 

* 3 IBNobody
* 32 Jack Humbert

## quantum/keymap_extras/keymap_bepo.h 

* 308 Didier Loiseau
* 1 Jack Humbert   
* 2 Vivien Alger

## quantum/keymap_extras/keymap_colemak.h 

* 31 Erez Zukerman
* 44 Jack Humbert

## quantum/keymap_extras/keymap_dvorak.h 

* 69 Jack Humbert
* 15 Jonathan A. Kollasch
* 1 Keller-Laminar

## quantum/keymap_extras/keymap_fr_ch.h 

* 1 Jack Humbert
* 1 Jonathan A. Kollasch
* 96 Vincent Pochet

## quantum/keymap_extras/keymap_french.h 

* 80 Jack Humbert
* 2 Jonathan A. Kollasch
* 1 Kévin Letord

## quantum/keymap_extras/keymap_french_osx.h 

* 1 Jack Humbert
* 76 Sébastien Pérochon

## quantum/keymap_extras/keymap_german.h 

* 1 Jack Humbert
* 1 Jonathan A. Kollasch
* 58 Matthias Schmitt
* 39 plgruener

## quantum/keymap_extras/keymap_german_ch.h 

* 1 Jack Humbert
* 1 Jonathan A. Kollasch
* 100 heartsekai

## quantum/keymap_extras/keymap_german_osx.h 

* 1 Jack Humbert
* 96 Stephan Bösebeck

## quantum/keymap_extras/keymap_neo2.h 

* 2 Jack Humbert
* 42 Matthias Schmitt
* 19 plgruener

## quantum/keymap_extras/keymap_nordic.h 

* 1 Andreas Lindhé
* 1 Erez Zukerman
* 3 Fernando Mendonca
* 53 Jack Humbert
* 1 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_norwegian.h 

* 1 Andreas Lindhé
* 40 joar

## quantum/keymap_extras/keymap_plover.h 

* 1 Jack Humbert
* 31 James ‘Twey’ Kay

## quantum/keymap_extras/keymap_spanish.h 

* 59 Jack Humbert
* 1 Jonathan A. Kollasch
* 2 Rubén Díaz-Jorge

## quantum/keymap_extras/keymap_uk.h 

* 34 Jack Humbert
* 2 Jonathan A. Kollasch

## quantum/process_keycode/process_midi.c 

* 3 Adam Gausmann
* 65 Jack Humbert

## quantum/process_keycode/process_music.c 

* 180 Jack Humbert
* 6 Robert Dale

## quantum/process_keycode/process_tap_dance.c 

* 90 Gergely Nagy
* 38 Jack Humbert
* 8 Pavlos Vinieratos

## quantum/process_keycode/process_tap_dance.h 

* 22 Gergely Nagy
* 41 Jack Humbert
* 9 Pavlos Vinieratos

## quantum/process_keycode/process_unicode.c 

* 176 Gergely Nagy
* 24 Jack Humbert
* 84 Priyadi Iman Nurcahyo
* 5 coderkun

## quantum/process_keycode/process_unicode.h 

* 40 Gergely Nagy
* 117 Jack Humbert
* 10 Priyadi Iman Nurcahyo

## quantum/template/config.h 

* 9 Eric Tang
* 78 IBNobody
* 75 Jack Humbert

## quantum/template/template.c 

* 9 Damien Pollet
* 7 IBNobody
* 8 Jack Humbert
* 4 yoyoerx

## quantum/template/template.h 

* 2 Damien Pollet
* 16 Jack Humbert
* 1 Noah Andrews

# All Single Author Files

These files have only a single author and so clarifying licensing should be pretty straightforward.

* quantum/analog.c: Jack Humbert
* quantum/analog.h: Jack Humbert
* quantum/api.h: Jack Humbert
* quantum/keycode_config.c: Jack Humbert
* quantum/pincontrol.h: Wez Furlong
* quantum/api/api_sysex.h: Jack Humbert
* quantum/audio/luts.c: IBNobody
* quantum/audio/luts.h: IBNobody
* quantum/audio/musical_notes.h: Jack Humbert
* quantum/audio/wave.h: Jack Humbert
* quantum/keymap_extras/keymap_br_abnt2.h: Potiguar Faga
* quantum/keymap_extras/keymap_dvp.h: Artyom Mironov
* quantum/keymap_extras/keymap_jp.h: h-youhei
* quantum/keymap_extras/keymap_unicode_cyrillic.h: kuel
* quantum/process_keycode/process_chording.c: Jack Humbert
* quantum/process_keycode/process_chording.h: Jack Humbert
* quantum/process_keycode/process_leader.c: Jack Humbert
* quantum/process_keycode/process_leader.h: Jack Humbert
* quantum/process_keycode/process_midi.h: Jack Humbert
* quantum/process_keycode/process_music.h: Jack Humbert
* quantum/process_keycode/process_printer.c: Jack Humbert
* quantum/process_keycode/process_printer.h: Jack Humbert
* quantum/process_keycode/process_printer_bb.c: Jack Humbert
* quantum/serial_link/LICENSE: Fred Sundvik
* quantum/serial_link/protocol/frame_router.c: Fred Sundvik
* quantum/serial_link/protocol/frame_router.h: Fred Sundvik
* quantum/serial_link/protocol/frame_validator.c: Fred Sundvik
* quantum/serial_link/protocol/frame_validator.h: Fred Sundvik
* quantum/serial_link/protocol/physical.h: Fred Sundvik
* quantum/serial_link/protocol/triple_buffered_object.c: Fred Sundvik
* quantum/serial_link/protocol/triple_buffered_object.h: Fred Sundvik
* quantum/serial_link/system/serial_link.c: Fred Sundvik
* quantum/serial_link/system/serial_link.h: Fred Sundvik
* quantum/serial_link/tests/byte_stuffer_tests.cpp: Fred Sundvik
* quantum/serial_link/tests/frame_router_tests.cpp: Fred Sundvik
* quantum/serial_link/tests/frame_validator_tests.cpp: Fred Sundvik
* quantum/serial_link/tests/Makefile: Fred Sundvik
* quantum/serial_link/tests/transport_tests.cpp: Fred Sundvik
* quantum/serial_link/tests/triple_buffered_object_tests.cpp: Fred Sundvik
* quantum/template/rules.mk: Fred Sundvik
* quantum/template/keymaps/default/config.h: Jack Humbert
* quantum/template/keymaps/default/Makefile: Jack Humbert
* quantum/template/keymaps/default/readme.md: Jack Humbert
* quantum/tools/eeprom_reset.hex: Jack Humbert
* quantum/tools/readme.md: Jack Humbert
* quantum/visualizer/lcd_backlight.c: Fred Sundvik
* quantum/visualizer/lcd_backlight.h: Fred Sundvik
* quantum/visualizer/led_test.h: Fred Sundvik
* quantum/visualizer/LICENSE.md: Fred Sundvik
* quantum/visualizer/readme.md: Fred Sundvik
* quantum/visualizer/example_integration/callbacks.c: Fred Sundvik
* quantum/visualizer/example_integration/gfxconf.h: Fred Sundvik
* quantum/visualizer/example_integration/lcd_backlight_hal.c: Fred Sundvik
* quantum/visualizer/example_integration/visualizer_user.c: Fred Sundvik

# All Files

## quantum/analog.c 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert

## quantum/analog.h 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert

## quantum/api.c 

* 7edac212c8ed8442bf4207e70dc8194631b2bf27 Sat Nov 26 15:37:46 2016 -0500 Jack Humbert
* 06c64bbff3e228df542149acde64eadaf59b9b0f Mon Dec 19 11:18:18 2016 -0500 Jack Humbert

## quantum/api.h 

* 7edac212c8ed8442bf4207e70dc8194631b2bf27 Sat Nov 26 15:37:46 2016 -0500 Jack Humbert

## quantum/config_common.h 

* 35a81f5b8b081e1607a7c04489b01f551c3213cc Mon Oct 26 16:32:37 2015 -0400 Jack Humbert
* aaa758f1d3f97dda39879f2b055ad2da9680adfe Mon May 23 20:42:21 2016 -0700 Eric Tang
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* 705c775a4a433249081321cea0c2def2627817dc Sun Aug 21 22:05:55 2016 -0500 IBNobody
* 936a26d04ffa12801031c058f27e221174e3fabd Thu Aug 25 00:15:41 2016 -0500 IBNobody
* 6390033e8688550826a4bd3004a2e76568600657 Mon Nov 21 20:14:16 2016 -0500 Jack Humbert
* 03d6e165bb0baf9d0093250d3c3c0771290df4d6 Fri Nov 25 09:17:40 2016 +0200 ofples
* 0c9d66eb59add717397ba83d508577073412ce86 Fri Nov 25 09:20:41 2016 +0200 ofples
* de1df639535817e17f1c01f07e7a629cec478526 Sat Nov 26 13:55:41 2016 +0700 Priyadi Iman Nurcahyo
* 17acde94ee2695ab69ea336742c904d649dce17c Sat Nov 26 14:02:38 2016 +0700 Priyadi Iman Nurcahyo
* d9d67e7b7686fdcbc7269a76d2a54c42325bdd03 Sat Nov 26 15:26:02 2016 +0700 Priyadi Iman Nurcahyo
* f2214ce1cb6cfe7a0efabe870a2c00fb8451ee80 Sat Nov 26 15:57:48 2016 +0700 Priyadi Iman Nurcahyo
* 6e0f994950435aa5867e7b7ce780186d881d74ac Mon Nov 28 23:51:07 2016 -0500 Jack Humbert
* dd685eceb2045371d38f24d454f1ab08ca7416f4 Thu Dec 29 12:13:30 2016 +0200 Fred Sundvik

## quantum/dynamic_macro.h 

* 39e8e61258b51a2c33a94dd877e983f0b1dae0c1 Thu Aug 18 01:37:13 2016 +0200 Wojciech Siewierski
* 70f32842e5d94f14d05c1f9adcb1b1144a25a132 Sun Oct 9 12:52:39 2016 +0200 Wojciech Siewierski

## quantum/keycode_config.c 

* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert

## quantum/keycode_config.h 

* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 4d4f7684e684bec319f166121463a88cd4a62703 Fri Jul 1 17:04:53 2016 +0300 fredizzimo
* 558f3ec1eb325caf706efc15e2fab26121aba442 Tue Sep 6 23:19:01 2016 -0500 IBNobody

## quantum/keymap.h 

* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 76076db72545bbb649f11394a12721f61579527f Mon Jun 20 22:36:36 2016 -0400 Jack & Erez
* 1a0bac8bccf0e156d2f3c5f14a7214f9677b6370 Tue Jun 21 17:42:29 2016 -0400 Jack Humbert
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 4d4f7684e684bec319f166121463a88cd4a62703 Fri Jul 1 17:04:53 2016 +0300 fredizzimo
* 50c686587ed49d8079ba1b11d45ceb6a55d6cd4b Thu Jul 7 23:34:33 2016 -0400 TerryMathews
* e692ebf86a962e90c51302e7b17a953ea2858f79 Fri Aug 12 20:38:26 2016 +0900 shela
* 558f3ec1eb325caf706efc15e2fab26121aba442 Tue Sep 6 23:19:01 2016 -0500 IBNobody
* 1048a588c750e27ff0f900cd6aaf670e034086d0 Fri Oct 7 17:15:11 2016 +0200 npoirey
* 5b2e455d3b71bfb90754930d1f22d3e8ce98b927 Mon Oct 10 00:46:20 2016 +0700 Priyadi Iman Nurcahyo
* e27a754b70434de88a37c4a572e4ca5f7730ff58 Wed Oct 12 22:18:27 2016 -0400 Jack & Erez
* 52d7f7d2770a35adf0b0b0c803e05ae8719f539f Sun Oct 16 15:49:45 2016 -0400 Jack Humbert
* 5f91fb413624781ac79db641549b9e08753c04b5 Sun Oct 16 16:03:33 2016 -0400 Jack Humbert
* 33e62c080c9161a0fc921c90ed299a67fc2e1799 Sat Nov 12 20:54:37 2016 -0500 Jack Humbert
* 01038ab54ca6c2858ea9e856c717a1129ffe4156 Fri Dec 23 21:51:11 2016 +0200 Ofer Plesser
* d8a608f3ff4cb4d73cd57be500fd9881e230099d Thu Dec 29 18:28:48 2016 +1100 Wilba6582

## quantum/keymap_common.c 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* 35a81f5b8b081e1607a7c04489b01f551c3213cc Mon Oct 26 16:32:37 2015 -0400 Jack Humbert
* cc1c32671eb1eb43a87e55ac4ffa60b15115e48d Mon Oct 26 20:02:25 2015 -0400 Jack Humbert
* d9f08e6177271594fa573993d9f4dbc2d98c7416 Tue Oct 27 22:00:52 2015 -0400 Jack Humbert
* 18da1e6801335b0d9515ab72e9236a01d629915f Tue Oct 27 23:06:18 2015 -0400 Jack Humbert
* d3db8d62f6fc6a7dee43978ddc8356579b502b37 Wed Oct 28 04:07:15 2015 +0200 Erez Zukerman
* 7d6716beded4a60cd9de24e95d8ec60694692b6f Fri Jan 29 23:27:36 2016 -0500 Jack Humbert
* 65b41e2e59e274354e57ed36cad097823f111f1a Sun Feb 7 11:48:28 2016 +0100 Wojciech Siewierski
* 47dcec29456106828b83fe5b85fa7a7427ddc710 Sun Jan 3 17:49:28 2016 -0500 Chris Gerber
* 1d13aa933bbb57bf0c1fe0196981b81233c3df97 Mon Mar 28 19:45:20 2016 -0500 IBNobody
* 3755ef5ddbdad9f25a53fee951c3eb78035b52c3 Wed Apr 13 20:57:51 2016 -0500 IBNobody
* ee2ee7f4f049dda385a9db7dddd8e7e91681315b Fri Apr 15 13:44:07 2016 -0400 Jack Humbert
* 9cfc74c35b940884618b0fe1e6fd25c570e1c974 Thu Apr 7 15:21:06 2016 +0300 Erez Zukerman
* ab19ebd08a8b955775e6fa94cdf6b8d128d8b43c Sat Apr 16 18:51:58 2016 -0400 Jack Humbert
* c83aa16f1d614c1c10f7597a67ffb9f2ae871951 Sat Apr 16 20:26:02 2016 -0400 Jack Humbert
* 41cc35425ab32c9a9492006da8b667d01d32dfa6 Sat Apr 16 21:31:40 2016 -0400 Jack Humbert
* 8bbd064cf52a76508589579f19595607a1f3af21 Sat Apr 16 23:07:50 2016 -0400 Jack Humbert
* 45f10b4c4b308226fa1568277654a13853a03ab4 Sat Apr 16 22:10:18 2016 -0500 IBNobody
* e7b9959819e709d7df2e96a94bdaf36e4e9e23e3 Sat Apr 16 23:15:40 2016 -0400 Jack Humbert
* a67d425f4d5278595e7ab785a0f246b83fb1a09f Sun Apr 17 01:00:39 2016 -0400 Jack Humbert
* d5b72e7bde5ede25f7d5699b50b7d9eb6f31ba92 Sun Apr 17 12:54:32 2016 -0500 IBNobody
* 3103ea542f0039637a1a266df79a97a7a13fa6b4 Sun Apr 17 12:55:19 2016 -0500 IBNobody
* 23231fa577f7c6c585124226a83f21a7668e62dd Sun Apr 17 14:16:03 2016 -0500 IBNobody
* 5c98ad59606ee95b82c27bf2525383a9ec88542b Sun Apr 17 20:14:37 2016 -0500 IBNobody
* e49712b5593b887c8af18aeb7196513f1c7b7bcf Mon Apr 18 21:01:48 2016 -0400 Jack Humbert
* 620ac4b260fa663d12b11a0b15ac50379523c125 Thu Apr 21 19:35:18 2016 -0700 Eric Tang
* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody
* 41b3e399b1d43db9574c6016951d92974b3d93e7 Thu May 5 21:50:51 2016 -0400 Jack Humbert
* 1a8c0dd22d6a2255511d0db6a456315541b5815b Sun May 15 00:27:32 2016 -0400 Erez Zukerman
* fde477a927edc6b4207a6968d44aeed021e8b300 Sun May 15 00:51:06 2016 -0400 Jack Humbert
* b732b79b49b098dba8e14493c745075f336747d8 Wed May 18 23:47:16 2016 -0400 Jack Humbert
* 287eb7ad148abc8fe3fb014218d71e205fd9131d Tue May 24 11:56:53 2016 -0400 Jack Humbert
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 4d4f7684e684bec319f166121463a88cd4a62703 Fri Jul 1 17:04:53 2016 +0300 fredizzimo
* 9870082a06386eba8c0c5f22da90d0256ef6244b Thu Jul 7 19:48:39 2016 +0300 Fred Sundvik
* 8b94e26d7c3b30cc57d710a11e5651d15e8e3b20 Sun Jul 24 22:07:43 2016 -0400 Jack Humbert
* d8a608f3ff4cb4d73cd57be500fd9881e230099d Thu Dec 29 18:28:48 2016 +1100 Wilba6582

## quantum/light_ws2812.c 

* ba9ac457b2159097ecfd9848c5171c52e3a68260 Sun Jan 24 17:05:47 2016 -0800 Yang Liu
* 57e08eb8badc5db2fb44d2df684f32ea48cce411 Thu Jul 7 11:33:32 2016 -0400 Jack Humbert
* 5f91fb413624781ac79db641549b9e08753c04b5 Sun Oct 16 16:03:33 2016 -0400 Jack Humbert
* 33e62c080c9161a0fc921c90ed299a67fc2e1799 Sat Nov 12 20:54:37 2016 -0500 Jack Humbert
* e9f748751808de2f1e85cf7fb670d78773bd5e76 Sun Nov 13 23:02:38 2016 -0500 Jack Humbert
* 530dd3377e4d409a7ca2fee7e47b60b735ebc0fa Tue Nov 15 13:18:10 2016 -0500 Jack Humbert
* 3774a7fcdab5544fc787f4c200be05fcd417e31f Thu Nov 17 17:42:14 2016 -0500 Jack Humbert

## quantum/light_ws2812.h 

* ba9ac457b2159097ecfd9848c5171c52e3a68260 Sun Jan 24 17:05:47 2016 -0800 Yang Liu
* 5f91fb413624781ac79db641549b9e08753c04b5 Sun Oct 16 16:03:33 2016 -0400 Jack Humbert
* e9f748751808de2f1e85cf7fb670d78773bd5e76 Sun Nov 13 23:02:38 2016 -0500 Jack Humbert
* 664c0a036b3d7c3ed39f4a7a78d97f4a9cc7d20c Mon Nov 21 19:50:55 2016 -0500 Jack Humbert
* 06c64bbff3e228df542149acde64eadaf59b9b0f Mon Dec 19 11:18:18 2016 -0500 Jack Humbert

## quantum/matrix.c 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* 35a81f5b8b081e1607a7c04489b01f551c3213cc Mon Oct 26 16:32:37 2015 -0400 Jack Humbert
* 641859df84bf40025b2c14319d1a168a435562e2 Thu Mar 10 11:28:34 2016 -0500 yoyoerx
* 684793360cdb08ac1e50a6d27e1796fadd527adb Mon May 9 00:36:23 2016 -0400 Jack Humbert
* 1a8c0dd22d6a2255511d0db6a456315541b5815b Sun May 15 00:27:32 2016 -0400 Erez Zukerman
* aaa758f1d3f97dda39879f2b055ad2da9680adfe Mon May 23 20:42:21 2016 -0700 Eric Tang
* 1ae6011cef2230826a9e6db6c5b638677bc640b7 Tue May 24 08:44:40 2016 -0700 Eric Tang
* de57799530d3184722532f93d156364067d8fcd5 Sat May 28 11:56:06 2016 -0400 Jack Humbert
* 008c8d54a0a1a1e908d372d0fe9edb45a2d491e5 Fri Jun 17 22:09:59 2016 -0400 Jack Humbert
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* 215c2119af5281072d5a6efb0308408793cadd08 Wed Jun 29 16:21:41 2016 -0400 Jack Humbert
* 4d4f7684e684bec319f166121463a88cd4a62703 Fri Jul 1 17:04:53 2016 +0300 fredizzimo
* 8e88d55bfd7c88cb15845e0c6415e4e892532861 Mon Jul 4 11:45:58 2016 -0400 Jack Humbert
* 3577e26fd9916ceab58779ec6323d43da54eb3b5 Wed Jul 6 00:24:31 2016 -0400 Jack Humbert
* 17170ba76d3c94edcf1ab263520238fdb0384774 Sun Oct 23 23:00:43 2016 -0500 IBNobody
* 508eddf8ba8548d3f71e1c09a404839beb49f45c Fri Oct 28 14:21:38 2016 -0500 IBNobody
* 4c6960835c0a6e29670dabdc27117d7d3c7f99f5 Fri Oct 28 16:24:20 2016 -0500 IBNobody
* 32f88c07173b795c6981c779057dceba00aeb1cb Sat Oct 29 10:39:03 2016 -0500 IBNobody
* f4030289744fc6dc82dd85c955070c0845813cc5 Sat Oct 29 16:12:58 2016 -0500 IBNobody
* a06115df19a74d39b08758472b221e630c3680d3 Fri Nov 18 23:20:07 2016 -0500 Jack Humbert

## quantum/pincontrol.h 

* 8485bb34d2e291db5b6c81f892850da1cdca37ba Sun Nov 27 22:43:11 2016 -0800 Wez Furlong

## quantum/quantum.c 

* 1a8c0dd22d6a2255511d0db6a456315541b5815b Sun May 15 00:27:32 2016 -0400 Erez Zukerman
* 15719f3574c6274ee0f3ec87431927c5a523aa3e Sun May 15 00:40:59 2016 -0400 Jack Humbert
* bf5c2ccee5497523c214dae7aacdc27fdbb0f235 Sun May 15 00:47:25 2016 -0400 Jack Humbert
* fde477a927edc6b4207a6968d44aeed021e8b300 Sun May 15 00:51:06 2016 -0400 Jack Humbert
* 0428214b905e5f8b3bed721885957ce249ba4991 Wed May 18 23:14:00 2016 -0400 Jack Humbert
* b732b79b49b098dba8e14493c745075f336747d8 Wed May 18 23:47:16 2016 -0400 Jack Humbert
* 0275d444d77c9d85d2189b09d8813fb76dc4d566 Thu May 19 15:36:28 2016 +0300 purpleP
* 287eb7ad148abc8fe3fb014218d71e205fd9131d Tue May 24 11:56:53 2016 -0400 Jack Humbert
* 1237025963484d70bbe5185a790bec6544653ccc Tue May 24 23:27:59 2016 -0400 Erez Zukerman
* 8bc69afc633d3e199e3ac0a5bf39e4d255f2ce4a Tue May 24 23:48:46 2016 -0400 Erez Zukerman
* 17977a7e24ddab6ca101341b33c8fe7ad13e68f5 Sat May 28 15:22:30 2016 -0400 Jack Humbert
* 1c9f33c06a6ef18c9c21e5841180af5ae554c34b Wed Jun 1 22:49:55 2016 -0400 Jack Humbert
* 4635b4453335b61df11008fa907eef221db5912b Wed Jun 1 23:00:55 2016 -0400 Jack Humbert
* 794aed37a0da5a277a07e7fa86263e0852fa9f6d Fri Jun 3 12:48:40 2016 -0700 Eric Tang
* b70248fa2144d297504eedbc80a76dfdc40d9f1f Fri Jun 17 21:42:59 2016 -0400 Jack Humbert
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 76076db72545bbb649f11394a12721f61579527f Mon Jun 20 22:36:36 2016 -0400 Jack & Erez
* 98f0807359cfa78d25442b91ff4c5bbfc5679661 Tue Jun 21 22:55:54 2016 -0400 Jack Humbert
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* b68b722325e1f0f68387e161365fa8e31c79b7b2 Thu Jun 23 23:14:21 2016 -0400 Jack Humbert
* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 197f152dee834a737cd820f2a95d1ade98be4898 Wed Jun 29 18:29:20 2016 -0400 Jack Humbert
* 60fd885a6e540509baa2193932e15caeaeb8f4c5 Wed Jun 29 18:35:29 2016 -0400 Jack Humbert
* 4d4f7684e684bec319f166121463a88cd4a62703 Fri Jul 1 17:04:53 2016 +0300 fredizzimo
* 1412076df68ac00f9a00173977d2826603c12ddf Mon Jul 4 19:56:08 2016 -0700 Smilliam
* 6b0c9cc905c0985f96a80306cf5fe0d6724b28fc Mon Jul 4 19:58:26 2016 -0700 Smilliam
* a4bf46f9b1d0a0be0cecb2cd0f0d941aa7c71bd3 Wed Jul 6 22:48:19 2016 -0400 Jack Humbert
* 50c686587ed49d8079ba1b11d45ceb6a55d6cd4b Thu Jul 7 23:34:33 2016 -0400 TerryMathews
* f7a86822266603b8ffd21e9f89ec1de8d4950791 Fri Jul 8 03:32:28 2016 -0400 TerryMathews
* b12fe6abb25db1feca6a7649097a8d1cb67a063f Sun Jul 10 19:04:01 2016 -0700 Smilliam
* a998a48673372e409991066d7d2d9ba282f79d59 Mon Jul 11 09:14:43 2016 -0400 Jack Humbert
* a28a6e5b79c819e5f9323f62686498eca3ef399f Wed Jul 13 16:38:02 2016 +0200 Pavlos Vinieratos
* 857aa5bef6a74f8785a7039feea5286c07bf7067 Sat Aug 13 11:14:42 2016 +0200 Gergely Nagy
* 644c8c79271db8cf1bd934b9a80a0215585e46e7 Thu Aug 18 01:34:05 2016 +0200 Wojciech Siewierski
* 0d28787c5cf2173d12f57b397515f91cffaa820a Thu Aug 18 11:29:53 2016 +0200 Gergely Nagy
* e571d4656cd283ce8d793fe3dd2ac176b84b0bf5 Tue Sep 6 18:02:43 2016 -0500 IBNobody
* 558f3ec1eb325caf706efc15e2fab26121aba442 Tue Sep 6 23:19:01 2016 -0500 IBNobody
* 5b2e455d3b71bfb90754930d1f22d3e8ce98b927 Mon Oct 10 00:46:20 2016 +0700 Priyadi Iman Nurcahyo
* 5f91fb413624781ac79db641549b9e08753c04b5 Sun Oct 16 16:03:33 2016 -0400 Jack Humbert
* 33e62c080c9161a0fc921c90ed299a67fc2e1799 Sat Nov 12 20:54:37 2016 -0500 Jack Humbert
* e9f748751808de2f1e85cf7fb670d78773bd5e76 Sun Nov 13 23:02:38 2016 -0500 Jack Humbert
* ffa5b1e7ea6697acf9ebfcade1149031642f7870 Sat Nov 19 11:32:09 2016 +0100 Gergely Nagy
* 74a1f00713d1407fb1d2e20d58da93919ab0c221 Sat Nov 19 18:19:18 2016 +0100 Gergely Nagy
* 664c0a036b3d7c3ed39f4a7a78d97f4a9cc7d20c Mon Nov 21 19:50:55 2016 -0500 Jack Humbert
* 450a8fb5b61de8166fe21eb4f57e1c00514afe32 Mon Nov 21 20:17:45 2016 -0500 Jack Humbert
* cefa8468fb5f28bd67a0c02d371a4aef0964e20c Wed Nov 23 20:16:38 2016 -0500 Jack Humbert
* 7edac212c8ed8442bf4207e70dc8194631b2bf27 Sat Nov 26 15:37:46 2016 -0500 Jack Humbert
* 01038ab54ca6c2858ea9e856c717a1129ffe4156 Fri Dec 23 21:51:11 2016 +0200 Ofer Plesser

## quantum/quantum.h 

* 1a8c0dd22d6a2255511d0db6a456315541b5815b Sun May 15 00:27:32 2016 -0400 Erez Zukerman
* fde477a927edc6b4207a6968d44aeed021e8b300 Sun May 15 00:51:06 2016 -0400 Jack Humbert
* 0428214b905e5f8b3bed721885957ce249ba4991 Wed May 18 23:14:00 2016 -0400 Jack Humbert
* b732b79b49b098dba8e14493c745075f336747d8 Wed May 18 23:47:16 2016 -0400 Jack Humbert
* 287eb7ad148abc8fe3fb014218d71e205fd9131d Tue May 24 11:56:53 2016 -0400 Jack Humbert
* de57799530d3184722532f93d156364067d8fcd5 Sat May 28 11:56:06 2016 -0400 Jack Humbert
* 17977a7e24ddab6ca101341b33c8fe7ad13e68f5 Sat May 28 15:22:30 2016 -0400 Jack Humbert
* 1c9f33c06a6ef18c9c21e5841180af5ae554c34b Wed Jun 1 22:49:55 2016 -0400 Jack Humbert
* 794aed37a0da5a277a07e7fa86263e0852fa9f6d Fri Jun 3 12:48:40 2016 -0700 Eric Tang
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 98f0807359cfa78d25442b91ff4c5bbfc5679661 Tue Jun 21 22:55:54 2016 -0400 Jack Humbert
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 197f152dee834a737cd820f2a95d1ade98be4898 Wed Jun 29 18:29:20 2016 -0400 Jack Humbert
* 8125cdb88ce1201fcfd16ed4c5313222ef4c230c Wed Jun 29 18:36:52 2016 -0400 Jack Humbert
* 4d4f7684e684bec319f166121463a88cd4a62703 Fri Jul 1 17:04:53 2016 +0300 fredizzimo
* a28a6e5b79c819e5f9323f62686498eca3ef399f Wed Jul 13 16:38:02 2016 +0200 Pavlos Vinieratos
* e01b4c3fd9a7b66276ffd22dcac25d569d7bb7ff Sat Jul 9 00:41:15 2016 +0300 Fred Sundvik
* 0d28787c5cf2173d12f57b397515f91cffaa820a Thu Aug 18 11:29:53 2016 +0200 Gergely Nagy
* 5f91fb413624781ac79db641549b9e08753c04b5 Sun Oct 16 16:03:33 2016 -0400 Jack Humbert
* 664c0a036b3d7c3ed39f4a7a78d97f4a9cc7d20c Mon Nov 21 19:50:55 2016 -0500 Jack Humbert
* cefa8468fb5f28bd67a0c02d371a4aef0964e20c Wed Nov 23 20:16:38 2016 -0500 Jack Humbert
* 7edac212c8ed8442bf4207e70dc8194631b2bf27 Sat Nov 26 15:37:46 2016 -0500 Jack Humbert

## quantum/quantum_keycodes.h 

* d8a608f3ff4cb4d73cd57be500fd9881e230099d Thu Dec 29 18:28:48 2016 +1100 Wilba6582
* 8459bb97c1e8bcb9ccce55a1ed849d373bd7706c Wed Jan 11 21:57:41 2017 -0500 Erez Zukerman
* 3717cf5864d6505e406b5eb75f315e6dc2392912 Thu Jan 12 07:38:07 2017 -0500 Erez Zukerman
* 7288e5ab9c005a7b035d91e68358aa2b6a12420c Fri Jan 13 14:04:51 2017 -0500 Jack Humbert

## quantum/rgblight.c 

* ba9ac457b2159097ecfd9848c5171c52e3a68260 Sun Jan 24 17:05:47 2016 -0800 Yang Liu
* 2647c7cd84820a833b85e41ea86caf76b36e6ee1 Sun Jan 24 17:19:33 2016 -0800 Yang Liu
* 97f8f378761506914b69d4fd2d5661bfcae28295 Sun Apr 10 21:16:49 2016 -0700 skullY
* 620ac4b260fa663d12b11a0b15ac50379523c125 Thu Apr 21 19:35:18 2016 -0700 Eric Tang
* c37d52d2137acf5739c481cc0c8917ad6fd77161 Tue Apr 26 13:48:36 2016 -0400 Jack Humbert
* e024c11f7a849a38e478cda9fb9939a838cfa2e0 Tue Apr 26 13:50:04 2016 -0400 Jack Humbert
* 80c87054193b9243670aeb85adefbe1aa6c0fda0 Tue Jun 21 12:53:21 2016 -0400 Jack Humbert
* 57e08eb8badc5db2fb44d2df684f32ea48cce411 Thu Jul 7 11:33:32 2016 -0400 Jack Humbert
* 3a860c4bc210857f03ef9fae5043d6d5736d140d Tue Jul 26 14:43:45 2016 -0500 Jordi Orlando
* 899c88cd8bf024792760fcf3ee8be6fed13fb315 Tue Jul 26 14:46:30 2016 -0500 Jordi Orlando
* ea2d2f5d5841791745c93ef27cd1528a7fd69c97 Tue Jul 26 15:31:22 2016 -0500 Jordi Orlando
* b8679bbe045a2285d6ab6bbc420121b26f516b9a Wed Oct 5 20:41:33 2016 -0400 Jack Humbert
* 9b0e21f87f446935f29254bb623c2cfe29472b6e Sun Oct 9 19:26:16 2016 +0300 Fred Sundvik
* 92a3a96849aee708753a6623b0db228023e3baf8 Sun Oct 9 19:47:05 2016 +0300 Fred Sundvik
* ffae9d84c5279b463da112ee15568d536649b819 Sun Oct 9 19:53:41 2016 +0300 Fred Sundvik
* 03b6fcdaf034392e27752a9bd2c11de06a166e39 Mon Oct 10 00:20:24 2016 -0400 Jack Humbert
* 33e62c080c9161a0fc921c90ed299a67fc2e1799 Sat Nov 12 20:54:37 2016 -0500 Jack Humbert
* e9f748751808de2f1e85cf7fb670d78773bd5e76 Sun Nov 13 23:02:38 2016 -0500 Jack Humbert
* 3774a7fcdab5544fc787f4c200be05fcd417e31f Thu Nov 17 17:42:14 2016 -0500 Jack Humbert
* 285c5a91f23e972d9c579184283443111186329d Thu Nov 17 20:56:36 2016 -0500 Erez Zukerman
* 2e23689b8e3222982082c1f5a4f8ce7686f9658b Wed Nov 23 18:52:02 2016 -0500 Jack Humbert
* 4094544d41450617bc21ab58646603b8964eae0e Tue Nov 29 09:23:16 2016 -0500 Erez Zukerman
* cae269b08b642b07ee06dec7120a784a3c3d7aab Fri Dec 23 10:29:19 2016 -0500 Jack Humbert
* 748181dccddb8c9fa52a776f4fcd904ddca9aa31 Wed Dec 28 16:29:02 2016 -0500 Scott Wilson
* b8e74c378b1f118178edf0634d9fa7f0f9dd5e08 Thu Dec 29 09:32:02 2016 -0500 Scott Wilson

## quantum/rgblight.h 

* ba9ac457b2159097ecfd9848c5171c52e3a68260 Sun Jan 24 17:05:47 2016 -0800 Yang Liu
* 2647c7cd84820a833b85e41ea86caf76b36e6ee1 Sun Jan 24 17:19:33 2016 -0800 Yang Liu
* 620ac4b260fa663d12b11a0b15ac50379523c125 Thu Apr 21 19:35:18 2016 -0700 Eric Tang
* 80c87054193b9243670aeb85adefbe1aa6c0fda0 Tue Jun 21 12:53:21 2016 -0400 Jack Humbert
* 57e08eb8badc5db2fb44d2df684f32ea48cce411 Thu Jul 7 11:33:32 2016 -0400 Jack Humbert
* b8679bbe045a2285d6ab6bbc420121b26f516b9a Wed Oct 5 20:41:33 2016 -0400 Jack Humbert
* 9b0e21f87f446935f29254bb623c2cfe29472b6e Sun Oct 9 19:26:16 2016 +0300 Fred Sundvik
* 33e62c080c9161a0fc921c90ed299a67fc2e1799 Sat Nov 12 20:54:37 2016 -0500 Jack Humbert
* e9f748751808de2f1e85cf7fb670d78773bd5e76 Sun Nov 13 23:02:38 2016 -0500 Jack Humbert
* 3774a7fcdab5544fc787f4c200be05fcd417e31f Thu Nov 17 17:42:14 2016 -0500 Jack Humbert
* 285c5a91f23e972d9c579184283443111186329d Thu Nov 17 20:56:36 2016 -0500 Erez Zukerman
* 2e23689b8e3222982082c1f5a4f8ce7686f9658b Wed Nov 23 18:52:02 2016 -0500 Jack Humbert
* 4094544d41450617bc21ab58646603b8964eae0e Tue Nov 29 09:23:16 2016 -0500 Erez Zukerman
* cae269b08b642b07ee06dec7120a784a3c3d7aab Fri Dec 23 10:29:19 2016 -0500 Jack Humbert
* 748181dccddb8c9fa52a776f4fcd904ddca9aa31 Wed Dec 28 16:29:02 2016 -0500 Scott Wilson

## quantum/variable_trace.c 

* f519b94be7086852f2afe4ec248786b47968f7ff Sun Nov 6 21:57:26 2016 +0200 Fred Sundvik
* a377017c95b826d83ac7a46ef176d39a58294b44 Sun Nov 6 22:11:24 2016 +0200 Fred Sundvik

## quantum/variable_trace.h 

* a377017c95b826d83ac7a46ef176d39a58294b44 Sun Nov 6 22:11:24 2016 +0200 Fred Sundvik
* 0ba3e523a7c124e4ce54dfd043dc32e72ad3233b Sun Nov 6 22:44:43 2016 +0200 Fred Sundvik

## quantum/version.h 

* None None None

## quantum/api/api_sysex.c 

* 7edac212c8ed8442bf4207e70dc8194631b2bf27 Sat Nov 26 15:37:46 2016 -0500 Jack Humbert
* dd685eceb2045371d38f24d454f1ab08ca7416f4 Thu Dec 29 12:13:30 2016 +0200 Fred Sundvik

## quantum/api/api_sysex.h 

* 7edac212c8ed8442bf4207e70dc8194631b2bf27 Sat Nov 26 15:37:46 2016 -0500 Jack Humbert

## quantum/audio/audio.c 

* 73228f5e5d1d4cd31a46e5e93aa893a8f727e3b9 Thu Apr 21 00:37:45 2016 -0400 Jack Humbert
* 620ac4b260fa663d12b11a0b15ac50379523c125 Thu Apr 21 19:35:18 2016 -0700 Eric Tang
* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody
* 3f02637f4dd765803671c2611191beb096d60b36 Mon May 9 13:17:15 2016 -0400 Jack Humbert
* 15719f3574c6274ee0f3ec87431927c5a523aa3e Sun May 15 00:40:59 2016 -0400 Jack Humbert
* 0428214b905e5f8b3bed721885957ce249ba4991 Wed May 18 23:14:00 2016 -0400 Jack Humbert
* 287eb7ad148abc8fe3fb014218d71e205fd9131d Tue May 24 11:56:53 2016 -0400 Jack Humbert
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 06c64bbff3e228df542149acde64eadaf59b9b0f Mon Dec 19 11:18:18 2016 -0500 Jack Humbert

## quantum/audio/audio.h 

* 73228f5e5d1d4cd31a46e5e93aa893a8f727e3b9 Thu Apr 21 00:37:45 2016 -0400 Jack Humbert
* 082a0f313d8c842a5de7bae30ec8a3597e35880b Fri Apr 22 00:01:38 2016 -0500 IBNobody
* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody
* 3f02637f4dd765803671c2611191beb096d60b36 Mon May 9 13:17:15 2016 -0400 Jack Humbert
* 15719f3574c6274ee0f3ec87431927c5a523aa3e Sun May 15 00:40:59 2016 -0400 Jack Humbert
* 0428214b905e5f8b3bed721885957ce249ba4991 Wed May 18 23:14:00 2016 -0400 Jack Humbert
* 287eb7ad148abc8fe3fb014218d71e205fd9131d Tue May 24 11:56:53 2016 -0400 Jack Humbert
* 215c2119af5281072d5a6efb0308408793cadd08 Wed Jun 29 16:21:41 2016 -0400 Jack Humbert

## quantum/audio/audio_pwm.c 

* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert

## quantum/audio/luts.c 

* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody

## quantum/audio/luts.h 

* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody

## quantum/audio/musical_notes.h 

* 73228f5e5d1d4cd31a46e5e93aa893a8f727e3b9 Thu Apr 21 00:37:45 2016 -0400 Jack Humbert

## quantum/audio/song_list.h 

* 73228f5e5d1d4cd31a46e5e93aa893a8f727e3b9 Thu Apr 21 00:37:45 2016 -0400 Jack Humbert
* 7d0345ef25b5e1924f1e98c76d78607778e0b17d Sat Jul 30 01:52:33 2016 -0700 JeeBak Kim

## quantum/audio/voices.c 

* 73228f5e5d1d4cd31a46e5e93aa893a8f727e3b9 Thu Apr 21 00:37:45 2016 -0400 Jack Humbert
* e89b806b850ad1b5484176664288b71b0131683e Thu Apr 21 00:40:00 2016 -0400 Jack Humbert
* 9828aba2a12f03fccbc1095bc8e4918ae58fa31b Thu Apr 21 18:14:25 2016 -0400 Jack Humbert
* 7b3f212500210ae85063b043952b5b3ef6988ad6 Thu Apr 21 23:10:47 2016 -0400 Jack Humbert
* 082a0f313d8c842a5de7bae30ec8a3597e35880b Fri Apr 22 00:01:38 2016 -0500 IBNobody
* b1900c8dde2a68e87aaabd84280a99bf6658ea9f Fri Apr 22 01:02:50 2016 -0400 Jack Humbert
* a8086126fecbdce1c192036cf1011329d406949d Fri Apr 22 01:04:13 2016 -0400 Jack Humbert
* a718c53fe77f0b3b4361c850531eee5f23e3e13d Fri Apr 22 11:58:29 2016 -0400 Jack Humbert
* e7b6bb641c0636c01e3781fe51865fdb20014eeb Mon Apr 25 00:59:47 2016 -0400 Jack Humbert
* 140b97a1cd226432a8ec647004943698e3d87f0b Tue Apr 26 01:16:47 2016 -0400 Jack Humbert
* 66e0323881a5a3da65e14daeec41a1e9cfbda431 Fri Apr 29 12:42:55 2016 -0400 Jack Humbert
* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody
* 0edfe55bfe4afd037918ff73e49552a28f39a5ca Mon Dec 12 15:39:07 2016 -0500 Jack Humbert
* 06c64bbff3e228df542149acde64eadaf59b9b0f Mon Dec 19 11:18:18 2016 -0500 Jack Humbert
* 438a5d685bb7b726ff59109ce4229eca6303cd8e Tue Dec 20 19:38:22 2016 -0500 Jack Humbert
* 2fa36e38cf28f07ad4a4d74722486921fa7b8706 Wed Dec 21 00:22:32 2016 -0500 Jack Humbert

## quantum/audio/voices.h 

* 73228f5e5d1d4cd31a46e5e93aa893a8f727e3b9 Thu Apr 21 00:37:45 2016 -0400 Jack Humbert
* e89b806b850ad1b5484176664288b71b0131683e Thu Apr 21 00:40:00 2016 -0400 Jack Humbert
* 9828aba2a12f03fccbc1095bc8e4918ae58fa31b Thu Apr 21 18:14:25 2016 -0400 Jack Humbert
* 7b3f212500210ae85063b043952b5b3ef6988ad6 Thu Apr 21 23:10:47 2016 -0400 Jack Humbert
* 082a0f313d8c842a5de7bae30ec8a3597e35880b Fri Apr 22 00:01:38 2016 -0500 IBNobody
* b1900c8dde2a68e87aaabd84280a99bf6658ea9f Fri Apr 22 01:02:50 2016 -0400 Jack Humbert
* a8086126fecbdce1c192036cf1011329d406949d Fri Apr 22 01:04:13 2016 -0400 Jack Humbert
* a718c53fe77f0b3b4361c850531eee5f23e3e13d Fri Apr 22 11:58:29 2016 -0400 Jack Humbert
* e7b6bb641c0636c01e3781fe51865fdb20014eeb Mon Apr 25 00:59:47 2016 -0400 Jack Humbert
* 140b97a1cd226432a8ec647004943698e3d87f0b Tue Apr 26 01:16:47 2016 -0400 Jack Humbert
* 83e1cc241e3aabd69f6cdcd2581477d4b85bb8d3 Tue May 3 12:56:40 2016 -0500 IBNobody
* 0edfe55bfe4afd037918ff73e49552a28f39a5ca Mon Dec 12 15:39:07 2016 -0500 Jack Humbert
* 06c64bbff3e228df542149acde64eadaf59b9b0f Mon Dec 19 11:18:18 2016 -0500 Jack Humbert
* 438a5d685bb7b726ff59109ce4229eca6303cd8e Tue Dec 20 19:38:22 2016 -0500 Jack Humbert

## quantum/audio/wave.h 

* 73228f5e5d1d4cd31a46e5e93aa893a8f727e3b9 Thu Apr 21 00:37:45 2016 -0400 Jack Humbert

## quantum/keymap_extras/keymap_bepo.h 

* 7c33f8493fb4ecd664390232c8de856158f9fcae Sun Feb 7 19:29:49 2016 +0100 Didier Loiseau
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 7b4d30ee50aa534a973473c715924964991739f0 Sun Jul 24 10:57:49 2016 +0200 Vivien Alger

## quantum/keymap_extras/keymap_br_abnt2.h 

* 7aa31ad338325477199f752ac3e344a6ab9b27d0 Tue Nov 8 13:32:04 2016 -0200 Potiguar Faga

## quantum/keymap_extras/keymap_canadian_multilingual.h 

* a7cef2ca0a2322448d02008337013936b1d550ec Wed Feb 17 21:45:38 2016 +0100 Didier Loiseau
* 7840e69bfaee1d67de273c235b532d6f20c905a9 Thu Feb 18 00:47:23 2016 +0100 Didier Loiseau
* 911222892ecb1c01551e0abdfbe98ed1dbf82139 Fri Feb 26 00:55:39 2016 +0100 Didier Loiseau
* 3a91ddb0745ae0f52007984793ea1b48abb2098c Tue Mar 1 22:59:38 2016 +0100 Didier Loiseau
* aa5eb49edd993e2abe3adf814e030fcdda4a3596 Wed Mar 2 00:22:41 2016 +0100 Didier Loiseau
* 1aeb59335f2fe67613df25308a630ca453975ac0 Sun Sep 11 02:19:55 2016 +0200 Didier Loiseau

## quantum/keymap_extras/keymap_colemak.h 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* 39915b1748cefd99f841fa03b7f6e7c20439fbcf Thu Oct 29 15:12:51 2015 -0400 Jack Humbert
* 3c683aa9f23288ddada760fb49abcc5fa7324f5e Fri Feb 5 16:28:24 2016 +0200 Erez Zukerman
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert

## quantum/keymap_extras/keymap_dvorak.h 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* 233af3a41c69d456583bfcfd897233b9c117caa6 Mon Feb 22 13:06:26 2016 -0500 Keller-Laminar
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 4278d8861526ed285d9d00badcdc8c121454be60 Thu Jul 14 11:32:43 2016 -0500 Jonathan A. Kollasch
* f0021c9cb9e30d47d5a3ab5ec75e59e626c3d244 Mon Sep 19 14:25:44 2016 -0500 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_dvp.h 

* 6e003b1e3fa844cfde0069004e755aae7a9539f3 Wed Oct 19 23:45:55 2016 +0300 Artyom Mironov

## quantum/keymap_extras/keymap_fr_ch.h 

* 1934e8a270820ff6f08c95f4399b26162623e4e0 Sat Feb 20 14:01:28 2016 +0100 Vincent Pochet
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 25938a09a6bfb2624bc96841b53897eda532e293 Thu Jul 14 11:13:35 2016 -0500 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_french.h 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* 4a19cc054dc7aeb0a35613d608143bf51fa791cc Sat Feb 27 15:22:54 2016 +0100 Kévin Letord
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 010dd1308420e25b327fa4d5d6b13f67a849408b Thu Jul 14 11:04:25 2016 -0500 Jonathan A. Kollasch
* 25938a09a6bfb2624bc96841b53897eda532e293 Thu Jul 14 11:13:35 2016 -0500 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_french_osx.h 

* 48eff6dd89672c6c71afd8a3d1cdc5d35b0bf768 Tue Jan 5 10:49:36 2016 +0100 Sébastien Pérochon
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert

## quantum/keymap_extras/keymap_german.h 

* 3dbcad51d1217b32c3c17917c2646fa7a9a9165b Sat Dec 19 01:22:12 2015 +0100 Matthias Schmitt
* da09312dd56e3b085fb217cc7cc2abf06f401992 Tue Jan 19 20:04:08 2016 +0100 plgruener
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 25938a09a6bfb2624bc96841b53897eda532e293 Thu Jul 14 11:13:35 2016 -0500 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_german_ch.h 

* 465aabe11dbd673fb4c68ecbffbfb062273def1a Wed May 18 21:22:04 2016 +0200 heartsekai
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 25938a09a6bfb2624bc96841b53897eda532e293 Thu Jul 14 11:13:35 2016 -0500 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_german_osx.h 

* e44c30f2030dd4c481a6e38e9392f147be7b0ae2 Fri Jan 15 15:55:00 2016 +0100 Stephan Bösebeck
* bfc6eca44aeb3ad22a1c37206005dcfe617431cd Mon Mar 14 13:35:34 2016 +0100 Daniel Kriesten
* dbd4ab3457dd001ab4bbcec14315047b815f7dfe Thu Mar 31 23:15:59 2016 +0200 Stephan Bösebeck
* 6d40f7c5060f608068b0c4fc90871687c70b4f05 Sun Apr 17 22:19:47 2016 +0200 Stephan Bösebeck
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 1a0bac8bccf0e156d2f3c5f14a7214f9677b6370 Tue Jun 21 17:42:29 2016 -0400 Jack Humbert

## quantum/keymap_extras/keymap_jp.h 

* 2febf9b9f7d610fc2eca666a842272cb90a87919 Tue Nov 22 20:40:12 2016 +0900 h-youhei

## quantum/keymap_extras/keymap_neo2.h 

* 7b7870bae178c80138be5c587238fdedeb837df9 Sat Dec 19 01:41:23 2015 +0100 Matthias Schmitt
* 4ca43225011ac94bd0a7976baf7f84059274dfbf Fri Feb 19 21:04:30 2016 +0100 plgruener
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* e329729d3a11b5798f4e2b9f65ac9bc2dcc84a9e Tue Jun 21 18:32:28 2016 -0400 Jack Humbert

## quantum/keymap_extras/keymap_nordic.h 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* c29ad125a7a58d5a2ced0a619165204136da9019 Fri Feb 5 01:50:54 2016 +0100 Fernando Mendonca
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 25938a09a6bfb2624bc96841b53897eda532e293 Thu Jul 14 11:13:35 2016 -0500 Jonathan A. Kollasch
* 283ebbe14298fe75128765fa42c46f02534fb761 Mon Jul 25 12:50:27 2016 +0200 Andreas Lindhé
* 555e41d9e5f8d393637898e2c77c64066b648245 Fri Dec 2 13:03:51 2016 -0500 Erez Zukerman

## quantum/keymap_extras/keymap_norwegian.h 

* e329729d3a11b5798f4e2b9f65ac9bc2dcc84a9e Tue Jun 21 18:32:28 2016 -0400 Jack Humbert
* b6fa762234fb5a3590d0ff91ffdf5aa3ae322c8f Mon Jul 25 11:29:54 2016 +0200 Andreas Lindhé

## quantum/keymap_extras/keymap_plover.h 

* 7ccfaf750d08bdb3a25ef2869cac251b7cd4d3ad Sat Apr 23 18:49:10 2016 +0100 James ‘Twey’ Kay
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert

## quantum/keymap_extras/keymap_russian.h 

* c5ee24a6c3ea39e9725dfc276c92d5bce726ca78 Sun Aug 7 11:01:12 2016 -0500 kuel
* 2a0121a78643b1dc774d82352f8c9e246010803e Sun Aug 7 11:07:38 2016 -0500 kuel

## quantum/keymap_extras/keymap_spanish.h 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 132c04746910f7230b63ed33717c4ed65599ed1b Sat Jul 2 10:26:04 2016 +0200 Rubén Díaz-Jorge
* 25938a09a6bfb2624bc96841b53897eda532e293 Thu Jul 14 11:13:35 2016 -0500 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_uk.h 

* 46e7fb2d3ccd699c0a1b1fd9d02860b1f2a44141 Mon Oct 26 14:49:46 2015 -0400 Jack Humbert
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 010dd1308420e25b327fa4d5d6b13f67a849408b Thu Jul 14 11:04:25 2016 -0500 Jonathan A. Kollasch
* 25938a09a6bfb2624bc96841b53897eda532e293 Thu Jul 14 11:13:35 2016 -0500 Jonathan A. Kollasch

## quantum/keymap_extras/keymap_unicode_cyrillic.h 

* c5ee24a6c3ea39e9725dfc276c92d5bce726ca78 Sun Aug 7 11:01:12 2016 -0500 kuel

## quantum/process_keycode/process_chording.c 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert

## quantum/process_keycode/process_chording.h 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert

## quantum/process_keycode/process_leader.c 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert

## quantum/process_keycode/process_leader.h 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert

## quantum/process_keycode/process_midi.c 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 8b94e26d7c3b30cc57d710a11e5651d15e8e3b20 Sun Jul 24 22:07:43 2016 -0400 Jack Humbert
* 8d99140d1b80bf497b2198138d3f481e93b0fbab Thu Sep 29 14:46:10 2016 -0500 Adam Gausmann

## quantum/process_keycode/process_midi.h 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert

## quantum/process_keycode/process_music.c 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 3ea738e450e9326b0d3ee4192da881cffb4c13c1 Sun Jul 24 10:00:39 2016 -0400 Robert Dale
* ae95834f5af7404c04e6fe3446019046278d814b Mon Dec 12 16:06:41 2016 -0500 Jack Humbert
* 273faa4d9cd5a84207548f83ba550c9efee90933 Fri Dec 23 20:59:00 2016 -0500 Jack Humbert
* 841d7e6a1d74b1fc45575ed551132ec27353ebf3 Mon Jan 23 13:55:24 2017 -0500 Jack Humbert

## quantum/process_keycode/process_music.h 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert

## quantum/process_keycode/process_printer.c 

* a889b899e2cf52b3b7807d8a7ad39f12e0761a10 Sun Oct 16 16:03:56 2016 -0400 Jack Humbert

## quantum/process_keycode/process_printer.h 

* a889b899e2cf52b3b7807d8a7ad39f12e0761a10 Sun Oct 16 16:03:56 2016 -0400 Jack Humbert

## quantum/process_keycode/process_printer_bb.c 

* a889b899e2cf52b3b7807d8a7ad39f12e0761a10 Sun Oct 16 16:03:56 2016 -0400 Jack Humbert

## quantum/process_keycode/process_tap_dance.c 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 1a7e954f9fc4d250ba1ae46e3bfc168aca2b5cce Wed Jul 13 00:20:28 2016 +0200 Pavlos Vinieratos
* f3b56701ed7e6c622dc48e429780124ba5fde172 Wed Jul 13 16:47:45 2016 +0200 Pavlos Vinieratos
* d3091faf363afc8fef73ddf4948f872439b0e827 Fri Jul 15 23:54:08 2016 +0200 Pavlos Vinieratos
* dda2fd6ff3984ed96f8275c661b47a0484f9ee18 Mon Jul 18 23:34:02 2016 +0200 Pavlos Vinieratos
* d5daec2a58019ebdb9804787e0f786e4fc3c05b9 Tue Jul 19 18:00:59 2016 +0200 Pavlos Vinieratos
* 4e6a8627d8ebd7af942f68142d1a959d60361d90 Tue Jul 19 18:02:13 2016 +0200 Pavlos Vinieratos
* 70e42489dec375e558d8e81ed5ebfb69b4f3dbd9 Wed Jul 20 10:22:52 2016 +0200 Gergely Nagy
* ce8cc9219fca5dde077f1142d03d011b38d27479 Wed Jul 20 11:34:45 2016 +0200 Gergely Nagy
* 44e16ffc80620b61eaa17aedcfdd8233d9c99bd9 Wed Jul 20 11:49:59 2016 +0200 Gergely Nagy
* b21e8b97acb722bfa7b85831cfd010716ed77962 Wed Jul 27 08:42:09 2016 +0200 Gergely Nagy
* d78058cc75a9b05a6885991506d5f807ebb2a9f9 Wed Aug 17 10:28:08 2016 +0200 Gergely Nagy
* 29f64d7a93d941167c6c6e95f893ab84586b2205 Wed Aug 17 13:04:50 2016 +0200 Gergely Nagy
* 0d28787c5cf2173d12f57b397515f91cffaa820a Thu Aug 18 11:29:53 2016 +0200 Gergely Nagy
* acda2b793f69c6e0e9b9667e9ebe8a0325eb5ecd Thu Sep 1 08:32:47 2016 +0200 Gergely Nagy
* e1f131db8e59c6ed3471906d3a62457d593f51af Wed Sep 21 10:11:42 2016 +0200 Pavlos Vinieratos

## quantum/process_keycode/process_tap_dance.h 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* f3b56701ed7e6c622dc48e429780124ba5fde172 Wed Jul 13 16:47:45 2016 +0200 Pavlos Vinieratos
* d3091faf363afc8fef73ddf4948f872439b0e827 Fri Jul 15 23:54:08 2016 +0200 Pavlos Vinieratos
* 70e42489dec375e558d8e81ed5ebfb69b4f3dbd9 Wed Jul 20 10:22:52 2016 +0200 Gergely Nagy
* ce8cc9219fca5dde077f1142d03d011b38d27479 Wed Jul 20 11:34:45 2016 +0200 Gergely Nagy
* b21e8b97acb722bfa7b85831cfd010716ed77962 Wed Jul 27 08:42:09 2016 +0200 Gergely Nagy
* 29f64d7a93d941167c6c6e95f893ab84586b2205 Wed Aug 17 13:04:50 2016 +0200 Gergely Nagy
* 0edc82f0300924394324e2f3c4d2f8f0008439db Wed Sep 21 11:29:34 2016 +0200 Pavlos Vinieratos
* cda4b534fa4921c2d8f9884aa6a144333e7b07c4 Wed Sep 21 11:29:43 2016 +0200 Pavlos Vinieratos

## quantum/process_keycode/process_unicode.c 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 8bdf745909bc2581491acce11225f56a85bc8f24 Sat Aug 13 10:33:47 2016 +0200 Gergely Nagy
* 63e5782d2cdf0ee282ad434c773463d9da9db6b3 Sat Aug 13 10:43:22 2016 +0200 Gergely Nagy
* fa06a163607e8c6c4bd0968c2de96a9a298b777c Sat Aug 13 10:46:38 2016 +0200 Gergely Nagy
* 0b6861827faea747345ea38202d64c8004ab128c Sat Aug 13 11:11:22 2016 +0200 Gergely Nagy
* 857aa5bef6a74f8785a7039feea5286c07bf7067 Sat Aug 13 11:14:42 2016 +0200 Gergely Nagy
* 234dd276cf03be6fd6961473e9d9c8f35deec682 Sun Aug 14 10:37:51 2016 +0200 Gergely Nagy
* a312cbf712764277e0dbbbb99410c2f6fc6c7484 Sun Aug 14 14:34:52 2016 +0200 Gergely Nagy
* 43d08629cf275d0b32281ffe8785258fff226b49 Mon Aug 15 10:02:05 2016 +0200 Gergely Nagy
* e8845f0daf8dc7a7674dc5420cc5a684bbbea09b Mon Aug 15 10:07:13 2016 +0200 Gergely Nagy
* dffdeb50b79d3c623e2ed9fd1c1d82d6d0ae7bf0 Sun Aug 21 20:25:19 2016 +0200 coderkun
* 81594c7883deefedbcd317c72c1b1f1d32e65cd7 Sun Aug 21 21:02:18 2016 +0200 coderkun
* a058ae40e268b34ba5db45f5fd5d557d50fa5437 Wed Aug 24 15:39:23 2016 +0200 Gergely Nagy
* c9ea236fc35d350c0ff33de0af84d3dee7d0eb95 Wed Aug 31 08:21:52 2016 +0200 Gergely Nagy
* a3f5a4cf5839fe29dd37400d72c5e353812002f8 Sun Oct 2 10:35:09 2016 +0200 coderkun
* 5b2e455d3b71bfb90754930d1f22d3e8ce98b927 Mon Oct 10 00:46:20 2016 +0700 Priyadi Iman Nurcahyo
* e7d5dc89f2890007d776f6b613dc9deb473cff22 Sun Oct 23 05:36:26 2016 +0700 Priyadi Iman Nurcahyo
* 4a666c201007eacf13a9031e3c9b156e2e04afe6 Sun Oct 23 19:15:33 2016 +0700 Priyadi Iman Nurcahyo
* 8d60354d5a116b6cb1fc32eac7461eb125543c7d Wed Oct 26 00:48:44 2016 -0400 Jack Humbert
* 30b80a23f3cafd846937b37b249f2df4411e1f5a Mon Jan 9 02:59:10 2017 +0700 Priyadi Iman Nurcahyo

## quantum/process_keycode/process_unicode.h 

* 65faab3b89245f81c50b029ca178aed175d5f330 Wed Jun 29 17:49:41 2016 -0400 Jack Humbert
* 63e5782d2cdf0ee282ad434c773463d9da9db6b3 Sat Aug 13 10:43:22 2016 +0200 Gergely Nagy
* fa06a163607e8c6c4bd0968c2de96a9a298b777c Sat Aug 13 10:46:38 2016 +0200 Gergely Nagy
* 857aa5bef6a74f8785a7039feea5286c07bf7067 Sat Aug 13 11:14:42 2016 +0200 Gergely Nagy
* 234dd276cf03be6fd6961473e9d9c8f35deec682 Sun Aug 14 10:37:51 2016 +0200 Gergely Nagy
* a312cbf712764277e0dbbbb99410c2f6fc6c7484 Sun Aug 14 14:34:52 2016 +0200 Gergely Nagy
* 43d08629cf275d0b32281ffe8785258fff226b49 Mon Aug 15 10:02:05 2016 +0200 Gergely Nagy
* e8845f0daf8dc7a7674dc5420cc5a684bbbea09b Mon Aug 15 10:07:13 2016 +0200 Gergely Nagy
* a058ae40e268b34ba5db45f5fd5d557d50fa5437 Wed Aug 24 15:39:23 2016 +0200 Gergely Nagy
* c9ea236fc35d350c0ff33de0af84d3dee7d0eb95 Wed Aug 31 08:21:52 2016 +0200 Gergely Nagy
* 5b2e455d3b71bfb90754930d1f22d3e8ce98b927 Mon Oct 10 00:46:20 2016 +0700 Priyadi Iman Nurcahyo
* 4a666c201007eacf13a9031e3c9b156e2e04afe6 Sun Oct 23 19:15:33 2016 +0700 Priyadi Iman Nurcahyo
* 6fee7e178f7c949213a124d78de60bc30267d367 Sat Nov 26 23:53:15 2016 +0700 Priyadi Iman Nurcahyo

## quantum/serial_link/LICENSE 

* 639cdd363e35c13fe331939d0972aa4db5f5198d Tue Jul 5 23:27:47 2016 +0300 Fred Sundvik

## quantum/serial_link/README.md 

* 639cdd363e35c13fe331939d0972aa4db5f5198d Tue Jul 5 23:27:47 2016 +0300 Fred Sundvik
* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/byte_stuffer.c 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik
* 0a11460175d6a838c71343c19eb4ce4699936247 Wed Aug 24 22:23:17 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/byte_stuffer.h 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik
* 0a11460175d6a838c71343c19eb4ce4699936247 Wed Aug 24 22:23:17 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/frame_router.c 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/frame_router.h 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/frame_validator.c 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/frame_validator.h 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/physical.h 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/transport.c 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik
* bcdf9ab76bf3723e6015d4255d53e7c1e7259b61 Sat Aug 27 14:18:49 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/transport.h 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik
* bcdf9ab76bf3723e6015d4255d53e7c1e7259b61 Sat Aug 27 14:18:49 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/triple_buffered_object.c 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/protocol/triple_buffered_object.h 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/system/serial_link.c 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/system/serial_link.h 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/byte_stuffer_tests.cpp 

* 0a11460175d6a838c71343c19eb4ce4699936247 Wed Aug 24 22:23:17 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/frame_router_tests.cpp 

* cdd0913bcc63334fa20f1a7bd46bdce4d4f2843b Sat Aug 27 13:43:46 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/frame_validator_tests.cpp 

* b3eba797af74ace19b9f2e762bdd33d9449e3f94 Sat Aug 27 13:54:16 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/Makefile 

* d5e7603d551a31836bf0c59db259ddc3593a1aa7 Wed Jul 6 13:26:20 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/rules.mk 

* 0a11460175d6a838c71343c19eb4ce4699936247 Wed Aug 24 22:23:17 2016 +0300 Fred Sundvik
* cdd0913bcc63334fa20f1a7bd46bdce4d4f2843b Sat Aug 27 13:43:46 2016 +0300 Fred Sundvik
* b3eba797af74ace19b9f2e762bdd33d9449e3f94 Sat Aug 27 13:54:16 2016 +0300 Fred Sundvik
* bcdf9ab76bf3723e6015d4255d53e7c1e7259b61 Sat Aug 27 14:18:49 2016 +0300 Fred Sundvik
* ffb0a126f5b2484eda7f6b1c62ea61924eec6521 Sat Aug 27 14:25:52 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/testlist.mk 

* 6d7cd639a5e4503f00162c7cfa4bc7302b82c71c Sun Aug 21 16:29:54 2016 +0300 Fred Sundvik
* ffb0a126f5b2484eda7f6b1c62ea61924eec6521 Sat Aug 27 14:25:52 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/transport_tests.cpp 

* bcdf9ab76bf3723e6015d4255d53e7c1e7259b61 Sat Aug 27 14:18:49 2016 +0300 Fred Sundvik

## quantum/serial_link/tests/triple_buffered_object_tests.cpp 

* ffb0a126f5b2484eda7f6b1c62ea61924eec6521 Sat Aug 27 14:25:52 2016 +0300 Fred Sundvik

## quantum/template/config.h 

* 6f3141965e88c4ee0ebf7c18a243e4c2d9c5021b Tue Oct 27 14:33:18 2015 -0400 Jack Humbert
* 24f2698fba0055128eb90fbde793e3c84900df69 Sat Jan 23 20:45:52 2016 -0500 Jack Humbert
* 577971ab07a49405e1dcd8e5f75b3ecb87e710b9 Mon Mar 28 00:03:21 2016 -0500 IBNobody
* 1d13aa933bbb57bf0c1fe0196981b81233c3df97 Mon Mar 28 19:45:20 2016 -0500 IBNobody
* aaa758f1d3f97dda39879f2b055ad2da9680adfe Mon May 23 20:42:21 2016 -0700 Eric Tang
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert

## quantum/template/Makefile 

* 6f3141965e88c4ee0ebf7c18a243e4c2d9c5021b Tue Oct 27 14:33:18 2015 -0400 Jack Humbert
* 6485c7d7dae01c499a7e1f27e7956f12ce0f6901 Thu Nov 5 12:07:03 2015 -0500 Jack Humbert
* 24f2698fba0055128eb90fbde793e3c84900df69 Sat Jan 23 20:45:52 2016 -0500 Jack Humbert
* 577971ab07a49405e1dcd8e5f75b3ecb87e710b9 Mon Mar 28 00:03:21 2016 -0500 IBNobody
* 0656f2fa10e25e160617c3e5d14cfbae35dd9c8d Fri Apr 29 22:19:40 2016 -0400 Jack Humbert
* 38987d4c1589d2d457459f42e179be24b712be30 Sat May 28 12:05:17 2016 -0400 Jack Humbert
* d9e4dad0a828a8a904f44dda090a4d6d08fe2948 Sat Jun 11 13:31:31 2016 -0400 Jack Humbert
* a8375fa15a6ca9285eb15ae89bcda898349e06f8 Tue Jun 21 10:21:43 2016 -0400 Jack Humbert
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* ab4d7adbb96fa034fd20364247d615f527661594 Fri Aug 19 09:06:28 2016 +0300 Fred Sundvik

## quantum/template/readme.md 

* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* 1f5838a28679975f689e35471a35720ed5c7e7c5 Sat Aug 27 23:29:37 2016 +0300 Fred Sundvik

## quantum/template/rules.mk 

* ab4d7adbb96fa034fd20364247d615f527661594 Fri Aug 19 09:06:28 2016 +0300 Fred Sundvik

## quantum/template/template.c 

* 6f3141965e88c4ee0ebf7c18a243e4c2d9c5021b Tue Oct 27 14:33:18 2015 -0400 Jack Humbert
* 641859df84bf40025b2c14319d1a168a435562e2 Thu Mar 10 11:28:34 2016 -0500 yoyoerx
* eba9a7d74db0be548cddc107f0370dabf43b017f Tue Mar 15 23:52:51 2016 -0500 IBNobody
* ec62d9e85cab5cf166241b0536120d005fa7c898 Tue Mar 22 20:39:05 2016 -0500 IBNobody
* 3d56ec052ed485d4b717da930c4024b4a3f792e0 Tue Mar 22 21:06:22 2016 -0500 IBNobody
* 2181be029e01d9cf46ae3cadcdf25f5bca02c631 Mon Mar 28 16:13:37 2016 +0200 Damien Pollet
* 0656f2fa10e25e160617c3e5d14cfbae35dd9c8d Fri Apr 29 22:19:40 2016 -0400 Jack Humbert
* 1a8c0dd22d6a2255511d0db6a456315541b5815b Sun May 15 00:27:32 2016 -0400 Erez Zukerman
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert
* 589df84d6cd19ad7d776cc19bcddade1cd178ddc Thu Jul 7 09:58:44 2016 -0400 Jack Humbert
* c1dfb636ef61159456bdb24f4fee3f27e5babbeb Thu Jul 7 12:22:10 2016 -0400 Jack Humbert

## quantum/template/template.h 

* 6f3141965e88c4ee0ebf7c18a243e4c2d9c5021b Tue Oct 27 14:33:18 2015 -0400 Jack Humbert
* 24f2698fba0055128eb90fbde793e3c84900df69 Sat Jan 23 20:45:52 2016 -0500 Jack Humbert
* ee1b94045e5bebda517119cb1853b0ab3fd0f499 Fri Mar 4 10:53:58 2016 -0500 Noah Andrews
* 641859df84bf40025b2c14319d1a168a435562e2 Thu Mar 10 11:28:34 2016 -0500 yoyoerx
* eba9a7d74db0be548cddc107f0370dabf43b017f Tue Mar 15 23:52:51 2016 -0500 IBNobody
* ec62d9e85cab5cf166241b0536120d005fa7c898 Tue Mar 22 20:39:05 2016 -0500 IBNobody
* 2181be029e01d9cf46ae3cadcdf25f5bca02c631 Mon Mar 28 16:13:37 2016 +0200 Damien Pollet
* 0656f2fa10e25e160617c3e5d14cfbae35dd9c8d Fri Apr 29 22:19:40 2016 -0400 Jack Humbert
* 1a8c0dd22d6a2255511d0db6a456315541b5815b Sun May 15 00:27:32 2016 -0400 Erez Zukerman
* db32864ce7029d758f57729cc2f75e051a28d0a2 Sat Jun 18 14:30:24 2016 -0400 Jack Humbert
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert

## quantum/template/keymaps/default/config.h 

* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert

## quantum/template/keymaps/default/keymap.c 

* d9e4dad0a828a8a904f44dda090a4d6d08fe2948 Sat Jun 11 13:31:31 2016 -0400 Jack Humbert
* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert

## quantum/template/keymaps/default/Makefile 

* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert

## quantum/template/keymaps/default/readme.md 

* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert

## quantum/tools/eeprom_reset.hex 

* 0b0ec82427aff54481103559066213056b6d7598 Sat Apr 16 00:01:22 2016 -0400 Jack Humbert

## quantum/tools/readme.md 

* 13bb6b4b7fdd2b3e419d0f89c93fb980b00eeb9b Thu Jun 23 22:18:20 2016 -0400 Jack Humbert

## quantum/visualizer/lcd_backlight.c 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik

## quantum/visualizer/lcd_backlight.h 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik

## quantum/visualizer/led_test.c 

* 6c296557909501b71fe344ce379e74094cf77c8e Wed Jul 6 20:30:58 2016 +0300 Fred Sundvik
* 07d0d5cbe48d7afaf0bc8c9916d40179ec51cb42 Thu Jul 7 12:46:10 2016 +0300 Fred Sundvik

## quantum/visualizer/led_test.h 

* 6c296557909501b71fe344ce379e74094cf77c8e Wed Jul 6 20:30:58 2016 +0300 Fred Sundvik

## quantum/visualizer/LICENSE.md 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik

## quantum/visualizer/readme.md 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik

## quantum/visualizer/visualizer.c 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik
* 6c296557909501b71fe344ce379e74094cf77c8e Wed Jul 6 20:30:58 2016 +0300 Fred Sundvik
* 70797bb8f21c72cba15b314b2d0a6684bfedc369 Thu Jul 7 00:20:20 2016 +0300 Fred Sundvik
* 7229751ba9d402b2a6c9dc1b7b29385b5162fe41 Thu Jul 7 14:01:20 2016 +0300 Fred Sundvik
* dae7c9bfb3325412c542fbbe4342c9c8e0fc1904 Thu Jul 7 14:12:56 2016 +0300 Fred Sundvik
* 9eb8d05246fba4f46c04b8fa1884b8f2d2ee0664 Tue Jan 17 21:47:07 2017 -0500 SjB

## quantum/visualizer/visualizer.h 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik
* 6c296557909501b71fe344ce379e74094cf77c8e Wed Jul 6 20:30:58 2016 +0300 Fred Sundvik
* 70797bb8f21c72cba15b314b2d0a6684bfedc369 Thu Jul 7 00:20:20 2016 +0300 Fred Sundvik
* 9eb8d05246fba4f46c04b8fa1884b8f2d2ee0664 Tue Jan 17 21:47:07 2017 -0500 SjB

## quantum/visualizer/visualizer.mk 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik
* 6c296557909501b71fe344ce379e74094cf77c8e Wed Jul 6 20:30:58 2016 +0300 Fred Sundvik
* 70797bb8f21c72cba15b314b2d0a6684bfedc369 Thu Jul 7 00:20:20 2016 +0300 Fred Sundvik
* 07d0d5cbe48d7afaf0bc8c9916d40179ec51cb42 Thu Jul 7 12:46:10 2016 +0300 Fred Sundvik
* 7229751ba9d402b2a6c9dc1b7b29385b5162fe41 Thu Jul 7 14:01:20 2016 +0300 Fred Sundvik
* aaac254ebce2005272e7385488b5690bbbe6d7c8 Thu Jul 7 14:29:53 2016 +0300 Fred Sundvik
* caedec92d2c22480313c43a364408fb920c55364 Thu Jul 7 14:42:16 2016 +0300 Fred Sundvik

## quantum/visualizer/example_integration/callbacks.c 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik

## quantum/visualizer/example_integration/gfxconf.h 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik

## quantum/visualizer/example_integration/lcd_backlight_hal.c 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik

## quantum/visualizer/example_integration/visualizer_user.c 

* 9f33a5593cc70dfb0885328061f1aa4b2c2fa386 Wed Jul 6 20:15:45 2016 +0300 Fred Sundvik