#ifndef UserEventAction_HH
#define UserEventAction_HH

// Local Libraries
//
#include "GLDetectorConstruction.hh"
#include "GLPrimaryGeneratorAction.hh"
#include "GLRunAction.hh"

// Geant4 Libraries
//
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4UserEventAction.hh"

#include "GLSteppingAction.hh"

// #include "CerenkovValidation.hh"

// C++ Libraries
//
#include <string>

// class GLDetectorConstruction;

class GLEventAction : public G4UserEventAction {
  public:
    GLEventAction(GLRunAction *runAction, GLPrimaryGeneratorAction *primaryGenAction, GLDetectorConstruction *det, GLSteppingAction *steppingAction);
    // GLEventAction(GLRunAction *runAction, GLPrimaryGeneratorAction *primaryGenAction, GLDetectorConstruction *det);
    virtual ~GLEventAction();

    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);

    void countingCerenkovs(G4int cphoton);
    void countingCerenkovs(G4double trackLength);
    G4double nPhotons;

    GLRunAction *fRunAction;
    GLPrimaryGeneratorAction *fPriGenAction;
    GLDetectorConstruction *fDetector;
    GLSteppingAction *fSteppingAction; // Ponteiro para o SteppingAction

    G4ThreeVector partMomeDir;

    G4int ROWID_hodoscope1;
    G4int COLUMNID_hodoscope1;
    G4double TIME_hodoscope1;

    G4int SecElectronCount;
    G4int totCerenkovCount;
    G4int totCerenkovMuCount;
    G4int totCerenkovElectronCount;
    G4double fTime;

    int muonOk;
    int elecOk;
    int gammOk;
    int neutOk;

    std::string partId;

  private:
    // IDs dos SDs das PMTs
    G4int fPMT1CollID;
    G4int fPMT2CollID;
    G4int fPMT3CollID;

    //    CerenkovValidation* validating;
    G4int cerenkovPhontons;
    G4double totalLength;

    G4int cphoton;
    G4double trackLength;

    G4int fWaterCollectionID;
    // G4int fPMTCollID;
    G4int fHodoscope1CollID;

    G4int fVerbose;

    G4int fPMTThreshold;

    G4bool fForcedrawphotons;
    G4bool fForcenophotons;

    G4int fHitCount;
    G4int fPhotonCount_Scint;
    G4int fPhotonCount_Ceren;
    G4int fAbsorptionCount;
    G4int fBoundaryAbsorptionCount;

    // G4double ftimeScint;
    // G4double ftimePMT;

    G4int pmts;
    G4int hodoscope_hit;

    G4double aveTimePmtHits;
    G4double firstLXeHitTime;
    std::vector<G4double> time_hodoscope1;
    std::vector<G4int> columnID_hodoscope1;
    std::vector<G4int> rowID_hodoscope1;

    G4double aveTimePmtHits_mu;
    G4double fHitCount_mu;
    G4double aveTimePmtHits_e;
    G4double fHitCount_e;

    G4double edep;
    G4double edep_mu;
    G4double edep_e;
    G4double edep_gamma;
    G4double fTotE;
    G4double fTotE_mu;
    G4double fTotE_e;
    G4double fTotE_gamma;
    G4int NumberSecondary;
    G4double ParentID;
    G4double secondaryenergy_electron_sum;
    G4double secondaryelectron_count;
    G4double secondaryenergy_cerenkov_sum;
    G4double secondarycerenkov_count;
    G4double secondarycerenkov_muon_count;
    G4double secondarycerenkov_electron_count;
    G4double secondaryenergy_scintillation_sum;
    G4double secondaryscintillation_count;
    G4double secondaryscintillation_muon_count;
    G4double secondaryscintillation_electron_count;

    // These only have meaning if totE > 0
    // If totE = 0 then these won't be set by EndOfEventAction
    G4ThreeVector fEWeightPos;
    G4ThreeVector fReconPos; // Also relies on hitCount>0
    G4ThreeVector fConvPos;  // true (initial) converstion position
    G4bool fConvPosSet;
    G4ThreeVector fPosMax;
    G4double fEdepMax;

    G4int fPMTsAboveThreshold;
};

#endif
