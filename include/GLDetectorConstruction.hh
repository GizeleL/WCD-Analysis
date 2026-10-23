#ifndef GLDETECTORCONSTRUCTION_HH
#define GLDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"

#include "G4Box.hh"
#include "G4Cache.hh"
#include "G4Element.hh"
#include "G4Ellipsoid.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"

#include "globals.hh"

// Local Libraries
//
#include "GLDetectorMessenger.hh"
#include "GLWorld.hh"
#include "GLwcdPMT1.hh"
#include "GLwcdPMT2.hh"
#include "GLwcdPMT3.hh"
#include "GLwcdPMT4.hh"
#include "GLworldGround.hh"
#include "grdFloor.hh"

class G4LogicalVolume;
class Hodoscope1SD;

class GLDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    GLDetectorConstruction();
    virtual ~GLDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

    // void ConstructSDandField() override;

    G4VPhysicalVolume *GetWaterVolume() const {
        return fwaterVolume;
    }

    G4VPhysicalVolume *GetExpHall() const {
        return expHall->getPhysVolume();
    }

    G4double wcdRadius;
    G4double wcdHight;
    G4ThreeVector dims;
    G4double d_mtl;
    G4int nx, ny, nz;
    G4int fNx;
    G4int fNy;
    G4int fNz;

    G4double outerRadius_pmt;
    G4bool b;
    G4double r;
    G4int n;
    G4double y;
    G4int save;

    void setWcdRadius(G4double wcdR);
    void setWcdHight(G4double wcdH);

    void SetDefaults();

    void SetDimensions(G4ThreeVector dims);

    G4double GetScintX() const {
        //  fScint_x = wcdRadius;
        return fScint_x;
    }
    G4double GetScintY() const {
        //  fScint_y = wcdRadius;
        return fScint_y;
    }
    G4double GetScintZ() const {
        //  fScint_z = wcdHight;
        return fScint_z;
    }
    G4double GetNFibers() const {
        //  fNfibers = 15;
        return fNfibers;
    }
    G4double GetSlabZ() const {
        //  fSlab_z = 2.55 * mm;
        return fNfibers;
    }

    void GetSlabZ(G4double fz);

    G4double fScint_x;
    G4double fScint_y;
    G4double fScint_z;
    G4double fSlab_z;
    G4double fNfibers;

    G4Box *hodoscope1Solid;
    G4LogicalVolume *fHodoscope1Logical;

    G4Box *hodoscope1ColumnSolid;
    G4LogicalVolume *fHodoscope1ColumnLogical;

    G4Box *hodoscope1CellSolid;
    G4LogicalVolume *fHodoscope1CellLogical;

    G4Box *hodoscope2Solid;
    G4LogicalVolume *fHodoscope2Logical;

    G4Box *hodoscope2ColumnSolid;
    G4LogicalVolume *fHodoscope2ColumnLogical;

    G4Box *hodoscope2CellSolid;
    G4LogicalVolume *fHodoscope2CellLogical;

    G4Box *hodoscope3Solid;
    G4LogicalVolume *fHodoscope3Logical;

    G4Box *hodoscope3ColumnSolid;
    G4LogicalVolume *fHodoscope3ColumnLogical;

    G4Box *hodoscope3CellSolid;
    G4LogicalVolume *fHodoscope3CellLogical;

    G4Box *hodoscope4Solid;
    G4LogicalVolume *fHodoscope4Logical;

    G4Box *hodoscope4ColumnSolid;
    G4LogicalVolume *fHodoscope4ColumnLogical;

    G4Box *hodoscope4CellSolid;
    G4LogicalVolume *fHodoscope4CellLogical;

    G4Box *hodoscope5Solid;
    G4LogicalVolume *fHodoscope5Logical;

    G4Box *hodoscope5ColumnSolid;
    G4LogicalVolume *fHodoscope5ColumnLogical;

    G4Box *hodoscope5CellSolid;
    G4LogicalVolume *fHodoscope5CellLogical;
    // G4double fD_mtl;

  private:
    G4double xWorld, yWorld, zWorld;

    world *expHall;
    worldGround *groundBase;
    grdFloor *grd;

    G4Material *tank_polietileno;
    G4Tubs *tank_geo;
    G4LogicalVolume *tank_log;
    G4VPhysicalVolume *tank_phys;

    G4Material *wcdWater;
    G4Tubs *water_geo;
    G4LogicalVolume *water_log;
    G4VPhysicalVolume *water_phys;

    wcdpmt *pmt_det;
    wcdpmt2 *pmt_det2;
    wcdpmt3 *pmt_det3;

    // ...
    wcdpmt4 *pmt_det4;
    G4VPhysicalVolume *fwaterVolume;

    G4Material *vacuum;

    G4VPhysicalVolume *ConstructDetector();

    GLDetectorMessenger *fDetectorMessenger;

    G4bool checkOverlaps;

    //***Elements
    G4Element *fH;
    G4Element *fC;
    G4Element *fN;
    G4Element *fO;
    G4Element *fF;

    G4Material *fPolyethylene;
    G4Material *fPethylene1;

    // G4Cache<WaterSD *> fScint_SD;
    G4Cache<Hodoscope1SD *> fHodoscope1CollID;
};

#endif