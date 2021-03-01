/*  Kiddle.hpp | dictionary of Unicode symbols on equal-sized frames divisible by four bytes. */

struct Kiddle {  typedef __builtin_int_t Nonabsolute; 
  
  union Tetra𝘖rUnicode { int32_t count; char32_t uc; } * cached₋tile; 
  
  void * tiletree=NULL; __builtin_int_t cached₋number=-1, tile₋count=0, uc₋brk=0, 
   tetras₋per₋tile;
  
  int init(__builtin_int_t tetras₋per₋tile, 
    __builtin_int_t count, 
    void * ᵒfᵗᵉⁿ𝟺kb₋tiles[], 
    void * (^leaf₋alloc)(int bytes)
  )
  {  this->tetras₋per₋tile = tetras₋per₋tile; 
     if (inflate(count,ᵒfᵗᵉⁿ𝟺kb₋tiles,leaf₋alloc)) { return -1; }
     return 0;
  } /* ⬷ a corresponding utf-8 files' byte length always indicates enough space. */
  
  /* int optional₋uninit(void * (^unalloc)(int bytes)) { } ⬷ operating system releases 
   allocated memory space when program ends. */
  
#pragma mark tile collection
  
  int inflate(
    __builtin_int_t count, 
    void * ᵒfᵗᵉⁿ𝟺kb₋tiles[], 
    void * (^leaf₋alloc)(int bytes)
  )
  {
     for (__builtin_int_t i=0; i<count; ++i, ++tile₋count) {
       Treeint leaf { .keyvalue = { tile₋count , __builtin_uint_t(ᵒfᵗᵉⁿ𝟺kb₋tiles[i]) } };
       Insert(tiletree, leaf, leaf₋alloc);
     }
     return 0;
  }
  
  Tetra𝘖rUnicode * particular(__builtin_int_t exact)
  {
     if (exact == cached₋number) { return cached₋tile; }
     Treeint leafkey { exact, 0 };
     Treeint * seeked = Lookup(tiletree, leafkey);
     if (seeked == NULL) { return (Tetra𝘖rUnicode *)NULL; }
     return (Tetra𝘖rUnicode *)(seeked->keyvalue.val);
  }
  
#pragma mark indexing
  
  Tetra𝘖rUnicode& at(__builtin_int_t slot₋idx, __builtin_int_t tile₋idx) 
    { return *(slot₋idx + particular(tile₋idx)); }
  
  Tetra𝘖rUnicode& at(Nonabsolute relative) { __builtin_int_t 
    tile₋idx=relative/tetras₋per₋tile, slot₋idx=relative%tetras₋per₋tile;
    return at(slot₋idx,tile₋idx);
  }
  
#pragma mark input
  
  int copy₋append₋text(int count, char32_t cs[], 
    void (^inflate)(__builtin_int_t ﹟, bool& cancel) 
  )
  {
    /* optionally grow with a few pages ⤐ */
    __builtin_int_t max₋uc = tile₋count * tetras₋per₋tile;
    __builtin_int_t uc₋overflow = uc₋brk + count - max₋uc;
    if (uc₋overflow > 0) { bool cancel = false; 
      __builtin_int_t modula = uc₋overflow % tetras₋per₋tile, 
       ﹟ = uc₋overflow/tetras₋per₋tile;
      inflate(1 + ﹟ + (modula == 0 ? 0 : 0), cancel);
      if (cancel) { return -1; }
    }
    for (int i=0; i<count; ++i, ++uc₋brk) {
      if (uc₋brk >= tetras₋per₋tile) { ++tile₋count; uc₋brk=0; }
      at(uc₋brk,tile₋count).uc = cs[i];
    }
    return 0;
  }
  
  int datum₋text(short tetras) {
    Nonabsolute relative = uc₋brk + (tile₋count - 1)*tetras₋per₋tile - tetras;
    at(relative).count = tetras;
    return 0;
  }
  
#pragma mark comparision
  
  int textual₋similar(Unicodes uc₁, Nonabsolute relative) {
    __builtin_int_t tetras = at(relative).count;
    if (uc₁.tetras != tetras) { return 0; }
    for (__builtin_int_t i=0; i<tetras; ++i) {
      if (*(i + uc₁.unicodes) != at(relative + i).uc) { return 0; }
    }
    return 1;
  } /* ⬷ see Unicode normalization. */
  
#pragma mark inner recollection (possibly --<Additions/treeᵚ.hpp>)
  
  void * legato=NULL; /* =Map<int128_t, { Nonabsolute,jot,... }> */
  
  struct Node { union Key { __int128_t sgned; __uint128_t bits; } key; 
   Nonabsolute offset; void * jot; Node *right, *left; };
  
   Node * newNode(__uint128_t fineprint, void * (^alloc)(int bytes)) {
     Node * nodeloc = (Node *)alloc(sizeof(Node));
     if (nodeloc) { return NULL; }
     Node * node = new (nodeloc) struct Node;
     node->key.bits = fineprint; node->left = NULL; node->right = NULL;
     return node;
   }
  
