#ifndef nSimSCL2DetectorConstruction_h
#define nSimSCL2DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry

class nSimSCL2DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    nSimSCL2DetectorConstruction();
    virtual ~nSimSCL2DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
