#ifndef detector_mcgregor90_H
#define detector_mcgregor90_H 1

#include "dressedSpinDetectorConstruction.hh"

class detector_mcgregor90 : public dressedSpinDetectorConstruction
{
  public:

    detector_mcgregor90();
    ~detector_mcgregor90();

  protected:
    void ConstructCell(); // called by Construct()

  private:
    
};

#endif

