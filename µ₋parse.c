
import Twinbeam;

typedef enum { ident, number, lparen, rparen, times, slash, plus, minus, 
 eql, neq, lss, leq, gtr, geq, callsym, beginsym, semicolon, endsym, 
 ifsym, whilesym, becomes, thensym, dosym, constsym, comma, varsym, 
 procsym, period, oddsym } Symbol;

/* clang -fmodules-ts -fimplicit-modules -fmodule-map-file=🚦.modules µ₋parse.c \
 ../Apps/Source/Releases/libTwinbeam-x86_64.a ../Apps/Additions/monolith-sequent.c */

Symbol sym; struct Unicodes text;

enum language₋mode { mode₋initial, mode₋integer, mode₋regular };

struct language₋context {
  __builtin_int_t tip₋unicode;
  enum language₋mode state;
  char32̄_t regular[2048];
  short symbols₋in₋regular;
  __builtin_int_t ongoing;
} Ctxt;

#define STATE(s) (s == ctxt->state)

void error(char msg[]) { print("⬚\n", ﹟s7(msg)); }

int next₋token(struct language₋context * ctxt)
{ __builtin_int_t i,symbols=100; char32̄_t uc,uc₊₁; int uc₋last=0;
   typedef int (^type)(char32̄_t);
   type digit = ^(char32̄_t uc) { return U'0' <= uc && uc <= U'9'; };
   type letter = ^(char32̄_t uc) { return U'a' <= uc && uc <= U'z'; };
   🧵(start,identifier,numeric₋constant,trouble,completion) {
   case identifier: sym=ident; return 0;
   case number: sym=number; return 0;
   case completion: exit(1); return -1;
   case trouble: exit(2); return -2;
   }
again:
   i=ctxt->tip₋unicode; ctxt->tip₋unicode+=1;
   if (i >= symbols && STATE(mode₋initial)) { confess(completion); }
   if (i == symbols - 1) { uc₋last=1; }
   uc = *(text.unicodes + i);
   uc₊₁ = uc₋last ? U' ' : *(text.unicodes + i + 1);
   if (STATE(mode₋initial) && uc == U'\xa') { }
   else if (STATE(mode₋initial) && uc == U' ') { }
   else if (STATE(mode₋initial) && uc == U'\t') { }
   else if (STATE(mode₋initial) && uc == U'=') { sym=eql; return 0; }
   else if (STATE(mode₋initial) && uc == U':' && uc₊₁ == U'=') { ctxt->tip₋unicode+=1; sym=becomes; return 0; }
   else if (STATE(mode₋initial) && uc == U',') { sym=comma; return 0; }
   else if (STATE(mode₋initial) && uc == U';') { sym=semicolon; return 0; }
   else if ((STATE(mode₋initial) && letter(uc)) || (STATE(mode₋regular) && (letter(uc) || digit(uc)))) {
     if (ctxt->symbols₋in₋regular == 2048) { error("identifier alternatively keyword too long"); confess(trouble); }
     ctxt->regular[ctxt->symbols₋in₋regular] = uc;
     ctxt->symbols₋in₋regular += 1;
     if (!(U'a' <= uc₊₁ && uc₊₁ <= U'z')) {
      confess(identifier); }
      ctxt->state = mode₋regular;
   }
   else if ((STATE(mode₋initial) || STATE(mode₋integer)) && digit(uc)) {
     ctxt->ongoing *= 10; ctxt->ongoing += uc - U'0';
     if (!(U'0' <= uc₊₁ && uc₊₁ <= U'9')) { confess(numeric₋constant); }
     ctxt->state = mode₋integer;
   }
   else confess(trouble);
   goto again;
}

void expression(void);

int match(Symbol s) { if (sym == s) { next₋token(&Ctxt); return 1; } return 0; }

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
   while (sym == times || sym == slash) { next₋token(&Ctxt); factor(); }
}

void expression(void)
{
   if (sym == plus || sym == minus) next₋token(&Ctxt); term();
   while (sym == plus || sym == minus) { next₋token(&Ctxt); term(); }
}

void condition(void)
{
   if (match(oddsym)) { expression(); }
   else {
     expression();
     if (sym == eql || sym == neq || sym == lss || sym == leq || sym == gtr || sym == geq) 
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
   if (match(ident)) { expect(becomes); expression(); }
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

void program(void) { next₋token(&Ctxt); block(); expect(period); }

int main()
{
   Ctxt.state=mode₋initial;
   Ctxt.tip₋unicode=0;
   text = Run(U"const abcd ;");
   program();
}

/*

 program = block '.'
 block = 'const' ident '=' number { ',' ident '=' number } ';'
         'var' ident { ',' ident } ';'
 statement = ident ':=' expression
             'call' ident
             'begin' statement ';' { statment ';' } 'end'
             'if' condition 'then' statement
             'while' condition 'do' statement
 condition = 'odd' statment | expression ('='|'#'|'<'|'<='|'>'|'>=') expression
 expression = ['+'|'-'] term {'+'|'-' term}
 term = factor {'*'|'/' factor}
 factor = ident | number | '(' expression ')'
 
 */
