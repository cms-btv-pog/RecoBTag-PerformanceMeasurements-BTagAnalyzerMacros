#include "tdrstyle.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TH1D.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "THStack.h"
#include "TFile.h"
#include "TROOT.h"
#include "TColor.h"
#include "TF1.h"
#include "TMath.h"
#include <TLegend.h>
#include <TProfile.h>
#include <TLatex.h>
#include <TAxis.h>
#include <TProfile.h>
#include <TString.h>

using namespace std;

/*
TString filename_1="ttbar_pu_repair_on.root";
TString filename_2="ttbar_pu_repair_off.root";
TString filename_3="ttbar_nopu_repair_on.root";
TString filename_4="ttbar_nopu_repair_off.root";
*/

TString filename_1="qcd40_repair_on.root";
TString filename_2="qcd40_repair_off.root";
TString filename_3="qcd500_repair_on.root";
TString filename_4="qcd500_repair_off.root";

bool printfunc=false;
bool wgsplit = true;
//bool wgsplit = false;

TString format=".pdf"; // .png or .pdf or .gif

void DrawROC(TString name);
void DrawAllPlot();
void DrawAllPlot2(int flag_cvsb=1);
void ComputeEffAndErr(TH1D* disc_b, TH1D* disc_c, TH1D* disc_l, Double_t * eff_b, Double_t * err_b, Double_t * eff_c, Double_t * err_c, Double_t * eff_l, Double_t * err_l);
void ComputeRevEffAndErr(TH1D* disc_b, TH1D* disc_c, TH1D* disc_l, Double_t * eff_b, Double_t * err_b, Double_t * eff_c, Double_t * err_c, Double_t * eff_l, Double_t * err_l);
void DrawEffvsPt(TString name);
void DrawEff(TString name, int flag1=1);
void ComputeEffvsPT(TH1D* hist_b_r1, TH1D* hist_c_r1, TH1D* hist_l_r1, TH1D* hist_b_1, TH1D* hist_c_1, TH1D* hist_l_1, TH1D* Eff1_b, TH1D* Eff1_c, TH1D* Eff1_l, int icol);

void CompareEff(TString name, int wpflag=1, int flag1=1);
void CompareEff2(TString name, int wpflag=1, int flag1=1);
void CompareEff3(TString name, int wpflag=1, int flag1=1);
void CompareEffPlus(TString name, int wpflag=1, int flag1=1);
void CompareEffPlus2(TString name, int wpflag=1, int flag1=1);

//--------

void DrawROC(TString name){

    bool log=true;


    TGraph* EffBvsUDSG[100];
    TGraph* EffBvsC[100];
    TGraph* BvsUDSG3;
    TGraph* BvsC3;
    TFile* fileacces[100];

    // CREATE CANVAS

    setTDRStyle();
    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
    c1->SetFillColor(10);
    c1->cd();

  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetLogy(log);
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetTopMargin(0.065);
    c1_1->SetFrameBorderMode(0);

    gStyle->SetOptTitle(0);

    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.045);
    latex->SetTextFont(42); //22
    latex->SetTextAlign(13);

    TLegend* qw = 0;
    qw = new TLegend(0.20,0.55,0.40,0.74);
//    qw->SetFillColor(kWhite);
    TLegend* qw2 = 0;
    qw2 = new TLegend(0.82,0.15,0.95,0.25);
//    qw2->SetFillColor(kWhite);

/*
    TFile *myFile     = new TFile(filename_1);
    myFile->cd();
    const char *disc_array[] = {"CSVIVF","DeepCSV", "DeepFlavour","CvsL_deep","CvsB_deep"};
    TString qw_array[] = {"CSVv2","DeepCSV","DeepJet","CvsL_deepCSV","CvsB_deepCSV"};
    int markerstyle[] = {20,21,22,21,21};
    int markercolor[] = {kBlue,8,2, 28, kViolet-5};
*/


    const char *file_array[] = {filename_1,filename_2,filename_3,filename_4};
//    TString qw_array[] = {"On PU=50","Off PU=50","On PU=0","Off PU=0"};
    TString qw_array[] = {"On 50-250","Off 50-250","On 525-1000","Off 525-1000"};
    std::vector<std::string> file_iter(file_array, std::end(file_array));
    int markerstyle[] = {20,21,22,23};
    int markercolor[] = {kBlue,8,2, kViolet-5};

    int count = 0;

    cout << "Looping over file names\n";

    for(vector<string>::const_iterator iter = file_iter.begin(); iter != file_iter.end(); ++iter) {

        fileacces[count]     = new TFile((*iter).c_str());
        fileacces[count]->cd();

        TH1D* disc_b;
        TH1D* disc_c;
        TH1D* disc_l;
        TH1D* disc_g;
        TH1D* disc_bfg;
        TH1D* disc_cfg;

        disc_b         = (TH1D*)gROOT->FindObject(name+"_b");
        disc_c         = (TH1D*)gROOT->FindObject(name+"_c");
        disc_l         = (TH1D*)gROOT->FindObject(name+"_l");
        disc_g         = (TH1D*)gROOT->FindObject(name+"_g");
        disc_bfg       = (TH1D*)gROOT->FindObject(name+"_bfromg");
        disc_cfg       = (TH1D*)gROOT->FindObject(name+"_cfromg");

        disc_l->Add(disc_g);
        if (wgsplit) {
         disc_b->Add(disc_bfg);
         disc_c->Add(disc_cfg);
        }

        int nbin_max= disc_b->GetNbinsX()+1;

        Double_t eff_b[nbin_max];
        Double_t eff_l[nbin_max];
        Double_t eff_c[nbin_max];

        Double_t err_b[nbin_max];
        Double_t err_l[nbin_max];
        Double_t err_c[nbin_max];

        ComputeEffAndErr(disc_b, disc_c, disc_l, eff_b, err_b, eff_c, err_c, eff_l, err_l);

        cout << (*iter).c_str() << endl;
        cout << " eff "<< eff_b[0] << "  " << eff_c[0] << "  " << eff_l[0] << endl;
        cout << " eff "<< eff_b[1] << "  " << eff_c[1] << "  " << eff_l[1] << endl;
        cout << " eff "<< eff_b[2] << "  " << eff_c[2] << "  " << eff_l[2] << endl;

        TGraphErrors* BvsUDSG = new TGraphErrors(nbin_max,eff_b,eff_l,err_b,err_l);
        TGraphErrors* BvsC    = new TGraphErrors(nbin_max,eff_b,eff_c,err_b,err_c);

        BvsUDSG->GetXaxis()->SetLimits(0.,1.);
        BvsUDSG->GetHistogram()->SetMaximum(1.);
        BvsUDSG->GetHistogram()->SetMinimum(0.0005);

        BvsC->GetXaxis()->SetLimits(0.,1.);
        BvsC->GetHistogram()->SetMaximum(1.);
        BvsC->GetHistogram()->SetMinimum(0.001);

        // SET COSMETICS

//        BvsUDSG->SetMarkerStyle(markerstyle[count]);
        BvsUDSG->SetMarkerStyle(1);
        BvsUDSG->SetMarkerColor(markercolor[count]);
        BvsUDSG->SetLineColor(markercolor[count]);
        BvsUDSG->SetLineWidth(2);
        BvsUDSG->SetMarkerSize(0.75);
        BvsUDSG->GetXaxis()->SetTitle("b-jet efficiency");
        BvsUDSG->GetYaxis()->SetTitle("misid. probability");
        cout << "Cloning " << (*iter).c_str() << '\n';
        EffBvsUDSG[count] = (TGraphErrors*)BvsUDSG->Clone();

//        BvsC->SetMarkerStyle(markerstyle[count]+4);
        BvsC->SetMarkerStyle(1);
        BvsC->SetMarkerSize(0.75);
        BvsC->SetMarkerColor(markercolor[count]);
        BvsC->SetLineColor(markercolor[count]);
        BvsC->SetLineWidth(4);
        BvsC->SetLineStyle(2);
        BvsC->GetXaxis()->SetTitle("b-jet efficiency");
        BvsC->GetYaxis()->SetTitle("misid. probability");

        EffBvsC[count] = (TGraphErrors*)BvsC->Clone();

        qw->AddEntry(BvsUDSG, qw_array[count],"l");
        ++count;
        if (count==3) {
          BvsUDSG3= (TGraphErrors*)BvsUDSG->Clone();
          BvsC3= (TGraphErrors*)BvsC->Clone();
          BvsUDSG3->SetMarkerStyle(markerstyle[0]);
          BvsUDSG3->SetMarkerColor(1.);
          BvsUDSG3->SetLineColor(1.);
          BvsC3->SetMarkerStyle(markerstyle[0]+4);
          BvsC3->SetMarkerColor(1.);
          BvsC3->SetLineColor(1.);
          qw2->AddEntry(BvsUDSG3, "udsg","l");
          qw2->AddEntry(BvsC3, "c","l");
        }
    }

    c1->cd();
    c1_1->cd();
    c1_1->SetGridy();
    c1_1->SetGridx();
    cout << "Drawing the graphs\n";


    EffBvsUDSG[0]->GetHistogram()->SetTitleSize(0.08,"Y");
    EffBvsUDSG[0]->GetHistogram()->SetTitleOffset(0.65,"Y");
    EffBvsUDSG[0]->GetHistogram()->SetTitleOffset(0.81,"Y");
    EffBvsUDSG[0]->GetHistogram()->GetYaxis()->SetLabelSize( 0.045 );
    EffBvsUDSG[0]->GetHistogram()->GetYaxis()->SetTitleSize( 0.06 );
    EffBvsUDSG[0]->GetHistogram()->GetXaxis()->SetLabelSize( 0.045 );
    EffBvsUDSG[0]->GetHistogram()->GetXaxis()->SetTitleSize( 0.055 );


    for (int tgs = 0; tgs < count; ++tgs){
        if (tgs == 0) EffBvsUDSG[tgs]->Draw("ALP E1X0");
        else EffBvsUDSG[tgs]->Draw("LPsame E1X0");
    }
    for (int tgs = 0; tgs < count; ++tgs){
//        if (tgs == 0) EffBvsC[tgs]->Draw("ALP");
//        else EffBvsC[tgs]->Draw("LPsame");
        EffBvsC[tgs]->Draw("LPsame E1X0");
    }

  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
     qw->SetFillColor(0);
    qw2->SetFillColor(0);

    qw->Draw();
    qw2->Draw();

TLatex *   tex = new TLatex(0.98,0.95125,"Pixel Repair Validation");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.92,"CMS Simulation");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();

//    tex = new TLatex(0.20, 0.86, "t#bar{t} events");
    tex = new TLatex(0.20, 0.86, "QCD events");
//    tex = new TLatex(0.20, 0.86, "multijet events");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
//    tex = new TLatex(0.20, 0.80, "AK4jets (p_{T} > 20 GeV)");
    tex = new TLatex(0.20, 0.80, "AK4jets");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();


   
    TString name_plot="perf_"+ name + "_Linear"+format;
//    if(log) name_plot="perf_"+ name + "Log"+format;
    c1->SaveAs(name_plot);
    TString name_plot3="perf_"+ name + "_Linear.gif";
    c1->SaveAs(name_plot3);


}

void DrawAllPlot(){

    bool log=true;

    TFile *myFile     = new TFile(filename_1);
    myFile->cd();

    TGraph* EffBvsUDSG[100];
    TGraph* EffBvsC[100];
    TGraph* BvsUDSG3;
    TGraph* BvsC3;

    // CREATE CANVAS

    setTDRStyle();
    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
    c1->SetFillColor(10);
    c1->cd();

  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetLogy(log);
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetTopMargin(0.065);
    c1_1->SetFrameBorderMode(0);

    gStyle->SetOptTitle(0);

    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.045);
    latex->SetTextFont(42); //22
    latex->SetTextAlign(13);

    TLegend* qw = 0;
    qw = new TLegend(0.20,0.55,0.40,0.74);
//    qw->SetFillColor(kWhite);
    TLegend* qw2 = 0;
    qw2 = new TLegend(0.82,0.15,0.95,0.25);
//    qw2->SetFillColor(kWhite);

    const char *disc_array[] = {"CSVIVF","DeepCSV", "DeepFlavour","CvsL_deep","CvsB_deep"};
    TString qw_array[] = {"CSVv2","DeepCSV","DeepJet","CvsL_deepCSV","CvsB_deepCSV"};
    int markerstyle[] = {20,21,22,21,21};
    int markercolor[] = {kBlue,8,2, 28, kViolet-5};


    std::vector<std::string> disc_names(disc_array, std::end(disc_array));

    int count = 0;

    cout << "Looping over disc. names\n";

    for(vector<string>::const_iterator iter = disc_names.begin(); iter != disc_names.end(); ++iter) {

        TH1D* disc_b;
        TH1D* disc_c;
        TH1D* disc_l;
        TH1D* disc_g;
        TH1D* disc_bfg;
        TH1D* disc_cfg;

        disc_b         = (TH1D*)gROOT->FindObject((*iter+"_b").c_str());
        disc_c         = (TH1D*)gROOT->FindObject((*iter+"_c").c_str());
        disc_l         = (TH1D*)gROOT->FindObject((*iter+"_l").c_str());
        disc_g         = (TH1D*)gROOT->FindObject((*iter+"_g").c_str());
        disc_bfg       = (TH1D*)gROOT->FindObject((*iter+"_bfromg").c_str());
        disc_cfg       = (TH1D*)gROOT->FindObject((*iter+"_cfromg").c_str());

        disc_l->Add(disc_g);
    if (wgsplit) {
        disc_b->Add(disc_bfg);
        disc_c->Add(disc_cfg);
    }

        int nbin_max= disc_b->GetNbinsX()+1;

        Double_t eff_b[nbin_max];
        Double_t eff_l[nbin_max];
        Double_t eff_c[nbin_max];

        Double_t err_b[nbin_max];
        Double_t err_l[nbin_max];
        Double_t err_c[nbin_max];

        ComputeEffAndErr(disc_b, disc_c, disc_l, eff_b, err_b, eff_c, err_c, eff_l, err_l);

        if (count==1) {
           cout << " eff "<< eff_b[0] << "  " << eff_c[0] << "  " << eff_l[0] << endl;
           cout << " eff "<< eff_b[1] << "  " << eff_c[1] << "  " << eff_l[1] << endl;
           cout << " eff "<< eff_b[2] << "  " << eff_c[2] << "  " << eff_l[2] << endl;
        }

        TGraphErrors* BvsUDSG = new TGraphErrors(nbin_max,eff_b,eff_l,err_b,err_l);
        TGraphErrors* BvsC    = new TGraphErrors(nbin_max,eff_b,eff_c,err_b,err_c);

        BvsUDSG->GetXaxis()->SetLimits(0.,1.);
        BvsUDSG->GetHistogram()->SetMaximum(1.);
        BvsUDSG->GetHistogram()->SetMinimum(0.0005);

        BvsC->GetXaxis()->SetLimits(0.,1.);
        BvsC->GetHistogram()->SetMaximum(1.);
        BvsC->GetHistogram()->SetMinimum(0.001);

        // SET COSMETICS

//        BvsUDSG->SetMarkerStyle(markerstyle[count]);
        BvsUDSG->SetMarkerStyle(1);
        BvsUDSG->SetMarkerColor(markercolor[count]);
        BvsUDSG->SetLineColor(markercolor[count]);
        BvsUDSG->SetLineWidth(2);
        BvsUDSG->SetMarkerSize(0.75);
        BvsUDSG->GetXaxis()->SetTitle("b-jet efficiency");
//        BvsUDSG->GetYaxis()->SetTitle("udsg-jet misid. probability");
        BvsUDSG->GetYaxis()->SetTitle("misid. probability");
        cout << "Cloning " << (*iter).c_str() << '\n';
        EffBvsUDSG[count] = (TGraphErrors*)BvsUDSG->Clone();

//        BvsC->SetMarkerStyle(markerstyle[count]+4);
        BvsC->SetMarkerStyle(1);
        BvsC->SetMarkerSize(0.75);
        BvsC->SetMarkerColor(markercolor[count]);
        BvsC->SetLineColor(markercolor[count]);
        BvsC->SetLineWidth(4);
        BvsC->SetLineStyle(2);
        BvsC->GetXaxis()->SetTitle("b-jet efficiency");
//        BvsC->GetYaxis()->SetTitle("c-jet misid. probability");
        BvsC->GetYaxis()->SetTitle("misid. probability");

        EffBvsC[count] = (TGraphErrors*)BvsC->Clone();

//        qw->AddEntry(BvsUDSG, (*iter).c_str() ,"p");
        qw->AddEntry(BvsUDSG, qw_array[count],"l");
        ++count;
        if (count==3) {
          BvsUDSG3= (TGraphErrors*)BvsUDSG->Clone();
          BvsC3= (TGraphErrors*)BvsC->Clone();
          BvsUDSG3->SetMarkerStyle(markerstyle[0]);
          BvsUDSG3->SetMarkerColor(1.);
          BvsUDSG3->SetLineColor(1.);
          BvsC3->SetMarkerStyle(markerstyle[0]+4);
          BvsC3->SetMarkerColor(1.);
          BvsC3->SetLineColor(1.);
//          qw2->AddEntry(BvsUDSG3, "udsg","p");
//          qw2->AddEntry(BvsC3, "c","p");
          qw2->AddEntry(BvsUDSG3, "udsg","l");
          qw2->AddEntry(BvsC3, "c","l");
        }
    }

    c1->cd();
    c1_1->cd();
    c1_1->SetGridy();
    c1_1->SetGridx();
    cout << "Drawing the graphs\n";


    EffBvsUDSG[0]->GetHistogram()->SetTitleSize(0.08,"Y");
    EffBvsUDSG[0]->GetHistogram()->SetTitleOffset(0.65,"Y");
    EffBvsUDSG[0]->GetHistogram()->SetTitleOffset(0.81,"Y");
    EffBvsUDSG[0]->GetHistogram()->GetYaxis()->SetLabelSize( 0.045 );
    EffBvsUDSG[0]->GetHistogram()->GetYaxis()->SetTitleSize( 0.06 );
    EffBvsUDSG[0]->GetHistogram()->GetXaxis()->SetLabelSize( 0.045 );
    EffBvsUDSG[0]->GetHistogram()->GetXaxis()->SetTitleSize( 0.055 );


    for (int tgs = 0; tgs < count; ++tgs){
        if (tgs == 0) EffBvsUDSG[tgs]->Draw("ALP E1X0");
        else EffBvsUDSG[tgs]->Draw("LPsame E1X0");
    }
    for (int tgs = 0; tgs < count; ++tgs){
//        if (tgs == 0) EffBvsC[tgs]->Draw("ALP");
//        else EffBvsC[tgs]->Draw("LPsame");
        EffBvsC[tgs]->Draw("LPsame E1X0");
    }

  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
     qw->SetFillColor(0);
    qw2->SetFillColor(0);

    qw->Draw();
    qw2->Draw();

TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV, 2016");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.92,"CMS Simulation");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();

    tex = new TLatex(0.20, 0.86, "t#bar{t} events");
//    tex = new TLatex(0.20, 0.86, "QCD events, trigger: jet p_{T} > 60 GeV");
//    tex = new TLatex(0.20, 0.86, "multijet events");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
//    tex = new TLatex(0.20, 0.80, "Jet p_{T} > 30 GeV, |#eta| < 2.4");
//    tex = new TLatex(0.20, 0.80, "AK4jets (p_{T} > 30 GeV)");
    tex = new TLatex(0.20, 0.80, "AK4jets (p_{T} > 20 GeV)");
//    tex = new TLatex(0.20, 0.80, "Jet p_{T} > 60 GeV, |#eta| < 2.4");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();


   
    TString name_plot="perf_Lin"+format;
    if(log) name_plot="perf_Log"+format;
    c1->SaveAs(name_plot);


}


void DrawAllPlot2( int flag_cvsb){

    bool log=true;

    TFile *myFile     = new TFile(filename_1);
    myFile->cd();

    TGraph* EffCvsUDSG[100];
    TGraph* EffCvsB[100];
    TGraph* CvsUDSG3;
    TGraph* CvsC3;

    // CREATE CANVAS

    setTDRStyle();
    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
    c1->SetFillColor(10);
    c1->cd();

  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetLogy(log);
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetTopMargin(0.065);
    c1_1->SetFrameBorderMode(0);

    gStyle->SetOptTitle(0);

    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.045);
    latex->SetTextFont(42); //22
    latex->SetTextAlign(13);

    TLegend* qw = 0;
    qw = new TLegend(0.67,0.25,0.95,0.40);
//    qw->SetFillColor(kWhite);
    TLegend* qw2 = 0;
    qw2 = new TLegend(0.82,0.15,0.95,0.25);
//    qw2->SetFillColor(kWhite);

    TString name_ctag;
    TString name2_ctag;
    TString name_deep;
    TString name2_deep;
    if (flag_cvsb==1) {
       name_ctag= "ctag_vb";
       name_deep= "deep_cvl"; // swap
       name2_ctag= "c-tagger CvsB";
       name2_deep= "DeepCSV CvsB";
    }
    else {
       name_ctag= "ctag_vl";
       name_deep= "deep_cvb"; // swap
       name2_ctag= "c-tagger CvsL";
       name2_deep= "DeepCSV CvsL";
    }



    // for the paper
    const char *disc_array[] = {"CSVIVF", "cMVA", name_deep, name_ctag};
    TString qw_array[] = {"CSVv2","cMVAv2", name2_deep, name2_ctag};
    int markerstyle[] = {21,22, 22, 22};
    int markercolor[] = {kBlue,2, kViolet-5,8};

 
/* 
    // for DP
    const char *disc_array[] = {"CSVIVF",  name_ctag, name_deep};
    TString qw_array[] = {"CSVv2", name2_ctag, name2_deep};
    int markerstyle[] = {21, 22, 22};
    int markercolor[] = {kBlue, 8, kViolet-5};
*/


