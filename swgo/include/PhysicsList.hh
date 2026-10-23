
#ifndef PhysicsList_HH
#define PhysicsList_HH

// #ifndef PhysicsList_h
// #define PhysicsList_h 1

#include "../include/OpticalPhysics.hh"
#include "FTFP_BERT.hh"
#include "G4VModularPhysicsList.hh"
#include "QGSP_BERT_HP.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class PhysicsListMessenger;
class StepMax;
class OpticalPhysics;

class PhysicsList : public G4VModularPhysicsList {
  public:
    PhysicsList(G4String);
    virtual ~PhysicsList();

    void SetCuts();
    void SetCutForGamma(G4double);
    void SetCutForElectron(G4double);
    void SetCutForPositron(G4double);

    void SetStepMax(G4double);
    StepMax *GetStepMaxProcess();
    void AddStepMax();

    /// Remove specific physics from physics list.
    void RemoveFromPhysicsList(const G4String &);

    /// Make sure that the physics list is empty.
    void ClearPhysics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

    // Turn on or off the absorption process
    void SetAbsorption(G4bool);

    void SetNbOfPhotonsCerenkov(G4int);

    void SetVerbose(G4int);

  private:
    G4double fCutForGamma;
    G4double fCutForElectron;
    G4double fCutForPositron;

    StepMax *fStepMaxProcess;

    G4bool fAbsorptionOn;

    OpticalPhysics *fOpticalPhysics;

    PhysicsListMessenger *fMessenger;

    G4VMPLData::G4PhysConstVectorData *fPhysicsVector;
};

#endif