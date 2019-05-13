#include "tdrstyle.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TH1D.h"
#include "TMultiGraph.h"
#include "TGraph.h"
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
TString filenameMC = "inclmc_2016_trig40_50_250_pvweight.root";

TString filename1 = "jetht_2016_tot_trig40_50_250_pvweight.root";
TString filename2 = "jetht_2016_runb2f_trig40_50_250.root";
TString filename3 = "jetht_2016_rung2h_trig40_50_250.root";
TString dir4plots="plots/";
    TString jettype="AK4 jets (50 <p_{T}< 250 GeV)" ;
bool btag = false;   
*/

/*
TString filenameMC = "muemc_2016_trig170_200_450_pseudopvweight.root";
TString filename1 = "btag_2016_tot_trig170_200_450.root";
TString filename2 = "btag_2016_runb2f_trig170_200_450.root";
TString filename3 = "btag_2016_rung2h_trig170_200_450.root";
TString dir4plots="plots/";
    TString jettype="AK4 jets (200 <p_{T}< 450 GeV)" ;
bool btag = true;    
*/


TString filenameMC = "muemc_2016_trig40_50_250_pseudopvweight.root";
TString filename3 = "btag_2016_rung2h_trig40_50_250.root";
bool btag = false; 


TString filename4 = "btag_2018_v3.root";
TString filename5 = "btag_2018_v2.root";
TString filename6 = "plot_v1/btag_2018.root";
TString filename7 = "incl_rune_304672.root";
TString filename8 = "pfjet40_50_250_297425.root";


TString qwname3="2016 (runG-runH)";

TString qwname4="2018 315802-316271";
TString qwname5="2018 315489-315801";
TString qwname6="2018 314472-315490";
TString qwname7="RunE (after 304671)";
TString qwname8="P 297425-488";

// comparaison dans Drawdata
//TString filename1b = "jetht500_repair_off.root";
//TString filename2b = "jetht500_repair_on.root";
TString filename1b = "jetht40_repair_off.root";
TString filename2b = "jetht40_repair_on.root";
TString filename1 = filename1b;
TString filename2 = filename2b;

/*
//TString dir4plots="plots_jetht500/";
TString dir4plots="plots_jetht40/";
TString qwname1="off" ;
TString qwname2="on ";
TString jettype="AK4 jets (50 <p_{T}< 250 GeV)" ;
//TString jettype="AK4 jets (525 <p_{T}< 1000 GeV)" ;
*/

//
//
//
// comparaison dans DrawMCCompare
//


/*
//TString filename_1 = "ttbar_nopu_repair_off.root";
//TString filename_2 = "ttbar_nopu_repair_on.root";
TString filename_1 = "ttbar_pu_repair_off.root";
TString filename_2 = "ttbar_pu_repair_on.root";
TString qwname1="off" ;
TString qwname2="on ";
TString labelfile1="repair off";
TString labelfile2="repair on";
//TString dir4plots="plots_ttbar_nopu/";
//TString jettype="ttbar noPU (20 <p_{T}< 500 GeV)" ;
TString dir4plots="plots_ttbar_pu/";
TString jettype="ttbar PU (20 <p_{T}< 500 GeV)" ;
*/




TString filename_1 = "qcd500_repair_off.root";
TString filename_2 = "qcd500_repair_on.root";
//TString filename_1 = "qcd40_repair_off.root";
//TString filename_2 = "qcd40_repair_on.root";
TString labelfile1="repair off";
TString labelfile2="repair on";
TString qwname1="off" ;
TString qwname2="on ";
//TString dir4plots="plots_qcd40/";
//TString jettype="QCD (50 <p_{T}< 250 GeV)" ;
TString dir4plots="plots_qcd500/";
TString jettype="QCD (525 <p_{T}< 1000 GeV)" ;




TString filename = "incl_ctag_full.root";
TString filename2D = "test_2d_rund_mc.root";

bool booname2=true; 
bool booname3=false; 
bool booname4=false;
bool booname5=false;
bool booname6=false;
bool booname7=false;
bool booname8=false;

TString datacaption="297099-297101";



TString adddir = "./";

bool boolfile3=false;
TString filename_3=adddir+"QCD_8P6NoPU.root";
TString labelfile3="QCD 8TeV Pyth6 No PU";

bool boolfile4=false;
TString filename_4=adddir+"QCD_8P6wPU.root";
TString labelfile4="QCD 8TeV Pyth6 w/ PU";


bool boolfile5=false;
TString filename_5=adddir+"QCD_13P8NoPU.root";
TString labelfile5="QCD 13TeV Pyth8 No PU";

bool boolfile6=false;
TString filename_6=adddir+"QCD_13P8wPU.root";
TString labelfile6="QCD 13TeV Pyth8 w/ PU";



bool displayRatio = false;

TString PU = "";



TString title = "CMS Preliminary";


//TString format=".gif"; // .png or .pdf or .gif
TString format=".pdf"; // .png or .pdf or .gif
bool bOverflow=true;
bool web = false;




void Draw(TString name, TString histotitle, bool log, float miny=-1);
void Draw(TString name, TString ytitle, TString histotitle, bool log, float miny=-1);
void Draw2017(TString name, TString ytitle, TString histotitle, bool log, float miny=-1);
void Drawdata(TString name, TString ytitle, TString histotitle, bool log, float miny=-1);
void Drawdata2(TString name, TString ytitle, TString histotitle, bool log, float miny=-1);
void DrawMC(TString name, TString histotitle, bool log);
void DrawMCCompare(TString name, TString histotitle, bool log);
void DrawMCCompare(TString name, TString ytitle,  TString histotitle, bool log, float miny=-1);
void DrawMCgen(TString name, TString histotitle, bool log);
void DrawTagRate(TString name, TString histotitle, bool log);
void Draw2DPlot(TString name, TString histotitle, TString titleX, TString titleY, bool log);
void OverFlowBinFix(TH1D* );
void ModifyBinning(TH1D* histo, int imax);
void DefineHstack(TString filename_x, TString name, TH1D*& hist_fill, THStack * & hs_fill, TH1D* & hist_fill_b, TH1D* & hist_fill_c, TH1D* & hist_fill_l, TH1D* & hist_fill_g, TH1D* & hist_fill_bfromg, TH1D* & hist_fill_cfromg, TH1D* & hist_fill_puu );
void DefineHline(TString filename_x, TString name, TH1D* & hist_line, int iMcolor, float xMsize, int iMstyle, int iLwidth);
void DefineHratio(TString nameRatio, TH1D* & histo_ratio1, TH1D* hnum, TH1D* hdenum, int iMcolor, float xMsize, int iMstyle, int iLwidth );
void DefineHgen(TString filename_x, TString name, TH1D* & hist_fill, int iColor);
void PrintEff(TString name);


void anplot();
void anplot2();

//--------

void DrawCommPlot(bool Draw_track_plots, bool Draw_Nminus1_plots, bool Draw_sv_plots, bool Draw_muons_plots, bool Draw_discriminator_plots , 
                  bool Draw_newdiscriminator_plots, bool Draw_tagRate_plots, bool Draw_2D_plots, bool Draw_pflepton){

    TString action = "mkdir "+dir4plots+"/";
    system(action);
  
    //cout << "Drawing pt, eta, phi plots\n";
    //Draw("jet_multi"    ,"number of jets",1);	    
    DrawMCCompare("jet_pt_all"   ,"pT of all jets",1);	    
    DrawMCCompare("jet_eta"      ,"eta of all jets",	0);    
    DrawMCCompare("jet_phi"      ,"phi of all jets",0);
    DrawMCCompare("track_multi"  ,"number of tracks in the jets", 0);
    //DrawMC("nPV"      ,"# of PV",0);

    //cout << "Drawing tack plots\n";
    if (Draw_track_plots){	      
        DrawMCCompare("track_multi"  ,      "number of tracks in the jets",0);		   
        DrawMCCompare("trk_multi_sel"  ,    "number of selected tracks in the jets",0);	   
        DrawMCCompare("track_chi2"   ,      "normalized #chi^{2} of the tracks"	,1);	   
        DrawMCCompare("track_nHit" ,      "number of hits",1);		   
        DrawMCCompare("track_HPix"   ,      "number of hits in the Pixel",1);		   
        DrawMCCompare("track_len"     ,     "Track decay length",1);				   
        DrawMCCompare("track_dist"    ,     "Track distance to the jet axis"	,1);	   
        DrawMCCompare("track_dz"     ,      "Track IP_dz",1);				   
        DrawMCCompare("track_pt"     ,      "pT of all the tracks",1);			   
        DrawMCCompare("track_pt15"     ,      "pT of all the tracks",1);			   
        //Draw("track_isfromSV",     "Track is from SV",1);			   

        DrawMCCompare("track_IPs"    ,      "3D IP significance of all tracks",1);	   
        DrawMCCompare("track_IPs1tr" ,      "3D IP significance of the first track",1);	   
        DrawMCCompare("track_IPs2tr" ,      "3D IP significance of the second track",1);     
        DrawMCCompare("track_IPs3tr" ,      "3D IP significance of the third track",1);	
        DrawMCCompare("track_IP"     ,      "3D IP of all tracks",1);			   
        DrawMCCompare("track_IP1tr"  ,      "3D IP of the first track"	,1);	   
        DrawMCCompare("track_IP2tr"  ,      "3D IP of the second track",1);		   
        DrawMCCompare("track_IP3tr"  ,      "3D IP of the third track"	,1);	
        DrawMCCompare("track_IP2Ds"	,    "2D IP significance of all tracks"	,1);   
        DrawMCCompare("track_IP2Ds1tr" ,    "2D IP significance of the first track",1);	   
        DrawMCCompare("track_IP2Ds2tr" ,    "2D IP significance of the second track" ,1);    
        DrawMCCompare("track_IP2Ds3tr" ,    "2D IP significance of the third track" ,1);
        DrawMCCompare("track_IP2D"    ,     "2D IP of all tracks",1);			   
        DrawMCCompare("track_IP2D1tr" ,     "2D IP of the first track"	,1);	   
        DrawMCCompare("track_IP2D2tr" ,     "2D IP of the second track",1);		   
        DrawMCCompare("track_IP2D3tr" ,     "2D IP of the third track"	,1);	
        DrawMCCompare("track_IP2Derr" ,     "2D IP error of all tracks",1);				   
        DrawMCCompare("track_IP2Derr1tr" ,  "2D IP error of the first track",1);  	   
        DrawMCCompare("track_IP2Derr2tr" ,  "2D IP error of the second track" ,1);	   
        DrawMCCompare("track_IP2Derr3tr" ,  "2D IP error of the third track",1);  	
        DrawMCCompare("track_IPerr"   ,     "3D IP error of all tracks",1);				   
        DrawMCCompare("track_IPerr1tr"   ,  "3D IP error of the first track" ,1); 	   
        DrawMCCompare("track_IPerr2tr"   ,  "3D IP error of the second track" ,1);	   
        DrawMCCompare("track_IPerr3tr"   ,  "3D IP error of the third track" ,1); 	
	
    }  
    if (Draw_Nminus1_plots){  
        DrawMCCompare("track_chi2_cut"    ,"Normalized #chi^{2} @N-1 step",1);	    
        DrawMCCompare("track_nHit_cut"  ," Number of hits @N-1 step",1);
        DrawMCCompare("track_HPix_cut"    ,"Number of hits in the Pixel @N-1 step",1);  
        DrawMCCompare("track_len_cut"     ,"Decay length @N-1 step",1);		    
        DrawMCCompare("track_dist_cut"    ,"Distance to the jet axis @N-1 step" ,1);  
        DrawMCCompare("track_dz_cut"     , "Transverse IP @N-1 step",1);		    
        DrawMCCompare("track_pt_cut"	   ,"Track pT @N-1 step",1);
        DrawMCCompare("track_pt15_cut"	   ,"Track pT @N-1 step",1);
    }
    if (Draw_sv_plots){

        DrawMCCompare("jet_pt_sv"    ,"pT of jets containing a SV",1);
        DrawMCCompare("sv_multi_0","nr. of SV including bin 0",1); 
        DrawMCCompare("sv_multi","nr. of SV",1);
        DrawMCCompare("sv_mass","SV mass",0);
        DrawMCCompare("sv_mass_3trk","SV mass if #tracks@SV >=3",0);
        DrawMCCompare("sv_chi2norm","SV norm. #chi^{2}",1);
        DrawMCCompare("sv_deltaR_jet","Delta R between the jet and the SV direction.",0);
        DrawMCCompare("sv_deltaR_sumJet","#Delta R between the jet and the SV {p}",0);
        DrawMCCompare("sv_deltaR_sumDir","#Delta R between the SV direction and the SV {p}",0);
        DrawMCCompare("sv_en_ratio","SV energy ratio",0);	
        DrawMCCompare("sv_aboveC","IP2D of the first track above the charm threshold",1);	
        DrawMCCompare("sv_pt","SV p_{T}",1); 	
        DrawMCCompare("sv_eta","SV #eta",0);	
        DrawMCCompare("sv_phi","SV #phi",0);	
        DrawMCCompare("sv_flight3D","SV 3D flight distance",1);	
        DrawMCCompare("sv_flight2D","SV 2D flight distance",1);	
        DrawMCCompare("sv_flight2D_3trk","SV 2D flight dist. if #tracks@SV >=3",1);	
        DrawMCCompare("sv_flight2DSig_3trk","SV 2D flight dist. sig. if #tracks@SV >=3",1);	
        DrawMCCompare("sv_flight3DSig","SV 3D flight distance significance",1);
        DrawMCCompare("sv_flightSig2D","SV 2D flight distance significance",1);
        DrawMCCompare("sv_flight3Derr","SV 3D flight distance error",1);
        DrawMCCompare("sv_flight2Derr","SV 2D flight distance error",1);
        DrawMCCompare("svnTrk","nr. of tracks from a SV",1);	
        DrawMCCompare("svnTrk_firstVxt","nr. of tracks from the first SV",1);
    }
    if (Draw_muons_plots){  
        DrawMCCompare("muon_multi"   ,      "number of muons", 1);       
        DrawMCCompare("muon_multi_sel"   ,  "number of selected muons",1);
        DrawMCCompare("mu_ptrel"     ,      "p_{T} rel. of the muon",0);    
        DrawMCCompare("mu_chi2"      ,      "norm. #chi^{2} of the muon", 1);
        DrawMCCompare("muon_Pt",	     "Muon p_{T}",1);	       
        DrawMCCompare("muon_eta",	     "Muon #eta",0);	       
        DrawMCCompare("muon_phi",	     "Muon #phi",0);	       
        DrawMCCompare("muon_Ip3d",	     "Muon 3D IP",1);	       
        DrawMCCompare("muon_Ip2d",	     "Muon 2D IP",1);	       
        DrawMCCompare("muon_Sip3d",	     "Muon 3D IP significance",1);
        DrawMCCompare("muon_Sip2d",	     "Muon 2D IP significance",1);
        DrawMCCompare("muon_DeltaR",	     "Muon1 #Delta R",0);
  
    } 
    if (Draw_discriminator_plots){  
        DrawMCCompare("TCHE_extended1"       ,"TCHE (extended)",1);    
        DrawMCCompare("TCHP_extended1"       ,"TCHP (extended)",1);    
        DrawMCCompare("discri_ssche0",      "SSVHE Discriminator", 1);
        DrawMCCompare("discri_sschp0",      "SSVHP Discriminator", 1);

        DrawMCCompare("TCHE"	      ,"TCHE Discriminator", 1); 		    
        DrawMCCompare("TCHP"	      ,"TCHP Discriminator",1);  		    
        DrawMCCompare("JP"	      ,"JP Discriminator",1);			    
        DrawMCCompare("JBP"	      ,"JBP Discriminator",1);			    
        DrawMCCompare("SSV"	      ,"SSVHE Discriminator",0);			    
        DrawMCCompare("SSVHP"        ,"SSVHP Discriminator",0); 		    
        DrawMCCompare("CSV"	      ,"CSV Discriminator",1);
  
    }
    if (Draw_newdiscriminator_plots) {
        DrawMCCompare("RetCombSvx"         ,"CSV_v1 Discriminator",1);
        DrawMCCompare("RetCombSvx"         ,"CSV_v1 Discriminator",0);
        DrawMCCompare("CombCSVJP"          ,"CSVJP Discriminator",1);
        DrawMCCompare("CombCSVSL"          ,"CSVSL_v1 Discriminator",1);
        DrawMCCompare("CombCSVJPSL"        ,"CSVJPSL Discriminator",1);
        DrawMCCompare("SoftMu"        ,"Soft Muon Discriminator",1);
        DrawMCCompare("SoftMu"        ,"Soft Muon Discriminator",0);
        DrawMCCompare("SoftEl"        ,"Soft Electron Discriminator",1);
    }
  			    
    if (Draw_tagRate_plots){ 
        DrawTagRate("TCHE_extended1","TCHE (extended)", 1);
        DrawTagRate("TCHP_extended1"," TCHP (extended)", 1);
        DrawTagRate("discri_ssche0","SSVHE (extended)", 1);
        DrawTagRate("discri_sschp0","SSVHP (extended)", 1);

        DrawTagRate("TCHE"	      ,"TCHE Discriminator", 1);
        DrawTagRate("TCHP"	      ,"TCHP Discriminator", 1);
        DrawTagRate("JP"	      ,"JP Discriminator", 1);
        DrawTagRate("JBP"	      ,"JBP Discriminator", 1);
        DrawTagRate("SSV"	      ,"SSVHE Discriminator", 0);
        DrawTagRate("SSVHP"         ,"SSVHP Discriminator", 0);
        DrawTagRate("CSV"	      ,"CSV Discriminator", 1);

  
    }
  
    if (Draw_2D_plots){
        Draw2DPlot("seltrack_vs_jetpt", "nr. of selected tracks as a function of the jet p_{T}", "jet p_{T}","nr. of selected tracks",0);
        Draw2DPlot("sv_mass_vs_flightDist3D", " SV mass as a function of the SV 3D flight distance ","SV 3D flight distance","SV mass",  0);
        Draw2DPlot("avg_sv_mass_vs_jetpt","Avg SV mass as a function of the jet p_{T}","jet p_{T}","Avg SV mass", 0);	       
        Draw2DPlot("sv_deltar_jet_vs_jetpt","#Delta R between the SV and the jet as a function of the jet p_{T}","jet p_{T}","#Delta R between the SV and the jet", 0); 
        Draw2DPlot("sv_deltar_sum_jet_vs_jetpt","#Delta R between the SV and the jet sum as a function of the jet p_{T}","jet p_{T}","#Delta R between the SV and the jet sum", 0);     
        Draw2DPlot("sv_deltar_sum_dir_vs_jetpt","#Delta R between the SV and the jet direction as a function of the jet p_{T}", "jet p_{T}","#Delta R between the SV and the jet direction", 0); 
        Draw2DPlot("muon_ptrel_vs_jetpt","Muon_p{T}^{rel} as a function of the jet p_{T}","jet p_{T}","Muon_p{T}^{rel}",	 0);       
        Draw2DPlot("muon_DeltaR_vs_jetpt","Muon #Delta R as a function of the jet p_{T}","jet p_{T}","Muon #Delta R",  0);	         
    }

    if (Draw_pflepton) {

        DrawMCCompare("pfelectron_multi","number of pfelectron",1);
        DrawMCCompare("pfelectron_pt","pfelectron p_{T}",1);
        DrawMCCompare("pfelectron_eta","pfelectron #eta",0);
        DrawMCCompare("pfelectron_phi","pfelectron #phi", 0);
        DrawMCCompare("pfelectron_Sip","3D IP significance of pfelectron",1);
        DrawMCCompare("pfelectron_ptrel","pT rel. of the pfelectron",0);
        DrawMCCompare("pfelectron_ratio","ratio of pfelectron", 1);
        DrawMCCompare("pfelectron_ratiorel",   "ratioRel of pfelectron",1);
        DrawMCCompare("pfelectron_deltar", "#DeltaR(pfelectron,jet)",0);

        DrawMCCompare("pfmuon_multi","number of pfmuon",1);
        DrawMCCompare("pfmuon_goodquality","quality of pfmuons",0);
        DrawMCCompare("pfmuon_pt","pfmuon p_{T}",1);
        DrawMCCompare("pfmuon_eta","pfmuon #eta",0);
        DrawMCCompare("pfmuon_phi","pfmuon #phi", 0);
        DrawMCCompare("pfmuon_Sip","3D IP significance of pfmuon",1);
        DrawMCCompare("pfmuon_ptrel","pT rel. of the pfmuon",0);
        DrawMCCompare("pfmuon_ratio","ratio of pfmuon", 1);
        DrawMCCompare("pfmuon_ratiorel",   "ratioRel of pfmuon",1);
        DrawMCCompare("pfmuon_deltar", "#DeltaR(pfmuon,jet)",0);

    }

}
void anplot() {

    TString action = "mkdir "+dir4plots+"/";
    system(action);
  
  
    DrawMCCompare("jet_pt_all"   ,"pT of all jets",1);	    

    DrawMCCompare("track_IPs"    ,      "3D IP significance of all tracks",1);	   
    DrawMCCompare("track_IP"     ,      "3D IP of all tracks",1);			   
    DrawMCCompare("track_IPerr"   ,     "3D IP error of all tracks",1);				   
    DrawMCCompare("track_chi2_cut"    ,"Normalized #chi^{2} @N-1 step",1);	    
    DrawMCCompare("track_nHit_cut"  ," Number of hits @N-1 step",1);
    DrawMCCompare("track_HPix_cut"    ,"Number of hits in the Pixel @N-1 step",1);  
    DrawMCCompare("track_len_cut"     ,"Decay length @N-1 step",1);		    
    DrawMCCompare("track_dist_cut"    ,"Distance to the jet axis @N-1 step" ,1);  
    DrawMCCompare("track_dz_cut"     , "IP_dz @N-1 step",1);		    
    DrawMCCompare("track_pt_cut"	   ,"Track pT @N-1 step",1);
    DrawMCCompare("track_pt15_cut"	   ,"Track pT @N-1 step",1);
    DrawMCCompare("track_IP2D_cut"    ,"IP2D @N-1 step",1);

    /*
      DrawMCCompare("sv_multi_0","nr. of SV including bin 0",1); 
      DrawMCCompare("sv_mass","SV mass",0);
      DrawMCCompare("sv_deltaR_jet","Delta R between the jet and the SV direction.",0);
      DrawMCCompare("sv_pt","SV p_{T}",1); 	

      DrawMCCompare("mu_ptrel"     ,      "p_{T} rel. of the muon",0);    
      DrawMCCompare("muon_Pt",	     "Muon p_{T}",1);	       
      DrawMCCompare("muon_Sip3d",	     "Muon 3D IP significance",1);
      DrawMCCompare("muon_DeltaR",	     "Muon1 #Delta R",0);
  
      DrawMCCompare("discri_ssche0",      "SSVHE Discriminator", 1);
      DrawMCCompare("discri_sschp0",      "SSVHP Discriminator", 1);

      DrawMCCompare("TCHE"	      ,"TCHE Discriminator", 1); 		    
      DrawMCCompare("TCHP"	      ,"TCHP Discriminator",1);  		    
      DrawMCCompare("JP"	      ,"JP Discriminator",1);			    
      DrawMCCompare("JBP"	      ,"JBP Discriminator",1);			    
      DrawMCCompare("CSV"	      ,"CSV Discriminator",1);
    */
}
void anplot2() {

    TString action = "mkdir "+dir4plots+"/";
    system(action);
  
  
    DrawMCCompare("CSV"	      ,"CSV Discriminator",1);
    DrawMCCompare("CombCSVSL"          ,"CSVSL_v1 Discriminator",1);
    /*
      DrawMCCompare("RetCombSvx"         ,"CSV_v1 Discriminator",1);
      DrawMCCompare("RetCombSvx"         ,"CSV_v1 Discriminator",0);
      DrawMCCompare("CombCSVJP"          ,"CSVJP Discriminator",1);
      DrawMCCompare("CombCSVJPSL"        ,"CSVJPSL Discriminator",1);
      DrawMCCompare("SoftMu"        ,"Soft Muon Discriminator",1);
      DrawMCCompare("SoftEl"        ,"Soft Electron Discriminator",1);
    */
  			    

}

