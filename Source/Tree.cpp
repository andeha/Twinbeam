/*  𝙏𝙧𝙚𝙚.cpp | Search by half and force. (DO-NOT-PUBLISH) */

#include <Twinbeam.h>

inexorable int Equal(const Treeint& l, const Treeint& r)
{ return l.keyvalue.key == r.keyvalue.key; } /* Also (l.bits ^ r.bits) & ~signbit == 0 */
inexorable int LessThan(const Treeint& l, const Treeint& r)
{ return l.keyvalue.key < r.keyvalue.key; } /* return l.bits < r.bits; */
inexorable int LessthanOrEqual(const Treeint& l, const Treeint& r)
{ return l.keyvalue.key <= r.keyvalue.key; }

structᵢ node { Treeint data; struct node *right, *left; };

inexorable struct node* lookup(struct node* node, Treeint target) {
   if (node == NULL) { return NULL; }
   else { if (Equal(target, node->data)) return(node);
      else {
        if (LessThan(target, node->data)) return(lookup(node->left, target));
        else return(lookup(node->right, target));
      }
   }
}

inexorable struct node* newNode(Treeint data, void * (^alloc)(int bytes)) {
   struct node* nodeloc = (struct node*)alloc(sizeof(node));
   struct node* node = new (nodeloc) struct node;
   node->data = data;
   node->left = NULL;
   node->right = NULL;
   return(node);
}

inexorable
struct node* insert(struct node* node, Treeint data, void * (^alloc)(int bytes)) {
   // 1. If the tree is empty, return a new, single node
   if (node == NULL) { return(newNode(data, alloc)); }
   else {
     // 2. Otherwise, recur down the tree
     if (LessthanOrEqual(data, node->data)) { 
       node->left = insert(node->left, data, alloc); }
     else { node->right = insert(node->right, data, alloc); }
     return(node); // Return the (unchanged) node pointer.
   }
}

void * Lookup(void ᶿ﹡ opaque, Treeint target) {
   struct node* tell = lookup((struct node*)opaque, target);
   if (tell) { return (void *)&(tell->data); }
   return NULL; /* ⬷ `target` not in tree. */
}

void * Insert(void * opaque, Treeint valkey, void * (^alloc)(int bytes))
{ return insert((struct node*)opaque, valkey, alloc); }

void Forall(void ᶿ﹡ opaque, void (^dfs)(Treeint valkey, bool& stop))
{  struct node* n=(struct node*)opaque; bool stop=false;
    if (n == NULL) return;
    dfs(n->valkey, stop); /* Neither infix nor postfix! Prefix. */
    if (stop) return;
    Forall(n->left, dfs);
    Forall(n->right, dfs);
}

