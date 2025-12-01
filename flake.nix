{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.11";

    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    inputs = {
      url = "git+ssh://git@github.com/SebastianStork/advent-of-code-inputs.git?shallow=1";
      flake = false;
    };
  };

  outputs =
    {
      nixpkgs,
      rust-overlay,
      inputs,
      ...
    }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system} = {
        default = pkgs.mkShellNoCC {
          packages = [ pkgs.stow ];
          shellHook = ''
            stow --dir=${inputs} --target=./. package
          '';
        };

        cpp = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
          packages = [
            pkgs.gdb
            pkgs.clang-tools
          ];
        };

        go = pkgs.mkShellNoCC {
          packages = [ pkgs.go ];
        };

        rust =
          let
            pkgs = import nixpkgs {
              inherit system;
              overlays = [ rust-overlay.overlays.default ];
            };
            rust-toolchain = pkgs.rust-bin.stable.latest.default.override { extensions = [ "rust-src" ]; };
          in
          pkgs.mkShellNoCC {
            packages = [ rust-toolchain ];
            RUST_SRC_PATH = "${rust-toolchain}/lib/rustlib/src/rust/library";
          };
      };

      formatter.${system} = pkgs.nixfmt-tree;
    };
}
