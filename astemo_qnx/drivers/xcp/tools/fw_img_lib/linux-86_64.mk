ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=Image handling library
endef
#===== NAME - name of the project (default - name of project directory).
NAME=fw_img

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH= \
  $(PROJECT_ROOT)/src \

EXTRA_INCVPATH= \
  $(PROJECT_ROOT)/inc \
  $(PROJECT_ROOT)/../zlib/inc \
  $(PROJECT_ROOT)/../../xcp_lib/inc \

INSTALLDIR_SO=$(PROJECT_ROOT)/../x86-install
SO_FILE=libfw_img.so.1
A_FILE=libfw_imgS.a
MKDIR_P=/bin/mkdir -p

EXTRA_LIBVPATH=$(INSTALLDIR_SO)

#===== CCFLAGS - add the flags to the C compiler command line.
CCFLAGS= -ggdb3 -O0 -DTARGET_X86_BUILD
#===== NAME - name of the project (default - name of project directory).
LIBS=zlibS

PRE_TARGET=xcp_zlib

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

install:
	@echo "copying x86 binaries.."
	$(MKDIR_P) $(INSTALLDIR_SO)
	$(CP_HOST) $(BUILDNAME) $(INSTALLDIR_SO)/$(BUILDNAME)
	$(LN_HOST) $(BUILDNAME) $(INSTALLDIR_SO)/$(SO_FILE)
	$(CP_HOST) $(A_FILE) $(INSTALLDIR_SO)

xcp_zlib:
	$(MAKE) install -C $(PROJECT_ROOT)/../zlib
