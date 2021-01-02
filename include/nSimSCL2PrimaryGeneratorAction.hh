/// \file nSimSCL2PrimaryGeneratorAction.hh
/// \brief Definition of the nSimSCL2PrimaryGeneratorAction class

#ifndef nSimSCL2PrimaryGeneratorAction_h
#define nSimSCL2PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 600 MeV proton.

class nSimSCL2PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    nSimSCL2PrimaryGeneratorAction();
    virtual ~nSimSCL2PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
