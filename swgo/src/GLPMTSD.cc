// Geant4 Libraries
//
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"

#include "G4AnalysisManager.hh"
#include "G4RootAnalysisManager.hh"
#include "G4VAnalysisManager.hh"

#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4ios.hh"

// #include "g4root.hh"

// Local Libraries
#include "GLDetectorConstruction.hh"
#include "GLPMTHit.hh"
#include "GLPMTSD.hh"

// C++ Libraries
// #include <iomanip>
// #include <locale>
// #include <sstream>
// #include <string>

PMTSD::PMTSD()
    : phoHit(),
      pulseNumber(0),
      phoDetec(0.)
//  : G4VSensitiveDetector(name),
{
    G4cout << "...PMTSD..." << G4endl;
    phoHit = new PMTHit;
    kinEnergy = 0.;
    phoDetec = 0;
}

PMTSD::~PMTSD() {}

G4int PMTSD::ProcessHits(const G4Step *aStep, G4double time) {
    kinEnergy = aStep->GetTrack()->GetTotalEnergy();
    phoDetec = phoHit->askDetected(kinEnergy);
    double tracktime;
    tracktime = aStep->GetPostStepPoint()->GetGlobalTime();
    if (phoDetec > 0)
        doPulse(tracktime); // aStep->GetTrack(), time);

    return int(phoDetec);

    // return true;
}

void PMTSD::resetPMTSD() {
    phoDetec = 0;
    kinEnergy = 0.;
}

void PMTSD::doPulse(G4double time) // const G4Track* track, G4double time)
{
    //  G4RootAnalysisManager *analysisManager = G4RootAnalysisManager::Instance();
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(0, (time / (1. * ns)));
    // pulseNumber++;
}