//
/*
    const char *disc_array[] = {"CSVIVF", "cMVA", name_ctag};
    TString qw_array[] = {"CSVv2","cMVAv2", name2_ctag};
    int markerstyle[] = {21,22, 22};
    int markercolor[] = {kBlue,2, 8};
*/

    std::vector<std::string> disc_names(disc_array, std::end(disc_array));

    int count = 0;

    cout << "Looping over disc. names\n";

    for(vector<string>::const_iterator iter = disc_names.begin(); iter != disc_names.end(); ++iter) {

        TH1D* disc_b;
        TH1D* disc_c;
        TH1D* disc_l;
        TH1D* disc_g;
        TH1D* disc_bfg;
        TH1D* disc_cfg;

        disc_b         = (TH1D*)gROOT->FindObject((*iter+"_b").c_str());
        disc_c         = (TH1D*)gROOT->FindObject((*iter+"_c").c_str());
        disc_l         = (TH1D*)gROOT->FindObject((*iter+"_l").c_str());
        disc_g         = (TH1D*)gROOT->FindObject((*iter+"_g").c_str());
        disc_bfg       = (TH1D*)gROOT->FindObject((*iter+"_bfromg").c_str());
        disc_cfg       = (TH1D*)gROOT->FindObject((*iter+"_cfromg").c_str());

        cout << " histo "<< (*iter+"_b").c_str() << endl;

        disc_l->Add(disc_g);
    if (wgsplit) {
        disc_b->Add(disc_bfg);
        disc_c->Add(disc_cfg);
    }

        int nbin_max= disc_b->GetNbinsX()+1;

        Double_t eff_b[nbin_max];
        Double_t eff_l[nbin_max];
        Double_t eff_c[nbin_max];

        Double_t err_b[nbin_max];
        Double_t err_l[nbin_max];
        Double_t err_c[nbin_max];

        if (flag_cvsb==1 && (qw_array[count]=="CSVv2" || qw_array[count]=="cMVAv2")) {
            cout << "special treatment of efficiency computation : reverse order "<< endl;
            ComputeRevEffAndErr(disc_b, disc_c, disc_l, eff_b, err_b, eff_c, err_c, eff_l, err_l);
        }
        else {
            ComputeEffAndErr(disc_b, disc_c, disc_l, eff_b, err_b, eff_c, err_c, eff_l, err_l);
        }

        TGraphErrors* CvsUDSG = new TGraphErrors(nbin_max,eff_c,eff_l,err_c,err_l);
        TGraphErrors* CvsB    = new TGraphErrors(nbin_max,eff_c,eff_b,err_c,err_b);

        CvsUDSG->GetXaxis()->SetLimits(0.,1.);
        CvsUDSG->GetHistogram()->SetMaximum(1.);
        CvsUDSG->GetHistogram()->SetMinimum(0.0005);

        CvsB->GetXaxis()->SetLimits(0.,1.);
        CvsB->GetHistogram()->SetMaximum(1.);
        CvsB->GetHistogram()->SetMinimum(0.001);

        // SET COSMETICS

//        BvsUDSG->SetMarkerStyle(markerstyle[count]);
        CvsUDSG->SetMarkerStyle(1);
        CvsUDSG->SetMarkerColor(markercolor[count]);
        CvsUDSG->SetLineColor(markercolor[count]);
        CvsUDSG->SetLineWidth(2);
        CvsUDSG->SetMarkerSize(0.75);
        CvsUDSG->GetXaxis()->SetTitle("c-jet efficiency");
        CvsUDSG->GetYaxis()->SetTitle("udsg-jet misid. probability");
//      CvsUDSG->GetYaxis()->SetTitle("misid. probability");
        cout << "Cloning " << (*iter).c_str() << '\n';
        EffCvsUDSG[count] = (TGraphErrors*)CvsUDSG->Clone();

//        CvsB->SetMarkerStyle(markerstyle[count]+4);
        CvsB->SetMarkerStyle(1);
        CvsB->SetMarkerSize(0.75);
        CvsB->SetMarkerColor(markercolor[count]);
        CvsB->SetLineColor(markercolor[count]);
        CvsB->SetLineWidth(2);
//        CvsB->SetLineWidth(4);
//        CvsB->SetLineStyle(2);
        CvsB->GetXaxis()->SetTitle("c-jet efficiency");
        CvsB->GetYaxis()->SetTitle("b-jet misid. probability");
//      CvsB->GetYaxis()->SetTitle("misid. probability");

        EffCvsB[count] = (TGraphErrors*)CvsB->Clone();

        qw->AddEntry(CvsUDSG, qw_array[count],"l");
        ++count;
/*
        if (count==3) {
          CvsUDSG3= (TGraphErrors*)CvsUDSG->Clone();
          CvsB3= (TGraphErrors*)CvsB->Clone();
          CvsUDSG3->SetMarkerStyle(markerstyle[0]);
          CvsUDSG3->SetMarkerColor(1.);
          CvsUDSG3->SetLineColor(1.);
          CvsB3->SetMarkerStyle(markerstyle[0]+4);
          CvsB3->SetMarkerColor(1.);
          CvsB3->SetLineColor(1.);
//          qw2->AddEntry(BvsUDSG3, "udsg","p");
//          qw2->AddEntry(BvsC3, "c","p");
          qw2->AddEntry(BvsUDSG3, "udsg","l");
          qw2->AddEntry(BvsC3, "c","l");
        }
*/
    }

    c1->cd();
    c1_1->cd();
    c1_1->SetGridy();
    c1_1->SetGridx();
    cout << "Drawing the graphs\n";


    EffCvsUDSG[0]->GetHistogram()->SetTitleSize(0.08,"Y");
    EffCvsUDSG[0]->GetHistogram()->SetTitleOffset(0.65,"Y");
    EffCvsUDSG[0]->GetHistogram()->SetTitleOffset(0.81,"Y");
    EffCvsUDSG[0]->GetHistogram()->GetYaxis()->SetLabelSize( 0.045 );
    EffCvsUDSG[0]->GetHistogram()->GetYaxis()->SetTitleSize( 0.06 );
    EffCvsUDSG[0]->GetHistogram()->GetXaxis()->SetLabelSize( 0.045 );
    EffCvsUDSG[0]->GetHistogram()->GetXaxis()->SetTitleSize( 0.055 );


   if (flag_cvsb!=1) {
    for (int tgs = 0; tgs < count; ++tgs){
        if (tgs == 0) EffCvsUDSG[tgs]->Draw("ALP E1X0");
        else EffCvsUDSG[tgs]->Draw("LPsame E1X0");
    }
   }
   else {
    for (int tgs = 0; tgs < count; ++tgs){
        if (tgs == 0) EffCvsB[tgs]->Draw("ALP E1X0");
        else EffCvsB[tgs]->Draw("LPsame E1X0");
//        EffCvsB[tgs]->Draw("LPsame E1X0");
    }
   }

  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
  qw->Draw();




TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV, 2018");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.92,"CMS Simulation");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();

    tex = new TLatex(0.20, 0.86, "t#bar{t} events");
//    tex = new TLatex(0.20, 0.86, "QCD events, trigger: jet p_{T} > 60 GeV");
//    tex = new TLatex(0.20, 0.86, "multijet events");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
//    tex = new TLatex(0.20, 0.80, "Jet p_{T} > 30 GeV, |#eta| < 2.4");
//    tex = new TLatex(0.20, 0.80, "AK4jets (p_{T} > 30 GeV)");
    tex = new TLatex(0.20, 0.80, "AK4jets (p_{T} > 20 GeV)");
//    tex = new TLatex(0.20, 0.80, "Jet p_{T} > 60 GeV, |#eta| < 2.4");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();


    TString stringcsv;
    if (flag_cvsb==1)  stringcsv="cvsb";
    else stringcsv="cvsl";
    TString name_plot="perf_"+stringcsv+"_Lin"+format;
    if(log) name_plot="perf_"+stringcsv+"_Log"+format;
    c1->SaveAs(name_plot);


}


void ComputeEffAndErr(TH1D* disc_b, TH1D* disc_c, TH1D* disc_l, Double_t * eff_b, Double_t * err_b, Double_t * eff_c, Double_t * err_c, Double_t * eff_l, Double_t * err_l)
{

        int nbin_max= disc_b->GetNbinsX();
        double tot_b=disc_b->Integral(0,nbin_max+2);
        double tot_c=disc_c->Integral(0,nbin_max+2);
        double tot_udsg=disc_l->Integral(0,nbin_max+2);

        // equivalent numbers (= number without weights with the same statistical error than weighted events)
        double neq_b=0;
        double neq_c=0;
        double neq_l=0;

        for (int ii=0; ii<nbin_max+2; ii++) {
          if (disc_b->GetBinError(ii)>0)  neq_b+=(disc_b->GetBinContent(ii)*disc_b->GetBinContent(ii)) / (disc_b->GetBinError(ii)*disc_b->GetBinError(ii));
          if (disc_c->GetBinError(ii)>0)  neq_c+=(disc_c->GetBinContent(ii)*disc_c->GetBinContent(ii)) / (disc_c->GetBinError(ii)*disc_c->GetBinError(ii));
          if (disc_l->GetBinError(ii)>0)  neq_l+=(disc_l->GetBinContent(ii)*disc_l->GetBinContent(ii)) / (disc_l->GetBinError(ii)*disc_l->GetBinError(ii));
        }

        for (int ii=0; ii<nbin_max+2; ii++) {

            double val_b=0., val_c=0., val_udsg=0.;
            double error_b=0., error_c=0., error_udsg=0.;


            if (tot_b > 0.) val_b = disc_b->Integral(ii+0,nbin_max+2) / tot_b;
            if (neq_b > 0.) error_b = sqrt(neq_b *val_b*(1.-val_b)) / neq_b;

            if (tot_c > 0.) val_c = disc_c->Integral(ii+0,nbin_max+2) / tot_c;
            if (neq_c > 0.) error_c = sqrt(neq_c *val_c*(1.-val_c)) / neq_c;

            if (tot_udsg > 0.) val_udsg = disc_l->Integral(ii+0,nbin_max+2) / tot_udsg;
            if (neq_l > 0.) error_udsg = sqrt(neq_l *val_udsg*(1.-val_udsg)) / neq_l;

            eff_b[ii] = val_b;
            err_b[ii] = error_b;

            eff_c[ii] = val_c;
            err_c[ii] = error_c;

            eff_l[ii] = val_udsg;
            err_l[ii] = error_udsg;

        }

}
void ComputeRevEffAndErr(TH1D* disc_b, TH1D* disc_c, TH1D* disc_l, Double_t * eff_b, Double_t * err_b, Double_t * eff_c, Double_t * err_c, Double_t * eff_l, Double_t * err_l)
{

        int nbin_max= disc_b->GetNbinsX();
        double tot_b=disc_b->Integral(0,nbin_max+2);
        double tot_c=disc_c->Integral(0,nbin_max+2);
        double tot_udsg=disc_l->Integral(0,nbin_max+2);

        // equivalent numbers (= number without weights with the same statistical error than weighted events)
        double neq_b=0;
        double neq_c=0;
        double neq_l=0;

        for (int ii=0; ii<nbin_max+2; ii++) {
          if (disc_b->GetBinError(ii)>0)  neq_b+=(disc_b->GetBinContent(ii)*disc_b->GetBinContent(ii)) / (disc_b->GetBinError(ii)*disc_b->GetBinError(ii));
          if (disc_c->GetBinError(ii)>0)  neq_c+=(disc_c->GetBinContent(ii)*disc_c->GetBinContent(ii)) / (disc_c->GetBinError(ii)*disc_c->GetBinError(ii));
          if (disc_l->GetBinError(ii)>0)  neq_l+=(disc_l->GetBinContent(ii)*disc_l->GetBinContent(ii)) / (disc_l->GetBinError(ii)*disc_l->GetBinError(ii));
        }

        for (int ii=0; ii<nbin_max+2; ii++) {

            double val_b=0., val_c=0., val_udsg=0.;
            double error_b=0., error_c=0., error_udsg=0.;


            if (tot_b > 0.) val_b = disc_b->Integral(0,ii+1) / tot_b;
            if (neq_b > 0.) error_b = sqrt(neq_b *val_b*(1.-val_b)) / neq_b;

            if (tot_c > 0.) val_c = disc_c->Integral(0,ii+1) / tot_c;
            if (neq_c > 0.) error_c = sqrt(neq_c *val_c*(1.-val_c)) / neq_c;

            if (tot_udsg > 0.) val_udsg = disc_l->Integral(0,ii+1) / tot_udsg;
            if (neq_l > 0.) error_udsg = sqrt(neq_l *val_udsg*(1.-val_udsg)) / neq_l;

            eff_b[ii] = val_b;
            err_b[ii] = error_b;

            eff_c[ii] = val_c;
            err_c[ii] = error_c;

            eff_l[ii] = val_udsg;
            err_l[ii] = error_udsg;

        }

}


void DrawEffvsPt(TString name){

    // File1
    TH1D* hist_b_r1;
    TH1D* hist_c_r1;
    TH1D* hist_l_r1;
    TH1D* hist_g_r1;
    TH1D* hist_gc_r1;
    TH1D* hist_gb_r1;

    TH1D* hist_b_1;
    TH1D* hist_c_1;
    TH1D* hist_l_1;
    TH1D* hist_g_1;
    TH1D* hist_gc_1;
    TH1D* hist_gb_1;
    TH1D* hist_b_2;
    TH1D* hist_c_2;
    TH1D* hist_l_2;
    TH1D* hist_g_2;
    TH1D* hist_gc_2;
    TH1D* hist_gb_2;
    TH1D* hist_b_3;
    TH1D* hist_c_3;
    TH1D* hist_l_3;
    TH1D* hist_g_3;
    TH1D* hist_gc_3;
    TH1D* hist_gb_3;

    TFile *myFile_1     = new TFile(filename_1);
    myFile_1->cd();

    hist_b_r1         = (TH1D*)gROOT->FindObject("jet_pt_nobtag_b");
    hist_c_r1         = (TH1D*)gROOT->FindObject("jet_pt_nobtag_c");
    hist_l_r1         = (TH1D*)gROOT->FindObject("jet_pt_nobtag_l");
    hist_g_r1         = (TH1D*)gROOT->FindObject("jet_pt_nobtag_g");
    hist_gb_r1         = (TH1D*)gROOT->FindObject("jet_pt_nobtag_bfromg");
    hist_gc_r1         = (TH1D*)gROOT->FindObject("jet_pt_nobtag_cfromg");

        hist_l_r1->Add(hist_g_r1);
    if (wgsplit) {
        hist_b_r1->Add(hist_gb_r1);
        hist_c_r1->Add(hist_gc_r1);
    }


    hist_b_1         = (TH1D*)gROOT->FindObject("jet_pt_ivf_b");
    hist_c_1         = (TH1D*)gROOT->FindObject("jet_pt_ivf_c");
    hist_l_1         = (TH1D*)gROOT->FindObject("jet_pt_ivf_l");
    hist_g_1         = (TH1D*)gROOT->FindObject("jet_pt_ivf_g");
    hist_gb_1         = (TH1D*)gROOT->FindObject("jet_pt_ivf_bfromg");
    hist_gc_1         = (TH1D*)gROOT->FindObject("jet_pt_ivf_cfromg");

        hist_l_1->Add(hist_g_1);
    if (wgsplit) {
        hist_b_1->Add(hist_gb_1);
        hist_c_1->Add(hist_gc_1);
    }

    hist_b_2         = (TH1D*)gROOT->FindObject("jet_pt_avr_b");
    hist_c_2         = (TH1D*)gROOT->FindObject("jet_pt_avr_c");
    hist_l_2         = (TH1D*)gROOT->FindObject("jet_pt_avr_l");
    hist_g_2         = (TH1D*)gROOT->FindObject("jet_pt_avr_g");
    hist_gb_2         = (TH1D*)gROOT->FindObject("jet_pt_avr_bfromg");
    hist_gc_2         = (TH1D*)gROOT->FindObject("jet_pt_avr_cfromg");

        hist_l_2->Add(hist_g_2);
    if (wgsplit) {
        hist_b_2->Add(hist_gb_2);
        hist_c_2->Add(hist_gc_2);
    }

    hist_b_3         = (TH1D*)gROOT->FindObject("jet_pt_2sv_b");
    hist_c_3         = (TH1D*)gROOT->FindObject("jet_pt_2sv_c");
    hist_l_3         = (TH1D*)gROOT->FindObject("jet_pt_2sv_l");
    hist_g_3         = (TH1D*)gROOT->FindObject("jet_pt_2sv_g");
    hist_gb_3         = (TH1D*)gROOT->FindObject("jet_pt_2sv_bfromg");
    hist_gc_3         = (TH1D*)gROOT->FindObject("jet_pt_2sv_cfromg");

        hist_l_3->Add(hist_g_3);
    if (wgsplit) {
        hist_b_3->Add(hist_gb_3);
        hist_c_3->Add(hist_gc_3);
    }
    int nbin_max_1= hist_b_1->GetNbinsX();
    float minx=hist_b_1->GetXaxis()->GetXmin();
    float maxx=hist_b_1->GetXaxis()->GetXmax();
    cout << "nbin_max_1 "<< nbin_max_1 << "   " << minx << "  " << maxx << endl;

    cout << " Efficency for "<< name << endl;
    cout << " Loose  "<< hist_b_1->Integral()/hist_b_r1->Integral() << endl;
    cout << " Medium "<< hist_b_2->Integral()/hist_b_r1->Integral() << endl;
    cout << " Tight  "<< hist_b_3->Integral()/hist_b_r1->Integral() << endl;
    cout << endl;

    TH1D * Eff1_b= new TH1D ("Eff1_b",name,nbin_max_1,minx,maxx);
    TH1D * Eff1_c = new TH1D ("Eff1_c",name,nbin_max_1,minx,maxx);
    TH1D * Eff1_l = new TH1D ("Eff1_l",name,nbin_max_1,minx,maxx);
    TH1D * Eff2_b= new TH1D ("Eff2_b",name,nbin_max_1,minx,maxx);
    TH1D * Eff2_c = new TH1D ("Eff2_c",name,nbin_max_1,minx,maxx);
    TH1D * Eff2_l = new TH1D ("Eff2_l",name,nbin_max_1,minx,maxx);
    TH1D * Eff3_b= new TH1D ("Eff3_b",name,nbin_max_1,minx,maxx);
    TH1D * Eff3_c = new TH1D ("Eff3_c",name,nbin_max_1,minx,maxx);
    TH1D * Eff3_l = new TH1D ("Eff3_l",name,nbin_max_1,minx,maxx);

    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_1,hist_c_1,hist_l_1,Eff1_b,Eff1_c,Eff1_l, 8) ;
    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_2,hist_c_2,hist_l_2,Eff2_b,Eff2_c,Eff2_l, kBlue) ;
    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_3,hist_c_3,hist_l_3,Eff3_b,Eff3_c,Eff3_l, 2) ;


    Eff1_c->SetMaximum(0.6);        
    Eff1_l->SetMaximum(0.35);        


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    // CREATE CANVAS

/*
    Eff1_b->GetXaxis()->SetRangeUser(0,200);
    Eff1_c->GetXaxis()->SetRangeUser(0,200);
    Eff1_l->GetXaxis()->SetRangeUser(0,200);
*/

    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);


    c1->SetFillColor(10);
    c1->cd();
  c1->SetBorderMode(0);  
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
   c1_1->SetLeftMargin(0.1461539);
   c1_1->SetRightMargin(0.05384616);
   c1_1->SetTopMargin(0.06831119);
   c1_1->SetBottomMargin(0.1574953);
    c1_1->SetFrameBorderMode(0);
    c1_1->cd(); 
    c1_1->SetGridy();


    TLegend* qw = 0;
