#ifndef wcdpmt2_h
#define wcdpmt2_h 1

// Geant4 Libraries
//
#include "G4Element.hh"
#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"

// Local Libraries
//

class wcdpmt2 {
  public:
    wcdpmt2();
    virtual ~wcdpmt2();
    void DefineMaterials();
    void buildDetector(G4LogicalVolume *log_mother, G4double postZ, G4bool *overLaps);
    G4VPhysicalVolume *getPhysVolume();
    G4LogicalVolume *getLogVolume();

  private:
    G4Material *pmt_mat2;
    G4Ellipsoid *pmt_geo2;
    G4LogicalVolume *pmt_log2;
    G4VPhysicalVolume *pmt_phy2;

    G4Element *fH;
    G4Element *fC;
    G4Element *fN;
    G4Element *fO;
    G4Material *fAir;
};
#endif
