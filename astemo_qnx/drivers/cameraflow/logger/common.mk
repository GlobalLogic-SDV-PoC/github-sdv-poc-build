ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
include $(AMSS_ROOT)/amss_defs_af.mk

#===== NAME - name of the project (default - name of project directory).
NAME=cam_logger

#===== USEFILE - the file containing the usage message for the application.
USEFILE=

#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=Camera data flow logger library
endef

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH=$(PROJECT_ROOT)/src

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH= \
    $(PROJECT_ROOT)/public \
    $(AMSS_ROOT)/inc \
    $(INSTALL_ROOT_nto)/usr/include/amss \

#===== LIBS - a space-separated list of library items to be included in the link.
LIBS=slog2

CCFLAG_64=-02 -Werror

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk
