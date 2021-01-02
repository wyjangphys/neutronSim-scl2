/// \file nSimSCL2EventAction.hh
/// \brief Definition of the nSimSCL2EventAction class

#ifndef nSimSCL2EventAction_h
#define nSimSCL2EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class nSimSCL2RunAction;

/// Event action class
///

class nSimSCL2EventAction : public G4UserEventAction
{
  public:
    nSimSCL2EventAction(nSimSCL2RunAction* runAction);
    virtual ~nSimSCL2EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    nSimSCL2RunAction* fRunAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

