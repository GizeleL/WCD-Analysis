#include "GLwcdPMT4.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"

using namespace std;

wcdpmt4::wcdpmt4() {
    G4cout << "...pmt4 is OK..." << G4endl;
    pmt_geo4 = NULL;
    pmt_log4 = NULL;
    pmt_phy4 = NULL;
}

wcdpmt4::~wcdpmt4() {}

void wcdpmt4::DefineMaterials() {
    G4NistManager *nist = G4NistManager::Instance();
    fAir = nist->FindOrBuildMaterial("G4_AIR");
    // fAir = nist->FindOrBuildMaterial("G4_Pyrex_Glass"); // era G4_AIR
    // fAir = nist->FindOrBuildMaterial("G4_WATER"); // índice igual à água
}

void wcdpmt4::buildDetector(G4LogicalVolume *log_mother, G4double postZ, G4bool *overLaps) {
    G4double pxSemiAxis = 11.25 * cm;
    G4double pySemiAxis = 11.25 * cm;
    G4double pzSemiAxis = 10.5 * cm;
    G4double pzBottomCut = -pzSemiAxis;
    G4double pzTopCut = 0. * cm;

    pmt_geo4 = new G4Ellipsoid("pmt_geo4",
                               pxSemiAxis,
                               pySemiAxis,
                               pzSemiAxis,
                               pzBottomCut,
                               pzTopCut);

    pmt_log4 = new G4LogicalVolume(pmt_geo4,
                                   fAir,
                                   pmt_geo4->GetName());

    // original
    pmt_phy4 = new G4PVPlacement(0,
                                 G4ThreeVector(0. * cm, 0. * cm, (postZ / 2. - 15. * cm)),
                                 pmt_log4,
                                 pmt_log4->GetName(),
                                 log_mother,
                                 false,
                                 0,
                                 overLaps);

    G4Color Color_pmt(G4Colour(0.45, 0.25, 0.0, 1.));
    G4VisAttributes *pmt4_va = new G4VisAttributes(Color_pmt);
    pmt_log4->SetVisAttributes(new G4VisAttributes(pmt4_va));
    pmt4_va->SetForceSolid(true);
}

G4VPhysicalVolume *wcdpmt4::getPhysVolume() {
    return pmt_phy4;
}

G4LogicalVolume *wcdpmt4::getLogVolume() {
    return pmt_log4;
}