//--------------------------

void Draw(TString name, TString histotitle, bool log, float miny)
{
  Draw(name, "Entries", histotitle, log, miny);
}
////  Commissioning50ns
void Draw(TString name, TString ytitle, TString histotitle, bool log, float miny)
{

    cout << " name " << name << "     ytitle " << ytitle << "     histotitle " << histotitle << endl;
    cout << " log " << log << "     miny " << miny << endl;
    TH1D* hist_b;
    TH1D* hist_bfromg;
    TH1D* hist_c;
    TH1D* hist_l;

    TH1D* hist_g;
    TH1D* hist_cfromg;
    TH1D* hist_puu;

    TH1D* hist_data;
    TH1D* hist_data1;
    TH1D* hist_data2;
    TH1D* hist_data3;
    TH1D* hist_data4;
    TH1D* hist_data5;
    TH1D* hist_data6;
    TH1D* hist_data7;
    TH1D* hist_data8;

 
 
    TFile *myFile     = new TFile(filenameMC);
 
    myFile->cd();
    hist_b         = (TH1D*)gROOT->FindObject(name+"_b");
    hist_c         = (TH1D*)gROOT->FindObject(name+"_c");
    hist_bfromg    = (TH1D*)gROOT->FindObject(name+"_bfromg");
    hist_l         = (TH1D*)gROOT->FindObject(name+"_l");
    hist_g         = (TH1D*)gROOT->FindObject(name+"_g");
    hist_cfromg         = (TH1D*)gROOT->FindObject(name+"_cfromg");
    hist_puu         = (TH1D*)gROOT->FindObject(name+"_puu");

    TFile *myFile1     = new TFile(filename1);

    myFile1->cd();
    hist_data1      = (TH1D*)gROOT->FindObject(name+"_data");



    if (btag) hist_l->Scale(1.27);
    if (btag) hist_g->Scale(1.27);
    cout << " btag rewighting for hist_l and hist_g " << endl;
/*
    if (btag) hist_l->Scale(1./0.93);
    if (btag) hist_g->Scale(1./0.93);
*/


/*
    //test caro
    float xval;
    float xval2;
//    xval=1.;
    cout << " quelle valeur pour le reweighting des light? "<< endl;
    cin >> xval;
    hist_l->Scale(xval);
    hist_g->Scale(xval);
    cout << " quelle valeur pour le reweighting des c? "<< endl;
    cin >> xval2;
//    xval2=1.5;
    hist_c->Scale(xval2);
    hist_cfromg->Scale(xval2);
*/

    if(booname2) {
    TFile *myFile2     = new TFile(filename2);
    myFile2->cd();
    hist_data2      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    else { hist_data2 = (TH1D*)hist_data1->Clone(); }

    if(booname3) {
    TFile *myFile3     = new TFile(filename3);
    myFile3->cd();
    hist_data3      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname4) {
    TFile *myFile4     = new TFile(filename4);
    myFile4->cd();
    hist_data4      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname5) {
    TFile *myFile5     = new TFile(filename5);
    myFile5->cd();
    hist_data5      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname6) {
    TFile *myFile6     = new TFile(filename6);
    myFile6->cd();
    hist_data6      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname7) {  
    TFile *myFile7     = new TFile(filename7);
    myFile7->cd();
    hist_data7      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname8) {  
    TFile *myFile8     = new TFile(filename8);
    myFile8->cd();
    hist_data8      = (TH1D*)gROOT->FindObject(name+"_data");
    }

    bool ovbin = true;
    for (int i=1;i<10;i++) {
        char ccc[20];
        sprintf(ccc,"bin%d",i);
        TString biccc = ccc;
        if (name==biccc+"_SVmass" ||
            name==biccc+"_sv_flight3DSig" ||
            name==biccc+"_sv_pt" ||
            name==biccc+"_sv_deltaR_jet" ) ovbin= false;
    }

/*
    int imax=16; // 21
    if (name=="trk_multi_sel") {
        ModifyBinning(hist_b,imax);
        ModifyBinning(hist_c,imax);
        ModifyBinning(hist_bfromg,imax);
        ModifyBinning(hist_l,imax);
        ModifyBinning(hist_data,imax);
        ModifyBinning(hist_g,imax);
        ModifyBinning(hist_cfromg,imax);
        ModifyBinning(hist_puu,imax);
    }
*/

    if (name=="pfmuonqual_multi") ovbin= false;
    if (bOverflow && name!="SSV" && name!="SSVHP" && name!="sv_mass" 
        && name!="sv_mass_3trk" && ovbin) {
        OverFlowBinFix(hist_b);
        OverFlowBinFix(hist_c);
        OverFlowBinFix(hist_bfromg);
        OverFlowBinFix(hist_l);
//        OverFlowBinFix(hist_data);
        OverFlowBinFix(hist_g);
        OverFlowBinFix(hist_cfromg);
        OverFlowBinFix(hist_puu);
        OverFlowBinFix(hist_data1);
        if (booname2) OverFlowBinFix(hist_data2);
        if (booname3) OverFlowBinFix(hist_data3);
        if (booname4) OverFlowBinFix(hist_data4);
        if (booname5) OverFlowBinFix(hist_data5);
        if (booname6) OverFlowBinFix(hist_data6);
        if (booname7) OverFlowBinFix(hist_data7);
        if (booname8) OverFlowBinFix(hist_data8);
    }



    TH1D* histo_tot = (TH1D*) hist_b->Clone();
    histo_tot->Sumw2();
    histo_tot ->Add(hist_c);
    histo_tot ->Add(hist_bfromg);
    histo_tot ->Add(hist_l);  
    histo_tot ->Add(hist_g);  
    histo_tot ->Add(hist_cfromg);  
    histo_tot ->Add(hist_puu);  

 

    float scale_f = (hist_data1->Integral())/(hist_b->Integral() + hist_c ->Integral()+ hist_bfromg->Integral() + hist_l->Integral() + hist_g->Integral() + hist_cfromg->Integral() + hist_puu->Integral());

    hist_b       ->Scale(scale_f);
    hist_c       ->Scale(scale_f);
    hist_bfromg  ->Scale(scale_f);
    hist_l       ->Scale(scale_f);
    hist_g       ->Scale(scale_f);
    hist_cfromg       ->Scale(scale_f);
    hist_puu       ->Scale(scale_f);
    histo_tot    ->Scale(scale_f);

    if (name!="prob_DeepFlavourUDS" && name!="prob_DeepFlavourG") {
       hist_l       ->Add(hist_g);
    }
    hist_c       ->Add(hist_cfromg);

    float scale_f2 =1;
    if (booname2) { scale_f2= (hist_data1->Integral())/(hist_data2->Integral()); hist_data2       ->Scale(scale_f2);}
    float scale_f3 =1;
    float scale_f4 =1;
    float scale_f5 =1;
    float scale_f6 =1;
    float scale_f7 =1;
    float scale_f8 =1;
    if (booname3) { scale_f3 = (hist_data1->Integral())/(hist_data3->Integral()); hist_data3       ->Scale(scale_f3); }
    if (booname4) { scale_f4 = (hist_data1->Integral())/(hist_data4->Integral()); hist_data4       ->Scale(scale_f4); }
    if (booname5) { scale_f5 = (hist_data1->Integral())/(hist_data5->Integral()); hist_data5       ->Scale(scale_f5); }
    if (booname6) { scale_f6 = (hist_data1->Integral())/(hist_data6->Integral()); hist_data6       ->Scale(scale_f6); }
    if (booname7) { scale_f7 = (hist_data1->Integral())/(hist_data7->Integral()); hist_data7       ->Scale(scale_f7); }
    if (booname8) { scale_f8 = (hist_data1->Integral())/(hist_data8->Integral()); hist_data8       ->Scale(scale_f8); }


  
  
    TH1D* histo_ratio;

    histo_ratio = (TH1D*) hist_data1->Clone();
    histo_ratio->SetName("histo_ratio");
    histo_ratio->SetTitle("");
  
    histo_ratio->Divide(histo_tot);
  
    hist_data1  ->SetLineWidth(2);
    hist_data1  ->SetMarkerStyle(20);  
    hist_data1  ->SetMarkerSize(0.75); 

/*
 if (booname2 || booname3 || booname4 || booname5 || booname6) {
    hist_c     ->SetFillStyle(3001);
    hist_cfromg     ->SetFillStyle(3001);
    hist_b     ->SetFillStyle(3001);
    hist_bfromg     ->SetFillStyle(3001);
    hist_l     ->SetFillStyle(3001);
    hist_g     ->SetFillStyle(3001);
    hist_puu     ->SetFillStyle(3001);
  }
*/

    hist_c     ->SetFillColor(8);
    hist_b     ->SetFillColor(kRed);
    hist_bfromg->SetFillColor(7);  //Pour merger les contributions --> kRed
    hist_l     ->SetFillColor(kBlue);
    if (name=="prob_DeepFlavourUDS" || name=="prob_DeepFlavourG") {
       hist_g     ->SetFillColor(kBlue-9);
    }
    else {
      hist_g     ->SetFillColor(kBlue);
    }
    hist_cfromg     ->SetFillColor(8);
    hist_puu     ->SetFillColor(kYellow);

    hist_c     ->SetLineColor(1);
    hist_b     ->SetLineColor(1);
    hist_bfromg->SetLineColor(1);  //Pour merger les contributions --> kRed
    hist_l     ->SetLineColor(1);
    if (name=="prob_DeepFlavourUDS" || name=="prob_DeepFlavourG") {
     hist_g     ->SetLineColor(1);
    }
    else {
     hist_g     ->SetLineColor(kBlue);
    }
    hist_cfromg     ->SetLineColor(8);
    hist_puu     ->SetLineColor(1);

  
    histo_tot  ->SetLineColor(1);
  

    THStack *stack = new THStack("stack","stack");
  
    stack      ->Add(hist_b);
    stack      ->Add(hist_bfromg);
//    stack      ->Add(hist_cfromg);
    stack      ->Add(hist_c);
    stack      ->Add(hist_puu);
    if (name=="prob_DeepFlavourUDS" || name=="prob_DeepFlavourG") {
       stack      ->Add(hist_g);
    }
    // otherwise is added in hist_l before
    stack      ->Add(hist_l);

    TH1D* histo_ratio2;
    TH1D* histo_ratio3;
    TH1D* histo_ratio4;
    TH1D* histo_ratio5;
    TH1D* histo_ratio6;
    TH1D* histo_ratio7;
    TH1D* histo_ratio8;
    if(booname2) {histo_ratio2 = (TH1D*) hist_data2->Clone();
     histo_ratio2->SetName("histo_ratio2");
     histo_ratio2->SetTitle("");
//     histo_ratio2->Divide(hist_data1);
     histo_ratio2->Divide(histo_tot);
    }
    if (booname3)  histo_ratio3 = (TH1D*) hist_data3->Clone();
    if (booname4)  histo_ratio4 = (TH1D*) hist_data4->Clone();
    if (booname5)  histo_ratio5 = (TH1D*) hist_data5->Clone();
    if (booname6)  histo_ratio6 = (TH1D*) hist_data6->Clone();
    if (booname7)  histo_ratio7 = (TH1D*) hist_data7->Clone();
    if (booname8)  histo_ratio8 = (TH1D*) hist_data8->Clone();
    if (booname3)  histo_ratio3->Divide(histo_tot);
    if (booname4)  histo_ratio4->Divide(histo_tot);
    if (booname5)  histo_ratio5->Divide(histo_tot);
    if (booname6)  histo_ratio6->Divide(histo_tot);
    if (booname7)  histo_ratio7->Divide(histo_tot);
/*
    if (booname3)  histo_ratio3->Divide(hist_data1);
    if (booname4)  histo_ratio4->Divide(hist_data1);
    if (booname5)  histo_ratio5->Divide(hist_data1);
    if (booname6)  histo_ratio6->Divide(hist_data1);
    if (booname7)  histo_ratio7->Divide(hist_data1);
    if (booname8)  histo_ratio8->Divide(hist_data1);
*/

    if(booname2) {
    hist_data2  ->SetMarkerStyle(20); //Caro 24
    hist_data2  ->SetMarkerSize(0.75);
//    hist_data2  ->SetLineColor(2);
//    hist_data2  ->SetMarkerColor(2);
    hist_data2  ->SetLineColor(kPink+6);
    hist_data2  ->SetMarkerColor(kPink+6);
    histo_ratio2->SetMarkerStyle(20);
    histo_ratio2->SetMarkerSize(0.75);
//    histo_ratio2  ->SetLineColor(2);
//    histo_ratio2  ->SetMarkerColor(2);
    histo_ratio2  ->SetLineColor(kPink+6);
    histo_ratio2  ->SetMarkerColor(kPink+6);
    }
   if (booname3) {
       hist_data3->SetMarkerStyle(20);
       hist_data3->SetMarkerSize(0.75);
       hist_data3->SetLineColor(kAzure-4);
       hist_data3->SetMarkerColor(kAzure-4);
       histo_ratio3->SetMarkerStyle(20);
       histo_ratio3->SetMarkerSize(0.75);
       histo_ratio3->SetLineColor(kAzure-4);
       histo_ratio3->SetMarkerColor(kAzure-4);
    }
    if (booname4) {
       hist_data4->SetMarkerStyle(23);
       hist_data4->SetMarkerSize(0.75);
       hist_data4->SetLineColor(13);
       hist_data4->SetMarkerColor(13);
       histo_ratio4->SetMarkerStyle(23);
       histo_ratio4->SetMarkerSize(0.75);
       histo_ratio4->SetLineColor(13);
       histo_ratio4->SetMarkerColor(13);
    }
    if (booname5) {
       hist_data5->SetMarkerStyle(33);
       hist_data5->SetMarkerSize(0.75);
       hist_data5->SetLineColor(6);
       hist_data5->SetMarkerColor(6);
       histo_ratio5->SetMarkerStyle(33);
       histo_ratio5->SetMarkerSize(0.75);
       histo_ratio5->SetLineColor(6);
       histo_ratio5->SetMarkerColor(6);
    }
    if (booname6) {
       hist_data6->SetMarkerStyle(29);
       hist_data6->SetMarkerSize(0.75);
       hist_data6->SetLineColor(7);
       hist_data6->SetMarkerColor(7);
       histo_ratio6->SetMarkerStyle(29);
       histo_ratio6->SetMarkerSize(0.75);
       histo_ratio6->SetLineColor(7);
       histo_ratio6->SetMarkerColor(7);
    }
    if (booname7) {
       hist_data7->SetMarkerStyle(33);
       hist_data7->SetMarkerSize(0.75);
       hist_data7->SetLineColor(16);
       hist_data7->SetMarkerColor(16);
       histo_ratio7->SetMarkerStyle(33);
       histo_ratio7->SetMarkerSize(0.75);
       histo_ratio7->SetLineColor(16);
       histo_ratio7->SetMarkerColor(16);
    }
    if (booname8) {
       hist_data8->SetMarkerStyle(33);
       hist_data8->SetLineColor(13);
       hist_data8->SetMarkerColor(13);
       histo_ratio8->SetLineColor(13);
       histo_ratio8->SetMarkerColor(13);
    }



    setTDRStyle();
    gStyle->SetErrorX(0.);

  
    TCanvas *c1 = new TCanvas(name, name,10,32,782,552);
    c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    c1->  cd();   
  

    TPad* canvas_1 = new TPad("canvas"+name, "canvas"+name,0,0.23,1.0,0.98);
    canvas_1 ->Draw();
  canvas_1->SetFillColor(0);
  canvas_1->SetBorderMode(0);
  canvas_1->SetBorderSize(2);
  canvas_1->SetTopMargin(0.065);
  canvas_1->SetFrameBorderMode(0);
    canvas_1 ->cd();
 
    canvas_1->SetLogy(log);
 
    if (!log) stack->SetMaximum( stack->GetMaximum()*2);
    else stack->SetMaximum( stack->GetMaximum()*5000);

    if (name=="trk_multi_sel" && log) stack->SetMaximum( stack->GetMaximum()*50000);
    if (miny==-1) {
      if (log) stack->SetMinimum(0.1);
      else  stack->SetMinimum(0.); 
    }
    else {
      stack->SetMinimum(miny);
    }

    stack    ->Draw("hist");  
  
    stack    ->GetHistogram()->GetXaxis()->SetTitle(name);
    stack    ->GetHistogram()->GetYaxis()->SetTitle(ytitle);

    stack    ->GetHistogram()->SetTitleSize(0.08,"Y");
    stack    ->GetHistogram()->SetTitleOffset(0.65,"Y"); 
  stack->GetHistogram()->SetTitleOffset(0.81,"Y");
  stack->GetHistogram()->GetYaxis()->SetLabelSize( 0.05 );
  stack->GetHistogram()->GetYaxis()->SetTitleSize( 0.06 );
    if (name=="sv_mass" || name=="tagvarCSV_vertexmass_cat0") stack    ->GetHistogram()->SetTitleOffset(0.91,"Y");
    hist_data1->Draw("same E1X0");
   if (booname2) {
    hist_data2->Draw("same E1X0");
    }

    if (booname3) { hist_data3->Draw("same E1X0"); }
    if (booname4) { hist_data4->Draw("same E1X0"); }
    if (booname5) { hist_data5->Draw("same E1X0"); }
    if (booname6) { hist_data6->Draw("same E1X0"); }
    if (booname7) { hist_data7->Draw("same E1X0"); }
    if (booname8) { hist_data8->Draw("same E1X0"); }

    hist_data1->Draw("same E1X0");


    int move_legend=0;
    if (name=="jet_phi" || name=="sv_phi" || name=="muon_phi" || name=="pfelectron_phi" || name=="pfmuon_phi") move_legend=1;
    if (btag) {
        if (name=="CombCSVJPSL" || name=="CombCSVSL" || (name=="SoftMu" && !log) ) move_legend=2;
        if (name=="CSV" || name=="CombCSVJP" || (name=="RetCombSvx" && !log) ) move_legend=3;
        if ((name=="RetCombSvx" || name=="SoftMu" ) && log) move_legend=1;
    }
    if (log && name=="sv_en_ratio" ) move_legend=1;
    TLegend* qw;
  qw = new TLegend(0.65,0.60,0.95,0.90,NULL,"brNDC");
//    qw->AddEntry(hist_data,     datacaption,                       "ep");
    qw->AddEntry(hist_b,        "b quark"           ,         "f");
    qw->AddEntry(hist_c,        "c quark"           ,         "f");
  //  qw->AddEntry(hist_cfromg,   "c from g split"           ,         "f");
    if (name=="prob_DeepFlavourUDS" || name=="prob_DeepFlavourG") {
      qw->AddEntry(hist_l,        "uds quark"     ,    "f");
      qw->AddEntry(hist_g,        "gluon"     ,    "f");
    }
    else {
      qw->AddEntry(hist_l,        "uds quark or gluon"     ,    "f");
    }
  //  qw->AddEntry(hist_g,        "gluon"     ,    "f");
    qw->AddEntry(hist_bfromg,   "b from gluon splitting"     ,"f");
    qw->AddEntry(hist_puu,        "pile-up"     ,    "f");
    qw->AddEntry(hist_data1,     qwname1,                       "ep");
    if (booname2) qw->AddEntry(hist_data2,     qwname2           ,         "ep");
    if (booname3) qw->AddEntry(hist_data3,      qwname3          ,         "ep");
    if (booname4) qw->AddEntry(hist_data4,      qwname4          ,         "ep");
    if (booname5) qw->AddEntry(hist_data5,      qwname5          ,         "ep");
    if (booname7) qw->AddEntry(hist_data7,      qwname7          ,         "ep");
    if (booname6) qw->AddEntry(hist_data6,      qwname6          ,         "ep");
    if (booname8) qw->AddEntry(hist_data8,      qwname8          ,         "ep");

  //
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
  qw->SetBorderSize(0);


 
    qw->SetFillColor(0);
    qw->Draw();

/*
  int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
  int iPos = 11 ;

  CMS_lumi( canvas_1, iPeriod, iPos );
*/
//   TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV, 50ns");
TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.89,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.05681);
   tex->SetLineWidth(2);
   tex->Draw();

  
  
   TString sample = "";
//     if (filename.Contains("pfsel")) sample += "Multijets" ;
//     else if (filename.Contains("musel")) sample += "Muon enriched QCD" ;
//     sample += "Multijets" ;
     if (btag) {
         sample += "Muon enriched QCD" ;
     }
     else {
         sample += "Multijets" ;
     }

    TLatex *tex1 = new TLatex(0.20,0.74,sample);
    tex1->SetNDC();
    tex1->SetTextAlign(13);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.055);
    tex1->SetLineWidth(2);
    tex1->Draw();


    TLatex *tex2 = new TLatex(0.20,0.68,jettype);
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.055);
    tex2->SetLineWidth(2);
    tex2->Draw();


     canvas_1->Modified();


    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->SetFillColor(0);
    canvas_2->SetBorderMode(0);
    canvas_2->SetBorderSize(2);
    canvas_2->SetGridy();
    canvas_2->SetBottomMargin(0.31);
    canvas_2->SetFrameBorderMode(0);

    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();
  
    histo_ratio->SetMarkerStyle(20);
    histo_ratio->SetMarkerSize(0.75);
    histo_ratio->SetLineWidth(2);

 
