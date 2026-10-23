#ifndef histosRun_h
#define histosRun_h 1

// C++ Libraries
//
#include <vector>

// Geant4 Libraries
//

// Root Libraries
//
class TFile;
class TTree;
class TH1F;
class TH1I;
class TH2D;
class TH1D;

// Local Libraries
//

class histosRun {
  public:
    histosRun();
    ~histosRun();

    // ===========================
    // *** Initializing histos ***
    void initHistos();

    // ===================
    // *** For photons ***
    void cerenPho(int optCerenPho);
    void fillCerenPho(int optFillPho);

    //////////////////////////////////////////PMT
    void cerenPhoPmt(int optCerenPhoPmt);
    void fillCerenPhoPmt(int optFillPhoPmt2);

    void cerenPhoElect(int optCerenPhoElect, int wl);
    void fillCerenPhoElect(int optCerenPhoElect);

    // ==============
    // *** Pulses ***
    void meanPulse(int optMeanPulse, double time);
    //////////////////////////////////////////// PMT2

    void cerenPhoPmt2(int optCerenPhoPmt2);
    void fillCerenPhoPmt2(int optFillPhoPmt2);

    void cerenPhoElect2(int optCerenPhoElect, int wl);
    void fillCerenPhoElect2(int optCerenPhoElect);

    // ==============
    // *** Pulses ***
    void meanPulse2(int optMeanPulse, double time);

    //////////////////////////////////////////// PMT3

    void cerenPhoPmt3(int optCerenPhoPmt3);
    void fillCerenPhoPmt3(int optFillPhoPmt3);

    void cerenPhoElect3(int optCerenPhoElect, int wl);
    void fillCerenPhoElect3(int optCerenPhoElect);

    // ==============
    // *** Pulses ***
    void meanPulse3(int optMeanPulse, double time);

    //////////////////////////////////////////PMT
    void cerenPhoPmtAll(int optCerenPhoPmt);
    void fillCerenPhoPmtAll(int optFillPhoPmt2);

    void cerenPhoElectAll(int optCerenPhoElect, int wl);
    void fillCerenPhoElectAll(int optCerenPhoElect);

    // ==============
    // *** Pulses ***
    void meanPulseAll(int optMeanPulse, double time);
    ////////////////////////////////////////////

    /////////////////////////////////////////////////
    // =======================
    // *** inside detector ***
    void trackLengthDetec(int optLengthDectec, double length, double energy);
    void fillTrackLengthDetec(int optFillLengthDectec);

    // ================
    // *** Injected ***
    void distInject(int part);
    void postInject(double partPosX, double partPosY);

    void histPartEnergy(double energy);
    //====================
    //*** FillColor ***
    // void FillColorinhistogram();

  private:
    // ===================
    // *** Output File ***
    TFile *histosOutput;

    // Fauth TTree
    TTree *t1;

    // ===================
    // *** For photons ***
    TH1D *histCerenPhoMuon;
    TH1D *histCerenPhoElec;
    TH1D *histCerenPhoGamm;
    TH1D *histCerenPhoNeut;
    TH1D *histCerenPhoHadr;
    TH1D *histCerenPhoAll;
    int cMuonCerPho;
    int cElecCerPho;
    int cGammCerPho;
    int cNeutCerPho;
    int cHadrCerPho;
    int cAllCerPho;

    TH1D *histCerenPhoMuonPmt;
    TH1D *histCerenPhoMuonPmt2;
    TH1D *histCerenPhoMuonPmt3;
    TH1D *histCerenPhoPmtAll;
    int cMuonPhoPmt;
    int cMuonPhoPmt2;
    int cMuonPhoPmt3;

    int cElecPhoPmt;
    int cGammPhoPmt;
    int cNeutPhoPmt;
    int cHadrPhoPmt;
    int cAllPhoPmt;

    TH1D *histCerenPhoElectMuonPmt;
    TH1D *histCerenPhoElectMuonPmt2;
    TH1D *histCerenPhoElectMuonPmt3;
    TH1D *histCerenPhoElectMuonPmtAll;
    int cMuonPhoElect;
    int cMuonPhoElect2;
    int cMuonPhoElect3;

    int cElecPhoElect;
    int cGammPhoElect;
    int cNeutPhoElect;
    int cHadrPhoElect;
    int cAllPhoElect;

    TH1D *histCerenPhoSpectMuonPmt;
    TH1D *histCerenPhoSpectMuonPmt2;
    TH1D *histCerenPhoSpectMuonPmt3;
    TH1D *histCerenPhoSpectMuonPmtAll;

    std::vector<int> cMuonSpecPhoElect;
    std::vector<int> cMuonSpecPhoElect2;
    std::vector<int> cMuonSpecPhoElect3;

    std::vector<int> cElecSpecPhoElect;
    std::vector<int> cGammSpecPhoElect;
    std::vector<int> cNeutSpecPhoElect;
    std::vector<int> cHadrSpecPhoElect;
    std::vector<int> cAllSpecPhoElect;

    // ==================
    // *** For pulses ***
    TH1D *histMeanPulseMuonPmt;
    TH1D *histMeanPulseMuonPmt2;
    TH1D *histMeanPulseMuonPmt3;
    TH1D *histMeanPulseAll;

    TH1D *histRiseTimeMuonPmt1;
    TH1D *histRiseTimeMuonPmt2;
    TH1D *histRiseTimeMuonPmt3;
    TH1D *histRiseTimeMuonPmtAll;

    TH1D *histRiseTime10to90MuonPmt1;
    TH1D *histRiseTime10to90MuonPmt2;
    TH1D *histRiseTime10to90MuonPmt3;
    TH1D *histRiseTime10to90MuonPmtAll;

    TH1D *histVoltagePMT1;
    TH1D *histVoltagePMT2;
    TH1D *histVoltagePMT3;
    TH1D *histVoltageAll;

    TH1D *histIntegratedChargePMT1;
    TH1D *histIntegratedChargePMT2;
    TH1D *histIntegratedChargePMT3;
    TH1D *histIntegratedChargeAll;

    // =======================
    // *** inside detector ***
    TH1D *histTrackLengthDetecMuon;
    TH1D *histTrackLengthDetecAll;
    double cMuonLengthDetec;
    double cElecLengthDetec;
    double cGammLengthDetec;
    double cNeutLengthDetec;
    double cHadrLengthDetec;
    double cAllLengthDetec;

    const double mm2cm = 10.;

    TH1D *histParticleEnergy;
    TH1D *histEnergyDeposit;
    TH2D *histEnergymm;

    double cMounEnergyDeposit;
    double InicialEnergy;
    // ================
    // *** Injected ***
    TH1I *histPartInject;
    TH2D *histPostInject;
    float mult = 1.96;
};
#endif
