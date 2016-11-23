#include "BlochEq.hh"

#include "periodicStepping.hh"

BlochEq::BlochEq() : fgamma(-20393.963)
{

  // maximum allowed accumulated error per second in each
  // component of the spin vector:
  // set to 10^-3 over of the entire simulation period
  fAllowedErrPerSec = 1.0e-3/periodicStepping::kMaxSimulationSeconds;


  fRKh_next = 1.0e-6*s; // initial Runge-Kutta step size will be adapted to be
                        // consistent with fAllowedErrPerSec
  fRKh_last = 0.0; // last successful Runge-Kutta step size

  hBlochEqIntervalSize = new TH1D("hBlochEqIntervalSize", "Runge-Kutta Interval Size",
      1000, 0., 10.);
  hBlochEqIntervalSize->GetXaxis()->SetTitle("#Deltat (#mus)");

  hBlochEqStepSize = new TH1D("hBlochEqStepSize", "Runge-Kutta Step Size",
      1000, 0., 10.);
  hBlochEqStepSize->GetXaxis()->SetTitle("h (#mus)");

  hBlochEqSxerr = new TH1D("hBlochEqSxerr","estimate of max accumulated error in S_{x}",
      1000, 0., periodicStepping::kMaxSimulationSeconds);
  hBlochEqSxerr->GetXaxis()->SetTitle("elapsed time (s)");
  hBlochEqSxerr->GetYaxis()->SetTitle("max accum. err per time bin");
  hBlochEqSyerr = new TH1D("hBlochEqSyerr","estimate of max accumulated error in S_{y}",
      1000, 0., periodicStepping::kMaxSimulationSeconds);
  hBlochEqSyerr->GetXaxis()->SetTitle("elapsed time (s)");
  hBlochEqSyerr->GetYaxis()->SetTitle("max accum. err per time bin");
  hBlochEqSzerr = new TH1D("hBlochEqSzerr","estimate of max accumulated error in S_{z}",
      1000, 0., periodicStepping::kMaxSimulationSeconds);
  hBlochEqSzerr->GetXaxis()->SetTitle("elapsed time (s)");
  hBlochEqSzerr->GetYaxis()->SetTitle("max accum. err per time bin");

  hBxDelt = new TH1D("hBxDelt","B_{x}/gauss weighted by #Deltat",20000,0.998*10e-3, 1.002*10e-3);
  hByDelt = new TH1D("hByDelt","B_{y}/gauss weighted by #Deltat",20000,-0.002*10e-3, 0.002*10e-3);
  hBzDelt = new TH1D("hBzDelt","B_{z}/gauss weighted by #Deltat",20000,-0.002*10e-3, 0.002*10e-3);

}

BlochEq::~BlochEq()
{
}

void BlochEq::EvolveSpin(G4ThreeVector& Sf, const G4Step& step)
{
  G4double t          = step.GetPreStepPoint()->GetGlobalTime();
  G4double tf         = step.GetPostStepPoint()->GetGlobalTime();
  G4ThreeVector p     = step.GetPreStepPoint()->GetPosition();
  G4double deltat      = step.GetDeltaTime();
  G4ThreeVector deltal = step.GetDeltaPosition();

  hBlochEqIntervalSize->Fill(deltat/s*1e6);

  // make sure step is nonzero in time
  if(deltat == 0) return;
  G4ThreeVector vel = deltal/deltat;

  G4ThreeVector S = Sf; // holder for the result of the step
  G4ThreeVector Serr; // holder for the estimate of the RK step error

  int istep = 0;
  while(true) {
    G4double h = tf - t; // time interval to end of tracking step
    if(h > fRKh_next) h = fRKh_next; // possibly reduce h to recommended next step
    ++istep;
    G4int nfailed = QualityControlledRKStep(S, Serr, t, p, vel, h);

#if 0
if(nfailed > 0) {
G4cout << "t = " << t/s << " s, istep = " << istep << ", nfailed = " << nfailed << G4endl;
}
#endif

    G4ThreeVector B = Bfield(t, p);
    hBxDelt->Fill(B.x()/gauss, fRKh_last/s);
    hByDelt->Fill(B.y()/gauss, fRKh_last/s);
    hBzDelt->Fill(B.z()/gauss, fRKh_last/s);

    t += fRKh_last; // increment time to end of successful step
    hBlochEqSxerr->Fill(t/s, fabs(Serr.x())); // diagnostic histograms (accumulated
    hBlochEqSyerr->Fill(t/s, fabs(Serr.y())); // error per time bin)
    hBlochEqSzerr->Fill(t/s, fabs(Serr.z()));
    hBlochEqStepSize->Fill(fRKh_last/s*1e6); 

    if(t >= tf) break; // done with full tracking step,
    if(nfailed < 0) {
      G4cout << "BlochEq: Underflow error (step size too small)" << G4endl;
    }
    p = p + fRKh_last*vel; // update position to end of last RK step
  }
  Sf = S;

  return;
}


