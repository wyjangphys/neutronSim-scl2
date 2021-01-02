/// \file nSimSCL2SteppingAction.hh
/// \brief Definition of the nSimSCL2SteppingAction class

#ifndef nSimSCL2SteppingAction_h
#define nSimSCL2SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class nSimSCL2EventAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class nSimSCL2SteppingAction : public G4UserSteppingAction
{
  public:
    nSimSCL2SteppingAction(nSimSCL2EventAction* eventAction);
    virtual ~nSimSCL2SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    nSimSCL2EventAction*  fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
