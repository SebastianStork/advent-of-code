{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system} = {
        cpp =
          pkgs.mkShell.override
            {
              stdenv = pkgs.clangStdenv;
            }
            {
              packages = with pkgs; [
                gdb
                clang-tools
                qt6.full
              ];
            };
        go = pkgs.mkShell {
          packages = with pkgs; [ go ];
        };
      };

      formatter.${system} = pkgs.nixfmt-rfc-style;
    };
}
