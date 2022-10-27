{
  description = "QMK firmware dirty flake expression";

  # Load inputs from Niv and make them compatible with outputs args usage.
  inputs = let
    packageSources = import ./sources.nix {};
  in {
    flake-utils = import packageSources.flake-utils.outPath;
    nixpkgs = packageSources.nixpkgs.outPath;
    poetry2nix-src = packageSources.poetry2nix;
  };

  outputs = {
    self,
    flake-utils,
    nixpkgs,
    poetry2nix-src,
    shellNix-path,
  }:
    {
      pythonOverlay = import ./python-overlay.nix;
    }
    // flake-utils.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          overlays = [self.pythonOverlay];
          inherit system;
        };

        poetry2nix = pkgs.callPackage poetry2nix-src {};
      in {
        devShells.default = pkgs.callPackage shellNix-path {inherit pkgs poetry2nix;};
      }
    );
}