//    qw = new TLegend(0.13,0.22,0.33,0.39,NULL,"brNDC"); // Caro
    qw = new TLegend(0.1884615,0.2144213,0.3602564,0.4079696,NULL,"brNDC"); 
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);

    qw->AddEntry(Eff1_b, "IVF", "p");
    qw->AddEntry(Eff2_b, "AVR", "p");
    qw->AddEntry(Eff3_b, "IVF & AVR", "p");

    Eff1_b->SetTitleSize(0.08,"Y");
    Eff1_b->SetTitleOffset(0.65,"Y");  
    Eff1_b->SetTitleOffset(0.81,"Y");
    Eff1_b->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_b->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_b->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_b->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_b->GetYaxis()->SetTitleOffset(0.9);
    Eff1_b->SetMarkerStyle(7);
    Eff2_b->SetMarkerStyle(7);
    Eff3_b->SetMarkerStyle(7);
    Eff1_b->SetMarkerSize(2);
    Eff2_b->SetMarkerSize(2);
    Eff3_b->SetMarkerSize(2);
    Eff1_b->Draw();
    Eff1_b->GetXaxis()->SetRangeUser(0,200);
    Eff1_c->GetXaxis()->SetRangeUser(0,200);
    Eff1_l->GetXaxis()->SetRangeUser(0,200);


    if (name=="cmvav2" && printfunc) {
     // Loose
/*
     TF1* fun1_b = new TF1("fun1_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,120.);
     fun1_b->SetParameter(0, 0.390116);
     fun1_b->SetParameter(1, 0.017563);
     fun1_b->SetParameter(2, -0.000251589);
     fun1_b->SetParameter(3, 1.59848e-06 );
     fun1_b->SetParameter(4, -3.78592e-09) ;
     fun1_b->SetLineColor(8);
     fun1_b->Draw("same");
     TF1* fun1_b2= new TF1("fun1_b2","[0]+[1]*x+[2]*pow(x,2)",115.,1000.);
     fun1_b2->SetParameter(0, 0.871303);
     fun1_b2->SetParameter(1, -0.000167681);
     fun1_b2->SetParameter(2, 3.64797e-08);
     fun1_b2->SetLineColor(8);
     fun1_b2->Draw("same");
*/

     TF1* rfun1_b = new TF1("rfun1_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,120.);
     rfun1_b->SetParameter(0, 0.390);
     rfun1_b->SetParameter(1, 0.0176);
     rfun1_b->SetParameter(2, -2.518e-04);
     rfun1_b->SetParameter(3, 1.598e-06 );
     rfun1_b->SetParameter(4, -3.786e-09) ;
     rfun1_b->SetLineColor(8);
     rfun1_b->Draw("same");
     TF1* rfun1_b2= new TF1("rfun1_b2","[0]+[1]*x+[2]*pow(x,2)",115.,1000.);
     rfun1_b2->SetParameter(0, 0.871);
     rfun1_b2->SetParameter(1, -1.68e-04);
     rfun1_b2->SetParameter(2, 3.65e-08);
     rfun1_b2->SetLineColor(8);
     rfun1_b2->Draw("same");


/*
     TF1* fun2_b = new TF1("fun2_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,130.);
     fun2_b->SetParameter(0, 0.172494);
     fun2_b->SetParameter(1, 0.0187559);
     fun2_b->SetParameter(2, -0.00024156);
     fun2_b->SetParameter(3,   1.35432e-06);
     fun2_b->SetParameter(4, -2.81669e-09);
     fun2_b->SetLineColor(kBlue);
     fun2_b->Draw("same");
     TF1* fun2_b2= new TF1("fun2_b2","[0]+[1]*x+[2]*pow(x,2)",125.,1000.);
     fun2_b2->SetParameter(0, 0.785332);
     fun2_b2->SetParameter(1, -0.000688402);
     fun2_b2->SetParameter(2,  2.72019e-07);
     fun2_b2->SetLineColor(kBlue);
     fun2_b2->Draw("same");
*/

     TF1* rfun2_b = new TF1("rfun2_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,130.);
     rfun2_b->SetParameter(0, 0.1725);
     rfun2_b->SetParameter(1, 0.01876);
     rfun2_b->SetParameter(2, -2.416e-04);
     rfun2_b->SetParameter(3, 1.354e-06);
     rfun2_b->SetParameter(4, -2.817e-09);
     rfun2_b->SetLineColor(kBlue);
     rfun2_b->Draw("same");
     TF1* rfun2_b2= new TF1("rfun2_b2","[0]+[1]*x+[2]*pow(x,2)",125.,1000.);
     rfun2_b2->SetParameter(0, 0.785);
     rfun2_b2->SetParameter(1, -6.88e-04);
     rfun2_b2->SetParameter(2,  2.72e-07);
     rfun2_b2->SetLineColor(kBlue);
     rfun2_b2->Draw("same");


     TF1* fun3_b = new TF1("fun3_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,160.);
     fun3_b->SetParameter(0, -0.0793627);
     fun3_b->SetParameter(1, 0.0227807);
     fun3_b->SetParameter(2,-0.000307868);
     fun3_b->SetParameter(3,1.81316e-06 );
     fun3_b->SetParameter(4,-3.99115e-09);
     fun3_b->SetLineColor(2);
     fun3_b->Draw("same");
     TF1* fun3_b2= new TF1("fun3_b2","[0]+[1]*x+[2]*pow(x,2)",155.,1000.);
     fun3_b2->SetParameter(0,0.650046); 
     fun3_b2->SetParameter(1, -0.00107534);
     fun3_b2->SetParameter(2, 5.65376e-07);
     fun3_b2->SetLineColor(2);
     fun3_b2->Draw("same");


     TF1* rfun3_b = new TF1("rfun3_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,160.);
     rfun3_b->SetParameter(0, -0.0794);
     rfun3_b->SetParameter(1, 0.0228);
     rfun3_b->SetParameter(2, -3.08e-04);
     rfun3_b->SetParameter(3, 1.813e-06 );
     rfun3_b->SetParameter(4, -3.991e-09);
     rfun3_b->SetLineColor(2);
     rfun3_b->Draw("same");
     TF1* rfun3_b2= new TF1("rfun3_b2","[0]+[1]*x+[2]*pow(x,2)",155.,1000.);
     rfun3_b2->SetParameter(0,0.650); 
     rfun3_b2->SetParameter(1, -1.07e-03);
     rfun3_b2->SetParameter(2, 5.65e-07);
     rfun3_b2->SetLineColor(2);
     rfun3_b2->Draw("same");


    }
    else if (name=="csvv2" && printfunc) {
     // Loose
/*
     TF1* fun1_b = new TF1("fun1_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,165.);
     fun1_b->SetParameter(0, 0.625404);
     fun1_b->SetParameter(1, 0.00629137);
     fun1_b->SetParameter(2, -7.44931e-05);
     fun1_b->SetParameter(3, 3.79928e-07 );
     fun1_b->SetParameter(4, -7.23654e-10);
     fun1_b->SetLineColor(1);
     fun1_b->Draw("same");
     TF1* fun1_b2= new TF1("fun1_b2","[0]+[1]*x+[2]*pow(x,2)",165.,1000.);
     fun1_b2->SetParameter(0, 0.845173); 
     fun1_b2->SetParameter(1, -0.000226895);
     fun1_b2->SetParameter(2,-2.12743e-08);
     fun1_b2->SetLineColor(1);
     fun1_b2->Draw("same");
*/

     // Loose
     TF1* rfun1_b = new TF1("rfun1_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,165.);
     rfun1_b->SetParameter(0, 0.625);
     rfun1_b->SetParameter(1, 0.0063);
     rfun1_b->SetParameter(2, -7.45e-05);
     rfun1_b->SetParameter(3, 3.80e-07 );
     rfun1_b->SetParameter(4, -7.24e-10);
     rfun1_b->SetLineColor(8);
     rfun1_b->Draw("same");
     TF1* rfun1_b2= new TF1("rfun1_b2","[0]+[1]*x+[2]*pow(x,2)",165.,1000.);
     rfun1_b2->SetParameter(0, 0.845); 
     rfun1_b2->SetParameter(1, -2.27e-04);
     rfun1_b2->SetParameter(2,-2.13e-08);
     rfun1_b2->SetLineColor(8);
     rfun1_b2->Draw("same");

/*
     TF1* fun2_b = new TF1("fun2_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,115.);
     fun2_b->SetParameter(0, 0.190846);
     fun2_b->SetParameter(1, 0.0177482);
     fun2_b->SetParameter(2, -0.000224877);
     fun2_b->SetParameter(3, 1.17774e-06);
     fun2_b->SetParameter(4, -2.13669e-09);
     fun2_b->SetLineColor(1);
     fun2_b->Draw("same");
     TF1* fun2_b2= new TF1("fun2_b2","[0]+[1]*x+[2]*pow(x,2)",115.,1000.);
     fun2_b2->SetParameter(0, 0.765334); 
     fun2_b2->SetParameter(1, -0.000820586);
     fun2_b2->SetParameter(2,3.21459e-07);
     fun2_b2->SetLineColor(1);
     fun2_b2->Draw("same");
*/

     TF1* rfun2_b = new TF1("rfun2_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,115.);
     rfun2_b->SetParameter(0, 0.1908);
     rfun2_b->SetParameter(1, 0.01775);
     rfun2_b->SetParameter(2, -2.2488e-04);
     rfun2_b->SetParameter(3, 1.178e-06);
     rfun2_b->SetParameter(4, -2.14e-09);
     rfun2_b->SetLineColor(kBlue);
     rfun2_b->Draw("same");
     TF1* rfun2_b2= new TF1("rfun2_b2","[0]+[1]*x+[2]*pow(x,2)",115.,1000.);
     rfun2_b2->SetParameter(0, 0.765); 
     rfun2_b2->SetParameter(1, -8.21e-04);
     rfun2_b2->SetParameter(2,3.21e-07);
     rfun2_b2->SetLineColor(kBlue);
     rfun2_b2->Draw("same");


/*

     TF1* fun3_b = new TF1("fun3_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,105.);
     fun3_b->SetParameter(0,-0.127222); 
     fun3_b->SetParameter(1, 0.0251803);
     fun3_b->SetParameter(2,-0.000365723);
     fun3_b->SetParameter(3,2.28646e-06);
     fun3_b->SetParameter(4,-5.2336e-09);
     fun3_b->SetLineColor(1);
     fun3_b->Draw("same");
     TF1* fun3_b2= new TF1("fun3_b2","[0]+[1]*x+[2]*pow(x,2)",105.,1000.);
     fun3_b2->SetParameter(0,0.597455 );
     fun3_b2->SetParameter(1,-0.00102487);
     fun3_b2->SetParameter(2,5.41659e-07);
     fun3_b2->SetLineColor(1);
     fun3_b2->Draw("same");
*/



     TF1* rfun3_b = new TF1("rfun3_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,105.);
     rfun3_b->SetParameter(0,-0.127); 
     rfun3_b->SetParameter(1, 0.0252);
     rfun3_b->SetParameter(2,-3.657e-04);
     rfun3_b->SetParameter(3,2.286e-06);
     rfun3_b->SetParameter(4,-5.23e-09);
     rfun3_b->SetLineColor(2);
     rfun3_b->Draw("same");
     TF1* rfun3_b2= new TF1("rfun3_b2","[0]+[1]*x+[2]*pow(x,2)",105.,1000.);
     rfun3_b2->SetParameter(0,0.597 );
     rfun3_b2->SetParameter(1,-1.02e-03);
     rfun3_b2->SetParameter(2,5.42e-07);
     rfun3_b2->SetLineColor(2);
     rfun3_b2->Draw("same");

    }


    Eff1_b->Draw("same");
    Eff2_b->Draw("same");
    Eff3_b->Draw("same");


    TLatex *   tex1 = new TLatex(0.8782051,0.9506641,"#sqrt{s}=13 TeV, 2016");
    tex1->SetNDC();
    tex1->SetTextAlign(31);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.04875);
    tex1->SetLineWidth(2);
    tex1->Draw();
//    TLatex *  tex2 = new TLatex(0.5782051,0.9184061,"CMS Simulation");
    TLatex *  tex2 = new TLatex(0.1935897,0.9089184,"CMS Simulation");
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.065);
    tex2->SetLineWidth(2);
    tex2->Draw();


    qw->Draw();
    TString name_plot="effvspt_b_"+name+format;
    if (printfunc) name_plot="fit_"+name_plot;
    c1->SaveAs(name_plot);

    TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
    c2->cd();
  c2->SetBorderMode(0);  
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderMode(0);

    TPad *c2_1 = new TPad("canvas_2", "canvas_2",0,0,1.0,1.0);
    c2_1->SetFillColor(0);
    c2_1->SetBorderMode(0);
    c2_1->SetBorderSize(2);
   c2_1->SetLeftMargin(0.1461539);
   c2_1->SetRightMargin(0.05384616);
   c2_1->SetTopMargin(0.06831119);
   c2_1->SetBottomMargin(0.1574953);
    c2_1->SetFrameBorderMode(0);
    c2_1->Draw();
    c2_1->cd();
    c2_1->SetGridy();

    TLegend* qw2 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw2 = new TLegend(0.6666667,0.7343454,0.8666667,0.9032258,NULL,"brNDC");
    qw2->AddEntry(Eff1_b, "IVF", "p");
    qw2->AddEntry(Eff2_b, "AVR", "p");
    qw2->AddEntry(Eff3_b, "IVF & AVR", "p");
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
    Eff1_c->SetTitleSize(0.08,"Y");
    Eff1_c->SetTitleOffset(0.65,"Y");  
    Eff1_c->SetTitleOffset(0.81,"Y");
    Eff1_c->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_c->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_c->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_c->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_c->GetYaxis()->SetTitleOffset(0.9);

    Eff1_c->SetMarkerStyle(7);
    Eff2_c->SetMarkerStyle(7);
    Eff3_c->SetMarkerStyle(7);
    Eff1_c->SetMarkerSize(2);
    Eff2_c->SetMarkerSize(2);
    Eff3_c->SetMarkerSize(2);
    Eff1_c->Draw("L");
    if (name=="cmvav2" and printfunc) {
/*
     TF1* fun1_c = new TF1("fun1_c","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)",30.,1000.);
     fun1_c->SetParameter(0,0.312228);
     fun1_c->SetParameter(1,0.00137164);
     fun1_c->SetParameter(2,-6.5563e-06);
     fun1_c->SetParameter(3,1.43096e-08);
     fun1_c->SetParameter(4,-1.39982e-11);
     fun1_c->SetParameter(5,5.04312e-15 );
     fun1_c->SetLineColor(1);
     fun1_c->Draw("same");
*/
     TF1* rfun1_c = new TF1("rfun1_c","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)",30.,1000.);
     rfun1_c->SetParameter(0,0.312);
     rfun1_c->SetParameter(1,0.00137);
     rfun1_c->SetParameter(2,-6.556e-06);
     rfun1_c->SetParameter(3,1.431e-08);
     rfun1_c->SetParameter(4,-1.40e-11);
     rfun1_c->SetParameter(5,5.043e-15 );
     rfun1_c->SetLineColor(8);
     rfun1_c->Draw("same");

/*
     TF1* fun2_c = new TF1("fun2_c","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)",30.,1000.);
     fun2_c->SetParameter(0,0.101931);
     fun2_c->SetParameter(1,0.000824452);
     fun2_c->SetParameter(2,-4.71195e-06);
     fun2_c->SetParameter(3,1.02355e-08 );
     fun2_c->SetParameter(4,-9.83593e-12);
     fun2_c->SetParameter(5,3.50961e-15 );
     fun2_c->SetLineColor(1);
     fun2_c->Draw("same");
*/
     TF1* rfun2_c = new TF1("rfun2_c","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)",30.,1000.);
     rfun2_c->SetParameter(0,0.102);
     rfun2_c->SetParameter(1,8.24e-04);
     rfun2_c->SetParameter(2,-4.712e-06);
     rfun2_c->SetParameter(3,1.0235e-08 );
     rfun2_c->SetParameter(4,-9.836e-12);
     rfun2_c->SetParameter(5,3.51e-15 );
     rfun2_c->SetLineColor(kBlue);
     rfun2_c->Draw("same");

/*
     TF1* fun3_c = new TF1("fun3_c","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)",30.,1000.);
     fun3_c->SetParameter(0,0.0206985);
     fun3_c->SetParameter(1,0.000236893);
     fun3_c->SetParameter(2,-1.4141e-06);
     fun3_c->SetParameter(3,2.99787e-09);
     fun3_c->SetParameter(4,-2.76415e-12);
     fun3_c->SetParameter(5,9.42036e-16);
     fun3_c->SetLineColor(1);
     fun3_c->Draw("same");
*/
     TF1* rfun3_c = new TF1("rfun3_c","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)",30.,1000.);
     rfun3_c->SetParameter(0,0.0207);
     rfun3_c->SetParameter(1,2.37e-04);
     rfun3_c->SetParameter(2,-1.41e-06);
     rfun3_c->SetParameter(3,2.99e-09);
     rfun3_c->SetParameter(4,-2.76e-12);
     rfun3_c->SetParameter(5,9.42e-16);
     rfun3_c->SetLineColor(2);
     rfun3_c->Draw("same");
    }
    else if (name=="csvv2" and printfunc) {
/*
     TF1* fun1_c = new TF1("fun1_c","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     fun1_c->SetParameter(0,0.347017);
     fun1_c->SetParameter(1,-5.08316e-05);
     fun1_c->SetParameter(2,-3.24605e-10);
     fun1_c->SetLineColor(1);
     fun1_c->Draw("same");

     TF1* fun2_c = new TF1("fun2_c","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     fun2_c->SetParameter(0,0.157019);
     fun2_c->SetParameter(1,-0.000175927);
     fun2_c->SetParameter(2,7.95035e-08);
     fun2_c->SetLineColor(1);
     fun2_c->Draw("same");

     TF1* fun3_c = new TF1("fun3_c","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     fun3_c->SetParameter(0,0.0303739);
     fun3_c->SetParameter(1,-3.3768e-05);
     fun3_c->SetParameter(2,1.54025e-08);
     fun3_c->SetLineColor(1);
     fun3_c->Draw("same");
*/

     TF1* rfun1_c = new TF1("rfun1_c","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     rfun1_c->SetParameter(0,0.347);
     rfun1_c->SetParameter(1,-5.08e-05);
     rfun1_c->SetParameter(2,-3.25e-10);
     rfun1_c->SetLineColor(8);
     rfun1_c->Draw("same");

     TF1* rfun2_c = new TF1("rfun2_c","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     rfun2_c->SetParameter(0,0.157);
     rfun2_c->SetParameter(1,-1.76e-04);
     rfun2_c->SetParameter(2,7.95e-08);
     rfun2_c->SetLineColor(kBlue);
     rfun2_c->Draw("same");

     TF1* rfun3_c = new TF1("rfun3_c","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     rfun3_c->SetParameter(0,0.0304);
     rfun3_c->SetParameter(1,-3.38e-05);
     rfun3_c->SetParameter(2,1.54e-08);
     rfun3_c->SetLineColor(2);
     rfun3_c->Draw("same");
    }
    Eff1_c->Draw("L same");
    Eff2_c->Draw("L same");
    Eff3_c->Draw("L same");
    qw2->Draw();
    tex1->Draw();
    tex2->Draw();
    TString name_plot2="effvspt_c_"+name+format;
    if (printfunc) name_plot2="fit_"+name_plot2;
    c2->SaveAs(name_plot2);

  
    TCanvas *c3 = new TCanvas("c3", "c3",10,32,782,552);
    c3->cd();
  c3->SetBorderMode(0);  
  c3->SetBorderSize(2);
  c3->SetFrameFillColor(0);
  c3->SetFrameBorderMode(0);
    TPad *c3_1 = new TPad("canvas_3", "canvas_3",0,0,1.0,1.0);
    c3_1->SetFillColor(0);
    c3_1->SetBorderMode(0);
    c3_1->SetBorderSize(2);
   c3_1->SetLeftMargin(0.1461539);
   c3_1->SetRightMargin(0.05384616);
   c3_1->SetTopMargin(0.06831119);
   c3_1->SetBottomMargin(0.1574953);
    c3_1->SetFrameBorderMode(0);
    c3_1->Draw();
    c3_1->cd();
    c3_1->SetGridy();

    Eff1_l->SetTitleSize(0.08,"Y");
    Eff1_l->SetTitleOffset(0.65,"Y");  
    Eff1_l->SetTitleOffset(0.81,"Y");
    Eff1_l->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_l->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_l->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_l->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_l->GetYaxis()->SetTitleOffset(0.9);
    Eff1_l->SetMarkerStyle(7);
    Eff2_l->SetMarkerStyle(7);
    Eff3_l->SetMarkerStyle(7);
    Eff1_l->SetMarkerSize(2);
    Eff2_l->SetMarkerSize(2);
    Eff3_l->SetMarkerSize(2);
    Eff1_l->Draw("L");
    if (name=="cmvav2" and printfunc) {

/*
     TF1* fun1_l = new TF1("fun1_l","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)+[6]*pow(x,6)+[7]*pow(x,7)",30.,1000.);
     fun1_l->SetParameter(0,0.100318);
     fun1_l->SetParameter(1,-0.000759263 );
     fun1_l->SetParameter(2,1.27781e-05);
     fun1_l->SetParameter(3,-6.32109e-08);
     fun1_l->SetParameter(4,1.57185e-10);
     fun1_l->SetParameter(5,-2.07647e-13);
     fun1_l->SetParameter(6,1.39145e-16);
     fun1_l->SetParameter(7,-3.72673e-20);
     fun1_l->SetLineColor(1);
     fun1_l->Draw("same");
*/


     TF1* rfun1_l = new TF1("rfun1_l","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)+[6]*pow(x,6)+[7]*pow(x,7)",30.,1000.);
     rfun1_l->SetParameter(0,0.1003);
     rfun1_l->SetParameter(1,-7.5926e-04 );
     rfun1_l->SetParameter(2,1.2778e-05);
     rfun1_l->SetParameter(3,-6.3211e-08);
     rfun1_l->SetParameter(4,1.5719e-10);
     rfun1_l->SetParameter(5,-2.07647e-13);
     rfun1_l->SetParameter(6,1.3914e-16);
     rfun1_l->SetParameter(7,-3.7267e-20);
     rfun1_l->SetLineColor(8);
     rfun1_l->Draw("same");



/*
     TF1* fun2_l = new TF1("fun2_l","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     fun2_l->SetParameter(0,0.00573761);
     fun2_l->SetParameter(1,5.23871e-05);
     fun2_l->SetParameter(2,-5.44813e-09);
     fun2_l->SetLineColor(1);
     fun2_l->Draw("same");

     TF1* fun3_l = new TF1("fun3_l","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     fun3_l->SetParameter(0,0.000503304);
     fun3_l->SetParameter(1,5.44438e-06);
     fun3_l->SetParameter(2, -4.98334e-10);
     fun3_l->SetLineColor(1);
     fun3_l->Draw("same");
*/

     TF1* rfun2_l = new TF1("rfun2_l","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     rfun2_l->SetParameter(0,5.74e-03);
     rfun2_l->SetParameter(1,5.24e-05);
     rfun2_l->SetParameter(2,-5.45e-09);
     rfun2_l->SetLineColor(kBlue);
     rfun2_l->Draw("same");

     TF1* rfun3_l = new TF1("rfun3_l","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     rfun3_l->SetParameter(0,5.03e-04);
     rfun3_l->SetParameter(1,5.44e-06);
     rfun3_l->SetParameter(2, -4.98e-10);
     rfun3_l->SetLineColor(2);
     rfun3_l->Draw("same");


    }
    else if (name=="csvv2" and printfunc) {
/*
     TF1* fun1_l = new TF1("fun1_l","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,195.);
     fun1_l->SetParameter(0,0.239697);
     fun1_l->SetParameter(1,-0.0060077);
     fun1_l->SetParameter(2,7.44621e-05);
     fun1_l->SetParameter(3,-3.7838e-07);
     fun1_l->SetParameter(4,6.96297e-10);
     fun1_l->SetLineColor(1);
     fun1_l->Draw("same");
     TF1* fun1_l2 = new TF1("fun1_l2","[0]+[1]*x+[2]*pow(x,2)",195.,1000.);
     fun1_l2->SetParameter(0,0.0652218);
     fun1_l2->SetParameter(1,0.000191387);
     fun1_l2->SetParameter(2,-5.82485e-08);
     fun1_l2->SetLineColor(1);
     fun1_l2->Draw("same");
*/

     TF1* rfun1_l = new TF1("rfun1_l","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,195.);
     rfun1_l->SetParameter(0,0.24);
     rfun1_l->SetParameter(1,-0.00601);
     rfun1_l->SetParameter(2,7.4462e-05);
     rfun1_l->SetParameter(3,-3.7838e-07);
     rfun1_l->SetParameter(4,6.96297e-10);
     rfun1_l->SetLineColor(8);
     rfun1_l->Draw("same");
     TF1* rfun1_l2 = new TF1("rfun1_l2","[0]+[1]*x+[2]*pow(x,2)",195.,1000.);
     rfun1_l2->SetParameter(0,0.065);
     rfun1_l2->SetParameter(1,1.91e-04);
     rfun1_l2->SetParameter(2,-5.82e-08);
     rfun1_l2->SetLineColor(8);
     rfun1_l2->Draw("same");

/*
     TF1* fun2_l = new TF1("fun2_l","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,65.);
     fun2_l->SetParameter(0,0.0301219);
     fun2_l->SetParameter(1,-0.00098619);
     fun2_l->SetParameter(2,1.61105e-05);
     fun2_l->SetParameter(3,-1.13902e-07);
     fun2_l->SetParameter(4,2.993e-10);
     fun2_l->SetLineColor(1);
     fun2_l->Draw("same");

     TF1* fun2_l2 = new TF1("fun2_l2","[0]+[1]*x+[2]*pow(x,2)",65.,1000.);
     fun2_l2->SetParameter(0,0.00677158);
     fun2_l2->SetParameter(1,2.04218e-05);
     fun2_l2->SetParameter(2,1.50644e-09);
     fun2_l2->SetLineColor(1);
     fun2_l2->Draw("same");
*/


     TF1* rfun2_l = new TF1("rfun2_l","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,65.);
     rfun2_l->SetParameter(0,0.030);
     rfun2_l->SetParameter(1,-9.862e-04);
     rfun2_l->SetParameter(2,1.611e-05);
     rfun2_l->SetParameter(3,-1.139e-07);
     rfun2_l->SetParameter(4,2.99e-10);
     rfun2_l->SetLineColor(kBlue);
     rfun2_l->Draw("same");

     TF1* rfun2_l2 = new TF1("rfun2_l2","[0]+[1]*x+[2]*pow(x,2)",65.,1000.);
     rfun2_l2->SetParameter(0,6.77e-03);
     rfun2_l2->SetParameter(1,2.04e-05);
     rfun2_l2->SetParameter(2,1.51e-09);
     rfun2_l2->SetLineColor(kBlue);
     rfun2_l2->Draw("same");

/*
     TF1* fun3_l = new TF1("fun3_l","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     fun3_l->SetParameter(0,0.000685174);
     fun3_l->SetParameter(1,3.8751e-06);
     fun3_l->SetParameter(2,-2.4856e-10);
     fun3_l->SetLineColor(1);
     fun3_l->Draw("same");
*/

     TF1* rfun3_l = new TF1("rfun3_l","[0]+[1]*x+[2]*pow(x,2)",30.,1000.);
     rfun3_l->SetParameter(0,6.85e-04);
     rfun3_l->SetParameter(1,3.87e-06);
     rfun3_l->SetParameter(2,-2.48e-10);
     rfun3_l->SetLineColor(2);
     rfun3_l->Draw("same");

    }


    Eff1_l->Draw("same");
    Eff2_l->Draw("L same");
    Eff3_l->Draw("L same");
    qw2->Draw(); 
    tex1->Draw();
    tex2->Draw();
    TString name_plot3="effvspt_l_"+name+format;
    if (printfunc) name_plot3="fit_"+name_plot3;
    c3->SaveAs(name_plot3);
    


}

void DrawEff(TString name, int flag1){

    // File1
    TH1D* hist_b_r1;
    TH1D* hist_c_r1;
    TH1D* hist_l_r1;
    TH1D* hist_g_r1;
    TH1D* hist_gc_r1;
    TH1D* hist_gb_r1;

    TH1D* hist_b_1;
    TH1D* hist_c_1;
    TH1D* hist_l_1;
    TH1D* hist_g_1;
    TH1D* hist_gc_1;
    TH1D* hist_gb_1;
    TH1D* hist_b_2;
    TH1D* hist_c_2;
    TH1D* hist_l_2;
    TH1D* hist_g_2;
    TH1D* hist_gc_2;
    TH1D* hist_gb_2;
    TH1D* hist_b_3;
    TH1D* hist_c_3;
    TH1D* hist_l_3;
    TH1D* hist_g_3;
    TH1D* hist_gc_3;
    TH1D* hist_gb_3;

    TFile *myFile_1     = new TFile(filename_1);
    myFile_1->cd();

    TString flagname;
    if (flag1==1) flagname="pt";
    else if (flag1==2) flagname="eta";
    else if (flag1==3) flagname="pu";

    hist_b_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");


    hist_l_r1->Add(hist_g_r1);
    if (wgsplit) {
        hist_b_r1->Add(hist_gb_r1);
        hist_c_r1->Add(hist_gc_r1);
    }


    hist_b_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_l_b");
    hist_c_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_l_c");
    hist_l_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_l_l");
    hist_g_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_l_g");
    hist_gb_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_l_bfromg");
    hist_gc_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_l_cfromg");

        hist_l_1->Add(hist_g_1);
    if (wgsplit) {
        hist_b_1->Add(hist_gb_1);
        hist_c_1->Add(hist_gc_1);
    }

    hist_b_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_m_b");
    hist_c_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_m_c");
    hist_l_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_m_l");
    hist_g_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_m_g");
    hist_gb_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_m_bfromg");
    hist_gc_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_m_cfromg");

        hist_l_2->Add(hist_g_2);
    if (wgsplit) {
        hist_b_2->Add(hist_gb_2);
        hist_c_2->Add(hist_gc_2);
    }

    hist_b_3         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_t_b");
    hist_c_3         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_t_c");
    hist_l_3         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_t_l");
    hist_g_3         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_t_g");
    hist_gb_3         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_t_bfromg");
    hist_gc_3         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_t_cfromg");


        hist_l_3->Add(hist_g_3);
    if (wgsplit) {
        hist_b_3->Add(hist_gb_3);
        hist_c_3->Add(hist_gc_3);
    }
    int nbin_max_1= hist_b_1->GetNbinsX();
    float minx=hist_b_1->GetXaxis()->GetXmin();
    float maxx=hist_b_1->GetXaxis()->GetXmax();
    cout << "nbin_max_1 "<< nbin_max_1 << "   " << minx << "  " << maxx << endl;

    cout << " Efficency for "<< name << endl;
    cout << " Loose  "<< hist_b_1->Integral()/hist_b_r1->Integral() << endl;
    cout << " Medium "<< hist_b_2->Integral()/hist_b_r1->Integral() << endl;
    cout << " Tight  "<< hist_b_3->Integral()/hist_b_r1->Integral() << endl;
    cout << endl;



/*
    TH1D * Eff1_b= new TH1D ("Eff1_b",name,nbin_max_1,minx,maxx);
    TH1D * Eff1_c = new TH1D ("Eff1_c",name,nbin_max_1,minx,maxx);
    TH1D * Eff1_l = new TH1D ("Eff1_l",name,nbin_max_1,minx,maxx);
    TH1D * Eff2_b= new TH1D ("Eff2_b",name,nbin_max_1,minx,maxx);
    TH1D * Eff2_c = new TH1D ("Eff2_c",name,nbin_max_1,minx,maxx);
    TH1D * Eff2_l = new TH1D ("Eff2_l",name,nbin_max_1,minx,maxx);
    TH1D * Eff3_b= new TH1D ("Eff3_b",name,nbin_max_1,minx,maxx);
    TH1D * Eff3_c = new TH1D ("Eff3_c",name,nbin_max_1,minx,maxx);
    TH1D * Eff3_l = new TH1D ("Eff3_l",name,nbin_max_1,minx,maxx);
*/

     TH1D * hist_clone = (TH1D*)hist_b_1->Clone("hist_clone");
     for (int i=0; i<hist_clone->GetNbinsX()+1; i++) {
        hist_clone->SetBinContent(i,0);
        hist_clone->SetBinError(i,0);
     }
     TH1D * Eff1_b= (TH1D*) hist_clone->Clone("Eff1_b");
     TH1D * Eff1_c= (TH1D*) hist_clone->Clone("Eff1_c");
     TH1D * Eff1_l= (TH1D*) hist_clone->Clone("Eff1_l");
     TH1D * Eff2_b= (TH1D*) hist_clone->Clone("Eff2_b");
     TH1D * Eff2_c= (TH1D*) hist_clone->Clone("Eff2_c");
     TH1D * Eff2_l= (TH1D*) hist_clone->Clone("Eff2_l");
     TH1D * Eff3_b= (TH1D*) hist_clone->Clone("Eff3_b");
     TH1D * Eff3_c= (TH1D*) hist_clone->Clone("Eff3_c");
     TH1D * Eff3_l= (TH1D*) hist_clone->Clone("Eff3_l");


    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_1,hist_c_1,hist_l_1,Eff1_b,Eff1_c,Eff1_l, 8) ;
    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_2,hist_c_2,hist_l_2,Eff2_b,Eff2_c,Eff2_l, kBlue) ;
    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_3,hist_c_3,hist_l_3,Eff3_b,Eff3_c,Eff3_l, 2) ;

    TString titleHisti;
    if (flag1==1) titleHisti="jet pT [GeV]";
    else if (flag1==2) titleHisti="jet eta ";
    else if (flag1==3) titleHisti="#PU";
    Eff1_b->GetXaxis()->SetTitle(titleHisti);
    Eff1_l->GetXaxis()->SetTitle(titleHisti);
    Eff1_c->GetXaxis()->SetTitle(titleHisti);


    Eff1_c->SetMaximum(0.6);        
    Eff1_l->SetMaximum(0.6);        
//    if (name=="deep") Eff1_l->SetMaximum(0.6);
    if (name=="ctag") Eff1_l->SetMaximum(1.1);
    if (name=="ctag") Eff1_c->SetMaximum(1.);
    if (name=="ctag") Eff1_b->SetMaximum(0.7);
    if (name=="ctag") Eff1_l->SetMinimum(0.005);


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    // CREATE CANVAS

/*
    Eff1_b->GetXaxis()->SetRangeUser(0,200);
    Eff1_c->GetXaxis()->SetRangeUser(0,200);
    Eff1_l->GetXaxis()->SetRangeUser(0,200);
*/

    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);


    c1->SetFillColor(10);
    c1->cd();
  c1->SetBorderMode(0);  
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
   c1_1->SetLeftMargin(0.1461539);
   c1_1->SetRightMargin(0.05384616);
   c1_1->SetTopMargin(0.06831119);
   c1_1->SetBottomMargin(0.1574953);
    c1_1->SetFrameBorderMode(0);
    c1_1->cd(); 
    c1_1->SetGridy();
    if (flag1==1) c1_1->SetLogx(1);


    TLegend* qw = 0;
//    qw = new TLegend(0.1884615,0.2144213,0.3602564,0.4079696,NULL,"brNDC"); 
    if (name=="ctag") qw = new TLegend(0.25,0.61,0.43,0.80,NULL,"brNDC"); 
    else qw = new TLegend(0.25,0.2144213,0.43,0.4079696,NULL,"brNDC"); 
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);

    TString nameTag;
    if (name=="csvv2") nameTag="CSVv2";
    else if (name=="cmvav2") nameTag="cMVAv2";
    else if (name=="deep") nameTag="DeepCSV";
    else if (name=="ctag") nameTag="c-tagger";
    else nameTag=name;
    qw->SetHeader(nameTag);

    qw->AddEntry(Eff1_b, "Loose", "p");
    qw->AddEntry(Eff2_b, "Medium", "p");
    qw->AddEntry(Eff3_b, "Tight", "p");

    Eff1_b->SetTitleSize(0.08,"Y");
    Eff1_b->SetTitleOffset(0.65,"Y");  
    Eff1_b->SetTitleOffset(0.81,"Y");
    Eff1_b->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_b->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_b->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_b->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_b->GetYaxis()->SetTitleOffset(0.9);
    Eff1_b->SetMarkerStyle(7);
    Eff2_b->SetMarkerStyle(7);
    Eff3_b->SetMarkerStyle(7);
    Eff1_b->SetMarkerSize(2);
    Eff2_b->SetMarkerSize(2);
    Eff3_b->SetMarkerSize(2);
    Eff1_b->Draw("L");
    if (flag1==1) Eff1_b->GetXaxis()->SetMoreLogLabels();
/*
    Eff1_b->GetXaxis()->SetRangeUser(0,200);
    Eff1_c->GetXaxis()->SetRangeUser(0,200);
    Eff1_l->GetXaxis()->SetRangeUser(0,200);
*/


    if (name=="cmvav2" && printfunc) {
/*
     TF1* rfun1_b = new TF1("rfun1_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,120.);
     rfun1_b->SetParameter(0, 0.390);
     rfun1_b->SetParameter(1, 0.0176);
     rfun1_b->SetParameter(2, -2.518e-04);
     rfun1_b->SetParameter(3, 1.598e-06 );
     rfun1_b->SetParameter(4, -3.786e-09) ;
     rfun1_b->SetLineColor(8);
     rfun1_b->Draw("same");
     TF1* rfun1_b2= new TF1("rfun1_b2","[0]+[1]*x+[2]*pow(x,2)",115.,1000.);
     rfun1_b2->SetParameter(0, 0.871);
     rfun1_b2->SetParameter(1, -1.68e-04);
     rfun1_b2->SetParameter(2, 3.65e-08);
     rfun1_b2->SetLineColor(8);
     rfun1_b2->Draw("same");
*/
    }
    else if (name=="csvv2" && printfunc) {
/*

     // Loose
     TF1* rfun1_b = new TF1("rfun1_b","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)",30.,165.);
     rfun1_b->SetParameter(0, 0.625);
     rfun1_b->SetParameter(1, 0.0063);
     rfun1_b->SetParameter(2, -7.45e-05);
     rfun1_b->SetParameter(3, 3.80e-07 );
     rfun1_b->SetParameter(4, -7.24e-10);
     rfun1_b->SetLineColor(8);
     rfun1_b->Draw("same");
     TF1* rfun1_b2= new TF1("rfun1_b2","[0]+[1]*x+[2]*pow(x,2)",165.,1000.);
     rfun1_b2->SetParameter(0, 0.845); 
     rfun1_b2->SetParameter(1, -2.27e-04);
     rfun1_b2->SetParameter(2,-2.13e-08);
     rfun1_b2->SetLineColor(8);
     rfun1_b2->Draw("same");
*/

    }


    Eff1_b->Draw("L same");
    Eff2_b->Draw("L same");
    Eff3_b->Draw("L same");


    TLatex *   tex1 = new TLatex(0.8782051,0.9506641,"#sqrt{s}=13 TeV, 2016");
    tex1->SetNDC();
    tex1->SetTextAlign(31);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.04875);
    tex1->SetLineWidth(2);
    tex1->Draw();
//    TLatex *  tex2 = new TLatex(0.5782051,0.9184061,"CMS Simulation");
    TLatex *  tex2 = new TLatex(0.1935897,0.9089184,"CMS Simulation");
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.065);
    tex2->SetLineWidth(2);
    tex2->Draw();


    qw->Draw();
    TString name_plot="effvs"+flagname+"_b_"+name+format;
    if (printfunc) name_plot="fit_"+name_plot;
    c1->SaveAs(name_plot);

    TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
    c2->cd();
  c2->SetBorderMode(0);  
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderMode(0);

    TPad *c2_1 = new TPad("canvas_2", "canvas_2",0,0,1.0,1.0);
    c2_1->SetFillColor(0);
    c2_1->SetBorderMode(0);
    c2_1->SetBorderSize(2);
   c2_1->SetLeftMargin(0.1461539);
   c2_1->SetRightMargin(0.05384616);
   c2_1->SetTopMargin(0.06831119);
   c2_1->SetBottomMargin(0.1574953);
    c2_1->SetFrameBorderMode(0);
    c2_1->Draw();
    c2_1->cd();
    c2_1->SetGridy();
    if (flag1==1) c2_1->SetLogx(1);

    TLegend* qw2 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    if (name=="ctag") qw2 = new TLegend(0.6666667,0.7343454-0.2,0.8666667,0.9032258-0.2,NULL,"brNDC");
    else qw2 = new TLegend(0.6666667,0.7343454-0.3,0.8666667,0.9032258-0.3,NULL,"brNDC");
    qw2->SetHeader(nameTag);
    qw2->AddEntry(Eff1_b, "Loose", "p");
    qw2->AddEntry(Eff2_b, "Medium", "p");
    qw2->AddEntry(Eff3_b, "Tight", "p");
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
    Eff1_c->SetTitleSize(0.08,"Y");
    Eff1_c->SetTitleOffset(0.65,"Y");  
    Eff1_c->SetTitleOffset(0.81,"Y");
    Eff1_c->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_c->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_c->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_c->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_c->GetYaxis()->SetTitleOffset(0.9);

    Eff1_c->SetMarkerStyle(7);
    Eff2_c->SetMarkerStyle(7);
    Eff3_c->SetMarkerStyle(7);
    Eff1_c->SetMarkerSize(2);
    Eff2_c->SetMarkerSize(2);
    Eff3_c->SetMarkerSize(2);
    Eff1_c->Draw("L");
    if (flag1==1) Eff1_c->GetXaxis()->SetMoreLogLabels();
    Eff1_c->Draw("L same");
    Eff2_c->Draw("L same");
    Eff3_c->Draw("L same");
    qw2->Draw();
    tex1->Draw();
    tex2->Draw();
    TString name_plot2="effvs"+flagname+"_c_"+name+format;
    if (printfunc) name_plot2="fit_"+name_plot2;
    c2->SaveAs(name_plot2);

  
    TCanvas *c3 = new TCanvas("c3", "c3",10,32,782,552);
    c3->cd();
  c3->SetBorderMode(0);  
  c3->SetBorderSize(2);
  c3->SetFrameFillColor(0);
  c3->SetFrameBorderMode(0);
    TPad *c3_1 = new TPad("canvas_3", "canvas_3",0,0,1.0,1.0);
    c3_1->SetFillColor(0);
    c3_1->SetBorderMode(0);
    c3_1->SetBorderSize(2);
   c3_1->SetLeftMargin(0.1461539);
   c3_1->SetRightMargin(0.05384616);
   c3_1->SetTopMargin(0.06831119);
   c3_1->SetBottomMargin(0.1574953);
    c3_1->SetFrameBorderMode(0);
    c3_1->Draw();
    c3_1->cd();
    c3_1->SetGridy();
    c3_1->SetLogy(1);
    if (flag1==1) c3_1->SetLogx(1);

    TLegend* qw3 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    if (name=="ctag") qw3 = new TLegend(0.6666667,0.7343454-0.3,0.8666667,0.9032258-0.3,NULL,"brNDC");
    else qw3 = new TLegend(0.6666667,0.7343454-0.52,0.8666667,0.9032258-0.52,NULL,"brNDC");
    qw3->SetHeader(nameTag);
    qw3->AddEntry(Eff1_b, "Loose", "p");
    qw3->AddEntry(Eff2_b, "Medium", "p");
    qw3->AddEntry(Eff3_b, "Tight", "p");
  qw3->SetBorderSize(1);
  qw3->SetTextFont(62);
  qw3->SetLineColor(1);
  qw3->SetLineStyle(1);
  qw3->SetLineWidth(1);
  qw3->SetFillColor(0);
  qw3->SetFillStyle(1001);
    Eff1_l->SetTitleSize(0.08,"Y");
    Eff1_l->SetTitleOffset(0.65,"Y");  
    Eff1_l->SetTitleOffset(0.81,"Y");
    Eff1_l->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_l->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_l->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_l->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_l->GetYaxis()->SetTitleOffset(0.9);
    Eff1_l->SetMarkerStyle(7);
    Eff2_l->SetMarkerStyle(7);
    Eff3_l->SetMarkerStyle(7);
    Eff1_l->SetMarkerSize(2);
    Eff2_l->SetMarkerSize(2);
    Eff3_l->SetMarkerSize(2);
    Eff1_l->Draw("L");
    if (flag1==1) Eff1_l->GetXaxis()->SetMoreLogLabels();
    Eff1_l->Draw("L same");
    Eff2_l->Draw("L same");
    Eff3_l->Draw("L same");
    qw3->Draw(); 
    tex1->Draw();
    tex2->Draw();
    TString name_plot3="effvs"+flagname+"_l_"+name+format;
    if (printfunc) name_plot3="fit_"+name_plot3;
    c3->SaveAs(name_plot3);
    


}

void ComputeEffvsPT(TH1D* hist_b_r1, TH1D* hist_c_r1, TH1D* hist_l_r1, TH1D* hist_b_1, TH1D* hist_c_1, TH1D* hist_l_1, TH1D* Eff1_b, TH1D* Eff1_c, TH1D* Eff1_l, int icol) {

    // equivalent numbers (= number without weights with the same statistical error than weighted events)
    int nbin_max_1= hist_b_1->GetNbinsX();

    for (int ii=1; ii<nbin_max_1+1; ii++) {
          double val_b=0., val_c=0., val_l=0.;
          double error_b=0., error_c=0., error_l=0.;
          double neq_b=0;
          double neq_c=0;
          double neq_l=0;

          if (hist_b_r1->GetBinError(ii)>0)  neq_b= (hist_b_r1->GetBinContent(ii)*hist_b_r1->GetBinContent(ii)) / (hist_b_r1->GetBinError(ii)*hist_b_r1->GetBinError(ii));
          if (hist_c_r1->GetBinError(ii)>0)  neq_c= (hist_c_r1->GetBinContent(ii)*hist_c_r1->GetBinContent(ii)) / (hist_c_r1->GetBinError(ii)*hist_c_r1->GetBinError(ii));
          if (hist_l_r1->GetBinError(ii)>0)  neq_l= (hist_l_r1->GetBinContent(ii)*hist_l_r1->GetBinContent(ii)) / (hist_l_r1->GetBinError(ii)*hist_l_r1->GetBinError(ii));

          if (hist_b_r1->GetBinContent(ii)>0) val_b = (hist_b_1->GetBinContent(ii))/hist_b_r1->GetBinContent(ii);
          if (neq_b > 0.) error_b = sqrt(neq_b *val_b*(1.-val_b)) / neq_b;
          if (hist_c_r1->GetBinContent(ii)>0) val_c = (hist_c_1->GetBinContent(ii))/hist_c_r1->GetBinContent(ii);
          if (neq_c > 0.) error_c = sqrt(neq_c *val_c*(1.-val_c)) / neq_c;
          if (hist_l_r1->GetBinContent(ii)>0) val_l = (hist_l_1->GetBinContent(ii))/hist_l_r1->GetBinContent(ii);
          if (neq_l > 0.) error_l = sqrt(neq_l *val_l*(1.-val_l)) / neq_l;

          Eff1_b->SetBinContent(ii, val_b);
          Eff1_b->SetBinError(ii,   error_b);
          Eff1_c->SetBinContent(ii, val_c);
          Eff1_c->SetBinError(ii,   error_c);
          Eff1_l->SetBinContent(ii, val_l);
          Eff1_l->SetBinError(ii,   error_l);
    }


    Eff1_b->SetLineColor(icol);
    Eff1_c->SetLineColor(icol);
    Eff1_l->SetLineColor(icol);
    Eff1_b->SetMarkerColor(icol);
    Eff1_c->SetMarkerColor(icol);
    Eff1_l->SetMarkerColor(icol);
    Eff1_b->SetMarkerSize(1.5);
    Eff1_c->SetMarkerSize(1.5);
    Eff1_l->SetMarkerSize(1.5);

/*
    Eff1_b->GetXaxis()->SetTitle("jet pT [GeV]");  
    Eff1_l->GetXaxis()->SetTitle("jet pT [GeV]");  
    Eff1_c->GetXaxis()->SetTitle("jet pT [GeV]");  
*/
    Eff1_b->GetYaxis()->SetTitle("b-jet efficiency");  
    Eff1_l->GetYaxis()->SetTitle("udsg-jet misid. probability");
    Eff1_c->GetYaxis()->SetTitle("c-jet misid. probability");

    Eff1_b->SetMaximum(1.);        
    Eff1_c->SetMaximum(1.);        
    Eff1_l->SetMaximum(1.);        
    Eff1_b->SetMinimum(0.);        
    Eff1_c->SetMinimum(0.);        
    Eff1_l->SetMinimum(0.0001);        
/*
    Eff1_b->SetMaximum(1.);        
    Eff1_c->SetMaximum(0.8);        
    Eff1_l->SetMaximum(0.5);        
*/
    
}

void CompareEff(TString name, int wpflag, int flag1){

    // File1
    TH1D* hist_b_r1;
    TH1D* hist_c_r1;
    TH1D* hist_l_r1;
    TH1D* hist_g_r1;
    TH1D* hist_gc_r1;
    TH1D* hist_gb_r1;

    TH1D* hist_b_1;
    TH1D* hist_c_1;
    TH1D* hist_l_1;
    TH1D* hist_g_1;
    TH1D* hist_gc_1;
    TH1D* hist_gb_1;

    // File2
    TH1D* hist_b_r2;
    TH1D* hist_c_r2;
    TH1D* hist_l_r2;
    TH1D* hist_g_r2;
    TH1D* hist_gc_r2;
    TH1D* hist_gb_r2;
    TH1D* hist_b_2;
    TH1D* hist_c_2;
    TH1D* hist_l_2;
    TH1D* hist_g_2;
    TH1D* hist_gc_2;
    TH1D* hist_gb_2;

    // File3
    TH1D* hist_b_r3;
    TH1D* hist_c_r3;
    TH1D* hist_l_r3;
    TH1D* hist_g_r3;
    TH1D* hist_gc_r3;
    TH1D* hist_gb_r3;
    TH1D* hist_b_3;
    TH1D* hist_c_3;
    TH1D* hist_l_3;
    TH1D* hist_g_3;
    TH1D* hist_gc_3;
    TH1D* hist_gb_3;

    TFile *myFile_1     = new TFile(filename_1);
    myFile_1->cd();

    TString flagname;
    if (flag1==1) flagname="pt";
    else if (flag1==2) flagname="eta";
    else if (flag1==3) flagname="pu";
    else if (flag1==4) flagname="hadpt";
    else if (flag1==5) flagname="ptlead";
    else if (flag1==6) flagname="etalead";
    else if (flag1==7) flagname="hadptlead";

    hist_b_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    cout << "1- 'ok ? " << endl;
    hist_l_r1->Add(hist_g_r1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r1->Add(hist_gb_r1);
        hist_c_r1->Add(hist_gc_r1);
    }

    TString wpname;
    if (wpflag==0) wpname="l";
    else if (wpflag==1) wpname="m";
    else if (wpflag==2) wpname="t";
    hist_b_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    cout << "2- 'ok ? " << endl;
    hist_l_1->Add(hist_g_1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_1->Add(hist_gb_1);
        hist_c_1->Add(hist_gc_1);
    }

    cout << "2.1- 'ok ? " << endl;
    TFile *myFile_2     = new TFile(filename_2);
    myFile_2->cd();
    cout << "2.5- 'ok ? " << endl;

    hist_b_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    cout << "2.6- 'ok ? " << endl;
    hist_c_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_b_r3         = (TH1D*) hist_b_r2->Clone();
    hist_c_r3         = (TH1D*) hist_c_r2->Clone();
    hist_l_r3         = (TH1D*) hist_l_r2->Clone();
    hist_g_r3         = (TH1D*) hist_g_r2->Clone();
    hist_gb_r3         = (TH1D*) hist_gb_r2->Clone();
    hist_gc_r3         = (TH1D*) hist_gc_r2->Clone();


    cout << "3- 'ok ? " << endl;
    hist_l_r2->Add(hist_g_r2);
    hist_l_r3->Add(hist_g_r3);

    // r2 with gluon splitting
    hist_b_r2->Add(hist_gb_r2);
    hist_c_r2->Add(hist_gc_r2);
    // r3 without    


    hist_b_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_b_3         = (TH1D*) hist_b_2->Clone();
    hist_c_3         = (TH1D*) hist_c_2->Clone();
    hist_l_3         = (TH1D*) hist_l_2->Clone();
    hist_g_3         = (TH1D*) hist_g_2->Clone();
    hist_gb_3         = (TH1D*) hist_gb_2->Clone();
    hist_gc_3         = (TH1D*) hist_gc_2->Clone();

    hist_l_2->Add(hist_g_2);
    hist_l_3->Add(hist_g_3);
    hist_b_2->Add(hist_gb_2);
    hist_c_2->Add(hist_gc_2);

    cout << "4- 'ok ? " << endl;

    int nbin_max_1= hist_b_1->GetNbinsX();
    float minx=hist_b_1->GetXaxis()->GetXmin();
    float maxx=hist_b_1->GetXaxis()->GetXmax();
    cout << "nbin_max_1 "<< nbin_max_1 << "   " << minx << "  " << maxx << endl;

     TH1D * hist_clone = (TH1D*)hist_b_1->Clone("hist_clone");
     for (int i=0; i<hist_clone->GetNbinsX()+1; i++) {
        hist_clone->SetBinContent(i,0);
        hist_clone->SetBinError(i,0);
     }
     TH1D * Eff1_b= (TH1D*) hist_clone->Clone("Eff1_b");
     TH1D * Eff1_c= (TH1D*) hist_clone->Clone("Eff1_c");
     TH1D * Eff1_l= (TH1D*) hist_clone->Clone("Eff1_l");
     TH1D * Eff2_b= (TH1D*) hist_clone->Clone("Eff2_b");
     TH1D * Eff2_c= (TH1D*) hist_clone->Clone("Eff2_c");
     TH1D * Eff2_l= (TH1D*) hist_clone->Clone("Eff2_l");
     TH1D * Eff3_b= (TH1D*) hist_clone->Clone("Eff3_b");
     TH1D * Eff3_c= (TH1D*) hist_clone->Clone("Eff3_c");
     TH1D * Eff3_l= (TH1D*) hist_clone->Clone("Eff3_l");


    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_1,hist_c_1,hist_l_1,Eff1_b,Eff1_c,Eff1_l, 8) ;
    ComputeEffvsPT(hist_b_r2,hist_c_r2,hist_l_r2,hist_b_2,hist_c_2,hist_l_2,Eff2_b,Eff2_c,Eff2_l, kBlue) ;
    ComputeEffvsPT(hist_b_r3,hist_c_r3,hist_l_r3,hist_b_3,hist_c_3,hist_l_3,Eff3_b,Eff3_c,Eff3_l, 2) ;
 
    cout << "5- 'ok ? " << endl;

    TString titleHisti;
    if (flag1==1) titleHisti="jet pT [GeV]";
    else if (flag1==2) titleHisti="jet eta ";
    else if (flag1==3) titleHisti="#PU";
    else if (flag1==4) titleHisti="hadron pT [GeV]";
    else if (flag1==5) titleHisti="leading jet pT [GeV]";
    else if (flag1==6) titleHisti="leading jet eta [GeV]";
    else if (flag1==7) titleHisti="hadron pT of leading jet [GeV]";
    Eff1_b->GetXaxis()->SetTitle(titleHisti);
    Eff1_l->GetXaxis()->SetTitle(titleHisti);
    Eff1_c->GetXaxis()->SetTitle(titleHisti);


    Eff1_c->SetMaximum(0.6);        
    Eff1_l->SetMaximum(0.35);        
    if (name=="deep") Eff1_l->SetMaximum(0.6);
    if (name=="ctag") Eff1_l->SetMaximum(1.1);
    if (name=="ctag") Eff1_c->SetMaximum(1.);
    if (name=="ctag") Eff1_b->SetMaximum(0.7);
    if (name=="ctag") Eff1_l->SetMinimum(0.005);


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);


    c1->SetFillColor(10);
    c1->cd();
    c1->SetBorderMode(0);  
    c1->SetBorderSize(2);
    c1->SetFrameFillColor(0);
    c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetLeftMargin(0.1461539);
    c1_1->SetRightMargin(0.05384616);
    c1_1->SetTopMargin(0.06831119);
    c1_1->SetBottomMargin(0.1574953);
    c1_1->SetFrameBorderMode(0);
    c1_1->cd(); 
    c1_1->SetGridy();


    TLegend* qw = 0;
//    qw = new TLegend(0.13,0.22,0.33,0.39,NULL,"brNDC"); // Caro
    qw = new TLegend(0.1884615,0.2144213,0.3602564,0.4079696,NULL,"brNDC"); 
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);

    qw->AddEntry(Eff1_b, "ttbar", "p");
    if (flag1!=4 && flag1!=7) qw->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw->AddEntry(Eff3_b, "QCD without gsplit", "p");

    Eff1_b->SetTitleSize(0.08,"Y");
    Eff1_b->SetTitleOffset(0.65,"Y");  
    Eff1_b->SetTitleOffset(0.81,"Y");
    Eff1_b->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_b->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_b->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_b->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_b->GetYaxis()->SetTitleOffset(0.9);
    Eff1_b->SetMarkerStyle(7);
    Eff2_b->SetMarkerStyle(7);
    Eff3_b->SetMarkerStyle(7);
    Eff1_b->SetMarkerSize(2);
    Eff2_b->SetMarkerSize(2);
    Eff3_b->SetMarkerSize(2);
    Eff1_b->Draw();

    Eff1_b->Draw("same");
    if (flag1!=4 && flag1!=7) Eff2_b->Draw("same");
    Eff3_b->Draw("same");


    TLatex *   tex1 = new TLatex(0.8782051,0.9506641,"#sqrt{s}=13 TeV, 2016");
    tex1->SetNDC();
    tex1->SetTextAlign(31);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.04875);
    tex1->SetLineWidth(2);
    tex1->Draw();
//    TLatex *  tex2 = new TLatex(0.5782051,0.9184061,"CMS Simulation");
    TLatex *  tex2 = new TLatex(0.1935897,0.9089184,"CMS Simulation");
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.065);
    tex2->SetLineWidth(2);
    tex2->Draw();


    qw->Draw();
    TString name_plot="compare_vs_"+flagname+"_b_"+name+wpname+format;
    if (printfunc) name_plot="fit_"+name_plot;
    c1->SaveAs(name_plot);

    TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
    c2->cd();
  c2->SetBorderMode(0);  
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderMode(0);

    TPad *c2_1 = new TPad("canvas_2", "canvas_2",0,0,1.0,1.0);
    c2_1->SetFillColor(0);
    c2_1->SetBorderMode(0);
    c2_1->SetBorderSize(2);
   c2_1->SetLeftMargin(0.1461539);
   c2_1->SetRightMargin(0.05384616);
   c2_1->SetTopMargin(0.06831119);
   c2_1->SetBottomMargin(0.1574953);
    c2_1->SetFrameBorderMode(0);
    c2_1->Draw();
    c2_1->cd();
    c2_1->SetGridy();

    TLegend* qw2 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw2 = new TLegend(0.6666667,0.7343454-0.3,0.8666667,0.9032258-0.3,NULL,"brNDC");
    qw2->AddEntry(Eff1_b, "ttbar", "p");
    if (flag1!=4 && flag1!=7) qw2->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw2->AddEntry(Eff3_b, "QCD without gsplit", "p");
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
    Eff1_c->SetTitleSize(0.08,"Y");
    Eff1_c->SetTitleOffset(0.65,"Y");  
    Eff1_c->SetTitleOffset(0.81,"Y");
    Eff1_c->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_c->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_c->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_c->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_c->GetYaxis()->SetTitleOffset(0.9);

    Eff1_c->SetMarkerStyle(7);
    Eff2_c->SetMarkerStyle(7);
    Eff3_c->SetMarkerStyle(7);
    Eff1_c->SetMarkerSize(2);
    Eff2_c->SetMarkerSize(2);
    Eff3_c->SetMarkerSize(2);
    Eff1_c->Draw("L");
    Eff1_c->Draw("L same");
    if (flag1!=4 && flag1!=7) Eff2_c->Draw("L same");
    Eff3_c->Draw("L same");
    qw2->Draw();
    tex1->Draw();
    tex2->Draw();
    TString name_plot2="compare_vs_"+flagname+"_c_"+name+wpname+format;
    if (printfunc) name_plot2="fit_"+name_plot2;
    c2->SaveAs(name_plot2);

  
    TCanvas *c3 = new TCanvas("c3", "c3",10,32,782,552);
    c3->cd();
  c3->SetBorderMode(0);  
  c3->SetBorderSize(2);
  c3->SetFrameFillColor(0);
  c3->SetFrameBorderMode(0);
    TPad *c3_1 = new TPad("canvas_3", "canvas_3",0,0,1.0,1.0);
    c3_1->SetFillColor(0);
    c3_1->SetBorderMode(0);
    c3_1->SetBorderSize(2);
   c3_1->SetLeftMargin(0.1461539);
   c3_1->SetRightMargin(0.05384616);
   c3_1->SetTopMargin(0.06831119);
   c3_1->SetBottomMargin(0.1574953);
    c3_1->SetFrameBorderMode(0);
    c3_1->Draw();
    c3_1->cd();
    c3_1->SetGridy();
    c3_1->SetLogy(1);

    TLegend* qw3 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw3 = new TLegend(0.6666667,0.7343454-0.5,0.8666667,0.9032258-0.5,NULL,"brNDC");
    qw3->AddEntry(Eff1_b, "ttbar", "p");
