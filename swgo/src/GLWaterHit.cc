#include "GLWaterHit.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<GLWaterHit> *GLWaterHitAllocator = nullptr;

GLWaterHit::GLWaterHit()
    : fEdep(0.),
      fPos(0.),
      fTime(0.) {}

GLWaterHit::GLWaterHit(G4VPhysicalVolume *pVol)
    : fPhysVol(pVol) {}

GLWaterHit::~GLWaterHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GLWaterHit::GLWaterHit(const GLWaterHit &right)
    : G4VHit() {
    fEdep = right.fEdep;
    fPos = right.fPos;
    fPhysVol = right.fPhysVol;
    fTime = right.fTime;

    fNumberSecondary = right.fNumberSecondary;
    particleName = right.particleName;
    secondaryname = right.secondaryname;
    process = right.process;

    secondaryenergy_electron_sum = right.secondaryenergy_electron_sum;
    secondaryelectron_count = right.secondaryelectron_count;
    secondaryenergy_cerenkov_sum = right.secondaryenergy_cerenkov_sum;
    secondarycerenkov_count = right.secondarycerenkov_count;

    secondaryenergy_scintillation_sum = right.secondaryenergy_scintillation_sum;
    secondaryscintillation_count = right.secondaryscintillation_count;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const GLWaterHit &GLWaterHit::operator=(const GLWaterHit &right) {
    fEdep = right.fEdep;
    fPos = right.fPos;
    fPhysVol = right.fPhysVol;
    fTime = right.fTime;

    fNumberSecondary = right.fNumberSecondary;
    particleName = right.particleName;
    secondaryname = right.secondaryname;
    process = right.process;

    secondaryenergy_electron_sum = right.secondaryenergy_electron_sum;
    secondaryelectron_count = right.secondaryelectron_count;
    secondaryenergy_cerenkov_sum = right.secondaryenergy_cerenkov_sum;
    secondarycerenkov_count = right.secondarycerenkov_count;

    secondaryenergy_scintillation_sum = right.secondaryenergy_scintillation_sum;
    secondaryscintillation_count = right.secondaryscintillation_count;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool GLWaterHit::operator==(const GLWaterHit &right) const {
    return (this == &right) ? true : false;
    // returns false because there currently isn't need to check for equality
}
