{ pkgs ? import <nixpkgs> {}
, avr ? true, arm ? true }:

with pkgs;
let
  avr_incflags = [
    "-isystem ${avrlibc}/avr/include"
    "-B${avrlibc}/avr/lib/avr5"
    "-L${avrlibc}/avr/lib/avr5"
    "-B${avrlibc}/avr/lib/avr35"
    "-L${avrlibc}/avr/lib/avr35"
    "-B${avrlibc}/avr/lib/avr51"
    "-L${avrlibc}/avr/lib/avr51"
  ];
in

stdenv.mkDerivation {
  name = "qmk-firmware";

  buildInputs = [ dfu-programmer dfu-util diffutils git ]
    ++ lib.optional avr [ avrbinutils avrgcc avrlibc ]
    ++ lib.optional arm [ gcc-arm-embedded ];

  CFLAGS = lib.optional avr avr_incflags;
  ASFLAGS = lib.optional avr avr_incflags;
}
