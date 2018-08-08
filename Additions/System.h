//
//  System.h
//  as sometimes cognized inside 𝐵𝐿𝑈𝐸 𝑈𝑁𝐼𝐶𝑂𝑅𝑁 𝑂𝐹 𝑆𝑇𝐸𝐸𝐿.
//

#ifndef __SYSTEM_H
#define __SYSTEM_H

namespace Naturals {
    constexpr auto π = 3.1415926535897932384626433832795028841971693993751058209749;
    constexpr auto e = 2.7182818284590452353602874713526624977572470936999595749669;
    constexpr auto φ = 1.6180339887498948482045868343656381177203091798057628621354;
}

#pragma mark Rectangular Coordinate Systems

#include <Twinbeam.h> // For partial order, convenntion and hypothesis.

struct Cartesian3D { typedef double type; typedef type (^Hilbert)(Chronology::Instant t); Hilbert x, y, z; };

struct Rasterized2D { typedef __builtin_int_t type; type x, y; };

struct Cartesian2D {
    
    typedef double type; type x, y;
    
    Cartesian2D(double x, double y) : x(x), y(y) { }
    
    Cartesian2D(const Cartesian2D &p) : x(p.x), y(p.y) { }
    
};

#pragma mark Non-rectangular Coordinate Systems

typedef struct Polar { typedef double type; type r, 𝜑; } Polar;

typedef struct Spherical { typedef double type; type r, 𝛳, 𝜑; } Spherical;

typedef struct Cylindrical { typedef double type; type h, 𝜑; } Cylindrical;

enum Projection { Equirectangular, Cassini, Mercator };

typedef struct EarthbasedSpatial {
    double degrees, arcminutes, arcseconds;
} EarthbasedSpatial;

typedef EarthbasedSpatial DefaultSpatialLocation;

/**  Angles continue in a clockwise direction, rather than counterclockwise. */

typedef struct Eulerangles { typedef double type; typedef type (^Hilbert)(Chronology::Instant t); Hilbert 𝛳, 𝛹, 𝛷; } EulerAngles;

// #define EarthBasedSpatialTemporalHeading 360 == 0 degrees

namespace Naturals {
    constexpr auto degreesPerRadian = 57.296;
    constexpr auto π² = 9.86960440108935861883449099987615113531369940724079062641334; // 😐: ≅ 10
    constexpr auto π²div6 = 1.6449340668482264364724151666460251892189499012067984377; // 😐: ≅ ∑ 1/k², k ∈ [1 ⃨∞)
    // constexpr auto √5 = 2.23606797749978969640917366873127623544061835961152572427089; // 🕛: 𝜖 = 10³ @w N[Sqrt[5], 70]
    // constexpr auto πᵉ = 22.45915771836104547342715220454373502758931513399669224920;
    // constexpr auto φ² = 2.618033988749894848204586834365638117720309179805762862135; 😐: ≅ φ¹ + φ⁰
}

#pragma mark - Directions

typedef __builtin_uint_t Positano; enum : Positano { // Movements on an approx. spherical surface while responding to 𝑜𝑛𝑒 gravitational field.
    PositanoUpLeftwards     = 0b00000001,
    PositanoLeftToRight     = 0b00000010,
    PositanoDownLeftwards   = 0b00000100,
    PositanoRightToLeft     = 0b00001000,
    PositanoDownRighttwards = 0b00010000,
    PositanoTopToBottom     = 0b00100000,
    PositanoUpRighttwards   = 0b01000000,
    PositanoBottomToTop     = 0b10000000 };

typedef __builtin_uint_t Turtle; enum : Turtle {
    TurtleLeft        = 0b00000001,
    TurtleRight       = 0b00000010,
    TurtleForward     = 0b00000011,
    TurtleReverse     = 0b00000100,
    TurtleUp          = 0b00000101,
    TurtleDown        = 0b00000110,
    TurtleAccelerate  = 0b00001000,
    TurtleDeccelerate = 0b00010000 };

typedef __builtin_uint_t Strider; enum : Strider { // ☜😐: 🔅
    StriderPort      = 0b00000001,
    StriderStarboard = 0b00000010,
    StriderForward   = 0b00000101,
    StriderAdrift    = 0b00000110,
    StriderAnchored  = 0b00000100 };

typedef __builtin_uint_t RelationalStrider; enum : RelationalStrider {
    RelationalStriderAbaft         = 0b00000001,
    RelationalStriderLeeward       = 0b00000010,
    RelationalStriderAboard        = 0b00000011,
    RelationalStriderAthwartships  = 0b00000100,
    RelationalStriderBelowdecks    = 0b00000101,
    RelationalStriderAmidships     = 0b00000110,
    RelationalStriderOutboard      = 0b00000111,
    RelationalStriderAlee          = 0b000001000 };

typedef __builtin_uint_t Manhattan; enum : Manhattan {
    ManhattanLeftToRight = 0b0001,
    ManhattanRightToLeft = 0b0010,
    ManhattanTopToBottom = 0b0100,
    ManhattanBottomToTop = 0b1000 };

template <typename T> struct LeftclosedInterval { T closedBeginning; T openEnd; };
template <typename T> struct ClosedInterval { T closedBeginning; T closedEnd; };

#include <Additions/Additions.h>

#endif
