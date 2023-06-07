LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm-16.0.0/bin/llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

CLANGLIBS = \
	-Wl,--start-group\
	-lclang\
	-lclangFrontend\
	-lclangDriver\
	-lclangSerialization\
	-lclangParse\
	-lclangSema\
	-lclangAnalysis\
	-lclangEdit\
	-lclangAST\
	-lclangLex\
	-lclangBasic\
	-Wl,--end-group
LLVMLIBS=$(shell $(LLVM_CONFIG) --libs)

PROJECT=parseToken
PROJECT_OBJECTS=parseToken.o

default: $(PROJECT)

%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(PROJECT) : $(PROJECT_OBJECTS)
	@echo Linking $@
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS) `$(LLVM_CONFIG) --system-libs`

clean::
	$(QUIET)rm -f $(PROJECT) $(PROJECT_OBJECTS)
