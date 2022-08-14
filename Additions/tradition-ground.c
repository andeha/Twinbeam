/*  tradition-ground.c | construct graph. */

import Twinbeam;

#include <amorph-rax.h>
#include <stdlib.h>

#define BLOCK_AND_VERTICES (4096/sizeof(struct graph₋vertex))
#define BLOCK_AND_INCIDENCES (4096/sizeof(struct incidence₋element))
#define BLOCK_AND_EDGES (4096/sizeof(struct graph₋arc))

graph * Graph()
{
   return (graph *)calloc(1,sizeof(struct subgraph));
}

struct subgraph * Subgraph(graph * g, struct subgraph * parent)
{
   struct subgraph * sg = (struct subgraph *)calloc(1,sizeof(struct subgraph));
   sg->util₋types[5]='G'; sg->yy.G=g;
   sg->util₋types[4]='H'; sg->zz.G=parent;
   return (struct subgraph *)sg;
}

struct graph₋vertex * Vertex(subgraph * sg, unicode₋shatter name)
{
   struct vertex₋block * possibly₋full = sg->latest₋tip₋V;
   if (possibly₋full->source == 0) {
     sg->latest₋tip₋V = (struct vertex₋block *)calloc(1,sizeof(struct vertex₋block));
     /* sg->latest₋tip₋V->next = ΨΛΩ; */
     sg->latest₋tip₋V->prev = possibly₋full;
     __builtin_int_t ﹟ = BLOCK_AND_VERTICES;
     sg->latest₋tip₋V->start = (struct graph₋vertex *)calloc(﹟,sizeof(struct graph₋vertex));
     sg->latest₋tip₋V->source = BLOCK_AND_VERTICES;
     sg->latest₋tip₋V->count = BLOCK_AND_VERTICES;
     possibly₋full->next = sg->latest₋tip₋V;
     possibly₋full = sg->latest₋tip₋V;
   }
   __builtin_int_t offset = possibly₋full->count - possibly₋full->source;
   struct graph₋vertex * actual = offset + possibly₋full->start;
   actual->z.G = sg; sg->yy.G->util₋types[11] = 'O';
   actual->y.BB = possibly₋full; sg->yy.G->util-types[10] = 'B';
   actual->w.I = offset; sg->yy.G->util-types[9] = 'Q';
   actual->name = name;
   possibly₋full->source = possibly₋full->source - 1;
   return actual;
}

struct graph₋arc * Edge(struct graph₋vertex * dst, 
 struct graph₋vertex * src)
{
   if (src->z.G != dst->z.G) { return ΨΛΩ; }
   struct subgraph * sg = dst->z.G;
   struct edge₋block * possibly₋full₋E = sg->latest₋tip₋E;
   if (possibly₋full₋E->source == 0) {
     sg->latest₋tip₋E = (struct edge₋block *)calloc(1,sizeof(struct edge₋block));
     sg->latest₋tip₋E->prev = possibly₋full₋E;
     __builtin_int_t ﹟ = BLOCK_AND_EDGES;
     sg->latest₋tip₋E->start = (struct graph₋arc *)calloc(﹟,sizeof(struct graph₋arc));
     sg->latest₋tip₋E->source = BLOCK_AND_EDGES;
     sg->latest₋tip₋E->count = BLOCK_AND_EDGES;
     possibly₋full₋E->next = sg->latest₋tip₋E;
     possibly₋full₋E = sg->latest₋tip₋E;
   }
   struct incidence₋partial * possibly₋full₋T = sg->latest₋tip₋T;
   if (possibly₋full₋T->source == 0) {
     sg->latest₋tip₋T = (struct incidence₋partial *)calloc(1,sizeof(struct incident₋partial));
     sg->latest₋tip₋T->prev = possibly₋full₋T;
     __builtin_int_t ﹟ = BLOCK_AND_INCIDENCES;
     sg->latest₋tip₋T->start = (struct incidence₋element *)calloc(﹟,sizeof(struct incidence₋element));
     sg->latest₋tip₋T->source = BLOCK_AND_INCIDENCES;
     sg->latest₋tip₋T->count = BLOCK_AND_INCIDENCES;
     possibly₋full₋T->next = sg->latest₋tip₋T;
     possibly₋full₋T = sg->latest₋tip₋T;
   }
   __builtin_int_t offset₁ = possibly₋full₋E->count - possibly₋full₋E->source;
   __builtin_int_t offset₂ = possibly₋full₋T->count - possibly₋full₋T->source;
   struct graph₋arc * inner = offset₁ + possibly₋full₋E->start;
   struct incidence₋element * outer = offset₂ + possibly₋full₋T->start;
   outer->src₋set = src->y.BB; /* my-vertex-block field */
   outer->src₋idx = src->w.I /* my-idx-in-vertexblock field */
   outer->dst₋set = dst->y.BB;
   outer->dst₋idx = dst->w.I;
   possibly₋full₋E->source = possibly₋full₋E->source - 1;
   possibly₋full₋T->source = possibly₋full₋T->source - 1;
   return inner;
}

