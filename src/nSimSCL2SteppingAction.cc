/// \file nSimSCL2SteppingAction.cc
/// \brief Implementation of the nSimSCL2SteppingAction class

#include "nSimSCL2SteppingAction.hh"
#include "nSimSCL2EventAction.hh"
#include "nSimSCL2DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
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
  G4double Edep = step->GetTotalEnergyDeposit();
  G4double energy = step->GetPreStepPoint()->GetKineticEnergy();
  G4ThreeVector momentumDirection = step->GetPreStepPoint()->GetMomentumDirection();
  G4ThreeVector vectorPosition = step->GetPreStepPoint()->GetPosition();

  //----------------------------------------------                                                                                                                                    
  //        Track                                                                                                                                                                      
  //----------------------------------------------                                                                                                                                    

  G4ParticleDefinition* fDef = fTrack->GetDefinition();     // dynamic particle definition                                                                                      
  G4String name = fDef->GetParticleName();                  //                                                                                                                  
  G4String partType= fDef->GetParticleType();               // ??                                                                                                                
  G4double lifeTime = fDef->GetPDGLifeTime();               //<---                                                                                                              
  //const G4VProcess* process = fTrack->GetCreatorProcess();
  G4int ZZ=fDef->GetAtomicNumber();
  G4int AA=fDef->GetAtomicMass();

  //  =================================================                                                                                                                                
  G4int pID = fTrack->GetParentID();
  G4int tID = fTrack->GetTrackID();
  G4int sID = fTrack->GetCurrentStepNumber();

  G4double tLength = fTrack->GetTrackLength();
  G4double sLength = fTrack->GetStepLength();

  G4double gTime = fTrack->GetGlobalTime();
  G4double lTime = fTrack->GetLocalTime();
  G4double pTime = fTrack->GetProperTime();

  G4String currentStepVolName, postStepVolName, currentProcessName, preStepProcessName;
  currentStepVolName = fTrack->GetVolume()->GetName();

  if( fTrack->GetNextVolume() != NULL )
    postStepVolName = fTrack->GetNextVolume()->GetName();
  else
    postStepVolName = "\0";

  if( step->GetPostStepPoint() != NULL )
    currentProcessName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  else
    currentProcessName = "\0";

  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  if( preStepPoint != NULL && preStepPoint->GetProcessDefinedStep() != NULL )
    preStepProcessName = preStepPoint->GetProcessDefinedStep()->GetProcessName();
  else
    preStepProcessName = "\0";

  if( name == "neutron" )
  {
  G4cout << "\t" <<
    Edep << "\t" <<
    energy << "\t" <<
    name << "\t" <<
    partType << "\t" <<
    lifeTime << "\t" <<
    pID << "\t" <<
    tID << "\t" <<
    sID << "\t" <<
    tLength << "\t" <<
    sLength << "\t" <<
    gTime << "\t" <<
    lTime << "\t" <<
    pTime << "\t" <<
    currentStepVolName << "\t" <<
    postStepVolName << "\t" <<
    currentProcessName << "\t" <<
    ZZ << "\t" <<
    AA << "\t" << G4endl;
  }

  auto analysisManager = G4AnalysisManager::Instance();

  const G4TrackVector* secondary = step->GetSecondary();
  for( size_t lp = 0; lp < (*secondary).size(); lp++ )
  {
    // particle name
    analysisManager->FillNtupleSColumn(0, (*secondary)[lp]->GetDefinition()->GetParticleName() );
    // preStepProc
    analysisManager->FillNtupleSColumn(1, step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
    // parent id
    analysisManager->FillNtupleDColumn(2, (*secondary)[lp]->GetParentID());
    // track id
    analysisManager->FillNtupleDColumn(3, (*secondary)[lp]->GetTrackID());
    // step number
    analysisManager->FillNtupleDColumn(4, (*secondary)[lp]->GetCurrentStepNumber());
    // kineticEnergy
    analysisManager->FillNtupleDColumn(5, (G4double)(*secondary)[lp]->GetKineticEnergy()/CLHEP::MeV);
    // vertex coordinates
    analysisManager->FillNtupleDColumn(6, (G4double)(*secondary)[lp]->GetPosition().getX());
    analysisManager->FillNtupleDColumn(7, (G4double)(*secondary)[lp]->GetPosition().getY());
    analysisManager->FillNtupleDColumn(8, (G4double)(*secondary)[lp]->GetPosition().getZ());
    // momentum
    analysisManager->FillNtupleDColumn(9, (G4double)(*secondary)[lp]->GetMomentum().getX()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(10, (G4double)(*secondary)[lp]->GetMomentum().getY()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(11, (G4double)(*secondary)[lp]->GetMomentum().getZ()/CLHEP::MeV);
    analysisManager->AddNtupleRow();
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

