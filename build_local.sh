#!/bin/sh

# Clear out any firmware files
rm --force *.hex
rm --force *.uf2

# Ensure QMK CLI is installed
if ! command -v qmk >/dev/null 2>&1; then
    errcho "QMK CLI not found"
    errcho "Install with pipx install qmk"
    exit 2
fi

# Checkout QMK repository
if [ -d "qmk_firmware" ]; then
    echo "QMK repository already exists, pulling latest changes"
    cd qmk_firmware
    git pull
    cd ..
else
    echo "QMK repository does not exist, cloning"
    git clone --depth 1 --recurse-submodules https://github.com/qmk/qmk_firmware
fi

# Copy files to QMK repository
if [ ! -L "qmk_firmware/keyboards/crkbd/keymaps/kwmlodozeniec" ]; then
    echo "Symlink keymaps in QMK repository"
    ln --symbolic --force --no-dereference $(pwd)/crkbd/kwmlodozeniec qmk_firmware/keyboards/crkbd/keymaps/
fi

# Build firmware
echo "Building firmware..."
cd qmk_firmware
qmk compile -kb crkbd/r2g -km kwmlodozeniec
qmk compile -kb crkbd/rev1 -km kwmlodozeniec
qmk compile -kb crkbd/rev1 -km kwmlodozeniec -e CONVERT_TO=kb2040
cd ..

# Copy firmware out of build directory
cp qmk_firmware/.build/*.hex .
cp qmk_firmware/.build/*.uf2 .