G4int BlochEq::QualityControlledRKStep(G4ThreeVector &S, G4ThreeVector &Serr,
 const G4double t0, const G4ThreeVector &p0, const G4ThreeVector &vel, G4double h)
{
// based on the Numerical Recipes routine rkqs(...).
// This version returns the number of failed steps.
  const G4double kPgrow = -0.2;
  const G4double kPshrink = -0.25;
  const G4double kSafety = 0.9;
  const G4double kErrCon = 1.89e-4;

  G4ThreeVector S0 = S;
  G4int nfailed = 0;
  G4double errmax = 0;
  while(true) {
    CashKarpRKStep(S, Serr, t0, p0, vel, h);
    errmax = sqrt(Serr * Serr)/(h/s)/fAllowedErrPerSec; // estimate of the step error
    if(errmax <= 1.0) { // the step was successful
      fRKh_last = h;
      break;
    }

    ++nfailed;
    S = S0; // reset to value before the failed step
    G4double htemp = kSafety*h*pow(errmax, kPshrink);
    if(htemp < 0.1*h) h = 0.1*h; // don't reduce h by more than factor of 10
    else h = htemp;

    // check for underflow condition (h smaller than machine precision of t0)
    G4double ttemp = t0 + h;
    if(ttemp == t0) {
      G4cerr << "stepsize underflow in TBlochEq::QualityConrolledRKStep(...)" << G4endl;
      return -1;
    }
  } // end while(true)

  if(errmax > kErrCon) fRKh_next = kSafety*h*pow(errmax, kPgrow);
  else fRKh_next = 5.0*h; // so that h is not increased >5-fold at a time

  return nfailed;
}

G4ThreeVector BlochEq::Bfield(const G4double t, const G4ThreeVector &p)
{
  return G4ThreeVector(0,0,0);
}

G4ThreeVector BlochEq::Efield(const G4double t, const G4ThreeVector &p)
{
  return G4ThreeVector(0,0,0);
}

G4ThreeVector BlochEq::dSdt(const G4ThreeVector &S,
 const G4double t, const G4ThreeVector &p, const G4ThreeVector &vel)
{
  return fgamma/s*S.cross(Bfield(t,p)/gauss + vel.cross(Efield(t,p))/c_light/c_light/gauss);
}

void BlochEq::CashKarpRKStep(G4ThreeVector &S, G4ThreeVector &Serr,
 const G4double t0, const G4ThreeVector &p0, const G4ThreeVector &vel, const G4double h)
{
// Numerical Recipes chapter 16.2, function rkck(...)
// The advantage of this method over the classical 4th order Runge-Kutta method is
// the estimate of the step error.

  static G4double a2=0.2,a3=0.3,a4=0.6,a5=1.0,a6=0.875,b21=0.2,
     b31=3.0/40.0,b32=9.0/40.0,b41=0.3,b42= -0.9,b43=1.2,
     b51 = -11.0/54.0, b52=2.5,b53 = -70.0/27.0,b54=35.0/27.0,
     b61=1631.0/55296.0,b62=175.0/512.0,b63=575.0/13824.0,
     b64=44275.0/110592.0,b65=253.0/4096.0,c1=37.0/378.0,
     c3=250.0/621.0,c4=125.0/594.0,c6=512.0/1771.0,
     dc5 = -277.00/14336.0;
  static G4double dc1=c1-2825.0/27648.0,dc3=c3-18575.0/48384.0,
     dc4=c4-13525.0/55296.0,dc6=c6-0.25;

  G4ThreeVector S0 = S;


  // first step based on derivatives evaluated at (t0,p0)
  // t0, p0
  G4ThreeVector ak1 = dSdt(S0,t0,p0,vel);
  G4ThreeVector S1 = S0 + b21*h*ak1;

  G4double t1 = t0 + a2*h;
  G4ThreeVector p1 = p0 + a2*h*vel;
  G4ThreeVector ak2 = dSdt(S1,t1,p1,vel);
  G4ThreeVector S2 = S0 + h*(b31*ak1 + b32*ak2);

  G4double t2 = t0 + a3*h;
  G4ThreeVector p2 = p0 + a3*h*vel;
  G4ThreeVector ak3 = dSdt(S2,t2,p2,vel);
  G4ThreeVector S3 = S0 + h*(b41*ak1 + b42*ak2 + b43*ak3);

  G4double t3 = t0 + a4*h;
  G4ThreeVector p3 = p0 + a4*h*vel;
  G4ThreeVector ak4 = dSdt(S3,t3,p3,vel);
  G4ThreeVector S4 = S0 + h*(b51*ak1 + b52*ak2 + b53*ak3 + b54*ak4);

  G4double t4 = t0 + a5*h;
  G4ThreeVector p4 = p0 + a5*h*vel;
  G4ThreeVector ak5 = dSdt(S4,t4,p4,vel);
  G4ThreeVector S5 = S0 + h*(b61*ak1 + b62*ak2 + b63*ak3 + b64*ak4 + b65*ak5);

  G4double t5 = t0 + a6*h;
  G4ThreeVector p5 = p0 + a6*h*vel;
  G4ThreeVector ak6 = dSdt(S5,t5,p5,vel);

  // "Accumulate increments with proper weights."
  S = S0 + h*(c1*ak1 + c3*ak3 + c4*ak4 + c6*ak6);

  // "Estimate error as difference between fourth and fifth order methods.
  Serr = h*(dc1*ak1 + dc3*ak3 + dc4*ak4 + dc5*ak5 + dc6*ak6);

}





