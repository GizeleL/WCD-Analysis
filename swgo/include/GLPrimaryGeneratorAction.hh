#ifndef GLPRIMARYGENERATORACTION_HH
#define GLPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;
class GLDetectorConstruction;

class GLPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    GLPrimaryGeneratorAction();
    ~GLPrimaryGeneratorAction();
    // ~GPPrimaryGeneratorAction() override;

    virtual void GeneratePrimaries(G4Event *);
    // void GeneratePrimaries(G4Event *);
    // void GeneratePrimaries(G4Event *) override;

    std::string primaryId;
    //  G4ThreeVector position;
    // G4ThreeVector direction;

    double GetEnergy();
    // G4double x, y, z;
    // G4ThreeVector position(G4double x, G4double y, G4double z);
    // double GetPosX();
    // double GetPosY();

  private:
    G4GeneralParticleSource *fGeneralParticleSource = nullptr;
    GLDetectorConstruction *Detector;

    // G4double x, y, z;
    G4double px, py, pz;
};

#endif