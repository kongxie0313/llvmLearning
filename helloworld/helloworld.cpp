#include"llvm/Bitcode/BitcodeReader.h"
#include"llvm/Bitcode/BitcodeWriter.h"
#include"llvm/IR/Function.h"
#include"llvm/IR/Module.h"
#include"llvm/Support/CommandLine.h"
#include"llvm/Support/MemoryBuffer.h"
#include"llvm/Support/raw_os_ostream.h"
#include"llvm/Support/Error.h"
#include<iostream>

using namespace llvm;

static cl::opt<std::string> FileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);

int main(int argc, char** argv) {
	cl::ParseCommandLineOptions(argc, argv, "LLVM hello world\n");
	LLVMContext context;
	llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> BitcodeBuffer = llvm::MemoryBuffer::getFile(FileName, true);

	std::cout<<"++++++++++++++++++++++++\n";
	if (!BitcodeBuffer) {
		errs() << "fib.bc not found\n";
		std::cout<<"++++++++++++++++++++++++\n";
		return -1;
	}
	std::cout<<"BitcodeBuffer created!\n";

	MemoryBufferRef BitcodeBufferRef = (**BitcodeBuffer).getMemBufferRef();
	Expected<std::unique_ptr<Module>> m = parseBitcodeFile(BitcodeBufferRef, context);
	if( !m ) {
		errs() << m.takeError() << "\n";
		std::cout<<"++++++++++++++++++++++++\n";
		return -1;
	}
	std::cout<<"Parse BitcodeFile compeleted!\n";
	std::cout<<"++++++++++++++++++++++++\n\n";
	
	raw_os_ostream O(std::cout);
	for(Module::const_iterator i = m.get()->getFunctionList().begin(), e = m.get()->getFunctionList().end(); i != e; i++) {
		if( !i->isDeclaration()) {
			O << i->getName() << " has " << i->size() << " basic block(s).\n";
		}
	}

	return 0;
}
