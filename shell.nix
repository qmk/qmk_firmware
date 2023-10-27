let
  # We specify sources via Niv: use "niv update nixpkgs" to update nixpkgs, for example.
  sources = import ./util/nix/sources.nix { };
in
# However, if you want to override Niv's inputs, this will let you do that.
{ pkgs ? import sources.nixpkgs { }
, pyproject-nix ? pkgs.callPackage (import sources."pyproject.nix") { }
, avr ? true
, arm ? true
, teensy ? true }:

let
  inherit (pkgs) pkgsCross mkShell lib;

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

  pythonEnv = let
    python = pkgs.python3.override {
      packageOverrides = self: super: {
        # QMK isn't exposed as a Python module in nixpkgs, only as a top-level package.
        # Convert it to a Python module and add it to the Python set so it can be used in the withPackages call.
        qmk = ((self.toPythonModule pkgs.qmk).override { python3 = self.python; }).overrideAttrs(old: {
          # Allow QMK CLI to run "qmk" as a subprocess (the wrapper changes
          # $PATH and breaks these invocations).
          dontWrapPythonPrograms = true;
        });
      };
    };

    project = pyproject-nix.lib.project.loadRequirementsTxt {
      requirements = ./requirements-dev.txt;
    };
  in
    # Assert that versions from nixpkgs matches what's described in requirements.txt
    assert project.validators.validateVersionConstraints { inherit python; } == { }; (
      # Render requirements.txt into a Python withPackages environment
      python.withPackages (project.renderers.withPackages {
        inherit python;
        extraPackages = ps: [ ps.qmk ];
      })
    );

in
mkShell {
  name = "qmk-firmware";

  buildInputs = with pkgs; [
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
}
