
import Twinbeam;

typedef enum { ident, number, lparen, rparen, times, slash, plus, minus, 
 eql, neq, lss, leq, gtr, geq, callsym, beginsym, semicolon, endsym, 
 ifsym, whilesym, becomes, thensym, dosym, constsym, comma, varsym, 
 procsym, period, oddsym, end₋of₋transmission } Symbol;

/* clang -fmodules-ts -fimplicit-modules -fmodule-map-file=🚦.modules µ₋parse.c ../Apps/Source/Releases/libTwinbeam-x86_64.a */

Symbol sym; struct Unicodes text;

enum language₋mode { mode₋initial };

struct language₋context {
  __builtin_int_t tip₋unicode;
  enum language₋mode state;
} Ctxt;

#define STATE(s) (s == ctxt->state)

int next₋token(struct language₋context * ctxt)
{ __builtin_int_t i,symbols=100;
   🧵(start,identifier,error,completion) {
   case identifier: return 0;
   case completion: return -1;
   case error: return -2;
   }
again:
   i=ctxt->tip₋unicode; ctxt->tip₋unicode+=1;
   if (i >= symbols && STATE(mode₋initial)) { confess(completion); }
   else confess(error);
   goto again;
}

void error(const char msg[]) { print(msg); }

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
   text = Run(U"const myid1=321,myid2=543;");
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
