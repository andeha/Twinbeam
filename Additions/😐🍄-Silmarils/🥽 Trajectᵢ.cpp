/*  𝙏𝙧𝙖𝙟𝙚𝙘𝙩ᵢ.cpp | Ballistic and cannon in a constant gravitational force. (DO-NOT-COPY) */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <Additions/mathˢ.h>

/* Compile with xcrun clang @ccargs_macᵧ² -o Trajectᵢ '🥽 Trajectᵢ.cpp'    \
     ../../Source/llvmʳᵗ³.cpp */

namespace Naturals { auto 🥈 π = 3.141592653589793238462643383279502887169; }
auto ﹟F₂ = ^(double x) { return ﹟F(x, NumberFormat::CForm); };

MACRO double ˚2ᴿ(double 𝑑𝑒𝑔) { return (Naturals::π/180)*𝑑𝑒𝑔; }
MACRO double ᴿ2˚(double 𝑟𝑎𝑑) { return (180/Naturals::π)*𝑟𝑎𝑑; }

int
main(
  int argc,
  const char * argv[]
)
{  double pos₀[2], pos[2], vel₀[2], vel[2], acc[2], 𝛳₀, v̅₀, t, impactTime;
    int impact=0;
    
    /* Gravitational acceleration ℊ is constant ≈9.81 m/s² towards centre of earth, 
      therefore v𝑦(t) = ∫ ℊ dt = ℊ*t + v₀ and position p𝑦(t) = ℊ*t²/2 + v₀*t + pos₀. */
    
    /* Initialize ½-d and 2ᵈ values: */
    t=0.0; pos={ 0.0, 0.0 }; vel={ 0.0, 0.0 };
    acc={ 0.0, -9.81 };
    𝛳₀=˚2ᴿ(ᴿ2˚(Naturals::π/6.0)) /* rad */; v̅₀=50.0 /* m/s */;
    
    /* (Initial) location and velocity at time t = 0: */
    pos₀={ pos[0], pos[1] };
    vel₀={ cos(𝛳₀)*v̅₀, sin(𝛳₀)*v̅₀ };
    
    print("t, x, y, v𝑥, v𝑦\n"); /* Run simulation ⤐ */
    while (!impact) {
        vel[0] = vel₀[0] + acc[0] * t;
        vel[1] = vel₀[1] + acc[1] * t;
        pos[0] = pos₀[0] + (vel₀[0] + 0.5 * acc[0] * t) * t;
        pos[1] = pos₀[1] + (vel₀[1] + 0.5 * acc[1] * t) * t;
        print("⬚, ⬚, ⬚, ⬚, ⬚\n", ﹟F₂(t), ﹟F₂(pos[0]), ﹟F₂(pos[1]), ﹟F₂(vel[0]), ﹟F₂(vel[1]));
        if (pos[1] < 0.0) { impact = 1; /* ⬷ Shutdown simulation. */
           impactTime = (- vel₀[1] - sqrt(vel₀[1] * vel₀[1] - 2.0*pos₀[1])) / -9.81;
           pos = { impactTime*vel₀[0], 0.0 };
        }
        t += 0.01;
    }
    
    print("Impact time=⬚, 𝛥x=⬚\n", ﹟F₂(impactTime), ﹟F₂(pos[0]));
    return 0;
}

/*  The caliber 20'' Tsar Cannon at Kremlin Armory can be loaded with 61 kg gun-powder. */

