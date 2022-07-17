/*  geolog-orient.h | ellipsoid alternatively spherical. */

enum { earthcompass₋north₋true, earthcompass₋north₋magnetic, 
 earthcompass₋south₋true, earthcompass₋east, earthcompass₋west
}; /*  magnetic field required. */

typedef struct EarthbasedSpatial {
   double degrees, arcminutes, arcseconds; /* relatively calm. */
   int earthcompass;
} Sexagesimal; /* for 𝑝𝑎𝑟𝑎𝑙𝑙𝑒𝑙𝑠 and 𝑚𝑒𝑟𝑖𝑑𝑖𝑎𝑛𝑠. */

/* #define EarthbasedSpatialTemporalHeading 360 == 0 degrees */

#define Valetta₋lat { 35, 53, 4, earthcompass₋north₋true }
#define Valetta₋lon { 14, 30, 25, earthcompass₋east }
#define Rongorongo₋lat { 27, 7, 0, earthcompass₋south }
#define Rongorongo₋lon { 109, 22, 1, earthcompass₋west }
#define ChestnutRidge₋lat { 42, 50, 42, earthcompass₋north₋true }
#define ChestnutRidge₋lon { 78, 46, 45, earthcompass₋west }

void Vincenty(
  struct EarthbasedSpatial s₁,
  struct EarthbasedSpatial s₂,
  void (^approxi)()
); /*  keep distance below 300m, today approximately 297m. */

void Pitus(); /*  increments and pressure as chisel. */

