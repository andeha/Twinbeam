
import Twinbeam;

enum symbol₋class { ident=1, number, times, divide, plus, minus, lparen, 
 rparen, eql, neq, lss, leq, gtr, geq, semicolon, termi₋render, callsym, 
 beginsym, endsym, /* whilesym, dosym, forsym */ branch₋goto₋optsym, elsesym, 
 thensym, ifsym, afterward, constsym, varsym, procsym, period, comma, oddsym, 
 voidsym, sectionsym, textsym, lformalpresentsym, rformalpresentsym, 
 rformalreferencesym, end₋of₋transmission₋and₋file
};

/* clang -g -fmodules-ts -fimplicit-modules -fmodule-map-file=🚦.modules µ-parse.c \
 ../Apps/Source/Releases/libTwinbeam-x86_64.a ../Apps/Additions/monolith-sequent.c */

enum language₋mode { mode₋initial, mode₋integer, mode₋regular, mode₋biblio, mode₋fixpoint };

struct language₋context {
  __builtin_int_t tip₋unicode;
  enum language₋mode state;
  char32̄_t regular[2048];
  short syms₋in₋regular;
  __builtin_int_t ongoing,render₋newline₋last;
  Trie keys;
};

typedef struct { int symbols; char32̄_t * start; } Symbolinterval;

struct token₋detail {
  union {
    Symbolinterval regularOrIdent;
    Sequenta figure;
  } store;
  int kind;
  __builtin_int_t lineno₋first,lineno₋last,column₋first,column₋last;
};

typedef struct Symbol { enum symbol₋class class; struct token₋detail gritty; } Symbol;

Symbol symbol,retrospect; struct Unicodes text; struct language₋context Ctxt; /* executable and parser. */
/* the global variable `symbol` are among scholars known as `lookahead`. */

#define STATE(s) (s == ctxt->state)
#define TRACE₋TOKENS

void error(int type, char msg[], ...) { print("⬚.\n", ﹟s7(msg)); }

void assign₋symbol(enum symbol₋class s, Symbol * sym) { sym->class=s; }

int symbol₋equal(enum symbol₋class s) { return symbol.class==s; }

