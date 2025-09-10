{
  # To update this flake, run `nix flake update --flake ./util/nix`
  description = "Development shell for QMK firmware";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = with pkgs; mkShell {
          packages = [
            # The `qmk` package in nixpkgs comes magically bundled with most of
            # the dependencies needed as well as the `qmk` CLI tool.
            qmk
            # Needed to build/display the docs
            doxygen
            yarn
          ];
        };
      }
    );
}
