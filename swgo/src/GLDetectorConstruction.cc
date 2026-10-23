#include "GLDetectorConstruction.hh"
#include "GLDetectorMessenger.hh"
#include "GLWaterHit.hh"
#include "GLWaterSD.hh"

#include "GLPMTSD.hh"
#include "GLWorld.hh"
#include "GLwater.hh"
#include "GLwcdPMT1.hh"
#include "GLwcdPMT2.hh"
#include "GLwcdPMT3.hh"
#include "GLworldGround.hh"
#include "grdFloor.hh"

#include "G4Color.hh"
#include "G4GeometryManager.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"

#include "LXeWLSSlab.hh"

GLDetectorConstruction::GLDetectorConstruction() : G4VUserDetectorConstruction() {
    // Construct();
    G4cout << " \n"
           << "GLDetectorConstruction ... is ready! \n"
           << G4endl;

    // dimenWorld = 6.5 m
    //
    // fD_mtl = 0.1000 * m;
    // fScint_x = 3.4000 / 2. * m; => 1.7
    // fScint_y = 3.4000 / 2. * m;
    // fScint_z = 1.8787 / 2 * m; => 0.873

    // // conferido
    // fOuterRadius_pmt = 101. * mm;

    expHall = new world();
    groundBase = new worldGround();
    grd = new grdFloor();

    water *tmp = new water();
    wcdWater = tmp->doWater();
    wcdWater->SetMaterialPropertiesTable(tmp->doOpwater());

    pmt_det = new wcdpmt();
    pmt_det2 = new wcdpmt2();
    pmt_det3 = new wcdpmt3();

    // conferido
    wcdRadius = 170. * cm;
    wcdHight = 95. * cm;

    // wcdRadius = 160. * cm;
    // wcdHight = 114. * cm;

    checkOverlaps = true;

    fDetectorMessenger = new GLDetectorMessenger(this);
};

GLDetectorConstruction::~GLDetectorConstruction() {
    delete fDetectorMessenger;
};

G4VPhysicalVolume *GLDetectorConstruction::Construct() {
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    G4LogicalSkinSurface::CleanSurfaceTable();
    G4LogicalBorderSurface::CleanSurfaceTable();

    return ConstructDetector();
}

