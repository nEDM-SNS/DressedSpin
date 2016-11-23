#ifndef fieldmapFile_H
#define fieldmapFile_H 1

#ifdef ROOTMacros
#define G4double double
#else
#include "globals.hh"
#include "G4ThreeVector.hh"
#endif

#include "TH3.h"


class fieldmapFile
{
  public:

    fieldmapFile(char* input_filename);
    virtual ~fieldmapFile();

#ifdef ROOTMacros
    void GetFieldVector(Float_t x, Float_t y, Float_t z,
                        Double_t *pBx, Double_t *pBy, Double_t *pBz);
#else
    G4ThreeVector GetFieldVector(const G4ThreeVector &p);
    // returns normalized field (i.e., scaled by fB0x_norm)
#endif

    G4double GetFieldNormalization() { return fB0x_norm; }
    G4double GetScaleDevsFactor() { return fScaleDevs; }
    void SetScaleDevsFactor(G4double val) { fScaleDevs = val; }

    TH3* GetHistBx() { return hBx; }
    TH3* GetHistBy() { return hBy; }
    TH3* GetHistBz() { return hBz; }

    // this method should not normally be used.
    void setB0x_norm(double val) { fB0x_norm = val; }

  protected:
    TH3* hBx; // x-component of B-field (gauss), axes in cm
    TH3* hBy; // y-component of B-field (gauss), axes in cm
    TH3* hBz; // z-component of B-field (gauss), axes in cm
    TH1* hFieldPars; // contains volume-average of Bx in cell

    void read_fieldmap(char* input_filename, TH3* hx, TH3* hy, TH3* hz);
    G4double fB0x_norm; // normalization factor of fieldmap file values
    G4double fScaleDevs; // amount to scale deviations from ideal field

    G4double trilinearInterpolate(TH3* hBi, const double vec[3]);

#ifdef ROOTMacros
    ClassDef(fieldmapFile, 1)
#endif

};

#endif

