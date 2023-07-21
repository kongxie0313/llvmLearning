#include "llvm/ExecutionEngine/MCJIT.h"

#include"llvm/Bitcode/BitcodeReader.h"
#include"llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include"llvm/Support/raw_os_ostream.h"
#include"llvm/Support/Error.h"
#include "llvm/Support/FileSystem.h"

using namespace std;

bool UseMCJIT = true;

int main() {
	llvm::InitializeNativeTarget();

	if(UseMCJIT) {
		llvm::InitializeNativeTargetAsmPrinter();
		llvm::InitializeNativeTargetAsmParser();
	}

	llvm::LLVMContext Context;
	llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> BitcodeBuffer = llvm::MemoryBuffer::getFile("./sum.bc", true);
        if (!BitcodeBuffer) {
		llvm::errs() << "sum.bc not found\n";
                return -1;
        }
	llvm::MemoryBufferRef BitcodeBufferRef = (**BitcodeBuffer).getMemBufferRef();
	llvm::Expected<std::unique_ptr<llvm::Module>> m = llvm::parseBitcodeFile(BitcodeBufferRef, Context);

	std::unique_ptr<llvm::ExecutionEngine> EE;
	if (UseMCJIT)
		EE.reset(llvm::EngineBuilder(std::move(m.get())).create());
	else
		llvm::errs() << "Not use MCJIT. exited!\n";

	int (*Sum)(int, int) = NULL;
	if (UseMCJIT)
		Sum = (int (*)(int, int)) EE->getFunctionAddress(std::string("sum"));
	else
		llvm::errs() << "Not use MCJIT. exited!\n";

	int res = Sum(4, 5);
	llvm::errs() << "Sum result: " << res << "\n";
	res = Sum(res, 6);
	llvm::errs() << "Sum result: " << res << "\n";

	llvm::llvm_shutdown();
	return 0;
}
