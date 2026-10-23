// Geant4 Libraries
//
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

// Local Libraries
//
#include "GLPMTHit.hh"

G4ThreadLocal G4Allocator<PMTHit> *PMTHitAllocator = 0;

PMTHit::PMTHit()
    : waveLength(0.) {}

PMTHit::~PMTHit() {}

G4int PMTHit::askDetected(G4double phoEner) {
    waveLength = 1240. / (phoEner / (1. * eV));

    if (waveLength >= 250. && waveLength < (1240 / 4.2)) //  if(waveLength >= 250. && waveLength < 300.)
    {
        if (G4UniformRand() <= 0.04 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 4.2) && waveLength < (1240 / 4.07)) // alterei
    {
        if (G4UniformRand() <= 0.09 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 4.07) && waveLength < (1240 / 3.94)) // alterei
    {
        if (G4UniformRand() <= 0.14 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.94) && waveLength < (1240 / 3.81)) // alterei
    {
        if (G4UniformRand() <= 0.17 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.81) && waveLength < (1240 / 3.7)) // alterei
    {
        if (G4UniformRand() <= 0.21 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.7) && waveLength < (1240 / 3.59)) // alterei
    {
        if (G4UniformRand() <= 0.22 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.59) && waveLength < (1240 / 3.49)) // alterei
    {
        if (G4UniformRand() <= 0.23 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.49) && waveLength < (1240 / 3.4)) // alterei
    {
        if (G4UniformRand() <= 0.24 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.4) && waveLength < (1240 / 3.31)) // alterei
    {
        if (G4UniformRand() <= 0.24 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.31) && waveLength < (1240 / 3.22)) // alterei
    {
        if (G4UniformRand() <= 0.24 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.22) && waveLength < (1240 / 3.14)) // alterei
    {
        if (G4UniformRand() <= 0.23 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.14) && waveLength < (1240 / 3.06)) // alterei
    {
        if (G4UniformRand() <= 0.22 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 3.06) && waveLength < (1240 / 2.99)) // alterei
    {
        if (G4UniformRand() <= 0.22 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.99) && waveLength < (1240 / 2.92)) // alterei
    {
        if (G4UniformRand() <= 0.21 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.92) && waveLength < (1240 / 2.85)) // alterei
    {
        if (G4UniformRand() <= 0.20 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.85) && waveLength < (1240 / 2.79)) // alterei
    {
        if (G4UniformRand() <= 0.19 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.79) && waveLength < (1240 / 2.72)) // alterei
    {
        if (G4UniformRand() <= 0.18 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.72) && waveLength < (1240 / 2.67)) // alterei
    {
        if (G4UniformRand() <= 0.16 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.67) && waveLength < (1240 / 2.61)) // alterei
    {
        if (G4UniformRand() <= 0.15 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.61) && waveLength < (1240 / 2.56)) // alterei
    {
        if (G4UniformRand() <= 0.13 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.56) && waveLength < (1240 / 2.50)) // alterei
    {
        if (G4UniformRand() <= 0.11 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.50) && waveLength < (1240 / 2.46)) // alterei
    {
        if (G4UniformRand() <= 0.10 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.46) && waveLength < (1240 / 2.41)) // alterei
    {
        if (G4UniformRand() <= 0.09 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.41) && waveLength < (1240 / 2.36)) // alterei
    {
        if (G4UniformRand() <= 0.08 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.36) && waveLength < (1240 / 2.32)) // alterei
    {
        if (G4UniformRand() <= 0.07 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.32) && waveLength < (1240 / 2.27)) // alterei
    {
        if (G4UniformRand() <= 0.06 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.27) && waveLength < (1240 / 2.23)) // alterei
    {
        if (G4UniformRand() <= 0.05 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.23) && waveLength < (1240 / 2.19)) // alterei
    {
        if (G4UniformRand() <= 0.04 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.19) && waveLength < (1240 / 2.16)) // alterei
    {
        if (G4UniformRand() <= 0.03 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.16) && waveLength < (1240 / 2.08)) // alterei
    {
        if (G4UniformRand() <= 0.02 * probaCollect)
            return waveLength;
        else
            return 0;
    } else if (waveLength >= (1240 / 2.08) && waveLength < (650)) // alterei
    {
        if (G4UniformRand() <= 0.02 * probaCollect)
            return waveLength;
        else
            return 0;
    }
}