G4VPhysicalVolume *GLDetectorConstruction::ConstructDetector() {
    // G4NistManager *nist = G4NistManager::Instance();

    G4double a; // atomic mass
    G4double z; // atomic number
    G4double density;

    G4int polyPMMA = 1;
    G4int nC_PMMA = 3 + 2 * polyPMMA;
    G4int nH_PMMA = 6 + 2 * polyPMMA;

    G4int polyeth = 1;
    G4int nC_eth = 2 * polyeth;
    G4int nH_eth = 4 * polyeth;

    //***Elements
    fH = new G4Element("H", "H", z = 1., a = 1.01 * g / mole);
    fC = new G4Element("C", "C", z = 6., a = 12.01 * g / mole);
    fN = new G4Element("N", "N", z = 7., a = 14.01 * g / mole);
    fO = new G4Element("O", "O", z = 8., a = 16.00 * g / mole);
    fF = new G4Element("F", "F", z = 8., a = 16.00 * g / mole);

    fPolyethylene = new G4Material("Polyethylene", 1.200 * g / cm3, 2); // defining material object
    fPolyethylene->AddElement(fH, 4);                                   // adding the hydrogen element to object
    fPolyethylene->AddElement(fC, 2);
    // Cladding(polyethylene)
    fPethylene1 = new G4Material("Pethylene1", density = 1200. * kg / m3, 2);
    fPethylene1->AddElement(fH, nH_eth);
    fPethylene1->AddElement(fC, nC_eth);

    // new G4Material("Galactic", z = 1., a = 1.01 * g / mole, density = universe_mean_density,
    //              kStateGas, 2.73 * kelvin, 3.e-18 * pascal);
    // G4_Galactic or

    G4Material *vacuum = new G4Material("Vacuum", z = 7., a = 14.007 * g / mole, density = 0.001 * g / cm3);

    // tank_polietileno = nist->FindOrBuildMaterial("G4_POLYETHYLENE"); // G4_STAINLESS-STEEL

    expHall->DefineMaterials();
    expHall->buildDetector(&checkOverlaps);

    groundBase->DefineMaterials();
    groundBase->buildDetector(expHall->getLogVolume(), &checkOverlaps);

    G4double half_wdcHight = wcdHight / 2.;

    G4double Z_water = half_wdcHight * cm;
    G4double Z_tank = half_wdcHight + (.05) * cm;
    G4double Z_scint = half_wdcHight + (1.6) * cm; // out overlap
    G4double Z_rpc = -(wcdHight / 2. + (.05) * cm);

    G4cout << "Z_water: " << Z_water << " cm";
    G4cout << "Z_tank: " << Z_tank << " cm";
    G4cout << "Z_scint: " << Z_scint << " cm";
    G4cout << "Z_rpc: " << Z_rpc << " cm";

    tank_geo = NULL;
    tank_log = NULL;
    tank_phys = NULL;

    ////////// TANQUE //////////////////////////////
    tank_geo =
        new G4Tubs("wcdTank",
                   0. * cm,
                   wcdRadius + 10 * cm, // 48.1*cm, //105.1*cm,
                   Z_tank,              // 31.05*cm, //45.05*cm,
                   0. * deg,
                   360. * deg);

    tank_log =
        new G4LogicalVolume(tank_geo,
                            fPolyethylene,
                            tank_geo->GetName(),
                            0,
                            0,
                            0);

    tank_phys =
        new G4PVPlacement(0,
                          G4ThreeVector(0. * cm, 0. * cm, 1. * cm),
                          tank_log,
                          tank_log->GetName(),
                          groundBase->getLogVolume(),
                          false,
                          0,
                          checkOverlaps);

    //  tank_log->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
    G4Color transparentColor_tank(0.8, 0.8, 0.8, 0.5);
    G4VisAttributes *tank_va = new G4VisAttributes(transparentColor_tank);
    // tank_va->SetForceSolid(true);
    tank_log->SetVisAttributes(tank_va);

    ////////// AGUA //////////////////////////////
    water_geo =
        new G4Tubs("watervol",
                   0. * cm,       // inner radio
                   wcdRadius,     // 48.*cm, //105.*cm, //outer radio
                   wcdHight / 2., // 31.*cm, //45.*cm,  //High
                   0. * deg,
                   360. * deg);

    water_log =
        new G4LogicalVolume(water_geo,
                            wcdWater,
                            water_geo->GetName(),
                            0,
                            0,
                            0);

    water_phys =
        new G4PVPlacement(0,
                          G4ThreeVector(0. * cm, 0. * cm, 0. * cm),
                          water_log,
                          water_log->GetName(),
                          tank_log,
                          false,
                          0,
                          checkOverlaps);

    GLWaterSD *waterSD = new GLWaterSD("/WaterSD");
    G4SDManager *sdman = G4SDManager::GetSDMpointer();
    sdman->AddNewDetector(waterSD);
    water_log->SetSensitiveDetector(waterSD);

    //  water_log->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));

    G4Color transparentColor_water(0.0, 0.0, 1.0, 0.8);
    G4VisAttributes *water_va = new G4VisAttributes(transparentColor_water);
    water_va->SetForceSolid(true);
    water_log->SetVisAttributes(water_va);

    // ============================
    // *** Set Tyvek as coating ***
    G4OpticalSurface *opWaterSurface = new G4OpticalSurface("OptTyvek");

    opWaterSurface->SetType(dielectric_LUT);
    opWaterSurface->SetFinish(groundtyvekair);
    opWaterSurface->SetModel(LUT);

    new G4LogicalBorderSurface(
        "WaterTyvekTank",
        water_phys,
        tank_phys,
        opWaterSurface);

    pmt_det->DefineMaterials();
    pmt_det->buildDetector(water_log, wcdHight, &checkOverlaps);

    pmt_det2->DefineMaterials();
    pmt_det2->buildDetector(water_log, wcdHight, &checkOverlaps);

    pmt_det3->DefineMaterials();
    pmt_det3->buildDetector(water_log, wcdHight, &checkOverlaps);

    fwaterVolume = water_phys;

    grd->DefineMaterials();
    grd->buildDetector(wcdHight, groundBase->getLogVolume(), &checkOverlaps);

    //! Scintillator bars

    G4bool checkOverlaps = true;

    //* hodoscope1 above (center)
    hodoscope1Solid = new G4Box("hodoscope1Box", 80 * cm, 80 * cm, 1 * cm);
    fHodoscope1Logical = new G4LogicalVolume(hodoscope1Solid, fPethylene1, "hodoscope1Logical");
    new G4PVPlacement(nullptr, G4ThreeVector(0., 0., Z_scint + 5.), fHodoscope1Logical,
                      "hodoscope1Physical", groundBase->getLogVolume(), false, 0, checkOverlaps);

    fHodoscope1Logical->SetVisAttributes(G4Colour(1, 0, 0));

    G4int kNofHodoscopeColumns = 32;

    //* hodoscope1 column
    hodoscope1ColumnSolid = new G4Box("hodoscope1ColumnBox", 2.5 * cm, 80 * cm, 1 * cm);
    fHodoscope1ColumnLogical = new G4LogicalVolume(hodoscope1ColumnSolid, fPethylene1, "hodoscope1ColumnLogical");
    new G4PVReplica("hodoscope1ColumnPhysical", fHodoscope1ColumnLogical,
                    fHodoscope1Logical, kXAxis, kNofHodoscopeColumns, 5 * cm);

    fHodoscope1ColumnLogical->SetVisAttributes(G4Colour(1, 0, 0));

    G4int kNofHodoscopeRows = 32;

    //* hodoscope1 cell
    hodoscope1CellSolid = new G4Box("hodoscope1CellBox", 2.5 * cm, 2.5 * cm, 1 * cm);
    fHodoscope1CellLogical = new G4LogicalVolume(hodoscope1CellSolid, fPethylene1, "hodoscope1CellLogical");
    new G4PVReplica("hodoscope1CellPhysical", fHodoscope1CellLogical,
                    fHodoscope1ColumnLogical, kYAxis, kNofHodoscopeRows, 5 * cm);

    fHodoscope1CellLogical->SetVisAttributes(G4Colour(1, 0, 0));

    // ============================
    // *** Set Tyvek as coating ***
    G4OpticalSurface *opScintillator = new G4OpticalSurface("OptTyvek");

    opWaterSurface->SetType(dielectric_LUT);
    opWaterSurface->SetFinish(groundtyvekair);
    opWaterSurface->SetModel(LUT);

    //! RPCs pads

    //* hodoscope2 below (canto direito superior)
    hodoscope2Solid = new G4Box("hodoscope2Box", 76 * cm, 60 * cm, 1 * cm);
    fHodoscope2Logical = new G4LogicalVolume(hodoscope2Solid, fPethylene1, "hodoscope2Logical");
    new G4PVPlacement(nullptr, G4ThreeVector(83 * cm, 66 * cm, Z_rpc), fHodoscope2Logical,
                      "hodoscope2Physical", groundBase->getLogVolume(), "hodoscope2", 0, checkOverlaps);

    G4int kNofHodoscope2Columns = 8;

    //* hodoscope2 column
    hodoscope2ColumnSolid = new G4Box("hodoscope2ColumnBox", 9.5 * cm, 60 * cm, 1 * cm);
    fHodoscope2ColumnLogical = new G4LogicalVolume(hodoscope2ColumnSolid, fPethylene1, "hodoscope2ColumnLogical");
    new G4PVReplica("hodoscope2ColumnPhysical", fHodoscope2ColumnLogical,
                    fHodoscope2Logical, kXAxis, kNofHodoscope2Columns, 19 * cm);

    G4int kNofHodoscope2Rows = 8;

    //*hodoscope2 cell
    hodoscope2CellSolid = new G4Box("hodoscope2CellBox", 9.5 * cm, 7.5 * cm, 1 * cm);
    fHodoscope2CellLogical = new G4LogicalVolume(hodoscope2CellSolid, fPethylene1, "hodoscope2CellLogical");
    new G4PVReplica("hodoscope2CellPhysical", fHodoscope2CellLogical,
                    fHodoscope2ColumnLogical, kYAxis, kNofHodoscope2Rows, 15 * cm);

    fHodoscope2CellLogical->SetVisAttributes(G4Colour(1, 0, 0));

    //*hodoscope3 below (canto esquerdo inferior)
    hodoscope3Solid = new G4Box("hodoscope3Box", 76 * cm, 60 * cm, 1 * cm);
    fHodoscope3Logical = new G4LogicalVolume(hodoscope3Solid, fPethylene1, "hodoscope3Logical");
    new G4PVPlacement(nullptr, G4ThreeVector(-83 * cm, -66 * cm, Z_rpc), fHodoscope3Logical,
                      "hodoscope3Physical", groundBase->getLogVolume(), "hodoscope3", 0, checkOverlaps);

    G4int kNofHodoscope3Columns = 8;

    //*hodoscope3 column
    hodoscope3ColumnSolid = new G4Box("hodoscope3ColumnBox", 9.5 * cm, 60 * cm, 1 * cm);
    fHodoscope3ColumnLogical = new G4LogicalVolume(hodoscope3ColumnSolid, fPethylene1, "hodoscope3ColumnLogical");
    new G4PVReplica("hodoscope3ColumnPhysical", fHodoscope3ColumnLogical,
                    fHodoscope3Logical, kXAxis, kNofHodoscope3Columns, 19 * cm);

    G4int kNofHodoscope3Rows = 8;

    //*hodoscope3 cell
    hodoscope3CellSolid = new G4Box("hodoscope3CellBox", 9.5 * cm, 7.5 * cm, 1 * cm);
    fHodoscope3CellLogical = new G4LogicalVolume(hodoscope3CellSolid, fPethylene1, "hodoscope3CellLogical");
    new G4PVReplica("hodoscope3CellPhysical", fHodoscope3CellLogical,
                    fHodoscope3ColumnLogical, kYAxis, kNofHodoscope3Rows, 15 * cm);

    fHodoscope3CellLogical->SetVisAttributes(G4Colour(1, 0, 0));

    //*hodoscope4 below (canto direito inferior)
    hodoscope4Solid = new G4Box("hodoscope4Box", 76 * cm, 60 * cm, 1 * cm);
    fHodoscope4Logical = new G4LogicalVolume(hodoscope4Solid, fPethylene1, "hodoscope4Logical");
    new G4PVPlacement(nullptr, G4ThreeVector(83 * cm, -66 * cm, Z_rpc), fHodoscope4Logical,
                      "hodoscope4Physical", groundBase->getLogVolume(), "hodoscope4", 0, checkOverlaps);

    G4int kNofHodoscope4Columns = 8;

    //*hodoscope4 column
    hodoscope4ColumnSolid = new G4Box("hodoscope4ColumnBox", 9.5 * cm, 60 * cm, 1 * cm);
    fHodoscope4ColumnLogical = new G4LogicalVolume(hodoscope4ColumnSolid, fPethylene1, "hodoscope4ColumnLogical");
    new G4PVReplica("hodoscope4ColumnPhysical", fHodoscope4ColumnLogical,
                    fHodoscope4Logical, kXAxis, kNofHodoscope4Columns, 19 * cm);

    G4int kNofHodoscope4Rows = 8;

    //*hodoscope4 cell
    hodoscope4CellSolid = new G4Box("hodoscope4CellBox", 9.5 * cm, 7.5 * cm, 1 * cm);
    fHodoscope4CellLogical = new G4LogicalVolume(hodoscope4CellSolid, fPethylene1, "hodoscope4CellLogical");
    new G4PVReplica("hodoscope4CellPhysical", fHodoscope4CellLogical,
                    fHodoscope4ColumnLogical, kYAxis, kNofHodoscope4Rows, 15 * cm);

    fHodoscope4CellLogical->SetVisAttributes(G4Colour(1, 0, 0));

    //*hodoscope5 below (canto esquerdo superior)
    hodoscope5Solid = new G4Box("hodoscope5Box", 76 * cm, 60 * cm, 1 * cm);
    fHodoscope5Logical = new G4LogicalVolume(hodoscope5Solid, fPethylene1, "hodoscope5Logical");
    new G4PVPlacement(nullptr, G4ThreeVector(-83 * cm, 66 * cm, Z_rpc), fHodoscope5Logical,
                      "hodoscope5Physical", groundBase->getLogVolume(), "hodoscope5", 0, checkOverlaps);

    G4int kNofHodoscope5Columns = 8;

    //*hodoscope5 column
    hodoscope5ColumnSolid = new G4Box("hodoscope5ColumnBox", 9.5 * cm, 60 * cm, 1 * cm);
    fHodoscope5ColumnLogical = new G4LogicalVolume(hodoscope5ColumnSolid, fPethylene1, "hodoscope5ColumnLogical");
    new G4PVReplica("hodoscope5ColumnPhysical", fHodoscope5ColumnLogical,
                    fHodoscope5Logical, kXAxis, kNofHodoscope5Columns, 19 * cm);

    G4int kNofHodoscope5Rows = 8;

    //*hodoscope5 cell
    hodoscope5CellSolid = new G4Box("hodoscope5CellBox", 9.5 * cm, 7.5 * cm, 1 * cm);
    fHodoscope5CellLogical = new G4LogicalVolume(hodoscope5CellSolid, fPethylene1, "hodoscope5CellLogical");
    new G4PVReplica("hodoscope5CellPhysical", fHodoscope5CellLogical,
                    fHodoscope5ColumnLogical, kYAxis, kNofHodoscope5Rows, 15 * cm);

    fHodoscope5CellLogical->SetVisAttributes(G4Colour(1, 0, 0));

    return expHall->getPhysVolume();
}

