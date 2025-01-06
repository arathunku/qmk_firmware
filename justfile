set unstable := true

moonlander name="arathunku":
    #!/usr/bin/env nix-shell
    #!nix-shell {{justfile_directory()}}/shell.nix
    #!nix-shell -i bash

    qmk setup zsa/qmk_firmware -b firmware24
    make "zsa/moonlander:{{name}}"
    just maybe-flash "moonlander_{{name}}"

[confirm('Flash keyboard? Requires clicking reset. Y/n')]
maybe-flash binname="moonlander_arathunku":
    wally-cli ./{{binname}}.bin
    ~/bin/keyboard

unpack-latest zip:
    test -f {{zip}}
    unzip -oj {{zip}} -d {{justfile_directory()}}/keyboards/zsa/moonlander/keymaps/arathunku-oryx

