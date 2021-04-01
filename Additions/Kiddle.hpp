/*  Kiddle.hpp | dictionary of Unicode symbols alternatively signed 7-bits characters 
 on equal-sized frames divisible by four bytes. */

struct Kiddle { typedef __builtin_int_t Nonabsolute; void *tiletree=NULL, *cached₋tile;
  
  union Tetra𝘖rUnicode { int32_t count; char32_t uc; };
  union Smallpool { uint8_t count₋hi₋to₋lo; signed char 𝟽bit₋char; };
  union Synthesizer { uint8_t count₋hi₋to₋lo[4]; int32_t * count; };
  
  __builtin_int_t cached₋number=-1, tile₋count=0, ucAlt𝟽bit₋brk₋count=0, tetras₋per₋tile;
  
  FOCAL
  int
  init(__builtin_int_t tetras₋per₋tile, 
    __builtin_int_t count, void * kbXtiles[], 
    void * (^leaf₋alloc)(int bytes)
  )
  {  this->tetras₋per₋tile = tetras₋per₋tile; 
     if (inflate(count,kbXtiles,leaf₋alloc)) { return -1; }
     return 0;
  } /* ⬷ a corresponding utf-8 files' byte length always indicates enough space. */
  
  int optional₋uninit(void * (^unalloc)(int bytes)) { return 0; }
  /* ⬷ operating system releases allocated memory space when program ends. */
  
#pragma mark the tile collection
  
  int
  inflate(
    __builtin_int_t count, 
    void * kbXtiles[], 
    void * (^leaf₋alloc)(int bytes)
  )
  {
     for (__builtin_int_t i=0; i<count; ++i, ++tile₋count) {
       Treeint leaf { .keyvalue = { tile₋count , __builtin_uint_t(kbXtiles[i]) } };
       void * node = Insert(tiletree,leaf,leaf₋alloc);
       if (node == NULL) { return -1; }
     }
     return 0;
  }
  
  void * particular₋tile(__builtin_int_t exact)
  {
    if (exact == cached₋number) { return cached₋tile; }
    Treeint leafkey { exact, 0 };
    Treeint * seeked = Lookup(tiletree,leafkey);
    if (seeked == NULL) { return NULL; }
    return (void *)(seeked->keyvalue.val);
  }
  
#pragma mark tiles and offsets
  
  void * at(__builtin_int_t slot₋idx, __builtin_int_t tile₋idx, int flavor)
  {
    if (flavor) { return slot₋idx + ((Smallpool *)(particular₋tile(tile₋idx))); }
    else { return slot₋idx + ((Tetra𝘖rUnicode *)(particular₋tile(tile₋idx))); }
  }
  
  Smallpool& at₁(Nonabsolute relative)
  {
    __builtin_int_t tile₋idx=relative/tetras₋per₋tile, slot₋idx=relative%tetras₋per₋tile;
    return (Smallpool&)*(Smallpool *)at(slot₋idx,tile₋idx,0);
  }
  
  Tetra𝘖rUnicode& at₂(Nonabsolute relative)
  {
    __builtin_int_t tile₋idx=relative/tetras₋per₋tile, slot₋idx=relative%tetras₋per₋tile;
    return (Tetra𝘖rUnicode&)*(Tetra𝘖rUnicode *)at(slot₋idx,tile₋idx,1);
  }
  
#pragma mark controlling and linearly traverse text
  
  int copy₋append₋text(int count, signed char cs[], Kiddle::Nonabsolute * ref, 
  /* ⬷ a․𝘬․a '𝟽bit₋pointer' except semantic on inclusion of NULL. */
    void (^inflate)(__builtin_int_t ﹟, void **kbXtiles, bool& cancel)
  )
  { /* optionally grow with a few pages ⤐ */
    __builtin_int_t max₋bytes = 4 * tile₋count * tetras₋per₋tile;
    __builtin_int_t bytes₋overflow = ucAlt𝟽bit₋brk₋count + count - max₋bytes;
    __builtin_int_t bytes₋per₋tile = 4*tetras₋per₋tile;
    if (bytes₋overflow > 0) { bool cancel = false; 
      __builtin_int_t modula = bytes₋overflow % bytes₋per₋tile, 
       ﹟ = bytes₋overflow/bytes₋per₋tile; void * kbXtiles[﹟];
       inflate(1 + ﹟ + (modula == 0 ? 0 : 0), kbXtiles, cancel);
       if (cancel) { return -1; }
    }
    for (int i=0; i<count; ++i, ++ucAlt𝟽bit₋brk₋count) {
      if (ucAlt𝟽bit₋brk₋count == bytes₋per₋tile) { ++tile₋count; ucAlt𝟽bit₋brk₋count=0; }
      /* at₁(ucAlt𝟽bit₋brk₋count,tile₋count).𝟽bit₋char = cs[i]; */
      ((Smallpool *)at(ucAlt𝟽bit₋brk₋count,tile₋count,0))->𝟽bit₋char = cs[i];
    }
    return 0;
  }
  
