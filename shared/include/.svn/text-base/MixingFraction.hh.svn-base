#ifndef MixingFraction_h
#define MixingFraction_h 1

//*******************************************************************
// This class calculates the amount of liquid formed and the
// concentration of 3He in the liquid, for given container volume,
// temperature, and amounts of 4He and 3He.
// The calculation, which assumes equilibrium at the liquid-vapor
// interface, is based on the equations in appendix A.2 of
// Nacher, Cornut, and Hayden, "Compression of 3He by Resluxing 4He:
// A Model for Computing HEVAC Effects in 3He-4He Mixtures,"
// JLTP v97, n5/6 (1994), p. 417.
//*******************************************************************

#include "HeVaporPressure.hh"

class MixingFraction
{
  public:
  MixingFraction();
  virtual ~MixingFraction();

  HeVaporPressure *GetVaporPressureObj() { return fHeVaporPressure; }

  double GetT() { return fT; }
  double Getn3() { return fn3; }
  double Getn4() { return fn4; }
  double GetWoverk() { return fWoverk; }
  double GetV() { return fV; }
  double GetVm() { return fVm; }

  void SetT(double val) { fT = val; fNeedsUpdate = kTRUE; }
  void Setn3(double val) { fn3 = val; fNeedsUpdate = kTRUE; }
  void Setn4(double val) { fn4 = val; fNeedsUpdate = kTRUE; }
  void SetWoverk(double val) { fWoverk = val; fNeedsUpdate = kTRUE; }
  void SetV(double val) { fV = val; fNeedsUpdate = kTRUE; }
  void SetVm(double val) { fVm = val; fNeedsUpdate = kTRUE; }

  double GetXliq();
  double Getp3(double Xliq = -1.);
  double Getp4(double Xliq = -1.);
  double Getnliq(double Xliq = -1.);

  static const double R; // gas constant

  private:
  HeVaporPressure *fHeVaporPressure;

  double mix_func(double Xliq);
  double solve_Xliq(double eps, double &Xmin, double &Xmax);

  double fT;
  double fn3;
  double fn4;
  double fWoverk;
  double fV;
  double fVm;
  Bool_t fNeedsUpdate; // set to kTRUE when parameter is changed
  double fXliq;


};

#endif

