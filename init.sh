#!/usr/bin/env bash

source /etc/os-release

set -x
set -u
set -e

apt update && apt install -y wget

wget https://packages.microsoft.com/config/ubuntu/${VERSION_ID}/packages-microsoft-prod.deb \
    -O packages-microsoft-prod.deb
dpkg -i packages-microsoft-prod.deb && rm -f packages-microsoft-prod.deb

echo 'deb [trusted=yes] http://security.ubuntu.com/ubuntu bionic-security main' \
    | tee -a /etc/apt/sources.list.d/bionic-security.list

apt update
## TODO: WIP. S3 repo with aptly
apt install -y /dists/*.deb ## Change me ASAP

update-alternatives --install /usr/bin/python python /usr/bin/python2.7 0

# Build flow
cp -a MakeFile_changed /opt/qcom_qnx/apps/qnx_ap/Makefile

mkdir -p ${HOME}/.qnx/
cp -a /opt/qcom_qnx/apps/qnx_ap/qnx_bins/license ${HOME}/.qnx/license

(
    /app/build.sh build all \
    && /app/build.sh metabuild \
    && /app/build.sh collect
    du -sb ./out_collect
)

sleep infinity
