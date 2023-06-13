#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
#include <map>

using namespace llvm;

namespace {
	class FnArgCnt : public FunctionPass {
	public:
		static char ID;
		std::map<Type::TypeID, std::string> typeMap;
		FnArgCnt() : FunctionPass(ID) {
			typeMap[Type::HalfTyID] = "HalfTyID: 16-bit floating point type";
			typeMap[Type::BFloatTyID] = "BFloatTyID: 16-bit floating point type (7-bit significand)";
			typeMap[Type::FloatTyID] = "FloatTyID: 32-bit floating point type";
			typeMap[Type::DoubleTyID] = "DoubleTyID: 64-bit floating point type";
			typeMap[Type::X86_FP80TyID] = "X86_FP80TyID: 80-bit floating point type (X87)";
			typeMap[Type::FP128TyID] = "FP128TyID: 128-bit floating point type (112-bit significand)";
			typeMap[Type::PPC_FP128TyID] = "PPC_FP128TyID: 128-bit floating point type (two 64-bits, PowerPC)";
			typeMap[Type::VoidTyID] = "VoidTyID: type with no size";
			typeMap[Type::LabelTyID] = "LabelTyID: Labels";
			typeMap[Type::MetadataTyID] = "MetadataTyID: Metadata";
			typeMap[Type::X86_MMXTyID] = "X86_MMXTyID: MMX vectors (64 bits, X86 specific)";
			typeMap[Type::X86_AMXTyID] = "X86_AMXTyID: AMX vectors (8192 bits, X86 specific)";
			typeMap[Type::TokenTyID] = "TokenTyID: Tokens";

			typeMap[Type::IntegerTyID] = "IntegerTyID: Arbitrary bit width integers";
			typeMap[Type::FunctionTyID] = "FunctionTyID: Functions";
			typeMap[Type::PointerTyID] = "PointerTyID: Pointers";
			typeMap[Type::StructTyID] = "StructTyID: Structures";
			typeMap[Type::ArrayTyID] = "ArrayTyID: Arrays";
			typeMap[Type::FixedVectorTyID] = "FixedVectorTyID: Fixed width SIMD vector type";
			typeMap[Type::ScalableVectorTyID] = "ScalableVectorTyID: Scalable SIMD vector type";
			typeMap[Type::TypedPointerTyID] = "TypedPointerTyID: Typed pointer used by some GPU targets";
			typeMap[Type::TargetExtTyID] = "TargetExtTyID: Target extension type";
		}

		virtual bool runOnFunction(Function &F) {
			errs() << "FnArgCnt --- ";
			errs() << F.getName() << ": ";
			printType(F.getReturnType()->getTypeID());
			return false;
		}
		void printType(Type::TypeID id) {
			std::map<Type::TypeID, std::string>::iterator iter = typeMap.find(id);
			if(iter != typeMap.end()) {
				errs() << "Return typeid: " << iter->first << ". Info: " << iter->second << '\n';
			} else {
				errs() << "Unknown return typeid: " << id << '\n';
			}
		}
	};
}

char FnArgCnt::ID = 0;
static RegisterPass<FnArgCnt> X("fnargcnt", "Function Argument Count Pass", false, false);
