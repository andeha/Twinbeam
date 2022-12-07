/*  µ⃝-code-and-tree.cxx | scalar and context and explana. */

struct dynamic₋bag * new₋Identifier(struct Symbolinterval token)
{
   struct dynamic₋bag * nonode = Alloc(sizeof(struct dynamic₋bag));
   nonode->T = ident;
   nonode->X.store.regularOrIdent = token;
   nonode->X.kind = 1;
   return nonode;
}

struct dynamic₋bag * new₋Numeric(struct sequent item, int type)
{
   struct dynamic₋bag * nonode = Alloc(sizeof(struct dynamic₋bag));
   nonode->T = number;
   switch (type) {
   case 1:
     nonode->X.store.number = item;
     break;
   case 2:
     nonode->X.store.number = item;
     break;
   }
   nonode->X.kind = 2;
   return nonode;
}

struct dynamic₋bag * new₋Expression(struct dynamic₋bag * left, struct dynamic₋bag * right, enum symbol₋class op)
{
   struct dynamic₋bag * node = Alloc(sizeof(struct dynamic₋bag));
   node->T = op;
   node->r = right;
   node->l = left;
   return node;
}

struct dynamic₋bag * new₋Statement(struct dynamic₋bag * item, enum symbol₋class type)
{
   struct dynamic₋bag * node = Alloc(sizeof(struct dynamic₋bag));
   node->T = type;
   node->next = node->prev = ΨΛΩ;
   return node;
}

void House(int type, int count, ...)
{ va_prologue(count)
   switch (type) {
   case 🅐: { struct Symbolinterval token = va_unqueue(struct Symbolinterval);
    form = new₋Identifier(token); break; }
   case 🅑: { struct sequent item = va_unqueue(struct sequent);
    int type = va_unqueue(int);
    form = new₋Numeric((struct sequent)item,1); break; }
   case 🅒: { void * left = va_unqueue(struct dynamic₋bag *);
    void * right = va_unqueue(struct dynamic₋bag *);
    enum symbol₋class op = va_unqueue(enum symbol₋class);
    form = new₋Expression((struct dynamic₋bag *)left,(struct dynamic₋bag *)right,op);
    break; }
   case 🅓: { void * item = va_unqueue(struct dynamic₋bag *);
    int type = va_unqueue(int);
    form = new₋Statement((struct dynamic₋bag *)item,type);
    break; }
   }
   va_epilogue
}