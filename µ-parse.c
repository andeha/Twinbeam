
import Twinbeam;

enum symbol₋class { ident=1, number, times, divide, plus, minus, lparen, 
 rparen, eql, neq/*=10*/, lss, leq, gtr, geq, semicolon, termirender, callsym, 
 beginsym, endsym, /* whilesym, dosym, forsym */ branch₋goto₋optsym/*=20*/, elsesym, 
 thensym, ifsym, afterward, constsym, varsym, procsym, period, comma, oddsym/*=30*/, 
 voidsym, sectionsym, textsym, lformalrefpressym, rformalpresentsym, 
 rformalreferencesym, additionssym, colon, label, symbol₋for₋enquery/*=40*/, 
 end₋of₋transmission₋and₋file, uninit₋symbol, 
};

/* clang -g -fmodules-ts -fimplicit-modules -fmodule-map-file=🚦.modules µ-parse.c \
 ../Apps/Source/Releases/libTwinbeam-x86_64.a ../Apps/Additions/monolith-sequent.c */

enum language₋mode { mode₋initial, mode₋integer, mode₋regular, mode₋biblio, mode₋fixpoint };

struct language₋context {
  __builtin_int_t tip₋unicode;
  int carrier; /* 'retrospect did purge newline' and 'retrospect₋detail and retrospect₋summar differs'. */
  enum language₋mode state;
  char32̄_t regular[2048];
  short syms₋in₋regular;
  __builtin_int_t ongoing,render₋newline₋last;
  Trie keys;
};

typedef struct Symbolinterval { int symbols; char32̄_t * start; } Symbolinterval;

struct token₋detail {
  union {
    Symbolinterval regularOrIdent;
    Sequenta number;
  } store;
  int kind;
  __builtin_int_t lineno₋first,lineno₋last,column₋first,column₋last;
};

typedef struct Symbol { enum symbol₋class class; struct token₋detail gritty; } Symbol;

Symbol symbol,retrospect; struct Unicodes text; struct language₋context Ctxt; /* executable and parser. */
/* the global variable `symbol` are among scholars known as `lookahead`. */
Symbol summary₋ground; /*  a․𝘬․a 'memory after reading passed'. */

#define STATE(s) (s == ctxt->state)
#define TRACE₋TOKENS

typedef void (^Utf8)(char8₋t *,__builtin_int_t);

void error(int type, char text[], ...)
{ va_prologue(text);
   int write(int,const char *,...);
   int print﹟(Utf8,const char *,__builtin_va_list);
   Utf8 out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1,(const void *)u8s,bytes); };
   print﹟(out,text,__various);
   print(out,".\n");
   va_epilogue;
}

void assign₋symbol(enum symbol₋class s, Symbol * sym) { sym->class=s; }

int symbol₋equal(enum symbol₋class s) { return symbol.class==s; }

