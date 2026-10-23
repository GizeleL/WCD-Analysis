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
/// \file optical/swgo/src/swgoDetectorMessenger.cc
/// \brief Implementation of the swgoDetectorMessenger class
//
//
#include "GLDetectorMessenger.hh"
#include "GLDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Scintillation.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GLDetectorMessenger::GLDetectorMessenger(GLDetectorConstruction *detector)
    : fGLDetector(detector) {
    // Setup a command directory for detector controls with guidance
    fDetectorDir = new G4UIdirectory("/swgo/detector/");
    fDetectorDir->SetGuidance("Detector geometry control");

    fVolumesDir = new G4UIdirectory("/swgo/detector/volumes/");
    fVolumesDir->SetGuidance("Enable/disable volumes");

    // Various commands for modifying detector geometry
    fDimensionsCmd =
        new G4UIcmdWith3VectorAndUnit("/swgo/detector/dimensions", this);
    fDimensionsCmd->SetGuidance("Set the dimensions of the detector volume.");
    fDimensionsCmd->SetParameterName("scint_x", "scint_y", "scint_z", false);
    fDimensionsCmd->SetDefaultUnit("cm");
    fDimensionsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fDimensionsCmd->SetToBeBroadcasted(false);

    fHousingThicknessCmd =
        new G4UIcmdWithADoubleAndUnit("/swgo/detector/housingThickness", this);
    fHousingThicknessCmd->SetGuidance("Set the thickness of the housing.");
    fHousingThicknessCmd->SetParameterName("d_mtl", false);
    fHousingThicknessCmd->SetDefaultUnit("cm");
    fHousingThicknessCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fHousingThicknessCmd->SetToBeBroadcasted(false);

    fPmtRadiusCmd =
        new G4UIcmdWithADoubleAndUnit("/swgo/detector/pmtRadius", this);
    fPmtRadiusCmd->SetGuidance("Set the radius of the PMTs.");
    fPmtRadiusCmd->SetParameterName("radius", false);
    fPmtRadiusCmd->SetDefaultUnit("cm");
    fPmtRadiusCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fPmtRadiusCmd->SetToBeBroadcasted(false);

    fNxCmd = new G4UIcmdWithAnInteger("/swgo/detector/nx", this);
    fNxCmd->SetGuidance("Set the number of PMTs along the x-dimension.");
    fNxCmd->SetParameterName("nx", false);
    fNxCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fNxCmd->SetToBeBroadcasted(false);

    fNyCmd = new G4UIcmdWithAnInteger("/swgo/detector/ny", this);
    fNyCmd->SetGuidance("Set the number of PMTs along the y-dimension.");
    fNyCmd->SetParameterName("ny", false);
    fNyCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fNyCmd->SetToBeBroadcasted(false);

    fNzCmd = new G4UIcmdWithAnInteger("/swgo/detector/nz", this);
    fNzCmd->SetGuidance("Set the number of PMTs along the z-dimension.");
    fNzCmd->SetParameterName("nz", false);
    fNzCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fNzCmd->SetToBeBroadcasted(false);

    fSphereCmd = new G4UIcmdWithABool("/swgo/detector/volumes/sphere", this);
    fSphereCmd->SetGuidance("Enable/Disable the sphere.");
    fSphereCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fSphereCmd->SetToBeBroadcasted(false);

    fReflectivityCmd = new G4UIcmdWithADouble("/swgo/detector/reflectivity", this);
    fReflectivityCmd->SetGuidance("Set the reflectivity of the housing.");
    fReflectivityCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fReflectivityCmd->SetToBeBroadcasted(false);

    fWlsCmd = new G4UIcmdWithABool("/swgo/detector/volumes/wls", this);
    fWlsCmd->SetGuidance("Enable/Disable the WLS slab");
    fWlsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fWlsCmd->SetToBeBroadcasted(false);

    // fswgoCmd = new G4UIcmdWithABool("/swgo/detector/volumes/swgo", this);
    // fswgoCmd->SetGuidance("Enable/Disable the main detector volume.");
    // fswgoCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    // fswgoCmd->SetToBeBroadcasted(false);

    // fNFibersCmd = new G4UIcmdWithAnInteger("/swgo/detector/nfibers", this);
    // fNFibersCmd->SetGuidance("Set the number of WLS fibers in the WLS slab.");
    // fNFibersCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    // fNFibersCmd->SetToBeBroadcasted(false);

    // fMainScintYield =
    //     new G4UIcmdWithADouble("/swgo/detector/MainScintYield", this);
    // fMainScintYield->SetGuidance("Set scinitillation yield of main volume.");
    // fMainScintYield->SetGuidance("Specified in photons/MeV");
    // fMainScintYield->AvailableForStates(G4State_PreInit, G4State_Idle);
    // fMainScintYield->SetToBeBroadcasted(false);

    // fWLSScintYield = new G4UIcmdWithADouble("/swgo/detector/WLSScintYield", this);
    // fWLSScintYield->SetGuidance("Set scintillation yield of WLS Slab");
    // fWLSScintYield->SetGuidance("Specified in photons/MeV");
    // fWLSScintYield->AvailableForStates(G4State_PreInit, G4State_Idle);
    // fWLSScintYield->SetToBeBroadcasted(false);

    // fSaveThresholdCmd = new G4UIcmdWithAnInteger("/swgo/saveThreshold", this);
    // fSaveThresholdCmd->SetGuidance(
    //     "Set the photon count threshold for saving the random number seed");
    // fSaveThresholdCmd->SetParameterName("photons", true);
    // fSaveThresholdCmd->SetDefaultValue(4500);
    // fSaveThresholdCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    // fDefaultsCmd = new G4UIcommand("/swgo/detector/defaults", this);
    // fDefaultsCmd->SetGuidance("Set all detector geometry values to defaults.");
    // fDefaultsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    // fDefaultsCmd->SetToBeBroadcasted(false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GLDetectorMessenger::~GLDetectorMessenger() {
    delete fDimensionsCmd;
    delete fHousingThicknessCmd;
    delete fPmtRadiusCmd;
    delete fNxCmd;
    delete fNyCmd;
    delete fNzCmd;
    delete fSphereCmd;
    delete fWlsCmd;
    // delete fswgoCmd;
    delete fNFibersCmd;
    delete fReflectivityCmd;
    delete fMainScintYield;
    delete fWLSScintYield;
    delete fSaveThresholdCmd;
    delete fDefaultsCmd;
    delete fDetectorDir;
    delete fVolumesDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GLDetectorMessenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if (command == fDimensionsCmd) {
        fGLDetector->SetDimensions(fDimensionsCmd->GetNew3VectorValue(newValue));
    }
    // } else if (command == fHousingThicknessCmd) {
    //     fswgoDetector->SetHousingThickness(
    //         fHousingThicknessCmd->GetNewDoubleValue(newValue));
    // } else if (command == fPmtRadiusCmd) {
    //     fswgoDetector->SetPMTRadius(fPmtRadiusCmd->GetNewDoubleValue(newValue));
    // } else if (command == fNxCmd) {
    //     fswgoDetector->SetNX(fNxCmd->GetNewIntValue(newValue));
    // } else if (command == fNyCmd) {
    //     fswgoDetector->SetNY(fNyCmd->GetNewIntValue(newValue));
    // } else if (command == fNzCmd) {
    //     fswgoDetector->SetNZ(fNzCmd->GetNewIntValue(newValue));
    // } else if (command == fSphereCmd) {
    //     fswgoDetector->SetSphereOn(fSphereCmd->GetNewBoolValue(newValue));
    // } else if (command == fReflectivityCmd) {
    //     fswgoDetector->SetHousingReflectivity(
    //         fReflectivityCmd->GetNewDoubleValue(newValue));
    // } else if (command == fWlsCmd) {
    //     fswgoDetector->SetWLSSlabOn(fWlsCmd->GetNewBoolValue(newValue));
    // } else if (command == fswgoCmd) {
    //     fswgoDetector->SetMainVolumeOn(fswgoCmd->GetNewBoolValue(newValue));
    // } else if (command == fNFibersCmd) {
    //     fswgoDetector->SetNFibers(fNFibersCmd->GetNewIntValue(newValue));
    // } else if (command == fMainScintYield) {
    //     fswgoDetector->SetMainScintYield(
    //         fMainScintYield->GetNewDoubleValue(newValue));
    // } else if (command == fWLSScintYield) {
    //     fswgoDetector->SetWLSScintYield(fWLSScintYield->GetNewDoubleValue(newValue));
    // } else if (command == fSaveThresholdCmd) {
    //     fswgoDetector->SetSaveThreshold(fSaveThresholdCmd->GetNewIntValue(newValue));
    // } else if (command == fDefaultsCmd) {
    //     fswgoDetector->SetDefaults();
    //     G4RunManager::GetRunManager()->ReinitializeGeometry();
    // }
}
