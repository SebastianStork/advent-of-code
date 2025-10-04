{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";

    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs =
    { nixpkgs, rust-overlay, ... }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system} = {
        cpp = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
          packages = with pkgs; [
            gdb
            clang-tools
            qt6.full
          ];
        };

        go = pkgs.mkShellNoCC {
          packages = with pkgs; [ go ];
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