//    histo_ratio->GetYaxis()->SetTitle("ratio");
    histo_ratio->GetYaxis()->SetTitle("Data/MC");
    histo_ratio->GetXaxis()->SetTitle(histotitle);
    histo_ratio->GetYaxis()->SetNdivisions( 505 );

    histo_ratio->SetTitleOffset(0.9,"X");
    histo_ratio->SetTitleOffset(0.31,"Y");
    double labelsizex=0.12;
    double labelsizey=0.12;
    double titlesizex=0.15;
    double titlesizey=0.14;

    histo_ratio->GetXaxis()->SetLabelSize( labelsizex );
    histo_ratio->GetXaxis()->SetTitleSize( titlesizex );
    histo_ratio->GetYaxis()->SetLabelSize( labelsizey );
    histo_ratio->GetYaxis()->SetTitleSize( titlesizey );


    histo_ratio->SetMinimum(0.4);
    histo_ratio->SetMaximum(1.6);
    histo_ratio->Draw("E1X0");

    if (booname2) histo_ratio2->Draw("E1X0 same");
    if (booname3) histo_ratio3->Draw("E1X0 same");
    if (booname4) histo_ratio4->Draw("E1X0 same");
    if (booname5) histo_ratio5->Draw("E1X0 same");
    if (booname6) histo_ratio6->Draw("E1X0 same");
    if (booname7) histo_ratio7->Draw("E1X0 same");
    if (booname8) histo_ratio8->Draw("E1X0 same");

    histo_ratio->Draw("E1X0 same");

    c1->cd();  
  

    TString name_plot=name+"_Linear"+format; 
    if(log) name_plot=name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);

    TString name_plot3=name+"_Linear.pdf";
    if(log) name_plot3=name+"_Log.pdf";
    c1->SaveAs(dir4plots+"/"+name_plot3);



/*
    if (log && web) {  // save also _Linear for web
        canvas_1 ->cd();
        canvas_1->SetLogy(false);
        c1->cd();
        c1->SaveAs(dir4plots+"/"+name+"_Linear"+format);
        c1->SaveAs(dir4plots+"/"+name+"_Linear.pdf");
    }
*/




}
void Draw2017(TString name, TString ytitle, TString histotitle, bool log, float miny)
{

    TH1D* hist_b;
    TH1D* hist_bfromg;
    TH1D* hist_c;
    TH1D* hist_l;

    TH1D* hist_g;
    TH1D* hist_cfromg;
    TH1D* hist_puu;

    TH1D* hist_data;
    TH1D* hist_data4;
    TH1D* hist_data5;
 
 
    TFile *myFile     = new TFile(filenameMC);
 
    myFile->cd();
    hist_b         = (TH1D*)gROOT->FindObject(name+"_b");
    hist_c         = (TH1D*)gROOT->FindObject(name+"_c");
    hist_bfromg    = (TH1D*)gROOT->FindObject(name+"_bfromg");
    hist_l         = (TH1D*)gROOT->FindObject(name+"_l");
    hist_g         = (TH1D*)gROOT->FindObject(name+"_g");
    hist_cfromg         = (TH1D*)gROOT->FindObject(name+"_cfromg");
    hist_puu         = (TH1D*)gROOT->FindObject(name+"_puu");

    TFile *myFile2     = new TFile(filename1);
    myFile2->cd();
    hist_data      = (TH1D*)gROOT->FindObject(name+"_data");
    TFile *myFile4     = new TFile(filename2);
    myFile4->cd();
    hist_data4     = (TH1D*)gROOT->FindObject(name+"_data");
    TFile *myFile5     = new TFile(filename3);
    myFile5->cd();
    hist_data5     = (TH1D*)gROOT->FindObject(name+"_data");
/*
    if (btag) hist_l->Scale(1.27);
    if (btag) hist_g->Scale(1.27);
    cout << " btag rewighting for hist_l and hist_g " << endl;
    if (btag) hist_l->Scale(1./0.93);
    if (btag) hist_g->Scale(1./0.93);
*/


    bool ovbin = true;
    for (int i=1;i<10;i++) {
        char ccc[20];
        sprintf(ccc,"bin%d",i);
        TString biccc = ccc;
        if (name==biccc+"_SVmass" ||
            name==biccc+"_sv_flight3DSig" ||
            name==biccc+"_sv_pt" ||
            name==biccc+"_sv_deltaR_jet" ) ovbin= false;
    }

    if (bOverflow && name!="SSV" && name!="SSVHP" && name!="sv_mass" 
        && name!="sv_mass_3trk" && ovbin) {
        OverFlowBinFix(hist_b);
        OverFlowBinFix(hist_c);
        OverFlowBinFix(hist_bfromg);
        OverFlowBinFix(hist_l);
        OverFlowBinFix(hist_data);
        OverFlowBinFix(hist_data4);
        OverFlowBinFix(hist_data5);
        OverFlowBinFix(hist_g);
        OverFlowBinFix(hist_cfromg);
        OverFlowBinFix(hist_puu);
    }



    TH1D* histo_tot = (TH1D*) hist_b->Clone();
    histo_tot->Sumw2();
    histo_tot ->Add(hist_c);
    histo_tot ->Add(hist_bfromg);
    histo_tot ->Add(hist_l);  
    histo_tot ->Add(hist_g);  
    histo_tot ->Add(hist_cfromg);  
    histo_tot ->Add(hist_puu);  

 

    float scale_f = (hist_data->Integral())/(hist_b->Integral() + hist_c ->Integral()+ hist_bfromg->Integral() + hist_l->Integral() + hist_g->Integral() + hist_cfromg->Integral() + hist_puu->Integral());

    hist_b       ->Scale(scale_f);
    hist_c       ->Scale(scale_f);
    hist_bfromg  ->Scale(scale_f);
    hist_l       ->Scale(scale_f);
    hist_g       ->Scale(scale_f);
    hist_cfromg       ->Scale(scale_f);
    hist_puu       ->Scale(scale_f);
    histo_tot    ->Scale(scale_f);

    float scale_f4 = (hist_data->Integral())/(hist_data4->Integral());
    float scale_f5 = (hist_data->Integral())/(hist_data5->Integral());
    if (hist_data->GetXaxis()->GetBinUpEdge(hist_data->GetNbinsX()) != hist_data4->GetXaxis()->GetBinUpEdge(hist_data4->GetNbinsX())) {
       cout << "name histo ALERT " << name << endl;
       cout << "xmax " <<  hist_data->GetXaxis()->GetBinUpEdge(hist_data->GetNbinsX()) << "   "   << hist_data4->GetXaxis()->GetBinUpEdge(hist_data4->GetNbinsX()) << endl;
    }
    if (hist_data->GetNbinsX()!=hist_data4->GetNbinsX())  {
       cout << "name histo ALERT " << name << endl;
       cout << "not the same bin number" << hist_data->GetNbinsX() << " "  << hist_data4->GetNbinsX() <<  endl;
       cout << "xmax " <<  hist_data->GetXaxis()->GetBinUpEdge(hist_data->GetNbinsX()) << "   "   << hist_data4->GetXaxis()->GetBinUpEdge(hist_data4->GetNbinsX()) << endl;
      if (hist_data->GetXaxis()->GetBinUpEdge(hist_data->GetNbinsX()) == hist_data4->GetXaxis()->GetBinUpEdge(hist_data4->GetNbinsX()) ) scale_f4/=hist_data->GetNbinsX()/hist_data4->GetNbinsX();
    }
    hist_data4->Scale(scale_f4);
    hist_data5->Scale(scale_f5);
  
  
    TH1D* histo_ratio;
    histo_ratio = (TH1D*) hist_data->Clone();
    histo_ratio->SetName("histo_ratio");
    histo_ratio->SetTitle("");
  
    histo_ratio->Divide(histo_tot);
    TH1D* histo_ratio4;
    histo_ratio4 = (TH1D*) hist_data4->Clone();
    histo_ratio4->Divide(histo_tot);
    TH1D* histo_ratio5;
    histo_ratio5 = (TH1D*) hist_data5->Clone();
    histo_ratio5->Divide(histo_tot);
  
    hist_data  ->SetLineWidth(2);
    hist_data  ->SetMarkerStyle(20);  
    hist_data  ->SetMarkerSize(0.75); 
    hist_data5  ->SetLineWidth(2);
    hist_data5  ->SetMarkerStyle(33);  
//    hist_data5  ->SetMarkerSize(0.75); 
    hist_data5  ->SetMarkerColor(2); 
    hist_data5  ->SetLineColor(2); 
    hist_data4  ->SetLineWidth(2);
    hist_data4  ->SetMarkerStyle(25);  
//    hist_data4  ->SetMarkerSize(0.75); 
    hist_data4  ->SetMarkerColor(13); 
    hist_data4  ->SetLineColor(13); 


    hist_c     ->SetFillColor(8);
    hist_b     ->SetFillColor(kRed);
    hist_bfromg->SetFillColor(7);  //Pour merger les contributions --> kRed
    hist_l     ->SetFillColor(kBlue);
    hist_g     ->SetFillColor(kBlue);
    hist_cfromg     ->SetFillColor(8);
    hist_puu     ->SetFillColor(kYellow);

    hist_c     ->SetLineColor(1);
    hist_b     ->SetLineColor(1);
    hist_bfromg->SetLineColor(1);  //Pour merger les contributions --> kRed
    hist_l     ->SetLineColor(1);
    hist_g     ->SetLineColor(kBlue);
    hist_cfromg     ->SetLineColor(8);
    hist_puu     ->SetLineColor(1);

  
    histo_tot  ->SetLineColor(1);
  

    THStack *stack = new THStack("stack","stack");
  
    stack      ->Add(hist_b);
    stack      ->Add(hist_bfromg);
    stack      ->Add(hist_cfromg);
    stack      ->Add(hist_c);
    stack      ->Add(hist_puu);
    stack      ->Add(hist_g);
    stack      ->Add(hist_l);



    setTDRStyle();
    gStyle->SetErrorX(0.);

  
    TCanvas *c1 = new TCanvas(name, name,10,32,782,552);
    c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    c1->  cd();   
  

    TPad* canvas_1 = new TPad("canvas"+name, "canvas"+name,0,0.23,1.0,0.98);
    canvas_1 ->Draw();
  canvas_1->SetFillColor(0);
  canvas_1->SetBorderMode(0);
  canvas_1->SetBorderSize(2);
  canvas_1->SetTopMargin(0.065);
  canvas_1->SetFrameBorderMode(0);
    canvas_1 ->cd();
 
    canvas_1->SetLogy(log);
 
    if (!log) stack->SetMaximum( stack->GetMaximum()*2);
    else stack->SetMaximum( stack->GetMaximum()*5000);

    if (name=="trk_multi_sel" && log) stack->SetMaximum( stack->GetMaximum()*50000);
    if (miny==-1) {
      if (log) stack->SetMinimum(0.1);
      else  stack->SetMinimum(0.); 
    }
    else {
      stack->SetMinimum(miny);
    }

    stack    ->Draw("hist");  
  
    stack    ->GetHistogram()->GetXaxis()->SetTitle(name);
    stack    ->GetHistogram()->GetYaxis()->SetTitle(ytitle);

    stack    ->GetHistogram()->SetTitleSize(0.08,"Y");
    stack    ->GetHistogram()->SetTitleOffset(0.65,"Y"); 
  stack->GetHistogram()->SetTitleOffset(0.81,"Y");
  stack->GetHistogram()->GetYaxis()->SetLabelSize( 0.05 );
  stack->GetHistogram()->GetYaxis()->SetTitleSize( 0.06 );
    if (name=="sv_mass" || name=="tagvarCSV_vertexmass_cat0") stack    ->GetHistogram()->SetTitleOffset(0.91,"Y");
    hist_data->Draw("same E1X0");
    hist_data4->Draw("same E1X0");
    hist_data5->Draw("same E1X0");


    int move_legend=0;
    if (name=="jet_phi" || name=="sv_phi" || name=="muon_phi" || name=="pfelectron_phi" || name=="pfmuon_phi") move_legend=1;
    if (btag) {
        if (name=="CombCSVJPSL" || name=="CombCSVSL" || (name=="SoftMu" && !log) ) move_legend=2;
        if (name=="CSV" || name=="CombCSVJP" || (name=="RetCombSvx" && !log) ) move_legend=3;
        if ((name=="RetCombSvx" || name=="SoftMu" ) && log) move_legend=1;
    }
    if (log && name=="sv_en_ratio" ) move_legend=1;
    TLegend* qw;
  qw = new TLegend(0.65,0.60,0.95,0.90,NULL,"brNDC");
    qw->AddEntry(hist_data,     datacaption,                       "ep");
    qw->AddEntry(hist_data4,     qwname2,                       "ep");
    qw->AddEntry(hist_data5,     qwname3,                       "ep");
    qw->AddEntry(hist_b,        "b quark"           ,         "f");
    qw->AddEntry(hist_c,        "c quark"           ,         "f");
  //  qw->AddEntry(hist_cfromg,   "c from g split"           ,         "f");
    qw->AddEntry(hist_l,        "uds quark or gluon"     ,    "f");
  //  qw->AddEntry(hist_g,        "gluon"     ,    "f");
    qw->AddEntry(hist_bfromg,   "b from gluon splitting"     ,"f");
  //  qw->AddEntry(hist_puu,        "pile-up"     ,    "f");
  //
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
  qw->SetBorderSize(0);


 
    qw->SetFillColor(0);
    qw->Draw();

/*
  int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
  int iPos = 11 ;

  CMS_lumi( canvas_1, iPeriod, iPos );
*/
//   TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV, 50ns");
TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV, 2017");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.89,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.05681);
   tex->SetLineWidth(2);
   tex->Draw();

  
  
   TString sample = "";
//     if (filename.Contains("pfsel")) sample += "Multijets" ;
//     else if (filename.Contains("musel")) sample += "Muon enriched QCD" ;
     sample += "Multijets" ;

    TLatex *tex1 = new TLatex(0.20,0.74,sample);
    tex1->SetNDC();
    tex1->SetTextAlign(13);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.055);
    tex1->SetLineWidth(2);
    tex1->Draw();


    TLatex *tex2 = new TLatex(0.20,0.68,jettype);
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.055);
    tex2->SetLineWidth(2);
    tex2->Draw();


     canvas_1->Modified();


    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->SetFillColor(0);
    canvas_2->SetBorderMode(0);
    canvas_2->SetBorderSize(2);
    canvas_2->SetGridy();
    canvas_2->SetBottomMargin(0.31);
    canvas_2->SetFrameBorderMode(0);

    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();
  
    histo_ratio->SetMarkerStyle(20);
    histo_ratio->SetMarkerSize(0.75);
    histo_ratio->SetLineWidth(2);
    histo_ratio5->SetMarkerStyle(33);
//    histo_ratio5->SetMarkerSize(0.75);
    histo_ratio5->SetLineWidth(2);
    histo_ratio5->SetLineColor(2);
    histo_ratio5->SetMarkerColor(2);
    histo_ratio4->SetMarkerStyle(25);