int next₋token₋inner(struct language₋context * ctxt, int return₋equal₋semicolon, Symbol * out)
{ __builtin_int_t i,symbols=text.tetras; char32̄_t uc,uc₊₁,uc₊2; int left₋least=0,sym;
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
   if (i == symbols - 1) { left₋least=1; }
   if (i == symbols - 2) { left₋least=2; }
   uc = *(text.unicodes + i), 
   uc₊₁ = left₋least >= 1 ? U' ' : *(text.unicodes + i + 1);
   uc₊2 = left₋least >= 2 ? U' ' : *(text.unicodes + i + 2);
   if (STATE(mode₋initial) && uc == U'\xa') {
     ctxt->render₋newline₋last+=1;
     if (return₋equal₋semicolon)
     {
       print("replaced render-newline with and reported semicolon\n");
       assign₋symbol(semicolon,out); return 0;
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
   else if (STATE(mode₋initial) && uc == U',') { assign₋symbol(comma,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'.') { assign₋symbol(period,out); print("754 period\n"); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'*') { assign₋symbol(sectionsym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@') { assign₋symbol(textsym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'<') { assign₋symbol(lformalpresentsym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'>' && uc₊2 == U'=') { assign₋symbol(rformalpresentsym,out); return 0; }
   else if (STATE(mode₋initial) && uc == U'@' && uc₊₁ == U'>') { assign₋symbol(rformalreferencesym,out); return 0; }
   else if ((STATE(mode₋initial) && letter(uc)) || (STATE(mode₋regular) && (letter(uc) || digit(uc)))) {
     if (ctxt->syms₋in₋regular == 2048) { error(1,"identifier and keyword too long"); confess(trouble); }
     ctxt->regular[ctxt->syms₋in₋regular] = uc;
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
   } /* else if mode₋fixpoint. */
   else {
    confess(trouble);
   }
   goto again;
}

void next₋token(struct language₋context * ctxt, int semicolon₋equal₋return)
{ int y;
  if (ctxt->tip₋unicode==0) {
    y = next₋token₋inner(ctxt,semicolon₋equal₋return,&symbol);
    if (y != 0) { error(1,"scanner error: initial trouble"); exit(2); }
  } else {
    symbol = retrospect;
  }
  y = next₋token₋inner(ctxt,semicolon₋equal₋return,&retrospect);
  if (y != 0) { error(1,"scanner error: advanced failure"); exit(2); }
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
  case afterward: print("':='\n"); break;
  case semicolon: print("';'\n"); break;
  case end₋of₋transmission₋and₋file: print("completion\n"); break;
  case sectionsym: print("@*"); break;
  case textsym: print("@"); break;
  case lformalpresentsym: print("@<"); break;
  case rformalpresentsym: print("@>="); break;
  case rformalreferencesym: print("@>"); break;
  default: print("period and non-sorted generalization.");
  }
#endif
}

void expression(void);

int match(enum symbol₋class s) { if (symbol₋equal(s)) { next₋token(&Ctxt,0); return 1; } return 0; }

int expect(enum symbol₋class s) { if (match(s)) return 1; error(2,"expect: unexpected symbol"); return 0; }

int enriching(enum symbol₋class s, enum symbol₋class not₋passed) { if (symbol₋equal(s) && retrospect.class == not₋passed) { next₋token(&Ctxt,0); return 1; } return 0; }
/*  Consumes one symbols when two symbols matches. */

int at₋opt(enum symbol₋class s, void (*action)()) { if (symbol₋equal(s)) { next₋token(&Ctxt,0); action(); } return 0; }

void valid(int type, enum symbol₋class s, char msg[]) { if (!symbol₋equal(s)) { error(type,msg); } }

int superfluous₋match(enum symbol₋class s) { if (symbol₋equal(s)) { next₋token(&Ctxt,1); return 1; } return 0; }

int superfluous₋expect(enum symbol₋class s) { if (superfluous₋match(s)) return 1; error(2,"expect: unexpected symbol"); return 0; }

void factor(void)
{
   if (match(ident)) { ; }
   else if (match(number)) { ; }
   else if (match(lparen)) { expression(); expect(rparen); }
   else { error(2,"factor: syntax error"); next₋token(&Ctxt,0); }
}

void term(void)
{
   factor();
   while (symbol₋equal(times) || symbol₋equal(divide)) { next₋token(&Ctxt,0); factor(); }
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

void opt₋etter()
{
   void statement(void);
   statement();
}

void statement(void)
{
   if (match(ident)) {
    if (match(lparen)) { /* actual₋list() */ expect(rparen); }
    else if (match(afterward)) { condition(); }
    /* expect(afterward); condition(); */
   }
   else if (enriching(callsym,ident)) { expect(ident); }
   else if (match(beginsym)) { do { statement(); } while (superfluous₋match(semicolon)); expect(endsym); }
   else if (match(ifsym)) { condition(); expect(thensym); statement(); at₋opt(elsesym,opt₋etter); }
   /* else if (match(whilesym)) { condition(); expect(dosym); statement(); } */
   else { error(2,"statement: syntax error"); next₋token(&Ctxt,0); }
}

void block(void)
{
  if (match(constsym)) {
    do { expect(ident); expect(eql); condition(); 
    } while (match(comma)); superfluous₋expect(semicolon);
  }
  if (match(varsym)) {
    do { expect(ident); } while (match(comma));
    superfluous₋expect(semicolon);
  }
  while (match(procsym)) { expect(ident); expect(lparen); /* formal₋list(); */ expect(rparen); block(); }
  statement();
}

void program(void) { next₋token(&Ctxt,0); block(); valid(2,end₋of₋transmission₋and₋file,"incorrect signature"); }

int main()
{
   char32̄_t * kvlist[] = { U"const",U"var",U"call",U"begin",U"end",U"if",U"then",U"odd",U"transcript",U"else",U"void" };
   int symlist[] = { constsym,varsym,callsym,beginsym,endsym,ifsym,thensym,oddsym,procsym,elsesym,voidsym };
   merge₋to₋trie(11,kvlist,symlist,&(Ctxt.keys));
   Ctxt.state=mode₋initial;
   Ctxt.tip₋unicode=0;
   Ctxt.syms₋in₋regular=0;
   Ctxt.ongoing=0;
   Ctxt.render₋newline₋last=0;
   text = Run(U"const abcd=321+1,dcba=123\nvar cdeg,gec,cgb\nbegin\n call elder;\nif cdeg <> gec then begin cgb:=1+1; abcd() end else begin cgb:=1-1 end end");
   program();
}

/*
 
 program = block end₋of₋transmission₋and₋file
 block = 'const' ident '=' number { ',' ident '=' number } ';'
         'var' ident { ',' ident } ';'
 statement = ident ':=' expression
              { 'call' } ident
             'begin' statement ';' { statment ';' } 'end'
             'if' condition 'then' statement
             / * 'while' condition 'do' statement * /
 condition = 'odd' statment | expression ('='|'#'|'<'|'<='|'>'|'>=') expression
 expression = ['+'|'-'] term {'+'|'-' term}
 term = factor {'*'|'/' factor}
 factor = ident | number | '(' expression ')'
 
 􀈐-language.c */
