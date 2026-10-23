// C++ Libraries
//
#include <vector>

// Geant4 Libraries
//
#include "G4Step.hh"
#include "G4Track.hh"

// Local Libraries
//
#include "histosRun.hh"

// Root Libraries
//
#include <TFile.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2D.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>

histosRun::histosRun() {
    G4cout << "...histosRun..." << G4endl;
    histosOutput = new TFile("histosOutput_muon_vem.root", "RECREATE");
}

histosRun::~histosRun() {
    histosOutput->Write();
    histosOutput->Close();
}
double chargeintegratedPMT1, chargeintegratedPMT2, chargeintegratedPMT3, chargeintegratedAll;
double voltagePMT1, voltagePMT2, voltagePMT3, voltageAll;
int risetimePMT1, risetimePMT2, risetimePMT3, risetimeAll;
int RT10to90PMT1, RT10to90PMT2, RT10to90PMT3, RT10to90PMTAll;
const double pico = 1e+12;
const int mili = 1000;

void histosRun::initHistos() {
    double maxbinEnergy = 20000;
    double nbinEnergy = 5000;
    int binForPhotons = 100000; //
    int binforfotonsmin = 300;
    int binForPhotons2 = 3000;
    int binForPhotons1 = 1500;
    int binForPhotons1min = 500;
    int binforfotons2min = 300;
    int binForPulses = 500;
    int binInsideDetec = 250;
    int binInsideDetec1 = 500;
    int nummaxpulse = 2000;
    int binforCphoSpect = 1000;
    int binForRiseTime = 100;
    int binForRiseTime2 = 100;
    int binForDownTime = 500;
    int binForDownTime2 = 2000;
    int binForCharge = 30000 / 2;
    int binForChargeMax = 30000;
    int binForVoltage = 500;
    int binForVoltageMax = 500;
    int binForFWHM = 300;
    int binForFWHMMax = 300;
    int particletrack = 150;
    int binparticletrack = 150;

    // ===================
    // *** For photons ***
    histParticleEnergy = new TH1D("ParticleEnergy", "meanEnergy", nbinEnergy, 0, maxbinEnergy);

    histCerenPhoMuon = new TH1D("histCerenPhoMuon", "CerenPhoMuon", binforfotonsmin, 1, binForPhotons + 1);
    histCerenPhoAll = new TH1D("histCerenPhoAll", "CerenPhoAll", binforfotonsmin, 1, binForPhotons + 1);

    histCerenPhoMuonPmt = new TH1D("histCerenPhoMuonPmt", "CerenPhoMuonPmt", binforfotonsmin, 1, binForPhotons2 + 1);
    histCerenPhoMuonPmt2 = new TH1D("histCerenPhoMuonPmt2", "CerenPhoMuonPmt2", binforfotonsmin, 1, binForPhotons2 + 1);
    histCerenPhoMuonPmt3 = new TH1D("histCerenPhoMuonPmt3", "CerenPhoMuonPmt3", binforfotonsmin, 1, binForPhotons2 + 1);
    histCerenPhoPmtAll = new TH1D("histCerenPhoPmtAll", "CerenPhoPmtAll", binforfotonsmin, 1, binForPhotons2 + 1);

    histCerenPhoElectMuonPmt = new TH1D("histCerenPhoElectMuonPmt", "CerenPhoElectMuonPmt", binForPhotons1min, 1, binForPhotons1 + 1);
    histCerenPhoElectMuonPmt2 = new TH1D("histCerenPhoElectMuonPmt2", "CerenPhoElectMuonPmt2", binForPhotons1min, 1, binForPhotons1 + 1);
    histCerenPhoElectMuonPmt3 = new TH1D("histCerenPhoElectMuonPmt3", "CerenPhoElectMuonPmt3", binForPhotons1min, 1, binForPhotons1 + 1);
    histCerenPhoElectMuonPmtAll = new TH1D("histCerenPhoElectMuonPmtAll", "CerenPhoElectMuonPmtAll", binForPhotons1min, 1, binForPhotons1 + 1);

    histCerenPhoSpectMuonPmt = new TH1D("histCerenPhoSpectMuonPmt", "CerenPhoSpectMuonPmt", binforCphoSpect, 0, binforCphoSpect);
    histCerenPhoSpectMuonPmt2 = new TH1D("histCerenPhoSpectMuonPmt2", "CerenPhoSpectMuonPmt2", binforCphoSpect, 0, binforCphoSpect);
    histCerenPhoSpectMuonPmt3 = new TH1D("histCerenPhoSpectMuonPmt3", "CerenPhoSpectMuonPmt3", binforCphoSpect, 0, binforCphoSpect);
    histCerenPhoSpectMuonPmtAll = new TH1D("histCerenPhoSpectMuonPmtAll", "CerenPhoSpectMuonPmtAll", binforCphoSpect, 0, binforCphoSpect);

    // ==================|:
    // *** For pulses ***
    histMeanPulseMuonPmt = new TH1D("histMeanPulseMuonPmt", "MeanPulseMuonPmt", binForPulses, 0, nummaxpulse);
    histMeanPulseMuonPmt2 = new TH1D("histMeanPulseMuonPmt2", "MeanPulseMuonPmt2", binForPulses, 0, nummaxpulse);
    histMeanPulseMuonPmt3 = new TH1D("histMeanPulseMuonPmt3", "MeanPulseMuonPmt3", binForPulses, 0, nummaxpulse);
    histMeanPulseAll = new TH1D("histMeanPulseAll", "MeanPulseAll", binForPulses, 0, nummaxpulse);

    //=====================
    // *** For Rise Time ***

    histRiseTimeMuonPmt1 = new TH1D("histRiseTimeMuonPmt1", "rise time Pmt1", binForRiseTime, 0, binForRiseTime2);
    histRiseTimeMuonPmt2 = new TH1D("histRiseTimeMuonPmt2", "rise time Pmt2", binForRiseTime, 0, binForRiseTime2);
    histRiseTimeMuonPmt3 = new TH1D("histRiseTimeMuonPmt3", "rise time Pmt3", binForRiseTime, 0, binForRiseTime2);
    histRiseTimeMuonPmtAll = new TH1D("histRiseTimeMuonPmtAll", "rise time PmtAll", binForRiseTime, 0, binForRiseTime2);

    histRiseTime10to90MuonPmt1 = new TH1D("histRiseTime10to90MuonPmt1", "rise time 10 to 90 Pmt1", binForRiseTime, 0, binForRiseTime2);
    histRiseTime10to90MuonPmt2 = new TH1D("histRiseTime10to90MuonPmt2", "rise time 10 to 90 Pmt2", binForRiseTime, 0, binForRiseTime2);
    histRiseTime10to90MuonPmt3 = new TH1D("histRiseTime10to90MuonPmt3", "rise time 10 to 90 Pmt3", binForRiseTime, 0, binForRiseTime2);
    histRiseTime10to90MuonPmtAll = new TH1D("histRiseTime10to90MuonPmtAll", "rise time 10 to 90 PmtAll", binForRiseTime, 0, binForRiseTime2);

    //=======================
    // *** For Total Charge ***
    histIntegratedChargePMT1 = new TH1D("IntegratedChargePMT1", "Total Charge PMT1", binForCharge, 0, binForChargeMax);
    histIntegratedChargePMT2 = new TH1D("IntegratedChargePMT2", "Total Charge PMT2", binForCharge, 0, binForChargeMax);
    histIntegratedChargePMT3 = new TH1D("IntegratedChargePMT3", "Total Charge PMT3", binForCharge, 0, binForChargeMax);
    histIntegratedChargeAll = new TH1D("IntegratedChargeAll", "Total Charge All", binForCharge, 0, binForChargeMax);

    //========================
    // *** For Voltage Output ***

    histVoltagePMT1 = new TH1D("VoltageOutputPMT1", "Voltage PMT1", binForVoltage, 0, binForVoltageMax);
    histVoltagePMT2 = new TH1D("VoltageOutputPMT2", "Voltage PMT2", binForVoltage, 0, binForVoltageMax);
    histVoltagePMT3 = new TH1D("VoltageOutputPMT3", "Voltage PMT3", binForVoltage, 0, binForVoltageMax);
    histVoltageAll = new TH1D("VoltageOutputAll", "Voltage All", binForVoltage, 0, binForVoltageMax);

    // =======================
    // *** inside detector ***
    histTrackLengthDetecMuon = new TH1D("histTrackLengthDetecMuon", "TrackLengthDetecMuon", binInsideDetec, 1, binInsideDetec1 + 1);
    histTrackLengthDetecAll = new TH1D("histTrackLengthDetecAll", "TrackLengthDetecAll", binInsideDetec, 1, binInsideDetec1 + 1);

    // ================
    // *** Injected ***
    histPartInject = new TH1I("histPartInject", "PartInject", 6, 0, 6);
    histPostInject = new TH2D("histPostInject", "PostInject", 1001, -500, 500, 1001, -500, 500);

    // Fill color
    for (int i = 0; i == 0; i++) {
        histCerenPhoMuon->SetFillColor(kBlue);
        histCerenPhoMuonPmt->SetFillColor(kBlue);
        histCerenPhoMuonPmt2->SetFillColor(kBlue);
        histCerenPhoMuonPmt3->SetFillColor(kBlue);
        histCerenPhoPmtAll->SetFillColor(kBlue);
        histCerenPhoElectMuonPmt->SetFillColor(kBlue);
        histCerenPhoElectMuonPmt2->SetFillColor(kBlue);
        histCerenPhoElectMuonPmt3->SetFillColor(kBlue);
        histCerenPhoElectMuonPmtAll->SetFillColor(kBlue);
        histCerenPhoElectMuonPmt->SetFillColor(kBlue);
        histCerenPhoElectMuonPmt2->SetFillColor(kBlue);
        histCerenPhoElectMuonPmt3->SetFillColor(kBlue);
        histCerenPhoElectMuonPmtAll->SetFillColor(kBlue);

        histCerenPhoSpectMuonPmt->SetFillColor(kBlue);
        histCerenPhoSpectMuonPmt2->SetFillColor(kBlue);
        histCerenPhoSpectMuonPmt3->SetFillColor(kBlue);
        histCerenPhoSpectMuonPmtAll->SetFillColor(kBlue);

        // ==================|:
        // *** For pulses ***
        histMeanPulseMuonPmt->SetFillColor(kBlue);
        histMeanPulseMuonPmt2->SetFillColor(kBlue);
        histMeanPulseMuonPmt3->SetFillColor(kBlue);
        histMeanPulseAll->SetFillColor(kBlue);

        //=====================
        // *** For Rise Time ***

        histRiseTimeMuonPmt1->SetFillColor(kBlue);
        histRiseTimeMuonPmt2->SetFillColor(kBlue);
        histRiseTimeMuonPmt3->SetFillColor(kBlue);
        histRiseTimeMuonPmtAll->SetFillColor(kBlue);

        histRiseTime10to90MuonPmt1->SetFillColor(kBlue);
        histRiseTime10to90MuonPmt2->SetFillColor(kBlue);
        histRiseTime10to90MuonPmt3->SetFillColor(kBlue);
        histRiseTime10to90MuonPmtAll->SetFillColor(kBlue);

        //=======================
        // *** For Total Charge ***
        histIntegratedChargePMT1->SetFillColor(kBlue);
        histIntegratedChargePMT2->SetFillColor(kBlue);
        histIntegratedChargePMT3->SetFillColor(kBlue);
        histIntegratedChargeAll->SetFillColor(kBlue);
    }
}