   Node * insert(Node * node, __uint128_t fineprint, void * (^alloc)(int bytes)) {
     /* 1. If the tree is empty, return a new, single node */
     if (node == NULL) { return newNode(fineprint, alloc); }
     else { /* 2. otherwise, recur down the tree */
       if (fineprint <= node->key.bits) {
         node->left = insert(node->left, fineprint, alloc); }
       else { node->right = insert(node->right, fineprint, alloc); }
       return node; /* Return the (unchanged) node pointer. */
     }
   }
  
   Node * lookup(Node * node, __uint128_t target) {
     if (node == NULL) { return NULL; }
     else { if (target == node->key.bits) { return node; } 
        else {
          if (target < node->key.bits) return lookup(node->left, target);
          else return lookup(node->right, target);
        }
     }
   }
   
#pragma mark recollection
  
  Node * store₋impression(__uint128_t fineprint, void * (^leaf₋alloc)(int bytes))
  {
     return insert((Node *)legato, fineprint, leaf₋alloc);
  }
  
  Node * seek₋impression(__uint128_t fineprint)
  {
     return lookup((Node *)legato, fineprint);
  }
  
}; /* ⬷ a․𝘬․a 'a-lot-plus-a-reminiscence'. */

/**
    
    Finds the corresponding post-it JOT for a given Unicode fragment.
    
    @param kiddle The collection to search
    
    @param uc The symbolic fragment under analysis
    
    @param jot₋alloc The dynamic memory allocator used when creating a new 
      post-it jot
    
    @param leaf₋alloc The dynamic memory allocator to-use when creating 
      a new post-it jot
    
    @param inflate Block to allocate tiles and call the 'inflate' method
    
    @return a pointer to a post-it jot. Returns NULL on various errors.
    
 */

template <typename JOT>
JOT * 
Match(Kiddle& kiddle, Unicodes uc, 
  void * (^jot₋alloc)(int bytes), 
  void * (^leaf₋alloc)(int bytes), 
  void (^inflate)(__builtin_int_t ﹟, bool& cancel) 
)
{
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __uint128_t prime = (__uint128_t)0b1<<88 | 0b1<<8 | 0x3b, 
      h = __uint128_t(0x6c62272e07bb0142)<<64 | 0x62b821756295c58d;
   
     auto FNV₋1b = ^(void * materialToHash, __builtin_int_t bytes)
     {
       uint8_t * p = (uint8_t *)materialToHash;
       for (__builtin_int_t i=0; i<bytes; ++i) { h = (h ^ prime) * p[i]; }
     }; /* ⬷ possibly-maybe collision-resistant as a prime. */
   
   FNV₋1b((void *)(uc.unicodes), uc.tetras*4);
   
   Kiddle::Node * agree; uint8_t eot=0x4;
   
again: /* zero, one or multiple matches may occur ⤐ */
   
   agree = kiddle.seek₋impression(h);
   
   if (agree == NULL) { goto ended; }
   
   if (kiddle.textual₋similar(uc,agree->offset)) { return agree->jot; }
   
   /* identical yet non-similar ⤐ */ FNV₋1b(&eot,1);
   
   goto again;
   
ended: /* include a fresh and formerly non-existing entry ⤐ */
   
   agree = kiddle.store₋impression(h,leaf₋alloc);
   if (agree == NULL) { return NULL; }
   agree->jot = (JOT *)jot₋alloc(sizeof(JOT));
   /*  ⬷ include₁ and include₂ ⤐ */
   if (kiddle.copy₋append₋text(uc.tetras,uc.unicodes,inflate)) { return NULL; }
   if (kiddle.datum₋text(uc.tetras)) { return NULL; }
   
   return agree->jot;
}

inline int Setup₋shattered(unsigned expeditionary, Kiddle& kiddle)
{ __builtin_int_t 🥈 tetras₋per₋tile = 4096/4;
   __builtin_int_t ﹟=100; void * 𝟺kbframes[﹟];
   if (CoalescingAcquire(expeditionary,𝟺kbframes,﹟)) { return -1; }
   auto leaf₋alloc = ^(int bytes) { return Alloc(bytes); };
   if (kiddle.init(tetras₋per₋tile,﹟,𝟺kbframes,leaf₋alloc)) { return -2; }
   return 0;
}

inline int Setup₋filelength₋enough(Kiddle& kiddle, __builtin_int_t bytes)
{
   __builtin_int_t tetras₋per₋tile = bytes/4;
   void * tiles[] = { Alloc(bytes) };
   auto leaf₋alloc = ^(int bytes) { return Alloc(bytes); };
   if (kiddle.init(tetras₋per₋tile,1,tiles,leaf₋alloc)) { return -1; }
   return 0;
}


