let
  # We specify sources via Niv: use "niv update nixpkgs" to update nixpkgs, for example.
  sources = import ./util/nix/sources.nix { };

  # `tomlkit` >= 0.8.0 is required to build `jsonschema` >= 4.11.0 (older
  # version do not support some valid TOML syntax: sdispater/tomlkit#148).  The
  # updated `tomlkit` must be used by `makeRemoveSpecialDependenciesHook`
  # inside `poetry2nix`, therefore just providing the updated version through
  # our `nix/pyproject.toml` does not work, and using an overlay is required.
  pythonOverlay = final: prev: {
    python3 = prev.python3.override {
      packageOverrides = self: super: {
        tomlkit = super.tomlkit.overridePythonAttrs(old: rec {
          version = "0.11.4";
          src = super.fetchPypi {
            inherit (old) pname;
            inherit version;
            sha256 = "sha256-MjWpAQ+uVDI+cnw6wG+3IHUv5mNbNCbjedrsYPvUSoM=";
          };
        });
      };
    };
  };
in
# However, if you want to override Niv's inputs, this will let you do that.
{ pkgs ? import sources.nixpkgs { overlays = [ pythonOverlay ]; }
, poetry2nix ? pkgs.callPackage (import sources.poetry2nix) { }
, avr ? true
, arm ? true
, teensy ? true }:
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

  # Builds the python env based on nix/pyproject.toml and
  # nix/poetry.lock Use the "poetry update --lock", "poetry add
  # --lock" etc. in the nix folder to adjust the contents of those
  # files if the requirements*.txt files change
  pythonEnv = poetry2nix.mkPoetryEnv {
    projectDir = ./util/nix;
    overrides = poetry2nix.overrides.withDefaults (self: super: {
      pillow = super.pillow.overridePythonAttrs(old: {
        # Use preConfigure from nixpkgs to fix library detection issues and
        # impurities which can break the build process; this also requires
        # adding propagatedBuildInputs and buildInputs from the same source.
        propagatedBuildInputs = (old.buildInputs or []) ++ pkgs.python3.pkgs.pillow.propagatedBuildInputs;
        buildInputs = (old.buildInputs or []) ++ pkgs.python3.pkgs.pillow.buildInputs;
        preConfigure = (old.preConfigure or "") + pkgs.python3.pkgs.pillow.preConfigure;
      });
      qmk = super.qmk.overridePythonAttrs(old: {
        # Allow QMK CLI to run "qmk" as a subprocess (the wrapper changes
        # $PATH and breaks these invocations).
        dontWrapPythonPrograms = true;
      });
    });
  };
in
mkShell {
  name = "qmk-firmware";

  buildInputs = [ clang-tools dfu-programmer dfu-util diffutils git pythonEnv niv ]
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
