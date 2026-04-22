#include <TH1F.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TF1.h>

void read_data() {
    TFile* dataFile = new TFile("V0_data.root");
    TTree* dataTree = (TTree*)dataFile->Get("Ks2pipi_dd/DecayTree");
    // read data
    Double_t h1Px, h1Py, h1Pz, h1M,
        h2Px, H2Py, h2Pz, h2M;

    dataTree->SetBranchAddress("h1_PX", &h1Px);
    dataTree->SetBranchAddress("h1_PY", &h1Py);
    dataTree->SetBranchAddress("h1_PZ", &h1Pz);
    dataTree->SetBranchAddress("h1_M", &h1M);

    dataTree->SetBranchAddress("h2_PX", &h2Px);
    dataTree->SetBranchAddress("h2_PY", &H2Py);
    dataTree->SetBranchAddress("h2_PZ", &h2Pz);
    dataTree->SetBranchAddress("h2_M", &h2M);

    // read number of entries
    auto numEntries = dataTree->GetEntries();

    // create histogram
    auto constexpr histMin = 460;
    auto constexpr histMax = 540;
    TH1F* histogram = new TH1F("histogram", "Mass distribution", 40, histMin, histMax);
    histogram->GetXaxis()->SetTitle("Mass distribution [MeV]");
    histogram->SetMarkerStyle(20);

    // iterate over data
    for (int i =0; i < numEntries; i++) {
        dataTree->GetEntry(i);

        auto const e1 = sqrt(h1M*h1M + h1Px * h1Px + h1Py * h1Py + h1Pz * h1Pz);
        auto const v1 = new TLorentzVector();
        v1->SetPxPyPzE(h1Px, h1Py, h1Pz, e1);

        auto const e2 = sqrt(h2M*h2M + h2Px * h2Px + H2Py * H2Py + h2Pz * h2Pz);
        auto const v2 = new TLorentzVector();
        v2->SetPxPyPzE(h2Px, H2Py, h2Pz, e2);

        auto const vSum  = *v1 + *v2;
        auto const mass = vSum.M();
        histogram->Fill(mass);
    }

    histogram->Sumw2();

    auto constexpr NORMALIZATION = 0;
    auto constexpr MEAN = 1;
    auto fit = new TF1("fit_mass", "gaus(0) + pol2(3)", histMin, histMax);
    fit->SetParameter(NORMALIZATION, 900);
    fit->SetParameter(MEAN, 500);
    histogram->Fit("fit_mass", "RN");

    // display results
    auto const canvas = new TCanvas("canvas", "CEIO Project", 100, 10, 800, 600);
    histogram->Draw();
    fit->Draw("same");
}
