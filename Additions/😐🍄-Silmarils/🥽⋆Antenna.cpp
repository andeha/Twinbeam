/*  Antenna.cpp | Transmitting and recieving (cylinder, rot. volume and sphere). */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <Additions/mathˢ.hpp>
#ifdef __x86_64__
#elif defined __mips__
#include <Additions/Mipsmath.hpp>
#endif

/*  Note that: 
 
 - sphere is 'scalar distance from one point'
 - cylinder is 'and point and one interval'
 - cone is 'two alt. three intervals'
 
 Also 'rot' and 'div'.

*/

namespace Convex { enum { cylinder, cone, sphere } };

enum Control { warm₋up, operational, power₋off };
typedef Control (^input)(double signal, bool& stop);
typedef int (^power)(int count, double * wattsᵒᵘᵗ);
typedef Control (^dynamic)(input, power);

int coroutine₋Field(int convex, dynamic amplifier)
{
    return 0;
}

int
main(
  int argc,
  const char * argv[]
)
{
    return 0;
}

/* See also --<🥽⋆CO₂.cpp>. */

