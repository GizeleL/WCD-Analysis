#ifndef wcdpmt3_HH
#define wcdpmt3_HH

// Geant4 Libraries
//
#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"

// Local Libraries
//

class wcdpmt3 {
  public:
    wcdpmt3();
    virtual ~wcdpmt3();
    void DefineMaterials();
    void buildDetector(G4LogicalVolume *log_mother, G4double postZ, G4bool *overLaps);
    G4VPhysicalVolume *getPhysVolume();
    G4LogicalVolume *getLogVolume();

  private:
    G4Material *pmt_mat3;
    G4Ellipsoid *pmt_geo3;
    G4LogicalVolume *pmt_log3;
    G4VPhysicalVolume *pmt_phy3;

    G4Element *fH;
    G4Element *fC;
    G4Element *fN;
    G4Element *fO;
    G4Material *fAir;
};
#endif
