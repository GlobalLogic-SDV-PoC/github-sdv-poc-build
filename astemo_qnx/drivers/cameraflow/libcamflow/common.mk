ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
include $(AMSS_ROOT)/amss_defs_af.mk

#===== NAME - name of the project (default - name of project directory).
NAME=camflow

#===== USEFILE - the file containing the usage message for the application.
USEFILE=

#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=Camera data flow library
endef

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH=$(PROJECT_ROOT)/src

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH= \
    $(PROJECT_ROOT)/public \
    $(PROJECT_ROOT)/inc \
    $(PROJECT_ROOT)/../logger/public \
    $(AMSS_ROOT)/inc \
    $(AMSS_ROOT)/multimedia/graphics/include/private/C2D \
    $(INSTALL_ROOT_nto)/usr/include/amss \

#===== EXTRA_LIBVPATH - a space-separated list of directories to search for library files.
EXTRA_LIBVPATH+= \
    $(RIM_BUILD_ROOT)/install/aarch64le/usr/lib/graphics/qc \
    $(RIM_BUILD_ROOT)/install/aarch64le/lib

#===== LIBS - a space-separated list of library items to be included in the link.
LIBS=slog2 qcd qcd_client cam_logger c2d30

PRE_TARGET=libcam_logger

CCFLAG_64=-02 -Werror

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

libcam_logger:
	$(MAKE) -C $(PROJECT_ROOT)/../logger install
