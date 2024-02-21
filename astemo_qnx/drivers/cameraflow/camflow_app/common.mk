# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
include $(AMSS_ROOT)/amss_defs_af.mk
#===== USEFILE - the file containing the usage message for the application.
USEFILE=

#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=Camera data flow application
endef

EXTRA_SRCVPATH=$(PROJECT_ROOT)/src

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH=$(INSTALL_ROOT_nto)/usr/include/amss/core
INCVPATH= \
    $(INSTALL_ROOT_nto)/usr/include/amss \
    $(INSTALL_ROOT_nto)/usr/include \

#===== LIBS - a space-separated list of library items to be included in the link.
LIBS=slog2 camflow c2d30
CCFLAGS=-Wall -Werror

#===== EXTRA_LIBVPATH - a space-separated list of directories to search for library files.
EXTRA_LIBVPATH=$(INSTALL_ROOT_nto)/$(cpulist)/lib \
               $(RIM_BUILD_ROOT)/install/aarch64le/usr/lib/graphics/qc \
               $(RIM_BUILD_ROOT)/install/aarch64le/lib \

PRE_TARGET=libcamflow

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

libcamflow:
	$(MAKE) -C $(PROJECT_ROOT)/../libcamflow install
