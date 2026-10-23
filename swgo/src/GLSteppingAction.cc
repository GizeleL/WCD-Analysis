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

GLSteppingAction::GLSteppingAction(GLEventAction *eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction) {
    G4cout << "...SteppingAction..." << G4endl;
    G4TransportationManager::GetTransportationManager()
        ->GetNavigatorForTracking()
        ->SetPushVerbosity(0);

    fScintillationCounter = 0;
    lengthMaxOk = 0;
    fEventNumber = -1;
    initEner = 0.;
    pmtSD = new PMTSD;
    // cerValid = new CerenkovValidation;

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

    // --------------------------------------------------------------

    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        currStep = track->GetCurrentStepNumber();
        cerenProc = track->GetCreatorProcess()->GetProcessName();

        // =====================
        // *** For histosRun ***

        // ----------------------
        // ** Fill for Photons **

        // ---------------------
        // * Fill for CerenPho *

        if (currStep == 1 && cerenProc == "Cerenkov") {
            if (fEventAction->muonOk)
                fEventAction->fRunAction->histRun->cerenPho(0);

            fEventAction->fRunAction->histRun->cerenPho(5);
        }

        ///////////////////////////////////////////////////////////////////// PMT
        // ------------------------
        // * Fill for CerenPhoPmt *
        if (cerenProc == "Cerenkov" && volumName == "pmt_geo") {
            if (fEventAction->muonOk)
                fEventAction->fRunAction->histRun->cerenPhoPmt(0);

            fEventAction->fRunAction->histRun->cerenPhoPmt(5);

            // ---------------------------
            // ** Fill for Pulses **
            // * Fill for CerenPhoElect *

            wlSpect = pmtSD->ProcessHits(step, trackTime = step->GetPostStepPoint()->GetGlobalTime());

            // if ( pmtSD->ProcessHits(step, track->GetGlobalTime()) > 0 )
            if (wlSpect > 0) {
                trackTime = step->GetPostStepPoint()->GetGlobalTime() / (1. * ns);

                if (fEventAction->muonOk) {
                    fEventAction->fRunAction->histRun->cerenPhoElect(0, wlSpect);
                    fEventAction->fRunAction->histRun->meanPulse(0, trackTime);
                }
                fEventAction->fRunAction->histRun->cerenPhoElect(5, wlSpect);
                fEventAction->fRunAction->histRun->meanPulse(5, trackTime);
            }
            track->SetTrackStatus(fStopAndKill);
        }

        ///////////////////////////////////////////////////////////////////// PMT2
        // ------------------------
        // * Fill for CerenPhoPmt *
        if (cerenProc == "Cerenkov" && volumName == "pmt_geo2") {
            if (fEventAction->muonOk)
                fEventAction->fRunAction->histRun->cerenPhoPmt2(1);

            fEventAction->fRunAction->histRun->cerenPhoPmt(5);

            // ---------------------------
            // ** Fill for Pulses **
            // * Fill for CerenPhoElect *

            wlSpect2 = pmtSD->ProcessHits(step, trackTime = step->GetPostStepPoint()->GetGlobalTime());

            // if ( pmtSD->ProcessHits(step, track->GetGlobalTime()) > 0 )
            if (wlSpect2 > 0) {
                trackTime = step->GetPostStepPoint()->GetGlobalTime() / (1. * ns);

                if (fEventAction->muonOk) {
                    fEventAction->fRunAction->histRun->cerenPhoElect2(1, wlSpect2);
                    fEventAction->fRunAction->histRun->meanPulse2(1, trackTime);
                }

                fEventAction->fRunAction->histRun->cerenPhoElect(5, wlSpect2);
                fEventAction->fRunAction->histRun->meanPulse(5, trackTime);
            }
            track->SetTrackStatus(fStopAndKill);
        }

        ///////////////////////////////////////////////////////////////////// PMT3
        // ------------------------
        // * Fill for CerenPhoPmt *
        if (cerenProc == "Cerenkov" && volumName == "pmt_geo3") {
            if (fEventAction->muonOk)
                fEventAction->fRunAction->histRun->cerenPhoPmt3(3);

            fEventAction->fRunAction->histRun->cerenPhoPmt(5);
            // ---------------------------
            // ** Fill for Pulses **
            // * Fill for CerenPhoElect *

            wlSpect3 = pmtSD->ProcessHits(step, trackTime = step->GetPostStepPoint()->GetGlobalTime());

            // if ( pmtSD->ProcessHits(step, track->GetGlobalTime()) > 0 )
            if (wlSpect3 > 0) {
                trackTime = step->GetPostStepPoint()->GetGlobalTime() / (1. * ns);

                if (fEventAction->muonOk) {
                    fEventAction->fRunAction->histRun->cerenPhoElect3(3, wlSpect3);
                    fEventAction->fRunAction->histRun->meanPulse3(3, trackTime);
                }
                fEventAction->fRunAction->histRun->cerenPhoElect(5, wlSpect3);
                fEventAction->fRunAction->histRun->meanPulse(5, trackTime);
            }
            track->SetTrackStatus(fStopAndKill);
        }
    }

    // -------------------------------
    // ** Fill for Inside Detector  **

    if (track->GetParentID() == 0 && volumName == "watervol") {
        lengthStep = step->GetStepLength();
        de = step->GetTotalEnergyDeposit();
        if (fEventAction->muonOk)
            fEventAction->fRunAction->histRun->trackLengthDetec(0, lengthStep, de);

        fEventAction->fRunAction->histRun->trackLengthDetec(5, lengthStep, de);
    }
}