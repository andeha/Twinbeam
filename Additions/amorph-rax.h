/*  amorph-rax.h | Unicode-freshened graph theory reminiscent Knuth's SGB. */

union graph₋utility {
  struct graph₋vertex * V;
  struct graph₋arc * A;
  struct subgraph * G;
  unicode₋shatter S;
  keyput₋shatter s;
  __builtin_int_t I;
};

struct graph₋vertex {
  unicode₋shatter name;
  union graph₋utility u,v,w,y,z;
};

struct graph₋arc {
  __builtin_int_t length;
  union graph₋utility a,b;
};

struct vertex₋block {
  struct graph₋vertex * start;
  __builtin_int_t count;
};

struct edge₋block {
  struct graph₋edge * start;
  __builtin_int_t count;
};

struct incidence₋element {
  struct vertex₋block * src₋set, *dst₋set;
  struct edge₋block * edge₋set;
  __builtin_int_t edge₋idx,dst₋idx,src₋idx;
};

struct incidence₋partial {
  struct incidence₋element * set;
  __builtin_int_t edge₋idx;
}; /*  a․𝘬․a partial₋incidence₋function. */

fostrat₋defi subgraph {
  struct vertex₋block * tip;
  struct edge₋block * tip;
  struct incidence₋partial * tip;
  __builtin_int_t n,m;
  char util₋types[15]; /* P=subgraph₋next,N=subgraph₋prev,C=connection, 
   L=Unicode₋label,l=keyput₋label,I=weight. */
  union graph₋utility uu,vv,ww,xx,yy,zz;
} Graph;

EXT₋C int strong₋and₋weak(Graph * g, Graph ** SAndΨΛΩ, Graph ** WAndΨΛΩ);

