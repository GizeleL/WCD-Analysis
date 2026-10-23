// Geant4 Libraries
//
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"

// Local Libraries
//

#include "GLwater.hh"

water::water() {
    G4cout << "...Creating water..." << G4endl;

    O = H = NULL;
    thewater = NULL;
    a = z = density = 0.;
}

water::~water() {}

G4Material *water::doWater() {

    O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * (g / mole));
    H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * (g / mole));

    thewater = new G4Material("Water", density = 1.0 * (g / cm3), 2);

    thewater->AddElement(H, 2);
    thewater->AddElement(O, 1);

    return thewater;
}

G4MaterialPropertiesTable *water::doOpwater() {

    // Water matrial properties
    std::vector<G4double> photonEnergy = {
        2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
        2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
        2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
        4.002 * eV, 4.136 * eV};

    std::vector<G4double> refractiveIndex1 = {
        1.3435, 1.344, 1.3445, 1.345, 1.3455, 1.346, 1.3465, 1.347,
        1.3475, 1.348, 1.3485, 1.3492, 1.35, 1.3505, 1.351, 1.3518,
        1.3522, 1.3530, 1.3535, 1.354, 1.3545, 1.355, 1.3555, 1.356,
        1.3568, 1.3572, 1.358, 1.3585, 1.359, 1.3595, 1.36, 1.3608};

    float absLength = 1.0;

    std::vector<G4double> absorption = {
        3.448 * absLength * m, 4.082 * absLength * m, 6.329 * absLength * m, 9.174 * absLength * m, 12.346 * absLength * m, 13.889 * absLength * m,
        15.152 * absLength * m, 17.241 * absLength * m, 18.868 * absLength * m, 20.000 * absLength * m, 26.316 * absLength * m, 35.714 * absLength * m,
        45.455 * absLength * m, 47.619 * absLength * m, 52.632 * absLength * m, 52.632 * absLength * m, 55.556 * absLength * m, 52.632 * absLength * m,
        52.632 * absLength * m, 47.619 * absLength * m, 45.455 * absLength * m, 41.667 * absLength * m, 37.037 * absLength * m, 33.333 * absLength * m,
        30.000 * absLength * m, 28.500 * absLength * m, 27.000 * absLength * m, 24.500 * absLength * m, 22.000 * absLength * m, 19.500 * absLength * m,
        17.500 * absLength * m, 14.500 * absLength * m};

    // Material properties can be added as arrays. However, in this case it is
    // up to the user to make sure both arrays have the same number of elements.
    // G4double scintilFastArray[]{ 1.0, 1.0 };
    // G4double energyArray[]{ 2.034 * eV, 4.136 * eV };
    // G4int lenArray = 2;

    // std::vector<G4double> scintilSlow = {
    //   0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
    //   7.00, 6.00, 4.00, 3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00, 4.00,
    //   5.00, 6.00, 7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 5.00, 4.00
    // };

    G4MaterialPropertiesTable *fWater_mt = new G4MaterialPropertiesTable();

    // Values can be added to the material property table individually.
    // With this method, spline interpolation cannot be set. Arguments
    // createNewKey and spline both take their default values of false.
    // Need to specify the number of entries (1) in the arrays, as an argument
    // to AddProperty.
    G4int numEntries = 1;
    fWater_mt->AddProperty("RINDEX", &photonEnergy[0], &refractiveIndex1[0],
                           numEntries);

    for (size_t i = 1; i < photonEnergy.size(); ++i) {
        fWater_mt->AddEntry("RINDEX", photonEnergy[i], refractiveIndex1[i]);
    }

    // Check that group velocity is calculated from RINDEX
    if (fWater_mt->GetProperty("RINDEX")->GetVectorLength() !=
        fWater_mt->GetProperty("GROUPVEL")->GetVectorLength()) {
        G4ExceptionDescription ed;
        ed << "Error calculating group velocities. Incorrect number of entries "
              "in group velocity material property vector.";
        G4Exception("LXe::LXeDetectorConstruction", "LXe001",
                    FatalException, ed);
    }

    // Adding a property from two std::vectors. Argument createNewKey is false
    // and spline is true.
    fWater_mt->AddProperty("ABSLENGTH", photonEnergy, absorption, false, true);

    // => remove the proprety for water = > Scintilation
    // Adding a property using a C-style array.
    // Spline interpolation isn't used for scintillation.
    // Arguments spline and createNewKey both take default value false.
    // fWater_mt->AddProperty("SCINTILLATIONCOMPONENT1", energyArray, scintilFastArray,
    //                        lenArray);

    // fWater_mt->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintilSlow,
    //                     false, true);
    // fWater_mt->AddConstProperty("SCINTILLATIONYIELD", 50. / MeV);
    // fWater_mt->AddConstProperty("RESOLUTIONSCALE", 1.0);
    // fWater_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1. * ns);
    // fWater_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 10. * ns);
    // fWater_mt->AddConstProperty("SCINTILLATIONYIELD1", 0.8);
    // fWater_mt->AddConstProperty("SCINTILLATIONYIELD2", 0.2);

    std::vector<G4double> energy_water = {
        1.56962 * eV, 1.58974 * eV, 1.61039 * eV, 1.63157 * eV, 1.65333 * eV,
        1.67567 * eV, 1.69863 * eV, 1.72222 * eV, 1.74647 * eV, 1.77142 * eV,
        1.7971 * eV, 1.82352 * eV, 1.85074 * eV, 1.87878 * eV, 1.90769 * eV,
        1.93749 * eV, 1.96825 * eV, 1.99999 * eV, 2.03278 * eV, 2.06666 * eV,
        2.10169 * eV, 2.13793 * eV, 2.17543 * eV, 2.21428 * eV, 2.25454 * eV,
        2.29629 * eV, 2.33962 * eV, 2.38461 * eV, 2.43137 * eV, 2.47999 * eV,
        2.53061 * eV, 2.58333 * eV, 2.63829 * eV, 2.69565 * eV, 2.75555 * eV,
        2.81817 * eV, 2.88371 * eV, 2.95237 * eV, 3.02438 * eV, 3.09999 * eV,
        3.17948 * eV, 3.26315 * eV, 3.35134 * eV, 3.44444 * eV, 3.54285 * eV,
        3.64705 * eV, 3.75757 * eV, 3.87499 * eV, 3.99999 * eV, 4.13332 * eV,
        4.27585 * eV, 4.42856 * eV, 4.59258 * eV, 4.76922 * eV, 4.95999 * eV,
        5.16665 * eV, 5.39129 * eV, 5.63635 * eV, 5.90475 * eV, 6.19998 * eV};

    // Rayleigh scattering length is calculated by G4OpRayleigh

    // Mie: assume 100 times larger than the rayleigh scattering
    std::vector<G4double> mie_water = {
        167024.4 * m, 158726.7 * m, 150742 * m, 143062.5 * m, 135680.2 * m,
        128587.4 * m, 121776.3 * m, 115239.5 * m, 108969.5 * m, 102958.8 * m,
        97200.35 * m, 91686.86 * m, 86411.33 * m, 81366.79 * m, 76546.42 * m,
        71943.46 * m, 67551.29 * m, 63363.36 * m, 59373.25 * m, 55574.61 * m,
        51961.24 * m, 48527.00 * m, 45265.87 * m, 42171.94 * m, 39239.39 * m,
        36462.50 * m, 33835.68 * m, 31353.41 * m, 29010.30 * m, 26801.03 * m,
        24720.42 * m, 22763.36 * m, 20924.88 * m, 19200.07 * m, 17584.16 * m,
        16072.45 * m, 14660.38 * m, 13343.46 * m, 12117.33 * m, 10977.70 * m,
        9920.416 * m, 8941.407 * m, 8036.711 * m, 7202.470 * m, 6434.927 * m,
        5730.429 * m, 5085.425 * m, 4496.467 * m, 3960.210 * m, 3473.413 * m,
        3032.937 * m, 2635.746 * m, 2278.907 * m, 1959.588 * m, 1675.064 * m,
        1422.710 * m, 1200.004 * m, 1004.528 * m, 833.9666 * m, 686.1063 * m};

    // Mie: gforward, gbackward, forward backward ratio
    G4double mie_water_const[3] = {0.99, 0.99, 0.8};

    // Correção para melhorar performance -> retirar o Mie
    // fWater_mt->AddProperty("MIEHG", energy_water, mie_water, false, true);
    // fWater_mt->AddConstProperty("MIEHG_FORWARD", mie_water_const[0]);
    // fWater_mt->AddConstProperty("MIEHG_BACKWARD", mie_water_const[1]);
    // fWater_mt->AddConstProperty("MIEHG_FORWARD_RATIO", mie_water_const[2]);

    thewater->SetMaterialPropertiesTable(fWater_mt);

    // the Birks Constant is contant for all materials
    //  thewater->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);

    G4cout << "G4MaterialPropertiesTable for Water is OK... " << G4endl;
    // fWater_mt->DumpTable();

    return fWater_mt; //  water->SetMaterialPropertiesTable(fWater_mt);
}