//    histo_ratio4->SetMarkerSize(0.75);
    histo_ratio4->SetLineWidth(2);
    histo_ratio4->SetLineColor(13);
    histo_ratio4->SetMarkerColor(13);

 
    histo_ratio->GetYaxis()->SetTitle("Data/MC");
    histo_ratio->GetXaxis()->SetTitle(histotitle);
    histo_ratio->GetYaxis()->SetNdivisions( 505 );

    histo_ratio->SetTitleOffset(0.9,"X");
    histo_ratio->SetTitleOffset(0.31,"Y");
    double labelsizex=0.12;
    double labelsizey=0.12;
    double titlesizex=0.15;
    double titlesizey=0.14;

    histo_ratio->GetXaxis()->SetLabelSize( labelsizex );
    histo_ratio->GetXaxis()->SetTitleSize( titlesizex );
    histo_ratio->GetYaxis()->SetLabelSize( labelsizey );
    histo_ratio->GetYaxis()->SetTitleSize( titlesizey );


    histo_ratio->SetMinimum(0.);
    histo_ratio->SetMaximum(2.);
    histo_ratio->Draw("E1X0");
    histo_ratio4->Draw("same E1X0");
    histo_ratio5->Draw("same E1X0");

    c1->cd();  
  
    TString name_plot=name+"_Linear"+format; 
    if(log) name_plot=name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);
    TString name_plot3=name+"_Linear.pdf";
    if(log) name_plot3=name+"_Log.pdf";
    c1->SaveAs(dir4plots+"/"+name_plot3);

    if (log && web) {  // save also _Linear for web
        canvas_1 ->cd();
        canvas_1->SetLogy(false);
        c1->cd();
        c1->SaveAs(dir4plots+"/"+name+"_Linear"+format);
    }




}

void Drawdata(TString name, TString ytitle, TString histotitle, bool log, float miny)
{

    cout << " name " << name << "     ytitle " << ytitle << "     histotitle " << histotitle << endl;
    cout << " log " << log << "     miny " << miny << endl;
    TH1D* hist_data1;
    TH1D* hist_data2;
 
 
    TFile *myFile     = new TFile(filename1b);
    myFile->cd();
    hist_data1      = (TH1D*)gROOT->FindObject(name+"_data");

    TFile *myFile2     = new TFile(filename2b);
    myFile2->cd();
    hist_data2      = (TH1D*)gROOT->FindObject(name+"_data");
 
    bool ovbin = true;
    for (int i=1;i<10;i++) {
        char ccc[20];
        sprintf(ccc,"bin%d",i);
        TString biccc = ccc;
        if (name==biccc+"_SVmass" ||
            name==biccc+"_sv_flight3DSig" ||
            name==biccc+"_sv_pt" ||
            name==biccc+"_sv_deltaR_jet" ) ovbin= false;
    }

    if (bOverflow && name!="SSV" && name!="SSVHP" && name!="sv_mass" 
        && name!="sv_mass_3trk" && ovbin) {
        OverFlowBinFix(hist_data1);
        OverFlowBinFix(hist_data2);
    }



    float scale_f = (hist_data1->Integral())/(hist_data2->Integral());
//    if (name=="jet_eta") scale_f/=2;
    if (hist_data1->GetNbinsX()!=hist_data2->GetNbinsX())  {
       cout << "not the same bin number" << hist_data1->GetNbinsX() << " "  << hist_data2->GetNbinsX() <<  endl;
       cout << "xmax " <<  hist_data1->GetXaxis()->GetBinUpEdge(hist_data1->GetNbinsX()) << "   "   << hist_data2->GetXaxis()->GetBinUpEdge(hist_data2->GetNbinsX()) << endl;
      if (hist_data1->GetXaxis()->GetBinUpEdge(hist_data1->GetNbinsX()) == hist_data2->GetXaxis()->GetBinUpEdge(hist_data2->GetNbinsX()) ) scale_f/=hist_data1->GetNbinsX()/hist_data2->GetNbinsX();
    }
    
    // no scaling !
    //hist_data2       ->Scale(scale_f);

    TH1D* histo_ratio;
    histo_ratio = (TH1D*) hist_data2->Clone();
    histo_ratio->SetName("histo_ratio");
    histo_ratio->SetTitle("");
    histo_ratio->Divide(hist_data1);
  
    hist_data2  ->SetLineWidth(2);
    hist_data2  ->SetMarkerStyle(20);  
    hist_data2  ->SetMarkerSize(0.75); 
    hist_data1  ->SetLineWidth(2);
    hist_data1  ->SetMarkerStyle(24);  
    hist_data1  ->SetMarkerSize(0.75); 
    hist_data1  ->SetFillColor(6);
    hist_data1  ->SetLineColor(6);
    setTDRStyle();
    gStyle->SetErrorX(0.);

  
    TCanvas *c1 = new TCanvas(name, name,10,32,782,552);
    c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    c1->  cd();   
  

    TPad* canvas_1 = new TPad("canvas"+name, "canvas"+name,0,0.23,1.0,0.98);
    canvas_1 ->Draw();
  canvas_1->SetFillColor(0);
  canvas_1->SetBorderMode(0);
  canvas_1->SetBorderSize(2);
  canvas_1->SetTopMargin(0.065);
  canvas_1->SetFrameBorderMode(0);
    canvas_1 ->cd();
 
    canvas_1->SetLogy(log);
 
    if (!log) hist_data1->SetMaximum( hist_data1->GetMaximum()*2);
    else hist_data1->SetMaximum( hist_data1->GetMaximum()*5000);
    if (!log) hist_data1->SetMinimum( 0);
    else hist_data1->SetMinimum( 0.1);

    hist_data1  ->Draw("hist");  
  
    hist_data1   ->GetXaxis()->SetTitle(name);
    hist_data1   ->GetYaxis()->SetTitle(ytitle);

    hist_data1   ->SetTitleSize(0.08,"Y");
    hist_data1   ->SetTitleOffset(0.65,"Y"); 
  hist_data1->SetTitleOffset(0.81,"Y");
  hist_data1->GetYaxis()->SetLabelSize( 0.05 );
  hist_data1->GetYaxis()->SetTitleSize( 0.06 );
    hist_data2->Draw("same E1X0");


    int move_legend=0;
    if (name=="jet_phi" || name=="sv_phi" || name=="muon_phi" || name=="pfelectron_phi" || name=="pfmuon_phi") move_legend=1;
    if (btag) {
        if (name=="CombCSVJPSL" || name=="CombCSVSL" || (name=="SoftMu" && !log) ) move_legend=2;
        if (name=="CSV" || name=="CombCSVJP" || (name=="RetCombSvx" && !log) ) move_legend=3;
        if ((name=="RetCombSvx" || name=="SoftMu" ) && log) move_legend=1;
    }
    if (log && name=="sv_en_ratio" ) move_legend=1;
    TLegend* qw;
  qw = new TLegend(0.65,0.60,0.95,0.90,NULL,"brNDC");
    qw->AddEntry(hist_data1,     "JetHT repair Off",                       "f");
    qw->AddEntry(hist_data2,     "JetHT repair On"           ,         "ep");
  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
  qw->SetBorderSize(0);


 
    qw->SetFillColor(0);
    qw->Draw();

TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.89,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.05681);
   tex->SetLineWidth(2);
   tex->Draw();

  
  
   TString sample = "Multijets";
//   TString sample = "Muon enriched QCD";
//     if (filename.Contains("pfsel")) sample += "Multijets" ;
//     else if (filename.Contains("musel")) sample += "Muon enriched QCD" ;


    TLatex *tex1 = new TLatex(0.20,0.74,sample);
    tex1->SetNDC();
    tex1->SetTextAlign(13);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.055);
    tex1->SetLineWidth(2);
    tex1->Draw();


    TLatex *tex2 = new TLatex(0.20,0.68,jettype);
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.055);
    tex2->SetLineWidth(2);
    tex2->Draw();


     canvas_1->Modified();


    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->SetFillColor(0);
    canvas_2->SetBorderMode(0);
    canvas_2->SetBorderSize(2);
    canvas_2->SetGridy();
    canvas_2->SetBottomMargin(0.31);
    canvas_2->SetFrameBorderMode(0);

    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();
  
    histo_ratio->SetMarkerStyle(24);
    histo_ratio->SetMarkerSize(0.75);
    histo_ratio->SetLineWidth(2);
    histo_ratio->SetLineColor(6);
    histo_ratio->SetMarkerColor(6);

 
    histo_ratio->GetYaxis()->SetTitle(qwname2+"/"+qwname1);
    histo_ratio->GetXaxis()->SetTitle(histotitle);
    histo_ratio->GetYaxis()->SetNdivisions( 505 );

    histo_ratio->SetTitleOffset(0.9,"X");
    histo_ratio->SetTitleOffset(0.31,"Y");
    double labelsizex=0.12;
    double labelsizey=0.12;
    double titlesizex=0.15;
    double titlesizey=0.14;

    histo_ratio->GetXaxis()->SetLabelSize( labelsizex );
    histo_ratio->GetXaxis()->SetTitleSize( titlesizex );
    histo_ratio->GetYaxis()->SetLabelSize( labelsizey );
    histo_ratio->GetYaxis()->SetTitleSize( titlesizey );


    histo_ratio->SetMinimum(0.5);
    histo_ratio->SetMaximum(1.5);
//    histo_ratio->SetMinimum(0.8);
//    histo_ratio->SetMaximum(1.2);
    histo_ratio->Draw("E1X0");

    c1->cd();  
  
    TString name_plot=name+"_Linear"+format; 
    if(log) name_plot=name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);
    TString name_plot3=name+"_Linear.gif";
    if(log) name_plot3=name+"_Log.gif";
    c1->SaveAs(dir4plots+"/"+name_plot3);

    if (log && web) {  // save also _Linear for web
        canvas_1 ->cd();
        canvas_1->SetLogy(false);
        c1->cd();
        c1->SaveAs(dir4plots+"/"+name+"_Linear"+format);
    }




}

//--------------------------
void Drawdata2(TString name, TString ytitle, TString histotitle, bool log, float miny)
{

    TH1D* hist_data1;
    TH1D* hist_data2;
    TH1D* hist_data3;
    TH1D* hist_data4;
    TH1D* hist_data5;
    TH1D* hist_data6;
    TH1D* hist_data7;
    TH1D* hist_data8;
 
 
    TFile *myFile     = new TFile(filename1);
    myFile->cd();
    hist_data1      = (TH1D*)gROOT->FindObject(name+"_data");

    if(booname2) {
    TFile *myFile2     = new TFile(filename2);
    myFile2->cd();
    hist_data2      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    else { hist_data2 = (TH1D*)hist_data1->Clone(); }

    if(booname3) {
    TFile *myFile3     = new TFile(filename3);
    myFile3->cd();
    hist_data3      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname4) {
    TFile *myFile4     = new TFile(filename4);
    myFile4->cd();
    hist_data4      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname5) {
    TFile *myFile5     = new TFile(filename5);
    myFile5->cd();
    hist_data5      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname6) {
    TFile *myFile6     = new TFile(filename6);
    myFile6->cd();
    hist_data6      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname7) {
    TFile *myFile7     = new TFile(filename7);
    myFile7->cd();
    hist_data7      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname8) {
    TFile *myFile8     = new TFile(filename8);
    myFile8->cd();
    hist_data8      = (TH1D*)gROOT->FindObject(name+"_data");
    }
 
    bool ovbin = true;
    for (int i=1;i<10;i++) {
        char ccc[20];
        sprintf(ccc,"bin%d",i);
        TString biccc = ccc;
        if (name==biccc+"_SVmass" ||
            name==biccc+"_sv_flight3DSig" ||
            name==biccc+"_sv_pt" ||
            name==biccc+"_sv_deltaR_jet" ) ovbin= false;
    }

    if (bOverflow && name!="SSV" && name!="SSVHP" && name!="sv_mass" 
        && name!="sv_mass_3trk" && ovbin) {
        OverFlowBinFix(hist_data1);
        if (booname2) OverFlowBinFix(hist_data2);
        if (booname3) OverFlowBinFix(hist_data3);
        if (booname4) OverFlowBinFix(hist_data4);
        if (booname5) OverFlowBinFix(hist_data5);
        if (booname6) OverFlowBinFix(hist_data6);
        if (booname7) OverFlowBinFix(hist_data7);
        if (booname8) OverFlowBinFix(hist_data8);
    }

    cout << "ok 1" << endl;

    float scale_f =1;
    if (booname2) {
     scale_f= (hist_data1->Integral())/(hist_data2->Integral());

     if (hist_data1->GetXaxis()->GetBinUpEdge(hist_data1->GetNbinsX()) != hist_data2->GetXaxis()->GetBinUpEdge(hist_data2->GetNbinsX())) {
       cout << "name histo ALERT " << name << endl;
       cout << "xmax " <<  hist_data1->GetXaxis()->GetBinUpEdge(hist_data1->GetNbinsX()) << "   "   << hist_data2->GetXaxis()->GetBinUpEdge(hist_data2->GetNbinsX()) << endl;
     }
     if (hist_data1->GetNbinsX()!=hist_data2->GetNbinsX())  {
       cout << "name histo ALERT " << name << endl;
       cout << "not the same bin number" << hist_data1->GetNbinsX() << " "  << hist_data2->GetNbinsX() <<  endl;
       cout << "xmax " <<  hist_data1->GetXaxis()->GetBinUpEdge(hist_data1->GetNbinsX()) << "   "   << hist_data2->GetXaxis()->GetBinUpEdge(hist_data2->GetNbinsX()) << endl;
      if (hist_data1->GetXaxis()->GetBinUpEdge(hist_data1->GetNbinsX()) == hist_data2->GetXaxis()->GetBinUpEdge(hist_data2->GetNbinsX()) ) scale_f/=hist_data1->GetNbinsX()/hist_data2->GetNbinsX();
     }
    hist_data2       ->Scale(scale_f);
    }


    cout << "ok 2" << endl;
    float scale_f3 =1;
    float scale_f4 =1;
    float scale_f5 =1;
    float scale_f6 =1;
    float scale_f7 =1;
    float scale_f8 =1;
    if (booname3) { scale_f3 = (hist_data1->Integral())/(hist_data3->Integral()); hist_data3       ->Scale(scale_f3); }
    if (booname4) { scale_f4 = (hist_data1->Integral())/(hist_data4->Integral()); hist_data4       ->Scale(scale_f4); }
    if (booname5) { scale_f5 = (hist_data1->Integral())/(hist_data5->Integral()); hist_data5       ->Scale(scale_f5); }
    if (booname6) { scale_f6 = (hist_data1->Integral())/(hist_data6->Integral()); hist_data6       ->Scale(scale_f6); }
    if (booname7) { scale_f7 = (hist_data1->Integral())/(hist_data7->Integral()); hist_data7       ->Scale(scale_f7); }
    if (booname8) { scale_f8 = (hist_data1->Integral())/(hist_data8->Integral()); hist_data8       ->Scale(scale_f8); }
    
    cout << "ok 3" << endl;

    TH1D* histo_ratio;
    TH1D* histo_ratio3;
    TH1D* histo_ratio4;
    TH1D* histo_ratio5;
    TH1D* histo_ratio6;
    TH1D* histo_ratio7;
    TH1D* histo_ratio8;
    if(booname2) {histo_ratio = (TH1D*) hist_data2->Clone();
     histo_ratio->SetName("histo_ratio");
     histo_ratio->SetTitle("");
     histo_ratio->Divide(hist_data1);
    }
    else { histo_ratio = (TH1D*) hist_data1->Clone();
      histo_ratio->Divide(hist_data1);
    }
    if (booname3)  histo_ratio3 = (TH1D*) hist_data3->Clone();
    if (booname4)  histo_ratio4 = (TH1D*) hist_data4->Clone();
    if (booname5)  histo_ratio5 = (TH1D*) hist_data5->Clone();
    if (booname6)  histo_ratio6 = (TH1D*) hist_data6->Clone();
    if (booname7)  histo_ratio7 = (TH1D*) hist_data7->Clone();
    if (booname8)  histo_ratio8 = (TH1D*) hist_data8->Clone();
    if (booname3)  histo_ratio3->Divide(hist_data1);
    if (booname4)  histo_ratio4->Divide(hist_data1);
    if (booname5)  histo_ratio5->Divide(hist_data1);
    if (booname6)  histo_ratio6->Divide(hist_data1);
    if (booname7)  histo_ratio7->Divide(hist_data1);
    if (booname8)  histo_ratio8->Divide(hist_data1);
  
    cout << "ok 4" << endl;
    hist_data1  ->SetLineWidth(2);
    hist_data1  ->SetMarkerStyle(33);  
//    hist_data1  ->SetMarkerSize(0.75); 

    if(booname2) {
//    hist_data2  ->SetLineWidth(2);
    hist_data2  ->SetMarkerStyle(20);  
    hist_data2  ->SetMarkerSize(0.75); 
    hist_data2  ->SetLineColor(6);
//    hist_data2  ->SetMarkerColor(2);
    hist_data2  ->SetFillColor(6);
    histo_ratio->SetMarkerStyle(20);
    histo_ratio->SetMarkerSize(0.75);
//    histo_ratio->SetLineWidth(2);
    histo_ratio  ->SetLineColor(6);
    histo_ratio  ->SetMarkerColor(6);
    }

    if (booname3) { 
//       hist_data3->SetLineWidth(2);
       hist_data3->SetMarkerStyle(21);
       hist_data3->SetMarkerSize(0.75);
       hist_data3->SetLineColor(4);
       hist_data3->SetMarkerColor(4);
//       histo_ratio3->SetLineWidth(2);
       histo_ratio3->SetMarkerStyle(21);
       histo_ratio3->SetMarkerSize(0.75);
       histo_ratio3->SetLineColor(4);
       histo_ratio3->SetMarkerColor(4);
    }
    if (booname4) {
//       hist_data4->SetLineWidth(2);
       hist_data4->SetMarkerStyle(21);
       hist_data4->SetMarkerSize(0.75);
       hist_data4->SetLineColor(8);
       hist_data4->SetMarkerColor(8);
//       histo_ratio4->SetLineWidth(2);
       histo_ratio4->SetMarkerStyle(21);
       histo_ratio4->SetMarkerSize(0.75);
       histo_ratio4->SetLineColor(8);
       histo_ratio4->SetMarkerColor(8);
    }
    if (booname5) {
//       hist_data5->SetLineWidth(2);
       hist_data5->SetMarkerStyle(21);
       hist_data5->SetMarkerSize(0.75);
       hist_data5->SetLineColor(13);
       hist_data5->SetMarkerColor(13);
 //      histo_ratio5->SetLineWidth(2);
       histo_ratio5->SetMarkerStyle(21);
       histo_ratio5->SetMarkerSize(0.75);
       histo_ratio5->SetLineColor(13);
       histo_ratio5->SetMarkerColor(13);
    }
    if (booname6) {
//       hist_data6->SetLineWidth(2);
       hist_data6->SetMarkerStyle(24);
       hist_data6->SetMarkerSize(0.75);
       hist_data6->SetLineColor(4);
       hist_data6->SetMarkerColor(4);
//       histo_ratio6->SetLineWidth(2);
       histo_ratio6->SetMarkerStyle(24);
       histo_ratio6->SetMarkerSize(0.75);
       histo_ratio6->SetLineColor(4);
       histo_ratio6->SetMarkerColor(4);
    }
    if (booname7) {
//       hist_data7->SetLineWidth(2);
       hist_data7->SetMarkerStyle(26);
       hist_data7->SetMarkerSize(0.75);
       hist_data7->SetLineColor(4);
       hist_data7->SetMarkerColor(4);
//       histo_ratio7->SetLineWidth(2);
       histo_ratio7->SetMarkerStyle(26);
       histo_ratio7->SetMarkerSize(0.75);
       histo_ratio7->SetLineColor(4);
       histo_ratio7->SetMarkerColor(4);
    }
    if (booname8) {
//       hist_data8->SetLineWidth(2);
       hist_data8->SetMarkerStyle(33);
       hist_data8->SetLineColor(13);
       hist_data8->SetMarkerColor(13);
//       histo_ratio8->SetLineWidth(2);
       histo_ratio8->SetMarkerStyle(33);
       histo_ratio8->SetLineColor(13);
       histo_ratio8->SetMarkerColor(13);
    }

    cout << "ok 5" << endl;
    
    setTDRStyle();
    gStyle->SetErrorX(0.);

  
    TCanvas *c1 = new TCanvas(name, name,10,32,782,552);
    c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    c1->  cd();   
  

    TPad* canvas_1 = new TPad("canvas"+name, "canvas"+name,0,0.23,1.0,0.98);
    canvas_1 ->Draw();
  canvas_1->SetFillColor(0);
  canvas_1->SetBorderMode(0);
  canvas_1->SetBorderSize(2);
  canvas_1->SetTopMargin(0.065);
  canvas_1->SetFrameBorderMode(0);
    canvas_1 ->cd();
 
    canvas_1->SetLogy(log);
 

    if (booname2) {
      hist_data2   ->GetXaxis()->SetTitle(name);
      hist_data2   ->GetYaxis()->SetTitle(ytitle);

      hist_data2   ->SetTitleSize(0.08,"Y");
      hist_data2   ->SetTitleOffset(0.65,"Y");
      hist_data2->SetTitleOffset(0.81,"Y");
      hist_data2->GetYaxis()->SetLabelSize( 0.05 );
      hist_data2->GetYaxis()->SetTitleSize( 0.06 );
      if (!log) hist_data2->SetMaximum( hist_data2->GetMaximum()*2);
      else hist_data2->SetMaximum( hist_data2->GetMaximum()*5000);
      if (name=="jet_phi") hist_data2->SetMinimum(0.);
      hist_data2  ->Draw("hist");  
      if (miny==-1) {
        if (log) hist_data2->SetMinimum(0.1);
        else  hist_data2->SetMinimum(0.);
      }
      else { 
          hist_data2->SetMinimum(miny);
      }
    }
    else  {
      hist_data1   ->GetXaxis()->SetTitle(name);
      hist_data1   ->GetYaxis()->SetTitle(ytitle);

      if (!log) hist_data1->SetMaximum( hist_data1->GetMaximum()*2);
      else hist_data1->SetMaximum( hist_data1->GetMaximum()*5000);
      if (name=="jet_phi") hist_data1->SetMinimum(0.);
      hist_data1   ->SetTitleSize(0.08,"Y");
      hist_data1   ->SetTitleOffset(0.65,"Y"); 
      hist_data1->SetTitleOffset(0.81,"Y");
      hist_data1->GetYaxis()->SetLabelSize( 0.05 );
      hist_data1->GetYaxis()->SetTitleSize( 0.06 );
      hist_data1  ->Draw("E1X0");
      if (miny==-1) {
        if (log) hist_data1->SetMinimum(0.1);
        else  hist_data1->SetMinimum(0.);
      }
      else { 
          hist_data1->SetMinimum(miny);
      }
    }


    if (booname3) { hist_data3->Draw("same E1X0"); }
    if (booname4) { hist_data4->Draw("same E1X0"); }
    if (booname5) { hist_data5->Draw("same E1X0"); }
    if (booname6) { hist_data6->Draw("same E1X0"); }
    if (booname7) { hist_data7->Draw("same E1X0"); }
    if (booname8) { hist_data8->Draw("same E1X0"); }
      hist_data1 ->Draw("E1X0 same");

    int move_legend=0;
    if (name=="jet_phi" || name=="sv_phi" || name=="muon_phi" || name=="pfelectron_phi" || name=="pfmuon_phi") move_legend=1;
    if (btag) {
        if (name=="CombCSVJPSL" || name=="CombCSVSL" || (name=="SoftMu" && !log) ) move_legend=2;
        if (name=="CSV" || name=="CombCSVJP" || (name=="RetCombSvx" && !log) ) move_legend=3;
        if ((name=="RetCombSvx" || name=="SoftMu" ) && log) move_legend=1;
    }
    if (log && name=="sv_en_ratio" ) move_legend=1;
    TLegend* qw;
  qw = new TLegend(0.65,0.60,0.95,0.90,NULL,"brNDC");
    qw->AddEntry(hist_data1,     qwname1,                       "ep");
    if (booname3) qw->AddEntry(hist_data3,      qwname3          ,         "ep");
    if (booname4) qw->AddEntry(hist_data4,      qwname4          ,         "ep");
    if (booname5) qw->AddEntry(hist_data5,      qwname5          ,         "ep");
    if (booname7) qw->AddEntry(hist_data7,      qwname7          ,         "ep");
    if (booname6) qw->AddEntry(hist_data6,      qwname6          ,         "ep");
    if (booname8) qw->AddEntry(hist_data8,      qwname8          ,         "ep");
    if (booname2) qw->AddEntry(hist_data2,     qwname2           ,         "f");
    cout << "ok 6" << endl;

  qw->SetBorderSize(1);
  qw->SetTextFont(62);
  qw->SetLineColor(1);
  qw->SetLineStyle(1);
  qw->SetLineWidth(1);
  qw->SetFillColor(0);
  qw->SetFillStyle(1001);
  qw->SetBorderSize(0);


 
    qw->SetFillColor(0);
    qw->Draw();

TLatex *   tex = new TLatex(0.98,0.95125,"#sqrt{s}=13 TeV");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04875);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.89,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.05681);
   tex->SetLineWidth(2);
   tex->Draw();

  
  
