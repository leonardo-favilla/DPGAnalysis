void RateVsLumi(){
  TFile *f8149 = TFile::Open("/eos/home-f/fcarneva/ZB_2022/RPCNtuple.root");
  TTree *event_tree_8149 = (TTree*) f8149->Get("demo/event_tree");
  TTree *hit_tree_8149 = (TTree*) f8149->Get("demo/hit_tree");

  TH1F *lumi_8149 = new TH1F("lumi_8149","lumi_8149",21,-0.5,20.5);
  TH2F *Wm2RB1in_8149 = new TH2F("Wm2RB1in_8149","Wm2RB1in_8149",21,-0.5,20.5,7,-3.5,3.5);
  event_tree_8149->Project("lumi_8149","lumi","lumi>7.5");
  hit_tree_8149->Project("Wm2RB1in_8149","RPCbx:lumi","region==0 && lumi>7.5 && station==1 && layer==1 && ring==-2 && RPC_Id!=637567757");
  TH1F *proj_barrel_8149 = (TH1F *) Wm2RB1in_8149->ProjectionX()->Clone();
  proj_barrel_8149->Sumw2();
  lumi_8149->Sumw2();
  proj_barrel_8149->Divide(lumi_8149);
  proj_barrel_8149->Scale(1./(5*25e-9*(572680.00+25791.199-49872.6)));
  proj_barrel_8149->Draw();

  TH2F *Wp1RB4_8149 = new TH2F("Wp1RB4_8149","Wp1RB4_8149",21,-0.5,20.5,7,-3.5,3.5);
  hit_tree_8149->Project("Wp1RB4_8149","RPCbx:lumi","region==0 && lumi>7.5 && station==4 && ring==+1 && sector!=4 && RPC_Id!=637568249 && RPC_Id!=637633785");
  TH1F *proj_barrel_8149_ = (TH1F *) Wp1RB4_8149->ProjectionX()->Clone();
  proj_barrel_8149_->Sumw2();
  proj_barrel_8149_->Divide(lumi_8149);
  proj_barrel_8149_->Scale(1./(5*25e-9*(462924+495792-60040.800)));
  proj_barrel_8149_->Draw("same");



  TH2F *REp42_8149 = new TH2F("REp42_8149","REp42_8149",21,-0.5,20.5,7,-3.5,3.5);
  hit_tree_8149->Project("REp42_8149","RPCbx:lumi","region==1 && lumi>7.5 && station==4 && ring==2 && RPC_Id!=637604582 && RPC_Id!=637579750 && RPC_Id!=637612518 && RPC_Id!=637645286 && RPC_Id!=637587942 && RPC_Id!=637620710 && RPC_Id!=637653478");
  TH1F *proj_endcap_8149 = (TH1F *) REp42_8149->ProjectionX()->Clone();
  proj_endcap_8149->Sumw2();
  lumi_8149->Sumw2();
  proj_endcap_8149->Divide(lumi_8149);
  proj_endcap_8149->Scale(1./(5*25e-9*(399554.30)));
  proj_endcap_8149->Draw("same");

  TFile *f8148 = TFile::Open("/eos/home-f/fcarneva/ZB_2022_Scheme8148/RPCNtuple.root");
  TTree *event_tree_8148 = (TTree*) f8148->Get("demo/event_tree");
  TTree *hit_tree_8148 = (TTree*) f8148->Get("demo/hit_tree");

  TH1F *lumi_8148 = new TH1F("lumi_8148","lumi_8148",21,-0.5,20.5);
  TH2F *Wm2RB1in_8148 = new TH2F("Wm2RB1in_8148","Wm2RB1in_8148",21,-0.5,20.5,7,-3.5,3.5);
  event_tree_8148->Project("lumi_8148","lumi","lumi>9.5");
  hit_tree_8148->Project("Wm2RB1in_8148","RPCbx:lumi","region==0 && lumi>9.5 && station==1 && layer==1 && ring==-2 && RPC_Id!=637567757");
  TH1F *proj_barrel_8148 = (TH1F *) Wm2RB1in_8148->ProjectionX()->Clone();
  proj_barrel_8148->Sumw2();
  lumi_8148->Sumw2();
  proj_barrel_8148->Divide(lumi_8148);
  proj_barrel_8148->Scale(1./(5*25e-9*(572680.00+25791.199-49872.6)));
  proj_barrel_8148->SetLineColor(kRed);
  proj_barrel_8148->Draw("esame");

  TH2F *REp42_8148 = new TH2F("REp42_8148","REp42_8148",21,-0.5,20.5,7,-3.5,3.5);
  hit_tree_8148->Project("REp42_8148","RPCbx:lumi","region==1 && lumi>9.5 && station==4 && ring==2 && RPC_Id!=637604582 && RPC_Id!=637579750 && RPC_Id!=637612518 && RPC_Id!=637645286 && RPC_Id!=637587942 && RPC_Id!=637620710 && RPC_Id!=637653478");
  TH1F *proj_endcap_8148 = (TH1F *) REp42_8148->ProjectionX()->Clone();
  proj_endcap_8148->Sumw2();
  lumi_8148->Sumw2();
  proj_endcap_8148->Divide(lumi_8148);
  proj_endcap_8148->Scale(1./(5*25e-9*(399554.30)));
  proj_endcap_8148->Draw("same");

  TH2F *Wp1RB4_8148 = new TH2F("Wp1RB4_8148","Wp1RB4_8148",21,-0.5,20.5,7,-3.5,3.5);
  hit_tree_8148->Project("Wp1RB4_8148","RPCbx:lumi","region==0 && lumi>9.5 && station==4 && ring==+1 && sector!=4 && RPC_Id!=637568249 && RPC_Id!=637633785");
  TH1F *proj_barrel_8148_ = (TH1F *) Wp1RB4_8148->ProjectionX()->Clone();
  proj_barrel_8148_->Sumw2();
  proj_barrel_8148_->Divide(lumi_8148);
  proj_barrel_8148_->Scale(1./(5*25e-9*(462924+495792-60040.800)));
  proj_barrel_8148_->Draw("same");


}
