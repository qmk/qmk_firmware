{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?rev=c0e881852006b132236cbf0301bd1939bb50867e";
    # nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    poetry2nix = {
      url = "github:nix-community/poetry2nix?rev=88ffae91c605aaafc2797f4096ca9f065152796a";
      # url = "github:nix-community/poetry2nix/master";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = args@{ self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        overlays = [ args.poetry2nix.overlay ];
        pkgs = import nixpkgs { inherit system overlays; };
        inherit (pkgs) lib pkgsCross;

        makeShell =
          { avr ? true
          , arm ? true
          , teensy ? true
          }:

          let
            avrlibc = pkgsCross.avr.libcCross;
            poetry2nix = pkgs.poetry2nix;

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
                pillow = super.pillow.overridePythonAttrs (old: {
                  # Use preConfigure from nixpkgs to fix library detection issues and
                  # impurities which can break the build process; this also requires
                  # adding propagatedBuildInputs and buildInputs from the same source.
                  propagatedBuildInputs = (old.buildInputs or [ ]) ++ pkgs.python3.pkgs.pillow.propagatedBuildInputs;
                  buildInputs = (old.buildInputs or [ ]) ++ pkgs.python3.pkgs.pillow.buildInputs;
                  preConfigure = (old.preConfigure or "") + pkgs.python3.pkgs.pillow.preConfigure;
                });
                qmk = super.qmk.overridePythonAttrs (old: {
                  # Allow QMK CLI to run "qmk" as a subprocess (the wrapper changes
                  # $PATH and breaks these invocations).
                  dontWrapPythonPrograms = true;
                });
              });
            };
          in
          pkgs.mkShell {
            name = "qmk-firmware";

            buildInputs = with pkgs;[
              clang-tools
              dfu-programmer
              dfu-util
              diffutils
              git
              pythonEnv
              niv
            ]
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

            # pass through no* attributes so they
            # can be combined (in any order) like this:
            # nix develop .#noAvr.noArm.noTeensy
            passthru =
              {
                noAvr = (makeShell { inherit arm teensy; avr = false; });
                noArm = (makeShell { inherit avr teensy; arm = false; });
                noTeensy = (makeShell { inherit avr arm; teensy = false; });
              };
          };
      in
      {
        # default shell with all options enabled
        # nix develop
        devShell = makeShell { };

        # disable any option using
        # nix develop .#noArm
        # nix develop .#noTeensy.noArm
        devShells = {
          noAvr = makeShell { avr = false; };
          noArm = makeShell { arm = false; };
          noTeensy = makeShell { teensy = false; };
        };
      }
    );
}
