#ifndef GLRunAction_HH
#define GLRunAction_HH

// Geant4 Libraries
//
#include "G4UserRunAction.hh"
#include "globals.hh"
// #include "g4root.hh"
// #include "G4AnalysisManager.hh"
// #include "G4RootAnalysisManager.hh"
#include "G4AnalysisManager.hh"
#include "G4VAnalysisManager.hh"

// Local Libraries
//
#include "CerValHistograms.hh"
#include "CerenkovValidation.hh"
#include "histosRun.hh"

#include "GLSteppingAction.hh"

class G4Timer;
class G4Run;

class GLRunAction : public G4UserRunAction {
  public:
    GLRunAction();
    virtual ~GLRunAction();

  public:
    virtual void BeginOfRunAction(const G4Run *aRun);
    virtual void EndOfRunAction(const G4Run *aRun);

    void startCerenkValid();
    void closeCerenkValid();

    CerenkovValidation *cerVali;
    CerValHistograms *histCerVali;
    histosRun *histRun;

    void fillHistPhoVcm();

    void startCoulombValid();
    void closeCoulombValid();

    //    coulombScattering* scatter;

  private:
    // G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4Timer *fTimer;
    int cervaliOk = 0;
    int coulombOk = 0;
    int histRunOk = 1;

    GLSteppingAction *fSteppingAction; // Ponteiro para o SteppingAction
};
#endif
