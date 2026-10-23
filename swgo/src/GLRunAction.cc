// Geant4 Libraries
//
// #include "G4AnalysisManager.hh"
#include "G4AccumulableManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4Timer.hh"
#include "G4Types.hh"
#include "G4VVisManager.hh"
#include <iostream>
//  Local Libraries
//
#include "GLRunAction.hh"
GLRunAction::GLRunAction() : G4UserRunAction(),
                             fTimer(0) {

    G4cout << "...RunAction..." << G4endl;
    fTimer = new G4Timer;

    //  create a 1D histogram
    //  analysisManager->CreateH1("0", "Edep total", 100, 0, 60 * CLHEP::MeV);
    //  analysisManager->CreateH1("1", "Edep mu-", 100, 0, 60 * CLHEP::MeV);
    //  analysisManager->CreateH1("2", "Edep e-", 200, 0, 0.01 * CLHEP::MeV);

    // analysisManager->CreateH1("3", "Edep gamma", 150, 0, 0.01 * CLHEP::MeV);
    // analysisManager->CreateH1("4", "Ekin e-", 150, -1, 1 * CLHEP::MeV);

    // analysisManager->CreateNtuple("Events", "Particle"); //(x,y)
    // analysisManager->CreateNtupleIColumn("iEvents");
    // analysisManager->CreateNtupleDColumn("fX");
    // analysisManager->CreateNtupleDColumn("fY");
    // analysisManager->CreateNtupleDColumn("fZ");
    // analysisManager->CreateNtupleDColumn("fGlobalTime");

    // analysisManager->CreateNtuple("fTime", "SecParticle"); //(x,y)
    // analysisManager->CreateNtupleIColumn("fGlobalTime");
    // analysisManager->CreateNtupleDColumn("Sec_e- count by mu- (MuIoni)");
    // analysisManager->CreateNtupleDColumn("secCerenkov count");
    // analysisManager->CreateNtupleDColumn("secCerenkov count by mu-");
    // analysisManager->CreateNtupleDColumn("secCerenkov count by Delta e-");
    // analysisManager->CreateNtupleDColumn("fWlen");       // for cerenkov

    // new
    fTimer = new G4Timer;

    // -----------------------
    // Histogram for One Pulse
    analysisManager->CreateH1("0", "Time at Pmt", 1000, 0., 1000.);
    // startCerenkValid();

    cerVali = new CerenkovValidation();

    if (cervaliOk)
        histCerVali = new CerValHistograms();

    //  if(coulombOk)
    //    scatter = new coulombScattering();

    if (histRunOk) {
        histRun = new histosRun();
        histRun->initHistos();
    }
}

GLRunAction::~GLRunAction() {
    if (cervaliOk)
        histCerVali->~CerValHistograms();

    //  if(coulombOk)
    //    scatter->~coulombScattering();

    delete fTimer;
}

void GLRunAction::BeginOfRunAction(const G4Run *aRun) {

    //  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // G4int runID = aRun->GetRunID();

    // std::stringstream strRunID;
    // strRunID << runID;

    // analysisManager->OpenFile("OutputRun_" + strRunID.str() + ".root");

    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    fTimer->Start();

    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    if (cervaliOk)
        histCerVali->creatingHist(aRun->GetRunID());

    // if (coulombOk)
    //     scatter->creatingHist();

    // // ---------------------------
    // // Root File for Pulses On PMT

    // G4String rootFile = "rootPulsesOnPMT";
    // analysisManager->OpenFile(rootFile);

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("data.csv");

    analysisManager->CreateNtuple("Data", "Dados dos Hits na água");
    analysisManager->CreateNtupleIColumn("EventID");              // Coluna 0: ID do evento
    analysisManager->CreateNtupleDColumn("EnergyDeposited");      // Coluna 1: Energia depositada
    analysisManager->CreateNtupleDColumn("PositionX");            // Coluna 2: Posição X
    analysisManager->CreateNtupleDColumn("PositionY");            // Coluna 3: Posição Y
    analysisManager->CreateNtupleDColumn("PositionZ");            // Coluna 4: Posição Z
    analysisManager->CreateNtupleDColumn("Time");                 // Coluna 5: Tempo
    analysisManager->CreateNtupleIColumn("CherenkovPhotonCount"); // Coluna 6: Número de fótons Cherenkov
    analysisManager->CreateNtupleDColumn("EnergyElectronSec");    // Coluna 7: Energia eletrons
    analysisManager->CreateNtupleDColumn("nElectronSec");         // Coluna 8: Número de eletrons secundarios
                                                                  // analysisManager->CreateNtupleDColumn("nCerenkov");            // Coluna 9: Coluna 9: Fótons Cherenkov

    analysisManager->FinishNtuple();
}

void GLRunAction::EndOfRunAction(const G4Run *aRun) {
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

    //   G4int runID = aRun->GetRunID();
    //   G4cout << "Finishing run" << runID << G4endl;

    fTimer->Stop();
    G4cout << "number of event = " << aRun->GetNumberOfEvent()
           << " " << *fTimer << G4endl;

    closeCerenkValid();
    histRun->~histosRun();
}

void GLRunAction::startCerenkValid() {
    analysisManager->CreateH1("1", "PhotoElectrons", 500, 0, 500);
    analysisManager->OpenFile("rootCerenkValid");
}

void GLRunAction::closeCerenkValid() {
    analysisManager->Write();
    analysisManager->CloseFile();
}

void GLRunAction::startCoulombValid() {
    analysisManager->CreateH1("1", "CoulombSomeThing", 500, 0, 500);
    analysisManager->OpenFile("rootCoulombValid");
}

void GLRunAction::closeCoulombValid() {
    analysisManager->Write();
    analysisManager->CloseFile();
}

void GLRunAction::fillHistPhoVcm() {
    histCerVali->doHistCerPhoCm(cerVali->nphoVcm);
}
