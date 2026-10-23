#ifndef GLWORLD_HH
#define GLWORLD_HH

// Geant4 Libraries
//
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"

class world {
  public:
    world();
    virtual ~world();
    void DefineMaterials();
    void buildDetector(G4bool *overLaps);
    G4LogicalVolume *getLogVolume();
    G4VPhysicalVolume *getPhysVolume();

    G4double dimenWorld = 6.5 * m;

  private:
    G4Material *expHall_mat;

    G4Box *expHall_geo;
    G4LogicalVolume *expHall_log;
    G4VPhysicalVolume *expHall_phys;

    G4Element *fH;
    G4Element *fC;
    G4Element *fN;
    G4Element *fO;
    G4Material *fAir;
};
#endif
