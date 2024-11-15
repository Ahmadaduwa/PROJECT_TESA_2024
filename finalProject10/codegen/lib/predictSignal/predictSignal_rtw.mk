###########################################################################
## Makefile generated for component 'predictSignal'. 
## 
## Makefile     : predictSignal_rtw.mk
## Generated on : Fri Nov 15 10:15:32 2024
## Final product: ./predictSignal.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = predictSignal
MAKEFILE                  = predictSignal_rtw.mk
MATLAB_ROOT               = $(MATLAB_WORKSPACE)/E/Program_to_Writecode
MATLAB_BIN                = $(MATLAB_WORKSPACE)/E/Program_to_Writecode/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = $(MATLAB_WORKSPACE)/E/Work_Inclass/Preprocess
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
CUSTOM_C_FLAGS            = 
CUSTOM_CPP_FLAGS          = 
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
MODELLIB                  = predictSignal.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU GCC Embedded Linux
# Supported Version(s):    
# ToolchainInfo Version:   2024b
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

CCOUTPUTFLAG = --output_file=
LDOUTPUTFLAG = --output_file=

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lm -lrt -lpthread -ldl -lm -lstdc++ -lrt -lpthread -ldl

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: GNU GCC Embedded Linux Assembler
AS = as

# C Compiler: GNU GCC Embedded Linux C Compiler
CC = gcc

# Linker: GNU GCC Embedded Linux Linker
LD = gcc

# C++ Compiler: GNU GCC Embedded Linux C++ Compiler
CPP = g++

# C++ Linker: GNU GCC Embedded Linux C++ Linker
CPP_LD = g++

# Archiver: GNU GCC Embedded Linux Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: Make Tool
MAKE = make


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  =
ECHO                = echo
MV                  =
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = -r
ASFLAGS              = -c \
                       $(ASFLAGS_ADDITIONAL) \
                       $(INCLUDES)
CFLAGS               = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -O2 \
                        -DMW_NUM_CORES=$(shell nproc)  \
                       $(CUSTOM_C_FLAGS)
CPPFLAGS             = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -fpermissive  \
                       -O2 \
                        -DMW_NUM_CORES=$(shell nproc)  \
                       $(CUSTOM_CPP_FLAGS)
CPP_LDFLAGS          = -Wl,--no-as-needed
CPP_SHAREDLIB_LDFLAGS  = -shared  \
                         -Wl,--no-as-needed
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -Wl,--no-as-needed
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -j$(($(nproc)+1)) -Otarget -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared  \
                       -Wl,--no-as-needed



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./predictSignal.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/predictSignal -I$(START_DIR) -I$(MATLAB_WORKSPACE)/C/ProgramData/MATLAB/SupportPackages/R2024b/toolbox/realtime/targets/raspi/include -I$(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__
DEFINES_CUSTOM = 
DEFINES_SKIPFORSIL = -D__linux__ -DARM_PROJECT -D_USE_TARGET_UDP_ -D_RUNONTARGETHARDWARE_BUILD_ -DSTACK_SIZE=200000
DEFINES_STANDARD = -DMODEL=predictSignal

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/predictSignal/predictSignal_data.c $(START_DIR)/codegen/lib/predictSignal/rt_nonfinite.c $(START_DIR)/codegen/lib/predictSignal/rtGetNaN.c $(START_DIR)/codegen/lib/predictSignal/rtGetInf.c $(START_DIR)/codegen/lib/predictSignal/predictSignal_initialize.c $(START_DIR)/codegen/lib/predictSignal/predictSignal_terminate.c $(START_DIR)/codegen/lib/predictSignal/predictSignal.c $(START_DIR)/codegen/lib/predictSignal/ClassificationKNN.c $(START_DIR)/codegen/lib/predictSignal/knnsearch.c $(START_DIR)/codegen/lib/predictSignal/kdsearchfun.c $(START_DIR)/codegen/lib/predictSignal/minOrMax.c $(START_DIR)/codegen/lib/predictSignal/sort.c $(START_DIR)/codegen/lib/predictSignal/sortIdx.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = predictSignal_data.c.o rt_nonfinite.c.o rtGetNaN.c.o rtGetInf.c.o predictSignal_initialize.c.o predictSignal_terminate.c.o predictSignal.c.o ClassificationKNN.c.o knnsearch.c.o kdsearchfun.c.o minOrMax.c.o sort.c.o sortIdx.c.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(LINUX_TARGET_LIBS_MACRO)

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = -fopenmp
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = -fopenmp
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -fopenmp

CPP_LDFLAGS += $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -fopenmp

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = -fopenmp

LDFLAGS += $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -fopenmp

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################


DERIVED_SRCS = $(subst .o,.dep,$(OBJS))

build:

%.dep:



-include codertarget_assembly_flags.mk
-include *.dep


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.c.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : %.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/codegen/lib/predictSignal/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/codegen/lib/predictSignal/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/codegen/lib/predictSignal/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


predictSignal_data.c.o : $(START_DIR)/codegen/lib/predictSignal/predictSignal_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.c.o : $(START_DIR)/codegen/lib/predictSignal/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.c.o : $(START_DIR)/codegen/lib/predictSignal/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.c.o : $(START_DIR)/codegen/lib/predictSignal/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


predictSignal_initialize.c.o : $(START_DIR)/codegen/lib/predictSignal/predictSignal_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


predictSignal_terminate.c.o : $(START_DIR)/codegen/lib/predictSignal/predictSignal_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


predictSignal.c.o : $(START_DIR)/codegen/lib/predictSignal/predictSignal.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ClassificationKNN.c.o : $(START_DIR)/codegen/lib/predictSignal/ClassificationKNN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


knnsearch.c.o : $(START_DIR)/codegen/lib/predictSignal/knnsearch.c
	$(CC) $(CFLAGS) -o "$@" "$<"


kdsearchfun.c.o : $(START_DIR)/codegen/lib/predictSignal/kdsearchfun.c
	$(CC) $(CFLAGS) -o "$@" "$<"


minOrMax.c.o : $(START_DIR)/codegen/lib/predictSignal/minOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sort.c.o : $(START_DIR)/codegen/lib/predictSignal/sort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortIdx.c.o : $(START_DIR)/codegen/lib/predictSignal/sortIdx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	echo "### PRODUCT = $(PRODUCT)"
	echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	echo "### BUILD_TYPE = $(BUILD_TYPE)"
	echo "### INCLUDES = $(INCLUDES)"
	echo "### DEFINES = $(DEFINES)"
	echo "### ALL_SRCS = $(ALL_SRCS)"
	echo "### ALL_OBJS = $(ALL_OBJS)"
	echo "### LIBS = $(LIBS)"
	echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	echo "### ASFLAGS = $(ASFLAGS)"
	echo "### CFLAGS = $(CFLAGS)"
	echo "### LDFLAGS = $(LDFLAGS)"
	echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	echo "### CPPFLAGS = $(CPPFLAGS)"
	echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	echo "### ARFLAGS = $(ARFLAGS)"
	echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(RM) *.c.dep
	$(RM) *.cpp.dep
	$(ECHO) "### Deleted all derived files."


