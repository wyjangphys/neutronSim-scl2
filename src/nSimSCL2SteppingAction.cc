/// \file nSimSCL2SteppingAction.cc
/// \brief Implementation of the nSimSCL2SteppingAction class

#include "nSimSCL2SteppingAction.hh"
#include "nSimSCL2EventAction.hh"
#include "nSimSCL2DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleTypes.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2SteppingAction::nSimSCL2SteppingAction(nSimSCL2EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2SteppingAction::~nSimSCL2SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nSimSCL2SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* fTrack = step->GetTrack();

  //----------------------------------------------
  //       Step information
  //----------------------------------------------
  G4StepPoint* preStepPt = step->GetPreStepPoint();
  G4StepPoint* postStepPt = step->GetPostStepPoint();
  G4double Edep = step->GetTotalEnergyDeposit();
  G4double energy = preStepPt->GetTotalEnergy();
  G4double kin_energy = preStepPt->GetKineticEnergy();
  G4ThreeVector momentumDirection = preStepPt->GetMomentumDirection();
  G4ThreeVector vectorPosition = preStepPt->GetPosition();

  //----------------------------------------------
  //        Track
  //----------------------------------------------

  G4ParticleDefinition* fDef = fTrack->GetDefinition();     // dynamic particle definition
  G4String name = fDef->GetParticleName();                  //
  G4String partType= fDef->GetParticleType();               // ??
  G4double lifeTime = fDef->GetPDGLifeTime()/CLHEP::nm;     //<---
  //const G4VProcess* process = fTrack->GetCreatorProcess();
  G4int ZZ=fDef->GetAtomicNumber();
  G4int AA=fDef->GetAtomicMass();

  //  =================================================
  G4int pID = fTrack->GetParentID();
  G4int tID = fTrack->GetTrackID();
  G4int sID = fTrack->GetCurrentStepNumber();

  G4double tLength = fTrack->GetTrackLength()/CLHEP::nm;
  G4double sLength = fTrack->GetStepLength()/CLHEP::nm;

  G4double gTime = preStepPt->GetGlobalTime()/CLHEP::ns;
  G4double lTime = preStepPt->GetLocalTime()/CLHEP::ns;
  G4double pTime = preStepPt->GetProperTime()/CLHEP::ns;

  G4double px, py, pz;
  px = postStepPt->GetMomentum().getX()/CLHEP::GeV;
  py = postStepPt->GetMomentum().getY()/CLHEP::GeV;
  pz = postStepPt->GetMomentum().getZ()/CLHEP::GeV;

  G4double vertex_x, vertex_y, vertex_z;
  vertex_x = postStepPt->GetPosition().getX()/CLHEP::m;
  vertex_y = postStepPt->GetPosition().getY()/CLHEP::m;
  vertex_z = postStepPt->GetPosition().getZ()/CLHEP::m;

  G4String preStepVolName, postStepVolName, postStepProcessName, preStepProcessName;
  preStepVolName = preStepPt->GetPhysicalVolume()->GetName();

  if( fTrack->GetNextVolume() != NULL )
    postStepVolName = postStepPt->GetPhysicalVolume()->GetName();
  else
    postStepVolName = "\0";

  if( postStepPt != NULL )
    postStepProcessName = postStepPt->GetProcessDefinedStep()->GetProcessName();
  else
    postStepProcessName = "\0";

  G4StepPoint* preStepPoint = preStepPt;
  if( preStepPoint != NULL && preStepPoint->GetProcessDefinedStep() != NULL )
    preStepProcessName = preStepPoint->GetProcessDefinedStep()->GetProcessName();
  else
    preStepProcessName = "\0";


  // -------------------------------------------------------------------
  //
  // Save data into the ntuple
  //
  // -------------------------------------------------------------------

  auto analysisManager = G4AnalysisManager::Instance();

  if( name == "neutron"
      && preStepVolName == "Target"
      && postStepVolName == "Modulator"
      && preStepProcessName == "Transportation" )
  {
    analysisManager->FillNtupleDColumn(0, 0);
    analysisManager->FillNtupleSColumn(1, preStepProcessName);
    analysisManager->FillNtupleSColumn(2, postStepProcessName);
    analysisManager->FillNtupleDColumn(3, energy);
    analysisManager->FillNtupleDColumn(4, kin_energy);
    analysisManager->FillNtupleDColumn(5, vertex_x);
    analysisManager->FillNtupleDColumn(6, vertex_y);
    analysisManager->FillNtupleDColumn(7, vertex_z);
    analysisManager->FillNtupleDColumn(8, px);
    analysisManager->FillNtupleDColumn(9, py);
    analysisManager->FillNtupleDColumn(10, pz);
    analysisManager->FillNtupleDColumn(11, gTime);
    analysisManager->FillNtupleDColumn(12, lTime);
    analysisManager->FillNtupleDColumn(13, pTime);
  }
  else if( name == "neutron"
      && preStepVolName == "Modulator"
      && postStepVolName == "Detector"
      && preStepProcessName == "Transportation" )
  {
    analysisManager->FillNtupleDColumn(0, 1);
    analysisManager->FillNtupleSColumn(1, preStepProcessName);
    analysisManager->FillNtupleSColumn(2, postStepProcessName);
    analysisManager->FillNtupleDColumn(3, energy);
    analysisManager->FillNtupleDColumn(4, kin_energy);
    analysisManager->FillNtupleDColumn(5, vertex_x);
    analysisManager->FillNtupleDColumn(6, vertex_y);
    analysisManager->FillNtupleDColumn(7, vertex_z);
    analysisManager->FillNtupleDColumn(8, px);
    analysisManager->FillNtupleDColumn(9, py);
    analysisManager->FillNtupleDColumn(10, pz);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

