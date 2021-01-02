/// \file nSimSCL2ActionInitialization.cc
/// \brief Implementation of the nSimSCL2ActionInitialization class

#include "nSimSCL2ActionInitialization.hh"
#include "nSimSCL2PrimaryGeneratorAction.hh"
#include "nSimSCL2RunAction.hh"
#include "nSimSCL2EventAction.hh"
#include "nSimSCL2SteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2ActionInitialization::nSimSCL2ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2ActionInitialization::~nSimSCL2ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nSimSCL2ActionInitialization::BuildForMaster() const
{
  nSimSCL2RunAction* runAction = new nSimSCL2RunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nSimSCL2ActionInitialization::Build() const
{
  SetUserAction(new nSimSCL2PrimaryGeneratorAction);

  nSimSCL2RunAction* runAction = new nSimSCL2RunAction;
  SetUserAction(runAction);
  
  nSimSCL2EventAction* eventAction = new nSimSCL2EventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new nSimSCL2SteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
