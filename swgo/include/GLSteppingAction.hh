#ifndef GLSteppingAction_HH
#define GLSteppingAction_HH

// Geant4 Libraries
//
#include "G4UserSteppingAction.hh"
#include "globals.hh"

// Local Libraries
//
#include "../include/GLDetectorConstruction.hh"
#include "../include/GLPMTSD.hh"
// #include "CerenkovValidation.hh"

// C++ Libraries
//

class GLEventAction;
class GLPrimaryGeneratorAction;

/// Stepping action class
///

class GLSteppingAction : public G4UserSteppingAction {
  public:
    GLSteppingAction(GLEventAction *eventAction);
    virtual ~GLSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step *);
    GLEventAction *fEventAction;

  private:
    // For Cerenkov validation
    //
    //    CerenkovValidation* cerValid;
    //    CerenkovValidation* validating;
    const GLDetectorConstruction *detectorConstruction;
    G4VPhysicalVolume *fwaterVolume;
    G4int fScintillationCounter;
    G4int lengthMaxOk;
    G4double initEner;
    G4int fEventNumber;
    PMTSD *pmtSD;

    G4String volumName;
    G4String cerenProc;
    G4int currStep;
    G4double lengthStep;

    double trackTime;
    double de;
    int wlSpect;
    int wlSpect2;
    int wlSpect3;
    int wlSpectall;
};

#endif
