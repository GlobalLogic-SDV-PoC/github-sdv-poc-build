#!/usr/bin/env bash

# Variables
SCRIPT_NAME=$(basename ${0})
REPO_ROOT_DIR=`pwd`
ASTEMO_VARIANT_DIR="/opt/qcom_qnx/apps/qnx_ap/target/hypervisor/astemo"
FLAVOR="astemo_a0"
export SECTOOLS="/opt/qcom_amss/common/sectoolsv2/ext/Linux/sectools"
export SECTOOLS_V2_ROOT="${SECTOOLS}"
export LLVM_VERSION="16.0.0"
export LLVMROOT="/opt/tools/llvm/16.0"
export MUSL32PATH="/opt/tools/llvm/16.0/armv7-none-eabi/libc"
export LLVMCLANG="/opt/tools/llvm/16.0/lib/clang/16.0.0"
export LLVMLIB="/opt/tools/llvm/16.0/lib/clang/16.0.0/lib/linux"
export MUSLPATH="/opt/tools/llvm/16.0/aarch64-none-elf/libc"
export LLVMTOOLPATH="/opt/tools/llvm/16.0/tools/bin"
export LLVMBIN="/opt/tools/llvm/16.0/bin"
export LLVMLIBPROP="/opt/tools/llvm/16.0/lib/clang/16.0.0/lib/linux-propri_rt"
export LLVMINC="/opt/tools/llvm/16.0/aarch64-none-elf/libc/include"
export LLVM32INC="/opt/tools/llvm/16.0/armv7-none-eabi/libc/include"
export PATH="/opt/tools/llvm/16.0/bin:${PATH}"
export PYTHONPATH="${PYTHONPATH}:/opt/qcom_qnx/common/build/lib"

# Functions
function check_build_dependencies {
    local dependencies=(
    )

    for dep in "${dependencies[@]}"; do
        [[ `which ${dep}` ]] ||
        [[ `dpkg -s ${dep}` ]] || {
            echo -e "${dep} is not installed on the host"
            exit -1
        }
    done

    local py_ver="$(python -V 2>&1)"
    if [[ "$py_ver" != *"2.7"* ]]; then
        echo "'python' executable shall be linked to Python 2.7.x"
        exit -1
    fi

    # Validate sectools
    if [[ ! -f "${SECTOOLS}" ]]; then
        echo "ERROR: '${SECTOOLS}' file doesn't exist"
        exit -1
    fi

    local sectools_blocked=0
    ${SECTOOLS} --version > /dev/null 2>&1 || sectools_blocked=$?
    if [[ ${sectools_blocked} -ne 0 ]]; then
        echo "ERROR: Sectools is not executed properly"
        echo "       Kindly check the reasons for sectools failure"
        echo "       Sectools path: ${SECTOOLS}"
        echo "       Try command: sectools --version"
        exit -1
    fi
}

function print_usage {
    echo -e "${SCRIPT_NAME} - build script for QDrive4.0 BSP building"
    echo -e ""
    echo -e "Usage:   ${SCRIPT_NAME} <options>"
    echo -e ""
    echo -e "Options:"
    echo -e "\t <-b|--build|build> [target] build target (See list of targets below)"
    echo -e "\t <-c|--clean|clean> [target] clean target building"
    echo -e "\t <-m|--metabuild|metabuild>  create metabuild"
    echo -e "\t <--collect|collect>         collect metabuild output to 'out_collect' directory"
    echo -e "\t <-f|--flavor> [flavor]      specify the build flavor (See list of flavors below. Default flavor is '${FLAVOR}')"
    echo -e "\t <-h|--help|help>            print script usage"
    echo -e ""
    echo -e "Targets:"
    echo -e "xbl, tz, qnx, cdt, all"
    echo -e ""
    echo -e "Flavors:"
    echo -e "astemo_a0, 8650_asic"
    echo -e ""
    echo -e "Examples:"
    echo -e "1. Build xbl:"
    echo -e "    ${SCRIPT_NAME} build xbl"
    echo -e "2. Clean xbl building:"
    echo -e "    ${SCRIPT_NAME} clean xbl"
    echo -e "3. Build all BSP:"
    echo -e "    ${SCRIPT_NAME} build all"
    echo -e "4. Create metabuild for 8650_asic flavor:"
    echo -e "    ${SCRIPT_NAME} metabuild -f 8650_asic"
    echo -e "5. Collect metabuild output for default flavor:"
    echo -e "    ${SCRIPT_NAME} collect"
    echo -e "6. Build CDT for astemo_a0 flavor:"
    echo -e "    ${SCRIPT_NAME} build cdt --flavor astemo_a0"

    exit
}

