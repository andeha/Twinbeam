/*  Shoebox.h - Storage and food-for-thoughts. */

#ifdef __SHOEBOX_H
#include <Additions/Artclasses.h>
#include <Additions/CachedFile.h>
#include <Additions/Nimble.hpp>

enum class Retrieveopinion { accept, rejecting, commit, quit, rollback };

typedef void (^Refinement)(Unicodes primary𝘖𝘳𝑆econd); /* todo: Connect 'temporal' and 'spatial' with fork. */

int
Retrieve(Unicodes primary𝘖𝘳𝑆econd, 
  Retrieveopinion (^zeroOrMoreEntries)(int total, Unicodes primary, 
  Inode * several, Unicodes second, Refinement &r, bool &stop));

int
Promenade(__builtin_int_t count, 
  Unicodes primaries𝘖𝘳𝑆econds[],
  bool structuralRecursive, /* ⬷ Recurring structure. */
  bool temporalRecursive, /* ⬷ Recurring alternate (creational and/or access). */
  void (^zero𝘖rManyCanonical)(Guid absolutePathOrGuidOrCylOrSquidma, 
  Unicodes *currentEdge, Tribool isFirstOnEdge, Tribool isLastOnEdge, 
  Unicodes &newEdge, bool &stop)
);

int DerivativePathWithExtension(
  Unicodes ᵚᵍpath, Unicodes ext, 
  void (^finally)(Unicodes nextpath)
); /* Also `DerivativePathWithExtension⁻¹`. */

int IsTextual(Unicodes ᵚᵍpath, double⁺ʳ *literacy); /* Possibly `IsConvexconsumable` and `IsRadioconsumable`. */
int IsIllustrative(Unicodes ᵚᵍpath, double⁺ʳ *colordepth); /* Sometimes precanned. */
int IsTransparency(Unicodes ᵚᵍpath); /* Useful on a substrate. */
int IsSubstrate(Unicodes ᵚᵍpath, bool &appearsTransparent); /* A canvas and not a transparency. */
int IsFeebased(Unicodes ᵚᵍpath, bool &active); /* A․𝘬․a `IsSubscriptionbased`. */
int Abridged(Unicode ᵚᵍpath, bool &yes);

#endif /* Unable to ^S, see also `Reconcile` and `Cattle`. */

