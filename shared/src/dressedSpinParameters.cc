#include "dressedSpinParameters.hh"
#include "diffusionMaterial.hh"

dressedSpinParameters::dressedSpinParameters()
  : detector(0), gen_action(0), physics(0)
{
  hParameters = new TH1D("hParameters","Simulation Parameters",
         10, 0.5, 10.5);

  fT = 300*kelvin;
  fPressure = 1; // torr
  fD = 1370.2*cm*cm/s; // T = 300 K and P = 1 torr

  paramsMessenger = new dressedSpinMessenger(this);
}

dressedSpinParameters::~dressedSpinParameters()
{
  delete paramsMessenger;
}

G4double dressedSpinParameters::GetThermalVelocity()
{
  return gen_action->GetVelocity();
}

void dressedSpinParameters::SetTemperature(G4double temperature)
{
  fT = temperature;

  G4double alpha_vl = 1.0;
  G4double m_eff = 2.4;
  G4double E_B = 2.8*kelvin;
  G4double alpha_lv = alpha_vl/m_eff*exp(-E_B/fT);
  physics->GetDiffusionBoundaryProcess()->SetEvaporationProb(alpha_lv);
  physics->GetDiffusionBoundaryProcess()->SetCondensationProb(alpha_vl);
  G4cout << "T = " << fT/kelvin << " K, alpha_vl = " << alpha_vl
         << ", alpha_lv = " << alpha_lv << G4endl;

  changedPT(); // recalculate T- and P-dependent parameters
}

void dressedSpinParameters::SetPressure(G4double pressure)
{
  fPressure = pressure;
  changedPT(); // recalculate T- and P-dependent parameters
}

void dressedSpinParameters::changedPT()
{
//  G4double KE = 1.5*k_Boltzmann*fT; // KE of particle with rms vel. sqrt(3kT/m)
  G4double KE = 4/pi*k_Boltzmann*fT; // KE of particle with avg. vel. of sqrt(8kT/(pi m))
  gen_action->SetKineticEnergy(KE); // KE if in vacuum (will scale by m_3/m_eff if in LHe4)
  G4double v_3 = GetThermalVelocity(); // v_3 if in vacuum

  // it is up to the detector object to scale v_3 if necessary when computing the
  // mean free path.
  detector->SetParticleVelocity(v_3);
  detector->SetTemperature(fT);
  detector->SetPressure(fPressure);

  diffusionMaterial* cell_mat = (diffusionMaterial*)(detector->GetCellLV()->GetMaterial());
  fD = cell_mat->GetD();

  FillParamHist();
}

void dressedSpinParameters::FillParamHist()
{
  G4double KE = gen_action->GetKineticEnergy();
  G4double v_3 = gen_action->GetVelocity();
  G4Material* cell_mat = detector->GetCellLV()->GetMaterial();
  G4double lambda = ((diffusionMaterial*)cell_mat)->GetMeanFreePath();

  hParameters->GetXaxis()->SetBinLabel(1, "T (K)");
  hParameters->SetBinContent(1, fT/kelvin);
  hParameters->GetXaxis()->SetBinLabel(2, "D (cm^{2}/s)");
  hParameters->SetBinContent(2, fD/cm/cm*s);

  hParameters->GetXaxis()->SetBinLabel(5, "Particle K.E. (MeV)");
  hParameters->SetBinContent(5, KE/MeV);
  hParameters->GetXaxis()->SetBinLabel(6, "v_{3} (cm/s)");
  hParameters->SetBinContent(6, v_3/cm*s);
  hParameters->GetXaxis()->SetBinLabel(7, "m.f.p. (cm)");
  hParameters->SetBinContent(7, lambda/cm);
}

void dressedSpinParameters::ShowParams()
{
  G4double KE = gen_action->GetKineticEnergy();
  G4double v_3 = gen_action->GetVelocity();
  G4double mass = gen_action->GetMass();
  G4Material* cell_mat = detector->GetCellLV()->GetMaterial();
  G4double lambda = ((diffusionMaterial*)cell_mat)->GetMeanFreePath();

  G4cout << "T = " << fT/kelvin << " K" << G4endl
         << "D = " << fD/cm/cm*s << " cm^2/s" << G4endl
         << "KE = " << KE/MeV << " MeV" << G4endl
         << "v_3 = " << v_3/cm*s << " cm/s" << G4endl
         << "lambda = " << lambda/cm << " cm" << G4endl
         << "mass = " << mass/c_light/c_light/gram*Avogadro
                      << " gram/mole" << G4endl;
}