//   TString sample = "Multijets";
//   TString sample = "Muon enriched QCD";
   TString sample = "";
   if (filename1.Contains("jet")) sample += "Multijets" ;
   else if (filename1.Contains("btag")) sample += "Muon enriched QCD" ;


    TLatex *tex1 = new TLatex(0.20,0.74,sample);
    tex1->SetNDC();
    tex1->SetTextAlign(13);
    tex1->SetTextFont(42);
    tex1->SetTextSize(0.055);
    tex1->SetLineWidth(2);
    tex1->Draw();


    TLatex *tex2 = new TLatex(0.20,0.68,jettype);
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.055);
    tex2->SetLineWidth(2);
    tex2->Draw();


     canvas_1->Modified();


    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->SetFillColor(0);
    canvas_2->SetBorderMode(0);
    canvas_2->SetBorderSize(2);
    canvas_2->SetGridy();
    canvas_2->SetBottomMargin(0.31);
    canvas_2->SetFrameBorderMode(0);

    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();
  
    histo_ratio->GetYaxis()->SetTitle("color/black");
//    histo_ratio->GetYaxis()->SetTitle("color/2016");
    histo_ratio->GetXaxis()->SetTitle(histotitle);
    histo_ratio->GetYaxis()->SetNdivisions( 505 );

    histo_ratio->SetTitleOffset(0.9,"X");
    histo_ratio->SetTitleOffset(0.31,"Y");
    double labelsizex=0.12;
    double labelsizey=0.12;
    double titlesizex=0.15;
    double titlesizey=0.14;

    histo_ratio->GetXaxis()->SetLabelSize( labelsizex );
    histo_ratio->GetXaxis()->SetTitleSize( titlesizex );
    histo_ratio->GetYaxis()->SetLabelSize( labelsizey );
    histo_ratio->GetYaxis()->SetTitleSize( titlesizey );


    histo_ratio->SetMinimum(0.4);
    histo_ratio->SetMaximum(1.6);
//    histo_ratio->SetMinimum(0.);
//    histo_ratio->SetMaximum(2.);
    if (booname2) histo_ratio->Draw("E1X0");
    else histo_ratio->Draw("hist");

    if (booname3) histo_ratio3->Draw("E1X0 same");
    if (booname4) histo_ratio4->Draw("E1X0 same");
    if (booname5) histo_ratio5->Draw("E1X0 same");
    if (booname6) histo_ratio6->Draw("E1X0 same");
    if (booname7) histo_ratio7->Draw("E1X0 same");
    if (booname8) histo_ratio8->Draw("E1X0 same");

    cout << "ok 7" << endl;
    c1->cd();  
  
    TString name_plot=name+"_Linear"+format; 
    if(log) name_plot=name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);
    TString name_plot3=name+"_Linear.pdf";
    if(log) name_plot3=name+"_Log.pdf";
    c1->SaveAs(dir4plots+"/"+name_plot3);

    if (log && web) {  // save also _Linear for web
        canvas_1 ->cd();
        canvas_1->SetLogy(false);
        if (log && booname2) hist_data2->SetMaximum( hist_data2->GetMaximum()/2500);
        else if (log) hist_data1->SetMaximum( hist_data1->GetMaximum()/2500);
        c1->cd();
        c1->SaveAs(dir4plots+"/"+name+"_Linear"+format);
    }




}

//--------------------------


