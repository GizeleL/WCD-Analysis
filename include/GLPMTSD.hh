#ifndef PMTSD_HH
#define PMTSD_HH

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4VSensitiveDetector.hh"
#include "GLPMTHit.hh"

class PMTSD : public G4VSensitiveDetector {
  public:
    PMTSD(G4String name);
    virtual ~PMTSD();

    virtual void Initialize(G4HCofThisEvent *hitsCE) override;
    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;
    virtual void EndOfEvent(G4HCofThisEvent *hitsCE) override;

    G4int GetPhotonCount() const { return fPhotonCount; }
    void ResetCount() { fPhotonCount = 0; }

    PMTHit *GetPMTHit() const { return fPMTHit; }
    void IncrementPhotonCount() { fPhotonCount++; }

  private:
    PMTHit *fPMTHit;
    G4int fPhotonCount;
    G4String fPMTName;
};

#endif