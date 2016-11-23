#include "HeVaporPressure.hh"

int HeVaporPressure::g_objID = 0;

double func_3He_curve(double x[], double par[])
{
  double T = x[0];
  double *a = par + 1; // a[-1] ... a[5]  <--->  par[0] ... par[6]
//  double an1 = par[0];
//  double a0 = par[1];
//  double a1 = par[2];
//  double a2 = par[3];

  double lnP = 0;
  for(int i = -1; i <= 4; i++) {
    lnP += a[i]*TMath::Power(T, i);
  }
  lnP += a[5]*TMath::Log(T);
  return TMath::Exp(lnP)/133.3224; // (converted from Pa to torr)
}

double func_4HeII_curve(double x[], double par[])
{
  double T = x[0];
  double *b = par + 1; // b[-1] ... b[6]  <--->  par[0] ... par[7]

  double lnP = 0;
  for(int i = -1; i <= 6; i++) {
    lnP += b[i]*TMath::Power(T, i);
  }
  return TMath::Exp(lnP)/133.3224; // (converted from Pa to torr)
}

double func_4HeI_curve(double x[], double par[])
{
  double T = x[0];
  double t = T/5.1953;
  double *c = par + 1; // c[-1] ... c[9]  <--->  par[0] ... par[10]

  double lnP = 0;
  for(int i = -1; i <= 8; i++) {
    lnP += c[i]*TMath::Power(t, i);
  }
  lnP += c[9]*TMath::Power((1 - t), 1.9);
  return TMath::Exp(lnP)/133.3224; // (converted from Pa to torr)
}


HeVaporPressure::HeVaporPressure()
{
  ++g_objID;
  char str[50];
  sprintf(str, "func_PvsT4_I_%d", g_objID);
  fFunc_PvsT4_I = new TF1(str, func_4HeI_curve, 2.1768, 4.2, 11);
  fFunc_PvsT4_I->SetParameter(0, -30.93285);     // c_-1
  fFunc_PvsT4_I->SetParameter(1, 392.47361);     // c_0
  fFunc_PvsT4_I->SetParameter(2, -2328.04587);   // c_1
  fFunc_PvsT4_I->SetParameter(3, 8111.30347);    // c_2
  fFunc_PvsT4_I->SetParameter(4, -17809.80901);  // c_3
  fFunc_PvsT4_I->SetParameter(5, 25766.52747);   // c_4
  fFunc_PvsT4_I->SetParameter(6, -24601.4);      // c_5
  fFunc_PvsT4_I->SetParameter(7, 14944.65142);   // c_6
  fFunc_PvsT4_I->SetParameter(8, -5240.36518);   // c_7
  fFunc_PvsT4_I->SetParameter(9, 807.93168);     // c_8
  fFunc_PvsT4_I->SetParameter(10, 14.53333);     // c_9

  sprintf(str, "func_PvsT4_II_%d", g_objID);
  fFunc_PvsT4_II = new TF1(str, func_4HeII_curve, 0.5, 2.1768, 8);
  fFunc_PvsT4_II->SetParameter(0, -7.41816);   // b_-1
  fFunc_PvsT4_II->SetParameter(1, 5.42128);    // b_0
  fFunc_PvsT4_II->SetParameter(2, 9.903203);   // b_1
  fFunc_PvsT4_II->SetParameter(3, -9.617095);  // b_2
  fFunc_PvsT4_II->SetParameter(4, 6.804602);   // b_3
  fFunc_PvsT4_II->SetParameter(5, -3.0154606); // b_4
  fFunc_PvsT4_II->SetParameter(6, 0.7461357);  // b_5
  fFunc_PvsT4_II->SetParameter(7, -0.0791791); // b_6

  sprintf(str, "func_PvsT3_%d", g_objID);
  fFunc_PvsT3 = new TF1(str, func_3He_curve, 0.2, 4.2, 7);
  fFunc_PvsT3->SetParameter(0, -2.50943);   // a_-1
  fFunc_PvsT3->SetParameter(1, 9.70876);    // a_0
  fFunc_PvsT3->SetParameter(2, -0.304433);  // a_1
  fFunc_PvsT3->SetParameter(3, 0.210429);   // a_2
  fFunc_PvsT3->SetParameter(4, -0.0545145); // a_3
  fFunc_PvsT3->SetParameter(5, 0.0056067);  // a_4
  fFunc_PvsT3->SetParameter(6, 2.25484);    // a_5
}

HeVaporPressure::~HeVaporPressure()
{
}

float HeVaporPressure::P4sat(float T)
{
  if(T < 2.1768) {
    return fFunc_PvsT4_II->Eval(T);
  } else {
    return fFunc_PvsT4_I->Eval(T);
  }
}

float HeVaporPressure::P3sat(float T)
{
  return fFunc_PvsT3->Eval(T);
}

