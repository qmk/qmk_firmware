cd $HOME
git clone https://github.com/qmk/qmk_userspace.git
qmk config user.overlay_dir="$(realpath qmk_userspace)"
