{ avr ? true, arm ? true, teensy ? true }:

let
  nixpkgs = builtins.fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/1f77a4c8c74bbe896053994836790aa9bf6dc5ba.tar.gz";
    sha256 = "1j62nmzz3w33dplzf1xz1pg1pfkxii7lwdqmsxmc71cs9cm3s7n1";
  };

  pkgs = import nixpkgs { };

  pythonEnv = pkgs.python3.withPackages (p: with p; [
    # requirements.txt
    appdirs
    argcomplete
    colorama
    dotty-dict
    hjson
    jsonschema
    milc
    pygments
    # requirements-dev.txt
    nose2
    flake8
    pep8-naming
    yapf
  ]);
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
mkShell {
  name = "qmk-firmware";

  buildInputs = [ clang-tools dfu-programmer dfu-util diffutils git pythonEnv ]
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
  shellHook = ''
    # Prevent the avr-gcc wrapper from picking up host GCC flags
    # like -iframework, which is problematic on Darwin
    unset NIX_CFLAGS_COMPILE_FOR_TARGET
  '';
}
