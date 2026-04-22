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

}
