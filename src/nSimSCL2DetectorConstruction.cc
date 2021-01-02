/// \file nSimSCL2DetectorConstruction.cc
/// \brief Implementation of the nSimSCL2DetectorConstruction class

#include "nSimSCL2DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2DetectorConstruction::nSimSCL2DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nSimSCL2DetectorConstruction::~nSimSCL2DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* nSimSCL2DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Target parameters
  //
  G4double target_sizeXY = 100*cm, target_sizeZ = 100*cm;
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_Fe");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2*target_sizeXY;
  G4double world_sizeZ  = 1.2*target_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Fe dump
  //
  G4Box* solidTarget =
    new G4Box("FeDump",                    //its name
        0.5*target_sizeXY,
        0.5*target_sizeXY,
        0.5*target_sizeZ); //its size

  G4LogicalVolume* logicTarget =
    new G4LogicalVolume(solidTarget,            //its solid
                        target_mat,             //its material
                        "Target");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicTarget,                //its logical volume
                    "Target",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  // Neutron Modulator
  //
  G4double nmod_sizeXY = 1*m;
  G4double nmod_sizeZ = 0.1*m;

  G4Box* solidModulator =
    new G4Box("NeutronModulator",
        0.5*nmod_sizeXY,
        0.5*nmod_sizeXY,
        0.5*nmod_sizeZ);
  //------------------------------------------------------------------------------------------
  // Polyurethane : modulator material
  G4Element* elC = new G4Element("Carbon", // its name
      "C", // its symbol
      6., // its atomic number
      12.*g/mole);  // its atomic mass
  G4Element* elH = new G4Element("Hydrogen", "H", 1., 1.01*g/mole);
  G4Element* elN = new G4Element("Nitrogen", "N", 7., 14.*g/mole);
  G4Element* elO = new G4Element("Oxygen", "O", 8., 16.00*g/mole);
  G4Material *modulator_mat = new G4Material(
      "Polyurethane",   // name
      1100 * kg / m3,   // density
      4,                // number of elements
      kStateSolid);     // state : solid? liquid? gas?
  modulator_mat->AddElement(elC, 3);
  modulator_mat->AddElement(elH, 8);
  modulator_mat->AddElement(elN, 2);
  modulator_mat->AddElement(elO, 1);
  //------------------------------------------------------------------------------------------
  G4LogicalVolume* logicModulator =
    new G4LogicalVolume(solidModulator,
        modulator_mat,     // if this is a vacuum test run, replace solidModulator into world_mat
        "Modulator");

  new G4PVPlacement(0,
      G4ThreeVector(0,0,0.5*(target_sizeZ+nmod_sizeZ)),
      logicModulator,
      "Modulator",
      logicWorld,
      false,
      0,
      checkOverlaps);

  //---------------------------------------------------------------------------------------------
  //
  // LAr Detector
  //
  //---------------------------------------------------------------------------------------------
  // LAr material
  G4double        z = 18.0;
  G4double        a = 207.19 * g/mole;
  G4double  density = 11.35 * g/cm3;
  G4Material* lArMat = new G4Material("lArMat", z, a, density);

  G4double lArTrd_dx1 = 1.15*m;
  G4double lArTrd_dx2 = 2.24*m;
  G4double lArTrd_dy1 = 1.15*m;
  G4double lArTrd_dy2 = 2.24*m;
  G4double lArTrd_dz  = 1.0*m;
  G4Trd* lArTrd =
    new G4Trd("lArTrd",
        0.5 * lArTrd_dx1,   // dx1
        0.5 * lArTrd_dx2,   // dx2
        0.5 * lArTrd_dy1,   // dy1
        0.5 * lArTrd_dy2,   // dy2
        0.5 * lArTrd_dz);

  G4LogicalVolume* lArLogicV =
    new G4LogicalVolume(lArTrd,
        lArMat,
        "Detector");

  G4VPhysicalVolume* physlAr =
    new G4PVPlacement(0,
        G4ThreeVector(0, 0, 0.5*target_sizeZ + nmod_sizeZ + 0.5*lArTrd_dz ),
        lArLogicV,
        "Detector",
        logicWorld,
        false,
        0,
        checkOverlaps);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
