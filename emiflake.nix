{ avr ? true, arm ? true, teensy ? true }:
let
  # We specify sources via Niv: use "niv update nixpkgs" to update nixpkgs, for example.
  sources = import ./util/nix/sources.nix { };
  pkgs = import sources.nixpkgs { };

  poetry2nix = pkgs.callPackage (import sources.poetry2nix) { };

  # Builds the python env based on nix/pyproject.toml and
  # nix/poetry.lock Use the "poetry update --lock", "poetry add
  # --lock" etc. in the nix folder to adjust the contents of those
  # files if the requirements*.txt files change
  pythonEnv = poetry2nix.mkPoetryEnv {
    projectDir = ./util/nix;
    overrides = poetry2nix.overrides.withDefaults (self: super: {
      qmk = super.qmk.overridePythonAttrs (old: {
        # Allow QMK CLI to run "bin/qmk" as a subprocess (the wrapper changes
        # $PATH and breaks these invocations).
        dontWrapPythonPrograms = true;
      });
    });
  };
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
  name = "emiflake";
  src = ./.;

  buildInputs = [
    clang-tools
    dfu-programmer
    dfu-util
    diffutils
    git
    pythonEnv
    poetry
    niv
    which
    pkgsCross.avr.buildPackages.binutils
    pkgsCross.avr.buildPackages.gcc8
    avrlibc
    avrdude
    gcc-arm-embedded
    teensy-loader-cli
    gcc-arm-embedded
  ];

  AVR_CFLAGS = lib.optional avr avr_incflags;
  AVR_ASFLAGS = lib.optional avr avr_incflags;

  buildPhase = ''
    make planck/rev6:emiflake:hex
  '';

  installPhase = ''
    mv .build/planck_rev6_emiflake.hex $out
  '';
}
