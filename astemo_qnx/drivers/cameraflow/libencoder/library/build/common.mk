ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

include $(AMSS_ROOT)/amss_defs_af.mk

define PINFO
PINFO DESCRIPTION = Astemo encoder library
endef

USEFILE=

APP_NAME_STR=\"video_enc\"

NAME=video_enc

LIBRARY_ROOT=$(PWD)/../../../../library

#===== DEBUG
#===== STDOUT_DEBUG: 0 - DISABLE, 1 - ENABLE
STDOUT_DEBUG_ENABLE=0
#===== SLOGGER2_DEBUG: 0 - DISABLE, 1 - ENABLE
SLOGGER2_DEBUG_ENABLE=1
SLOGGER2_NUM_PAGES=256
DEBUG_VERBOSE_LEVEL=5

#===== CCFLAGS - add the flags to the C compiler command line.
CCFLAGS+=-Werror
CCFLAGS+=-DAPP_NAME=${APP_NAME_STR}
CCFLAGS+=-DCONFIG_VERBOSE_LEVEL=${DEBUG_VERBOSE_LEVEL}
#CCFLAGS+=-DCONFIG_DEBUG_STDOUT=${STDOUT_DEBUG_ENABLE}
CCFLAGS+=-DCONFIG_DEBUG_SLOGGER2=${SLOGGER2_DEBUG_ENABLE}
CCFLAGS+=-DCONFIG_SLOG2_NUM_PAGES=${SLOGGER2_NUM_PAGES}

INCVPATH +=                                                                                         \
    $(AMSS_INC)                                                                                     \
    $(AMSS_ROOT)/multimedia/inc/                                                                    \
    $(AMSS_ROOT)/multimedia/video/source/common/drivers/inc/                                        \
    $(INSTALL_ROOT_nto)/usr/include/amss                                                            \
    $(INSTALL_ROOT_nto)/usr/include/amss/core                                                       \
    $(LIBRARY_ROOT)/public-inc                                                                      \
    $(LIBRARY_ROOT)/src/core/                                                                       \
    $(LIBRARY_ROOT)/src/help/                                                                       \
    $(LIBRARY_ROOT)/src/logger/                                                                     \
    $(LIBRARY_ROOT)/src/platform/                                                                   \
    $(LIBRARY_ROOT)/src/state                                                                       \
    $(LIBRARY_ROOT)/src/utils/                                                                      \
    $(LIBRARY_ROOT)/src/vidc/                                                                       \

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH +=                                                                                   \
    $(LIBRARY_ROOT)/src/core                                                                        \
    $(LIBRARY_ROOT)/src/help                                                                        \
    $(LIBRARY_ROOT)/src/logger                                                                      \
    $(LIBRARY_ROOT)/src/platform                                                                    \
    $(LIBRARY_ROOT)/src/state                                                                       \
    $(LIBRARY_ROOT)/src/utils                                                                       \
    $(LIBRARY_ROOT)/src/vidc                                                                        \

# Encoder SRC
SRCS += enc-api.c

# Logger SRC
SRCS += enc-logger.c
SRCS += enc-slog2.c

# State SRC
SRCS += enc-state-api.c

# Platform SRC
SRCS += pfm-critical.c
SRCS += pfm-file.c
SRCS += pfm-pmem.c
SRCS += pfm-queue.c
SRCS += pfm-resources.c
SRCS += pfm-stdlib.c
SRCS += pfm-string.c

# Utils SRC
SRCS += utils.c

# VIDC SRC
SRCS += enc-vidc-callback.c
SRCS += enc-vidc-contexts-api.c
SRCS += enc-vidc-converters.c
SRCS += enc-vidc-frames-api.c
SRCS += enc-vidc-ioctl.c
SRCS += enc-vidc-printing-api.c
SRCS += enc-vidc-properties-api.c

# External libs
LIBS += OSAbstraction
LIBS += ioctlClient
LIBS += libstd
LIBS += pmem_client
LIBS += pmemext
LIBS += slog2

include $(MKFILES_ROOT)/qmacros.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

include $(MKFILES_ROOT)/qtargets.mk
