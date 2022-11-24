
import Twinbeam;

typedef enum Symbol { ident, number, lparen, rparen, times, divide, plus, minus, 
 eql, neq, lss, leq, gtr, geq, callsym, beginsym, semicolon, endsym, 
 ifsym, whilesym, afterward, thensym, dosym, constsym, comma, varsym, 
 procsym, period, oddsym, end₋of₋transmission₋and₋file } Symbol;

/* clang -g -fmodules-ts -fimplicit-modules -fmodule-map-file=🚦.modules µ-parse.c \
 ../Apps/Source/Releases/libTwinbeam-x86_64.a ../Apps/Additions/monolith-sequent.c */

Symbol symbol; struct Unicodes text;

enum language₋mode { mode₋initial, mode₋integer, mode₋regular };

struct language₋context {
  __builtin_int_t tip₋unicode;
  enum language₋mode state;
  char32̄_t regular[2048];
  short syms₋in₋regular;
  __builtin_int_t ongoing,render₋newline₋count;
  Trie keys;
} Ctxt;

#define STATE(s) (s == ctxt->state)
#define TRACE₋TOKENS

void error(char msg[]) { print("⬚\n", ﹟s7(msg)); }

int next₋token₋inner(struct language₋context * ctxt)
{ __builtin_int_t i,symbols=text.tetras; char32̄_t uc,uc₊₁; int uc₋last=0,sym;
   typedef int (^type)(char32̄_t);
   type digit = ^(char32̄_t uc) { return U'0' <= uc && uc <= U'9'; };
   type letter = ^(char32̄_t uc) { return U'a' <= uc && uc <= U'z'; };
   🧵(identifier,numeric₋constant,keyword,trouble,completion) {
   case identifier: symbol=ident; ctxt->syms₋in₋regular=0; ctxt->state=mode₋initial; return 0;
   case numeric₋constant: symbol=number; Ctxt.ongoing=0; ctxt->state=mode₋initial; return 0;
   case keyword: symbol=sym; ctxt->syms₋in₋regular=0; ctxt->state=mode₋initial; return 0;
   case completion: symbol=end₋of₋transmission₋and₋file; return 0;
   case trouble: return -1;
   }
again:
   i=ctxt->tip₋unicode; ctxt->tip₋unicode+=1;
   if (i >= symbols && STATE(mode₋initial)) { confess(completion); }
   if (i == symbols - 1) { uc₋last=1; }
   uc = *(text.unicodes + i);
   uc₊₁ = uc₋last ? U' ' : *(text.unicodes + i + 1);
   if (STATE(mode₋initial) && uc == U'\xa') { ctxt->render₋newline₋count += 1; }
   else if (STATE(mode₋initial) && uc == U'\xd') { }
   else if (STATE(mode₋initial) && uc == U' ') { }
   else if (STATE(mode₋initial) && uc == U'\t') { }
   else if (STATE(mode₋initial) && uc == U'(') { symbol=lparen; return 0; }
   else if (STATE(mode₋initial) && uc == U')') { symbol=rparen; return 0; }
   else if (STATE(mode₋initial) && uc == U'*') { symbol=times; return 0; }
   else if (STATE(mode₋initial) && uc == U'/') { symbol=divide; return 0; }
   else if (STATE(mode₋initial) && uc == U'+') { symbol=plus; return 0; }
   else if (STATE(mode₋initial) && uc == U'-') { symbol=minus; return 0; }
   else if (STATE(mode₋initial) && uc == U'=') { symbol=eql; return 0; }
   else if (STATE(mode₋initial) && uc == U'<' && uc₊₁ == U'=') { ctxt->tip₋unicode+=1; symbol=leq; return 0; }
   else if (STATE(mode₋initial) && uc == U'<') { symbol=lss; return 0; }
   else if (STATE(mode₋initial) && uc == U'>' && uc₊₁ == U'=') { ctxt->tip₋unicode+=1; symbol=geq; return 0; }
   else if (STATE(mode₋initial) && uc == U'>') { symbol=gtr; return 0; }
   else if (STATE(mode₋initial) && uc == U';') { symbol=semicolon; return 0; }
   else if (STATE(mode₋initial) && uc == U':' && uc₊₁ == U'=') { ctxt->tip₋unicode+=1; symbol=afterward; return 0; }
   else if (STATE(mode₋initial) && uc == U',') { symbol=comma; return 0; }
   else if (STATE(mode₋initial) && uc == U'.') { symbol=period; print("period\n"); return 0; }
   else if ((STATE(mode₋initial) && letter(uc)) || (STATE(mode₋regular) && (letter(uc) || digit(uc)))) {
     if (ctxt->syms₋in₋regular == 2048) { error("identifier alternatively keyword too long"); confess(trouble); }
     ctxt->regular[ctxt->syms₋in₋regular] = uc;
     ctxt->syms₋in₋regular += 1;
     ctxt->state = mode₋regular;
     if (!(U'a' <= uc₊₁ && uc₊₁ <= U'z')) {
       if (trie₋keyword(ctxt->syms₋in₋regular,ctxt->regular,&sym,&(Ctxt.keys))) { confess(identifier); }
       confess(keyword); }
   }
   else if ((STATE(mode₋initial) || STATE(mode₋integer)) && digit(uc)) {
     ctxt->ongoing *= 10; ctxt->ongoing += uc - U'0';
     ctxt->state = mode₋integer;
     if (!(U'0' <= uc₊₁ && uc₊₁ <= U'9')) { confess(numeric₋constant); }
   }
   else { 
    confess(trouble);
   }
   goto again;
}

