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
/// \file B5/src/Hodoscope1SD.cc
/// \brief Implementation of the B5::Hodoscope1SD class
#include "G4HCofThisEvent.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"
#include "G4ios.hh"

#include "Hodoscope1Hit.hh"
#include "Hodoscope1SD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Hodoscope1SD::Hodoscope1SD(G4String name)
    : G4VSensitiveDetector(name), fHCID(-1) {
    fHodoscope1HitsCollection = nullptr;
    collectionName.insert(name.substr(1) + "Collection"); // ex: Hodoscope1SDCollection
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Hodoscope1SD::~Hodoscope1SD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Hodoscope1SD::Initialize(G4HCofThisEvent *hitsCE) {
    fHodoscope1HitsCollection = new Hodoscope1HitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHodoscope1HitsCollection);
    }
    hitsCE->AddHitsCollection(fHCID, fHodoscope1HitsCollection);

    // fill calorimeter hits with zero energy deposition
    for (G4int column = 0; column < 32; column++) {
        for (G4int row = 0; row < 32; row++) {
            fHodoscope1HitsCollection->insert(new Hodoscope1Hit());

            //   Hodoscope1Hit* aHit = new Hodoscope1Hit();
            //   fHodoscope1HitsCollection->insert( aHit );
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool Hodoscope1SD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {
    auto edep = aStep->GetTotalEnergyDeposit();
    if (edep == 0.) return true;

    // if(aStep->GetTrack()->GetDefinition()
    //    == G4OpticalPhoton::OpticalPhotonDefinition()) return false;

    // if(aStep->GetTrack()->GetDefinition()
    //  == G4Electron::ElectronDefinition()) return false;

    G4StepPoint *thePrePoint = aStep->GetPreStepPoint();
    G4TouchableHistory *touchable = (G4TouchableHistory *)(aStep->GetPreStepPoint()->GetTouchable());

    // touchable = aStep->GetPreaStepPoint()->GetTouchable();
    // auto rowNo = touchable->GetReplicaNumber();
    // auto columnNo = touchable->GetReplicaNumber();
    // auto hitID = 32*columnNo+rowNo;

    // auto hit = (*fHodoscope1HitsCollection)[hitID];
    // auto hitTime = aStep->GetPreaStepPoint()->GetGlobalTime();
    // auto copyNo = touchable->GetVolume()->GetCopyNo();

    // G4VPhysicalVolume* PrePV = aStep->GetPreaStepPoint()->GetTouchableHandle()->GetVolume();

    // G4String VolumeName = PrePV->GetName();

    // G4VPhysicalVolume* theCellPhysical = touchable->GetVolume(1);
    // G4String CellVolumeName = theCellPhysical->GetName();
    // G4int rowNo = theCellPhysical->GetCopyNo();
    // G4VPhysicalVolume* theColumnPhysical = touchable->GetVolume(0);
    // G4String ColumnVolumeName = theColumnPhysical->GetName();
    G4ParticleDefinition *particleType = aStep->GetTrack()->GetDefinition();
    G4String particleName = particleType->GetParticleName();

    // G4cout<<"luuuuuuuuuuu: "<< touchable->GetVolume(0)->GetName() << G4endl;
    // G4cout<<"Particle name - hodoscope: "<< aStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;

    // G4cout<<"Hodoscope1 volume: "<< touchable->GetVolume(0)->GetName() << G4endl;
    // G4cout<<"Particle name - hodoscope1: "<< aStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;
    // G4cout<<"Hit time - hodoscope1: "<< aStep->GetPreStepPoint()->GetGlobalTime() << G4endl;

    G4int ColumnID = touchable->GetCopyNumber(1);
    G4int RowID = touchable->GetCopyNumber(0);
    G4int hitID = 32 * ColumnID + RowID;
    auto aHit = (*fHodoscope1HitsCollection)[hitID];

    // if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
    // RowID = touchable->GetCopyNumber(1);
    // ColumnID = touchable->GetCopyNumber(0);
    // G4cout<<"Row ID- hodoscope1: "<< RowID << "Column ID- hodoscope1: "<< ColumnID << "HIT ID: " << 32*ColumnID+RowID << G4endl;
    // G4cout<< "Particle hit time hodoscope: " << aStep->GetPreStepPoint()->GetGlobalTime()  / CLHEP::nanosecond <<G4endl;

    // Hodoscope1Hit* aHit = new Hodoscope1Hit();

    if (aStep->GetTrack()->GetDefinition()->GetParticleName() == "mu+" ||
        aStep->GetTrack()->GetDefinition()->GetParticleName() == "mu-") {
        aHit->SetTime(aStep->GetPreStepPoint()->GetGlobalTime());
        aHit->SetColumnID(touchable->GetCopyNumber(0));
        aHit->SetRowID(touchable->GetCopyNumber(1));
        aHit->SetParticle(aStep->GetTrack()->GetDefinition()->GetParticleName());
        aHit->AddEdep(edep);
        // fHodoscope1HitsCollection->insert(aHit);
    }

    // check if it is first touch
    // if (VolumeName=="hodoscope1ColumnLogical"){
    // G4int columnNo = touchable->GetCopyNumber(3);
    // hodoscope1Hit->SetColumnID(columnNo);//}

    // if (VolumeName=="hodoscope1CellLogical"){
    // G4int rowNo = touchable->GetCopyNumber(2);
    // hodoscope1Hit->SetRowID(rowNo);//}
    // hodoscope1Hit->SetRowID(rowNo);
    // hodoscope1Hit->SetTime(aStep->GetPreaStepPoint()->GetGlobalTime());
    //   G4double depth = touchable->GetHistory()->GetDepth();
    //   auto transform = touchable->GetHistory()->GetTransform(depth-2);
    //   transform.Invert();
    //   hit->SetRot(transform.NetRotation());
    //   hit->SetPos(transform.NetTranslation());
    // if (hit->GetTime()>hitTime) {
    //    hit->SetTime(hitTime);}
    //}

    //  auto ix = -1;
    //  for (std::size_t i=0;i<fHodoscope1HitsCollection->entries();++i) {
    //    if ((*fHodoscope1HitsCollection)[i]->GetID()==copyNo) {
    //      ix = i;
    //      break;
    //    }
    //  }

    //  if (ix>=0) {
    //    // if it has, then take the earlier time
    //    if ((*fHodoscope1HitsCollection)[ix]->GetTime()>hitTime) {
    //      (*fHodoscope1HitsCollection)[ix]->SetTime(hitTime);
    //    }
    //  }
    // add energy deposition
    // aHit->AddEdep(edep);
    // hit->SetTime(hitTime);

    // fHodoscope1HitsCollection->insert(aHit);

    return true;
}

void Hodoscope1SD::EndOfEvent(G4HCofThisEvent *hitsCE) {
    /*
        G4String HHCname = collectionName[0];
        static G4int HHCID = -1;
        if (HHCID < 0)
            HHCID = G4SDManager::GetSDMpointer()->GetCollectionID(HHCname);
        hitsCE->AddHitsCollection(HHCID, fHodoscope1HitsCollection);

        G4int nHitss = fHodoscope1HitsCollection->entries();
        if (verboseLevel >= 1)
            G4cout << "     LXe collection: " << nHitss << " hits" << G4endl;
        if (verboseLevel >= 2)
            fHodoscope1HitsCollection->PrintAllHits();

            */
}