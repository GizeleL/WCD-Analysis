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
    GLSteppingAction();
    virtual ~GLSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step *);
    void SetEventAction(GLEventAction *eventAction); // Método para configurar o GLEventAction

    G4int GetCherenkovPhotonCount() const { return fCherenkovPhotonCount; }
    void ResetCherenkovPhotonCount() { fCherenkovPhotonCount = 0; }

  private:
    GLEventAction *fEventAction; // Ponteiro para GLEventAction

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
    // PMTSD *pmtSD;

    G4String volumName;
    G4String cerenProc;
    G4int currStep;
    G4double lengthStep;

    G4int fCherenkovPhotonCount;

    double trackTime;
    double de;
    int wlSpect;
    int wlSpect2;
    int wlSpect3;
    int wlSpectall;
};

#endif