int RiseTime10to90(TH1D *histMeanPulse) /// meu codigo
{
    int FirstBin, TopperBin;
    int MaxBin;
    int risetime10to90;
    int MaxBinValue10to90;
    int MBV10, MBV90;

    MaxBin = histMeanPulse->GetMaximumBin();
    MaxBinValue10to90 = histMeanPulse->GetBinContent(MaxBin);

    MBV10 = 0.1 * MaxBinValue10to90;
    MBV90 = 0.9 * MaxBinValue10to90;

    FirstBin = histMeanPulse->FindFirstBinAbove(MBV10);
    TopperBin = histMeanPulse->FindFirstBinAbove(MBV90);

    risetime10to90 = TopperBin - FirstBin;
    return risetime10to90;
}

int RiseTime0to100(TH1D *histMeanPulse) {
    int FirstBin, TopperBin;
    int MaxBin;
    int risetime0to100;
    int MaxBinValue0to100;
    int MBV0;
    int MBV100;

    MaxBin = histMeanPulse->GetMaximumBin();
    MaxBinValue0to100 = histMeanPulse->GetBinContent(MaxBin);

    MBV0 = 1;
    MBV100 = 1.0 * MaxBinValue0to100;

    FirstBin = histMeanPulse->FindFirstBinAbove(MBV0);
    TopperBin = histMeanPulse->FindFirstBinAbove(MBV100);

    risetime0to100 = TopperBin - FirstBin;

    return risetime0to100;
}

