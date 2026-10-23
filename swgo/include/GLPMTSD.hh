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

  private:
    PMTHit *fPMTHit;
    G4int fPhotonCount;
    G4String fPMTName;
};

#endif
/*
#ifndef PMTSD_HH
#define PMTSD_HH
// Geant4 Libraries
//#include "G4DataVector.hh"
//#include "G4VSensitiveDetector.hh"
#include "G4Track.hh"

// Local Libraries
//
#include "GLPMTHit.hh"

class G4Step;
class G4HCofThisEvent;


class PMTSD //: public G4VSensitiveDetector
{

  public:
    PMTSD();//G4String name);
    virtual ~PMTSD();
    G4int ProcessHits(const G4Step* aStep, G4double time);
    void resetPMTSD();
    G4double getPhoDetected()
    {
      return phoDetec;
    }


  private:
   PMTHit *phoHit;
   G4int pulseNumber;
   G4int phoDetec;
   G4double kinEnergy;
   void doPulse(G4double time);//const G4Track* track, G4double time);
};
#endif
*/