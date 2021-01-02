/// \file nSimSCL2EventAction.cc
/// \brief Implementation of the nSimSCL2EventAction class

#include "nSimSCL2EventAction.hh"
#include "nSimSCL2RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2EventAction::nSimSCL2EventAction(nSimSCL2RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2EventAction::~nSimSCL2EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nSimSCL2EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nSimSCL2EventAction::EndOfEventAction(const G4Event* event)
{
  /*
  for( unsigned long i = 0; i < event->GetTrajectoryContainer()->size(); i++)
  {
    G4cout << "TrackID: "    << event->GetTrajectoryContainer()->GetVector()->at(i)->GetTrackID() << G4endl;
    G4cout << "Name: "       << event->GetTrajectoryContainer()->GetVector()->at(i)->GetParticleName() << G4endl;
    G4cout << "InitMom:"     << event->GetTrajectoryContainer()->GetVector()->at(i)->GetInitialMomentum() << G4endl;
    G4cout << "ParentID: "   << event->GetTrajectoryContainer()->GetVector()->at(i)->GetParentID() << G4endl;
    G4cout << "PDGEncoding:" << event->GetTrajectoryContainer()->GetVector()->at(i)->GetPDGEncoding() << G4endl;
  }
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