void GLDetectorConstruction::setWcdRadius(G4double wcdR) {
    this->wcdRadius = wcdR;

    pmt_det->getLogVolume()->RemoveDaughter(pmt_det->getPhysVolume());
    delete pmt_det->getPhysVolume();
    pmt_det->buildDetector(water_log, wcdHight, &checkOverlaps);

    pmt_det2->getLogVolume()->RemoveDaughter(pmt_det->getPhysVolume());
    delete pmt_det2->getPhysVolume();
    pmt_det2->buildDetector(water_log, wcdHight, &checkOverlaps);

    pmt_det3->getLogVolume()->RemoveDaughter(pmt_det->getPhysVolume());
    delete pmt_det3->getPhysVolume();
    pmt_det3->buildDetector(water_log, wcdHight, &checkOverlaps);

    fwaterVolume = water_phys;

    grd->getLogVolume()->RemoveDaughter(grd->getPhysVolume());
    delete grd->getPhysVolume();
    grd->buildDetector(wcdHight, groundBase->getLogVolume(), &checkOverlaps);

    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GLDetectorConstruction::setWcdHight(G4double wcdH) {
    this->wcdHight = wcdH;

    pmt_det->getLogVolume()->RemoveDaughter(pmt_det->getPhysVolume());
    delete pmt_det->getPhysVolume();
    pmt_det->buildDetector(water_log, wcdHight, &checkOverlaps);

    pmt_det2->getLogVolume()->RemoveDaughter(pmt_det->getPhysVolume());
    delete pmt_det2->getPhysVolume();
    pmt_det2->buildDetector(water_log, wcdHight, &checkOverlaps);

    pmt_det3->getLogVolume()->RemoveDaughter(pmt_det->getPhysVolume());
    delete pmt_det3->getPhysVolume();
    pmt_det3->buildDetector(water_log, wcdHight, &checkOverlaps);

    fwaterVolume = water_phys;

    grd->getLogVolume()->RemoveDaughter(grd->getPhysVolume());
    delete grd->getPhysVolume();
    grd->buildDetector(wcdHight, groundBase->getLogVolume(), &checkOverlaps);

    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

// void GLDetectorConstruction::ConstructSDandField() {

//     GLWaterSD *water = fSDWater.Get();
//     if (SDWater) {
//         G4cout << "Construction /swgo/detector/SDWater" << G4endl;

//         GLSDWater *water_SD = new GLWaterSD("/swgo/detector/GLWaterSD");
//         fSDWater.Put(water_SD);
//     }
// }

void GLDetectorConstruction::SetDimensions(G4ThreeVector dims) {
    fScint_x = dims[0];
    fScint_y = dims[1];
    fScint_z = dims[2];
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void GLDetectorConstruction::SetDefaults() {
    // Resets to default values
    // Conferido
    // fD_mtl = 0.1000 * m;
    // fScint_x = 3.4000 / 2. * m;
    // fScint_y = 3.4000 / 2. * m;
    // fScint_z = 1.8787 / 2 * m;

    fScint_x = 160 / 2. * cm;
    fScint_y = 160 / 2. * cm;
    fScint_z = wcdHight;

    // fNx = 1;
    // fNy = 1;
    // fNz = 1;

    // conferido
    // fOuterRadius_pmt = 101. * mm;
    // fD_mtl = 0.2000 * m;

    // fScint_x = 3.8000 * m;
    // fScint_y = 3.8000 * m;
    // fScint_z = 1.7226 * m;

    // fNx = 1;
    // fNy = 1;
    // fNz = 1;

    // fOuterRadius_pmt = 1.2000 * m;

    // fSphereOn = false;
    // fRefl = 1.0;

    fNfibers = 15;
    //  fWLSslab = false;
    // fMainVolumeOn = true;
    // fMainVolume = nullptr;
    fSlab_z = 2.5 * mm;

    // G4UImanager::GetUIpointer()->ApplyCommand(
    //     "/swgo/detector/scintYieldFactor 1.");

    // if (fLXe_mt)
    //     fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", 12000. / MeV);
    // if (fMPTPStyrene)
    //     fMPTPStyrene->AddConstProperty("SCINTILLATIONYIELD", 10. / keV);
}