void next₋token(struct language₋context * ctxt)
{
  int y = next₋token₋inner(ctxt);
  if (y != 0) { error("scanner error: trouble."); exit(2); }
#if defined TRACE₋TOKENS
  switch (symbol) {
  case ident: print("identifier\n"); break;
  case number: print("numeric₋constant\n"); break;
  case beginsym: print("'begin'\n"); break;
  case endsym: print("'end'"); break;
  case eql: print("'='\n"); break;
  case afterward: print("':='\n"); break;
  case semicolon: print("';'\n"); break;
  case end₋of₋transmission₋and₋file: print("completion\n"); break;
  }
#endif
}

void expression(void);

int match(Symbol s) { if (symbol == s) { next₋token(&Ctxt); return 1; } return 0; }

int expect(Symbol s) { if (match(s)) return 1; error("expect: unexpected symbol"); return 0; }

void factor(void)
{
   if (match(ident)) { ; }
   else if (match(number)) { ; }
   else if (match(lparen)) { expression(); expect(rparen); }
   else { error("factor: syntax error"); next₋token(&Ctxt); }
}

void term(void)
{
   factor();
   while (symbol == times || symbol == divide) { next₋token(&Ctxt); factor(); }
}

void expression(void)
{
   if (symbol == plus || symbol == minus) next₋token(&Ctxt); term();
   while (symbol == plus || symbol == minus) { next₋token(&Ctxt); term(); }
}

void condition(void)
{
   if (match(oddsym)) { expression(); }
   else {
     expression();
     if (symbol == eql || symbol == neq || symbol == lss || symbol == leq || symbol == gtr || symbol == geq) 
     {
       next₋token(&Ctxt); expression();
     } else {
       error("condition: invalid operator"); 
       next₋token(&Ctxt);
     }
   }
}

void statement(void)
{
   if (match(ident)) { expect(afterward); expression(); }
   else if (match(callsym)) { expect(ident); }
   else if (match(beginsym)) { do { statement(); } while (match(semicolon)); expect(endsym); }
   else if (match(ifsym)) { condition(); expect(thensym); statement(); }
   else if (match(whilesym)) { condition(); expect(dosym); statement(); }
   else { error("statement: syntax error"); next₋token(&Ctxt); }
}

void block(void)
{
  if (match(constsym)) {
    do { expect(ident); expect(eql); expect(number); 
    } while (match(comma)); expect(semicolon);
  }
  if (match(varsym)) {
    do { expect(ident); } while (match(comma));
    expect(semicolon);
  }
  while (match(procsym)) { expect(ident); expect(semicolon); block(); expect(semicolon); }
  statement();
}

void program(void) { next₋token(&Ctxt); block(); expect(end₋of₋transmission₋and₋file); }

int main()
{
   char32̄_t * kvlist[] = { U"const",U"var",U"call",U"begin",U"end",U"if",U"then",U"while",U"do",U"odd" };
   int symlist[] = { constsym,varsym,callsym,beginsym,endsym,ifsym,thensym,whilesym,dosym,oddsym };
   merge₋to₋trie(10,kvlist,symlist,&(Ctxt.keys));
   Ctxt.state=mode₋initial;
   Ctxt.tip₋unicode=0;
   Ctxt.syms₋in₋regular=0;
   Ctxt.ongoing=0;
   Ctxt.render₋newline₋count=0;
   text = Run(U"const abcd=321,dcba=123;\nvar cdeg,gec,cgb;");
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
             'while' condition 'do' statement
 condition = 'odd' statment | expression ('='|'#'|'<'|'<='|'>'|'>=') expression
 expression = ['+'|'-'] term {'+'|'-' term}
 term = factor {'*'|'/' factor}
 factor = ident | number | '(' expression ')'
 
 􀈐-language.c */
