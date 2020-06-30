{ avr ? true, arm ? true, teensy ? true }:

let
  overlay = self: super:
    let addDarwinSupport = pkg: pkg.overrideAttrs (oldAttrs: {
      meta.platforms = (oldAttrs.meta.platforms or []) ++ self.lib.platforms.darwin;
    });
    in {
      dfu-programmer = addDarwinSupport super.dfu-programmer;
      teensy-loader-cli = addDarwinSupport super.teensy-loader-cli;
    };

  nixpkgs = builtins.fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/903266491b7b9b0379e88709feca0af900def0d9.tar.gz";
    sha256 = "1b5wjrfgyha6s15k1yjyx41hvrpmd5szpkpkxk6l5hyrfqsr8wip";
  };

  pkgs = import nixpkgs { overlays = [ overlay ]; };
in

with pkgs;
let 
  avrlibc = pkgsCross.avr.libcCross;

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

  buildInputs = [ dfu-programmer dfu-util diffutils git python3 ]
    ++ lib.optional avr [ 
      pkgsCross.avr.buildPackages.binutils
      pkgsCross.avr.buildPackages.gcc8
      avrlibc
      avrdude
    ]
    ++ lib.optional arm [ gcc-arm-embedded ]
    ++ lib.optional teensy [ teensy-loader-cli ];

  AVR_CFLAGS = lib.optional avr avr_incflags;
  AVR_ASFLAGS = lib.optional avr avr_incflags;
}
