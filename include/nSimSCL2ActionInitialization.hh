#ifndef nSimSCL2ActionInitialization_h
#define nSimSCL2ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class nSimSCL2ActionInitialization : public G4VUserActionInitialization
{
  public:
    nSimSCL2ActionInitialization();
    virtual ~nSimSCL2ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif
