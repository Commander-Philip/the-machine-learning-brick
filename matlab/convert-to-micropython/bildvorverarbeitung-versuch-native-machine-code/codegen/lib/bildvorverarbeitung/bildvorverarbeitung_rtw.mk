###########################################################################
## Makefile generated for component 'bildvorverarbeitung'. 
## 
## Makefile     : bildvorverarbeitung_rtw.mk
## Generated on : Tue Aug 05 20:01:21 2025
## Final product: .\bildvorverarbeitung.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = bildvorverarbeitung
MAKEFILE                  = bildvorverarbeitung_rtw.mk
MATLAB_ROOT               = D:\Program Files\MATLAB\R2025a
MATLAB_BIN                = D:\Program Files\MATLAB\R2025a\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
START_DIR                 = D:\Git\the-machine-learning-brick\matlab\convert-to-micropython\bildvorverarbeitung-versuch-native-machine-code
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ..\..\..
COMPILER_COMMAND_FILE     = bildvorverarbeitung_rtw_comp.rsp
CMD_FILE                  = bildvorverarbeitung_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1
MODELLIB                  = bildvorverarbeitung.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2019 v16.0 | nmake (64-bit Windows)
# Supported Version(s):    16.0
# ToolchainInfo Version:   2025a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS
# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS /wd4251 /Zc:__cplusplus
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) $(C_STANDARD_OPTS) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) $(CPP_STANDARD_OPTS) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = .\bildvorverarbeitung.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=bildvorverarbeitung

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_data.c $(START_DIR)\codegen\lib\bildvorverarbeitung\rt_nonfinite.c $(START_DIR)\codegen\lib\bildvorverarbeitung\rtGetNaN.c $(START_DIR)\codegen\lib\bildvorverarbeitung\rtGetInf.c $(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_initialize.c $(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_terminate.c $(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung.c $(START_DIR)\codegen\lib\bildvorverarbeitung\imfilter.c $(START_DIR)\codegen\lib\bildvorverarbeitung\imfindcircles.c $(START_DIR)\codegen\lib\bildvorverarbeitung\chaccum.c $(START_DIR)\codegen\lib\bildvorverarbeitung\graythresh.c $(START_DIR)\codegen\lib\bildvorverarbeitung\medfilt2.c $(START_DIR)\codegen\lib\bildvorverarbeitung\chcenters.c $(START_DIR)\codegen\lib\bildvorverarbeitung\imhmax.c $(START_DIR)\codegen\lib\bildvorverarbeitung\imregionalmax.c $(START_DIR)\codegen\lib\bildvorverarbeitung\regionprops.c $(START_DIR)\codegen\lib\bildvorverarbeitung\bwconncomp.c $(START_DIR)\codegen\lib\bildvorverarbeitung\sum.c $(START_DIR)\codegen\lib\bildvorverarbeitung\sort.c $(START_DIR)\codegen\lib\bildvorverarbeitung\sortIdx.c $(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_emxutil.c $(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_emxAPI.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = bildvorverarbeitung_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj bildvorverarbeitung_initialize.obj bildvorverarbeitung_terminate.obj bildvorverarbeitung.obj imfilter.obj imfindcircles.obj chaccum.obj graythresh.obj medfilt2.obj chcenters.obj imhmax.obj imregionalmax.obj regionprops.obj bwconncomp.obj sum.obj sort.obj sortIdx.obj bildvorverarbeitung_emxutil.obj bildvorverarbeitung_emxAPI.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwrgb2gray_tbb.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwippfilter.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwgrayto8.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwtbbhist.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwimfilter.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwgetnumcores.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwordfilt2.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwimregionalmax.lib" "$(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwippreconstruct.lib"

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = /LIBPATH:"$(MATLAB_ROOT)\bin\win64" "$(MATLAB_ROOT)\bin\win64\libiomp5md.lib"

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = /source-charset:utf-8
CFLAGS_OPTS = /openmp /wd4101
CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_) $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = /source-charset:utf-8
CPPFLAGS_OPTS = /openmp /wd4101
CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_) $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = /nodefaultlib:vcomp  

CPP_LDFLAGS = $(CPP_LDFLAGS) $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = /nodefaultlib:vcomp  

CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS) $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = /nodefaultlib:vcomp  

LDFLAGS = $(LDFLAGS) $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = /nodefaultlib:vcomp  

SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS) $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj:
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


.cc.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


.cxx.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj:
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cc.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cxx.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\bildvorverarbeitung}.c.obj:
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\bildvorverarbeitung}.cpp.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\bildvorverarbeitung}.cc.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\bildvorverarbeitung}.cxx.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj:
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cc.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cxx.obj:
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


bildvorverarbeitung_data.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_data.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_data.c"


rt_nonfinite.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\rt_nonfinite.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\rt_nonfinite.c"


rtGetNaN.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\rtGetNaN.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\rtGetNaN.c"


rtGetInf.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\rtGetInf.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\rtGetInf.c"


bildvorverarbeitung_initialize.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_initialize.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_initialize.c"


bildvorverarbeitung_terminate.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_terminate.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_terminate.c"


bildvorverarbeitung.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung.c"


imfilter.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\imfilter.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\imfilter.c"


imfindcircles.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\imfindcircles.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\imfindcircles.c"


chaccum.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\chaccum.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\chaccum.c"


graythresh.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\graythresh.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\graythresh.c"


medfilt2.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\medfilt2.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\medfilt2.c"


chcenters.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\chcenters.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\chcenters.c"


imhmax.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\imhmax.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\imhmax.c"


imregionalmax.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\imregionalmax.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\imregionalmax.c"


regionprops.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\regionprops.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\regionprops.c"


bwconncomp.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\bwconncomp.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\bwconncomp.c"


sum.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\sum.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\sum.c"


sort.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\sort.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\sort.c"


sortIdx.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\sortIdx.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\sortIdx.c"


bildvorverarbeitung_emxutil.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_emxutil.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_emxutil.c"


bildvorverarbeitung_emxAPI.obj : "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_emxAPI.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\bildvorverarbeitung\bildvorverarbeitung_emxAPI.c"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


