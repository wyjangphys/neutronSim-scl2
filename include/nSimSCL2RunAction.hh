/// \file nSimSCL2RunAction.hh
/// \brief Definition of the nSimSCL2RunAction class
//

#ifndef nSimSCL2RunAction_h
#define nSimSCL2RunAction_h 1
#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class nSimSCL2RunAction : public G4UserRunAction
{
  public:
    nSimSCL2RunAction();
    virtual ~nSimSCL2RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif
