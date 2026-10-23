#ifndef GLWaterSD_HH
#define GLWaterSD_HH

#include "G4VSensitiveDetector.hh"
#include "GLWaterHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;

class GLWaterSD : public G4VSensitiveDetector {
  public:
    GLWaterSD(G4String name);
    ~GLWaterSD();

    void Initialize(G4HCofThisEvent *);                      // override;
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *); // override;
    void EndOfEvent(G4HCofThisEvent *);

    // const std::map<G4int, G4double> &GetTrackEdepMap() const {
    //     return fTrackEdepMap;
    // }

  private:
    GLWaterHitsCollection *fWaterCollection;
    G4int fHitsCID;

    std::map<G4int, G4double> fTrackEdepMap; // Mapa para armazenar edep por track
};

#endif
