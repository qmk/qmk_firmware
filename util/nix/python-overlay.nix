# `tomlkit` >= 0.8.0 is required to build `jsonschema` >= 4.11.0 (older
# version do not support some valid TOML syntax: sdispater/tomlkit#148).  The
# updated `tomlkit` must be used by `makeRemoveSpecialDependenciesHook`
# inside `poetry2nix`, therefore just providing the updated version through
# our `nix/pyproject.toml` does not work, and using an overlay is required.
final: prev: {
  python3 = prev.python3.override {
    packageOverrides = self: super: {
      tomlkit = super.tomlkit.overridePythonAttrs (old: rec {
        version = "0.11.4";
        src = super.fetchPypi {
          inherit (old) pname;
          inherit version;
          sha256 = "sha256-MjWpAQ+uVDI+cnw6wG+3IHUv5mNbNCbjedrsYPvUSoM=";
        };
      });
    };
  };
}
