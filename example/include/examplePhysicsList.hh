#ifndef examplePhysicsList_h
#define examplePhysicsList_h 1

#include "dressedSpinPhysicsList.hh"

class examplePhysicsList: public dressedSpinPhysicsList
{
  public:
    examplePhysicsList();
    ~examplePhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructProcess();

};

#endif



