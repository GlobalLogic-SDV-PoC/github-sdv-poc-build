#    __________  __  _______  ____  ________________ ____  ____
#   / ____/ __ \/  |/  / __ \/ __ \/ ____/ ___/ ___// __ \/ __ \
#  / /   / / / / /|_/ / /_/ / /_/ / __/  \__ \\__ \/ / / / /_/ /
# / /___/ /_/ / /  / / ____/ _, _/ /___ ___/ /__/ / /_/ / _, _/
# \____/\____/_/  /_/_/   /_/ |_/_____//____/____/\____/_/ |_|
#
# **************************************************************************************************
# *    @file           : main.py
# *    @brief          : firmware_compressor script body
# **************************************************************************************************
# *    @author     Volodymyr Noha
# *
# *    @description:
# *    Simple python utility to compress firmware files and create firmware image
# *
# *    @section  HISTORY:
# *    v1.0  - First version
# *
# *    @section  DOCUMENTATION:
# *    Check README.md
# *
# **************************************************************************************************
# !/usr/bin/env python3.8
# -*- coding: utf-8 -*-

# general python imports
import os
import sys
import gzip
import json
import datetime
import struct
import shutil
import sys
import argparse

# C interface module for python
from ctypes import *

# 3d party python packages
try:
    from loguru import logger
except ImportError:
    print("Neccessary python packages are not installed")
    print("Use pip3 install -r requirements.txt")

# Firmware file paths import
import fw_files

# Config load
config_file = open('config/config.json', 'r')
config_file_content = config_file.read()
config = json.loads(config_file_content)
config_file.close()

# User pv
border_expander = 120
read_chunk = 256

# Paths
comp_path = 'compressed_files/'
decomp_path = 'decompressed_files/'
img_files_path = 'images/'

arch_ext = '.gz'

# Other
test_consistency_flag = config['test_consistency_flag']

# C fw processor lib pv
FWIMG_MAX_PART_NAME = 256
FWIMG_FILE_ATTR = 2

# Logger configs
LOG_FILE_PATH = config['log_file_path']
LOG_ROTATION_SIZE = config['log_rotation_size']
LOG_FILTER_NAME = config['log_filter_name']
LOG_LEVEL = config['log_level']

# Exit status codes
EXIT_SUCCESS = 0
EXIT_FAILED = 1

# logger object configuration
logger.add(sys.stderr, format="{time} {level} {message}",
           filter=LOG_FILTER_NAME,
           level=LOG_LEVEL)

logger.add(LOG_FILE_PATH + "log.log",
           rotation=LOG_ROTATION_SIZE)

arg_parser = argparse.ArgumentParser(description="Firmware compressor")


# callout function for argument parsing
# Args: master, args
# Return: None
def callout(args):
    global firmware_file_paths

    if args.debug_info:
        firmware_file_paths = args.firmware_file_paths


# Add CLI argument
arg_parser.add_argument(
    "-file-paths",
    "--paths",
    dest="firmware_file_paths",
    type=str,
    default='../out_collect/',
    help='path to the firmware images folder',
)

# Init CLI argument parser
args = arg_parser.parse_args()


# fwimg_parts struct definition for fw images
class fw_partitions_zipped_st_t(Structure):
    _fields_ = [
        ('partition_name', c_char_p),
        ('partition_file', c_char_p),
        ('partition_zipped_flag', c_int)
    ]


# Ctypes connect .so lib
so_lib = '../x86-install/libfw_img.so'
firmware_processor = CDLL(so_lib)


# Creates working directories in the project
# Args: path
# Return: None
def create_working_dirs():
    try:

        if not os.path.exists(comp_path):
            logger.info("%s directory created" % (comp_path))
            os.makedirs(comp_path)
        else:
            logger.info("%s directory already exist" % (decomp_path))

        if not os.path.exists(decomp_path):
            logger.info("%s directory created" % (decomp_path))
            os.makedirs(decomp_path)
        else:
            logger.info("%s directory already exist" % (decomp_path))

        if not os.path.exists(img_files_path):
            logger.info("%s directory created" % (img_files_path))
            os.makedirs(img_files_path)
        else:
            logger.info("%s directory already exist" % (decomp_path))

    except OSError as e:
        logger.error("Error occured: %s" % (str(e)))
        sys.exit(EXIT_FAILED)


# Remove files from directories
# Args: path
# Return: None
def remove_files(path):
    files_dir = os.listdir(path)
    if [] != files_dir:
        logger.info("Cleaning up %s directory" % (path))

        for file in files_dir:
            file_path = os.path.join(path, file)
            try:
                if os.path.isfile(file_path) or os.path.islink(file_path):
                    os.unlink(file_path)
                    logger.info("File removed: %s" % (file_path))

            except Exception as e:
                logger.error("Error has occured: %s" % (str(e)))


# Remove directories from project
# Args: path
# Return: None
def remove_dir(path):
    try:
        if os.path.isdir(path):
            shutil.rmtree(path)
            logger.info("Directory removed: %s" %(path))
    except Exception as e:
        logger.error("Error has occured: %s" %(e))


# Check content of the firmware image file
# Args: path
# Return: None
def check_fw_image_file(path):
    context_dir = os.listdir(path)
    if [] != context_dir:
        for file in context_dir:
            file_path = os.path.join(path, file)
            file_size = os.path.getsize(file_path)

            # Read xcp_repro_ctx struct from file
            context_file = open(file_path, 'rb')
            context_content = context_file.read(16)
            context_file.close()
            data = struct.unpack_from('qiI', context_content, offset=0)

            logger.info("%s file path: %s" % (file, file_path))
            logger.info("%s file size: %d bytes" % (file, file_size))
            logger.info("%s file magic: %s" % (file, hex(data[0])))
            logger.info("%s fw files number: %i" % (file, data[1]))
            logger.info("%s context file CRC32: %s" % (file, hex(data[2])))


