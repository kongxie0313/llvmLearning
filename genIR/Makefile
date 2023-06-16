LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm-16.0.4/bin/llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags) -g
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

PROJ=genIR
PROJ_OBJECT=genIR.o
default: $(PROJ)

%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(PROJ) : $(PROJ_OBJECT)
	@echo Linking $@
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ `$(LLVM_CONFIG) --libs bitwriter core support --system-libs`

clean::
	$(QUIET)rm -f $(PROJ) $(PROJ_OBJECT)
