{
  description = "QMK firmware";

  # Input dependencies are loaded on the dirty flake side via Niv.
  # This pattern is inspired by https://github.com/crazazy/niv-flakes.
  outputs = args: let
    dirtyFlake = import ./util/nix/dirty-flake.nix;
    shellNix-path = ./shell.nix;
  in
    dirtyFlake.outputs (args // {inherit shellNix-path;} // dirtyFlake.inputs);
}