void DrawTagRate(TString name, TString histotitle, bool log){


    TH1D* hist_b;
    TH1D* hist_c;
    TH1D* hist_bfromg;
    TH1D* hist_l;
    TH1D* hist_data;
    TH1D* hist_data2;
    TH1D* hist_data3;
    TH1D* hist_data4;

    TH1D* hist_g;
    TH1D* hist_cfromg;
    TH1D* hist_puu;
 
 
    TFile *myFile     = new TFile(filenameMC);
 
    myFile->cd();
    hist_b         = (TH1D*)gROOT->FindObject(name+"_b");
    hist_c         = (TH1D*)gROOT->FindObject(name+"_c");
    hist_bfromg    = (TH1D*)gROOT->FindObject(name+"_bfromg");
    hist_l         = (TH1D*)gROOT->FindObject(name+"_l");
    hist_g         = (TH1D*)gROOT->FindObject(name+"_g");
    hist_cfromg         = (TH1D*)gROOT->FindObject(name+"_cfromg");
    hist_puu         = (TH1D*)gROOT->FindObject(name+"_puu");

    TFile *myFile2     = new TFile(filename1);
    myFile2->cd();
    hist_data      = (TH1D*)gROOT->FindObject(name+"_data");
 
    if(booname2) {
    TFile *myFile2     = new TFile(filename2);
    myFile2->cd();
    hist_data2      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    else { hist_data2 = (TH1D*)hist_data->Clone(); }

    if(booname3) {
    TFile *myFile3     = new TFile(filename3);
    myFile3->cd();
    hist_data3      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname4) {
    TFile *myFile4     = new TFile(filename4);
    myFile4->cd();
    hist_data4      = (TH1D*)gROOT->FindObject(name+"_data");
    }

    if (btag) hist_l->Scale(1.27);
    if (btag) hist_g->Scale(1.27);
    cout << " btag rewighting for hist_l and hist_g " << endl;

    TH1D* histo_tot = (TH1D*) hist_b->Clone();
    histo_tot->Sumw2();
    histo_tot ->Add(hist_c);
    histo_tot ->Add(hist_bfromg);
    histo_tot ->Add(hist_l);  
    histo_tot ->Add(hist_g);  
    histo_tot ->Add(hist_cfromg);  
    histo_tot ->Add(hist_puu);  

    int nbin_max= hist_data->GetNbinsX();
    float scale_f = (hist_data->Integral(0,nbin_max+1))/(histo_tot->Integral(0,nbin_max+1));
    float scale_f2 =1;
    if (booname2) { scale_f2= (hist_data->Integral())/(hist_data2->Integral()); hist_data2       ->Scale(scale_f2);}
    float scale_f3 =1;
    float scale_f4 =1;
    if (booname3) { scale_f3 = (hist_data->Integral())/(hist_data3->Integral()); hist_data3       ->Scale(scale_f3); }
    if (booname4) { scale_f4 = (hist_data->Integral())/(hist_data4->Integral()); hist_data4       ->Scale(scale_f4); }

    hist_b       ->Scale(scale_f);
    hist_c       ->Scale(scale_f);
    hist_bfromg  ->Scale(scale_f);
    hist_cfromg  ->Scale(scale_f);
    hist_l       ->Scale(scale_f);
    hist_g       ->Scale(scale_f);
    hist_puu       ->Scale(scale_f);
    histo_tot    ->Scale(scale_f);

    hist_l->Add(hist_g);
    hist_c->Add(hist_cfromg);
 
    int   nbinx=hist_data->GetNbinsX();
    float minx=hist_data->GetXaxis()->GetXmin();
    float maxx=hist_data->GetXaxis()->GetXmax();
 
    TH1D * TagRate_Data = new TH1D ("TagRate_Data",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_MC   = new TH1D ("TagRate_MC",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_MC_b = new TH1D ("TagRate_MC_b",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_MC_c = new TH1D ("TagRate_MC_c",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_MC_udsg = new TH1D ("TagRate_MC_udsg",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_MC_gspl = new TH1D ("TagRate_MC_gspl",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_MC_puu = new TH1D ("TagRate_MC_puu",histotitle,nbinx,minx,maxx);

    TH1D * TagRate_Data2 = new TH1D ("TagRate_Data2",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_Data3 = new TH1D ("TagRate_Data3",histotitle,nbinx,minx,maxx);
    TH1D * TagRate_Data4 = new TH1D ("TagRate_Data4",histotitle,nbinx,minx,maxx);

    for (int ii=0; ii<nbin_max; ii++) {
        float totdata=hist_data->Integral(0,nbin_max+1);
        float totmc=histo_tot->Integral(0,nbin_max+1);


        float val = hist_data->Integral(ii+1,nbin_max+1) / totdata;
        float err = sqrt(totdata *val*(1-val))/ totdata;
      
        float valMC = histo_tot->Integral(ii+1,nbin_max+1)/ totmc;
        float errMC = sqrt(totmc *valMC*(1-valMC))/ totmc;

        TagRate_Data->SetBinContent(ii+1, val);
        TagRate_Data->SetBinError(ii+1, err);
        TagRate_MC->SetBinContent(ii+1,   histo_tot->Integral(ii+1,nbin_max+1) / totmc);
        TagRate_MC->SetBinError(ii+1, errMC  );
        TagRate_MC_b->SetBinContent(ii+1, hist_b->Integral(ii+1,nbin_max+1) / totmc);
        TagRate_MC_c->SetBinContent(ii+1, hist_c->Integral(ii+1,nbin_max+1) / totmc);
        TagRate_MC_udsg->SetBinContent(ii+1, hist_l->Integral(ii+1,nbin_max+1) / totmc);
        TagRate_MC_gspl->SetBinContent(ii+1, hist_bfromg->Integral(ii+1,nbin_max+1) / totmc);
        TagRate_MC_puu->SetBinContent(ii+1, hist_puu->Integral(ii+1,nbin_max+1) / totmc);

        if (booname2) {
        float totdata2=hist_data2->Integral(0,nbin_max+1);
        float val2 = hist_data2->Integral(ii+1,nbin_max+1) / totdata2;
        float err2 = sqrt(totdata2 *val2*(1-val2))/ totdata2;
        TagRate_Data2->SetBinContent(ii+1, val2);
        TagRate_Data2->SetBinError(ii+1, err2);
        }
        if (booname3) {
        float totdata3=hist_data3->Integral(0,nbin_max+1);
        float val3 = hist_data3->Integral(ii+1,nbin_max+1) / totdata3;
        float err3 = sqrt(totdata3 *val3*(1-val3))/ totdata3;
        TagRate_Data3->SetBinContent(ii+1, val3);
        TagRate_Data3->SetBinError(ii+1, err3);
        }
        if (booname4) {
        float totdata4=hist_data4->Integral(0,nbin_max+1);
        float val4 = hist_data4->Integral(ii+1,nbin_max+1) / totdata4;
        float err4 = sqrt(totdata4 *val4*(1-val4))/ totdata4;
        TagRate_Data4->SetBinContent(ii+1, val4);
        TagRate_Data4->SetBinError(ii+1, err4);
        }

    }

    double titleoffsety=0.2;
    double titlesizex=0.17;
    double titlesizey=0.2;
    double labelsizex=0.14;
    double labelsizey=0.12;

    TagRate_Data  ->GetYaxis()->SetLabelSize(labelsizey);
    TagRate_Data  ->GetYaxis()->SetTitleSize(titlesizey);
    TagRate_Data  ->GetYaxis()->SetTitleOffset(titleoffsety);
  
    TagRate_MC     ->GetYaxis()->SetLabelSize(labelsizey);
    TagRate_MC     ->GetYaxis()->SetTitleSize(titlesizey);
    TagRate_MC     ->GetYaxis()->SetTitleOffset(titleoffsety);
    TagRate_MC_b     ->GetYaxis()->SetLabelSize(labelsizey);
    TagRate_MC_b     ->GetYaxis()->SetTitleSize(titlesizey);
    TagRate_MC_b     ->GetYaxis()->SetTitleOffset(titleoffsety);



    // MAKE DATA/MC RATIO
  
    TH1D* histo_ratio;
    histo_ratio = (TH1D*) TagRate_Data->Clone();
    histo_ratio->SetName("histo0_ratio");
    histo_ratio->SetTitle("");
    histo_ratio->Divide(TagRate_MC);

    TH1D* histo_ratio2;
    TH1D* histo_ratio3;
    TH1D* histo_ratio4;
    if(booname2) {histo_ratio2 = (TH1D*) TagRate_Data2->Clone();
     histo_ratio2->SetName("histo_ratio2");
     histo_ratio2->SetTitle("");
     histo_ratio2->Divide(TagRate_MC);
    }
    if (booname3)  {
     histo_ratio3 = (TH1D*) TagRate_Data3->Clone();
     histo_ratio3->Divide(TagRate_MC);
    }
    if (booname4)  {
     histo_ratio4 = (TH1D*) TagRate_Data4->Clone();
     histo_ratio4->Divide(TagRate_MC);
    }

    // SET COLORS
    TagRate_MC->SetLineColor(2);
    TagRate_MC_b->SetFillColor(2);
    TagRate_MC_c->SetFillColor(8);
    TagRate_MC_gspl->SetFillColor(7);
    TagRate_MC_udsg->SetFillColor(4);
    TagRate_MC_puu->SetFillColor(kYellow);

    // DO STACK
    THStack* hs= new THStack();

    hs->Add(TagRate_MC_b);
    hs->Add(TagRate_MC_gspl);  
    hs->Add(TagRate_MC_puu);
    hs->Add(TagRate_MC_c);
    hs->Add(TagRate_MC_udsg);
  
  
  
    // SET COSMETICS
    TagRate_Data->SetMarkerStyle(20);
    TagRate_Data->SetMarkerSize(0.75);
    TagRate_Data->GetXaxis()->SetTitle();  

    if(booname2) {
    TagRate_Data2  ->SetMarkerStyle(20);  
    TagRate_Data2  ->SetMarkerSize(0.75); 
    TagRate_Data2  ->SetLineColor(kPink+6);
    TagRate_Data2  ->SetMarkerColor(kPink+6);
    histo_ratio2->SetMarkerStyle(20);
    histo_ratio2->SetMarkerSize(0.75);
    histo_ratio2  ->SetLineColor(kPink+6);
    histo_ratio2  ->SetMarkerColor(kPink+6);
    }

    if (booname3) { 
       TagRate_Data3->SetMarkerStyle(20);
       TagRate_Data3->SetMarkerSize(0.75);
       TagRate_Data3->SetLineColor(kAzure-4);
       TagRate_Data3->SetMarkerColor(kAzure-4);
       histo_ratio3->SetMarkerStyle(20);
       histo_ratio3->SetMarkerSize(0.75);
       histo_ratio3->SetLineColor(kAzure-4);
       histo_ratio3->SetMarkerColor(kAzure-4);
    }
    if (booname4) {
       TagRate_Data4->SetMarkerStyle(21);
       TagRate_Data4->SetMarkerSize(0.75);
       TagRate_Data4->SetLineColor(13);
       TagRate_Data4->SetMarkerColor(13);
       histo_ratio4->SetMarkerStyle(21);
       histo_ratio4->SetMarkerSize(0.75);
       histo_ratio4->SetLineColor(13);
       histo_ratio4->SetMarkerColor(13);
    }


    setTDRStyle();
    gStyle->SetErrorX(0.);


    // CREATE CANVAS
  
    TCanvas *c1 = new TCanvas(name, name,10,32,782,552);
    c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    c1->  cd();


    TPad* canvas_1 = new TPad("canvas"+name, "canvas"+name,0,0.23,1.0,0.98);
    canvas_1 ->Draw();
  canvas_1->SetFillColor(0);
  canvas_1->SetBorderMode(0);
  canvas_1->SetBorderSize(2);
  canvas_1->SetTopMargin(0.065);
  canvas_1->SetFrameBorderMode(0);
    canvas_1 ->cd();

    canvas_1->SetLogy(log);

    if (TagRate_Data->GetMaximum() > hs->GetMaximum() ) {
        hs->SetMaximum(TagRate_Data->GetMaximum()*1.1 );
    }
    hs->Draw("hist");

    hs->GetHistogram()->SetTitleSize(0.08,"Y");
    hs->GetHistogram()->SetTitleOffset(0.55,"Y"); 
    hs->GetHistogram()->GetYaxis()->SetTitle("Tag Rate");
    hs->GetHistogram()->GetXaxis()->SetTitle(histotitle);

    TagRate_Data->Draw("E1X0 same");  
    if (booname2) TagRate_Data2->Draw("E1X0 same");
    if (booname3) TagRate_Data3->Draw("E1X0 same");
    if (booname4) TagRate_Data4->Draw("E1X0 same");
    // ADD LEGEND
    TLegend* qw = 0;
    if (name=="CvsB_flav" || name=="CvsB_deep" ) {
      qw = new TLegend(0.21,0.31,0.54,0.58);
    }
    else {
      qw = new TLegend(0.6,0.73,0.95,1.);
    }
//    qw->AddEntry(TagRate_Data,        "2018"                     ,"p");
    qw->AddEntry(TagRate_MC_b,        "b quark"                  ,"f");
    qw->AddEntry(TagRate_MC_gspl,     "b from gluon splitting"   ,"f");
    qw->AddEntry(TagRate_MC_c,        "c quark"                  ,"f");
    qw->AddEntry(TagRate_MC_udsg,     "uds quark or gluon"     ,"f");
    qw->AddEntry(TagRate_MC_puu,      "other"                  ,"f");
    qw->AddEntry(TagRate_Data,     qwname1,                       "ep");
    if (booname2) qw->AddEntry(TagRate_Data2,     qwname2           ,         "ep");
    if (booname3) qw->AddEntry(TagRate_Data3,      qwname3          ,         "ep");
    if (booname4) qw->AddEntry(TagRate_Data4,      qwname4          ,         "ep");
 
    qw->SetFillColor(0);
    qw->Draw();

/*
    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.055);
    latex->SetTextFont(42); //22

    latex->SetTextAlign(13);
    latex->DrawLatex(0.08, 0.96, title);
*/
  

    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->SetFillColor(0);
    canvas_2->SetBorderMode(0);
    canvas_2->SetBorderSize(2);
    canvas_2->SetGridy();
    canvas_2->SetBottomMargin(0.31);
    canvas_2->SetFrameBorderMode(0);

    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();

  
    histo_ratio->SetMarkerStyle(20);
    histo_ratio->SetMarkerSize(0.75);
    histo_ratio->SetLineWidth(2);
 
    histo_ratio->GetYaxis()->SetTitle("Data/MC");
//    histo_ratio->GetYaxis()->SetTitle("ratio");
    histo_ratio->GetXaxis()->SetTitle(histotitle);
    histo_ratio->GetYaxis()->SetNdivisions( 505 );

    histo_ratio->GetXaxis()->SetLabelSize( labelsizex);
    histo_ratio->GetXaxis()->SetTitleSize( titlesizex );

/*
    histo_ratio->SetMinimum(0.);
    histo_ratio->SetMaximum(1.6);
*/

    histo_ratio->SetMinimum(0.8);
    histo_ratio->SetMaximum(1.2);

    histo_ratio->Draw("E1X0");
    if (booname2) histo_ratio2->Draw("E1X0 same");
    if (booname3) histo_ratio3->Draw("E1X0 same");
    if (booname4) histo_ratio4->Draw("E1X0 same");


    c1->cd();
  
    TString name_plot="tag_"+name+"_Linear"+format;
    if(log) name_plot="tag_"+name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);

    if (log && web) {  // save also _Linear for web
        canvas_1 ->cd();
        canvas_1->SetLogy(false);
        c1->cd();
        c1->SaveAs(dir4plots+"/tag_"+name+"_Linear"+format);
    }
}


//--------------------------


void Draw2DPlot(TString name, TString histotitle, TString titleX, TString titleY, bool log){



    cout << histotitle << endl;
    TH2D* hist_b;
    TH2D* hist_c;
    TH2D* hist_bfromg;
    TH2D* hist_l;
    TH2D* hist_data;

    TH2D* hist_cfromg;
    TH2D* hist_puu;
 
 
    TFile *myFile     = new TFile(filename2D);
 
    myFile->cd();
    hist_b         = (TH2D*)gROOT->FindObject(name+"_b");
    hist_c         = (TH2D*)gROOT->FindObject(name+"_c");
    hist_bfromg    = (TH2D*)gROOT->FindObject(name+"_bfromg");
    hist_l         = (TH2D*)gROOT->FindObject(name+"_l");
    hist_data      = (TH2D*)gROOT->FindObject(name+"_data");

    hist_cfromg      = (TH2D*)gROOT->FindObject(name+"_cfromg");
    hist_puu      = (TH2D*)gROOT->FindObject(name+"_puu");
 

    TH2D* histo_tot = (TH2D*) hist_b->Clone();
    histo_tot ->Add(hist_c);
    histo_tot ->Add(hist_bfromg);
    histo_tot ->Add(hist_l); 
    histo_tot ->Add(hist_cfromg); 
    histo_tot ->Add(hist_puu); 
 
    float scale_f = (hist_data->Integral())/(histo_tot->Integral() );

    hist_b       ->Scale(scale_f);
    hist_c       ->Scale(scale_f);
    hist_bfromg  ->Scale(scale_f);
    hist_l       ->Scale(scale_f);
    hist_puu     ->Scale(scale_f);
    hist_cfromg  ->Scale(scale_f);
    histo_tot    ->Scale(scale_f);

    hist_c->Add(hist_cfromg);
    
  
    TProfile * pro_mc = histo_tot->ProfileX(name+"_tot");
    TProfile * pro_mc_b = hist_b->ProfileX();
    TProfile * pro_mc_c = hist_c->ProfileX();
    //TProfile * pro_mc_udsg = hist_l->ProfileX();
    //TProfile * pro_mc_gspl = hist_gsplit->ProfileX();
    TProfile * pro_mc_udsg = hist_l->ProfileX();
    TProfile * pro_mc_gspl = hist_bfromg->ProfileX();
    TProfile * pro_mc_puu = hist_puu->ProfileX();
    TProfile * pro_data = hist_data->ProfileX();
 
    // SET COLORS
    pro_mc->SetLineColor(1);
    pro_mc_b->SetLineColor(2);
    pro_mc_c->SetLineColor(8);
    pro_mc_udsg->SetLineColor(4);
    pro_mc_gspl->SetLineColor(7);
    pro_mc_puu->SetLineColor(kYellow);

    pro_data->SetMarkerStyle(20);
    pro_data->SetMarkerSize(0.75);
  
    pro_mc_gspl->GetXaxis()->SetTitle(titleX);  
    pro_mc_gspl->GetYaxis()->SetTitle(titleY);  
  
  
    // SET COSMETICS
    pro_data->SetMarkerStyle(20);
    pro_data->SetMarkerSize(0.75);
    //pro_mc_gspl->GetXaxis()->SetTitle();  
    //pro_mc_gspl->GetYaxis()->SetTitle();  


    gStyle->SetOptTitle(0);


    Double_t titleoffsetx=0.8;
    Double_t titleoffsety=0.8;
    Double_t titlesizex=0.05;
    Double_t titlesizey=0.05;
    Double_t labelsizex=0.035;
    Double_t labelsizey=0.035;

    pro_data->GetYaxis()->SetLabelSize(labelsizey);
    pro_data->GetYaxis()->SetTitleSize(titlesizey);
    pro_data->GetYaxis()->SetTitleOffset(titleoffsety);
    pro_mc->GetYaxis()->SetLabelSize(labelsizey);
    pro_mc->GetYaxis()->SetTitleSize(titlesizey);
    pro_mc->GetYaxis()->SetTitleOffset(titleoffsety);
    pro_mc_b->GetYaxis()->SetLabelSize(labelsizey);
    pro_mc_b->GetYaxis()->SetTitleSize(titlesizey);
    pro_mc_b->GetYaxis()->SetTitleOffset(titleoffsety);
    pro_mc_c->GetYaxis()->SetLabelSize(labelsizey);
    pro_mc_c->GetYaxis()->SetTitleSize(titlesizey);
    pro_mc_c->GetYaxis()->SetTitleOffset(titleoffsety);

    pro_mc_gspl->GetYaxis()->SetLabelSize(labelsizey);
    pro_mc_gspl->GetYaxis()->SetTitleSize(titlesizey);
    pro_mc_gspl->GetYaxis()->SetTitleOffset(titleoffsety);

    pro_mc_udsg->GetYaxis()->SetLabelSize(labelsizey);
    pro_mc_udsg->GetYaxis()->SetTitleSize(titlesizey);
    pro_mc_udsg->GetYaxis()->SetTitleOffset(titleoffsety);



    pro_data->GetXaxis()->SetLabelSize(labelsizex);
    pro_data->GetXaxis()->SetTitleSize(titlesizex);
    pro_data->GetXaxis()->SetTitleOffset(titleoffsetx);
    pro_mc->GetXaxis()->SetLabelSize(labelsizex);
    pro_mc->GetXaxis()->SetTitleSize(titlesizex);
    pro_mc->GetXaxis()->SetTitleOffset(titleoffsetx);
    pro_mc_b->GetXaxis()->SetLabelSize(labelsizex);
    pro_mc_b->GetXaxis()->SetTitleSize(titlesizex);
    pro_mc_b->GetXaxis()->SetTitleOffset(titleoffsetx);
    pro_mc_c->GetXaxis()->SetLabelSize(labelsizex);
    pro_mc_c->GetXaxis()->SetTitleSize(titlesizex);
    pro_mc_c->GetXaxis()->SetTitleOffset(titleoffsetx);

    pro_mc_gspl->GetXaxis()->SetLabelSize(labelsizex);
    pro_mc_gspl->GetXaxis()->SetTitleSize(titlesizex);
    pro_mc_gspl->GetXaxis()->SetTitleOffset(titleoffsetx);

    pro_mc_udsg->GetXaxis()->SetLabelSize(labelsizex);
    pro_mc_udsg->GetXaxis()->SetTitleSize(titlesizex);
    pro_mc_udsg->GetXaxis()->SetTitleOffset(titleoffsetx);

    setTDRStyle();
    gStyle->SetErrorX(0.);

    TCanvas *canvas = new TCanvas("c1", "c1",10,32,782,552);
    canvas->cd();

    float maxhist= pro_mc_gspl->GetMaximum();
    if (pro_mc_b->GetMaximum() > maxhist) maxhist = pro_mc_b->GetMaximum()*1.1;
    if (pro_mc_c->GetMaximum() > maxhist) maxhist = pro_mc_c->GetMaximum()*1.1;
    if (pro_mc_udsg->GetMaximum() > maxhist) maxhist = pro_mc_udsg->GetMaximum()*1.1;
    if (pro_mc->GetMaximum() > maxhist) maxhist = pro_mc->GetMaximum()*1.1;
    if (pro_data->GetMaximum() > maxhist) maxhist = pro_data->GetMaximum()*1.1;

    float minhist= pro_mc_gspl->GetMinimum();
    if (pro_mc_b->GetMinimum() < minhist) minhist = pro_mc_b->GetMinimum()*0.9;
    if (pro_mc_c->GetMinimum() < minhist) minhist = pro_mc_c->GetMinimum()*0.9;
    if (pro_mc_udsg->GetMinimum() < minhist) minhist = pro_mc_udsg->GetMinimum()*0.9;
    if (pro_mc->GetMinimum() < minhist) minhist = pro_mc->GetMinimum()*0.9;
    if (pro_data->GetMinimum() < minhist) minhist = pro_data->GetMinimum()*0.9;

    if (maxhist> pro_mc_gspl->GetMaximum()) pro_mc_gspl->SetMaximum(maxhist);
    if (pro_mc_gspl->GetMinimum() >minhist) pro_mc_gspl->SetMinimum(minhist);

/*
    pro_mc_gspl->Draw("hist");
    pro_mc_b->Draw("hist,same");
    pro_mc_c->Draw("hist,same");
    pro_mc_udsg->Draw("hist,same");
    pro_mc->Draw("hist,same");
    pro_mc_puu->Draw("hist,same");
    pro_data->Draw("e,same");
*/

    pro_mc->Draw("hist");
    pro_data->Draw("e,same");

/*
    TLegend* qw = 0;
    qw =  new TLegend(0.6,0.73,0.95,1.);
    qw->AddEntry(pro_data,        datacaption                   ,"p");
    qw->AddEntry(pro_mc,          "total "                 ,"l");
    qw->AddEntry(pro_mc_b,        "b quark"                ,"l");
    qw->AddEntry(pro_mc_gspl,     "b from gluon splitting" ,"l");
    qw->AddEntry(pro_mc_c,        "c quark"                ,"l");
    qw->AddEntry(pro_mc_udsg,     "uds quark or gluon"     ,"l");
    qw->AddEntry(pro_mc_puu,      "other"     ,"l");
*/
    TLegend* qw = 0;
    qw =  new TLegend(0.6,0.73,0.95,1.);
    qw->AddEntry(pro_data,        "data"                   ,"p");
    qw->AddEntry(pro_mc,          "mc "                 ,"l");


    qw->SetFillColor(0);
    qw->Draw();


    TString name_plot=name+"_Linear"+format;
    if(log) name_plot=name+"_Log"+format;
    canvas->SaveAs(dir4plots+"/"+name_plot);

}

//------------

void OverFlowBinFix(TH1D* histo){

    Float_t val, errval;

    val=histo->GetBinContent(1)+histo->GetBinContent(0);
/*
    errval=0;
    if(histo->GetBinContent(1)!=0.)
        errval+=pow(histo->GetBinError(1)/histo->GetBinContent(1),2);
    if(histo->GetBinContent(0)!=0.)
        errval+=pow(histo->GetBinError(0)/histo->GetBinContent(0),2);
    errval=sqrt(errval)*val;
*/
    errval=sqrt( histo->GetBinError(1)*histo->GetBinError(1) + histo->GetBinError(0)*histo->GetBinError(0));
    histo->SetBinContent(1,val);
    histo->SetBinError(1,errval);
    histo->SetBinContent(0,0);
    histo->SetBinError(0,0);

    Int_t highbin=histo->GetNbinsX();

    val=histo->GetBinContent(highbin)+histo->GetBinContent(highbin+1);
/*  
    errval=0;
    if(histo->GetBinContent(highbin)!=0.)
        errval+=pow(histo->GetBinError(highbin)/histo->GetBinContent(highbin),2);
    if(histo->GetBinContent(highbin+1)!=0.)
        errval+=pow(histo->GetBinError(highbin+1)/histo->GetBinContent(highbin+1),2);
    errval=sqrt(errval)*val;
*/
    errval=sqrt( histo->GetBinError(highbin)*histo->GetBinError(highbin) + histo->GetBinError(highbin+1)*histo->GetBinError(highbin+1));
    histo->SetBinContent(highbin,val);
    histo->SetBinError(highbin,errval);
    histo->SetBinContent(highbin+1,0);
    histo->SetBinError(highbin+1,0);
}


void ModifyBinning(TH1D* histo, int imax){

    Float_t val=0;
    Float_t errval=0;

    int nbins_x=histo->GetNbinsX();
    for (int i = imax; i <nbins_x+2; i++) {
       val += histo->GetBinContent(i);
       errval += histo->GetBinError(i)*histo->GetBinError(i);
    }
    errval = sqrt(errval);

    histo->SetBinContent(imax,val);
    histo->SetBinError(imax,errval);
    for (int i = imax+1; i <nbins_x+2; i++) {
       histo->SetBinContent(i,0.);
       histo->SetBinError(i,0.);
    }
    histo->GetXaxis()->SetRange(1,imax);

}

void DrawMC(TString name, TString histotitle, bool log)
 
{

    TH1D* hist_mc;     
    TH1D* hist_data1;  
    TH1D* hist_data2;
    TH1D* hist_data3;
    TH1D* hist_data4;
    TH1D* hist_data5;
    TH1D* hist_data6;
    TH1D* hist_data7;
    TH1D* hist_data8;
    TFile *myFile     = new TFile(filenameMC);
    myFile->cd();
    if (name=="nPV") {
         //  hist_mc       = (TH1D*)gROOT->FindObject(name+"_mc_unw");
        hist_mc       = (TH1D*)gROOT->FindObject(name+"_mc");
    }
    else {
        hist_mc       = (TH1D*)gROOT->FindObject(name+"_mc");
    }
    TFile *myFile1     = new TFile(filename1);
    myFile1->cd();
    hist_data1     = (TH1D*)gROOT->FindObject(name+"_data");
    if(booname2) {
    TFile *myFile2     = new TFile(filename2);
    myFile2->cd();
    hist_data2      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    else { hist_data2 = (TH1D*)hist_data1->Clone(); }

    if(booname3) {
    TFile *myFile3     = new TFile(filename3);
    myFile3->cd();
    hist_data3      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname4) {
    TFile *myFile4     = new TFile(filename4);
    myFile4->cd();
    hist_data4      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname5) {
    TFile *myFile5     = new TFile(filename5);
    myFile5->cd();
    hist_data5      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname6) {
    TFile *myFile6     = new TFile(filename6);
    myFile6->cd();
    hist_data6      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname7) {  
    TFile *myFile7     = new TFile(filename7);
    myFile7->cd();
    hist_data7      = (TH1D*)gROOT->FindObject(name+"_data");
    }
    if(booname8) {  
    TFile *myFile8     = new TFile(filename8);
    myFile8->cd();
    hist_data8      = (TH1D*)gROOT->FindObject(name+"_data");
    }

        OverFlowBinFix(hist_mc);
        OverFlowBinFix(hist_data1);
        if (booname2) OverFlowBinFix(hist_data2);
        if (booname3) OverFlowBinFix(hist_data3);
        if (booname4) OverFlowBinFix(hist_data4);
        if (booname5) OverFlowBinFix(hist_data5);
        if (booname6) OverFlowBinFix(hist_data6);
        if (booname7) OverFlowBinFix(hist_data7);
        if (booname8) OverFlowBinFix(hist_data8);


    float scale_f = (hist_data1->Integral())/(hist_mc->Integral());
    hist_mc       ->Scale(scale_f);


    TH1D* histo_ratio2;
    TH1D* histo_ratio3;
    TH1D* histo_ratio4;
    TH1D* histo_ratio5;
    TH1D* histo_ratio6;
    TH1D* histo_ratio7;
    TH1D* histo_ratio8;
    if(booname2) {
     histo_ratio2 = (TH1D*) hist_data2->Clone();
     histo_ratio2->SetName("histo_ratio2");
     histo_ratio2->SetTitle("");
    }
    if (booname3)  histo_ratio3 = (TH1D*) hist_data3->Clone();
    if (booname4)  histo_ratio4 = (TH1D*) hist_data4->Clone();
    if (booname5)  histo_ratio5 = (TH1D*) hist_data5->Clone();
    if (booname6)  histo_ratio6 = (TH1D*) hist_data6->Clone();
    if (booname7)  histo_ratio7 = (TH1D*) hist_data7->Clone();
    if (booname8)  histo_ratio8 = (TH1D*) hist_data8->Clone();
    float scale_f2 =1;
    if (booname2) { scale_f2= (hist_data1->Integral())/(hist_data2->Integral()); histo_ratio2       ->Scale(scale_f2);  hist_data2->Scale(scale_f2);}
    float scale_f3 =1;
    float scale_f4 =1;
    float scale_f5 =1;
    float scale_f6 =1;
    float scale_f7 =1;
    float scale_f8 =1;
    if (booname3) { scale_f3 = (hist_data1->Integral())/(hist_data3->Integral()); histo_ratio3       ->Scale(scale_f3); hist_data3->Scale(scale_f3); }
    if (booname4) { scale_f4 = (hist_data1->Integral())/(hist_data4->Integral()); histo_ratio4       ->Scale(scale_f4); hist_data4->Scale(scale_f4); }
    if (booname5) { scale_f5 = (hist_data1->Integral())/(hist_data5->Integral()); histo_ratio5       ->Scale(scale_f5); }
    if (booname6) { scale_f6 = (hist_data1->Integral())/(hist_data6->Integral()); histo_ratio6       ->Scale(scale_f6); }
    if (booname7) { scale_f7 = (hist_data1->Integral())/(hist_data7->Integral()); histo_ratio7       ->Scale(scale_f7); }
    if (booname8) { scale_f8 = (hist_data1->Integral())/(hist_data8->Integral()); histo_ratio8       ->Scale(scale_f8); }
/*
    if (booname2)  histo_ratio2->Divide(hist_data1);
    if (booname3)  histo_ratio3->Divide(hist_data1);
    if (booname4)  histo_ratio4->Divide(hist_data1);
    if (booname5)  histo_ratio5->Divide(hist_data1);
    if (booname6)  histo_ratio6->Divide(hist_data1);
    if (booname7)  histo_ratio7->Divide(hist_data1);
    if (booname8)  histo_ratio8->Divide(hist_data1);
*/
    if (booname2)  histo_ratio2->Divide(hist_mc);
    if (booname3)  histo_ratio3->Divide(hist_mc);
    if (booname4)  histo_ratio4->Divide(hist_mc);
    if (booname5)  histo_ratio5->Divide(hist_mc);
    if (booname6)  histo_ratio6->Divide(hist_mc);
    if (booname7)  histo_ratio7->Divide(hist_mc);
    if (booname8)  histo_ratio8->Divide(hist_mc);


    TH1D* histo_ratio;
    histo_ratio = (TH1D*) hist_data1->Clone();
    histo_ratio->SetName("histo_ratio");
    histo_ratio->SetTitle("");
  
    histo_ratio->Divide(hist_mc);
  
    hist_data1  ->SetLineWidth(2);
    hist_data1  ->SetMarkerStyle(20);  
    hist_data1  ->SetMarkerSize(0.75); 
    histo_ratio  ->SetLineWidth(2);
    histo_ratio  ->SetMarkerStyle(20);  
    histo_ratio  ->SetMarkerSize(0.75); 
    if(booname2) {
    hist_data2  ->SetMarkerStyle(20);  // Caro : 24
    hist_data2  ->SetMarkerSize(0.75);
//    hist_data2  ->SetLineColor(2);
    hist_data2  ->SetLineColor(kPink+6);
    hist_data2  ->SetMarkerColor(kPink+6);
    histo_ratio2->SetMarkerStyle(20);
    histo_ratio2->SetMarkerSize(0.75);
//    histo_ratio2  ->SetLineColor(2);
    histo_ratio2  ->SetLineColor(kPink+6);
    histo_ratio2  ->SetMarkerColor(kPink+6);
    }
   if (booname3) {
       hist_data3->SetMarkerStyle(20);
       hist_data3->SetMarkerSize(0.75);
       hist_data3->SetLineColor(kAzure-4);
       hist_data3->SetMarkerColor(kAzure-4);
       histo_ratio3->SetMarkerStyle(20);
       histo_ratio3->SetMarkerSize(0.75);
       histo_ratio3->SetLineColor(kAzure-4);
       histo_ratio3->SetMarkerColor(kAzure-4);
    }
    if (booname4) {
       hist_data4->SetMarkerStyle(23);
       hist_data4->SetMarkerSize(0.75);
       hist_data4->SetLineColor(13);
       hist_data4->SetMarkerColor(13);
       histo_ratio4->SetMarkerStyle(23);
       histo_ratio4->SetMarkerSize(0.75);
       histo_ratio4->SetLineColor(13);
       histo_ratio4->SetMarkerColor(14);
    }
    if (booname5) {
       hist_data5->SetMarkerStyle(33);
       hist_data5->SetMarkerSize(0.75);
       hist_data5->SetLineColor(6);
       hist_data5->SetMarkerColor(6);
       histo_ratio5->SetMarkerStyle(33);
       histo_ratio5->SetMarkerSize(0.75);
       histo_ratio5->SetLineColor(6);
       histo_ratio5->SetMarkerColor(6);
    }
    if (booname6) {
       hist_data6->SetMarkerStyle(29);
       hist_data6->SetMarkerSize(0.75);
       hist_data6->SetLineColor(7);
       hist_data6->SetMarkerColor(7);
       histo_ratio6->SetMarkerStyle(29);
       histo_ratio6->SetMarkerSize(0.75);
       histo_ratio6->SetLineColor(7);
       histo_ratio6->SetMarkerColor(7);
    }
    if (booname7) {
       hist_data7->SetMarkerStyle(33);
       hist_data7->SetMarkerSize(0.75);
       hist_data7->SetLineColor(16);
       hist_data7->SetMarkerColor(16);
       histo_ratio7->SetMarkerStyle(33);
       histo_ratio7->SetMarkerSize(0.75);
       histo_ratio7->SetLineColor(16);
       histo_ratio7->SetMarkerColor(16);
    }
    if (booname8) {
       hist_data8->SetMarkerStyle(33);
       hist_data8->SetLineColor(13);
       hist_data8->SetMarkerColor(13);
       histo_ratio8->SetLineColor(13);
       histo_ratio8->SetMarkerColor(13);
    }


/*

    setTDRStyle();
    gStyle->SetErrorX(0.);
*/

  



    double titleoffsety=0.2;
    double titlesizex=0.17;
    double titlesizey=0.2;
    double labelsizex=0.14;
  
   
  
    hist_mc     ->GetYaxis()->SetTitleSize(titlesizey);
    hist_mc     ->GetYaxis()->SetTitleOffset(titleoffsety);

    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);  
  
    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
    c1->SetFillColor(10);
    c1->  cd();   
  

    TPad* canvas_1 = new TPad("canvas_1", "canvas_1",0,0.25,1.0,0.98);
    canvas_1 ->Draw();
    canvas_1 ->cd();
 
    canvas_1->SetLogy(log);
 
    if (hist_data1->GetMaximum() > hist_mc->GetMaximum()) hist_mc->SetMaximum(hist_data1->GetMaximum()*1.1);
    if (hist_mc->GetMaximum() < hist_data2->GetMaximum()) hist_mc->SetMaximum(hist_data2->GetMaximum()*1.2) ;
    hist_mc    ->Draw("hist");  
  
    hist_mc    ->GetXaxis()->SetTitle(name);
    hist_mc    ->GetYaxis()->SetTitle("entries");

    hist_mc    ->SetTitleSize(0.08,"Y");
    hist_mc    ->SetTitleOffset(0.65,"Y"); 

    hist_data1->Draw("same E1X0");
    if (booname2) { hist_data2->Draw("same E1X0"); }
    if (booname3) { hist_data3->Draw("same E1X0"); }
    if (booname4) { hist_data4->Draw("same E1X0"); }
    if (booname5) { hist_data5->Draw("same E1X0"); }
    if (booname6) { hist_data6->Draw("same E1X0"); }
    if (booname7) { hist_data7->Draw("same E1X0"); }
    if (booname8) { hist_data8->Draw("same E1X0"); }


    TLegend* qw =  new TLegend(0.6,0.73,0.95,1.);
    //Legend
    qw->AddEntry(hist_mc,        "MC "           ,         "f");
    qw->AddEntry(hist_data1,     qwname1,                       "ep");
    if (booname2) qw->AddEntry(hist_data2,     qwname2           ,         "ep");
    if (booname3) qw->AddEntry(hist_data3,      qwname3          ,         "ep");
    if (booname4) qw->AddEntry(hist_data4,      qwname4          ,         "ep");
    if (booname5) qw->AddEntry(hist_data5,      qwname5          ,         "ep");
    if (booname7) qw->AddEntry(hist_data7,      qwname7          ,         "ep");
    if (booname6) qw->AddEntry(hist_data6,      qwname6          ,         "ep");
    if (booname8) qw->AddEntry(hist_data8,      qwname8          ,         "ep");
 
    qw->SetFillColor(0);
    qw->Draw();
  
  
    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.055);
    latex->SetTextFont(42); //22

    latex->SetTextAlign(13);
    latex->DrawLatex(0.08, 0.96, title);


    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();
  
 


    histo_ratio->GetYaxis()->SetTitle("Data/MC");
    histo_ratio->GetXaxis()->SetTitle(histotitle);
    histo_ratio->GetYaxis()->SetNdivisions( 505 );




   histo_ratio->SetTitleOffset(0.9,"X");
   histo_ratio->SetTitleOffset(0.31,"Y");
   labelsizex=0.12;
   double labelsizey=0.12;
   titlesizex=0.15;
   titlesizey=0.14;

   histo_ratio->GetXaxis()->SetLabelSize( labelsizex );
   histo_ratio->GetXaxis()->SetTitleSize( titlesizex );
   histo_ratio->GetYaxis()->SetLabelSize( labelsizey );
   histo_ratio->GetYaxis()->SetTitleSize( titlesizey );


    histo_ratio->SetMinimum(0.4);
    histo_ratio->SetMaximum(1.6);
    histo_ratio->Draw("E1X0");
    if (booname2) histo_ratio2->Draw("E1X0 same");
    if (booname3) histo_ratio3->Draw("E1X0 same");
    if (booname4) histo_ratio4->Draw("E1X0 same");
    if (booname5) histo_ratio5->Draw("E1X0 same");
    if (booname6) histo_ratio6->Draw("E1X0 same");
    if (booname7) histo_ratio7->Draw("E1X0 same");
    if (booname8) histo_ratio8->Draw("E1X0 same");

    /*
      if (name=="nPV") {
      cout << " nPV ratio Data/MC " << endl;
      for (int i=1; i<61; i++) {
      cout <<i-1 << "  " << histo_ratio->GetBinContent(i) <<endl;
      }
      }
    */

    c1->cd();  
  
    TString name_plot=name+"_Linear"+format; 
    if(log) name_plot=name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);

    TString name_plot2=name+"_Linear.pdf"; 
    if(log) name_plot2=name+"_Log.pdf";
    c1->SaveAs(dir4plots+"/"+name_plot2);
 

}


void DrawMCCompare(TString name, TString histotitle, bool log)
{
   DrawMCCompare(name, "Events", histotitle, log);
}
void DrawMCCompare(TString name, TString ytitle,  TString histotitle, bool log, float miny)
{


    TH1D* hist_fill;
    THStack *hs_fill;
    TH1D* hist_fill_b;
    TH1D* hist_fill_c;
    TH1D* hist_fill_l;
    TH1D* hist_fill_g;
    TH1D* hist_fill_bfromg;
    TH1D* hist_fill_cfromg;
    TH1D* hist_fill_puu;
    DefineHstack(filename_1, name, hist_fill, hs_fill, hist_fill_b, hist_fill_c, hist_fill_l, hist_fill_g, hist_fill_bfromg, hist_fill_cfromg, hist_fill_puu);




    TH1D* hist_line;
    DefineHline(filename_2, name, hist_line,  1, 0.75, 20, 2) ;


    TH1D* hist_line2;
    if (boolfile3) DefineHline(filename_3, name, hist_line2, kGray+2, 1,1,1 );


    TH1D* hist_line4;
    if (boolfile4) DefineHline(filename_4, name, hist_line4, kViolet, 1,1,1);


    TH1D* hist_line5;
    if (boolfile5) DefineHline(filename_5, name, hist_line5, kCyan-6, 1,1,1);

    TH1D* hist_line6;
    if (boolfile6) DefineHline(filename_6, name, hist_line6, 46, 1,1,1);

    TH1D* histo_ratio1;
    DefineHratio("histo_ratio1", histo_ratio1, hist_line, hist_fill,   1, 0.75, 20, 2) ;



    TH1D* histo_ratio2;
    if (boolfile3) DefineHratio("histo_ratio2", histo_ratio2, hist_line2, hist_fill,  kGray+2, 1,7,1 );
    TH1D* histo_ratio4;
    if (boolfile4) DefineHratio("histo_ratio4", histo_ratio4, hist_line4, hist_fill, kViolet, 1,7,1);
    TH1D* histo_ratio5;
    if (boolfile5)DefineHratio("histo_ratio5", histo_ratio5, hist_line5, hist_fill, kCyan-6, 1,7,1);
    TH1D* histo_ratio6;
    if (boolfile6)DefineHratio("histo_ratio6", histo_ratio6, hist_line6, hist_fill, 46, 1,7,1);



    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);  
  

    TCanvas *c1 = new TCanvas(name, name,10,32,782,552);
    c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);

    c1->  cd();   
  

    TPad* canvas_1 = new TPad("canvas_1", "canvas_1",0,0.25,1.0,0.98);
    canvas_1 ->Draw();
    canvas_1 ->cd();
 
    canvas_1->SetLogy(log);


 
    if (hist_line->GetMaximum() > hs_fill->GetMaximum()) hs_fill->SetMaximum(hist_line->GetMaximum()*1.1);
    if (log) {
    hs_fill->SetMaximum(hs_fill->GetMaximum()*5000.);
    }
    else {
       hs_fill->SetMaximum(hs_fill->GetMaximum()*2.);
    }
    if (!log) hs_fill->SetMinimum( 0);
    else hs_fill->SetMinimum( 0.1);

    hs_fill->Draw("hist");
    hs_fill->GetXaxis()->SetTitle(name);
    hs_fill->GetYaxis()->SetTitle(ytitle);
    hs_fill->GetYaxis()->SetLabelSize(0.05);
    hs_fill->GetYaxis()->SetTitleSize(0.08);
    hs_fill->GetYaxis()->SetTitleOffset(0.65); 

    cout << " off " << hist_fill->Integral() << " on " << hist_line->Integral() << " on/off " << hist_line->Integral()*1./(1.*hist_fill->Integral()) << endl;

  

//    hist_line->Draw("hist error same");
    hist_line->Draw("error same");
    if (boolfile3) hist_line2->Draw("hist same");
    if (boolfile4) hist_line4->Draw("hist same");
    if (boolfile5) hist_line5->Draw("hist same");
    if (boolfile6) hist_line6->Draw("hist same");


    TLegend* qw =  new TLegend(0.7,0.65,0.975,1.);
    //Legend
    qw->AddEntry(hist_fill_b, "bottom", "f");
    qw->AddEntry(hist_fill_bfromg, "bfromg", "f");
    qw->AddEntry(hist_fill_c, "charm", "f");
    qw->AddEntry(hist_fill_cfromg, "cfromg", "f");
    qw->AddEntry(hist_fill_l, "light", "f");
    qw->AddEntry(hist_fill_puu, "other", "f");

//    qw->AddEntry(hist_line, labelfile2,"f");
    qw->AddEntry(hist_line, labelfile2,"ep");
    if (boolfile3) qw->AddEntry(hist_line2, labelfile3,"f");
    if (boolfile4) qw->AddEntry(hist_line4, labelfile4,"f");
    if (boolfile5) qw->AddEntry(hist_line5, labelfile5,"f");
    if (boolfile6) qw->AddEntry(hist_line6, labelfile6,"f");
 
    qw->SetFillColor(0);
    qw->Draw();
  
  

   TLatex*   tex = new TLatex(0.20,0.89,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(62);
   tex->SetTextSize(0.065);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.20,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.05681);
   tex->SetLineWidth(2);
   tex->Draw();


    TLatex *mclabels = new TLatex();
    mclabels->SetNDC();
    mclabels->SetTextSize(0.04);
    mclabels->SetTextFont(42);
    mclabels->SetTextAlign(13);



    TLatex *tex2 = new TLatex(0.20,0.74,jettype);
    tex2->SetNDC();
    tex2->SetTextAlign(13);
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.055);
    tex2->SetLineWidth(2);
    tex2->Draw();



    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();

    histo_ratio1->GetXaxis()->SetTitle(histotitle);
    histo_ratio1->GetYaxis()->SetTitle(qwname2+"/"+qwname1);
//    histo_ratio1->GetYaxis()->SetTitle("ratio");
//    histo_ratio1->SetMinimum(0.5);
//    histo_ratio1->SetMaximum(1.5);

    histo_ratio1->SetMinimum(0.8);
    histo_ratio1->SetMaximum(1.2);

    histo_ratio1->Draw("E1X0");
    
    if(boolfile3) histo_ratio2->Draw("E1X0 same");
    if(boolfile4) histo_ratio4->Draw("E1X0 same");
    if(boolfile5) histo_ratio5->Draw("E1X0 same");
    if(boolfile6) histo_ratio6->Draw("E1X0 same");

/*
    TLegend* hrl =  new TLegend(0.7,0.7,0.975,1.);
    //Legend
    hrl->AddEntry(histo_ratio1, labelfile2+"over ref", "pl");
    if (boolfile3) hrl->AddEntry(histo_ratio2, labelfile3+"over ref", "pl");
    if (boolfile4) hrl->AddEntry(histo_ratio4, labelfile4+"over ref", "pl");
    if (boolfile5) hrl->AddEntry(histo_ratio5, labelfile5+"over ref", "pl");
    if (boolfile6) hrl->AddEntry(histo_ratio6, labelfile6+"over ref", "pl");
    hrl->SetFillColor(0);
    hrl->Draw();
*/


    /*
      if (name=="nPV") {
      cout << " nPV ratio Data/MC " << endl;
      for (int i=1; i<61; i++) {
      cout <<i-1 << "  " << histo_ratio->GetBinContent(i) <<endl;
      }
      }
    */


    c1->cd();  
  
    TString name_plot=name+"_Linear"+format; 
    if(log) name_plot=name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);
    TString name_plot3=name+"_Linear.gif"; 
    if(log) name_plot3=name+"_Log.gif";
    c1->SaveAs(dir4plots+"/"+name_plot3);

    if (web && log) {
      canvas_1->cd();
      canvas_1->SetLogy(0);
      c1->cd();
      c1->SaveAs(dir4plots+"/"+name+"_Linear"+format);
      TString name_plot3=name+"_Linear.gif"; 
      if(log) name_plot3=name+"_Log.gif";
      c1->SaveAs(dir4plots+"/"+name_plot3);
    }


    if (displayRatio) {
      TCanvas *c2 = new TCanvas("c2", "c2",10,32,782,552);
      c2->SetFillColor(10);
      int howmuch=1;
      if (boolfile3) howmuch++;
      if (boolfile4) howmuch++;
      if (boolfile5) howmuch++;
      if (boolfile6) howmuch++;
      c2->Divide(1,howmuch);
      c2->  cd(1);   
          gPad->SetGridy();
      histo_ratio1->Draw("E1X0");
      howmuch=1;
      if (boolfile3) { 
          howmuch++;
          c2->cd(howmuch);
          gPad->SetGridy();
          histo_ratio2->SetMinimum(0.5);
	  histo_ratio2->SetMaximum(2.0);
          histo_ratio2->Draw("E1X0");
      }
      if (boolfile4) { 
          howmuch++;
          c2->cd(howmuch);
          gPad->SetGridy();
          histo_ratio4->SetMinimum(0.5);
	  histo_ratio4->SetMaximum(2.0);
          histo_ratio4->Draw("E1X0");
      }
      if (boolfile5) { 
          howmuch++;
          c2->cd(howmuch);
          gPad->SetGridy();
          histo_ratio5->SetMinimum(0.5);
	  histo_ratio5->SetMaximum(2.0);
          histo_ratio5->Draw("E1X0");
      }
      if (boolfile6) { 
          howmuch++;
          c2->cd(howmuch);
          gPad->SetGridy();
	  histo_ratio6->SetMinimum(0.5);
	  histo_ratio6->SetMaximum(2.0);
          histo_ratio6->Draw("E1X0");
      }
      c2->cd();
      c2->SaveAs(dir4plots+"/ratio_"+name+format);
    }

 

}
//--------------------------

void DrawMCgen(TString name, TString histotitle, bool log)
{
    //cout << "Getting 2025 file\n";
    
    TH1D* hist_fill;
    DefineHgen(filename_1, name, hist_fill,  2);


    //cout << "Getting 4050 file\n";
    TH1D* hist_line;
    DefineHgen(filename_2, name, hist_line, 1);

    TH1D* hist_line_2;
    if (boolfile3) DefineHgen(filename_3, name, hist_line_2, kGray+2);

    TH1D* hist_line_4;
    if (boolfile4) DefineHgen(filename_4, name, hist_line_4, kViolet);

    TH1D* hist_line_5;
    if (boolfile5) DefineHgen(filename_5, name, hist_line_5, kCyan-6);

    TH1D* hist_line_6;
    if (boolfile6) DefineHgen(filename_6, name, hist_line_6, 46);

    TH1D* histo_ratio1;
    DefineHratio("histo_ratio1", histo_ratio1, hist_line, hist_fill,   kOrange, 0.75, 20, 1) ;

    TH1D* histo_ratio2;
    if (boolfile3) DefineHratio("histo_ratio2", histo_ratio2, hist_line_2, hist_fill,   kGray+2, 1, 7, 1) ;

    TH1D* histo_ratio3;
    if (boolfile5) DefineHratio("histo_ratio3", histo_ratio3, hist_fill, hist_line_5,   1, 1, 7, 1) ;

    TH1D* histo_ratio4;
    if (boolfile4) DefineHratio("histo_ratio4", histo_ratio4, hist_line_4, hist_fill,   kViolet, 1, 7, 1) ;

    TH1D* histo_ratio5;
    if (boolfile5) DefineHratio("histo_ratio5", histo_ratio5, hist_line_5, hist_fill,   kCyan-6, 1, 7, 1) ;

    TH1D* histo_ratio6;
    if (boolfile6) DefineHratio("histo_ratio6", histo_ratio6, hist_line_6, hist_fill,   46, 1, 7, 1) ;

/*
    cout << "histo_ratio1" << endl;
    for (int i=1; i<histo_ratio2->GetNbinsX(); i++) {
    cout << i << "  " << histo_ratio1->GetBinContent(i) << endl;
    cout << "ratio 13/8 pthat" << endl;
    for (int i=1; i<histo_ratio3->GetNbinsX()+1; i++) {
    cout << i << "  " << histo_ratio3->GetBinContent(i) << endl;
    }
    */


    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);  
  
    TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
    c1->SetFillColor(10);
    c1->  cd();   
  

    TPad* canvas_1 = new TPad("canvas_1", "canvas_1",0,0.25,1.0,0.98);
    canvas_1 ->Draw();
    canvas_1 ->cd();
 
    canvas_1->SetLogy(log);

    float max = hist_fill->GetMaximum();
    if (hist_line->GetMaximum() > max) max= hist_line->GetMaximum();
    if (boolfile3 && hist_line_2->GetMaximum() > max) max= hist_line_2->GetMaximum();
    hist_fill->SetMaximum(max*1.1);
 
    hist_fill->SetLineWidth(2);
    hist_fill->Draw("hist");
//    hist_line->Draw("hist, same");
    hist_line->SetLineWidth(2);
    hist_line->SetLineColor(kBlack);
    hist_line->SetMarkerStyle(20);
    hist_line->SetMarkerSize(0.75);
    hist_line->SetMarkerColor(kBlack);
    hist_line->Draw("same");
    if (boolfile3) hist_line_2->Draw("hist, same");
    if (boolfile4) hist_line_4->Draw("hist, same");
    if (boolfile5) hist_line_5->Draw("hist, same");
    if (boolfile6) hist_line_6->Draw("hist, same");
  
    TLegend* qw =  new TLegend(0.7,0.65,0.975,1.);
    //Legend
    qw->AddEntry(hist_fill, labelfile1, "f");
    qw->AddEntry(hist_line, labelfile2, "f");
    if (boolfile3) qw->AddEntry(hist_line_2, labelfile3, "f");
    if (boolfile4) qw->AddEntry(hist_line_4, labelfile4, "f");
    if (boolfile5) qw->AddEntry(hist_line_5, labelfile5, "f");
    if (boolfile6) qw->AddEntry(hist_line_6, labelfile6, "f");
 
    qw->SetFillColor(0);
    qw->Draw();
  
  
    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.055);
    latex->SetTextFont(42); //22
    latex->SetTextAlign(13);
    latex->DrawLatex(0.1, 0.96, title);


    c1->cd();  
  
    TPad* canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.32);
    canvas_2->Draw();
    canvas_2->cd();
    gPad->SetBottomMargin(0.375);
    gPad->SetGridy();

    histo_ratio1->GetXaxis()->SetTitle(histotitle);
    histo_ratio1->GetYaxis()->SetTitle(qwname2+"/"+qwname1);
