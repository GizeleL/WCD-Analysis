// Geant4 Libraries
//
#include "GLEventAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4UserEventAction.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "GLDetectorConstruction.hh"
#include "GLPMTSD.hh"
#include "GLPrimaryGeneratorAction.hh"
#include "GLRunAction.hh"
#include "GLWaterHit.hh"
#include "GLWaterSD.hh"
#include "Hodoscope1Hit.hh"
#include "Hodoscope1SD.hh"
#include "LXeTrajectory.hh"
#include <cmath>
#include <map>

GLEventAction::GLEventAction(GLRunAction *runAction, GLPrimaryGeneratorAction *generator, GLDetectorConstruction *det, GLSteppingAction *steppingAction)
    : G4UserEventAction(),
      fRunAction(runAction),
      fPriGenAction(generator),
      fDetector(det),
      fWaterCollectionID(-1),
      fHodoscope1CollID(-1),
      fPMT1CollID(-1), //
      fPMT2CollID(-1), //
      fPMT3CollID(-1), //
      fSteppingAction(steppingAction) {
    G4cout << "...EventAction..." << G4endl;
    if (!fSteppingAction) {
        G4Exception("MyEventAction::MyEventAction", "InvalidPointer",
                    FatalException, "SteppingAction pointer is null!");
    }
}

GLEventAction::~GLEventAction() {}

void GLEventAction::BeginOfEventAction(const G4Event *event) {
    partId = fPriGenAction->primaryId;

    G4SDManager *SDman = G4SDManager::GetSDMpointer();
    if (fWaterCollectionID == -1) {
        fWaterCollectionID = SDman->GetCollectionID("waterCollection");
    }

    if (fHodoscope1CollID == -1) {
        fHodoscope1CollID = SDman->GetCollectionID("Hodoscope1SDCollection");
    }
}
/*
void GLEventAction::EndOfEventAction(const G4Event *event) {
    if (fWaterCollectionID < 0) return;

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4int eventID = event->GetEventID();

    GLWaterHitsCollection *WaterHC = NULL;
    G4HCofThisEvent *hitsCE = event->GetHCofThisEvent();

    G4String particleName = "";
    G4double fTotE = 0.;
    G4double fsecondaryenergy_electron = 0.;
    G4double secondaryelectron_count = 0.;
    G4double fsecondarycerenkov_count = 0.;
    G4double fsecondarycerenkov_muon_count = 0.;
    G4double fsecondarycerenkov_electron_count = 0.;
    G4double fsecondaryelectron_count = 0.;
    G4double fedep_gamma = 0.;

    if (hitsCE) {
        WaterHC = (GLWaterHitsCollection *)(hitsCE->GetHC(fWaterCollectionID));

        if (WaterHC) {
            G4int nHits = WaterHC->entries();
            for (G4int i = 0; i < nHits; ++i) {
                if(particleName == "opticalphoton") continue; //filtro

                particleName = (*WaterHC)[i]->GetParticle();
                GLWaterHit *hit = (*WaterHC)[i];

                G4double energyDeposited = hit->GetEdep(); /// step
                fTotE += energyDeposited;

                analysisManager->FillNtupleDColumn(11, fTotE / CLHEP::eV); // track

                G4ThreeVector position = hit->GetPos();
                G4double time = hit->GetTime();

                G4String particleSecondaryName = (*WaterHC)[i]->GetSecondaryParticle();

                G4double secondaryenergy_electron = (*WaterHC)[i]->GetSecondaryElectronEnergy();
                fsecondaryenergy_electron += secondaryenergy_electron;

                G4int secondaryelectron_count = (*WaterHC)[i]->GetSecondaryElectronCount();
                fsecondaryelectron_count += secondaryelectron_count;

                G4int secondarycerenkov_count = (*WaterHC)[i]->GetSecondaryCerenkovCount();
                fsecondarycerenkov_count += secondarycerenkov_count;

                G4int secondarycerenkov_muon_count = (*WaterHC)[i]->GetSecondaryCerenkovMuonCount();
                fsecondarycerenkov_muon_count += secondarycerenkov_muon_count;

                G4int secondarycerenkov_electron_count = (*WaterHC)[i]->GetSecondaryCerenkovElectronCount();
                fsecondarycerenkov_electron_count += secondarycerenkov_electron_count;

                analysisManager->FillNtupleIColumn(0, event->GetEventID());
                analysisManager->FillNtupleDColumn(1, energyDeposited / CLHEP::eV);
                analysisManager->FillNtupleDColumn(2, position.x());
                analysisManager->FillNtupleDColumn(3, position.y());
                analysisManager->FillNtupleDColumn(4, position.z());
                analysisManager->FillNtupleDColumn(5, time / CLHEP::ns);
                analysisManager->FillNtupleDColumn(6, fsecondaryenergy_electron / CLHEP::eV);
                analysisManager->FillNtupleDColumn(7, fsecondaryelectron_count);
                // analysisManager->FillNtupleDColumn(7, fsecondaryelectron_count);
                analysisManager->FillNtupleDColumn(8, fsecondarycerenkov_muon_count);
                analysisManager->FillNtupleDColumn(9, fsecondarycerenkov_electron_count);

                if (particleSecondaryName == "gamma") {
                    G4double edep_gamma = (*WaterHC)[i]->GetEdep();
                    fedep_gamma += edep_gamma;

                    analysisManager->FillNtupleDColumn(10, fedep_gamma);
                }

                // if (particleName == "mu-") { // 50MeV
                //     edep_mu += (*WaterHC)[i]->GetEdep();
                //     analysisManager->FillNtupleDColumn(11, edep_mu / CLHEP::eV);
                // }

                analysisManager->AddNtupleRow();
            }
        }
    }
}
*/

