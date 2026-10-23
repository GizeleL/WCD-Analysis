#ifndef GLwcdPMT4_HH
#define GLwcdPMT4_HH

#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"

class wcdpmt4 {
  public:
    wcdpmt4();
    ~wcdpmt4();
    void DefineMaterials();
    void buildDetector(G4LogicalVolume *log_mother, G4double postZ, G4bool *overLaps);
    G4VPhysicalVolume *getPhysVolume();
    G4LogicalVolume *getLogVolume();

  private:
    G4Ellipsoid *pmt_geo4;
    G4LogicalVolume *pmt_log4;
    G4VPhysicalVolume *pmt_phy4;
    G4Material *fAir;
};

#endif