function build_xbl {
    python3 /opt/qcom_amss/boot/boot_images/boot_tools/buildex.py --variant AU -r RELEASE -t LeMans,QcomToolsPkg
    ${SECTOOLS} secure-image /opt/qcom_amss/boot/boot_images/Build/LeMansAU/Loader/RELEASE_CLANG140LINUX/AARCH64/xbl.elf --outfile /opt/qcom_amss/boot/boot_images/Build/LeMansAU/Loader/RELEASE_CLANG140LINUX/AARCH64/xbl.elf --image-id XBL --security-profile /opt/qcom_amss/boot/boot_images/ssg/security_profile/lemans_boot_security_profile.xml --sign --signing-mode TEST
}

function clean_xbl {
    python3 /opt/qcom_amss/boot/boot_images/boot_tools/buildex.py --variant AU -r RELEASE -t LeMans,QcomToolsPkg --build_flags=cleanall
}

function build_tz {
    python3 /opt/qcom_amss/tz/trustzone_images/build/ms/build_all.py -b TZ.XF.5.0 CHIPSET=lemans_qh
}

function clean_tz {
    python3 /opt/qcom_amss/tz/trustzone_images/build/ms/build_all.py -b TZ.XF.5.0 CHIPSET=lemans_qh --clean
}

function build_qnx {
    cd /opt/qcom_qnx/apps/qnx_ap
    source /opt/qcom_qnx/apps/qnx_ap/setenv_qos222.sh --external /opt/qnx_sdp/
    make
    cd ${REPO_ROOT_DIR}
}

function clean_qnx {
    cd /opt/qcom_qnx/apps/qnx_ap
    source /opt/qcom_qnx/apps/qnx_ap/setenv_qos222.sh --external /opt/qnx_sdp/
    make clean
    cd ${REPO_ROOT_DIR}
}

function build_cdt {
    CONFIG=/opt/qcom_qnx/boot/boot_images/boot/QcomPkg/Tools/astemo_cdt_configs/${FLAVOR}_cdt_config.xml
    if [[ ! -f "${CONFIG}" ]]; then
        echo "ERROR: '${CONFIG}' file doesn't exist."
        exit -3
    fi

    mkdir -p ${ASTEMO_VARIANT_DIR}/cdt/
    python2 /opt/qcom_qnx/boot/boot_images/boot/QcomPkg/Tools/cdt_generator.py ${CONFIG} ${ASTEMO_VARIANT_DIR}/cdt/${FLAVOR}_cdt.bin

    echo "CDT for ${FLAVOR} was created successfully."
}

function create_metabuild {
    local files=(
        boot/boot_images/boot/QcomPkg/Tools/storage/fh_loader/lsusb.exe
        boot/boot_images/boot/QcomPkg/Tools/storage/fh_loader/QSaharaServer.exe
        boot/boot_images/boot/QcomPkg/Tools/storage/fh_loader/fh_loader.exe
        boot/boot_images/boot/QcomPkg/Tools/binaries/logfs_ufs_8mb.bin
        boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Tools/storage/UFS/JtagProgrammer.cmm
        boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/imagefv.elf
        boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/JtagProgrammer.elf
        boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/prog_firehose_ddr.elf
        boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/prog_firehose_lite.elf
        boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/shrm.elf
        tz/trustzone_images/build/ms/bin/MAKAANAB/devcfg.mbn
        tz/trustzone_images/build/ms/bin/MAKAANAB/devcfg_auto.mbn
        tz/trustzone_images/build/ms/bin/MAKAANAB/devcfg_rfcomm.mbn
        tz/trustzone_images/build/ms/bin/MAKAANAB/qwes.mbn
        tz/trustzone_images/build/ms/bin/MAKAANAB/smplap32.mbn
        tz/trustzone_images/build/ms/bin/MAKAANAB/smplap64.mbn
        tz/trustzone_images/build/ms/bin/MAKAANAB/tz.mbn
    )

    for file in "${files[@]}"; do
        cp "/opt/qcom_amss/${file}" "/opt/qcom_qnx/${file}"
    done

    cp /opt/qcom_amss/boot/boot_images/Build/LeMansAU/Loader/RELEASE_CLANG140LINUX/AARCH64/xbl.elf /opt/qcom_qnx/boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/xbl.elf
    cp /opt/qcom_amss/boot/boot_images/Build/LeMansAU/xblconfig/auto_gen/xbl_config.elf /opt/qcom_qnx/boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/xbl_config.elf

    cd /opt/qcom_qnx/common/build
    python3 build.py --flavors=${FLAVOR},sail_nor
    cd ${REPO_ROOT_DIR}
}

