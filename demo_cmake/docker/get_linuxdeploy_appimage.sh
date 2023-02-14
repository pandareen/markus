#!/bin/sh -xe
# Script to install osxcross with SDK


[ "$LINUXDEPLOY_QT_GIT" ] || LINUXDEPLOY_QT_GIT="https://github.com/linuxdeploy/linuxdeploy-plugin-appimage.git"

# Init the package system
apt update

echo
echo '--> Save the original installed packages list'
echo

dpkg --get-selections | cut -f 1 > /tmp/packages_orig.lst

echo
echo '--> Install the required packages to install linuxdeploy-plugin-appimage '
echo

apt install -y git libboost-filesystem-dev libboost-regex-dev cimg-dev wget patchelf nlohmann-json3-dev build-essential

echo
echo '--> Download & install the linuxdeploy-plugin-appimage '
echo

git clone "$LINUXDEPLOY_QT_GIT" /tmp/linuxdeploy-plugin-appimage 
git -C /tmp/linuxdeploy-plugin-appimage checkout master
git -C /tmp/linuxdeploy-plugin-appimage submodule update --init --recursive

cmake /tmp/linuxdeploy-plugin-appimage -B /tmp/linuxdeploy-plugin-appimage-build -G Ninja -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release -DUSE_CCACHE=OFF
cmake --build /tmp/linuxdeploy-plugin-appimage-build

mkdir -p /usr/local/bin

mv /tmp/linuxdeploy-plugin-appimage-build/src/linuxdeploy-plugin-appimage /usr/local/bin

echo
echo '--> Restore the packages list to the original state'
echo

dpkg --get-selections | cut -f 1 > /tmp/packages_curr.lst
grep -Fxv -f /tmp/packages_orig.lst /tmp/packages_curr.lst | xargs apt remove -y --purge

# Complete the cleaning

apt -qq clean
rm -rf /var/lib/apt/lists/* /tmp/linuxdeploy*
