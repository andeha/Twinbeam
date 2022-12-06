/*  µ⃝-code-and-tree.cxx | scalar and context and explana. */

struct dynamic₋bag * new₋Identifier(struct Unicodes token)
{
   struct dynamic₋bag * nonode = Alloc(sizeof(struct dynamic₋bag));
   nonode->
   return nonode;
}

struct dynamic₋bag * new₋Numeric(struct dynamic₋bag * item, int type)
{
   struct dynamic₋bag * nonode = Alloc(sizeof(struct dynamic₋bag));
   switch (type) {
   case 1:
     nonode->
     break;
   case 2:
     nonode->
     break;
   }
   
   return nonode;
}

struct dynamic₋bag * new₋Operand(struct dynamic₋bag * left, struct dynamic₋bag * right, int op)
{
   struct dynamic₋bag * node = Alloc(sizeof(struct dynamic₋bag));
   return node;
}

struct dynamic₋bag * new₋Statement(struct dynamic₋bag * item, int type)
{
   struct dynamic₋bag * node = Alloc(sizeof(struct dynamic₋bag));
   return node;
}

void House(int type, int count, ... /* void * ctxt₋bag */)
{ va_prologue(count) __builtin_va_list various;
   switch (type) {
   case 1: { struct Unicodes token = __builtin_va_arg(various,struct Unicodes);
    form = new₋Identifier(token); break; }
   case 2: { void * item = __builtin_va_arg(various,struct dynamic₋bag *);
    int type = __builtin_va_arg(various,int);
    form = new₋Numeric((struct dynamic₋bag *)item,type); break; }
   case 3: { void * left = __builtin_va_arg(various,struct dynamic₋bag *);
    void * right = __builtin_va_arg(various,struct dynamic₋bag *);
    int op = __builtin_va_arg(various,int);
    form = new₋Operand((struct dynamic₋bag *)left,(struct dynamic₋bag *)right,op);
    break; }
   case 4: { void * item = __builtin_va_arg(various,struct dynamic₋bag *);
    int type = __builtin_va_arg(various,int);
    form = new₋Statement((struct dynamic₋bag *)item,type);
    break; }
   }
   va_epilogue
}