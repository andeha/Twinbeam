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
   struct dynamic₋bag init = { .T=op, .element=item };
   *node=init;
   return node;
}

struct dynamic₋bag * new₋Statement(enum symbol₋class type)
{
   struct dynamic₋bag *node = Alloc(sizeof(struct dynamic₋bag));
   struct dynamic₋bag init = { .T=type, .prev=ΨΛΩ, .next=ΨΛΩ };
   *node=init;
   return node;
}

struct dynamic₋bag * new₋Function(Nonabsolut symbol, struct dynamic₋bag * actual, 
 struct dynamic₋bag * detail)
{
   struct dynamic₋bag *node = Alloc(sizeof(struct dynamic₋bag));
   struct dynamic₋bag init = { .T=procsym, .X.kind=1, .X.store.regularOrIdent=symbol };
   *node=init;
   return node;
}

int indentation=0; Argᴾ ﹟run(Nonabsolut);

void print₋tree(struct dynamic₋bag * item)
{
   typedef void (^Print)(char *);
   typedef void (^Detail)(struct dynamic₋bag * item);
   typedef void (^Every)(struct dynamic₋bag *, Detail);
   Print trace = ^(char * operation) { print("⬚ @⬚\n",﹟s7(operation), 
    ﹟d((__builtin_int_t)item->memory)); indentation+=1; 
    print₋tree(item->l); print₋tree(item->r); indentation+=-1; };
   Every each = ^(struct dynamic₋bag * item₋first, Detail detail) { 
    struct dynamic₋bag * i=item₋first; for (;i;i=i->next) { detail(i); } };
   Detail detail = ^(struct dynamic₋bag * item) { print₋tree(item); };
   switch (item->T)
   {
   case ident: print("ident '⬚' @⬚\n", ﹟run(item->X.store.regularOrIdent),﹟d((__builtin_int_t)item->memory)); break;
   case number: print("number '⬚' @⬚\n", ﹟d(item->X.store.integer), ﹟d((__builtin_int_t)item->memory)); break;
   case times: trace("times"); break;
   case divide: trace("divide"); break;
   case plus: trace("plus"); break;
   case minus: trace("minus"); break;
   case eql: trace("eql"); break;
   case neq: trace("neq"); break;
   case lss: trace("lss"); break;
   case leq: trace("leq"); break;
   case gtr: trace("gtr"); break;
   case geq: trace("geq"); break;
   case callsym: print("call '⬚'\n", ﹟run(item->X.store.regularOrIdent)); break;
   case branch₋goto₋optsym: print("branch ⬚\n", ﹟run(item->X.store.regularOrIdent)); break;
   case ifsym: print("compare\n"); indentation+=1; print₋tree(item->compare₋then); 
    print₋tree(item->compare₋else); indentation+=-1; break;
   case afterward: print("afterward @⬚\n", ﹟d((__builtin_int_t)item->memory)); indentation+=1; 
    print₋tree(item->l); if (item->r) print₋tree(item->r); else print("<unassigned>\n"); break;
   case constsym: print("constsym\n"); each(item->sequence,detail); break;
   case varsym: print("varsym\n"); each(item->sequence,detail); break;
   case procsym: print("procsym '⬚'\n", ﹟run(item->X.store.regularOrIdent)); 
    indentation+=1; each(item->formal,detail); print("\n"); 
    each(item->detail,detail); indentation+=-1; break;
   default: { print("unknown item with symbol-type '⬚'\n", ﹟d((__builtin_int_t)item->T)); }
   }
}

void House(int type, int count, ...)
{ va_prologue(count) typedef struct dynamic₋bag * refers; /* refer-en-ce = auto *. A․𝘬․a 'biblio' and 'redux'. */
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
   case 🅔: { Nonabsolut left = va_unqueue(Nonabsolut);
    void * right = va_unqueue(struct dynamic₋bag *);
    form = new₋Statement(additionssym);
    form->l = new₋Identifier(left);
    form->r = (struct dynamic₋bag *)right;
    break; }
   case 🅕: { Nonabsolut identity = va_unqueue(Nonabsolut);
    void * right = va_unqueue(struct dynamic₋bag *);
    form = new₋Statement(afterward);
    form->l = new₋Identifier(identity);
    form->r = right;
    break; }
   case 🅖: { Nonabsolut callee = va_unqueue(Nonabsolut);
    form = new₋Identifier(callee);
    form->T = callsym;
    break; }
   case 🅗: { void * unit = va_unqueue(struct dynamic₋bag *);
    form = (struct dynamic₋bag *)unit;
    break; }/* statement list */
   case 🅙: { void * condition = va_unqueue(struct dynamic₋bag *);
    void * compare₋then = va_unqueue(struct dynamic₋bag *);
    void * compare₋else = va_unqueue(struct dynamic₋bag *);
    form = new₋Statement(ifsym);
    form->compare₋then = compare₋then;
    form->compare₋else = compare₋else;
    break; } /* condition */
   case 🅛: { Nonabsolut uni₋vers = va_unqueue(Nonabsolut);
    void * serpent = va_unqueue(struct dynamic₋bag *);
    form = new₋Statement(afterward);
    form->l = new₋Identifier(uni₋vers);
    form->r = serpent;
    break; }
   case 🅝: { Nonabsolut identifier = va_unqueue(Nonabsolut);
    void * arg₋u₋men = va_unqueue(struct dynamic₋bag *);
    form = new₋Statement(afterward);
    form->l = new₋Identifier(identifier);
    form->r = arg₋u₋men;
    break; }
   case 🅟: { Nonabsolut sy = va_unqueue(Nonabsolut);
    void * parameters = va_unqueue(struct dynamic₋bag *);
    void * detail = va_unqueue(struct dynamic₋bag *);
    form = new₋Function(sy,(struct dynamic₋bag *)parameters,(struct dynamic₋bag *)detail);
    break; }
   case 🅠: { refers tree = va_unqueue(struct dynamic₋bag *);
    refers reads = va_unqueue(struct dynamic₋bag *);
    if (tree->art==ΨΛΩ) { tree->art=reads; } 
    else { reads->prev=tree->art->last; if (tree->art->last) tree->art->last->next=reads; tree->art->last=reads; }
    break; }
   case 🅡: { refers tree = va_unqueue(struct dynamic₋bag *);
    refers reads = va_unqueue(struct dynamic₋bag *);
    if (tree->var==ΨΛΩ) { tree->var=reads; }
    else { reads->prev=tree->var->last; if (tree->var->last) tree->var->last->next=reads; tree->var->last=reads; }
    break; }
   case 🅩: { refers tree = va_unqueue(struct dynamic₋bag *);
    refers reads = va_unqueue(struct dynamic₋bag *);
    if (tree->pct == ΨΛΩ) { tree->pct=reads; }
    else { reads->prev=tree->pct->last; if (tree->pct->last) tree->pct->last->next=reads; tree->pct->last=reads; }
    break; }
   }
   va_epilogue
}

