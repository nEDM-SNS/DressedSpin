#ifndef BlochEq_h
#define BlochEq_h 1

#include "G4Step.hh"
#include "TH2.h"

class BlochEq
{
  public:

  BlochEq();
  virtual ~BlochEq();

  void EvolveSpin(G4ThreeVector& Sf, const G4Step& step);

  void SetGyromagRatio(G4double val) { fgamma = val; }
  G4double GetGyromagRatio() { return fgamma; }

  void SetAllowedErrPerSec(G4double val) { fAllowedErrPerSec = val; }
  G4double GetAllowedErrPerSec() { return fAllowedErrPerSec; }

  // Bfield should be overridden in a derived class to specify
  // the particular magnetic field configuration of interest.
  virtual G4ThreeVector Bfield(const G4double t, const G4ThreeVector& p);

  // optional Efield to look at vxE effects
  virtual G4ThreeVector Efield(const G4double t, const G4ThreeVector& p);

  protected:

  G4int QualityControlledRKStep(G4ThreeVector &S, G4ThreeVector &Serr, const G4double t0,
                     const G4ThreeVector &p0, const G4ThreeVector &vel, const G4double h);
  void CashKarpRKStep(G4ThreeVector &S, G4ThreeVector &Serr, const G4double t0,
                     const G4ThreeVector &p0, const G4ThreeVector &vel, const G4double h);
  G4ThreeVector dSdt(const G4ThreeVector &S, const G4double t, const G4ThreeVector &p,
                     const G4ThreeVector &vel);

  G4double fgamma; // gyromagnetic ratio
  G4double fAllowedErrPerSec; // max allowed step error (parts per 1, per sec)
  G4double fRKh_next; // suggested next Runge-Kutta step size (in time)
  G4double fRKh_last; // most recent successful Runge-Kutta step size (in time)

  TH1* hBlochEqIntervalSize;
  TH1* hBlochEqStepSize;
  TH1* hBlochEqSxerr;
  TH1* hBlochEqSyerr;
  TH1* hBlochEqSzerr;

};




#endif

