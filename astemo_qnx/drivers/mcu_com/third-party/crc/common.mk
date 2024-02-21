ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== USEFILE - the file containing the usage message for the application
USEFILE=

define PINFO
PINFO DESCRIPTION=QCOM CRC8 library
endef

NAME=crc8

EXTRA_SRCVPATH =                                                                \
    $(PROJECT_ROOT)/src                                                         \

EXTRA_INCVPATH =                                                                \
    $(PROJECT_ROOT)/public                                                      \

LIBS = slog2

CCFLAGS = -Werror -ggdb3 -O0  -Wno-pointer-compare

include $(MKFILES_ROOT)/qmacros.mk
include $(MKFILES_ROOT)/qtargets.mk
