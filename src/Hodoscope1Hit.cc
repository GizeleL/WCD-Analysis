//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B5/src/Hodoscope1Hit.cc
/// \brief Implementation of the B5::Hodoscope1Hit class

#include "Hodoscope1Hit.hh"
// #include "GLDetectorConstruction.hh"

#include "G4AttDef.hh"
#include "G4AttDefStore.hh"
#include "G4AttValue.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<Hodoscope1Hit> *Hodoscope1HitAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
Hodoscope1Hit::Hodoscope1Hit()
    //: ColumnID(0.)
    //, RowID(0.)
    //: fTime(0.)
    : fPhysVolume(nullptr) {}
*/
// new
Hodoscope1Hit::Hodoscope1Hit()
    : fPhysVolume(nullptr),
      ColumnID(-1),
      RowID(-1),
      fEdep(0.),
      Time(0.),
      particleName("") {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Hodoscope1Hit::Hodoscope1Hit(G4VPhysicalVolume *volume)
    : fPhysVolume(volume) {}

Hodoscope1Hit::~Hodoscope1Hit() {}
/*
Hodoscope1Hit::Hodoscope1Hit(const Hodoscope1Hit &right)
    : G4VHit() {
    ColumnID = right.ColumnID;
    RowID = right.RowID;
    Time = right.Time;
    particleName = right.particleName;
}
*/
// new
Hodoscope1Hit::Hodoscope1Hit(const Hodoscope1Hit &right)
    : G4VHit() {
    ColumnID = right.ColumnID;
    RowID = right.RowID;
    fEdep = right.fEdep;
    Time = right.Time;
    particleName = right.particleName;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
const Hodoscope1Hit &Hodoscope1Hit::operator=(const Hodoscope1Hit &right) {
    ColumnID = right.ColumnID;
    RowID = right.RowID;
    Time = right.Time;
    particleName = right.particleName;
    return *this;
}
*/
// new
const Hodoscope1Hit &Hodoscope1Hit::operator=(const Hodoscope1Hit &right) {
    ColumnID = right.ColumnID;
    RowID = right.RowID;
    fEdep = right.fEdep;
    Time = right.Time;
    particleName = right.particleName;
    return *this;
}

G4bool Hodoscope1Hit::operator==(const Hodoscope1Hit &right) const {
    return (this == &right) ? true : false;
    // returns false because there currently isn't need to check for equality
}

// G4bool Hodoscope1Hit::operator==(const Hodoscope1Hit &right) const
//{
//   return ( fColumnID==right.fColumnID && fRowID==right.fRowID  && ftime==right.ftime);
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void Hodoscope1Hit::Draw()
//{
//   auto visManager = G4VVisManager::GetConcreteInstance();
//   if (! visManager || (fEdep==0.)) return;

// Draw a calorimeter cell with depth propotional to the energy deposition
//  G4Transform3D trans(fRot.inverse(),fPos);
//  G4VisAttributes attribs;
//  G4Colour colour(1.,0.,0.);
//  attribs.SetColour(colour);
//  attribs.SetForceSolid(true);
//  G4Box box("dummy",15.*cm,15.*cm,1.*m*fEdep/(0.1*GeV));
//  visManager->Draw(box,attribs,trans);
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// const std::map<G4String,G4AttDef>* Hodoscope1Hit::GetAttDefs() const
//{
//   G4bool isNew;
//   auto store = G4AttDefStore::GetInstance("Hodoscope1Hit",isNew);

// if (isNew) {
//   (*store)["HitType"]
//     = G4AttDef("HitType","Hit Type","Physics","","G4String");

// (*store)["Column"]
//   = G4AttDef("Column","Column ID","Physics","","G4int");

// (*store)["Row"]
//   = G4AttDef("Row","Row ID","Physics","","G4int");

// (*store)["Energy"]
//   = G4AttDef("Energy","Energy Deposited","Physics","G4BestUnit",
//              "G4double");

//  (*store)["Pos"]
//    = G4AttDef("Pos", "Position", "Physics","G4BestUnit",
//               "G4ThreeVector");
//}
// return store;
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// std::vector<G4AttValue>* Hodoscope1Hit::CreateAttValues() const
//{
//   auto values = new std::vector<G4AttValue>;

// values
//->push_back(G4AttValue("HitType","Hodoscope1Hit",""));
// values
//->push_back(G4AttValue("Column",G4UIcommand::ConvertToString(fColumnID),
//                        ""));
// values
//->push_back(G4AttValue("Row",G4UIcommand::ConvertToString(fRowID),""));
// values
//   ->push_back(G4AttValue("Energy",G4BestUnit(fEdep,"Energy"),""));
// values
//   ->push_back(G4AttValue("Pos",G4BestUnit(fPos,"Length"),""));

//  return values;
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void Hodoscope1Hit::Print()
//{
//   G4cout << "  Cell[" << fRowID << ", " << fColumnID << "] "
//     << G4endl;
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
