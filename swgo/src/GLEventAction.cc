// Geant4 Libraries
//
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
#include "G4ios.hh"
// #include "g4root.hh"

// C++ Libraries
//
#include <cmath>

// Local Libraries
//
#include "GLDetectorConstruction.hh"
#include "GLEventAction.hh"
#include "GLPrimaryGeneratorAction.hh"
#include "GLRunAction.hh"

#include "GLWaterHit.hh"
#include "GLWaterSD.hh"

// #include "CerValHistograms.hh"
// #include "CerenkovValidation.hh"

// Get all hits collections
G4VHitsCollection *GetHC(const G4Event *event, G4int collId) {
    auto hce = event->GetHCofThisEvent();
    if (!hce) {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl;
        G4Exception("EventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return nullptr;
    }

    auto hc = hce->GetHC(collId);
    if (!hc) {
        G4ExceptionDescription msg;
        msg << "Hits collection " << collId << " of this event not found." << G4endl;
        G4Exception("EventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
    }
    return hc;
}

GLEventAction::GLEventAction(GLRunAction *runAction, GLPrimaryGeneratorAction *generator, GLDetectorConstruction *det)
    : G4UserEventAction(),
      fRunAction(runAction),
      fPriGenAction(generator),
      fDetector(det),
      fWaterCollectionID(-1) {
    G4cout << "...EventAction..." << G4endl;

    fHitCount = 0;
    fPhotonCount_Scint = 0;
    fPhotonCount_Ceren = 0;
    fAbsorptionCount = 0;
    fBoundaryAbsorptionCount = 0;
    fTotE = 0.0;
    // ftimeScint               = 0.0;
    // ftimePMT                 = 0.0;

    fConvPosSet = false;
    fEdepMax = 0.0;
}

GLEventAction::~GLEventAction() {}

// std::ofstream output("./WaterCollection.dat");
void GLEventAction::BeginOfEventAction(const G4Event *event) {
    fHitCount = 0;
    fHitCount_mu = 0;
    fHitCount_e = 0;
    fPhotonCount_Scint = 0;
    fPhotonCount_Ceren = 0;
    fAbsorptionCount = 0;
    fBoundaryAbsorptionCount = 0;
    edep = 0.0;
    edep_mu = 0.0;
    edep_e = 0.0;
    edep_gamma = 0.0;
    fTotE = 0.0;
    fTotE_mu = 0.0;
    fTotE_e = 0.0;
    fTotE_gamma = 0.0;
    // columnID_hodoscope1;
    // rowID_hodoscope1;
    // ftimeScint               = 0.0;
    // ftimePMT                 = 0.0;

    fConvPosSet = false;
    fEdepMax = 0.0;

    G4SDManager *SDman = G4SDManager::GetSDMpointer();
    if (fWaterCollectionID == -1) {
        fWaterCollectionID = SDman->GetCollectionID("waterCollection");
    }

    // output << "fEnergy"
    //        << ","
    //        << "direction"
    //        << ","
    //        << "cosTheta"
    //        << ","
    //        << "fPhi"
    //        << ","
    //        << "fT0"
    //        << ","
    //        << "fTotE / MeV"
    //        << ","
    //        << "fTotE_mu / MeV"
    //        << ","
    //        << ","
    //        << "fTotE_e / MeV"
    //        << ","
    //        << "gammac"
    //        << ","
    //        << "fTotE_gamma / MeV"
    //        << ","
    //        << "secondaryelectron_count"
    //        << ","
    //        << "(secondaryenergy_electron_sum / CLHEP::MeV) / secondaryelectron_count"
    //        << ","
    //        << "(secondaryenergy_cerenkov_sum / CLHEP::eV) / secondarycerenkov_count"
    //        << ","
    //        << "secondarycerenkov_count" << G4endl;

    // OOOOOOooooooooooooooooooooOOOOOOOOOOOOOoooooooooooooooooOOOOOOOOOOOOOOOOOOOoooooooooooooo
    nPhotons = 0.;
    cerenkovPhontons = 0;
    totalLength = 0.;
    // G4cout << "Begin Event: " << cerenkovPhontons << " " << event->GetEventID() << G4endl;

    muonOk = 0;
    elecOk = 0;
    gammOk = 0;
    neutOk = 0;

    partId = fPriGenAction->primaryId;

    G4Step *aStep = new G4Step();
    G4StepPoint *endPoint = aStep->GetPostStepPoint();
    G4ThreeVector posParticle = endPoint->GetPosition();

    // fRunAction->histRun->postInject(fPriGenAction->position.x() / cm, fPriGenAction->position.y() / cm);
    fRunAction->histRun->postInject(posParticle[0] / cm, posParticle[1] / cm);
    fRunAction->histRun->histPartEnergy(fPriGenAction->GetEnergy());
    if (partId == "mu-" || partId == "mu+") {
        muonOk = 1;
        fRunAction->histRun->distInject(0);
    } else if (partId == "e-" || partId == "e+") {
        elecOk = 1;
        fRunAction->histRun->distInject(1);
    } else if (partId == "gamma") {
        gammOk = 1;
        fRunAction->histRun->distInject(2);
    } else if (partId == "neutron") {
        neutOk = 1;
        fRunAction->histRun->distInject(3);
    } else
        fRunAction->histRun->distInject(4);

    // fRunAction->cerVali->resetting();
}

void GLEventAction::EndOfEventAction(const G4Event *event) {
    G4cout << "End Event: " << event->GetEventID() << G4endl;

    fRunAction->cerVali->printtingCerPhoCounting(1);
    fRunAction->cerVali->resetting();

    if (muonOk) {
        fRunAction->histRun->fillCerenPho(0);
        fRunAction->histRun->fillCerenPhoPmt(0);
        fRunAction->histRun->fillCerenPhoElect(0);
        fRunAction->histRun->fillTrackLengthDetec(0);

        fRunAction->histRun->fillCerenPhoPmt2(1);
        fRunAction->histRun->fillCerenPhoElect2(1);

        fRunAction->histRun->fillCerenPhoPmt3(3);
        fRunAction->histRun->fillCerenPhoElect3(3);

        fRunAction->histRun->fillCerenPho(5);
        fRunAction->histRun->fillCerenPhoPmtAll(5);
        fRunAction->histRun->fillCerenPhoElectAll(5);
        fRunAction->histRun->fillCerenPhoPmtAll(5);
    }

    if (fWaterCollectionID < 0) return;

    // Others SDs
    //   if(fHodoscope1CollID == -1)
    //     fHodoscope1CollID = SDman->GetCollectionID("Hodoscope1Collection");
    //   if(fPMTCollID == -1)
    //     fPMTCollID = SDman->GetCollectionID("pmtHitCollection");
    //  if (fHodoscope1CollID < 0 || fScintCollID < 0 || fPMTCollID < 0) return;
    // Trajectory fill modifications
    // G4TrajectoryContainer *trajectoryContainer =
    //     anEvent->GetTrajectoryContainer();
    // G4int n_trajectories = 0;
    // if (trajectoryContainer)
    //     n_trajectories = trajectoryContainer->entries();

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4int eventID = event->GetEventID();
    //  analysisManager->FillNtupleIColumn(0, 0, eventID);

    //! Call for event hits in water
    GLWaterHitsCollection *WaterHC = NULL;
    G4HCofThisEvent *hitsCE = event->GetHCofThisEvent();

    if (hitsCE) {
        WaterHC = (GLWaterHitsCollection *)(hitsCE->GetHC(fWaterCollectionID));
    }

    // Extrantion info for the water hits
    G4String particleName = "";
    G4String particleSecondaryName = "";
    G4int gammac = 0;

    if (WaterHC) {
        G4int nHits = WaterHC->entries();
        for (G4int i = 0; i < nHits; ++i) {
            GLWaterHit *hit = (*WaterHC)[i];

            G4double energyDeposited = hit->GetEdep();
            G4ThreeVector position = hit->GetPos();
            G4double time = hit->GetTime();

            G4double secondaryenergy_electron = (*WaterHC)[i]->GetSecondaryElectronEnergy();
            G4int secondaryelectron_count = (*WaterHC)[i]->GetSecondaryElectronCount();

            G4int secondarycerenkov_count = (*WaterHC)[i]->GetSecondaryCerenkovCount();

            // Preencha as colunas no arquivo CSV
            analysisManager->FillNtupleIColumn(0, event->GetEventID());                   // ID do evento
            analysisManager->FillNtupleDColumn(1, energyDeposited / CLHEP::MeV);          // Energia depositada pelo primário na água
            analysisManager->FillNtupleDColumn(2, position.x());                          // Posição X na água
            analysisManager->FillNtupleDColumn(3, position.y());                          // Posição Y na água
            analysisManager->FillNtupleDColumn(4, position.z());                          // Posição Z na água
            analysisManager->FillNtupleDColumn(5, time);                                  // Tempo na água
            analysisManager->FillNtupleDColumn(6, secondaryenergy_electron / CLHEP::MeV); // Energia -e secundario na água
            analysisManager->FillNtupleDColumn(7, secondaryelectron_count);               // Contagem de -e secundarios na água
            analysisManager->FillNtupleDColumn(8, secondaryelectron_count);               // Contagem de -e secundarios na água

            analysisManager->AddNtupleRow();
        }
    }

    // Obtenha o número de fótons Cherenkov contados no SteppingAction
    // G4int cherenkovPhotonCount = fSteppingAction->GetCherenkovPhotonCount();

    // // Salve os dados no arquivo CSV
    // analysisManager->FillNtupleIColumn(0, event->GetEventID());  // ID do evento
    // analysisManager->FillNtupleIColumn(1, cherenkovPhotonCount); // Número de fótons Cherenkov
    // analysisManager->AddNtupleRow();

    // // Reinicie o contador para o próximo evento
    // fSteppingAction->ResetCherenkovPhotonCount();

    //   G4ThreeVector eWeightPos(0.);
    //   G4double edepMax = 0.;
    // for (G4int i = 0; i < n_hit; ++i) { // gather info on hits in scintillator
    //     particleName = (*WaterHC)[i]->GetParticle();
    //     edep = (*WaterHC)[i]->GetEdep();
    //     fTotE += edep;
    // }
    // for (G4int i = 0; i < n_hit; ++i) { // gather info on hits in scintillator
    //     particleName = (*WaterHC)[i]->GetParticle();
    //     edep = (*WaterHC)[i]->GetEdep();
    //     fTotE += edep;
    //     analysisManager->FillH1(0, fTotE);
    //     // G4cout << "Particle :" << particleName << G4endl;
    //     if (particleName == "mu-") {
    //         edep_mu = (*WaterHC)[i]->GetEdep();
    //         fTotE_mu += edep_mu;
    //         analysisManager->FillH1(1, fTotE_mu);
    //     }
    //     //  G4cout << "particle init time: " << firsHitTime << G4endl;
    //     // eWeightPos +=
    //     //   (*WaterHC)[i]->GetPos() * edep;  // calculate energy weighted pos
    //     particleSecondaryName = (*WaterHC)[i]->GetSecondaryParticle();

    //     secondaryelectron_count += (*WaterHC)[i]->GetSecondaryElectronCount();
    //     secondaryenergy_electron_sum += (*WaterHC)[i]->GetSecondaryElectronEnergy();
    //     // analysisManager->FillH1(4, (*WaterHC)[i]->GetSecondaryElectronEnergy());

    //     secondarycerenkov_count += (*WaterHC)[i]->GetSecondaryCerenkovCount();
    //     secondarycerenkov_muon_count += (*WaterHC)[i]->GetSecondaryCerenkovMuonCount();
    //     secondarycerenkov_electron_count += (*WaterHC)[i]->GetSecondaryCerenkovElectronCount();

    //     secondaryenergy_cerenkov_sum += (*WaterHC)[i]->GetSecondaryCerenkovEnergy();

    //     // secondaryscintillation_count += (*WaterHC)[i]->GetSecondaryScintillationCount();
    //     // secondaryscintillation_muon_count += (*WaterHC)[i]->GetSecondaryScintillationMuonCount();
    //     // secondaryscintillation_electron_count += (*WaterHC)[i]->GetSecondaryScintillationElectronCount();
    //     // secondaryenergy_scintillation_sum += (*WaterHC)[i]->GetSecondaryScintillationEnergy();

    //     NumberSecondary += (*WaterHC)[i]->GetNumberSecondary();

    //     if (particleSecondaryName == "e-") {
    //         edep_e = (*WaterHC)[i]->GetEdep();
    //         fTotE_e += edep_e;
    //         //  G4cout << "TotE_e: " << fTotE_e / CLHEP::MeV << G4endl;
    //         analysisManager->FillH1(2, fTotE_e);
    //     }
    //     if (particleSecondaryName == "gamma") {
    //         edep_gamma = (*WaterHC)[i]->GetEdep();
    //         fTotE_gamma += edep_gamma;
    //         gammac++;
    //         analysisManager->FillH1(3, fTotE_gamma);
    //     }
    //     if (edep_mu > edepMax) {
    //         edepMax = edep_mu; // store max energy deposit
    //         G4ThreeVector posMax = (*WaterHC)[i]->GetPos();
    //         fPosMax = posMax;
    //         fEdepMax = edep_mu;
    //     }
    // }

    G4double fEnergy;
    fEnergy = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();

    G4ThreeVector direction;
    direction = event->GetPrimaryVertex()->GetPrimary()->GetMomentumDirection();
    G4double Theta;
    G4double cosTheta = direction.z(); //(direction.x()/std::sqrt((direction.x()*direction.x())+(direction.y()*direction.y())+(direction.z()*direction.z())));
    // Theta = G4INCL::Math::arcCos(cosTheta);
    Theta = std::acos(-cosTheta);

    G4double fT0;
    fT0 = event->GetPrimaryVertex()->GetT0();

    G4double fPhi;
    fPhi = direction.phi();

    G4cout << "Event Action" << event->GetEventID() << G4endl;
    G4cout << "#### End of Event Action ###" << G4endl;
    G4cout << "#### GPS info ###" << G4endl;
    G4cout << "Energia GPS gun:  " << fEnergy << " GeV" << G4endl;
    G4cout << "Angulo theta do GPS:  " << direction << " deg" << G4endl;
    G4cout << "Angulo cos(theta) :  " << cosTheta << " deg" << G4endl;
    G4cout << "Angulo phi(theta) :  " << fPhi << " deg" << G4endl;
    G4cout << "T0 from GPS :  " << fT0 << " deg\n"
           << G4endl;
    G4cout << "#### Water info ###" << G4endl;
    G4cout << "Energia Depositada Total:  " << fTotE / CLHEP::MeV << " MeV" << G4endl;
    G4cout << "Energia total depositada pelo mu na água:  " << fTotE_mu / CLHEP::MeV << " MeV " << G4endl;
    G4cout << "Energia total depositada por e- na água:  " << fTotE_e / CLHEP::MeV << " MeV "
           << " Getedep includes mass!" << G4endl;
    G4cout << "Número de gamas secundários na água: " << gammac << G4endl;
    G4cout << "Energia total depositada por gamas raros na água:  " << fTotE_gamma / CLHEP::MeV << " MeV "
           << "includes mass!" << G4endl;
    G4cout << "Número de e- secundários na água: " << secondaryelectron_count << G4endl;
    G4cout << "Energia Cinética Média e- secundários na água:  " << (secondaryenergy_electron_sum / CLHEP::MeV) / secondaryelectron_count << " MeV" << G4endl;
    G4cout << "Energia Cinética Média fótons Cherenkov secundários na água: " << (secondaryenergy_cerenkov_sum / CLHEP::eV) / secondarycerenkov_count << " eV" << G4endl;
    G4cout << "Número de fótons Cherenkov secundários na água: " << secondarycerenkov_count << G4endl;

    // output << fEnergy << "," << direction << "," << cosTheta << "," << fPhi << "," << fT0 << "," << fTotE / CLHEP::MeV << "," << fTotE_mu / CLHEP::MeV << ","
    //        << "," << fTotE_e / CLHEP::MeV << "," << gammac << "," << fTotE_gamma / CLHEP::MeV
    //        << "," << secondaryelectron_count << "," << (secondaryenergy_electron_sum / CLHEP::MeV) / secondaryelectron_count << "," << (secondaryenergy_cerenkov_sum / CLHEP::eV) / secondarycerenkov_count << "," << secondarycerenkov_count << G4endl;

    // output << fEnergy / CLHEP::GeV << "," << Theta / deg << "," << fTotE / CLHEP::eV << "," << fTotE_mu / CLHEP::eV << "," << fTotE_e / CLHEP::eV << "," << fTotE_gamma / CLHEP::eV << "," << NumberSecondary << "," << (secondaryenergy_electron_sum / CLHEP::eV) / secondaryelectron_count << "," << secondaryelectron_count << "," << G4endl;

    //  output.close();

    // fRunAction->cerVali->printtingCerPhoCounting(1);
    // fRunAction->cerVali->resetting();

    //   if ( muonOk )
    //   {
    //     fRunAction->histRun->fillCerenPho(0);
    //     fRunAction->histRun->fillCerenPhoPmt(0);
    //     fRunAction->histRun->fillCerenPhoElect(0);
    //     fRunAction->histRun->fillTrackLengthDetec(0);

    //     fRunAction->histRun->fillCerenPhoPmt2(1);    // PMT2
    //     fRunAction->histRun->fillCerenPhoElect2(1);

    //     fRunAction->histRun->fillCerenPhoPmt3(3);    // PMT3
    //     fRunAction->histRun->fillCerenPhoElect3(3);

    //     fRunAction->histRun->fillCerenPho(5);
    //     fRunAction->histRun->fillCerenPhoPmtAll(5);
    //     fRunAction->histRun->fillCerenPhoElectAll(5);
    //     fRunAction->histRun->fillTrackLengthDetec(5);

    //   }
}

void GLEventAction::countingCerenkovs(G4int cphoton) {
    cerenkovPhontons += cphoton;
}

void GLEventAction::countingCerenkovs(G4double trackLength) {
    totalLength = trackLength;
}
