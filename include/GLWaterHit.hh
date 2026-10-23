#ifndef GLWaterHit_HH
#define GLWaterHit_HH

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4VPhysicalVolume.hh"

class GLWaterHit : public G4VHit {
  public:
    GLWaterHit();
    GLWaterHit(G4VPhysicalVolume *pVol);
    ~GLWaterHit();

    GLWaterHit(const GLWaterHit &right);
    const GLWaterHit &operator=(const GLWaterHit &right);
    G4bool operator==(const GLWaterHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    inline void SetTrackEdep(G4double tedep) { fTrackEdep = tedep; }
    inline G4double GetTrackEdep() const { return fTrackEdep; }

    inline void SetEdep(G4double de) { fEdep = de; }
    inline void AddEdep(G4double de) { fEdep += de; }
    inline G4double GetEdep() { return fEdep; }

    inline void SetParticle(G4String name) { particleName = name; };
    inline void SetSecondaryParticle(G4String name) { secondaryname = name; };
    inline void SetNumberSecondary(G4int ns) { fNumberSecondary = ns; };
    inline void SetParticleProcess(G4String name) { process = name; };

    inline void SetSecondaryElectronEnergy(G4double se) { secondaryenergy_electron_sum = se; };
    inline void SetSecondaryElectronCount(G4double sec) { secondaryelectron_count = sec; };
    inline void SetSecondaryCerenkovEnergy(G4double sc) { secondaryenergy_cerenkov_sum = sc; };
    inline void SetSecondaryCerenkovCount(G4double scc) { secondarycerenkov_count = scc; };
    inline void SetSecondaryCerenkovMuonCount(G4double scc) { secondarycerenkov_muon_count = scc; };
    inline void SetSecondaryCerenkovElectronCount(G4double scc) { secondarycerenkov_electron_count = scc; };
    inline void SetSecondaryScintillationEnergy(G4double ss) { secondaryenergy_scintillation_sum = ss; };
    inline void SetSecondaryScintillationCount(G4double ssc) { secondaryscintillation_count = ssc; };
    inline void SetSecondaryScintillationMuonCount(G4double ssc) { secondaryscintillation_muon_count = ssc; };
    inline void SetSecondaryScintillationElectronCount(G4double ssc) { secondaryscintillation_electron_count = ssc; };

    void SetTime(G4double t2) { fTime = t2; };
    // inline void SetTime(G4double val) { ftimeScint = val; }
    // inline G4double GetTime() const { return ftimeScint; }
    G4double GetTime() { return fTime; };
    G4int GetNumberSecondary() { return fNumberSecondary; };
    G4String GetParticle() { return particleName; };
    G4String GetSecondaryParticle() { return secondaryname; };
    G4String GetParticleProcess() { return process; };
    G4double GetSecondaryElectronEnergy() { return secondaryenergy_electron_sum; };
    G4double GetSecondaryElectronCount() { return secondaryelectron_count; };
    G4double GetSecondaryCerenkovEnergy() { return secondaryenergy_cerenkov_sum; };
    G4double GetSecondaryCerenkovCount() { return secondarycerenkov_count; };
    G4double GetSecondaryCerenkovMuonCount() { return secondarycerenkov_muon_count; };
    G4double GetSecondaryCerenkovElectronCount() { return secondarycerenkov_electron_count; };
    G4double GetSecondaryScintillationEnergy() { return secondaryenergy_scintillation_sum; };
    G4double GetSecondaryScintillationCount() { return secondaryscintillation_count; };
    G4double GetSecondaryScintillationMuonCount() { return secondaryscintillation_muon_count; };
    G4double GetSecondaryScintillationElectronCount() { return secondaryscintillation_electron_count; };

    inline void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    inline G4ThreeVector GetPos() { return fPos; }

    inline const G4VPhysicalVolume *GetPhysV() { return fPhysVol; }

  private:
    G4double fTrackEdep; // Energia total depositada por track

    G4double fEdep;
    G4int fNumberSecondary;
    G4double fTime;
    G4ThreeVector fPos;
    G4String particleName;
    G4String secondaryname;
    G4String process;

    const G4VPhysicalVolume *fPhysVol;
    G4double secondaryenergy_electron_sum;
    G4double secondaryelectron_count;
    G4double secondaryenergy_cerenkov_sum;
    G4double secondarycerenkov_count;
    G4double secondarycerenkov_muon_count;
    G4double secondarycerenkov_electron_count;
    G4double secondaryenergy_scintillation_sum;
    G4double secondaryscintillation_count;
    G4double secondaryscintillation_muon_count;
    G4double secondaryscintillation_electron_count;
};

// Water collection allocator
typedef G4THitsCollection<GLWaterHit> GLWaterHitsCollection;

extern G4ThreadLocal G4Allocator<GLWaterHit> *GLWaterHitAllocator;

inline void *GLWaterHit::operator new(size_t) {
    if (!GLWaterHitAllocator)
        GLWaterHitAllocator = new G4Allocator<GLWaterHit>;
    return (void *)GLWaterHitAllocator->MallocSingle();
}

inline void GLWaterHit::operator delete(void *aHit) {
    GLWaterHitAllocator->FreeSingle((GLWaterHit *)aHit);
}

#endif