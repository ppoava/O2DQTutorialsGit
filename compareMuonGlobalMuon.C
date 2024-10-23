// compareMuonGlobalMuon.C
// Created: 22 oct 2024
// Paul VEEN (paveen)
// Simple macro to compare results from the O2DQ tutorial

#include <iostream>
#include <string>
#include "TFile.h"
#include "TH1F.h"
#include "THashList.h"
#include "TList.h"

void drawHist()
 {

    std::cout << "hoi" << std::endl;

    THashList *listMuon, *listGlobalMuon, *listMuonPbPb;
    TList *subListMuon, *subListGlobalMuon, *subListMuonPbPb;
    
    // Global muon pp
    TFile* fGlobalMuon = new TFile("AnalysisResults_hyperloop_globalMuon.root", "READ");
    listGlobalMuon = (THashList*)fGlobalMuon->Get("analysis-same-event-pairing/output");
    subListGlobalMuon = (TList*)listGlobalMuon->FindObject("PairsMuonSEPM_matchedQualityCuts");

    TH1F *hMuonMass, *hGlobalMuonMass, *hMuonPbPbMass;
    hGlobalMuonMass = (TH1F*)subListGlobalMuon->FindObject("Mass");
    hGlobalMuonMass->Scale(1/(hGlobalMuonMass->Integral()));

    // Standalone muon pp
    TFile* fMuon = new TFile("AnalysisResults_hyperloop_muon.root", "READ");
    listMuon = (THashList*)fMuon->Get("analysis-same-event-pairing/output");
    subListMuon = (TList*)listMuon->FindObject("PairsMuonSEPM_muonQualityCuts");

    hMuonMass = (TH1F*)subListMuon->FindObject("Mass");
    hMuonMass->Scale(1/(hMuonMass->Integral()));

   // Standalone muon PbPb
   TFile* fMuonPbPb = new TFile("AnalysisResults_hyperloop_PbPbmuon.root", "READ");
   listMuonPbPb = (THashList*)fMuonPbPb->Get("analysis-same-event-pairing/output");
   subListMuonPbPb = (TList*)listMuonPbPb->FindObject("PairsMuonSEPM_muonQualityCuts");

   hMuonPbPbMass = (TH1F*)subListMuonPbPb->FindObject("Mass");
   hMuonPbPbMass->Scale(1/(hMuonPbPbMass->Integral()));

   // Draw histograms
   hGlobalMuonMass->GetYaxis()->SetTitle("entries / total entries");
   hGlobalMuonMass->Draw("hist E");
   hMuonMass->SetLineColor(kRed);
   hMuonMass->Draw("same hist E");
   hMuonPbPbMass->SetLineColor(kBlack);
   hMuonPbPbMass->Draw("same hist E");
  
   // Draw legend
   TLegend *leg = new TLegend(0.6, 0.6, 0.8, 0.8);
   leg->AddEntry(hGlobalMuonMass, "global muon pp");
   leg->AddEntry(hMuonMass, "standalone muon pp");
   leg->AddEntry(hMuonPbPbMass, "standalone muon PbPb");
   leg->Draw("same");

 } // drawHist()

int compareMuonGlobalMuon() 
 {
    drawHist();
    return 0;
 }