//    qw3->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw3->AddEntry(Eff3_b, "QCD", "p");
  qw3->SetBorderSize(1);
  qw3->SetTextFont(62);
  qw3->SetLineColor(1);
  qw3->SetLineStyle(1);
  qw3->SetLineWidth(1);
  qw3->SetFillColor(0);
  qw3->SetFillStyle(1001);
    Eff1_l->SetTitleSize(0.08,"Y");
    Eff1_l->SetTitleOffset(0.65,"Y");  
    Eff1_l->SetTitleOffset(0.81,"Y");
    Eff1_l->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_l->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_l->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_l->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_l->GetYaxis()->SetTitleOffset(0.9);
    Eff1_l->SetMarkerStyle(7);
    Eff2_l->SetMarkerStyle(7);
    Eff3_l->SetMarkerStyle(7);
    Eff1_l->SetMarkerSize(2);
    Eff2_l->SetMarkerSize(2);
    Eff3_l->SetMarkerSize(2);
    Eff1_l->Draw("L");
    Eff1_l->Draw("same");
//    Eff2_l->Draw("L same");
    Eff3_l->Draw("L same");
    qw3->Draw(); 
    tex1->Draw();
    tex2->Draw();
    TString name_plot3="compare_vs_"+flagname+"_l_"+name+wpname+format;
    if (printfunc) name_plot3="fit_"+name_plot3;
    c3->SaveAs(name_plot3);
    


}
void CompareEff2(TString name, int wpflag, int flag1){

    // File1
    TH1D* hist_b_r1;
    TH1D* hist_c_r1;
    TH1D* hist_l_r1;
    TH1D* hist_g_r1;
    TH1D* hist_gc_r1;
    TH1D* hist_gb_r1;

    TH1D* hist_b_1;
    TH1D* hist_c_1;
    TH1D* hist_l_1;
    TH1D* hist_g_1;
    TH1D* hist_gc_1;
    TH1D* hist_gb_1;

    // File2
    TH1D* hist_b_r2;
    TH1D* hist_c_r2;
    TH1D* hist_l_r2;
    TH1D* hist_g_r2;
    TH1D* hist_gc_r2;
    TH1D* hist_gb_r2;
    TH1D* hist_b_2;
    TH1D* hist_c_2;
    TH1D* hist_l_2;
    TH1D* hist_g_2;
    TH1D* hist_gc_2;
    TH1D* hist_gb_2;

    // File3
    TH1D* hist_b_r3;
    TH1D* hist_c_r3;
    TH1D* hist_l_r3;
    TH1D* hist_g_r3;
    TH1D* hist_gc_r3;
    TH1D* hist_gb_r3;
    TH1D* hist_b_3;
    TH1D* hist_c_3;
    TH1D* hist_l_3;
    TH1D* hist_g_3;
    TH1D* hist_gc_3;
    TH1D* hist_gb_3;

    // File3
    TH1D* hist_b_r4;
    TH1D* hist_c_r4;
    TH1D* hist_l_r4;
    TH1D* hist_g_r4;
    TH1D* hist_gc_r4;
    TH1D* hist_gb_r4;
    TH1D* hist_b_4;
    TH1D* hist_c_4;
    TH1D* hist_l_4;
    TH1D* hist_g_4;
    TH1D* hist_gc_4;
    TH1D* hist_gb_4;


    TFile *myFile_1     = new TFile(filename_1);
    myFile_1->cd();

    TString flagname;
    if (flag1==1) flagname="pt";
    else if (flag1==2) flagname="eta";
    else if (flag1==3) flagname="pu";
    else if (flag1==4) flagname="hadpt";
    else if (flag1==5) flagname="ptlead";
    else if (flag1==6) flagname="etalead";
    else if (flag1==7) flagname="hadptlead";

    hist_b_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    cout << "1- 'ok ? " << endl;
    hist_l_r1->Add(hist_g_r1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r1->Add(hist_gb_r1);
        hist_c_r1->Add(hist_gc_r1);
    }

    TString wpname;
    if (wpflag==0) wpname="l";
    else if (wpflag==1) wpname="m";
    else if (wpflag==2) wpname="t";
    hist_b_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    cout << "2- 'ok ? " << endl;
    hist_l_1->Add(hist_g_1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_1->Add(hist_gb_1);
        hist_c_1->Add(hist_gc_1);
    }

    cout << "2.1- 'ok ? " << endl;
    TFile *myFile_2     = new TFile(filename_2);
    myFile_2->cd();
    cout << "2.5- 'ok ? " << endl;

    hist_b_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    cout << "2.6- 'ok ? " << endl;
    hist_c_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_b_r3         = (TH1D*) hist_b_r2->Clone();
    hist_c_r3         = (TH1D*) hist_c_r2->Clone();
    hist_l_r3         = (TH1D*) hist_l_r2->Clone();
    hist_g_r3         = (TH1D*) hist_g_r2->Clone();
    hist_gb_r3         = (TH1D*) hist_gb_r2->Clone();
    hist_gc_r3         = (TH1D*) hist_gc_r2->Clone();


    cout << "3- 'ok ? " << endl;
    hist_l_r2->Add(hist_g_r2);
    hist_l_r3->Add(hist_g_r3);

    // r2 with gluon splitting
    hist_b_r2->Add(hist_gb_r2);
    hist_c_r2->Add(hist_gc_r2);
    // r3 without    


    hist_b_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_b_3         = (TH1D*) hist_b_2->Clone();
    hist_c_3         = (TH1D*) hist_c_2->Clone();
    hist_l_3         = (TH1D*) hist_l_2->Clone();
    hist_g_3         = (TH1D*) hist_g_2->Clone();
    hist_gb_3         = (TH1D*) hist_gb_2->Clone();
    hist_gc_3         = (TH1D*) hist_gc_2->Clone();

    hist_l_2->Add(hist_g_2);
    hist_l_3->Add(hist_g_3);
    hist_b_2->Add(hist_gb_2);
    hist_c_2->Add(hist_gc_2);

    cout << "4- 'ok ? " << endl;

    TFile *myFile_3     = new TFile(filename_3);
    myFile_3->cd();

    hist_b_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_l_r4->Add(hist_g_r4);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r4->Add(hist_gb_r4);
        hist_c_r4->Add(hist_gc_r4);
    }

    hist_b_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_l_4->Add(hist_g_4);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_4->Add(hist_gb_4);
        hist_c_4->Add(hist_gc_4);
    }

    int nbin_max_1= hist_b_1->GetNbinsX();
    float minx=hist_b_1->GetXaxis()->GetXmin();
    float maxx=hist_b_1->GetXaxis()->GetXmax();
    cout << "nbin_max_1 "<< nbin_max_1 << "   " << minx << "  " << maxx << endl;

     TH1D * hist_clone = (TH1D*)hist_b_1->Clone("hist_clone");
     for (int i=0; i<hist_clone->GetNbinsX()+1; i++) {
        hist_clone->SetBinContent(i,0);
        hist_clone->SetBinError(i,0);
     }
     TH1D * Eff1_b= (TH1D*) hist_clone->Clone("Eff1_b");
     TH1D * Eff1_c= (TH1D*) hist_clone->Clone("Eff1_c");
     TH1D * Eff1_l= (TH1D*) hist_clone->Clone("Eff1_l");
     TH1D * Eff2_b= (TH1D*) hist_clone->Clone("Eff2_b");
     TH1D * Eff2_c= (TH1D*) hist_clone->Clone("Eff2_c");
     TH1D * Eff2_l= (TH1D*) hist_clone->Clone("Eff2_l");
     TH1D * Eff3_b= (TH1D*) hist_clone->Clone("Eff3_b");
     TH1D * Eff3_c= (TH1D*) hist_clone->Clone("Eff3_c");
     TH1D * Eff3_l= (TH1D*) hist_clone->Clone("Eff3_l");
     TH1D * Eff4_b= (TH1D*) hist_clone->Clone("Eff4_b");
     TH1D * Eff4_c= (TH1D*) hist_clone->Clone("Eff4_c");
     TH1D * Eff4_l= (TH1D*) hist_clone->Clone("Eff4_l");


    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_1,hist_c_1,hist_l_1,Eff1_b,Eff1_c,Eff1_l, 8) ;
    ComputeEffvsPT(hist_b_r2,hist_c_r2,hist_l_r2,hist_b_2,hist_c_2,hist_l_2,Eff2_b,Eff2_c,Eff2_l, kBlue) ;
    ComputeEffvsPT(hist_b_r3,hist_c_r3,hist_l_r3,hist_b_3,hist_c_3,hist_l_3,Eff3_b,Eff3_c,Eff3_l, 2) ;
    ComputeEffvsPT(hist_b_r4,hist_c_r4,hist_l_r4,hist_b_4,hist_c_4,hist_l_4,Eff4_b,Eff4_c,Eff4_l, kViolet) ;
 
    cout << "5- 'ok ? " << endl;

    TString titleHisti;
    if (flag1==1) titleHisti="jet pT [GeV]";
    else if (flag1==2) titleHisti="jet eta ";
    else if (flag1==3) titleHisti="#PU";
    else if (flag1==4) titleHisti="hadron pT [GeV]";
    else if (flag1==5) titleHisti="leading jet pT [GeV]";
    else if (flag1==6) titleHisti="leading jet eta [GeV]";
    else if (flag1==7) titleHisti="hadron pT of leading jet [GeV]";
    Eff1_b->GetXaxis()->SetTitle(titleHisti);
    Eff1_l->GetXaxis()->SetTitle(titleHisti);
    Eff1_c->GetXaxis()->SetTitle(titleHisti);


    Eff1_c->SetMaximum(0.6);        
    Eff1_l->SetMaximum(0.35);        
    if (name=="deep") Eff1_l->SetMaximum(0.6);
    if (name=="ctag") Eff1_l->SetMaximum(1.1);
    if (name=="ctag") Eff1_c->SetMaximum(1.);
    if (name=="ctag") Eff1_b->SetMaximum(0.7);
    if (name=="ctag") Eff1_l->SetMinimum(0.005);


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);


    c1->SetFillColor(10);
    c1->cd();
    c1->SetBorderMode(0);  
    c1->SetBorderSize(2);
    c1->SetFrameFillColor(0);
    c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetLeftMargin(0.1461539);
    c1_1->SetRightMargin(0.05384616);
    c1_1->SetTopMargin(0.06831119);
    c1_1->SetBottomMargin(0.1574953);
    c1_1->SetFrameBorderMode(0);
    c1_1->cd(); 
    c1_1->SetGridy();


    TLegend* qw = 0;