  int copy₋append₋text(int count, char32_t cs[], Kiddle::Nonabsolute * ref, 
    void (^inflate)(__builtin_int_t ﹟, void **kbXtiles, bool& cancel)
  )
  {
    /* optionally grow with a few pages ⤐ */
    __builtin_int_t max₋uc = tile₋count * tetras₋per₋tile;
    __builtin_int_t uc₋overflow = ucAlt𝟽bit₋brk₋count + count - max₋uc;
    if (uc₋overflow > 0) { bool cancel = false; 
      __builtin_int_t modula = uc₋overflow % tetras₋per₋tile, 
       ﹟ = uc₋overflow/tetras₋per₋tile; void * kbXtiles[﹟];
      inflate(1 + ﹟ + (modula == 0 ? 0 : 0), kbXtiles, cancel);
      if (cancel) { return -1; }
    }
    for (int i=0; i<count; ++i, ++ucAlt𝟽bit₋brk₋count) {
      if (ucAlt𝟽bit₋brk₋count == tetras₋per₋tile) { ++tile₋count; ucAlt𝟽bit₋brk₋count=0; }
      /* at₂(ucAlt𝟽bit₋brk₋count,tile₋count).uc = cs[i]; */
      ((Tetra𝘖rUnicode *)at(ucAlt𝟽bit₋brk₋count,tile₋count,1))->uc = cs[i];
    }
    return 0;
  }
  
  int datum₋text₁(int32_t bytes)
  {
    Nonabsolute relative = ucAlt𝟽bit₋brk₋count + 4*(tile₋count - 1)*tetras₋per₋tile - bytes;
    int32_t bytes2=bytes; Synthesizer synth { .count=&bytes2 };
    Smallpool * first = &at₁(relative);
    (first + 0)->𝟽bit₋char = synth.count₋hi₋to₋lo[0];
    (first + 1)->𝟽bit₋char = synth.count₋hi₋to₋lo[1];
    (first + 2)->𝟽bit₋char = synth.count₋hi₋to₋lo[2];
    (first + 3)->𝟽bit₋char = synth.count₋hi₋to₋lo[3];
    return 0;
  }
  
  int datum₋text₂(int32_t tetras)
  {
    Nonabsolute relative = ucAlt𝟽bit₋brk₋count + (tile₋count - 1)*tetras₋per₋tile - tetras;
    at₂(relative).count = tetras;
    return 0;
  }
  
#pragma mark text comparision
  
  int textual₋similar(𝟽bit₋text txt₁, Nonabsolute relative)
  {
     uint8_t * count₋hi₋to₋lo₋ptr = (uint8_t *)&(at₁(relative).count₋hi₋to₋lo);
     Synthesizer synth;
     synth.count₋hi₋to₋lo[0] = *(count₋hi₋to₋lo₋ptr + 0);
     synth.count₋hi₋to₋lo[1] = *(count₋hi₋to₋lo₋ptr + 1);
     synth.count₋hi₋to₋lo[2] = *(count₋hi₋to₋lo₋ptr + 2);
     synth.count₋hi₋to₋lo[3] = *(count₋hi₋to₋lo₋ptr + 3);
     __builtin_int_t bytes = *synth.count;
     if (txt₁.bytes != bytes) { return 0; }
     for (__builtin_int_t i=0; i<bytes; ++i) {
       if (*(i + txt₁.segment) != at₁(relative + i).𝟽bit₋char) { return 0; }
     }
     return 1;
  }
  
  int textual₋similar(Unicodes uc₁, Nonabsolute relative)
  {
    __builtin_int_t tetras = at₂(relative).count;
    if (uc₁.tetras != tetras) { return 0; }
    for (__builtin_int_t i=0; i<tetras; ++i) {
      if (*(i + uc₁.unicodes) != at₂(relative + i).uc) { return 0; }
    }
    return 1;
  } /* ⬷ continue further with Unicode normalization. */
  
#pragma mark inner recollection a․𝘬․a --<Additions/treeᵚ.hpp>
  
  void * legato=NULL; /* =Map<int128_t, { Nonabsolute,jot,... }> */
  
  struct Node { union Key { __int128_t sgned; __uint128_t bits; } key; 
   Nonabsolute offset; void * jot; Node *right, *left; };
  
   Node * new₋node(__uint128_t fineprint, void * (^alloc)(int bytes)) {
     Node * nodeloc = (Node *)alloc(sizeof(Node));
     if (nodeloc) { return NULL; }
     Node * node = new (nodeloc) struct Node;
     node->key.bits = fineprint; node->left = NULL; node->right = NULL;
     return node;
   }
  
   Node * insert(Node * node, __uint128_t fineprint, void * (^alloc)(int bytes)) {
     /* 1. If the tree is empty, return a new, single node */
     if (node == NULL) { return new₋node(fineprint, alloc); }
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
  void (^inflate)(__builtin_int_t ﹟, void **kbXtiles, bool& cancel)
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
   /*  ⬷ include₁ and include₂ ⤐ */ Kiddle::Nonabsolute ref;
   if (kiddle.copy₋append₋text(uc.tetras,uc.unicodes,&ref,inflate)) { return NULL; }
   if (kiddle.datum₋text₂(uc.tetras)) { return NULL; }
   
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

/* ✁ until ✂️ and store --<shoebox>{Kiddle.hpp} */
/* ✂️ */