void GLEventAction::EndOfEventAction(const G4Event *event) {
    // G4cout << "DEBUG 1: inicio EndOfEvent" << G4endl;
    if (fWaterCollectionID < 0) return;
    //  G4cout << "DEBUG 2: apos waterCollectionID" << G4endl;

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    // G4cout << "DEBUG 4: hitsCE = " << G4endl;

    GLWaterHitsCollection *WaterHC = NULL;
    G4HCofThisEvent *hitsCE = event->GetHCofThisEvent();

    if (!hitsCE) return;
    //  G4cout << "DEBUG 5: apos hitsCE check" << G4endl;
    WaterHC = (GLWaterHitsCollection *)(hitsCE->GetHC(fWaterCollectionID));
    //  G4cout << "DEBUG 6: WaterHC = " << WaterHC << G4endl;
    if (!WaterHC) return;
    //  G4cout << "DEBUG 7: apos WaterHC check" << G4endl;
    // Variáveis acumulaveis por evento
    G4double fTotE = 0.;
    G4double fsecondaryenergy_electron = 0.;
    G4double fsecondaryelectron_count = 0.;
    G4double fsecondarycerenkov_muon_count = 0.;
    G4double fsecondarycerenkov_electron_count = 0.;
    G4double fedep_gamma = 0.;

    // Variáveis do último hit do múon (posição, tempo)
    G4ThreeVector lastPos(0., 0., 0.);
    G4double lastTime = 0.;

    G4int nHits = WaterHC->entries();
    // G4cout << "DEBUG 8: nHits = " << nHits << G4endl;
    for (G4int i = 0; i < nHits; ++i) {
        // G4cout << "DEBUG 9: hit " << i << G4endl;
        GLWaterHit *hit = (*WaterHC)[i];
        if (!hit) {
            G4cout << "DEBUG: hit nulo!" << G4endl;
            continue;
        }
        G4String particleName = hit->GetParticle();
        //  G4cout << "DEBUG 10: loop completo" << G4endl;
        // Acumula energia total depositada
        fTotE += hit->GetEdep();

        // Acumula secundários
        fsecondaryenergy_electron += hit->GetSecondaryElectronEnergy();
        fsecondaryelectron_count += hit->GetSecondaryElectronCount();
        fsecondarycerenkov_muon_count += hit->GetSecondaryCerenkovMuonCount();
        fsecondarycerenkov_electron_count += hit->GetSecondaryCerenkovElectronCount();

        // Acumula edep de gammas
        if (hit->GetSecondaryParticle() == "gamma")
            fedep_gamma += hit->GetEdep();

        // Guarda posição e tempo do último hit do múon primário
        if (particleName == "mu-") {
            lastPos = hit->GetPos();
            lastTime = hit->GetTime();
        }
    }

    // Padronização
    // Escreve UMA linha por evento
    analysisManager->FillNtupleIColumn(0, event->GetEventID());
    // G4cout << "DEBUG 11: apos Fill eventID" << G4endl;
    analysisManager->FillNtupleDColumn(1, fTotE / CLHEP::MeV);                     // MeV
                                                                                   // G4cout << "DEBUG 12: apos Fill fTotE" << G4endl;
    analysisManager->FillNtupleDColumn(2, lastPos.x() / CLHEP::cm);                // cm
                                                                                   // G4cout << "DEBUG 13: apos Fill posX" << G4endl;
    analysisManager->FillNtupleDColumn(3, lastPos.y() / CLHEP::cm);                // cm
                                                                                   //  G4cout << "DEBUG 14: apos Fill posY" << G4endl;
    analysisManager->FillNtupleDColumn(4, lastPos.z() / CLHEP::cm);                // cm
                                                                                   // G4cout << "DEBUG 15: apos Fill posZ" << G4endl;
    analysisManager->FillNtupleDColumn(5, lastTime / CLHEP::ns);                   // ns
                                                                                   // G4cout << "DEBUG 16: apos Fill time" << G4endl;
    analysisManager->FillNtupleDColumn(6, fsecondaryenergy_electron / CLHEP::MeV); // MeV
                                                                                   //  G4cout << "DEBUG 17: apos AddNtupleRow" << G4endl;
    analysisManager->FillNtupleDColumn(7, fsecondaryelectron_count);               // contagem
                                                                                   //  G4cout << "DEBUG 18: apos secondaryelectron_count" << G4endl;
    analysisManager->FillNtupleDColumn(8, fsecondarycerenkov_muon_count);          // contagem
                                                                                   //  G4cout << "DEBUG 19: apos secondarycherenkov_count" << G4endl;
    analysisManager->FillNtupleDColumn(9, fsecondarycerenkov_electron_count);      // contagem
                                                                                   //  G4cout << "DEBUG 20: apos secondarycherenkov_electron_count" << G4endl;
    analysisManager->FillNtupleDColumn(10, fedep_gamma / CLHEP::MeV);              // MeV
                                                                                   // G4cout << "DEBUG 21: apos edep_gamma" << G4endl;
    analysisManager->FillNtupleDColumn(11, fTotE / CLHEP::MeV);                    // MeV
                                                                                   //  G4cout << "DEBUG 22: add ToTE" << G4endl;
    analysisManager->AddNtupleRow();
    //  G4cout << "DEBUG 23: addNtupleRow" << G4endl;
    // Lê contagem de fótons de cada PMT
    // G4cout << "DEBUG 24: inicio bloco PMTs" << G4endl;
    G4SDManager *sdman = G4SDManager::GetSDMpointer();
    //   G4cout << "DEBUG 25: sdman ok" << G4endl;
    PMTSD *pmt1 = static_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT1"));
    //  G4cout << "DEBUG 26: pmt1 = " << pmt1 << G4endl;
    PMTSD *pmt2 = static_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT2"));
    //  G4cout << "DEBUG 27: pmt2 = " << pmt2 << G4endl;
    PMTSD *pmt3 = static_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT3"));
    //  G4cout << "DEBUG 28: pmt3 = " << pmt3 << G4endl;
    PMTSD *pmt4 = static_cast<PMTSD *>(sdman->FindSensitiveDetector("/PMT4"));
    // G4cout << "DEBUG 29: pmt4 = " << pmt4 << G4endl;

    G4int nPMT1 = pmt1 ? pmt1->GetPhotonCount() : 0;
    G4int nPMT2 = pmt2 ? pmt2->GetPhotonCount() : 0;
    G4int nPMT3 = pmt3 ? pmt3->GetPhotonCount() : 0;
    G4int nPMT4 = pmt4 ? pmt4->GetPhotonCount() : 0;

    // Escreve na ntuple 1 (PMTs)
    // G4cout << "DEBUG 30: inicio Fill PMTs" << G4endl;
    analysisManager->FillNtupleIColumn(1, 0, event->GetEventID());
    // G4cout << "DEBUG 31: apos Fill eventID PMT" << G4endl;
    analysisManager->FillNtupleIColumn(1, 1, nPMT1);
    //  G4cout << "DEBUG 32: apos Fill PMT1" << G4endl;
    analysisManager->FillNtupleIColumn(1, 2, nPMT2);
    //  G4cout << "DEBUG 33: apos Fill PMT2" << G4endl;
    analysisManager->FillNtupleIColumn(1, 3, nPMT3);
    // G4cout << "DEBUG 34: apos Fill PMT3" << G4endl;
    analysisManager->FillNtupleIColumn(1, 4, nPMT4);
    //  G4cout << "DEBUG 35: apos Fill PMT4" << G4endl;
    analysisManager->AddNtupleRow(1);
    //  G4cout << "DEBUG 36: apos AddNtupleRow PMTs" << G4endl;

    // Lê hits do hodoscópio
    // G4HCofThisEvent *hitsCE = event->GetHCofThisEvent();
    //  G4cout << "DEBUG 37: inicio bloco hodoscópio" << G4endl;
    if (hitsCE) {
        static G4int holoHCID = -1;
        if (holoHCID < 0)

            //  holoHCID = G4SDManager::GetSDMpointer()->GetCollectionID("Hodoscope1Collection");

            holoHCID = G4SDManager::GetSDMpointer()
                           ->GetCollectionID("Hodoscope1SDCollection");

        //    G4cout << "DEBUG 39: holoHCID = " << holoHCID << G4endl;

        Hodoscope1HitsCollection *hodoHC =
            static_cast<Hodoscope1HitsCollection *>(hitsCE->GetHC(holoHCID));

        //   G4cout << "DEBUG 40: hodoHC = " << hodoHC << G4endl;

        if (hodoHC) {
            //      G4cout << "DEBUG 41: inicio loop hodo" << G4endl;
            G4int nHodoHits = hodoHC->entries();
            //      G4cout << "DEBUG 42: nHodoHits = " << nHodoHits << G4endl;
            for (G4int i = 0; i < nHodoHits; i++) {
                Hodoscope1Hit *hit = (*hodoHC)[i];
                if (!hit) {
                    //         G4cout << "DEBUG: hit nulo i=" << i << G4endl;
                    continue;
                }
                //   G4cout << "DEBUG 43: hit " << i << " edep=" << hit->GetEdep() << G4endl;
                if (!hit) continue;
                if (hit->GetEdep() > 0.) {
                    analysisManager->FillNtupleIColumn(2, 0, event->GetEventID());
                    analysisManager->FillNtupleIColumn(2, 1, hit->GetColumnID());
                    analysisManager->FillNtupleIColumn(2, 2, hit->GetRowID());
                    analysisManager->FillNtupleDColumn(2, 3, hit->GetEdep() / CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(2, 4, hit->GetTime() / CLHEP::ns);
                    analysisManager->AddNtupleRow(2);
                }
            }
        }
    }

    // Lê hits das RPCs
    struct RPCInfo {
        const char *name;
        int id;
    };
    RPCInfo rpcs[] = {
        {"Hodoscope2SDCollection", 2},
        {"Hodoscope3SDCollection", 3},
        {"Hodoscope4SDCollection", 4},
        {"Hodoscope5SDCollection", 5}};

    for (auto &rpc : rpcs) {
        static std::map<std::string, G4int> rpcIDs;
        if (rpcIDs.find(rpc.name) == rpcIDs.end()) {
            rpcIDs[rpc.name] = G4SDManager::GetSDMpointer()
                                   ->GetCollectionID(rpc.name);
        }
        G4int rpcHCID = rpcIDs[rpc.name];
        if (rpcHCID < 0) continue;

        Hodoscope1HitsCollection *rpcHC =
            static_cast<Hodoscope1HitsCollection *>(hitsCE->GetHC(rpcHCID));
        if (!rpcHC) continue;

        G4int nRPCHits = rpcHC->entries();
        for (G4int i = 0; i < nRPCHits; i++) {
            Hodoscope1Hit *hit = (*rpcHC)[i];
            if (!hit) continue;
            if (hit->GetEdep() > 0.) {
                analysisManager->FillNtupleIColumn(3, 0, event->GetEventID());
                analysisManager->FillNtupleIColumn(3, 1, rpc.id);
                analysisManager->FillNtupleIColumn(3, 2, hit->GetColumnID());
                analysisManager->FillNtupleIColumn(3, 3, hit->GetRowID());
                analysisManager->FillNtupleDColumn(3, 4, hit->GetEdep() / CLHEP::MeV);
                analysisManager->FillNtupleDColumn(3, 5, hit->GetTime() / CLHEP::ns);
                analysisManager->AddNtupleRow(3);
            }
        }
    }
}
