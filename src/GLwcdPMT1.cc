// Geant4 Libraries
//
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
#include "GLwcdPMT1.hh"

using namespace std;

wcdpmt::wcdpmt() {
    G4cout << "...pmt1 is OK..." << G4endl;

    // Initializing for mechanical detector
    //
    pmt_geo = NULL;
    pmt_log = NULL;
    pmt_phy = NULL;
}

wcdpmt::~wcdpmt() {}

void wcdpmt::DefineMaterials() {

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

    G4NistManager *nist = G4NistManager::Instance();
    fAir = nist->FindOrBuildMaterial("G4_AIR");
}

void wcdpmt::buildDetector(G4LogicalVolume *log_mother, G4double postZ, G4bool *overLaps) {

    G4double pxSemiAxis = 11.25 * cm;
    G4double pySemiAxis = 11.25 * cm;
    G4double pzSemiAxis = 10.5 * cm;
    G4double pzBottomCut = -pzSemiAxis;
    G4double pzTopCut = 0. * cm;

    G4double theta1 = (3.14159 * 0.) / 180.;

    pmt_geo = new G4Ellipsoid("pmt_geo",
                              pxSemiAxis,
                              pySemiAxis,
                              pzSemiAxis,
                              pzBottomCut,
                              pzTopCut);

    pmt_log = new G4LogicalVolume(pmt_geo,
                                  fAir,
                                  pmt_geo->GetName());

    G4RotationMatrix *rotMat = new G4RotationMatrix();
    rotMat->rotateX(180 * deg);
    rotMat->rotateY(0 * deg);
    rotMat->rotateZ(0 * deg);

    pmt_phy = new G4PVPlacement(rotMat,
                                // G4ThreeVector(-140. * sin(theta1) * cm, -140. * cos(theta1) * cm, -postZ / 2.), // 60.*cm),//45.*cm),//80.*cm),//295.*cm),//60.*cm),
                                G4ThreeVector(-140. * sin(theta1) * cm, -140. * cos(theta1) * cm, -(postZ / 2. - 11. * cm)),
                                pmt_log,
                                pmt_log->GetName(),
                                log_mother,
                                false,
                                0,
                                overLaps);

    G4Color Color_pmt(G4Colour(0.45, 0.25, 0.0, 1.));
    G4VisAttributes *pmt1_va = new G4VisAttributes(Color_pmt);
    pmt_log->SetVisAttributes(new G4VisAttributes(pmt1_va));
    pmt1_va->SetForceSolid(true);
}

G4VPhysicalVolume *wcdpmt::getPhysVolume() {
    return pmt_phy;
}

G4LogicalVolume *wcdpmt::getLogVolume() {
    return pmt_log;
}
