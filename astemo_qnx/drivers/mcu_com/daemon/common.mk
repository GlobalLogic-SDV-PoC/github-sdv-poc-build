ifndef QCONFIG
QCONFIG = qconfig.mk
endif
include $(QCONFIG)

include $(AMSS_ROOT)/amss_defs.mk

USEFILE=$(PROJECT_ROOT)/mcu_com.use

define PINFO
PINFO DESCRIPTION=MCU communication manager
endef

NAME = mcu_com

EXTRA_SRCVPATH =                                                                \
    $(PROJECT_ROOT)/src/com                                                     \
    $(PROJECT_ROOT)/src/core                                                    \
    $(PROJECT_ROOT)/src/log                                                     \
    $(PROJECT_ROOT)/src/msg                                                     \
    $(PROJECT_ROOT)/src/msg-handler                                             \
    $(PROJECT_ROOT)/src/uart                                                    \
    $(PROJECT_ROOT)/../third-party/crc/public                                   \

EXTRA_INCVPATH =                                                                \
    $(INSTALL_ROOT_nto)/usr/include/amss/core                                   \

EXTRA_LIBVPATH = $(INSTALL_ROOT_nto)/aarch64le/lib                              \

LIBS = crc8 lcm-control mq slog2

CCFLAGS = -Werror -ggdb3 -O0

PRE_TARGET=                                                                     \
    libcrc8                                                                     \

include $(MKFILES_ROOT)/qmacros.mk

ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

libcrc8:
	$(MAKE) install -C $(PROJECT_ROOT)/../third-party/crc
