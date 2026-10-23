#include "GLRunAction.hh"
#include "G4AccumulableManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4Timer.hh"
#include "G4Types.hh"
#include "G4VVisManager.hh"
#include <iostream>

GLRunAction::GLRunAction() : G4UserRunAction(), fTimer(0) {
    G4cout << "...RunAction..." << G4endl;
    fTimer = new G4Timer;

    // Unidades
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->CreateNtuple("Data", "all");
    analysisManager->CreateNtupleIColumn("iEventID");              // Coluna 0
    analysisManager->CreateNtupleDColumn("EnergyDeposited_MeV");   // Coluna 1
    analysisManager->CreateNtupleDColumn("PositionX_cm");          // Coluna 2
    analysisManager->CreateNtupleDColumn("PositionY_cm");          // Coluna 3
    analysisManager->CreateNtupleDColumn("PositionZ_cm");          // Coluna 4
    analysisManager->CreateNtupleDColumn("Time_ns");               // Coluna 5
    analysisManager->CreateNtupleDColumn("EnergyElectronSec_MeV"); // Coluna 6
    analysisManager->CreateNtupleDColumn("nElectronSec");          // Coluna 7
    analysisManager->CreateNtupleDColumn("nCerenkovByMuon");       // Coluna 8
    analysisManager->CreateNtupleDColumn("nCerenkovByElectron");   // Coluna 9
    analysisManager->CreateNtupleDColumn("EdepGammas_MeV");        // Coluna 10
    analysisManager->CreateNtupleDColumn("EdepTrack_MeV");         // Coluna 11
    analysisManager->FinishNtuple();

    // Ntuple 1 — PMTs
    analysisManager->CreateNtuple("PMTData", "pmt");
    analysisManager->CreateNtupleIColumn("iEventID");    // Coluna 0
    analysisManager->CreateNtupleIColumn("nFotonsPMT1"); // Coluna 1
    analysisManager->CreateNtupleIColumn("nFotonsPMT2"); // Coluna 2
    analysisManager->CreateNtupleIColumn("nFotonsPMT3"); // Coluna 3
    analysisManager->CreateNtupleIColumn("nFotonsPMT4"); // Coluna 4
    analysisManager->FinishNtuple();

    // Ntuple 2 — Hodoscópio
    analysisManager->CreateNtuple("HodoData", "hodoscope");
    analysisManager->CreateNtupleIColumn("iEventID"); // Coluna 0
    analysisManager->CreateNtupleIColumn("ColumnID"); // Coluna 1
    analysisManager->CreateNtupleIColumn("RowID");    // Coluna 2
    analysisManager->CreateNtupleDColumn("Edep_MeV"); // Coluna 3
    analysisManager->CreateNtupleDColumn("Time_ns");  // Coluna 4
    analysisManager->FinishNtuple();

    // Ntuple 3 — RPCs
    analysisManager->CreateNtuple("RPCData", "rpcs");
    analysisManager->CreateNtupleIColumn("iEventID"); // Coluna 0
    analysisManager->CreateNtupleIColumn("RPCID");    // Coluna 1 — qual RPC (2,3,4,5)
    analysisManager->CreateNtupleIColumn("ColumnID"); // Coluna 2
    analysisManager->CreateNtupleIColumn("RowID");    // Coluna 3
    analysisManager->CreateNtupleDColumn("Edep_MeV"); // Coluna 4
    analysisManager->CreateNtupleDColumn("Time_ns");  // Coluna 5
    analysisManager->FinishNtuple();
}

GLRunAction::~GLRunAction() {
    delete fTimer;
}

void GLRunAction::BeginOfRunAction(const G4Run *aRun) {
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    fTimer->Start();

    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    // if (!analysisManager->OpenFile("SWGO_gamma500MeV_1000ev.csv")) {
    //  if (!analysisManager->OpenFile("SWGO_muon5GeV_vertical_1000ev.csv")) {
    //   if (!analysisManager->OpenFile("SWGO_muon5GeV_10deg_1000ev.csv")) {
    //   if (!analysisManager->OpenFile("SWGO_muon5GeV_15deg_1000ev.csv")) {
    //   if (!analysisManager->OpenFile("SWGO_muon5GeV_30deg_1000ev.csv")) {
    //   if (!analysisManager->OpenFile("SWGO_muon5GeV_45deg_1000ev.csv")) {
    //      if (!analysisManager->OpenFile("SWGO_muon5GeV_60deg_1000ev.csv")) {
    // if (!analysisManager->OpenFile("SWGO_gamma500MeV_absL1_10ev.csv")) {
    if (!analysisManager->OpenFile("SWGO_gamma100MeV_absL1_10ev.csv")) {
        G4ExceptionDescription msg;
        msg << "Failed to open output file.";
        G4Exception("GLRunAction::BeginOfRunAction()", "Analysis001", FatalException, msg);
    }
}

void GLRunAction::EndOfRunAction(const G4Run *aRun) {
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsOpenFile()) {
        analysisManager->Write();
        analysisManager->CloseFile();
        G4cout << "Arquivo de saída salvo e fechado." << G4endl;
    }

    fTimer->Stop();
}