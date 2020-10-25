{ avr ? true, arm ? true, teensy ? true }:

let
  nixpkgs = builtins.fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/903266491b7b9b0379e88709feca0af900def0d9.tar.gz";
    sha256 = "1b5wjrfgyha6s15k1yjyx41hvrpmd5szpkpkxk6l5hyrfqsr8wip";
  };

  pkgs = import nixpkgs { };

  hjson = with pkgs.python3Packages; buildPythonPackage rec {
    pname = "hjson";
    version = "3.0.1";

    src = fetchPypi {
      inherit pname version;
      sha256 = "1yaimcgz8w0ps1wk28wk9g9zdidp79d14xqqj9rjkvxalvx2f5qx";
    };
    doCheck = false;
  };

  pythonEnv = pkgs.python3.withPackages (p: with p; [
    # requirements.txt
    appdirs
    argcomplete
    colorama
    hjson
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

  buildInputs = [ dfu-programmer dfu-util diffutils git pythonEnv ]
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
    unset NIX_TARGET_CFLAGS_COMPILE
  '';
}
