#include "Hodoscope1Hit.hh"
#include "Hodoscope1SD.hh"

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"

#include "GLActionInitialization.hh"
#include "GLDetectorConstruction.hh"
#include "GLPrimaryGeneratorAction.hh"
#include "GLRunAction.hh"

#include "ExtraPhysics.hh"
#include "OpticalPhysics.hh"
#include "PhysicsList.hh"
#include "StepMax.hh"

#include "G4Types.hh"

int main(int argc, char **argv) {

    // Modo batch (com macro) ou interativo (sem macro)
    G4String macro;
    G4UIExecutive *ui = nullptr;
    if (argc > 1) {
        macro = argv[1];
    } else {
        ui = new G4UIExecutive(argc, argv);
    }

    // RunManager
    G4RunManager *runManager = new G4RunManager();

    // Geometria
    GLDetectorConstruction *det = new GLDetectorConstruction();
    runManager->SetUserInitialization(det);

    // Física
    G4String physName = "QGSP_BERT_HP";
    runManager->SetUserInitialization(new PhysicsList(physName));

    // Ações
    runManager->SetUserInitialization(new GLActionInitialization(det));
    runManager->Initialize();

    // Visualização
    G4VisManager *visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // UI
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (macro.size()) {
        // Modo batch
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);
    } else {
        // Modo interativo
        UImanager->ApplyCommand("/control/execute vis.mac");
        if (ui->IsGUI())
            UImanager->ApplyCommand("/control/execute gui.mac");
        ui->SessionStart();
        delete ui;
    }

    // Limpeza
    delete visManager;
    delete runManager;

    return 0;
}