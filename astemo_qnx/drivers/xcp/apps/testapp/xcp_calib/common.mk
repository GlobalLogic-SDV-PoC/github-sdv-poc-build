ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
include $(AMSS_ROOT)/amss_defs.mk


#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=XCP Calibration application
endef
#===== NAME - name of the project (default - name of project directory).
NAME=xcp_calib

#===== USEFILE - the file containing the usage message for the application.
USEFILE=$(PROJECT_ROOT)/src/xcp_calib.use

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH= \
  $(PROJECT_ROOT)/src \

EXTRA_INCVPATH= \
  $(PROJECT_ROOT)/inc \
  $(PROJECT_ROOT)/../../../XCPlite/src \
  $(PROJECT_ROOT)/../../../XCPlite/xlapi \
  $(PROJECT_ROOT)/../../../xcp_lib/inc \

EXTRA_LIBVPATH=$(PROJECT_ROOT)/../../xcp_lib/aarch64/so-le \
#===== CCFLAGS - add the flags to the C compiler command line.

PRE_TARGET=xcp_lib

#===== VERSION_TAG_SO - version tag for SONAME. Use it only if you don't like SONAME_VERSION
override VERSION_TAG_SO=

CCFLAGS= -ggdb3 -O0 -DXCP_REPRO_COMMANDS
#===== NAME - name of the project (default - name of project directory).
LIBS=slog2 m xcpS socketS

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

xcp_lib:
	$(MAKE) install -C $(PROJECT_ROOT)/../../../xcp_lib

