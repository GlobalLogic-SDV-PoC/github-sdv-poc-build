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

echo 'deb [trusted=true] https://he-poc-repo-bucket-b997.s3.eu-west-1.amazonaws.com/ stable main' \
    | tee -a /etc/apt/sources.list.d/he-poc.list

apt update && apt install -y astemo-meta

update-alternatives --install /usr/bin/python python /usr/bin/python2.7 0

# Build flow
cp -a MakeFile_changed /opt/qcom_qnx/apps/qnx_ap/Makefile

mkdir -p ${HOME}/.qnx/
cp -a /opt/qcom_qnx/apps/qnx_ap/qnx_bins/license ${HOME}/.qnx/license

## (
##    /app/build.sh build all \
##    && /app/build.sh metabuild \
##    && /app/build.sh collect
##    du -sb ./out_collect
## )
