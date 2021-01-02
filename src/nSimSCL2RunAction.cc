/// \file nSimSCL2RunAction.cc
/// \brief Implementation of the nSimSCL2RunAction class

#include "nSimSCL2RunAction.hh"
#include "nSimSCL2PrimaryGeneratorAction.hh"
#include "nSimSCL2DetectorConstruction.hh"
// #include "nSimSCL2Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"
//#include "g4analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2RunAction::nSimSCL2RunAction()
: G4UserRunAction()
{
  // Analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);

  // Create 1-dimensional histogram
  analysisManager->CreateNtuple("tRAONSCL2_nSim", "RAONSCL2 NeutronSim");
  analysisManager->CreateNtupleDColumn("category");
  analysisManager->CreateNtupleSColumn("preStepProc");
  analysisManager->CreateNtupleSColumn("postStepProc");
  analysisManager->CreateNtupleDColumn("energy");
  analysisManager->CreateNtupleDColumn("kineticEnergy");
  analysisManager->CreateNtupleDColumn("vertex_x");
  analysisManager->CreateNtupleDColumn("vertex_y");
  analysisManager->CreateNtupleDColumn("vertex_z");
  analysisManager->CreateNtupleDColumn("px");
  analysisManager->CreateNtupleDColumn("py");
  analysisManager->CreateNtupleDColumn("pz");
  analysisManager->CreateNtupleDColumn("gTime");
  analysisManager->CreateNtupleDColumn("lTime");
  analysisManager->CreateNtupleDColumn("pTime");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2RunAction::~nSimSCL2RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nSimSCL2RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  // set file name and open file
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName("RAONSCL2");
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nSimSCL2RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // Print
  //
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