int next₋token₋inner(struct language₋context * ctxt, int newline₋on₋termirender, Symbol * out)
{ __builtin_int_t i,symbols=text.tetras; char32̄_t uc,uc₊₁,uc₊2; int pad₋count=0,sym;
   typedef int (^type)(char32̄_t);
   type digit = ^(char32̄_t uc) { return U'0' <= uc && uc <= U'9'; };
   type letter = ^(char32̄_t uc) { return U'a' <= uc && uc <= U'z'; };
   🧵(identifier,integer₋constant,keyword,trouble,completion) {
   case identifier: assign₋symbol(ident,out); ctxt->syms₋in₋regular=0; ctxt->state=mode₋initial; return 0;
   case integer₋constant: assign₋symbol(number,out); Ctxt.ongoing=0; ctxt->state=mode₋initial; return 0;
   case keyword: assign₋symbol(sym,out); ctxt->syms₋in₋regular=0; ctxt->state=mode₋initial; return 0;
   case completion: assign₋symbol(end₋of₋transmission₋and₋file,out); return 0;
   case trouble: return -1;
   }
again:
   i=ctxt->tip₋unicode,ctxt->tip₋unicode+=1;
   if (i >= symbols) { confess(completion); }
   if (i == symbols - 1) { pad₋count=2; }
   if (i == symbols - 2) { pad₋count=1; }
   uc = *(text.unicodes + i), 
   uc₊₁ = pad₋count >= 2 ? U' ' : *(text.unicodes + i + 1);
   uc₊2 = pad₋count >= 1 ? U' ' : *(text.unicodes + i + 2);
   if (STATE(mode₋initial) && uc == U'\xa') { print("newline passed\n");
     ctxt->render₋newline₋last+=1;
     if (newline₋on₋termirender)
     {
       print("termirender\n");
       assign₋symbol(termirender,out); return 0;
     }
   }
   else if (STATE(mode₋initial) && uc == U'\xd') { }
   else if (STATE(mode₋initial) && uc == U' ') { }
   else if (STATE(mode₋initial) && uc == U'\t') { }
   else if (STATE(mode₋initial) && uc == U'(') { assign₋symbol(lparen,out); return 0; }
   else if (STATE(mode₋initial) && uc == U')') { assign₋symbol(rparen,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'*') { assign₋symbol(times,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'/') { assign₋symbol(divide,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'+') { assign₋symbol(plus,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'-') { assign₋symbol(minus,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'=') { assign₋symbol(eql,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'<' && uc₊₁ == U'>') { ctxt->tip₋unicode+=1; assign₋symbol(neq,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'<' && uc₊₁ == U'=') { ctxt->tip₋unicode+=1; assign₋symbol(leq,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'<') { assign₋symbol(lss,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'>' && uc₊₁ == U'=') { ctxt->tip₋unicode+=1; assign₋symbol(geq,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'>') { assign₋symbol(gtr,out); return 0; }
   else if (STATE(mode₋initial) && uc == U';') { assign₋symbol(semicolon,out); return 0; } /* @<semicolon₋processed@> twice. */
   else if (STATE(mode₋initial) && uc == U':' && uc₊₁ == U'=') { ctxt->tip₋unicode+=1; assign₋symbol(afterward,out); return 0; }
   else if (STATE(mode₋initial) && uc == U':') { assign₋symbol(colon,out); return 0; }
   else if (STATE(mode₋initial) && uc == U',') { assign₋symbol(comma,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'.') { assign₋symbol(period,out); print("754 period\n"); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'*') { assign₋symbol(sectionsym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@') { assign₋symbol(textsym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'<') { assign₋symbol(lformalrefpressym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'>' && uc₊2 == U'=') { assign₋symbol(rformalpresentsym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'>') { assign₋symbol(rformalreferencesym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'\x2405') { assign₋symbol(symbol₋for₋enquery,out); return 0; }
   else if ((STATE(mode₋initial) && letter(uc)) || (STATE(mode₋regular) && (letter(uc) || digit(uc)))) {
     if (ctxt->syms₋in₋regular == 2048) { error(1,"identifier and keyword too long"); confess(trouble); }
     ctxt->regular[ctxt->syms₋in₋regular]=uc;
     ctxt->syms₋in₋regular+=1;
     ctxt->state = mode₋regular;
     if (!(U'a' <= uc₊₁ && uc₊₁ <= U'z')) {
       if (trie₋keyword(ctxt->syms₋in₋regular,ctxt->regular,&sym,&(Ctxt.keys))) { confess(identifier); }
       confess(keyword); }
   }
   else if ((STATE(mode₋initial) || STATE(mode₋integer)) && digit(uc)) {
     ctxt->ongoing *= 10; ctxt->ongoing += uc - U'0';
     ctxt->state = mode₋integer;
     if (!(U'0' <= uc₊₁ && uc₊₁ <= U'9')) { confess(integer₋constant); }
   } /* else if mode₋fixpoint \also in --<􀥳 lingustics-epi.c>{array buffer the}. */
     /* @= #include "u-arithmetic.cxx" */ /* if (x==0) @<array buffer the@> */
   else {
    confess(trouble);
   }
   goto again;
}

void next₋token(struct language₋context * ctxt, int newline₋on₋termirender)
{ int y;
  if (ctxt->tip₋unicode==0) {
    y = next₋token₋inner(ctxt,newline₋on₋termirender,&symbol);
    if (y != 0) { error(1,"scanner error: initial trouble"); exit(2); }
  } else {
    summary₋ground = symbol;
    symbol = retrospect;
  }
  y = next₋token₋inner(ctxt,newline₋on₋termirender,&retrospect);
  if (y != 0) { error(1,"scanner error: advanced failure"); exit(2); }
  if (retrospect.class == constsym || retrospect.class == varsym || retrospect.class == beginsym) { print("inpass semicolon\n"); }
#if defined TRACE₋TOKENS
  switch (symbol.class) {
  case ident: print("identifier\n"); break;
  case number: print("integer-constant\n"); break;
  case lparen: print("'('\n"); break;
  case rparen: print("')'\n"); break;
  case times: print("'*'\n"); break;
  case divide: print("'/'\n"); break;
  case plus: print("'+'\n"); break;
  case minus: print("'-'\n"); break;
  case neq: print("'<>'\n"); break;
  case lss: print("'<'\n"); break;
  case leq: print("'<='\n"); break;
  case gtr: print("'>'\n"); break;
  case geq: print("'>='\n"); break;
  case callsym: print("'call'\n"); break;
  case ifsym: print("'if'\n"); break;
  case thensym: print("'then'\n"); break;
  case elsesym: print("'else'\n"); break;
  /* case whilesym: print("'while'\n"); break;
  case dosym: print("'do'\n"); break; */
  case branch₋goto₋optsym: print("'branch-goto-opt'\n"); break;
  case constsym: print("'const'\n"); break;
  case comma: print("','\n"); break;
  case varsym: print("'var'\n"); break;
  case procsym: print("'transcript'\n"); break;
  case oddsym: print("'odd'\n"); break;
  case beginsym: print("'begin'\n"); break;
  case endsym: print("'end'\n"); break;
  case eql: print("'='\n"); break;
  case colon: print("':'\n"); break;
  case afterward: print("':='\n"); break;
  case termirender: print("'termirender'\n");
  case semicolon: print("';'\n"); break;
  case end₋of₋transmission₋and₋file: print("completion\n"); break;
  case sectionsym: print("'@*'\n"); break;
  case textsym: print("'@'\n"); break;
  case lformalrefpressym: print("'@<'\n"); break;
  case rformalpresentsym: print("'@>='\n"); break;
  case rformalreferencesym: print("'@>'\n"); break;
  case additionssym: print("'additions'\n"); break;
  case label: print("label\n"); break;
  default: print("period and non-sorted generalization.");
  }
#endif
} /* .IF .ELSE .END .INCLUDE .DEFINE. */

void expression(void);

int match(enum symbol₋class s) { if (symbol₋equal(s)) { next₋token(&Ctxt,0); return 1; } return 0; }

int expect(enum symbol₋class s) { if (match(s)) return 1; error(2,"expect: unexpected symbol (⬚)", ﹟d((__builtin_int_t)(symbol.class))); return 0; }

int enrich(enum symbol₋class s, enum symbol₋class not₋passed) { if (symbol₋equal(s) && retrospect.class == not₋passed) { next₋token(&Ctxt,0); return 1; } return 0; }
/*  Consumes one symbols when two symbols matches. */

int at₋opt(enum symbol₋class s, void (*action)()) { if (symbol₋equal(s)) { next₋token(&Ctxt,0); action(); } return 0; }

void valid(int type, enum symbol₋class s, char msg[]) { if (!symbol₋equal(s)) { error(type,msg); } }

int newline₋match(enum symbol₋class s) { if (symbol₋equal(s)) { next₋token(&Ctxt,1); return 1; } return 0; }

/* int superfluous₋expect(enum symbol₋class s) { if (newline₋match(s)) return 1; error(2,"expect: unexpected symbol (⬚)", ﹟d((__builtin_int_t)(symbol.class))); return 0; } */

struct dynamic₋bag {
  struct token₋detail X;
  enum symbol₋class T;
  struct dynamic₋bag *l,*r,*next,*prev,*compare₋then,*compare₋else;
  __uint128_t fineprint;
};

struct dynamic₋bag * summary₋groundfold;

enum { 🅐=1, 🅑, 🅒, 🅓, 🅔, 🅕, 🅖, 🅗, 🅘, 🅙, 🅚, 🅛 };

void House(int type, int count, ...);
void codegenerate();

struct dynamic₋bag * form;
symboltable₋ref identifiers;

#include "µ⃝-code-and-tree.cxx"
/* #include "µ⃝-code-and-arm.cxx" */
#include "µ⃝-code-and-intel.cxx"

void factor(void)
{
   if (match(ident)) { House(🅐,1,summary₋ground.gritty.store.regularOrIdent); }
   else if (match(number)) { House(🅑,2,summary₋ground.gritty.store.number,1); }
   else if (match(lparen)) { expression(); expect(rparen); }
   else { error(2,"factor: syntax error"); next₋token(&Ctxt,0); }
}

void term(void)
{ 
   factor(); struct dynamic₋bag * ground₋fold=form;
   while (symbol₋equal(times) || symbol₋equal(divide)) { next₋token(&Ctxt,0); factor(); 
    House(🅒,3,ground₋fold,form,times); }
} /*  'multiplication' has higher precedence than 'addition'. */

void expression(void)
{
   if (symbol₋equal(plus) || symbol₋equal(minus)) { next₋token(&Ctxt,0); } term();
   while (symbol₋equal(plus) || symbol₋equal(minus)) { next₋token(&Ctxt,0); term(); }
} /*  'addition' has not as high precedence as 'multiplication'. */

void condition(void)
{
   if (match(oddsym)) { expression(); }
   else {
     expression();
     if (symbol₋equal(eql) || symbol₋equal(neq) || symbol₋equal(lss) || symbol₋equal(leq) || symbol₋equal(gtr) || symbol₋equal(geq)) 
     {
       next₋token(&Ctxt,0); expression();
     } /* else {
       error(2,"condition: invalid operator");
       next₋token(&Ctxt,0);
     } */
   }
}

void actual₋list(void)
{
   do { condition(); } while(match(comma));
}

void opt₋etter(void)
{
   void statement(void);
   statement();
}

int faschion₋se₋p(int * newline₋on₋termirender)
{
   return !(retrospect.class==ident || retrospect.class==callsym || retrospect.class==beginsym || retrospect.class==ifsym);
}

int block₋p₋se(int * newline₋on₋termirender)
{
   return !(retrospect.class==procsym || retrospect.class==varsym || retrospect.class==constsym);
}

void statement(void)
{
   if (match(additionssym)) { do { expect(ident); if (match(eql)) { expect(eql); condition(); } } while (match(comma)); }
   else if (match(ident)) {
    if (match(lparen)) { if (!symbol₋equal(rparen)) { actual₋list(); } expect(rparen); }
    else if (match(afterward)) { condition(); }
    else { error(2,"neither assignment, call nor introduction"); }
   }
   else if (enrich(callsym,ident)) { expect(ident); }
   else if (match(beginsym)) { do { statement(); } while (newline₋match(semicolon)); expect(endsym); }
   else if (match(ifsym)) { condition(); expect(thensym); statement(); at₋opt(elsesym,opt₋etter); }
   /* else if (match(whilesym)) { condition(); expect(dosym); statement(); } */
   else { error(2,"statement: syntax error"); next₋token(&Ctxt,0); }
}

void formal₋list(void)
{
   do { expect(ident); expect(/*left₋*/ident); if (!match(comma)) { expect(/*right₋ */ident); } } while(match(comma));
}

void opt₋void(void) { }

void block(void)
{
   if (match(constsym)) {
     do { expect(ident); expect(eql); condition(); 
     } while (match(comma)); at₋opt(semicolon,opt₋void);
   }
   if (match(varsym)) {
     do { expect(ident); if (match(eql)) { expect(eql); condition(); } } while (match(comma));
     at₋opt(semicolon,opt₋void);
   }
   while (match(procsym)) { expect(ident); expect(lparen); if (!symbol₋equal(rparen)) { formal₋list(); } expect(rparen); statement(); }
}

void program(void) { next₋token(&Ctxt,0); block(); valid(2,end₋of₋transmission₋and₋file,"incorrect signature"); }

int main()
{
   char32̄_t * kvlist[] = { U"const",U"var",U"call",U"begin",U"end",U"if",U"then",U"odd",U"transcript",U"else",U"void" };
   int symlist[] = { constsym,varsym,callsym,beginsym,endsym,ifsym,thensym,oddsym,procsym,elsesym,voidsym };
   merge₋to₋trie(11,kvlist,symlist,&(Ctxt.keys));
   Ctxt.state=mode₋initial;
   Ctxt.tip₋unicode=0;
   Ctxt.carrier=0;
   Ctxt.syms₋in₋regular=0;
   Ctxt.ongoing=0;
   Ctxt.render₋newline₋last=0;
   summary₋ground.class = uninit₋symbol;
   text = Run(U"const abcd=321+1,dcba=123;\nvar cdeg,gec,cgb\ntranscript foo() begin\n call window;\nif cdeg <> gec then begin cgb:=1+1; abcd() end else begin cgb:=1-1 end end\n transcript fie()\nbegin\n call view\nend\n transcript fue()\nbegin\ncall control; end");
   program();
   codegenerate();
}

/*
 
 program = block end₋of₋transmission₋and₋file
 block = 'const' ident '=' number { ',' ident '=' number } block₋p₋se
         'var' ident { ',' ident } block₋p₋se
         'transcript' ident '(' { formal-list } ')' statement block₋p₋se
 statement = ident ':=' expression
              { 'call' } ident
             'begin' statement stmt₋se₋p { statment stmt₋se₋p } 'end'
             'if' condition 'then' statement
             / * 'while' condition 'do' statement * /
 condition = 'odd' statment | expression ('='|'#'|'<'|'<='|'>'|'>=') expression
 expression = ['+'|'-'] term {'+'|'-' term}
 term = factor {'*'|'/' factor}
 factor = ident | number | '(' expression ')'
 
 fashion₋se₋p = semicolon₋alternatively₋termirender₋and₋not(ident,'call','begin','if')
 block₋p₋se = termirender₋and₋not('transcript','var','const')
 
 􀈐-language.c */
