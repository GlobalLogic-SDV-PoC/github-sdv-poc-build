ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
include $(AMSS_ROOT)/amss_defs.mk


#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=zlib Library
endef
#===== NAME - name of the project (default - name of project directory).
NAME=zlib

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH= \
  $(PROJECT_ROOT)/src \

EXTRA_INCVPATH= \
  $(PROJECT_ROOT)/inc \


#===== CCFLAGS - add the flags to the C compiler command line.
CCFLAGS= -ggdb3 -O0
#===== NAME - name of the project (default - name of project directory).
LIBS=
#pmem_clientS fdt_utilsS

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk
