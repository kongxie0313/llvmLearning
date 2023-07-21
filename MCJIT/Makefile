LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm-16.0.4/bin/llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags) -g -O3 -rdynamic -fno-rtti
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

PROJ=sum-jit
PROJ_OBJECTS=sum-jit.o
default: $(PROJ)

%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(PROJ) : $(PROJ_OBJECTS)
	@echo Linking $@
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ `$(LLVM_CONFIG) --libs mcjit native irreader --system-libs`

clean::
	$(QUIET)rm -f $(PROJ) $(PROJ_OBJECTS)