//    histo_ratio1->SetMinimum(0.5);
//    histo_ratio1->SetMaximum(1.5);
    histo_ratio1->SetMinimum(0.8);
    histo_ratio1->SetMaximum(1.2);

    histo_ratio1->Draw("E1X0");
    
    if (boolfile3) histo_ratio2->Draw("E1X0 same");
    if (boolfile4) histo_ratio4->Draw("E1X0 same");
    if (boolfile5) histo_ratio5->Draw("E1X0 same");
    if (boolfile6) histo_ratio6->Draw("E1X0 same");

    c1->cd();  
  
    TString name_plot=name+"_Linear"+format; 
    if(log) name_plot=name+"_Log"+format;
    c1->SaveAs(dir4plots+"/"+name_plot);
    TString name_plot3=name+"_Linear.gif"; 
    if(log) name_plot3=name+"_Log.gif";
    c1->SaveAs(dir4plots+"/"+name_plot3);

 

}
//--------------------------

void DefineHstack(TString filename_x, TString name, TH1D*& hist_fill, THStack * & hs_fill, TH1D* & hist_fill_b, TH1D* & hist_fill_c, TH1D* & hist_fill_l, TH1D* & hist_fill_g, TH1D* & hist_fill_bfromg, TH1D* & hist_fill_cfromg, TH1D* & hist_fill_puu )
{

    TFile *fileFill     = new TFile(filename_x);


    fileFill->cd();

    hist_fill_b       = (TH1D*)gROOT->FindObject(name+"_b");
    hist_fill_c       = (TH1D*)gROOT->FindObject(name+"_c");
    hist_fill_l       = (TH1D*)gROOT->FindObject(name+"_l");
    hist_fill_g       = (TH1D*)gROOT->FindObject(name+"_g");
    hist_fill_bfromg  = (TH1D*)gROOT->FindObject(name+"_bfromg");
    hist_fill_cfromg  = (TH1D*)gROOT->FindObject(name+"_cfromg");
    hist_fill_puu     = (TH1D*)gROOT->FindObject(name+"_puu");

    if (bOverflow) {
        OverFlowBinFix(hist_fill_b);
        OverFlowBinFix(hist_fill_c);
        OverFlowBinFix(hist_fill_l);
        OverFlowBinFix(hist_fill_g);
        OverFlowBinFix(hist_fill_bfromg);
        OverFlowBinFix(hist_fill_cfromg);
        OverFlowBinFix(hist_fill_puu);
    }

/*
    if (btag) {
      cout << " reweighting light and g contribution for " <<  filename_x << endl;
      hist_fill_l->Scale(1./0.93);
      hist_fill_g->Scale(1./0.93);
    }
*/

    hist_fill = (TH1D*) hist_fill_b->Clone();
    hist_fill->Add(hist_fill_bfromg);
    hist_fill->Add(hist_fill_c);
    hist_fill->Add(hist_fill_cfromg);
    hist_fill->Add(hist_fill_l);
    hist_fill->Add(hist_fill_g);
    hist_fill->Add(hist_fill_puu);



/*
    float int_fill = hist_fill->Integral();
    if (int_fill > 0.){
        hist_fill->Scale(1./int_fill);
        hist_fill_b->Scale(1./int_fill);
        hist_fill_c->Scale(1./int_fill);
        hist_fill_l->Scale(1./int_fill);
        hist_fill_g->Scale(1./int_fill);
        hist_fill_puu->Scale(1./int_fill);
        hist_fill_bfromg->Scale(1./int_fill);
        hist_fill_cfromg->Scale(1./int_fill);
    }
*/

/*
    cout << filename_x << "     " << hist_fill_b->Integral() 
    << "     " << hist_fill_c->Integral()  
    << "     " << hist_fill_l->Integral()
    << "     " << hist_fill_g->Integral()
    << "     " << hist_fill_bfromg->Integral()
    << "     " << hist_fill_cfromg->Integral() <<endl;
*/

    double titleoffsety=0.2;
    double titlesizey=0.2;
    hist_fill->GetYaxis()->SetTitleSize(titlesizey);
    hist_fill->GetYaxis()->SetTitleOffset(titleoffsety);

    hist_fill_b->SetFillColor(kRed);
    hist_fill_bfromg->SetFillColor(kCyan);
    hist_fill_c->SetFillColor(8);
    hist_fill_cfromg->SetFillColor(kMagenta);
    hist_fill_l->SetFillColor(kBlue);
    hist_fill_g->SetFillColor(kBlue);
    hist_fill_puu->SetFillColor(kYellow);
    hist_fill_b->SetLineColor(kRed);
    hist_fill_bfromg->SetLineColor(kCyan);
    hist_fill_c->SetLineColor(8);
    hist_fill_cfromg->SetLineColor(kMagenta);
    hist_fill_l->SetLineColor(kBlue);
    hist_fill_g->SetLineColor(kBlue);
    hist_fill_puu->SetLineColor(kYellow);

    hist_fill->SetLineWidth(2);
    hist_fill->SetLineColor(kBlack);
    hist_fill->SetMarkerStyle(20);  
    hist_fill->SetMarkerSize(0.75);
    hist_fill->SetMarkerColor(kBlack);

    hs_fill = new THStack("hs_fill","Stacked histograms AOD");
    hs_fill->Add(hist_fill_b);
    hs_fill->Add(hist_fill_bfromg);
    hs_fill->Add(hist_fill_c);
    hs_fill->Add(hist_fill_cfromg);
    hs_fill->Add(hist_fill_l);
    hs_fill->Add(hist_fill_g);
    hs_fill->Add(hist_fill_puu);


}

