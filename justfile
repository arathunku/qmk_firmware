set unstable := true
# jj config set --repo 'revset-aliases."trunk()"' firmware25@origin
# [remote "upstream"]
#   url = git@github.com:zsa/qmk_firmware.git
#   fetch = +refs/heads/firmware25:refs/remotes/upstream/firmware25
#   tagOpt = --no-tags

setup:
  curl -fsSL https://install.qmk.fm | sh
  sudo apt install -y dos2unix
  uv tool install qmk
  export QMK_HOME="$(pwd)"
  qmk setup zsa/qmk_firmware -b firmware25

moonlander name="arathunku":
    make "zsa/moonlander/reva:{{name}}" && just maybe-flash "zsa_moonlander_{{name}}"

[confirm('Flash keyboard? Requires clicking reset. Y/n')]
maybe-flash binname="zsa_moonlander_arathunku":
    wally-cli ./{{binname}}.bin
    sleep 10 # time for booting
    ~/bin/keyboard

unpack-latest zip:
    test -f {{zip}}
    unzip -oj {{zip}} -d {{justfile_directory()}}/keyboards/zsa/moonlander/keymaps/arathunku-oryx

