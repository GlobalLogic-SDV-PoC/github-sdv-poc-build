ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=Image Creating application
endef
#===== NAME - name of the project (default - name of project directory).
NAME=img_builder

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH= \
  $(PROJECT_ROOT)/src \

EXTRA_INCVPATH= \
  $(PROJECT_ROOT)/inc \
  $(PROJECT_ROOT)/ \
  $(PROJECT_ROOT)/../fw_img_lib/inc

USEFILE=$(PROJECT_ROOT)/img_builder.use

PRE_TARGET=fwimg_lib

#===== CCFLAGS - add the flags to the C compiler command line.
CCFLAGS= -ggdb3 -O0 -DTARGET_X86_BUILD
#===== NAME - name of the project (default - name of project directory).
LIBS=fw_imgS zlibS

INSTALLDIR_BIN=$(PROJECT_ROOT)/../x86-install
MKDIR_P=/bin/mkdir -p

EXTRA_LIBVPATH=$(INSTALLDIR_BIN) \

include $(MKFILES_ROOT)/qmacros.mk

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(BSP_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

fwimg_lib:
	$(MAKE) install -C $(PROJECT_ROOT)/../fw_img_lib

install:
	@echo "copying x86 binaries.."
	$(MKDIR_P) $(INSTALLDIR_BIN)
	$(CP_HOST) $(BUILDNAME) $(INSTALLDIR_BIN)/$(BUILDNAME)
