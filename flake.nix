{
  description = "QMK firmware";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/c0e881852006b132236cbf0301bd1939bb50867e";

  inputs.flake-utils.url = "github:numtide/flake-utils/c0e246b9b83f637f4681389ecabcb2681b4f3af0";

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    {
      # We specify sources via Niv: use "niv update nixpkgs" to update nixpkgs, for example.
      sources = import ./util/nix/sources.nix {};

      pythonOverlay = import ./util/nix/python-overlay.nix;
    }
    // flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          overlays = [self.pythonOverlay];
          inherit system;
        };

        poetry2nix = pkgs.callPackage (import self.sources.poetry2nix) {};
      in {
        devShells.default = pkgs.callPackage ./shell.nix {inherit pkgs poetry2nix;};
      }
    );
}
