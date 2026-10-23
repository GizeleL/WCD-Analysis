#include "../include/GLPrimaryGeneratorAction.hh"
#include "../include/GLDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

GLPrimaryGeneratorAction::GLPrimaryGeneratorAction() {
    fGeneralParticleSource = new G4GeneralParticleSource();
    G4double x = 0. * CLHEP::m;
    G4double y = 0. * CLHEP::m;
    G4double z = 2. * CLHEP::m;

    G4ThreeVector position(x, y, z);

    G4double px = 0.;
    G4double py = 0.;
    G4double pz = -3.;

    G4ThreeVector Mom(px, py, pz);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    primaryId = "mu-";
    G4ParticleDefinition *particle = particleTable->FindParticle(primaryId);
    fGeneralParticleSource->SetParticlePosition(position);

    // Particle definition
    fGeneralParticleSource->GetCurrentSource()->SetParticleDefinition(G4MuonMinus::MuonMinusDefinition());
    // Energy definition
    fGeneralParticleSource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(5.0 * GeV);
    // Position definiton
    fGeneralParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(position);
    // Direction definition
    fGeneralParticleSource->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(Mom);
}

GLPrimaryGeneratorAction::~GLPrimaryGeneratorAction() {
    delete fGeneralParticleSource;
}
void GLPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    fGeneralParticleSource->GeneratePrimaryVertex(anEvent);
}

double GLPrimaryGeneratorAction::GetEnergy() {

    return fGeneralParticleSource->GetParticleEnergy();
}

// double GLPrimaryGeneratorAction::GetPosX() {
//     return GetParticlePosition().x();
// }

// double GLPrimaryGeneratorAction::GetPosY() {
//     return GetParticlePosition().y();
// }