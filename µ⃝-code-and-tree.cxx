/*  µ⃝-code-and-tree.cxx | scalar and context and explana. */

struct dynamic₋bag * new₋Identifier(Nonabsolut token)
{
   struct dynamic₋bag * nonode = Alloc(sizeof(struct dynamic₋bag));
   struct dynamic₋bag init = { .T=ident, .X.kind=1, .X.store.regularOrIdent=token };
   *nonode = init;
   return nonode;
}

struct dynamic₋bag * new₋Numeric(struct token₋detail item, int type)
{
   struct dynamic₋bag * nonode = Alloc(sizeof(struct dynamic₋bag));
   nonode->T=number;
   switch (type)
   {
   case 1:
     nonode->X.store.number=item.store.number;
     nonode->X.kind=2;
     break;
   case 2:
     nonode->X.store.integer=item.store.integer;
     nonode->X.kind=3;
     break;
   }
   return nonode;
}

struct dynamic₋bag * new₋Expression(struct dynamic₋bag * left, struct dynamic₋bag * right, enum symbol₋class op)
{
   struct dynamic₋bag *node = Alloc(sizeof(struct dynamic₋bag));
   struct dynamic₋bag init = { .T=op, .l=left, .r=right };
   *node = init;
   return node;
}

struct dynamic₋bag * new₋Unary(struct dynamic₋bag * item, enum symbol₋class op)
{
   struct dynamic₋bag *node = Alloc(sizeof(struct dynamic₋bag));
   struct dynamic₋bag init = { .T=op, .expression=item };
   *node=init;
   return node;
}

struct dynamic₋bag * new₋Statement(struct dynamic₋bag * item, enum symbol₋class type)
{
   struct dynamic₋bag *node = Alloc(sizeof(struct dynamic₋bag));
   struct dynamic₋bag init = { .T=type, .prev=ΨΛΩ, .next=ΨΛΩ };
   *node=init;
   return node;
}

void House(int type, int count, ...)
{ va_prologue(count)
   switch (type)
   {
   case 🅐: { Nonabsolut token = va_unqueue(Nonabsolut);
    form = new₋Identifier(token); break; }
   case 🅑: { struct token₋detail item = va_unqueue(struct token₋detail);
    int type = va_unqueue(int);
    form = new₋Numeric((struct token₋detail)item,1); break; }
   case 🅒: { void * left = va_unqueue(struct dynamic₋bag *);
    void * right = va_unqueue(struct dynamic₋bag *);
    enum symbol₋class op = va_unqueue(enum symbol₋class);
    form = new₋Expression((struct dynamic₋bag *)left,(struct dynamic₋bag *)right,op);
    break; }
   case 🅔: { void * item = va_unqueue(struct dynamic₋bag *);
    int type = va_unqueue(int);
    form = new₋Statement((struct dynamic₋bag *)item,type);
    break; }
   case 🅕: { Nonabsolut identity = va_unqueue(Nonabsolut);
    void * right = va_unqueue(struct dynamic₋bag *);
    form = new₋Statement(new₋Identifier(identity),afterward);
    break; }
   case 🅖: { Nonabsolut callee = va_unqueue(Nonabsolut);
    form = new₋Identifier(callee);
    form->T = callsym;
    break; }
   case 🅗: { /* statement list */
      break; }
   case 🅙: { /* condition */
      break; }
   case 🅛: { Nonabsolut uni₋vers = va_unqueue(Nonabsolut);
      void * serpent = va_unqueue(struct dynamic₋bag *);
      break; }
   case 🅝: { Nonabsolut identifier = va_unqueue(Nonabsolut);
      void * arg₋u₋ment = va_unqueue(struct dynamic₋bag *);
      break; }
   case 🅟: { Nonabsolut _symbol = va_unqueue(Nonabsolut);
      void * parameters = va_unqueue(struct dynamic₋bag *);
      void * detail = va_unqueue(struct dynamic₋bag *);
      break; }
   }
   va_epilogue
}

