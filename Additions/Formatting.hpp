//
//  Formatting.hpp
//  Additions
//

#ifndef __FORMATTING_HPP
#define __FORMATTING_HPP

/**  Streaming a tree to/in a terminal. */

template <typename U8OS>
struct TreePresenter {
  void nudge(short delta) { tabCount += delta; }
  void write(U8OS &os) { short i = tabCount; while (i) { os.write("\t"); i--; }}
  short unsigned tabCount = 0;
};

/**  Streaming a matrix to the terminal with a left-aligned first columns. */

template <typename T>
inline
void
PresentTable(
  Utf8Terminal &os,
  const Vector<T>& array,
  void (^header)(Utf8Terminal &os),
  bool (^compare)(const T&, const T&),
  __builtin_int_t (^aggregate)(const T&),
  void (^printRow)(Utf8Terminal&, const T&, __builtin_int_t),
  void (^footer)(Utf8Terminal &os)
)
{
    header(os);
    __builtin_int_t maxWidth = MaxWidth(array, compare, aggregate);
    array.elements(^(SemanticPointer<T *> elem, bool &) { printRow(os, *elem.pointer, maxWidth); });
    footer(os);
}

/**  Return the maximum aggregative in a sequence. */

template <typename T, typename C, typename A>
inline
__builtin_int_t
MaxWidth(
  const Vector<T>& array,
  C cmp, A aggr
)
{
    __builtin_int_t count = array.count();
    if (count == 0) return 0;
    else if (count == 1) return aggr(array[0]);
    else {
        __block __builtin_int_t largestIdx = 0;
        array.forall(^(SemanticPointer<T *> elem, bool first, bool last,
          __builtin_int_t idx, bool& stop) {
            T& l = array.at(largestIdx), &r = array.at(idx);
            if (cmp(l, r)) largestIdx = idx;
        });
        return aggr(array[largestIdx]);
    }
}

#endif