void DefineHline(TString filename_x, TString name, TH1D* & hist_line, int icolor, float xMsize, int iMstyle, int iLwidth )
{

    TFile *fileLine     = new TFile(filename_x);

    TH1D* hist_line_b;
    TH1D* hist_line_c;
    TH1D* hist_line_l;
    TH1D* hist_line_g;
    TH1D* hist_line_bfromg;
    TH1D* hist_line_cfromg;
    TH1D* hist_line_puu;

    fileLine->cd();

    hist_line_b       = (TH1D*)gROOT->FindObject(name+"_b");
    hist_line_c       = (TH1D*)gROOT->FindObject(name+"_c");
    hist_line_l       = (TH1D*)gROOT->FindObject(name+"_l");
    hist_line_g       = (TH1D*)gROOT->FindObject(name+"_g");
    hist_line_bfromg  = (TH1D*)gROOT->FindObject(name+"_bfromg");
    hist_line_cfromg  = (TH1D*)gROOT->FindObject(name+"_cfromg");
    hist_line_puu  = (TH1D*)gROOT->FindObject(name+"_puu");

    if (bOverflow) {
        OverFlowBinFix(hist_line_b);
        OverFlowBinFix(hist_line_c);
        OverFlowBinFix(hist_line_l);
        OverFlowBinFix(hist_line_g);
        OverFlowBinFix(hist_line_bfromg);
        OverFlowBinFix(hist_line_cfromg);
        OverFlowBinFix(hist_line_puu);
    }
    
    hist_line = (TH1D*) hist_line_b->Clone();
    hist_line->Add(hist_line_bfromg);
    hist_line->Add(hist_line_c);
    hist_line->Add(hist_line_cfromg);
    hist_line->Add(hist_line_l);
    hist_line->Add(hist_line_g);
    hist_line->Add(hist_line_puu);


/*
    float int_line = hist_line->Integral();
    if (int_line > 0.){
        hist_line->Scale(1./int_line);
        hist_line_b->Scale(1./int_line);
        hist_line_c->Scale(1./int_line);
        hist_line_l->Scale(1./int_line);
        hist_line_g->Scale(1./int_line);
        hist_line_puu->Scale(1./int_line);
        hist_line_bfromg->Scale(1./int_line);
        hist_line_cfromg->Scale(1./int_line);
    }
*/


/*
    cout << filename_x << "     " << hist_line_b->Integral() 
    << "     " << hist_line_c->Integral()  
    << "     " << hist_line_l->Integral()
    << "     " << hist_line_g->Integral()
    << "     " << hist_line_bfromg->Integral()
    << "     " << hist_line_cfromg->Integral() <<endl;
*/

    double titleoffsety=0.2;
    double titlesizey=0.2;
    hist_line->GetYaxis()->SetTitleSize(titlesizey);
    hist_line->GetYaxis()->SetTitleOffset(titleoffsety);

    hist_line->SetLineWidth(iLwidth);
    hist_line->SetLineColor(icolor);
    hist_line->SetMarkerStyle(iMstyle);  
    hist_line->SetMarkerSize(xMsize);
    hist_line->SetMarkerColor(icolor);

/*
    hist_line_b->SetLineColor(kRed+2);
    hist_line_b->SetMarkerColor(kRed+2);
    hist_line_b->SetLineWidth(2);
    hist_line_b->SetFillStyle(0);
    hist_line_bfromg->SetLineColor(kCyan+2);
    hist_line_bfromg->SetMarkerColor(kCyan+2);
    hist_line_bfromg->SetLineWidth(2);
    hist_line_bfromg->SetFillStyle(0);
    hist_line_c->SetLineColor(kGreen+2);
    hist_line_c->SetMarkerColor(kGreen+2);
    hist_line_c->SetLineWidth(2);
    hist_line_c->SetFillStyle(0);
    hist_line_cfromg->SetLineColor(kMagenta+3);
    hist_line_cfromg->SetMarkerColor(kMagenta+3);
    hist_line_cfromg->SetLineWidth(2);
    hist_line_cfromg->SetFillStyle(0);
    hist_line_l->SetLineColor(kBlack);
    hist_line_l->SetMarkerColor(kBlack);
    hist_line_l->SetLineWidth(2);
    hist_line_l->SetFillStyle(0);
    hist_line_g->SetLineColor(kBlack);
    hist_line_g->SetMarkerColor(kBlack);
    hist_line_g->SetLineWidth(2);
    hist_line_g->SetFillStyle(0);
    hist_line_puu->SetLineColor(kYellow);
    hist_line_puu->SetMarkerColor(kYellow);
    hist_line_puu->SetLineWidth(2);
    hist_line_puu->SetFillStyle(0);
*/

}

void DefineHratio(TString nameRatio, TH1D* & histo_ratio1, TH1D* hnum, TH1D* hdenum, int icolor, float xMsize, int iMstyle, int iLwidth )
{
    histo_ratio1 = (TH1D*) hnum->Clone();
    histo_ratio1->SetName(nameRatio);
    histo_ratio1->SetTitle(""); 
    histo_ratio1->Divide(hdenum);

    double titlesizex=0.17;
    double labelsizex=0.14;
    histo_ratio1->GetYaxis()->SetNdivisions( 505 );
    histo_ratio1->GetXaxis()->SetLabelSize( labelsizex);
    histo_ratio1->GetXaxis()->SetTitleSize( titlesizex );
    histo_ratio1->GetYaxis()->SetLabelSize( 0.1);

    histo_ratio1->SetLineWidth(iLwidth);
    histo_ratio1->SetLineColor(icolor);
    histo_ratio1->SetMarkerStyle(iMstyle);  
    histo_ratio1->SetMarkerSize(xMsize);
    histo_ratio1->SetMarkerColor(icolor);
}

void DefineHgen(TString filename_x, TString name, TH1D* & hist_fill, int iColor)
{

    TFile *fileFill     = new TFile(filename_x);
    fileFill->cd();
    hist_fill       = (TH1D*)gROOT->FindObject(name);
    if (bOverflow) {
        OverFlowBinFix(hist_fill);
    }

    float int_fill = hist_fill->Integral();
//    hist_fill->Scale(1./int_fill);

    double titleoffsety=0.65;
    double titlesizey=0.08;
     
    hist_fill->GetYaxis()->SetTitleSize(titlesizey);
    hist_fill->GetYaxis()->SetTitleOffset(titleoffsety);
  
    hist_fill->SetLineColor(iColor);
}

void PrintEff(TString nametag){

    TH1D* hist_data1;
    TH1D* hist_data2;
    TH1D* hist_data3;
    TH1D* hist_data4;
    TH1D* hist_data5;
    TH1D* hist_data6;
    TH1D* hist_data7;
    TH1D* hist_data8;

    TH1D* hist_totda1;
    TH1D* hist_totda2;
    TH1D* hist_totda3;
    TH1D* hist_totda4;
    TH1D* hist_totda5;
    TH1D* hist_totda6;
    TH1D* hist_totda7;
    TH1D* hist_totda8;


// jet_eta_deepcsv_l
// jet_eta
// jet_pt_csvv2_l
// jet_pt_deepfl_m

    TString name="jet_pt_"+nametag;
    TFile *myFile1     = new TFile(filename1);
    myFile1->cd();
    hist_data1      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda1      = (TH1D*)gROOT->FindObject("jet_pt_all_data");

    if(booname2) {
    TFile *myFile2     = new TFile(filename2);
    myFile2->cd();
    hist_data2      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda2      = (TH1D*)gROOT->FindObject("jet_pt_all_data");
    }

    if(booname3) {
    TFile *myFile3     = new TFile(filename3);
    myFile3->cd();
    hist_data3      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda3      = (TH1D*)gROOT->FindObject("jet_pt_all_data");
    }
    if(booname4) {
    TFile *myFile4     = new TFile(filename4);
    myFile4->cd();
    hist_data4      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda4      = (TH1D*)gROOT->FindObject("jet_pt_all_data");
    }
    if(booname5) {
    TFile *myFile5     = new TFile(filename5);
    myFile5->cd();
    hist_data5      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda5      = (TH1D*)gROOT->FindObject("jet_pt_all_data");
    }
    if(booname6) {
    TFile *myFile6     = new TFile(filename6);
    myFile6->cd();
    hist_data6      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda6      = (TH1D*)gROOT->FindObject("jet_pt_all_data");
    }
    if(booname7) {
    TFile *myFile7     = new TFile(filename7);
    myFile7->cd();
    hist_data7      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda7      = (TH1D*)gROOT->FindObject("jet_pt_all_data");
    }
    if(booname8) {
    TFile *myFile8     = new TFile(filename8);
    myFile8->cd();
    hist_data8      = (TH1D*)gROOT->FindObject(name+"_data");
    hist_totda8      = (TH1D*)gROOT->FindObject("jet_pt_all_data");
    }


    cout << " Efficency for "<< name << endl;
    cout << qwname1 << "   "<< hist_data1->Integral()/hist_totda1->Integral() << "   "  << sqrt(hist_data1->Integral()*(hist_totda1->Integral()-hist_data1->Integral())*1./(1.*hist_totda1->Integral()))/(1.*hist_totda1->Integral()) << endl;
    if(booname2) {cout << qwname2 << "   "<< hist_data2->Integral()/hist_totda2->Integral() <<"   "  <<  sqrt(hist_data2->Integral()*(hist_totda2->Integral()-hist_data2->Integral())*1./(1.*hist_totda2->Integral()))/(1.*hist_totda2->Integral())  <<endl;}
    if(booname3) {cout << qwname3 << "   "<< hist_data3->Integral()/hist_totda3->Integral() << "   "  << sqrt(hist_data3->Integral()*(hist_totda3->Integral()-hist_data3->Integral())*1./(1.*hist_totda3->Integral()))/(1.*hist_totda3->Integral())  <<endl;}
    if(booname4) {cout << qwname4 << "   "<< hist_data4->Integral()/hist_totda4->Integral() << "   "  << sqrt(hist_data4->Integral()*(hist_totda4->Integral()-hist_data4->Integral())*1./(1.*hist_totda4->Integral()))/(1.*hist_totda4->Integral())  <<endl;}
    if(booname5) {cout << qwname5 << "   "<< hist_data5->Integral()/hist_totda5->Integral() << "   "  << sqrt(hist_data5->Integral()*(hist_totda5->Integral()-hist_data5->Integral())*1./(1.*hist_totda5->Integral()))/(1.*hist_totda5->Integral())  <<endl;}
    if(booname6) {cout << qwname6 << "   "<< hist_data6->Integral()/hist_totda6->Integral() << "   "  << sqrt(hist_data6->Integral()*(hist_totda6->Integral()-hist_data6->Integral())*1./(1.*hist_totda6->Integral()))/(1.*hist_totda6->Integral())  <<endl;}
    if(booname7) {cout << qwname7 << "   "<< hist_data7->Integral()/hist_totda7->Integral() << "   "  << sqrt(hist_data7->Integral()*(hist_totda7->Integral()-hist_data7->Integral())*1./(1.*hist_totda7->Integral()))/(1.*hist_totda7->Integral())  <<endl;}
    if(booname8) {cout << qwname8 << "   "<< hist_data8->Integral()/hist_totda8->Integral() << "   "  << sqrt(hist_data8->Integral()*(hist_totda8->Integral()-hist_data8->Integral())*1./(1.*hist_totda8->Integral()))/(1.*hist_totda8->Integral())  <<endl;}
    cout << endl;
}

