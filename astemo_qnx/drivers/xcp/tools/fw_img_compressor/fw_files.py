def set_root_path(fw_root_path):
    sail_fw_file_paths = {
        "SAIL_HYP":
            {"sailhyp.elf": fw_root_path + "qcom_qnx/sail/sail_proc/build/ms/bin/DEBUG/signed/sailhyp.elf"},
        "SAIL_SW1":
            {"sailsw1.elf": fw_root_path + "qcom_qnx/sail/sail_proc/build/ms/bin/DEBUG/signed/sailsw1.elf"},
        "SAIL_SW2":
            {"sailsw2.elf": fw_root_path + "qcom_qnx/sail/sail_proc/build/ms/bin/DEBUG/signed/sailsw2.elf"},
        "SAIL_SW3":
            {"sailsw3.elf": fw_root_path + "qcom_qnx/sail/sail_proc/build/ms/bin/DEBUG/signed/sailsw3.elf"}
    }

    md_fw_file_paths = {
        "MD_ABL":
            {"abl_fastboot.elf": fw_root_path + "qcom_qnx/apps/qnx_ap/target/hypervisor/astemo/abl-image-lemans/signed/abl_fastboot.elf"},
        "MD_AOP":
            {"aop.mbn": fw_root_path + "qcom_qnx/aop/aop_proc/build/ms/bin/AAAAANAZO/lemansau/4PMIC/aop.mbn"},
        "MD_BOOT":
            {"boot_qdrive.img": fw_root_path + "qcom_qnx/apps/qnx_ap/target/hypervisor/astemo/out_lemans/boot_qdrive.img"},
        "MD_CPUCP":
            {"cpucp.elf": fw_root_path+"qcom_qnx/cpucp/cpucp_proc/lemansau/cpucp/cpucp.elf"},
        "MD_DDR":
            {"zeros_5sectors.bin": fw_root_path + "qcom_qnx/common/build/ufs/8650_asic/zeros_5sectors.bin"},
        "MD_DEVCFG":
            {"devcfg.mbn": fw_root_path + "qcom_qnx/tz/trustzone_images/build/ms/bin/MAKAANAB/devcfg.mbn"},
        "MD_DSPFW":
            {"dspnonfusafw.bin": fw_root_path + "qcom_qnx/common/build/ufs/8650_nonfusa/bin/dspnonfusafw.bin"},
        "MD_DSPLIB":
            {"dspnonfusalib.bin": fw_root_path + "qcom_qnx/common/build/ufs/8650_nonfusa/bin/dspnonfusalib.bin"},
        "MD_HYP":
            {"mifs_hyp_qdrive.img": fw_root_path + "qcom_qnx/apps/qnx_ap/target/hypervisor/astemo/out_lemans/signed/default/qhee/mifs_hyp_qdrive.img"},
        "MD_IFS2":
            {"ifs2_qdrive.img": fw_root_path + "qcom_qnx/apps/qnx_ap/target/hypervisor/astemo/out_lemans/ifs2_qdrive.img"},
        "MD_IMAGEFV":
            {"imagefv.elf": fw_root_path + "qcom_qnx/boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/imagefv.elf"},
        "MD_KEYMASTER":
            {"keymint.mbn": fw_root_path + "qcom_qnx/tz_apps/qtee_tas/build/ms/bin/MAKAANAA/keymint.mbn"},
        "MD_LOGFS":
            {"logfs_ufs_8mb.bin": fw_root_path + "qcom_qnx/boot/boot_images/boot/QcomPkg/Tools/binaries/logfs_ufs_8mb.bin"},
        "MD_MODEM":
            {"NON-HLOS.bin": fw_root_path + "qcom_qnx/common/build/ufs/8650_asic/bin/NON-HLOS.bin"},
        "MD_MULTIIMGOEM":
            {"multi_image.mbn": fw_root_path + "qcom_qnx/common/build/bin/ufs/8650_asic/multi_image.mbn"},
        "MD_PERSIST":
            {"persist_qnx.img": fw_root_path + "qcom_qnx/apps/qnx_ap/target/hypervisor/astemo/out_lemans/persist_qnx.img"},
        "MD_SHRM":
            {"shrm.elf": fw_root_path + "qcom_qnx/boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/shrm.elf"},
        "MD_SYSTEM":
            {"system_qdrive.img": fw_root_path + "qcom_qnx/apps/qnx_ap/target/hypervisor/astemo/out_lemans/system_qdrive.img"},
        "MD_TZ":
            {"tz.mbn": fw_root_path + "qcom_qnx/tz/trustzone_images/build/ms/bin/MAKAANAB/tz.mbn"},
        "MD_XBL":
            {"xbl.elf": fw_root_path + "qcom_qnx/boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/xbl.elf"},
        "MD_XBL_CONFIG":
            {"xbl_config.elf": fw_root_path + "qcom_qnx/boot/boot_images/boot/QcomPkg/SocPkg/LeMans/Bin/AU/RELEASE/xbl_config.elf"}
    }

    sa9000_fw_file_paths = {
        "SA9000_FW1":
            {"fw1.bin": "SA9000_bin_files/fw1.bin"},
        "SA9000_FW5":
            {"fw5.bin": "SA9000_bin_files/fw5.bin"},
        "SA9000_FW9":
            {"fw6.bin": "SA9000_bin_files/fw9.bin"},
        "SA9000_FW10":
            {"fw10.bin": "SA9000_bin_files/fw10.bin"}
    }

    name_labels = ('sail_image.bin', 'md_image.bin', 'sa9000_image.bin')
    fw_image_files = (sail_fw_file_paths, md_fw_file_paths, sa9000_fw_file_paths)

    return fw_image_files, name_labels
