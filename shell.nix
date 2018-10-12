# dfu-programmer doesn't have darwin on it's list of supported platforms
{ pkgs ? import <nixpkgs> { config = { allowUnsupportedSystem = true; }; }
, avr ? true, arm ? true, teensy ? true }:

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
  avrgcc = pkgs.avrgcc.overrideAttrs (oldAttrs: rec {
    name = "avr-gcc-8.1.0";
    src = fetchurl {
      url = "mirror://gcc/releases/gcc-8.1.0/gcc-8.1.0.tar.xz";
      sha256 = "0lxil8x0jjx7zbf90cy1rli650akaa6hpk8wk8s62vk2jbwnc60x";
    };
  });
in

stdenv.mkDerivation {
  name = "qmk-firmware";

  buildInputs = [ dfu-programmer dfu-util diffutils git ]
    ++ lib.optional avr [ avrbinutils avrgcc avrlibc avrdude ]
    ++ lib.optional arm [ gcc-arm-embedded ]
    ++ lib.optional teensy [ teensy-loader-cli ];

  CFLAGS = lib.optional avr avr_incflags;
  ASFLAGS = lib.optional avr avr_incflags;
}
