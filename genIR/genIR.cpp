#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/FileSystem.h>

using namespace llvm;

static LLVMContext &getGlobalContext() {
  static LLVMContext GlobalContext;
  return GlobalContext;
}

Module* makeLLVMModule() {
	Module* mod = new Module("sum.ll", getGlobalContext());
	mod->setDataLayout("e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
	mod->setTargetTriple("x86_64-unknown-linux-gnu");

	SmallVector<Type*, 2> FuncTyArgs;
	FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
	FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
	FunctionType* FuncTy = FunctionType::get(
			/*Result=*/ IntegerType::get(mod->getContext(), 32),
			/*Params=*/ FuncTyArgs,
			/*isVarArg=*/ false);

	Function* funcSum = Function::Create(
			/*Type=*/ FuncTy,
			/*Linkage=*/ GlobalValue::ExternalLinkage,
			/*Name=*/ "sum",
			/**/ mod);
	funcSum->setCallingConv(CallingConv::C);

	Function::arg_iterator args = funcSum->arg_begin();
	Value* int32_a = args++;
	int32_a->setName("a");
	Value* int32_b = args++;
	int32_b->setName("b");

	const DataLayout &DL = mod->getDataLayout();
	unsigned AllocaAS = DL.getAllocaAddrSpace();
	BasicBlock* labelEntry = BasicBlock::Create(mod->getContext(), "entry", funcSum, 0);

	// Block entry (label_entry)
	AllocaInst* ptrA = new AllocaInst(IntegerType::get(mod->getContext(), 32), AllocaAS, "a.addr", labelEntry);
	ptrA->setAlignment(llvm::Align(4));
	AllocaInst* ptrB = new AllocaInst(IntegerType::get(mod->getContext(), 32), AllocaAS, "b.addr", labelEntry);
	ptrB->setAlignment(llvm::Align(4));

	StoreInst* st0 = new StoreInst(int32_a, ptrA, false, labelEntry);
	st0->setAlignment(llvm::Align(4));
	StoreInst* st1 = new StoreInst(int32_b, ptrB, false, labelEntry);
	st1->setAlignment(llvm::Align(4));

	LoadInst* ld0 = new LoadInst(IntegerType::get(mod->getContext(), 32), ptrA, "", false, labelEntry);
	ld0->setAlignment(llvm::Align(4));
	LoadInst* ld1 = new LoadInst(IntegerType::get(mod->getContext(), 32), ptrB, "", false, labelEntry);
	ld1->setAlignment(llvm::Align(4));
	BinaryOperator* addRes = BinaryOperator::Create(Instruction::Add, ld0, ld1, "add", labelEntry);
	ReturnInst::Create(mod->getContext(), addRes, labelEntry);

	return mod;
}

int main() {
	Module* Mod = makeLLVMModule();
	verifyModule(*Mod, &llvm::errs());
	std::error_code EC;
	std::unique_ptr<ToolOutputFile> Out(new ToolOutputFile("./sum.bc", EC, sys::fs::OF_None));
	if(EC) {
		errs() << "ToolOutputFile ERROR!\n";
		return -1;
	}
	WriteBitcodeToFile(*Mod, Out->os());
	Out->keep();

	return 0;
}
