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
/// \file B5/include/Hodoscope1Hit.hh
/// \brief Definition of the B5::Hodoscope1Hit class

#ifndef Hodoscope1Hit_h
#define Hodoscope1Hit_h 1

#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4VHit.hh"
#include "G4VPhysicalVolume.hh"

// class G4AttDef;
// class G4AttValue;

/// Hadron Calorimeter hit
///
/// It records:
/// - the cell column ID and row ID
/// - the energy deposit
/// - the cell position and rotation

class Hodoscope1Hit : public G4VHit {
  public:
    Hodoscope1Hit(); // = default;
    Hodoscope1Hit(G4VPhysicalVolume *volume);
    // Hodoscope1Hit(G4int i,G4double t);
    // Hodoscope1Hit(G4int iCol,G4int iRow);
    // Hodoscope1Hit(G4int iCol,G4int iRow);
    Hodoscope1Hit(const Hodoscope1Hit &right); // = default;
    ~Hodoscope1Hit();                          // override = default;

    // Hodoscope1Hit& operator=(const Hodoscope1Hit &right) = default;
    // Hodoscope1Hit& operator=(const Hodoscope1Hit &right) = default;
    const Hodoscope1Hit &operator=(const Hodoscope1Hit &right);
    G4bool operator==(const Hodoscope1Hit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    // void Draw() override;
    // const std::map<G4String,G4AttDef>* GetAttDefs() const override;
    // std::vector<G4AttValue>* CreateAttValues() const override;
    // void Print() override;

    inline void SetColumnID(G4int z) { ColumnID = z; }
    G4int GetColumnID() { return ColumnID; }

    inline void SetRowID(G4int z) { RowID = z; }
    G4int GetRowID() { return RowID; }

    inline void SetEdep(G4double de) { fEdep = de; }
    inline void AddEdep(G4double de) { fEdep += de; }
    inline G4double GetEdep() { return fEdep; }

    inline void SetParticle(G4String name) { particleName = name; };

    void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    // G4ThreeVector GetPos() const { return fPos; }

    void SetRot(G4RotationMatrix rmat) { fRot = rmat; }
    // G4RotationMatrix GetRot() const { return fRot; }

    void SetTime(G4double t3) { Time = t3; };
    G4double GetTime() { return Time; };
    G4String GetParticle() { return particleName; };

    inline const G4VPhysicalVolume *GetPhysV() { return fPhysVolume; }

  private:
    // G4int fId = 0;
    G4int ColumnID;
    G4int RowID;
    G4double fEdep; // = 0.;
    G4ThreeVector fPos;
    G4RotationMatrix fRot;
    G4double Time; // = 0.;
    const G4VPhysicalVolume *fPhysVolume;
    G4String particleName;
};

typedef G4THitsCollection<Hodoscope1Hit> Hodoscope1HitsCollection; // Hodoscope1HitsCollection = G4THitsCollection<Hodoscope1Hit>;

// using Hodoscope1HitsCollection = G4THitsCollection<Hodoscope1Hit>;

extern G4ThreadLocal G4Allocator<Hodoscope1Hit> *Hodoscope1HitAllocator;

inline void *Hodoscope1Hit::operator new(size_t) {
    if (!Hodoscope1HitAllocator) {
        Hodoscope1HitAllocator = new G4Allocator<Hodoscope1Hit>;
    }
    return (void *)Hodoscope1HitAllocator->MallocSingle();
}

inline void Hodoscope1Hit::operator delete(void *aHit) {
    Hodoscope1HitAllocator->FreeSingle((Hodoscope1Hit *)aHit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif