// Geant4 Libraries
//
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"

// Local Libraries
//
#include "../include/GLWorld.hh"

world::world() {
    G4cout << "...Creating world..." << G4endl;

    // Initializing for mechanical detector
    //
    expHall_geo = NULL;
    expHall_log = NULL;
    expHall_phys = NULL;
}

world::~world() {}

void world::DefineMaterials() {
    // G4NistManager *nist = G4NistManager::Instance();

    // expHall_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4double a; // atomic mass
    G4double z; // atomic number
    G4double density;

    //***Elements
    fH = new G4Element("H", "H", z = 1., a = 1.01 * g / mole);
    fC = new G4Element("C", "C", z = 6., a = 12.01 * g / mole);
    fN = new G4Element("N", "N", z = 7., a = 14.01 * g / mole);
    fO = new G4Element("O", "O", z = 8., a = 16.00 * g / mole);
    fAir = new G4Material("Air", density = 1.29 * mg / cm3, 2);

    fAir->AddElement(fN, 70 * perCent);
    fAir->AddElement(fO, 30 * perCent);
}

void world::buildDetector(G4bool *overLaps) {
    G4double dimenWorld = 6.5 * m;
    expHall_geo =
        new G4Box("expHall_geo",
                  dimenWorld,
                  dimenWorld,
                  dimenWorld);

    expHall_log =
        new G4LogicalVolume(expHall_geo,
                            fAir,
                            "expHall_log",
                            0,
                            0,
                            0);

    expHall_phys =
        new G4PVPlacement(0,
                          G4ThreeVector(0. * cm, 0. * cm, 0. * cm),
                          expHall_log,
                          "expHall",
                          0,
                          false,
                          0,
                          overLaps);

    expHall_log->SetVisAttributes(G4VisAttributes::GetInvisible());
}

G4LogicalVolume *world::getLogVolume() {
    return expHall_log;
}

G4VPhysicalVolume *world::getPhysVolume() {
    return expHall_phys;
}
