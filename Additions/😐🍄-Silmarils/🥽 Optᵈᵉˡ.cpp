/*  Optᵈᵉˡ.cpp | When an element optionally is deleted. */

#include <Twinbeam.h>

/* To compile: xcrun clang @ccargs_macᵧ² -o Optᵈᵉˡ ../../Source/llvmʳᵗ³.cpp \
   '🥽 Optᵈᵉˡ.cpp' */

template <typename T> struct Optᵈᵉˡ : Opt<T> { bool deleted() { return *this; } };

auto alloc = ^(int bytes) { return Alloc(bytes); };

int 
main(
  int argc, 
  const char * argv[]
)
{
    void * root = NULL; 
    Treeint leaf₁ { .keyvalue={1,0x1} }, leaf₂ { .keyvalue={-2,0x10} }, 
      leaf₃ { .keyvalue={3,0x5} }; root=Insert(root,leaf₁,alloc); 
      root=Insert(root,leaf₂,alloc); root=Insert(root,leaf₃,alloc);
    auto dfs = ^(Treeint valkey, bool& stop) { print("⬚:⬚\n", ﹟d(valkey.keyvalue.key), 
     ﹟x(valkey.keyvalue.val)); };
    Forall(root, dfs); Treeint target = leaf₂;
    Treeint * x = (Treeint *)Lookup(root, target);
    if (x == NULL) { print("Nonavailable\n"); } else { print("⬚\n", ﹟x(x->keyvalue.val)); }
    return 0;
}

