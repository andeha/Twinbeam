/*  amorph-rax.h | Unicode-freshened graph theory reminiscent Knuth's SGB. */

union graph₋utility {
  struct graph₋vertex * V;
  struct graph₋arc * A;
  struct subgraph * G;
  unicode₋shatter S;
  __builtin_int_t I;
};
struct graph₋vertex {
  struct graph₋arc * arcs;
  unicode₋shatter name;
  union graph₋utility u,v,w,y,z;
};
struct graph₋arc {
  struct graph₋vertex * tip;
  struct graph₋arc * next;
  __builtin_int_t length;
  union graph₋utility a,b;
};
typedef struct subgraph {
  struct graph₋vertex * vertices;
  __builtin_int_t n,m;
  char util₋types[15];
  union graph₋utility uu,vv,ww,xx,yy,zz;
} Graph;

