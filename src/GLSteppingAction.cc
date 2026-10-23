// Geant4 Libraries
//
#include "G4Step.hh"
#include "G4Track.hh"

#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
// #include "g4root.hh"

// Local Libraries
#include "CerenkovValidation.hh"
#include "GLDetectorConstruction.hh"
#include "GLEventAction.hh"
#include "GLPMTSD.hh"
#include "GLPrimaryGeneratorAction.hh"
#include "GLSteppingAction.hh"
#include "histosRun.hh"

GLSteppingAction::GLSteppingAction()
    // GLSteppingAction::GLSteppingAction(GLEventAction *eventAction)
    : G4UserSteppingAction() {
    // fEventAction(nullptr) {
    G4cout << "...SteppingAction..." << G4endl;
    G4TransportationManager::GetTransportationManager()
        ->GetNavigatorForTracking()
        ->SetPushVerbosity(0);

    fScintillationCounter = 0;
    lengthMaxOk = 0;
    fEventNumber = -1;
    initEner = 0.;

    detectorConstruction = static_cast<const GLDetectorConstruction *>(G4RunManager::GetRunManager()
                                                                           ->GetUserDetectorConstruction());
}

GLSteppingAction::~GLSteppingAction() {}

void GLSteppingAction::UserSteppingAction(const G4Step *step) {
    // --------------------
    // Get G4Track variable
    G4Track *track = step->GetTrack();
    volumName = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();

    if (track->GetParentID() == 0 && volumName == "Ground_geo")
        track->SetTrackStatus(fStopAndKill);

    if (volumName == "expHall" || volumName == "Ground_geo")
        track->SetTrackStatus(fStopAndKill);

    // -------------------------------------------------------------

    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
            G4int stepNum = track->GetCurrentStepNumber();
            //   if (stepNum == 1) {
            //     G4cout << "Fóton criado em: " << volumName << G4endl;
            //  }
            //  if (stepNum % 100 == 0) {
            //      G4cout << "Fóton no passo " << stepNum
            //             << " no volume: " << volumName << G4endl;
            //  }
            if (stepNum > 1000) {
                track->SetTrackStatus(fStopAndKill);
                return;
            }

            // Detecta fótons chegando nas PMTs
            G4String nextVolume = "";
            if (step->GetPostStepPoint()->GetPhysicalVolume()) {
                nextVolume = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();
            }

            if (nextVolume == "pmt_geo" ||
                nextVolume == "pmt_geo2" ||
                nextVolume == "pmt_geo3") {

                // Busca o SD correto e registra o hit
                G4SDManager *sdman = G4SDManager::GetSDMpointer();
                // protecao da memoria
                if (!sdman) {
                    track->SetTrackStatus(fStopAndKill);
                    return;
                }

                //  PMTSD *pmt = nullptr;
                // if (nextVolume == "pmt_geo")
                //     pmt = static_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT1"));
                // else if (nextVolume == "pmt_geo2")
                //     pmt = static_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT2"));
                // else if (nextVolume == "pmt_geo3")
                //                    pmt = static_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT3"));

                PMTSD *pmt = nullptr;
                if (nextVolume == "pmt_geo")
                    pmt = dynamic_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT1"));
                else if (nextVolume == "pmt_geo2")
                    pmt = dynamic_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT2"));
                else if (nextVolume == "pmt_geo3")
                    pmt = dynamic_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT3"));
                else if (nextVolume == "pmt_geo4")
                    pmt = dynamic_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT4"));

                if (pmt && pmt->GetPMTHit()) {
                    G4double energy = track->GetTotalEnergy();
                    G4int detected = pmt->GetPMTHit()->askDetected(energy);
                    if (detected > 0) {
                        pmt->IncrementPhotonCount();
                    }
                }
                track->SetTrackStatus(fStopAndKill);
            }
        }

        currStep = track->GetCurrentStepNumber();
        cerenProc = track->GetCreatorProcess()->GetProcessName();
    }

    // -------------------------------
    // ** Fill for Inside Detector  **
    // No m[uon veertical, nao vemos fótons acima de 70m cm
    // if (volumName == "watervol") {
    //     G4double posZ = step->GetPostStepPoint()->GetPosition().z();
    //     if (posZ > 700.) { // acima de 70cm (em mm)
    //          G4cout << "Fóton acima de 70cm: Z=" << posZ / 10. << " cm" << G4endl;
    //    }
    //  }
}

void GLSteppingAction::SetEventAction(GLEventAction *eventAction) {
    fEventAction = eventAction; // Configure o ponteiro para GLEventAction
}