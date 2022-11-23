/*  latitude-arab.c | suffix tried by non-egyptian. */

import Twinbeam;

int trie₋keyword(int letters, char32̄_t text[], int * residue, Trie * ᐧ 🆃)
{ int i=0,word₋index,stored; struct trie₋word * ᐧ letter₋next=🆃;
   if (letters == 0) { return -1; } /* searching for no word. */
again:
   word₋index = (int)(text[i] - U'a');
   if (word₋index < 0 || word₋index > 24) { return -2; } /* letter in `text` outside trie alphabet. */
   if (i == letters - 1) {
     stored = letter₋next->residue[word₋index];
     if (stored == -1) { return -3; } /* no residue stored for `text`. */
     *residue = stored; return 0; } /* found word in `text`. */
   letter₋next = letter₋next->downhill₋letters[word₋index];
   if (letter₋next == ΨΛΩ) { return -4; } /* no installed word as long as `text`. */
   i+=1; goto again;
}

void merge₋to₋trie(int count, char32̄_t * keywords[], int residue[], Trie * ᐧ 🆃)
{ int i=0,j,modula,word₋index; char32̄_t letter,*word; struct trie₋word * ᐧ letter₋process,*next₋cursor;
   for (int i=0; i<25; i+=1) { 🆃->downhill₋letters[i]=ΨΛΩ; 🆃->residue[i]=-1; }
lower:
   if (i>=count) { return; }
   letter₋process = 🆃;
   word = keywords[i];
   modula = residue[i];
   j=0;
upper:
   letter = word[j];
   word₋index = (int)(letter - U'a');
   next₋cursor = letter₋process->downhill₋letters[word₋index];
   if (next₋cursor == ΨΛΩ) { next₋cursor = Heap₋alloc(sizeof(struct trie₋word)); 
    for (int i=0; i<25; i+=1) { next₋cursor->downhill₋letters[i]=ΨΛΩ; next₋cursor->residue[i]=-1; }
    letter₋process->downhill₋letters[word₋index] = next₋cursor;
   }
   if (word[j+1] == '\0') { goto next; }
   letter₋process = letter₋process->downhill₋letters[word₋index];
   j+=1; goto upper;
next:
   letter₋process->residue[word₋index] = modula;
   i+=1; goto lower;
}

