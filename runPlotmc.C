{
//gROOT->ProcessLine(".L DrawCommPlot.C++");
DrawMCgen("nPV_mc","nPV",0);
DrawMCCompare("jet_pt_all","Jets/10","jet p_{T} (GeV)", 1,100);
DrawMCCompare("jet_pt_all","Jets/10","jet p_{T} (GeV)", 0,0);
DrawMCCompare("jet_eta","Jets/0.25","Jet #eta",0,0);
DrawMCCompare("jet_phi","Jets/0.314","Jet #phi (rad)",0,0);
DrawMCCompare("jet_phi_deepcsv_l","Jets passing DeepCSV L/0.126","Jet #phi (rad)",0,0);
DrawMCCompare("jet_phi_deepcsv_m","Jets passing DeepCSV M/0.126","Jet #phi (rad)",0,0);
DrawMCCompare("jet_phi_deepcsv_t","Jets passing DeepCSV T/0.126","Jet #phi (rad)",0,0);
DrawMCCompare("trk_multi_sel"  ,"Jets",     "Number of selected tracks in the jets",0,0);
DrawMCCompare("track_pt"     , "Tracks/2.5",      "Track p_{T} (GeV)",1,0.5);
DrawMCCompare("track_pt"     , "Tracks/2.5",      "Track p_{T} (GeV)",0,0.);
DrawMCCompare("track_pt15"     , "Tracks/0.1",      "Track p_{T} (GeV)",1,0.5);
DrawMCCompare("track_pt15"     , "Tracks/0.1",      "Track p_{T} (GeV)",0,0.);
DrawMCCompare("track_nHit" , "Tracks",      "Number of hits",0,0);
DrawMCCompare("track_HPix"   , "Tracks",      "Number of hits in the Pixel",0,0);
DrawMCCompare("track_len"     , "Tracks/0.05",     "Track decay length (cm)",1,10);
DrawMCCompare("track_len"     , "Tracks/0.05",     "Track decay length (cm)",0,0);
DrawMCCompare("track_dist"    , "Tracks/0.00008",     "Track distance to the jet axis (cm)"   ,1,10);
DrawMCCompare("track_dist"    , "Tracks/0.00008",     "Track distance to the jet axis (cm)"   ,0,0);
DrawMCCompare("track_chi2"    , "Tracks","Normalized #chi^{2} of tracks",1,10);
DrawMCCompare("track_chi2"    , "Tracks","Normalized #chi^{2} of tracks",0,0);
DrawMCCompare("track_IPs"    , "Tracks/0.7",      "3D IP significance of tracks",1, 20.);
DrawMCCompare("track_IPs"    , "Tracks/0.7",      "3D IP significance of tracks",0, 0.);
DrawMCCompare("track_IP"    , "Tracks/0.002",      "3D IP of tracks",1, 20.);
DrawMCCompare("track_IP"    , "Tracks/0.002",      "3D IP of tracks",0, 0.);
DrawMCCompare("track_IPerr"    , "Tracks/0.001",      "3D IP errors of tracks",1, 20.);
DrawMCCompare("track_IPerr"    , "Tracks/0.001",      "3D IP errors of tracks",0, 0.);
DrawMCCompare("sv_multi_0","Jets","Number of SVs",1,10);
DrawMCCompare("sv_multi_0","Jets","Number of SVs",0,0);
DrawMCCompare("sv_deltaR_jet","SVs/0.01","#Delta R(SV direction,jet)",0,0);
DrawMCCompare("sv_flight3DSig","SVs/2","SV 3D flight distance significance",1, 10.);
DrawMCCompare("sv_flight3DSig","SVs/2","SV 3D flight distance significance",0, 0.);
DrawMCCompare("tagvarCSV_vertexCategory"    , "Jets",     "Vertex category in CSVv2",1, 100.);
DrawMCCompare("tagvarCSV_vertexCategory"    , "Jets",     "Vertex category in CSVv2",0, 0.);
DrawMCCompare("tagvarCSV_vertexmass_cat0","SVs/0.2","SV mass (GeV)", 0,0);
DrawMCCompare("tagvarCSV_vertexmass3trk_cat0","SVs/0.2", "SV mass (at least 3 tracks) (GeV)", 0,0);
DrawMCCompare("tagvarCSV_vertexJetDeltaR_cat0","SVs","#Delta R(SV direction,jet)",0,0);
DrawMCCompare("tagvarCSV_energyratio","SVs/0.025","Fractional energy",1,10);
DrawMCCompare("tagvarCSV_energyratio","SVs/0.025","Fractional energy",0,0);
DrawMCCompare("tagvarCSV_Sig2dAboveCharm","Jets/3.5","IP significance 2D charm",1,10);
DrawMCCompare("tagvarCSV_Sig2dAboveCharm","Jets/3.5","IP significance 2D charm",0,0);
DrawMCCompare("pfmuon_multi"   ,"Jets",      "Number of muons", 1, 1.);
DrawMCCompare("pfmuon_multi"   ,"Jets",      "Number of muons", 0, 0.);
DrawMCCompare("pfmuon_ptrel"     ,"Muons/0.125",      "p_{T} rel. of the muon",0,0);
DrawMCCompare("pfmuon_pt","Muons/2",             "Muon p_{T} (GeV)",1,1);
DrawMCCompare("pfmuon_pt","Muons/2",             "Muon p_{T} (GeV)",0,0);
DrawMCCompare("pfmuon_ip","Muons"    ,      "IP of the muon",1,1);
DrawMCCompare("pfmuon_deltar"   ,"Muons",      "#Delta R(#mu,jet)",1,1);
DrawMCCompare("pfmuon_deltar"   ,"Muons" ,      "#Delta R(#mu,jet)",0,0);
DrawMCCompare("pfmuon_eta","Muons",             "Muon #eta",0,0);
DrawMCCompare("pfmuon_phi","Muons",             "Muon #phi (rad)",0,0);
DrawMCCompare("pfmuonqual_ptrel"     ,"Muons/0.125",      "p_{T} rel. of the muon",0,0);
DrawMCCompare("pfmuonqual_pt","Muons/2",             "Muon p_{T} (GeV)",1,1);
DrawMCCompare("pfmuonqual_pt","Muons/2",             "Muon p_{T} (GeV)",0,0);
DrawMCCompare("pfmuonqual_ip","Muons"    ,      "IP of the muon",1,1);
DrawMCCompare("pfmuonqual_deltar"   ,"Muons",      "#Delta R(#mu,jet)",1,1);
DrawMCCompare("pfmuonqual_deltar"   ,"Muons" ,      "#Delta R(#mu,jet)",0,0);
DrawMCCompare("pfmuonqual_eta","Muons",             "Muon #eta",0,0);
DrawMCCompare("pfmuonqual_phi","Muons",             "Muon #phi (rad)",0,0);


DrawMCCompare("CSVIVF","Jets/0.02","CSVv2 Discriminator",1,10.);

DrawMCCompare("CSVIVF","Jets/0.02","CSVv2 Discriminator",0,0.);
DrawMCCompare("DeepCSV","Jets/0.02","DeepCSV Discriminator",1,10.);
DrawMCCompare("DeepCSV","Jets/0.02","DeepCSV Discriminator",0,0.);

DrawMCCompare("DeepFlavour","Jets/0.02","DeepJet Discriminator",1,10.);
DrawMCCompare("DeepFlavour","Jets/0.02","DeepJet Discriminator",0,0.);

DrawMCCompare("CvsL_deep","Jets","CvsL_deep Discriminator",1,10.);
DrawMCCompare("CvsL_deep","Jets","CvsL_deep Discriminator",0,0.);
DrawMCCompare("CvsB_deep","Jets","CvsB_deep Discriminator",1,10.);
DrawMCCompare("CvsB_deep","Jets","CvsB_deep Discriminator",0,0.);

DrawMCCompare("CvsL_flav","Jets","CvsL_flav Discriminator",1,10.);
DrawMCCompare("CvsL_flav","Jets","CvsL_flav Discriminator",0,0.);
DrawMCCompare("CvsB_flav","Jets","CvsB_flav Discriminator",1,10.);
DrawMCCompare("CvsB_flav","Jets","CvsB_flav Discriminator",0,0.);


DrawMCCompare("cTagCvsB","Jets","cTagCvsB Discriminator",1,10.);
DrawMCCompare("cTagCvsB","Jets","cTagCvsB Discriminator",0,0.);
DrawMCCompare("cTagCvsL","Jets","cTagCvsL Discriminator",1,10.);
DrawMCCompare("cTagCvsL","Jets","cTagCvsL Discriminator",0,0.);


DrawMCCompare("prob_DeepCSVb", "Jets",  "Jet_DeepCSVb",                 1,10.  );
DrawMCCompare("prob_DeepCSVc", "Jets",  "Jet_DeepCSVc",                 1,10.  );
DrawMCCompare("prob_DeepCSVl", "Jets",  "Jet_DeepCSVl",                 1,10.  );
DrawMCCompare("prob_DeepCSVbb", "Jets",  "Jet_DeepCSVbb",                 1,1.  );

DrawMCCompare("prob_DeepFlavourB", "Jets",  "Jet_DeepFlavourB",                 1,10.  );
DrawMCCompare("prob_DeepFlavourBB", "Jets",  "Jet_DeepFlavourBB",                 1,1.  );
DrawMCCompare("prob_DeepFlavourLEPB", "Jets",  "Jet_DeepFlavourLEPB",                 1,1.  );
DrawMCCompare("prob_DeepFlavourC", "Jets",  "Jet_DeepFlavourC",                 1,10.  );
DrawMCCompare("prob_DeepFlavourUDS", "Jets",  "Jet_DeepFlavourUDS",                 1,10.  );
DrawMCCompare("prob_DeepFlavourG", "Jets",  "Jet_DeepFlavourG",                 1,1.  );

DrawMCCompare("prob_DeepCSVb", "Jets",  "Jet_DeepCSVb",        0,0.);
DrawMCCompare("prob_DeepCSVc", "Jets",  "Jet_DeepCSVc",      0,0.);
DrawMCCompare("prob_DeepCSVl", "Jets",  "Jet_DeepCSVl",       0,0.);
DrawMCCompare("prob_DeepCSVbb", "Jets",  "Jet_DeepCSVbb",   0,0.);

DrawMCCompare("prob_DeepFlavourB", "Jets",  "Jet_DeepFlavourB",  0,0.);
DrawMCCompare("prob_DeepFlavourBB", "Jets",  "Jet_DeepFlavourBB",  0,0.);
DrawMCCompare("prob_DeepFlavourLEPB", "Jets",  "Jet_DeepFlavourLEPB",  0,0.);
DrawMCCompare("prob_DeepFlavourC", "Jets",  "Jet_DeepFlavourC",        0,0.);
DrawMCCompare("prob_DeepFlavourUDS", "Jets",  "Jet_DeepFlavourUDS",    0,0.);
DrawMCCompare("prob_DeepFlavourG", "Jets",  "Jet_DeepFlavourG",         0,0.);     



DrawMCCompare("SoftMu"    ,"Jets/0.02",      "SMT Discriminator",1,1.);
DrawMCCompare("SoftMu"    ,"Jets/0.02",      "SMT Discriminator",0,0.);
DrawMCCompare("SoftEl"    ,"Jets/0.02",      "SET Discriminator",1,10);
DrawMCCompare("SoftEl"    ,"Jets/0.02",      "SET Discriminator",0,0);

DrawMCCompare("df_neutral_drminsv","Jets/0.02","df_neutral_drminsv",1,10.);
DrawMCCompare("df_neutral_drminsv","Jets/0.02","df_neutral_drminsv",0,0.);
DrawMCCompare("df_neutral_hadFrac","Jets","df_neutral_hadFrac",1,10.);
DrawMCCompare("df_neutral_hadFrac","Jets","df_neutral_hadFrac",0,0.);
DrawMCCompare("df_neutral_ptrel","Jets/0.05","df_neutral_ptrel",1,10.);
DrawMCCompare("df_neutral_ptrel","Jets/0.05","df_neutral_ptrel",0,0.);
DrawMCCompare("df_charged_Sip3dSig","Jets/0.7","df_charged_Sip3dSig",1,10);
DrawMCCompare("df_charged_Sip3dSig","Jets/0.7","df_charged_Sip3dSig",0,0);
DrawMCCompare("df_charged_chi2","Jets/0.5","df_charged_chi2",1,1);
DrawMCCompare("df_charged_chi2","Jets/0.5","df_charged_chi2",0,0);
DrawMCCompare("df_sv_normchi2","Jets/20","df_sv_normchi2",1,10);
DrawMCCompare("df_sv_normchi2","Jets/20","df_sv_normchi2",0,0);
DrawMCCompare("df_sv_d3dsig","Jets/10","df_sv_d3dsig",1,10);
DrawMCCompare("df_sv_d3dsig","Jets/10","df_sv_d3dsig",0,0);


/*
 * gROOT->ProcessLine(".L DrawEfficiencyPlot.C++");
 * DrawROC("DeepCSV");
 * DrawROC("DeepFlavour");
 */
}
