/*  µ⃝-general-register.cxx | register allocation. */

void assign(struct dynamic₋bag * expression)
{ struct dynamic₋bag * item=expression;
   typedef void (^Init)();
   Init ground = ^{
     item->l->leg=1,item->r->leg=2,assign(item->l),assign(item->r);
     item->memory=max(item->l->memory,item->r->memory);
   };
   Init leaf = ^{ if (leq==1) { item->memory=0; } else { item->memory=1; } };
again:
   if (item==ΨΛΩ) { return; }
   switch (item->T)
   {
   case ident: leaf(); break;
   case number: leaf(); break;
   case times: ground(); break; /* max(2,l1,l2) alternatively l1 + 1 when l1!=l2. */
   case divide: ground(); break;
   case plus: ground(); break;
   case minus: ground(); break;
   case eql: ground(); break;
   case neq: ground(); break;
   case lss: ground(); break;
   case leq: ground(); break;
   case gtr: ground(); break;
   case geq: ground(); break;
   case callsym: assign(item->sequence); break;
   case branch₋goto₋optsym: assign(item->sequence); break;
   case elsesym: assign(item->sequence); break;
   case thensym: assign(item->sequence); break;
   case ifsym: assign(item->sequence); break;
   case afterward: assign(item->r); break;
   case constsym: assign(item->sequence); break;
   case varsym: break;
   case procsym: assign(item->sequence); break;
   case oddsym: assign(item->sequence); break;
   case end₋of₋transmission₋and₋file: break;
   default: break;
   }
   item=item->next; goto again;
}

