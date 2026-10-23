#ifndef wcdpmt_HH
#define wcdpmt_HH

// Geant4 Libraries
//
#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"

// Local Libraries
//

class wcdpmt {
  public:
    wcdpmt();
    virtual ~wcdpmt();
    void DefineMaterials();
    void buildDetector(G4LogicalVolume *log_mother, G4double postZ, G4bool *overLaps);
    G4VPhysicalVolume *getPhysVolume();
    G4LogicalVolume *getLogVolume();

  private:
    G4Material *pmt_mat;
    G4Ellipsoid *pmt_geo;
    G4LogicalVolume *pmt_log;
    G4VPhysicalVolume *pmt_phy;

    G4Element *fH;
    G4Element *fC;
    G4Element *fN;
    G4Element *fO;
    G4Material *fAir;
};
#endif