# Creates firmware image fro gziped files
# Args: ctx_file_name, files_path, fw_files_prop_dict
# Return: int status
def create_firmware_image(fw_img_file_name, files_path, fw_files_prop_dict):
    archived_bin_dir = os.listdir(files_path)
    count_files = len(archived_bin_dir)

    fw_partitions = fw_partitions_zipped_st_t * count_files
    fw_partitions_arr = fw_partitions()

    fw_img_file_path = os.path.join(img_files_path, fw_img_file_name)
    fw_img_file = create_string_buffer(fw_img_file_path.encode('utf-8'))

    if [] != archived_bin_dir:
        for partition in fw_files_prop_dict:
            path = fw_files_prop_dict[partition]['archived_file_path']
            arch_f = fw_files_prop_dict[partition]['archived_flag']
            file_num = fw_files_prop_dict[partition]['file_num']

            fw_part = partition.encode('utf-8'), path.encode('utf-8'), arch_f
            fw_partitions_arr[file_num] = fw_part

    # Call firmware processor C API
    ret = firmware_processor.fwimg_create_image(fw_img_file,
                                                fw_partitions_arr,
                                                count_files,
                                                None)
    # Return status code
    return ret


# Extracts firmware binaries from the image file
# Args: ctx_file_name, files_path, fw_files_prop_dict
# Return: int status
def extract_binaries_from_image(image_path):

    ret = firmware_processor.fwimg_extract_files(image_path.encode('utf-8'),
                                                 decomp_path.encode('utf-8'),
                                                 None)

    return ret


# Compress firmware file
# Args: path, file_name
# Return: None
def compress_binary_file(path, file_name, arch_path):
    logger.info("Compression started on: %s" % (file_name))
    arch_path = os.path.join(arch_path, file_name)

    with open(path, 'rb') as original_fw_file, gzip.open(arch_path + arch_ext, 'wb') as comp_file:

        while True:
            data = original_fw_file.read(read_chunk)

            if not data:
                break

            comp_file.write(data)

        original_fw_file.close()
        comp_file.close()

        original_binary_size = os.path.getsize(path)
        compressed_binary_size = os.path.getsize(arch_path + arch_ext)

        logger.info("File path: %s" % (path))
        logger.info("Original file size: %d bytes" % original_binary_size)
        logger.info("Compressed file size: %d bytes" % compressed_binary_size)
        logger.info("Compression finished on: %s" % (file_name))


# Creates domain related firmware info dictionary and calls compression
# Args: domain_files, domain_arch_path
# Return: dictionary domain_fw_info
def archive_binary_file(domain_files, domain_arch_path):
    domain_fw_info = {}
    file_num = 0

    for partition in domain_files:
        root = domain_files[partition]

        for file_name in root:
            try:
                path = root[file_name]

                compress_binary_file(path=path,
                                     file_name=file_name,
                                     arch_path=domain_arch_path)

                gzipped_path = os.path.join(domain_arch_path, file_name)

                domain_fw_info[partition] = {
                    "archived_file_path": gzipped_path + arch_ext,
                    "archived_flag": FWIMG_FILE_ATTR,
                    "file_num": file_num
                }

                file_num = file_num + 1
            except Exception as e:
                logger.error("Error occured: %s" % (str(e)))

    return domain_fw_info


# Firmware compressor main function
# Args: None
# Return: None
def main():
    start = datetime.datetime.now()

    create_working_dirs()

    # Working directory clean-up on start
    remove_files(path=comp_path)
    remove_files(path=img_files_path)
    remove_files(path=decomp_path)

    file_path = args.firmware_file_paths
    bin_files, bin_file_names = fw_files.set_root_path(fw_root_path=file_path + '/')

    try:
        for binary_file, binary_file_name in zip(bin_files, bin_file_names):

            domain_fw_info = archive_binary_file(domain_files=binary_file,
                                                 domain_arch_path=comp_path)
            if {} != domain_fw_info:

                ret = create_firmware_image(fw_img_file_name=binary_file_name,
                                            files_path=comp_path,
                                            fw_files_prop_dict=domain_fw_info)

                if EXIT_SUCCESS != ret:
                    logger.error("Image creator ERROR. code: %i" % (ret))
                    sys.exit(EXIT_FAILED)

                logger.info("Image creator status: SUCCESS")
                remove_files(path=comp_path)

            else:
                logger.error("Archive creator firmware dictionary is empty!")
                sys.exit(EXIT_FAILED)

        check_fw_image_file(path=img_files_path)

        # Test consistency of the firmware image files
        if test_consistency_flag:
            list_img_dir = os.listdir(img_files_path)

            for item in list_img_dir:
                image_path = os.path.join(img_files_path, item)
                ret = extract_binaries_from_image(image_path=image_path)

                if EXIT_SUCCESS != ret:
                    logger.error("Consistency check ERROR. code: %i" % (ret))
                    sys.exit(EXIT_FAILED)

                logger.info("Consistency ckeck status: SUCCESS")
                remove_files(path=decomp_path)

        remove_dir(path=decomp_path)
        remove_dir(path=comp_path)

    except KeyboardInterrupt:
        logger.info("Exit with keyboard interrupt by user")
        sys.exit(EXIT_SUCCESS)

    except Exception as e:
        logger.error("Exit with error: %s" % (str(e)))
        sys.exit(EXIT_FAILED)

    end = datetime.datetime.now()
    elapsed_time = end - start

    logger.info("Total time elapsed: %s" % (str(elapsed_time)))


# Script entry point
if __name__ == "__main__":
    main()