long double ChargeIntegrated(TH1D *histPulseMuon, TH1D *nInputParticle) // nInputParticle ->gráfico com o numero de partículas de entrada
{
    int neletronsPMT, neletronsSingleParticlePMT;
    double chargeintegrated;
    double eletronCharge = 1.60217662e-19;
    double nParticle;

    nParticle = nInputParticle->Integral();
    neletronsPMT = histPulseMuon->Integral();
    neletronsSingleParticlePMT = neletronsPMT / nParticle;

    chargeintegrated = eletronCharge * neletronsSingleParticlePMT * 1e12;

    // return nParticle;
    // return neletronsSingleParticlePMT;
    return chargeintegrated;
}

double VoltageOutofPMT(TH1D *histMeanPulse, double totalcharge) {
    int lastBinTime; // está em segundo
    double impedance;
    double current;
    double voltage;
    const double nano = 1e-09; // usado para converter segundo em ns nesta função

    impedance = 50; // Ohm
    lastBinTime = histMeanPulse->FindLastBinAbove(0.1);

    current = totalcharge / (lastBinTime * nano);

    voltage = impedance * current;

    return voltage;
}

void ChargeMultiplicationPMT(TH1D *fillpulse, double time) {

    double time1, time2, time3, time4, time5, time6, time7, time8, time9;
    double gain1, gain2, gain3, gain4, gain5, gain6, gain7, gain8;
    double desviopadrao = 3 + 2 * gRandom->Rndm();
    double DeriveTime = 1 + gRandom->Rndm();
    double timetofistdynode = 10;

    // fillpulse->Fill(time);
    for (int i = 0; i < 1; i++) {

        time1 = time;
        gain1 = 5 + 2 * gRandom->Rndm();
        for (int i = 0; i < gain1; i++) {

            time2 = timetofistdynode + 1 * gRandom->Poisson(time1);
            gain2 = 5 + 2 * gRandom->Rndm();

            for (int i = 0; i < gain2; i++) {

                time3 = 1 + gRandom->Rndm() + gRandom->Gaus(time2, gRandom->Rndm());
                gain3 = 5 + 2 * gRandom->Rndm();

                for (int i = 0; i < gain3; i++) {

                    time4 = 1 + gRandom->Rndm() + gRandom->Gaus(time3, gRandom->Rndm());
                    gain4 = 5 + 2 * gRandom->Rndm();

                    for (int i = 0; i < gain4; i++) {

                        time5 = 1 + gRandom->Rndm() + gRandom->Gaus(time4, gRandom->Rndm());
                        gain5 = 5 + 2 * gRandom->Rndm();

                        for (int i = 0; i < gain5; i++) {

                            time6 = 1 + gRandom->Rndm() + gRandom->Gaus(time5, gRandom->Rndm());
                            gain6 = 5 + 2 * gRandom->Rndm();

                            for (int i = 0; i < gain6; i++) {

                                time7 = 1 + gRandom->Rndm() + gRandom->Gaus(time6, gRandom->Rndm());
                                gain7 = 5 + 2 * gRandom->Rndm();

                                for (int i = 0; i < gain7; i++) {

                                    time8 = 1 + gRandom->Rndm() + gRandom->Gaus(time7, gRandom->Rndm());
                                    gain8 = 5 + 2 * gRandom->Rndm();

                                    for (int i = 0; i < gain8; i++) {

                                        time9 = 1 + gRandom->Rndm() + gRandom->Gaus(time8, gRandom->Rndm());

                                        fillpulse->Fill(time9);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void histosRun::cerenPho(int optCerenPho) {
    switch (optCerenPho) {
    case 0:
        cMuonCerPho++;
        break;
    case 5:
        cAllCerPho++;
        break;
    }
}

void histosRun::fillCerenPho(int optFillPho) {
    switch (optFillPho) {
    case 0:
        histCerenPhoMuon->Fill(cMuonCerPho);
        break;
    case 5:
        histCerenPhoAll->Fill(cAllCerPho);
        break;
    }

    cMuonCerPho = 0;
    cElecCerPho = 0;
    cGammCerPho = 0;
    cNeutCerPho = 0;
    cHadrCerPho = 0;

    if (optFillPho == 5)
        cAllCerPho = 0;
}

////////////////////////////////////////////////////////////////////// PMT1

void histosRun::cerenPhoPmt(int optCerenPhoPmt) {
    switch (optCerenPhoPmt) {
    case 0:
        cMuonPhoPmt++;
        break;
    case 5:
        cAllPhoPmt++;
        break;
    }
}

void histosRun::fillCerenPhoPmt(int optFillPhoPmt) {
    switch (optFillPhoPmt) {
    case 0:
        histCerenPhoMuonPmt->Fill(cMuonPhoPmt);
        break;
    }

    cMuonPhoPmt = 0;
}

void histosRun::cerenPhoElect(int optCerenPhoElect, int wl) {
    switch (optCerenPhoElect) {
    case 0:
        cMuonPhoElect++;
        cMuonSpecPhoElect.push_back(wl);
        ;
        break;
    case 5:
        cAllPhoElect++;
        cAllSpecPhoElect.push_back(wl);
        ;
        break;
    }
}

void histosRun::fillCerenPhoElect(int optFillPhoElect) {
    switch (optFillPhoElect) {
    case 0:
        histCerenPhoElectMuonPmt->Fill(cMuonPhoElect);
        for (std::vector<int>::iterator iter = cMuonSpecPhoElect.begin(); iter != cMuonSpecPhoElect.end(); ++iter) {
            histCerenPhoSpectMuonPmt->Fill(*iter);
        }
        break;
    }

    cMuonPhoElect = 0;

    cMuonSpecPhoElect.clear();

    if (optFillPhoElect == 5) {
        cAllPhoElect = 0;
        cAllSpecPhoElect.clear();
    }
}

void histosRun::meanPulse(int optMeanPulse, double time) {
    switch (optMeanPulse) {
    case 0:
        ChargeMultiplicationPMT(histMeanPulseMuonPmt, time);

        risetimePMT1 = RiseTime0to100(histMeanPulseMuonPmt);
        histRiseTimeMuonPmt1->Fill(risetimePMT1);

        RT10to90PMT1 = RiseTime10to90(histMeanPulseMuonPmt);
        histRiseTime10to90MuonPmt1->Fill(RT10to90PMT1);

        chargeintegratedPMT1 = ChargeIntegrated(histMeanPulseMuonPmt, histCerenPhoMuon);
        // histIntegratedChargePMT1->Fill(pico*chargeintegratedPMT1);
        histIntegratedChargePMT1->Fill(chargeintegratedPMT1);

        voltagePMT1 = VoltageOutofPMT(histMeanPulseMuonPmt, chargeintegratedPMT1);
        histVoltagePMT1->Fill(mili * voltagePMT1);

        break;

    case 5:
        ChargeMultiplicationPMT(histMeanPulseAll, time);
        // histMeanPulseAll->Fill(time);

        risetimeAll = RiseTime0to100(histMeanPulseAll);
        histRiseTimeMuonPmtAll->Fill(risetimeAll);

        RT10to90PMTAll = RiseTime10to90(histMeanPulseAll);
        histRiseTime10to90MuonPmtAll->Fill(RT10to90PMTAll);

        chargeintegratedAll = ChargeIntegrated(histMeanPulseAll, histCerenPhoMuon);
        // histIntegratedChargeAll->Fill(pico*chargeintegratedAll);
        histIntegratedChargeAll->Fill(chargeintegratedAll);

        voltageAll = VoltageOutofPMT(histMeanPulseAll, chargeintegratedAll);
        histVoltageAll->Fill(mili * voltageAll);

        break;
    }
}

//////////////////////////////////////////////////////////////////// PMT2

void histosRun::cerenPhoPmt2(int optCerenPhoPmt2) {
    switch (optCerenPhoPmt2) {
    case 1:
        cMuonPhoPmt2++;
        break;
    }
}

void histosRun::fillCerenPhoPmt2(int optFillPhoPmt2) {
    switch (optFillPhoPmt2) {
    case 1:
        histCerenPhoMuonPmt2->Fill(cMuonPhoPmt2);
        break;
    }

    cMuonPhoPmt2 = 0;
}

void histosRun::cerenPhoElect2(int optCerenPhoElect, int wl) {
    switch (optCerenPhoElect) {
    case 1:
        cMuonPhoElect2++;
        cMuonSpecPhoElect2.push_back(wl);
        ;
        break;
    }
}

void histosRun::fillCerenPhoElect2(int optFillPhoElect) {
    switch (optFillPhoElect) {
    case 1:
        histCerenPhoElectMuonPmt2->Fill(cMuonPhoElect2);
        for (std::vector<int>::iterator iter = cMuonSpecPhoElect2.begin(); iter != cMuonSpecPhoElect2.end(); ++iter) {
            histCerenPhoSpectMuonPmt2->Fill(*iter);
        }
        break;
    }

    cMuonPhoElect2 = 0;

    cMuonSpecPhoElect2.clear();
}

void histosRun::meanPulse2(int optMeanPulse, double time) {
    switch (optMeanPulse) {
    case 1:
        ChargeMultiplicationPMT(histMeanPulseMuonPmt2, time);

        risetimePMT2 = RiseTime0to100(histMeanPulseMuonPmt2);
        histRiseTimeMuonPmt2->Fill(risetimePMT2);

        RT10to90PMT2 = RiseTime10to90(histMeanPulseMuonPmt2);
        histRiseTime10to90MuonPmt2->Fill(RT10to90PMT2);

        chargeintegratedPMT2 = ChargeIntegrated(histMeanPulseMuonPmt2, histCerenPhoMuon);
        // histIntegratedChargePMT2->Fill(pico*chargeintegratedPMT2);
        histIntegratedChargePMT2->Fill(chargeintegratedPMT2);

        voltagePMT2 = VoltageOutofPMT(histMeanPulseMuonPmt2, chargeintegratedPMT2);
        histVoltagePMT2->Fill(mili * voltagePMT2);

        break;

    case 5:
        ChargeMultiplicationPMT(histMeanPulseAll, time);
        // histMeanPulseAll->Fill(time);

        risetimeAll = RiseTime0to100(histMeanPulseAll);
        histRiseTimeMuonPmtAll->Fill(risetimeAll);

        RT10to90PMTAll = RiseTime10to90(histMeanPulseAll);
        histRiseTime10to90MuonPmtAll->Fill(RT10to90PMTAll);

        chargeintegratedAll = ChargeIntegrated(histMeanPulseAll, histCerenPhoMuon);
        // histIntegratedChargeAll->Fill(pico*chargeintegratedAll);
        histIntegratedChargeAll->Fill(chargeintegratedAll);

        voltageAll = VoltageOutofPMT(histMeanPulseAll, chargeintegratedAll);
        histVoltageAll->Fill(mili * voltageAll);

        break;
    }
}

////////////////////////////////////////////////////////////// PMT3

void histosRun::cerenPhoPmt3(int optCerenPhoPmt3) {
    switch (optCerenPhoPmt3) {
    case 3:
        cMuonPhoPmt3++;
        break;
    }
}

void histosRun::fillCerenPhoPmt3(int optFillPhoPmt3) {
    switch (optFillPhoPmt3) {
    case 3:
        histCerenPhoMuonPmt3->Fill(cMuonPhoPmt3);
        break;
    }

    cMuonPhoPmt3 = 0;
}

void histosRun::cerenPhoElect3(int optCerenPhoElect, int wl) {
    switch (optCerenPhoElect) {
    case 3:
        cMuonPhoElect3++;
        cMuonSpecPhoElect3.push_back(wl);
        ;
        break;
    }
}

void histosRun::fillCerenPhoElect3(int optFillPhoElect) {
    switch (optFillPhoElect) {
    case 3:
        histCerenPhoElectMuonPmt3->Fill(cMuonPhoElect3);
        for (std::vector<int>::iterator iter = cMuonSpecPhoElect3.begin(); iter != cMuonSpecPhoElect3.end(); ++iter) {
            histCerenPhoSpectMuonPmt2->Fill(*iter);
        }
        break;
    }

    cMuonPhoElect3 = 0;

    cMuonSpecPhoElect3.clear();
}

void histosRun::meanPulse3(int optMeanPulse, double time) {
    switch (optMeanPulse) {
    case 3:
        ChargeMultiplicationPMT(histMeanPulseMuonPmt3, time);

        risetimePMT3 = RiseTime0to100(histMeanPulseMuonPmt3);
        histRiseTimeMuonPmt3->Fill(risetimePMT3);

        RT10to90PMT3 = RiseTime10to90(histMeanPulseMuonPmt3);
        histRiseTime10to90MuonPmt3->Fill(RT10to90PMT3);

        chargeintegratedPMT3 = ChargeIntegrated(histMeanPulseMuonPmt3, histCerenPhoMuon);
        // histIntegratedChargePMT3->Fill(pico*chargeintegratedPMT3);
        histIntegratedChargePMT3->Fill(chargeintegratedPMT3);

        voltagePMT3 = VoltageOutofPMT(histMeanPulseMuonPmt3, chargeintegratedPMT3);
        histVoltagePMT3->Fill(mili * voltagePMT3);

        break;

    case 5:
        ChargeMultiplicationPMT(histMeanPulseAll, time);
        // histMeanPulseAll->Fill(time);
        risetimeAll = RiseTime0to100(histMeanPulseAll);
        histRiseTimeMuonPmtAll->Fill(risetimeAll);

        RT10to90PMTAll = RiseTime10to90(histMeanPulseAll);
        histRiseTime10to90MuonPmtAll->Fill(RT10to90PMTAll);

        chargeintegratedAll = ChargeIntegrated(histMeanPulseAll, histCerenPhoMuon);
        // histIntegratedChargeAll->Fill(pico*chargeintegratedAll);
        histIntegratedChargeAll->Fill(chargeintegratedAll);

        voltageAll = VoltageOutofPMT(histMeanPulseAll, chargeintegratedAll);
        histVoltageAll->Fill(mili * voltageAll);

        break;
    }
}

////////////////////////////////////////////////////////////////////////// PMT 1 2 3

void histosRun::cerenPhoPmtAll(int optCerenPhoPmt) {
    switch (optCerenPhoPmt) {

    case 5:
        cAllPhoPmt++;
        break;
    }
}

void histosRun::fillCerenPhoPmtAll(int optFillPhoPmt) {
    switch (optFillPhoPmt) {
    case 5:
        histCerenPhoPmtAll->Fill(cAllPhoPmt);
        break;
    }

    if (optFillPhoPmt == 5)
        cAllPhoPmt = 0;
}

void histosRun::cerenPhoElectAll(int optCerenPhoElect, int wl) {
    switch (optCerenPhoElect) {

    case 5:
        cAllPhoElect++;
        cAllSpecPhoElect.push_back(wl);
        ;
        break;
    }
}

void histosRun::fillCerenPhoElectAll(int optFillPhoElect) {
    switch (optFillPhoElect) {
    case 5:
        histCerenPhoElectMuonPmtAll->Fill(cAllPhoElect);
        for (std::vector<int>::iterator iter = cAllSpecPhoElect.begin(); iter != cAllSpecPhoElect.end(); ++iter) {
            histCerenPhoSpectMuonPmtAll->Fill(*iter);
        }
        break;
    }

    cMuonPhoElect = 0;

    cMuonSpecPhoElect.clear();

    if (optFillPhoElect == 5) {
        cAllPhoElect = 0;
        cAllSpecPhoElect.clear();
    }
}

/*void histosRun::meanPulse3(int optMeanPulse, double time)
{
  switch ( optMeanPulse )
  {
    case 5:
      ChargeMultiplicationPMT(histMeanPulseAll, time);
      //histMeanPulseAll->Fill(time);
      risetimeAll = RiseTime0to100(histMeanPulseAll);
      histRiseTimeMuonPmtAll->Fill(risetimeAll);

      RT10to90PMTAll = RiseTime10to90(histMeanPulseAll);
      histRiseTime10to90MuonPmtAll->Fill(RT10to90PMTAll);

      chargeintegratedAll = ChargeIntegrated(histMeanPulseAll, histCerenPhoMuon);
      //histIntegratedChargeAll->Fill(pico*chargeintegratedAll);
      histIntegratedChargeAll->Fill(chargeintegratedAll);

      voltageAll = VoltageOutofPMT(histMeanPulseAll, chargeintegratedAll);
      histVoltageAll->Fill(mili*voltageAll);

      break;
  }
}
*/

void histosRun::trackLengthDetec(int optLengthDectec, double length, double energy) {
    switch (optLengthDectec) {
    case 0:
        cMuonLengthDetec += length;
        cMounEnergyDeposit += energy;
        break;
    case 5:
        cAllLengthDetec += length;
        break;
    }
}

void histosRun::fillTrackLengthDetec(int optFillLengthDectec) {
    switch (optFillLengthDectec) {
    case 0:
        histTrackLengthDetecMuon->Fill(cMuonLengthDetec / mm2cm);

        break;
    case 5:
        histTrackLengthDetecAll->Fill(cAllLengthDetec / mm2cm);
        break;
    }

    cMuonLengthDetec = 0;
    cMounEnergyDeposit = 0;
    if (optFillLengthDectec == 5)
        cAllLengthDetec = 0;
}

void histosRun::distInject(int part) {
    histPartInject->Fill(part);
}

void histosRun::postInject(double partPosX, double partPosY) {
    histPostInject->Fill(partPosX, partPosY);
}

void histosRun::histPartEnergy(double energy) {
    InicialEnergy = energy;
    histParticleEnergy->Fill(energy);
}
