ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
include $(AMSS_ROOT)/amss_defs.mk


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

EXTRA_LIBVPATH=$(PROJECT_ROOT)/../zlib/aarch64/so-le \

PRE_TARGET=xcp_zlib

#===== CCFLAGS - add the flags to the C compiler command line.
CCFLAGS= -ggdb3 -O0
#===== NAME - name of the project (default - name of project directory).
LIBS=slog2 zlibS

include $(MKFILES_ROOT)/qmacros.mk

ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

xcp_zlib:
	$(MAKE) install -C $(PROJECT_ROOT)/../zlib