//    qw = new TLegend(0.13,0.22,0.33,0.39,NULL,"brNDC"); // Caro
    qw = new TLegend(0.1884615,0.2144213,0.3602564,0.4079696,NULL,"brNDC"); 
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);

    qw->AddEntry(Eff1_b, "ttbar powheg", "p");
    qw->AddEntry(Eff4_b, "ttbar herwig", "p");
    if (flag1!=4 && flag1!=7) qw->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw->AddEntry(Eff3_b, "QCD without gsplit", "p");

    Eff1_b->SetTitleSize(0.08,"Y");
    Eff1_b->SetTitleOffset(0.65,"Y");  
    Eff1_b->SetTitleOffset(0.81,"Y");
    Eff1_b->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_b->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_b->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_b->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_b->GetYaxis()->SetTitleOffset(0.9);
    Eff1_b->SetMarkerStyle(7);
    Eff2_b->SetMarkerStyle(7);
    Eff3_b->SetMarkerStyle(7);
    Eff4_b->SetMarkerStyle(7);
    Eff1_b->SetMarkerSize(2);
    Eff2_b->SetMarkerSize(2);
    Eff3_b->SetMarkerSize(2);
    Eff4_b->SetMarkerSize(2);
    Eff1_b->Draw();

    Eff1_b->Draw("same");
    if (flag1!=4 && flag1!=7) Eff2_b->Draw("same");
    Eff3_b->Draw("same");
    Eff4_b->Draw("same");



    TLatex *   tex1 = new TLatex(0.8782051,0.9506641,"#sqrt{s}=13 TeV, 2016");
    tex1->SetNDC();
    tex1->SetTextAlign(31);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.04875);
    tex1->SetLineWidth(2);
    tex1->Draw();
