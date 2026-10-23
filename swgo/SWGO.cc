// #include <iostream>

#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VUserDetectorConstruction.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4VisExecutive.hh"
#include "G4VisManager.hh"

#include "QGSP_BERT_HP.hh"

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

    // G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    // #ifdef G4MULTITHREADED
    //     G4MTRunManager *runManager = new G4MTRunManager();
    // #else

    // G4UIExecutive *ui = nullptr;
    // if (argc == 1) {
    //     ui = new G4UIExecutive(argc, argv);
    // }

    // Instantiate G4UIExecutive if interactive mode
    G4String macro;
    G4UIExecutive *ui = nullptr;
    if (macro.size() == 0) {
        ui = new G4UIExecutive(argc, argv);
    }

    // auto runManager = G4RunManagerFactory::CreateRunManager();

    G4RunManager *runManager = new G4RunManager();

    // Place the world
    GLDetectorConstruction *det = new GLDetectorConstruction();
    runManager->SetUserInitialization(det);
    // runManager->SetUserInitialization(new GLDetectorConstruction());

    // PhysicsLists
    G4String physName = "QGSP_BERT_HP";
    runManager->SetUserInitialization(new PhysicsList(physName));

    runManager->SetUserInitialization(new GLActionInitialization(det));
    runManager->Initialize();

    G4VisManager *visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (macro.size()) {

        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);

        delete ui;
    } else // Define UI session for interactive mode
    {
        UImanager->ApplyCommand("/control/execute vis.mac");
        if (ui->IsGUI())
            UImanager->ApplyCommand("/control/execute gui.mac");
        ui->SessionStart();
    }

    // G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    // if (ui) {
    //     UImanager->ApplyCommand("/control/execute vis.mac");
    //     //  UImanager->ApplyCommand("/control/execute muon.mac");
    //     if (ui->IsGUI()) {
    //         UImanager->ApplyCommand("/control/execute gui.mac");
    //     }
    //     ui->SessionStart();
    //     delete ui;
    // } else {
    //     // batch mode
    //     G4String command = "/control/execute ";
    //     G4String fileName = argv[1];
    //     UImanager->ApplyCommand(command + fileName);
    // }

    // job termination
    delete visManager;
    delete runManager;

    // #ifdef G4VIS_USE
    //     delete visManager;
    // #endif
    //     delete runManager;

    // visManager->Initialize();
    // ui->SessionStart();

    return 0;
}