function collect {
    rm -rf ${REPO_ROOT_DIR}/out_collect
    python3 ${REPO_ROOT_DIR}/build/collect.py --flavor=${FLAVOR} --contents_file /opt/qcom_qnx/contents.xml
    cp /opt/qcom_qnx/contents.xml ${REPO_ROOT_DIR}/out_collect/qcom_qnx/
    cp /opt/qcom_qnx/about.html ${REPO_ROOT_DIR}/out_collect/qcom_qnx/
    cp /opt/qcom_qnx/common/build/*.py ${REPO_ROOT_DIR}/out_collect/qcom_qnx/common/build/
    cp -r /opt/qcom_qnx/common/build/app ${REPO_ROOT_DIR}/out_collect/qcom_qnx/common/build/
    cp -r /opt/qcom_qnx/common/build/lib ${REPO_ROOT_DIR}/out_collect/qcom_qnx/common/build/
    cp -r /opt/qcom_qnx/sail ${REPO_ROOT_DIR}/out_collect/qcom_qnx/sail/
}

function parse_cmd_line {
    (( $# < 1 )) && print_usage

    while [[ $# -gt 0 ]]
    do
        key="${1}"
        value="${2}"

        case ${key} in
            -b|--build|build)
                ACTION="build"
                TARGET="${value}"
                if [[ -z "${TARGET}" ]]; then
                    break
                fi

                shift 2
                ;;

            -c|--clean|clean)
                ACTION="clean"
                TARGET="${value}"
                if [[ -z "${TARGET}" ]]; then
                    break
                fi

                shift 2
                ;;

            -m|--metabuild|metabuild)
                ACTION="metabuild"
                shift 1
                ;;

            --collect|collect)
                ACTION="collect"
                shift 1
                ;;

            -f|--flavor)
                echo "Selected flavor: ${value}"
                FLAVOR=${value}
                if [[ -z "${FLAVOR}" ]]; then
                    break
                fi

                shift 2
                ;;

            -h|--help|help)
                ACTION="help"
                break
                ;;

            *)
                echo -e "Unknown parameter: ${key}"
                echo -e "To get help run '${SCRIPT_NAME} -h | --help | help'"
                exit -2
                ;;
        esac
    done
}

function main {
    parse_cmd_line $@

    case ${ACTION} in
        build)
            check_build_dependencies
            case ${TARGET} in
                xbl)
                    clean_xbl && build_xbl
                    ;;

                tz)
                    clean_tz && build_tz
                    ;;

                qnx)
                    clean_qnx && build_qnx
                    ;;

                cdt)
                    build_cdt
                    ;;

                all|"")
                    clean_xbl && clean_tz && clean_qnx && \
                    build_xbl && build_tz && build_qnx
                    ;;

                *)
                    echo -e "Unknown target: ${TARGET}"
                    echo -e "To get help run '${SCRIPT_NAME} -h | --help | help'"
                    exit -2
                    ;;
            esac
            ;;

        clean)
            check_build_dependencies
            case ${TARGET} in
                xbl)
                    clean_xbl
                    ;;

                tz)
                    clean_tz
                    ;;

                qnx)
                    clean_qnx
                    ;;

                all|"")
                    clean_xbl
                    clean_tz
                    clean_qnx
                    ;;

                *)
                    echo -e "Unknown target: ${TARGET}"
                    echo -e "To get help run '${SCRIPT_NAME} -h | --help | help'"
                    exit -2
                    ;;
            esac
            ;;

        metabuild)
            check_build_dependencies
            create_metabuild
            ;;

        collect)
            check_build_dependencies
            collect
            ;;

        help)
            print_usage
            ;;

        *)
            echo -e "Unknown parameter: ${ACTION}"
            echo -e "To get help run '${SCRIPT_NAME} -h | --help | help'"
            exit -2
            ;;
    esac
}

main $@
