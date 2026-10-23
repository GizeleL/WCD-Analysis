#ifndef PMTHit_HH
#define PMTHit_HH

// Geant4 Libraries
//
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4VHit.hh"
#include "G4VPhysicalVolume.hh"

#include "tls.hh"

// Local Libraries
//

class G4VTouchable;
class PMTHit //: public G4VHit
{

  public:
    PMTHit();
    virtual ~PMTHit();
    G4int askDetected(G4double);
    void reset();

  private:
    G4double waveLength;
    double probaCollect = 1.0; // versão TANCA ==>bib
};
#endif
