ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

include $(AMSS_ROOT)/amss_defs_af.mk

define PINFO
PINFO DESCRIPTION= Astemo encoder test application
endef

USEFILE=

APP_NAME_STR=\"astemo_enc_app\"

NAME=astemo_enc_app

LIBRARY_ROOT=$(PWD)/../../../../library
CLIENT_ROOT=$(PWD)/../../../../client

#===== DEBUG
#===== STDOUT_DEBUG: 0 - DISABLE, 1 - ENABLE
STDOUT_DEBUG_ENABLE=0
#===== SLOGGER2_DEBUG: 0 - DISABLE, 1 - ENABLE
SLOGGER2_DEBUG_ENABLE=1
SLOGGER2_NUM_PAGES=264
DEBUG_VERBOSE_LEVEL=5

#===== CCFLAGS - add the flags to the C compiler command line.
CCFLAGS+=-Werror
CCFLAGS+=-DAPP_NAME=${APP_NAME_STR}
CCFLAGS+=-DCONFIG_VERBOSE_LEVEL=${DEBUG_VERBOSE_LEVEL}
#CCFLAGS+=-DCONFIG_DEBUG_STDOUT=${STDOUT_DEBUG_ENABLE}
CCFLAGS+=-DCONFIG_DEBUG_SLOGGER2=${SLOGGER2_DEBUG_ENABLE}
CCFLAGS+=-DCONFIG_SLOG2_NUM_PAGES=${SLOGGER2_NUM_PAGES}

VFLAG_g=-gstabs+

EXTRA_INCVPATH +=                                                                                   \
    $(AMSS_ROOT)/inc/                                                                               \
    $(AMSS_ROOT)/multimedia/inc/                                                                    \
    $(AMSS_ROOT)/multimedia/video/source/common/drivers/inc/                                        \
    $(AMSS_ROOT)/platform/utilities/qnp_include/public/amss/core/                                   \
    $(CLIENT_ROOT)/inc/                                                                             \
    $(CLIENT_ROOT)/src/parser/                                                                      \
    $(CLIENT_ROOT)/src/core/                                                                        \
    $(LIBRARY_ROOT)/public-inc/                                                                     \
    $(LIBRARY_ROOT)/src/core/                                                                       \
    $(LIBRARY_ROOT)/src/help/                                                                       \
    $(LIBRARY_ROOT)/src/logger/                                                                     \
    $(LIBRARY_ROOT)/src/state/                                                                      \
    $(LIBRARY_ROOT)/src/platform/                                                                   \
    $(LIBRARY_ROOT)/src/utils/                                                                      \
    $(LIBRARY_ROOT)/src/vidc/                                                                       \

EXTRA_SRCVPATH +=                                                                                   \
    $(CLIENT_ROOT)/src/                                                                             \
    $(CLIENT_ROOT)/src/parser/                                                                      \
    $(CLIENT_ROOT)/src/core/                                                                        \
    $(LIBRARY_ROOT)/src/core/                                                                       \
    $(LIBRARY_ROOT)/src/help/                                                                       \
    $(LIBRARY_ROOT)/src/state/                                                                      \
    $(LIBRARY_ROOT)/src/logger/                                                                     \
    $(LIBRARY_ROOT)/src/platform/                                                                   \
    $(LIBRARY_ROOT)/src/utils/                                                                      \

#===== EXTRA_LIBVPATH - a space-separated list of directories to search for library files.
EXTRA_LIBVPATH +=                                                                                   \
    $(LIBRARY_ROOT)/build/aarch64/so.le/

# Client SRC
SRCS += cmd-parser.c
SRCS += main.c

# Library SRC
SRCS += client-resources.c
SRCS += client-settings.c
SRCS += enc-logger.c
SRCS += enc-ops.c
SRCS += enc-slog2.c
SRCS += pfm-read-data.c
SRCS += pfm-string.c
SRCS += utils.c

# External libs
LIBS += OSAbstraction
LIBS += ioctlClient
LIBS += libstd
LIBS += pmem_client
LIBS += pmemext
LIBS += slog2
LIBS += video_encS

PRE_TARGET=lib_enc_build

include $(MKFILES_ROOT)/qmacros.mk
include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

lib_enc_build:
	$(MAKE) -C $(LIBRARY_ROOT)
