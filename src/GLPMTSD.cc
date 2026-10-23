#include "GLPMTSD.hh"
#include "G4OpticalPhoton.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"

PMTSD::PMTSD(G4String name)
    : G4VSensitiveDetector(name),
      fPMTHit(nullptr),
      fPhotonCount(0),
      fPMTName(name) {
    // G4cout << "...PMTSD criado: " << name << "..." << G4endl;
    fPMTHit = new PMTHit();
}

PMTSD::~PMTSD() {
    if (fPMTHit) {
        delete fPMTHit;
        fPMTHit = nullptr;
    }
}

void PMTSD::Initialize(G4HCofThisEvent *) {
    //   G4cout << "PMTSD Initialize: " << fPMTName << G4endl;
    fPhotonCount = 0;
}

G4bool PMTSD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {
    //  G4cout << "PMTSD ProcessHits chamado! Partícula: "
    //         << aStep->GetTrack()->GetDefinition()->GetParticleName()
    //         << G4endl;

    if (aStep->GetTrack()->GetDefinition() !=
        G4OpticalPhoton::OpticalPhotonDefinition())
        return false;

    G4double energy = aStep->GetTrack()->GetTotalEnergy();

    // Aplica eficiência quântica
    G4int detected = fPMTHit->askDetected(energy);
    if (detected > 0) {
        fPhotonCount++;
        // Mata o fóton após detecção
        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    }

    return true;
}

void PMTSD::EndOfEvent(G4HCofThisEvent *) {
    // Contagem disponível via GetPhotonCount()
    // Será lida no EventAction
}