//    TLatex *  tex2 = new TLatex(0.5782051,0.9184061,"CMS Simulation");
    TLatex *  tex2 = new TLatex(0.1935897,0.9089184,"CMS Simulation");
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.065);
    tex2->SetLineWidth(2);
    tex2->Draw();


    qw->Draw();
    TString name_plot="compare2_vs_"+flagname+"_b_"+name+wpname+format;
    if (printfunc) name_plot="fit_"+name_plot;
    c1->SaveAs(name_plot);

    TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
    c2->cd();
  c2->SetBorderMode(0);  
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderMode(0);

    TPad *c2_1 = new TPad("canvas_2", "canvas_2",0,0,1.0,1.0);
    c2_1->SetFillColor(0);
    c2_1->SetBorderMode(0);
    c2_1->SetBorderSize(2);
   c2_1->SetLeftMargin(0.1461539);
   c2_1->SetRightMargin(0.05384616);
   c2_1->SetTopMargin(0.06831119);
   c2_1->SetBottomMargin(0.1574953);
    c2_1->SetFrameBorderMode(0);
    c2_1->Draw();
    c2_1->cd();
    c2_1->SetGridy();

    TLegend* qw2 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw2 = new TLegend(0.6666667,0.7343454-0.3,0.8666667,0.9032258-0.3,NULL,"brNDC");
    qw2->AddEntry(Eff1_b, "ttbar powheg", "p");
    qw2->AddEntry(Eff4_b, "ttbar herwig", "p");
    if (flag1!=4 && flag1!=7) qw2->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw2->AddEntry(Eff3_b, "QCD without gsplit", "p");
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
    Eff1_c->SetTitleSize(0.08,"Y");
    Eff1_c->SetTitleOffset(0.65,"Y");  
    Eff1_c->SetTitleOffset(0.81,"Y");
    Eff1_c->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_c->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_c->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_c->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_c->GetYaxis()->SetTitleOffset(0.9);

    Eff1_c->SetMarkerStyle(7);
    Eff2_c->SetMarkerStyle(7);
    Eff3_c->SetMarkerStyle(7);
    Eff4_c->SetMarkerStyle(7);
    Eff1_c->SetMarkerSize(2);
    Eff2_c->SetMarkerSize(2);
    Eff3_c->SetMarkerSize(2);
    Eff4_c->SetMarkerSize(2);
    Eff1_c->Draw("L");
    Eff1_c->Draw("L same");
    if (flag1!=4 && flag1!=7) Eff2_c->Draw("L same");
    Eff3_c->Draw("L same");
    Eff4_c->Draw("L same");
    qw2->Draw();
    tex1->Draw();
    tex2->Draw();
    TString name_plot2="compare2_vs_"+flagname+"_c_"+name+wpname+format;
    if (printfunc) name_plot2="fit_"+name_plot2;
    c2->SaveAs(name_plot2);

  
    TCanvas *c3 = new TCanvas("c3", "c3",10,32,782,552);
    c3->cd();
  c3->SetBorderMode(0);  
  c3->SetBorderSize(2);
  c3->SetFrameFillColor(0);
  c3->SetFrameBorderMode(0);
    TPad *c3_1 = new TPad("canvas_3", "canvas_3",0,0,1.0,1.0);
    c3_1->SetFillColor(0);
    c3_1->SetBorderMode(0);
    c3_1->SetBorderSize(2);
   c3_1->SetLeftMargin(0.1461539);
   c3_1->SetRightMargin(0.05384616);
   c3_1->SetTopMargin(0.06831119);
   c3_1->SetBottomMargin(0.1574953);
    c3_1->SetFrameBorderMode(0);
    c3_1->Draw();
    c3_1->cd();
    c3_1->SetGridy();
    c3_1->SetLogy(1);

    TLegend* qw3 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw3 = new TLegend(0.6666667,0.7343454-0.5,0.8666667,0.9032258-0.5,NULL,"brNDC");
    qw3->AddEntry(Eff1_b, "ttbar powheg", "p");
    qw3->AddEntry(Eff4_b, "ttbar herwig", "p");
//    qw3->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw3->AddEntry(Eff3_b, "QCD", "p");
  qw3->SetBorderSize(1);
  qw3->SetTextFont(62);
  qw3->SetLineColor(1);
  qw3->SetLineStyle(1);
  qw3->SetLineWidth(1);
  qw3->SetFillColor(0);
  qw3->SetFillStyle(1001);
    Eff1_l->SetTitleSize(0.08,"Y");
    Eff1_l->SetTitleOffset(0.65,"Y");  
    Eff1_l->SetTitleOffset(0.81,"Y");
    Eff1_l->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_l->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_l->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_l->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_l->GetYaxis()->SetTitleOffset(0.9);
    Eff1_l->SetMarkerStyle(7);
    Eff2_l->SetMarkerStyle(7);
    Eff3_l->SetMarkerStyle(7);
    Eff4_l->SetMarkerStyle(7);
    Eff1_l->SetMarkerSize(2);
    Eff2_l->SetMarkerSize(2);
    Eff3_l->SetMarkerSize(2);
    Eff4_l->SetMarkerSize(2);
    Eff1_l->Draw("L");
    Eff1_l->Draw("same");
//    Eff2_l->Draw("L same");
    Eff3_l->Draw("L same");
    Eff4_l->Draw("L same");
    qw3->Draw(); 
    tex1->Draw();
    tex2->Draw();
    TString name_plot3="compare2_vs_"+flagname+"_l_"+name+wpname+format;
    if (printfunc) name_plot3="fit_"+name_plot3;
    c3->SaveAs(name_plot3);
    


}
void CompareEff3(TString name, int wpflag, int flag1){

    // File1
    TH1D* hist_b_r1;
    TH1D* hist_c_r1;
    TH1D* hist_l_r1;
    TH1D* hist_g_r1;
    TH1D* hist_gc_r1;
    TH1D* hist_gb_r1;

    TH1D* hist_b_1;
    TH1D* hist_c_1;
    TH1D* hist_l_1;
    TH1D* hist_g_1;
    TH1D* hist_gc_1;
    TH1D* hist_gb_1;

    // File2
    TH1D* hist_b_r2;
    TH1D* hist_c_r2;
    TH1D* hist_l_r2;
    TH1D* hist_g_r2;
    TH1D* hist_gc_r2;
    TH1D* hist_gb_r2;
    TH1D* hist_b_2;
    TH1D* hist_c_2;
    TH1D* hist_l_2;
    TH1D* hist_g_2;
    TH1D* hist_gc_2;
    TH1D* hist_gb_2;

    // File3
    TH1D* hist_b_r3;
    TH1D* hist_c_r3;
    TH1D* hist_l_r3;
    TH1D* hist_g_r3;
    TH1D* hist_gc_r3;
    TH1D* hist_gb_r3;
    TH1D* hist_b_3;
    TH1D* hist_c_3;
    TH1D* hist_l_3;
    TH1D* hist_g_3;
    TH1D* hist_gc_3;
    TH1D* hist_gb_3;

    // File3
    TH1D* hist_b_r4;
    TH1D* hist_c_r4;
    TH1D* hist_l_r4;
    TH1D* hist_g_r4;
    TH1D* hist_gc_r4;
    TH1D* hist_gb_r4;
    TH1D* hist_b_4;
    TH1D* hist_c_4;
    TH1D* hist_l_4;
    TH1D* hist_g_4;
    TH1D* hist_gc_4;
    TH1D* hist_gb_4;


    // File4
    TH1D* hist_b_r5;
    TH1D* hist_c_r5;
    TH1D* hist_l_r5;
    TH1D* hist_g_r5;
    TH1D* hist_gc_r5;
    TH1D* hist_gb_r5;
    TH1D* hist_b_5;
    TH1D* hist_c_5;
    TH1D* hist_l_5;
    TH1D* hist_g_5;
    TH1D* hist_gc_5;
    TH1D* hist_gb_5;

    TFile *myFile_1     = new TFile(filename_1);
    myFile_1->cd();

    TString flagname;
    if (flag1==1) flagname="pt";
    else if (flag1==2) flagname="eta";
    else if (flag1==3) flagname="pu";
    else if (flag1==4) flagname="hadpt";
    else if (flag1==5) flagname="ptlead";
    else if (flag1==6) flagname="etalead";
    else if (flag1==7) flagname="hadptlead";

    hist_b_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    cout << "1- 'ok ? " << endl;
    hist_l_r1->Add(hist_g_r1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r1->Add(hist_gb_r1);
        hist_c_r1->Add(hist_gc_r1);
    }

    TString wpname;
    if (wpflag==0) wpname="l";
    else if (wpflag==1) wpname="m";
    else if (wpflag==2) wpname="t";
    hist_b_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    cout << "2- 'ok ? " << endl;
    hist_l_1->Add(hist_g_1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_1->Add(hist_gb_1);
        hist_c_1->Add(hist_gc_1);
    }

    cout << "2.1- 'ok ? " << endl;
    TFile *myFile_2     = new TFile(filename_2);
    myFile_2->cd();
    cout << "2.5- 'ok ? " << endl;

    hist_b_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    cout << "2.6- 'ok ? " << endl;
    hist_c_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_b_r3         = (TH1D*) hist_b_r2->Clone();
    hist_c_r3         = (TH1D*) hist_c_r2->Clone();
    hist_l_r3         = (TH1D*) hist_l_r2->Clone();
    hist_g_r3         = (TH1D*) hist_g_r2->Clone();
    hist_gb_r3         = (TH1D*) hist_gb_r2->Clone();
    hist_gc_r3         = (TH1D*) hist_gc_r2->Clone();


    cout << "3- 'ok ? " << endl;
    hist_l_r2->Add(hist_g_r2);
    hist_l_r3->Add(hist_g_r3);

    // r2 with gluon splitting
    hist_b_r2->Add(hist_gb_r2);
    hist_c_r2->Add(hist_gc_r2);
    // r3 without    


    hist_b_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_b_3         = (TH1D*) hist_b_2->Clone();
    hist_c_3         = (TH1D*) hist_c_2->Clone();
    hist_l_3         = (TH1D*) hist_l_2->Clone();
    hist_g_3         = (TH1D*) hist_g_2->Clone();
    hist_gb_3         = (TH1D*) hist_gb_2->Clone();
    hist_gc_3         = (TH1D*) hist_gc_2->Clone();

    hist_l_2->Add(hist_g_2);
    hist_l_3->Add(hist_g_3);
    hist_b_2->Add(hist_gb_2);
    hist_c_2->Add(hist_gc_2);

    cout << "4- 'ok ? " << endl;

    TFile *myFile_3     = new TFile(filename_3);
    myFile_3->cd();

    hist_b_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_l_r4->Add(hist_g_r4);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r4->Add(hist_gb_r4);
        hist_c_r4->Add(hist_gc_r4);
    }

    hist_b_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_l_4->Add(hist_g_4);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_4->Add(hist_gb_4);
        hist_c_4->Add(hist_gc_4);
    }

    TFile *myFile_5     = new TFile(filename_4);
    myFile_5->cd();

    hist_b_r5         = (TH1D*)gROOT->FindObject("jet_"+flagname+"prompt_nobtag_b");
    hist_c_r5         = (TH1D*)gROOT->FindObject("jet_"+flagname+"prompt_nobtag_c");

    hist_b_5         = (TH1D*)gROOT->FindObject("jet_"+flagname+"prompt_"+name+"_"+wpname+"_b");
    hist_c_5         = (TH1D*)gROOT->FindObject("jet_"+flagname+"prompt_"+name+"_"+wpname+"_c");

    hist_l_r5 = (TH1D*) hist_b_r5->Clone();
    hist_l_5 = (TH1D*) hist_b_5->Clone();

    int nbin_max_1= hist_b_1->GetNbinsX();
    float minx=hist_b_1->GetXaxis()->GetXmin();
    float maxx=hist_b_1->GetXaxis()->GetXmax();
    cout << "nbin_max_1 "<< nbin_max_1 << "   " << minx << "  " << maxx << endl;

     TH1D * hist_clone = (TH1D*)hist_b_1->Clone("hist_clone");
     for (int i=0; i<hist_clone->GetNbinsX()+1; i++) {
        hist_clone->SetBinContent(i,0);
        hist_clone->SetBinError(i,0);
     }
     TH1D * Eff1_b= (TH1D*) hist_clone->Clone("Eff1_b");
     TH1D * Eff1_c= (TH1D*) hist_clone->Clone("Eff1_c");
     TH1D * Eff1_l= (TH1D*) hist_clone->Clone("Eff1_l");
     TH1D * Eff2_b= (TH1D*) hist_clone->Clone("Eff2_b");
     TH1D * Eff2_c= (TH1D*) hist_clone->Clone("Eff2_c");
     TH1D * Eff2_l= (TH1D*) hist_clone->Clone("Eff2_l");
     TH1D * Eff3_b= (TH1D*) hist_clone->Clone("Eff3_b");
     TH1D * Eff3_c= (TH1D*) hist_clone->Clone("Eff3_c");
     TH1D * Eff3_l= (TH1D*) hist_clone->Clone("Eff3_l");
     TH1D * Eff4_b= (TH1D*) hist_clone->Clone("Eff4_b");
     TH1D * Eff4_c= (TH1D*) hist_clone->Clone("Eff4_c");
     TH1D * Eff4_l= (TH1D*) hist_clone->Clone("Eff4_l");
     TH1D * Eff5_b= (TH1D*) hist_clone->Clone("Eff5_b");
     TH1D * Eff5_c= (TH1D*) hist_clone->Clone("Eff5_c");
     TH1D * Eff5_l= (TH1D*) hist_clone->Clone("Eff5_l");


    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_1,hist_c_1,hist_l_1,Eff1_b,Eff1_c,Eff1_l, 8) ;
    ComputeEffvsPT(hist_b_r2,hist_c_r2,hist_l_r2,hist_b_2,hist_c_2,hist_l_2,Eff2_b,Eff2_c,Eff2_l, kBlue) ;
    ComputeEffvsPT(hist_b_r3,hist_c_r3,hist_l_r3,hist_b_3,hist_c_3,hist_l_3,Eff3_b,Eff3_c,Eff3_l, 2) ;
    ComputeEffvsPT(hist_b_r4,hist_c_r4,hist_l_r4,hist_b_4,hist_c_4,hist_l_4,Eff4_b,Eff4_c,Eff4_l, kViolet) ;
    ComputeEffvsPT(hist_b_r5,hist_c_r5,hist_l_r5,hist_b_5,hist_c_5,hist_l_5,Eff5_b,Eff5_c,Eff5_l, kGray) ;
 
    cout << "5- 'ok ? " << endl;

    TString titleHisti;
    if (flag1==1) titleHisti="jet pT [GeV]";
    else if (flag1==2) titleHisti="jet eta ";
    else if (flag1==3) titleHisti="#PU";
    else if (flag1==4) titleHisti="hadron pT [GeV]";
    else if (flag1==5) titleHisti="leading jet pT [GeV]";
    else if (flag1==6) titleHisti="leading jet eta [GeV]";
    else if (flag1==7) titleHisti="hadron pT of leading jet [GeV]";
    Eff1_b->GetXaxis()->SetTitle(titleHisti);
    Eff1_l->GetXaxis()->SetTitle(titleHisti);
    Eff1_c->GetXaxis()->SetTitle(titleHisti);


    Eff1_c->SetMaximum(0.6);        
    Eff1_l->SetMaximum(0.35);        
    if (name=="deep") Eff1_l->SetMaximum(0.6);
    if (name=="ctag") Eff1_l->SetMaximum(1.1);
    if (name=="ctag") Eff1_c->SetMaximum(1.);
    if (name=="ctag") Eff1_b->SetMaximum(0.7);
    if (name=="ctag") Eff1_l->SetMinimum(0.005);


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);


    c1->SetFillColor(10);
    c1->cd();
    c1->SetBorderMode(0);  
    c1->SetBorderSize(2);
    c1->SetFrameFillColor(0);
    c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetLeftMargin(0.1461539);
    c1_1->SetRightMargin(0.05384616);
    c1_1->SetTopMargin(0.06831119);
    c1_1->SetBottomMargin(0.1574953);
    c1_1->SetFrameBorderMode(0);
    c1_1->cd(); 
    c1_1->SetGridy();


    TLegend* qw = 0;
//    qw = new TLegend(0.13,0.22,0.33,0.39,NULL,"brNDC"); // Caro
    qw = new TLegend(0.1884615,0.2144213,0.3602564,0.4079696,NULL,"brNDC"); 
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);

    qw->AddEntry(Eff1_b, "ttbar powheg", "p");
    qw->AddEntry(Eff4_b, "ttbar herwig", "p");
    if (flag1!=4 && flag1!=7) qw->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw->AddEntry(Eff3_b, "QCD without gsplit", "p");
    qw->AddEntry(Eff5_b, "QCD prompt b", "p");

    Eff1_b->SetTitleSize(0.08,"Y");
    Eff1_b->SetTitleOffset(0.65,"Y");  
    Eff1_b->SetTitleOffset(0.81,"Y");
    Eff1_b->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_b->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_b->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_b->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_b->GetYaxis()->SetTitleOffset(0.9);
    Eff1_b->SetMarkerStyle(7);
    Eff2_b->SetMarkerStyle(7);
    Eff3_b->SetMarkerStyle(7);
    Eff4_b->SetMarkerStyle(7);
    Eff5_b->SetMarkerStyle(7);
    Eff1_b->SetMarkerSize(2);
    Eff2_b->SetMarkerSize(2);
    Eff3_b->SetMarkerSize(2);
    Eff4_b->SetMarkerSize(2);
    Eff5_b->SetMarkerSize(2);
    Eff1_b->Draw();

    Eff1_b->Draw("same");
    if (flag1!=4 && flag1!=7) Eff2_b->Draw("same");
    Eff3_b->Draw("same");
    Eff4_b->Draw("same");
    Eff5_b->Draw("same");



    TLatex *   tex1 = new TLatex(0.8782051,0.9506641,"#sqrt{s}=13 TeV, 2016");
    tex1->SetNDC();
    tex1->SetTextAlign(31);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.04875);
    tex1->SetLineWidth(2);
    tex1->Draw();
