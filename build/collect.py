import argparse
import os
import re

import shutil

# qcom specific module from qcom_qnx/common/build/lib
import meta_lib

def read_contents(file_path):
    if not os.path.exists(file_path):
        raise RuntimeError("Error: contents.xml file not found")
    return meta_lib.meta_info(file_pfn=file_path)

def copy_file(file_path):
    destdir = re.sub(
        f"^{os.path.abspath('/opt')}/?",
        "./out_collect/",
        file_path)
    try:
        os.makedirs(os.path.split(destdir)[0], exist_ok=True)
        shutil.copy(file_path, destdir)
    except FileExistsError as e:
        print("Warning: File {} was ignored: {}".format(file_path, e))

def main(args):
    contents = read_contents(args.contents_file)
    files = contents.get_files(flavor=args.flavor, storage='ufs')
    for file in files:  
        copy_file(file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--contents_file', help='Path to the contents.xml.', metavar="FILE", default='./qcom_qnx/contents.xml')
    parser.add_argument('--flavor', help='Copy files only with this flavor.', default=None)
    main(parser.parse_args())
