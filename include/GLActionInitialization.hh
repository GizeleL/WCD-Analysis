#ifndef GLACTIONINITIALIZATION_HH
#define GLACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class GLDetectorConstruction;

class GLActionInitialization : public G4VUserActionInitialization {
  public:
    GLActionInitialization(GLDetectorConstruction *det);
    virtual ~GLActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    GLDetectorConstruction *fDetector;
};

#endif