//    TLatex *  tex2 = new TLatex(0.5782051,0.9184061,"CMS Simulation");
    TLatex *  tex2 = new TLatex(0.1935897,0.9089184,"CMS Simulation");
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.065);
    tex2->SetLineWidth(2);
    tex2->Draw();


    qw->Draw();
    TString name_plot="compare3_vs_"+flagname+"_b_"+name+wpname+format;
    if (printfunc) name_plot="fit_"+name_plot;
    c1->SaveAs(name_plot);

    TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
    c2->cd();
  c2->SetBorderMode(0);  
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderMode(0);

    TPad *c2_1 = new TPad("canvas_2", "canvas_2",0,0,1.0,1.0);
    c2_1->SetFillColor(0);
    c2_1->SetBorderMode(0);
    c2_1->SetBorderSize(2);
   c2_1->SetLeftMargin(0.1461539);
   c2_1->SetRightMargin(0.05384616);
   c2_1->SetTopMargin(0.06831119);
   c2_1->SetBottomMargin(0.1574953);
    c2_1->SetFrameBorderMode(0);
    c2_1->Draw();
    c2_1->cd();
    c2_1->SetGridy();

    TLegend* qw2 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw2 = new TLegend(0.6666667,0.7343454-0.3,0.8666667,0.9032258-0.3,NULL,"brNDC");
    qw2->AddEntry(Eff1_b, "ttbar powheg", "p");
    qw2->AddEntry(Eff4_b, "ttbar herwig", "p");
    if (flag1!=4 && flag1!=7) qw2->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw2->AddEntry(Eff3_b, "QCD without gsplit", "p");
    qw2->AddEntry(Eff5_b, "QCD prompt b", "p");
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
    Eff1_c->SetTitleSize(0.08,"Y");
    Eff1_c->SetTitleOffset(0.65,"Y");  
    Eff1_c->SetTitleOffset(0.81,"Y");
    Eff1_c->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_c->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_c->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_c->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_c->GetYaxis()->SetTitleOffset(0.9);

    Eff1_c->SetMarkerStyle(7);
    Eff2_c->SetMarkerStyle(7);
    Eff3_c->SetMarkerStyle(7);
    Eff4_c->SetMarkerStyle(7);
    Eff5_c->SetMarkerStyle(7);
    Eff1_c->SetMarkerSize(2);
    Eff2_c->SetMarkerSize(2);
    Eff3_c->SetMarkerSize(2);
    Eff4_c->SetMarkerSize(2);
    Eff5_c->SetMarkerSize(2);
    Eff1_c->Draw("L");
    Eff1_c->Draw("L same");
    if (flag1!=4 && flag1!=7) Eff2_c->Draw("L same");
    Eff3_c->Draw("L same");
    Eff4_c->Draw("L same");
    Eff5_c->Draw("L same");
    qw2->Draw();
    tex1->Draw();
    tex2->Draw();
    TString name_plot2="compare3_vs_"+flagname+"_c_"+name+wpname+format;
    if (printfunc) name_plot2="fit_"+name_plot2;
    c2->SaveAs(name_plot2);

  
    TCanvas *c3 = new TCanvas("c3", "c3",10,32,782,552);
    c3->cd();
  c3->SetBorderMode(0);  
  c3->SetBorderSize(2);
  c3->SetFrameFillColor(0);
  c3->SetFrameBorderMode(0);
    TPad *c3_1 = new TPad("canvas_3", "canvas_3",0,0,1.0,1.0);
    c3_1->SetFillColor(0);
    c3_1->SetBorderMode(0);
    c3_1->SetBorderSize(2);
   c3_1->SetLeftMargin(0.1461539);
   c3_1->SetRightMargin(0.05384616);
   c3_1->SetTopMargin(0.06831119);
   c3_1->SetBottomMargin(0.1574953);
    c3_1->SetFrameBorderMode(0);
    c3_1->Draw();
    c3_1->cd();
    c3_1->SetGridy();
    c3_1->SetLogy(1);

    TLegend* qw3 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw3 = new TLegend(0.6666667,0.7343454-0.5,0.8666667,0.9032258-0.5,NULL,"brNDC");
    qw3->AddEntry(Eff1_b, "ttbar powheg", "p");
    qw3->AddEntry(Eff4_b, "ttbar herwig", "p");
//    qw3->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw3->AddEntry(Eff3_b, "QCD", "p");
  qw3->SetBorderSize(1);
  qw3->SetTextFont(62);
  qw3->SetLineColor(1);
  qw3->SetLineStyle(1);
  qw3->SetLineWidth(1);
  qw3->SetFillColor(0);
  qw3->SetFillStyle(1001);
    Eff1_l->SetTitleSize(0.08,"Y");
    Eff1_l->SetTitleOffset(0.65,"Y");  
    Eff1_l->SetTitleOffset(0.81,"Y");
    Eff1_l->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_l->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_l->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_l->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_l->GetYaxis()->SetTitleOffset(0.9);
    Eff1_l->SetMarkerStyle(7);
    Eff2_l->SetMarkerStyle(7);
    Eff3_l->SetMarkerStyle(7);
    Eff4_l->SetMarkerStyle(7);
    Eff1_l->SetMarkerSize(2);
    Eff2_l->SetMarkerSize(2);
    Eff3_l->SetMarkerSize(2);
    Eff4_l->SetMarkerSize(2);
    Eff1_l->Draw("L");
    Eff1_l->Draw("same");
//    Eff2_l->Draw("L same");
    Eff3_l->Draw("L same");
    Eff4_l->Draw("L same");
    qw3->Draw(); 
    tex1->Draw();
    tex2->Draw();
    TString name_plot3="compare3_vs_"+flagname+"_l_"+name+wpname+format;
    if (printfunc) name_plot3="fit_"+name_plot3;
    c3->SaveAs(name_plot3);
    


}
void CompareEffPlus2(TString name, int wpflag, int flag1){

    if (flag1!=1 && flag1!=4 && flag1!=5 && flag1!=7) return;
    // File1
    TH1D* hist_b_r1;
    TH1D* hist_c_r1;
    TH1D* hist_l_r1;
    TH1D* hist_g_r1;
    TH1D* hist_gc_r1;
    TH1D* hist_gb_r1;

    TH1D* hist_b_1;
    TH1D* hist_c_1;
    TH1D* hist_l_1;
    TH1D* hist_g_1;
    TH1D* hist_gc_1;
    TH1D* hist_gb_1;

    // File2
    TH1D* hist_b_r2;
    TH1D* hist_b_r2_p5;
    TH1D* hist_b_r2_m5;
    TH1D* hist_b_r2_gm25;
    TH1D* hist_b_r2_gp25;
    TH1D* hist_c_r2;
    TH1D* hist_l_r2;
    TH1D* hist_g_r2;
    TH1D* hist_gc_r2;
    TH1D* hist_gb_r2;
    TH1D* hist_b_2;
    TH1D* hist_b_2_gm25;
    TH1D* hist_b_2_gp25;
    TH1D* hist_b_2_p5;
    TH1D* hist_b_2_m5;
    TH1D* hist_c_2;
    TH1D* hist_l_2;
    TH1D* hist_g_2;
    TH1D* hist_gc_2;
    TH1D* hist_gb_2;

    // File3
    TH1D* hist_b_r3;
    TH1D* hist_b_r3_p5;
    TH1D* hist_b_r3_m5;
    TH1D* hist_c_r3;
    TH1D* hist_l_r3;
    TH1D* hist_g_r3;
    TH1D* hist_gc_r3;
    TH1D* hist_gb_r3;
    TH1D* hist_b_3;
    TH1D* hist_b_3_p5;
    TH1D* hist_b_3_m5;
    TH1D* hist_c_3;
    TH1D* hist_l_3;
    TH1D* hist_g_3;
    TH1D* hist_gc_3;
    TH1D* hist_gb_3;

    // File3
    TH1D* hist_b_r4;
    TH1D* hist_c_r4;
    TH1D* hist_l_r4;
    TH1D* hist_g_r4;
    TH1D* hist_gc_r4;
    TH1D* hist_gb_r4;
    TH1D* hist_b_4;
    TH1D* hist_c_4;
    TH1D* hist_l_4;
    TH1D* hist_g_4;
    TH1D* hist_gc_4;
    TH1D* hist_gb_4;


    TFile *myFile_1     = new TFile(filename_1);
    myFile_1->cd();

    TString flagname;
    if (flag1==1) flagname="pt";
    else if (flag1==2) flagname="eta";
    else if (flag1==3) flagname="pu";
    else if (flag1==4) flagname="hadpt";
    else if (flag1==5) flagname="ptlead";
    else if (flag1==7) flagname="hadptlead";

    hist_b_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");


    hist_l_r1->Add(hist_g_r1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r1->Add(hist_gb_r1);
        hist_c_r1->Add(hist_gc_r1);
    }

    TString wpname;
    if (wpflag==0) wpname="l";
    else if (wpflag==1) wpname="m";
    else if (wpflag==2) wpname="t";
    hist_b_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_l_1->Add(hist_g_1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_1->Add(hist_gb_1);
        hist_c_1->Add(hist_gc_1);
    }

    TFile *myFile_2     = new TFile(filename_2);
    myFile_2->cd();

    hist_b_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    if (flag1==1)  hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_nobtag_b");
    else if (flag1==5)  hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_nobtag_b");
    else if (flag1==7)  hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_hadpt_nobtag_b");
    else hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_"+flagname+"_nobtag_b");
    if (flag1==1)  hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_nobtag_b");
    else if (flag1==5)  hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_nobtag_b");
    else if (flag1==7)  hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_hadpt_nobtag_b");
    else hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_"+flagname+"_nobtag_b");
    hist_c_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_b_r3         = (TH1D*) hist_b_r2->Clone();
    hist_b_r3_p5         = (TH1D*) hist_b_r2_p5->Clone();
    hist_b_r3_m5         = (TH1D*) hist_b_r2_m5->Clone();
    hist_c_r3         = (TH1D*) hist_c_r2->Clone();
    hist_l_r3         = (TH1D*) hist_l_r2->Clone();
    hist_g_r3         = (TH1D*) hist_g_r2->Clone();
    hist_gb_r3         = (TH1D*) hist_gb_r2->Clone();
    hist_gc_r3         = (TH1D*) hist_gc_r2->Clone();


    hist_l_r2->Add(hist_g_r2);
    hist_l_r3->Add(hist_g_r3);

    // r2 with gluon splitting
    hist_b_r2_gm25 = (TH1D*) hist_gb_r2->Clone();
    hist_b_r2_gm25->Scale(0.75);
//    hist_b_r2_gm25->Scale(0.1);
    hist_b_r2_gm25->Add(hist_b_r2);
    hist_b_r2_gp25 = (TH1D*) hist_gb_r2->Clone();
    hist_b_r2_gp25->Scale(1.25);
//    hist_b_r2_gp25->Scale(1.5);
    hist_b_r2_gp25->Add(hist_b_r2);

    hist_b_r2->Add(hist_gb_r2);
    hist_c_r2->Add(hist_gc_r2);
    // r3 without    


    hist_b_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    if (flag1==1)  hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_"+name+"_"+wpname+"_b"); 
    else if (flag1==5)  hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_"+name+"_"+wpname+"_b"); 
    else if (flag1==7)  hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_hadpt_"+name+"_"+wpname+"_b");
    else hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_"+flagname+"_"+name+"_"+wpname+"_b");
    if (flag1==1)  hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_"+name+"_"+wpname+"_b"); 
    else if (flag1==5)  hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_"+name+"_"+wpname+"_b"); 
    else if (flag1==7)  hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_hadpt_"+name+"_"+wpname+"_b");
    else hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_b_3         = (TH1D*) hist_b_2->Clone();
    hist_b_3_p5      = (TH1D*) hist_b_2_p5->Clone();
    hist_b_3_m5      = (TH1D*) hist_b_2_m5->Clone();
    hist_c_3         = (TH1D*) hist_c_2->Clone();
    hist_l_3         = (TH1D*) hist_l_2->Clone();
    hist_g_3         = (TH1D*) hist_g_2->Clone();
    hist_gb_3         = (TH1D*) hist_gb_2->Clone();
    hist_gc_3         = (TH1D*) hist_gc_2->Clone();

    hist_l_2->Add(hist_g_2);
    hist_l_3->Add(hist_g_3);
    hist_b_2_gm25 = (TH1D*) hist_gb_2->Clone();
    hist_b_2_gm25->Scale(0.75);
//    hist_b_2_gm25->Scale(0.1);
    hist_b_2_gm25->Add(hist_b_2);
    hist_b_2_gp25 = (TH1D*) hist_gb_2->Clone();
    hist_b_2_gp25->Scale(1.25);
//    hist_b_2_gp25->Scale(1.5);
    hist_b_2_gp25->Add(hist_b_2);
    hist_b_2->Add(hist_gb_2);
    hist_c_2->Add(hist_gc_2);


    TFile *myFile_3     = new TFile(filename_3);
    myFile_3->cd();

    hist_b_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_l_r4->Add(hist_g_r4);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r4->Add(hist_gb_r4);
        hist_c_r4->Add(hist_gc_r4);
    }

    hist_b_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_4         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_l_4->Add(hist_g_4);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_4->Add(hist_gb_4);
        hist_c_4->Add(hist_gc_4);
    }
    int nbin_max_1= hist_b_1->GetNbinsX();
    float minx=hist_b_1->GetXaxis()->GetXmin();
    float maxx=hist_b_1->GetXaxis()->GetXmax();
    cout << "nbin_max_1 "<< nbin_max_1 << "   " << minx << "  " << maxx << endl;

     TH1D * hist_clone = (TH1D*)hist_b_1->Clone("hist_clone");
     for (int i=0; i<hist_clone->GetNbinsX()+1; i++) {
        hist_clone->SetBinContent(i,0);
        hist_clone->SetBinError(i,0);
     }
     TH1D * Eff1_b= (TH1D*) hist_clone->Clone("Eff1_b");
     TH1D * Eff1_c= (TH1D*) hist_clone->Clone("Eff1_c");
     TH1D * Eff1_l= (TH1D*) hist_clone->Clone("Eff1_l");
     TH1D * Eff2_b= (TH1D*) hist_clone->Clone("Eff2_b");
     TH1D * Eff2_c= (TH1D*) hist_clone->Clone("Eff2_c");
     TH1D * Eff2_l= (TH1D*) hist_clone->Clone("Eff2_l");
     TH1D * Eff3_b= (TH1D*) hist_clone->Clone("Eff3_b");
     TH1D * Eff3_c= (TH1D*) hist_clone->Clone("Eff3_c");
     TH1D * Eff3_l= (TH1D*) hist_clone->Clone("Eff3_l");
     TH1D * Eff3_b_p5= (TH1D*) hist_clone->Clone("Eff3_b_p5");
     TH1D * Eff3_b_m5= (TH1D*) hist_clone->Clone("Eff3_b_m5");
     TH1D * Eff_no= (TH1D*) hist_clone->Clone("Eff_no");
     TH1D * Eff2_b_gp25= (TH1D*) hist_clone->Clone("Eff2_b_gp25");
     TH1D * Eff2_b_gm25= (TH1D*) hist_clone->Clone("Eff2_b_gp25");
     TH1D * Eff4_b= (TH1D*) hist_clone->Clone("Eff4_b");
     TH1D * Eff4_c= (TH1D*) hist_clone->Clone("Eff4_c");
     TH1D * Eff4_l= (TH1D*) hist_clone->Clone("Eff4_l");


    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_1,hist_c_1,hist_l_1,Eff1_b,Eff1_c,Eff1_l, 8) ;
    ComputeEffvsPT(hist_b_r2,hist_c_r2,hist_l_r2,hist_b_2,hist_c_2,hist_l_2,Eff2_b,Eff2_c,Eff2_l, kBlue) ;
    ComputeEffvsPT(hist_b_r3,hist_c_r3,hist_l_r3,hist_b_3,hist_c_3,hist_l_3,Eff3_b,Eff3_c,Eff3_l, 2) ;
    ComputeEffvsPT(hist_b_r3_p5,hist_b_r3_m5,hist_b_r3_p5,hist_b_3_p5,hist_b_3_m5,hist_b_3_p5,Eff3_b_p5,Eff3_b_m5,Eff_no, kOrange-3) ;
    ComputeEffvsPT(hist_b_r2_gp25,hist_b_r2_gm25,hist_b_r2_gp25,hist_b_2_gp25,hist_b_2_gm25, hist_b_2_gp25, Eff2_b_gp25, Eff2_b_gm25, Eff_no, kAzure+8) ;
    ComputeEffvsPT(hist_b_r4,hist_c_r4,hist_l_r4,hist_b_4,hist_c_4,hist_l_4,Eff4_b,Eff4_c,Eff4_l, kViolet) ;

    TString titleHisti;
    if (flag1==1) titleHisti="jet pT [GeV]";
    else if (flag1==2) titleHisti="jet eta ";
    else if (flag1==3) titleHisti="#PU";
    else if (flag1==4) titleHisti="hadron pT [GeV]";
    else if (flag1==5) titleHisti="leading jet pT [GeV]";
    else if (flag1==7) titleHisti="hadron pT of leading jet[GeV]";
    Eff1_b->GetXaxis()->SetTitle(titleHisti);
    Eff1_l->GetXaxis()->SetTitle(titleHisti);
    Eff1_c->GetXaxis()->SetTitle(titleHisti);


    Eff1_c->SetMaximum(0.6);        
    Eff1_l->SetMaximum(0.35);        
    if (name=="deep") Eff1_l->SetMaximum(0.6);
    if (name=="ctag") Eff1_l->SetMaximum(1.1);
    if (name=="ctag") Eff1_c->SetMaximum(1.);
    if (name=="ctag") Eff1_b->SetMaximum(0.7);
    if (name=="ctag") Eff1_l->SetMinimum(0.005);


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);


    c1->SetFillColor(10);
    c1->cd();
    c1->SetBorderMode(0);  
    c1->SetBorderSize(2);
    c1->SetFrameFillColor(0);
    c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetLeftMargin(0.1461539);
    c1_1->SetRightMargin(0.05384616);
    c1_1->SetTopMargin(0.06831119);
    c1_1->SetBottomMargin(0.1574953);
    c1_1->SetFrameBorderMode(0);
    c1_1->cd(); 
    c1_1->SetGridy();


    TLegend* qw = 0;
//    qw = new TLegend(0.13,0.22,0.33,0.39,NULL,"brNDC"); // Caro
    qw = new TLegend(0.1884615,0.2144213,0.3602564,0.4079696,NULL,"brNDC"); 
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);

    qw->AddEntry(Eff1_b, "ttbar powheg", "p");
    qw->AddEntry(Eff4_b, "ttbar herwig", "p");
    if (flag1!=4 && flag1!=7) qw->AddEntry(Eff2_b, "QCD with gsplit", "p");
    if (flag1!=4 && flag1!=7) qw->AddEntry(Eff2_b_gp25, "variation of gsplit", "l");
    qw->AddEntry(Eff3_b, "QCD without gsplit", "p");
    qw->AddEntry(Eff3_b_p5, "variation of b-frag", "l");

    Eff1_b->SetTitleSize(0.08,"Y");
    Eff1_b->SetTitleOffset(0.65,"Y");  
    Eff1_b->SetTitleOffset(0.81,"Y");
    Eff1_b->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_b->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_b->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_b->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_b->GetYaxis()->SetTitleOffset(0.9);
    Eff1_b->SetMarkerStyle(7);
    Eff2_b->SetMarkerStyle(7);
    Eff4_b->SetMarkerStyle(7);
    Eff2_b_gp25->SetMarkerStyle(7);
    Eff2_b_gm25->SetMarkerStyle(7);
    Eff3_b->SetMarkerStyle(7);
    Eff3_b_p5->SetMarkerStyle(7);
    Eff3_b_m5->SetMarkerStyle(7);
    Eff1_b->SetMarkerSize(4);
    Eff2_b->SetMarkerSize(4);
    Eff4_b->SetMarkerSize(4);
    Eff2_b_gp25->SetMarkerSize(4);
    Eff2_b_gm25->SetMarkerSize(4);
    Eff3_b->SetMarkerSize(4);
    Eff3_b_p5->SetMarkerSize(4);
    Eff3_b_m5->SetMarkerSize(4);
    Eff1_b->Draw();

    Eff1_b->Draw("same");
    if (flag1!=4 && flag1!=7) Eff2_b->Draw("same");
    if (flag1!=4 && flag1!=7) Eff2_b_gp25->Draw("hist l same");
    if (flag1!=4 && flag1!=7) Eff2_b_gm25->Draw("hist l same");

    Eff3_b->Draw("same");
    Eff3_b_p5->Draw("hist l same");
    Eff3_b_m5->Draw("hist l same");
    Eff4_b->Draw("same");


    TLatex *   tex1 = new TLatex(0.8782051,0.9506641,"#sqrt{s}=13 TeV, 2016");
    tex1->SetNDC();
    tex1->SetTextAlign(31);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.04875);
    tex1->SetLineWidth(2);
    tex1->Draw();
//    TLatex *  tex2 = new TLatex(0.5782051,0.9184061,"CMS Simulation");
    TLatex *  tex2 = new TLatex(0.1935897,0.9089184,"CMS Simulation");
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.065);
    tex2->SetLineWidth(2);
    tex2->Draw();


    qw->Draw();
    TString name_plot="syst2_"+flagname+"_b_"+name+wpname+format;
    if (printfunc) name_plot="fit_"+name_plot;
    c1->SaveAs(name_plot);

