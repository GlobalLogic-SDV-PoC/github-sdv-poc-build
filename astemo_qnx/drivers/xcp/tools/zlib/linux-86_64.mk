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

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

INSTALLDIR_SO=$(PROJECT_ROOT)/../x86-install
SO_FILE=libzlib.so.1
A_FILE=libzlibS.a
MKDIR_P=        /bin/mkdir -p

include $(MKFILES_ROOT)/qmacros.mk

include $(MKFILES_ROOT)/qtargets.mk

install:
	@echo "copying x86 binaries.."
	$(MKDIR_P) $(INSTALLDIR_SO)
	$(CP_HOST) $(BUILDNAME) $(INSTALLDIR_SO)/$(BUILDNAME)
	$(LN_HOST) $(BUILDNAME) $(INSTALLDIR_SO)/$(SO_FILE)
	$(CP_HOST) $(A_FILE) $(INSTALLDIR_SO)
