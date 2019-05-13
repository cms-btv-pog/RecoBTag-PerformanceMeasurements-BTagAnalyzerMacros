{
   
    bool runOnData=false;
    bool runOnMC=true;
    // Declare the root files on which you want to run  (MC & Data) :
    TChain *superTree1 = new TChain("btagana/ttree");
    TChain *superTree2 = new TChain("btagana/ttree");


    int which_case=2;

    if (which_case==1) {

    // Data 
      if (runOnData) {
        
        // 2016 legacy
/*
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016B_ver2_v2/181221_143254/0000/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016B_ver2_v2/181221_143254/0001/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016B_ver2_v2/181221_143254/0002/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016C/181221_143901/0000/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016D/181221_143917/0000/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016D/181221_143917/0001/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016E/181221_143934/0000/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016F/181221_143958/0000/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016G/181221_144017/0000/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016G/181221_144017/0001/JetTree_data_*root");
*/
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016H/181221_144035/0000/JetTree_data_*root");
        superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/JetHT/run2016H/181221_144035/0001/JetTree_data_*root");
/*
*/
      }

    // MC



      if (runOnMC) {
       superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8/incl_qcd_30/190102_172429/0000/J*root");
       superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/incl_qcd_50/190102_172451/0000/J*root");
       superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/incl_qcd_80/190102_172507/0000/J*root");
       superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/incl_qcd_120/190102_172523/0000/J*root");
       superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/incl_qcd_170/190102_172541/0000/J*root");
       superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/incl_qcd_300/190102_172557/0000/J*root");
       superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/incl_qcd_470/190102_172614/0000/J*root");
      }


    }

    else if (which_case==2) {

      if (runOnData) {
         //2016 legacy
/*
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016B_ver2_v1/181221_143254/0000/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016B_ver2_v1/181221_143254/0001/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016B_ver2_v1/181221_143254/0002/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016C/181221_145128/0000/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016D/181221_145145/0000/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016D/181221_145145/0001/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016E/181221_145202/0000/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016F/181221_145219/0000/JetTree_data_*root");
*/

         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016G/181221_145235/0000/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016G/181221_145235/0001/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016H/181221_145251/0000/JetTree_data_*root");
         superTree1->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/BTagMu/run2016H/181221_145251/0001/JetTree_data_*root");

      }
      if (runOnMC) {
       // for trig 40:
       // superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_20/190107_095810/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_30/190107_095409/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_50/190107_095753/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_80/190107_095829/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_120/190110_101349/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_170/190107_095904/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_300/190107_095920/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_470/190107_095936/0000/J*root");
       
       /* //for trig 170 :
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_170/190107_095904/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_300/190107_095920/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_470/190107_095936/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_600/190107_095953/0000/J*root");
        superTree2->Add("/opt/sbg/cms/ui3_data1/ccollard/BTAntuples/legacy2016/MC_v2/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/muen_qcd_800/190107_100010/0000/J*root");
      */




      }
    
    

    }


    CommPlotProducer m_data(superTree1);
    CommPlotProducer m_mc(superTree2);


    // Setting up of the information
    // with generator = pythia or herwig, qcdtype =0 for inclusive or 1 for MuEnriched, and TeV = 8 or 13.
    if (which_case==1) {
      m_mc.SetInfo("pythia",0,13);
    }
    else if (which_case==2) {
      m_mc.SetInfo("pythia",1,13);
    }
 
    // Here put the number of events for each samples you are running on.
    // BE CAREFULL !!!!!
    // You should enter 12 numbers and following the increasing order in pthat of the MC samples.
    // n15_20, n20_30, n30_50, n50_80,  n80_120,  n120_170, n170_300,  n300_470,  n470_600, n600_800, n800_1000, n1000 ;
    //
    //  -->  m.Fill_nevent(n15_20,n20_30,n30_50,n50_80,n80_120,n120_170,n170_300,n300_470,n470_600,n600_800,n800_1000,n1000);
    //       for muenriched pythia and herwig.
    //  or
    //  -->  m.Fill_nevent(    0.,n15_30,n30_50,n50_80,n80_120,n120_170,n170_300,n300_470,n470_600,n600_800,n800_1000,n1000);
    //       for inclusive pythia and herwig.
    //
    // If you want to run only on the 50-80 and 80-120 samples for pythia 8 TeV, the correct syntaxe is
    //   m.Fill_nevent(0,0,0,n50_80,n80_120,0,0,0,0,0,0,0);
    //
    // Remark for 7TeV QCD MC:
    // for  inclusive QCD pythia at 7TeV, provide : 
    //  -->  m.Fill_nevent(    0.,n15_30,n30_50,n50_80,n80_120,n120_170,n170_300,n300,0.,0.,0.,0.);
    // for  MuEnriched QCD pythia at 7TeV, provide : 
    //  -->  m.Fill_nevent(    0.,n15_30,n30_50,n50_80,n80_120,n120_150,n150,0.,0.,0.,0.,0.);
    //
    // if you don't know how many events you have in your datasets
    // m.Counter(); --> TAKES 4 HOURS ON DATA+MC :(

   
//   m.Fill_nevent(n15_20,n20_30,n30_50,n50_80,n80_120,n120_170,n170_300,n300_470,n470_600,n600_800,n800_1000,n1000);
    double   n15    = 0;
    double   n20    = 0;
    double   n30    = 0; 
    double   n50    = 0;
    double   n80   =  0;
    double   n120  =  0;
    double   n170  =  0;
    double   n300  = 0;
    double   n470  = 0;
    double   n600  = 0;
    double   n800 = 0;
    double   n1000     = 0;


    if (which_case==1) {
            n20   =  0.;
            n30   =  9980049.;
            n50   =  9954369.;
            n80   =  7464822.;
            n120  =  5748736.;
            n170  =  5857344.;
            n300  =  14829856.;
            n470  =  9133725.;
	    n600  =  0.;
            n800  =  0.;
            n1000  =  0.;
    }
    else if (which_case==2) {
            n15    = 0.;
            n20    = 31297935.;
            n30    = 29809491.;
            n50    = 19227438.;
            n80   =  13605664.;
            n120  =  11622224.;
            n170  =  19644782.;
            n300  =  7937587.;
            n470  =  3972818.;
            n600  =  9782975.;
            n800  =  8226448.;
            n1000 = 0;

    }

    m_mc.Fill_nevent(n15,n20,n30,n50,n80,n120,n170,n300,n470,n600,n800,n1000);

    m_mc.SetXS();     // Assign the correct x-sections to QCD pthat bins, depending on SetInfo(), default = use inclusive pythia x-sections for 8 TeV.
    m_mc.SetSumXS();  // Compute the Total x-section of all the samples

   
    // no PU info
    if (runOnMC) {
     if (which_case==1) m_mc.SetPV("jetht_2016_tot_trig40_50_250_pvweight.root");  // use PV
//     else if (which_case==2) m_mc.SetPV("jetht_2016_tot_trig40_50_250_pvweight.root","btag_2016_tot_trig170_200_450.root");
     else if (which_case==2) m_mc.SetPV("jetht_2016_tot_trig40_50_250_pvweight.root","btag_2016_tot_trig40_50_250.root");
    }

/////      m_mc.SetPV("incl_mc_2018.root","jetht_2018.root");  // use PV
/////      m_mc.SetPV("plot_v1/incl_mc_2018.root","jetht_2018_v2.root");  // use PV
//    m_mc.SetJetPtCorr("musel_2fb1_dj40_pt.root","musel_2fb1_dj40_pv.root");  // use PV
   
//    m_data.SetPersonalConfig(false, false, false, false);
//    m_mv.SetPersonalConfig(false, false, false, false);

////    m_data.SetPS();

    if (which_case==1) {
      if (runOnData)  m_data.Loop("jet", 40, 50, 250,   "jetht_2016_runh_trig40_50_250");
      if (runOnMC)    m_mc.Loop("jet", 40, 50, 250,   "inclmc_2016_trig40_50_250_pvweight");
    }
    else if (which_case==2) {
//      if (runOnData)  m_data.Loop("btag", 40, 50, 250,   "btag_2016_runb2f_trig40_50_250");
      if (runOnData)  m_data.Loop("btag", 170, 200, 450,   "btag_2016_rung2h_trig170_200_450");
//      if (runOnMC)    m_mc.Loop("btag", 170, 200, 450,   "muemc_2016_trig170_200_450_pseudopvweight");
      if (runOnMC)    m_mc.Loop("btag", 40, 50, 250,   "muemc_2016_trig40_50_250_pseudopvweight");
    }

   
}
