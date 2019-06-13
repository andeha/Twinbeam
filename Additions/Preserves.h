/*  Preserves.h | 🍓 — Reading vectors, trees and maps. */
 
/* ␜ separates entries in a list, 
   ␜␞ separates rows and columns in a matrix, 
   ⇥ ␜␝ in a ⁺ᵃtree
   ↹ ␜␝ in a ⁺ᵚtree
   0x20 space separates in a key-value file
 
 1⁾ Fast double space to insert FIELD SEPARATOR
 
 2⁾ The TAB key for indent, SHIFT+TAB/RETURN for GROUP SEPARATOR
 
 3⁾ Fast return for RECORD SEPARATOR
 
 Note that entries are separated with SYMBOL FOR and not the actual character.
 
 */
 
enum PreservationError { };
 
typedef Utf8Interval SourceLocation;
 
/**
 
 Parse a list consisting of strings, 𝘦․𝘨 from a memory region 
 previously preserved on file.
 
  /tmp/my very long name containing space characters/my file₁ ␜
  /tmp/myfile₂ ␜ /tmp/myfile₃
 
 Colums are separated with ␜.
 
 */
 
 int ParseTextAsList(const char *utf8text, void (^error)(SourceLocation loc,
   PreservationError error), void (^out)(Unicodes item, bool first, bool last, 
   Utf8Interval itemLocation, bool& stop));
 
/**
 
 Parse a tree consisting of strings, 𝘦․𝘨 from a memory region previously 
 preserved on file.
 
  item 1 ⇥ subItem1 ␜ subItem2 ␝ item 33␟µF
 
  item 1 ↹ sub item 1 ␜ sub item 2 ␝ item 3
 
 Subtrees are created with ↹, tree items with ␜. A sub tree is 
 closed using the ␝ character.
 
 */

 FOCAL
 int ParseTextAsTree(const char *utf8, void (^error)(SourceLocation loc,
  PreservationError error), void (^out)(Unicodes item, bool lexFirst, 
    int nestings, int section[], bool lexLast, Utf8Interval itemLocation, 
    bool& stop));
 
/**
 
 Parse a matrix consisting of strings, 𝘦․𝘨 from a memory region previously 
 preserved on file.
 
  item11␜item12␜item13␞
  item21␜item22␜item23␞
  item31␜item32␜item33␞
 
 Colums are separated with ␜ and rows with ␞.
 
 */
 
 FOCAL
 int ParseTextAsMatrix(const char *utf8, void (^error)(SourceLocation loc, 
   PreservationError error), void (^out)(Unicodes item, bool firstRow, 
   bool firstCol, __builtin_uint_t row, __builtin_uint_t col, bool 
   lastColumn, bool lastRow, Utf8Interval itemLocation, bool& stop));
 
/**
 
 Parse a text file containing a key-value store. The file format asssumes
 that lines beginning with a '#' are one-line comments, empty/white space
 filled lines are stripped, that the first token is the key, that the rest
 of the trimmed line is the value.
 
  key₁ value₁
  key₂ value₁ ␜ value₂
 
 If not at least a key can be parsed, an error is reported.
 
 Note that a key can be associated with multiple values by including ␜.
 
 Optionally, new line can be inhibited by ending a line with `\`, by starting 
  a new line with `+`, by finalizing with double new line and ending with 
  PARAGRAPH_SEPARATOR.
 
 */

 FOCAL
 int ParseTextAsKVF(const char *utf8, void (^error)(SourceLocation loc,
   PreservationError error), void (^out)(Unicodes key, int index, bool 
   first, Unicodes value, bool last, bool& stop)
 );


