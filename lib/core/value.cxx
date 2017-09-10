#include <llvm/IR/LLVMContext.h>

#include <gns/core/value.h>

GNS_THREAD_LOCAL llvm::LLVMContext* llvmContext;

/*
using namespace gns;


struct gnsValueStructure {
  //llvm::Valu
};


gnsValue gnsAllocateValue() {

  return nullptr;
}
*/
void contextStartup() {
  llvmContext = new llvm::LLVMContext();
}

void contextShutdown() {
  delete llvmContext;
  llvmContext = nullptr;
}
