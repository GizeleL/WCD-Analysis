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
#include "GLwcdPMT3.hh"

using namespace std;

wcdpmt3::wcdpmt3() {
    G4cout << "...pmt3 is OK..." << G4endl;

    // Initializing for mechanical detector
    //
    pmt_geo3 = NULL;
    pmt_log3 = NULL;
    pmt_phy3 = NULL;
}

wcdpmt3::~wcdpmt3() {}

void wcdpmt3::DefineMaterials() {
    // G4NistManager *nist = G4NistManager::Instance();

    // pmt_mat3 = nist->FindOrBuildMaterial("G4_AIR");

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

void wcdpmt3::buildDetector(G4LogicalVolume *log_mother, G4double postZ, G4bool *overLaps) {
    G4double pxSemiAxis = 11.25 * cm;
    G4double pySemiAxis = 11.25 * cm;
    G4double pzSemiAxis = 10.5 * cm;
    G4double pzBottomCut = -pzSemiAxis;
    G4double pzTopCut = 0. * cm;

    G4double theta1 = 3.14159 * 240. / 180.;

    pmt_geo3 = new G4Ellipsoid("pmt_geo3",
                               pxSemiAxis,
                               pySemiAxis,
                               pzSemiAxis,
                               pzBottomCut,
                               pzTopCut);

    pmt_log3 = new G4LogicalVolume(pmt_geo3,
                                   fAir,
                                   pmt_geo3->GetName());

    G4RotationMatrix *rotMat = new G4RotationMatrix();
    rotMat->rotateX(180 * deg);
    rotMat->rotateY(0 * deg);
    rotMat->rotateZ(0 * deg);

    pmt_phy3 = new G4PVPlacement(rotMat,
                                 // G4ThreeVector(-140. * sin(theta1) * cm, -140. * cos(theta1) * cm, -postZ / 2.),
                                 G4ThreeVector(-140. * sin(theta1) * cm, -140. * cos(theta1) * cm, -(postZ / 2. - 11. * cm)),
                                 pmt_log3,
                                 pmt_log3->GetName(),
                                 log_mother,
                                 false,
                                 0,
                                 overLaps);
    //   pmt_log3->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
    //  pmt_log3->SetForceSolid(true);
    G4Color Color_pmt(G4Colour(0.45, 0.25, 0.0, 1.));
    G4VisAttributes *pmt3_va = new G4VisAttributes(Color_pmt);
    pmt_log3->SetVisAttributes(new G4VisAttributes(pmt3_va));
    pmt3_va->SetForceSolid(true);
}

G4VPhysicalVolume *wcdpmt3::getPhysVolume() {
    return pmt_phy3;
}

G4LogicalVolume *wcdpmt3::getLogVolume() {
    return pmt_log3;
}
