#include "MixingFraction.hh"

//*******************************************************************
//********* Implementation
//*******************************************************************

// ideal gas constant
const double MixingFraction::R = 62363.7; // cm^3*torr/(K*mol)

double MixingFraction::mix_func(double Xliq)
{
  double n3 = this->Getn3();
  double n4 = this->Getn4();
  double p3 = this->Getp3(Xliq);
  double p4 = this->Getp4(Xliq);
  double nliq = this->Getnliq(Xliq);

  return (n3 - Xliq*nliq)*p4 - (n4 - (1 - Xliq)*nliq)*p3;
}

double MixingFraction::solve_Xliq(double eps, double &Xmin, double &Xmax)
{
// use Newton's method to solve mis_func(Xliq) == 0
  double Xmid = (Xmin + Xmax)/2;

  long count = 0;
  long count_limit = 1000000;
  double dfmid = 10*eps;
  do {
    if(count >= count_limit) {
      return -1.;
    }
    double dfmin = mix_func(Xmin);
    double dfmax = mix_func(Xmax);

    if(count == 0) {
    // check if a solution exists
      if(dfmin*dfmax > 0) {
        return -1;
      }
    } // end if(count == 0)

    Xmid = (Xmin + Xmax)/2.;
    dfmid = mix_func(Xmid);
    if(dfmid*dfmin > 0) Xmin = Xmid;
    else Xmax = Xmid;
    ++count;
  } while(fabs(dfmid) > eps);

  printf("count = %ld\n", count);

  return Xmid;
}

double MixingFraction::Getp3(double Xliq)
{
  if(Xliq < 0) Xliq = this->GetXliq();
  double p3sat = this->GetVaporPressureObj()->P3sat(fT);
  return Xliq*p3sat*TMath::Exp((1 - Xliq)*(1 - Xliq)*fWoverk/fT);
}

double MixingFraction::Getp4(double Xliq)
{
  if(Xliq < 0) Xliq = this->GetXliq();
  double p4sat = this->GetVaporPressureObj()->P4sat(fT);
  return (1 - Xliq)*p4sat*TMath::Exp(Xliq*Xliq*fWoverk/fT);
}

double MixingFraction::Getnliq(double Xliq)
{
  double p3 = this->Getp3(Xliq);
  double p4 = this->Getp4(Xliq);
  return ((fn3 + fn4)*R*fT/(p3 + p4) - fV)/(R*fT/(p3 + p4) - fVm);
}

double MixingFraction::GetXliq()
{
  if(fNeedsUpdate) {
    double rel_err = 0.;
    double eps = 1e-10;
    double last_n3gas = 0;
    double Xmin = 0;
    double Xmax = 1.;
    do {
printf("eps = %e, Xmin = %e, Xmax = %e\n", eps, Xmin, Xmax);
      fXliq = solve_Xliq(eps, Xmin, Xmax);
      double n3gas = fn3 - fXliq*Getnliq(fXliq);
      eps *= 0.1;
      rel_err = (n3gas - last_n3gas)/n3gas;
      last_n3gas = n3gas;
    } while(fabs(rel_err) > 0.001); // require good relative precision of n3gas
    fNeedsUpdate = kFALSE;
  }

  return fXliq;
}


MixingFraction::MixingFraction()
{
  fHeVaporPressure = new HeVaporPressure();
  fNeedsUpdate = kTRUE;
}


MixingFraction::~MixingFraction()
{
  delete fHeVaporPressure;
}


//**************************************

