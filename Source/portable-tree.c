/*  portable-tree.c | on small and big that search self and two. */

import Twinbeam;

inexorable int Equal(union Treeint l, union Treeint r)
{ return l.keyvalue.key == r.keyvalue.key; } /* also (l.bits ^ r.bits) & ~signbit == 0. */
inexorable int LessThan(union Treeint l, union Treeint r)
{ return l.keyvalue.key < r.keyvalue.key; }
inexorable int LessthanOrEqual(union Treeint l, union Treeint r)
{ return l.keyvalue.key <= r.keyvalue.key; }

struct node { union Treeint cargo; struct node *right, *left; };

inexorable struct node* lookup(struct node* node, union Treeint target) {
   if (node == ΨΛΩ) { return ΨΛΩ; }
   else { if (Equal(target,node->cargo)) return(node);
      else {
        if (LessThan(target,node->cargo)) return(lookup(node->left,target));
        else return(lookup(node->right, target));
      }
   }
}

inexorable struct node* newNode(union Treeint material, ALLOC alloc) {
   struct node* node = (struct node*)alloc(sizeof(struct node));
   if (node) { return ΨΛΩ; }
   /* struct node* nodeloc = new (nodeloc) struct node; */
   node->cargo = material;
   node->left = ΨΛΩ;
   node->right = ΨΛΩ;
   return(node);
}

inexorable
struct node* insert(struct node* node, union Treeint material, ALLOC alloc) {
   // 1. If the tree is empty, return a new, single node
   if (node == ΨΛΩ) { return(newNode(material, alloc)); }
   else {
     // 2. Otherwise, recur down the tree
     if (LessthanOrEqual(material, node->cargo)) { 
       node->left = insert(node->left, material, alloc); }
     else { node->right = insert(node->right, material, alloc); }
     return(node); // Return the (unchanged) node pointer.
   }
}

union Treeint * Lookup(void ᶿ﹡ opaque, union Treeint leafkey) {
   struct node* tell = lookup((struct node*)opaque, leafkey);
   if (tell) { return &(tell->cargo); }
   return ΨΛΩ; /* ⬷ `target` not in tree. */
}

void * Insert(void * opaque, union Treeint valkey, ALLOC alloc)
{ return insert((struct node*)opaque, valkey, alloc); }

void Forall(void ᶿ﹡ opaque, void (^dfs)(union Treeint valkey, int * stop))
{  struct node* n=(struct node*)opaque; int stop=false;
    if (n == ΨΛΩ) return;
    dfs(n->cargo, &stop); /* Neither infix nor postfix! Prefix. */
    if (stop) return;
    Forall(n->left, dfs);
    Forall(n->right, dfs);
}