/*
    TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
    c2->cd();
  c2->SetBorderMode(0);  
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderMode(0);

    TPad *c2_1 = new TPad("canvas_2", "canvas_2",0,0,1.0,1.0);
    c2_1->SetFillColor(0);
    c2_1->SetBorderMode(0);
    c2_1->SetBorderSize(2);
   c2_1->SetLeftMargin(0.1461539);
   c2_1->SetRightMargin(0.05384616);
   c2_1->SetTopMargin(0.06831119);
   c2_1->SetBottomMargin(0.1574953);
    c2_1->SetFrameBorderMode(0);
    c2_1->Draw();
    c2_1->cd();
    c2_1->SetGridy();

    TLegend* qw2 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw2 = new TLegend(0.6666667,0.7343454-0.3,0.8666667,0.9032258-0.3,NULL,"brNDC");
    qw2->AddEntry(Eff1_b, "ttbar", "p");
    if (flag1!=4) qw2->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw2->AddEntry(Eff3_b, "QCD without gsplit", "p");
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
    Eff1_c->SetTitleSize(0.08,"Y");
    Eff1_c->SetTitleOffset(0.65,"Y");  
    Eff1_c->SetTitleOffset(0.81,"Y");
    Eff1_c->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_c->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_c->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_c->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_c->GetYaxis()->SetTitleOffset(0.9);

    Eff1_c->SetMarkerStyle(7);
    Eff2_c->SetMarkerStyle(7);
    Eff3_c->SetMarkerStyle(7);
    Eff1_c->SetMarkerSize(2);
    Eff2_c->SetMarkerSize(2);
    Eff3_c->SetMarkerSize(2);
    Eff1_c->Draw("L");
    Eff1_c->Draw("L same");
    if (flag1!=4) Eff2_c->Draw("L same");
    Eff3_c->Draw("L same");
    qw2->Draw();
    tex1->Draw();
    tex2->Draw();
    TString name_plot2="compare_vs_"+flagname+"_c_"+name+wpname+format;
    if (printfunc) name_plot2="fit_"+name_plot2;
    c2->SaveAs(name_plot2);

  
    TCanvas *c3 = new TCanvas("c3", "c3",10,32,782,552);
    c3->cd();
  c3->SetBorderMode(0);  
  c3->SetBorderSize(2);
  c3->SetFrameFillColor(0);
  c3->SetFrameBorderMode(0);
    TPad *c3_1 = new TPad("canvas_3", "canvas_3",0,0,1.0,1.0);
    c3_1->SetFillColor(0);
    c3_1->SetBorderMode(0);
    c3_1->SetBorderSize(2);
   c3_1->SetLeftMargin(0.1461539);
   c3_1->SetRightMargin(0.05384616);
   c3_1->SetTopMargin(0.06831119);
   c3_1->SetBottomMargin(0.1574953);
    c3_1->SetFrameBorderMode(0);
    c3_1->Draw();
    c3_1->cd();
    c3_1->SetGridy();
    c3_1->SetLogy(1);

    TLegend* qw3 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw3 = new TLegend(0.6666667,0.7343454-0.6,0.8666667,0.9032258-0.6,NULL,"brNDC");
    qw3->AddEntry(Eff1_b, "ttbar", "p");
//    qw3->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw3->AddEntry(Eff3_b, "QCD", "p");
  qw3->SetBorderSize(1);
  qw3->SetTextFont(62);
  qw3->SetLineColor(1);
  qw3->SetLineStyle(1);
  qw3->SetLineWidth(1);
  qw3->SetFillColor(0);
  qw3->SetFillStyle(1001);
    Eff1_l->SetTitleSize(0.08,"Y");
    Eff1_l->SetTitleOffset(0.65,"Y");  
    Eff1_l->SetTitleOffset(0.81,"Y");
    Eff1_l->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_l->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_l->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_l->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_l->GetYaxis()->SetTitleOffset(0.9);
    Eff1_l->SetMarkerStyle(7);
    Eff2_l->SetMarkerStyle(7);
    Eff3_l->SetMarkerStyle(7);
    Eff1_l->SetMarkerSize(2);
    Eff2_l->SetMarkerSize(2);
    Eff3_l->SetMarkerSize(2);
    Eff1_l->Draw("L");
    Eff1_l->Draw("same");
//    Eff2_l->Draw("L same");
    Eff3_l->Draw("L same");
    qw3->Draw(); 
    tex1->Draw();
    tex2->Draw();
    TString name_plot3="compare_vs_"+flagname+"_l_"+name+wpname+format;
    if (printfunc) name_plot3="fit_"+name_plot3;
    c3->SaveAs(name_plot3);
    
*/

}
void CompareEffPlus(TString name, int wpflag, int flag1){

    if (flag1!=1 && flag1!=4 && flag1!=5 && flag1!=7) return;
    // File1
    TH1D* hist_b_r1;
    TH1D* hist_c_r1;
    TH1D* hist_l_r1;
    TH1D* hist_g_r1;
    TH1D* hist_gc_r1;
    TH1D* hist_gb_r1;

    TH1D* hist_b_1;
    TH1D* hist_c_1;
    TH1D* hist_l_1;
    TH1D* hist_g_1;
    TH1D* hist_gc_1;
    TH1D* hist_gb_1;

    // File2
    TH1D* hist_b_r2;
    TH1D* hist_b_r2_p5;
    TH1D* hist_b_r2_m5;
    TH1D* hist_b_r2_gm25;
    TH1D* hist_b_r2_gp25;
    TH1D* hist_c_r2;
    TH1D* hist_l_r2;
    TH1D* hist_g_r2;
    TH1D* hist_gc_r2;
    TH1D* hist_gb_r2;
    TH1D* hist_b_2;
    TH1D* hist_b_2_gm25;
    TH1D* hist_b_2_gp25;
    TH1D* hist_b_2_p5;
    TH1D* hist_b_2_m5;
    TH1D* hist_c_2;
    TH1D* hist_l_2;
    TH1D* hist_g_2;
    TH1D* hist_gc_2;
    TH1D* hist_gb_2;

    // File3
    TH1D* hist_b_r3;
    TH1D* hist_b_r3_p5;
    TH1D* hist_b_r3_m5;
    TH1D* hist_c_r3;
    TH1D* hist_l_r3;
    TH1D* hist_g_r3;
    TH1D* hist_gc_r3;
    TH1D* hist_gb_r3;
    TH1D* hist_b_3;
    TH1D* hist_b_3_p5;
    TH1D* hist_b_3_m5;
    TH1D* hist_c_3;
    TH1D* hist_l_3;
    TH1D* hist_g_3;
    TH1D* hist_gc_3;
    TH1D* hist_gb_3;

    TFile *myFile_1     = new TFile(filename_1);
    myFile_1->cd();

    TString flagname;
    if (flag1==1) flagname="pt";
    else if (flag1==2) flagname="eta";
    else if (flag1==3) flagname="pu";
    else if (flag1==4) flagname="hadpt";
    else if (flag1==5) flagname="ptlead";
    else if (flag1==7) flagname="hadptlead";

    hist_b_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    hist_c_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");


    hist_l_r1->Add(hist_g_r1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_r1->Add(hist_gb_r1);
        hist_c_r1->Add(hist_gc_r1);
    }

    TString wpname;
    if (wpflag==0) wpname="l";
    else if (wpflag==1) wpname="m";
    else if (wpflag==2) wpname="t";
    hist_b_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_1         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_l_1->Add(hist_g_1);
    if (wgsplit && flag1!=4 && flag1!=7) {
        hist_b_1->Add(hist_gb_1);
        hist_c_1->Add(hist_gc_1);
    }

    TFile *myFile_2     = new TFile(filename_2);
    myFile_2->cd();

    hist_b_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_b");
    if (flag1==1)  hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_nobtag_b");
    else if (flag1==5)  hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_nobtag_b");
    else if (flag1==7)  hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_hadpt_nobtag_b");
    else hist_b_r2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_"+flagname+"_nobtag_b");
    if (flag1==1)  hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_nobtag_b");
    else if (flag1==5)  hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_nobtag_b");
    else if (flag1==7)  hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_hadpt_nobtag_b");
    else hist_b_r2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_"+flagname+"_nobtag_b");
    hist_c_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_c");
    hist_l_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_l");
    hist_g_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_g");
    hist_gb_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_bfromg");
    hist_gc_r2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_nobtag_cfromg");

    hist_b_r3         = (TH1D*) hist_b_r2->Clone();
    hist_b_r3_p5         = (TH1D*) hist_b_r2_p5->Clone();
    hist_b_r3_m5         = (TH1D*) hist_b_r2_m5->Clone();
    hist_c_r3         = (TH1D*) hist_c_r2->Clone();
    hist_l_r3         = (TH1D*) hist_l_r2->Clone();
    hist_g_r3         = (TH1D*) hist_g_r2->Clone();
    hist_gb_r3         = (TH1D*) hist_gb_r2->Clone();
    hist_gc_r3         = (TH1D*) hist_gc_r2->Clone();


    hist_l_r2->Add(hist_g_r2);
    hist_l_r3->Add(hist_g_r3);

    // r2 with gluon splitting
    hist_b_r2_gm25 = (TH1D*) hist_gb_r2->Clone();
    hist_b_r2_gm25->Scale(0.75);
//    hist_b_r2_gm25->Scale(0.1);
    hist_b_r2_gm25->Add(hist_b_r2);
    hist_b_r2_gp25 = (TH1D*) hist_gb_r2->Clone();
    hist_b_r2_gp25->Scale(1.25);
//    hist_b_r2_gp25->Scale(1.5);
    hist_b_r2_gp25->Add(hist_b_r2);

    hist_b_r2->Add(hist_gb_r2);
    hist_c_r2->Add(hist_gc_r2);
    // r3 without    


    hist_b_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_b");
    if (flag1==1)  hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_"+name+"_"+wpname+"_b"); 
    else if (flag1==5)  hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_"+name+"_"+wpname+"_b"); 
    else if (flag1==7)  hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5lead_hadpt_"+name+"_"+wpname+"_b");
    else hist_b_2_p5         = (TH1D*)gROOT->FindObject("jet_fragp5_"+flagname+"_"+name+"_"+wpname+"_b");
    if (flag1==1)  hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_"+name+"_"+wpname+"_b"); 
    else if (flag1==5)  hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_"+name+"_"+wpname+"_b"); 
    else if (flag1==7)  hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5lead_hadpt_"+name+"_"+wpname+"_b");
    else hist_b_2_m5         = (TH1D*)gROOT->FindObject("jet_fragm5_"+flagname+"_"+name+"_"+wpname+"_b");
    hist_c_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_c");
    hist_l_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_l");
    hist_g_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_g");
    hist_gb_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_bfromg");
    hist_gc_2         = (TH1D*)gROOT->FindObject("jet_"+flagname+"_"+name+"_"+wpname+"_cfromg");

    hist_b_3         = (TH1D*) hist_b_2->Clone();
    hist_b_3_p5      = (TH1D*) hist_b_2_p5->Clone();
    hist_b_3_m5      = (TH1D*) hist_b_2_m5->Clone();
    hist_c_3         = (TH1D*) hist_c_2->Clone();
    hist_l_3         = (TH1D*) hist_l_2->Clone();
    hist_g_3         = (TH1D*) hist_g_2->Clone();
    hist_gb_3         = (TH1D*) hist_gb_2->Clone();
    hist_gc_3         = (TH1D*) hist_gc_2->Clone();

    hist_l_2->Add(hist_g_2);
    hist_l_3->Add(hist_g_3);
    hist_b_2_gm25 = (TH1D*) hist_gb_2->Clone();
    hist_b_2_gm25->Scale(0.75);
//    hist_b_2_gm25->Scale(0.1);
    hist_b_2_gm25->Add(hist_b_2);
    hist_b_2_gp25 = (TH1D*) hist_gb_2->Clone();
    hist_b_2_gp25->Scale(1.25);
//    hist_b_2_gp25->Scale(1.5);
    hist_b_2_gp25->Add(hist_b_2);
    hist_b_2->Add(hist_gb_2);
    hist_c_2->Add(hist_gc_2);


    int nbin_max_1= hist_b_1->GetNbinsX();
    float minx=hist_b_1->GetXaxis()->GetXmin();
    float maxx=hist_b_1->GetXaxis()->GetXmax();
    cout << "nbin_max_1 "<< nbin_max_1 << "   " << minx << "  " << maxx << endl;

     TH1D * hist_clone = (TH1D*)hist_b_1->Clone("hist_clone");
     for (int i=0; i<hist_clone->GetNbinsX()+1; i++) {
        hist_clone->SetBinContent(i,0);
        hist_clone->SetBinError(i,0);
     }
     TH1D * Eff1_b= (TH1D*) hist_clone->Clone("Eff1_b");
     TH1D * Eff1_c= (TH1D*) hist_clone->Clone("Eff1_c");
     TH1D * Eff1_l= (TH1D*) hist_clone->Clone("Eff1_l");
     TH1D * Eff2_b= (TH1D*) hist_clone->Clone("Eff2_b");
     TH1D * Eff2_c= (TH1D*) hist_clone->Clone("Eff2_c");
     TH1D * Eff2_l= (TH1D*) hist_clone->Clone("Eff2_l");
     TH1D * Eff3_b= (TH1D*) hist_clone->Clone("Eff3_b");
     TH1D * Eff3_c= (TH1D*) hist_clone->Clone("Eff3_c");
     TH1D * Eff3_l= (TH1D*) hist_clone->Clone("Eff3_l");
     TH1D * Eff3_b_p5= (TH1D*) hist_clone->Clone("Eff3_b_p5");
     TH1D * Eff3_b_m5= (TH1D*) hist_clone->Clone("Eff3_b_m5");
     TH1D * Eff_no= (TH1D*) hist_clone->Clone("Eff_no");
     TH1D * Eff2_b_gp25= (TH1D*) hist_clone->Clone("Eff2_b_gp25");
     TH1D * Eff2_b_gm25= (TH1D*) hist_clone->Clone("Eff2_b_gp25");


    ComputeEffvsPT(hist_b_r1,hist_c_r1,hist_l_r1,hist_b_1,hist_c_1,hist_l_1,Eff1_b,Eff1_c,Eff1_l, 8) ;
    ComputeEffvsPT(hist_b_r2,hist_c_r2,hist_l_r2,hist_b_2,hist_c_2,hist_l_2,Eff2_b,Eff2_c,Eff2_l, kBlue) ;
    ComputeEffvsPT(hist_b_r3,hist_c_r3,hist_l_r3,hist_b_3,hist_c_3,hist_l_3,Eff3_b,Eff3_c,Eff3_l, 2) ;
    ComputeEffvsPT(hist_b_r3_p5,hist_b_r3_m5,hist_b_r3_p5,hist_b_3_p5,hist_b_3_m5,hist_b_3_p5,Eff3_b_p5,Eff3_b_m5,Eff_no, kOrange-3) ;
    ComputeEffvsPT(hist_b_r2_gp25,hist_b_r2_gm25,hist_b_r2_gp25,hist_b_2_gp25,hist_b_2_gm25, hist_b_2_gp25, Eff2_b_gp25, Eff2_b_gm25, Eff_no, kAzure+8) ;

    TString titleHisti;
    if (flag1==1) titleHisti="jet pT [GeV]";
    else if (flag1==2) titleHisti="jet eta ";
    else if (flag1==3) titleHisti="#PU";
    else if (flag1==4) titleHisti="hadron pT [GeV]";
    else if (flag1==5) titleHisti="leading jet pT [GeV]";
    else if (flag1==7) titleHisti="hadron pT of leading jet[GeV]";
    Eff1_b->GetXaxis()->SetTitle(titleHisti);
    Eff1_l->GetXaxis()->SetTitle(titleHisti);
    Eff1_c->GetXaxis()->SetTitle(titleHisti);


    Eff1_c->SetMaximum(0.6);        
    Eff1_l->SetMaximum(0.35);        
    if (name=="deep") Eff1_l->SetMaximum(0.6);
    if (name=="ctag") Eff1_l->SetMaximum(1.1);
    if (name=="ctag") Eff1_c->SetMaximum(1.);
    if (name=="ctag") Eff1_b->SetMaximum(0.7);
    if (name=="ctag") Eff1_l->SetMinimum(0.005);


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);


    c1->SetFillColor(10);
    c1->cd();
    c1->SetBorderMode(0);  
    c1->SetBorderSize(2);
    c1->SetFrameFillColor(0);
    c1->SetFrameBorderMode(0);

    // FIRST MC & DATA
    TPad *c1_1 = new TPad("canvas_1", "canvas_1",0,0,1.0,1.0);
    c1_1->Draw();
    c1_1->SetFillColor(0);
    c1_1->SetBorderMode(0);
    c1_1->SetBorderSize(2);
    c1_1->SetLeftMargin(0.1461539);
    c1_1->SetRightMargin(0.05384616);
    c1_1->SetTopMargin(0.06831119);
    c1_1->SetBottomMargin(0.1574953);
    c1_1->SetFrameBorderMode(0);
    c1_1->cd(); 
    c1_1->SetGridy();


    TLegend* qw = 0;
//    qw = new TLegend(0.13,0.22,0.33,0.39,NULL,"brNDC"); // Caro
    qw = new TLegend(0.1884615,0.2144213,0.3602564,0.4079696,NULL,"brNDC"); 
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
//  qw->SetBorderSize(0);

    qw->AddEntry(Eff1_b, "ttbar", "p");
    if (flag1!=4 && flag1!=7) qw->AddEntry(Eff2_b, "QCD with gsplit", "p");
    if (flag1!=4 && flag1!=7) qw->AddEntry(Eff2_b_gp25, "variation of gsplit", "l");
    qw->AddEntry(Eff3_b, "QCD without gsplit", "p");
    qw->AddEntry(Eff3_b_p5, "variation of b-frag", "l");

    Eff1_b->SetTitleSize(0.08,"Y");
    Eff1_b->SetTitleOffset(0.65,"Y");  
    Eff1_b->SetTitleOffset(0.81,"Y");
    Eff1_b->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_b->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_b->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_b->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_b->GetYaxis()->SetTitleOffset(0.9);
    Eff1_b->SetMarkerStyle(7);
    Eff2_b->SetMarkerStyle(7);
    Eff2_b_gp25->SetMarkerStyle(7);
    Eff2_b_gm25->SetMarkerStyle(7);
    Eff3_b->SetMarkerStyle(7);
    Eff3_b_p5->SetMarkerStyle(7);
    Eff3_b_m5->SetMarkerStyle(7);
    Eff1_b->SetMarkerSize(4);
    Eff2_b->SetMarkerSize(4);
    Eff2_b_gp25->SetMarkerSize(4);
    Eff2_b_gm25->SetMarkerSize(4);
    Eff3_b->SetMarkerSize(4);
    Eff3_b_p5->SetMarkerSize(4);
    Eff3_b_m5->SetMarkerSize(4);
    Eff1_b->Draw();

    Eff1_b->Draw("same");
    if (flag1!=4 && flag1!=7) Eff2_b->Draw("same");
    if (flag1!=4 && flag1!=7) Eff2_b_gp25->Draw("hist l same");
    if (flag1!=4 && flag1!=7) Eff2_b_gm25->Draw("hist l same");

    Eff3_b->Draw("same");
    Eff3_b_p5->Draw("hist l same");
    Eff3_b_m5->Draw("hist l same");


    TLatex *   tex1 = new TLatex(0.8782051,0.9506641,"#sqrt{s}=13 TeV, 2016");
    tex1->SetNDC();
    tex1->SetTextAlign(31);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.04875);
    tex1->SetLineWidth(2);
    tex1->Draw();
//    TLatex *  tex2 = new TLatex(0.5782051,0.9184061,"CMS Simulation");
    TLatex *  tex2 = new TLatex(0.1935897,0.9089184,"CMS Simulation");
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.065);
    tex2->SetLineWidth(2);
    tex2->Draw();


    qw->Draw();
    TString name_plot="syst_"+flagname+"_b_"+name+wpname+format;
    if (printfunc) name_plot="fit_"+name_plot;
    c1->SaveAs(name_plot);

/*
    TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
    c2->cd();
  c2->SetBorderMode(0);  
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderMode(0);

    TPad *c2_1 = new TPad("canvas_2", "canvas_2",0,0,1.0,1.0);
    c2_1->SetFillColor(0);
    c2_1->SetBorderMode(0);
    c2_1->SetBorderSize(2);
   c2_1->SetLeftMargin(0.1461539);
   c2_1->SetRightMargin(0.05384616);
   c2_1->SetTopMargin(0.06831119);
   c2_1->SetBottomMargin(0.1574953);
    c2_1->SetFrameBorderMode(0);
    c2_1->Draw();
    c2_1->cd();
    c2_1->SetGridy();

    TLegend* qw2 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw2 = new TLegend(0.6666667,0.7343454-0.3,0.8666667,0.9032258-0.3,NULL,"brNDC");
    qw2->AddEntry(Eff1_b, "ttbar", "p");
    if (flag1!=4) qw2->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw2->AddEntry(Eff3_b, "QCD without gsplit", "p");
  qw2->SetBorderSize(1);
  qw2->SetTextFont(62);
  qw2->SetLineColor(1);
  qw2->SetLineStyle(1);
  qw2->SetLineWidth(1);
  qw2->SetFillColor(0);
  qw2->SetFillStyle(1001);
//  qw2->SetBorderSize(0);
    Eff1_c->SetTitleSize(0.08,"Y");
    Eff1_c->SetTitleOffset(0.65,"Y");  
    Eff1_c->SetTitleOffset(0.81,"Y");
    Eff1_c->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_c->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_c->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_c->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_c->GetYaxis()->SetTitleOffset(0.9);

    Eff1_c->SetMarkerStyle(7);
    Eff2_c->SetMarkerStyle(7);
    Eff3_c->SetMarkerStyle(7);
    Eff1_c->SetMarkerSize(2);
    Eff2_c->SetMarkerSize(2);
    Eff3_c->SetMarkerSize(2);
    Eff1_c->Draw("L");
    Eff1_c->Draw("L same");
    if (flag1!=4) Eff2_c->Draw("L same");
    Eff3_c->Draw("L same");
    qw2->Draw();
    tex1->Draw();
    tex2->Draw();
    TString name_plot2="compare_vs_"+flagname+"_c_"+name+wpname+format;
    if (printfunc) name_plot2="fit_"+name_plot2;
    c2->SaveAs(name_plot2);

  
    TCanvas *c3 = new TCanvas("c3", "c3",10,32,782,552);
    c3->cd();
  c3->SetBorderMode(0);  
  c3->SetBorderSize(2);
  c3->SetFrameFillColor(0);
  c3->SetFrameBorderMode(0);
    TPad *c3_1 = new TPad("canvas_3", "canvas_3",0,0,1.0,1.0);
    c3_1->SetFillColor(0);
    c3_1->SetBorderMode(0);
    c3_1->SetBorderSize(2);
   c3_1->SetLeftMargin(0.1461539);
   c3_1->SetRightMargin(0.05384616);
   c3_1->SetTopMargin(0.06831119);
   c3_1->SetBottomMargin(0.1574953);
    c3_1->SetFrameBorderMode(0);
    c3_1->Draw();
    c3_1->cd();
    c3_1->SetGridy();
    c3_1->SetLogy(1);

    TLegend* qw3 = 0;
//    qw2 = new TLegend(0.15,0.75,0.35,0.92);
    qw3 = new TLegend(0.6666667,0.7343454-0.6,0.8666667,0.9032258-0.6,NULL,"brNDC");
    qw3->AddEntry(Eff1_b, "ttbar", "p");
//    qw3->AddEntry(Eff2_b, "QCD with gsplit", "p");
    qw3->AddEntry(Eff3_b, "QCD", "p");
  qw3->SetBorderSize(1);
  qw3->SetTextFont(62);
  qw3->SetLineColor(1);
  qw3->SetLineStyle(1);
  qw3->SetLineWidth(1);
  qw3->SetFillColor(0);
  qw3->SetFillStyle(1001);
    Eff1_l->SetTitleSize(0.08,"Y");
    Eff1_l->SetTitleOffset(0.65,"Y");  
    Eff1_l->SetTitleOffset(0.81,"Y");
    Eff1_l->GetYaxis()->SetLabelSize( 0.05 );
    Eff1_l->GetYaxis()->SetTitleSize( 0.06 );
    Eff1_l->GetXaxis()->SetLabelSize( 0.045 );
    Eff1_l->GetXaxis()->SetTitleSize( 0.055 );
    Eff1_l->GetYaxis()->SetTitleOffset(0.9);
    Eff1_l->SetMarkerStyle(7);
    Eff2_l->SetMarkerStyle(7);
    Eff3_l->SetMarkerStyle(7);
    Eff1_l->SetMarkerSize(2);
    Eff2_l->SetMarkerSize(2);
    Eff3_l->SetMarkerSize(2);
    Eff1_l->Draw("L");
    Eff1_l->Draw("same");
//    Eff2_l->Draw("L same");
    Eff3_l->Draw("L same");
    qw3->Draw(); 
    tex1->Draw();
    tex2->Draw();
    TString name_plot3="compare_vs_"+flagname+"_l_"+name+wpname+format;
    if (printfunc) name_plot3="fit_"+name_plot3;
    c3->SaveAs(name_plot3);
    
*/

}
