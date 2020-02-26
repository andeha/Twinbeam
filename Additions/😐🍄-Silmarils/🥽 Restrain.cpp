/*  Restrain.h | 👓: 'It is actually 'pointer at the top'.' */

#include <Twinbeam.h>

int
Restrain(
  void **pointer, __builtin_int_t words
) /* ⬷ Also 'Intervallic *pointer' a․𝘬․a `TransitiveIntervalPointer`. */
{  /* ⤐ Hypothetically 'pointer arithmetic' max value tracking ahead. ⤐ */
#ifdef __mips__ /* ⤐ Slim-sized `vm_protect`/`mprotect` where-ahead⁇ ⤐ */
    /* if (🐛𝑀𝑍𝐷𝐴(SBT0REG0,SIZE)) { return -1; } */
    /* 🎭𝑀𝑍𝐷𝐴(SBT0REG0,BASE, ^(uint32_t& shifted) { shifted=0; });
    🎭𝑀𝑍𝐷𝐴(SBT0REG0,PRI, ^(uint32_t& shifted) { shifted=0; });
    🎭𝑀𝑍𝐷𝐴(SBT0REG0,SIZE, ^(uint32_t& shifted) { shifted=0; });
    🎭𝑀𝑍𝐷𝐴(SBT0WR0,GROUP1, ^(uint32_t& shifted) { shifted=1; }); */
    return 0;
#elif defined __x86_64__ /* One compiler assumed 'const' when pointer attribute actually is transitive: */
    /* if (mprotect(*pointer, words<<3, PROT_READ | PROT_WRIT)) { return -1; }  ⬷ An interval. */
    *pointer = __bnd_set_ptr_bounds((const void *)*pointer, words<<3); /* `BNDMK` */
    return 0;
#endif
} /* A․𝘬․a `Underwrite` and `SostenutoVolatile`. */

int Validate(void **pointer) /* ⬷ The 'pointer' + 'size a․𝘬․a width' actually fits 128 bits! */
{
#ifdef __mips__
    return 0; /* 🐛𝑀𝑍𝐷𝐴(SBFLAG1,T0PGV1); */
#elif defined __x86_64__ /* MPX */
    __bnd_chk_ptr_ubounds((const void *)*pointer); /* `BNDCU` */
    *pointer = __bnd_init_ptr_bounds((const void *)*pointer);
    return 0;
#endif
} /* A․𝘬․a `Silentpiano`, `RespiteTransactional`, `UnderwriteEmbargo`. */

#pragma mark - ...and the main entry point:

int
main(
  int argc,
  const char * argv[]
)
{
    /* ⚠️: 'Hardware not able to...' */
    return 0;
}

/* See also --<🥽⋆Bounds.cpp>{Intervallic}. */

