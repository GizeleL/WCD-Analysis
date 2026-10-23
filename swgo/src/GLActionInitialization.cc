#include "GLActionInitialization.hh"
#include "GLDetectorConstruction.hh"
#include "GLEventAction.hh"
#include "GLPrimaryGeneratorAction.hh"
#include "GLRunAction.hh"
#include "GLSteppingAction.hh"

GLActionInitialization::GLActionInitialization(GLDetectorConstruction *det)
    : G4VUserActionInitialization(), fDetector(det) {
    //  G4cout << "...ActionInitialization..." << G4endl;
}
GLActionInitialization::~GLActionInitialization() {}

void GLActionInitialization::BuildForMaster() const {
    GLRunAction *runAction = new GLRunAction; // for analysis manager outputs
    SetUserAction(runAction);
}

void GLActionInitialization::Build() const {
    GLRunAction *runAction = new GLRunAction;
    SetUserAction(runAction);

    GLPrimaryGeneratorAction *generator = new GLPrimaryGeneratorAction();
    SetUserAction(generator);

    GLEventAction *eventAction = new GLEventAction(runAction, generator, fDetector);
    SetUserAction(eventAction);

    GLSteppingAction *stepAction = new GLSteppingAction(eventAction);
    SetUserAction(stepAction);
}
