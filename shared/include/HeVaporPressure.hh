#ifndef HeVaporPressure_h
#define HeVaporPressure_h 1

#include "TF1.h"
#include <stdio.h>
#include "TMath.h"

// implements parameterizations in
// Rusby, "New Vapor Pressure Equations for 4He and 3He,"
//    J. Low Temp. Phys., v 50 (1985), p 203

class HeVaporPressure
{
  public:
  HeVaporPressure();
  ~HeVaporPressure();


  TF1 *GetFunc_PvsT4_I() { return fFunc_PvsT4_I; }
  TF1 *GetFunc_PvsT4_II() { return fFunc_PvsT4_II; }
  TF1 *GetFunc_PvsT3() { return fFunc_PvsT3; }

  float P3sat(float T);
  float P4sat(float T);

  private:
  TF1 *fFunc_PvsT4_I;
  TF1 *fFunc_PvsT4_II;
  TF1 *fFunc_PvsT3;

  static int g_objID; // used to assign unique names for each instantiation
};

#endif

