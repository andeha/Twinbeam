/*  latitude-arab.c | suffix tried by non-egyptian. */

#include "twinbeam-inner.h"

int trie₋keyword(int count, char32̄_t text[], int * residue, Trie * ᐧ 🆃)
{ int i=0,word₋index; char32̄_t letter; 
   struct trie₋word * ᐧ letter₋next = 🆃;
   if (count == 0) return -3; /* searching for 'the empty word'. */
again:
   if (letter₋next == ΨΛΩ) return -2; /* recognized phrases all shorter than 'text'. */
   letter = text[i];
   if (letter == U'₋') word₋index = 77;
   else word₋index = (int)(letter - U'.');
   if (letter != U'₋' && (word₋index < 0 || word₋index > 76)) return -1;
   /* argument letter in 'text' outside trie alphabet. */
   if (i == count - 1) {
     *residue = letter₋next->residue[word₋index];
     return 0; } /* found word in 'text'. */
   letter₋next = letter₋next->downhill₋letters[word₋index];
   i+=1; goto again;
}

void merge₋to₋trie(int count, char32̄_t * keywords[], int residue[], 
 Trie * ᐧ 🆃)
{ int i=0,j,k,word₋index; char32̄_t letter,*word; 
   struct trie₋word * ᐧ letter₋process,*next₋cursor;
   for (k=0; k<78; k+=1) { 🆃->downhill₋letters[k]=ΨΛΩ; 🆃->residue[k]=-1; }
keyword:
   if (i>=count) return;
   word=keywords[i],j=0,letter₋process=🆃;
symbol:
   letter = word[j];
   if (letter == U'₋') word₋index = 77;
   else word₋index = (int)(letter - U'.');
   next₋cursor = letter₋process->downhill₋letters[word₋index];
   /* print("word-index is ⬚ and word is ⬚\n",﹟d(word₋index),﹟S(word)); */
   if (next₋cursor == ΨΛΩ) {
     next₋cursor = Heap₋alloc(sizeof(struct trie₋word));
     for (k=0; k<78; k+=1) {
       next₋cursor->downhill₋letters[k]=ΨΛΩ;
       next₋cursor->residue[k]=-1;
     }
     letter₋process->downhill₋letters[word₋index] = next₋cursor;
   }
   if (word[j+1] == '\0') goto end₋of₋word;
   letter₋process = letter₋process->downhill₋letters[word₋index];
   j+=1; goto symbol;
end₋of₋word:
   letter₋process->residue[word₋index] = residue[i];
   i+=1; goto keyword;
}

