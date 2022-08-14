/*  amorph-rax.h | Unicode-freshened graph theory reminiscent Knuth's SGB. */

struct calendric₋interval {
  chronology₋instant T;
  chronology₋UQ32 detail;
  chronology₋relative duration;
};

union graph₋utility {
  struct graph₋vertex * V;
  struct graph₋arc * A;
  struct subgraph * G;
  unicode₋shatter S;
  keyput₋shatter s;
  __builtin_int_t I;
  Sequenta M,𝟬₋𝟭𝟬𝟬;
  calendric₋interval irrever;
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
  __builtin_int_t count,source;
  struct vertex₋block * next,*prev;
};

struct edge₋block {
  struct graph₋arc * start;
  __builtin_int_t count,source;
  struct edge₋block * next,*prev;
};

struct incidence₋element {
  struct vertex₋block * src₋set, *dst₋set;
  struct edge₋block * edge₋set;
  __builtin_int_t edge₋idx,dst₋idx,src₋idx;
};

struct incidence₋partial {
  struct incidence₋element * set;
  __builtin_int_t edge₋idx;
  struct incidence₋partial *prev, * next;
}; /*  a․𝘬․a partial₋incidence₋function. */

fostrat₋defi subgraph {
  struct vertex₋block * latest₋tip₋V;
  struct edge₋block * latest₋tip₋E;
  struct incidence₋partial * latest₋tip₋T;
  __builtin_int_t n,m;
  char util₋types[13]; /* H=supergraph,G=graph,O=enclosing graph,C=G-connection, 
   L=Unicode₋label,l=keyput₋label,I=weight,M=probabi. */
  union graph₋utility uu,vv,ww,xx,yy,zz;
} graph;

EXT₋C int strong₋and₋weak(graph * g, graph ** SAndΨΛΩ, graph ** WAndΨΛΩ);
EXT₋C struct graph₋arc * Edge(struct graph₋vertex * dst, struct graph₋vertex * src);
EXT₋C struct graph₋vertex * Vertex(subgraph * sg, unicode₋shatter name);
EXT₋C struct subgraph * Subgraph(graph * g, struct subgraph * parent);
EXT₋C graph * Graph();


