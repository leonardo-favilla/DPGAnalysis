// Author Francesco Carnevali 2022
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/ESTransientHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include "DataFormats/RPCDigi/interface/RPCDigi.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
//#include "DataFormats/Scalers/interface/LumiScalers.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include <cmath> 
#include <map>
#include "TGraph.h"
#include "TGraphErrors.h"
#include <algorithm>
#include <fstream>
#include "TProfile.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TMath.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "DataFormats/OnlineMetaData/interface/OnlineLuminosityRecord.h"

//
// class declaration
//
using namespace std;
using namespace edm;

class RateVsLumi_PhiEtaRecompute : public edm::one::EDAnalyzer<edm::one::SharedResources>  
// class RateVsLumi_PhiEtaRecompute : public edm::EDAnalyzer  
{
   public:
      explicit RateVsLumi_PhiEtaRecompute(const edm::ParameterSet&);
      ~RateVsLumi_PhiEtaRecompute();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      // ----------member data ---------------------------
  
      edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitsLabel;
      edm::InputTag scalersSource_;
//      edm::EDGetTokenT<LumiScalersCollection> scalersSourceToken_;
//      edm::EDGetTokenT<OnlineLuminosityRecord> m_lumiScalerToken;
      edm::EDGetTokenT<OnlineLuminosityRecord> scalersSourceToken_;
//FIXME mileva
      edm::ESGetToken<RPCGeometry, MuonGeometryRecord> rpcGeoToken_;

      int lumiblock;
      int bunchNum;
      int bunchCross;
      int event=0;
      double lumiperblock;
      int lumi=0;



      std::string uncolliding_;
      int runNum;
      double orbitnumber=0;
      double area=0;

      bool debug;
      bool doAllBXs_;
      bool doAllBXno0_;
      int numbBXs_;
      bool doRechits_;
      std::string myBlackList_;

      double area_barrel=0.;
      int numhit=0;

      //bool low=false;

      // RB1in
    
      TH2F *bx_Wm2_RB1in_S01_high;
      TH2F *bx_Wm2_RB1in_S02_high;
      TH2F *bx_Wm2_RB1in_S03_high;
      TH2F *bx_Wm2_RB1in_S04_high;
      TH2F *bx_Wm2_RB1in_S05_high;
      TH2F *bx_Wm2_RB1in_S06_high;
      TH2F *bx_Wm2_RB1in_S07_high;
      TH2F *bx_Wm2_RB1in_S08_high;
      TH2F *bx_Wm2_RB1in_S09_high;
      TH2F *bx_Wm2_RB1in_S10_high;
      TH2F *bx_Wm2_RB1in_S11_high;
      TH2F *bx_Wm2_RB1in_S12_high;

      TH2F *bx_Wm1_RB1in_S01_high;
      TH2F *bx_Wm1_RB1in_S02_high;
      TH2F *bx_Wm1_RB1in_S03_high;
      TH2F *bx_Wm1_RB1in_S04_high;
      TH2F *bx_Wm1_RB1in_S05_high;
      TH2F *bx_Wm1_RB1in_S06_high;
      TH2F *bx_Wm1_RB1in_S07_high;
      TH2F *bx_Wm1_RB1in_S08_high;
      TH2F *bx_Wm1_RB1in_S09_high;
      TH2F *bx_Wm1_RB1in_S10_high;
      TH2F *bx_Wm1_RB1in_S11_high;
      TH2F *bx_Wm1_RB1in_S12_high;

      TH2F *bx_W0_RB1in_S01_high;
      TH2F *bx_W0_RB1in_S02_high;
      TH2F *bx_W0_RB1in_S03_high;
      TH2F *bx_W0_RB1in_S04_high;
      TH2F *bx_W0_RB1in_S05_high;
      TH2F *bx_W0_RB1in_S06_high;
      TH2F *bx_W0_RB1in_S07_high;
      TH2F *bx_W0_RB1in_S08_high;
      TH2F *bx_W0_RB1in_S09_high;
      TH2F *bx_W0_RB1in_S10_high;
      TH2F *bx_W0_RB1in_S11_high;
      TH2F *bx_W0_RB1in_S12_high;

      TH2F *bx_Wp1_RB1in_S01_high;
      TH2F *bx_Wp1_RB1in_S02_high;
      TH2F *bx_Wp1_RB1in_S03_high;
      TH2F *bx_Wp1_RB1in_S04_high;
      TH2F *bx_Wp1_RB1in_S05_high;
      TH2F *bx_Wp1_RB1in_S06_high;
      TH2F *bx_Wp1_RB1in_S07_high;
      TH2F *bx_Wp1_RB1in_S08_high;
      TH2F *bx_Wp1_RB1in_S09_high;
      TH2F *bx_Wp1_RB1in_S10_high;
      TH2F *bx_Wp1_RB1in_S11_high;
      TH2F *bx_Wp1_RB1in_S12_high;

      TH2F *bx_Wp2_RB1in_S01_high;
      TH2F *bx_Wp2_RB1in_S02_high;
      TH2F *bx_Wp2_RB1in_S03_high;
      TH2F *bx_Wp2_RB1in_S04_high;
      TH2F *bx_Wp2_RB1in_S05_high;
      TH2F *bx_Wp2_RB1in_S06_high;
      TH2F *bx_Wp2_RB1in_S07_high;
      TH2F *bx_Wp2_RB1in_S08_high;
      TH2F *bx_Wp2_RB1in_S09_high;
      TH2F *bx_Wp2_RB1in_S10_high;
      TH2F *bx_Wp2_RB1in_S11_high;
      TH2F *bx_Wp2_RB1in_S12_high;

      // RB1out
    
      TH2F *bx_Wm2_RB1out_S01_high;
      TH2F *bx_Wm2_RB1out_S02_high;
      TH2F *bx_Wm2_RB1out_S03_high;
      TH2F *bx_Wm2_RB1out_S04_high;
      TH2F *bx_Wm2_RB1out_S05_high;
      TH2F *bx_Wm2_RB1out_S06_high;
      TH2F *bx_Wm2_RB1out_S07_high;
      TH2F *bx_Wm2_RB1out_S08_high;
      TH2F *bx_Wm2_RB1out_S09_high;
      TH2F *bx_Wm2_RB1out_S10_high;
      TH2F *bx_Wm2_RB1out_S11_high;
      TH2F *bx_Wm2_RB1out_S12_high;

      TH2F *bx_Wm1_RB1out_S01_high;
      TH2F *bx_Wm1_RB1out_S02_high;
      TH2F *bx_Wm1_RB1out_S03_high;
      TH2F *bx_Wm1_RB1out_S04_high;
      TH2F *bx_Wm1_RB1out_S05_high;
      TH2F *bx_Wm1_RB1out_S06_high;
      TH2F *bx_Wm1_RB1out_S07_high;
      TH2F *bx_Wm1_RB1out_S08_high;
      TH2F *bx_Wm1_RB1out_S09_high;
      TH2F *bx_Wm1_RB1out_S10_high;
      TH2F *bx_Wm1_RB1out_S11_high;
      TH2F *bx_Wm1_RB1out_S12_high;

      TH2F *bx_W0_RB1out_S01_high;
      TH2F *bx_W0_RB1out_S02_high;
      TH2F *bx_W0_RB1out_S03_high;
      TH2F *bx_W0_RB1out_S04_high;
      TH2F *bx_W0_RB1out_S05_high;
      TH2F *bx_W0_RB1out_S06_high;
      TH2F *bx_W0_RB1out_S07_high;
      TH2F *bx_W0_RB1out_S08_high;
      TH2F *bx_W0_RB1out_S09_high;
      TH2F *bx_W0_RB1out_S10_high;
      TH2F *bx_W0_RB1out_S11_high;
      TH2F *bx_W0_RB1out_S12_high;

      TH2F *bx_Wp1_RB1out_S01_high;
      TH2F *bx_Wp1_RB1out_S02_high;
      TH2F *bx_Wp1_RB1out_S03_high;
      TH2F *bx_Wp1_RB1out_S04_high;
      TH2F *bx_Wp1_RB1out_S05_high;
      TH2F *bx_Wp1_RB1out_S06_high;
      TH2F *bx_Wp1_RB1out_S07_high;
      TH2F *bx_Wp1_RB1out_S08_high;
      TH2F *bx_Wp1_RB1out_S09_high;
      TH2F *bx_Wp1_RB1out_S10_high;
      TH2F *bx_Wp1_RB1out_S11_high;
      TH2F *bx_Wp1_RB1out_S12_high;

      TH2F *bx_Wp2_RB1out_S01_high;
      TH2F *bx_Wp2_RB1out_S02_high;
      TH2F *bx_Wp2_RB1out_S03_high;
      TH2F *bx_Wp2_RB1out_S04_high;
      TH2F *bx_Wp2_RB1out_S05_high;
      TH2F *bx_Wp2_RB1out_S06_high;
      TH2F *bx_Wp2_RB1out_S07_high;
      TH2F *bx_Wp2_RB1out_S08_high;
      TH2F *bx_Wp2_RB1out_S09_high;
      TH2F *bx_Wp2_RB1out_S10_high;
      TH2F *bx_Wp2_RB1out_S11_high;
      TH2F *bx_Wp2_RB1out_S12_high;

      TH2F *bx_Wm2_RB2in_S01_high;
      TH2F *bx_Wm2_RB2in_S02_high;
      TH2F *bx_Wm2_RB2in_S03_high;
      TH2F *bx_Wm2_RB2in_S04_high;
      TH2F *bx_Wm2_RB2in_S05_high;
      TH2F *bx_Wm2_RB2in_S06_high;
      TH2F *bx_Wm2_RB2in_S07_high;
      TH2F *bx_Wm2_RB2in_S08_high;
      TH2F *bx_Wm2_RB2in_S09_high;
      TH2F *bx_Wm2_RB2in_S10_high;
      TH2F *bx_Wm2_RB2in_S11_high;
      TH2F *bx_Wm2_RB2in_S12_high;
      TH2F *bx_Wm1_RB2in_S01_high;
      TH2F *bx_Wm1_RB2in_S02_high;
      TH2F *bx_Wm1_RB2in_S03_high;
      TH2F *bx_Wm1_RB2in_S04_high;
      TH2F *bx_Wm1_RB2in_S05_high;
      TH2F *bx_Wm1_RB2in_S06_high;
      TH2F *bx_Wm1_RB2in_S07_high;
      TH2F *bx_Wm1_RB2in_S08_high;
      TH2F *bx_Wm1_RB2in_S09_high;
      TH2F *bx_Wm1_RB2in_S10_high;
      TH2F *bx_Wm1_RB2in_S11_high;
      TH2F *bx_Wm1_RB2in_S12_high;
      TH2F *bx_W0_RB2in_S01_high;
      TH2F *bx_W0_RB2in_S02_high;
      TH2F *bx_W0_RB2in_S03_high;
      TH2F *bx_W0_RB2in_S04_high;
      TH2F *bx_W0_RB2in_S05_high;
      TH2F *bx_W0_RB2in_S06_high;
      TH2F *bx_W0_RB2in_S07_high;
      TH2F *bx_W0_RB2in_S08_high;
      TH2F *bx_W0_RB2in_S09_high;
      TH2F *bx_W0_RB2in_S10_high;
      TH2F *bx_W0_RB2in_S11_high;
      TH2F *bx_W0_RB2in_S12_high;
      TH2F *bx_Wp1_RB2in_S01_high;
      TH2F *bx_Wp1_RB2in_S02_high;
      TH2F *bx_Wp1_RB2in_S03_high;
      TH2F *bx_Wp1_RB2in_S04_high;
      TH2F *bx_Wp1_RB2in_S05_high;
      TH2F *bx_Wp1_RB2in_S06_high;
      TH2F *bx_Wp1_RB2in_S07_high;
      TH2F *bx_Wp1_RB2in_S08_high;
      TH2F *bx_Wp1_RB2in_S09_high;
      TH2F *bx_Wp1_RB2in_S10_high;
      TH2F *bx_Wp1_RB2in_S11_high;
      TH2F *bx_Wp1_RB2in_S12_high;
      TH2F *bx_Wp2_RB2in_S01_high;
      TH2F *bx_Wp2_RB2in_S02_high;
      TH2F *bx_Wp2_RB2in_S03_high;
      TH2F *bx_Wp2_RB2in_S04_high;
      TH2F *bx_Wp2_RB2in_S05_high;
      TH2F *bx_Wp2_RB2in_S06_high;
      TH2F *bx_Wp2_RB2in_S07_high;
      TH2F *bx_Wp2_RB2in_S08_high;
      TH2F *bx_Wp2_RB2in_S09_high;
      TH2F *bx_Wp2_RB2in_S10_high;
      TH2F *bx_Wp2_RB2in_S11_high;
      TH2F *bx_Wp2_RB2in_S12_high;

      TH2F *bx_Wm2_RB2out_S01_high;
      TH2F *bx_Wm2_RB2out_S02_high;
      TH2F *bx_Wm2_RB2out_S03_high;
      TH2F *bx_Wm2_RB2out_S04_high;
      TH2F *bx_Wm2_RB2out_S05_high;
      TH2F *bx_Wm2_RB2out_S06_high;
      TH2F *bx_Wm2_RB2out_S07_high;
      TH2F *bx_Wm2_RB2out_S08_high;
      TH2F *bx_Wm2_RB2out_S09_high;
      TH2F *bx_Wm2_RB2out_S10_high;
      TH2F *bx_Wm2_RB2out_S11_high;
      TH2F *bx_Wm2_RB2out_S12_high;
      TH2F *bx_Wm1_RB2out_S01_high;
      TH2F *bx_Wm1_RB2out_S02_high;
      TH2F *bx_Wm1_RB2out_S03_high;
      TH2F *bx_Wm1_RB2out_S04_high;
      TH2F *bx_Wm1_RB2out_S05_high;
      TH2F *bx_Wm1_RB2out_S06_high;
      TH2F *bx_Wm1_RB2out_S07_high;
      TH2F *bx_Wm1_RB2out_S08_high;
      TH2F *bx_Wm1_RB2out_S09_high;
      TH2F *bx_Wm1_RB2out_S10_high;
      TH2F *bx_Wm1_RB2out_S11_high;
      TH2F *bx_Wm1_RB2out_S12_high;
      TH2F *bx_W0_RB2out_S01_high;
      TH2F *bx_W0_RB2out_S02_high;
      TH2F *bx_W0_RB2out_S03_high;
      TH2F *bx_W0_RB2out_S04_high;
      TH2F *bx_W0_RB2out_S05_high;
      TH2F *bx_W0_RB2out_S06_high;
      TH2F *bx_W0_RB2out_S07_high;
      TH2F *bx_W0_RB2out_S08_high;
      TH2F *bx_W0_RB2out_S09_high;
      TH2F *bx_W0_RB2out_S10_high;
      TH2F *bx_W0_RB2out_S11_high;
      TH2F *bx_W0_RB2out_S12_high;
      TH2F *bx_Wp1_RB2out_S01_high;
      TH2F *bx_Wp1_RB2out_S02_high;
      TH2F *bx_Wp1_RB2out_S03_high;
      TH2F *bx_Wp1_RB2out_S04_high;
      TH2F *bx_Wp1_RB2out_S05_high;
      TH2F *bx_Wp1_RB2out_S06_high;
      TH2F *bx_Wp1_RB2out_S07_high;
      TH2F *bx_Wp1_RB2out_S08_high;
      TH2F *bx_Wp1_RB2out_S09_high;
      TH2F *bx_Wp1_RB2out_S10_high;
      TH2F *bx_Wp1_RB2out_S11_high;
      TH2F *bx_Wp1_RB2out_S12_high;
      TH2F *bx_Wp2_RB2out_S01_high;
      TH2F *bx_Wp2_RB2out_S02_high;
      TH2F *bx_Wp2_RB2out_S03_high;
      TH2F *bx_Wp2_RB2out_S04_high;
      TH2F *bx_Wp2_RB2out_S05_high;
      TH2F *bx_Wp2_RB2out_S06_high;
      TH2F *bx_Wp2_RB2out_S07_high;
      TH2F *bx_Wp2_RB2out_S08_high;
      TH2F *bx_Wp2_RB2out_S09_high;
      TH2F *bx_Wp2_RB2out_S10_high;
      TH2F *bx_Wp2_RB2out_S11_high;
      TH2F *bx_Wp2_RB2out_S12_high;


      TH2F *bx_Wm2_RB3_S01_high;
      TH2F *bx_Wm2_RB3_S02_high;
      TH2F *bx_Wm2_RB3_S03_high;
      TH2F *bx_Wm2_RB3_S04_high;
      TH2F *bx_Wm2_RB3_S05_high;
      TH2F *bx_Wm2_RB3_S06_high;
      TH2F *bx_Wm2_RB3_S07_high;
      TH2F *bx_Wm2_RB3_S08_high;
      TH2F *bx_Wm2_RB3_S09_high;
      TH2F *bx_Wm2_RB3_S10_high;
      TH2F *bx_Wm2_RB3_S11_high;
      TH2F *bx_Wm2_RB3_S12_high;
      TH2F *bx_Wm1_RB3_S01_high;
      TH2F *bx_Wm1_RB3_S02_high;
      TH2F *bx_Wm1_RB3_S03_high;
      TH2F *bx_Wm1_RB3_S04_high;
      TH2F *bx_Wm1_RB3_S05_high;
      TH2F *bx_Wm1_RB3_S06_high;
      TH2F *bx_Wm1_RB3_S07_high;
      TH2F *bx_Wm1_RB3_S08_high;
      TH2F *bx_Wm1_RB3_S09_high;
      TH2F *bx_Wm1_RB3_S10_high;
      TH2F *bx_Wm1_RB3_S11_high;
      TH2F *bx_Wm1_RB3_S12_high;
      TH2F *bx_W0_RB3_S01_high;
      TH2F *bx_W0_RB3_S02_high;
      TH2F *bx_W0_RB3_S03_high;
      TH2F *bx_W0_RB3_S04_high;
      TH2F *bx_W0_RB3_S05_high;
      TH2F *bx_W0_RB3_S06_high;
      TH2F *bx_W0_RB3_S07_high;
      TH2F *bx_W0_RB3_S08_high;
      TH2F *bx_W0_RB3_S09_high;
      TH2F *bx_W0_RB3_S10_high;
      TH2F *bx_W0_RB3_S11_high;
      TH2F *bx_W0_RB3_S12_high;
      TH2F *bx_Wp1_RB3_S01_high;
      TH2F *bx_Wp1_RB3_S02_high;
      TH2F *bx_Wp1_RB3_S03_high;
      TH2F *bx_Wp1_RB3_S04_high;
      TH2F *bx_Wp1_RB3_S05_high;
      TH2F *bx_Wp1_RB3_S06_high;
      TH2F *bx_Wp1_RB3_S07_high;
      TH2F *bx_Wp1_RB3_S08_high;
      TH2F *bx_Wp1_RB3_S09_high;
      TH2F *bx_Wp1_RB3_S10_high;
      TH2F *bx_Wp1_RB3_S11_high;
      TH2F *bx_Wp1_RB3_S12_high;
      TH2F *bx_Wp2_RB3_S01_high;
      TH2F *bx_Wp2_RB3_S02_high;
      TH2F *bx_Wp2_RB3_S03_high;
      TH2F *bx_Wp2_RB3_S04_high;
      TH2F *bx_Wp2_RB3_S05_high;
      TH2F *bx_Wp2_RB3_S06_high;
      TH2F *bx_Wp2_RB3_S07_high;
      TH2F *bx_Wp2_RB3_S08_high;
      TH2F *bx_Wp2_RB3_S09_high;
      TH2F *bx_Wp2_RB3_S10_high;
      TH2F *bx_Wp2_RB3_S11_high;
      TH2F *bx_Wp2_RB3_S12_high;
      TH2F *bx_Wm2_RB4_S01_high;
      TH2F *bx_Wm2_RB4_S02_high;
      TH2F *bx_Wm2_RB4_S03_high;
      TH2F *bx_Wm2_RB4_S04_high;
      TH2F *bx_Wm2_RB4_S05_high;
      TH2F *bx_Wm2_RB4_S06_high;
      TH2F *bx_Wm2_RB4_S07_high;
      TH2F *bx_Wm2_RB4_S08_high;
      TH2F *bx_Wm2_RB4_S09_high;
      TH2F *bx_Wm2_RB4_S10_high;
      TH2F *bx_Wm2_RB4_S11_high;
      TH2F *bx_Wm2_RB4_S12_high;
      TH2F *bx_Wm1_RB4_S01_high;
      TH2F *bx_Wm1_RB4_S02_high;
      TH2F *bx_Wm1_RB4_S03_high;
      TH2F *bx_Wm1_RB4_S04_high;
      TH2F *bx_Wm1_RB4_S05_high;
      TH2F *bx_Wm1_RB4_S06_high;
      TH2F *bx_Wm1_RB4_S07_high;
      TH2F *bx_Wm1_RB4_S08_high;
      TH2F *bx_Wm1_RB4_S09_high;
      TH2F *bx_Wm1_RB4_S10_high;
      TH2F *bx_Wm1_RB4_S11_high;
      TH2F *bx_Wm1_RB4_S12_high;
      TH2F *bx_W0_RB4_S01_high;
      TH2F *bx_W0_RB4_S02_high;
      TH2F *bx_W0_RB4_S03_high;
      TH2F *bx_W0_RB4_S04_high;
      TH2F *bx_W0_RB4_S05_high;
      TH2F *bx_W0_RB4_S06_high;
      TH2F *bx_W0_RB4_S07_high;
      TH2F *bx_W0_RB4_S08_high;
      TH2F *bx_W0_RB4_S09_high;
      TH2F *bx_W0_RB4_S10_high;
      TH2F *bx_W0_RB4_S11_high;
      TH2F *bx_W0_RB4_S12_high;
      TH2F *bx_Wp1_RB4_S01_high;
      TH2F *bx_Wp1_RB4_S02_high;
      TH2F *bx_Wp1_RB4_S03_high;
      TH2F *bx_Wp1_RB4_S04_high;
      TH2F *bx_Wp1_RB4_S05_high;
      TH2F *bx_Wp1_RB4_S06_high;
      TH2F *bx_Wp1_RB4_S07_high;
      TH2F *bx_Wp1_RB4_S08_high;
      TH2F *bx_Wp1_RB4_S09_high;
      TH2F *bx_Wp1_RB4_S10_high;
      TH2F *bx_Wp1_RB4_S11_high;
      TH2F *bx_Wp1_RB4_S12_high;
      TH2F *bx_Wp2_RB4_S01_high;
      TH2F *bx_Wp2_RB4_S02_high;
      TH2F *bx_Wp2_RB4_S03_high;
      TH2F *bx_Wp2_RB4_S04_high;
      TH2F *bx_Wp2_RB4_S05_high;
      TH2F *bx_Wp2_RB4_S06_high;
      TH2F *bx_Wp2_RB4_S07_high;
      TH2F *bx_Wp2_RB4_S08_high;
      TH2F *bx_Wp2_RB4_S09_high;
      TH2F *bx_Wp2_RB4_S10_high;
      TH2F *bx_Wp2_RB4_S11_high;
      TH2F *bx_Wp2_RB4_S12_high;

      TH2F *bx_REp42_S01_high;
      TH2F *bx_REp42_S02_high;
      TH2F *bx_REp42_S03_high;
      TH2F *bx_REp42_S04_high;
      TH2F *bx_REp42_S05_high;
      TH2F *bx_REp42_S06_high;
      TH2F *bx_REp42_S07_high;
      TH2F *bx_REp42_S08_high;
      TH2F *bx_REp42_S09_high;
      TH2F *bx_REp42_S10_high;
      TH2F *bx_REp42_S11_high;
      TH2F *bx_REp42_S12_high;

      TH2F *bx_REp43_S01_high;
      TH2F *bx_REp43_S02_high;
      TH2F *bx_REp43_S03_high;
      TH2F *bx_REp43_S04_high;
      TH2F *bx_REp43_S05_high;
      TH2F *bx_REp43_S06_high;
      TH2F *bx_REp43_S07_high;
      TH2F *bx_REp43_S08_high;
      TH2F *bx_REp43_S09_high;
      TH2F *bx_REp43_S10_high;
      TH2F *bx_REp43_S11_high;
      TH2F *bx_REp43_S12_high;

      TH2F *bx_REp12_S01_high;
      TH2F *bx_REp12_S02_high;
      TH2F *bx_REp12_S03_high;
      TH2F *bx_REp12_S04_high;
      TH2F *bx_REp12_S05_high;
      TH2F *bx_REp12_S06_high;
      TH2F *bx_REp12_S07_high;
      TH2F *bx_REp12_S08_high;
      TH2F *bx_REp12_S09_high;
      TH2F *bx_REp12_S10_high;
      TH2F *bx_REp12_S11_high;
      TH2F *bx_REp12_S12_high;

      TH2F *bx_REp13_S01_high;
      TH2F *bx_REp13_S02_high;
      TH2F *bx_REp13_S03_high;
      TH2F *bx_REp13_S04_high;
      TH2F *bx_REp13_S05_high;
      TH2F *bx_REp13_S06_high;
      TH2F *bx_REp13_S07_high;
      TH2F *bx_REp13_S08_high;
      TH2F *bx_REp13_S09_high;
      TH2F *bx_REp13_S10_high;
      TH2F *bx_REp13_S11_high;
      TH2F *bx_REp13_S12_high;

      TH2F *bx_REp22_S01_high;
      TH2F *bx_REp22_S02_high;
      TH2F *bx_REp22_S03_high;
      TH2F *bx_REp22_S04_high;
      TH2F *bx_REp22_S05_high;
      TH2F *bx_REp22_S06_high;
      TH2F *bx_REp22_S07_high;
      TH2F *bx_REp22_S08_high;
      TH2F *bx_REp22_S09_high;
      TH2F *bx_REp22_S10_high;
      TH2F *bx_REp22_S11_high;
      TH2F *bx_REp22_S12_high;

      TH2F *bx_REp23_S01_high;
      TH2F *bx_REp23_S02_high;
      TH2F *bx_REp23_S03_high;
      TH2F *bx_REp23_S04_high;
      TH2F *bx_REp23_S05_high;
      TH2F *bx_REp23_S06_high;
      TH2F *bx_REp23_S07_high;
      TH2F *bx_REp23_S08_high;
      TH2F *bx_REp23_S09_high;
      TH2F *bx_REp23_S10_high;
      TH2F *bx_REp23_S11_high;
      TH2F *bx_REp23_S12_high;

      TH2F *bx_REp32_S01_high;
      TH2F *bx_REp32_S02_high;
      TH2F *bx_REp32_S03_high;
      TH2F *bx_REp32_S04_high;
      TH2F *bx_REp32_S05_high;
      TH2F *bx_REp32_S06_high;
      TH2F *bx_REp32_S07_high;
      TH2F *bx_REp32_S08_high;
      TH2F *bx_REp32_S09_high;
      TH2F *bx_REp32_S10_high;
      TH2F *bx_REp32_S11_high;
      TH2F *bx_REp32_S12_high;
      TH2F *bx_REp33_S01_high;
      TH2F *bx_REp33_S02_high;
      TH2F *bx_REp33_S03_high;
      TH2F *bx_REp33_S04_high;
      TH2F *bx_REp33_S05_high;
      TH2F *bx_REp33_S06_high;
      TH2F *bx_REp33_S07_high;
      TH2F *bx_REp33_S08_high;
      TH2F *bx_REp33_S09_high;
      TH2F *bx_REp33_S10_high;
      TH2F *bx_REp33_S11_high;
      TH2F *bx_REp33_S12_high;



      TH2F *bx_REm22_S01_high;
      TH2F *bx_REm22_S02_high;
      TH2F *bx_REm22_S03_high;
      TH2F *bx_REm22_S04_high;
      TH2F *bx_REm22_S05_high;
      TH2F *bx_REm22_S06_high;
      TH2F *bx_REm22_S07_high;
      TH2F *bx_REm22_S08_high;
      TH2F *bx_REm22_S09_high;
      TH2F *bx_REm22_S10_high;
      TH2F *bx_REm22_S11_high;
      TH2F *bx_REm22_S12_high;

      TH2F *bx_REm23_S01_high;
      TH2F *bx_REm23_S02_high;
      TH2F *bx_REm23_S03_high;
      TH2F *bx_REm23_S04_high;
      TH2F *bx_REm23_S05_high;
      TH2F *bx_REm23_S06_high;
      TH2F *bx_REm23_S07_high;
      TH2F *bx_REm23_S08_high;
      TH2F *bx_REm23_S09_high;
      TH2F *bx_REm23_S10_high;
      TH2F *bx_REm23_S11_high;
      TH2F *bx_REm23_S12_high;

      TH2F *bx_REm32_S01_high;
      TH2F *bx_REm32_S02_high;
      TH2F *bx_REm32_S03_high;
      TH2F *bx_REm32_S04_high;
      TH2F *bx_REm32_S05_high;
      TH2F *bx_REm32_S06_high;
      TH2F *bx_REm32_S07_high;
      TH2F *bx_REm32_S08_high;
      TH2F *bx_REm32_S09_high;
      TH2F *bx_REm32_S10_high;
      TH2F *bx_REm32_S11_high;
      TH2F *bx_REm32_S12_high;
      TH2F *bx_REm33_S01_high;
      TH2F *bx_REm33_S02_high;
      TH2F *bx_REm33_S03_high;
      TH2F *bx_REm33_S04_high;
      TH2F *bx_REm33_S05_high;
      TH2F *bx_REm33_S06_high;
      TH2F *bx_REm33_S07_high;
      TH2F *bx_REm33_S08_high;
      TH2F *bx_REm33_S09_high;
      TH2F *bx_REm33_S10_high;
      TH2F *bx_REm33_S11_high;
      TH2F *bx_REm33_S12_high;


      // Low
      TH2F *bx_Wm2_RB1in_S01_low;
      TH2F *bx_Wm2_RB1in_S02_low;
      TH2F *bx_Wm2_RB1in_S03_low;
      TH2F *bx_Wm2_RB1in_S04_low;
      TH2F *bx_Wm2_RB1in_S05_low;
      TH2F *bx_Wm2_RB1in_S06_low;
      TH2F *bx_Wm2_RB1in_S07_low;
      TH2F *bx_Wm2_RB1in_S08_low;
      TH2F *bx_Wm2_RB1in_S09_low;
      TH2F *bx_Wm2_RB1in_S10_low;
      TH2F *bx_Wm2_RB1in_S11_low;
      TH2F *bx_Wm2_RB1in_S12_low;

      TH2F *bx_Wm1_RB1in_S01_low;
      TH2F *bx_Wm1_RB1in_S02_low;
      TH2F *bx_Wm1_RB1in_S03_low;
      TH2F *bx_Wm1_RB1in_S04_low;
      TH2F *bx_Wm1_RB1in_S05_low;
      TH2F *bx_Wm1_RB1in_S06_low;
      TH2F *bx_Wm1_RB1in_S07_low;
      TH2F *bx_Wm1_RB1in_S08_low;
      TH2F *bx_Wm1_RB1in_S09_low;
      TH2F *bx_Wm1_RB1in_S10_low;
      TH2F *bx_Wm1_RB1in_S11_low;
      TH2F *bx_Wm1_RB1in_S12_low;

      TH2F *bx_W0_RB1in_S01_low;
      TH2F *bx_W0_RB1in_S02_low;
      TH2F *bx_W0_RB1in_S03_low;
      TH2F *bx_W0_RB1in_S04_low;
      TH2F *bx_W0_RB1in_S05_low;
      TH2F *bx_W0_RB1in_S06_low;
      TH2F *bx_W0_RB1in_S07_low;
      TH2F *bx_W0_RB1in_S08_low;
      TH2F *bx_W0_RB1in_S09_low;
      TH2F *bx_W0_RB1in_S10_low;
      TH2F *bx_W0_RB1in_S11_low;
      TH2F *bx_W0_RB1in_S12_low;

      TH2F *bx_Wp1_RB1in_S01_low;
      TH2F *bx_Wp1_RB1in_S02_low;
      TH2F *bx_Wp1_RB1in_S03_low;
      TH2F *bx_Wp1_RB1in_S04_low;
      TH2F *bx_Wp1_RB1in_S05_low;
      TH2F *bx_Wp1_RB1in_S06_low;
      TH2F *bx_Wp1_RB1in_S07_low;
      TH2F *bx_Wp1_RB1in_S08_low;
      TH2F *bx_Wp1_RB1in_S09_low;
      TH2F *bx_Wp1_RB1in_S10_low;
      TH2F *bx_Wp1_RB1in_S11_low;
      TH2F *bx_Wp1_RB1in_S12_low;

      TH2F *bx_Wp2_RB1in_S01_low;
      TH2F *bx_Wp2_RB1in_S02_low;
      TH2F *bx_Wp2_RB1in_S03_low;
      TH2F *bx_Wp2_RB1in_S04_low;
      TH2F *bx_Wp2_RB1in_S05_low;
      TH2F *bx_Wp2_RB1in_S06_low;
      TH2F *bx_Wp2_RB1in_S07_low;
      TH2F *bx_Wp2_RB1in_S08_low;
      TH2F *bx_Wp2_RB1in_S09_low;
      TH2F *bx_Wp2_RB1in_S10_low;
      TH2F *bx_Wp2_RB1in_S11_low;
      TH2F *bx_Wp2_RB1in_S12_low;

      // RB1out
    
      TH2F *bx_Wm2_RB1out_S01_low;
      TH2F *bx_Wm2_RB1out_S02_low;
      TH2F *bx_Wm2_RB1out_S03_low;
      TH2F *bx_Wm2_RB1out_S04_low;
      TH2F *bx_Wm2_RB1out_S05_low;
      TH2F *bx_Wm2_RB1out_S06_low;
      TH2F *bx_Wm2_RB1out_S07_low;
      TH2F *bx_Wm2_RB1out_S08_low;
      TH2F *bx_Wm2_RB1out_S09_low;
      TH2F *bx_Wm2_RB1out_S10_low;
      TH2F *bx_Wm2_RB1out_S11_low;
      TH2F *bx_Wm2_RB1out_S12_low;

      TH2F *bx_Wm1_RB1out_S01_low;
      TH2F *bx_Wm1_RB1out_S02_low;
      TH2F *bx_Wm1_RB1out_S03_low;
      TH2F *bx_Wm1_RB1out_S04_low;
      TH2F *bx_Wm1_RB1out_S05_low;
      TH2F *bx_Wm1_RB1out_S06_low;
      TH2F *bx_Wm1_RB1out_S07_low;
      TH2F *bx_Wm1_RB1out_S08_low;
      TH2F *bx_Wm1_RB1out_S09_low;
      TH2F *bx_Wm1_RB1out_S10_low;
      TH2F *bx_Wm1_RB1out_S11_low;
      TH2F *bx_Wm1_RB1out_S12_low;

      TH2F *bx_W0_RB1out_S01_low;
      TH2F *bx_W0_RB1out_S02_low;
      TH2F *bx_W0_RB1out_S03_low;
      TH2F *bx_W0_RB1out_S04_low;
      TH2F *bx_W0_RB1out_S05_low;
      TH2F *bx_W0_RB1out_S06_low;
      TH2F *bx_W0_RB1out_S07_low;
      TH2F *bx_W0_RB1out_S08_low;
      TH2F *bx_W0_RB1out_S09_low;
      TH2F *bx_W0_RB1out_S10_low;
      TH2F *bx_W0_RB1out_S11_low;
      TH2F *bx_W0_RB1out_S12_low;

      TH2F *bx_Wp1_RB1out_S01_low;
      TH2F *bx_Wp1_RB1out_S02_low;
      TH2F *bx_Wp1_RB1out_S03_low;
      TH2F *bx_Wp1_RB1out_S04_low;
      TH2F *bx_Wp1_RB1out_S05_low;
      TH2F *bx_Wp1_RB1out_S06_low;
      TH2F *bx_Wp1_RB1out_S07_low;
      TH2F *bx_Wp1_RB1out_S08_low;
      TH2F *bx_Wp1_RB1out_S09_low;
      TH2F *bx_Wp1_RB1out_S10_low;
      TH2F *bx_Wp1_RB1out_S11_low;
      TH2F *bx_Wp1_RB1out_S12_low;

      TH2F *bx_Wp2_RB1out_S01_low;
      TH2F *bx_Wp2_RB1out_S02_low;
      TH2F *bx_Wp2_RB1out_S03_low;
      TH2F *bx_Wp2_RB1out_S04_low;
      TH2F *bx_Wp2_RB1out_S05_low;
      TH2F *bx_Wp2_RB1out_S06_low;
      TH2F *bx_Wp2_RB1out_S07_low;
      TH2F *bx_Wp2_RB1out_S08_low;
      TH2F *bx_Wp2_RB1out_S09_low;
      TH2F *bx_Wp2_RB1out_S10_low;
      TH2F *bx_Wp2_RB1out_S11_low;
      TH2F *bx_Wp2_RB1out_S12_low;

      TH2F *bx_Wm2_RB2in_S01_low;
      TH2F *bx_Wm2_RB2in_S02_low;
      TH2F *bx_Wm2_RB2in_S03_low;
      TH2F *bx_Wm2_RB2in_S04_low;
      TH2F *bx_Wm2_RB2in_S05_low;
      TH2F *bx_Wm2_RB2in_S06_low;
      TH2F *bx_Wm2_RB2in_S07_low;
      TH2F *bx_Wm2_RB2in_S08_low;
      TH2F *bx_Wm2_RB2in_S09_low;
      TH2F *bx_Wm2_RB2in_S10_low;
      TH2F *bx_Wm2_RB2in_S11_low;
      TH2F *bx_Wm2_RB2in_S12_low;
      TH2F *bx_Wm1_RB2in_S01_low;
      TH2F *bx_Wm1_RB2in_S02_low;
      TH2F *bx_Wm1_RB2in_S03_low;
      TH2F *bx_Wm1_RB2in_S04_low;
      TH2F *bx_Wm1_RB2in_S05_low;
      TH2F *bx_Wm1_RB2in_S06_low;
      TH2F *bx_Wm1_RB2in_S07_low;
      TH2F *bx_Wm1_RB2in_S08_low;
      TH2F *bx_Wm1_RB2in_S09_low;
      TH2F *bx_Wm1_RB2in_S10_low;
      TH2F *bx_Wm1_RB2in_S11_low;
      TH2F *bx_Wm1_RB2in_S12_low;
      TH2F *bx_W0_RB2in_S01_low;
      TH2F *bx_W0_RB2in_S02_low;
      TH2F *bx_W0_RB2in_S03_low;
      TH2F *bx_W0_RB2in_S04_low;
      TH2F *bx_W0_RB2in_S05_low;
      TH2F *bx_W0_RB2in_S06_low;
      TH2F *bx_W0_RB2in_S07_low;
      TH2F *bx_W0_RB2in_S08_low;
      TH2F *bx_W0_RB2in_S09_low;
      TH2F *bx_W0_RB2in_S10_low;
      TH2F *bx_W0_RB2in_S11_low;
      TH2F *bx_W0_RB2in_S12_low;
      TH2F *bx_Wp1_RB2in_S01_low;
      TH2F *bx_Wp1_RB2in_S02_low;
      TH2F *bx_Wp1_RB2in_S03_low;
      TH2F *bx_Wp1_RB2in_S04_low;
      TH2F *bx_Wp1_RB2in_S05_low;
      TH2F *bx_Wp1_RB2in_S06_low;
      TH2F *bx_Wp1_RB2in_S07_low;
      TH2F *bx_Wp1_RB2in_S08_low;
      TH2F *bx_Wp1_RB2in_S09_low;
      TH2F *bx_Wp1_RB2in_S10_low;
      TH2F *bx_Wp1_RB2in_S11_low;
      TH2F *bx_Wp1_RB2in_S12_low;
      TH2F *bx_Wp2_RB2in_S01_low;
      TH2F *bx_Wp2_RB2in_S02_low;
      TH2F *bx_Wp2_RB2in_S03_low;
      TH2F *bx_Wp2_RB2in_S04_low;
      TH2F *bx_Wp2_RB2in_S05_low;
      TH2F *bx_Wp2_RB2in_S06_low;
      TH2F *bx_Wp2_RB2in_S07_low;
      TH2F *bx_Wp2_RB2in_S08_low;
      TH2F *bx_Wp2_RB2in_S09_low;
      TH2F *bx_Wp2_RB2in_S10_low;
      TH2F *bx_Wp2_RB2in_S11_low;
      TH2F *bx_Wp2_RB2in_S12_low;

      TH2F *bx_Wm2_RB2out_S01_low;
      TH2F *bx_Wm2_RB2out_S02_low;
      TH2F *bx_Wm2_RB2out_S03_low;
      TH2F *bx_Wm2_RB2out_S04_low;
      TH2F *bx_Wm2_RB2out_S05_low;
      TH2F *bx_Wm2_RB2out_S06_low;
      TH2F *bx_Wm2_RB2out_S07_low;
      TH2F *bx_Wm2_RB2out_S08_low;
      TH2F *bx_Wm2_RB2out_S09_low;
      TH2F *bx_Wm2_RB2out_S10_low;
      TH2F *bx_Wm2_RB2out_S11_low;
      TH2F *bx_Wm2_RB2out_S12_low;
      TH2F *bx_Wm1_RB2out_S01_low;
      TH2F *bx_Wm1_RB2out_S02_low;
      TH2F *bx_Wm1_RB2out_S03_low;
      TH2F *bx_Wm1_RB2out_S04_low;
      TH2F *bx_Wm1_RB2out_S05_low;
      TH2F *bx_Wm1_RB2out_S06_low;
      TH2F *bx_Wm1_RB2out_S07_low;
      TH2F *bx_Wm1_RB2out_S08_low;
      TH2F *bx_Wm1_RB2out_S09_low;
      TH2F *bx_Wm1_RB2out_S10_low;
      TH2F *bx_Wm1_RB2out_S11_low;
      TH2F *bx_Wm1_RB2out_S12_low;
      TH2F *bx_W0_RB2out_S01_low;
      TH2F *bx_W0_RB2out_S02_low;
      TH2F *bx_W0_RB2out_S03_low;
      TH2F *bx_W0_RB2out_S04_low;
      TH2F *bx_W0_RB2out_S05_low;
      TH2F *bx_W0_RB2out_S06_low;
      TH2F *bx_W0_RB2out_S07_low;
      TH2F *bx_W0_RB2out_S08_low;
      TH2F *bx_W0_RB2out_S09_low;
      TH2F *bx_W0_RB2out_S10_low;
      TH2F *bx_W0_RB2out_S11_low;
      TH2F *bx_W0_RB2out_S12_low;
      TH2F *bx_Wp1_RB2out_S01_low;
      TH2F *bx_Wp1_RB2out_S02_low;
      TH2F *bx_Wp1_RB2out_S03_low;
      TH2F *bx_Wp1_RB2out_S04_low;
      TH2F *bx_Wp1_RB2out_S05_low;
      TH2F *bx_Wp1_RB2out_S06_low;
      TH2F *bx_Wp1_RB2out_S07_low;
      TH2F *bx_Wp1_RB2out_S08_low;
      TH2F *bx_Wp1_RB2out_S09_low;
      TH2F *bx_Wp1_RB2out_S10_low;
      TH2F *bx_Wp1_RB2out_S11_low;
      TH2F *bx_Wp1_RB2out_S12_low;
      TH2F *bx_Wp2_RB2out_S01_low;
      TH2F *bx_Wp2_RB2out_S02_low;
      TH2F *bx_Wp2_RB2out_S03_low;
      TH2F *bx_Wp2_RB2out_S04_low;
      TH2F *bx_Wp2_RB2out_S05_low;
      TH2F *bx_Wp2_RB2out_S06_low;
      TH2F *bx_Wp2_RB2out_S07_low;
      TH2F *bx_Wp2_RB2out_S08_low;
      TH2F *bx_Wp2_RB2out_S09_low;
      TH2F *bx_Wp2_RB2out_S10_low;
      TH2F *bx_Wp2_RB2out_S11_low;
      TH2F *bx_Wp2_RB2out_S12_low;


      TH2F *bx_Wm2_RB3_S01_low;
      TH2F *bx_Wm2_RB3_S02_low;
      TH2F *bx_Wm2_RB3_S03_low;
      TH2F *bx_Wm2_RB3_S04_low;
      TH2F *bx_Wm2_RB3_S05_low;
      TH2F *bx_Wm2_RB3_S06_low;
      TH2F *bx_Wm2_RB3_S07_low;
      TH2F *bx_Wm2_RB3_S08_low;
      TH2F *bx_Wm2_RB3_S09_low;
      TH2F *bx_Wm2_RB3_S10_low;
      TH2F *bx_Wm2_RB3_S11_low;
      TH2F *bx_Wm2_RB3_S12_low;
      TH2F *bx_Wm1_RB3_S01_low;
      TH2F *bx_Wm1_RB3_S02_low;
      TH2F *bx_Wm1_RB3_S03_low;
      TH2F *bx_Wm1_RB3_S04_low;
      TH2F *bx_Wm1_RB3_S05_low;
      TH2F *bx_Wm1_RB3_S06_low;
      TH2F *bx_Wm1_RB3_S07_low;
      TH2F *bx_Wm1_RB3_S08_low;
      TH2F *bx_Wm1_RB3_S09_low;
      TH2F *bx_Wm1_RB3_S10_low;
      TH2F *bx_Wm1_RB3_S11_low;
      TH2F *bx_Wm1_RB3_S12_low;
      TH2F *bx_W0_RB3_S01_low;
      TH2F *bx_W0_RB3_S02_low;
      TH2F *bx_W0_RB3_S03_low;
      TH2F *bx_W0_RB3_S04_low;
      TH2F *bx_W0_RB3_S05_low;
      TH2F *bx_W0_RB3_S06_low;
      TH2F *bx_W0_RB3_S07_low;
      TH2F *bx_W0_RB3_S08_low;
      TH2F *bx_W0_RB3_S09_low;
      TH2F *bx_W0_RB3_S10_low;
      TH2F *bx_W0_RB3_S11_low;
      TH2F *bx_W0_RB3_S12_low;
      TH2F *bx_Wp1_RB3_S01_low;
      TH2F *bx_Wp1_RB3_S02_low;
      TH2F *bx_Wp1_RB3_S03_low;
      TH2F *bx_Wp1_RB3_S04_low;
      TH2F *bx_Wp1_RB3_S05_low;
      TH2F *bx_Wp1_RB3_S06_low;
      TH2F *bx_Wp1_RB3_S07_low;
      TH2F *bx_Wp1_RB3_S08_low;
      TH2F *bx_Wp1_RB3_S09_low;
      TH2F *bx_Wp1_RB3_S10_low;
      TH2F *bx_Wp1_RB3_S11_low;
      TH2F *bx_Wp1_RB3_S12_low;
      TH2F *bx_Wp2_RB3_S01_low;
      TH2F *bx_Wp2_RB3_S02_low;
      TH2F *bx_Wp2_RB3_S03_low;
      TH2F *bx_Wp2_RB3_S04_low;
      TH2F *bx_Wp2_RB3_S05_low;
      TH2F *bx_Wp2_RB3_S06_low;
      TH2F *bx_Wp2_RB3_S07_low;
      TH2F *bx_Wp2_RB3_S08_low;
      TH2F *bx_Wp2_RB3_S09_low;
      TH2F *bx_Wp2_RB3_S10_low;
      TH2F *bx_Wp2_RB3_S11_low;
      TH2F *bx_Wp2_RB3_S12_low;
      TH2F *bx_Wm2_RB4_S01_low;
      TH2F *bx_Wm2_RB4_S02_low;
      TH2F *bx_Wm2_RB4_S03_low;
      TH2F *bx_Wm2_RB4_S04_low;
      TH2F *bx_Wm2_RB4_S05_low;
      TH2F *bx_Wm2_RB4_S06_low;
      TH2F *bx_Wm2_RB4_S07_low;
      TH2F *bx_Wm2_RB4_S08_low;
      TH2F *bx_Wm2_RB4_S09_low;
      TH2F *bx_Wm2_RB4_S10_low;
      TH2F *bx_Wm2_RB4_S11_low;
      TH2F *bx_Wm2_RB4_S12_low;
      TH2F *bx_Wm1_RB4_S01_low;
      TH2F *bx_Wm1_RB4_S02_low;
      TH2F *bx_Wm1_RB4_S03_low;
      TH2F *bx_Wm1_RB4_S04_low;
      TH2F *bx_Wm1_RB4_S05_low;
      TH2F *bx_Wm1_RB4_S06_low;
      TH2F *bx_Wm1_RB4_S07_low;
      TH2F *bx_Wm1_RB4_S08_low;
      TH2F *bx_Wm1_RB4_S09_low;
      TH2F *bx_Wm1_RB4_S10_low;
      TH2F *bx_Wm1_RB4_S11_low;
      TH2F *bx_Wm1_RB4_S12_low;
      TH2F *bx_W0_RB4_S01_low;
      TH2F *bx_W0_RB4_S02_low;
      TH2F *bx_W0_RB4_S03_low;
      TH2F *bx_W0_RB4_S04_low;
      TH2F *bx_W0_RB4_S05_low;
      TH2F *bx_W0_RB4_S06_low;
      TH2F *bx_W0_RB4_S07_low;
      TH2F *bx_W0_RB4_S08_low;
      TH2F *bx_W0_RB4_S09_low;
      TH2F *bx_W0_RB4_S10_low;
      TH2F *bx_W0_RB4_S11_low;
      TH2F *bx_W0_RB4_S12_low;
      TH2F *bx_Wp1_RB4_S01_low;
      TH2F *bx_Wp1_RB4_S02_low;
      TH2F *bx_Wp1_RB4_S03_low;
      TH2F *bx_Wp1_RB4_S04_low;
      TH2F *bx_Wp1_RB4_S05_low;
      TH2F *bx_Wp1_RB4_S06_low;
      TH2F *bx_Wp1_RB4_S07_low;
      TH2F *bx_Wp1_RB4_S08_low;
      TH2F *bx_Wp1_RB4_S09_low;
      TH2F *bx_Wp1_RB4_S10_low;
      TH2F *bx_Wp1_RB4_S11_low;
      TH2F *bx_Wp1_RB4_S12_low;
      TH2F *bx_Wp2_RB4_S01_low;
      TH2F *bx_Wp2_RB4_S02_low;
      TH2F *bx_Wp2_RB4_S03_low;
      TH2F *bx_Wp2_RB4_S04_low;
      TH2F *bx_Wp2_RB4_S05_low;
      TH2F *bx_Wp2_RB4_S06_low;
      TH2F *bx_Wp2_RB4_S07_low;
      TH2F *bx_Wp2_RB4_S08_low;
      TH2F *bx_Wp2_RB4_S09_low;
      TH2F *bx_Wp2_RB4_S10_low;
      TH2F *bx_Wp2_RB4_S11_low;
      TH2F *bx_Wp2_RB4_S12_low;

      TH2F *bx_REp42_S01_low;
      TH2F *bx_REp42_S02_low;
      TH2F *bx_REp42_S03_low;
      TH2F *bx_REp42_S04_low;
      TH2F *bx_REp42_S05_low;
      TH2F *bx_REp42_S06_low;
      TH2F *bx_REp42_S07_low;
      TH2F *bx_REp42_S08_low;
      TH2F *bx_REp42_S09_low;
      TH2F *bx_REp42_S10_low;
      TH2F *bx_REp42_S11_low;
      TH2F *bx_REp42_S12_low;

      TH2F *bx_REp43_S01_low;
      TH2F *bx_REp43_S02_low;
      TH2F *bx_REp43_S03_low;
      TH2F *bx_REp43_S04_low;
      TH2F *bx_REp43_S05_low;
      TH2F *bx_REp43_S06_low;
      TH2F *bx_REp43_S07_low;
      TH2F *bx_REp43_S08_low;
      TH2F *bx_REp43_S09_low;
      TH2F *bx_REp43_S10_low;
      TH2F *bx_REp43_S11_low;
      TH2F *bx_REp43_S12_low;

      TH2F *bx_REp12_S01_low;
      TH2F *bx_REp12_S02_low;
      TH2F *bx_REp12_S03_low;
      TH2F *bx_REp12_S04_low;
      TH2F *bx_REp12_S05_low;
      TH2F *bx_REp12_S06_low;
      TH2F *bx_REp12_S07_low;
      TH2F *bx_REp12_S08_low;
      TH2F *bx_REp12_S09_low;
      TH2F *bx_REp12_S10_low;
      TH2F *bx_REp12_S11_low;
      TH2F *bx_REp12_S12_low;

      TH2F *bx_REp13_S01_low;
      TH2F *bx_REp13_S02_low;
      TH2F *bx_REp13_S03_low;
      TH2F *bx_REp13_S04_low;
      TH2F *bx_REp13_S05_low;
      TH2F *bx_REp13_S06_low;
      TH2F *bx_REp13_S07_low;
      TH2F *bx_REp13_S08_low;
      TH2F *bx_REp13_S09_low;
      TH2F *bx_REp13_S10_low;
      TH2F *bx_REp13_S11_low;
      TH2F *bx_REp13_S12_low;

      TH2F *bx_REp22_S01_low;
      TH2F *bx_REp22_S02_low;
      TH2F *bx_REp22_S03_low;
      TH2F *bx_REp22_S04_low;
      TH2F *bx_REp22_S05_low;
      TH2F *bx_REp22_S06_low;
      TH2F *bx_REp22_S07_low;
      TH2F *bx_REp22_S08_low;
      TH2F *bx_REp22_S09_low;
      TH2F *bx_REp22_S10_low;
      TH2F *bx_REp22_S11_low;
      TH2F *bx_REp22_S12_low;

      TH2F *bx_REp23_S01_low;
      TH2F *bx_REp23_S02_low;
      TH2F *bx_REp23_S03_low;
      TH2F *bx_REp23_S04_low;
      TH2F *bx_REp23_S05_low;
      TH2F *bx_REp23_S06_low;
      TH2F *bx_REp23_S07_low;
      TH2F *bx_REp23_S08_low;
      TH2F *bx_REp23_S09_low;
      TH2F *bx_REp23_S10_low;
      TH2F *bx_REp23_S11_low;
      TH2F *bx_REp23_S12_low;

      TH2F *bx_REp32_S01_low;
      TH2F *bx_REp32_S02_low;
      TH2F *bx_REp32_S03_low;
      TH2F *bx_REp32_S04_low;
      TH2F *bx_REp32_S05_low;
      TH2F *bx_REp32_S06_low;
      TH2F *bx_REp32_S07_low;
      TH2F *bx_REp32_S08_low;
      TH2F *bx_REp32_S09_low;
      TH2F *bx_REp32_S10_low;
      TH2F *bx_REp32_S11_low;
      TH2F *bx_REp32_S12_low;
      TH2F *bx_REp33_S01_low;
      TH2F *bx_REp33_S02_low;
      TH2F *bx_REp33_S03_low;
      TH2F *bx_REp33_S04_low;
      TH2F *bx_REp33_S05_low;
      TH2F *bx_REp33_S06_low;
      TH2F *bx_REp33_S07_low;
      TH2F *bx_REp33_S08_low;
      TH2F *bx_REp33_S09_low;
      TH2F *bx_REp33_S10_low;
      TH2F *bx_REp33_S11_low;
      TH2F *bx_REp33_S12_low;



      TH2F *bx_REm22_S01_low;
      TH2F *bx_REm22_S02_low;
      TH2F *bx_REm22_S03_low;
      TH2F *bx_REm22_S04_low;
      TH2F *bx_REm22_S05_low;
      TH2F *bx_REm22_S06_low;
      TH2F *bx_REm22_S07_low;
      TH2F *bx_REm22_S08_low;
      TH2F *bx_REm22_S09_low;
      TH2F *bx_REm22_S10_low;
      TH2F *bx_REm22_S11_low;
      TH2F *bx_REm22_S12_low;

      TH2F *bx_REm23_S01_low;
      TH2F *bx_REm23_S02_low;
      TH2F *bx_REm23_S03_low;
      TH2F *bx_REm23_S04_low;
      TH2F *bx_REm23_S05_low;
      TH2F *bx_REm23_S06_low;
      TH2F *bx_REm23_S07_low;
      TH2F *bx_REm23_S08_low;
      TH2F *bx_REm23_S09_low;
      TH2F *bx_REm23_S10_low;
      TH2F *bx_REm23_S11_low;
      TH2F *bx_REm23_S12_low;

      TH2F *bx_REm32_S01_low;
      TH2F *bx_REm32_S02_low;
      TH2F *bx_REm32_S03_low;
      TH2F *bx_REm32_S04_low;
      TH2F *bx_REm32_S05_low;
      TH2F *bx_REm32_S06_low;
      TH2F *bx_REm32_S07_low;
      TH2F *bx_REm32_S08_low;
      TH2F *bx_REm32_S09_low;
      TH2F *bx_REm32_S10_low;
      TH2F *bx_REm32_S11_low;
      TH2F *bx_REm32_S12_low;
      TH2F *bx_REm33_S01_low;
      TH2F *bx_REm33_S02_low;
      TH2F *bx_REm33_S03_low;
      TH2F *bx_REm33_S04_low;
      TH2F *bx_REm33_S05_low;
      TH2F *bx_REm33_S06_low;
      TH2F *bx_REm33_S07_low;
      TH2F *bx_REm33_S08_low;
      TH2F *bx_REm33_S09_low;
      TH2F *bx_REm33_S10_low;
      TH2F *bx_REm33_S11_low;
      TH2F *bx_REm33_S12_low;


// Eta division
// RB1out
      TH2F *bx_Wp2_RB1out_B_high;
      TH2F *bx_Wp1_RB1out_B_high;
      TH2F *bx_W0_RB1out_B_high;
      TH2F *bx_Wm1_RB1out_B_high;
      TH2F *bx_Wm2_RB1out_B_high;

      TH2F *bx_Wp2_RB1out_F_high;
      TH2F *bx_Wp1_RB1out_F_high;
      TH2F *bx_W0_RB1out_F_high;
      TH2F *bx_Wm1_RB1out_F_high;
      TH2F *bx_Wm2_RB1out_F_high;


      TH2F *bx_Wp2_RB1out_B_low;
      TH2F *bx_Wp1_RB1out_B_low;
      TH2F *bx_W0_RB1out_B_low;
      TH2F *bx_Wm1_RB1out_B_low;
      TH2F *bx_Wm2_RB1out_B_low;

      TH2F *bx_Wp2_RB1out_F_low;
      TH2F *bx_Wp1_RB1out_F_low;
      TH2F *bx_W0_RB1out_F_low;
      TH2F *bx_Wm1_RB1out_F_low;
      TH2F *bx_Wm2_RB1out_F_low;

// RB1in

      TH2F *bx_Wp2_RB1in_B_high;
      TH2F *bx_Wp1_RB1in_B_high;
      TH2F *bx_W0_RB1in_B_high;
      TH2F *bx_Wm1_RB1in_B_high;
      TH2F *bx_Wm2_RB1in_B_high;

      TH2F *bx_Wp2_RB1in_F_high;
      TH2F *bx_Wp1_RB1in_F_high;
      TH2F *bx_W0_RB1in_F_high;
      TH2F *bx_Wm1_RB1in_F_high;
      TH2F *bx_Wm2_RB1in_F_high;


      TH2F *bx_Wp2_RB1in_B_low;
      TH2F *bx_Wp1_RB1in_B_low;
      TH2F *bx_W0_RB1in_B_low;
      TH2F *bx_Wm1_RB1in_B_low;
      TH2F *bx_Wm2_RB1in_B_low;

      TH2F *bx_Wp2_RB1in_F_low;
      TH2F *bx_Wp1_RB1in_F_low;
      TH2F *bx_W0_RB1in_F_low;
      TH2F *bx_Wm1_RB1in_F_low;
      TH2F *bx_Wm2_RB1in_F_low;

 //RB3

      TH2F *bx_Wp2_RB3_B_high;
      TH2F *bx_Wp1_RB3_B_high;
      TH2F *bx_W0_RB3_B_high;
      TH2F *bx_Wm1_RB3_B_high;
      TH2F *bx_Wm2_RB3_B_high;

      TH2F *bx_Wp2_RB3_F_high;
      TH2F *bx_Wp1_RB3_F_high;
      TH2F *bx_W0_RB3_F_high;
      TH2F *bx_Wm1_RB3_F_high;
      TH2F *bx_Wm2_RB3_F_high;


      TH2F *bx_Wp2_RB3_B_low;
      TH2F *bx_Wp1_RB3_B_low;
      TH2F *bx_W0_RB3_B_low;
      TH2F *bx_Wm1_RB3_B_low;
      TH2F *bx_Wm2_RB3_B_low;

      TH2F *bx_Wp2_RB3_F_low;
      TH2F *bx_Wp1_RB3_F_low;
      TH2F *bx_W0_RB3_F_low;
      TH2F *bx_Wm1_RB3_F_low;
      TH2F *bx_Wm2_RB3_F_low;

// RB4

      TH2F *bx_Wp2_RB4_B_high;
      TH2F *bx_Wp1_RB4_B_high;
      TH2F *bx_W0_RB4_B_high;
      TH2F *bx_Wm1_RB4_B_high;
      TH2F *bx_Wm2_RB4_B_high;

      TH2F *bx_Wp2_RB4_F_high;
      TH2F *bx_Wp1_RB4_F_high;
      TH2F *bx_W0_RB4_F_high;
      TH2F *bx_Wm1_RB4_F_high;
      TH2F *bx_Wm2_RB4_F_high;


      TH2F *bx_Wp2_RB4_B_low;
      TH2F *bx_Wp1_RB4_B_low;
      TH2F *bx_W0_RB4_B_low;
      TH2F *bx_Wm1_RB4_B_low;
      TH2F *bx_Wm2_RB4_B_low;

      TH2F *bx_Wp2_RB4_F_low;
      TH2F *bx_Wp1_RB4_F_low;
      TH2F *bx_W0_RB4_F_low;
      TH2F *bx_Wm1_RB4_F_low;
      TH2F *bx_Wm2_RB4_F_low;     



// RB2out
      TH2F *bx_Wp2_RB2out_B_high;
      TH2F *bx_Wp1_RB2out_B_high;
      TH2F *bx_W0_RB2out_B_high;
      TH2F *bx_Wm1_RB2out_B_high;
      TH2F *bx_Wm2_RB2out_B_high;

      TH2F *bx_Wp2_RB2out_F_high;
      TH2F *bx_Wp1_RB2out_F_high;
      TH2F *bx_W0_RB2out_F_high;
      TH2F *bx_Wm1_RB2out_F_high;
      TH2F *bx_Wm2_RB2out_F_high;


      TH2F *bx_Wp2_RB2out_B_low;
      TH2F *bx_Wp1_RB2out_B_low;
      TH2F *bx_W0_RB2out_B_low;
      TH2F *bx_Wm1_RB2out_B_low;
      TH2F *bx_Wm2_RB2out_B_low;

      TH2F *bx_Wp2_RB2out_F_low;
      TH2F *bx_Wp1_RB2out_F_low;
      TH2F *bx_W0_RB2out_F_low;
      TH2F *bx_Wm1_RB2out_F_low;
      TH2F *bx_Wm2_RB2out_F_low;

      TH2F *bx_Wp2_RB2out_M_high;
      TH2F *bx_Wm2_RB2out_M_high;

      TH2F *bx_Wp2_RB2out_M_low;
      TH2F *bx_Wm2_RB2out_M_low;


// RB2in

      TH2F *bx_Wp2_RB2in_B_high;
      TH2F *bx_Wp1_RB2in_B_high;
      TH2F *bx_W0_RB2in_B_high;
      TH2F *bx_Wm1_RB2in_B_high;
      TH2F *bx_Wm2_RB2in_B_high;

      TH2F *bx_Wp2_RB2in_F_high;
      TH2F *bx_Wp1_RB2in_F_high;
      TH2F *bx_W0_RB2in_F_high;
      TH2F *bx_Wm1_RB2in_F_high;
      TH2F *bx_Wm2_RB2in_F_high;


      TH2F *bx_Wp2_RB2in_B_low;
      TH2F *bx_Wp1_RB2in_B_low;
      TH2F *bx_W0_RB2in_B_low;
      TH2F *bx_Wm1_RB2in_B_low;
      TH2F *bx_Wm2_RB2in_B_low;

      TH2F *bx_Wp2_RB2in_F_low;
      TH2F *bx_Wp1_RB2in_F_low;
      TH2F *bx_W0_RB2in_F_low;
      TH2F *bx_Wm1_RB2in_F_low;
      TH2F *bx_Wm2_RB2in_F_low;     

      TH2F *bx_Wp1_RB2in_M_high;
      TH2F *bx_W0_RB2in_M_high;
      TH2F *bx_Wm1_RB2in_M_high;

      TH2F *bx_Wp1_RB2in_M_low;
      TH2F *bx_W0_RB2in_M_low;
      TH2F *bx_Wm1_RB2in_M_low;

// REp12

         TH2F *bx_REp12_B_high;
         TH2F *bx_REp12_M_high;
         TH2F *bx_REp12_F_high;

         TH2F *bx_REp12_B_low;
         TH2F *bx_REp12_M_low;
         TH2F *bx_REp12_F_low;

// REp13

         TH2F *bx_REp13_B_high;
         TH2F *bx_REp13_M_high;
         TH2F *bx_REp13_F_high;

         TH2F *bx_REp13_B_low;
         TH2F *bx_REp13_M_low;
         TH2F *bx_REp13_F_low;

// REp42

         TH2F *bx_REp42_B_high;
         TH2F *bx_REp42_M_high;
         TH2F *bx_REp42_F_high;

         TH2F *bx_REp42_B_low;
         TH2F *bx_REp42_M_low;
         TH2F *bx_REp42_F_low;

// REp43

         TH2F *bx_REp43_B_high;
         TH2F *bx_REp43_M_high;
         TH2F *bx_REp43_F_high;

         TH2F *bx_REp43_B_low;
         TH2F *bx_REp43_M_low;
         TH2F *bx_REp43_F_low;

// REp22

         TH2F *bx_REp22_B_high;
         TH2F *bx_REp22_M_high;
         TH2F *bx_REp22_F_high;

         TH2F *bx_REp22_B_low;
         TH2F *bx_REp22_M_low;
         TH2F *bx_REp22_F_low;

// REp23

         TH2F *bx_REp23_B_high;
         TH2F *bx_REp23_M_high;
         TH2F *bx_REp23_F_high;

         TH2F *bx_REp23_B_low;
         TH2F *bx_REp23_M_low;
         TH2F *bx_REp23_F_low;

// REp32

         TH2F *bx_REp32_B_high;
         TH2F *bx_REp32_M_high;
         TH2F *bx_REp32_F_high;

         TH2F *bx_REp32_B_low;
         TH2F *bx_REp32_M_low;
         TH2F *bx_REp32_F_low;

// REp33

         TH2F *bx_REp33_B_high;
         TH2F *bx_REp33_M_high;
         TH2F *bx_REp33_F_high;

         TH2F *bx_REp33_B_low;
         TH2F *bx_REp33_M_low;
         TH2F *bx_REp33_F_low;


// endcap negative

TH2F *bx_REm42_S01_high;
TH2F *bx_REm42_S02_high;
TH2F *bx_REm42_S03_high;
TH2F *bx_REm42_S04_high;
TH2F *bx_REm42_S05_high;
TH2F *bx_REm42_S06_high;
TH2F *bx_REm42_S07_high;
TH2F *bx_REm42_S08_high;
TH2F *bx_REm42_S09_high;
TH2F *bx_REm42_S10_high;
TH2F *bx_REm42_S11_high;
TH2F *bx_REm42_S12_high;
TH2F *bx_REm43_S01_high;
TH2F *bx_REm43_S02_high;
TH2F *bx_REm43_S03_high;
TH2F *bx_REm43_S04_high;
TH2F *bx_REm43_S05_high;
TH2F *bx_REm43_S06_high;
TH2F *bx_REm43_S07_high;
TH2F *bx_REm43_S08_high;
TH2F *bx_REm43_S09_high;
TH2F *bx_REm43_S10_high;
TH2F *bx_REm43_S11_high;
TH2F *bx_REm43_S12_high;
TH2F *bx_REm12_S01_high;
TH2F *bx_REm12_S02_high;
TH2F *bx_REm12_S03_high;
TH2F *bx_REm12_S04_high;
TH2F *bx_REm12_S05_high;
TH2F *bx_REm12_S06_high;
TH2F *bx_REm12_S07_high;
TH2F *bx_REm12_S08_high;
TH2F *bx_REm12_S09_high;
TH2F *bx_REm12_S10_high;
TH2F *bx_REm12_S11_high;
TH2F *bx_REm12_S12_high;
TH2F *bx_REm13_S01_high;
TH2F *bx_REm13_S02_high;
TH2F *bx_REm13_S03_high;
TH2F *bx_REm13_S04_high;
TH2F *bx_REm13_S05_high;
TH2F *bx_REm13_S06_high;
TH2F *bx_REm13_S07_high;
TH2F *bx_REm13_S08_high;
TH2F *bx_REm13_S09_high;
TH2F *bx_REm13_S10_high;
TH2F *bx_REm13_S11_high;
TH2F *bx_REm13_S12_high;
TH2F *bx_REm42_S01_low;
TH2F *bx_REm42_S02_low;
TH2F *bx_REm42_S03_low;
TH2F *bx_REm42_S04_low;
TH2F *bx_REm42_S05_low;
TH2F *bx_REm42_S06_low;
TH2F *bx_REm42_S07_low;
TH2F *bx_REm42_S08_low;
TH2F *bx_REm42_S09_low;
TH2F *bx_REm42_S10_low;
TH2F *bx_REm42_S11_low;
TH2F *bx_REm42_S12_low;
TH2F *bx_REm43_S01_low;
TH2F *bx_REm43_S02_low;
TH2F *bx_REm43_S03_low;
TH2F *bx_REm43_S04_low;
TH2F *bx_REm43_S05_low;
TH2F *bx_REm43_S06_low;
TH2F *bx_REm43_S07_low;
TH2F *bx_REm43_S08_low;
TH2F *bx_REm43_S09_low;
TH2F *bx_REm43_S10_low;
TH2F *bx_REm43_S11_low;
TH2F *bx_REm43_S12_low;
TH2F *bx_REm12_S01_low;
TH2F *bx_REm12_S02_low;
TH2F *bx_REm12_S03_low;
TH2F *bx_REm12_S04_low;
TH2F *bx_REm12_S05_low;
TH2F *bx_REm12_S06_low;
TH2F *bx_REm12_S07_low;
TH2F *bx_REm12_S08_low;
TH2F *bx_REm12_S09_low;
TH2F *bx_REm12_S10_low;
TH2F *bx_REm12_S11_low;
TH2F *bx_REm12_S12_low;
TH2F *bx_REm13_S01_low;
TH2F *bx_REm13_S02_low;
TH2F *bx_REm13_S03_low;
TH2F *bx_REm13_S04_low;
TH2F *bx_REm13_S05_low;
TH2F *bx_REm13_S06_low;
TH2F *bx_REm13_S07_low;
TH2F *bx_REm13_S08_low;
TH2F *bx_REm13_S09_low;
TH2F *bx_REm13_S10_low;
TH2F *bx_REm13_S11_low;
TH2F *bx_REm13_S12_low;
// REm12

TH2F *bx_REm12_B_high;
TH2F *bx_REm12_M_high;
TH2F *bx_REm12_F_high;
TH2F *bx_REm12_B_low;
TH2F *bx_REm12_M_low;
TH2F *bx_REm12_F_low;
// REm13

TH2F *bx_REm13_B_high;
TH2F *bx_REm13_M_high;
TH2F *bx_REm13_F_high;
TH2F *bx_REm13_B_low;
TH2F *bx_REm13_M_low;
TH2F *bx_REm13_F_low;
// REm42

TH2F *bx_REm42_B_high;
TH2F *bx_REm42_M_high;
TH2F *bx_REm42_F_high;
TH2F *bx_REm42_B_low;
TH2F *bx_REm42_M_low;
TH2F *bx_REm42_F_low;
// REm43

TH2F *bx_REm43_B_high;
TH2F *bx_REm43_M_high;
TH2F *bx_REm43_F_high;
TH2F *bx_REm43_B_low;
TH2F *bx_REm43_M_low;
TH2F *bx_REm43_F_low;

// REm22

         TH2F *bx_REm22_B_high;
         TH2F *bx_REm22_M_high;
         TH2F *bx_REm22_F_high;

         TH2F *bx_REm22_B_low;
         TH2F *bx_REm22_M_low;
         TH2F *bx_REm22_F_low;

// REm23

         TH2F *bx_REm23_B_high;
         TH2F *bx_REm23_M_high;
         TH2F *bx_REm23_F_high;

         TH2F *bx_REm23_B_low;
         TH2F *bx_REm23_M_low;
         TH2F *bx_REm23_F_low;

// REm32

         TH2F *bx_REm32_B_high;
         TH2F *bx_REm32_M_high;
         TH2F *bx_REm32_F_high;

         TH2F *bx_REm32_B_low;
         TH2F *bx_REm32_M_low;
         TH2F *bx_REm32_F_low;

// REm33

         TH2F *bx_REm33_B_high;
         TH2F *bx_REm33_M_high;
         TH2F *bx_REm33_F_high;

         TH2F *bx_REm33_B_low;
         TH2F *bx_REm33_M_low;
         TH2F *bx_REm33_F_low;


// pre beam and abort
TH2F *bx_Wm2_RB1in_S01_abort;
TH2F *bx_Wm2_RB1in_S01_prebeam;

TH2F *bx_Wm2_RB1in_S02_abort;
TH2F *bx_Wm2_RB1in_S02_prebeam;

TH2F *bx_Wm2_RB1in_S03_abort;
TH2F *bx_Wm2_RB1in_S03_prebeam;

TH2F *bx_Wm2_RB1in_S04_abort;
TH2F *bx_Wm2_RB1in_S04_prebeam;

TH2F *bx_Wm2_RB1in_S05_abort;
TH2F *bx_Wm2_RB1in_S05_prebeam;

TH2F *bx_Wm2_RB1in_S06_abort;
TH2F *bx_Wm2_RB1in_S06_prebeam;

TH2F *bx_Wm2_RB1in_S07_abort;
TH2F *bx_Wm2_RB1in_S07_prebeam;

TH2F *bx_Wm2_RB1in_S08_abort;
TH2F *bx_Wm2_RB1in_S08_prebeam;

TH2F *bx_Wm2_RB1in_S09_abort;
TH2F *bx_Wm2_RB1in_S09_prebeam;

TH2F *bx_Wm2_RB1in_S10_abort;
TH2F *bx_Wm2_RB1in_S10_prebeam;

TH2F *bx_Wm2_RB1in_S11_abort;
TH2F *bx_Wm2_RB1in_S11_prebeam;

TH2F *bx_Wm2_RB1in_S12_abort;
TH2F *bx_Wm2_RB1in_S12_prebeam;

TH2F *bx_Wm1_RB1in_S01_abort;
TH2F *bx_Wm1_RB1in_S01_prebeam;

TH2F *bx_Wm1_RB1in_S02_abort;
TH2F *bx_Wm1_RB1in_S02_prebeam;

TH2F *bx_Wm1_RB1in_S03_abort;
TH2F *bx_Wm1_RB1in_S03_prebeam;

TH2F *bx_Wm1_RB1in_S04_abort;
TH2F *bx_Wm1_RB1in_S04_prebeam;

TH2F *bx_Wm1_RB1in_S05_abort;
TH2F *bx_Wm1_RB1in_S05_prebeam;

TH2F *bx_Wm1_RB1in_S06_abort;
TH2F *bx_Wm1_RB1in_S06_prebeam;

TH2F *bx_Wm1_RB1in_S07_abort;
TH2F *bx_Wm1_RB1in_S07_prebeam;

TH2F *bx_Wm1_RB1in_S08_abort;
TH2F *bx_Wm1_RB1in_S08_prebeam;

TH2F *bx_Wm1_RB1in_S09_abort;
TH2F *bx_Wm1_RB1in_S09_prebeam;

TH2F *bx_Wm1_RB1in_S10_abort;
TH2F *bx_Wm1_RB1in_S10_prebeam;

TH2F *bx_Wm1_RB1in_S11_abort;
TH2F *bx_Wm1_RB1in_S11_prebeam;

TH2F *bx_Wm1_RB1in_S12_abort;
TH2F *bx_Wm1_RB1in_S12_prebeam;

TH2F *bx_W0_RB1in_S01_abort;
TH2F *bx_W0_RB1in_S01_prebeam;

TH2F *bx_W0_RB1in_S02_abort;
TH2F *bx_W0_RB1in_S02_prebeam;

TH2F *bx_W0_RB1in_S03_abort;
TH2F *bx_W0_RB1in_S03_prebeam;

TH2F *bx_W0_RB1in_S04_abort;
TH2F *bx_W0_RB1in_S04_prebeam;

TH2F *bx_W0_RB1in_S05_abort;
TH2F *bx_W0_RB1in_S05_prebeam;

TH2F *bx_W0_RB1in_S06_abort;
TH2F *bx_W0_RB1in_S06_prebeam;

TH2F *bx_W0_RB1in_S07_abort;
TH2F *bx_W0_RB1in_S07_prebeam;

TH2F *bx_W0_RB1in_S08_abort;
TH2F *bx_W0_RB1in_S08_prebeam;

TH2F *bx_W0_RB1in_S09_abort;
TH2F *bx_W0_RB1in_S09_prebeam;

TH2F *bx_W0_RB1in_S10_abort;
TH2F *bx_W0_RB1in_S10_prebeam;

TH2F *bx_W0_RB1in_S11_abort;
TH2F *bx_W0_RB1in_S11_prebeam;

TH2F *bx_W0_RB1in_S12_abort;
TH2F *bx_W0_RB1in_S12_prebeam;

TH2F *bx_Wp1_RB1in_S01_abort;
TH2F *bx_Wp1_RB1in_S01_prebeam;

TH2F *bx_Wp1_RB1in_S02_abort;
TH2F *bx_Wp1_RB1in_S02_prebeam;

TH2F *bx_Wp1_RB1in_S03_abort;
TH2F *bx_Wp1_RB1in_S03_prebeam;

TH2F *bx_Wp1_RB1in_S04_abort;
TH2F *bx_Wp1_RB1in_S04_prebeam;

TH2F *bx_Wp1_RB1in_S05_abort;
TH2F *bx_Wp1_RB1in_S05_prebeam;

TH2F *bx_Wp1_RB1in_S06_abort;
TH2F *bx_Wp1_RB1in_S06_prebeam;

TH2F *bx_Wp1_RB1in_S07_abort;
TH2F *bx_Wp1_RB1in_S07_prebeam;

TH2F *bx_Wp1_RB1in_S08_abort;
TH2F *bx_Wp1_RB1in_S08_prebeam;

TH2F *bx_Wp1_RB1in_S09_abort;
TH2F *bx_Wp1_RB1in_S09_prebeam;

TH2F *bx_Wp1_RB1in_S10_abort;
TH2F *bx_Wp1_RB1in_S10_prebeam;

TH2F *bx_Wp1_RB1in_S11_abort;
TH2F *bx_Wp1_RB1in_S11_prebeam;

TH2F *bx_Wp1_RB1in_S12_abort;
TH2F *bx_Wp1_RB1in_S12_prebeam;

TH2F *bx_Wp2_RB1in_S01_abort;
TH2F *bx_Wp2_RB1in_S01_prebeam;

TH2F *bx_Wp2_RB1in_S02_abort;
TH2F *bx_Wp2_RB1in_S02_prebeam;

TH2F *bx_Wp2_RB1in_S03_abort;
TH2F *bx_Wp2_RB1in_S03_prebeam;

TH2F *bx_Wp2_RB1in_S04_abort;
TH2F *bx_Wp2_RB1in_S04_prebeam;

TH2F *bx_Wp2_RB1in_S05_abort;
TH2F *bx_Wp2_RB1in_S05_prebeam;

TH2F *bx_Wp2_RB1in_S06_abort;
TH2F *bx_Wp2_RB1in_S06_prebeam;

TH2F *bx_Wp2_RB1in_S07_abort;
TH2F *bx_Wp2_RB1in_S07_prebeam;

TH2F *bx_Wp2_RB1in_S08_abort;
TH2F *bx_Wp2_RB1in_S08_prebeam;

TH2F *bx_Wp2_RB1in_S09_abort;
TH2F *bx_Wp2_RB1in_S09_prebeam;

TH2F *bx_Wp2_RB1in_S10_abort;
TH2F *bx_Wp2_RB1in_S10_prebeam;

TH2F *bx_Wp2_RB1in_S11_abort;
TH2F *bx_Wp2_RB1in_S11_prebeam;

TH2F *bx_Wp2_RB1in_S12_abort;
TH2F *bx_Wp2_RB1in_S12_prebeam;

TH2F *bx_Wm2_RB1out_S01_abort;
TH2F *bx_Wm2_RB1out_S01_prebeam;

TH2F *bx_Wm2_RB1out_S02_abort;
TH2F *bx_Wm2_RB1out_S02_prebeam;

TH2F *bx_Wm2_RB1out_S03_abort;
TH2F *bx_Wm2_RB1out_S03_prebeam;

TH2F *bx_Wm2_RB1out_S04_abort;
TH2F *bx_Wm2_RB1out_S04_prebeam;

TH2F *bx_Wm2_RB1out_S05_abort;
TH2F *bx_Wm2_RB1out_S05_prebeam;

TH2F *bx_Wm2_RB1out_S06_abort;
TH2F *bx_Wm2_RB1out_S06_prebeam;

TH2F *bx_Wm2_RB1out_S07_abort;
TH2F *bx_Wm2_RB1out_S07_prebeam;

TH2F *bx_Wm2_RB1out_S08_abort;
TH2F *bx_Wm2_RB1out_S08_prebeam;

TH2F *bx_Wm2_RB1out_S09_abort;
TH2F *bx_Wm2_RB1out_S09_prebeam;

TH2F *bx_Wm2_RB1out_S10_abort;
TH2F *bx_Wm2_RB1out_S10_prebeam;

TH2F *bx_Wm2_RB1out_S11_abort;
TH2F *bx_Wm2_RB1out_S11_prebeam;

TH2F *bx_Wm2_RB1out_S12_abort;
TH2F *bx_Wm2_RB1out_S12_prebeam;

TH2F *bx_Wm1_RB1out_S01_abort;
TH2F *bx_Wm1_RB1out_S01_prebeam;

TH2F *bx_Wm1_RB1out_S02_abort;
TH2F *bx_Wm1_RB1out_S02_prebeam;

TH2F *bx_Wm1_RB1out_S03_abort;
TH2F *bx_Wm1_RB1out_S03_prebeam;

TH2F *bx_Wm1_RB1out_S04_abort;
TH2F *bx_Wm1_RB1out_S04_prebeam;

TH2F *bx_Wm1_RB1out_S05_abort;
TH2F *bx_Wm1_RB1out_S05_prebeam;

TH2F *bx_Wm1_RB1out_S06_abort;
TH2F *bx_Wm1_RB1out_S06_prebeam;

TH2F *bx_Wm1_RB1out_S07_abort;
TH2F *bx_Wm1_RB1out_S07_prebeam;

TH2F *bx_Wm1_RB1out_S08_abort;
TH2F *bx_Wm1_RB1out_S08_prebeam;

TH2F *bx_Wm1_RB1out_S09_abort;
TH2F *bx_Wm1_RB1out_S09_prebeam;

TH2F *bx_Wm1_RB1out_S10_abort;
TH2F *bx_Wm1_RB1out_S10_prebeam;

TH2F *bx_Wm1_RB1out_S11_abort;
TH2F *bx_Wm1_RB1out_S11_prebeam;

TH2F *bx_Wm1_RB1out_S12_abort;
TH2F *bx_Wm1_RB1out_S12_prebeam;

TH2F *bx_W0_RB1out_S01_abort;
TH2F *bx_W0_RB1out_S01_prebeam;

TH2F *bx_W0_RB1out_S02_abort;
TH2F *bx_W0_RB1out_S02_prebeam;

TH2F *bx_W0_RB1out_S03_abort;
TH2F *bx_W0_RB1out_S03_prebeam;

TH2F *bx_W0_RB1out_S04_abort;
TH2F *bx_W0_RB1out_S04_prebeam;

TH2F *bx_W0_RB1out_S05_abort;
TH2F *bx_W0_RB1out_S05_prebeam;

TH2F *bx_W0_RB1out_S06_abort;
TH2F *bx_W0_RB1out_S06_prebeam;

TH2F *bx_W0_RB1out_S07_abort;
TH2F *bx_W0_RB1out_S07_prebeam;

TH2F *bx_W0_RB1out_S08_abort;
TH2F *bx_W0_RB1out_S08_prebeam;

TH2F *bx_W0_RB1out_S09_abort;
TH2F *bx_W0_RB1out_S09_prebeam;

TH2F *bx_W0_RB1out_S10_abort;
TH2F *bx_W0_RB1out_S10_prebeam;

TH2F *bx_W0_RB1out_S11_abort;
TH2F *bx_W0_RB1out_S11_prebeam;

TH2F *bx_W0_RB1out_S12_abort;
TH2F *bx_W0_RB1out_S12_prebeam;

TH2F *bx_Wp1_RB1out_S01_abort;
TH2F *bx_Wp1_RB1out_S01_prebeam;

TH2F *bx_Wp1_RB1out_S02_abort;
TH2F *bx_Wp1_RB1out_S02_prebeam;

TH2F *bx_Wp1_RB1out_S03_abort;
TH2F *bx_Wp1_RB1out_S03_prebeam;

TH2F *bx_Wp1_RB1out_S04_abort;
TH2F *bx_Wp1_RB1out_S04_prebeam;

TH2F *bx_Wp1_RB1out_S05_abort;
TH2F *bx_Wp1_RB1out_S05_prebeam;

TH2F *bx_Wp1_RB1out_S06_abort;
TH2F *bx_Wp1_RB1out_S06_prebeam;

TH2F *bx_Wp1_RB1out_S07_abort;
TH2F *bx_Wp1_RB1out_S07_prebeam;

TH2F *bx_Wp1_RB1out_S08_abort;
TH2F *bx_Wp1_RB1out_S08_prebeam;

TH2F *bx_Wp1_RB1out_S09_abort;
TH2F *bx_Wp1_RB1out_S09_prebeam;

TH2F *bx_Wp1_RB1out_S10_abort;
TH2F *bx_Wp1_RB1out_S10_prebeam;

TH2F *bx_Wp1_RB1out_S11_abort;
TH2F *bx_Wp1_RB1out_S11_prebeam;

TH2F *bx_Wp1_RB1out_S12_abort;
TH2F *bx_Wp1_RB1out_S12_prebeam;

TH2F *bx_Wp2_RB1out_S01_abort;
TH2F *bx_Wp2_RB1out_S01_prebeam;

TH2F *bx_Wp2_RB1out_S02_abort;
TH2F *bx_Wp2_RB1out_S02_prebeam;

TH2F *bx_Wp2_RB1out_S03_abort;
TH2F *bx_Wp2_RB1out_S03_prebeam;

TH2F *bx_Wp2_RB1out_S04_abort;
TH2F *bx_Wp2_RB1out_S04_prebeam;

TH2F *bx_Wp2_RB1out_S05_abort;
TH2F *bx_Wp2_RB1out_S05_prebeam;

TH2F *bx_Wp2_RB1out_S06_abort;
TH2F *bx_Wp2_RB1out_S06_prebeam;

TH2F *bx_Wp2_RB1out_S07_abort;
TH2F *bx_Wp2_RB1out_S07_prebeam;

TH2F *bx_Wp2_RB1out_S08_abort;
TH2F *bx_Wp2_RB1out_S08_prebeam;

TH2F *bx_Wp2_RB1out_S09_abort;
TH2F *bx_Wp2_RB1out_S09_prebeam;

TH2F *bx_Wp2_RB1out_S10_abort;
TH2F *bx_Wp2_RB1out_S10_prebeam;

TH2F *bx_Wp2_RB1out_S11_abort;
TH2F *bx_Wp2_RB1out_S11_prebeam;

TH2F *bx_Wp2_RB1out_S12_abort;
TH2F *bx_Wp2_RB1out_S12_prebeam;

TH2F *bx_Wm2_RB2in_S01_abort;
TH2F *bx_Wm2_RB2in_S01_prebeam;

TH2F *bx_Wm2_RB2in_S02_abort;
TH2F *bx_Wm2_RB2in_S02_prebeam;

TH2F *bx_Wm2_RB2in_S03_abort;
TH2F *bx_Wm2_RB2in_S03_prebeam;

TH2F *bx_Wm2_RB2in_S04_abort;
TH2F *bx_Wm2_RB2in_S04_prebeam;

TH2F *bx_Wm2_RB2in_S05_abort;
TH2F *bx_Wm2_RB2in_S05_prebeam;

TH2F *bx_Wm2_RB2in_S06_abort;
TH2F *bx_Wm2_RB2in_S06_prebeam;

TH2F *bx_Wm2_RB2in_S07_abort;
TH2F *bx_Wm2_RB2in_S07_prebeam;

TH2F *bx_Wm2_RB2in_S08_abort;
TH2F *bx_Wm2_RB2in_S08_prebeam;

TH2F *bx_Wm2_RB2in_S09_abort;
TH2F *bx_Wm2_RB2in_S09_prebeam;

TH2F *bx_Wm2_RB2in_S10_abort;
TH2F *bx_Wm2_RB2in_S10_prebeam;

TH2F *bx_Wm2_RB2in_S11_abort;
TH2F *bx_Wm2_RB2in_S11_prebeam;

TH2F *bx_Wm2_RB2in_S12_abort;
TH2F *bx_Wm2_RB2in_S12_prebeam;

TH2F *bx_Wm1_RB2in_S01_abort;
TH2F *bx_Wm1_RB2in_S01_prebeam;

TH2F *bx_Wm1_RB2in_S02_abort;
TH2F *bx_Wm1_RB2in_S02_prebeam;

TH2F *bx_Wm1_RB2in_S03_abort;
TH2F *bx_Wm1_RB2in_S03_prebeam;

TH2F *bx_Wm1_RB2in_S04_abort;
TH2F *bx_Wm1_RB2in_S04_prebeam;

TH2F *bx_Wm1_RB2in_S05_abort;
TH2F *bx_Wm1_RB2in_S05_prebeam;

TH2F *bx_Wm1_RB2in_S06_abort;
TH2F *bx_Wm1_RB2in_S06_prebeam;

TH2F *bx_Wm1_RB2in_S07_abort;
TH2F *bx_Wm1_RB2in_S07_prebeam;

TH2F *bx_Wm1_RB2in_S08_abort;
TH2F *bx_Wm1_RB2in_S08_prebeam;

TH2F *bx_Wm1_RB2in_S09_abort;
TH2F *bx_Wm1_RB2in_S09_prebeam;

TH2F *bx_Wm1_RB2in_S10_abort;
TH2F *bx_Wm1_RB2in_S10_prebeam;

TH2F *bx_Wm1_RB2in_S11_abort;
TH2F *bx_Wm1_RB2in_S11_prebeam;

TH2F *bx_Wm1_RB2in_S12_abort;
TH2F *bx_Wm1_RB2in_S12_prebeam;

TH2F *bx_W0_RB2in_S01_abort;
TH2F *bx_W0_RB2in_S01_prebeam;

TH2F *bx_W0_RB2in_S02_abort;
TH2F *bx_W0_RB2in_S02_prebeam;

TH2F *bx_W0_RB2in_S03_abort;
TH2F *bx_W0_RB2in_S03_prebeam;

TH2F *bx_W0_RB2in_S04_abort;
TH2F *bx_W0_RB2in_S04_prebeam;

TH2F *bx_W0_RB2in_S05_abort;
TH2F *bx_W0_RB2in_S05_prebeam;

TH2F *bx_W0_RB2in_S06_abort;
TH2F *bx_W0_RB2in_S06_prebeam;

TH2F *bx_W0_RB2in_S07_abort;
TH2F *bx_W0_RB2in_S07_prebeam;

TH2F *bx_W0_RB2in_S08_abort;
TH2F *bx_W0_RB2in_S08_prebeam;

TH2F *bx_W0_RB2in_S09_abort;
TH2F *bx_W0_RB2in_S09_prebeam;

TH2F *bx_W0_RB2in_S10_abort;
TH2F *bx_W0_RB2in_S10_prebeam;

TH2F *bx_W0_RB2in_S11_abort;
TH2F *bx_W0_RB2in_S11_prebeam;

TH2F *bx_W0_RB2in_S12_abort;
TH2F *bx_W0_RB2in_S12_prebeam;

TH2F *bx_Wp1_RB2in_S01_abort;
TH2F *bx_Wp1_RB2in_S01_prebeam;

TH2F *bx_Wp1_RB2in_S02_abort;
TH2F *bx_Wp1_RB2in_S02_prebeam;

TH2F *bx_Wp1_RB2in_S03_abort;
TH2F *bx_Wp1_RB2in_S03_prebeam;

TH2F *bx_Wp1_RB2in_S04_abort;
TH2F *bx_Wp1_RB2in_S04_prebeam;

TH2F *bx_Wp1_RB2in_S05_abort;
TH2F *bx_Wp1_RB2in_S05_prebeam;

TH2F *bx_Wp1_RB2in_S06_abort;
TH2F *bx_Wp1_RB2in_S06_prebeam;

TH2F *bx_Wp1_RB2in_S07_abort;
TH2F *bx_Wp1_RB2in_S07_prebeam;

TH2F *bx_Wp1_RB2in_S08_abort;
TH2F *bx_Wp1_RB2in_S08_prebeam;

TH2F *bx_Wp1_RB2in_S09_abort;
TH2F *bx_Wp1_RB2in_S09_prebeam;

TH2F *bx_Wp1_RB2in_S10_abort;
TH2F *bx_Wp1_RB2in_S10_prebeam;

TH2F *bx_Wp1_RB2in_S11_abort;
TH2F *bx_Wp1_RB2in_S11_prebeam;

TH2F *bx_Wp1_RB2in_S12_abort;
TH2F *bx_Wp1_RB2in_S12_prebeam;

TH2F *bx_Wp2_RB2in_S01_abort;
TH2F *bx_Wp2_RB2in_S01_prebeam;

TH2F *bx_Wp2_RB2in_S02_abort;
TH2F *bx_Wp2_RB2in_S02_prebeam;

TH2F *bx_Wp2_RB2in_S03_abort;
TH2F *bx_Wp2_RB2in_S03_prebeam;

TH2F *bx_Wp2_RB2in_S04_abort;
TH2F *bx_Wp2_RB2in_S04_prebeam;

TH2F *bx_Wp2_RB2in_S05_abort;
TH2F *bx_Wp2_RB2in_S05_prebeam;

TH2F *bx_Wp2_RB2in_S06_abort;
TH2F *bx_Wp2_RB2in_S06_prebeam;

TH2F *bx_Wp2_RB2in_S07_abort;
TH2F *bx_Wp2_RB2in_S07_prebeam;

TH2F *bx_Wp2_RB2in_S08_abort;
TH2F *bx_Wp2_RB2in_S08_prebeam;

TH2F *bx_Wp2_RB2in_S09_abort;
TH2F *bx_Wp2_RB2in_S09_prebeam;

TH2F *bx_Wp2_RB2in_S10_abort;
TH2F *bx_Wp2_RB2in_S10_prebeam;

TH2F *bx_Wp2_RB2in_S11_abort;
TH2F *bx_Wp2_RB2in_S11_prebeam;

TH2F *bx_Wp2_RB2in_S12_abort;
TH2F *bx_Wp2_RB2in_S12_prebeam;

TH2F *bx_Wm2_RB2out_S01_abort;
TH2F *bx_Wm2_RB2out_S01_prebeam;

TH2F *bx_Wm2_RB2out_S02_abort;
TH2F *bx_Wm2_RB2out_S02_prebeam;

TH2F *bx_Wm2_RB2out_S03_abort;
TH2F *bx_Wm2_RB2out_S03_prebeam;

TH2F *bx_Wm2_RB2out_S04_abort;
TH2F *bx_Wm2_RB2out_S04_prebeam;

TH2F *bx_Wm2_RB2out_S05_abort;
TH2F *bx_Wm2_RB2out_S05_prebeam;

TH2F *bx_Wm2_RB2out_S06_abort;
TH2F *bx_Wm2_RB2out_S06_prebeam;

TH2F *bx_Wm2_RB2out_S07_abort;
TH2F *bx_Wm2_RB2out_S07_prebeam;

TH2F *bx_Wm2_RB2out_S08_abort;
TH2F *bx_Wm2_RB2out_S08_prebeam;

TH2F *bx_Wm2_RB2out_S09_abort;
TH2F *bx_Wm2_RB2out_S09_prebeam;

TH2F *bx_Wm2_RB2out_S10_abort;
TH2F *bx_Wm2_RB2out_S10_prebeam;

TH2F *bx_Wm2_RB2out_S11_abort;
TH2F *bx_Wm2_RB2out_S11_prebeam;

TH2F *bx_Wm2_RB2out_S12_abort;
TH2F *bx_Wm2_RB2out_S12_prebeam;

TH2F *bx_Wm1_RB2out_S01_abort;
TH2F *bx_Wm1_RB2out_S01_prebeam;

TH2F *bx_Wm1_RB2out_S02_abort;
TH2F *bx_Wm1_RB2out_S02_prebeam;

TH2F *bx_Wm1_RB2out_S03_abort;
TH2F *bx_Wm1_RB2out_S03_prebeam;

TH2F *bx_Wm1_RB2out_S04_abort;
TH2F *bx_Wm1_RB2out_S04_prebeam;

TH2F *bx_Wm1_RB2out_S05_abort;
TH2F *bx_Wm1_RB2out_S05_prebeam;

TH2F *bx_Wm1_RB2out_S06_abort;
TH2F *bx_Wm1_RB2out_S06_prebeam;

TH2F *bx_Wm1_RB2out_S07_abort;
TH2F *bx_Wm1_RB2out_S07_prebeam;

TH2F *bx_Wm1_RB2out_S08_abort;
TH2F *bx_Wm1_RB2out_S08_prebeam;

TH2F *bx_Wm1_RB2out_S09_abort;
TH2F *bx_Wm1_RB2out_S09_prebeam;

TH2F *bx_Wm1_RB2out_S10_abort;
TH2F *bx_Wm1_RB2out_S10_prebeam;

TH2F *bx_Wm1_RB2out_S11_abort;
TH2F *bx_Wm1_RB2out_S11_prebeam;

TH2F *bx_Wm1_RB2out_S12_abort;
TH2F *bx_Wm1_RB2out_S12_prebeam;

TH2F *bx_W0_RB2out_S01_abort;
TH2F *bx_W0_RB2out_S01_prebeam;

TH2F *bx_W0_RB2out_S02_abort;
TH2F *bx_W0_RB2out_S02_prebeam;

TH2F *bx_W0_RB2out_S03_abort;
TH2F *bx_W0_RB2out_S03_prebeam;

TH2F *bx_W0_RB2out_S04_abort;
TH2F *bx_W0_RB2out_S04_prebeam;

TH2F *bx_W0_RB2out_S05_abort;
TH2F *bx_W0_RB2out_S05_prebeam;

TH2F *bx_W0_RB2out_S06_abort;
TH2F *bx_W0_RB2out_S06_prebeam;

TH2F *bx_W0_RB2out_S07_abort;
TH2F *bx_W0_RB2out_S07_prebeam;

TH2F *bx_W0_RB2out_S08_abort;
TH2F *bx_W0_RB2out_S08_prebeam;

TH2F *bx_W0_RB2out_S09_abort;
TH2F *bx_W0_RB2out_S09_prebeam;

TH2F *bx_W0_RB2out_S10_abort;
TH2F *bx_W0_RB2out_S10_prebeam;

TH2F *bx_W0_RB2out_S11_abort;
TH2F *bx_W0_RB2out_S11_prebeam;

TH2F *bx_W0_RB2out_S12_abort;
TH2F *bx_W0_RB2out_S12_prebeam;

TH2F *bx_Wp1_RB2out_S01_abort;
TH2F *bx_Wp1_RB2out_S01_prebeam;

TH2F *bx_Wp1_RB2out_S02_abort;
TH2F *bx_Wp1_RB2out_S02_prebeam;

TH2F *bx_Wp1_RB2out_S03_abort;
TH2F *bx_Wp1_RB2out_S03_prebeam;

TH2F *bx_Wp1_RB2out_S04_abort;
TH2F *bx_Wp1_RB2out_S04_prebeam;

TH2F *bx_Wp1_RB2out_S05_abort;
TH2F *bx_Wp1_RB2out_S05_prebeam;

TH2F *bx_Wp1_RB2out_S06_abort;
TH2F *bx_Wp1_RB2out_S06_prebeam;

TH2F *bx_Wp1_RB2out_S07_abort;
TH2F *bx_Wp1_RB2out_S07_prebeam;

TH2F *bx_Wp1_RB2out_S08_abort;
TH2F *bx_Wp1_RB2out_S08_prebeam;

TH2F *bx_Wp1_RB2out_S09_abort;
TH2F *bx_Wp1_RB2out_S09_prebeam;

TH2F *bx_Wp1_RB2out_S10_abort;
TH2F *bx_Wp1_RB2out_S10_prebeam;

TH2F *bx_Wp1_RB2out_S11_abort;
TH2F *bx_Wp1_RB2out_S11_prebeam;

TH2F *bx_Wp1_RB2out_S12_abort;
TH2F *bx_Wp1_RB2out_S12_prebeam;

TH2F *bx_Wp2_RB2out_S01_abort;
TH2F *bx_Wp2_RB2out_S01_prebeam;

TH2F *bx_Wp2_RB2out_S02_abort;
TH2F *bx_Wp2_RB2out_S02_prebeam;

TH2F *bx_Wp2_RB2out_S03_abort;
TH2F *bx_Wp2_RB2out_S03_prebeam;

TH2F *bx_Wp2_RB2out_S04_abort;
TH2F *bx_Wp2_RB2out_S04_prebeam;

TH2F *bx_Wp2_RB2out_S05_abort;
TH2F *bx_Wp2_RB2out_S05_prebeam;

TH2F *bx_Wp2_RB2out_S06_abort;
TH2F *bx_Wp2_RB2out_S06_prebeam;

TH2F *bx_Wp2_RB2out_S07_abort;
TH2F *bx_Wp2_RB2out_S07_prebeam;

TH2F *bx_Wp2_RB2out_S08_abort;
TH2F *bx_Wp2_RB2out_S08_prebeam;

TH2F *bx_Wp2_RB2out_S09_abort;
TH2F *bx_Wp2_RB2out_S09_prebeam;

TH2F *bx_Wp2_RB2out_S10_abort;
TH2F *bx_Wp2_RB2out_S10_prebeam;

TH2F *bx_Wp2_RB2out_S11_abort;
TH2F *bx_Wp2_RB2out_S11_prebeam;

TH2F *bx_Wp2_RB2out_S12_abort;
TH2F *bx_Wp2_RB2out_S12_prebeam;

TH2F *bx_Wm2_RB3_S01_abort;
TH2F *bx_Wm2_RB3_S01_prebeam;

TH2F *bx_Wm2_RB3_S02_abort;
TH2F *bx_Wm2_RB3_S02_prebeam;

TH2F *bx_Wm2_RB3_S03_abort;
TH2F *bx_Wm2_RB3_S03_prebeam;

TH2F *bx_Wm2_RB3_S04_abort;
TH2F *bx_Wm2_RB3_S04_prebeam;

TH2F *bx_Wm2_RB3_S05_abort;
TH2F *bx_Wm2_RB3_S05_prebeam;

TH2F *bx_Wm2_RB3_S06_abort;
TH2F *bx_Wm2_RB3_S06_prebeam;

TH2F *bx_Wm2_RB3_S07_abort;
TH2F *bx_Wm2_RB3_S07_prebeam;

TH2F *bx_Wm2_RB3_S08_abort;
TH2F *bx_Wm2_RB3_S08_prebeam;

TH2F *bx_Wm2_RB3_S09_abort;
TH2F *bx_Wm2_RB3_S09_prebeam;

TH2F *bx_Wm2_RB3_S10_abort;
TH2F *bx_Wm2_RB3_S10_prebeam;

TH2F *bx_Wm2_RB3_S11_abort;
TH2F *bx_Wm2_RB3_S11_prebeam;

TH2F *bx_Wm2_RB3_S12_abort;
TH2F *bx_Wm2_RB3_S12_prebeam;

TH2F *bx_Wm1_RB3_S01_abort;
TH2F *bx_Wm1_RB3_S01_prebeam;

TH2F *bx_Wm1_RB3_S02_abort;
TH2F *bx_Wm1_RB3_S02_prebeam;

TH2F *bx_Wm1_RB3_S03_abort;
TH2F *bx_Wm1_RB3_S03_prebeam;

TH2F *bx_Wm1_RB3_S04_abort;
TH2F *bx_Wm1_RB3_S04_prebeam;

TH2F *bx_Wm1_RB3_S05_abort;
TH2F *bx_Wm1_RB3_S05_prebeam;

TH2F *bx_Wm1_RB3_S06_abort;
TH2F *bx_Wm1_RB3_S06_prebeam;

TH2F *bx_Wm1_RB3_S07_abort;
TH2F *bx_Wm1_RB3_S07_prebeam;

TH2F *bx_Wm1_RB3_S08_abort;
TH2F *bx_Wm1_RB3_S08_prebeam;

TH2F *bx_Wm1_RB3_S09_abort;
TH2F *bx_Wm1_RB3_S09_prebeam;

TH2F *bx_Wm1_RB3_S10_abort;
TH2F *bx_Wm1_RB3_S10_prebeam;

TH2F *bx_Wm1_RB3_S11_abort;
TH2F *bx_Wm1_RB3_S11_prebeam;

TH2F *bx_Wm1_RB3_S12_abort;
TH2F *bx_Wm1_RB3_S12_prebeam;

TH2F *bx_W0_RB3_S01_abort;
TH2F *bx_W0_RB3_S01_prebeam;

TH2F *bx_W0_RB3_S02_abort;
TH2F *bx_W0_RB3_S02_prebeam;

TH2F *bx_W0_RB3_S03_abort;
TH2F *bx_W0_RB3_S03_prebeam;

TH2F *bx_W0_RB3_S04_abort;
TH2F *bx_W0_RB3_S04_prebeam;

TH2F *bx_W0_RB3_S05_abort;
TH2F *bx_W0_RB3_S05_prebeam;

TH2F *bx_W0_RB3_S06_abort;
TH2F *bx_W0_RB3_S06_prebeam;

TH2F *bx_W0_RB3_S07_abort;
TH2F *bx_W0_RB3_S07_prebeam;

TH2F *bx_W0_RB3_S08_abort;
TH2F *bx_W0_RB3_S08_prebeam;

TH2F *bx_W0_RB3_S09_abort;
TH2F *bx_W0_RB3_S09_prebeam;

TH2F *bx_W0_RB3_S10_abort;
TH2F *bx_W0_RB3_S10_prebeam;

TH2F *bx_W0_RB3_S11_abort;
TH2F *bx_W0_RB3_S11_prebeam;

TH2F *bx_W0_RB3_S12_abort;
TH2F *bx_W0_RB3_S12_prebeam;

TH2F *bx_Wp1_RB3_S01_abort;
TH2F *bx_Wp1_RB3_S01_prebeam;

TH2F *bx_Wp1_RB3_S02_abort;
TH2F *bx_Wp1_RB3_S02_prebeam;

TH2F *bx_Wp1_RB3_S03_abort;
TH2F *bx_Wp1_RB3_S03_prebeam;

TH2F *bx_Wp1_RB3_S04_abort;
TH2F *bx_Wp1_RB3_S04_prebeam;

TH2F *bx_Wp1_RB3_S05_abort;
TH2F *bx_Wp1_RB3_S05_prebeam;

TH2F *bx_Wp1_RB3_S06_abort;
TH2F *bx_Wp1_RB3_S06_prebeam;

TH2F *bx_Wp1_RB3_S07_abort;
TH2F *bx_Wp1_RB3_S07_prebeam;

TH2F *bx_Wp1_RB3_S08_abort;
TH2F *bx_Wp1_RB3_S08_prebeam;

TH2F *bx_Wp1_RB3_S09_abort;
TH2F *bx_Wp1_RB3_S09_prebeam;

TH2F *bx_Wp1_RB3_S10_abort;
TH2F *bx_Wp1_RB3_S10_prebeam;

TH2F *bx_Wp1_RB3_S11_abort;
TH2F *bx_Wp1_RB3_S11_prebeam;

TH2F *bx_Wp1_RB3_S12_abort;
TH2F *bx_Wp1_RB3_S12_prebeam;

TH2F *bx_Wp2_RB3_S01_abort;
TH2F *bx_Wp2_RB3_S01_prebeam;

TH2F *bx_Wp2_RB3_S02_abort;
TH2F *bx_Wp2_RB3_S02_prebeam;

TH2F *bx_Wp2_RB3_S03_abort;
TH2F *bx_Wp2_RB3_S03_prebeam;

TH2F *bx_Wp2_RB3_S04_abort;
TH2F *bx_Wp2_RB3_S04_prebeam;

TH2F *bx_Wp2_RB3_S05_abort;
TH2F *bx_Wp2_RB3_S05_prebeam;

TH2F *bx_Wp2_RB3_S06_abort;
TH2F *bx_Wp2_RB3_S06_prebeam;

TH2F *bx_Wp2_RB3_S07_abort;
TH2F *bx_Wp2_RB3_S07_prebeam;

TH2F *bx_Wp2_RB3_S08_abort;
TH2F *bx_Wp2_RB3_S08_prebeam;

TH2F *bx_Wp2_RB3_S09_abort;
TH2F *bx_Wp2_RB3_S09_prebeam;

TH2F *bx_Wp2_RB3_S10_abort;
TH2F *bx_Wp2_RB3_S10_prebeam;

TH2F *bx_Wp2_RB3_S11_abort;
TH2F *bx_Wp2_RB3_S11_prebeam;

TH2F *bx_Wp2_RB3_S12_abort;
TH2F *bx_Wp2_RB3_S12_prebeam;

TH2F *bx_Wm2_RB4_S01_abort;
TH2F *bx_Wm2_RB4_S01_prebeam;

TH2F *bx_Wm2_RB4_S02_abort;
TH2F *bx_Wm2_RB4_S02_prebeam;

TH2F *bx_Wm2_RB4_S03_abort;
TH2F *bx_Wm2_RB4_S03_prebeam;

TH2F *bx_Wm2_RB4_S04_abort;
TH2F *bx_Wm2_RB4_S04_prebeam;

TH2F *bx_Wm2_RB4_S05_abort;
TH2F *bx_Wm2_RB4_S05_prebeam;

TH2F *bx_Wm2_RB4_S06_abort;
TH2F *bx_Wm2_RB4_S06_prebeam;

TH2F *bx_Wm2_RB4_S07_abort;
TH2F *bx_Wm2_RB4_S07_prebeam;

TH2F *bx_Wm2_RB4_S08_abort;
TH2F *bx_Wm2_RB4_S08_prebeam;

TH2F *bx_Wm2_RB4_S09_abort;
TH2F *bx_Wm2_RB4_S09_prebeam;

TH2F *bx_Wm2_RB4_S10_abort;
TH2F *bx_Wm2_RB4_S10_prebeam;

TH2F *bx_Wm2_RB4_S11_abort;
TH2F *bx_Wm2_RB4_S11_prebeam;

TH2F *bx_Wm2_RB4_S12_abort;
TH2F *bx_Wm2_RB4_S12_prebeam;

TH2F *bx_Wm1_RB4_S01_abort;
TH2F *bx_Wm1_RB4_S01_prebeam;

TH2F *bx_Wm1_RB4_S02_abort;
TH2F *bx_Wm1_RB4_S02_prebeam;

TH2F *bx_Wm1_RB4_S03_abort;
TH2F *bx_Wm1_RB4_S03_prebeam;

TH2F *bx_Wm1_RB4_S04_abort;
TH2F *bx_Wm1_RB4_S04_prebeam;

TH2F *bx_Wm1_RB4_S05_abort;
TH2F *bx_Wm1_RB4_S05_prebeam;

TH2F *bx_Wm1_RB4_S06_abort;
TH2F *bx_Wm1_RB4_S06_prebeam;

TH2F *bx_Wm1_RB4_S07_abort;
TH2F *bx_Wm1_RB4_S07_prebeam;

TH2F *bx_Wm1_RB4_S08_abort;
TH2F *bx_Wm1_RB4_S08_prebeam;

TH2F *bx_Wm1_RB4_S09_abort;
TH2F *bx_Wm1_RB4_S09_prebeam;

TH2F *bx_Wm1_RB4_S10_abort;
TH2F *bx_Wm1_RB4_S10_prebeam;

TH2F *bx_Wm1_RB4_S11_abort;
TH2F *bx_Wm1_RB4_S11_prebeam;

TH2F *bx_Wm1_RB4_S12_abort;
TH2F *bx_Wm1_RB4_S12_prebeam;

TH2F *bx_W0_RB4_S01_abort;
TH2F *bx_W0_RB4_S01_prebeam;

TH2F *bx_W0_RB4_S02_abort;
TH2F *bx_W0_RB4_S02_prebeam;

TH2F *bx_W0_RB4_S03_abort;
TH2F *bx_W0_RB4_S03_prebeam;

TH2F *bx_W0_RB4_S04_abort;
TH2F *bx_W0_RB4_S04_prebeam;

TH2F *bx_W0_RB4_S05_abort;
TH2F *bx_W0_RB4_S05_prebeam;

TH2F *bx_W0_RB4_S06_abort;
TH2F *bx_W0_RB4_S06_prebeam;

TH2F *bx_W0_RB4_S07_abort;
TH2F *bx_W0_RB4_S07_prebeam;

TH2F *bx_W0_RB4_S08_abort;
TH2F *bx_W0_RB4_S08_prebeam;

TH2F *bx_W0_RB4_S09_abort;
TH2F *bx_W0_RB4_S09_prebeam;

TH2F *bx_W0_RB4_S10_abort;
TH2F *bx_W0_RB4_S10_prebeam;

TH2F *bx_W0_RB4_S11_abort;
TH2F *bx_W0_RB4_S11_prebeam;

TH2F *bx_W0_RB4_S12_abort;
TH2F *bx_W0_RB4_S12_prebeam;

TH2F *bx_Wp1_RB4_S01_abort;
TH2F *bx_Wp1_RB4_S01_prebeam;

TH2F *bx_Wp1_RB4_S02_abort;
TH2F *bx_Wp1_RB4_S02_prebeam;

TH2F *bx_Wp1_RB4_S03_abort;
TH2F *bx_Wp1_RB4_S03_prebeam;

TH2F *bx_Wp1_RB4_S04_abort;
TH2F *bx_Wp1_RB4_S04_prebeam;

TH2F *bx_Wp1_RB4_S05_abort;
TH2F *bx_Wp1_RB4_S05_prebeam;

TH2F *bx_Wp1_RB4_S06_abort;
TH2F *bx_Wp1_RB4_S06_prebeam;

TH2F *bx_Wp1_RB4_S07_abort;
TH2F *bx_Wp1_RB4_S07_prebeam;

TH2F *bx_Wp1_RB4_S08_abort;
TH2F *bx_Wp1_RB4_S08_prebeam;

TH2F *bx_Wp1_RB4_S09_abort;
TH2F *bx_Wp1_RB4_S09_prebeam;

TH2F *bx_Wp1_RB4_S10_abort;
TH2F *bx_Wp1_RB4_S10_prebeam;

TH2F *bx_Wp1_RB4_S11_abort;
TH2F *bx_Wp1_RB4_S11_prebeam;

TH2F *bx_Wp1_RB4_S12_abort;
TH2F *bx_Wp1_RB4_S12_prebeam;

TH2F *bx_Wp2_RB4_S01_abort;
TH2F *bx_Wp2_RB4_S01_prebeam;

TH2F *bx_Wp2_RB4_S02_abort;
TH2F *bx_Wp2_RB4_S02_prebeam;

TH2F *bx_Wp2_RB4_S03_abort;
TH2F *bx_Wp2_RB4_S03_prebeam;

TH2F *bx_Wp2_RB4_S04_abort;
TH2F *bx_Wp2_RB4_S04_prebeam;

TH2F *bx_Wp2_RB4_S05_abort;
TH2F *bx_Wp2_RB4_S05_prebeam;

TH2F *bx_Wp2_RB4_S06_abort;
TH2F *bx_Wp2_RB4_S06_prebeam;

TH2F *bx_Wp2_RB4_S07_abort;
TH2F *bx_Wp2_RB4_S07_prebeam;

TH2F *bx_Wp2_RB4_S08_abort;
TH2F *bx_Wp2_RB4_S08_prebeam;

TH2F *bx_Wp2_RB4_S09_abort;
TH2F *bx_Wp2_RB4_S09_prebeam;

TH2F *bx_Wp2_RB4_S10_abort;
TH2F *bx_Wp2_RB4_S10_prebeam;

TH2F *bx_Wp2_RB4_S11_abort;
TH2F *bx_Wp2_RB4_S11_prebeam;

TH2F *bx_Wp2_RB4_S12_abort;
TH2F *bx_Wp2_RB4_S12_prebeam;

TH2F *bx_REp42_S01_abort;
TH2F *bx_REp42_S01_prebeam;

TH2F *bx_REp42_S02_abort;
TH2F *bx_REp42_S02_prebeam;

TH2F *bx_REp42_S03_abort;
TH2F *bx_REp42_S03_prebeam;

TH2F *bx_REp42_S04_abort;
TH2F *bx_REp42_S04_prebeam;

TH2F *bx_REp42_S05_abort;
TH2F *bx_REp42_S05_prebeam;

TH2F *bx_REp42_S06_abort;
TH2F *bx_REp42_S06_prebeam;

TH2F *bx_REp42_S07_abort;
TH2F *bx_REp42_S07_prebeam;

TH2F *bx_REp42_S08_abort;
TH2F *bx_REp42_S08_prebeam;

TH2F *bx_REp42_S09_abort;
TH2F *bx_REp42_S09_prebeam;

TH2F *bx_REp42_S10_abort;
TH2F *bx_REp42_S10_prebeam;

TH2F *bx_REp42_S11_abort;
TH2F *bx_REp42_S11_prebeam;

TH2F *bx_REp42_S12_abort;
TH2F *bx_REp42_S12_prebeam;

TH2F *bx_REp43_S01_abort;
TH2F *bx_REp43_S01_prebeam;

TH2F *bx_REp43_S02_abort;
TH2F *bx_REp43_S02_prebeam;

TH2F *bx_REp43_S03_abort;
TH2F *bx_REp43_S03_prebeam;

TH2F *bx_REp43_S04_abort;
TH2F *bx_REp43_S04_prebeam;

TH2F *bx_REp43_S05_abort;
TH2F *bx_REp43_S05_prebeam;

TH2F *bx_REp43_S06_abort;
TH2F *bx_REp43_S06_prebeam;

TH2F *bx_REp43_S07_abort;
TH2F *bx_REp43_S07_prebeam;

TH2F *bx_REp43_S08_abort;
TH2F *bx_REp43_S08_prebeam;

TH2F *bx_REp43_S09_abort;
TH2F *bx_REp43_S09_prebeam;

TH2F *bx_REp43_S10_abort;
TH2F *bx_REp43_S10_prebeam;

TH2F *bx_REp43_S11_abort;
TH2F *bx_REp43_S11_prebeam;

TH2F *bx_REp43_S12_abort;
TH2F *bx_REp43_S12_prebeam;

TH2F *bx_REp12_S01_abort;
TH2F *bx_REp12_S01_prebeam;

TH2F *bx_REp12_S02_abort;
TH2F *bx_REp12_S02_prebeam;

TH2F *bx_REp12_S03_abort;
TH2F *bx_REp12_S03_prebeam;

TH2F *bx_REp12_S04_abort;
TH2F *bx_REp12_S04_prebeam;

TH2F *bx_REp12_S05_abort;
TH2F *bx_REp12_S05_prebeam;

TH2F *bx_REp12_S06_abort;
TH2F *bx_REp12_S06_prebeam;

TH2F *bx_REp12_S07_abort;
TH2F *bx_REp12_S07_prebeam;

TH2F *bx_REp12_S08_abort;
TH2F *bx_REp12_S08_prebeam;

TH2F *bx_REp12_S09_abort;
TH2F *bx_REp12_S09_prebeam;

TH2F *bx_REp12_S10_abort;
TH2F *bx_REp12_S10_prebeam;

TH2F *bx_REp12_S11_abort;
TH2F *bx_REp12_S11_prebeam;

TH2F *bx_REp12_S12_abort;
TH2F *bx_REp12_S12_prebeam;

TH2F *bx_REp13_S01_abort;
TH2F *bx_REp13_S01_prebeam;

TH2F *bx_REp13_S02_abort;
TH2F *bx_REp13_S02_prebeam;

TH2F *bx_REp13_S03_abort;
TH2F *bx_REp13_S03_prebeam;

TH2F *bx_REp13_S04_abort;
TH2F *bx_REp13_S04_prebeam;

TH2F *bx_REp13_S05_abort;
TH2F *bx_REp13_S05_prebeam;

TH2F *bx_REp13_S06_abort;
TH2F *bx_REp13_S06_prebeam;

TH2F *bx_REp13_S07_abort;
TH2F *bx_REp13_S07_prebeam;

TH2F *bx_REp13_S08_abort;
TH2F *bx_REp13_S08_prebeam;

TH2F *bx_REp13_S09_abort;
TH2F *bx_REp13_S09_prebeam;

TH2F *bx_REp13_S10_abort;
TH2F *bx_REp13_S10_prebeam;

TH2F *bx_REp13_S11_abort;
TH2F *bx_REp13_S11_prebeam;

TH2F *bx_REp13_S12_abort;
TH2F *bx_REp13_S12_prebeam;

TH2F *bx_REp22_S01_abort;
TH2F *bx_REp22_S01_prebeam;

TH2F *bx_REp22_S02_abort;
TH2F *bx_REp22_S02_prebeam;

TH2F *bx_REp22_S03_abort;
TH2F *bx_REp22_S03_prebeam;

TH2F *bx_REp22_S04_abort;
TH2F *bx_REp22_S04_prebeam;

TH2F *bx_REp22_S05_abort;
TH2F *bx_REp22_S05_prebeam;

TH2F *bx_REp22_S06_abort;
TH2F *bx_REp22_S06_prebeam;

TH2F *bx_REp22_S07_abort;
TH2F *bx_REp22_S07_prebeam;

TH2F *bx_REp22_S08_abort;
TH2F *bx_REp22_S08_prebeam;

TH2F *bx_REp22_S09_abort;
TH2F *bx_REp22_S09_prebeam;

TH2F *bx_REp22_S10_abort;
TH2F *bx_REp22_S10_prebeam;

TH2F *bx_REp22_S11_abort;
TH2F *bx_REp22_S11_prebeam;

TH2F *bx_REp22_S12_abort;
TH2F *bx_REp22_S12_prebeam;

TH2F *bx_REp23_S01_abort;
TH2F *bx_REp23_S01_prebeam;

TH2F *bx_REp23_S02_abort;
TH2F *bx_REp23_S02_prebeam;

TH2F *bx_REp23_S03_abort;
TH2F *bx_REp23_S03_prebeam;

TH2F *bx_REp23_S04_abort;
TH2F *bx_REp23_S04_prebeam;

TH2F *bx_REp23_S05_abort;
TH2F *bx_REp23_S05_prebeam;

TH2F *bx_REp23_S06_abort;
TH2F *bx_REp23_S06_prebeam;

TH2F *bx_REp23_S07_abort;
TH2F *bx_REp23_S07_prebeam;

TH2F *bx_REp23_S08_abort;
TH2F *bx_REp23_S08_prebeam;

TH2F *bx_REp23_S09_abort;
TH2F *bx_REp23_S09_prebeam;

TH2F *bx_REp23_S10_abort;
TH2F *bx_REp23_S10_prebeam;

TH2F *bx_REp23_S11_abort;
TH2F *bx_REp23_S11_prebeam;

TH2F *bx_REp23_S12_abort;
TH2F *bx_REp23_S12_prebeam;

TH2F *bx_REp32_S01_abort;
TH2F *bx_REp32_S01_prebeam;

TH2F *bx_REp32_S02_abort;
TH2F *bx_REp32_S02_prebeam;

TH2F *bx_REp32_S03_abort;
TH2F *bx_REp32_S03_prebeam;

TH2F *bx_REp32_S04_abort;
TH2F *bx_REp32_S04_prebeam;

TH2F *bx_REp32_S05_abort;
TH2F *bx_REp32_S05_prebeam;

TH2F *bx_REp32_S06_abort;
TH2F *bx_REp32_S06_prebeam;

TH2F *bx_REp32_S07_abort;
TH2F *bx_REp32_S07_prebeam;

TH2F *bx_REp32_S08_abort;
TH2F *bx_REp32_S08_prebeam;

TH2F *bx_REp32_S09_abort;
TH2F *bx_REp32_S09_prebeam;

TH2F *bx_REp32_S10_abort;
TH2F *bx_REp32_S10_prebeam;

TH2F *bx_REp32_S11_abort;
TH2F *bx_REp32_S11_prebeam;

TH2F *bx_REp32_S12_abort;
TH2F *bx_REp32_S12_prebeam;

TH2F *bx_REp33_S01_abort;
TH2F *bx_REp33_S01_prebeam;

TH2F *bx_REp33_S02_abort;
TH2F *bx_REp33_S02_prebeam;

TH2F *bx_REp33_S03_abort;
TH2F *bx_REp33_S03_prebeam;

TH2F *bx_REp33_S04_abort;
TH2F *bx_REp33_S04_prebeam;

TH2F *bx_REp33_S05_abort;
TH2F *bx_REp33_S05_prebeam;

TH2F *bx_REp33_S06_abort;
TH2F *bx_REp33_S06_prebeam;

TH2F *bx_REp33_S07_abort;
TH2F *bx_REp33_S07_prebeam;

TH2F *bx_REp33_S08_abort;
TH2F *bx_REp33_S08_prebeam;

TH2F *bx_REp33_S09_abort;
TH2F *bx_REp33_S09_prebeam;

TH2F *bx_REp33_S10_abort;
TH2F *bx_REp33_S10_prebeam;

TH2F *bx_REp33_S11_abort;
TH2F *bx_REp33_S11_prebeam;

TH2F *bx_REp33_S12_abort;
TH2F *bx_REp33_S12_prebeam;

TH2F *bx_REm22_S01_abort;
TH2F *bx_REm22_S01_prebeam;

TH2F *bx_REm22_S02_abort;
TH2F *bx_REm22_S02_prebeam;

TH2F *bx_REm22_S03_abort;
TH2F *bx_REm22_S03_prebeam;

TH2F *bx_REm22_S04_abort;
TH2F *bx_REm22_S04_prebeam;

TH2F *bx_REm22_S05_abort;
TH2F *bx_REm22_S05_prebeam;

TH2F *bx_REm22_S06_abort;
TH2F *bx_REm22_S06_prebeam;

TH2F *bx_REm22_S07_abort;
TH2F *bx_REm22_S07_prebeam;

TH2F *bx_REm22_S08_abort;
TH2F *bx_REm22_S08_prebeam;

TH2F *bx_REm22_S09_abort;
TH2F *bx_REm22_S09_prebeam;

TH2F *bx_REm22_S10_abort;
TH2F *bx_REm22_S10_prebeam;

TH2F *bx_REm22_S11_abort;
TH2F *bx_REm22_S11_prebeam;

TH2F *bx_REm22_S12_abort;
TH2F *bx_REm22_S12_prebeam;

TH2F *bx_REm23_S01_abort;
TH2F *bx_REm23_S01_prebeam;

TH2F *bx_REm23_S02_abort;
TH2F *bx_REm23_S02_prebeam;

TH2F *bx_REm23_S03_abort;
TH2F *bx_REm23_S03_prebeam;

TH2F *bx_REm23_S04_abort;
TH2F *bx_REm23_S04_prebeam;

TH2F *bx_REm23_S05_abort;
TH2F *bx_REm23_S05_prebeam;

TH2F *bx_REm23_S06_abort;
TH2F *bx_REm23_S06_prebeam;

TH2F *bx_REm23_S07_abort;
TH2F *bx_REm23_S07_prebeam;

TH2F *bx_REm23_S08_abort;
TH2F *bx_REm23_S08_prebeam;

TH2F *bx_REm23_S09_abort;
TH2F *bx_REm23_S09_prebeam;

TH2F *bx_REm23_S10_abort;
TH2F *bx_REm23_S10_prebeam;

TH2F *bx_REm23_S11_abort;
TH2F *bx_REm23_S11_prebeam;

TH2F *bx_REm23_S12_abort;
TH2F *bx_REm23_S12_prebeam;

TH2F *bx_REm32_S01_abort;
TH2F *bx_REm32_S01_prebeam;

TH2F *bx_REm32_S02_abort;
TH2F *bx_REm32_S02_prebeam;

TH2F *bx_REm32_S03_abort;
TH2F *bx_REm32_S03_prebeam;

TH2F *bx_REm32_S04_abort;
TH2F *bx_REm32_S04_prebeam;

TH2F *bx_REm32_S05_abort;
TH2F *bx_REm32_S05_prebeam;

TH2F *bx_REm32_S06_abort;
TH2F *bx_REm32_S06_prebeam;

TH2F *bx_REm32_S07_abort;
TH2F *bx_REm32_S07_prebeam;

TH2F *bx_REm32_S08_abort;
TH2F *bx_REm32_S08_prebeam;

TH2F *bx_REm32_S09_abort;
TH2F *bx_REm32_S09_prebeam;

TH2F *bx_REm32_S10_abort;
TH2F *bx_REm32_S10_prebeam;

TH2F *bx_REm32_S11_abort;
TH2F *bx_REm32_S11_prebeam;

TH2F *bx_REm32_S12_abort;
TH2F *bx_REm32_S12_prebeam;

TH2F *bx_REm33_S01_abort;
TH2F *bx_REm33_S01_prebeam;

TH2F *bx_REm33_S02_abort;
TH2F *bx_REm33_S02_prebeam;

TH2F *bx_REm33_S03_abort;
TH2F *bx_REm33_S03_prebeam;

TH2F *bx_REm33_S04_abort;
TH2F *bx_REm33_S04_prebeam;

TH2F *bx_REm33_S05_abort;
TH2F *bx_REm33_S05_prebeam;

TH2F *bx_REm33_S06_abort;
TH2F *bx_REm33_S06_prebeam;

TH2F *bx_REm33_S07_abort;
TH2F *bx_REm33_S07_prebeam;

TH2F *bx_REm33_S08_abort;
TH2F *bx_REm33_S08_prebeam;

TH2F *bx_REm33_S09_abort;
TH2F *bx_REm33_S09_prebeam;

TH2F *bx_REm33_S10_abort;
TH2F *bx_REm33_S10_prebeam;

TH2F *bx_REm33_S11_abort;
TH2F *bx_REm33_S11_prebeam;

TH2F *bx_REm33_S12_abort;
TH2F *bx_REm33_S12_prebeam;

TH2F *bx_Wp2_RB1out_B_abort;
TH2F *bx_Wp2_RB1out_B_prebeam;

TH2F *bx_Wp1_RB1out_B_abort;
TH2F *bx_Wp1_RB1out_B_prebeam;

TH2F *bx_W0_RB1out_B_abort;
TH2F *bx_W0_RB1out_B_prebeam;

TH2F *bx_Wm1_RB1out_B_abort;
TH2F *bx_Wm1_RB1out_B_prebeam;

TH2F *bx_Wm2_RB1out_B_abort;
TH2F *bx_Wm2_RB1out_B_prebeam;

TH2F *bx_Wp2_RB1out_F_abort;
TH2F *bx_Wp2_RB1out_F_prebeam;

TH2F *bx_Wp1_RB1out_F_abort;
TH2F *bx_Wp1_RB1out_F_prebeam;

TH2F *bx_W0_RB1out_F_abort;
TH2F *bx_W0_RB1out_F_prebeam;

TH2F *bx_Wm1_RB1out_F_abort;
TH2F *bx_Wm1_RB1out_F_prebeam;

TH2F *bx_Wm2_RB1out_F_abort;
TH2F *bx_Wm2_RB1out_F_prebeam;

TH2F *bx_Wp2_RB1in_B_abort;
TH2F *bx_Wp2_RB1in_B_prebeam;

TH2F *bx_Wp1_RB1in_B_abort;
TH2F *bx_Wp1_RB1in_B_prebeam;

TH2F *bx_W0_RB1in_B_abort;
TH2F *bx_W0_RB1in_B_prebeam;

TH2F *bx_Wm1_RB1in_B_abort;
TH2F *bx_Wm1_RB1in_B_prebeam;

TH2F *bx_Wm2_RB1in_B_abort;
TH2F *bx_Wm2_RB1in_B_prebeam;

TH2F *bx_Wp2_RB1in_F_abort;
TH2F *bx_Wp2_RB1in_F_prebeam;

TH2F *bx_Wp1_RB1in_F_abort;
TH2F *bx_Wp1_RB1in_F_prebeam;

TH2F *bx_W0_RB1in_F_abort;
TH2F *bx_W0_RB1in_F_prebeam;

TH2F *bx_Wm1_RB1in_F_abort;
TH2F *bx_Wm1_RB1in_F_prebeam;

TH2F *bx_Wm2_RB1in_F_abort;
TH2F *bx_Wm2_RB1in_F_prebeam;

TH2F *bx_Wp2_RB3_B_abort;
TH2F *bx_Wp2_RB3_B_prebeam;

TH2F *bx_Wp1_RB3_B_abort;
TH2F *bx_Wp1_RB3_B_prebeam;

TH2F *bx_W0_RB3_B_abort;
TH2F *bx_W0_RB3_B_prebeam;

TH2F *bx_Wm1_RB3_B_abort;
TH2F *bx_Wm1_RB3_B_prebeam;

TH2F *bx_Wm2_RB3_B_abort;
TH2F *bx_Wm2_RB3_B_prebeam;

TH2F *bx_Wp2_RB3_F_abort;
TH2F *bx_Wp2_RB3_F_prebeam;

TH2F *bx_Wp1_RB3_F_abort;
TH2F *bx_Wp1_RB3_F_prebeam;

TH2F *bx_W0_RB3_F_abort;
TH2F *bx_W0_RB3_F_prebeam;

TH2F *bx_Wm1_RB3_F_abort;
TH2F *bx_Wm1_RB3_F_prebeam;

TH2F *bx_Wm2_RB3_F_abort;
TH2F *bx_Wm2_RB3_F_prebeam;

TH2F *bx_Wp2_RB4_B_abort;
TH2F *bx_Wp2_RB4_B_prebeam;

TH2F *bx_Wp1_RB4_B_abort;
TH2F *bx_Wp1_RB4_B_prebeam;

TH2F *bx_W0_RB4_B_abort;
TH2F *bx_W0_RB4_B_prebeam;

TH2F *bx_Wm1_RB4_B_abort;
TH2F *bx_Wm1_RB4_B_prebeam;

TH2F *bx_Wm2_RB4_B_abort;
TH2F *bx_Wm2_RB4_B_prebeam;

TH2F *bx_Wp2_RB4_F_abort;
TH2F *bx_Wp2_RB4_F_prebeam;

TH2F *bx_Wp1_RB4_F_abort;
TH2F *bx_Wp1_RB4_F_prebeam;

TH2F *bx_W0_RB4_F_abort;
TH2F *bx_W0_RB4_F_prebeam;

TH2F *bx_Wm1_RB4_F_abort;
TH2F *bx_Wm1_RB4_F_prebeam;

TH2F *bx_Wm2_RB4_F_abort;
TH2F *bx_Wm2_RB4_F_prebeam;

TH2F *bx_Wp2_RB2out_B_abort;
TH2F *bx_Wp2_RB2out_B_prebeam;

TH2F *bx_Wp1_RB2out_B_abort;
TH2F *bx_Wp1_RB2out_B_prebeam;

TH2F *bx_W0_RB2out_B_abort;
TH2F *bx_W0_RB2out_B_prebeam;

TH2F *bx_Wm1_RB2out_B_abort;
TH2F *bx_Wm1_RB2out_B_prebeam;

TH2F *bx_Wm2_RB2out_B_abort;
TH2F *bx_Wm2_RB2out_B_prebeam;

TH2F *bx_Wp2_RB2out_F_abort;
TH2F *bx_Wp2_RB2out_F_prebeam;

TH2F *bx_Wp1_RB2out_F_abort;
TH2F *bx_Wp1_RB2out_F_prebeam;

TH2F *bx_W0_RB2out_F_abort;
TH2F *bx_W0_RB2out_F_prebeam;

TH2F *bx_Wm1_RB2out_F_abort;
TH2F *bx_Wm1_RB2out_F_prebeam;

TH2F *bx_Wm2_RB2out_F_abort;
TH2F *bx_Wm2_RB2out_F_prebeam;

TH2F *bx_Wp2_RB2out_M_abort;
TH2F *bx_Wp2_RB2out_M_prebeam;

TH2F *bx_Wm2_RB2out_M_abort;
TH2F *bx_Wm2_RB2out_M_prebeam;

TH2F *bx_Wp2_RB2in_B_abort;
TH2F *bx_Wp2_RB2in_B_prebeam;

TH2F *bx_Wp1_RB2in_B_abort;
TH2F *bx_Wp1_RB2in_B_prebeam;

TH2F *bx_W0_RB2in_B_abort;
TH2F *bx_W0_RB2in_B_prebeam;

TH2F *bx_Wm1_RB2in_B_abort;
TH2F *bx_Wm1_RB2in_B_prebeam;

TH2F *bx_Wm2_RB2in_B_abort;
TH2F *bx_Wm2_RB2in_B_prebeam;

TH2F *bx_Wp2_RB2in_F_abort;
TH2F *bx_Wp2_RB2in_F_prebeam;

TH2F *bx_Wp1_RB2in_F_abort;
TH2F *bx_Wp1_RB2in_F_prebeam;

TH2F *bx_W0_RB2in_F_abort;
TH2F *bx_W0_RB2in_F_prebeam;

TH2F *bx_Wm1_RB2in_F_abort;
TH2F *bx_Wm1_RB2in_F_prebeam;

TH2F *bx_Wm2_RB2in_F_abort;
TH2F *bx_Wm2_RB2in_F_prebeam;

TH2F *bx_Wp1_RB2in_M_abort;
TH2F *bx_Wp1_RB2in_M_prebeam;

TH2F *bx_W0_RB2in_M_abort;
TH2F *bx_W0_RB2in_M_prebeam;

TH2F *bx_Wm1_RB2in_M_abort;
TH2F *bx_Wm1_RB2in_M_prebeam;

TH2F *bx_REp12_B_abort;
TH2F *bx_REp12_B_prebeam;

TH2F *bx_REp12_M_abort;
TH2F *bx_REp12_M_prebeam;

TH2F *bx_REp12_F_abort;
TH2F *bx_REp12_F_prebeam;

TH2F *bx_REp13_B_abort;
TH2F *bx_REp13_B_prebeam;

TH2F *bx_REp13_M_abort;
TH2F *bx_REp13_M_prebeam;

TH2F *bx_REp13_F_abort;
TH2F *bx_REp13_F_prebeam;

TH2F *bx_REp42_B_abort;
TH2F *bx_REp42_B_prebeam;

TH2F *bx_REp42_M_abort;
TH2F *bx_REp42_M_prebeam;

TH2F *bx_REp42_F_abort;
TH2F *bx_REp42_F_prebeam;

TH2F *bx_REp43_B_abort;
TH2F *bx_REp43_B_prebeam;

TH2F *bx_REp43_M_abort;
TH2F *bx_REp43_M_prebeam;

TH2F *bx_REp43_F_abort;
TH2F *bx_REp43_F_prebeam;

TH2F *bx_REp22_B_abort;
TH2F *bx_REp22_B_prebeam;

TH2F *bx_REp22_M_abort;
TH2F *bx_REp22_M_prebeam;

TH2F *bx_REp22_F_abort;
TH2F *bx_REp22_F_prebeam;

TH2F *bx_REp23_B_abort;
TH2F *bx_REp23_B_prebeam;

TH2F *bx_REp23_M_abort;
TH2F *bx_REp23_M_prebeam;

TH2F *bx_REp23_F_abort;
TH2F *bx_REp23_F_prebeam;

TH2F *bx_REp32_B_abort;
TH2F *bx_REp32_B_prebeam;

TH2F *bx_REp32_M_abort;
TH2F *bx_REp32_M_prebeam;

TH2F *bx_REp32_F_abort;
TH2F *bx_REp32_F_prebeam;

TH2F *bx_REp33_B_abort;
TH2F *bx_REp33_B_prebeam;

TH2F *bx_REp33_M_abort;
TH2F *bx_REp33_M_prebeam;

TH2F *bx_REp33_F_abort;
TH2F *bx_REp33_F_prebeam;

TH2F *bx_REm42_S01_abort;
TH2F *bx_REm42_S01_prebeam;

TH2F *bx_REm42_S02_abort;
TH2F *bx_REm42_S02_prebeam;

TH2F *bx_REm42_S03_abort;
TH2F *bx_REm42_S03_prebeam;

TH2F *bx_REm42_S04_abort;
TH2F *bx_REm42_S04_prebeam;

TH2F *bx_REm42_S05_abort;
TH2F *bx_REm42_S05_prebeam;

TH2F *bx_REm42_S06_abort;
TH2F *bx_REm42_S06_prebeam;

TH2F *bx_REm42_S07_abort;
TH2F *bx_REm42_S07_prebeam;

TH2F *bx_REm42_S08_abort;
TH2F *bx_REm42_S08_prebeam;

TH2F *bx_REm42_S09_abort;
TH2F *bx_REm42_S09_prebeam;

TH2F *bx_REm42_S10_abort;
TH2F *bx_REm42_S10_prebeam;

TH2F *bx_REm42_S11_abort;
TH2F *bx_REm42_S11_prebeam;

TH2F *bx_REm42_S12_abort;
TH2F *bx_REm42_S12_prebeam;

TH2F *bx_REm43_S01_abort;
TH2F *bx_REm43_S01_prebeam;

TH2F *bx_REm43_S02_abort;
TH2F *bx_REm43_S02_prebeam;

TH2F *bx_REm43_S03_abort;
TH2F *bx_REm43_S03_prebeam;

TH2F *bx_REm43_S04_abort;
TH2F *bx_REm43_S04_prebeam;

TH2F *bx_REm43_S05_abort;
TH2F *bx_REm43_S05_prebeam;

TH2F *bx_REm43_S06_abort;
TH2F *bx_REm43_S06_prebeam;

TH2F *bx_REm43_S07_abort;
TH2F *bx_REm43_S07_prebeam;

TH2F *bx_REm43_S08_abort;
TH2F *bx_REm43_S08_prebeam;

TH2F *bx_REm43_S09_abort;
TH2F *bx_REm43_S09_prebeam;

TH2F *bx_REm43_S10_abort;
TH2F *bx_REm43_S10_prebeam;

TH2F *bx_REm43_S11_abort;
TH2F *bx_REm43_S11_prebeam;

TH2F *bx_REm43_S12_abort;
TH2F *bx_REm43_S12_prebeam;

TH2F *bx_REm12_S01_abort;
TH2F *bx_REm12_S01_prebeam;

TH2F *bx_REm12_S02_abort;
TH2F *bx_REm12_S02_prebeam;

TH2F *bx_REm12_S03_abort;
TH2F *bx_REm12_S03_prebeam;

TH2F *bx_REm12_S04_abort;
TH2F *bx_REm12_S04_prebeam;

TH2F *bx_REm12_S05_abort;
TH2F *bx_REm12_S05_prebeam;

TH2F *bx_REm12_S06_abort;
TH2F *bx_REm12_S06_prebeam;

TH2F *bx_REm12_S07_abort;
TH2F *bx_REm12_S07_prebeam;

TH2F *bx_REm12_S08_abort;
TH2F *bx_REm12_S08_prebeam;

TH2F *bx_REm12_S09_abort;
TH2F *bx_REm12_S09_prebeam;

TH2F *bx_REm12_S10_abort;
TH2F *bx_REm12_S10_prebeam;

TH2F *bx_REm12_S11_abort;
TH2F *bx_REm12_S11_prebeam;

TH2F *bx_REm12_S12_abort;
TH2F *bx_REm12_S12_prebeam;

TH2F *bx_REm13_S01_abort;
TH2F *bx_REm13_S01_prebeam;

TH2F *bx_REm13_S02_abort;
TH2F *bx_REm13_S02_prebeam;

TH2F *bx_REm13_S03_abort;
TH2F *bx_REm13_S03_prebeam;

TH2F *bx_REm13_S04_abort;
TH2F *bx_REm13_S04_prebeam;

TH2F *bx_REm13_S05_abort;
TH2F *bx_REm13_S05_prebeam;

TH2F *bx_REm13_S06_abort;
TH2F *bx_REm13_S06_prebeam;

TH2F *bx_REm13_S07_abort;
TH2F *bx_REm13_S07_prebeam;

TH2F *bx_REm13_S08_abort;
TH2F *bx_REm13_S08_prebeam;

TH2F *bx_REm13_S09_abort;
TH2F *bx_REm13_S09_prebeam;

TH2F *bx_REm13_S10_abort;
TH2F *bx_REm13_S10_prebeam;

TH2F *bx_REm13_S11_abort;
TH2F *bx_REm13_S11_prebeam;

TH2F *bx_REm13_S12_abort;
TH2F *bx_REm13_S12_prebeam;

TH2F *bx_REm12_B_abort;
TH2F *bx_REm12_B_prebeam;

TH2F *bx_REm12_M_abort;
TH2F *bx_REm12_M_prebeam;

TH2F *bx_REm12_F_abort;
TH2F *bx_REm12_F_prebeam;

TH2F *bx_REm13_B_abort;
TH2F *bx_REm13_B_prebeam;

TH2F *bx_REm13_M_abort;
TH2F *bx_REm13_M_prebeam;

TH2F *bx_REm13_F_abort;
TH2F *bx_REm13_F_prebeam;

TH2F *bx_REm42_B_abort;
TH2F *bx_REm42_B_prebeam;

TH2F *bx_REm42_M_abort;
TH2F *bx_REm42_M_prebeam;

TH2F *bx_REm42_F_abort;
TH2F *bx_REm42_F_prebeam;

TH2F *bx_REm43_B_abort;
TH2F *bx_REm43_B_prebeam;

TH2F *bx_REm43_M_abort;
TH2F *bx_REm43_M_prebeam;

TH2F *bx_REm43_F_abort;
TH2F *bx_REm43_F_prebeam;

TH2F *bx_REm22_B_abort;
TH2F *bx_REm22_B_prebeam;

TH2F *bx_REm22_M_abort;
TH2F *bx_REm22_M_prebeam;

TH2F *bx_REm22_F_abort;
TH2F *bx_REm22_F_prebeam;

TH2F *bx_REm23_B_abort;
TH2F *bx_REm23_B_prebeam;

TH2F *bx_REm23_M_abort;
TH2F *bx_REm23_M_prebeam;

TH2F *bx_REm23_F_abort;
TH2F *bx_REm23_F_prebeam;

TH2F *bx_REm32_B_abort;
TH2F *bx_REm32_B_prebeam;

TH2F *bx_REm32_M_abort;
TH2F *bx_REm32_M_prebeam;

TH2F *bx_REm32_F_abort;
TH2F *bx_REm32_F_prebeam;

TH2F *bx_REm33_B_abort;
TH2F *bx_REm33_B_prebeam;

TH2F *bx_REm33_M_abort;
TH2F *bx_REm33_M_prebeam;

TH2F *bx_REm33_F_abort;
TH2F *bx_REm33_F_prebeam;



      TH1F *lumi_low;
      TH1F *lumi_high;
      TH1F *lumi_abort;
      TH1F *lumi_prebeam;
      vector<float> *err_Wm2_RB1in=0;
      vector<float> *val_Wm2_RB1in=0;

bool low = false;
     




 


//areas


// area RB1in
      double areaWm2_RB1in_S01=0;
      double areaWm2_RB1in_S02=0;
      double areaWm2_RB1in_S03=0;
      double areaWm2_RB1in_S04=0;
      double areaWm2_RB1in_S05=0;
      double areaWm2_RB1in_S06=0;
      double areaWm2_RB1in_S07=0;
      double areaWm2_RB1in_S08=0;
      double areaWm2_RB1in_S09=0;
      double areaWm2_RB1in_S10=0;
      double areaWm2_RB1in_S11=0;
      double areaWm2_RB1in_S12=0;

      double areaWm1_RB1in_S01=0;
      double areaWm1_RB1in_S02=0;
      double areaWm1_RB1in_S03=0;
      double areaWm1_RB1in_S04=0;
      double areaWm1_RB1in_S05=0;
      double areaWm1_RB1in_S06=0;
      double areaWm1_RB1in_S07=0;
      double areaWm1_RB1in_S08=0;
      double areaWm1_RB1in_S09=0;
      double areaWm1_RB1in_S10=0;
      double areaWm1_RB1in_S11=0;
      double areaWm1_RB1in_S12=0;

      double areaW0_RB1in_S01=0;
      double areaW0_RB1in_S02=0;
      double areaW0_RB1in_S03=0;
      double areaW0_RB1in_S04=0;
      double areaW0_RB1in_S05=0;
      double areaW0_RB1in_S06=0;
      double areaW0_RB1in_S07=0;
      double areaW0_RB1in_S08=0;
      double areaW0_RB1in_S09=0;
      double areaW0_RB1in_S10=0;
      double areaW0_RB1in_S11=0;
      double areaW0_RB1in_S12=0;

      double areaWp1_RB1in_S01=0;
      double areaWp1_RB1in_S02=0;
      double areaWp1_RB1in_S03=0;
      double areaWp1_RB1in_S04=0;
      double areaWp1_RB1in_S05=0;
      double areaWp1_RB1in_S06=0;
      double areaWp1_RB1in_S07=0;
      double areaWp1_RB1in_S08=0;
      double areaWp1_RB1in_S09=0;
      double areaWp1_RB1in_S10=0;
      double areaWp1_RB1in_S11=0;
      double areaWp1_RB1in_S12=0;

      double areaWp2_RB1in_S01=0;
      double areaWp2_RB1in_S02=0;
      double areaWp2_RB1in_S03=0;
      double areaWp2_RB1in_S04=0;
      double areaWp2_RB1in_S05=0;
      double areaWp2_RB1in_S06=0;
      double areaWp2_RB1in_S07=0;
      double areaWp2_RB1in_S08=0;
      double areaWp2_RB1in_S09=0;
      double areaWp2_RB1in_S10=0;
      double areaWp2_RB1in_S11=0;
      double areaWp2_RB1in_S12=0;


// area RB1out
      double areaWm2_RB1out_S01=0;
      double areaWm2_RB1out_S02=0;
      double areaWm2_RB1out_S03=0;
      double areaWm2_RB1out_S04=0;
      double areaWm2_RB1out_S05=0;
      double areaWm2_RB1out_S06=0;
      double areaWm2_RB1out_S07=0;
      double areaWm2_RB1out_S08=0;
      double areaWm2_RB1out_S09=0;
      double areaWm2_RB1out_S10=0;
      double areaWm2_RB1out_S11=0;
      double areaWm2_RB1out_S12=0;

      double areaWm1_RB1out_S01=0;
      double areaWm1_RB1out_S02=0;
      double areaWm1_RB1out_S03=0;
      double areaWm1_RB1out_S04=0;
      double areaWm1_RB1out_S05=0;
      double areaWm1_RB1out_S06=0;
      double areaWm1_RB1out_S07=0;
      double areaWm1_RB1out_S08=0;
      double areaWm1_RB1out_S09=0;
      double areaWm1_RB1out_S10=0;
      double areaWm1_RB1out_S11=0;
      double areaWm1_RB1out_S12=0;

      double areaW0_RB1out_S01=0;
      double areaW0_RB1out_S02=0;
      double areaW0_RB1out_S03=0;
      double areaW0_RB1out_S04=0;
      double areaW0_RB1out_S05=0;
      double areaW0_RB1out_S06=0;
      double areaW0_RB1out_S07=0;
      double areaW0_RB1out_S08=0;
      double areaW0_RB1out_S09=0;
      double areaW0_RB1out_S10=0;
      double areaW0_RB1out_S11=0;
      double areaW0_RB1out_S12=0;

      double areaWp1_RB1out_S01=0;
      double areaWp1_RB1out_S02=0;
      double areaWp1_RB1out_S03=0;
      double areaWp1_RB1out_S04=0;
      double areaWp1_RB1out_S05=0;
      double areaWp1_RB1out_S06=0;
      double areaWp1_RB1out_S07=0;
      double areaWp1_RB1out_S08=0;
      double areaWp1_RB1out_S09=0;
      double areaWp1_RB1out_S10=0;
      double areaWp1_RB1out_S11=0;
      double areaWp1_RB1out_S12=0;

      double areaWp2_RB1out_S01=0;
      double areaWp2_RB1out_S02=0;
      double areaWp2_RB1out_S03=0;
      double areaWp2_RB1out_S04=0;
      double areaWp2_RB1out_S05=0;
      double areaWp2_RB1out_S06=0;
      double areaWp2_RB1out_S07=0;
      double areaWp2_RB1out_S08=0;
      double areaWp2_RB1out_S09=0;
      double areaWp2_RB1out_S10=0;
      double areaWp2_RB1out_S11=0;
      double areaWp2_RB1out_S12=0;

      double areaWm2_RB2in_S01=0;
      double areaWm2_RB2in_S02=0;
      double areaWm2_RB2in_S03=0;
      double areaWm2_RB2in_S04=0;
      double areaWm2_RB2in_S05=0;
      double areaWm2_RB2in_S06=0;
      double areaWm2_RB2in_S07=0;
      double areaWm2_RB2in_S08=0;
      double areaWm2_RB2in_S09=0;
      double areaWm2_RB2in_S10=0;
      double areaWm2_RB2in_S11=0;
      double areaWm2_RB2in_S12=0;

      double areaWm1_RB2in_S01=0;
      double areaWm1_RB2in_S02=0;
      double areaWm1_RB2in_S03=0;
      double areaWm1_RB2in_S04=0;
      double areaWm1_RB2in_S05=0;
      double areaWm1_RB2in_S06=0;
      double areaWm1_RB2in_S07=0;
      double areaWm1_RB2in_S08=0;
      double areaWm1_RB2in_S09=0;
      double areaWm1_RB2in_S10=0;
      double areaWm1_RB2in_S11=0;
      double areaWm1_RB2in_S12=0;

      double areaW0_RB2in_S01=0;
      double areaW0_RB2in_S02=0;
      double areaW0_RB2in_S03=0;
      double areaW0_RB2in_S04=0;
      double areaW0_RB2in_S05=0;
      double areaW0_RB2in_S06=0;
      double areaW0_RB2in_S07=0;
      double areaW0_RB2in_S08=0;
      double areaW0_RB2in_S09=0;
      double areaW0_RB2in_S10=0;
      double areaW0_RB2in_S11=0;
      double areaW0_RB2in_S12=0;

      double areaWp1_RB2in_S01=0;
      double areaWp1_RB2in_S02=0;
      double areaWp1_RB2in_S03=0;
      double areaWp1_RB2in_S04=0;
      double areaWp1_RB2in_S05=0;
      double areaWp1_RB2in_S06=0;
      double areaWp1_RB2in_S07=0;
      double areaWp1_RB2in_S08=0;
      double areaWp1_RB2in_S09=0;
      double areaWp1_RB2in_S10=0;
      double areaWp1_RB2in_S11=0;
      double areaWp1_RB2in_S12=0;

      double areaWp2_RB2in_S01=0;
      double areaWp2_RB2in_S02=0;
      double areaWp2_RB2in_S03=0;
      double areaWp2_RB2in_S04=0;
      double areaWp2_RB2in_S05=0;
      double areaWp2_RB2in_S06=0;
      double areaWp2_RB2in_S07=0;
      double areaWp2_RB2in_S08=0;
      double areaWp2_RB2in_S09=0;
      double areaWp2_RB2in_S10=0;
      double areaWp2_RB2in_S11=0;
      double areaWp2_RB2in_S12=0;


// area RB2out
      double areaWm2_RB2out_S01=0;
      double areaWm2_RB2out_S02=0;
      double areaWm2_RB2out_S03=0;
      double areaWm2_RB2out_S04=0;
      double areaWm2_RB2out_S05=0;
      double areaWm2_RB2out_S06=0;
      double areaWm2_RB2out_S07=0;
      double areaWm2_RB2out_S08=0;
      double areaWm2_RB2out_S09=0;
      double areaWm2_RB2out_S10=0;
      double areaWm2_RB2out_S11=0;
      double areaWm2_RB2out_S12=0;

      double areaWm1_RB2out_S01=0;
      double areaWm1_RB2out_S02=0;
      double areaWm1_RB2out_S03=0;
      double areaWm1_RB2out_S04=0;
      double areaWm1_RB2out_S05=0;
      double areaWm1_RB2out_S06=0;
      double areaWm1_RB2out_S07=0;
      double areaWm1_RB2out_S08=0;
      double areaWm1_RB2out_S09=0;
      double areaWm1_RB2out_S10=0;
      double areaWm1_RB2out_S11=0;
      double areaWm1_RB2out_S12=0;

      double areaW0_RB2out_S01=0;
      double areaW0_RB2out_S02=0;
      double areaW0_RB2out_S03=0;
      double areaW0_RB2out_S04=0;
      double areaW0_RB2out_S05=0;
      double areaW0_RB2out_S06=0;
      double areaW0_RB2out_S07=0;
      double areaW0_RB2out_S08=0;
      double areaW0_RB2out_S09=0;
      double areaW0_RB2out_S10=0;
      double areaW0_RB2out_S11=0;
      double areaW0_RB2out_S12=0;

      double areaWp1_RB2out_S01=0;
      double areaWp1_RB2out_S02=0;
      double areaWp1_RB2out_S03=0;
      double areaWp1_RB2out_S04=0;
      double areaWp1_RB2out_S05=0;
      double areaWp1_RB2out_S06=0;
      double areaWp1_RB2out_S07=0;
      double areaWp1_RB2out_S08=0;
      double areaWp1_RB2out_S09=0;
      double areaWp1_RB2out_S10=0;
      double areaWp1_RB2out_S11=0;
      double areaWp1_RB2out_S12=0;

      double areaWp2_RB2out_S01=0;
      double areaWp2_RB2out_S02=0;
      double areaWp2_RB2out_S03=0;
      double areaWp2_RB2out_S04=0;
      double areaWp2_RB2out_S05=0;
      double areaWp2_RB2out_S06=0;
      double areaWp2_RB2out_S07=0;
      double areaWp2_RB2out_S08=0;
      double areaWp2_RB2out_S09=0;
      double areaWp2_RB2out_S10=0;
      double areaWp2_RB2out_S11=0;
      double areaWp2_RB2out_S12=0;



      double areaWm2_RB3_S01=0;
      double areaWm2_RB3_S02=0;
      double areaWm2_RB3_S03=0;
      double areaWm2_RB3_S04=0;
      double areaWm2_RB3_S05=0;
      double areaWm2_RB3_S06=0;
      double areaWm2_RB3_S07=0;
      double areaWm2_RB3_S08=0;
      double areaWm2_RB3_S09=0;
      double areaWm2_RB3_S10=0;
      double areaWm2_RB3_S11=0;
      double areaWm2_RB3_S12=0;
      double areaWm1_RB3_S01=0;
      double areaWm1_RB3_S02=0;
      double areaWm1_RB3_S03=0;
      double areaWm1_RB3_S04=0;
      double areaWm1_RB3_S05=0;
      double areaWm1_RB3_S06=0;
      double areaWm1_RB3_S07=0;
      double areaWm1_RB3_S08=0;
      double areaWm1_RB3_S09=0;
      double areaWm1_RB3_S10=0;
      double areaWm1_RB3_S11=0;
      double areaWm1_RB3_S12=0;
      double areaW0_RB3_S01=0;
      double areaW0_RB3_S02=0;
      double areaW0_RB3_S03=0;
      double areaW0_RB3_S04=0;
      double areaW0_RB3_S05=0;
      double areaW0_RB3_S06=0;
      double areaW0_RB3_S07=0;
      double areaW0_RB3_S08=0;
      double areaW0_RB3_S09=0;
      double areaW0_RB3_S10=0;
      double areaW0_RB3_S11=0;
      double areaW0_RB3_S12=0;
      double areaWp1_RB3_S01=0;
      double areaWp1_RB3_S02=0;
      double areaWp1_RB3_S03=0;
      double areaWp1_RB3_S04=0;
      double areaWp1_RB3_S05=0;
      double areaWp1_RB3_S06=0;
      double areaWp1_RB3_S07=0;
      double areaWp1_RB3_S08=0;
      double areaWp1_RB3_S09=0;
      double areaWp1_RB3_S10=0;
      double areaWp1_RB3_S11=0;
      double areaWp1_RB3_S12=0;
      double areaWp2_RB3_S01=0;
      double areaWp2_RB3_S02=0;
      double areaWp2_RB3_S03=0;
      double areaWp2_RB3_S04=0;
      double areaWp2_RB3_S05=0;
      double areaWp2_RB3_S06=0;
      double areaWp2_RB3_S07=0;
      double areaWp2_RB3_S08=0;
      double areaWp2_RB3_S09=0;
      double areaWp2_RB3_S10=0;
      double areaWp2_RB3_S11=0;
      double areaWp2_RB3_S12=0;
      double areaWm2_RB4_S01=0;
      double areaWm2_RB4_S02=0;
      double areaWm2_RB4_S03=0;
      double areaWm2_RB4_S04=0;
      double areaWm2_RB4_S05=0;
      double areaWm2_RB4_S06=0;
      double areaWm2_RB4_S07=0;
      double areaWm2_RB4_S08=0;
      double areaWm2_RB4_S09=0;
      double areaWm2_RB4_S10=0;
      double areaWm2_RB4_S11=0;
      double areaWm2_RB4_S12=0;
      double areaWm1_RB4_S01=0;
      double areaWm1_RB4_S02=0;
      double areaWm1_RB4_S03=0;
      double areaWm1_RB4_S04=0;
      double areaWm1_RB4_S05=0;
      double areaWm1_RB4_S06=0;
      double areaWm1_RB4_S07=0;
      double areaWm1_RB4_S08=0;
      double areaWm1_RB4_S09=0;
      double areaWm1_RB4_S10=0;
      double areaWm1_RB4_S11=0;
      double areaWm1_RB4_S12=0;
      double areaW0_RB4_S01=0;
      double areaW0_RB4_S02=0;
      double areaW0_RB4_S03=0;
      double areaW0_RB4_S04=0;
      double areaW0_RB4_S05=0;
      double areaW0_RB4_S06=0;
      double areaW0_RB4_S07=0;
      double areaW0_RB4_S08=0;
      double areaW0_RB4_S09=0;
      double areaW0_RB4_S10=0;
      double areaW0_RB4_S11=0;
      double areaW0_RB4_S12=0;
      double areaWp1_RB4_S01=0;
      double areaWp1_RB4_S02=0;
      double areaWp1_RB4_S03=0;
      double areaWp1_RB4_S04=0;
      double areaWp1_RB4_S05=0;
      double areaWp1_RB4_S06=0;
      double areaWp1_RB4_S07=0;
      double areaWp1_RB4_S08=0;
      double areaWp1_RB4_S09=0;
      double areaWp1_RB4_S10=0;
      double areaWp1_RB4_S11=0;
      double areaWp1_RB4_S12=0;
      double areaWp2_RB4_S01=0;
      double areaWp2_RB4_S02=0;
      double areaWp2_RB4_S03=0;
      double areaWp2_RB4_S04=0;
      double areaWp2_RB4_S05=0;
      double areaWp2_RB4_S06=0;
      double areaWp2_RB4_S07=0;
      double areaWp2_RB4_S08=0;
      double areaWp2_RB4_S09=0;
      double areaWp2_RB4_S10=0;
      double areaWp2_RB4_S11=0;
      double areaWp2_RB4_S12=0;

//
      double areaREp42_S01=0;
      double areaREp42_S02=0;
      double areaREp42_S03=0;
      double areaREp42_S04=0;
      double areaREp42_S05=0;
      double areaREp42_S06=0;
      double areaREp42_S07=0;
      double areaREp42_S08=0;
      double areaREp42_S09=0;
      double areaREp42_S10=0;
      double areaREp42_S11=0;
      double areaREp42_S12=0;

      double areaREp43_S01=0;
      double areaREp43_S02=0;
      double areaREp43_S03=0;
      double areaREp43_S04=0;
      double areaREp43_S05=0;
      double areaREp43_S06=0;
      double areaREp43_S07=0;
      double areaREp43_S08=0;
      double areaREp43_S09=0;
      double areaREp43_S10=0;
      double areaREp43_S11=0;
      double areaREp43_S12=0;

      double areaREp12_S01=0;
      double areaREp12_S02=0;
      double areaREp12_S03=0;
      double areaREp12_S04=0;
      double areaREp12_S05=0;
      double areaREp12_S06=0;
      double areaREp12_S07=0;
      double areaREp12_S08=0;
      double areaREp12_S09=0;
      double areaREp12_S10=0;
      double areaREp12_S11=0;
      double areaREp12_S12=0;

      double areaREp13_S01=0;
      double areaREp13_S02=0;
      double areaREp13_S03=0;
      double areaREp13_S04=0;
      double areaREp13_S05=0;
      double areaREp13_S06=0;
      double areaREp13_S07=0;
      double areaREp13_S08=0;
      double areaREp13_S09=0;
      double areaREp13_S10=0;
      double areaREp13_S11=0;
      double areaREp13_S12=0;

      double areaREp22_S01=0;
      double areaREp22_S02=0;
      double areaREp22_S03=0;
      double areaREp22_S04=0;
      double areaREp22_S05=0;
      double areaREp22_S06=0;
      double areaREp22_S07=0;
      double areaREp22_S08=0;
      double areaREp22_S09=0;
      double areaREp22_S10=0;
      double areaREp22_S11=0;
      double areaREp22_S12=0;

      double areaREp23_S01=0;
      double areaREp23_S02=0;
      double areaREp23_S03=0;
      double areaREp23_S04=0;
      double areaREp23_S05=0;
      double areaREp23_S06=0;
      double areaREp23_S07=0;
      double areaREp23_S08=0;
      double areaREp23_S09=0;
      double areaREp23_S10=0;
      double areaREp23_S11=0;
      double areaREp23_S12=0;

      double areaREp32_S01=0;
      double areaREp32_S02=0;
      double areaREp32_S03=0;
      double areaREp32_S04=0;
      double areaREp32_S05=0;
      double areaREp32_S06=0;
      double areaREp32_S07=0;
      double areaREp32_S08=0;
      double areaREp32_S09=0;
      double areaREp32_S10=0;
      double areaREp32_S11=0;
      double areaREp32_S12=0;
      double areaREp33_S01=0;
      double areaREp33_S02=0;
      double areaREp33_S03=0;
      double areaREp33_S04=0;
      double areaREp33_S05=0;
      double areaREp33_S06=0;
      double areaREp33_S07=0;
      double areaREp33_S08=0;
      double areaREp33_S09=0;
      double areaREp33_S10=0;
      double areaREp33_S11=0;
      double areaREp33_S12=0;

// area

// RB1out
      double areaWp2_RB1out_B=0;
      double areaWp1_RB1out_B=0;
      double areaW0_RB1out_B=0;
      double areaWm1_RB1out_B=0;
      double areaWm2_RB1out_B=0;

      double areaWp2_RB1out_F=0;
      double areaWp1_RB1out_F=0;
      double areaW0_RB1out_F=0;
      double areaWm1_RB1out_F=0;
      double areaWm2_RB1out_F=0;

// RB1in

      double areaWp2_RB1in_B=0;
      double areaWp1_RB1in_B=0;
      double areaW0_RB1in_B=0;
      double areaWm1_RB1in_B=0;
      double areaWm2_RB1in_B=0;

      double areaWp2_RB1in_F=0;
      double areaWp1_RB1in_F=0;
      double areaW0_RB1in_F=0;
      double areaWm1_RB1in_F=0;
      double areaWm2_RB1in_F=0;

 //RB3

      double areaWp2_RB3_B=0;
      double areaWp1_RB3_B=0;
      double areaW0_RB3_B=0;
      double areaWm1_RB3_B=0;
      double areaWm2_RB3_B=0;

      double areaWp2_RB3_F=0;
      double areaWp1_RB3_F=0;
      double areaW0_RB3_F=0;
      double areaWm1_RB3_F=0;
      double areaWm2_RB3_F=0;

// RB4

      double areaWp2_RB4_B=0;
      double areaWp1_RB4_B=0;
      double areaW0_RB4_B=0;
      double areaWm1_RB4_B=0;
      double areaWm2_RB4_B=0;

      double areaWp2_RB4_F=0;
      double areaWp1_RB4_F=0;
      double areaW0_RB4_F=0;
      double areaWm1_RB4_F=0;
      double areaWm2_RB4_F=0;



// RB2out
      double areaWp2_RB2out_B=0;
      double areaWp1_RB2out_B=0;
      double areaW0_RB2out_B=0;
      double areaWm1_RB2out_B=0;
      double areaWm2_RB2out_B=0;

      double areaWp2_RB2out_F=0;
      double areaWp1_RB2out_F=0;
      double areaW0_RB2out_F=0;
      double areaWm1_RB2out_F=0;
      double areaWm2_RB2out_F=0;

      double areaWp2_RB2out_M=0;
      double areaWm2_RB2out_M=0;


// RB2in

      double areaWp2_RB2in_B=0;
      double areaWp1_RB2in_B=0;
      double areaW0_RB2in_B=0;
      double areaWm1_RB2in_B=0;
      double areaWm2_RB2in_B=0;

      double areaWp2_RB2in_F=0;
      double areaWp1_RB2in_F=0;
      double areaW0_RB2in_F=0;
      double areaWm1_RB2in_F=0;
      double areaWm2_RB2in_F=0;

      double areaWp1_RB2in_M=0;
      double areaW0_RB2in_M=0;
      double areaWm1_RB2in_M=0;

// REp12

      double areaREp12_B=0;
      double areaREp12_M=0;
      double areaREp12_F=0;

// REp13

      double areaREp13_B=0;
      double areaREp13_M=0;
      double areaREp13_F=0;

// REp42

      double areaREp42_B=0;
      double areaREp42_M=0;
      double areaREp42_F=0;

// REp43

      double areaREp43_B=0;
      double areaREp43_M=0;
      double areaREp43_F=0;

      double areaREp22_B=0;
      double areaREp22_M=0;
      double areaREp22_F=0;
      double areaREp23_B=0;
      double areaREp23_M=0;
      double areaREp23_F=0;
      double areaREp32_B=0;
      double areaREp32_M=0;
      double areaREp32_F=0;
      double areaREp33_B=0;
      double areaREp33_M=0;
      double areaREp33_F=0;

// endcap negative

      double areaREm42_S01=0;
      double areaREm42_S02=0;
      double areaREm42_S03=0;
      double areaREm42_S04=0;
      double areaREm42_S05=0;
      double areaREm42_S06=0;
      double areaREm42_S07=0;
      double areaREm42_S08=0;
      double areaREm42_S09=0;
      double areaREm42_S10=0;
      double areaREm42_S11=0;
      double areaREm42_S12=0;
      double areaREm43_S01=0;
      double areaREm43_S02=0;
      double areaREm43_S03=0;
      double areaREm43_S04=0;
      double areaREm43_S05=0;
      double areaREm43_S06=0;
      double areaREm43_S07=0;
      double areaREm43_S08=0;
      double areaREm43_S09=0;
      double areaREm43_S10=0;
      double areaREm43_S11=0;
      double areaREm43_S12=0;
      double areaREm12_S01=0;
      double areaREm12_S02=0;
      double areaREm12_S03=0;
      double areaREm12_S04=0;
      double areaREm12_S05=0;
      double areaREm12_S06=0;
      double areaREm12_S07=0;
      double areaREm12_S08=0;
      double areaREm12_S09=0;
      double areaREm12_S10=0;
      double areaREm12_S11=0;
      double areaREm12_S12=0;
      double areaREm13_S01=0;
      double areaREm13_S02=0;
      double areaREm13_S03=0;
      double areaREm13_S04=0;
      double areaREm13_S05=0;
      double areaREm13_S06=0;
      double areaREm13_S07=0;
      double areaREm13_S08=0;
      double areaREm13_S09=0;
      double areaREm13_S10=0;
      double areaREm13_S11=0;
      double areaREm13_S12=0;

      double areaREm22_S01=0;
      double areaREm22_S02=0;
      double areaREm22_S03=0;
      double areaREm22_S04=0;
      double areaREm22_S05=0;
      double areaREm22_S06=0;
      double areaREm22_S07=0;
      double areaREm22_S08=0;
      double areaREm22_S09=0;
      double areaREm22_S10=0;
      double areaREm22_S11=0;
      double areaREm22_S12=0;

      double areaREm23_S01=0;
      double areaREm23_S02=0;
      double areaREm23_S03=0;
      double areaREm23_S04=0;
      double areaREm23_S05=0;
      double areaREm23_S06=0;
      double areaREm23_S07=0;
      double areaREm23_S08=0;
      double areaREm23_S09=0;
      double areaREm23_S10=0;
      double areaREm23_S11=0;
      double areaREm23_S12=0;

      double areaREm32_S01=0;
      double areaREm32_S02=0;
      double areaREm32_S03=0;
      double areaREm32_S04=0;
      double areaREm32_S05=0;
      double areaREm32_S06=0;
      double areaREm32_S07=0;
      double areaREm32_S08=0;
      double areaREm32_S09=0;
      double areaREm32_S10=0;
      double areaREm32_S11=0;
      double areaREm32_S12=0;
      double areaREm33_S01=0;
      double areaREm33_S02=0;
      double areaREm33_S03=0;
      double areaREm33_S04=0;
      double areaREm33_S05=0;
      double areaREm33_S06=0;
      double areaREm33_S07=0;
      double areaREm33_S08=0;
      double areaREm33_S09=0;
      double areaREm33_S10=0;
      double areaREm33_S11=0;
      double areaREm33_S12=0;



      double areaREm12_B=0;
      double areaREm12_M=0;
      double areaREm12_F=0;
      double areaREm13_B=0;
      double areaREm13_M=0;
      double areaREm13_F=0;
      double areaREm42_B=0;
      double areaREm42_M=0;
      double areaREm42_F=0;
      double areaREm43_B=0;
      double areaREm43_M=0;
      double areaREm43_F=0;

      double areaREm22_B=0;
      double areaREm22_M=0;
      double areaREm22_F=0;
      double areaREm23_B=0;
      double areaREm23_M=0;
      double areaREm23_F=0;
      double areaREm32_B=0;
      double areaREm32_M=0;
      double areaREm32_F=0;
      double areaREm33_B=0;
      double areaREm33_M=0;
      double areaREm33_F=0;



         
      edm::Service<TFileService> fs;
};

RateVsLumi_PhiEtaRecompute::RateVsLumi_PhiEtaRecompute(const edm::ParameterSet& iConfig)
: rpcGeoToken_(esConsumes())
{
  debug=iConfig.getUntrackedParameter<bool>("debug",false);
  doAllBXs_=iConfig.getUntrackedParameter<bool>("doAllBXs",true);
  doAllBXno0_=iConfig.getUntrackedParameter<bool>("doAllBXno0",false);
  numbBXs_ = iConfig.getParameter<int>("numbBXs");
  rpcRecHitsLabel = consumes<RPCRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("rpcRecHits_tag"));
  scalersSourceToken_ = consumes<OnlineLuminosityRecord>(iConfig.getParameter<edm::InputTag>("scalersResults"));
  doRechits_=iConfig.getUntrackedParameter<bool>("doRechits",true);
  myBlackList_ = iConfig.getParameter<std::string>("myBlackList");
  uncolliding_ = iConfig.getParameter<std::string>("uncolliding");
  usesResource("TFileService");
}

RateVsLumi_PhiEtaRecompute::~RateVsLumi_PhiEtaRecompute()
{}

// ------------ method called for each event  ------------
void
RateVsLumi_PhiEtaRecompute::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  fstream myBlListStream;
  fstream uncollidingStream;
  uint32_t myId;
  string myName;
  std::vector<uint32_t> idBlackList;
  std::vector<int> uncolliding;
  int uncollBX;


  myBlListStream.open(myBlackList_, ios::in); //map the names and rollIds
  for (; myBlListStream >> myName >> myId;)
  {
#ifdef debug
    cout << myId << "\t"<< myName << endl;
#endif
    idBlackList.push_back(myId);
  }
  myBlListStream.close();

uncollidingStream.open(uncolliding_, ios::in); //map the names and rollIds
  for (; uncollidingStream >>uncollBX;)
  {

    uncolliding.push_back(uncollBX);
  }
  uncollidingStream.close();

  //numbEvents->Fill(1);
  using namespace edm;
//areas
  double area = 0.0;
  double stripArea = 0.0;


 

  areaWm2_RB1in_S01=0;
  areaWm2_RB1in_S02=0;
  areaWm2_RB1in_S03=0;
  areaWm2_RB1in_S04=0;
  areaWm2_RB1in_S05=0;
  areaWm2_RB1in_S06=0;
  areaWm2_RB1in_S07=0;
  areaWm2_RB1in_S08=0;
  areaWm2_RB1in_S09=0;
  areaWm2_RB1in_S10=0;
  areaWm2_RB1in_S11=0;
  areaWm2_RB1in_S12=0;

  areaWm1_RB1in_S01=0;
  areaWm1_RB1in_S02=0;
  areaWm1_RB1in_S03=0;
  areaWm1_RB1in_S04=0;
  areaWm1_RB1in_S05=0;
  areaWm1_RB1in_S06=0;
  areaWm1_RB1in_S07=0;
  areaWm1_RB1in_S08=0;
  areaWm1_RB1in_S09=0;
  areaWm1_RB1in_S10=0;
  areaWm1_RB1in_S11=0;
  areaWm1_RB1in_S12=0;

  areaW0_RB1in_S01=0;
  areaW0_RB1in_S02=0;
  areaW0_RB1in_S03=0;
  areaW0_RB1in_S04=0;
  areaW0_RB1in_S05=0;
  areaW0_RB1in_S06=0;
  areaW0_RB1in_S07=0;
  areaW0_RB1in_S08=0;
  areaW0_RB1in_S09=0;
  areaW0_RB1in_S10=0;
  areaW0_RB1in_S11=0;
  areaW0_RB1in_S12=0;

  areaWp1_RB1in_S01=0;
  areaWp1_RB1in_S02=0;
  areaWp1_RB1in_S03=0;
  areaWp1_RB1in_S04=0;
  areaWp1_RB1in_S05=0;
  areaWp1_RB1in_S06=0;
  areaWp1_RB1in_S07=0;
  areaWp1_RB1in_S08=0;
  areaWp1_RB1in_S09=0;
  areaWp1_RB1in_S10=0;
  areaWp1_RB1in_S11=0;
  areaWp1_RB1in_S12=0;

  areaWp2_RB1in_S01=0;
  areaWp2_RB1in_S02=0;
  areaWp2_RB1in_S03=0;
  areaWp2_RB1in_S04=0;
  areaWp2_RB1in_S05=0;
  areaWp2_RB1in_S06=0;
  areaWp2_RB1in_S07=0;
  areaWp2_RB1in_S08=0;
  areaWp2_RB1in_S09=0;
  areaWp2_RB1in_S10=0;
  areaWp2_RB1in_S11=0;
  areaWp2_RB1in_S12=0;

  areaWm2_RB1out_S01=0;
  areaWm2_RB1out_S02=0;
  areaWm2_RB1out_S03=0;
  areaWm2_RB1out_S04=0;
  areaWm2_RB1out_S05=0;
  areaWm2_RB1out_S06=0;
  areaWm2_RB1out_S07=0;
  areaWm2_RB1out_S08=0;
  areaWm2_RB1out_S09=0;
  areaWm2_RB1out_S10=0;
  areaWm2_RB1out_S11=0;
  areaWm2_RB1out_S12=0;

  areaWm1_RB1out_S01=0;
  areaWm1_RB1out_S02=0;
  areaWm1_RB1out_S03=0;
  areaWm1_RB1out_S04=0;
  areaWm1_RB1out_S05=0;
  areaWm1_RB1out_S06=0;
  areaWm1_RB1out_S07=0;
  areaWm1_RB1out_S08=0;
  areaWm1_RB1out_S09=0;
  areaWm1_RB1out_S10=0;
  areaWm1_RB1out_S11=0;
  areaWm1_RB1out_S12=0;

  areaW0_RB1out_S01=0;
  areaW0_RB1out_S02=0;
  areaW0_RB1out_S03=0;
  areaW0_RB1out_S04=0;
  areaW0_RB1out_S05=0;
  areaW0_RB1out_S06=0;
  areaW0_RB1out_S07=0;
  areaW0_RB1out_S08=0;
  areaW0_RB1out_S09=0;
  areaW0_RB1out_S10=0;
  areaW0_RB1out_S11=0;
  areaW0_RB1out_S12=0;

  areaWp1_RB1out_S01=0;
  areaWp1_RB1out_S02=0;
  areaWp1_RB1out_S03=0;
  areaWp1_RB1out_S04=0;
  areaWp1_RB1out_S05=0;
  areaWp1_RB1out_S06=0;
  areaWp1_RB1out_S07=0;
  areaWp1_RB1out_S08=0;
  areaWp1_RB1out_S09=0;
  areaWp1_RB1out_S10=0;
  areaWp1_RB1out_S11=0;
  areaWp1_RB1out_S12=0;

  areaWp2_RB1out_S01=0;
  areaWp2_RB1out_S02=0;
  areaWp2_RB1out_S03=0;
  areaWp2_RB1out_S04=0;
  areaWp2_RB1out_S05=0;
  areaWp2_RB1out_S06=0;
  areaWp2_RB1out_S07=0;
  areaWp2_RB1out_S08=0;
  areaWp2_RB1out_S09=0;
  areaWp2_RB1out_S10=0;
  areaWp2_RB1out_S11=0;
  areaWp2_RB1out_S12=0;

  areaWm2_RB2in_S01=0;
  areaWm2_RB2in_S02=0;
  areaWm2_RB2in_S03=0;
  areaWm2_RB2in_S04=0;
  areaWm2_RB2in_S05=0;
  areaWm2_RB2in_S06=0;
  areaWm2_RB2in_S07=0;
  areaWm2_RB2in_S08=0;
  areaWm2_RB2in_S09=0;
  areaWm2_RB2in_S10=0;
  areaWm2_RB2in_S11=0;
  areaWm2_RB2in_S12=0;

  areaWm1_RB2in_S01=0;
  areaWm1_RB2in_S02=0;
  areaWm1_RB2in_S03=0;
  areaWm1_RB2in_S04=0;
  areaWm1_RB2in_S05=0;
  areaWm1_RB2in_S06=0;
  areaWm1_RB2in_S07=0;
  areaWm1_RB2in_S08=0;
  areaWm1_RB2in_S09=0;
  areaWm1_RB2in_S10=0;
  areaWm1_RB2in_S11=0;
  areaWm1_RB2in_S12=0;

  areaW0_RB2in_S01=0;
  areaW0_RB2in_S02=0;
  areaW0_RB2in_S03=0;
  areaW0_RB2in_S04=0;
  areaW0_RB2in_S05=0;
  areaW0_RB2in_S06=0;
  areaW0_RB2in_S07=0;
  areaW0_RB2in_S08=0;
  areaW0_RB2in_S09=0;
  areaW0_RB2in_S10=0;
  areaW0_RB2in_S11=0;
  areaW0_RB2in_S12=0;

  areaWp1_RB2in_S01=0;
  areaWp1_RB2in_S02=0;
  areaWp1_RB2in_S03=0;
  areaWp1_RB2in_S04=0;
  areaWp1_RB2in_S05=0;
  areaWp1_RB2in_S06=0;
  areaWp1_RB2in_S07=0;
  areaWp1_RB2in_S08=0;
  areaWp1_RB2in_S09=0;
  areaWp1_RB2in_S10=0;
  areaWp1_RB2in_S11=0;
  areaWp1_RB2in_S12=0;

  areaWp2_RB2in_S01=0;
  areaWp2_RB2in_S02=0;
  areaWp2_RB2in_S03=0;
  areaWp2_RB2in_S04=0;
  areaWp2_RB2in_S05=0;
  areaWp2_RB2in_S06=0;
  areaWp2_RB2in_S07=0;
  areaWp2_RB2in_S08=0;
  areaWp2_RB2in_S09=0;
  areaWp2_RB2in_S10=0;
  areaWp2_RB2in_S11=0;
  areaWp2_RB2in_S12=0;

  areaWm2_RB2out_S01=0;
  areaWm2_RB2out_S02=0;
  areaWm2_RB2out_S03=0;
  areaWm2_RB2out_S04=0;
  areaWm2_RB2out_S05=0;
  areaWm2_RB2out_S06=0;
  areaWm2_RB2out_S07=0;
  areaWm2_RB2out_S08=0;
  areaWm2_RB2out_S09=0;
  areaWm2_RB2out_S10=0;
  areaWm2_RB2out_S11=0;
  areaWm2_RB2out_S12=0;

  areaWm1_RB2out_S01=0;
  areaWm1_RB2out_S02=0;
  areaWm1_RB2out_S03=0;
  areaWm1_RB2out_S04=0;
  areaWm1_RB2out_S05=0;
  areaWm1_RB2out_S06=0;
  areaWm1_RB2out_S07=0;
  areaWm1_RB2out_S08=0;
  areaWm1_RB2out_S09=0;
  areaWm1_RB2out_S10=0;
  areaWm1_RB2out_S11=0;
  areaWm1_RB2out_S12=0;

  areaW0_RB2out_S01=0;
  areaW0_RB2out_S02=0;
  areaW0_RB2out_S03=0;
  areaW0_RB2out_S04=0;
  areaW0_RB2out_S05=0;
  areaW0_RB2out_S06=0;
  areaW0_RB2out_S07=0;
  areaW0_RB2out_S08=0;
  areaW0_RB2out_S09=0;
  areaW0_RB2out_S10=0;
  areaW0_RB2out_S11=0;
  areaW0_RB2out_S12=0;

  areaWp1_RB2out_S01=0;
  areaWp1_RB2out_S02=0;
  areaWp1_RB2out_S03=0;
  areaWp1_RB2out_S04=0;
  areaWp1_RB2out_S05=0;
  areaWp1_RB2out_S06=0;
  areaWp1_RB2out_S07=0;
  areaWp1_RB2out_S08=0;
  areaWp1_RB2out_S09=0;
  areaWp1_RB2out_S10=0;
  areaWp1_RB2out_S11=0;
  areaWp1_RB2out_S12=0;

  areaWp2_RB2out_S01=0;
  areaWp2_RB2out_S02=0;
  areaWp2_RB2out_S03=0;
  areaWp2_RB2out_S04=0;
  areaWp2_RB2out_S05=0;
  areaWp2_RB2out_S06=0;
  areaWp2_RB2out_S07=0;
  areaWp2_RB2out_S08=0;
  areaWp2_RB2out_S09=0;
  areaWp2_RB2out_S10=0;
  areaWp2_RB2out_S11=0;
  areaWp2_RB2out_S12=0;


  areaWm2_RB3_S01=0;
  areaWm2_RB3_S02=0;
  areaWm2_RB3_S03=0;
  areaWm2_RB3_S04=0;
  areaWm2_RB3_S05=0;
  areaWm2_RB3_S06=0;
  areaWm2_RB3_S07=0;
  areaWm2_RB3_S08=0;
  areaWm2_RB3_S09=0;
  areaWm2_RB3_S10=0;
  areaWm2_RB3_S11=0;
  areaWm2_RB3_S12=0;
  areaWm1_RB3_S01=0;
  areaWm1_RB3_S02=0;
  areaWm1_RB3_S03=0;
  areaWm1_RB3_S04=0;
  areaWm1_RB3_S05=0;
  areaWm1_RB3_S06=0;
  areaWm1_RB3_S07=0;
  areaWm1_RB3_S08=0;
  areaWm1_RB3_S09=0;
  areaWm1_RB3_S10=0;
  areaWm1_RB3_S11=0;
  areaWm1_RB3_S12=0;

  areaW0_RB3_S01=0;
  areaW0_RB3_S02=0;
  areaW0_RB3_S03=0;
  areaW0_RB3_S04=0;
  areaW0_RB3_S05=0;
  areaW0_RB3_S06=0;
  areaW0_RB3_S07=0;
  areaW0_RB3_S08=0;
  areaW0_RB3_S09=0;
  areaW0_RB3_S10=0;
  areaW0_RB3_S11=0;
  areaW0_RB3_S12=0;
  areaWp1_RB3_S01=0;
  areaWp1_RB3_S02=0;
  areaWp1_RB3_S03=0;
  areaWp1_RB3_S04=0;
  areaWp1_RB3_S05=0;
  areaWp1_RB3_S06=0;
  areaWp1_RB3_S07=0;
  areaWp1_RB3_S08=0;
  areaWp1_RB3_S09=0;
  areaWp1_RB3_S10=0;
  areaWp1_RB3_S11=0;
  areaWp1_RB3_S12=0;
  areaWp2_RB3_S01=0;
  areaWp2_RB3_S02=0;
  areaWp2_RB3_S03=0;
  areaWp2_RB3_S04=0;
  areaWp2_RB3_S05=0;
  areaWp2_RB3_S06=0;
  areaWp2_RB3_S07=0;
  areaWp2_RB3_S08=0;
  areaWp2_RB3_S09=0;
  areaWp2_RB3_S10=0;
  areaWp2_RB3_S11=0;
  areaWp2_RB3_S12=0;
  areaWm2_RB4_S01=0;
  areaWm2_RB4_S02=0;
  areaWm2_RB4_S03=0;
  areaWm2_RB4_S04=0;
  areaWm2_RB4_S05=0;
  areaWm2_RB4_S06=0;
  areaWm2_RB4_S07=0;
  areaWm2_RB4_S08=0;
  areaWm2_RB4_S09=0;
  areaWm2_RB4_S10=0;
  areaWm2_RB4_S11=0;
  areaWm2_RB4_S12=0;
  areaWm1_RB4_S01=0;
  areaWm1_RB4_S02=0;
  areaWm1_RB4_S03=0;
  areaWm1_RB4_S04=0;
  areaWm1_RB4_S05=0;
  areaWm1_RB4_S06=0;
  areaWm1_RB4_S07=0;
  areaWm1_RB4_S08=0;
  areaWm1_RB4_S09=0;
  areaWm1_RB4_S10=0;
  areaWm1_RB4_S11=0;
  areaWm1_RB4_S12=0;
  areaW0_RB4_S01=0;
  areaW0_RB4_S02=0;
  areaW0_RB4_S03=0;
  areaW0_RB4_S04=0;
  areaW0_RB4_S05=0;
  areaW0_RB4_S06=0;
  areaW0_RB4_S07=0;
  areaW0_RB4_S08=0;
  areaW0_RB4_S09=0;
  areaW0_RB4_S10=0;
  areaW0_RB4_S11=0;
  areaW0_RB4_S12=0;
  areaWp1_RB4_S01=0;
  areaWp1_RB4_S02=0;
  areaWp1_RB4_S03=0;
  areaWp1_RB4_S04=0;
  areaWp1_RB4_S05=0;
  areaWp1_RB4_S06=0;
  areaWp1_RB4_S07=0;
  areaWp1_RB4_S08=0;
  areaWp1_RB4_S09=0;
  areaWp1_RB4_S10=0;
  areaWp1_RB4_S11=0;
  areaWp1_RB4_S12=0;
  areaWp2_RB4_S01=0;
  areaWp2_RB4_S02=0;
  areaWp2_RB4_S03=0;
  areaWp2_RB4_S04=0;
  areaWp2_RB4_S05=0;
  areaWp2_RB4_S06=0;
  areaWp2_RB4_S07=0;
  areaWp2_RB4_S08=0;
  areaWp2_RB4_S09=0;
  areaWp2_RB4_S10=0;
  areaWp2_RB4_S11=0;
  areaWp2_RB4_S12=0;



  areaREp42_S01=0;
  areaREp42_S02=0;
  areaREp42_S03=0;
  areaREp42_S04=0;
  areaREp42_S05=0;
  areaREp42_S06=0;
  areaREp42_S07=0;
  areaREp42_S08=0;
  areaREp42_S09=0;
  areaREp42_S10=0;
  areaREp42_S11=0;
  areaREp42_S12=0;
  areaREp43_S01=0;
  areaREp43_S02=0;
  areaREp43_S03=0;
  areaREp43_S04=0;
  areaREp43_S05=0;
  areaREp43_S06=0;
  areaREp43_S07=0;
  areaREp43_S08=0;
  areaREp43_S09=0;
  areaREp43_S10=0;
  areaREp43_S11=0;
  areaREp43_S12=0;
  areaREp12_S01=0;
  areaREp12_S02=0;
  areaREp12_S03=0;
  areaREp12_S04=0;
  areaREp12_S05=0;
  areaREp12_S06=0;
  areaREp12_S07=0;
  areaREp12_S08=0;
  areaREp12_S09=0;
  areaREp12_S10=0;
  areaREp12_S11=0;
  areaREp12_S12=0;
  areaREp13_S01=0;
  areaREp13_S02=0;
  areaREp13_S03=0;
  areaREp13_S04=0;
  areaREp13_S05=0;
  areaREp13_S06=0;
  areaREp13_S07=0;
  areaREp13_S08=0;
  areaREp13_S09=0;
  areaREp13_S10=0;
  areaREp13_S11=0;
  areaREp13_S12=0;

  areaREp22_S01=0;
  areaREp22_S02=0;
  areaREp22_S03=0;
  areaREp22_S04=0;
  areaREp22_S05=0;
  areaREp22_S06=0;
  areaREp22_S07=0;
  areaREp22_S08=0;
  areaREp22_S09=0;
  areaREp22_S10=0;
  areaREp22_S11=0;
  areaREp22_S12=0;
  areaREp23_S01=0;
  areaREp23_S02=0;
  areaREp23_S03=0;
  areaREp23_S04=0;
  areaREp23_S05=0;
  areaREp23_S06=0;
  areaREp23_S07=0;
  areaREp23_S08=0;
  areaREp23_S09=0;
  areaREp23_S10=0;
  areaREp23_S11=0;
  areaREp23_S12=0;

  areaREp32_S01=0;
  areaREp32_S02=0;
  areaREp32_S03=0;
  areaREp32_S04=0;
  areaREp32_S05=0;
  areaREp32_S06=0;
  areaREp32_S07=0;
  areaREp32_S08=0;
  areaREp32_S09=0;
  areaREp32_S10=0;
  areaREp32_S11=0;
  areaREp32_S12=0;
  areaREp33_S01=0;
  areaREp33_S02=0;
  areaREp33_S03=0;
  areaREp33_S04=0;
  areaREp33_S05=0;
  areaREp33_S06=0;
  areaREp33_S07=0;
  areaREp33_S08=0;
  areaREp33_S09=0;
  areaREp33_S10=0;
  areaREp33_S11=0;
  areaREp33_S12=0;


  areaWp2_RB1out_B=0;
areaWp1_RB1out_B=0;
areaW0_RB1out_B=0;
areaWm1_RB1out_B=0;
areaWm2_RB1out_B=0;
areaWp2_RB1out_F=0;
areaWp1_RB1out_F=0;
areaW0_RB1out_F=0;
areaWm1_RB1out_F=0;
areaWm2_RB1out_F=0;
areaWp2_RB1in_B=0;
areaWp1_RB1in_B=0;
areaW0_RB1in_B=0;
areaWm1_RB1in_B=0;
areaWm2_RB1in_B=0;
areaWp2_RB1in_F=0;
areaWp1_RB1in_F=0;
areaW0_RB1in_F=0;
areaWm1_RB1in_F=0;
areaWm2_RB1in_F=0;
areaWp2_RB3_B=0;
areaWp1_RB3_B=0;
areaW0_RB3_B=0;
areaWm1_RB3_B=0;
areaWm2_RB3_B=0;
areaWp2_RB3_F=0;
areaWp1_RB3_F=0;
areaW0_RB3_F=0;
areaWm1_RB3_F=0;
areaWm2_RB3_F=0;
areaWp2_RB4_B=0;
areaWp1_RB4_B=0;
areaW0_RB4_B=0;
areaWm1_RB4_B=0;
areaWm2_RB4_B=0;
areaWp2_RB4_F=0;
areaWp1_RB4_F=0;
areaW0_RB4_F=0;
areaWm1_RB4_F=0;
areaWm2_RB4_F=0;
areaWp2_RB2out_B=0;
areaWp1_RB2out_B=0;
areaW0_RB2out_B=0;
areaWm1_RB2out_B=0;
areaWm2_RB2out_B=0;
areaWp2_RB2out_F=0;
areaWp1_RB2out_F=0;
areaW0_RB2out_F=0;
areaWm1_RB2out_F=0;
areaWm2_RB2out_F=0;
areaWp2_RB2out_M=0;
areaWm2_RB2out_M=0;
areaWp2_RB2in_B=0;
areaWp1_RB2in_B=0;
areaW0_RB2in_B=0;
areaWm1_RB2in_B=0;
areaWm2_RB2in_B=0;
areaWp2_RB2in_F=0;
areaWp1_RB2in_F=0;
areaW0_RB2in_F=0;
areaWm1_RB2in_F=0;
areaWm2_RB2in_F=0;
areaWp1_RB2in_M=0;
areaW0_RB2in_M=0;
areaWm1_RB2in_M=0;
areaREp12_B=0;
areaREp12_M=0;
areaREp12_F=0;
areaREp13_B=0;
areaREp13_M=0;
areaREp13_F=0;
areaREp42_B=0;
areaREp42_M=0;
areaREp42_F=0;
areaREp43_B=0;
areaREp43_M=0;
areaREp43_F=0;

areaREp22_B=0;
areaREp22_M=0;
areaREp22_F=0;
areaREp23_B=0;
areaREp23_M=0;
areaREp23_F=0;
areaREp32_B=0;
areaREp32_M=0;
areaREp32_F=0;
areaREp33_B=0;
areaREp33_M=0;
areaREp33_F=0;



areaREm42_S01=0;
areaREm42_S02=0;
areaREm42_S03=0;
areaREm42_S04=0;
areaREm42_S05=0;
areaREm42_S06=0;
areaREm42_S07=0;
areaREm42_S08=0;
areaREm42_S09=0;
areaREm42_S10=0;
areaREm42_S11=0;
areaREm42_S12=0;
areaREm43_S01=0;
areaREm43_S02=0;
areaREm43_S03=0;
areaREm43_S04=0;
areaREm43_S05=0;
areaREm43_S06=0;
areaREm43_S07=0;
areaREm43_S08=0;
areaREm43_S09=0;
areaREm43_S10=0;
areaREm43_S11=0;
areaREm43_S12=0;
areaREm12_S01=0;
areaREm12_S02=0;
areaREm12_S03=0;
areaREm12_S04=0;
areaREm12_S05=0;
areaREm12_S06=0;
areaREm12_S07=0;
areaREm12_S08=0;
areaREm12_S09=0;
areaREm12_S10=0;
areaREm12_S11=0;
areaREm12_S12=0;
areaREm13_S01=0;
areaREm13_S02=0;
areaREm13_S03=0;
areaREm13_S04=0;
areaREm13_S05=0;
areaREm13_S06=0;
areaREm13_S07=0;
areaREm13_S08=0;
areaREm13_S09=0;
areaREm13_S10=0;
areaREm13_S11=0;
areaREm13_S12=0;


  areaREm22_S01=0;
  areaREm22_S02=0;
  areaREm22_S03=0;
  areaREm22_S04=0;
  areaREm22_S05=0;
  areaREm22_S06=0;
  areaREm22_S07=0;
  areaREm22_S08=0;
  areaREm22_S09=0;
  areaREm22_S10=0;
  areaREm22_S11=0;
  areaREm22_S12=0;
  areaREm23_S01=0;
  areaREm23_S02=0;
  areaREm23_S03=0;
  areaREm23_S04=0;
  areaREm23_S05=0;
  areaREm23_S06=0;
  areaREm23_S07=0;
  areaREm23_S08=0;
  areaREm23_S09=0;
  areaREm23_S10=0;
  areaREm23_S11=0;
  areaREm23_S12=0;

  areaREm32_S01=0;
  areaREm32_S02=0;
  areaREm32_S03=0;
  areaREm32_S04=0;
  areaREm32_S05=0;
  areaREm32_S06=0;
  areaREm32_S07=0;
  areaREm32_S08=0;
  areaREm32_S09=0;
  areaREm32_S10=0;
  areaREm32_S11=0;
  areaREm32_S12=0;
  areaREm33_S01=0;
  areaREm33_S02=0;
  areaREm33_S03=0;
  areaREm33_S04=0;
  areaREm33_S05=0;
  areaREm33_S06=0;
  areaREm33_S07=0;
  areaREm33_S08=0;
  areaREm33_S09=0;
  areaREm33_S10=0;
  areaREm33_S11=0;
  areaREm33_S12=0;





areaREm12_B=0;
areaREm12_M=0;
areaREm12_F=0;
areaREm13_B=0;
areaREm13_M=0;
areaREm13_F=0;
areaREm42_B=0;
areaREm42_M=0;
areaREm42_F=0;
areaREm43_B=0;
areaREm43_M=0;
areaREm43_F=0;

areaREm22_B=0;
areaREm22_M=0;
areaREm22_F=0;
areaREm23_B=0;
areaREm23_M=0;
areaREm23_F=0;
areaREm32_B=0;
areaREm32_M=0;
areaREm32_F=0;
areaREm33_B=0;
areaREm33_M=0;
areaREm33_F=0;

  area_barrel=0.;
  
  numhit=0;
  
  
//get the luminosity block
  lumiperblock = 0.;
  lumiblock = 0;
  bunchNum = 0;
  bunchCross = 0;
  event =0;
  bool low[5]={false};

//  edm::Handle<LumiScalersCollection> lumiScalers = iEvent.getHandle(scalersSourceToken_);
  edm::Handle<OnlineLuminosityRecord> lumiScalers = iEvent.getHandle(scalersSourceToken_);

//FIXME  edm::Handle<LumiScalersCollection> lumiScalers;
//  iEvent.getByToken(scalersSourceToken_, lumiScalers);

   if (lumiScalers.isValid()) { //&& !lumiScalers->empty()) {
//     if (lumiScalers->begin() != lumiScalers->end()) {

//       LumiScalersCollection::const_iterator lumiIt = lumiScalers->begin();

//       lumiperblock = lumiIt->instantLumi(); //10^30
       lumiperblock = lumiScalers->instLumi(); //10^30

       lumiblock = iEvent.getLuminosityBlock().luminosityBlock();
       lumiperblock = lumiperblock*1./1000.; //10^33
       lumi = lumiperblock;

//       bunchNum = lumiScalers->bunchNumber();
//       bunchNum = lumiIt->bunchNumber();

       bunchCross = iEvent.eventAuxiliary().bunchCrossing();
       orbitnumber = iEvent.eventAuxiliary().orbitNumber();
       

//FIXME mileva
       bunchNum = bunchCross;
//     }
//     else
//     {std::cout << "begin == end" << std::endl;
////       return;
//     }
  }
  else
  {std::cout << "not valid or empty" << std::endl;
//    return;
  }
  runNum = iEvent.eventAuxiliary().id().run();
  event = iEvent.eventAuxiliary().id().event();
// Get the RPC Geometry
// Get the RPC Geometry
//FIXME mileva
  auto rpcGeom = iSetup.getHandle(rpcGeoToken_);
//  edm::ESHandle<RPCGeometry> rpcGeom = iSetup.getHandle(rpcGeoToken_);
//  edm::ESHandle < RPCGeometry > rpcGeom;
//  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
  Handle<RPCRecHitCollection> rpcHits_handle;
  iEvent.getByToken(rpcRecHitsLabel,rpcHits_handle);

  const std::vector<  const RPCRoll * > rls = rpcGeom->rolls();
;

  if(debug) std::cout <<"\t Getting the RPC RecHits"<<std::endl;




  for(int bx=-2;bx<3;bx++){
      if (std::find(uncolliding.begin(), uncolliding.end(), bunchNum+bx) != uncolliding.end()) low[bx+2]=true;
      }

  for(int bx=-2;bx<3;bx++){
      if (low[bx+2]==true){
         if(bunchNum+bx<114)lumi_prebeam->Fill(lumiperblock);
         else if (bunchNum+bx>=3354) lumi_abort->Fill(lumiperblock);
         else lumi_low->Fill(lumiperblock);
      }
      else lumi_high->Fill(lumiperblock);
      }
  //if(low==false) lumi->Fill(lumiperblock);
  

  for (int i = 0; i < (int) rls.size() ; ++i)
  {
    RPCDetId rpcId =  rls[i]->id();
    if (std::find(idBlackList.begin(), idBlackList.end(), rpcId) != idBlackList.end())
      continue;
    const RPCRoll* roll = dynamic_cast<const RPCRoll*>(rpcGeom->roll(rpcId));

    if(debug) std::cout<<"roll"<<roll<<std::endl;
    //take the global coordiantes of the center of the rpc roll (eta partition)
    const int nstrips = roll->nstrips();
    float middleStrip = nstrips/2.;
    const LocalPoint& middleOfRoll = roll->centreOfStrip(middleStrip);
    const GlobalPoint& globMiddleRol = roll->toGlobal(middleOfRoll);
    
    if(debug) std::cout << "eta " << globMiddleRol.eta() << "\tphi " << globMiddleRol.phi() << std::endl;

    area = 0.0;
    float myPitch = 0.0;
    float xmin = 0.0;
    float xmax =0.0;
    float striplength;

    if ( rpcId.region() == 0 )
      {
        const RectangularStripTopology* top_ = dynamic_cast<const RectangularStripTopology*>(&(roll->topology()));
        xmin = (top_->localPosition(0.)).x();
        xmax = (top_->localPosition((float)roll->nstrips())).x();
        striplength = (top_->stripLength());
        myPitch = top_->pitch();
      }
    else
      {
        const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(roll->topology()));
        xmin = (top_->localPosition(0.)).x();
        xmax = (top_->localPosition((float)roll->nstrips())).x();
        striplength = (top_->stripLength());
        myPitch = top_->pitch();
      }
     area = striplength*(xmax-xmin);
     stripArea = striplength*myPitch;
     
//fill areas
     
    if (rpcId.region() == 0)
    {
      area_barrel+=area;


      if(rpcId.station() == 1 && rpcId.ring() == -2){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWm2_RB1in_F +=area;
        if (rpcId.roll() == 1) areaWm2_RB1in_B +=area;
        
        if(rpcId.sector() == 1) areaWm2_RB1in_S01+=area;
        if(rpcId.sector() == 2) areaWm2_RB1in_S02+=area;
        if(rpcId.sector() == 3) areaWm2_RB1in_S03+=area;
        if(rpcId.sector() == 4) areaWm2_RB1in_S04+=area;
        if(rpcId.sector() == 5) areaWm2_RB1in_S05+=area;
        if(rpcId.sector() == 6) areaWm2_RB1in_S06+=area;
        if(rpcId.sector() == 7) areaWm2_RB1in_S07+=area;
        if(rpcId.sector() == 8) areaWm2_RB1in_S08+=area;
        if(rpcId.sector() == 9) areaWm2_RB1in_S09+=area;
        if(rpcId.sector() == 10) areaWm2_RB1in_S10+=area;
        if(rpcId.sector() == 11) areaWm2_RB1in_S11+=area;
        if(rpcId.sector() == 12) areaWm2_RB1in_S12+=area;
      }

      } 


      if(rpcId.station() == 1 && rpcId.ring() == -1){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWm1_RB1in_F +=area;
        if (rpcId.roll() == 1) areaWm1_RB1in_B +=area;

 
        
        if(rpcId.sector() == 1) areaWm1_RB1in_S01+=area;
        if(rpcId.sector() == 2) areaWm1_RB1in_S02+=area;
        if(rpcId.sector() == 3) areaWm1_RB1in_S03+=area;
        if(rpcId.sector() == 4) areaWm1_RB1in_S04+=area;
        if(rpcId.sector() == 5) areaWm1_RB1in_S05+=area;
        if(rpcId.sector() == 6) areaWm1_RB1in_S06+=area;
        if(rpcId.sector() == 7) areaWm1_RB1in_S07+=area;
        if(rpcId.sector() == 8) areaWm1_RB1in_S08+=area;
        if(rpcId.sector() == 9) areaWm1_RB1in_S09+=area;
        if(rpcId.sector() == 10) areaWm1_RB1in_S10+=area;
        if(rpcId.sector() == 11) areaWm1_RB1in_S11+=area;
        if(rpcId.sector() == 12) areaWm1_RB1in_S12+=area;
      }

      } 



      if(rpcId.station() == 1 && rpcId.ring() == 0){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaW0_RB1in_F +=area;
        if (rpcId.roll() == 1) areaW0_RB1in_B +=area; 
        
        if(rpcId.sector() == 1) areaW0_RB1in_S01+=area;
        if(rpcId.sector() == 2) areaW0_RB1in_S02+=area;
        if(rpcId.sector() == 3) areaW0_RB1in_S03+=area;
        if(rpcId.sector() == 4) areaW0_RB1in_S04+=area;
        if(rpcId.sector() == 5) areaW0_RB1in_S05+=area;
        if(rpcId.sector() == 6) areaW0_RB1in_S06+=area;
        if(rpcId.sector() == 7) areaW0_RB1in_S07+=area;
        if(rpcId.sector() == 8) areaW0_RB1in_S08+=area;
        if(rpcId.sector() == 9) areaW0_RB1in_S09+=area;
        if(rpcId.sector() == 10) areaW0_RB1in_S10+=area;
        if(rpcId.sector() == 11) areaW0_RB1in_S11+=area;
        if(rpcId.sector() == 12) areaW0_RB1in_S12+=area;
      }

      } 


      if(rpcId.station() == 1 && rpcId.ring() == 1){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWp1_RB1in_F +=area;
        if (rpcId.roll() == 1) areaWp1_RB1in_B +=area;            
 
        
        if(rpcId.sector() == 1) areaWp1_RB1in_S01+=area;
        if(rpcId.sector() == 2) areaWp1_RB1in_S02+=area;
        if(rpcId.sector() == 3) areaWp1_RB1in_S03+=area;
        if(rpcId.sector() == 4) areaWp1_RB1in_S04+=area;
        if(rpcId.sector() == 5) areaWp1_RB1in_S05+=area;
        if(rpcId.sector() == 6) areaWp1_RB1in_S06+=area;
        if(rpcId.sector() == 7) areaWp1_RB1in_S07+=area;
        if(rpcId.sector() == 8) areaWp1_RB1in_S08+=area;
        if(rpcId.sector() == 9) areaWp1_RB1in_S09+=area;
        if(rpcId.sector() == 10) areaWp1_RB1in_S10+=area;
        if(rpcId.sector() == 11) areaWp1_RB1in_S11+=area;
        if(rpcId.sector() == 12) areaWp1_RB1in_S12+=area;
      }

      } 


      if(rpcId.station() == 1 && rpcId.ring() == 2){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWp2_RB1in_F +=area;
        if (rpcId.roll() == 1) areaWp2_RB1in_B +=area; 
        
        if(rpcId.sector() == 1) areaWp2_RB1in_S01+=area;
        if(rpcId.sector() == 2) areaWp2_RB1in_S02+=area;
        if(rpcId.sector() == 3) areaWp2_RB1in_S03+=area;
        if(rpcId.sector() == 4) areaWp2_RB1in_S04+=area;
        if(rpcId.sector() == 5) areaWp2_RB1in_S05+=area;
        if(rpcId.sector() == 6) areaWp2_RB1in_S06+=area;
        if(rpcId.sector() == 7) areaWp2_RB1in_S07+=area;
        if(rpcId.sector() == 8) areaWp2_RB1in_S08+=area;
        if(rpcId.sector() == 9) areaWp2_RB1in_S09+=area;
        if(rpcId.sector() == 10) areaWp2_RB1in_S10+=area;
        if(rpcId.sector() == 11) areaWp2_RB1in_S11+=area;
        if(rpcId.sector() == 12) areaWp2_RB1in_S12+=area;
      }

      } // end RB1in

      
      if(rpcId.station() == 1 && rpcId.ring() == -2){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWm2_RB1out_F +=area;
        if (rpcId.roll() == 1) areaWm2_RB1out_B +=area; 
        
        if(rpcId.sector() == 1) areaWm2_RB1out_S01+=area;
        if(rpcId.sector() == 2) areaWm2_RB1out_S02+=area;
        if(rpcId.sector() == 3) areaWm2_RB1out_S03+=area;
        if(rpcId.sector() == 4) areaWm2_RB1out_S04+=area;
        if(rpcId.sector() == 5) areaWm2_RB1out_S05+=area;
        if(rpcId.sector() == 6) areaWm2_RB1out_S06+=area;
        if(rpcId.sector() == 7) areaWm2_RB1out_S07+=area;
        if(rpcId.sector() == 8) areaWm2_RB1out_S08+=area;
        if(rpcId.sector() == 9) areaWm2_RB1out_S09+=area;
        if(rpcId.sector() == 10) areaWm2_RB1out_S10+=area;
        if(rpcId.sector() == 11) areaWm2_RB1out_S11+=area;
        if(rpcId.sector() == 12) areaWm2_RB1out_S12+=area;
      }

      } 


      if(rpcId.station() == 1 && rpcId.ring() == -1){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWm1_RB1out_F +=area;
        if (rpcId.roll() == 1) areaWm1_RB1out_B +=area;  
        
        if(rpcId.sector() == 1) areaWm1_RB1out_S01+=area;
        if(rpcId.sector() == 2) areaWm1_RB1out_S02+=area;
        if(rpcId.sector() == 3) areaWm1_RB1out_S03+=area;
        if(rpcId.sector() == 4) areaWm1_RB1out_S04+=area;
        if(rpcId.sector() == 5) areaWm1_RB1out_S05+=area;
        if(rpcId.sector() == 6) areaWm1_RB1out_S06+=area;
        if(rpcId.sector() == 7) areaWm1_RB1out_S07+=area;
        if(rpcId.sector() == 8) areaWm1_RB1out_S08+=area;
        if(rpcId.sector() == 9) areaWm1_RB1out_S09+=area;
        if(rpcId.sector() == 10) areaWm1_RB1out_S10+=area;
        if(rpcId.sector() == 11) areaWm1_RB1out_S11+=area;
        if(rpcId.sector() == 12) areaWm1_RB1out_S12+=area;
      }

      } 



      if(rpcId.station() == 1 && rpcId.ring() == 0){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaW0_RB1out_F +=area;
        if (rpcId.roll() == 1) areaW0_RB1out_B +=area;  
        
        if(rpcId.sector() == 1) areaW0_RB1out_S01+=area;
        if(rpcId.sector() == 2) areaW0_RB1out_S02+=area;
        if(rpcId.sector() == 3) areaW0_RB1out_S03+=area;
        if(rpcId.sector() == 4) areaW0_RB1out_S04+=area;
        if(rpcId.sector() == 5) areaW0_RB1out_S05+=area;
        if(rpcId.sector() == 6) areaW0_RB1out_S06+=area;
        if(rpcId.sector() == 7) areaW0_RB1out_S07+=area;
        if(rpcId.sector() == 8) areaW0_RB1out_S08+=area;
        if(rpcId.sector() == 9) areaW0_RB1out_S09+=area;
        if(rpcId.sector() == 10) areaW0_RB1out_S10+=area;
        if(rpcId.sector() == 11) areaW0_RB1out_S11+=area;
        if(rpcId.sector() == 12) areaW0_RB1out_S12+=area;
      }

      } 


      if(rpcId.station() == 1 && rpcId.ring() == 1){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWp1_RB1out_F +=area;
        if (rpcId.roll() == 1) areaWp1_RB1out_B +=area;  
        
        if(rpcId.sector() == 1) areaWp1_RB1out_S01+=area;
        if(rpcId.sector() == 2) areaWp1_RB1out_S02+=area;
        if(rpcId.sector() == 3) areaWp1_RB1out_S03+=area;
        if(rpcId.sector() == 4) areaWp1_RB1out_S04+=area;
        if(rpcId.sector() == 5) areaWp1_RB1out_S05+=area;
        if(rpcId.sector() == 6) areaWp1_RB1out_S06+=area;
        if(rpcId.sector() == 7) areaWp1_RB1out_S07+=area;
        if(rpcId.sector() == 8) areaWp1_RB1out_S08+=area;
        if(rpcId.sector() == 9) areaWp1_RB1out_S09+=area;
        if(rpcId.sector() == 10) areaWp1_RB1out_S10+=area;
        if(rpcId.sector() == 11) areaWp1_RB1out_S11+=area;
        if(rpcId.sector() == 12) areaWp1_RB1out_S12+=area;
      }

      } 


      if(rpcId.station() == 1 && rpcId.ring() == 2){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWp2_RB1out_F +=area;
        if (rpcId.roll() == 1) areaWp2_RB1out_B +=area;  
        
        if(rpcId.sector() == 1) areaWp2_RB1out_S01+=area;
        if(rpcId.sector() == 2) areaWp2_RB1out_S02+=area;
        if(rpcId.sector() == 3) areaWp2_RB1out_S03+=area;
        if(rpcId.sector() == 4) areaWp2_RB1out_S04+=area;
        if(rpcId.sector() == 5) areaWp2_RB1out_S05+=area;
        if(rpcId.sector() == 6) areaWp2_RB1out_S06+=area;
        if(rpcId.sector() == 7) areaWp2_RB1out_S07+=area;
        if(rpcId.sector() == 8) areaWp2_RB1out_S08+=area;
        if(rpcId.sector() == 9) areaWp2_RB1out_S09+=area;
        if(rpcId.sector() == 10) areaWp2_RB1out_S10+=area;
        if(rpcId.sector() == 11) areaWp2_RB1out_S11+=area;
        if(rpcId.sector() == 12) areaWp2_RB1out_S12+=area;
      }

      }// end RB1out 

  if(rpcId.station() == 2 && rpcId.ring() == -2){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWm2_RB2in_F +=area;
        if (rpcId.roll() == 1) areaWm2_RB2in_B +=area;            
 
        
        if(rpcId.sector() == 1) areaWm2_RB2in_S01+=area;
        if(rpcId.sector() == 2) areaWm2_RB2in_S02+=area;
        if(rpcId.sector() == 3) areaWm2_RB2in_S03+=area;
        if(rpcId.sector() == 4) areaWm2_RB2in_S04+=area;
        if(rpcId.sector() == 5) areaWm2_RB2in_S05+=area;
        if(rpcId.sector() == 6) areaWm2_RB2in_S06+=area;
        if(rpcId.sector() == 7) areaWm2_RB2in_S07+=area;
        if(rpcId.sector() == 8) areaWm2_RB2in_S08+=area;
        if(rpcId.sector() == 9) areaWm2_RB2in_S09+=area;
        if(rpcId.sector() == 10) areaWm2_RB2in_S10+=area;
        if(rpcId.sector() == 11) areaWm2_RB2in_S11+=area;
        if(rpcId.sector() == 12) areaWm2_RB2in_S12+=area;
      }

      } 


      if(rpcId.station() == 2 && rpcId.ring() == -1){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWm1_RB2in_F +=area;
        if (rpcId.roll() == 2) areaWm1_RB2in_M +=area;
        if (rpcId.roll() == 1) areaWm1_RB2in_B +=area;  
        
        if(rpcId.sector() == 1) areaWm1_RB2in_S01+=area;
        if(rpcId.sector() == 2) areaWm1_RB2in_S02+=area;
        if(rpcId.sector() == 3) areaWm1_RB2in_S03+=area;
        if(rpcId.sector() == 4) areaWm1_RB2in_S04+=area;
        if(rpcId.sector() == 5) areaWm1_RB2in_S05+=area;
        if(rpcId.sector() == 6) areaWm1_RB2in_S06+=area;
        if(rpcId.sector() == 7) areaWm1_RB2in_S07+=area;
        if(rpcId.sector() == 8) areaWm1_RB2in_S08+=area;
        if(rpcId.sector() == 9) areaWm1_RB2in_S09+=area;
        if(rpcId.sector() == 10) areaWm1_RB2in_S10+=area;
        if(rpcId.sector() == 11) areaWm1_RB2in_S11+=area;
        if(rpcId.sector() == 12) areaWm1_RB2in_S12+=area;
      }

      } 



      if(rpcId.station() == 2 && rpcId.ring() == 0){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaW0_RB2in_F +=area;
        if (rpcId.roll() == 2) areaW0_RB2in_M +=area;
        if (rpcId.roll() == 1) areaW0_RB2in_B +=area;  
        
        if(rpcId.sector() == 1) areaW0_RB2in_S01+=area;
        if(rpcId.sector() == 2) areaW0_RB2in_S02+=area;
        if(rpcId.sector() == 3) areaW0_RB2in_S03+=area;
        if(rpcId.sector() == 4) areaW0_RB2in_S04+=area;
        if(rpcId.sector() == 5) areaW0_RB2in_S05+=area;
        if(rpcId.sector() == 6) areaW0_RB2in_S06+=area;
        if(rpcId.sector() == 7) areaW0_RB2in_S07+=area;
        if(rpcId.sector() == 8) areaW0_RB2in_S08+=area;
        if(rpcId.sector() == 9) areaW0_RB2in_S09+=area;
        if(rpcId.sector() == 10) areaW0_RB2in_S10+=area;
        if(rpcId.sector() == 11) areaW0_RB2in_S11+=area;
        if(rpcId.sector() == 12) areaW0_RB2in_S12+=area;
      }

      } 


      if(rpcId.station() == 2 && rpcId.ring() == 1){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWp1_RB2in_F +=area;
        if (rpcId.roll() == 2) areaWp1_RB2in_M +=area;
        if (rpcId.roll() == 1) areaWp1_RB2in_B +=area;  
        
        if(rpcId.sector() == 1) areaWp1_RB2in_S01+=area;
        if(rpcId.sector() == 2) areaWp1_RB2in_S02+=area;
        if(rpcId.sector() == 3) areaWp1_RB2in_S03+=area;
        if(rpcId.sector() == 4) areaWp1_RB2in_S04+=area;
        if(rpcId.sector() == 5) areaWp1_RB2in_S05+=area;
        if(rpcId.sector() == 6) areaWp1_RB2in_S06+=area;
        if(rpcId.sector() == 7) areaWp1_RB2in_S07+=area;
        if(rpcId.sector() == 8) areaWp1_RB2in_S08+=area;
        if(rpcId.sector() == 9) areaWp1_RB2in_S09+=area;
        if(rpcId.sector() == 10) areaWp1_RB2in_S10+=area;
        if(rpcId.sector() == 11) areaWp1_RB2in_S11+=area;
        if(rpcId.sector() == 12) areaWp1_RB2in_S12+=area;
	
	}

      } 


      if(rpcId.station() == 2 && rpcId.ring() == 2){
        if(rpcId.layer() == 1){
        if (rpcId.roll() == 3) areaWp2_RB2in_F +=area;
        if (rpcId.roll() == 1) areaWp2_RB2in_B +=area;  
        
        if(rpcId.sector() == 1) areaWp2_RB2in_S01+=area;
        if(rpcId.sector() == 2) areaWp2_RB2in_S02+=area;
        if(rpcId.sector() == 3) areaWp2_RB2in_S03+=area;
        if(rpcId.sector() == 4) areaWp2_RB2in_S04+=area;
        if(rpcId.sector() == 5) areaWp2_RB2in_S05+=area;
        if(rpcId.sector() == 6) areaWp2_RB2in_S06+=area;
        if(rpcId.sector() == 7) areaWp2_RB2in_S07+=area;
        if(rpcId.sector() == 8) areaWp2_RB2in_S08+=area;
        if(rpcId.sector() == 9) areaWp2_RB2in_S09+=area;
        if(rpcId.sector() == 10) areaWp2_RB2in_S10+=area;
        if(rpcId.sector() == 11) areaWp2_RB2in_S11+=area;
        if(rpcId.sector() == 12) areaWp2_RB2in_S12+=area;
      }

      } // end RB2in

      
      if(rpcId.station() == 2 && rpcId.ring() == -2){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWm2_RB2out_F +=area;
        if (rpcId.roll() == 2) areaWm2_RB2out_M +=area;
        if (rpcId.roll() == 1) areaWm2_RB2out_B +=area;  
        
        if(rpcId.sector() == 1) areaWm2_RB2out_S01+=area;
        if(rpcId.sector() == 2) areaWm2_RB2out_S02+=area;
        if(rpcId.sector() == 3) areaWm2_RB2out_S03+=area;
        if(rpcId.sector() == 4) areaWm2_RB2out_S04+=area;
        if(rpcId.sector() == 5) areaWm2_RB2out_S05+=area;
        if(rpcId.sector() == 6) areaWm2_RB2out_S06+=area;
        if(rpcId.sector() == 7) areaWm2_RB2out_S07+=area;
        if(rpcId.sector() == 8) areaWm2_RB2out_S08+=area;
        if(rpcId.sector() == 9) areaWm2_RB2out_S09+=area;
        if(rpcId.sector() == 10) areaWm2_RB2out_S10+=area;
        if(rpcId.sector() == 11) areaWm2_RB2out_S11+=area;
        if(rpcId.sector() == 12) areaWm2_RB2out_S12+=area;
      }

      } 


      if(rpcId.station() == 2 && rpcId.ring() == -1){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWm1_RB2out_F +=area;
        if (rpcId.roll() == 1) areaWm1_RB2out_B +=area; 
        
        if(rpcId.sector() == 1) areaWm1_RB2out_S01+=area;
        if(rpcId.sector() == 2) areaWm1_RB2out_S02+=area;
        if(rpcId.sector() == 3) areaWm1_RB2out_S03+=area;
        if(rpcId.sector() == 4) areaWm1_RB2out_S04+=area;
        if(rpcId.sector() == 5) areaWm1_RB2out_S05+=area;
        if(rpcId.sector() == 6) areaWm1_RB2out_S06+=area;
        if(rpcId.sector() == 7) areaWm1_RB2out_S07+=area;
        if(rpcId.sector() == 8) areaWm1_RB2out_S08+=area;
        if(rpcId.sector() == 9) areaWm1_RB2out_S09+=area;
        if(rpcId.sector() == 10) areaWm1_RB2out_S10+=area;
        if(rpcId.sector() == 11) areaWm1_RB2out_S11+=area;
        if(rpcId.sector() == 12) areaWm1_RB2out_S12+=area;
      }

      } 



      if(rpcId.station() == 2 && rpcId.ring() == 0){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaW0_RB2out_F +=area;
        if (rpcId.roll() == 1) areaW0_RB2out_B +=area; 
        
        if(rpcId.sector() == 1) areaW0_RB2out_S01+=area;
        if(rpcId.sector() == 2) areaW0_RB2out_S02+=area;
        if(rpcId.sector() == 3) areaW0_RB2out_S03+=area;
        if(rpcId.sector() == 4) areaW0_RB2out_S04+=area;
        if(rpcId.sector() == 5) areaW0_RB2out_S05+=area;
        if(rpcId.sector() == 6) areaW0_RB2out_S06+=area;
        if(rpcId.sector() == 7) areaW0_RB2out_S07+=area;
        if(rpcId.sector() == 8) areaW0_RB2out_S08+=area;
        if(rpcId.sector() == 9) areaW0_RB2out_S09+=area;
        if(rpcId.sector() == 10) areaW0_RB2out_S10+=area;
        if(rpcId.sector() == 11) areaW0_RB2out_S11+=area;
        if(rpcId.sector() == 12) areaW0_RB2out_S12+=area;
      }

      } 


      if(rpcId.station() == 2 && rpcId.ring() == 1){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWp1_RB2out_F +=area;
        if (rpcId.roll() == 1) areaWp1_RB2out_B +=area; 
        
        if(rpcId.sector() == 1) areaWp1_RB2out_S01+=area;
        if(rpcId.sector() == 2) areaWp1_RB2out_S02+=area;
        if(rpcId.sector() == 3) areaWp1_RB2out_S03+=area;
        if(rpcId.sector() == 4) areaWp1_RB2out_S04+=area;
        if(rpcId.sector() == 5) areaWp1_RB2out_S05+=area;
        if(rpcId.sector() == 6) areaWp1_RB2out_S06+=area;
        if(rpcId.sector() == 7) areaWp1_RB2out_S07+=area;
        if(rpcId.sector() == 8) areaWp1_RB2out_S08+=area;
        if(rpcId.sector() == 9) areaWp1_RB2out_S09+=area;
        if(rpcId.sector() == 10) areaWp1_RB2out_S10+=area;
        if(rpcId.sector() == 11) areaWp1_RB2out_S11+=area;
        if(rpcId.sector() == 12) areaWp1_RB2out_S12+=area;
      }

      } 


      if(rpcId.station() == 2 && rpcId.ring() == 2){
        if(rpcId.layer() == 2){
        if (rpcId.roll() == 3) areaWp2_RB2out_F +=area;
        if (rpcId.roll() == 2) areaWp2_RB2out_M +=area;
        if (rpcId.roll() == 1) areaWp2_RB2out_B +=area; 
        
        if(rpcId.sector() == 1) areaWp2_RB2out_S01+=area;
        if(rpcId.sector() == 2) areaWp2_RB2out_S02+=area;
        if(rpcId.sector() == 3) areaWp2_RB2out_S03+=area;
        if(rpcId.sector() == 4) areaWp2_RB2out_S04+=area;
        if(rpcId.sector() == 5) areaWp2_RB2out_S05+=area;
        if(rpcId.sector() == 6) areaWp2_RB2out_S06+=area;
        if(rpcId.sector() == 7) areaWp2_RB2out_S07+=area;
        if(rpcId.sector() == 8) areaWp2_RB2out_S08+=area;
        if(rpcId.sector() == 9) areaWp2_RB2out_S09+=area;
        if(rpcId.sector() == 10) areaWp2_RB2out_S10+=area;
        if(rpcId.sector() == 11) areaWp2_RB2out_S11+=area;
        if(rpcId.sector() == 12) areaWp2_RB2out_S12+=area;
      }

      }// end RB2out 


       if(rpcId.station() == 3 && rpcId.ring() == -2){
            if (rpcId.roll() == 3) areaWm2_RB3_F +=area;
            if (rpcId.roll() == 1) areaWm2_RB3_B +=area; 
           
            if(rpcId.sector() == 1)areaWm2_RB3_S01+=area;
            if(rpcId.sector() == 2)areaWm2_RB3_S02+=area;
            if(rpcId.sector() == 3)areaWm2_RB3_S03+=area;
            if(rpcId.sector() == 4)areaWm2_RB3_S04+=area;
            if(rpcId.sector() == 5)areaWm2_RB3_S05+=area;
            if(rpcId.sector() == 6)areaWm2_RB3_S06+=area;
            if(rpcId.sector() == 7)areaWm2_RB3_S07+=area;
            if(rpcId.sector() == 8)areaWm2_RB3_S08+=area;
            if(rpcId.sector() == 9)areaWm2_RB3_S09+=area;
            if(rpcId.sector() == 10)areaWm2_RB3_S10+=area;
            if(rpcId.sector() == 11)areaWm2_RB3_S11+=area;
            if(rpcId.sector() == 12)areaWm2_RB3_S12+=area;

          

        }

        if(rpcId.station() == 3 && rpcId.ring() == -1){
            if (rpcId.roll() == 3) areaWm1_RB3_F +=area;
            if (rpcId.roll() == 1) areaWm1_RB3_B +=area; 

            if(rpcId.sector() == 1)areaWm1_RB3_S01+=area;
            if(rpcId.sector() == 2)areaWm1_RB3_S02+=area;
            if(rpcId.sector() == 3)areaWm1_RB3_S03+=area;
            if(rpcId.sector() == 4)areaWm1_RB3_S04+=area;
            if(rpcId.sector() == 5)areaWm1_RB3_S05+=area;
            if(rpcId.sector() == 6)areaWm1_RB3_S06+=area;
            if(rpcId.sector() == 7)areaWm1_RB3_S07+=area;
            if(rpcId.sector() == 8)areaWm1_RB3_S08+=area;
            if(rpcId.sector() == 9)areaWm1_RB3_S09+=area;
            if(rpcId.sector() == 10)areaWm1_RB3_S10+=area;
            if(rpcId.sector() == 11)areaWm1_RB3_S11+=area;
            if(rpcId.sector() == 12)areaWm1_RB3_S12+=area;

          

        }


        if(rpcId.station() == 3 && rpcId.ring() == 0){
            if (rpcId.roll() == 3) areaW0_RB3_F +=area;
            if (rpcId.roll() == 1) areaW0_RB3_B +=area;             
           
            if(rpcId.sector() == 1)areaW0_RB3_S01+=area;
            if(rpcId.sector() == 2)areaW0_RB3_S02+=area;
            if(rpcId.sector() == 3)areaW0_RB3_S03+=area;
            if(rpcId.sector() == 4)areaW0_RB3_S04+=area;
            if(rpcId.sector() == 5)areaW0_RB3_S05+=area;
            if(rpcId.sector() == 6)areaW0_RB3_S06+=area;
            if(rpcId.sector() == 7)areaW0_RB3_S07+=area;
            if(rpcId.sector() == 8)areaW0_RB3_S08+=area;
            if(rpcId.sector() == 9)areaW0_RB3_S09+=area;
            if(rpcId.sector() == 10)areaW0_RB3_S10+=area;
            if(rpcId.sector() == 11)areaW0_RB3_S11+=area;
            if(rpcId.sector() == 12)areaW0_RB3_S12+=area;

          

        }


        if(rpcId.station() == 3 && rpcId.ring() == 1){
            if (rpcId.roll() == 3) areaWp1_RB3_F +=area;
            if (rpcId.roll() == 1) areaWp1_RB3_B +=area;             
           
            if(rpcId.sector() == 1)areaWp1_RB3_S01+=area;
            if(rpcId.sector() == 2)areaWp1_RB3_S02+=area;
            if(rpcId.sector() == 3)areaWp1_RB3_S03+=area;
            if(rpcId.sector() == 4)areaWp1_RB3_S04+=area;
            if(rpcId.sector() == 5)areaWp1_RB3_S05+=area;
            if(rpcId.sector() == 6)areaWp1_RB3_S06+=area;
            if(rpcId.sector() == 7)areaWp1_RB3_S07+=area;
            if(rpcId.sector() == 8)areaWp1_RB3_S08+=area;
            if(rpcId.sector() == 9)areaWp1_RB3_S09+=area;
            if(rpcId.sector() == 10)areaWp1_RB3_S10+=area;
            if(rpcId.sector() == 11)areaWp1_RB3_S11+=area;
            if(rpcId.sector() == 12)areaWp1_RB3_S12+=area;

          

        }


        if(rpcId.station() == 3 && rpcId.ring() == 2){
            if (rpcId.roll() == 3) areaWp2_RB3_F +=area;
            if (rpcId.roll() == 1) areaWp2_RB3_B +=area;             
           
            if(rpcId.sector() == 1)areaWp2_RB3_S01+=area;
            if(rpcId.sector() == 2)areaWp2_RB3_S02+=area;
            if(rpcId.sector() == 3)areaWp2_RB3_S03+=area;
            if(rpcId.sector() == 4)areaWp2_RB3_S04+=area;
            if(rpcId.sector() == 5)areaWp2_RB3_S05+=area;
            if(rpcId.sector() == 6)areaWp2_RB3_S06+=area;
            if(rpcId.sector() == 7)areaWp2_RB3_S07+=area;
            if(rpcId.sector() == 8)areaWp2_RB3_S08+=area;
            if(rpcId.sector() == 9)areaWp2_RB3_S09+=area;
            if(rpcId.sector() == 10)areaWp2_RB3_S10+=area;
            if(rpcId.sector() == 11)areaWp2_RB3_S11+=area;
            if(rpcId.sector() == 12)areaWp2_RB3_S12+=area;

          

        }// end RB3

  if(rpcId.station() == 4 && rpcId.ring() == -2){
            if (rpcId.roll() == 3) areaWm2_RB4_F +=area;
            if (rpcId.roll() == 1) areaWm2_RB4_B +=area;       
           
            if(rpcId.sector() == 1)areaWm2_RB4_S01+=area;
            if(rpcId.sector() == 2)areaWm2_RB4_S02+=area;
            if(rpcId.sector() == 3)areaWm2_RB4_S03+=area;
            if(rpcId.sector() == 4)areaWm2_RB4_S04+=area;
            if(rpcId.sector() == 5)areaWm2_RB4_S05+=area;
            if(rpcId.sector() == 6)areaWm2_RB4_S06+=area;
            if(rpcId.sector() == 7)areaWm2_RB4_S07+=area;
            if(rpcId.sector() == 8)areaWm2_RB4_S08+=area;
            if(rpcId.sector() == 9)areaWm2_RB4_S09+=area;
            if(rpcId.sector() == 10)areaWm2_RB4_S10+=area;
            if(rpcId.sector() == 11)areaWm2_RB4_S11+=area;
            if(rpcId.sector() == 12)areaWm2_RB4_S12+=area;

          

        }

        if(rpcId.station() == 4 && rpcId.ring() == -1){
            if (rpcId.roll() == 3) areaWm1_RB4_F +=area;
            if (rpcId.roll() == 1) areaWm1_RB4_B +=area;    

            if(rpcId.sector() == 1)areaWm1_RB4_S01+=area;
            if(rpcId.sector() == 2)areaWm1_RB4_S02+=area;
            if(rpcId.sector() == 3)areaWm1_RB4_S03+=area;
            if(rpcId.sector() == 4)areaWm1_RB4_S04+=area;
            if(rpcId.sector() == 5)areaWm1_RB4_S05+=area;
            if(rpcId.sector() == 6)areaWm1_RB4_S06+=area;
            if(rpcId.sector() == 7)areaWm1_RB4_S07+=area;
            if(rpcId.sector() == 8)areaWm1_RB4_S08+=area;
            if(rpcId.sector() == 9)areaWm1_RB4_S09+=area;
            if(rpcId.sector() == 10)areaWm1_RB4_S10+=area;
            if(rpcId.sector() == 11)areaWm1_RB4_S11+=area;
            if(rpcId.sector() == 12)areaWm1_RB4_S12+=area;

          

        }


        if(rpcId.station() == 4 && rpcId.ring() == 0){
            if (rpcId.roll() == 3) areaW0_RB4_F +=area;
            if (rpcId.roll() == 1) areaW0_RB4_B +=area;                
           
            if(rpcId.sector() == 1)areaW0_RB4_S01+=area;
            if(rpcId.sector() == 2)areaW0_RB4_S02+=area;
            if(rpcId.sector() == 3)areaW0_RB4_S03+=area;
            if(rpcId.sector() == 4)areaW0_RB4_S04+=area;
            if(rpcId.sector() == 5)areaW0_RB4_S05+=area;
            if(rpcId.sector() == 6)areaW0_RB4_S06+=area;
            if(rpcId.sector() == 7)areaW0_RB4_S07+=area;
            if(rpcId.sector() == 8)areaW0_RB4_S08+=area;
            if(rpcId.sector() == 9)areaW0_RB4_S09+=area;
            if(rpcId.sector() == 10)areaW0_RB4_S10+=area;
            if(rpcId.sector() == 11)areaW0_RB4_S11+=area;
            if(rpcId.sector() == 12)areaW0_RB4_S12+=area;

          

        }


        if(rpcId.station() == 4 && rpcId.ring() == 1){
            if (rpcId.roll() == 3) areaWp1_RB4_F +=area;
            if (rpcId.roll() == 1) areaWp1_RB4_B +=area;    
           
            if(rpcId.sector() == 1)areaWp1_RB4_S01+=area;
            if(rpcId.sector() == 2)areaWp1_RB4_S02+=area;
            if(rpcId.sector() == 3)areaWp1_RB4_S03+=area;
            if(rpcId.sector() == 4)areaWp1_RB4_S04+=area;
            if(rpcId.sector() == 5)areaWp1_RB4_S05+=area;
            if(rpcId.sector() == 6)areaWp1_RB4_S06+=area;
            if(rpcId.sector() == 7)areaWp1_RB4_S07+=area;
            if(rpcId.sector() == 8)areaWp1_RB4_S08+=area;
            if(rpcId.sector() == 9)areaWp1_RB4_S09+=area;
            if(rpcId.sector() == 10)areaWp1_RB4_S10+=area;
            if(rpcId.sector() == 11)areaWp1_RB4_S11+=area;
            if(rpcId.sector() == 12)areaWp1_RB4_S12+=area;

          

        }


        if(rpcId.station() == 4 && rpcId.ring() == 2){
            if (rpcId.roll() == 3) areaWp2_RB4_F +=area;
            if (rpcId.roll() == 1) areaWp2_RB4_B +=area;    
           
            if(rpcId.sector() == 1)areaWp2_RB4_S01+=area;
            if(rpcId.sector() == 2)areaWp2_RB4_S02+=area;
            if(rpcId.sector() == 3)areaWp2_RB4_S03+=area;
            if(rpcId.sector() == 4)areaWp2_RB4_S04+=area;
            if(rpcId.sector() == 5)areaWp2_RB4_S05+=area;
            if(rpcId.sector() == 6)areaWp2_RB4_S06+=area;
            if(rpcId.sector() == 7)areaWp2_RB4_S07+=area;
            if(rpcId.sector() == 8)areaWp2_RB4_S08+=area;
            if(rpcId.sector() == 9)areaWp2_RB4_S09+=area;
            if(rpcId.sector() == 10)areaWp2_RB4_S10+=area;
            if(rpcId.sector() == 11)areaWp2_RB4_S11+=area;
            if(rpcId.sector() == 12)areaWp2_RB4_S12+=area;

          

        }// end RB4
    }
     if (rpcId.region() == 1)
      {
        if(rpcId.station()==4)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREp42_F +=area;
            if (rpcId.roll() == 2) areaREp42_M +=area;
            if (rpcId.roll() == 1) areaREp42_B +=area;            


            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp42_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp42_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp42_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp42_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp42_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp42_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp42_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp42_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp42_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp42_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp42_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp42_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREp43_F +=area;
            if (rpcId.roll() == 2) areaREp43_M +=area;
            if (rpcId.roll() == 1) areaREp43_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp43_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp43_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp43_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp43_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp43_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp43_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp43_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp43_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp43_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp43_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp43_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp43_S12+=area;
          }
         }

        if(rpcId.station()==3)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREp32_F +=area;
            if (rpcId.roll() == 2) areaREp32_M +=area;
            if (rpcId.roll() == 1) areaREp32_B +=area;            


            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp32_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp32_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp32_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp32_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp32_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp32_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp32_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp32_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp32_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp32_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp32_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp32_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREp33_F +=area;
            if (rpcId.roll() == 2) areaREp33_M +=area;
            if (rpcId.roll() == 1) areaREp33_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp33_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp33_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp33_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp33_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp33_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp33_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp33_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp33_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp33_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp33_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp33_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp33_S12+=area;
          }
         }
        if(rpcId.station()==2)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREp22_F +=area;
            if (rpcId.roll() == 2) areaREp22_M +=area;
            if (rpcId.roll() == 1) areaREp22_B +=area;            


            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp22_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp22_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp22_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp22_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp22_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp22_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp22_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp22_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp22_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp22_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp22_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp22_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREp23_F +=area;
            if (rpcId.roll() == 2) areaREp23_M +=area;
            if (rpcId.roll() == 1) areaREp23_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp23_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp23_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp23_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp23_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp23_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp23_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp23_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp23_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp23_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp23_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp23_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp23_S12+=area;
          }
         }

   if(rpcId.station()==1)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREp12_F +=area;
            if (rpcId.roll() == 2) areaREp12_M +=area;
            if (rpcId.roll() == 1) areaREp12_B +=area;            

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp12_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp12_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp12_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp12_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp12_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp12_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp12_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp12_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp12_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp12_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp12_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp12_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREp13_F +=area;
            if (rpcId.roll() == 2) areaREp13_M +=area;
            if (rpcId.roll() == 1) areaREp13_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREp13_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp13_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREp13_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp13_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREp13_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp13_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREp13_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp13_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREp13_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp13_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREp13_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREp13_S12+=area;
          }
         }
      }


if (rpcId.region() == -1)
      {
        if(rpcId.station()==4)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREm42_F +=area;
            if (rpcId.roll() == 2) areaREm42_M +=area;
            if (rpcId.roll() == 1) areaREm42_B +=area;            


            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm42_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm42_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm42_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm42_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm42_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm42_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm42_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm42_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm42_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm42_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm42_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm42_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREm43_F +=area;
            if (rpcId.roll() == 2) areaREm43_M +=area;
            if (rpcId.roll() == 1) areaREm43_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm43_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm43_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm43_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm43_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm43_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm43_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm43_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm43_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm43_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm43_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm43_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm43_S12+=area;
          }
         }

       if(rpcId.station()==3)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREm32_F +=area;
            if (rpcId.roll() == 2) areaREm32_M +=area;
            if (rpcId.roll() == 1) areaREm32_B +=area;            


            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm32_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm32_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm32_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm32_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm32_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm32_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm32_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm32_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm32_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm32_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm32_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm32_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREm33_F +=area;
            if (rpcId.roll() == 2) areaREm33_M +=area;
            if (rpcId.roll() == 1) areaREm33_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm33_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm33_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm33_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm33_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm33_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm33_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm33_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm33_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm33_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm33_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm33_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm33_S12+=area;
          }
         }
        if(rpcId.station()==2)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREm22_F +=area;
            if (rpcId.roll() == 2) areaREm22_M +=area;
            if (rpcId.roll() == 1) areaREm22_B +=area;            


            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm22_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm22_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm22_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm22_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm22_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm22_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm22_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm22_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm22_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm22_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm22_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm22_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREm23_F +=area;
            if (rpcId.roll() == 2) areaREm23_M +=area;
            if (rpcId.roll() == 1) areaREm23_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm23_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm23_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm23_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm23_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm23_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm23_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm23_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm23_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm23_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm23_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm23_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm23_S12+=area;
          }
         }

   if(rpcId.station()==1)
        {
          if(rpcId.ring() == 2) {
            if (rpcId.roll() == 3) areaREm12_F +=area;
            if (rpcId.roll() == 2) areaREm12_M +=area;
            if (rpcId.roll() == 1) areaREm12_B +=area;            

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm12_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm12_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm12_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm12_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm12_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm12_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm12_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm12_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm12_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm12_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm12_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm12_S12+=area;
          }

             if(rpcId.ring() == 3) {
            if (rpcId.roll() == 3) areaREm13_F +=area;
            if (rpcId.roll() == 2) areaREm13_M +=area;
            if (rpcId.roll() == 1) areaREm13_B +=area;                  

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) areaREm13_S01+=area;
            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm13_S02+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) areaREm13_S03+=area;
            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm13_S04+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) areaREm13_S05+=area;
            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm13_S06+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) areaREm13_S07+=area;
            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm13_S08+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) areaREm13_S09+=area;
            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm13_S10+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) areaREm13_S11+=area;
            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          areaREm13_S12+=area;
          }
         }
      }

//end areas  
 

    RPCRecHitCollection::range rpcRecHitRange = rpcHits_handle->get(rpcId);
    RPCRecHitCollection::const_iterator recHit_2itrat;   
    int countRecHits = 0;
    int countRecHits_nobx0 = 0;

    RPCGeomServ RPCname(rpcId);
    if (debug)
    {
      std::cout << RPCname.name() << "\tarea: " << area << "\tstrips: " << roll->nstrips() << "\tstripArea: "<< stripArea << "\tarea: " << (roll->nstrips())*stripArea << std::endl;
      std::cout << RPCname.name() << "\teta " << globMiddleRol.eta() << "\tphi " << globMiddleRol.phi() << std::endl;
    }
   

    for(recHit_2itrat = rpcRecHitRange.first; recHit_2itrat!=rpcRecHitRange.second; ++recHit_2itrat)
    {
      //if(low==true) continue;
     
  int cluSize = recHit_2itrat->clusterSize();    
  int bx=recHit_2itrat->BunchX();
  int myFirstStrip = recHit_2itrat->firstClusterStrip();
      if(debug) std::cout << "bx: " << bx << "\tcls: "<< cluSize << std::endl;
      
      if (bx > 3) std::cout << RPCname.name() << "\t" << myFirstStrip << "\t" << bx << "\t" << bunchCross << std::endl;

//FIXME  std::cout << RPCname.name() << "\t" << myFirstStrip << "\t" << bx << "\t" << bunchCross << std::endl;  
// barrel
    
      if (rpcId.region() == 0)
      {
        numhit+=1;

            if(rpcId.station() == 1 && rpcId.ring() == -2){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S10_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1in_B_high->Fill(lumiperblock,0);
                        }

                  }
            }

        

            if(rpcId.station() == 1 && rpcId.ring() == -1){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 1 && rpcId.ring() == 0){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S01_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S02_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S03_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S04_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S05_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S06_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S07_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S08_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S09_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S10_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S11_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_S12_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {


                                 if(bunchNum+bx<114)bx_W0_RB1in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_F_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1in_B_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }

            if(rpcId.station() == 1 && rpcId.ring() == 1){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 1 && rpcId.ring() == 2){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }



// end RB1in
            if(rpcId.station() == 1 && rpcId.ring() == -2){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S10_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB1out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB1out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB1out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB1out_B_high->Fill(lumiperblock,0);
                        }

                  }
            }

        

            if(rpcId.station() == 1 && rpcId.ring() == -1){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB1out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB1out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB1out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB1out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 1 && rpcId.ring() == 0){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S01_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S02_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S03_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S04_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S05_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S06_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S07_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S08_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S09_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S10_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S11_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_S12_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_F_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB1out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB1out_B_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB1out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB1out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }

            if(rpcId.station() == 1 && rpcId.ring() == 1){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB1out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB1out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB1out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB1out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 1 && rpcId.ring() == 2){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB1out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB1out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB1out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB1out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }

// end RB1out

            if(rpcId.station() == 2 && rpcId.ring() == -2){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S10_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2in_B_high->Fill(lumiperblock,0);
                        }

                  }
            }

        

            if(rpcId.station() == 2 && rpcId.ring() == -1){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==2){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_M_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_M_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_M_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_M_high->Fill(lumiperblock,0);
                        }                        
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 2 && rpcId.ring() == 0){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S01_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S02_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S03_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S04_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S05_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S06_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S07_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S08_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S09_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S10_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S11_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_S12_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_F_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==2){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_M_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_M_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_M_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_M_high->Fill(lumiperblock,0);
                        }                        
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2in_B_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }

            if(rpcId.station() == 2 && rpcId.ring() == 1){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==2){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_M_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_M_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_M_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_M_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 2 && rpcId.ring() == 2){
                  if(rpcId.layer() == 1) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2in_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2in_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2in_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2in_B_high->Fill(lumiperblock,0);
                        }
                  }
            }



// end RB2in
            if(rpcId.station() == 2 && rpcId.ring() == -2){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S10_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==2){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_M_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_M_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_M_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_M_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB2out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB2out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB2out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB2out_B_high->Fill(lumiperblock,0);
                        }

                  }
            }

        

            if(rpcId.station() == 2 && rpcId.ring() == -1){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB2out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB2out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB2out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB2out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 2 && rpcId.ring() == 0){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S01_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S02_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S03_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S04_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S05_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S06_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S07_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S08_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S09_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S10_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S11_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_S12_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_F_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB2out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB2out_B_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB2out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB2out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }

            if(rpcId.station() == 2 && rpcId.ring() == 1){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB2out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB2out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB2out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB2out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }


            if(rpcId.station() == 2 && rpcId.ring() == 2){
                  if(rpcId.layer() == 2) {
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==2){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_M_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_M_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_M_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_M_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB2out_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB2out_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB2out_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB2out_B_high->Fill(lumiperblock,0);
                        }
                  }
            }

// end RB2out

            if(rpcId.station() == 3 && rpcId.ring() == -2){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S10_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB3_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB3_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB3_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB3_B_high->Fill(lumiperblock,0);
                        }

                  
            }

        

            if(rpcId.station() == 3 && rpcId.ring() == -1){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB3_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB3_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB3_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB3_B_high->Fill(lumiperblock,0);
                        }
                  
            }


            if(rpcId.station() == 3 && rpcId.ring() == 0){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S01_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S02_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S03_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S04_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S05_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S06_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S07_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S08_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S09_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S10_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S11_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_S12_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_F_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_F_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB3_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB3_B_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB3_B_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB3_B_high->Fill(lumiperblock,0);
                        }
                  
            }

            if(rpcId.station() == 3 && rpcId.ring() == 1){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB3_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB3_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB3_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB3_B_high->Fill(lumiperblock,0);
                        }
                  
            }


            if(rpcId.station() == 3 && rpcId.ring() == 2){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB3_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB3_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB3_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB3_B_high->Fill(lumiperblock,0);
                        }
                  
            }

// end RB3

            if(rpcId.station() == 4 && rpcId.ring() == -2){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S10_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm2_RB4_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm2_RB4_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm2_RB4_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm2_RB4_B_high->Fill(lumiperblock,0);
                        }

                  
            }

        

            if(rpcId.station() == 4 && rpcId.ring() == -1){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_F_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wm1_RB4_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wm1_RB4_B_abort->Fill(lumiperblock,0);
                                 else bx_Wm1_RB4_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wm1_RB4_B_high->Fill(lumiperblock,0);
                        }
                  
            }


            if(rpcId.station() == 4 && rpcId.ring() == 0){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S01_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S02_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S03_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S04_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S05_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S06_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S07_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S08_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S09_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S10_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S11_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_S12_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_F_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_F_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_W0_RB4_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_W0_RB4_B_abort->Fill(lumiperblock,0);
                                 else bx_W0_RB4_B_low->Fill(lumiperblock,0);
                              }
                              else bx_W0_RB4_B_high->Fill(lumiperblock,0);
                        }
                  
            }

            if(rpcId.station() == 4 && rpcId.ring() == 1){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp1_RB4_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp1_RB4_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp1_RB4_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp1_RB4_B_high->Fill(lumiperblock,0);
                        }
                  
            }


            if(rpcId.station() == 4 && rpcId.ring() == 2){
                  
                        if(rpcId.sector() == 1){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S01_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S01_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S01_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S01_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 2){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S02_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S02_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S02_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S02_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S03_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S03_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S03_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S03_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 4){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S04_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S04_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S04_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S04_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 5){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S05_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S05_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S05_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S05_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 6){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S06_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S06_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S06_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S06_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 7){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S07_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S07_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S07_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S07_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 8){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S08_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S08_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S08_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S08_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 9){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S09_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S09_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S09_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S09_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 10){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S10_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S10_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S10_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S10_high->Fill(lumiperblock,0);
                        }                       
                        if(rpcId.sector() == 11){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S11_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S11_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S11_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S11_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.sector() == 12){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_S12_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_S12_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_S12_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_S12_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() == 3){
                              if(low[(int)bx+2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_F_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_F_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_F_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_F_high->Fill(lumiperblock,0);
                        }
                        if(rpcId.roll() ==1){
                              if(low[(int) bx +2]==true) {
                                 if(bunchNum+bx<114)bx_Wp2_RB4_B_prebeam->Fill(lumiperblock,0);
                                 else if(bunchNum+bx>=3354) bx_Wp2_RB4_B_abort->Fill(lumiperblock,0);
                                 else bx_Wp2_RB4_B_low->Fill(lumiperblock,0);
                              }
                              else bx_Wp2_RB4_B_high->Fill(lumiperblock,0);
                        }
                  
            }

            // end RB4


      }
      


if (rpcId.region() == 1)
      {
      if(rpcId.station()==4){
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_F_abort->Fill(lumiperblock,0);
                     else bx_REp42_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_M_abort->Fill(lumiperblock,0);
                     else bx_REp42_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REp42_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_B_abort->Fill(lumiperblock,0);
                     else bx_REp42_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S01_abort->Fill(lumiperblock,0);
                     else bx_REp42_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S02_abort->Fill(lumiperblock,0);
                     else bx_REp42_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S03_abort->Fill(lumiperblock,0);
                     else bx_REp42_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S04_abort->Fill(lumiperblock,0);
                     else bx_REp42_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S05_abort->Fill(lumiperblock,0);
                     else bx_REp42_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S06_abort->Fill(lumiperblock,0);
                     else bx_REp42_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S07_abort->Fill(lumiperblock,0);
                     else bx_REp42_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S08_abort->Fill(lumiperblock,0);
                     else bx_REp42_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S09_abort->Fill(lumiperblock,0);
                     else bx_REp42_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S10_abort->Fill(lumiperblock,0);
                     else bx_REp42_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S11_abort->Fill(lumiperblock,0);
                     else bx_REp42_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp42_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp42_S12_abort->Fill(lumiperblock,0);
                     else bx_REp42_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp42_S12_high->Fill(lumiperblock,0);
            }

      }

      if(rpcId.ring() == 3) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_F_abort->Fill(lumiperblock,0);
                     else bx_REp43_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_M_abort->Fill(lumiperblock,0);
                     else bx_REp43_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REp43_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_B_abort->Fill(lumiperblock,0);
                     else bx_REp43_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S01_abort->Fill(lumiperblock,0);
                     else bx_REp43_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S02_abort->Fill(lumiperblock,0);
                     else bx_REp43_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S03_abort->Fill(lumiperblock,0);
                     else bx_REp43_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S04_abort->Fill(lumiperblock,0);
                     else bx_REp43_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S05_abort->Fill(lumiperblock,0);
                     else bx_REp43_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S06_abort->Fill(lumiperblock,0);
                     else bx_REp43_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S07_abort->Fill(lumiperblock,0);
                     else bx_REp43_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S08_abort->Fill(lumiperblock,0);
                     else bx_REp43_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S09_abort->Fill(lumiperblock,0);
                     else bx_REp43_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S10_abort->Fill(lumiperblock,0);
                     else bx_REp43_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S11_abort->Fill(lumiperblock,0);
                     else bx_REp43_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp43_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp43_S12_abort->Fill(lumiperblock,0);
                     else bx_REp43_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp43_S12_high->Fill(lumiperblock,0);
            }

          }
         }

      if(rpcId.station()==3){
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_F_abort->Fill(lumiperblock,0);
                     else bx_REp32_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_M_abort->Fill(lumiperblock,0);
                     else bx_REp32_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REp32_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_B_abort->Fill(lumiperblock,0);
                     else bx_REp32_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S01_abort->Fill(lumiperblock,0);
                     else bx_REp32_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S02_abort->Fill(lumiperblock,0);
                     else bx_REp32_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S03_abort->Fill(lumiperblock,0);
                     else bx_REp32_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S04_abort->Fill(lumiperblock,0);
                     else bx_REp32_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S05_abort->Fill(lumiperblock,0);
                     else bx_REp32_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S06_abort->Fill(lumiperblock,0);
                     else bx_REp32_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S07_abort->Fill(lumiperblock,0);
                     else bx_REp32_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S08_abort->Fill(lumiperblock,0);
                     else bx_REp32_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S09_abort->Fill(lumiperblock,0);
                     else bx_REp32_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S10_abort->Fill(lumiperblock,0);
                     else bx_REp32_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S11_abort->Fill(lumiperblock,0);
                     else bx_REp32_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp32_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp32_S12_abort->Fill(lumiperblock,0);
                     else bx_REp32_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp32_S12_high->Fill(lumiperblock,0);
            }

      }

      if(rpcId.ring() == 3) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_F_abort->Fill(lumiperblock,0);
                     else bx_REp33_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_M_abort->Fill(lumiperblock,0);
                     else bx_REp33_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REp33_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_B_abort->Fill(lumiperblock,0);
                     else bx_REp33_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S01_abort->Fill(lumiperblock,0);
                     else bx_REp33_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S02_abort->Fill(lumiperblock,0);
                     else bx_REp33_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S03_abort->Fill(lumiperblock,0);
                     else bx_REp33_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S04_abort->Fill(lumiperblock,0);
                     else bx_REp33_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S05_abort->Fill(lumiperblock,0);
                     else bx_REp33_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S06_abort->Fill(lumiperblock,0);
                     else bx_REp33_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S07_abort->Fill(lumiperblock,0);
                     else bx_REp33_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S08_abort->Fill(lumiperblock,0);
                     else bx_REp33_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S09_abort->Fill(lumiperblock,0);
                     else bx_REp33_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S10_abort->Fill(lumiperblock,0);
                     else bx_REp33_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S11_abort->Fill(lumiperblock,0);
                     else bx_REp33_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp33_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp33_S12_abort->Fill(lumiperblock,0);
                     else bx_REp33_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp33_S12_high->Fill(lumiperblock,0);
            }

          }
         }
if(rpcId.station()==2){
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_F_abort->Fill(lumiperblock,0);
                     else bx_REp22_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_M_abort->Fill(lumiperblock,0);
                     else bx_REp22_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REp22_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_B_abort->Fill(lumiperblock,0);
                     else bx_REp22_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S01_abort->Fill(lumiperblock,0);
                     else bx_REp22_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S02_abort->Fill(lumiperblock,0);
                     else bx_REp22_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S03_abort->Fill(lumiperblock,0);
                     else bx_REp22_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S04_abort->Fill(lumiperblock,0);
                     else bx_REp22_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S05_abort->Fill(lumiperblock,0);
                     else bx_REp22_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S06_abort->Fill(lumiperblock,0);
                     else bx_REp22_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S07_abort->Fill(lumiperblock,0);
                     else bx_REp22_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S08_abort->Fill(lumiperblock,0);
                     else bx_REp22_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S09_abort->Fill(lumiperblock,0);
                     else bx_REp22_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S10_abort->Fill(lumiperblock,0);
                     else bx_REp22_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S11_abort->Fill(lumiperblock,0);
                     else bx_REp22_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp22_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp22_S12_abort->Fill(lumiperblock,0);
                     else bx_REp22_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp22_S12_high->Fill(lumiperblock,0);
            }

      }

      if(rpcId.ring() == 3) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_F_abort->Fill(lumiperblock,0);
                     else bx_REp23_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_M_abort->Fill(lumiperblock,0);
                     else bx_REp23_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REp23_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_B_abort->Fill(lumiperblock,0);
                     else bx_REp23_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S01_abort->Fill(lumiperblock,0);
                     else bx_REp23_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S02_abort->Fill(lumiperblock,0);
                     else bx_REp23_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S03_abort->Fill(lumiperblock,0);
                     else bx_REp23_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S04_abort->Fill(lumiperblock,0);
                     else bx_REp23_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S05_abort->Fill(lumiperblock,0);
                     else bx_REp23_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S06_abort->Fill(lumiperblock,0);
                     else bx_REp23_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S07_abort->Fill(lumiperblock,0);
                     else bx_REp23_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S08_abort->Fill(lumiperblock,0);
                     else bx_REp23_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S09_abort->Fill(lumiperblock,0);
                     else bx_REp23_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S10_abort->Fill(lumiperblock,0);
                     else bx_REp23_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S11_abort->Fill(lumiperblock,0);
                     else bx_REp23_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp23_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp23_S12_abort->Fill(lumiperblock,0);
                     else bx_REp23_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp23_S12_high->Fill(lumiperblock,0);
            }

          }
         }

   if(rpcId.station()==1)
        {
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_F_abort->Fill(lumiperblock,0);
                     else bx_REp12_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_M_abort->Fill(lumiperblock,0);
                     else bx_REp12_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REp12_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_B_abort->Fill(lumiperblock,0);
                     else bx_REp12_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S01_abort->Fill(lumiperblock,0);
                     else bx_REp12_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S02_abort->Fill(lumiperblock,0);
                     else bx_REp12_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S03_abort->Fill(lumiperblock,0);
                     else bx_REp12_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S04_abort->Fill(lumiperblock,0);
                     else bx_REp12_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S05_abort->Fill(lumiperblock,0);
                     else bx_REp12_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S06_abort->Fill(lumiperblock,0);
                     else bx_REp12_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S07_abort->Fill(lumiperblock,0);
                     else bx_REp12_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S08_abort->Fill(lumiperblock,0);
                     else bx_REp12_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S09_abort->Fill(lumiperblock,0);
                     else bx_REp12_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S10_abort->Fill(lumiperblock,0);
                     else bx_REp12_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S11_abort->Fill(lumiperblock,0);
                     else bx_REp12_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp12_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp12_S12_abort->Fill(lumiperblock,0);
                     else bx_REp12_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp12_S12_high->Fill(lumiperblock,0);
            }

          }

             if(rpcId.ring() == 3) {

                  if(rpcId.roll() ==3){
                        if(low[(int) bx+2]==true) {
                           if(bunchNum+bx<114)bx_REp13_F_prebeam->Fill(lumiperblock,0);
                           else if(bunchNum+bx>=3354) bx_REp13_F_abort->Fill(lumiperblock,0);
                           else bx_REp13_F_low->Fill(lumiperblock,0);
                        }
                        else bx_REp13_F_high->Fill(lumiperblock,0);                              
                  }

                  if(rpcId.roll() ==2){
                        if(low[(int) bx+2]==true) {
                           if(bunchNum+bx<114)bx_REp13_M_prebeam->Fill(lumiperblock,0);
                           else if(bunchNum+bx>=3354) bx_REp13_M_abort->Fill(lumiperblock,0);
                           else bx_REp13_M_low->Fill(lumiperblock,0);
                        }
                        else bx_REp13_M_high->Fill(lumiperblock,0);                               
                  }

                  if(rpcId.roll() ==1){
                        if(low[(int) bx +2]==true) {
                           if(bunchNum+bx<114)bx_REp13_B_prebeam->Fill(lumiperblock,0);
                           else if(bunchNum+bx>=3354) bx_REp13_B_abort->Fill(lumiperblock,0);
                           else bx_REp13_B_low->Fill(lumiperblock,0);
                        }
                        else bx_REp13_B_high->Fill(lumiperblock,0);
                  }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S01_abort->Fill(lumiperblock,0);
                     else bx_REp13_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S02_abort->Fill(lumiperblock,0);
                     else bx_REp13_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S03_abort->Fill(lumiperblock,0);
                     else bx_REp13_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S04_abort->Fill(lumiperblock,0);
                     else bx_REp13_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S05_abort->Fill(lumiperblock,0);
                     else bx_REp13_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S06_abort->Fill(lumiperblock,0);
                     else bx_REp13_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S07_abort->Fill(lumiperblock,0);
                     else bx_REp13_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S08_abort->Fill(lumiperblock,0);
                     else bx_REp13_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S09_abort->Fill(lumiperblock,0);
                     else bx_REp13_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S10_abort->Fill(lumiperblock,0);
                     else bx_REp13_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S11_abort->Fill(lumiperblock,0);
                     else bx_REp13_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REp13_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REp13_S12_abort->Fill(lumiperblock,0);
                     else bx_REp13_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REp13_S12_high->Fill(lumiperblock,0);
            }

          }
         }
      }


      if (rpcId.region() == -1)
      {
      if(rpcId.station()==4){
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_F_abort->Fill(lumiperblock,0);
                     else bx_REm42_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_M_abort->Fill(lumiperblock,0);
                     else bx_REm42_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REm42_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_B_abort->Fill(lumiperblock,0);
                     else bx_REm42_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S01_abort->Fill(lumiperblock,0);
                     else bx_REm42_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S02_abort->Fill(lumiperblock,0);
                     else bx_REm42_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S03_abort->Fill(lumiperblock,0);
                     else bx_REm42_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S04_abort->Fill(lumiperblock,0);
                     else bx_REm42_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S05_abort->Fill(lumiperblock,0);
                     else bx_REm42_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S06_abort->Fill(lumiperblock,0);
                     else bx_REm42_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S07_abort->Fill(lumiperblock,0);
                     else bx_REm42_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S08_abort->Fill(lumiperblock,0);
                     else bx_REm42_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S09_abort->Fill(lumiperblock,0);
                     else bx_REm42_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S10_abort->Fill(lumiperblock,0);
                     else bx_REm42_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S11_abort->Fill(lumiperblock,0);
                     else bx_REm42_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm42_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm42_S12_abort->Fill(lumiperblock,0);
                     else bx_REm42_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm42_S12_high->Fill(lumiperblock,0);
            }

      }

      if(rpcId.ring() == 3) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_F_abort->Fill(lumiperblock,0);
                     else bx_REm43_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_M_abort->Fill(lumiperblock,0);
                     else bx_REm43_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REm43_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_B_abort->Fill(lumiperblock,0);
                     else bx_REm43_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S01_abort->Fill(lumiperblock,0);
                     else bx_REm43_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S02_abort->Fill(lumiperblock,0);
                     else bx_REm43_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S03_abort->Fill(lumiperblock,0);
                     else bx_REm43_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S04_abort->Fill(lumiperblock,0);
                     else bx_REm43_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S05_abort->Fill(lumiperblock,0);
                     else bx_REm43_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S06_abort->Fill(lumiperblock,0);
                     else bx_REm43_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S07_abort->Fill(lumiperblock,0);
                     else bx_REm43_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S08_abort->Fill(lumiperblock,0);
                     else bx_REm43_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S09_abort->Fill(lumiperblock,0);
                     else bx_REm43_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S10_abort->Fill(lumiperblock,0);
                     else bx_REm43_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S11_abort->Fill(lumiperblock,0);
                     else bx_REm43_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm43_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm43_S12_abort->Fill(lumiperblock,0);
                     else bx_REm43_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm43_S12_high->Fill(lumiperblock,0);
            }

          }
         }

      if(rpcId.station()==3){
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_F_abort->Fill(lumiperblock,0);
                     else bx_REm32_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_M_abort->Fill(lumiperblock,0);
                     else bx_REm32_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REm32_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_B_abort->Fill(lumiperblock,0);
                     else bx_REm32_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S01_abort->Fill(lumiperblock,0);
                     else bx_REm32_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S02_abort->Fill(lumiperblock,0);
                     else bx_REm32_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S03_abort->Fill(lumiperblock,0);
                     else bx_REm32_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S04_abort->Fill(lumiperblock,0);
                     else bx_REm32_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S05_abort->Fill(lumiperblock,0);
                     else bx_REm32_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S06_abort->Fill(lumiperblock,0);
                     else bx_REm32_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S07_abort->Fill(lumiperblock,0);
                     else bx_REm32_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S08_abort->Fill(lumiperblock,0);
                     else bx_REm32_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S09_abort->Fill(lumiperblock,0);
                     else bx_REm32_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S10_abort->Fill(lumiperblock,0);
                     else bx_REm32_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S11_abort->Fill(lumiperblock,0);
                     else bx_REm32_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm32_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm32_S12_abort->Fill(lumiperblock,0);
                     else bx_REm32_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm32_S12_high->Fill(lumiperblock,0);
            }

      }

      if(rpcId.ring() == 3) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_F_abort->Fill(lumiperblock,0);
                     else bx_REm33_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_M_abort->Fill(lumiperblock,0);
                     else bx_REm33_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REm33_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_B_abort->Fill(lumiperblock,0);
                     else bx_REm33_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S01_abort->Fill(lumiperblock,0);
                     else bx_REm33_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S02_abort->Fill(lumiperblock,0);
                     else bx_REm33_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S03_abort->Fill(lumiperblock,0);
                     else bx_REm33_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S04_abort->Fill(lumiperblock,0);
                     else bx_REm33_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S05_abort->Fill(lumiperblock,0);
                     else bx_REm33_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S06_abort->Fill(lumiperblock,0);
                     else bx_REm33_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S07_abort->Fill(lumiperblock,0);
                     else bx_REm33_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S08_abort->Fill(lumiperblock,0);
                     else bx_REm33_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S09_abort->Fill(lumiperblock,0);
                     else bx_REm33_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S10_abort->Fill(lumiperblock,0);
                     else bx_REm33_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S11_abort->Fill(lumiperblock,0);
                     else bx_REm33_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm33_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm33_S12_abort->Fill(lumiperblock,0);
                     else bx_REm33_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm33_S12_high->Fill(lumiperblock,0);
            }

          }
         }
if(rpcId.station()==2){
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_F_abort->Fill(lumiperblock,0);
                     else bx_REm22_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_M_abort->Fill(lumiperblock,0);
                     else bx_REm22_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REm22_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_B_abort->Fill(lumiperblock,0);
                     else bx_REm22_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S01_abort->Fill(lumiperblock,0);
                     else bx_REm22_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S02_abort->Fill(lumiperblock,0);
                     else bx_REm22_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S03_abort->Fill(lumiperblock,0);
                     else bx_REm22_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S04_abort->Fill(lumiperblock,0);
                     else bx_REm22_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S05_abort->Fill(lumiperblock,0);
                     else bx_REm22_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S06_abort->Fill(lumiperblock,0);
                     else bx_REm22_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S07_abort->Fill(lumiperblock,0);
                     else bx_REm22_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S08_abort->Fill(lumiperblock,0);
                     else bx_REm22_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S09_abort->Fill(lumiperblock,0);
                     else bx_REm22_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S10_abort->Fill(lumiperblock,0);
                     else bx_REm22_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S11_abort->Fill(lumiperblock,0);
                     else bx_REm22_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm22_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm22_S12_abort->Fill(lumiperblock,0);
                     else bx_REm22_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm22_S12_high->Fill(lumiperblock,0);
            }

      }

      if(rpcId.ring() == 3) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_F_abort->Fill(lumiperblock,0);
                     else bx_REm23_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_M_abort->Fill(lumiperblock,0);
                     else bx_REm23_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REm23_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_B_abort->Fill(lumiperblock,0);
                     else bx_REm23_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S01_abort->Fill(lumiperblock,0);
                     else bx_REm23_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S02_abort->Fill(lumiperblock,0);
                     else bx_REm23_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S03_abort->Fill(lumiperblock,0);
                     else bx_REm23_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S04_abort->Fill(lumiperblock,0);
                     else bx_REm23_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S05_abort->Fill(lumiperblock,0);
                     else bx_REm23_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S06_abort->Fill(lumiperblock,0);
                     else bx_REm23_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S07_abort->Fill(lumiperblock,0);
                     else bx_REm23_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S08_abort->Fill(lumiperblock,0);
                     else bx_REm23_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S09_abort->Fill(lumiperblock,0);
                     else bx_REm23_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S10_abort->Fill(lumiperblock,0);
                     else bx_REm23_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S11_abort->Fill(lumiperblock,0);
                     else bx_REm23_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm23_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm23_S12_abort->Fill(lumiperblock,0);
                     else bx_REm23_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm23_S12_high->Fill(lumiperblock,0);
            }

          }
         }

   if(rpcId.station()==1)
        {
          if(rpcId.ring() == 2) {

            if(rpcId.roll() ==3){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_F_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_F_abort->Fill(lumiperblock,0);
                     else bx_REm12_F_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_F_high->Fill(lumiperblock,0);                        
            }

            if(rpcId.roll() ==2){
                  if(low[(int) bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_M_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_M_abort->Fill(lumiperblock,0);
                     else bx_REm12_M_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_M_high->Fill(lumiperblock,0);                         
            }

            if(rpcId.roll() ==1){
                  if(low[(int) bx +2]==true) {
                     if(bunchNum+bx<114)bx_REm12_B_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_B_abort->Fill(lumiperblock,0);
                     else bx_REm12_B_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_B_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S01_abort->Fill(lumiperblock,0);
                     else bx_REm12_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S02_abort->Fill(lumiperblock,0);
                     else bx_REm12_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S03_abort->Fill(lumiperblock,0);
                     else bx_REm12_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S04_abort->Fill(lumiperblock,0);
                     else bx_REm12_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S05_abort->Fill(lumiperblock,0);
                     else bx_REm12_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S06_abort->Fill(lumiperblock,0);
                     else bx_REm12_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S07_abort->Fill(lumiperblock,0);
                     else bx_REm12_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S08_abort->Fill(lumiperblock,0);
                     else bx_REm12_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S09_abort->Fill(lumiperblock,0);
                     else bx_REm12_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S10_abort->Fill(lumiperblock,0);
                     else bx_REm12_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S11_abort->Fill(lumiperblock,0);
                     else bx_REm12_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm12_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm12_S12_abort->Fill(lumiperblock,0);
                     else bx_REm12_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm12_S12_high->Fill(lumiperblock,0);
            }

          }

             if(rpcId.ring() == 3) {

                  if(rpcId.roll() ==3){
                        if(low[(int) bx+2]==true) {
                           if(bunchNum+bx<114)bx_REm13_F_prebeam->Fill(lumiperblock,0);
                           else if(bunchNum+bx>=3354) bx_REm13_F_abort->Fill(lumiperblock,0);
                           else bx_REm13_F_low->Fill(lumiperblock,0);
                        }
                        else bx_REm13_F_high->Fill(lumiperblock,0);                              
                  }

                  if(rpcId.roll() ==2){
                        if(low[(int) bx+2]==true) {
                           if(bunchNum+bx<114)bx_REm13_M_prebeam->Fill(lumiperblock,0);
                           else if(bunchNum+bx>=3354) bx_REm13_M_abort->Fill(lumiperblock,0);
                           else bx_REm13_M_low->Fill(lumiperblock,0);
                        }
                        else bx_REm13_M_high->Fill(lumiperblock,0);                               
                  }

                  if(rpcId.roll() ==1){
                        if(low[(int) bx +2]==true) {
                           if(bunchNum+bx<114)bx_REm13_B_prebeam->Fill(lumiperblock,0);
                           else if(bunchNum+bx>=3354) bx_REm13_B_abort->Fill(lumiperblock,0);
                           else bx_REm13_B_low->Fill(lumiperblock,0);
                        }
                        else bx_REm13_B_high->Fill(lumiperblock,0);
                  }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 6 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S01_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S01_abort->Fill(lumiperblock,0);
                     else bx_REm13_S01_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S01_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 1 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S02_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S02_abort->Fill(lumiperblock,0);
                     else bx_REm13_S02_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S02_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 1 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S03_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S03_abort->Fill(lumiperblock,0);
                     else bx_REm13_S03_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S03_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 2 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S04_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S04_abort->Fill(lumiperblock,0);
                     else bx_REm13_S04_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S04_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 2 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S05_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S05_abort->Fill(lumiperblock,0);
                     else bx_REm13_S05_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S05_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 3 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S06_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S06_abort->Fill(lumiperblock,0);
                     else bx_REm13_S06_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S06_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 3 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S07_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S07_abort->Fill(lumiperblock,0);
                     else bx_REm13_S07_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S07_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 4 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S08_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S08_abort->Fill(lumiperblock,0);
                     else bx_REm13_S08_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S08_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 4 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S09_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S09_abort->Fill(lumiperblock,0);
                     else bx_REm13_S09_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S09_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 5 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S10_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S10_abort->Fill(lumiperblock,0);
                     else bx_REm13_S10_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S10_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 1 || rpcId.subsector() == 2)) || (rpcId.sector() == 5 && rpcId.subsector() == 6 )) {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S11_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S11_abort->Fill(lumiperblock,0);
                     else bx_REm13_S11_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S11_high->Fill(lumiperblock,0);
            }

            if((rpcId.sector() == 6 && (rpcId.subsector() == 3 || rpcId.subsector() == 4 || rpcId.subsector() == 5)) )                          {
                  if(low[(int)bx+2]==true) {
                     if(bunchNum+bx<114)bx_REm13_S12_prebeam->Fill(lumiperblock,0);
                     else if(bunchNum+bx>=3354) bx_REm13_S12_abort->Fill(lumiperblock,0);
                     else bx_REm13_S12_low->Fill(lumiperblock,0);
                  }
                  else bx_REm13_S12_high->Fill(lumiperblock,0);
            }

          }
         }
      }


    }




  }



}// end RateVsLumi_PhiEtaRecompute:analyzer

// ------------ method called once each job just before starting event loop  ------------
void
RateVsLumi_PhiEtaRecompute::beginJob()
{
lumi_high = fs->make<TH1F>("lumi_high","lumi_high",21,-0.5,20.5);
lumi_low = fs->make<TH1F>("lumi_low","lumi_low",21,-0.5,20.5);
lumi_abort = fs->make<TH1F>("lumi_abort","lumi_abort",21,-0.5,20.5);
lumi_prebeam = fs->make<TH1F>("lumi_prebeam","lumi_prebeam",21,-0.5,20.5);



bx_Wm2_RB1in_S01_high = fs->make<TH2F>("bx_Wm2_RB1in_S01_high","bx_Wm2_RB1in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S02_high = fs->make<TH2F>("bx_Wm2_RB1in_S02_high","bx_Wm2_RB1in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S03_high = fs->make<TH2F>("bx_Wm2_RB1in_S03_high","bx_Wm2_RB1in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S04_high = fs->make<TH2F>("bx_Wm2_RB1in_S04_high","bx_Wm2_RB1in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S05_high = fs->make<TH2F>("bx_Wm2_RB1in_S05_high","bx_Wm2_RB1in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S06_high = fs->make<TH2F>("bx_Wm2_RB1in_S06_high","bx_Wm2_RB1in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S07_high = fs->make<TH2F>("bx_Wm2_RB1in_S07_high","bx_Wm2_RB1in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S08_high = fs->make<TH2F>("bx_Wm2_RB1in_S08_high","bx_Wm2_RB1in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S09_high = fs->make<TH2F>("bx_Wm2_RB1in_S09_high","bx_Wm2_RB1in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S10_high = fs->make<TH2F>("bx_Wm2_RB1in_S10_high","bx_Wm2_RB1in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S11_high = fs->make<TH2F>("bx_Wm2_RB1in_S11_high","bx_Wm2_RB1in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S12_high = fs->make<TH2F>("bx_Wm2_RB1in_S12_high","bx_Wm2_RB1in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB1in_S01_high = fs->make<TH2F>("bx_Wm1_RB1in_S01_high","bx_Wm1_RB1in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S02_high = fs->make<TH2F>("bx_Wm1_RB1in_S02_high","bx_Wm1_RB1in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S03_high = fs->make<TH2F>("bx_Wm1_RB1in_S03_high","bx_Wm1_RB1in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S04_high = fs->make<TH2F>("bx_Wm1_RB1in_S04_high","bx_Wm1_RB1in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S05_high = fs->make<TH2F>("bx_Wm1_RB1in_S05_high","bx_Wm1_RB1in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S06_high = fs->make<TH2F>("bx_Wm1_RB1in_S06_high","bx_Wm1_RB1in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S07_high = fs->make<TH2F>("bx_Wm1_RB1in_S07_high","bx_Wm1_RB1in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S08_high = fs->make<TH2F>("bx_Wm1_RB1in_S08_high","bx_Wm1_RB1in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S09_high = fs->make<TH2F>("bx_Wm1_RB1in_S09_high","bx_Wm1_RB1in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S10_high = fs->make<TH2F>("bx_Wm1_RB1in_S10_high","bx_Wm1_RB1in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S11_high = fs->make<TH2F>("bx_Wm1_RB1in_S11_high","bx_Wm1_RB1in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S12_high = fs->make<TH2F>("bx_Wm1_RB1in_S12_high","bx_Wm1_RB1in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB1in_S01_high = fs->make<TH2F>("bx_W0_RB1in_S01_high","bx_W0_RB1in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S02_high = fs->make<TH2F>("bx_W0_RB1in_S02_high","bx_W0_RB1in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S03_high = fs->make<TH2F>("bx_W0_RB1in_S03_high","bx_W0_RB1in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S04_high = fs->make<TH2F>("bx_W0_RB1in_S04_high","bx_W0_RB1in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S05_high = fs->make<TH2F>("bx_W0_RB1in_S05_high","bx_W0_RB1in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S06_high = fs->make<TH2F>("bx_W0_RB1in_S06_high","bx_W0_RB1in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S07_high = fs->make<TH2F>("bx_W0_RB1in_S07_high","bx_W0_RB1in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S08_high = fs->make<TH2F>("bx_W0_RB1in_S08_high","bx_W0_RB1in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S09_high = fs->make<TH2F>("bx_W0_RB1in_S09_high","bx_W0_RB1in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S10_high = fs->make<TH2F>("bx_W0_RB1in_S10_high","bx_W0_RB1in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S11_high = fs->make<TH2F>("bx_W0_RB1in_S11_high","bx_W0_RB1in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S12_high = fs->make<TH2F>("bx_W0_RB1in_S12_high","bx_W0_RB1in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB1in_S01_high = fs->make<TH2F>("bx_Wp1_RB1in_S01_high","bx_Wp1_RB1in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S02_high = fs->make<TH2F>("bx_Wp1_RB1in_S02_high","bx_Wp1_RB1in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S03_high = fs->make<TH2F>("bx_Wp1_RB1in_S03_high","bx_Wp1_RB1in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S04_high = fs->make<TH2F>("bx_Wp1_RB1in_S04_high","bx_Wp1_RB1in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S05_high = fs->make<TH2F>("bx_Wp1_RB1in_S05_high","bx_Wp1_RB1in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S06_high = fs->make<TH2F>("bx_Wp1_RB1in_S06_high","bx_Wp1_RB1in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S07_high = fs->make<TH2F>("bx_Wp1_RB1in_S07_high","bx_Wp1_RB1in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S08_high = fs->make<TH2F>("bx_Wp1_RB1in_S08_high","bx_Wp1_RB1in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S09_high = fs->make<TH2F>("bx_Wp1_RB1in_S09_high","bx_Wp1_RB1in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S10_high = fs->make<TH2F>("bx_Wp1_RB1in_S10_high","bx_Wp1_RB1in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S11_high = fs->make<TH2F>("bx_Wp1_RB1in_S11_high","bx_Wp1_RB1in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S12_high = fs->make<TH2F>("bx_Wp1_RB1in_S12_high","bx_Wp1_RB1in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB1in_S01_high = fs->make<TH2F>("bx_Wp2_RB1in_S01_high","bx_Wp2_RB1in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S02_high = fs->make<TH2F>("bx_Wp2_RB1in_S02_high","bx_Wp2_RB1in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S03_high = fs->make<TH2F>("bx_Wp2_RB1in_S03_high","bx_Wp2_RB1in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S04_high = fs->make<TH2F>("bx_Wp2_RB1in_S04_high","bx_Wp2_RB1in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S05_high = fs->make<TH2F>("bx_Wp2_RB1in_S05_high","bx_Wp2_RB1in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S06_high = fs->make<TH2F>("bx_Wp2_RB1in_S06_high","bx_Wp2_RB1in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S07_high = fs->make<TH2F>("bx_Wp2_RB1in_S07_high","bx_Wp2_RB1in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S08_high = fs->make<TH2F>("bx_Wp2_RB1in_S08_high","bx_Wp2_RB1in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S09_high = fs->make<TH2F>("bx_Wp2_RB1in_S09_high","bx_Wp2_RB1in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S10_high = fs->make<TH2F>("bx_Wp2_RB1in_S10_high","bx_Wp2_RB1in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S11_high = fs->make<TH2F>("bx_Wp2_RB1in_S11_high","bx_Wp2_RB1in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S12_high = fs->make<TH2F>("bx_Wp2_RB1in_S12_high","bx_Wp2_RB1in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

// RB1out

bx_Wm2_RB1out_S01_high = fs->make<TH2F>("bx_Wm2_RB1out_S01_high","bx_Wm2_RB1out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S02_high = fs->make<TH2F>("bx_Wm2_RB1out_S02_high","bx_Wm2_RB1out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S03_high = fs->make<TH2F>("bx_Wm2_RB1out_S03_high","bx_Wm2_RB1out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S04_high = fs->make<TH2F>("bx_Wm2_RB1out_S04_high","bx_Wm2_RB1out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S05_high = fs->make<TH2F>("bx_Wm2_RB1out_S05_high","bx_Wm2_RB1out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S06_high = fs->make<TH2F>("bx_Wm2_RB1out_S06_high","bx_Wm2_RB1out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S07_high = fs->make<TH2F>("bx_Wm2_RB1out_S07_high","bx_Wm2_RB1out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S08_high = fs->make<TH2F>("bx_Wm2_RB1out_S08_high","bx_Wm2_RB1out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S09_high = fs->make<TH2F>("bx_Wm2_RB1out_S09_high","bx_Wm2_RB1out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S10_high = fs->make<TH2F>("bx_Wm2_RB1out_S10_high","bx_Wm2_RB1out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S11_high = fs->make<TH2F>("bx_Wm2_RB1out_S11_high","bx_Wm2_RB1out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S12_high = fs->make<TH2F>("bx_Wm2_RB1out_S12_high","bx_Wm2_RB1out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB1out_S01_high = fs->make<TH2F>("bx_Wm1_RB1out_S01_high","bx_Wm1_RB1out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S02_high = fs->make<TH2F>("bx_Wm1_RB1out_S02_high","bx_Wm1_RB1out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S03_high = fs->make<TH2F>("bx_Wm1_RB1out_S03_high","bx_Wm1_RB1out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S04_high = fs->make<TH2F>("bx_Wm1_RB1out_S04_high","bx_Wm1_RB1out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S05_high = fs->make<TH2F>("bx_Wm1_RB1out_S05_high","bx_Wm1_RB1out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S06_high = fs->make<TH2F>("bx_Wm1_RB1out_S06_high","bx_Wm1_RB1out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S07_high = fs->make<TH2F>("bx_Wm1_RB1out_S07_high","bx_Wm1_RB1out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S08_high = fs->make<TH2F>("bx_Wm1_RB1out_S08_high","bx_Wm1_RB1out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S09_high = fs->make<TH2F>("bx_Wm1_RB1out_S09_high","bx_Wm1_RB1out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S10_high = fs->make<TH2F>("bx_Wm1_RB1out_S10_high","bx_Wm1_RB1out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S11_high = fs->make<TH2F>("bx_Wm1_RB1out_S11_high","bx_Wm1_RB1out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S12_high = fs->make<TH2F>("bx_Wm1_RB1out_S12_high","bx_Wm1_RB1out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB1out_S01_high = fs->make<TH2F>("bx_W0_RB1out_S01_high","bx_W0_RB1out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S02_high = fs->make<TH2F>("bx_W0_RB1out_S02_high","bx_W0_RB1out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S03_high = fs->make<TH2F>("bx_W0_RB1out_S03_high","bx_W0_RB1out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S04_high = fs->make<TH2F>("bx_W0_RB1out_S04_high","bx_W0_RB1out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S05_high = fs->make<TH2F>("bx_W0_RB1out_S05_high","bx_W0_RB1out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S06_high = fs->make<TH2F>("bx_W0_RB1out_S06_high","bx_W0_RB1out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S07_high = fs->make<TH2F>("bx_W0_RB1out_S07_high","bx_W0_RB1out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S08_high = fs->make<TH2F>("bx_W0_RB1out_S08_high","bx_W0_RB1out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S09_high = fs->make<TH2F>("bx_W0_RB1out_S09_high","bx_W0_RB1out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S10_high = fs->make<TH2F>("bx_W0_RB1out_S10_high","bx_W0_RB1out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S11_high = fs->make<TH2F>("bx_W0_RB1out_S11_high","bx_W0_RB1out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S12_high = fs->make<TH2F>("bx_W0_RB1out_S12_high","bx_W0_RB1out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB1out_S01_high = fs->make<TH2F>("bx_Wp1_RB1out_S01_high","bx_Wp1_RB1out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S02_high = fs->make<TH2F>("bx_Wp1_RB1out_S02_high","bx_Wp1_RB1out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S03_high = fs->make<TH2F>("bx_Wp1_RB1out_S03_high","bx_Wp1_RB1out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S04_high = fs->make<TH2F>("bx_Wp1_RB1out_S04_high","bx_Wp1_RB1out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S05_high = fs->make<TH2F>("bx_Wp1_RB1out_S05_high","bx_Wp1_RB1out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S06_high = fs->make<TH2F>("bx_Wp1_RB1out_S06_high","bx_Wp1_RB1out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S07_high = fs->make<TH2F>("bx_Wp1_RB1out_S07_high","bx_Wp1_RB1out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S08_high = fs->make<TH2F>("bx_Wp1_RB1out_S08_high","bx_Wp1_RB1out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S09_high = fs->make<TH2F>("bx_Wp1_RB1out_S09_high","bx_Wp1_RB1out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S10_high = fs->make<TH2F>("bx_Wp1_RB1out_S10_high","bx_Wp1_RB1out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S11_high = fs->make<TH2F>("bx_Wp1_RB1out_S11_high","bx_Wp1_RB1out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S12_high = fs->make<TH2F>("bx_Wp1_RB1out_S12_high","bx_Wp1_RB1out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB1out_S01_high = fs->make<TH2F>("bx_Wp2_RB1out_S01_high","bx_Wp2_RB1out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S02_high = fs->make<TH2F>("bx_Wp2_RB1out_S02_high","bx_Wp2_RB1out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S03_high = fs->make<TH2F>("bx_Wp2_RB1out_S03_high","bx_Wp2_RB1out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S04_high = fs->make<TH2F>("bx_Wp2_RB1out_S04_high","bx_Wp2_RB1out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S05_high = fs->make<TH2F>("bx_Wp2_RB1out_S05_high","bx_Wp2_RB1out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S06_high = fs->make<TH2F>("bx_Wp2_RB1out_S06_high","bx_Wp2_RB1out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S07_high = fs->make<TH2F>("bx_Wp2_RB1out_S07_high","bx_Wp2_RB1out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S08_high = fs->make<TH2F>("bx_Wp2_RB1out_S08_high","bx_Wp2_RB1out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S09_high = fs->make<TH2F>("bx_Wp2_RB1out_S09_high","bx_Wp2_RB1out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S10_high = fs->make<TH2F>("bx_Wp2_RB1out_S10_high","bx_Wp2_RB1out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S11_high = fs->make<TH2F>("bx_Wp2_RB1out_S11_high","bx_Wp2_RB1out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S12_high = fs->make<TH2F>("bx_Wp2_RB1out_S12_high","bx_Wp2_RB1out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

// RB2in

bx_Wm2_RB2in_S01_high = fs->make<TH2F>("bx_Wm2_RB2in_S01_high","bx_Wm2_RB2in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S02_high = fs->make<TH2F>("bx_Wm2_RB2in_S02_high","bx_Wm2_RB2in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S03_high = fs->make<TH2F>("bx_Wm2_RB2in_S03_high","bx_Wm2_RB2in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S04_high = fs->make<TH2F>("bx_Wm2_RB2in_S04_high","bx_Wm2_RB2in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S05_high = fs->make<TH2F>("bx_Wm2_RB2in_S05_high","bx_Wm2_RB2in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S06_high = fs->make<TH2F>("bx_Wm2_RB2in_S06_high","bx_Wm2_RB2in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S07_high = fs->make<TH2F>("bx_Wm2_RB2in_S07_high","bx_Wm2_RB2in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S08_high = fs->make<TH2F>("bx_Wm2_RB2in_S08_high","bx_Wm2_RB2in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S09_high = fs->make<TH2F>("bx_Wm2_RB2in_S09_high","bx_Wm2_RB2in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S10_high = fs->make<TH2F>("bx_Wm2_RB2in_S10_high","bx_Wm2_RB2in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S11_high = fs->make<TH2F>("bx_Wm2_RB2in_S11_high","bx_Wm2_RB2in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S12_high = fs->make<TH2F>("bx_Wm2_RB2in_S12_high","bx_Wm2_RB2in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB2in_S01_high = fs->make<TH2F>("bx_Wm1_RB2in_S01_high","bx_Wm1_RB2in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S02_high = fs->make<TH2F>("bx_Wm1_RB2in_S02_high","bx_Wm1_RB2in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S03_high = fs->make<TH2F>("bx_Wm1_RB2in_S03_high","bx_Wm1_RB2in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S04_high = fs->make<TH2F>("bx_Wm1_RB2in_S04_high","bx_Wm1_RB2in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S05_high = fs->make<TH2F>("bx_Wm1_RB2in_S05_high","bx_Wm1_RB2in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S06_high = fs->make<TH2F>("bx_Wm1_RB2in_S06_high","bx_Wm1_RB2in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S07_high = fs->make<TH2F>("bx_Wm1_RB2in_S07_high","bx_Wm1_RB2in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S08_high = fs->make<TH2F>("bx_Wm1_RB2in_S08_high","bx_Wm1_RB2in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S09_high = fs->make<TH2F>("bx_Wm1_RB2in_S09_high","bx_Wm1_RB2in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S10_high = fs->make<TH2F>("bx_Wm1_RB2in_S10_high","bx_Wm1_RB2in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S11_high = fs->make<TH2F>("bx_Wm1_RB2in_S11_high","bx_Wm1_RB2in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S12_high = fs->make<TH2F>("bx_Wm1_RB2in_S12_high","bx_Wm1_RB2in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB2in_S01_high = fs->make<TH2F>("bx_W0_RB2in_S01_high","bx_W0_RB2in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S02_high = fs->make<TH2F>("bx_W0_RB2in_S02_high","bx_W0_RB2in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S03_high = fs->make<TH2F>("bx_W0_RB2in_S03_high","bx_W0_RB2in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S04_high = fs->make<TH2F>("bx_W0_RB2in_S04_high","bx_W0_RB2in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S05_high = fs->make<TH2F>("bx_W0_RB2in_S05_high","bx_W0_RB2in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S06_high = fs->make<TH2F>("bx_W0_RB2in_S06_high","bx_W0_RB2in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S07_high = fs->make<TH2F>("bx_W0_RB2in_S07_high","bx_W0_RB2in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S08_high = fs->make<TH2F>("bx_W0_RB2in_S08_high","bx_W0_RB2in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S09_high = fs->make<TH2F>("bx_W0_RB2in_S09_high","bx_W0_RB2in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S10_high = fs->make<TH2F>("bx_W0_RB2in_S10_high","bx_W0_RB2in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S11_high = fs->make<TH2F>("bx_W0_RB2in_S11_high","bx_W0_RB2in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S12_high = fs->make<TH2F>("bx_W0_RB2in_S12_high","bx_W0_RB2in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB2in_S01_high = fs->make<TH2F>("bx_Wp1_RB2in_S01_high","bx_Wp1_RB2in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S02_high = fs->make<TH2F>("bx_Wp1_RB2in_S02_high","bx_Wp1_RB2in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S03_high = fs->make<TH2F>("bx_Wp1_RB2in_S03_high","bx_Wp1_RB2in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S04_high = fs->make<TH2F>("bx_Wp1_RB2in_S04_high","bx_Wp1_RB2in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S05_high = fs->make<TH2F>("bx_Wp1_RB2in_S05_high","bx_Wp1_RB2in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S06_high = fs->make<TH2F>("bx_Wp1_RB2in_S06_high","bx_Wp1_RB2in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S07_high = fs->make<TH2F>("bx_Wp1_RB2in_S07_high","bx_Wp1_RB2in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S08_high = fs->make<TH2F>("bx_Wp1_RB2in_S08_high","bx_Wp1_RB2in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S09_high = fs->make<TH2F>("bx_Wp1_RB2in_S09_high","bx_Wp1_RB2in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S10_high = fs->make<TH2F>("bx_Wp1_RB2in_S10_high","bx_Wp1_RB2in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S11_high = fs->make<TH2F>("bx_Wp1_RB2in_S11_high","bx_Wp1_RB2in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S12_high = fs->make<TH2F>("bx_Wp1_RB2in_S12_high","bx_Wp1_RB2in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB2in_S01_high = fs->make<TH2F>("bx_Wp2_RB2in_S01_high","bx_Wp2_RB2in_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S02_high = fs->make<TH2F>("bx_Wp2_RB2in_S02_high","bx_Wp2_RB2in_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S03_high = fs->make<TH2F>("bx_Wp2_RB2in_S03_high","bx_Wp2_RB2in_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S04_high = fs->make<TH2F>("bx_Wp2_RB2in_S04_high","bx_Wp2_RB2in_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S05_high = fs->make<TH2F>("bx_Wp2_RB2in_S05_high","bx_Wp2_RB2in_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S06_high = fs->make<TH2F>("bx_Wp2_RB2in_S06_high","bx_Wp2_RB2in_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S07_high = fs->make<TH2F>("bx_Wp2_RB2in_S07_high","bx_Wp2_RB2in_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S08_high = fs->make<TH2F>("bx_Wp2_RB2in_S08_high","bx_Wp2_RB2in_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S09_high = fs->make<TH2F>("bx_Wp2_RB2in_S09_high","bx_Wp2_RB2in_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S10_high = fs->make<TH2F>("bx_Wp2_RB2in_S10_high","bx_Wp2_RB2in_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S11_high = fs->make<TH2F>("bx_Wp2_RB2in_S11_high","bx_Wp2_RB2in_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S12_high = fs->make<TH2F>("bx_Wp2_RB2in_S12_high","bx_Wp2_RB2in_S12_high",21,-0.5,20.5,11,-5.5,5.5);

// RB2out

bx_Wm2_RB2out_S01_high = fs->make<TH2F>("bx_Wm2_RB2out_S01_high","bx_Wm2_RB2out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S02_high = fs->make<TH2F>("bx_Wm2_RB2out_S02_high","bx_Wm2_RB2out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S03_high = fs->make<TH2F>("bx_Wm2_RB2out_S03_high","bx_Wm2_RB2out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S04_high = fs->make<TH2F>("bx_Wm2_RB2out_S04_high","bx_Wm2_RB2out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S05_high = fs->make<TH2F>("bx_Wm2_RB2out_S05_high","bx_Wm2_RB2out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S06_high = fs->make<TH2F>("bx_Wm2_RB2out_S06_high","bx_Wm2_RB2out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S07_high = fs->make<TH2F>("bx_Wm2_RB2out_S07_high","bx_Wm2_RB2out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S08_high = fs->make<TH2F>("bx_Wm2_RB2out_S08_high","bx_Wm2_RB2out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S09_high = fs->make<TH2F>("bx_Wm2_RB2out_S09_high","bx_Wm2_RB2out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S10_high = fs->make<TH2F>("bx_Wm2_RB2out_S10_high","bx_Wm2_RB2out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S11_high = fs->make<TH2F>("bx_Wm2_RB2out_S11_high","bx_Wm2_RB2out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S12_high = fs->make<TH2F>("bx_Wm2_RB2out_S12_high","bx_Wm2_RB2out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB2out_S01_high = fs->make<TH2F>("bx_Wm1_RB2out_S01_high","bx_Wm1_RB2out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S02_high = fs->make<TH2F>("bx_Wm1_RB2out_S02_high","bx_Wm1_RB2out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S03_high = fs->make<TH2F>("bx_Wm1_RB2out_S03_high","bx_Wm1_RB2out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S04_high = fs->make<TH2F>("bx_Wm1_RB2out_S04_high","bx_Wm1_RB2out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S05_high = fs->make<TH2F>("bx_Wm1_RB2out_S05_high","bx_Wm1_RB2out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S06_high = fs->make<TH2F>("bx_Wm1_RB2out_S06_high","bx_Wm1_RB2out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S07_high = fs->make<TH2F>("bx_Wm1_RB2out_S07_high","bx_Wm1_RB2out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S08_high = fs->make<TH2F>("bx_Wm1_RB2out_S08_high","bx_Wm1_RB2out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S09_high = fs->make<TH2F>("bx_Wm1_RB2out_S09_high","bx_Wm1_RB2out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S10_high = fs->make<TH2F>("bx_Wm1_RB2out_S10_high","bx_Wm1_RB2out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S11_high = fs->make<TH2F>("bx_Wm1_RB2out_S11_high","bx_Wm1_RB2out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S12_high = fs->make<TH2F>("bx_Wm1_RB2out_S12_high","bx_Wm1_RB2out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB2out_S01_high = fs->make<TH2F>("bx_W0_RB2out_S01_high","bx_W0_RB2out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S02_high = fs->make<TH2F>("bx_W0_RB2out_S02_high","bx_W0_RB2out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S03_high = fs->make<TH2F>("bx_W0_RB2out_S03_high","bx_W0_RB2out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S04_high = fs->make<TH2F>("bx_W0_RB2out_S04_high","bx_W0_RB2out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S05_high = fs->make<TH2F>("bx_W0_RB2out_S05_high","bx_W0_RB2out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S06_high = fs->make<TH2F>("bx_W0_RB2out_S06_high","bx_W0_RB2out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S07_high = fs->make<TH2F>("bx_W0_RB2out_S07_high","bx_W0_RB2out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S08_high = fs->make<TH2F>("bx_W0_RB2out_S08_high","bx_W0_RB2out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S09_high = fs->make<TH2F>("bx_W0_RB2out_S09_high","bx_W0_RB2out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S10_high = fs->make<TH2F>("bx_W0_RB2out_S10_high","bx_W0_RB2out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S11_high = fs->make<TH2F>("bx_W0_RB2out_S11_high","bx_W0_RB2out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S12_high = fs->make<TH2F>("bx_W0_RB2out_S12_high","bx_W0_RB2out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB2out_S01_high = fs->make<TH2F>("bx_Wp1_RB2out_S01_high","bx_Wp1_RB2out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S02_high = fs->make<TH2F>("bx_Wp1_RB2out_S02_high","bx_Wp1_RB2out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S03_high = fs->make<TH2F>("bx_Wp1_RB2out_S03_high","bx_Wp1_RB2out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S04_high = fs->make<TH2F>("bx_Wp1_RB2out_S04_high","bx_Wp1_RB2out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S05_high = fs->make<TH2F>("bx_Wp1_RB2out_S05_high","bx_Wp1_RB2out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S06_high = fs->make<TH2F>("bx_Wp1_RB2out_S06_high","bx_Wp1_RB2out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S07_high = fs->make<TH2F>("bx_Wp1_RB2out_S07_high","bx_Wp1_RB2out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S08_high = fs->make<TH2F>("bx_Wp1_RB2out_S08_high","bx_Wp1_RB2out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S09_high = fs->make<TH2F>("bx_Wp1_RB2out_S09_high","bx_Wp1_RB2out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S10_high = fs->make<TH2F>("bx_Wp1_RB2out_S10_high","bx_Wp1_RB2out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S11_high = fs->make<TH2F>("bx_Wp1_RB2out_S11_high","bx_Wp1_RB2out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S12_high = fs->make<TH2F>("bx_Wp1_RB2out_S12_high","bx_Wp1_RB2out_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB2out_S01_high = fs->make<TH2F>("bx_Wp2_RB2out_S01_high","bx_Wp2_RB2out_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S02_high = fs->make<TH2F>("bx_Wp2_RB2out_S02_high","bx_Wp2_RB2out_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S03_high = fs->make<TH2F>("bx_Wp2_RB2out_S03_high","bx_Wp2_RB2out_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S04_high = fs->make<TH2F>("bx_Wp2_RB2out_S04_high","bx_Wp2_RB2out_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S05_high = fs->make<TH2F>("bx_Wp2_RB2out_S05_high","bx_Wp2_RB2out_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S06_high = fs->make<TH2F>("bx_Wp2_RB2out_S06_high","bx_Wp2_RB2out_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S07_high = fs->make<TH2F>("bx_Wp2_RB2out_S07_high","bx_Wp2_RB2out_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S08_high = fs->make<TH2F>("bx_Wp2_RB2out_S08_high","bx_Wp2_RB2out_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S09_high = fs->make<TH2F>("bx_Wp2_RB2out_S09_high","bx_Wp2_RB2out_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S10_high = fs->make<TH2F>("bx_Wp2_RB2out_S10_high","bx_Wp2_RB2out_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S11_high = fs->make<TH2F>("bx_Wp2_RB2out_S11_high","bx_Wp2_RB2out_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S12_high = fs->make<TH2F>("bx_Wp2_RB2out_S12_high","bx_Wp2_RB2out_S12_high",21,-0.5,20.5,11,-5.5,5.5);


// RB3

bx_Wm2_RB3_S01_high = fs->make<TH2F>("bx_Wm2_RB3_S01_high","bx_Wm2_RB3_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S02_high = fs->make<TH2F>("bx_Wm2_RB3_S02_high","bx_Wm2_RB3_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S03_high = fs->make<TH2F>("bx_Wm2_RB3_S03_high","bx_Wm2_RB3_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S04_high = fs->make<TH2F>("bx_Wm2_RB3_S04_high","bx_Wm2_RB3_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S05_high = fs->make<TH2F>("bx_Wm2_RB3_S05_high","bx_Wm2_RB3_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S06_high = fs->make<TH2F>("bx_Wm2_RB3_S06_high","bx_Wm2_RB3_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S07_high = fs->make<TH2F>("bx_Wm2_RB3_S07_high","bx_Wm2_RB3_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S08_high = fs->make<TH2F>("bx_Wm2_RB3_S08_high","bx_Wm2_RB3_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S09_high = fs->make<TH2F>("bx_Wm2_RB3_S09_high","bx_Wm2_RB3_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S10_high = fs->make<TH2F>("bx_Wm2_RB3_S10_high","bx_Wm2_RB3_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S11_high = fs->make<TH2F>("bx_Wm2_RB3_S11_high","bx_Wm2_RB3_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S12_high = fs->make<TH2F>("bx_Wm2_RB3_S12_high","bx_Wm2_RB3_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB3_S01_high = fs->make<TH2F>("bx_Wm1_RB3_S01_high","bx_Wm1_RB3_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S02_high = fs->make<TH2F>("bx_Wm1_RB3_S02_high","bx_Wm1_RB3_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S03_high = fs->make<TH2F>("bx_Wm1_RB3_S03_high","bx_Wm1_RB3_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S04_high = fs->make<TH2F>("bx_Wm1_RB3_S04_high","bx_Wm1_RB3_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S05_high = fs->make<TH2F>("bx_Wm1_RB3_S05_high","bx_Wm1_RB3_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S06_high = fs->make<TH2F>("bx_Wm1_RB3_S06_high","bx_Wm1_RB3_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S07_high = fs->make<TH2F>("bx_Wm1_RB3_S07_high","bx_Wm1_RB3_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S08_high = fs->make<TH2F>("bx_Wm1_RB3_S08_high","bx_Wm1_RB3_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S09_high = fs->make<TH2F>("bx_Wm1_RB3_S09_high","bx_Wm1_RB3_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S10_high = fs->make<TH2F>("bx_Wm1_RB3_S10_high","bx_Wm1_RB3_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S11_high = fs->make<TH2F>("bx_Wm1_RB3_S11_high","bx_Wm1_RB3_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S12_high = fs->make<TH2F>("bx_Wm1_RB3_S12_high","bx_Wm1_RB3_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB3_S01_high = fs->make<TH2F>("bx_W0_RB3_S01_high","bx_W0_RB3_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S02_high = fs->make<TH2F>("bx_W0_RB3_S02_high","bx_W0_RB3_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S03_high = fs->make<TH2F>("bx_W0_RB3_S03_high","bx_W0_RB3_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S04_high = fs->make<TH2F>("bx_W0_RB3_S04_high","bx_W0_RB3_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S05_high = fs->make<TH2F>("bx_W0_RB3_S05_high","bx_W0_RB3_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S06_high = fs->make<TH2F>("bx_W0_RB3_S06_high","bx_W0_RB3_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S07_high = fs->make<TH2F>("bx_W0_RB3_S07_high","bx_W0_RB3_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S08_high = fs->make<TH2F>("bx_W0_RB3_S08_high","bx_W0_RB3_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S09_high = fs->make<TH2F>("bx_W0_RB3_S09_high","bx_W0_RB3_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S10_high = fs->make<TH2F>("bx_W0_RB3_S10_high","bx_W0_RB3_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S11_high = fs->make<TH2F>("bx_W0_RB3_S11_high","bx_W0_RB3_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S12_high = fs->make<TH2F>("bx_W0_RB3_S12_high","bx_W0_RB3_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB3_S01_high = fs->make<TH2F>("bx_Wp1_RB3_S01_high","bx_Wp1_RB3_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S02_high = fs->make<TH2F>("bx_Wp1_RB3_S02_high","bx_Wp1_RB3_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S03_high = fs->make<TH2F>("bx_Wp1_RB3_S03_high","bx_Wp1_RB3_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S04_high = fs->make<TH2F>("bx_Wp1_RB3_S04_high","bx_Wp1_RB3_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S05_high = fs->make<TH2F>("bx_Wp1_RB3_S05_high","bx_Wp1_RB3_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S06_high = fs->make<TH2F>("bx_Wp1_RB3_S06_high","bx_Wp1_RB3_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S07_high = fs->make<TH2F>("bx_Wp1_RB3_S07_high","bx_Wp1_RB3_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S08_high = fs->make<TH2F>("bx_Wp1_RB3_S08_high","bx_Wp1_RB3_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S09_high = fs->make<TH2F>("bx_Wp1_RB3_S09_high","bx_Wp1_RB3_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S10_high = fs->make<TH2F>("bx_Wp1_RB3_S10_high","bx_Wp1_RB3_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S11_high = fs->make<TH2F>("bx_Wp1_RB3_S11_high","bx_Wp1_RB3_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S12_high = fs->make<TH2F>("bx_Wp1_RB3_S12_high","bx_Wp1_RB3_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB3_S01_high = fs->make<TH2F>("bx_Wp2_RB3_S01_high","bx_Wp2_RB3_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S02_high = fs->make<TH2F>("bx_Wp2_RB3_S02_high","bx_Wp2_RB3_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S03_high = fs->make<TH2F>("bx_Wp2_RB3_S03_high","bx_Wp2_RB3_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S04_high = fs->make<TH2F>("bx_Wp2_RB3_S04_high","bx_Wp2_RB3_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S05_high = fs->make<TH2F>("bx_Wp2_RB3_S05_high","bx_Wp2_RB3_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S06_high = fs->make<TH2F>("bx_Wp2_RB3_S06_high","bx_Wp2_RB3_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S07_high = fs->make<TH2F>("bx_Wp2_RB3_S07_high","bx_Wp2_RB3_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S08_high = fs->make<TH2F>("bx_Wp2_RB3_S08_high","bx_Wp2_RB3_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S09_high = fs->make<TH2F>("bx_Wp2_RB3_S09_high","bx_Wp2_RB3_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S10_high = fs->make<TH2F>("bx_Wp2_RB3_S10_high","bx_Wp2_RB3_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S11_high = fs->make<TH2F>("bx_Wp2_RB3_S11_high","bx_Wp2_RB3_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S12_high = fs->make<TH2F>("bx_Wp2_RB3_S12_high","bx_Wp2_RB3_S12_high",21,-0.5,20.5,11,-5.5,5.5);

// RB4

bx_Wm2_RB4_S01_high = fs->make<TH2F>("bx_Wm2_RB4_S01_high","bx_Wm2_RB4_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S02_high = fs->make<TH2F>("bx_Wm2_RB4_S02_high","bx_Wm2_RB4_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S03_high = fs->make<TH2F>("bx_Wm2_RB4_S03_high","bx_Wm2_RB4_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S04_high = fs->make<TH2F>("bx_Wm2_RB4_S04_high","bx_Wm2_RB4_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S05_high = fs->make<TH2F>("bx_Wm2_RB4_S05_high","bx_Wm2_RB4_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S06_high = fs->make<TH2F>("bx_Wm2_RB4_S06_high","bx_Wm2_RB4_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S07_high = fs->make<TH2F>("bx_Wm2_RB4_S07_high","bx_Wm2_RB4_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S08_high = fs->make<TH2F>("bx_Wm2_RB4_S08_high","bx_Wm2_RB4_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S09_high = fs->make<TH2F>("bx_Wm2_RB4_S09_high","bx_Wm2_RB4_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S10_high = fs->make<TH2F>("bx_Wm2_RB4_S10_high","bx_Wm2_RB4_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S11_high = fs->make<TH2F>("bx_Wm2_RB4_S11_high","bx_Wm2_RB4_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S12_high = fs->make<TH2F>("bx_Wm2_RB4_S12_high","bx_Wm2_RB4_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB4_S01_high = fs->make<TH2F>("bx_Wm1_RB4_S01_high","bx_Wm1_RB4_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S02_high = fs->make<TH2F>("bx_Wm1_RB4_S02_high","bx_Wm1_RB4_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S03_high = fs->make<TH2F>("bx_Wm1_RB4_S03_high","bx_Wm1_RB4_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S04_high = fs->make<TH2F>("bx_Wm1_RB4_S04_high","bx_Wm1_RB4_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S05_high = fs->make<TH2F>("bx_Wm1_RB4_S05_high","bx_Wm1_RB4_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S06_high = fs->make<TH2F>("bx_Wm1_RB4_S06_high","bx_Wm1_RB4_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S07_high = fs->make<TH2F>("bx_Wm1_RB4_S07_high","bx_Wm1_RB4_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S08_high = fs->make<TH2F>("bx_Wm1_RB4_S08_high","bx_Wm1_RB4_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S09_high = fs->make<TH2F>("bx_Wm1_RB4_S09_high","bx_Wm1_RB4_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S10_high = fs->make<TH2F>("bx_Wm1_RB4_S10_high","bx_Wm1_RB4_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S11_high = fs->make<TH2F>("bx_Wm1_RB4_S11_high","bx_Wm1_RB4_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S12_high = fs->make<TH2F>("bx_Wm1_RB4_S12_high","bx_Wm1_RB4_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB4_S01_high = fs->make<TH2F>("bx_W0_RB4_S01_high","bx_W0_RB4_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S02_high = fs->make<TH2F>("bx_W0_RB4_S02_high","bx_W0_RB4_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S03_high = fs->make<TH2F>("bx_W0_RB4_S03_high","bx_W0_RB4_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S04_high = fs->make<TH2F>("bx_W0_RB4_S04_high","bx_W0_RB4_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S05_high = fs->make<TH2F>("bx_W0_RB4_S05_high","bx_W0_RB4_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S06_high = fs->make<TH2F>("bx_W0_RB4_S06_high","bx_W0_RB4_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S07_high = fs->make<TH2F>("bx_W0_RB4_S07_high","bx_W0_RB4_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S08_high = fs->make<TH2F>("bx_W0_RB4_S08_high","bx_W0_RB4_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S09_high = fs->make<TH2F>("bx_W0_RB4_S09_high","bx_W0_RB4_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S10_high = fs->make<TH2F>("bx_W0_RB4_S10_high","bx_W0_RB4_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S11_high = fs->make<TH2F>("bx_W0_RB4_S11_high","bx_W0_RB4_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S12_high = fs->make<TH2F>("bx_W0_RB4_S12_high","bx_W0_RB4_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB4_S01_high = fs->make<TH2F>("bx_Wp1_RB4_S01_high","bx_Wp1_RB4_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S02_high = fs->make<TH2F>("bx_Wp1_RB4_S02_high","bx_Wp1_RB4_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S03_high = fs->make<TH2F>("bx_Wp1_RB4_S03_high","bx_Wp1_RB4_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S04_high = fs->make<TH2F>("bx_Wp1_RB4_S04_high","bx_Wp1_RB4_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S05_high = fs->make<TH2F>("bx_Wp1_RB4_S05_high","bx_Wp1_RB4_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S06_high = fs->make<TH2F>("bx_Wp1_RB4_S06_high","bx_Wp1_RB4_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S07_high = fs->make<TH2F>("bx_Wp1_RB4_S07_high","bx_Wp1_RB4_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S08_high = fs->make<TH2F>("bx_Wp1_RB4_S08_high","bx_Wp1_RB4_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S09_high = fs->make<TH2F>("bx_Wp1_RB4_S09_high","bx_Wp1_RB4_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S10_high = fs->make<TH2F>("bx_Wp1_RB4_S10_high","bx_Wp1_RB4_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S11_high = fs->make<TH2F>("bx_Wp1_RB4_S11_high","bx_Wp1_RB4_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S12_high = fs->make<TH2F>("bx_Wp1_RB4_S12_high","bx_Wp1_RB4_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB4_S01_high = fs->make<TH2F>("bx_Wp2_RB4_S01_high","bx_Wp2_RB4_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S02_high = fs->make<TH2F>("bx_Wp2_RB4_S02_high","bx_Wp2_RB4_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S03_high = fs->make<TH2F>("bx_Wp2_RB4_S03_high","bx_Wp2_RB4_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S04_high = fs->make<TH2F>("bx_Wp2_RB4_S04_high","bx_Wp2_RB4_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S05_high = fs->make<TH2F>("bx_Wp2_RB4_S05_high","bx_Wp2_RB4_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S06_high = fs->make<TH2F>("bx_Wp2_RB4_S06_high","bx_Wp2_RB4_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S07_high = fs->make<TH2F>("bx_Wp2_RB4_S07_high","bx_Wp2_RB4_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S08_high = fs->make<TH2F>("bx_Wp2_RB4_S08_high","bx_Wp2_RB4_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S09_high = fs->make<TH2F>("bx_Wp2_RB4_S09_high","bx_Wp2_RB4_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S10_high = fs->make<TH2F>("bx_Wp2_RB4_S10_high","bx_Wp2_RB4_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S11_high = fs->make<TH2F>("bx_Wp2_RB4_S11_high","bx_Wp2_RB4_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S12_high = fs->make<TH2F>("bx_Wp2_RB4_S12_high","bx_Wp2_RB4_S12_high",21,-0.5,20.5,11,-5.5,5.5);

//endcap +
bx_REp42_S01_high = fs->make<TH2F>("bx_REp42_S01_high","bx_REp42_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S02_high = fs->make<TH2F>("bx_REp42_S02_high","bx_REp42_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S03_high = fs->make<TH2F>("bx_REp42_S03_high","bx_REp42_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S04_high = fs->make<TH2F>("bx_REp42_S04_high","bx_REp42_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S05_high = fs->make<TH2F>("bx_REp42_S05_high","bx_REp42_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S06_high = fs->make<TH2F>("bx_REp42_S06_high","bx_REp42_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S07_high = fs->make<TH2F>("bx_REp42_S07_high","bx_REp42_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S08_high = fs->make<TH2F>("bx_REp42_S08_high","bx_REp42_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S09_high = fs->make<TH2F>("bx_REp42_S09_high","bx_REp42_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S10_high = fs->make<TH2F>("bx_REp42_S10_high","bx_REp42_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S11_high = fs->make<TH2F>("bx_REp42_S11_high","bx_REp42_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S12_high = fs->make<TH2F>("bx_REp42_S12_high","bx_REp42_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S01_high = fs->make<TH2F>("bx_REp43_S01_high","bx_REp43_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S02_high = fs->make<TH2F>("bx_REp43_S02_high","bx_REp43_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S03_high = fs->make<TH2F>("bx_REp43_S03_high","bx_REp43_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S04_high = fs->make<TH2F>("bx_REp43_S04_high","bx_REp43_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S05_high = fs->make<TH2F>("bx_REp43_S05_high","bx_REp43_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S06_high = fs->make<TH2F>("bx_REp43_S06_high","bx_REp43_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S07_high = fs->make<TH2F>("bx_REp43_S07_high","bx_REp43_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S08_high = fs->make<TH2F>("bx_REp43_S08_high","bx_REp43_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S09_high = fs->make<TH2F>("bx_REp43_S09_high","bx_REp43_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S10_high = fs->make<TH2F>("bx_REp43_S10_high","bx_REp43_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S11_high = fs->make<TH2F>("bx_REp43_S11_high","bx_REp43_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S12_high = fs->make<TH2F>("bx_REp43_S12_high","bx_REp43_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_REp32_S01_high = fs->make<TH2F>("bx_REp32_S01_high","bx_REp32_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S02_high = fs->make<TH2F>("bx_REp32_S02_high","bx_REp32_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S03_high = fs->make<TH2F>("bx_REp32_S03_high","bx_REp32_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S04_high = fs->make<TH2F>("bx_REp32_S04_high","bx_REp32_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S05_high = fs->make<TH2F>("bx_REp32_S05_high","bx_REp32_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S06_high = fs->make<TH2F>("bx_REp32_S06_high","bx_REp32_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S07_high = fs->make<TH2F>("bx_REp32_S07_high","bx_REp32_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S08_high = fs->make<TH2F>("bx_REp32_S08_high","bx_REp32_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S09_high = fs->make<TH2F>("bx_REp32_S09_high","bx_REp32_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S10_high = fs->make<TH2F>("bx_REp32_S10_high","bx_REp32_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S11_high = fs->make<TH2F>("bx_REp32_S11_high","bx_REp32_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S12_high = fs->make<TH2F>("bx_REp32_S12_high","bx_REp32_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S01_high = fs->make<TH2F>("bx_REp33_S01_high","bx_REp33_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S02_high = fs->make<TH2F>("bx_REp33_S02_high","bx_REp33_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S03_high = fs->make<TH2F>("bx_REp33_S03_high","bx_REp33_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S04_high = fs->make<TH2F>("bx_REp33_S04_high","bx_REp33_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S05_high = fs->make<TH2F>("bx_REp33_S05_high","bx_REp33_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S06_high = fs->make<TH2F>("bx_REp33_S06_high","bx_REp33_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S07_high = fs->make<TH2F>("bx_REp33_S07_high","bx_REp33_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S08_high = fs->make<TH2F>("bx_REp33_S08_high","bx_REp33_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S09_high = fs->make<TH2F>("bx_REp33_S09_high","bx_REp33_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S10_high = fs->make<TH2F>("bx_REp33_S10_high","bx_REp33_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S11_high = fs->make<TH2F>("bx_REp33_S11_high","bx_REp33_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S12_high = fs->make<TH2F>("bx_REp33_S12_high","bx_REp33_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_REp22_S01_high = fs->make<TH2F>("bx_REp22_S01_high","bx_REp22_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S02_high = fs->make<TH2F>("bx_REp22_S02_high","bx_REp22_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S03_high = fs->make<TH2F>("bx_REp22_S03_high","bx_REp22_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S04_high = fs->make<TH2F>("bx_REp22_S04_high","bx_REp22_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S05_high = fs->make<TH2F>("bx_REp22_S05_high","bx_REp22_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S06_high = fs->make<TH2F>("bx_REp22_S06_high","bx_REp22_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S07_high = fs->make<TH2F>("bx_REp22_S07_high","bx_REp22_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S08_high = fs->make<TH2F>("bx_REp22_S08_high","bx_REp22_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S09_high = fs->make<TH2F>("bx_REp22_S09_high","bx_REp22_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S10_high = fs->make<TH2F>("bx_REp22_S10_high","bx_REp22_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S11_high = fs->make<TH2F>("bx_REp22_S11_high","bx_REp22_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S12_high = fs->make<TH2F>("bx_REp22_S12_high","bx_REp22_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S01_high = fs->make<TH2F>("bx_REp23_S01_high","bx_REp23_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S02_high = fs->make<TH2F>("bx_REp23_S02_high","bx_REp23_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S03_high = fs->make<TH2F>("bx_REp23_S03_high","bx_REp23_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S04_high = fs->make<TH2F>("bx_REp23_S04_high","bx_REp23_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S05_high = fs->make<TH2F>("bx_REp23_S05_high","bx_REp23_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S06_high = fs->make<TH2F>("bx_REp23_S06_high","bx_REp23_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S07_high = fs->make<TH2F>("bx_REp23_S07_high","bx_REp23_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S08_high = fs->make<TH2F>("bx_REp23_S08_high","bx_REp23_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S09_high = fs->make<TH2F>("bx_REp23_S09_high","bx_REp23_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S10_high = fs->make<TH2F>("bx_REp23_S10_high","bx_REp23_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S11_high = fs->make<TH2F>("bx_REp23_S11_high","bx_REp23_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S12_high = fs->make<TH2F>("bx_REp23_S12_high","bx_REp23_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_REp12_S01_high = fs->make<TH2F>("bx_REp12_S01_high","bx_REp12_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S02_high = fs->make<TH2F>("bx_REp12_S02_high","bx_REp12_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S03_high = fs->make<TH2F>("bx_REp12_S03_high","bx_REp12_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S04_high = fs->make<TH2F>("bx_REp12_S04_high","bx_REp12_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S05_high = fs->make<TH2F>("bx_REp12_S05_high","bx_REp12_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S06_high = fs->make<TH2F>("bx_REp12_S06_high","bx_REp12_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S07_high = fs->make<TH2F>("bx_REp12_S07_high","bx_REp12_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S08_high = fs->make<TH2F>("bx_REp12_S08_high","bx_REp12_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S09_high = fs->make<TH2F>("bx_REp12_S09_high","bx_REp12_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S10_high = fs->make<TH2F>("bx_REp12_S10_high","bx_REp12_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S11_high = fs->make<TH2F>("bx_REp12_S11_high","bx_REp12_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S12_high = fs->make<TH2F>("bx_REp12_S12_high","bx_REp12_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S01_high = fs->make<TH2F>("bx_REp13_S01_high","bx_REp13_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S02_high = fs->make<TH2F>("bx_REp13_S02_high","bx_REp13_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S03_high = fs->make<TH2F>("bx_REp13_S03_high","bx_REp13_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S04_high = fs->make<TH2F>("bx_REp13_S04_high","bx_REp13_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S05_high = fs->make<TH2F>("bx_REp13_S05_high","bx_REp13_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S06_high = fs->make<TH2F>("bx_REp13_S06_high","bx_REp13_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S07_high = fs->make<TH2F>("bx_REp13_S07_high","bx_REp13_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S08_high = fs->make<TH2F>("bx_REp13_S08_high","bx_REp13_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S09_high = fs->make<TH2F>("bx_REp13_S09_high","bx_REp13_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S10_high = fs->make<TH2F>("bx_REp13_S10_high","bx_REp13_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S11_high = fs->make<TH2F>("bx_REp13_S11_high","bx_REp13_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S12_high = fs->make<TH2F>("bx_REp13_S12_high","bx_REp13_S12_high",21,-0.5,20.5,11,-5.5,5.5);

// endcap -

bx_REm42_S01_high = fs->make<TH2F>("bx_REm42_S01_high","bx_REm42_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S02_high = fs->make<TH2F>("bx_REm42_S02_high","bx_REm42_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S03_high = fs->make<TH2F>("bx_REm42_S03_high","bx_REm42_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S04_high = fs->make<TH2F>("bx_REm42_S04_high","bx_REm42_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S05_high = fs->make<TH2F>("bx_REm42_S05_high","bx_REm42_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S06_high = fs->make<TH2F>("bx_REm42_S06_high","bx_REm42_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S07_high = fs->make<TH2F>("bx_REm42_S07_high","bx_REm42_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S08_high = fs->make<TH2F>("bx_REm42_S08_high","bx_REm42_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S09_high = fs->make<TH2F>("bx_REm42_S09_high","bx_REm42_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S10_high = fs->make<TH2F>("bx_REm42_S10_high","bx_REm42_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S11_high = fs->make<TH2F>("bx_REm42_S11_high","bx_REm42_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S12_high = fs->make<TH2F>("bx_REm42_S12_high","bx_REm42_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S01_high = fs->make<TH2F>("bx_REm43_S01_high","bx_REm43_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S02_high = fs->make<TH2F>("bx_REm43_S02_high","bx_REm43_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S03_high = fs->make<TH2F>("bx_REm43_S03_high","bx_REm43_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S04_high = fs->make<TH2F>("bx_REm43_S04_high","bx_REm43_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S05_high = fs->make<TH2F>("bx_REm43_S05_high","bx_REm43_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S06_high = fs->make<TH2F>("bx_REm43_S06_high","bx_REm43_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S07_high = fs->make<TH2F>("bx_REm43_S07_high","bx_REm43_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S08_high = fs->make<TH2F>("bx_REm43_S08_high","bx_REm43_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S09_high = fs->make<TH2F>("bx_REm43_S09_high","bx_REm43_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S10_high = fs->make<TH2F>("bx_REm43_S10_high","bx_REm43_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S11_high = fs->make<TH2F>("bx_REm43_S11_high","bx_REm43_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S12_high = fs->make<TH2F>("bx_REm43_S12_high","bx_REm43_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_REm32_S01_high = fs->make<TH2F>("bx_REm32_S01_high","bx_REm32_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S02_high = fs->make<TH2F>("bx_REm32_S02_high","bx_REm32_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S03_high = fs->make<TH2F>("bx_REm32_S03_high","bx_REm32_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S04_high = fs->make<TH2F>("bx_REm32_S04_high","bx_REm32_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S05_high = fs->make<TH2F>("bx_REm32_S05_high","bx_REm32_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S06_high = fs->make<TH2F>("bx_REm32_S06_high","bx_REm32_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S07_high = fs->make<TH2F>("bx_REm32_S07_high","bx_REm32_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S08_high = fs->make<TH2F>("bx_REm32_S08_high","bx_REm32_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S09_high = fs->make<TH2F>("bx_REm32_S09_high","bx_REm32_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S10_high = fs->make<TH2F>("bx_REm32_S10_high","bx_REm32_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S11_high = fs->make<TH2F>("bx_REm32_S11_high","bx_REm32_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S12_high = fs->make<TH2F>("bx_REm32_S12_high","bx_REm32_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S01_high = fs->make<TH2F>("bx_REm33_S01_high","bx_REm33_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S02_high = fs->make<TH2F>("bx_REm33_S02_high","bx_REm33_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S03_high = fs->make<TH2F>("bx_REm33_S03_high","bx_REm33_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S04_high = fs->make<TH2F>("bx_REm33_S04_high","bx_REm33_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S05_high = fs->make<TH2F>("bx_REm33_S05_high","bx_REm33_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S06_high = fs->make<TH2F>("bx_REm33_S06_high","bx_REm33_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S07_high = fs->make<TH2F>("bx_REm33_S07_high","bx_REm33_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S08_high = fs->make<TH2F>("bx_REm33_S08_high","bx_REm33_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S09_high = fs->make<TH2F>("bx_REm33_S09_high","bx_REm33_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S10_high = fs->make<TH2F>("bx_REm33_S10_high","bx_REm33_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S11_high = fs->make<TH2F>("bx_REm33_S11_high","bx_REm33_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S12_high = fs->make<TH2F>("bx_REm33_S12_high","bx_REm33_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_REm22_S01_high = fs->make<TH2F>("bx_REm22_S01_high","bx_REm22_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S02_high = fs->make<TH2F>("bx_REm22_S02_high","bx_REm22_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S03_high = fs->make<TH2F>("bx_REm22_S03_high","bx_REm22_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S04_high = fs->make<TH2F>("bx_REm22_S04_high","bx_REm22_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S05_high = fs->make<TH2F>("bx_REm22_S05_high","bx_REm22_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S06_high = fs->make<TH2F>("bx_REm22_S06_high","bx_REm22_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S07_high = fs->make<TH2F>("bx_REm22_S07_high","bx_REm22_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S08_high = fs->make<TH2F>("bx_REm22_S08_high","bx_REm22_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S09_high = fs->make<TH2F>("bx_REm22_S09_high","bx_REm22_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S10_high = fs->make<TH2F>("bx_REm22_S10_high","bx_REm22_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S11_high = fs->make<TH2F>("bx_REm22_S11_high","bx_REm22_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S12_high = fs->make<TH2F>("bx_REm22_S12_high","bx_REm22_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S01_high = fs->make<TH2F>("bx_REm23_S01_high","bx_REm23_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S02_high = fs->make<TH2F>("bx_REm23_S02_high","bx_REm23_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S03_high = fs->make<TH2F>("bx_REm23_S03_high","bx_REm23_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S04_high = fs->make<TH2F>("bx_REm23_S04_high","bx_REm23_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S05_high = fs->make<TH2F>("bx_REm23_S05_high","bx_REm23_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S06_high = fs->make<TH2F>("bx_REm23_S06_high","bx_REm23_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S07_high = fs->make<TH2F>("bx_REm23_S07_high","bx_REm23_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S08_high = fs->make<TH2F>("bx_REm23_S08_high","bx_REm23_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S09_high = fs->make<TH2F>("bx_REm23_S09_high","bx_REm23_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S10_high = fs->make<TH2F>("bx_REm23_S10_high","bx_REm23_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S11_high = fs->make<TH2F>("bx_REm23_S11_high","bx_REm23_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S12_high = fs->make<TH2F>("bx_REm23_S12_high","bx_REm23_S12_high",21,-0.5,20.5,11,-5.5,5.5);

bx_REm12_S01_high = fs->make<TH2F>("bx_REm12_S01_high","bx_REm12_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S02_high = fs->make<TH2F>("bx_REm12_S02_high","bx_REm12_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S03_high = fs->make<TH2F>("bx_REm12_S03_high","bx_REm12_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S04_high = fs->make<TH2F>("bx_REm12_S04_high","bx_REm12_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S05_high = fs->make<TH2F>("bx_REm12_S05_high","bx_REm12_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S06_high = fs->make<TH2F>("bx_REm12_S06_high","bx_REm12_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S07_high = fs->make<TH2F>("bx_REm12_S07_high","bx_REm12_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S08_high = fs->make<TH2F>("bx_REm12_S08_high","bx_REm12_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S09_high = fs->make<TH2F>("bx_REm12_S09_high","bx_REm12_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S10_high = fs->make<TH2F>("bx_REm12_S10_high","bx_REm12_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S11_high = fs->make<TH2F>("bx_REm12_S11_high","bx_REm12_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S12_high = fs->make<TH2F>("bx_REm12_S12_high","bx_REm12_S12_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S01_high = fs->make<TH2F>("bx_REm13_S01_high","bx_REm13_S01_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S02_high = fs->make<TH2F>("bx_REm13_S02_high","bx_REm13_S02_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S03_high = fs->make<TH2F>("bx_REm13_S03_high","bx_REm13_S03_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S04_high = fs->make<TH2F>("bx_REm13_S04_high","bx_REm13_S04_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S05_high = fs->make<TH2F>("bx_REm13_S05_high","bx_REm13_S05_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S06_high = fs->make<TH2F>("bx_REm13_S06_high","bx_REm13_S06_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S07_high = fs->make<TH2F>("bx_REm13_S07_high","bx_REm13_S07_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S08_high = fs->make<TH2F>("bx_REm13_S08_high","bx_REm13_S08_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S09_high = fs->make<TH2F>("bx_REm13_S09_high","bx_REm13_S09_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S10_high = fs->make<TH2F>("bx_REm13_S10_high","bx_REm13_S10_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S11_high = fs->make<TH2F>("bx_REm13_S11_high","bx_REm13_S11_high",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S12_high = fs->make<TH2F>("bx_REm13_S12_high","bx_REm13_S12_high",21,-0.5,20.5,11,-5.5,5.5);

// Low

bx_Wm2_RB1in_S01_low = fs->make<TH2F>("bx_Wm2_RB1in_S01_low","bx_Wm2_RB1in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S02_low = fs->make<TH2F>("bx_Wm2_RB1in_S02_low","bx_Wm2_RB1in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S03_low = fs->make<TH2F>("bx_Wm2_RB1in_S03_low","bx_Wm2_RB1in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S04_low = fs->make<TH2F>("bx_Wm2_RB1in_S04_low","bx_Wm2_RB1in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S05_low = fs->make<TH2F>("bx_Wm2_RB1in_S05_low","bx_Wm2_RB1in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S06_low = fs->make<TH2F>("bx_Wm2_RB1in_S06_low","bx_Wm2_RB1in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S07_low = fs->make<TH2F>("bx_Wm2_RB1in_S07_low","bx_Wm2_RB1in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S08_low = fs->make<TH2F>("bx_Wm2_RB1in_S08_low","bx_Wm2_RB1in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S09_low = fs->make<TH2F>("bx_Wm2_RB1in_S09_low","bx_Wm2_RB1in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S10_low = fs->make<TH2F>("bx_Wm2_RB1in_S10_low","bx_Wm2_RB1in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S11_low = fs->make<TH2F>("bx_Wm2_RB1in_S11_low","bx_Wm2_RB1in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S12_low = fs->make<TH2F>("bx_Wm2_RB1in_S12_low","bx_Wm2_RB1in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB1in_S01_low = fs->make<TH2F>("bx_Wm1_RB1in_S01_low","bx_Wm1_RB1in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S02_low = fs->make<TH2F>("bx_Wm1_RB1in_S02_low","bx_Wm1_RB1in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S03_low = fs->make<TH2F>("bx_Wm1_RB1in_S03_low","bx_Wm1_RB1in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S04_low = fs->make<TH2F>("bx_Wm1_RB1in_S04_low","bx_Wm1_RB1in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S05_low = fs->make<TH2F>("bx_Wm1_RB1in_S05_low","bx_Wm1_RB1in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S06_low = fs->make<TH2F>("bx_Wm1_RB1in_S06_low","bx_Wm1_RB1in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S07_low = fs->make<TH2F>("bx_Wm1_RB1in_S07_low","bx_Wm1_RB1in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S08_low = fs->make<TH2F>("bx_Wm1_RB1in_S08_low","bx_Wm1_RB1in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S09_low = fs->make<TH2F>("bx_Wm1_RB1in_S09_low","bx_Wm1_RB1in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S10_low = fs->make<TH2F>("bx_Wm1_RB1in_S10_low","bx_Wm1_RB1in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S11_low = fs->make<TH2F>("bx_Wm1_RB1in_S11_low","bx_Wm1_RB1in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S12_low = fs->make<TH2F>("bx_Wm1_RB1in_S12_low","bx_Wm1_RB1in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB1in_S01_low = fs->make<TH2F>("bx_W0_RB1in_S01_low","bx_W0_RB1in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S02_low = fs->make<TH2F>("bx_W0_RB1in_S02_low","bx_W0_RB1in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S03_low = fs->make<TH2F>("bx_W0_RB1in_S03_low","bx_W0_RB1in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S04_low = fs->make<TH2F>("bx_W0_RB1in_S04_low","bx_W0_RB1in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S05_low = fs->make<TH2F>("bx_W0_RB1in_S05_low","bx_W0_RB1in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S06_low = fs->make<TH2F>("bx_W0_RB1in_S06_low","bx_W0_RB1in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S07_low = fs->make<TH2F>("bx_W0_RB1in_S07_low","bx_W0_RB1in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S08_low = fs->make<TH2F>("bx_W0_RB1in_S08_low","bx_W0_RB1in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S09_low = fs->make<TH2F>("bx_W0_RB1in_S09_low","bx_W0_RB1in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S10_low = fs->make<TH2F>("bx_W0_RB1in_S10_low","bx_W0_RB1in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S11_low = fs->make<TH2F>("bx_W0_RB1in_S11_low","bx_W0_RB1in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S12_low = fs->make<TH2F>("bx_W0_RB1in_S12_low","bx_W0_RB1in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB1in_S01_low = fs->make<TH2F>("bx_Wp1_RB1in_S01_low","bx_Wp1_RB1in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S02_low = fs->make<TH2F>("bx_Wp1_RB1in_S02_low","bx_Wp1_RB1in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S03_low = fs->make<TH2F>("bx_Wp1_RB1in_S03_low","bx_Wp1_RB1in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S04_low = fs->make<TH2F>("bx_Wp1_RB1in_S04_low","bx_Wp1_RB1in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S05_low = fs->make<TH2F>("bx_Wp1_RB1in_S05_low","bx_Wp1_RB1in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S06_low = fs->make<TH2F>("bx_Wp1_RB1in_S06_low","bx_Wp1_RB1in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S07_low = fs->make<TH2F>("bx_Wp1_RB1in_S07_low","bx_Wp1_RB1in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S08_low = fs->make<TH2F>("bx_Wp1_RB1in_S08_low","bx_Wp1_RB1in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S09_low = fs->make<TH2F>("bx_Wp1_RB1in_S09_low","bx_Wp1_RB1in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S10_low = fs->make<TH2F>("bx_Wp1_RB1in_S10_low","bx_Wp1_RB1in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S11_low = fs->make<TH2F>("bx_Wp1_RB1in_S11_low","bx_Wp1_RB1in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S12_low = fs->make<TH2F>("bx_Wp1_RB1in_S12_low","bx_Wp1_RB1in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB1in_S01_low = fs->make<TH2F>("bx_Wp2_RB1in_S01_low","bx_Wp2_RB1in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S02_low = fs->make<TH2F>("bx_Wp2_RB1in_S02_low","bx_Wp2_RB1in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S03_low = fs->make<TH2F>("bx_Wp2_RB1in_S03_low","bx_Wp2_RB1in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S04_low = fs->make<TH2F>("bx_Wp2_RB1in_S04_low","bx_Wp2_RB1in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S05_low = fs->make<TH2F>("bx_Wp2_RB1in_S05_low","bx_Wp2_RB1in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S06_low = fs->make<TH2F>("bx_Wp2_RB1in_S06_low","bx_Wp2_RB1in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S07_low = fs->make<TH2F>("bx_Wp2_RB1in_S07_low","bx_Wp2_RB1in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S08_low = fs->make<TH2F>("bx_Wp2_RB1in_S08_low","bx_Wp2_RB1in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S09_low = fs->make<TH2F>("bx_Wp2_RB1in_S09_low","bx_Wp2_RB1in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S10_low = fs->make<TH2F>("bx_Wp2_RB1in_S10_low","bx_Wp2_RB1in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S11_low = fs->make<TH2F>("bx_Wp2_RB1in_S11_low","bx_Wp2_RB1in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S12_low = fs->make<TH2F>("bx_Wp2_RB1in_S12_low","bx_Wp2_RB1in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

// RB1out

bx_Wm2_RB1out_S01_low = fs->make<TH2F>("bx_Wm2_RB1out_S01_low","bx_Wm2_RB1out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S02_low = fs->make<TH2F>("bx_Wm2_RB1out_S02_low","bx_Wm2_RB1out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S03_low = fs->make<TH2F>("bx_Wm2_RB1out_S03_low","bx_Wm2_RB1out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S04_low = fs->make<TH2F>("bx_Wm2_RB1out_S04_low","bx_Wm2_RB1out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S05_low = fs->make<TH2F>("bx_Wm2_RB1out_S05_low","bx_Wm2_RB1out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S06_low = fs->make<TH2F>("bx_Wm2_RB1out_S06_low","bx_Wm2_RB1out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S07_low = fs->make<TH2F>("bx_Wm2_RB1out_S07_low","bx_Wm2_RB1out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S08_low = fs->make<TH2F>("bx_Wm2_RB1out_S08_low","bx_Wm2_RB1out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S09_low = fs->make<TH2F>("bx_Wm2_RB1out_S09_low","bx_Wm2_RB1out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S10_low = fs->make<TH2F>("bx_Wm2_RB1out_S10_low","bx_Wm2_RB1out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S11_low = fs->make<TH2F>("bx_Wm2_RB1out_S11_low","bx_Wm2_RB1out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S12_low = fs->make<TH2F>("bx_Wm2_RB1out_S12_low","bx_Wm2_RB1out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB1out_S01_low = fs->make<TH2F>("bx_Wm1_RB1out_S01_low","bx_Wm1_RB1out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S02_low = fs->make<TH2F>("bx_Wm1_RB1out_S02_low","bx_Wm1_RB1out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S03_low = fs->make<TH2F>("bx_Wm1_RB1out_S03_low","bx_Wm1_RB1out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S04_low = fs->make<TH2F>("bx_Wm1_RB1out_S04_low","bx_Wm1_RB1out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S05_low = fs->make<TH2F>("bx_Wm1_RB1out_S05_low","bx_Wm1_RB1out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S06_low = fs->make<TH2F>("bx_Wm1_RB1out_S06_low","bx_Wm1_RB1out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S07_low = fs->make<TH2F>("bx_Wm1_RB1out_S07_low","bx_Wm1_RB1out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S08_low = fs->make<TH2F>("bx_Wm1_RB1out_S08_low","bx_Wm1_RB1out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S09_low = fs->make<TH2F>("bx_Wm1_RB1out_S09_low","bx_Wm1_RB1out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S10_low = fs->make<TH2F>("bx_Wm1_RB1out_S10_low","bx_Wm1_RB1out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S11_low = fs->make<TH2F>("bx_Wm1_RB1out_S11_low","bx_Wm1_RB1out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S12_low = fs->make<TH2F>("bx_Wm1_RB1out_S12_low","bx_Wm1_RB1out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB1out_S01_low = fs->make<TH2F>("bx_W0_RB1out_S01_low","bx_W0_RB1out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S02_low = fs->make<TH2F>("bx_W0_RB1out_S02_low","bx_W0_RB1out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S03_low = fs->make<TH2F>("bx_W0_RB1out_S03_low","bx_W0_RB1out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S04_low = fs->make<TH2F>("bx_W0_RB1out_S04_low","bx_W0_RB1out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S05_low = fs->make<TH2F>("bx_W0_RB1out_S05_low","bx_W0_RB1out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S06_low = fs->make<TH2F>("bx_W0_RB1out_S06_low","bx_W0_RB1out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S07_low = fs->make<TH2F>("bx_W0_RB1out_S07_low","bx_W0_RB1out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S08_low = fs->make<TH2F>("bx_W0_RB1out_S08_low","bx_W0_RB1out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S09_low = fs->make<TH2F>("bx_W0_RB1out_S09_low","bx_W0_RB1out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S10_low = fs->make<TH2F>("bx_W0_RB1out_S10_low","bx_W0_RB1out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S11_low = fs->make<TH2F>("bx_W0_RB1out_S11_low","bx_W0_RB1out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S12_low = fs->make<TH2F>("bx_W0_RB1out_S12_low","bx_W0_RB1out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB1out_S01_low = fs->make<TH2F>("bx_Wp1_RB1out_S01_low","bx_Wp1_RB1out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S02_low = fs->make<TH2F>("bx_Wp1_RB1out_S02_low","bx_Wp1_RB1out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S03_low = fs->make<TH2F>("bx_Wp1_RB1out_S03_low","bx_Wp1_RB1out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S04_low = fs->make<TH2F>("bx_Wp1_RB1out_S04_low","bx_Wp1_RB1out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S05_low = fs->make<TH2F>("bx_Wp1_RB1out_S05_low","bx_Wp1_RB1out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S06_low = fs->make<TH2F>("bx_Wp1_RB1out_S06_low","bx_Wp1_RB1out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S07_low = fs->make<TH2F>("bx_Wp1_RB1out_S07_low","bx_Wp1_RB1out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S08_low = fs->make<TH2F>("bx_Wp1_RB1out_S08_low","bx_Wp1_RB1out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S09_low = fs->make<TH2F>("bx_Wp1_RB1out_S09_low","bx_Wp1_RB1out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S10_low = fs->make<TH2F>("bx_Wp1_RB1out_S10_low","bx_Wp1_RB1out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S11_low = fs->make<TH2F>("bx_Wp1_RB1out_S11_low","bx_Wp1_RB1out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S12_low = fs->make<TH2F>("bx_Wp1_RB1out_S12_low","bx_Wp1_RB1out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB1out_S01_low = fs->make<TH2F>("bx_Wp2_RB1out_S01_low","bx_Wp2_RB1out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S02_low = fs->make<TH2F>("bx_Wp2_RB1out_S02_low","bx_Wp2_RB1out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S03_low = fs->make<TH2F>("bx_Wp2_RB1out_S03_low","bx_Wp2_RB1out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S04_low = fs->make<TH2F>("bx_Wp2_RB1out_S04_low","bx_Wp2_RB1out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S05_low = fs->make<TH2F>("bx_Wp2_RB1out_S05_low","bx_Wp2_RB1out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S06_low = fs->make<TH2F>("bx_Wp2_RB1out_S06_low","bx_Wp2_RB1out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S07_low = fs->make<TH2F>("bx_Wp2_RB1out_S07_low","bx_Wp2_RB1out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S08_low = fs->make<TH2F>("bx_Wp2_RB1out_S08_low","bx_Wp2_RB1out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S09_low = fs->make<TH2F>("bx_Wp2_RB1out_S09_low","bx_Wp2_RB1out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S10_low = fs->make<TH2F>("bx_Wp2_RB1out_S10_low","bx_Wp2_RB1out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S11_low = fs->make<TH2F>("bx_Wp2_RB1out_S11_low","bx_Wp2_RB1out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S12_low = fs->make<TH2F>("bx_Wp2_RB1out_S12_low","bx_Wp2_RB1out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

// RB2in

bx_Wm2_RB2in_S01_low = fs->make<TH2F>("bx_Wm2_RB2in_S01_low","bx_Wm2_RB2in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S02_low = fs->make<TH2F>("bx_Wm2_RB2in_S02_low","bx_Wm2_RB2in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S03_low = fs->make<TH2F>("bx_Wm2_RB2in_S03_low","bx_Wm2_RB2in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S04_low = fs->make<TH2F>("bx_Wm2_RB2in_S04_low","bx_Wm2_RB2in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S05_low = fs->make<TH2F>("bx_Wm2_RB2in_S05_low","bx_Wm2_RB2in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S06_low = fs->make<TH2F>("bx_Wm2_RB2in_S06_low","bx_Wm2_RB2in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S07_low = fs->make<TH2F>("bx_Wm2_RB2in_S07_low","bx_Wm2_RB2in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S08_low = fs->make<TH2F>("bx_Wm2_RB2in_S08_low","bx_Wm2_RB2in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S09_low = fs->make<TH2F>("bx_Wm2_RB2in_S09_low","bx_Wm2_RB2in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S10_low = fs->make<TH2F>("bx_Wm2_RB2in_S10_low","bx_Wm2_RB2in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S11_low = fs->make<TH2F>("bx_Wm2_RB2in_S11_low","bx_Wm2_RB2in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S12_low = fs->make<TH2F>("bx_Wm2_RB2in_S12_low","bx_Wm2_RB2in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB2in_S01_low = fs->make<TH2F>("bx_Wm1_RB2in_S01_low","bx_Wm1_RB2in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S02_low = fs->make<TH2F>("bx_Wm1_RB2in_S02_low","bx_Wm1_RB2in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S03_low = fs->make<TH2F>("bx_Wm1_RB2in_S03_low","bx_Wm1_RB2in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S04_low = fs->make<TH2F>("bx_Wm1_RB2in_S04_low","bx_Wm1_RB2in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S05_low = fs->make<TH2F>("bx_Wm1_RB2in_S05_low","bx_Wm1_RB2in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S06_low = fs->make<TH2F>("bx_Wm1_RB2in_S06_low","bx_Wm1_RB2in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S07_low = fs->make<TH2F>("bx_Wm1_RB2in_S07_low","bx_Wm1_RB2in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S08_low = fs->make<TH2F>("bx_Wm1_RB2in_S08_low","bx_Wm1_RB2in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S09_low = fs->make<TH2F>("bx_Wm1_RB2in_S09_low","bx_Wm1_RB2in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S10_low = fs->make<TH2F>("bx_Wm1_RB2in_S10_low","bx_Wm1_RB2in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S11_low = fs->make<TH2F>("bx_Wm1_RB2in_S11_low","bx_Wm1_RB2in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S12_low = fs->make<TH2F>("bx_Wm1_RB2in_S12_low","bx_Wm1_RB2in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB2in_S01_low = fs->make<TH2F>("bx_W0_RB2in_S01_low","bx_W0_RB2in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S02_low = fs->make<TH2F>("bx_W0_RB2in_S02_low","bx_W0_RB2in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S03_low = fs->make<TH2F>("bx_W0_RB2in_S03_low","bx_W0_RB2in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S04_low = fs->make<TH2F>("bx_W0_RB2in_S04_low","bx_W0_RB2in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S05_low = fs->make<TH2F>("bx_W0_RB2in_S05_low","bx_W0_RB2in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S06_low = fs->make<TH2F>("bx_W0_RB2in_S06_low","bx_W0_RB2in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S07_low = fs->make<TH2F>("bx_W0_RB2in_S07_low","bx_W0_RB2in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S08_low = fs->make<TH2F>("bx_W0_RB2in_S08_low","bx_W0_RB2in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S09_low = fs->make<TH2F>("bx_W0_RB2in_S09_low","bx_W0_RB2in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S10_low = fs->make<TH2F>("bx_W0_RB2in_S10_low","bx_W0_RB2in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S11_low = fs->make<TH2F>("bx_W0_RB2in_S11_low","bx_W0_RB2in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S12_low = fs->make<TH2F>("bx_W0_RB2in_S12_low","bx_W0_RB2in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB2in_S01_low = fs->make<TH2F>("bx_Wp1_RB2in_S01_low","bx_Wp1_RB2in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S02_low = fs->make<TH2F>("bx_Wp1_RB2in_S02_low","bx_Wp1_RB2in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S03_low = fs->make<TH2F>("bx_Wp1_RB2in_S03_low","bx_Wp1_RB2in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S04_low = fs->make<TH2F>("bx_Wp1_RB2in_S04_low","bx_Wp1_RB2in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S05_low = fs->make<TH2F>("bx_Wp1_RB2in_S05_low","bx_Wp1_RB2in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S06_low = fs->make<TH2F>("bx_Wp1_RB2in_S06_low","bx_Wp1_RB2in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S07_low = fs->make<TH2F>("bx_Wp1_RB2in_S07_low","bx_Wp1_RB2in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S08_low = fs->make<TH2F>("bx_Wp1_RB2in_S08_low","bx_Wp1_RB2in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S09_low = fs->make<TH2F>("bx_Wp1_RB2in_S09_low","bx_Wp1_RB2in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S10_low = fs->make<TH2F>("bx_Wp1_RB2in_S10_low","bx_Wp1_RB2in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S11_low = fs->make<TH2F>("bx_Wp1_RB2in_S11_low","bx_Wp1_RB2in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S12_low = fs->make<TH2F>("bx_Wp1_RB2in_S12_low","bx_Wp1_RB2in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB2in_S01_low = fs->make<TH2F>("bx_Wp2_RB2in_S01_low","bx_Wp2_RB2in_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S02_low = fs->make<TH2F>("bx_Wp2_RB2in_S02_low","bx_Wp2_RB2in_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S03_low = fs->make<TH2F>("bx_Wp2_RB2in_S03_low","bx_Wp2_RB2in_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S04_low = fs->make<TH2F>("bx_Wp2_RB2in_S04_low","bx_Wp2_RB2in_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S05_low = fs->make<TH2F>("bx_Wp2_RB2in_S05_low","bx_Wp2_RB2in_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S06_low = fs->make<TH2F>("bx_Wp2_RB2in_S06_low","bx_Wp2_RB2in_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S07_low = fs->make<TH2F>("bx_Wp2_RB2in_S07_low","bx_Wp2_RB2in_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S08_low = fs->make<TH2F>("bx_Wp2_RB2in_S08_low","bx_Wp2_RB2in_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S09_low = fs->make<TH2F>("bx_Wp2_RB2in_S09_low","bx_Wp2_RB2in_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S10_low = fs->make<TH2F>("bx_Wp2_RB2in_S10_low","bx_Wp2_RB2in_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S11_low = fs->make<TH2F>("bx_Wp2_RB2in_S11_low","bx_Wp2_RB2in_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S12_low = fs->make<TH2F>("bx_Wp2_RB2in_S12_low","bx_Wp2_RB2in_S12_low",21,-0.5,20.5,11,-5.5,5.5);

// RB2out

bx_Wm2_RB2out_S01_low = fs->make<TH2F>("bx_Wm2_RB2out_S01_low","bx_Wm2_RB2out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S02_low = fs->make<TH2F>("bx_Wm2_RB2out_S02_low","bx_Wm2_RB2out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S03_low = fs->make<TH2F>("bx_Wm2_RB2out_S03_low","bx_Wm2_RB2out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S04_low = fs->make<TH2F>("bx_Wm2_RB2out_S04_low","bx_Wm2_RB2out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S05_low = fs->make<TH2F>("bx_Wm2_RB2out_S05_low","bx_Wm2_RB2out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S06_low = fs->make<TH2F>("bx_Wm2_RB2out_S06_low","bx_Wm2_RB2out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S07_low = fs->make<TH2F>("bx_Wm2_RB2out_S07_low","bx_Wm2_RB2out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S08_low = fs->make<TH2F>("bx_Wm2_RB2out_S08_low","bx_Wm2_RB2out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S09_low = fs->make<TH2F>("bx_Wm2_RB2out_S09_low","bx_Wm2_RB2out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S10_low = fs->make<TH2F>("bx_Wm2_RB2out_S10_low","bx_Wm2_RB2out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S11_low = fs->make<TH2F>("bx_Wm2_RB2out_S11_low","bx_Wm2_RB2out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S12_low = fs->make<TH2F>("bx_Wm2_RB2out_S12_low","bx_Wm2_RB2out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB2out_S01_low = fs->make<TH2F>("bx_Wm1_RB2out_S01_low","bx_Wm1_RB2out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S02_low = fs->make<TH2F>("bx_Wm1_RB2out_S02_low","bx_Wm1_RB2out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S03_low = fs->make<TH2F>("bx_Wm1_RB2out_S03_low","bx_Wm1_RB2out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S04_low = fs->make<TH2F>("bx_Wm1_RB2out_S04_low","bx_Wm1_RB2out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S05_low = fs->make<TH2F>("bx_Wm1_RB2out_S05_low","bx_Wm1_RB2out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S06_low = fs->make<TH2F>("bx_Wm1_RB2out_S06_low","bx_Wm1_RB2out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S07_low = fs->make<TH2F>("bx_Wm1_RB2out_S07_low","bx_Wm1_RB2out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S08_low = fs->make<TH2F>("bx_Wm1_RB2out_S08_low","bx_Wm1_RB2out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S09_low = fs->make<TH2F>("bx_Wm1_RB2out_S09_low","bx_Wm1_RB2out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S10_low = fs->make<TH2F>("bx_Wm1_RB2out_S10_low","bx_Wm1_RB2out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S11_low = fs->make<TH2F>("bx_Wm1_RB2out_S11_low","bx_Wm1_RB2out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S12_low = fs->make<TH2F>("bx_Wm1_RB2out_S12_low","bx_Wm1_RB2out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB2out_S01_low = fs->make<TH2F>("bx_W0_RB2out_S01_low","bx_W0_RB2out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S02_low = fs->make<TH2F>("bx_W0_RB2out_S02_low","bx_W0_RB2out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S03_low = fs->make<TH2F>("bx_W0_RB2out_S03_low","bx_W0_RB2out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S04_low = fs->make<TH2F>("bx_W0_RB2out_S04_low","bx_W0_RB2out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S05_low = fs->make<TH2F>("bx_W0_RB2out_S05_low","bx_W0_RB2out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S06_low = fs->make<TH2F>("bx_W0_RB2out_S06_low","bx_W0_RB2out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S07_low = fs->make<TH2F>("bx_W0_RB2out_S07_low","bx_W0_RB2out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S08_low = fs->make<TH2F>("bx_W0_RB2out_S08_low","bx_W0_RB2out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S09_low = fs->make<TH2F>("bx_W0_RB2out_S09_low","bx_W0_RB2out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S10_low = fs->make<TH2F>("bx_W0_RB2out_S10_low","bx_W0_RB2out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S11_low = fs->make<TH2F>("bx_W0_RB2out_S11_low","bx_W0_RB2out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S12_low = fs->make<TH2F>("bx_W0_RB2out_S12_low","bx_W0_RB2out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB2out_S01_low = fs->make<TH2F>("bx_Wp1_RB2out_S01_low","bx_Wp1_RB2out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S02_low = fs->make<TH2F>("bx_Wp1_RB2out_S02_low","bx_Wp1_RB2out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S03_low = fs->make<TH2F>("bx_Wp1_RB2out_S03_low","bx_Wp1_RB2out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S04_low = fs->make<TH2F>("bx_Wp1_RB2out_S04_low","bx_Wp1_RB2out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S05_low = fs->make<TH2F>("bx_Wp1_RB2out_S05_low","bx_Wp1_RB2out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S06_low = fs->make<TH2F>("bx_Wp1_RB2out_S06_low","bx_Wp1_RB2out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S07_low = fs->make<TH2F>("bx_Wp1_RB2out_S07_low","bx_Wp1_RB2out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S08_low = fs->make<TH2F>("bx_Wp1_RB2out_S08_low","bx_Wp1_RB2out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S09_low = fs->make<TH2F>("bx_Wp1_RB2out_S09_low","bx_Wp1_RB2out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S10_low = fs->make<TH2F>("bx_Wp1_RB2out_S10_low","bx_Wp1_RB2out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S11_low = fs->make<TH2F>("bx_Wp1_RB2out_S11_low","bx_Wp1_RB2out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S12_low = fs->make<TH2F>("bx_Wp1_RB2out_S12_low","bx_Wp1_RB2out_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB2out_S01_low = fs->make<TH2F>("bx_Wp2_RB2out_S01_low","bx_Wp2_RB2out_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S02_low = fs->make<TH2F>("bx_Wp2_RB2out_S02_low","bx_Wp2_RB2out_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S03_low = fs->make<TH2F>("bx_Wp2_RB2out_S03_low","bx_Wp2_RB2out_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S04_low = fs->make<TH2F>("bx_Wp2_RB2out_S04_low","bx_Wp2_RB2out_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S05_low = fs->make<TH2F>("bx_Wp2_RB2out_S05_low","bx_Wp2_RB2out_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S06_low = fs->make<TH2F>("bx_Wp2_RB2out_S06_low","bx_Wp2_RB2out_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S07_low = fs->make<TH2F>("bx_Wp2_RB2out_S07_low","bx_Wp2_RB2out_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S08_low = fs->make<TH2F>("bx_Wp2_RB2out_S08_low","bx_Wp2_RB2out_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S09_low = fs->make<TH2F>("bx_Wp2_RB2out_S09_low","bx_Wp2_RB2out_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S10_low = fs->make<TH2F>("bx_Wp2_RB2out_S10_low","bx_Wp2_RB2out_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S11_low = fs->make<TH2F>("bx_Wp2_RB2out_S11_low","bx_Wp2_RB2out_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S12_low = fs->make<TH2F>("bx_Wp2_RB2out_S12_low","bx_Wp2_RB2out_S12_low",21,-0.5,20.5,11,-5.5,5.5);


// RB3

bx_Wm2_RB3_S01_low = fs->make<TH2F>("bx_Wm2_RB3_S01_low","bx_Wm2_RB3_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S02_low = fs->make<TH2F>("bx_Wm2_RB3_S02_low","bx_Wm2_RB3_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S03_low = fs->make<TH2F>("bx_Wm2_RB3_S03_low","bx_Wm2_RB3_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S04_low = fs->make<TH2F>("bx_Wm2_RB3_S04_low","bx_Wm2_RB3_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S05_low = fs->make<TH2F>("bx_Wm2_RB3_S05_low","bx_Wm2_RB3_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S06_low = fs->make<TH2F>("bx_Wm2_RB3_S06_low","bx_Wm2_RB3_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S07_low = fs->make<TH2F>("bx_Wm2_RB3_S07_low","bx_Wm2_RB3_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S08_low = fs->make<TH2F>("bx_Wm2_RB3_S08_low","bx_Wm2_RB3_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S09_low = fs->make<TH2F>("bx_Wm2_RB3_S09_low","bx_Wm2_RB3_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S10_low = fs->make<TH2F>("bx_Wm2_RB3_S10_low","bx_Wm2_RB3_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S11_low = fs->make<TH2F>("bx_Wm2_RB3_S11_low","bx_Wm2_RB3_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S12_low = fs->make<TH2F>("bx_Wm2_RB3_S12_low","bx_Wm2_RB3_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB3_S01_low = fs->make<TH2F>("bx_Wm1_RB3_S01_low","bx_Wm1_RB3_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S02_low = fs->make<TH2F>("bx_Wm1_RB3_S02_low","bx_Wm1_RB3_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S03_low = fs->make<TH2F>("bx_Wm1_RB3_S03_low","bx_Wm1_RB3_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S04_low = fs->make<TH2F>("bx_Wm1_RB3_S04_low","bx_Wm1_RB3_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S05_low = fs->make<TH2F>("bx_Wm1_RB3_S05_low","bx_Wm1_RB3_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S06_low = fs->make<TH2F>("bx_Wm1_RB3_S06_low","bx_Wm1_RB3_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S07_low = fs->make<TH2F>("bx_Wm1_RB3_S07_low","bx_Wm1_RB3_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S08_low = fs->make<TH2F>("bx_Wm1_RB3_S08_low","bx_Wm1_RB3_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S09_low = fs->make<TH2F>("bx_Wm1_RB3_S09_low","bx_Wm1_RB3_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S10_low = fs->make<TH2F>("bx_Wm1_RB3_S10_low","bx_Wm1_RB3_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S11_low = fs->make<TH2F>("bx_Wm1_RB3_S11_low","bx_Wm1_RB3_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S12_low = fs->make<TH2F>("bx_Wm1_RB3_S12_low","bx_Wm1_RB3_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB3_S01_low = fs->make<TH2F>("bx_W0_RB3_S01_low","bx_W0_RB3_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S02_low = fs->make<TH2F>("bx_W0_RB3_S02_low","bx_W0_RB3_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S03_low = fs->make<TH2F>("bx_W0_RB3_S03_low","bx_W0_RB3_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S04_low = fs->make<TH2F>("bx_W0_RB3_S04_low","bx_W0_RB3_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S05_low = fs->make<TH2F>("bx_W0_RB3_S05_low","bx_W0_RB3_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S06_low = fs->make<TH2F>("bx_W0_RB3_S06_low","bx_W0_RB3_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S07_low = fs->make<TH2F>("bx_W0_RB3_S07_low","bx_W0_RB3_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S08_low = fs->make<TH2F>("bx_W0_RB3_S08_low","bx_W0_RB3_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S09_low = fs->make<TH2F>("bx_W0_RB3_S09_low","bx_W0_RB3_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S10_low = fs->make<TH2F>("bx_W0_RB3_S10_low","bx_W0_RB3_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S11_low = fs->make<TH2F>("bx_W0_RB3_S11_low","bx_W0_RB3_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S12_low = fs->make<TH2F>("bx_W0_RB3_S12_low","bx_W0_RB3_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB3_S01_low = fs->make<TH2F>("bx_Wp1_RB3_S01_low","bx_Wp1_RB3_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S02_low = fs->make<TH2F>("bx_Wp1_RB3_S02_low","bx_Wp1_RB3_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S03_low = fs->make<TH2F>("bx_Wp1_RB3_S03_low","bx_Wp1_RB3_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S04_low = fs->make<TH2F>("bx_Wp1_RB3_S04_low","bx_Wp1_RB3_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S05_low = fs->make<TH2F>("bx_Wp1_RB3_S05_low","bx_Wp1_RB3_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S06_low = fs->make<TH2F>("bx_Wp1_RB3_S06_low","bx_Wp1_RB3_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S07_low = fs->make<TH2F>("bx_Wp1_RB3_S07_low","bx_Wp1_RB3_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S08_low = fs->make<TH2F>("bx_Wp1_RB3_S08_low","bx_Wp1_RB3_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S09_low = fs->make<TH2F>("bx_Wp1_RB3_S09_low","bx_Wp1_RB3_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S10_low = fs->make<TH2F>("bx_Wp1_RB3_S10_low","bx_Wp1_RB3_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S11_low = fs->make<TH2F>("bx_Wp1_RB3_S11_low","bx_Wp1_RB3_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S12_low = fs->make<TH2F>("bx_Wp1_RB3_S12_low","bx_Wp1_RB3_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB3_S01_low = fs->make<TH2F>("bx_Wp2_RB3_S01_low","bx_Wp2_RB3_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S02_low = fs->make<TH2F>("bx_Wp2_RB3_S02_low","bx_Wp2_RB3_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S03_low = fs->make<TH2F>("bx_Wp2_RB3_S03_low","bx_Wp2_RB3_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S04_low = fs->make<TH2F>("bx_Wp2_RB3_S04_low","bx_Wp2_RB3_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S05_low = fs->make<TH2F>("bx_Wp2_RB3_S05_low","bx_Wp2_RB3_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S06_low = fs->make<TH2F>("bx_Wp2_RB3_S06_low","bx_Wp2_RB3_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S07_low = fs->make<TH2F>("bx_Wp2_RB3_S07_low","bx_Wp2_RB3_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S08_low = fs->make<TH2F>("bx_Wp2_RB3_S08_low","bx_Wp2_RB3_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S09_low = fs->make<TH2F>("bx_Wp2_RB3_S09_low","bx_Wp2_RB3_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S10_low = fs->make<TH2F>("bx_Wp2_RB3_S10_low","bx_Wp2_RB3_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S11_low = fs->make<TH2F>("bx_Wp2_RB3_S11_low","bx_Wp2_RB3_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S12_low = fs->make<TH2F>("bx_Wp2_RB3_S12_low","bx_Wp2_RB3_S12_low",21,-0.5,20.5,11,-5.5,5.5);

// RB4

bx_Wm2_RB4_S01_low = fs->make<TH2F>("bx_Wm2_RB4_S01_low","bx_Wm2_RB4_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S02_low = fs->make<TH2F>("bx_Wm2_RB4_S02_low","bx_Wm2_RB4_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S03_low = fs->make<TH2F>("bx_Wm2_RB4_S03_low","bx_Wm2_RB4_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S04_low = fs->make<TH2F>("bx_Wm2_RB4_S04_low","bx_Wm2_RB4_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S05_low = fs->make<TH2F>("bx_Wm2_RB4_S05_low","bx_Wm2_RB4_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S06_low = fs->make<TH2F>("bx_Wm2_RB4_S06_low","bx_Wm2_RB4_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S07_low = fs->make<TH2F>("bx_Wm2_RB4_S07_low","bx_Wm2_RB4_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S08_low = fs->make<TH2F>("bx_Wm2_RB4_S08_low","bx_Wm2_RB4_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S09_low = fs->make<TH2F>("bx_Wm2_RB4_S09_low","bx_Wm2_RB4_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S10_low = fs->make<TH2F>("bx_Wm2_RB4_S10_low","bx_Wm2_RB4_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S11_low = fs->make<TH2F>("bx_Wm2_RB4_S11_low","bx_Wm2_RB4_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S12_low = fs->make<TH2F>("bx_Wm2_RB4_S12_low","bx_Wm2_RB4_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wm1_RB4_S01_low = fs->make<TH2F>("bx_Wm1_RB4_S01_low","bx_Wm1_RB4_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S02_low = fs->make<TH2F>("bx_Wm1_RB4_S02_low","bx_Wm1_RB4_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S03_low = fs->make<TH2F>("bx_Wm1_RB4_S03_low","bx_Wm1_RB4_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S04_low = fs->make<TH2F>("bx_Wm1_RB4_S04_low","bx_Wm1_RB4_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S05_low = fs->make<TH2F>("bx_Wm1_RB4_S05_low","bx_Wm1_RB4_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S06_low = fs->make<TH2F>("bx_Wm1_RB4_S06_low","bx_Wm1_RB4_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S07_low = fs->make<TH2F>("bx_Wm1_RB4_S07_low","bx_Wm1_RB4_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S08_low = fs->make<TH2F>("bx_Wm1_RB4_S08_low","bx_Wm1_RB4_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S09_low = fs->make<TH2F>("bx_Wm1_RB4_S09_low","bx_Wm1_RB4_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S10_low = fs->make<TH2F>("bx_Wm1_RB4_S10_low","bx_Wm1_RB4_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S11_low = fs->make<TH2F>("bx_Wm1_RB4_S11_low","bx_Wm1_RB4_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S12_low = fs->make<TH2F>("bx_Wm1_RB4_S12_low","bx_Wm1_RB4_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_W0_RB4_S01_low = fs->make<TH2F>("bx_W0_RB4_S01_low","bx_W0_RB4_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S02_low = fs->make<TH2F>("bx_W0_RB4_S02_low","bx_W0_RB4_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S03_low = fs->make<TH2F>("bx_W0_RB4_S03_low","bx_W0_RB4_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S04_low = fs->make<TH2F>("bx_W0_RB4_S04_low","bx_W0_RB4_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S05_low = fs->make<TH2F>("bx_W0_RB4_S05_low","bx_W0_RB4_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S06_low = fs->make<TH2F>("bx_W0_RB4_S06_low","bx_W0_RB4_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S07_low = fs->make<TH2F>("bx_W0_RB4_S07_low","bx_W0_RB4_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S08_low = fs->make<TH2F>("bx_W0_RB4_S08_low","bx_W0_RB4_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S09_low = fs->make<TH2F>("bx_W0_RB4_S09_low","bx_W0_RB4_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S10_low = fs->make<TH2F>("bx_W0_RB4_S10_low","bx_W0_RB4_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S11_low = fs->make<TH2F>("bx_W0_RB4_S11_low","bx_W0_RB4_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S12_low = fs->make<TH2F>("bx_W0_RB4_S12_low","bx_W0_RB4_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp1_RB4_S01_low = fs->make<TH2F>("bx_Wp1_RB4_S01_low","bx_Wp1_RB4_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S02_low = fs->make<TH2F>("bx_Wp1_RB4_S02_low","bx_Wp1_RB4_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S03_low = fs->make<TH2F>("bx_Wp1_RB4_S03_low","bx_Wp1_RB4_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S04_low = fs->make<TH2F>("bx_Wp1_RB4_S04_low","bx_Wp1_RB4_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S05_low = fs->make<TH2F>("bx_Wp1_RB4_S05_low","bx_Wp1_RB4_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S06_low = fs->make<TH2F>("bx_Wp1_RB4_S06_low","bx_Wp1_RB4_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S07_low = fs->make<TH2F>("bx_Wp1_RB4_S07_low","bx_Wp1_RB4_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S08_low = fs->make<TH2F>("bx_Wp1_RB4_S08_low","bx_Wp1_RB4_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S09_low = fs->make<TH2F>("bx_Wp1_RB4_S09_low","bx_Wp1_RB4_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S10_low = fs->make<TH2F>("bx_Wp1_RB4_S10_low","bx_Wp1_RB4_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S11_low = fs->make<TH2F>("bx_Wp1_RB4_S11_low","bx_Wp1_RB4_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S12_low = fs->make<TH2F>("bx_Wp1_RB4_S12_low","bx_Wp1_RB4_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_Wp2_RB4_S01_low = fs->make<TH2F>("bx_Wp2_RB4_S01_low","bx_Wp2_RB4_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S02_low = fs->make<TH2F>("bx_Wp2_RB4_S02_low","bx_Wp2_RB4_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S03_low = fs->make<TH2F>("bx_Wp2_RB4_S03_low","bx_Wp2_RB4_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S04_low = fs->make<TH2F>("bx_Wp2_RB4_S04_low","bx_Wp2_RB4_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S05_low = fs->make<TH2F>("bx_Wp2_RB4_S05_low","bx_Wp2_RB4_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S06_low = fs->make<TH2F>("bx_Wp2_RB4_S06_low","bx_Wp2_RB4_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S07_low = fs->make<TH2F>("bx_Wp2_RB4_S07_low","bx_Wp2_RB4_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S08_low = fs->make<TH2F>("bx_Wp2_RB4_S08_low","bx_Wp2_RB4_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S09_low = fs->make<TH2F>("bx_Wp2_RB4_S09_low","bx_Wp2_RB4_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S10_low = fs->make<TH2F>("bx_Wp2_RB4_S10_low","bx_Wp2_RB4_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S11_low = fs->make<TH2F>("bx_Wp2_RB4_S11_low","bx_Wp2_RB4_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S12_low = fs->make<TH2F>("bx_Wp2_RB4_S12_low","bx_Wp2_RB4_S12_low",21,-0.5,20.5,11,-5.5,5.5);

//endcap +
bx_REp42_S01_low = fs->make<TH2F>("bx_REp42_S01_low","bx_REp42_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S02_low = fs->make<TH2F>("bx_REp42_S02_low","bx_REp42_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S03_low = fs->make<TH2F>("bx_REp42_S03_low","bx_REp42_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S04_low = fs->make<TH2F>("bx_REp42_S04_low","bx_REp42_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S05_low = fs->make<TH2F>("bx_REp42_S05_low","bx_REp42_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S06_low = fs->make<TH2F>("bx_REp42_S06_low","bx_REp42_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S07_low = fs->make<TH2F>("bx_REp42_S07_low","bx_REp42_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S08_low = fs->make<TH2F>("bx_REp42_S08_low","bx_REp42_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S09_low = fs->make<TH2F>("bx_REp42_S09_low","bx_REp42_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S10_low = fs->make<TH2F>("bx_REp42_S10_low","bx_REp42_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S11_low = fs->make<TH2F>("bx_REp42_S11_low","bx_REp42_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S12_low = fs->make<TH2F>("bx_REp42_S12_low","bx_REp42_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S01_low = fs->make<TH2F>("bx_REp43_S01_low","bx_REp43_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S02_low = fs->make<TH2F>("bx_REp43_S02_low","bx_REp43_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S03_low = fs->make<TH2F>("bx_REp43_S03_low","bx_REp43_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S04_low = fs->make<TH2F>("bx_REp43_S04_low","bx_REp43_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S05_low = fs->make<TH2F>("bx_REp43_S05_low","bx_REp43_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S06_low = fs->make<TH2F>("bx_REp43_S06_low","bx_REp43_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S07_low = fs->make<TH2F>("bx_REp43_S07_low","bx_REp43_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S08_low = fs->make<TH2F>("bx_REp43_S08_low","bx_REp43_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S09_low = fs->make<TH2F>("bx_REp43_S09_low","bx_REp43_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S10_low = fs->make<TH2F>("bx_REp43_S10_low","bx_REp43_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S11_low = fs->make<TH2F>("bx_REp43_S11_low","bx_REp43_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S12_low = fs->make<TH2F>("bx_REp43_S12_low","bx_REp43_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S01_low = fs->make<TH2F>("bx_REp12_S01_low","bx_REp12_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S02_low = fs->make<TH2F>("bx_REp12_S02_low","bx_REp12_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S03_low = fs->make<TH2F>("bx_REp12_S03_low","bx_REp12_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S04_low = fs->make<TH2F>("bx_REp12_S04_low","bx_REp12_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S05_low = fs->make<TH2F>("bx_REp12_S05_low","bx_REp12_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S06_low = fs->make<TH2F>("bx_REp12_S06_low","bx_REp12_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S07_low = fs->make<TH2F>("bx_REp12_S07_low","bx_REp12_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S08_low = fs->make<TH2F>("bx_REp12_S08_low","bx_REp12_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S09_low = fs->make<TH2F>("bx_REp12_S09_low","bx_REp12_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S10_low = fs->make<TH2F>("bx_REp12_S10_low","bx_REp12_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S11_low = fs->make<TH2F>("bx_REp12_S11_low","bx_REp12_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S12_low = fs->make<TH2F>("bx_REp12_S12_low","bx_REp12_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S01_low = fs->make<TH2F>("bx_REp13_S01_low","bx_REp13_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S02_low = fs->make<TH2F>("bx_REp13_S02_low","bx_REp13_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S03_low = fs->make<TH2F>("bx_REp13_S03_low","bx_REp13_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S04_low = fs->make<TH2F>("bx_REp13_S04_low","bx_REp13_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S05_low = fs->make<TH2F>("bx_REp13_S05_low","bx_REp13_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S06_low = fs->make<TH2F>("bx_REp13_S06_low","bx_REp13_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S07_low = fs->make<TH2F>("bx_REp13_S07_low","bx_REp13_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S08_low = fs->make<TH2F>("bx_REp13_S08_low","bx_REp13_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S09_low = fs->make<TH2F>("bx_REp13_S09_low","bx_REp13_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S10_low = fs->make<TH2F>("bx_REp13_S10_low","bx_REp13_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S11_low = fs->make<TH2F>("bx_REp13_S11_low","bx_REp13_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S12_low = fs->make<TH2F>("bx_REp13_S12_low","bx_REp13_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_REp32_S01_low = fs->make<TH2F>("bx_REp32_S01_low","bx_REp32_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S02_low = fs->make<TH2F>("bx_REp32_S02_low","bx_REp32_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S03_low = fs->make<TH2F>("bx_REp32_S03_low","bx_REp32_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S04_low = fs->make<TH2F>("bx_REp32_S04_low","bx_REp32_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S05_low = fs->make<TH2F>("bx_REp32_S05_low","bx_REp32_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S06_low = fs->make<TH2F>("bx_REp32_S06_low","bx_REp32_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S07_low = fs->make<TH2F>("bx_REp32_S07_low","bx_REp32_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S08_low = fs->make<TH2F>("bx_REp32_S08_low","bx_REp32_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S09_low = fs->make<TH2F>("bx_REp32_S09_low","bx_REp32_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S10_low = fs->make<TH2F>("bx_REp32_S10_low","bx_REp32_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S11_low = fs->make<TH2F>("bx_REp32_S11_low","bx_REp32_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S12_low = fs->make<TH2F>("bx_REp32_S12_low","bx_REp32_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S01_low = fs->make<TH2F>("bx_REp33_S01_low","bx_REp33_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S02_low = fs->make<TH2F>("bx_REp33_S02_low","bx_REp33_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S03_low = fs->make<TH2F>("bx_REp33_S03_low","bx_REp33_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S04_low = fs->make<TH2F>("bx_REp33_S04_low","bx_REp33_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S05_low = fs->make<TH2F>("bx_REp33_S05_low","bx_REp33_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S06_low = fs->make<TH2F>("bx_REp33_S06_low","bx_REp33_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S07_low = fs->make<TH2F>("bx_REp33_S07_low","bx_REp33_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S08_low = fs->make<TH2F>("bx_REp33_S08_low","bx_REp33_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S09_low = fs->make<TH2F>("bx_REp33_S09_low","bx_REp33_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S10_low = fs->make<TH2F>("bx_REp33_S10_low","bx_REp33_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S11_low = fs->make<TH2F>("bx_REp33_S11_low","bx_REp33_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S12_low = fs->make<TH2F>("bx_REp33_S12_low","bx_REp33_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_REp22_S01_low = fs->make<TH2F>("bx_REp22_S01_low","bx_REp22_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S02_low = fs->make<TH2F>("bx_REp22_S02_low","bx_REp22_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S03_low = fs->make<TH2F>("bx_REp22_S03_low","bx_REp22_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S04_low = fs->make<TH2F>("bx_REp22_S04_low","bx_REp22_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S05_low = fs->make<TH2F>("bx_REp22_S05_low","bx_REp22_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S06_low = fs->make<TH2F>("bx_REp22_S06_low","bx_REp22_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S07_low = fs->make<TH2F>("bx_REp22_S07_low","bx_REp22_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S08_low = fs->make<TH2F>("bx_REp22_S08_low","bx_REp22_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S09_low = fs->make<TH2F>("bx_REp22_S09_low","bx_REp22_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S10_low = fs->make<TH2F>("bx_REp22_S10_low","bx_REp22_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S11_low = fs->make<TH2F>("bx_REp22_S11_low","bx_REp22_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S12_low = fs->make<TH2F>("bx_REp22_S12_low","bx_REp22_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S01_low = fs->make<TH2F>("bx_REp23_S01_low","bx_REp23_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S02_low = fs->make<TH2F>("bx_REp23_S02_low","bx_REp23_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S03_low = fs->make<TH2F>("bx_REp23_S03_low","bx_REp23_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S04_low = fs->make<TH2F>("bx_REp23_S04_low","bx_REp23_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S05_low = fs->make<TH2F>("bx_REp23_S05_low","bx_REp23_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S06_low = fs->make<TH2F>("bx_REp23_S06_low","bx_REp23_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S07_low = fs->make<TH2F>("bx_REp23_S07_low","bx_REp23_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S08_low = fs->make<TH2F>("bx_REp23_S08_low","bx_REp23_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S09_low = fs->make<TH2F>("bx_REp23_S09_low","bx_REp23_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S10_low = fs->make<TH2F>("bx_REp23_S10_low","bx_REp23_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S11_low = fs->make<TH2F>("bx_REp23_S11_low","bx_REp23_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S12_low = fs->make<TH2F>("bx_REp23_S12_low","bx_REp23_S12_low",21,-0.5,20.5,11,-5.5,5.5);

//endcap -
bx_REm42_S01_low = fs->make<TH2F>("bx_REm42_S01_low","bx_REm42_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S02_low = fs->make<TH2F>("bx_REm42_S02_low","bx_REm42_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S03_low = fs->make<TH2F>("bx_REm42_S03_low","bx_REm42_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S04_low = fs->make<TH2F>("bx_REm42_S04_low","bx_REm42_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S05_low = fs->make<TH2F>("bx_REm42_S05_low","bx_REm42_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S06_low = fs->make<TH2F>("bx_REm42_S06_low","bx_REm42_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S07_low = fs->make<TH2F>("bx_REm42_S07_low","bx_REm42_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S08_low = fs->make<TH2F>("bx_REm42_S08_low","bx_REm42_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S09_low = fs->make<TH2F>("bx_REm42_S09_low","bx_REm42_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S10_low = fs->make<TH2F>("bx_REm42_S10_low","bx_REm42_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S11_low = fs->make<TH2F>("bx_REm42_S11_low","bx_REm42_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S12_low = fs->make<TH2F>("bx_REm42_S12_low","bx_REm42_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S01_low = fs->make<TH2F>("bx_REm43_S01_low","bx_REm43_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S02_low = fs->make<TH2F>("bx_REm43_S02_low","bx_REm43_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S03_low = fs->make<TH2F>("bx_REm43_S03_low","bx_REm43_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S04_low = fs->make<TH2F>("bx_REm43_S04_low","bx_REm43_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S05_low = fs->make<TH2F>("bx_REm43_S05_low","bx_REm43_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S06_low = fs->make<TH2F>("bx_REm43_S06_low","bx_REm43_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S07_low = fs->make<TH2F>("bx_REm43_S07_low","bx_REm43_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S08_low = fs->make<TH2F>("bx_REm43_S08_low","bx_REm43_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S09_low = fs->make<TH2F>("bx_REm43_S09_low","bx_REm43_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S10_low = fs->make<TH2F>("bx_REm43_S10_low","bx_REm43_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S11_low = fs->make<TH2F>("bx_REm43_S11_low","bx_REm43_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S12_low = fs->make<TH2F>("bx_REm43_S12_low","bx_REm43_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S01_low = fs->make<TH2F>("bx_REm12_S01_low","bx_REm12_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S02_low = fs->make<TH2F>("bx_REm12_S02_low","bx_REm12_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S03_low = fs->make<TH2F>("bx_REm12_S03_low","bx_REm12_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S04_low = fs->make<TH2F>("bx_REm12_S04_low","bx_REm12_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S05_low = fs->make<TH2F>("bx_REm12_S05_low","bx_REm12_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S06_low = fs->make<TH2F>("bx_REm12_S06_low","bx_REm12_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S07_low = fs->make<TH2F>("bx_REm12_S07_low","bx_REm12_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S08_low = fs->make<TH2F>("bx_REm12_S08_low","bx_REm12_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S09_low = fs->make<TH2F>("bx_REm12_S09_low","bx_REm12_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S10_low = fs->make<TH2F>("bx_REm12_S10_low","bx_REm12_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S11_low = fs->make<TH2F>("bx_REm12_S11_low","bx_REm12_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S12_low = fs->make<TH2F>("bx_REm12_S12_low","bx_REm12_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S01_low = fs->make<TH2F>("bx_REm13_S01_low","bx_REm13_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S02_low = fs->make<TH2F>("bx_REm13_S02_low","bx_REm13_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S03_low = fs->make<TH2F>("bx_REm13_S03_low","bx_REm13_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S04_low = fs->make<TH2F>("bx_REm13_S04_low","bx_REm13_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S05_low = fs->make<TH2F>("bx_REm13_S05_low","bx_REm13_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S06_low = fs->make<TH2F>("bx_REm13_S06_low","bx_REm13_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S07_low = fs->make<TH2F>("bx_REm13_S07_low","bx_REm13_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S08_low = fs->make<TH2F>("bx_REm13_S08_low","bx_REm13_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S09_low = fs->make<TH2F>("bx_REm13_S09_low","bx_REm13_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S10_low = fs->make<TH2F>("bx_REm13_S10_low","bx_REm13_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S11_low = fs->make<TH2F>("bx_REm13_S11_low","bx_REm13_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S12_low = fs->make<TH2F>("bx_REm13_S12_low","bx_REm13_S12_low",21,-0.5,20.5,11,-5.5,5.5);

bx_REm32_S01_low = fs->make<TH2F>("bx_REm32_S01_low","bx_REm32_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S02_low = fs->make<TH2F>("bx_REm32_S02_low","bx_REm32_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S03_low = fs->make<TH2F>("bx_REm32_S03_low","bx_REm32_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S04_low = fs->make<TH2F>("bx_REm32_S04_low","bx_REm32_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S05_low = fs->make<TH2F>("bx_REm32_S05_low","bx_REm32_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S06_low = fs->make<TH2F>("bx_REm32_S06_low","bx_REm32_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S07_low = fs->make<TH2F>("bx_REm32_S07_low","bx_REm32_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S08_low = fs->make<TH2F>("bx_REm32_S08_low","bx_REm32_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S09_low = fs->make<TH2F>("bx_REm32_S09_low","bx_REm32_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S10_low = fs->make<TH2F>("bx_REm32_S10_low","bx_REm32_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S11_low = fs->make<TH2F>("bx_REm32_S11_low","bx_REm32_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S12_low = fs->make<TH2F>("bx_REm32_S12_low","bx_REm32_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S01_low = fs->make<TH2F>("bx_REm33_S01_low","bx_REm33_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S02_low = fs->make<TH2F>("bx_REm33_S02_low","bx_REm33_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S03_low = fs->make<TH2F>("bx_REm33_S03_low","bx_REm33_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S04_low = fs->make<TH2F>("bx_REm33_S04_low","bx_REm33_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S05_low = fs->make<TH2F>("bx_REm33_S05_low","bx_REm33_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S06_low = fs->make<TH2F>("bx_REm33_S06_low","bx_REm33_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S07_low = fs->make<TH2F>("bx_REm33_S07_low","bx_REm33_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S08_low = fs->make<TH2F>("bx_REm33_S08_low","bx_REm33_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S09_low = fs->make<TH2F>("bx_REm33_S09_low","bx_REm33_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S10_low = fs->make<TH2F>("bx_REm33_S10_low","bx_REm33_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S11_low = fs->make<TH2F>("bx_REm33_S11_low","bx_REm33_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S12_low = fs->make<TH2F>("bx_REm33_S12_low","bx_REm33_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S01_low = fs->make<TH2F>("bx_REm22_S01_low","bx_REm22_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S02_low = fs->make<TH2F>("bx_REm22_S02_low","bx_REm22_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S03_low = fs->make<TH2F>("bx_REm22_S03_low","bx_REm22_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S04_low = fs->make<TH2F>("bx_REm22_S04_low","bx_REm22_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S05_low = fs->make<TH2F>("bx_REm22_S05_low","bx_REm22_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S06_low = fs->make<TH2F>("bx_REm22_S06_low","bx_REm22_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S07_low = fs->make<TH2F>("bx_REm22_S07_low","bx_REm22_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S08_low = fs->make<TH2F>("bx_REm22_S08_low","bx_REm22_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S09_low = fs->make<TH2F>("bx_REm22_S09_low","bx_REm22_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S10_low = fs->make<TH2F>("bx_REm22_S10_low","bx_REm22_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S11_low = fs->make<TH2F>("bx_REm22_S11_low","bx_REm22_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S12_low = fs->make<TH2F>("bx_REm22_S12_low","bx_REm22_S12_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S01_low = fs->make<TH2F>("bx_REm23_S01_low","bx_REm23_S01_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S02_low = fs->make<TH2F>("bx_REm23_S02_low","bx_REm23_S02_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S03_low = fs->make<TH2F>("bx_REm23_S03_low","bx_REm23_S03_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S04_low = fs->make<TH2F>("bx_REm23_S04_low","bx_REm23_S04_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S05_low = fs->make<TH2F>("bx_REm23_S05_low","bx_REm23_S05_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S06_low = fs->make<TH2F>("bx_REm23_S06_low","bx_REm23_S06_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S07_low = fs->make<TH2F>("bx_REm23_S07_low","bx_REm23_S07_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S08_low = fs->make<TH2F>("bx_REm23_S08_low","bx_REm23_S08_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S09_low = fs->make<TH2F>("bx_REm23_S09_low","bx_REm23_S09_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S10_low = fs->make<TH2F>("bx_REm23_S10_low","bx_REm23_S10_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S11_low = fs->make<TH2F>("bx_REm23_S11_low","bx_REm23_S11_low",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S12_low = fs->make<TH2F>("bx_REm23_S12_low","bx_REm23_S12_low",21,-0.5,20.5,11,-5.5,5.5);


// RB1out
 bx_Wp2_RB1out_B_high = fs->make<TH2F>("bx_Wp2_RB1out_B_high","bx_Wp2_RB1out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1out_B_high = fs->make<TH2F>("bx_Wp1_RB1out_B_high","bx_Wp1_RB1out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1out_B_high = fs->make<TH2F>("bx_W0_RB1out_B_high","bx_W0_RB1out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1out_B_high = fs->make<TH2F>("bx_Wm1_RB1out_B_high","bx_Wm1_RB1out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1out_B_high = fs->make<TH2F>("bx_Wm2_RB1out_B_high","bx_Wm2_RB1out_B_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB1out_F_high = fs->make<TH2F>("bx_Wp2_RB1out_F_high","bx_Wp2_RB1out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1out_F_high = fs->make<TH2F>("bx_Wp1_RB1out_F_high","bx_Wp1_RB1out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1out_F_high = fs->make<TH2F>("bx_W0_RB1out_F_high","bx_W0_RB1out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1out_F_high = fs->make<TH2F>("bx_Wm1_RB1out_F_high","bx_Wm1_RB1out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1out_F_high = fs->make<TH2F>("bx_Wm2_RB1out_F_high","bx_Wm2_RB1out_F_high",21,-0.5,20.5,11,-5.5,5.5);


 bx_Wp2_RB1out_B_low = fs->make<TH2F>("bx_Wp2_RB1out_B_low","bx_Wp2_RB1out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1out_B_low = fs->make<TH2F>("bx_Wp1_RB1out_B_low","bx_Wp1_RB1out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1out_B_low = fs->make<TH2F>("bx_W0_RB1out_B_low","bx_W0_RB1out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1out_B_low = fs->make<TH2F>("bx_Wm1_RB1out_B_low","bx_Wm1_RB1out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1out_B_low = fs->make<TH2F>("bx_Wm2_RB1out_B_low","bx_Wm2_RB1out_B_low",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB1out_F_low = fs->make<TH2F>("bx_Wp2_RB1out_F_low","bx_Wp2_RB1out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1out_F_low = fs->make<TH2F>("bx_Wp1_RB1out_F_low","bx_Wp1_RB1out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1out_F_low = fs->make<TH2F>("bx_W0_RB1out_F_low","bx_W0_RB1out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1out_F_low = fs->make<TH2F>("bx_Wm1_RB1out_F_low","bx_Wm1_RB1out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1out_F_low = fs->make<TH2F>("bx_Wm2_RB1out_F_low","bx_Wm2_RB1out_F_low",21,-0.5,20.5,11,-5.5,5.5);

// RB1in

 bx_Wp2_RB1in_B_high = fs->make<TH2F>("bx_Wp2_RB1in_B_high","bx_Wp2_RB1in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1in_B_high = fs->make<TH2F>("bx_Wp1_RB1in_B_high","bx_Wp1_RB1in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1in_B_high = fs->make<TH2F>("bx_W0_RB1in_B_high","bx_W0_RB1in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1in_B_high = fs->make<TH2F>("bx_Wm1_RB1in_B_high","bx_Wm1_RB1in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1in_B_high = fs->make<TH2F>("bx_Wm2_RB1in_B_high","bx_Wm2_RB1in_B_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB1in_F_high = fs->make<TH2F>("bx_Wp2_RB1in_F_high","bx_Wp2_RB1in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1in_F_high = fs->make<TH2F>("bx_Wp1_RB1in_F_high","bx_Wp1_RB1in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1in_F_high = fs->make<TH2F>("bx_W0_RB1in_F_high","bx_W0_RB1in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1in_F_high = fs->make<TH2F>("bx_Wm1_RB1in_F_high","bx_Wm1_RB1in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1in_F_high = fs->make<TH2F>("bx_Wm2_RB1in_F_high","bx_Wm2_RB1in_F_high",21,-0.5,20.5,11,-5.5,5.5);


 bx_Wp2_RB1in_B_low = fs->make<TH2F>("bx_Wp2_RB1in_B_low","bx_Wp2_RB1in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1in_B_low = fs->make<TH2F>("bx_Wp1_RB1in_B_low","bx_Wp1_RB1in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1in_B_low = fs->make<TH2F>("bx_W0_RB1in_B_low","bx_W0_RB1in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1in_B_low = fs->make<TH2F>("bx_Wm1_RB1in_B_low","bx_Wm1_RB1in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1in_B_low = fs->make<TH2F>("bx_Wm2_RB1in_B_low","bx_Wm2_RB1in_B_low",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB1in_F_low = fs->make<TH2F>("bx_Wp2_RB1in_F_low","bx_Wp2_RB1in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB1in_F_low = fs->make<TH2F>("bx_Wp1_RB1in_F_low","bx_Wp1_RB1in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB1in_F_low = fs->make<TH2F>("bx_W0_RB1in_F_low","bx_W0_RB1in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB1in_F_low = fs->make<TH2F>("bx_Wm1_RB1in_F_low","bx_Wm1_RB1in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB1in_F_low = fs->make<TH2F>("bx_Wm2_RB1in_F_low","bx_Wm2_RB1in_F_low",21,-0.5,20.5,11,-5.5,5.5);

 //RB3

 bx_Wp2_RB3_B_high = fs->make<TH2F>("bx_Wp2_RB3_B_high","bx_Wp2_RB3_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB3_B_high = fs->make<TH2F>("bx_Wp1_RB3_B_high","bx_Wp1_RB3_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB3_B_high = fs->make<TH2F>("bx_W0_RB3_B_high","bx_W0_RB3_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB3_B_high = fs->make<TH2F>("bx_Wm1_RB3_B_high","bx_Wm1_RB3_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB3_B_high = fs->make<TH2F>("bx_Wm2_RB3_B_high","bx_Wm2_RB3_B_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB3_F_high = fs->make<TH2F>("bx_Wp2_RB3_F_high","bx_Wp2_RB3_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB3_F_high = fs->make<TH2F>("bx_Wp1_RB3_F_high","bx_Wp1_RB3_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB3_F_high = fs->make<TH2F>("bx_W0_RB3_F_high","bx_W0_RB3_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB3_F_high = fs->make<TH2F>("bx_Wm1_RB3_F_high","bx_Wm1_RB3_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB3_F_high = fs->make<TH2F>("bx_Wm2_RB3_F_high","bx_Wm2_RB3_F_high",21,-0.5,20.5,11,-5.5,5.5);


 bx_Wp2_RB3_B_low = fs->make<TH2F>("bx_Wp2_RB3_B_low","bx_Wp2_RB3_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB3_B_low = fs->make<TH2F>("bx_Wp1_RB3_B_low","bx_Wp1_RB3_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB3_B_low = fs->make<TH2F>("bx_W0_RB3_B_low","bx_W0_RB3_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB3_B_low = fs->make<TH2F>("bx_Wm1_RB3_B_low","bx_Wm1_RB3_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB3_B_low = fs->make<TH2F>("bx_Wm2_RB3_B_low","bx_Wm2_RB3_B_low",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB3_F_low = fs->make<TH2F>("bx_Wp2_RB3_F_low","bx_Wp2_RB3_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB3_F_low = fs->make<TH2F>("bx_Wp1_RB3_F_low","bx_Wp1_RB3_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB3_F_low = fs->make<TH2F>("bx_W0_RB3_F_low","bx_W0_RB3_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB3_F_low = fs->make<TH2F>("bx_Wm1_RB3_F_low","bx_Wm1_RB3_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB3_F_low = fs->make<TH2F>("bx_Wm2_RB3_F_low","bx_Wm2_RB3_F_low",21,-0.5,20.5,11,-5.5,5.5);

// RB4

 bx_Wp2_RB4_B_high = fs->make<TH2F>("bx_Wp2_RB4_B_high","bx_Wp2_RB4_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB4_B_high = fs->make<TH2F>("bx_Wp1_RB4_B_high","bx_Wp1_RB4_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB4_B_high = fs->make<TH2F>("bx_W0_RB4_B_high","bx_W0_RB4_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB4_B_high = fs->make<TH2F>("bx_Wm1_RB4_B_high","bx_Wm1_RB4_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB4_B_high = fs->make<TH2F>("bx_Wm2_RB4_B_high","bx_Wm2_RB4_B_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB4_F_high = fs->make<TH2F>("bx_Wp2_RB4_F_high","bx_Wp2_RB4_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB4_F_high = fs->make<TH2F>("bx_Wp1_RB4_F_high","bx_Wp1_RB4_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB4_F_high = fs->make<TH2F>("bx_W0_RB4_F_high","bx_W0_RB4_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB4_F_high = fs->make<TH2F>("bx_Wm1_RB4_F_high","bx_Wm1_RB4_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB4_F_high = fs->make<TH2F>("bx_Wm2_RB4_F_high","bx_Wm2_RB4_F_high",21,-0.5,20.5,11,-5.5,5.5);


 bx_Wp2_RB4_B_low = fs->make<TH2F>("bx_Wp2_RB4_B_low","bx_Wp2_RB4_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB4_B_low = fs->make<TH2F>("bx_Wp1_RB4_B_low","bx_Wp1_RB4_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB4_B_low = fs->make<TH2F>("bx_W0_RB4_B_low","bx_W0_RB4_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB4_B_low = fs->make<TH2F>("bx_Wm1_RB4_B_low","bx_Wm1_RB4_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB4_B_low = fs->make<TH2F>("bx_Wm2_RB4_B_low","bx_Wm2_RB4_B_low",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB4_F_low = fs->make<TH2F>("bx_Wp2_RB4_F_low","bx_Wp2_RB4_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB4_F_low = fs->make<TH2F>("bx_Wp1_RB4_F_low","bx_Wp1_RB4_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB4_F_low = fs->make<TH2F>("bx_W0_RB4_F_low","bx_W0_RB4_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB4_F_low = fs->make<TH2F>("bx_Wm1_RB4_F_low","bx_Wm1_RB4_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB4_F_low = fs->make<TH2F>("bx_Wm2_RB4_F_low","bx_Wm2_RB4_F_low",21,-0.5,20.5,11,-5.5,5.5);     



// RB2out
 bx_Wp2_RB2out_B_high = fs->make<TH2F>("bx_Wp2_RB2out_B_high","bx_Wp2_RB2out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2out_B_high = fs->make<TH2F>("bx_Wp1_RB2out_B_high","bx_Wp1_RB2out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2out_B_high = fs->make<TH2F>("bx_W0_RB2out_B_high","bx_W0_RB2out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2out_B_high = fs->make<TH2F>("bx_Wm1_RB2out_B_high","bx_Wm1_RB2out_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2out_B_high = fs->make<TH2F>("bx_Wm2_RB2out_B_high","bx_Wm2_RB2out_B_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB2out_F_high = fs->make<TH2F>("bx_Wp2_RB2out_F_high","bx_Wp2_RB2out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2out_F_high = fs->make<TH2F>("bx_Wp1_RB2out_F_high","bx_Wp1_RB2out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2out_F_high = fs->make<TH2F>("bx_W0_RB2out_F_high","bx_W0_RB2out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2out_F_high = fs->make<TH2F>("bx_Wm1_RB2out_F_high","bx_Wm1_RB2out_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2out_F_high = fs->make<TH2F>("bx_Wm2_RB2out_F_high","bx_Wm2_RB2out_F_high",21,-0.5,20.5,11,-5.5,5.5);


 bx_Wp2_RB2out_B_low = fs->make<TH2F>("bx_Wp2_RB2out_B_low","bx_Wp2_RB2out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2out_B_low = fs->make<TH2F>("bx_Wp1_RB2out_B_low","bx_Wp1_RB2out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2out_B_low = fs->make<TH2F>("bx_W0_RB2out_B_low","bx_W0_RB2out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2out_B_low = fs->make<TH2F>("bx_Wm1_RB2out_B_low","bx_Wm1_RB2out_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2out_B_low = fs->make<TH2F>("bx_Wm2_RB2out_B_low","bx_Wm2_RB2out_B_low",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB2out_F_low = fs->make<TH2F>("bx_Wp2_RB2out_F_low","bx_Wp2_RB2out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2out_F_low = fs->make<TH2F>("bx_Wp1_RB2out_F_low","bx_Wp1_RB2out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2out_F_low = fs->make<TH2F>("bx_W0_RB2out_F_low","bx_W0_RB2out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2out_F_low = fs->make<TH2F>("bx_Wm1_RB2out_F_low","bx_Wm1_RB2out_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2out_F_low = fs->make<TH2F>("bx_Wm2_RB2out_F_low","bx_Wm2_RB2out_F_low",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB2out_M_high = fs->make<TH2F>("bx_Wp2_RB2out_M_high","bx_Wp2_RB2out_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2out_M_high = fs->make<TH2F>("bx_Wm2_RB2out_M_high","bx_Wm2_RB2out_M_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB2out_M_low = fs->make<TH2F>("bx_Wp2_RB2out_M_low","bx_Wp2_RB2out_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2out_M_low = fs->make<TH2F>("bx_Wm2_RB2out_M_low","bx_Wm2_RB2out_M_low",21,-0.5,20.5,11,-5.5,5.5);


// RB2in

 bx_Wp2_RB2in_B_high = fs->make<TH2F>("bx_Wp2_RB2in_B_high","bx_Wp2_RB2in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2in_B_high = fs->make<TH2F>("bx_Wp1_RB2in_B_high","bx_Wp1_RB2in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2in_B_high = fs->make<TH2F>("bx_W0_RB2in_B_high","bx_W0_RB2in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2in_B_high = fs->make<TH2F>("bx_Wm1_RB2in_B_high","bx_Wm1_RB2in_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2in_B_high = fs->make<TH2F>("bx_Wm2_RB2in_B_high","bx_Wm2_RB2in_B_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB2in_F_high = fs->make<TH2F>("bx_Wp2_RB2in_F_high","bx_Wp2_RB2in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2in_F_high = fs->make<TH2F>("bx_Wp1_RB2in_F_high","bx_Wp1_RB2in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2in_F_high = fs->make<TH2F>("bx_W0_RB2in_F_high","bx_W0_RB2in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2in_F_high = fs->make<TH2F>("bx_Wm1_RB2in_F_high","bx_Wm1_RB2in_F_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2in_F_high = fs->make<TH2F>("bx_Wm2_RB2in_F_high","bx_Wm2_RB2in_F_high",21,-0.5,20.5,11,-5.5,5.5);


 bx_Wp2_RB2in_B_low = fs->make<TH2F>("bx_Wp2_RB2in_B_low","bx_Wp2_RB2in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2in_B_low = fs->make<TH2F>("bx_Wp1_RB2in_B_low","bx_Wp1_RB2in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2in_B_low = fs->make<TH2F>("bx_W0_RB2in_B_low","bx_W0_RB2in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2in_B_low = fs->make<TH2F>("bx_Wm1_RB2in_B_low","bx_Wm1_RB2in_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2in_B_low = fs->make<TH2F>("bx_Wm2_RB2in_B_low","bx_Wm2_RB2in_B_low",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp2_RB2in_F_low = fs->make<TH2F>("bx_Wp2_RB2in_F_low","bx_Wp2_RB2in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wp1_RB2in_F_low = fs->make<TH2F>("bx_Wp1_RB2in_F_low","bx_Wp1_RB2in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2in_F_low = fs->make<TH2F>("bx_W0_RB2in_F_low","bx_W0_RB2in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2in_F_low = fs->make<TH2F>("bx_Wm1_RB2in_F_low","bx_Wm1_RB2in_F_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm2_RB2in_F_low = fs->make<TH2F>("bx_Wm2_RB2in_F_low","bx_Wm2_RB2in_F_low",21,-0.5,20.5,11,-5.5,5.5);     

 bx_Wp1_RB2in_M_high = fs->make<TH2F>("bx_Wp1_RB2in_M_high","bx_Wp1_RB2in_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2in_M_high = fs->make<TH2F>("bx_W0_RB2in_M_high","bx_W0_RB2in_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2in_M_high = fs->make<TH2F>("bx_Wm1_RB2in_M_high","bx_Wm1_RB2in_M_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_Wp1_RB2in_M_low = fs->make<TH2F>("bx_Wp1_RB2in_M_low","bx_Wp1_RB2in_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_W0_RB2in_M_low = fs->make<TH2F>("bx_W0_RB2in_M_low","bx_W0_RB2in_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_Wm1_RB2in_M_low = fs->make<TH2F>("bx_Wm1_RB2in_M_low","bx_Wm1_RB2in_M_low",21,-0.5,20.5,11,-5.5,5.5);

// REp12

 bx_REp12_B_high = fs->make<TH2F>("bx_REp12_B_high","bx_REp12_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp12_M_high = fs->make<TH2F>("bx_REp12_M_high","bx_REp12_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp12_F_high = fs->make<TH2F>("bx_REp12_F_high","bx_REp12_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp12_B_low = fs->make<TH2F>("bx_REp12_B_low","bx_REp12_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp12_M_low = fs->make<TH2F>("bx_REp12_M_low","bx_REp12_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp12_F_low = fs->make<TH2F>("bx_REp12_F_low","bx_REp12_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REp13

 bx_REp13_B_high = fs->make<TH2F>("bx_REp13_B_high","bx_REp13_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp13_M_high = fs->make<TH2F>("bx_REp13_M_high","bx_REp13_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp13_F_high = fs->make<TH2F>("bx_REp13_F_high","bx_REp13_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp13_B_low = fs->make<TH2F>("bx_REp13_B_low","bx_REp13_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp13_M_low = fs->make<TH2F>("bx_REp13_M_low","bx_REp13_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp13_F_low = fs->make<TH2F>("bx_REp13_F_low","bx_REp13_F_low",21,-0.5,20.5,11,-5.5,5.5);

 // REp22

 bx_REp22_B_high = fs->make<TH2F>("bx_REp22_B_high","bx_REp22_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp22_M_high = fs->make<TH2F>("bx_REp22_M_high","bx_REp22_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp22_F_high = fs->make<TH2F>("bx_REp22_F_high","bx_REp22_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp22_B_low = fs->make<TH2F>("bx_REp22_B_low","bx_REp22_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp22_M_low = fs->make<TH2F>("bx_REp22_M_low","bx_REp22_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp22_F_low = fs->make<TH2F>("bx_REp22_F_low","bx_REp22_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REp23

 bx_REp23_B_high = fs->make<TH2F>("bx_REp23_B_high","bx_REp23_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp23_M_high = fs->make<TH2F>("bx_REp23_M_high","bx_REp23_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp23_F_high = fs->make<TH2F>("bx_REp23_F_high","bx_REp23_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp23_B_low = fs->make<TH2F>("bx_REp23_B_low","bx_REp23_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp23_M_low = fs->make<TH2F>("bx_REp23_M_low","bx_REp23_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp23_F_low = fs->make<TH2F>("bx_REp23_F_low","bx_REp23_F_low",21,-0.5,20.5,11,-5.5,5.5);


  // REp32

 bx_REp32_B_high = fs->make<TH2F>("bx_REp32_B_high","bx_REp32_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp32_M_high = fs->make<TH2F>("bx_REp32_M_high","bx_REp32_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp32_F_high = fs->make<TH2F>("bx_REp32_F_high","bx_REp32_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp32_B_low = fs->make<TH2F>("bx_REp32_B_low","bx_REp32_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp32_M_low = fs->make<TH2F>("bx_REp32_M_low","bx_REp32_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp32_F_low = fs->make<TH2F>("bx_REp32_F_low","bx_REp32_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REp33

 bx_REp33_B_high = fs->make<TH2F>("bx_REp33_B_high","bx_REp33_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp33_M_high = fs->make<TH2F>("bx_REp33_M_high","bx_REp33_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp33_F_high = fs->make<TH2F>("bx_REp33_F_high","bx_REp33_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp33_B_low = fs->make<TH2F>("bx_REp33_B_low","bx_REp33_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp33_M_low = fs->make<TH2F>("bx_REp33_M_low","bx_REp33_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp33_F_low = fs->make<TH2F>("bx_REp33_F_low","bx_REp33_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REp42

 bx_REp42_B_high = fs->make<TH2F>("bx_REp42_B_high","bx_REp42_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp42_M_high = fs->make<TH2F>("bx_REp42_M_high","bx_REp42_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp42_F_high = fs->make<TH2F>("bx_REp42_F_high","bx_REp42_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp42_B_low = fs->make<TH2F>("bx_REp42_B_low","bx_REp42_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp42_M_low = fs->make<TH2F>("bx_REp42_M_low","bx_REp42_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp42_F_low = fs->make<TH2F>("bx_REp42_F_low","bx_REp42_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REp43

 bx_REp43_B_high = fs->make<TH2F>("bx_REp43_B_high","bx_REp43_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp43_M_high = fs->make<TH2F>("bx_REp43_M_high","bx_REp43_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp43_F_high = fs->make<TH2F>("bx_REp43_F_high","bx_REp43_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REp43_B_low = fs->make<TH2F>("bx_REp43_B_low","bx_REp43_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp43_M_low = fs->make<TH2F>("bx_REp43_M_low","bx_REp43_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REp43_F_low = fs->make<TH2F>("bx_REp43_F_low","bx_REp43_F_low",21,-0.5,20.5,11,-5.5,5.5);


 // endcap minus

 // REp12

 bx_REm12_B_high = fs->make<TH2F>("bx_REm12_B_high","bx_REm12_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm12_M_high = fs->make<TH2F>("bx_REm12_M_high","bx_REm12_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm12_F_high = fs->make<TH2F>("bx_REm12_F_high","bx_REm12_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm12_B_low = fs->make<TH2F>("bx_REm12_B_low","bx_REm12_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm12_M_low = fs->make<TH2F>("bx_REm12_M_low","bx_REm12_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm12_F_low = fs->make<TH2F>("bx_REm12_F_low","bx_REm12_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REm13

 bx_REm13_B_high = fs->make<TH2F>("bx_REm13_B_high","bx_REm13_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm13_M_high = fs->make<TH2F>("bx_REm13_M_high","bx_REm13_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm13_F_high = fs->make<TH2F>("bx_REm13_F_high","bx_REm13_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm13_B_low = fs->make<TH2F>("bx_REm13_B_low","bx_REm13_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm13_M_low = fs->make<TH2F>("bx_REm13_M_low","bx_REm13_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm13_F_low = fs->make<TH2F>("bx_REm13_F_low","bx_REm13_F_low",21,-0.5,20.5,11,-5.5,5.5);

  // REm22

 bx_REm22_B_high = fs->make<TH2F>("bx_REm22_B_high","bx_REm22_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm22_M_high = fs->make<TH2F>("bx_REm22_M_high","bx_REm22_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm22_F_high = fs->make<TH2F>("bx_REm22_F_high","bx_REm22_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm22_B_low = fs->make<TH2F>("bx_REm22_B_low","bx_REm22_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm22_M_low = fs->make<TH2F>("bx_REm22_M_low","bx_REm22_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm22_F_low = fs->make<TH2F>("bx_REm22_F_low","bx_REm22_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REm23

 bx_REm23_B_high = fs->make<TH2F>("bx_REm23_B_high","bx_REm23_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm23_M_high = fs->make<TH2F>("bx_REm23_M_high","bx_REm23_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm23_F_high = fs->make<TH2F>("bx_REm23_F_high","bx_REm23_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm23_B_low = fs->make<TH2F>("bx_REm23_B_low","bx_REm23_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm23_M_low = fs->make<TH2F>("bx_REm23_M_low","bx_REm23_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm23_F_low = fs->make<TH2F>("bx_REm23_F_low","bx_REm23_F_low",21,-0.5,20.5,11,-5.5,5.5);


  // REm32

 bx_REm32_B_high = fs->make<TH2F>("bx_REm32_B_high","bx_REm32_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm32_M_high = fs->make<TH2F>("bx_REm32_M_high","bx_REm32_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm32_F_high = fs->make<TH2F>("bx_REm32_F_high","bx_REm32_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm32_B_low = fs->make<TH2F>("bx_REm32_B_low","bx_REm32_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm32_M_low = fs->make<TH2F>("bx_REm32_M_low","bx_REm32_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm32_F_low = fs->make<TH2F>("bx_REm32_F_low","bx_REm32_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REm33

 bx_REm33_B_high = fs->make<TH2F>("bx_REm33_B_high","bx_REm33_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm33_M_high = fs->make<TH2F>("bx_REm33_M_high","bx_REm33_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm33_F_high = fs->make<TH2F>("bx_REm33_F_high","bx_REm33_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm33_B_low = fs->make<TH2F>("bx_REm33_B_low","bx_REm33_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm33_M_low = fs->make<TH2F>("bx_REm33_M_low","bx_REm33_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm33_F_low = fs->make<TH2F>("bx_REm33_F_low","bx_REm33_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REm42

 bx_REm42_B_high = fs->make<TH2F>("bx_REm42_B_high","bx_REm42_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm42_M_high = fs->make<TH2F>("bx_REm42_M_high","bx_REm42_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm42_F_high = fs->make<TH2F>("bx_REm42_F_high","bx_REm42_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm42_B_low = fs->make<TH2F>("bx_REm42_B_low","bx_REm42_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm42_M_low = fs->make<TH2F>("bx_REm42_M_low","bx_REm42_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm42_F_low = fs->make<TH2F>("bx_REm42_F_low","bx_REm42_F_low",21,-0.5,20.5,11,-5.5,5.5);

// REm43

 bx_REm43_B_high = fs->make<TH2F>("bx_REm43_B_high","bx_REm43_B_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm43_M_high = fs->make<TH2F>("bx_REm43_M_high","bx_REm43_M_high",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm43_F_high = fs->make<TH2F>("bx_REm43_F_high","bx_REm43_F_high",21,-0.5,20.5,11,-5.5,5.5);

 bx_REm43_B_low = fs->make<TH2F>("bx_REm43_B_low","bx_REm43_B_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm43_M_low = fs->make<TH2F>("bx_REm43_M_low","bx_REm43_M_low",21,-0.5,20.5,11,-5.5,5.5);
 bx_REm43_F_low = fs->make<TH2F>("bx_REm43_F_low","bx_REm43_F_low",21,-0.5,20.5,11,-5.5,5.5);

 // abort and pre beam
 bx_Wm2_RB1in_S01_abort = fs->make<TH2F>("bx_Wm2_RB1in_S01_abort","bx_Wm2_RB1in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S01_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S01_prebeam","bx_Wm2_RB1in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S02_abort = fs->make<TH2F>("bx_Wm2_RB1in_S02_abort","bx_Wm2_RB1in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S02_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S02_prebeam","bx_Wm2_RB1in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S03_abort = fs->make<TH2F>("bx_Wm2_RB1in_S03_abort","bx_Wm2_RB1in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S03_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S03_prebeam","bx_Wm2_RB1in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S04_abort = fs->make<TH2F>("bx_Wm2_RB1in_S04_abort","bx_Wm2_RB1in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S04_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S04_prebeam","bx_Wm2_RB1in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S05_abort = fs->make<TH2F>("bx_Wm2_RB1in_S05_abort","bx_Wm2_RB1in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S05_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S05_prebeam","bx_Wm2_RB1in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S06_abort = fs->make<TH2F>("bx_Wm2_RB1in_S06_abort","bx_Wm2_RB1in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S06_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S06_prebeam","bx_Wm2_RB1in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S07_abort = fs->make<TH2F>("bx_Wm2_RB1in_S07_abort","bx_Wm2_RB1in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S07_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S07_prebeam","bx_Wm2_RB1in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S08_abort = fs->make<TH2F>("bx_Wm2_RB1in_S08_abort","bx_Wm2_RB1in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S08_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S08_prebeam","bx_Wm2_RB1in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S09_abort = fs->make<TH2F>("bx_Wm2_RB1in_S09_abort","bx_Wm2_RB1in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S09_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S09_prebeam","bx_Wm2_RB1in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S10_abort = fs->make<TH2F>("bx_Wm2_RB1in_S10_abort","bx_Wm2_RB1in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S10_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S10_prebeam","bx_Wm2_RB1in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S11_abort = fs->make<TH2F>("bx_Wm2_RB1in_S11_abort","bx_Wm2_RB1in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S11_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S11_prebeam","bx_Wm2_RB1in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S12_abort = fs->make<TH2F>("bx_Wm2_RB1in_S12_abort","bx_Wm2_RB1in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_S12_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_S12_prebeam","bx_Wm2_RB1in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S01_abort = fs->make<TH2F>("bx_Wm1_RB1in_S01_abort","bx_Wm1_RB1in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S01_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S01_prebeam","bx_Wm1_RB1in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S02_abort = fs->make<TH2F>("bx_Wm1_RB1in_S02_abort","bx_Wm1_RB1in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S02_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S02_prebeam","bx_Wm1_RB1in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S03_abort = fs->make<TH2F>("bx_Wm1_RB1in_S03_abort","bx_Wm1_RB1in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S03_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S03_prebeam","bx_Wm1_RB1in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S04_abort = fs->make<TH2F>("bx_Wm1_RB1in_S04_abort","bx_Wm1_RB1in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S04_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S04_prebeam","bx_Wm1_RB1in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S05_abort = fs->make<TH2F>("bx_Wm1_RB1in_S05_abort","bx_Wm1_RB1in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S05_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S05_prebeam","bx_Wm1_RB1in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S06_abort = fs->make<TH2F>("bx_Wm1_RB1in_S06_abort","bx_Wm1_RB1in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S06_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S06_prebeam","bx_Wm1_RB1in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S07_abort = fs->make<TH2F>("bx_Wm1_RB1in_S07_abort","bx_Wm1_RB1in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S07_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S07_prebeam","bx_Wm1_RB1in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S08_abort = fs->make<TH2F>("bx_Wm1_RB1in_S08_abort","bx_Wm1_RB1in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S08_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S08_prebeam","bx_Wm1_RB1in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S09_abort = fs->make<TH2F>("bx_Wm1_RB1in_S09_abort","bx_Wm1_RB1in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S09_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S09_prebeam","bx_Wm1_RB1in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S10_abort = fs->make<TH2F>("bx_Wm1_RB1in_S10_abort","bx_Wm1_RB1in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S10_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S10_prebeam","bx_Wm1_RB1in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S11_abort = fs->make<TH2F>("bx_Wm1_RB1in_S11_abort","bx_Wm1_RB1in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S11_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S11_prebeam","bx_Wm1_RB1in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S12_abort = fs->make<TH2F>("bx_Wm1_RB1in_S12_abort","bx_Wm1_RB1in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_S12_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_S12_prebeam","bx_Wm1_RB1in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S01_abort = fs->make<TH2F>("bx_W0_RB1in_S01_abort","bx_W0_RB1in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S01_prebeam = fs->make<TH2F>("bx_W0_RB1in_S01_prebeam","bx_W0_RB1in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S02_abort = fs->make<TH2F>("bx_W0_RB1in_S02_abort","bx_W0_RB1in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S02_prebeam = fs->make<TH2F>("bx_W0_RB1in_S02_prebeam","bx_W0_RB1in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S03_abort = fs->make<TH2F>("bx_W0_RB1in_S03_abort","bx_W0_RB1in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S03_prebeam = fs->make<TH2F>("bx_W0_RB1in_S03_prebeam","bx_W0_RB1in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S04_abort = fs->make<TH2F>("bx_W0_RB1in_S04_abort","bx_W0_RB1in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S04_prebeam = fs->make<TH2F>("bx_W0_RB1in_S04_prebeam","bx_W0_RB1in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S05_abort = fs->make<TH2F>("bx_W0_RB1in_S05_abort","bx_W0_RB1in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S05_prebeam = fs->make<TH2F>("bx_W0_RB1in_S05_prebeam","bx_W0_RB1in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S06_abort = fs->make<TH2F>("bx_W0_RB1in_S06_abort","bx_W0_RB1in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S06_prebeam = fs->make<TH2F>("bx_W0_RB1in_S06_prebeam","bx_W0_RB1in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S07_abort = fs->make<TH2F>("bx_W0_RB1in_S07_abort","bx_W0_RB1in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S07_prebeam = fs->make<TH2F>("bx_W0_RB1in_S07_prebeam","bx_W0_RB1in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S08_abort = fs->make<TH2F>("bx_W0_RB1in_S08_abort","bx_W0_RB1in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S08_prebeam = fs->make<TH2F>("bx_W0_RB1in_S08_prebeam","bx_W0_RB1in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S09_abort = fs->make<TH2F>("bx_W0_RB1in_S09_abort","bx_W0_RB1in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S09_prebeam = fs->make<TH2F>("bx_W0_RB1in_S09_prebeam","bx_W0_RB1in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S10_abort = fs->make<TH2F>("bx_W0_RB1in_S10_abort","bx_W0_RB1in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S10_prebeam = fs->make<TH2F>("bx_W0_RB1in_S10_prebeam","bx_W0_RB1in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S11_abort = fs->make<TH2F>("bx_W0_RB1in_S11_abort","bx_W0_RB1in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S11_prebeam = fs->make<TH2F>("bx_W0_RB1in_S11_prebeam","bx_W0_RB1in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S12_abort = fs->make<TH2F>("bx_W0_RB1in_S12_abort","bx_W0_RB1in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_S12_prebeam = fs->make<TH2F>("bx_W0_RB1in_S12_prebeam","bx_W0_RB1in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S01_abort = fs->make<TH2F>("bx_Wp1_RB1in_S01_abort","bx_Wp1_RB1in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S01_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S01_prebeam","bx_Wp1_RB1in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S02_abort = fs->make<TH2F>("bx_Wp1_RB1in_S02_abort","bx_Wp1_RB1in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S02_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S02_prebeam","bx_Wp1_RB1in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S03_abort = fs->make<TH2F>("bx_Wp1_RB1in_S03_abort","bx_Wp1_RB1in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S03_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S03_prebeam","bx_Wp1_RB1in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S04_abort = fs->make<TH2F>("bx_Wp1_RB1in_S04_abort","bx_Wp1_RB1in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S04_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S04_prebeam","bx_Wp1_RB1in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S05_abort = fs->make<TH2F>("bx_Wp1_RB1in_S05_abort","bx_Wp1_RB1in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S05_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S05_prebeam","bx_Wp1_RB1in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S06_abort = fs->make<TH2F>("bx_Wp1_RB1in_S06_abort","bx_Wp1_RB1in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S06_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S06_prebeam","bx_Wp1_RB1in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S07_abort = fs->make<TH2F>("bx_Wp1_RB1in_S07_abort","bx_Wp1_RB1in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S07_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S07_prebeam","bx_Wp1_RB1in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S08_abort = fs->make<TH2F>("bx_Wp1_RB1in_S08_abort","bx_Wp1_RB1in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S08_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S08_prebeam","bx_Wp1_RB1in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S09_abort = fs->make<TH2F>("bx_Wp1_RB1in_S09_abort","bx_Wp1_RB1in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S09_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S09_prebeam","bx_Wp1_RB1in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S10_abort = fs->make<TH2F>("bx_Wp1_RB1in_S10_abort","bx_Wp1_RB1in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S10_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S10_prebeam","bx_Wp1_RB1in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S11_abort = fs->make<TH2F>("bx_Wp1_RB1in_S11_abort","bx_Wp1_RB1in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S11_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S11_prebeam","bx_Wp1_RB1in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S12_abort = fs->make<TH2F>("bx_Wp1_RB1in_S12_abort","bx_Wp1_RB1in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_S12_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_S12_prebeam","bx_Wp1_RB1in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S01_abort = fs->make<TH2F>("bx_Wp2_RB1in_S01_abort","bx_Wp2_RB1in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S01_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S01_prebeam","bx_Wp2_RB1in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S02_abort = fs->make<TH2F>("bx_Wp2_RB1in_S02_abort","bx_Wp2_RB1in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S02_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S02_prebeam","bx_Wp2_RB1in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S03_abort = fs->make<TH2F>("bx_Wp2_RB1in_S03_abort","bx_Wp2_RB1in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S03_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S03_prebeam","bx_Wp2_RB1in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S04_abort = fs->make<TH2F>("bx_Wp2_RB1in_S04_abort","bx_Wp2_RB1in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S04_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S04_prebeam","bx_Wp2_RB1in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S05_abort = fs->make<TH2F>("bx_Wp2_RB1in_S05_abort","bx_Wp2_RB1in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S05_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S05_prebeam","bx_Wp2_RB1in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S06_abort = fs->make<TH2F>("bx_Wp2_RB1in_S06_abort","bx_Wp2_RB1in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S06_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S06_prebeam","bx_Wp2_RB1in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S07_abort = fs->make<TH2F>("bx_Wp2_RB1in_S07_abort","bx_Wp2_RB1in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S07_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S07_prebeam","bx_Wp2_RB1in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S08_abort = fs->make<TH2F>("bx_Wp2_RB1in_S08_abort","bx_Wp2_RB1in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S08_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S08_prebeam","bx_Wp2_RB1in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S09_abort = fs->make<TH2F>("bx_Wp2_RB1in_S09_abort","bx_Wp2_RB1in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S09_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S09_prebeam","bx_Wp2_RB1in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S10_abort = fs->make<TH2F>("bx_Wp2_RB1in_S10_abort","bx_Wp2_RB1in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S10_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S10_prebeam","bx_Wp2_RB1in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S11_abort = fs->make<TH2F>("bx_Wp2_RB1in_S11_abort","bx_Wp2_RB1in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S11_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S11_prebeam","bx_Wp2_RB1in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S12_abort = fs->make<TH2F>("bx_Wp2_RB1in_S12_abort","bx_Wp2_RB1in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_S12_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_S12_prebeam","bx_Wp2_RB1in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S01_abort = fs->make<TH2F>("bx_Wm2_RB1out_S01_abort","bx_Wm2_RB1out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S01_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S01_prebeam","bx_Wm2_RB1out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S02_abort = fs->make<TH2F>("bx_Wm2_RB1out_S02_abort","bx_Wm2_RB1out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S02_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S02_prebeam","bx_Wm2_RB1out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S03_abort = fs->make<TH2F>("bx_Wm2_RB1out_S03_abort","bx_Wm2_RB1out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S03_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S03_prebeam","bx_Wm2_RB1out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S04_abort = fs->make<TH2F>("bx_Wm2_RB1out_S04_abort","bx_Wm2_RB1out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S04_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S04_prebeam","bx_Wm2_RB1out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S05_abort = fs->make<TH2F>("bx_Wm2_RB1out_S05_abort","bx_Wm2_RB1out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S05_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S05_prebeam","bx_Wm2_RB1out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S06_abort = fs->make<TH2F>("bx_Wm2_RB1out_S06_abort","bx_Wm2_RB1out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S06_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S06_prebeam","bx_Wm2_RB1out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S07_abort = fs->make<TH2F>("bx_Wm2_RB1out_S07_abort","bx_Wm2_RB1out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S07_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S07_prebeam","bx_Wm2_RB1out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S08_abort = fs->make<TH2F>("bx_Wm2_RB1out_S08_abort","bx_Wm2_RB1out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S08_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S08_prebeam","bx_Wm2_RB1out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S09_abort = fs->make<TH2F>("bx_Wm2_RB1out_S09_abort","bx_Wm2_RB1out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S09_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S09_prebeam","bx_Wm2_RB1out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S10_abort = fs->make<TH2F>("bx_Wm2_RB1out_S10_abort","bx_Wm2_RB1out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S10_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S10_prebeam","bx_Wm2_RB1out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S11_abort = fs->make<TH2F>("bx_Wm2_RB1out_S11_abort","bx_Wm2_RB1out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S11_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S11_prebeam","bx_Wm2_RB1out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S12_abort = fs->make<TH2F>("bx_Wm2_RB1out_S12_abort","bx_Wm2_RB1out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_S12_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_S12_prebeam","bx_Wm2_RB1out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S01_abort = fs->make<TH2F>("bx_Wm1_RB1out_S01_abort","bx_Wm1_RB1out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S01_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S01_prebeam","bx_Wm1_RB1out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S02_abort = fs->make<TH2F>("bx_Wm1_RB1out_S02_abort","bx_Wm1_RB1out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S02_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S02_prebeam","bx_Wm1_RB1out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S03_abort = fs->make<TH2F>("bx_Wm1_RB1out_S03_abort","bx_Wm1_RB1out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S03_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S03_prebeam","bx_Wm1_RB1out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S04_abort = fs->make<TH2F>("bx_Wm1_RB1out_S04_abort","bx_Wm1_RB1out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S04_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S04_prebeam","bx_Wm1_RB1out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S05_abort = fs->make<TH2F>("bx_Wm1_RB1out_S05_abort","bx_Wm1_RB1out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S05_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S05_prebeam","bx_Wm1_RB1out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S06_abort = fs->make<TH2F>("bx_Wm1_RB1out_S06_abort","bx_Wm1_RB1out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S06_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S06_prebeam","bx_Wm1_RB1out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S07_abort = fs->make<TH2F>("bx_Wm1_RB1out_S07_abort","bx_Wm1_RB1out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S07_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S07_prebeam","bx_Wm1_RB1out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S08_abort = fs->make<TH2F>("bx_Wm1_RB1out_S08_abort","bx_Wm1_RB1out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S08_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S08_prebeam","bx_Wm1_RB1out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S09_abort = fs->make<TH2F>("bx_Wm1_RB1out_S09_abort","bx_Wm1_RB1out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S09_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S09_prebeam","bx_Wm1_RB1out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S10_abort = fs->make<TH2F>("bx_Wm1_RB1out_S10_abort","bx_Wm1_RB1out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S10_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S10_prebeam","bx_Wm1_RB1out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S11_abort = fs->make<TH2F>("bx_Wm1_RB1out_S11_abort","bx_Wm1_RB1out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S11_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S11_prebeam","bx_Wm1_RB1out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S12_abort = fs->make<TH2F>("bx_Wm1_RB1out_S12_abort","bx_Wm1_RB1out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_S12_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_S12_prebeam","bx_Wm1_RB1out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S01_abort = fs->make<TH2F>("bx_W0_RB1out_S01_abort","bx_W0_RB1out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S01_prebeam = fs->make<TH2F>("bx_W0_RB1out_S01_prebeam","bx_W0_RB1out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S02_abort = fs->make<TH2F>("bx_W0_RB1out_S02_abort","bx_W0_RB1out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S02_prebeam = fs->make<TH2F>("bx_W0_RB1out_S02_prebeam","bx_W0_RB1out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S03_abort = fs->make<TH2F>("bx_W0_RB1out_S03_abort","bx_W0_RB1out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S03_prebeam = fs->make<TH2F>("bx_W0_RB1out_S03_prebeam","bx_W0_RB1out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S04_abort = fs->make<TH2F>("bx_W0_RB1out_S04_abort","bx_W0_RB1out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S04_prebeam = fs->make<TH2F>("bx_W0_RB1out_S04_prebeam","bx_W0_RB1out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S05_abort = fs->make<TH2F>("bx_W0_RB1out_S05_abort","bx_W0_RB1out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S05_prebeam = fs->make<TH2F>("bx_W0_RB1out_S05_prebeam","bx_W0_RB1out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S06_abort = fs->make<TH2F>("bx_W0_RB1out_S06_abort","bx_W0_RB1out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S06_prebeam = fs->make<TH2F>("bx_W0_RB1out_S06_prebeam","bx_W0_RB1out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S07_abort = fs->make<TH2F>("bx_W0_RB1out_S07_abort","bx_W0_RB1out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S07_prebeam = fs->make<TH2F>("bx_W0_RB1out_S07_prebeam","bx_W0_RB1out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S08_abort = fs->make<TH2F>("bx_W0_RB1out_S08_abort","bx_W0_RB1out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S08_prebeam = fs->make<TH2F>("bx_W0_RB1out_S08_prebeam","bx_W0_RB1out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S09_abort = fs->make<TH2F>("bx_W0_RB1out_S09_abort","bx_W0_RB1out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S09_prebeam = fs->make<TH2F>("bx_W0_RB1out_S09_prebeam","bx_W0_RB1out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S10_abort = fs->make<TH2F>("bx_W0_RB1out_S10_abort","bx_W0_RB1out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S10_prebeam = fs->make<TH2F>("bx_W0_RB1out_S10_prebeam","bx_W0_RB1out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S11_abort = fs->make<TH2F>("bx_W0_RB1out_S11_abort","bx_W0_RB1out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S11_prebeam = fs->make<TH2F>("bx_W0_RB1out_S11_prebeam","bx_W0_RB1out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S12_abort = fs->make<TH2F>("bx_W0_RB1out_S12_abort","bx_W0_RB1out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_S12_prebeam = fs->make<TH2F>("bx_W0_RB1out_S12_prebeam","bx_W0_RB1out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S01_abort = fs->make<TH2F>("bx_Wp1_RB1out_S01_abort","bx_Wp1_RB1out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S01_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S01_prebeam","bx_Wp1_RB1out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S02_abort = fs->make<TH2F>("bx_Wp1_RB1out_S02_abort","bx_Wp1_RB1out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S02_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S02_prebeam","bx_Wp1_RB1out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S03_abort = fs->make<TH2F>("bx_Wp1_RB1out_S03_abort","bx_Wp1_RB1out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S03_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S03_prebeam","bx_Wp1_RB1out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S04_abort = fs->make<TH2F>("bx_Wp1_RB1out_S04_abort","bx_Wp1_RB1out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S04_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S04_prebeam","bx_Wp1_RB1out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S05_abort = fs->make<TH2F>("bx_Wp1_RB1out_S05_abort","bx_Wp1_RB1out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S05_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S05_prebeam","bx_Wp1_RB1out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S06_abort = fs->make<TH2F>("bx_Wp1_RB1out_S06_abort","bx_Wp1_RB1out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S06_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S06_prebeam","bx_Wp1_RB1out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S07_abort = fs->make<TH2F>("bx_Wp1_RB1out_S07_abort","bx_Wp1_RB1out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S07_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S07_prebeam","bx_Wp1_RB1out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S08_abort = fs->make<TH2F>("bx_Wp1_RB1out_S08_abort","bx_Wp1_RB1out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S08_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S08_prebeam","bx_Wp1_RB1out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S09_abort = fs->make<TH2F>("bx_Wp1_RB1out_S09_abort","bx_Wp1_RB1out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S09_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S09_prebeam","bx_Wp1_RB1out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S10_abort = fs->make<TH2F>("bx_Wp1_RB1out_S10_abort","bx_Wp1_RB1out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S10_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S10_prebeam","bx_Wp1_RB1out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S11_abort = fs->make<TH2F>("bx_Wp1_RB1out_S11_abort","bx_Wp1_RB1out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S11_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S11_prebeam","bx_Wp1_RB1out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S12_abort = fs->make<TH2F>("bx_Wp1_RB1out_S12_abort","bx_Wp1_RB1out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_S12_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_S12_prebeam","bx_Wp1_RB1out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S01_abort = fs->make<TH2F>("bx_Wp2_RB1out_S01_abort","bx_Wp2_RB1out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S01_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S01_prebeam","bx_Wp2_RB1out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S02_abort = fs->make<TH2F>("bx_Wp2_RB1out_S02_abort","bx_Wp2_RB1out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S02_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S02_prebeam","bx_Wp2_RB1out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S03_abort = fs->make<TH2F>("bx_Wp2_RB1out_S03_abort","bx_Wp2_RB1out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S03_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S03_prebeam","bx_Wp2_RB1out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S04_abort = fs->make<TH2F>("bx_Wp2_RB1out_S04_abort","bx_Wp2_RB1out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S04_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S04_prebeam","bx_Wp2_RB1out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S05_abort = fs->make<TH2F>("bx_Wp2_RB1out_S05_abort","bx_Wp2_RB1out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S05_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S05_prebeam","bx_Wp2_RB1out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S06_abort = fs->make<TH2F>("bx_Wp2_RB1out_S06_abort","bx_Wp2_RB1out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S06_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S06_prebeam","bx_Wp2_RB1out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S07_abort = fs->make<TH2F>("bx_Wp2_RB1out_S07_abort","bx_Wp2_RB1out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S07_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S07_prebeam","bx_Wp2_RB1out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S08_abort = fs->make<TH2F>("bx_Wp2_RB1out_S08_abort","bx_Wp2_RB1out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S08_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S08_prebeam","bx_Wp2_RB1out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S09_abort = fs->make<TH2F>("bx_Wp2_RB1out_S09_abort","bx_Wp2_RB1out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S09_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S09_prebeam","bx_Wp2_RB1out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S10_abort = fs->make<TH2F>("bx_Wp2_RB1out_S10_abort","bx_Wp2_RB1out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S10_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S10_prebeam","bx_Wp2_RB1out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S11_abort = fs->make<TH2F>("bx_Wp2_RB1out_S11_abort","bx_Wp2_RB1out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S11_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S11_prebeam","bx_Wp2_RB1out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S12_abort = fs->make<TH2F>("bx_Wp2_RB1out_S12_abort","bx_Wp2_RB1out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_S12_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_S12_prebeam","bx_Wp2_RB1out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S01_abort = fs->make<TH2F>("bx_Wm2_RB2in_S01_abort","bx_Wm2_RB2in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S01_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S01_prebeam","bx_Wm2_RB2in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S02_abort = fs->make<TH2F>("bx_Wm2_RB2in_S02_abort","bx_Wm2_RB2in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S02_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S02_prebeam","bx_Wm2_RB2in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S03_abort = fs->make<TH2F>("bx_Wm2_RB2in_S03_abort","bx_Wm2_RB2in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S03_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S03_prebeam","bx_Wm2_RB2in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S04_abort = fs->make<TH2F>("bx_Wm2_RB2in_S04_abort","bx_Wm2_RB2in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S04_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S04_prebeam","bx_Wm2_RB2in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S05_abort = fs->make<TH2F>("bx_Wm2_RB2in_S05_abort","bx_Wm2_RB2in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S05_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S05_prebeam","bx_Wm2_RB2in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S06_abort = fs->make<TH2F>("bx_Wm2_RB2in_S06_abort","bx_Wm2_RB2in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S06_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S06_prebeam","bx_Wm2_RB2in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S07_abort = fs->make<TH2F>("bx_Wm2_RB2in_S07_abort","bx_Wm2_RB2in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S07_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S07_prebeam","bx_Wm2_RB2in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S08_abort = fs->make<TH2F>("bx_Wm2_RB2in_S08_abort","bx_Wm2_RB2in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S08_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S08_prebeam","bx_Wm2_RB2in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S09_abort = fs->make<TH2F>("bx_Wm2_RB2in_S09_abort","bx_Wm2_RB2in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S09_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S09_prebeam","bx_Wm2_RB2in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S10_abort = fs->make<TH2F>("bx_Wm2_RB2in_S10_abort","bx_Wm2_RB2in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S10_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S10_prebeam","bx_Wm2_RB2in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S11_abort = fs->make<TH2F>("bx_Wm2_RB2in_S11_abort","bx_Wm2_RB2in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S11_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S11_prebeam","bx_Wm2_RB2in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S12_abort = fs->make<TH2F>("bx_Wm2_RB2in_S12_abort","bx_Wm2_RB2in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_S12_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_S12_prebeam","bx_Wm2_RB2in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S01_abort = fs->make<TH2F>("bx_Wm1_RB2in_S01_abort","bx_Wm1_RB2in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S01_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S01_prebeam","bx_Wm1_RB2in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S02_abort = fs->make<TH2F>("bx_Wm1_RB2in_S02_abort","bx_Wm1_RB2in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S02_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S02_prebeam","bx_Wm1_RB2in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S03_abort = fs->make<TH2F>("bx_Wm1_RB2in_S03_abort","bx_Wm1_RB2in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S03_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S03_prebeam","bx_Wm1_RB2in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S04_abort = fs->make<TH2F>("bx_Wm1_RB2in_S04_abort","bx_Wm1_RB2in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S04_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S04_prebeam","bx_Wm1_RB2in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S05_abort = fs->make<TH2F>("bx_Wm1_RB2in_S05_abort","bx_Wm1_RB2in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S05_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S05_prebeam","bx_Wm1_RB2in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S06_abort = fs->make<TH2F>("bx_Wm1_RB2in_S06_abort","bx_Wm1_RB2in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S06_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S06_prebeam","bx_Wm1_RB2in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S07_abort = fs->make<TH2F>("bx_Wm1_RB2in_S07_abort","bx_Wm1_RB2in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S07_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S07_prebeam","bx_Wm1_RB2in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S08_abort = fs->make<TH2F>("bx_Wm1_RB2in_S08_abort","bx_Wm1_RB2in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S08_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S08_prebeam","bx_Wm1_RB2in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S09_abort = fs->make<TH2F>("bx_Wm1_RB2in_S09_abort","bx_Wm1_RB2in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S09_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S09_prebeam","bx_Wm1_RB2in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S10_abort = fs->make<TH2F>("bx_Wm1_RB2in_S10_abort","bx_Wm1_RB2in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S10_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S10_prebeam","bx_Wm1_RB2in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S11_abort = fs->make<TH2F>("bx_Wm1_RB2in_S11_abort","bx_Wm1_RB2in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S11_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S11_prebeam","bx_Wm1_RB2in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S12_abort = fs->make<TH2F>("bx_Wm1_RB2in_S12_abort","bx_Wm1_RB2in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_S12_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_S12_prebeam","bx_Wm1_RB2in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S01_abort = fs->make<TH2F>("bx_W0_RB2in_S01_abort","bx_W0_RB2in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S01_prebeam = fs->make<TH2F>("bx_W0_RB2in_S01_prebeam","bx_W0_RB2in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S02_abort = fs->make<TH2F>("bx_W0_RB2in_S02_abort","bx_W0_RB2in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S02_prebeam = fs->make<TH2F>("bx_W0_RB2in_S02_prebeam","bx_W0_RB2in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S03_abort = fs->make<TH2F>("bx_W0_RB2in_S03_abort","bx_W0_RB2in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S03_prebeam = fs->make<TH2F>("bx_W0_RB2in_S03_prebeam","bx_W0_RB2in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S04_abort = fs->make<TH2F>("bx_W0_RB2in_S04_abort","bx_W0_RB2in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S04_prebeam = fs->make<TH2F>("bx_W0_RB2in_S04_prebeam","bx_W0_RB2in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S05_abort = fs->make<TH2F>("bx_W0_RB2in_S05_abort","bx_W0_RB2in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S05_prebeam = fs->make<TH2F>("bx_W0_RB2in_S05_prebeam","bx_W0_RB2in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S06_abort = fs->make<TH2F>("bx_W0_RB2in_S06_abort","bx_W0_RB2in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S06_prebeam = fs->make<TH2F>("bx_W0_RB2in_S06_prebeam","bx_W0_RB2in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S07_abort = fs->make<TH2F>("bx_W0_RB2in_S07_abort","bx_W0_RB2in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S07_prebeam = fs->make<TH2F>("bx_W0_RB2in_S07_prebeam","bx_W0_RB2in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S08_abort = fs->make<TH2F>("bx_W0_RB2in_S08_abort","bx_W0_RB2in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S08_prebeam = fs->make<TH2F>("bx_W0_RB2in_S08_prebeam","bx_W0_RB2in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S09_abort = fs->make<TH2F>("bx_W0_RB2in_S09_abort","bx_W0_RB2in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S09_prebeam = fs->make<TH2F>("bx_W0_RB2in_S09_prebeam","bx_W0_RB2in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S10_abort = fs->make<TH2F>("bx_W0_RB2in_S10_abort","bx_W0_RB2in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S10_prebeam = fs->make<TH2F>("bx_W0_RB2in_S10_prebeam","bx_W0_RB2in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S11_abort = fs->make<TH2F>("bx_W0_RB2in_S11_abort","bx_W0_RB2in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S11_prebeam = fs->make<TH2F>("bx_W0_RB2in_S11_prebeam","bx_W0_RB2in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S12_abort = fs->make<TH2F>("bx_W0_RB2in_S12_abort","bx_W0_RB2in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_S12_prebeam = fs->make<TH2F>("bx_W0_RB2in_S12_prebeam","bx_W0_RB2in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S01_abort = fs->make<TH2F>("bx_Wp1_RB2in_S01_abort","bx_Wp1_RB2in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S01_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S01_prebeam","bx_Wp1_RB2in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S02_abort = fs->make<TH2F>("bx_Wp1_RB2in_S02_abort","bx_Wp1_RB2in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S02_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S02_prebeam","bx_Wp1_RB2in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S03_abort = fs->make<TH2F>("bx_Wp1_RB2in_S03_abort","bx_Wp1_RB2in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S03_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S03_prebeam","bx_Wp1_RB2in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S04_abort = fs->make<TH2F>("bx_Wp1_RB2in_S04_abort","bx_Wp1_RB2in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S04_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S04_prebeam","bx_Wp1_RB2in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S05_abort = fs->make<TH2F>("bx_Wp1_RB2in_S05_abort","bx_Wp1_RB2in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S05_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S05_prebeam","bx_Wp1_RB2in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S06_abort = fs->make<TH2F>("bx_Wp1_RB2in_S06_abort","bx_Wp1_RB2in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S06_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S06_prebeam","bx_Wp1_RB2in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S07_abort = fs->make<TH2F>("bx_Wp1_RB2in_S07_abort","bx_Wp1_RB2in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S07_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S07_prebeam","bx_Wp1_RB2in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S08_abort = fs->make<TH2F>("bx_Wp1_RB2in_S08_abort","bx_Wp1_RB2in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S08_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S08_prebeam","bx_Wp1_RB2in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S09_abort = fs->make<TH2F>("bx_Wp1_RB2in_S09_abort","bx_Wp1_RB2in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S09_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S09_prebeam","bx_Wp1_RB2in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S10_abort = fs->make<TH2F>("bx_Wp1_RB2in_S10_abort","bx_Wp1_RB2in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S10_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S10_prebeam","bx_Wp1_RB2in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S11_abort = fs->make<TH2F>("bx_Wp1_RB2in_S11_abort","bx_Wp1_RB2in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S11_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S11_prebeam","bx_Wp1_RB2in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S12_abort = fs->make<TH2F>("bx_Wp1_RB2in_S12_abort","bx_Wp1_RB2in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_S12_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_S12_prebeam","bx_Wp1_RB2in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S01_abort = fs->make<TH2F>("bx_Wp2_RB2in_S01_abort","bx_Wp2_RB2in_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S01_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S01_prebeam","bx_Wp2_RB2in_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S02_abort = fs->make<TH2F>("bx_Wp2_RB2in_S02_abort","bx_Wp2_RB2in_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S02_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S02_prebeam","bx_Wp2_RB2in_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S03_abort = fs->make<TH2F>("bx_Wp2_RB2in_S03_abort","bx_Wp2_RB2in_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S03_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S03_prebeam","bx_Wp2_RB2in_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S04_abort = fs->make<TH2F>("bx_Wp2_RB2in_S04_abort","bx_Wp2_RB2in_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S04_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S04_prebeam","bx_Wp2_RB2in_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S05_abort = fs->make<TH2F>("bx_Wp2_RB2in_S05_abort","bx_Wp2_RB2in_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S05_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S05_prebeam","bx_Wp2_RB2in_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S06_abort = fs->make<TH2F>("bx_Wp2_RB2in_S06_abort","bx_Wp2_RB2in_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S06_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S06_prebeam","bx_Wp2_RB2in_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S07_abort = fs->make<TH2F>("bx_Wp2_RB2in_S07_abort","bx_Wp2_RB2in_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S07_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S07_prebeam","bx_Wp2_RB2in_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S08_abort = fs->make<TH2F>("bx_Wp2_RB2in_S08_abort","bx_Wp2_RB2in_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S08_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S08_prebeam","bx_Wp2_RB2in_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S09_abort = fs->make<TH2F>("bx_Wp2_RB2in_S09_abort","bx_Wp2_RB2in_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S09_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S09_prebeam","bx_Wp2_RB2in_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S10_abort = fs->make<TH2F>("bx_Wp2_RB2in_S10_abort","bx_Wp2_RB2in_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S10_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S10_prebeam","bx_Wp2_RB2in_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S11_abort = fs->make<TH2F>("bx_Wp2_RB2in_S11_abort","bx_Wp2_RB2in_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S11_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S11_prebeam","bx_Wp2_RB2in_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S12_abort = fs->make<TH2F>("bx_Wp2_RB2in_S12_abort","bx_Wp2_RB2in_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_S12_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_S12_prebeam","bx_Wp2_RB2in_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S01_abort = fs->make<TH2F>("bx_Wm2_RB2out_S01_abort","bx_Wm2_RB2out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S01_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S01_prebeam","bx_Wm2_RB2out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S02_abort = fs->make<TH2F>("bx_Wm2_RB2out_S02_abort","bx_Wm2_RB2out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S02_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S02_prebeam","bx_Wm2_RB2out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S03_abort = fs->make<TH2F>("bx_Wm2_RB2out_S03_abort","bx_Wm2_RB2out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S03_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S03_prebeam","bx_Wm2_RB2out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S04_abort = fs->make<TH2F>("bx_Wm2_RB2out_S04_abort","bx_Wm2_RB2out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S04_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S04_prebeam","bx_Wm2_RB2out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S05_abort = fs->make<TH2F>("bx_Wm2_RB2out_S05_abort","bx_Wm2_RB2out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S05_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S05_prebeam","bx_Wm2_RB2out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S06_abort = fs->make<TH2F>("bx_Wm2_RB2out_S06_abort","bx_Wm2_RB2out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S06_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S06_prebeam","bx_Wm2_RB2out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S07_abort = fs->make<TH2F>("bx_Wm2_RB2out_S07_abort","bx_Wm2_RB2out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S07_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S07_prebeam","bx_Wm2_RB2out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S08_abort = fs->make<TH2F>("bx_Wm2_RB2out_S08_abort","bx_Wm2_RB2out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S08_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S08_prebeam","bx_Wm2_RB2out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S09_abort = fs->make<TH2F>("bx_Wm2_RB2out_S09_abort","bx_Wm2_RB2out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S09_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S09_prebeam","bx_Wm2_RB2out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S10_abort = fs->make<TH2F>("bx_Wm2_RB2out_S10_abort","bx_Wm2_RB2out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S10_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S10_prebeam","bx_Wm2_RB2out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S11_abort = fs->make<TH2F>("bx_Wm2_RB2out_S11_abort","bx_Wm2_RB2out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S11_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S11_prebeam","bx_Wm2_RB2out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S12_abort = fs->make<TH2F>("bx_Wm2_RB2out_S12_abort","bx_Wm2_RB2out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_S12_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_S12_prebeam","bx_Wm2_RB2out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S01_abort = fs->make<TH2F>("bx_Wm1_RB2out_S01_abort","bx_Wm1_RB2out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S01_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S01_prebeam","bx_Wm1_RB2out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S02_abort = fs->make<TH2F>("bx_Wm1_RB2out_S02_abort","bx_Wm1_RB2out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S02_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S02_prebeam","bx_Wm1_RB2out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S03_abort = fs->make<TH2F>("bx_Wm1_RB2out_S03_abort","bx_Wm1_RB2out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S03_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S03_prebeam","bx_Wm1_RB2out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S04_abort = fs->make<TH2F>("bx_Wm1_RB2out_S04_abort","bx_Wm1_RB2out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S04_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S04_prebeam","bx_Wm1_RB2out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S05_abort = fs->make<TH2F>("bx_Wm1_RB2out_S05_abort","bx_Wm1_RB2out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S05_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S05_prebeam","bx_Wm1_RB2out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S06_abort = fs->make<TH2F>("bx_Wm1_RB2out_S06_abort","bx_Wm1_RB2out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S06_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S06_prebeam","bx_Wm1_RB2out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S07_abort = fs->make<TH2F>("bx_Wm1_RB2out_S07_abort","bx_Wm1_RB2out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S07_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S07_prebeam","bx_Wm1_RB2out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S08_abort = fs->make<TH2F>("bx_Wm1_RB2out_S08_abort","bx_Wm1_RB2out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S08_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S08_prebeam","bx_Wm1_RB2out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S09_abort = fs->make<TH2F>("bx_Wm1_RB2out_S09_abort","bx_Wm1_RB2out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S09_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S09_prebeam","bx_Wm1_RB2out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S10_abort = fs->make<TH2F>("bx_Wm1_RB2out_S10_abort","bx_Wm1_RB2out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S10_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S10_prebeam","bx_Wm1_RB2out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S11_abort = fs->make<TH2F>("bx_Wm1_RB2out_S11_abort","bx_Wm1_RB2out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S11_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S11_prebeam","bx_Wm1_RB2out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S12_abort = fs->make<TH2F>("bx_Wm1_RB2out_S12_abort","bx_Wm1_RB2out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_S12_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_S12_prebeam","bx_Wm1_RB2out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S01_abort = fs->make<TH2F>("bx_W0_RB2out_S01_abort","bx_W0_RB2out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S01_prebeam = fs->make<TH2F>("bx_W0_RB2out_S01_prebeam","bx_W0_RB2out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S02_abort = fs->make<TH2F>("bx_W0_RB2out_S02_abort","bx_W0_RB2out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S02_prebeam = fs->make<TH2F>("bx_W0_RB2out_S02_prebeam","bx_W0_RB2out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S03_abort = fs->make<TH2F>("bx_W0_RB2out_S03_abort","bx_W0_RB2out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S03_prebeam = fs->make<TH2F>("bx_W0_RB2out_S03_prebeam","bx_W0_RB2out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S04_abort = fs->make<TH2F>("bx_W0_RB2out_S04_abort","bx_W0_RB2out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S04_prebeam = fs->make<TH2F>("bx_W0_RB2out_S04_prebeam","bx_W0_RB2out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S05_abort = fs->make<TH2F>("bx_W0_RB2out_S05_abort","bx_W0_RB2out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S05_prebeam = fs->make<TH2F>("bx_W0_RB2out_S05_prebeam","bx_W0_RB2out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S06_abort = fs->make<TH2F>("bx_W0_RB2out_S06_abort","bx_W0_RB2out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S06_prebeam = fs->make<TH2F>("bx_W0_RB2out_S06_prebeam","bx_W0_RB2out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S07_abort = fs->make<TH2F>("bx_W0_RB2out_S07_abort","bx_W0_RB2out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S07_prebeam = fs->make<TH2F>("bx_W0_RB2out_S07_prebeam","bx_W0_RB2out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S08_abort = fs->make<TH2F>("bx_W0_RB2out_S08_abort","bx_W0_RB2out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S08_prebeam = fs->make<TH2F>("bx_W0_RB2out_S08_prebeam","bx_W0_RB2out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S09_abort = fs->make<TH2F>("bx_W0_RB2out_S09_abort","bx_W0_RB2out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S09_prebeam = fs->make<TH2F>("bx_W0_RB2out_S09_prebeam","bx_W0_RB2out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S10_abort = fs->make<TH2F>("bx_W0_RB2out_S10_abort","bx_W0_RB2out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S10_prebeam = fs->make<TH2F>("bx_W0_RB2out_S10_prebeam","bx_W0_RB2out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S11_abort = fs->make<TH2F>("bx_W0_RB2out_S11_abort","bx_W0_RB2out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S11_prebeam = fs->make<TH2F>("bx_W0_RB2out_S11_prebeam","bx_W0_RB2out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S12_abort = fs->make<TH2F>("bx_W0_RB2out_S12_abort","bx_W0_RB2out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_S12_prebeam = fs->make<TH2F>("bx_W0_RB2out_S12_prebeam","bx_W0_RB2out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S01_abort = fs->make<TH2F>("bx_Wp1_RB2out_S01_abort","bx_Wp1_RB2out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S01_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S01_prebeam","bx_Wp1_RB2out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S02_abort = fs->make<TH2F>("bx_Wp1_RB2out_S02_abort","bx_Wp1_RB2out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S02_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S02_prebeam","bx_Wp1_RB2out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S03_abort = fs->make<TH2F>("bx_Wp1_RB2out_S03_abort","bx_Wp1_RB2out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S03_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S03_prebeam","bx_Wp1_RB2out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S04_abort = fs->make<TH2F>("bx_Wp1_RB2out_S04_abort","bx_Wp1_RB2out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S04_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S04_prebeam","bx_Wp1_RB2out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S05_abort = fs->make<TH2F>("bx_Wp1_RB2out_S05_abort","bx_Wp1_RB2out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S05_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S05_prebeam","bx_Wp1_RB2out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S06_abort = fs->make<TH2F>("bx_Wp1_RB2out_S06_abort","bx_Wp1_RB2out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S06_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S06_prebeam","bx_Wp1_RB2out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S07_abort = fs->make<TH2F>("bx_Wp1_RB2out_S07_abort","bx_Wp1_RB2out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S07_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S07_prebeam","bx_Wp1_RB2out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S08_abort = fs->make<TH2F>("bx_Wp1_RB2out_S08_abort","bx_Wp1_RB2out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S08_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S08_prebeam","bx_Wp1_RB2out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S09_abort = fs->make<TH2F>("bx_Wp1_RB2out_S09_abort","bx_Wp1_RB2out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S09_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S09_prebeam","bx_Wp1_RB2out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S10_abort = fs->make<TH2F>("bx_Wp1_RB2out_S10_abort","bx_Wp1_RB2out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S10_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S10_prebeam","bx_Wp1_RB2out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S11_abort = fs->make<TH2F>("bx_Wp1_RB2out_S11_abort","bx_Wp1_RB2out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S11_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S11_prebeam","bx_Wp1_RB2out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S12_abort = fs->make<TH2F>("bx_Wp1_RB2out_S12_abort","bx_Wp1_RB2out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_S12_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_S12_prebeam","bx_Wp1_RB2out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S01_abort = fs->make<TH2F>("bx_Wp2_RB2out_S01_abort","bx_Wp2_RB2out_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S01_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S01_prebeam","bx_Wp2_RB2out_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S02_abort = fs->make<TH2F>("bx_Wp2_RB2out_S02_abort","bx_Wp2_RB2out_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S02_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S02_prebeam","bx_Wp2_RB2out_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S03_abort = fs->make<TH2F>("bx_Wp2_RB2out_S03_abort","bx_Wp2_RB2out_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S03_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S03_prebeam","bx_Wp2_RB2out_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S04_abort = fs->make<TH2F>("bx_Wp2_RB2out_S04_abort","bx_Wp2_RB2out_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S04_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S04_prebeam","bx_Wp2_RB2out_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S05_abort = fs->make<TH2F>("bx_Wp2_RB2out_S05_abort","bx_Wp2_RB2out_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S05_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S05_prebeam","bx_Wp2_RB2out_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S06_abort = fs->make<TH2F>("bx_Wp2_RB2out_S06_abort","bx_Wp2_RB2out_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S06_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S06_prebeam","bx_Wp2_RB2out_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S07_abort = fs->make<TH2F>("bx_Wp2_RB2out_S07_abort","bx_Wp2_RB2out_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S07_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S07_prebeam","bx_Wp2_RB2out_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S08_abort = fs->make<TH2F>("bx_Wp2_RB2out_S08_abort","bx_Wp2_RB2out_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S08_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S08_prebeam","bx_Wp2_RB2out_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S09_abort = fs->make<TH2F>("bx_Wp2_RB2out_S09_abort","bx_Wp2_RB2out_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S09_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S09_prebeam","bx_Wp2_RB2out_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S10_abort = fs->make<TH2F>("bx_Wp2_RB2out_S10_abort","bx_Wp2_RB2out_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S10_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S10_prebeam","bx_Wp2_RB2out_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S11_abort = fs->make<TH2F>("bx_Wp2_RB2out_S11_abort","bx_Wp2_RB2out_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S11_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S11_prebeam","bx_Wp2_RB2out_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S12_abort = fs->make<TH2F>("bx_Wp2_RB2out_S12_abort","bx_Wp2_RB2out_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_S12_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_S12_prebeam","bx_Wp2_RB2out_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S01_abort = fs->make<TH2F>("bx_Wm2_RB3_S01_abort","bx_Wm2_RB3_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S01_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S01_prebeam","bx_Wm2_RB3_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S02_abort = fs->make<TH2F>("bx_Wm2_RB3_S02_abort","bx_Wm2_RB3_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S02_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S02_prebeam","bx_Wm2_RB3_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S03_abort = fs->make<TH2F>("bx_Wm2_RB3_S03_abort","bx_Wm2_RB3_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S03_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S03_prebeam","bx_Wm2_RB3_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S04_abort = fs->make<TH2F>("bx_Wm2_RB3_S04_abort","bx_Wm2_RB3_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S04_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S04_prebeam","bx_Wm2_RB3_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S05_abort = fs->make<TH2F>("bx_Wm2_RB3_S05_abort","bx_Wm2_RB3_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S05_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S05_prebeam","bx_Wm2_RB3_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S06_abort = fs->make<TH2F>("bx_Wm2_RB3_S06_abort","bx_Wm2_RB3_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S06_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S06_prebeam","bx_Wm2_RB3_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S07_abort = fs->make<TH2F>("bx_Wm2_RB3_S07_abort","bx_Wm2_RB3_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S07_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S07_prebeam","bx_Wm2_RB3_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S08_abort = fs->make<TH2F>("bx_Wm2_RB3_S08_abort","bx_Wm2_RB3_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S08_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S08_prebeam","bx_Wm2_RB3_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S09_abort = fs->make<TH2F>("bx_Wm2_RB3_S09_abort","bx_Wm2_RB3_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S09_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S09_prebeam","bx_Wm2_RB3_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S10_abort = fs->make<TH2F>("bx_Wm2_RB3_S10_abort","bx_Wm2_RB3_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S10_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S10_prebeam","bx_Wm2_RB3_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S11_abort = fs->make<TH2F>("bx_Wm2_RB3_S11_abort","bx_Wm2_RB3_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S11_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S11_prebeam","bx_Wm2_RB3_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S12_abort = fs->make<TH2F>("bx_Wm2_RB3_S12_abort","bx_Wm2_RB3_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_S12_prebeam = fs->make<TH2F>("bx_Wm2_RB3_S12_prebeam","bx_Wm2_RB3_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S01_abort = fs->make<TH2F>("bx_Wm1_RB3_S01_abort","bx_Wm1_RB3_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S01_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S01_prebeam","bx_Wm1_RB3_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S02_abort = fs->make<TH2F>("bx_Wm1_RB3_S02_abort","bx_Wm1_RB3_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S02_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S02_prebeam","bx_Wm1_RB3_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S03_abort = fs->make<TH2F>("bx_Wm1_RB3_S03_abort","bx_Wm1_RB3_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S03_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S03_prebeam","bx_Wm1_RB3_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S04_abort = fs->make<TH2F>("bx_Wm1_RB3_S04_abort","bx_Wm1_RB3_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S04_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S04_prebeam","bx_Wm1_RB3_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S05_abort = fs->make<TH2F>("bx_Wm1_RB3_S05_abort","bx_Wm1_RB3_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S05_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S05_prebeam","bx_Wm1_RB3_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S06_abort = fs->make<TH2F>("bx_Wm1_RB3_S06_abort","bx_Wm1_RB3_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S06_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S06_prebeam","bx_Wm1_RB3_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S07_abort = fs->make<TH2F>("bx_Wm1_RB3_S07_abort","bx_Wm1_RB3_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S07_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S07_prebeam","bx_Wm1_RB3_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S08_abort = fs->make<TH2F>("bx_Wm1_RB3_S08_abort","bx_Wm1_RB3_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S08_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S08_prebeam","bx_Wm1_RB3_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S09_abort = fs->make<TH2F>("bx_Wm1_RB3_S09_abort","bx_Wm1_RB3_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S09_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S09_prebeam","bx_Wm1_RB3_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S10_abort = fs->make<TH2F>("bx_Wm1_RB3_S10_abort","bx_Wm1_RB3_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S10_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S10_prebeam","bx_Wm1_RB3_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S11_abort = fs->make<TH2F>("bx_Wm1_RB3_S11_abort","bx_Wm1_RB3_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S11_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S11_prebeam","bx_Wm1_RB3_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S12_abort = fs->make<TH2F>("bx_Wm1_RB3_S12_abort","bx_Wm1_RB3_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_S12_prebeam = fs->make<TH2F>("bx_Wm1_RB3_S12_prebeam","bx_Wm1_RB3_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S01_abort = fs->make<TH2F>("bx_W0_RB3_S01_abort","bx_W0_RB3_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S01_prebeam = fs->make<TH2F>("bx_W0_RB3_S01_prebeam","bx_W0_RB3_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S02_abort = fs->make<TH2F>("bx_W0_RB3_S02_abort","bx_W0_RB3_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S02_prebeam = fs->make<TH2F>("bx_W0_RB3_S02_prebeam","bx_W0_RB3_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S03_abort = fs->make<TH2F>("bx_W0_RB3_S03_abort","bx_W0_RB3_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S03_prebeam = fs->make<TH2F>("bx_W0_RB3_S03_prebeam","bx_W0_RB3_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S04_abort = fs->make<TH2F>("bx_W0_RB3_S04_abort","bx_W0_RB3_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S04_prebeam = fs->make<TH2F>("bx_W0_RB3_S04_prebeam","bx_W0_RB3_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S05_abort = fs->make<TH2F>("bx_W0_RB3_S05_abort","bx_W0_RB3_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S05_prebeam = fs->make<TH2F>("bx_W0_RB3_S05_prebeam","bx_W0_RB3_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S06_abort = fs->make<TH2F>("bx_W0_RB3_S06_abort","bx_W0_RB3_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S06_prebeam = fs->make<TH2F>("bx_W0_RB3_S06_prebeam","bx_W0_RB3_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S07_abort = fs->make<TH2F>("bx_W0_RB3_S07_abort","bx_W0_RB3_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S07_prebeam = fs->make<TH2F>("bx_W0_RB3_S07_prebeam","bx_W0_RB3_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S08_abort = fs->make<TH2F>("bx_W0_RB3_S08_abort","bx_W0_RB3_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S08_prebeam = fs->make<TH2F>("bx_W0_RB3_S08_prebeam","bx_W0_RB3_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S09_abort = fs->make<TH2F>("bx_W0_RB3_S09_abort","bx_W0_RB3_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S09_prebeam = fs->make<TH2F>("bx_W0_RB3_S09_prebeam","bx_W0_RB3_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S10_abort = fs->make<TH2F>("bx_W0_RB3_S10_abort","bx_W0_RB3_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S10_prebeam = fs->make<TH2F>("bx_W0_RB3_S10_prebeam","bx_W0_RB3_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S11_abort = fs->make<TH2F>("bx_W0_RB3_S11_abort","bx_W0_RB3_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S11_prebeam = fs->make<TH2F>("bx_W0_RB3_S11_prebeam","bx_W0_RB3_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S12_abort = fs->make<TH2F>("bx_W0_RB3_S12_abort","bx_W0_RB3_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_S12_prebeam = fs->make<TH2F>("bx_W0_RB3_S12_prebeam","bx_W0_RB3_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S01_abort = fs->make<TH2F>("bx_Wp1_RB3_S01_abort","bx_Wp1_RB3_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S01_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S01_prebeam","bx_Wp1_RB3_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S02_abort = fs->make<TH2F>("bx_Wp1_RB3_S02_abort","bx_Wp1_RB3_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S02_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S02_prebeam","bx_Wp1_RB3_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S03_abort = fs->make<TH2F>("bx_Wp1_RB3_S03_abort","bx_Wp1_RB3_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S03_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S03_prebeam","bx_Wp1_RB3_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S04_abort = fs->make<TH2F>("bx_Wp1_RB3_S04_abort","bx_Wp1_RB3_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S04_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S04_prebeam","bx_Wp1_RB3_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S05_abort = fs->make<TH2F>("bx_Wp1_RB3_S05_abort","bx_Wp1_RB3_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S05_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S05_prebeam","bx_Wp1_RB3_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S06_abort = fs->make<TH2F>("bx_Wp1_RB3_S06_abort","bx_Wp1_RB3_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S06_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S06_prebeam","bx_Wp1_RB3_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S07_abort = fs->make<TH2F>("bx_Wp1_RB3_S07_abort","bx_Wp1_RB3_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S07_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S07_prebeam","bx_Wp1_RB3_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S08_abort = fs->make<TH2F>("bx_Wp1_RB3_S08_abort","bx_Wp1_RB3_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S08_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S08_prebeam","bx_Wp1_RB3_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S09_abort = fs->make<TH2F>("bx_Wp1_RB3_S09_abort","bx_Wp1_RB3_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S09_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S09_prebeam","bx_Wp1_RB3_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S10_abort = fs->make<TH2F>("bx_Wp1_RB3_S10_abort","bx_Wp1_RB3_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S10_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S10_prebeam","bx_Wp1_RB3_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S11_abort = fs->make<TH2F>("bx_Wp1_RB3_S11_abort","bx_Wp1_RB3_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S11_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S11_prebeam","bx_Wp1_RB3_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S12_abort = fs->make<TH2F>("bx_Wp1_RB3_S12_abort","bx_Wp1_RB3_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_S12_prebeam = fs->make<TH2F>("bx_Wp1_RB3_S12_prebeam","bx_Wp1_RB3_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S01_abort = fs->make<TH2F>("bx_Wp2_RB3_S01_abort","bx_Wp2_RB3_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S01_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S01_prebeam","bx_Wp2_RB3_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S02_abort = fs->make<TH2F>("bx_Wp2_RB3_S02_abort","bx_Wp2_RB3_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S02_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S02_prebeam","bx_Wp2_RB3_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S03_abort = fs->make<TH2F>("bx_Wp2_RB3_S03_abort","bx_Wp2_RB3_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S03_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S03_prebeam","bx_Wp2_RB3_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S04_abort = fs->make<TH2F>("bx_Wp2_RB3_S04_abort","bx_Wp2_RB3_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S04_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S04_prebeam","bx_Wp2_RB3_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S05_abort = fs->make<TH2F>("bx_Wp2_RB3_S05_abort","bx_Wp2_RB3_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S05_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S05_prebeam","bx_Wp2_RB3_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S06_abort = fs->make<TH2F>("bx_Wp2_RB3_S06_abort","bx_Wp2_RB3_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S06_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S06_prebeam","bx_Wp2_RB3_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S07_abort = fs->make<TH2F>("bx_Wp2_RB3_S07_abort","bx_Wp2_RB3_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S07_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S07_prebeam","bx_Wp2_RB3_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S08_abort = fs->make<TH2F>("bx_Wp2_RB3_S08_abort","bx_Wp2_RB3_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S08_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S08_prebeam","bx_Wp2_RB3_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S09_abort = fs->make<TH2F>("bx_Wp2_RB3_S09_abort","bx_Wp2_RB3_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S09_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S09_prebeam","bx_Wp2_RB3_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S10_abort = fs->make<TH2F>("bx_Wp2_RB3_S10_abort","bx_Wp2_RB3_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S10_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S10_prebeam","bx_Wp2_RB3_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S11_abort = fs->make<TH2F>("bx_Wp2_RB3_S11_abort","bx_Wp2_RB3_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S11_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S11_prebeam","bx_Wp2_RB3_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S12_abort = fs->make<TH2F>("bx_Wp2_RB3_S12_abort","bx_Wp2_RB3_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_S12_prebeam = fs->make<TH2F>("bx_Wp2_RB3_S12_prebeam","bx_Wp2_RB3_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S01_abort = fs->make<TH2F>("bx_Wm2_RB4_S01_abort","bx_Wm2_RB4_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S01_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S01_prebeam","bx_Wm2_RB4_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S02_abort = fs->make<TH2F>("bx_Wm2_RB4_S02_abort","bx_Wm2_RB4_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S02_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S02_prebeam","bx_Wm2_RB4_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S03_abort = fs->make<TH2F>("bx_Wm2_RB4_S03_abort","bx_Wm2_RB4_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S03_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S03_prebeam","bx_Wm2_RB4_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S04_abort = fs->make<TH2F>("bx_Wm2_RB4_S04_abort","bx_Wm2_RB4_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S04_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S04_prebeam","bx_Wm2_RB4_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S05_abort = fs->make<TH2F>("bx_Wm2_RB4_S05_abort","bx_Wm2_RB4_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S05_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S05_prebeam","bx_Wm2_RB4_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S06_abort = fs->make<TH2F>("bx_Wm2_RB4_S06_abort","bx_Wm2_RB4_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S06_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S06_prebeam","bx_Wm2_RB4_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S07_abort = fs->make<TH2F>("bx_Wm2_RB4_S07_abort","bx_Wm2_RB4_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S07_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S07_prebeam","bx_Wm2_RB4_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S08_abort = fs->make<TH2F>("bx_Wm2_RB4_S08_abort","bx_Wm2_RB4_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S08_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S08_prebeam","bx_Wm2_RB4_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S09_abort = fs->make<TH2F>("bx_Wm2_RB4_S09_abort","bx_Wm2_RB4_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S09_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S09_prebeam","bx_Wm2_RB4_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S10_abort = fs->make<TH2F>("bx_Wm2_RB4_S10_abort","bx_Wm2_RB4_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S10_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S10_prebeam","bx_Wm2_RB4_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S11_abort = fs->make<TH2F>("bx_Wm2_RB4_S11_abort","bx_Wm2_RB4_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S11_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S11_prebeam","bx_Wm2_RB4_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S12_abort = fs->make<TH2F>("bx_Wm2_RB4_S12_abort","bx_Wm2_RB4_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_S12_prebeam = fs->make<TH2F>("bx_Wm2_RB4_S12_prebeam","bx_Wm2_RB4_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S01_abort = fs->make<TH2F>("bx_Wm1_RB4_S01_abort","bx_Wm1_RB4_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S01_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S01_prebeam","bx_Wm1_RB4_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S02_abort = fs->make<TH2F>("bx_Wm1_RB4_S02_abort","bx_Wm1_RB4_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S02_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S02_prebeam","bx_Wm1_RB4_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S03_abort = fs->make<TH2F>("bx_Wm1_RB4_S03_abort","bx_Wm1_RB4_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S03_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S03_prebeam","bx_Wm1_RB4_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S04_abort = fs->make<TH2F>("bx_Wm1_RB4_S04_abort","bx_Wm1_RB4_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S04_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S04_prebeam","bx_Wm1_RB4_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S05_abort = fs->make<TH2F>("bx_Wm1_RB4_S05_abort","bx_Wm1_RB4_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S05_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S05_prebeam","bx_Wm1_RB4_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S06_abort = fs->make<TH2F>("bx_Wm1_RB4_S06_abort","bx_Wm1_RB4_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S06_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S06_prebeam","bx_Wm1_RB4_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S07_abort = fs->make<TH2F>("bx_Wm1_RB4_S07_abort","bx_Wm1_RB4_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S07_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S07_prebeam","bx_Wm1_RB4_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S08_abort = fs->make<TH2F>("bx_Wm1_RB4_S08_abort","bx_Wm1_RB4_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S08_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S08_prebeam","bx_Wm1_RB4_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S09_abort = fs->make<TH2F>("bx_Wm1_RB4_S09_abort","bx_Wm1_RB4_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S09_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S09_prebeam","bx_Wm1_RB4_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S10_abort = fs->make<TH2F>("bx_Wm1_RB4_S10_abort","bx_Wm1_RB4_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S10_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S10_prebeam","bx_Wm1_RB4_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S11_abort = fs->make<TH2F>("bx_Wm1_RB4_S11_abort","bx_Wm1_RB4_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S11_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S11_prebeam","bx_Wm1_RB4_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S12_abort = fs->make<TH2F>("bx_Wm1_RB4_S12_abort","bx_Wm1_RB4_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_S12_prebeam = fs->make<TH2F>("bx_Wm1_RB4_S12_prebeam","bx_Wm1_RB4_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S01_abort = fs->make<TH2F>("bx_W0_RB4_S01_abort","bx_W0_RB4_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S01_prebeam = fs->make<TH2F>("bx_W0_RB4_S01_prebeam","bx_W0_RB4_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S02_abort = fs->make<TH2F>("bx_W0_RB4_S02_abort","bx_W0_RB4_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S02_prebeam = fs->make<TH2F>("bx_W0_RB4_S02_prebeam","bx_W0_RB4_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S03_abort = fs->make<TH2F>("bx_W0_RB4_S03_abort","bx_W0_RB4_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S03_prebeam = fs->make<TH2F>("bx_W0_RB4_S03_prebeam","bx_W0_RB4_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S04_abort = fs->make<TH2F>("bx_W0_RB4_S04_abort","bx_W0_RB4_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S04_prebeam = fs->make<TH2F>("bx_W0_RB4_S04_prebeam","bx_W0_RB4_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S05_abort = fs->make<TH2F>("bx_W0_RB4_S05_abort","bx_W0_RB4_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S05_prebeam = fs->make<TH2F>("bx_W0_RB4_S05_prebeam","bx_W0_RB4_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S06_abort = fs->make<TH2F>("bx_W0_RB4_S06_abort","bx_W0_RB4_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S06_prebeam = fs->make<TH2F>("bx_W0_RB4_S06_prebeam","bx_W0_RB4_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S07_abort = fs->make<TH2F>("bx_W0_RB4_S07_abort","bx_W0_RB4_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S07_prebeam = fs->make<TH2F>("bx_W0_RB4_S07_prebeam","bx_W0_RB4_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S08_abort = fs->make<TH2F>("bx_W0_RB4_S08_abort","bx_W0_RB4_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S08_prebeam = fs->make<TH2F>("bx_W0_RB4_S08_prebeam","bx_W0_RB4_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S09_abort = fs->make<TH2F>("bx_W0_RB4_S09_abort","bx_W0_RB4_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S09_prebeam = fs->make<TH2F>("bx_W0_RB4_S09_prebeam","bx_W0_RB4_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S10_abort = fs->make<TH2F>("bx_W0_RB4_S10_abort","bx_W0_RB4_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S10_prebeam = fs->make<TH2F>("bx_W0_RB4_S10_prebeam","bx_W0_RB4_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S11_abort = fs->make<TH2F>("bx_W0_RB4_S11_abort","bx_W0_RB4_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S11_prebeam = fs->make<TH2F>("bx_W0_RB4_S11_prebeam","bx_W0_RB4_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S12_abort = fs->make<TH2F>("bx_W0_RB4_S12_abort","bx_W0_RB4_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_S12_prebeam = fs->make<TH2F>("bx_W0_RB4_S12_prebeam","bx_W0_RB4_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S01_abort = fs->make<TH2F>("bx_Wp1_RB4_S01_abort","bx_Wp1_RB4_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S01_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S01_prebeam","bx_Wp1_RB4_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S02_abort = fs->make<TH2F>("bx_Wp1_RB4_S02_abort","bx_Wp1_RB4_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S02_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S02_prebeam","bx_Wp1_RB4_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S03_abort = fs->make<TH2F>("bx_Wp1_RB4_S03_abort","bx_Wp1_RB4_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S03_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S03_prebeam","bx_Wp1_RB4_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S04_abort = fs->make<TH2F>("bx_Wp1_RB4_S04_abort","bx_Wp1_RB4_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S04_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S04_prebeam","bx_Wp1_RB4_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S05_abort = fs->make<TH2F>("bx_Wp1_RB4_S05_abort","bx_Wp1_RB4_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S05_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S05_prebeam","bx_Wp1_RB4_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S06_abort = fs->make<TH2F>("bx_Wp1_RB4_S06_abort","bx_Wp1_RB4_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S06_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S06_prebeam","bx_Wp1_RB4_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S07_abort = fs->make<TH2F>("bx_Wp1_RB4_S07_abort","bx_Wp1_RB4_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S07_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S07_prebeam","bx_Wp1_RB4_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S08_abort = fs->make<TH2F>("bx_Wp1_RB4_S08_abort","bx_Wp1_RB4_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S08_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S08_prebeam","bx_Wp1_RB4_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S09_abort = fs->make<TH2F>("bx_Wp1_RB4_S09_abort","bx_Wp1_RB4_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S09_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S09_prebeam","bx_Wp1_RB4_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S10_abort = fs->make<TH2F>("bx_Wp1_RB4_S10_abort","bx_Wp1_RB4_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S10_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S10_prebeam","bx_Wp1_RB4_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S11_abort = fs->make<TH2F>("bx_Wp1_RB4_S11_abort","bx_Wp1_RB4_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S11_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S11_prebeam","bx_Wp1_RB4_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S12_abort = fs->make<TH2F>("bx_Wp1_RB4_S12_abort","bx_Wp1_RB4_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_S12_prebeam = fs->make<TH2F>("bx_Wp1_RB4_S12_prebeam","bx_Wp1_RB4_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S01_abort = fs->make<TH2F>("bx_Wp2_RB4_S01_abort","bx_Wp2_RB4_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S01_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S01_prebeam","bx_Wp2_RB4_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S02_abort = fs->make<TH2F>("bx_Wp2_RB4_S02_abort","bx_Wp2_RB4_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S02_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S02_prebeam","bx_Wp2_RB4_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S03_abort = fs->make<TH2F>("bx_Wp2_RB4_S03_abort","bx_Wp2_RB4_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S03_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S03_prebeam","bx_Wp2_RB4_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S04_abort = fs->make<TH2F>("bx_Wp2_RB4_S04_abort","bx_Wp2_RB4_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S04_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S04_prebeam","bx_Wp2_RB4_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S05_abort = fs->make<TH2F>("bx_Wp2_RB4_S05_abort","bx_Wp2_RB4_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S05_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S05_prebeam","bx_Wp2_RB4_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S06_abort = fs->make<TH2F>("bx_Wp2_RB4_S06_abort","bx_Wp2_RB4_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S06_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S06_prebeam","bx_Wp2_RB4_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S07_abort = fs->make<TH2F>("bx_Wp2_RB4_S07_abort","bx_Wp2_RB4_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S07_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S07_prebeam","bx_Wp2_RB4_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S08_abort = fs->make<TH2F>("bx_Wp2_RB4_S08_abort","bx_Wp2_RB4_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S08_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S08_prebeam","bx_Wp2_RB4_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S09_abort = fs->make<TH2F>("bx_Wp2_RB4_S09_abort","bx_Wp2_RB4_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S09_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S09_prebeam","bx_Wp2_RB4_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S10_abort = fs->make<TH2F>("bx_Wp2_RB4_S10_abort","bx_Wp2_RB4_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S10_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S10_prebeam","bx_Wp2_RB4_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S11_abort = fs->make<TH2F>("bx_Wp2_RB4_S11_abort","bx_Wp2_RB4_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S11_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S11_prebeam","bx_Wp2_RB4_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S12_abort = fs->make<TH2F>("bx_Wp2_RB4_S12_abort","bx_Wp2_RB4_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_S12_prebeam = fs->make<TH2F>("bx_Wp2_RB4_S12_prebeam","bx_Wp2_RB4_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S01_abort = fs->make<TH2F>("bx_REp42_S01_abort","bx_REp42_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S01_prebeam = fs->make<TH2F>("bx_REp42_S01_prebeam","bx_REp42_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S02_abort = fs->make<TH2F>("bx_REp42_S02_abort","bx_REp42_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S02_prebeam = fs->make<TH2F>("bx_REp42_S02_prebeam","bx_REp42_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S03_abort = fs->make<TH2F>("bx_REp42_S03_abort","bx_REp42_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S03_prebeam = fs->make<TH2F>("bx_REp42_S03_prebeam","bx_REp42_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S04_abort = fs->make<TH2F>("bx_REp42_S04_abort","bx_REp42_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S04_prebeam = fs->make<TH2F>("bx_REp42_S04_prebeam","bx_REp42_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S05_abort = fs->make<TH2F>("bx_REp42_S05_abort","bx_REp42_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S05_prebeam = fs->make<TH2F>("bx_REp42_S05_prebeam","bx_REp42_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S06_abort = fs->make<TH2F>("bx_REp42_S06_abort","bx_REp42_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S06_prebeam = fs->make<TH2F>("bx_REp42_S06_prebeam","bx_REp42_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S07_abort = fs->make<TH2F>("bx_REp42_S07_abort","bx_REp42_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S07_prebeam = fs->make<TH2F>("bx_REp42_S07_prebeam","bx_REp42_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S08_abort = fs->make<TH2F>("bx_REp42_S08_abort","bx_REp42_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S08_prebeam = fs->make<TH2F>("bx_REp42_S08_prebeam","bx_REp42_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S09_abort = fs->make<TH2F>("bx_REp42_S09_abort","bx_REp42_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S09_prebeam = fs->make<TH2F>("bx_REp42_S09_prebeam","bx_REp42_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S10_abort = fs->make<TH2F>("bx_REp42_S10_abort","bx_REp42_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S10_prebeam = fs->make<TH2F>("bx_REp42_S10_prebeam","bx_REp42_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S11_abort = fs->make<TH2F>("bx_REp42_S11_abort","bx_REp42_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S11_prebeam = fs->make<TH2F>("bx_REp42_S11_prebeam","bx_REp42_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S12_abort = fs->make<TH2F>("bx_REp42_S12_abort","bx_REp42_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_S12_prebeam = fs->make<TH2F>("bx_REp42_S12_prebeam","bx_REp42_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S01_abort = fs->make<TH2F>("bx_REp43_S01_abort","bx_REp43_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S01_prebeam = fs->make<TH2F>("bx_REp43_S01_prebeam","bx_REp43_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S02_abort = fs->make<TH2F>("bx_REp43_S02_abort","bx_REp43_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S02_prebeam = fs->make<TH2F>("bx_REp43_S02_prebeam","bx_REp43_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S03_abort = fs->make<TH2F>("bx_REp43_S03_abort","bx_REp43_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S03_prebeam = fs->make<TH2F>("bx_REp43_S03_prebeam","bx_REp43_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S04_abort = fs->make<TH2F>("bx_REp43_S04_abort","bx_REp43_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S04_prebeam = fs->make<TH2F>("bx_REp43_S04_prebeam","bx_REp43_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S05_abort = fs->make<TH2F>("bx_REp43_S05_abort","bx_REp43_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S05_prebeam = fs->make<TH2F>("bx_REp43_S05_prebeam","bx_REp43_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S06_abort = fs->make<TH2F>("bx_REp43_S06_abort","bx_REp43_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S06_prebeam = fs->make<TH2F>("bx_REp43_S06_prebeam","bx_REp43_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S07_abort = fs->make<TH2F>("bx_REp43_S07_abort","bx_REp43_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S07_prebeam = fs->make<TH2F>("bx_REp43_S07_prebeam","bx_REp43_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S08_abort = fs->make<TH2F>("bx_REp43_S08_abort","bx_REp43_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S08_prebeam = fs->make<TH2F>("bx_REp43_S08_prebeam","bx_REp43_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S09_abort = fs->make<TH2F>("bx_REp43_S09_abort","bx_REp43_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S09_prebeam = fs->make<TH2F>("bx_REp43_S09_prebeam","bx_REp43_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S10_abort = fs->make<TH2F>("bx_REp43_S10_abort","bx_REp43_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S10_prebeam = fs->make<TH2F>("bx_REp43_S10_prebeam","bx_REp43_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S11_abort = fs->make<TH2F>("bx_REp43_S11_abort","bx_REp43_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S11_prebeam = fs->make<TH2F>("bx_REp43_S11_prebeam","bx_REp43_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S12_abort = fs->make<TH2F>("bx_REp43_S12_abort","bx_REp43_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_S12_prebeam = fs->make<TH2F>("bx_REp43_S12_prebeam","bx_REp43_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S01_abort = fs->make<TH2F>("bx_REp12_S01_abort","bx_REp12_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S01_prebeam = fs->make<TH2F>("bx_REp12_S01_prebeam","bx_REp12_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S02_abort = fs->make<TH2F>("bx_REp12_S02_abort","bx_REp12_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S02_prebeam = fs->make<TH2F>("bx_REp12_S02_prebeam","bx_REp12_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S03_abort = fs->make<TH2F>("bx_REp12_S03_abort","bx_REp12_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S03_prebeam = fs->make<TH2F>("bx_REp12_S03_prebeam","bx_REp12_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S04_abort = fs->make<TH2F>("bx_REp12_S04_abort","bx_REp12_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S04_prebeam = fs->make<TH2F>("bx_REp12_S04_prebeam","bx_REp12_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S05_abort = fs->make<TH2F>("bx_REp12_S05_abort","bx_REp12_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S05_prebeam = fs->make<TH2F>("bx_REp12_S05_prebeam","bx_REp12_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S06_abort = fs->make<TH2F>("bx_REp12_S06_abort","bx_REp12_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S06_prebeam = fs->make<TH2F>("bx_REp12_S06_prebeam","bx_REp12_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S07_abort = fs->make<TH2F>("bx_REp12_S07_abort","bx_REp12_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S07_prebeam = fs->make<TH2F>("bx_REp12_S07_prebeam","bx_REp12_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S08_abort = fs->make<TH2F>("bx_REp12_S08_abort","bx_REp12_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S08_prebeam = fs->make<TH2F>("bx_REp12_S08_prebeam","bx_REp12_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S09_abort = fs->make<TH2F>("bx_REp12_S09_abort","bx_REp12_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S09_prebeam = fs->make<TH2F>("bx_REp12_S09_prebeam","bx_REp12_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S10_abort = fs->make<TH2F>("bx_REp12_S10_abort","bx_REp12_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S10_prebeam = fs->make<TH2F>("bx_REp12_S10_prebeam","bx_REp12_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S11_abort = fs->make<TH2F>("bx_REp12_S11_abort","bx_REp12_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S11_prebeam = fs->make<TH2F>("bx_REp12_S11_prebeam","bx_REp12_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S12_abort = fs->make<TH2F>("bx_REp12_S12_abort","bx_REp12_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_S12_prebeam = fs->make<TH2F>("bx_REp12_S12_prebeam","bx_REp12_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S01_abort = fs->make<TH2F>("bx_REp13_S01_abort","bx_REp13_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S01_prebeam = fs->make<TH2F>("bx_REp13_S01_prebeam","bx_REp13_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S02_abort = fs->make<TH2F>("bx_REp13_S02_abort","bx_REp13_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S02_prebeam = fs->make<TH2F>("bx_REp13_S02_prebeam","bx_REp13_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S03_abort = fs->make<TH2F>("bx_REp13_S03_abort","bx_REp13_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S03_prebeam = fs->make<TH2F>("bx_REp13_S03_prebeam","bx_REp13_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S04_abort = fs->make<TH2F>("bx_REp13_S04_abort","bx_REp13_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S04_prebeam = fs->make<TH2F>("bx_REp13_S04_prebeam","bx_REp13_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S05_abort = fs->make<TH2F>("bx_REp13_S05_abort","bx_REp13_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S05_prebeam = fs->make<TH2F>("bx_REp13_S05_prebeam","bx_REp13_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S06_abort = fs->make<TH2F>("bx_REp13_S06_abort","bx_REp13_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S06_prebeam = fs->make<TH2F>("bx_REp13_S06_prebeam","bx_REp13_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S07_abort = fs->make<TH2F>("bx_REp13_S07_abort","bx_REp13_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S07_prebeam = fs->make<TH2F>("bx_REp13_S07_prebeam","bx_REp13_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S08_abort = fs->make<TH2F>("bx_REp13_S08_abort","bx_REp13_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S08_prebeam = fs->make<TH2F>("bx_REp13_S08_prebeam","bx_REp13_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S09_abort = fs->make<TH2F>("bx_REp13_S09_abort","bx_REp13_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S09_prebeam = fs->make<TH2F>("bx_REp13_S09_prebeam","bx_REp13_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S10_abort = fs->make<TH2F>("bx_REp13_S10_abort","bx_REp13_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S10_prebeam = fs->make<TH2F>("bx_REp13_S10_prebeam","bx_REp13_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S11_abort = fs->make<TH2F>("bx_REp13_S11_abort","bx_REp13_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S11_prebeam = fs->make<TH2F>("bx_REp13_S11_prebeam","bx_REp13_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S12_abort = fs->make<TH2F>("bx_REp13_S12_abort","bx_REp13_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_S12_prebeam = fs->make<TH2F>("bx_REp13_S12_prebeam","bx_REp13_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S01_abort = fs->make<TH2F>("bx_REp22_S01_abort","bx_REp22_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S01_prebeam = fs->make<TH2F>("bx_REp22_S01_prebeam","bx_REp22_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S02_abort = fs->make<TH2F>("bx_REp22_S02_abort","bx_REp22_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S02_prebeam = fs->make<TH2F>("bx_REp22_S02_prebeam","bx_REp22_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S03_abort = fs->make<TH2F>("bx_REp22_S03_abort","bx_REp22_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S03_prebeam = fs->make<TH2F>("bx_REp22_S03_prebeam","bx_REp22_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S04_abort = fs->make<TH2F>("bx_REp22_S04_abort","bx_REp22_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S04_prebeam = fs->make<TH2F>("bx_REp22_S04_prebeam","bx_REp22_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S05_abort = fs->make<TH2F>("bx_REp22_S05_abort","bx_REp22_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S05_prebeam = fs->make<TH2F>("bx_REp22_S05_prebeam","bx_REp22_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S06_abort = fs->make<TH2F>("bx_REp22_S06_abort","bx_REp22_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S06_prebeam = fs->make<TH2F>("bx_REp22_S06_prebeam","bx_REp22_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S07_abort = fs->make<TH2F>("bx_REp22_S07_abort","bx_REp22_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S07_prebeam = fs->make<TH2F>("bx_REp22_S07_prebeam","bx_REp22_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S08_abort = fs->make<TH2F>("bx_REp22_S08_abort","bx_REp22_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S08_prebeam = fs->make<TH2F>("bx_REp22_S08_prebeam","bx_REp22_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S09_abort = fs->make<TH2F>("bx_REp22_S09_abort","bx_REp22_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S09_prebeam = fs->make<TH2F>("bx_REp22_S09_prebeam","bx_REp22_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S10_abort = fs->make<TH2F>("bx_REp22_S10_abort","bx_REp22_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S10_prebeam = fs->make<TH2F>("bx_REp22_S10_prebeam","bx_REp22_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S11_abort = fs->make<TH2F>("bx_REp22_S11_abort","bx_REp22_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S11_prebeam = fs->make<TH2F>("bx_REp22_S11_prebeam","bx_REp22_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S12_abort = fs->make<TH2F>("bx_REp22_S12_abort","bx_REp22_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_S12_prebeam = fs->make<TH2F>("bx_REp22_S12_prebeam","bx_REp22_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S01_abort = fs->make<TH2F>("bx_REp23_S01_abort","bx_REp23_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S01_prebeam = fs->make<TH2F>("bx_REp23_S01_prebeam","bx_REp23_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S02_abort = fs->make<TH2F>("bx_REp23_S02_abort","bx_REp23_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S02_prebeam = fs->make<TH2F>("bx_REp23_S02_prebeam","bx_REp23_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S03_abort = fs->make<TH2F>("bx_REp23_S03_abort","bx_REp23_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S03_prebeam = fs->make<TH2F>("bx_REp23_S03_prebeam","bx_REp23_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S04_abort = fs->make<TH2F>("bx_REp23_S04_abort","bx_REp23_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S04_prebeam = fs->make<TH2F>("bx_REp23_S04_prebeam","bx_REp23_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S05_abort = fs->make<TH2F>("bx_REp23_S05_abort","bx_REp23_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S05_prebeam = fs->make<TH2F>("bx_REp23_S05_prebeam","bx_REp23_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S06_abort = fs->make<TH2F>("bx_REp23_S06_abort","bx_REp23_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S06_prebeam = fs->make<TH2F>("bx_REp23_S06_prebeam","bx_REp23_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S07_abort = fs->make<TH2F>("bx_REp23_S07_abort","bx_REp23_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S07_prebeam = fs->make<TH2F>("bx_REp23_S07_prebeam","bx_REp23_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S08_abort = fs->make<TH2F>("bx_REp23_S08_abort","bx_REp23_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S08_prebeam = fs->make<TH2F>("bx_REp23_S08_prebeam","bx_REp23_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S09_abort = fs->make<TH2F>("bx_REp23_S09_abort","bx_REp23_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S09_prebeam = fs->make<TH2F>("bx_REp23_S09_prebeam","bx_REp23_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S10_abort = fs->make<TH2F>("bx_REp23_S10_abort","bx_REp23_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S10_prebeam = fs->make<TH2F>("bx_REp23_S10_prebeam","bx_REp23_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S11_abort = fs->make<TH2F>("bx_REp23_S11_abort","bx_REp23_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S11_prebeam = fs->make<TH2F>("bx_REp23_S11_prebeam","bx_REp23_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S12_abort = fs->make<TH2F>("bx_REp23_S12_abort","bx_REp23_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_S12_prebeam = fs->make<TH2F>("bx_REp23_S12_prebeam","bx_REp23_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S01_abort = fs->make<TH2F>("bx_REp32_S01_abort","bx_REp32_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S01_prebeam = fs->make<TH2F>("bx_REp32_S01_prebeam","bx_REp32_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S02_abort = fs->make<TH2F>("bx_REp32_S02_abort","bx_REp32_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S02_prebeam = fs->make<TH2F>("bx_REp32_S02_prebeam","bx_REp32_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S03_abort = fs->make<TH2F>("bx_REp32_S03_abort","bx_REp32_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S03_prebeam = fs->make<TH2F>("bx_REp32_S03_prebeam","bx_REp32_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S04_abort = fs->make<TH2F>("bx_REp32_S04_abort","bx_REp32_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S04_prebeam = fs->make<TH2F>("bx_REp32_S04_prebeam","bx_REp32_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S05_abort = fs->make<TH2F>("bx_REp32_S05_abort","bx_REp32_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S05_prebeam = fs->make<TH2F>("bx_REp32_S05_prebeam","bx_REp32_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S06_abort = fs->make<TH2F>("bx_REp32_S06_abort","bx_REp32_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S06_prebeam = fs->make<TH2F>("bx_REp32_S06_prebeam","bx_REp32_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S07_abort = fs->make<TH2F>("bx_REp32_S07_abort","bx_REp32_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S07_prebeam = fs->make<TH2F>("bx_REp32_S07_prebeam","bx_REp32_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S08_abort = fs->make<TH2F>("bx_REp32_S08_abort","bx_REp32_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S08_prebeam = fs->make<TH2F>("bx_REp32_S08_prebeam","bx_REp32_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S09_abort = fs->make<TH2F>("bx_REp32_S09_abort","bx_REp32_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S09_prebeam = fs->make<TH2F>("bx_REp32_S09_prebeam","bx_REp32_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S10_abort = fs->make<TH2F>("bx_REp32_S10_abort","bx_REp32_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S10_prebeam = fs->make<TH2F>("bx_REp32_S10_prebeam","bx_REp32_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S11_abort = fs->make<TH2F>("bx_REp32_S11_abort","bx_REp32_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S11_prebeam = fs->make<TH2F>("bx_REp32_S11_prebeam","bx_REp32_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S12_abort = fs->make<TH2F>("bx_REp32_S12_abort","bx_REp32_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_S12_prebeam = fs->make<TH2F>("bx_REp32_S12_prebeam","bx_REp32_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S01_abort = fs->make<TH2F>("bx_REp33_S01_abort","bx_REp33_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S01_prebeam = fs->make<TH2F>("bx_REp33_S01_prebeam","bx_REp33_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S02_abort = fs->make<TH2F>("bx_REp33_S02_abort","bx_REp33_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S02_prebeam = fs->make<TH2F>("bx_REp33_S02_prebeam","bx_REp33_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S03_abort = fs->make<TH2F>("bx_REp33_S03_abort","bx_REp33_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S03_prebeam = fs->make<TH2F>("bx_REp33_S03_prebeam","bx_REp33_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S04_abort = fs->make<TH2F>("bx_REp33_S04_abort","bx_REp33_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S04_prebeam = fs->make<TH2F>("bx_REp33_S04_prebeam","bx_REp33_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S05_abort = fs->make<TH2F>("bx_REp33_S05_abort","bx_REp33_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S05_prebeam = fs->make<TH2F>("bx_REp33_S05_prebeam","bx_REp33_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S06_abort = fs->make<TH2F>("bx_REp33_S06_abort","bx_REp33_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S06_prebeam = fs->make<TH2F>("bx_REp33_S06_prebeam","bx_REp33_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S07_abort = fs->make<TH2F>("bx_REp33_S07_abort","bx_REp33_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S07_prebeam = fs->make<TH2F>("bx_REp33_S07_prebeam","bx_REp33_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S08_abort = fs->make<TH2F>("bx_REp33_S08_abort","bx_REp33_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S08_prebeam = fs->make<TH2F>("bx_REp33_S08_prebeam","bx_REp33_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S09_abort = fs->make<TH2F>("bx_REp33_S09_abort","bx_REp33_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S09_prebeam = fs->make<TH2F>("bx_REp33_S09_prebeam","bx_REp33_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S10_abort = fs->make<TH2F>("bx_REp33_S10_abort","bx_REp33_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S10_prebeam = fs->make<TH2F>("bx_REp33_S10_prebeam","bx_REp33_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S11_abort = fs->make<TH2F>("bx_REp33_S11_abort","bx_REp33_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S11_prebeam = fs->make<TH2F>("bx_REp33_S11_prebeam","bx_REp33_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S12_abort = fs->make<TH2F>("bx_REp33_S12_abort","bx_REp33_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_S12_prebeam = fs->make<TH2F>("bx_REp33_S12_prebeam","bx_REp33_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S01_abort = fs->make<TH2F>("bx_REm22_S01_abort","bx_REm22_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S01_prebeam = fs->make<TH2F>("bx_REm22_S01_prebeam","bx_REm22_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S02_abort = fs->make<TH2F>("bx_REm22_S02_abort","bx_REm22_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S02_prebeam = fs->make<TH2F>("bx_REm22_S02_prebeam","bx_REm22_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S03_abort = fs->make<TH2F>("bx_REm22_S03_abort","bx_REm22_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S03_prebeam = fs->make<TH2F>("bx_REm22_S03_prebeam","bx_REm22_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S04_abort = fs->make<TH2F>("bx_REm22_S04_abort","bx_REm22_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S04_prebeam = fs->make<TH2F>("bx_REm22_S04_prebeam","bx_REm22_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S05_abort = fs->make<TH2F>("bx_REm22_S05_abort","bx_REm22_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S05_prebeam = fs->make<TH2F>("bx_REm22_S05_prebeam","bx_REm22_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S06_abort = fs->make<TH2F>("bx_REm22_S06_abort","bx_REm22_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S06_prebeam = fs->make<TH2F>("bx_REm22_S06_prebeam","bx_REm22_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S07_abort = fs->make<TH2F>("bx_REm22_S07_abort","bx_REm22_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S07_prebeam = fs->make<TH2F>("bx_REm22_S07_prebeam","bx_REm22_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S08_abort = fs->make<TH2F>("bx_REm22_S08_abort","bx_REm22_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S08_prebeam = fs->make<TH2F>("bx_REm22_S08_prebeam","bx_REm22_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S09_abort = fs->make<TH2F>("bx_REm22_S09_abort","bx_REm22_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S09_prebeam = fs->make<TH2F>("bx_REm22_S09_prebeam","bx_REm22_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S10_abort = fs->make<TH2F>("bx_REm22_S10_abort","bx_REm22_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S10_prebeam = fs->make<TH2F>("bx_REm22_S10_prebeam","bx_REm22_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S11_abort = fs->make<TH2F>("bx_REm22_S11_abort","bx_REm22_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S11_prebeam = fs->make<TH2F>("bx_REm22_S11_prebeam","bx_REm22_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S12_abort = fs->make<TH2F>("bx_REm22_S12_abort","bx_REm22_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_S12_prebeam = fs->make<TH2F>("bx_REm22_S12_prebeam","bx_REm22_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S01_abort = fs->make<TH2F>("bx_REm23_S01_abort","bx_REm23_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S01_prebeam = fs->make<TH2F>("bx_REm23_S01_prebeam","bx_REm23_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S02_abort = fs->make<TH2F>("bx_REm23_S02_abort","bx_REm23_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S02_prebeam = fs->make<TH2F>("bx_REm23_S02_prebeam","bx_REm23_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S03_abort = fs->make<TH2F>("bx_REm23_S03_abort","bx_REm23_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S03_prebeam = fs->make<TH2F>("bx_REm23_S03_prebeam","bx_REm23_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S04_abort = fs->make<TH2F>("bx_REm23_S04_abort","bx_REm23_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S04_prebeam = fs->make<TH2F>("bx_REm23_S04_prebeam","bx_REm23_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S05_abort = fs->make<TH2F>("bx_REm23_S05_abort","bx_REm23_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S05_prebeam = fs->make<TH2F>("bx_REm23_S05_prebeam","bx_REm23_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S06_abort = fs->make<TH2F>("bx_REm23_S06_abort","bx_REm23_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S06_prebeam = fs->make<TH2F>("bx_REm23_S06_prebeam","bx_REm23_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S07_abort = fs->make<TH2F>("bx_REm23_S07_abort","bx_REm23_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S07_prebeam = fs->make<TH2F>("bx_REm23_S07_prebeam","bx_REm23_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S08_abort = fs->make<TH2F>("bx_REm23_S08_abort","bx_REm23_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S08_prebeam = fs->make<TH2F>("bx_REm23_S08_prebeam","bx_REm23_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S09_abort = fs->make<TH2F>("bx_REm23_S09_abort","bx_REm23_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S09_prebeam = fs->make<TH2F>("bx_REm23_S09_prebeam","bx_REm23_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S10_abort = fs->make<TH2F>("bx_REm23_S10_abort","bx_REm23_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S10_prebeam = fs->make<TH2F>("bx_REm23_S10_prebeam","bx_REm23_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S11_abort = fs->make<TH2F>("bx_REm23_S11_abort","bx_REm23_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S11_prebeam = fs->make<TH2F>("bx_REm23_S11_prebeam","bx_REm23_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S12_abort = fs->make<TH2F>("bx_REm23_S12_abort","bx_REm23_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_S12_prebeam = fs->make<TH2F>("bx_REm23_S12_prebeam","bx_REm23_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S01_abort = fs->make<TH2F>("bx_REm32_S01_abort","bx_REm32_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S01_prebeam = fs->make<TH2F>("bx_REm32_S01_prebeam","bx_REm32_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S02_abort = fs->make<TH2F>("bx_REm32_S02_abort","bx_REm32_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S02_prebeam = fs->make<TH2F>("bx_REm32_S02_prebeam","bx_REm32_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S03_abort = fs->make<TH2F>("bx_REm32_S03_abort","bx_REm32_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S03_prebeam = fs->make<TH2F>("bx_REm32_S03_prebeam","bx_REm32_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S04_abort = fs->make<TH2F>("bx_REm32_S04_abort","bx_REm32_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S04_prebeam = fs->make<TH2F>("bx_REm32_S04_prebeam","bx_REm32_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S05_abort = fs->make<TH2F>("bx_REm32_S05_abort","bx_REm32_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S05_prebeam = fs->make<TH2F>("bx_REm32_S05_prebeam","bx_REm32_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S06_abort = fs->make<TH2F>("bx_REm32_S06_abort","bx_REm32_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S06_prebeam = fs->make<TH2F>("bx_REm32_S06_prebeam","bx_REm32_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S07_abort = fs->make<TH2F>("bx_REm32_S07_abort","bx_REm32_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S07_prebeam = fs->make<TH2F>("bx_REm32_S07_prebeam","bx_REm32_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S08_abort = fs->make<TH2F>("bx_REm32_S08_abort","bx_REm32_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S08_prebeam = fs->make<TH2F>("bx_REm32_S08_prebeam","bx_REm32_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S09_abort = fs->make<TH2F>("bx_REm32_S09_abort","bx_REm32_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S09_prebeam = fs->make<TH2F>("bx_REm32_S09_prebeam","bx_REm32_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S10_abort = fs->make<TH2F>("bx_REm32_S10_abort","bx_REm32_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S10_prebeam = fs->make<TH2F>("bx_REm32_S10_prebeam","bx_REm32_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S11_abort = fs->make<TH2F>("bx_REm32_S11_abort","bx_REm32_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S11_prebeam = fs->make<TH2F>("bx_REm32_S11_prebeam","bx_REm32_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S12_abort = fs->make<TH2F>("bx_REm32_S12_abort","bx_REm32_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_S12_prebeam = fs->make<TH2F>("bx_REm32_S12_prebeam","bx_REm32_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S01_abort = fs->make<TH2F>("bx_REm33_S01_abort","bx_REm33_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S01_prebeam = fs->make<TH2F>("bx_REm33_S01_prebeam","bx_REm33_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S02_abort = fs->make<TH2F>("bx_REm33_S02_abort","bx_REm33_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S02_prebeam = fs->make<TH2F>("bx_REm33_S02_prebeam","bx_REm33_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S03_abort = fs->make<TH2F>("bx_REm33_S03_abort","bx_REm33_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S03_prebeam = fs->make<TH2F>("bx_REm33_S03_prebeam","bx_REm33_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S04_abort = fs->make<TH2F>("bx_REm33_S04_abort","bx_REm33_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S04_prebeam = fs->make<TH2F>("bx_REm33_S04_prebeam","bx_REm33_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S05_abort = fs->make<TH2F>("bx_REm33_S05_abort","bx_REm33_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S05_prebeam = fs->make<TH2F>("bx_REm33_S05_prebeam","bx_REm33_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S06_abort = fs->make<TH2F>("bx_REm33_S06_abort","bx_REm33_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S06_prebeam = fs->make<TH2F>("bx_REm33_S06_prebeam","bx_REm33_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S07_abort = fs->make<TH2F>("bx_REm33_S07_abort","bx_REm33_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S07_prebeam = fs->make<TH2F>("bx_REm33_S07_prebeam","bx_REm33_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S08_abort = fs->make<TH2F>("bx_REm33_S08_abort","bx_REm33_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S08_prebeam = fs->make<TH2F>("bx_REm33_S08_prebeam","bx_REm33_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S09_abort = fs->make<TH2F>("bx_REm33_S09_abort","bx_REm33_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S09_prebeam = fs->make<TH2F>("bx_REm33_S09_prebeam","bx_REm33_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S10_abort = fs->make<TH2F>("bx_REm33_S10_abort","bx_REm33_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S10_prebeam = fs->make<TH2F>("bx_REm33_S10_prebeam","bx_REm33_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S11_abort = fs->make<TH2F>("bx_REm33_S11_abort","bx_REm33_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S11_prebeam = fs->make<TH2F>("bx_REm33_S11_prebeam","bx_REm33_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S12_abort = fs->make<TH2F>("bx_REm33_S12_abort","bx_REm33_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_S12_prebeam = fs->make<TH2F>("bx_REm33_S12_prebeam","bx_REm33_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_B_abort = fs->make<TH2F>("bx_Wp2_RB1out_B_abort","bx_Wp2_RB1out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_B_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_B_prebeam","bx_Wp2_RB1out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_B_abort = fs->make<TH2F>("bx_Wp1_RB1out_B_abort","bx_Wp1_RB1out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_B_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_B_prebeam","bx_Wp1_RB1out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_B_abort = fs->make<TH2F>("bx_W0_RB1out_B_abort","bx_W0_RB1out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_B_prebeam = fs->make<TH2F>("bx_W0_RB1out_B_prebeam","bx_W0_RB1out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_B_abort = fs->make<TH2F>("bx_Wm1_RB1out_B_abort","bx_Wm1_RB1out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_B_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_B_prebeam","bx_Wm1_RB1out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_B_abort = fs->make<TH2F>("bx_Wm2_RB1out_B_abort","bx_Wm2_RB1out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_B_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_B_prebeam","bx_Wm2_RB1out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_F_abort = fs->make<TH2F>("bx_Wp2_RB1out_F_abort","bx_Wp2_RB1out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1out_F_prebeam = fs->make<TH2F>("bx_Wp2_RB1out_F_prebeam","bx_Wp2_RB1out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_F_abort = fs->make<TH2F>("bx_Wp1_RB1out_F_abort","bx_Wp1_RB1out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1out_F_prebeam = fs->make<TH2F>("bx_Wp1_RB1out_F_prebeam","bx_Wp1_RB1out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_F_abort = fs->make<TH2F>("bx_W0_RB1out_F_abort","bx_W0_RB1out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1out_F_prebeam = fs->make<TH2F>("bx_W0_RB1out_F_prebeam","bx_W0_RB1out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_F_abort = fs->make<TH2F>("bx_Wm1_RB1out_F_abort","bx_Wm1_RB1out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1out_F_prebeam = fs->make<TH2F>("bx_Wm1_RB1out_F_prebeam","bx_Wm1_RB1out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_F_abort = fs->make<TH2F>("bx_Wm2_RB1out_F_abort","bx_Wm2_RB1out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1out_F_prebeam = fs->make<TH2F>("bx_Wm2_RB1out_F_prebeam","bx_Wm2_RB1out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_B_abort = fs->make<TH2F>("bx_Wp2_RB1in_B_abort","bx_Wp2_RB1in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_B_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_B_prebeam","bx_Wp2_RB1in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_B_abort = fs->make<TH2F>("bx_Wp1_RB1in_B_abort","bx_Wp1_RB1in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_B_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_B_prebeam","bx_Wp1_RB1in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_B_abort = fs->make<TH2F>("bx_W0_RB1in_B_abort","bx_W0_RB1in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_B_prebeam = fs->make<TH2F>("bx_W0_RB1in_B_prebeam","bx_W0_RB1in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_B_abort = fs->make<TH2F>("bx_Wm1_RB1in_B_abort","bx_Wm1_RB1in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_B_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_B_prebeam","bx_Wm1_RB1in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_B_abort = fs->make<TH2F>("bx_Wm2_RB1in_B_abort","bx_Wm2_RB1in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_B_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_B_prebeam","bx_Wm2_RB1in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_F_abort = fs->make<TH2F>("bx_Wp2_RB1in_F_abort","bx_Wp2_RB1in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB1in_F_prebeam = fs->make<TH2F>("bx_Wp2_RB1in_F_prebeam","bx_Wp2_RB1in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_F_abort = fs->make<TH2F>("bx_Wp1_RB1in_F_abort","bx_Wp1_RB1in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB1in_F_prebeam = fs->make<TH2F>("bx_Wp1_RB1in_F_prebeam","bx_Wp1_RB1in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_F_abort = fs->make<TH2F>("bx_W0_RB1in_F_abort","bx_W0_RB1in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB1in_F_prebeam = fs->make<TH2F>("bx_W0_RB1in_F_prebeam","bx_W0_RB1in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_F_abort = fs->make<TH2F>("bx_Wm1_RB1in_F_abort","bx_Wm1_RB1in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB1in_F_prebeam = fs->make<TH2F>("bx_Wm1_RB1in_F_prebeam","bx_Wm1_RB1in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_F_abort = fs->make<TH2F>("bx_Wm2_RB1in_F_abort","bx_Wm2_RB1in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB1in_F_prebeam = fs->make<TH2F>("bx_Wm2_RB1in_F_prebeam","bx_Wm2_RB1in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_B_abort = fs->make<TH2F>("bx_Wp2_RB3_B_abort","bx_Wp2_RB3_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_B_prebeam = fs->make<TH2F>("bx_Wp2_RB3_B_prebeam","bx_Wp2_RB3_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_B_abort = fs->make<TH2F>("bx_Wp1_RB3_B_abort","bx_Wp1_RB3_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_B_prebeam = fs->make<TH2F>("bx_Wp1_RB3_B_prebeam","bx_Wp1_RB3_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_B_abort = fs->make<TH2F>("bx_W0_RB3_B_abort","bx_W0_RB3_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_B_prebeam = fs->make<TH2F>("bx_W0_RB3_B_prebeam","bx_W0_RB3_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_B_abort = fs->make<TH2F>("bx_Wm1_RB3_B_abort","bx_Wm1_RB3_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_B_prebeam = fs->make<TH2F>("bx_Wm1_RB3_B_prebeam","bx_Wm1_RB3_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_B_abort = fs->make<TH2F>("bx_Wm2_RB3_B_abort","bx_Wm2_RB3_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_B_prebeam = fs->make<TH2F>("bx_Wm2_RB3_B_prebeam","bx_Wm2_RB3_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_F_abort = fs->make<TH2F>("bx_Wp2_RB3_F_abort","bx_Wp2_RB3_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB3_F_prebeam = fs->make<TH2F>("bx_Wp2_RB3_F_prebeam","bx_Wp2_RB3_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_F_abort = fs->make<TH2F>("bx_Wp1_RB3_F_abort","bx_Wp1_RB3_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB3_F_prebeam = fs->make<TH2F>("bx_Wp1_RB3_F_prebeam","bx_Wp1_RB3_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_F_abort = fs->make<TH2F>("bx_W0_RB3_F_abort","bx_W0_RB3_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB3_F_prebeam = fs->make<TH2F>("bx_W0_RB3_F_prebeam","bx_W0_RB3_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_F_abort = fs->make<TH2F>("bx_Wm1_RB3_F_abort","bx_Wm1_RB3_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB3_F_prebeam = fs->make<TH2F>("bx_Wm1_RB3_F_prebeam","bx_Wm1_RB3_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_F_abort = fs->make<TH2F>("bx_Wm2_RB3_F_abort","bx_Wm2_RB3_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB3_F_prebeam = fs->make<TH2F>("bx_Wm2_RB3_F_prebeam","bx_Wm2_RB3_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_B_abort = fs->make<TH2F>("bx_Wp2_RB4_B_abort","bx_Wp2_RB4_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_B_prebeam = fs->make<TH2F>("bx_Wp2_RB4_B_prebeam","bx_Wp2_RB4_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_B_abort = fs->make<TH2F>("bx_Wp1_RB4_B_abort","bx_Wp1_RB4_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_B_prebeam = fs->make<TH2F>("bx_Wp1_RB4_B_prebeam","bx_Wp1_RB4_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_B_abort = fs->make<TH2F>("bx_W0_RB4_B_abort","bx_W0_RB4_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_B_prebeam = fs->make<TH2F>("bx_W0_RB4_B_prebeam","bx_W0_RB4_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_B_abort = fs->make<TH2F>("bx_Wm1_RB4_B_abort","bx_Wm1_RB4_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_B_prebeam = fs->make<TH2F>("bx_Wm1_RB4_B_prebeam","bx_Wm1_RB4_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_B_abort = fs->make<TH2F>("bx_Wm2_RB4_B_abort","bx_Wm2_RB4_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_B_prebeam = fs->make<TH2F>("bx_Wm2_RB4_B_prebeam","bx_Wm2_RB4_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_F_abort = fs->make<TH2F>("bx_Wp2_RB4_F_abort","bx_Wp2_RB4_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB4_F_prebeam = fs->make<TH2F>("bx_Wp2_RB4_F_prebeam","bx_Wp2_RB4_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_F_abort = fs->make<TH2F>("bx_Wp1_RB4_F_abort","bx_Wp1_RB4_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB4_F_prebeam = fs->make<TH2F>("bx_Wp1_RB4_F_prebeam","bx_Wp1_RB4_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_F_abort = fs->make<TH2F>("bx_W0_RB4_F_abort","bx_W0_RB4_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB4_F_prebeam = fs->make<TH2F>("bx_W0_RB4_F_prebeam","bx_W0_RB4_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_F_abort = fs->make<TH2F>("bx_Wm1_RB4_F_abort","bx_Wm1_RB4_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB4_F_prebeam = fs->make<TH2F>("bx_Wm1_RB4_F_prebeam","bx_Wm1_RB4_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_F_abort = fs->make<TH2F>("bx_Wm2_RB4_F_abort","bx_Wm2_RB4_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB4_F_prebeam = fs->make<TH2F>("bx_Wm2_RB4_F_prebeam","bx_Wm2_RB4_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_B_abort = fs->make<TH2F>("bx_Wp2_RB2out_B_abort","bx_Wp2_RB2out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_B_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_B_prebeam","bx_Wp2_RB2out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_B_abort = fs->make<TH2F>("bx_Wp1_RB2out_B_abort","bx_Wp1_RB2out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_B_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_B_prebeam","bx_Wp1_RB2out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_B_abort = fs->make<TH2F>("bx_W0_RB2out_B_abort","bx_W0_RB2out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_B_prebeam = fs->make<TH2F>("bx_W0_RB2out_B_prebeam","bx_W0_RB2out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_B_abort = fs->make<TH2F>("bx_Wm1_RB2out_B_abort","bx_Wm1_RB2out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_B_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_B_prebeam","bx_Wm1_RB2out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_B_abort = fs->make<TH2F>("bx_Wm2_RB2out_B_abort","bx_Wm2_RB2out_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_B_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_B_prebeam","bx_Wm2_RB2out_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_F_abort = fs->make<TH2F>("bx_Wp2_RB2out_F_abort","bx_Wp2_RB2out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_F_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_F_prebeam","bx_Wp2_RB2out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_F_abort = fs->make<TH2F>("bx_Wp1_RB2out_F_abort","bx_Wp1_RB2out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2out_F_prebeam = fs->make<TH2F>("bx_Wp1_RB2out_F_prebeam","bx_Wp1_RB2out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_F_abort = fs->make<TH2F>("bx_W0_RB2out_F_abort","bx_W0_RB2out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2out_F_prebeam = fs->make<TH2F>("bx_W0_RB2out_F_prebeam","bx_W0_RB2out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_F_abort = fs->make<TH2F>("bx_Wm1_RB2out_F_abort","bx_Wm1_RB2out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2out_F_prebeam = fs->make<TH2F>("bx_Wm1_RB2out_F_prebeam","bx_Wm1_RB2out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_F_abort = fs->make<TH2F>("bx_Wm2_RB2out_F_abort","bx_Wm2_RB2out_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_F_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_F_prebeam","bx_Wm2_RB2out_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_M_abort = fs->make<TH2F>("bx_Wp2_RB2out_M_abort","bx_Wp2_RB2out_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2out_M_prebeam = fs->make<TH2F>("bx_Wp2_RB2out_M_prebeam","bx_Wp2_RB2out_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_M_abort = fs->make<TH2F>("bx_Wm2_RB2out_M_abort","bx_Wm2_RB2out_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2out_M_prebeam = fs->make<TH2F>("bx_Wm2_RB2out_M_prebeam","bx_Wm2_RB2out_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_B_abort = fs->make<TH2F>("bx_Wp2_RB2in_B_abort","bx_Wp2_RB2in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_B_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_B_prebeam","bx_Wp2_RB2in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_B_abort = fs->make<TH2F>("bx_Wp1_RB2in_B_abort","bx_Wp1_RB2in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_B_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_B_prebeam","bx_Wp1_RB2in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_B_abort = fs->make<TH2F>("bx_W0_RB2in_B_abort","bx_W0_RB2in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_B_prebeam = fs->make<TH2F>("bx_W0_RB2in_B_prebeam","bx_W0_RB2in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_B_abort = fs->make<TH2F>("bx_Wm1_RB2in_B_abort","bx_Wm1_RB2in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_B_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_B_prebeam","bx_Wm1_RB2in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_B_abort = fs->make<TH2F>("bx_Wm2_RB2in_B_abort","bx_Wm2_RB2in_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_B_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_B_prebeam","bx_Wm2_RB2in_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_F_abort = fs->make<TH2F>("bx_Wp2_RB2in_F_abort","bx_Wp2_RB2in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp2_RB2in_F_prebeam = fs->make<TH2F>("bx_Wp2_RB2in_F_prebeam","bx_Wp2_RB2in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_F_abort = fs->make<TH2F>("bx_Wp1_RB2in_F_abort","bx_Wp1_RB2in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_F_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_F_prebeam","bx_Wp1_RB2in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_F_abort = fs->make<TH2F>("bx_W0_RB2in_F_abort","bx_W0_RB2in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_F_prebeam = fs->make<TH2F>("bx_W0_RB2in_F_prebeam","bx_W0_RB2in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_F_abort = fs->make<TH2F>("bx_Wm1_RB2in_F_abort","bx_Wm1_RB2in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_F_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_F_prebeam","bx_Wm1_RB2in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_F_abort = fs->make<TH2F>("bx_Wm2_RB2in_F_abort","bx_Wm2_RB2in_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm2_RB2in_F_prebeam = fs->make<TH2F>("bx_Wm2_RB2in_F_prebeam","bx_Wm2_RB2in_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_M_abort = fs->make<TH2F>("bx_Wp1_RB2in_M_abort","bx_Wp1_RB2in_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wp1_RB2in_M_prebeam = fs->make<TH2F>("bx_Wp1_RB2in_M_prebeam","bx_Wp1_RB2in_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_M_abort = fs->make<TH2F>("bx_W0_RB2in_M_abort","bx_W0_RB2in_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_W0_RB2in_M_prebeam = fs->make<TH2F>("bx_W0_RB2in_M_prebeam","bx_W0_RB2in_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_M_abort = fs->make<TH2F>("bx_Wm1_RB2in_M_abort","bx_Wm1_RB2in_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_Wm1_RB2in_M_prebeam = fs->make<TH2F>("bx_Wm1_RB2in_M_prebeam","bx_Wm1_RB2in_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_B_abort = fs->make<TH2F>("bx_REp12_B_abort","bx_REp12_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_B_prebeam = fs->make<TH2F>("bx_REp12_B_prebeam","bx_REp12_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_M_abort = fs->make<TH2F>("bx_REp12_M_abort","bx_REp12_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_M_prebeam = fs->make<TH2F>("bx_REp12_M_prebeam","bx_REp12_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_F_abort = fs->make<TH2F>("bx_REp12_F_abort","bx_REp12_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp12_F_prebeam = fs->make<TH2F>("bx_REp12_F_prebeam","bx_REp12_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_B_abort = fs->make<TH2F>("bx_REp13_B_abort","bx_REp13_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_B_prebeam = fs->make<TH2F>("bx_REp13_B_prebeam","bx_REp13_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_M_abort = fs->make<TH2F>("bx_REp13_M_abort","bx_REp13_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_M_prebeam = fs->make<TH2F>("bx_REp13_M_prebeam","bx_REp13_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_F_abort = fs->make<TH2F>("bx_REp13_F_abort","bx_REp13_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp13_F_prebeam = fs->make<TH2F>("bx_REp13_F_prebeam","bx_REp13_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_B_abort = fs->make<TH2F>("bx_REp42_B_abort","bx_REp42_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_B_prebeam = fs->make<TH2F>("bx_REp42_B_prebeam","bx_REp42_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_M_abort = fs->make<TH2F>("bx_REp42_M_abort","bx_REp42_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_M_prebeam = fs->make<TH2F>("bx_REp42_M_prebeam","bx_REp42_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_F_abort = fs->make<TH2F>("bx_REp42_F_abort","bx_REp42_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp42_F_prebeam = fs->make<TH2F>("bx_REp42_F_prebeam","bx_REp42_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_B_abort = fs->make<TH2F>("bx_REp43_B_abort","bx_REp43_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_B_prebeam = fs->make<TH2F>("bx_REp43_B_prebeam","bx_REp43_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_M_abort = fs->make<TH2F>("bx_REp43_M_abort","bx_REp43_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_M_prebeam = fs->make<TH2F>("bx_REp43_M_prebeam","bx_REp43_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_F_abort = fs->make<TH2F>("bx_REp43_F_abort","bx_REp43_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp43_F_prebeam = fs->make<TH2F>("bx_REp43_F_prebeam","bx_REp43_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_B_abort = fs->make<TH2F>("bx_REp22_B_abort","bx_REp22_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_B_prebeam = fs->make<TH2F>("bx_REp22_B_prebeam","bx_REp22_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_M_abort = fs->make<TH2F>("bx_REp22_M_abort","bx_REp22_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_M_prebeam = fs->make<TH2F>("bx_REp22_M_prebeam","bx_REp22_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_F_abort = fs->make<TH2F>("bx_REp22_F_abort","bx_REp22_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp22_F_prebeam = fs->make<TH2F>("bx_REp22_F_prebeam","bx_REp22_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_B_abort = fs->make<TH2F>("bx_REp23_B_abort","bx_REp23_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_B_prebeam = fs->make<TH2F>("bx_REp23_B_prebeam","bx_REp23_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_M_abort = fs->make<TH2F>("bx_REp23_M_abort","bx_REp23_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_M_prebeam = fs->make<TH2F>("bx_REp23_M_prebeam","bx_REp23_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_F_abort = fs->make<TH2F>("bx_REp23_F_abort","bx_REp23_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp23_F_prebeam = fs->make<TH2F>("bx_REp23_F_prebeam","bx_REp23_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_B_abort = fs->make<TH2F>("bx_REp32_B_abort","bx_REp32_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_B_prebeam = fs->make<TH2F>("bx_REp32_B_prebeam","bx_REp32_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_M_abort = fs->make<TH2F>("bx_REp32_M_abort","bx_REp32_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_M_prebeam = fs->make<TH2F>("bx_REp32_M_prebeam","bx_REp32_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_F_abort = fs->make<TH2F>("bx_REp32_F_abort","bx_REp32_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp32_F_prebeam = fs->make<TH2F>("bx_REp32_F_prebeam","bx_REp32_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_B_abort = fs->make<TH2F>("bx_REp33_B_abort","bx_REp33_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_B_prebeam = fs->make<TH2F>("bx_REp33_B_prebeam","bx_REp33_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_M_abort = fs->make<TH2F>("bx_REp33_M_abort","bx_REp33_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_M_prebeam = fs->make<TH2F>("bx_REp33_M_prebeam","bx_REp33_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_F_abort = fs->make<TH2F>("bx_REp33_F_abort","bx_REp33_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REp33_F_prebeam = fs->make<TH2F>("bx_REp33_F_prebeam","bx_REp33_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S01_abort = fs->make<TH2F>("bx_REm42_S01_abort","bx_REm42_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S01_prebeam = fs->make<TH2F>("bx_REm42_S01_prebeam","bx_REm42_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S02_abort = fs->make<TH2F>("bx_REm42_S02_abort","bx_REm42_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S02_prebeam = fs->make<TH2F>("bx_REm42_S02_prebeam","bx_REm42_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S03_abort = fs->make<TH2F>("bx_REm42_S03_abort","bx_REm42_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S03_prebeam = fs->make<TH2F>("bx_REm42_S03_prebeam","bx_REm42_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S04_abort = fs->make<TH2F>("bx_REm42_S04_abort","bx_REm42_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S04_prebeam = fs->make<TH2F>("bx_REm42_S04_prebeam","bx_REm42_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S05_abort = fs->make<TH2F>("bx_REm42_S05_abort","bx_REm42_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S05_prebeam = fs->make<TH2F>("bx_REm42_S05_prebeam","bx_REm42_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S06_abort = fs->make<TH2F>("bx_REm42_S06_abort","bx_REm42_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S06_prebeam = fs->make<TH2F>("bx_REm42_S06_prebeam","bx_REm42_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S07_abort = fs->make<TH2F>("bx_REm42_S07_abort","bx_REm42_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S07_prebeam = fs->make<TH2F>("bx_REm42_S07_prebeam","bx_REm42_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S08_abort = fs->make<TH2F>("bx_REm42_S08_abort","bx_REm42_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S08_prebeam = fs->make<TH2F>("bx_REm42_S08_prebeam","bx_REm42_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S09_abort = fs->make<TH2F>("bx_REm42_S09_abort","bx_REm42_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S09_prebeam = fs->make<TH2F>("bx_REm42_S09_prebeam","bx_REm42_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S10_abort = fs->make<TH2F>("bx_REm42_S10_abort","bx_REm42_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S10_prebeam = fs->make<TH2F>("bx_REm42_S10_prebeam","bx_REm42_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S11_abort = fs->make<TH2F>("bx_REm42_S11_abort","bx_REm42_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S11_prebeam = fs->make<TH2F>("bx_REm42_S11_prebeam","bx_REm42_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S12_abort = fs->make<TH2F>("bx_REm42_S12_abort","bx_REm42_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_S12_prebeam = fs->make<TH2F>("bx_REm42_S12_prebeam","bx_REm42_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S01_abort = fs->make<TH2F>("bx_REm43_S01_abort","bx_REm43_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S01_prebeam = fs->make<TH2F>("bx_REm43_S01_prebeam","bx_REm43_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S02_abort = fs->make<TH2F>("bx_REm43_S02_abort","bx_REm43_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S02_prebeam = fs->make<TH2F>("bx_REm43_S02_prebeam","bx_REm43_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S03_abort = fs->make<TH2F>("bx_REm43_S03_abort","bx_REm43_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S03_prebeam = fs->make<TH2F>("bx_REm43_S03_prebeam","bx_REm43_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S04_abort = fs->make<TH2F>("bx_REm43_S04_abort","bx_REm43_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S04_prebeam = fs->make<TH2F>("bx_REm43_S04_prebeam","bx_REm43_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S05_abort = fs->make<TH2F>("bx_REm43_S05_abort","bx_REm43_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S05_prebeam = fs->make<TH2F>("bx_REm43_S05_prebeam","bx_REm43_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S06_abort = fs->make<TH2F>("bx_REm43_S06_abort","bx_REm43_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S06_prebeam = fs->make<TH2F>("bx_REm43_S06_prebeam","bx_REm43_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S07_abort = fs->make<TH2F>("bx_REm43_S07_abort","bx_REm43_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S07_prebeam = fs->make<TH2F>("bx_REm43_S07_prebeam","bx_REm43_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S08_abort = fs->make<TH2F>("bx_REm43_S08_abort","bx_REm43_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S08_prebeam = fs->make<TH2F>("bx_REm43_S08_prebeam","bx_REm43_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S09_abort = fs->make<TH2F>("bx_REm43_S09_abort","bx_REm43_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S09_prebeam = fs->make<TH2F>("bx_REm43_S09_prebeam","bx_REm43_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S10_abort = fs->make<TH2F>("bx_REm43_S10_abort","bx_REm43_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S10_prebeam = fs->make<TH2F>("bx_REm43_S10_prebeam","bx_REm43_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S11_abort = fs->make<TH2F>("bx_REm43_S11_abort","bx_REm43_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S11_prebeam = fs->make<TH2F>("bx_REm43_S11_prebeam","bx_REm43_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S12_abort = fs->make<TH2F>("bx_REm43_S12_abort","bx_REm43_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_S12_prebeam = fs->make<TH2F>("bx_REm43_S12_prebeam","bx_REm43_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S01_abort = fs->make<TH2F>("bx_REm12_S01_abort","bx_REm12_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S01_prebeam = fs->make<TH2F>("bx_REm12_S01_prebeam","bx_REm12_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S02_abort = fs->make<TH2F>("bx_REm12_S02_abort","bx_REm12_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S02_prebeam = fs->make<TH2F>("bx_REm12_S02_prebeam","bx_REm12_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S03_abort = fs->make<TH2F>("bx_REm12_S03_abort","bx_REm12_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S03_prebeam = fs->make<TH2F>("bx_REm12_S03_prebeam","bx_REm12_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S04_abort = fs->make<TH2F>("bx_REm12_S04_abort","bx_REm12_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S04_prebeam = fs->make<TH2F>("bx_REm12_S04_prebeam","bx_REm12_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S05_abort = fs->make<TH2F>("bx_REm12_S05_abort","bx_REm12_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S05_prebeam = fs->make<TH2F>("bx_REm12_S05_prebeam","bx_REm12_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S06_abort = fs->make<TH2F>("bx_REm12_S06_abort","bx_REm12_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S06_prebeam = fs->make<TH2F>("bx_REm12_S06_prebeam","bx_REm12_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S07_abort = fs->make<TH2F>("bx_REm12_S07_abort","bx_REm12_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S07_prebeam = fs->make<TH2F>("bx_REm12_S07_prebeam","bx_REm12_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S08_abort = fs->make<TH2F>("bx_REm12_S08_abort","bx_REm12_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S08_prebeam = fs->make<TH2F>("bx_REm12_S08_prebeam","bx_REm12_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S09_abort = fs->make<TH2F>("bx_REm12_S09_abort","bx_REm12_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S09_prebeam = fs->make<TH2F>("bx_REm12_S09_prebeam","bx_REm12_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S10_abort = fs->make<TH2F>("bx_REm12_S10_abort","bx_REm12_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S10_prebeam = fs->make<TH2F>("bx_REm12_S10_prebeam","bx_REm12_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S11_abort = fs->make<TH2F>("bx_REm12_S11_abort","bx_REm12_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S11_prebeam = fs->make<TH2F>("bx_REm12_S11_prebeam","bx_REm12_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S12_abort = fs->make<TH2F>("bx_REm12_S12_abort","bx_REm12_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_S12_prebeam = fs->make<TH2F>("bx_REm12_S12_prebeam","bx_REm12_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S01_abort = fs->make<TH2F>("bx_REm13_S01_abort","bx_REm13_S01_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S01_prebeam = fs->make<TH2F>("bx_REm13_S01_prebeam","bx_REm13_S01_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S02_abort = fs->make<TH2F>("bx_REm13_S02_abort","bx_REm13_S02_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S02_prebeam = fs->make<TH2F>("bx_REm13_S02_prebeam","bx_REm13_S02_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S03_abort = fs->make<TH2F>("bx_REm13_S03_abort","bx_REm13_S03_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S03_prebeam = fs->make<TH2F>("bx_REm13_S03_prebeam","bx_REm13_S03_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S04_abort = fs->make<TH2F>("bx_REm13_S04_abort","bx_REm13_S04_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S04_prebeam = fs->make<TH2F>("bx_REm13_S04_prebeam","bx_REm13_S04_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S05_abort = fs->make<TH2F>("bx_REm13_S05_abort","bx_REm13_S05_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S05_prebeam = fs->make<TH2F>("bx_REm13_S05_prebeam","bx_REm13_S05_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S06_abort = fs->make<TH2F>("bx_REm13_S06_abort","bx_REm13_S06_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S06_prebeam = fs->make<TH2F>("bx_REm13_S06_prebeam","bx_REm13_S06_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S07_abort = fs->make<TH2F>("bx_REm13_S07_abort","bx_REm13_S07_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S07_prebeam = fs->make<TH2F>("bx_REm13_S07_prebeam","bx_REm13_S07_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S08_abort = fs->make<TH2F>("bx_REm13_S08_abort","bx_REm13_S08_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S08_prebeam = fs->make<TH2F>("bx_REm13_S08_prebeam","bx_REm13_S08_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S09_abort = fs->make<TH2F>("bx_REm13_S09_abort","bx_REm13_S09_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S09_prebeam = fs->make<TH2F>("bx_REm13_S09_prebeam","bx_REm13_S09_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S10_abort = fs->make<TH2F>("bx_REm13_S10_abort","bx_REm13_S10_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S10_prebeam = fs->make<TH2F>("bx_REm13_S10_prebeam","bx_REm13_S10_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S11_abort = fs->make<TH2F>("bx_REm13_S11_abort","bx_REm13_S11_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S11_prebeam = fs->make<TH2F>("bx_REm13_S11_prebeam","bx_REm13_S11_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S12_abort = fs->make<TH2F>("bx_REm13_S12_abort","bx_REm13_S12_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_S12_prebeam = fs->make<TH2F>("bx_REm13_S12_prebeam","bx_REm13_S12_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_B_abort = fs->make<TH2F>("bx_REm12_B_abort","bx_REm12_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_B_prebeam = fs->make<TH2F>("bx_REm12_B_prebeam","bx_REm12_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_M_abort = fs->make<TH2F>("bx_REm12_M_abort","bx_REm12_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_M_prebeam = fs->make<TH2F>("bx_REm12_M_prebeam","bx_REm12_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_F_abort = fs->make<TH2F>("bx_REm12_F_abort","bx_REm12_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm12_F_prebeam = fs->make<TH2F>("bx_REm12_F_prebeam","bx_REm12_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_B_abort = fs->make<TH2F>("bx_REm13_B_abort","bx_REm13_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_B_prebeam = fs->make<TH2F>("bx_REm13_B_prebeam","bx_REm13_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_M_abort = fs->make<TH2F>("bx_REm13_M_abort","bx_REm13_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_M_prebeam = fs->make<TH2F>("bx_REm13_M_prebeam","bx_REm13_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_F_abort = fs->make<TH2F>("bx_REm13_F_abort","bx_REm13_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm13_F_prebeam = fs->make<TH2F>("bx_REm13_F_prebeam","bx_REm13_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_B_abort = fs->make<TH2F>("bx_REm42_B_abort","bx_REm42_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_B_prebeam = fs->make<TH2F>("bx_REm42_B_prebeam","bx_REm42_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_M_abort = fs->make<TH2F>("bx_REm42_M_abort","bx_REm42_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_M_prebeam = fs->make<TH2F>("bx_REm42_M_prebeam","bx_REm42_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_F_abort = fs->make<TH2F>("bx_REm42_F_abort","bx_REm42_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm42_F_prebeam = fs->make<TH2F>("bx_REm42_F_prebeam","bx_REm42_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_B_abort = fs->make<TH2F>("bx_REm43_B_abort","bx_REm43_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_B_prebeam = fs->make<TH2F>("bx_REm43_B_prebeam","bx_REm43_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_M_abort = fs->make<TH2F>("bx_REm43_M_abort","bx_REm43_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_M_prebeam = fs->make<TH2F>("bx_REm43_M_prebeam","bx_REm43_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_F_abort = fs->make<TH2F>("bx_REm43_F_abort","bx_REm43_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm43_F_prebeam = fs->make<TH2F>("bx_REm43_F_prebeam","bx_REm43_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_B_abort = fs->make<TH2F>("bx_REm22_B_abort","bx_REm22_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_B_prebeam = fs->make<TH2F>("bx_REm22_B_prebeam","bx_REm22_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_M_abort = fs->make<TH2F>("bx_REm22_M_abort","bx_REm22_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_M_prebeam = fs->make<TH2F>("bx_REm22_M_prebeam","bx_REm22_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_F_abort = fs->make<TH2F>("bx_REm22_F_abort","bx_REm22_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm22_F_prebeam = fs->make<TH2F>("bx_REm22_F_prebeam","bx_REm22_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_B_abort = fs->make<TH2F>("bx_REm23_B_abort","bx_REm23_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_B_prebeam = fs->make<TH2F>("bx_REm23_B_prebeam","bx_REm23_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_M_abort = fs->make<TH2F>("bx_REm23_M_abort","bx_REm23_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_M_prebeam = fs->make<TH2F>("bx_REm23_M_prebeam","bx_REm23_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_F_abort = fs->make<TH2F>("bx_REm23_F_abort","bx_REm23_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm23_F_prebeam = fs->make<TH2F>("bx_REm23_F_prebeam","bx_REm23_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_B_abort = fs->make<TH2F>("bx_REm32_B_abort","bx_REm32_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_B_prebeam = fs->make<TH2F>("bx_REm32_B_prebeam","bx_REm32_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_M_abort = fs->make<TH2F>("bx_REm32_M_abort","bx_REm32_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_M_prebeam = fs->make<TH2F>("bx_REm32_M_prebeam","bx_REm32_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_F_abort = fs->make<TH2F>("bx_REm32_F_abort","bx_REm32_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm32_F_prebeam = fs->make<TH2F>("bx_REm32_F_prebeam","bx_REm32_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_B_abort = fs->make<TH2F>("bx_REm33_B_abort","bx_REm33_B_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_B_prebeam = fs->make<TH2F>("bx_REm33_B_prebeam","bx_REm33_B_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_M_abort = fs->make<TH2F>("bx_REm33_M_abort","bx_REm33_M_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_M_prebeam = fs->make<TH2F>("bx_REm33_M_prebeam","bx_REm33_M_prebeam",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_F_abort = fs->make<TH2F>("bx_REm33_F_abort","bx_REm33_F_abort",21,-0.5,20.5,11,-5.5,5.5);
bx_REm33_F_prebeam = fs->make<TH2F>("bx_REm33_F_prebeam","bx_REm33_F_prebeam",21,-0.5,20.5,11,-5.5,5.5);





 
}

// ------------ method called once each job just after ending the event loop  ------------
void
RateVsLumi_PhiEtaRecompute::endJob()
{


  std::cout<<"areaWm2_RB1in_S01: "<<areaWm2_RB1in_S01<<std::endl;
  std::cout<<"areaWm2_RB1in_S02: "<<areaWm2_RB1in_S02<<std::endl;
  std::cout<<"areaWm2_RB1in_S03: "<<areaWm2_RB1in_S03<<std::endl;
  std::cout<<"areaWm2_RB1in_S04: "<<areaWm2_RB1in_S04<<std::endl;
  std::cout<<"areaWm2_RB1in_S05: "<<areaWm2_RB1in_S05<<std::endl;
  std::cout<<"areaWm2_RB1in_S06: "<<areaWm2_RB1in_S06<<std::endl;
  std::cout<<"areaWm2_RB1in_S07: "<<areaWm2_RB1in_S07<<std::endl;
  std::cout<<"areaWm2_RB1in_S08: "<<areaWm2_RB1in_S08<<std::endl;
  std::cout<<"areaWm2_RB1in_S09: "<<areaWm2_RB1in_S09<<std::endl;
  std::cout<<"areaWm2_RB1in_S10: "<<areaWm2_RB1in_S10<<std::endl;
  std::cout<<"areaWm2_RB1in_S11: "<<areaWm2_RB1in_S11<<std::endl;
  std::cout<<"areaWm2_RB1in_S12: "<<areaWm2_RB1in_S12<<std::endl;

  std::cout<<"areaWm1_RB1in_S01: "<<areaWm1_RB1in_S01<<std::endl;
  std::cout<<"areaWm1_RB1in_S02: "<<areaWm1_RB1in_S02<<std::endl;
  std::cout<<"areaWm1_RB1in_S03: "<<areaWm1_RB1in_S03<<std::endl;
  std::cout<<"areaWm1_RB1in_S04: "<<areaWm1_RB1in_S04<<std::endl;
  std::cout<<"areaWm1_RB1in_S05: "<<areaWm1_RB1in_S05<<std::endl;
  std::cout<<"areaWm1_RB1in_S06: "<<areaWm1_RB1in_S06<<std::endl;
  std::cout<<"areaWm1_RB1in_S07: "<<areaWm1_RB1in_S07<<std::endl;
  std::cout<<"areaWm1_RB1in_S08: "<<areaWm1_RB1in_S08<<std::endl;
  std::cout<<"areaWm1_RB1in_S09: "<<areaWm1_RB1in_S09<<std::endl;
  std::cout<<"areaWm1_RB1in_S10: "<<areaWm1_RB1in_S10<<std::endl;
  std::cout<<"areaWm1_RB1in_S11: "<<areaWm1_RB1in_S11<<std::endl;
  std::cout<<"areaWm1_RB1in_S12: "<<areaWm1_RB1in_S12<<std::endl;

  std::cout<<"areaW0_RB1in_S01: "<<areaW0_RB1in_S01<<std::endl;
  std::cout<<"areaW0_RB1in_S02: "<<areaW0_RB1in_S02<<std::endl;
  std::cout<<"areaW0_RB1in_S03: "<<areaW0_RB1in_S03<<std::endl;
  std::cout<<"areaW0_RB1in_S04: "<<areaW0_RB1in_S04<<std::endl;
  std::cout<<"areaW0_RB1in_S05: "<<areaW0_RB1in_S05<<std::endl;
  std::cout<<"areaW0_RB1in_S06: "<<areaW0_RB1in_S06<<std::endl;
  std::cout<<"areaW0_RB1in_S07: "<<areaW0_RB1in_S07<<std::endl;
  std::cout<<"areaW0_RB1in_S08: "<<areaW0_RB1in_S08<<std::endl;
  std::cout<<"areaW0_RB1in_S09: "<<areaW0_RB1in_S09<<std::endl;
  std::cout<<"areaW0_RB1in_S10: "<<areaW0_RB1in_S10<<std::endl;
  std::cout<<"areaW0_RB1in_S11: "<<areaW0_RB1in_S11<<std::endl;
  std::cout<<"areaW0_RB1in_S12: "<<areaW0_RB1in_S12<<std::endl;

  std::cout<<"areaWp1_RB1in_S01: "<<areaWp1_RB1in_S01<<std::endl;
  std::cout<<"areaWp1_RB1in_S02: "<<areaWp1_RB1in_S02<<std::endl;
  std::cout<<"areaWp1_RB1in_S03: "<<areaWp1_RB1in_S03<<std::endl;
  std::cout<<"areaWp1_RB1in_S04: "<<areaWp1_RB1in_S04<<std::endl;
  std::cout<<"areaWp1_RB1in_S05: "<<areaWp1_RB1in_S05<<std::endl;
  std::cout<<"areaWp1_RB1in_S06: "<<areaWp1_RB1in_S06<<std::endl;
  std::cout<<"areaWp1_RB1in_S07: "<<areaWp1_RB1in_S07<<std::endl;
  std::cout<<"areaWp1_RB1in_S08: "<<areaWp1_RB1in_S08<<std::endl;
  std::cout<<"areaWp1_RB1in_S09: "<<areaWp1_RB1in_S09<<std::endl;
  std::cout<<"areaWp1_RB1in_S10: "<<areaWp1_RB1in_S10<<std::endl;
  std::cout<<"areaWp1_RB1in_S11: "<<areaWp1_RB1in_S11<<std::endl;
  std::cout<<"areaWp1_RB1in_S12: "<<areaWp1_RB1in_S12<<std::endl;

  std::cout<<"areaWp2_RB1in_S01: "<<areaWp2_RB1in_S01<<std::endl;
  std::cout<<"areaWp2_RB1in_S02: "<<areaWp2_RB1in_S02<<std::endl;
  std::cout<<"areaWp2_RB1in_S03: "<<areaWp2_RB1in_S03<<std::endl;
  std::cout<<"areaWp2_RB1in_S04: "<<areaWp2_RB1in_S04<<std::endl;
  std::cout<<"areaWp2_RB1in_S05: "<<areaWp2_RB1in_S05<<std::endl;
  std::cout<<"areaWp2_RB1in_S06: "<<areaWp2_RB1in_S06<<std::endl;
  std::cout<<"areaWp2_RB1in_S07: "<<areaWp2_RB1in_S07<<std::endl;
  std::cout<<"areaWp2_RB1in_S08: "<<areaWp2_RB1in_S08<<std::endl;
  std::cout<<"areaWp2_RB1in_S09: "<<areaWp2_RB1in_S09<<std::endl;
  std::cout<<"areaWp2_RB1in_S10: "<<areaWp2_RB1in_S10<<std::endl;
  std::cout<<"areaWp2_RB1in_S11: "<<areaWp2_RB1in_S11<<std::endl;
  std::cout<<"areaWp2_RB1in_S12: "<<areaWp2_RB1in_S12<<std::endl;

  std::cout<<"areaWm2_RB1out_S01: "<<areaWm2_RB1out_S01<<std::endl;
  std::cout<<"areaWm2_RB1out_S02: "<<areaWm2_RB1out_S02<<std::endl;
  std::cout<<"areaWm2_RB1out_S03: "<<areaWm2_RB1out_S03<<std::endl;
  std::cout<<"areaWm2_RB1out_S04: "<<areaWm2_RB1out_S04<<std::endl;
  std::cout<<"areaWm2_RB1out_S05: "<<areaWm2_RB1out_S05<<std::endl;
  std::cout<<"areaWm2_RB1out_S06: "<<areaWm2_RB1out_S06<<std::endl;
  std::cout<<"areaWm2_RB1out_S07: "<<areaWm2_RB1out_S07<<std::endl;
  std::cout<<"areaWm2_RB1out_S08: "<<areaWm2_RB1out_S08<<std::endl;
  std::cout<<"areaWm2_RB1out_S09: "<<areaWm2_RB1out_S09<<std::endl;
  std::cout<<"areaWm2_RB1out_S10: "<<areaWm2_RB1out_S10<<std::endl;
  std::cout<<"areaWm2_RB1out_S11: "<<areaWm2_RB1out_S11<<std::endl;
  std::cout<<"areaWm2_RB1out_S12: "<<areaWm2_RB1out_S12<<std::endl;

  std::cout<<"areaWm1_RB1out_S01: "<<areaWm1_RB1out_S01<<std::endl;
  std::cout<<"areaWm1_RB1out_S02: "<<areaWm1_RB1out_S02<<std::endl;
  std::cout<<"areaWm1_RB1out_S03: "<<areaWm1_RB1out_S03<<std::endl;
  std::cout<<"areaWm1_RB1out_S04: "<<areaWm1_RB1out_S04<<std::endl;
  std::cout<<"areaWm1_RB1out_S05: "<<areaWm1_RB1out_S05<<std::endl;
  std::cout<<"areaWm1_RB1out_S06: "<<areaWm1_RB1out_S06<<std::endl;
  std::cout<<"areaWm1_RB1out_S07: "<<areaWm1_RB1out_S07<<std::endl;
  std::cout<<"areaWm1_RB1out_S08: "<<areaWm1_RB1out_S08<<std::endl;
  std::cout<<"areaWm1_RB1out_S09: "<<areaWm1_RB1out_S09<<std::endl;
  std::cout<<"areaWm1_RB1out_S10: "<<areaWm1_RB1out_S10<<std::endl;
  std::cout<<"areaWm1_RB1out_S11: "<<areaWm1_RB1out_S11<<std::endl;
  std::cout<<"areaWm1_RB1out_S12: "<<areaWm1_RB1out_S12<<std::endl;

  std::cout<<"areaW0_RB1out_S01: "<<areaW0_RB1out_S01<<std::endl;
  std::cout<<"areaW0_RB1out_S02: "<<areaW0_RB1out_S02<<std::endl;
  std::cout<<"areaW0_RB1out_S03: "<<areaW0_RB1out_S03<<std::endl;
  std::cout<<"areaW0_RB1out_S04: "<<areaW0_RB1out_S04<<std::endl;
  std::cout<<"areaW0_RB1out_S05: "<<areaW0_RB1out_S05<<std::endl;
  std::cout<<"areaW0_RB1out_S06: "<<areaW0_RB1out_S06<<std::endl;
  std::cout<<"areaW0_RB1out_S07: "<<areaW0_RB1out_S07<<std::endl;
  std::cout<<"areaW0_RB1out_S08: "<<areaW0_RB1out_S08<<std::endl;
  std::cout<<"areaW0_RB1out_S09: "<<areaW0_RB1out_S09<<std::endl;
  std::cout<<"areaW0_RB1out_S10: "<<areaW0_RB1out_S10<<std::endl;
  std::cout<<"areaW0_RB1out_S11: "<<areaW0_RB1out_S11<<std::endl;
  std::cout<<"areaW0_RB1out_S12: "<<areaW0_RB1out_S12<<std::endl;

  std::cout<<"areaWp1_RB1out_S01: "<<areaWp1_RB1out_S01<<std::endl;
  std::cout<<"areaWp1_RB1out_S02: "<<areaWp1_RB1out_S02<<std::endl;
  std::cout<<"areaWp1_RB1out_S03: "<<areaWp1_RB1out_S03<<std::endl;
  std::cout<<"areaWp1_RB1out_S04: "<<areaWp1_RB1out_S04<<std::endl;
  std::cout<<"areaWp1_RB1out_S05: "<<areaWp1_RB1out_S05<<std::endl;
  std::cout<<"areaWp1_RB1out_S06: "<<areaWp1_RB1out_S06<<std::endl;
  std::cout<<"areaWp1_RB1out_S07: "<<areaWp1_RB1out_S07<<std::endl;
  std::cout<<"areaWp1_RB1out_S08: "<<areaWp1_RB1out_S08<<std::endl;
  std::cout<<"areaWp1_RB1out_S09: "<<areaWp1_RB1out_S09<<std::endl;
  std::cout<<"areaWp1_RB1out_S10: "<<areaWp1_RB1out_S10<<std::endl;
  std::cout<<"areaWp1_RB1out_S11: "<<areaWp1_RB1out_S11<<std::endl;
  std::cout<<"areaWp1_RB1out_S12: "<<areaWp1_RB1out_S12<<std::endl;

  std::cout<<"areaWp2_RB1out_S01: "<<areaWp2_RB1out_S01<<std::endl;
  std::cout<<"areaWp2_RB1out_S02: "<<areaWp2_RB1out_S02<<std::endl;
  std::cout<<"areaWp2_RB1out_S03: "<<areaWp2_RB1out_S03<<std::endl;
  std::cout<<"areaWp2_RB1out_S04: "<<areaWp2_RB1out_S04<<std::endl;
  std::cout<<"areaWp2_RB1out_S05: "<<areaWp2_RB1out_S05<<std::endl;
  std::cout<<"areaWp2_RB1out_S06: "<<areaWp2_RB1out_S06<<std::endl;
  std::cout<<"areaWp2_RB1out_S07: "<<areaWp2_RB1out_S07<<std::endl;
  std::cout<<"areaWp2_RB1out_S08: "<<areaWp2_RB1out_S08<<std::endl;
  std::cout<<"areaWp2_RB1out_S09: "<<areaWp2_RB1out_S09<<std::endl;
  std::cout<<"areaWp2_RB1out_S10: "<<areaWp2_RB1out_S10<<std::endl;
  std::cout<<"areaWp2_RB1out_S11: "<<areaWp2_RB1out_S11<<std::endl;
  std::cout<<"areaWp2_RB1out_S12: "<<areaWp2_RB1out_S12<<std::endl;

  std::cout<<"areaWm2_RB2in_S01: "<<areaWm2_RB2in_S01<<std::endl;
  std::cout<<"areaWm2_RB2in_S02: "<<areaWm2_RB2in_S02<<std::endl;
  std::cout<<"areaWm2_RB2in_S03: "<<areaWm2_RB2in_S03<<std::endl;
  std::cout<<"areaWm2_RB2in_S04: "<<areaWm2_RB2in_S04<<std::endl;
  std::cout<<"areaWm2_RB2in_S05: "<<areaWm2_RB2in_S05<<std::endl;
  std::cout<<"areaWm2_RB2in_S06: "<<areaWm2_RB2in_S06<<std::endl;
  std::cout<<"areaWm2_RB2in_S07: "<<areaWm2_RB2in_S07<<std::endl;
  std::cout<<"areaWm2_RB2in_S08: "<<areaWm2_RB2in_S08<<std::endl;
  std::cout<<"areaWm2_RB2in_S09: "<<areaWm2_RB2in_S09<<std::endl;
  std::cout<<"areaWm2_RB2in_S10: "<<areaWm2_RB2in_S10<<std::endl;
  std::cout<<"areaWm2_RB2in_S11: "<<areaWm2_RB2in_S11<<std::endl;
  std::cout<<"areaWm2_RB2in_S12: "<<areaWm2_RB2in_S12<<std::endl;

  std::cout<<"areaWm1_RB2in_S01: "<<areaWm1_RB2in_S01<<std::endl;
  std::cout<<"areaWm1_RB2in_S02: "<<areaWm1_RB2in_S02<<std::endl;
  std::cout<<"areaWm1_RB2in_S03: "<<areaWm1_RB2in_S03<<std::endl;
  std::cout<<"areaWm1_RB2in_S04: "<<areaWm1_RB2in_S04<<std::endl;
  std::cout<<"areaWm1_RB2in_S05: "<<areaWm1_RB2in_S05<<std::endl;
  std::cout<<"areaWm1_RB2in_S06: "<<areaWm1_RB2in_S06<<std::endl;
  std::cout<<"areaWm1_RB2in_S07: "<<areaWm1_RB2in_S07<<std::endl;
  std::cout<<"areaWm1_RB2in_S08: "<<areaWm1_RB2in_S08<<std::endl;
  std::cout<<"areaWm1_RB2in_S09: "<<areaWm1_RB2in_S09<<std::endl;
  std::cout<<"areaWm1_RB2in_S10: "<<areaWm1_RB2in_S10<<std::endl;
  std::cout<<"areaWm1_RB2in_S11: "<<areaWm1_RB2in_S11<<std::endl;
  std::cout<<"areaWm1_RB2in_S12: "<<areaWm1_RB2in_S12<<std::endl;

  std::cout<<"areaW0_RB2in_S01: "<<areaW0_RB2in_S01<<std::endl;
  std::cout<<"areaW0_RB2in_S02: "<<areaW0_RB2in_S02<<std::endl;
  std::cout<<"areaW0_RB2in_S03: "<<areaW0_RB2in_S03<<std::endl;
  std::cout<<"areaW0_RB2in_S04: "<<areaW0_RB2in_S04<<std::endl;
  std::cout<<"areaW0_RB2in_S05: "<<areaW0_RB2in_S05<<std::endl;
  std::cout<<"areaW0_RB2in_S06: "<<areaW0_RB2in_S06<<std::endl;
  std::cout<<"areaW0_RB2in_S07: "<<areaW0_RB2in_S07<<std::endl;
  std::cout<<"areaW0_RB2in_S08: "<<areaW0_RB2in_S08<<std::endl;
  std::cout<<"areaW0_RB2in_S09: "<<areaW0_RB2in_S09<<std::endl;
  std::cout<<"areaW0_RB2in_S10: "<<areaW0_RB2in_S10<<std::endl;
  std::cout<<"areaW0_RB2in_S11: "<<areaW0_RB2in_S11<<std::endl;
  std::cout<<"areaW0_RB2in_S12: "<<areaW0_RB2in_S12<<std::endl;

  std::cout<<"areaWp1_RB2in_S01: "<<areaWp1_RB2in_S01<<std::endl;
  std::cout<<"areaWp1_RB2in_S02: "<<areaWp1_RB2in_S02<<std::endl;
  std::cout<<"areaWp1_RB2in_S03: "<<areaWp1_RB2in_S03<<std::endl;
  std::cout<<"areaWp1_RB2in_S04: "<<areaWp1_RB2in_S04<<std::endl;
  std::cout<<"areaWp1_RB2in_S05: "<<areaWp1_RB2in_S05<<std::endl;
  std::cout<<"areaWp1_RB2in_S06: "<<areaWp1_RB2in_S06<<std::endl;
  std::cout<<"areaWp1_RB2in_S07: "<<areaWp1_RB2in_S07<<std::endl;
  std::cout<<"areaWp1_RB2in_S08: "<<areaWp1_RB2in_S08<<std::endl;
  std::cout<<"areaWp1_RB2in_S09: "<<areaWp1_RB2in_S09<<std::endl;
  std::cout<<"areaWp1_RB2in_S10: "<<areaWp1_RB2in_S10<<std::endl;
  std::cout<<"areaWp1_RB2in_S11: "<<areaWp1_RB2in_S11<<std::endl;
  std::cout<<"areaWp1_RB2in_S12: "<<areaWp1_RB2in_S12<<std::endl;

  std::cout<<"areaWp2_RB2in_S01: "<<areaWp2_RB2in_S01<<std::endl;
  std::cout<<"areaWp2_RB2in_S02: "<<areaWp2_RB2in_S02<<std::endl;
  std::cout<<"areaWp2_RB2in_S03: "<<areaWp2_RB2in_S03<<std::endl;
  std::cout<<"areaWp2_RB2in_S04: "<<areaWp2_RB2in_S04<<std::endl;
  std::cout<<"areaWp2_RB2in_S05: "<<areaWp2_RB2in_S05<<std::endl;
  std::cout<<"areaWp2_RB2in_S06: "<<areaWp2_RB2in_S06<<std::endl;
  std::cout<<"areaWp2_RB2in_S07: "<<areaWp2_RB2in_S07<<std::endl;
  std::cout<<"areaWp2_RB2in_S08: "<<areaWp2_RB2in_S08<<std::endl;
  std::cout<<"areaWp2_RB2in_S09: "<<areaWp2_RB2in_S09<<std::endl;
  std::cout<<"areaWp2_RB2in_S10: "<<areaWp2_RB2in_S10<<std::endl;
  std::cout<<"areaWp2_RB2in_S11: "<<areaWp2_RB2in_S11<<std::endl;
  std::cout<<"areaWp2_RB2in_S12: "<<areaWp2_RB2in_S12<<std::endl;

  std::cout<<"areaWm2_RB2out_S01: "<<areaWm2_RB2out_S01<<std::endl;
  std::cout<<"areaWm2_RB2out_S02: "<<areaWm2_RB2out_S02<<std::endl;
  std::cout<<"areaWm2_RB2out_S03: "<<areaWm2_RB2out_S03<<std::endl;
  std::cout<<"areaWm2_RB2out_S04: "<<areaWm2_RB2out_S04<<std::endl;
  std::cout<<"areaWm2_RB2out_S05: "<<areaWm2_RB2out_S05<<std::endl;
  std::cout<<"areaWm2_RB2out_S06: "<<areaWm2_RB2out_S06<<std::endl;
  std::cout<<"areaWm2_RB2out_S07: "<<areaWm2_RB2out_S07<<std::endl;
  std::cout<<"areaWm2_RB2out_S08: "<<areaWm2_RB2out_S08<<std::endl;
  std::cout<<"areaWm2_RB2out_S09: "<<areaWm2_RB2out_S09<<std::endl;
  std::cout<<"areaWm2_RB2out_S10: "<<areaWm2_RB2out_S10<<std::endl;
  std::cout<<"areaWm2_RB2out_S11: "<<areaWm2_RB2out_S11<<std::endl;
  std::cout<<"areaWm2_RB2out_S12: "<<areaWm2_RB2out_S12<<std::endl;

  std::cout<<"areaWm1_RB2out_S01: "<<areaWm1_RB2out_S01<<std::endl;
  std::cout<<"areaWm1_RB2out_S02: "<<areaWm1_RB2out_S02<<std::endl;
  std::cout<<"areaWm1_RB2out_S03: "<<areaWm1_RB2out_S03<<std::endl;
  std::cout<<"areaWm1_RB2out_S04: "<<areaWm1_RB2out_S04<<std::endl;
  std::cout<<"areaWm1_RB2out_S05: "<<areaWm1_RB2out_S05<<std::endl;
  std::cout<<"areaWm1_RB2out_S06: "<<areaWm1_RB2out_S06<<std::endl;
  std::cout<<"areaWm1_RB2out_S07: "<<areaWm1_RB2out_S07<<std::endl;
  std::cout<<"areaWm1_RB2out_S08: "<<areaWm1_RB2out_S08<<std::endl;
  std::cout<<"areaWm1_RB2out_S09: "<<areaWm1_RB2out_S09<<std::endl;
  std::cout<<"areaWm1_RB2out_S10: "<<areaWm1_RB2out_S10<<std::endl;
  std::cout<<"areaWm1_RB2out_S11: "<<areaWm1_RB2out_S11<<std::endl;
  std::cout<<"areaWm1_RB2out_S12: "<<areaWm1_RB2out_S12<<std::endl;

  std::cout<<"areaW0_RB2out_S01: "<<areaW0_RB2out_S01<<std::endl;
  std::cout<<"areaW0_RB2out_S02: "<<areaW0_RB2out_S02<<std::endl;
  std::cout<<"areaW0_RB2out_S03: "<<areaW0_RB2out_S03<<std::endl;
  std::cout<<"areaW0_RB2out_S04: "<<areaW0_RB2out_S04<<std::endl;
  std::cout<<"areaW0_RB2out_S05: "<<areaW0_RB2out_S05<<std::endl;
  std::cout<<"areaW0_RB2out_S06: "<<areaW0_RB2out_S06<<std::endl;
  std::cout<<"areaW0_RB2out_S07: "<<areaW0_RB2out_S07<<std::endl;
  std::cout<<"areaW0_RB2out_S08: "<<areaW0_RB2out_S08<<std::endl;
  std::cout<<"areaW0_RB2out_S09: "<<areaW0_RB2out_S09<<std::endl;
  std::cout<<"areaW0_RB2out_S10: "<<areaW0_RB2out_S10<<std::endl;
  std::cout<<"areaW0_RB2out_S11: "<<areaW0_RB2out_S11<<std::endl;
  std::cout<<"areaW0_RB2out_S12: "<<areaW0_RB2out_S12<<std::endl;

  std::cout<<"areaWp1_RB2out_S01: "<<areaWp1_RB2out_S01<<std::endl;
  std::cout<<"areaWp1_RB2out_S02: "<<areaWp1_RB2out_S02<<std::endl;
  std::cout<<"areaWp1_RB2out_S03: "<<areaWp1_RB2out_S03<<std::endl;
  std::cout<<"areaWp1_RB2out_S04: "<<areaWp1_RB2out_S04<<std::endl;
  std::cout<<"areaWp1_RB2out_S05: "<<areaWp1_RB2out_S05<<std::endl;
  std::cout<<"areaWp1_RB2out_S06: "<<areaWp1_RB2out_S06<<std::endl;
  std::cout<<"areaWp1_RB2out_S07: "<<areaWp1_RB2out_S07<<std::endl;
  std::cout<<"areaWp1_RB2out_S08: "<<areaWp1_RB2out_S08<<std::endl;
  std::cout<<"areaWp1_RB2out_S09: "<<areaWp1_RB2out_S09<<std::endl;
  std::cout<<"areaWp1_RB2out_S10: "<<areaWp1_RB2out_S10<<std::endl;
  std::cout<<"areaWp1_RB2out_S11: "<<areaWp1_RB2out_S11<<std::endl;
  std::cout<<"areaWp1_RB2out_S12: "<<areaWp1_RB2out_S12<<std::endl;

  std::cout<<"areaWp2_RB2out_S01: "<<areaWp2_RB2out_S01<<std::endl;
  std::cout<<"areaWp2_RB2out_S02: "<<areaWp2_RB2out_S02<<std::endl;
  std::cout<<"areaWp2_RB2out_S03: "<<areaWp2_RB2out_S03<<std::endl;
  std::cout<<"areaWp2_RB2out_S04: "<<areaWp2_RB2out_S04<<std::endl;
  std::cout<<"areaWp2_RB2out_S05: "<<areaWp2_RB2out_S05<<std::endl;
  std::cout<<"areaWp2_RB2out_S06: "<<areaWp2_RB2out_S06<<std::endl;
  std::cout<<"areaWp2_RB2out_S07: "<<areaWp2_RB2out_S07<<std::endl;
  std::cout<<"areaWp2_RB2out_S08: "<<areaWp2_RB2out_S08<<std::endl;
  std::cout<<"areaWp2_RB2out_S09: "<<areaWp2_RB2out_S09<<std::endl;
  std::cout<<"areaWp2_RB2out_S10: "<<areaWp2_RB2out_S10<<std::endl;
  std::cout<<"areaWp2_RB2out_S11: "<<areaWp2_RB2out_S11<<std::endl;
  std::cout<<"areaWp2_RB2out_S12: "<<areaWp2_RB2out_S12<<std::endl;


  std::cout<<"areaWm2_RB3_S01: "<<areaWm2_RB3_S01<<std::endl;
  std::cout<<"areaWm2_RB3_S02: "<<areaWm2_RB3_S02<<std::endl;
  std::cout<<"areaWm2_RB3_S03: "<<areaWm2_RB3_S03<<std::endl;
  std::cout<<"areaWm2_RB3_S04: "<<areaWm2_RB3_S04<<std::endl;
  std::cout<<"areaWm2_RB3_S05: "<<areaWm2_RB3_S05<<std::endl;
  std::cout<<"areaWm2_RB3_S06: "<<areaWm2_RB3_S06<<std::endl;
  std::cout<<"areaWm2_RB3_S07: "<<areaWm2_RB3_S07<<std::endl;
  std::cout<<"areaWm2_RB3_S08: "<<areaWm2_RB3_S08<<std::endl;
  std::cout<<"areaWm2_RB3_S09: "<<areaWm2_RB3_S09<<std::endl;
  std::cout<<"areaWm2_RB3_S10: "<<areaWm2_RB3_S10<<std::endl;
  std::cout<<"areaWm2_RB3_S11: "<<areaWm2_RB3_S11<<std::endl;
  std::cout<<"areaWm2_RB3_S12: "<<areaWm2_RB3_S12<<std::endl;
  std::cout<<"areaWm1_RB3_S01: "<<areaWm1_RB3_S01<<std::endl;
  std::cout<<"areaWm1_RB3_S02: "<<areaWm1_RB3_S02<<std::endl;
  std::cout<<"areaWm1_RB3_S03: "<<areaWm1_RB3_S03<<std::endl;
  std::cout<<"areaWm1_RB3_S04: "<<areaWm1_RB3_S04<<std::endl;
  std::cout<<"areaWm1_RB3_S05: "<<areaWm1_RB3_S05<<std::endl;
  std::cout<<"areaWm1_RB3_S06: "<<areaWm1_RB3_S06<<std::endl;
  std::cout<<"areaWm1_RB3_S07: "<<areaWm1_RB3_S07<<std::endl;
  std::cout<<"areaWm1_RB3_S08: "<<areaWm1_RB3_S08<<std::endl;
  std::cout<<"areaWm1_RB3_S09: "<<areaWm1_RB3_S09<<std::endl;
  std::cout<<"areaWm1_RB3_S10: "<<areaWm1_RB3_S10<<std::endl;
  std::cout<<"areaWm1_RB3_S11: "<<areaWm1_RB3_S11<<std::endl;
  std::cout<<"areaWm1_RB3_S12: "<<areaWm1_RB3_S12<<std::endl;

  std::cout<<"areaW0_RB3_S01: "<<areaW0_RB3_S01<<std::endl;
  std::cout<<"areaW0_RB3_S02: "<<areaW0_RB3_S02<<std::endl;
  std::cout<<"areaW0_RB3_S03: "<<areaW0_RB3_S03<<std::endl;
  std::cout<<"areaW0_RB3_S04: "<<areaW0_RB3_S04<<std::endl;
  std::cout<<"areaW0_RB3_S05: "<<areaW0_RB3_S05<<std::endl;
  std::cout<<"areaW0_RB3_S06: "<<areaW0_RB3_S06<<std::endl;
  std::cout<<"areaW0_RB3_S07: "<<areaW0_RB3_S07<<std::endl;
  std::cout<<"areaW0_RB3_S08: "<<areaW0_RB3_S08<<std::endl;
  std::cout<<"areaW0_RB3_S09: "<<areaW0_RB3_S09<<std::endl;
  std::cout<<"areaW0_RB3_S10: "<<areaW0_RB3_S10<<std::endl;
  std::cout<<"areaW0_RB3_S11: "<<areaW0_RB3_S11<<std::endl;
  std::cout<<"areaW0_RB3_S12: "<<areaW0_RB3_S12<<std::endl;
  std::cout<<"areaWp1_RB3_S01: "<<areaWp1_RB3_S01<<std::endl;
  std::cout<<"areaWp1_RB3_S02: "<<areaWp1_RB3_S02<<std::endl;
  std::cout<<"areaWp1_RB3_S03: "<<areaWp1_RB3_S03<<std::endl;
  std::cout<<"areaWp1_RB3_S04: "<<areaWp1_RB3_S04<<std::endl;
  std::cout<<"areaWp1_RB3_S05: "<<areaWp1_RB3_S05<<std::endl;
  std::cout<<"areaWp1_RB3_S06: "<<areaWp1_RB3_S06<<std::endl;
  std::cout<<"areaWp1_RB3_S07: "<<areaWp1_RB3_S07<<std::endl;
  std::cout<<"areaWp1_RB3_S08: "<<areaWp1_RB3_S08<<std::endl;
  std::cout<<"areaWp1_RB3_S09: "<<areaWp1_RB3_S09<<std::endl;
  std::cout<<"areaWp1_RB3_S10: "<<areaWp1_RB3_S10<<std::endl;
  std::cout<<"areaWp1_RB3_S11: "<<areaWp1_RB3_S11<<std::endl;
  std::cout<<"areaWp1_RB3_S12: "<<areaWp1_RB3_S12<<std::endl;
  std::cout<<"areaWp2_RB3_S01: "<<areaWp2_RB3_S01<<std::endl;
  std::cout<<"areaWp2_RB3_S02: "<<areaWp2_RB3_S02<<std::endl;
  std::cout<<"areaWp2_RB3_S03: "<<areaWp2_RB3_S03<<std::endl;
  std::cout<<"areaWp2_RB3_S04: "<<areaWp2_RB3_S04<<std::endl;
  std::cout<<"areaWp2_RB3_S05: "<<areaWp2_RB3_S05<<std::endl;
  std::cout<<"areaWp2_RB3_S06: "<<areaWp2_RB3_S06<<std::endl;
  std::cout<<"areaWp2_RB3_S07: "<<areaWp2_RB3_S07<<std::endl;
  std::cout<<"areaWp2_RB3_S08: "<<areaWp2_RB3_S08<<std::endl;
  std::cout<<"areaWp2_RB3_S09: "<<areaWp2_RB3_S09<<std::endl;
  std::cout<<"areaWp2_RB3_S10: "<<areaWp2_RB3_S10<<std::endl;
  std::cout<<"areaWp2_RB3_S11: "<<areaWp2_RB3_S11<<std::endl;
  std::cout<<"areaWp2_RB3_S12: "<<areaWp2_RB3_S12<<std::endl;
  std::cout<<"areaWm2_RB4_S01: "<<areaWm2_RB4_S01<<std::endl;
  std::cout<<"areaWm2_RB4_S02: "<<areaWm2_RB4_S02<<std::endl;
  std::cout<<"areaWm2_RB4_S03: "<<areaWm2_RB4_S03<<std::endl;
  std::cout<<"areaWm2_RB4_S04: "<<areaWm2_RB4_S04<<std::endl;
  std::cout<<"areaWm2_RB4_S05: "<<areaWm2_RB4_S05<<std::endl;
  std::cout<<"areaWm2_RB4_S06: "<<areaWm2_RB4_S06<<std::endl;
  std::cout<<"areaWm2_RB4_S07: "<<areaWm2_RB4_S07<<std::endl;
  std::cout<<"areaWm2_RB4_S08: "<<areaWm2_RB4_S08<<std::endl;
  std::cout<<"areaWm2_RB4_S09: "<<areaWm2_RB4_S09<<std::endl;
  std::cout<<"areaWm2_RB4_S10: "<<areaWm2_RB4_S10<<std::endl;
  std::cout<<"areaWm2_RB4_S11: "<<areaWm2_RB4_S11<<std::endl;
  std::cout<<"areaWm2_RB4_S12: "<<areaWm2_RB4_S12<<std::endl;
  std::cout<<"areaWm1_RB4_S01: "<<areaWm1_RB4_S01<<std::endl;
  std::cout<<"areaWm1_RB4_S02: "<<areaWm1_RB4_S02<<std::endl;
  std::cout<<"areaWm1_RB4_S03: "<<areaWm1_RB4_S03<<std::endl;
  std::cout<<"areaWm1_RB4_S04: "<<areaWm1_RB4_S04<<std::endl;
  std::cout<<"areaWm1_RB4_S05: "<<areaWm1_RB4_S05<<std::endl;
  std::cout<<"areaWm1_RB4_S06: "<<areaWm1_RB4_S06<<std::endl;
  std::cout<<"areaWm1_RB4_S07: "<<areaWm1_RB4_S07<<std::endl;
  std::cout<<"areaWm1_RB4_S08: "<<areaWm1_RB4_S08<<std::endl;
  std::cout<<"areaWm1_RB4_S09: "<<areaWm1_RB4_S09<<std::endl;
  std::cout<<"areaWm1_RB4_S10: "<<areaWm1_RB4_S10<<std::endl;
  std::cout<<"areaWm1_RB4_S11: "<<areaWm1_RB4_S11<<std::endl;
  std::cout<<"areaWm1_RB4_S12: "<<areaWm1_RB4_S12<<std::endl;
  std::cout<<"areaW0_RB4_S01: "<<areaW0_RB4_S01<<std::endl;
  std::cout<<"areaW0_RB4_S02: "<<areaW0_RB4_S02<<std::endl;
  std::cout<<"areaW0_RB4_S03: "<<areaW0_RB4_S03<<std::endl;
  std::cout<<"areaW0_RB4_S04: "<<areaW0_RB4_S04<<std::endl;
  std::cout<<"areaW0_RB4_S05: "<<areaW0_RB4_S05<<std::endl;
  std::cout<<"areaW0_RB4_S06: "<<areaW0_RB4_S06<<std::endl;
  std::cout<<"areaW0_RB4_S07: "<<areaW0_RB4_S07<<std::endl;
  std::cout<<"areaW0_RB4_S08: "<<areaW0_RB4_S08<<std::endl;
  std::cout<<"areaW0_RB4_S09: "<<areaW0_RB4_S09<<std::endl;
  std::cout<<"areaW0_RB4_S10: "<<areaW0_RB4_S10<<std::endl;
  std::cout<<"areaW0_RB4_S11: "<<areaW0_RB4_S11<<std::endl;
  std::cout<<"areaW0_RB4_S12: "<<areaW0_RB4_S12<<std::endl;
  std::cout<<"areaWp1_RB4_S01: "<<areaWp1_RB4_S01<<std::endl;
  std::cout<<"areaWp1_RB4_S02: "<<areaWp1_RB4_S02<<std::endl;
  std::cout<<"areaWp1_RB4_S03: "<<areaWp1_RB4_S03<<std::endl;
  std::cout<<"areaWp1_RB4_S04: "<<areaWp1_RB4_S04<<std::endl;
  std::cout<<"areaWp1_RB4_S05: "<<areaWp1_RB4_S05<<std::endl;
  std::cout<<"areaWp1_RB4_S06: "<<areaWp1_RB4_S06<<std::endl;
  std::cout<<"areaWp1_RB4_S07: "<<areaWp1_RB4_S07<<std::endl;
  std::cout<<"areaWp1_RB4_S08: "<<areaWp1_RB4_S08<<std::endl;
  std::cout<<"areaWp1_RB4_S09: "<<areaWp1_RB4_S09<<std::endl;
  std::cout<<"areaWp1_RB4_S10: "<<areaWp1_RB4_S10<<std::endl;
  std::cout<<"areaWp1_RB4_S11: "<<areaWp1_RB4_S11<<std::endl;
  std::cout<<"areaWp1_RB4_S12: "<<areaWp1_RB4_S12<<std::endl;
  std::cout<<"areaWp2_RB4_S01: "<<areaWp2_RB4_S01<<std::endl;
  std::cout<<"areaWp2_RB4_S02: "<<areaWp2_RB4_S02<<std::endl;
  std::cout<<"areaWp2_RB4_S03: "<<areaWp2_RB4_S03<<std::endl;
  std::cout<<"areaWp2_RB4_S04: "<<areaWp2_RB4_S04<<std::endl;
  std::cout<<"areaWp2_RB4_S05: "<<areaWp2_RB4_S05<<std::endl;
  std::cout<<"areaWp2_RB4_S06: "<<areaWp2_RB4_S06<<std::endl;
  std::cout<<"areaWp2_RB4_S07: "<<areaWp2_RB4_S07<<std::endl;
  std::cout<<"areaWp2_RB4_S08: "<<areaWp2_RB4_S08<<std::endl;
  std::cout<<"areaWp2_RB4_S09: "<<areaWp2_RB4_S09<<std::endl;
  std::cout<<"areaWp2_RB4_S10: "<<areaWp2_RB4_S10<<std::endl;
  std::cout<<"areaWp2_RB4_S11: "<<areaWp2_RB4_S11<<std::endl;
  std::cout<<"areaWp2_RB4_S12: "<<areaWp2_RB4_S12<<std::endl;



  std::cout<<"areaREp42_S01: "<<areaREp42_S01<<std::endl;
  std::cout<<"areaREp42_S02: "<<areaREp42_S02<<std::endl;
  std::cout<<"areaREp42_S03: "<<areaREp42_S03<<std::endl;
  std::cout<<"areaREp42_S04: "<<areaREp42_S04<<std::endl;
  std::cout<<"areaREp42_S05: "<<areaREp42_S05<<std::endl;
  std::cout<<"areaREp42_S06: "<<areaREp42_S06<<std::endl;
  std::cout<<"areaREp42_S07: "<<areaREp42_S07<<std::endl;
  std::cout<<"areaREp42_S08: "<<areaREp42_S08<<std::endl;
  std::cout<<"areaREp42_S09: "<<areaREp42_S09<<std::endl;
  std::cout<<"areaREp42_S10: "<<areaREp42_S10<<std::endl;
  std::cout<<"areaREp42_S11: "<<areaREp42_S11<<std::endl;
  std::cout<<"areaREp42_S12: "<<areaREp42_S12<<std::endl;
  std::cout<<"areaREp43_S01: "<<areaREp43_S01<<std::endl;
  std::cout<<"areaREp43_S02: "<<areaREp43_S02<<std::endl;
  std::cout<<"areaREp43_S03: "<<areaREp43_S03<<std::endl;
  std::cout<<"areaREp43_S04: "<<areaREp43_S04<<std::endl;
  std::cout<<"areaREp43_S05: "<<areaREp43_S05<<std::endl;
  std::cout<<"areaREp43_S06: "<<areaREp43_S06<<std::endl;
  std::cout<<"areaREp43_S07: "<<areaREp43_S07<<std::endl;
  std::cout<<"areaREp43_S08: "<<areaREp43_S08<<std::endl;
  std::cout<<"areaREp43_S09: "<<areaREp43_S09<<std::endl;
  std::cout<<"areaREp43_S10: "<<areaREp43_S10<<std::endl;
  std::cout<<"areaREp43_S11: "<<areaREp43_S11<<std::endl;
  std::cout<<"areaREp43_S12: "<<areaREp43_S12<<std::endl;

  std::cout<<"areaREp32_S01: "<<areaREp32_S01<<std::endl;
  std::cout<<"areaREp32_S02: "<<areaREp32_S02<<std::endl;
  std::cout<<"areaREp32_S03: "<<areaREp32_S03<<std::endl;
  std::cout<<"areaREp32_S04: "<<areaREp32_S04<<std::endl;
  std::cout<<"areaREp32_S05: "<<areaREp32_S05<<std::endl;
  std::cout<<"areaREp32_S06: "<<areaREp32_S06<<std::endl;
  std::cout<<"areaREp32_S07: "<<areaREp32_S07<<std::endl;
  std::cout<<"areaREp32_S08: "<<areaREp32_S08<<std::endl;
  std::cout<<"areaREp32_S09: "<<areaREp32_S09<<std::endl;
  std::cout<<"areaREp32_S10: "<<areaREp32_S10<<std::endl;
  std::cout<<"areaREp32_S11: "<<areaREp32_S11<<std::endl;
  std::cout<<"areaREp32_S12: "<<areaREp32_S12<<std::endl;
  std::cout<<"areaREp33_S01: "<<areaREp33_S01<<std::endl;
  std::cout<<"areaREp33_S02: "<<areaREp33_S02<<std::endl;
  std::cout<<"areaREp33_S03: "<<areaREp33_S03<<std::endl;
  std::cout<<"areaREp33_S04: "<<areaREp33_S04<<std::endl;
  std::cout<<"areaREp33_S05: "<<areaREp33_S05<<std::endl;
  std::cout<<"areaREp33_S06: "<<areaREp33_S06<<std::endl;
  std::cout<<"areaREp33_S07: "<<areaREp33_S07<<std::endl;
  std::cout<<"areaREp33_S08: "<<areaREp33_S08<<std::endl;
  std::cout<<"areaREp33_S09: "<<areaREp33_S09<<std::endl;
  std::cout<<"areaREp33_S10: "<<areaREp33_S10<<std::endl;
  std::cout<<"areaREp33_S11: "<<areaREp33_S11<<std::endl;
  std::cout<<"areaREp33_S12: "<<areaREp33_S12<<std::endl;

  std::cout<<"areaREp22_S01: "<<areaREp22_S01<<std::endl;
  std::cout<<"areaREp22_S02: "<<areaREp22_S02<<std::endl;
  std::cout<<"areaREp22_S03: "<<areaREp22_S03<<std::endl;
  std::cout<<"areaREp22_S04: "<<areaREp22_S04<<std::endl;
  std::cout<<"areaREp22_S05: "<<areaREp22_S05<<std::endl;
  std::cout<<"areaREp22_S06: "<<areaREp22_S06<<std::endl;
  std::cout<<"areaREp22_S07: "<<areaREp22_S07<<std::endl;
  std::cout<<"areaREp22_S08: "<<areaREp22_S08<<std::endl;
  std::cout<<"areaREp22_S09: "<<areaREp22_S09<<std::endl;
  std::cout<<"areaREp22_S10: "<<areaREp22_S10<<std::endl;
  std::cout<<"areaREp22_S11: "<<areaREp22_S11<<std::endl;
  std::cout<<"areaREp22_S12: "<<areaREp22_S12<<std::endl;
  std::cout<<"areaREp23_S01: "<<areaREp23_S01<<std::endl;
  std::cout<<"areaREp23_S02: "<<areaREp23_S02<<std::endl;
  std::cout<<"areaREp23_S03: "<<areaREp23_S03<<std::endl;
  std::cout<<"areaREp23_S04: "<<areaREp23_S04<<std::endl;
  std::cout<<"areaREp23_S05: "<<areaREp23_S05<<std::endl;
  std::cout<<"areaREp23_S06: "<<areaREp23_S06<<std::endl;
  std::cout<<"areaREp23_S07: "<<areaREp23_S07<<std::endl;
  std::cout<<"areaREp23_S08: "<<areaREp23_S08<<std::endl;
  std::cout<<"areaREp23_S09: "<<areaREp23_S09<<std::endl;
  std::cout<<"areaREp23_S10: "<<areaREp23_S10<<std::endl;
  std::cout<<"areaREp23_S11: "<<areaREp23_S11<<std::endl;
  std::cout<<"areaREp23_S12: "<<areaREp23_S12<<std::endl;   
  
  std::cout<<"areaREp12_S01: "<<areaREp12_S01<<std::endl;
  std::cout<<"areaREp12_S02: "<<areaREp12_S02<<std::endl;
  std::cout<<"areaREp12_S03: "<<areaREp12_S03<<std::endl;
  std::cout<<"areaREp12_S04: "<<areaREp12_S04<<std::endl;
  std::cout<<"areaREp12_S05: "<<areaREp12_S05<<std::endl;
  std::cout<<"areaREp12_S06: "<<areaREp12_S06<<std::endl;
  std::cout<<"areaREp12_S07: "<<areaREp12_S07<<std::endl;
  std::cout<<"areaREp12_S08: "<<areaREp12_S08<<std::endl;
  std::cout<<"areaREp12_S09: "<<areaREp12_S09<<std::endl;
  std::cout<<"areaREp12_S10: "<<areaREp12_S10<<std::endl;
  std::cout<<"areaREp12_S11: "<<areaREp12_S11<<std::endl;
  std::cout<<"areaREp12_S12: "<<areaREp12_S12<<std::endl;
  std::cout<<"areaREp13_S01: "<<areaREp13_S01<<std::endl;
  std::cout<<"areaREp13_S02: "<<areaREp13_S02<<std::endl;
  std::cout<<"areaREp13_S03: "<<areaREp13_S03<<std::endl;
  std::cout<<"areaREp13_S04: "<<areaREp13_S04<<std::endl;
  std::cout<<"areaREp13_S05: "<<areaREp13_S05<<std::endl;
  std::cout<<"areaREp13_S06: "<<areaREp13_S06<<std::endl;
  std::cout<<"areaREp13_S07: "<<areaREp13_S07<<std::endl;
  std::cout<<"areaREp13_S08: "<<areaREp13_S08<<std::endl;
  std::cout<<"areaREp13_S09: "<<areaREp13_S09<<std::endl;
  std::cout<<"areaREp13_S10: "<<areaREp13_S10<<std::endl;
  std::cout<<"areaREp13_S11: "<<areaREp13_S11<<std::endl;
  std::cout<<"areaREp13_S12: "<<areaREp13_S12<<std::endl;


  std::cout<<"areaREm42_S01: "<<areaREm42_S01<<std::endl;
  std::cout<<"areaREm42_S02: "<<areaREm42_S02<<std::endl;
  std::cout<<"areaREm42_S03: "<<areaREm42_S03<<std::endl;
  std::cout<<"areaREm42_S04: "<<areaREm42_S04<<std::endl;
  std::cout<<"areaREm42_S05: "<<areaREm42_S05<<std::endl;
  std::cout<<"areaREm42_S06: "<<areaREm42_S06<<std::endl;
  std::cout<<"areaREm42_S07: "<<areaREm42_S07<<std::endl;
  std::cout<<"areaREm42_S08: "<<areaREm42_S08<<std::endl;
  std::cout<<"areaREm42_S09: "<<areaREm42_S09<<std::endl;
  std::cout<<"areaREm42_S10: "<<areaREm42_S10<<std::endl;
  std::cout<<"areaREm42_S11: "<<areaREm42_S11<<std::endl;
  std::cout<<"areaREm42_S12: "<<areaREm42_S12<<std::endl;
  std::cout<<"areaREm43_S01: "<<areaREm43_S01<<std::endl;
  std::cout<<"areaREm43_S02: "<<areaREm43_S02<<std::endl;
  std::cout<<"areaREm43_S03: "<<areaREm43_S03<<std::endl;
  std::cout<<"areaREm43_S04: "<<areaREm43_S04<<std::endl;
  std::cout<<"areaREm43_S05: "<<areaREm43_S05<<std::endl;
  std::cout<<"areaREm43_S06: "<<areaREm43_S06<<std::endl;
  std::cout<<"areaREm43_S07: "<<areaREm43_S07<<std::endl;
  std::cout<<"areaREm43_S08: "<<areaREm43_S08<<std::endl;
  std::cout<<"areaREm43_S09: "<<areaREm43_S09<<std::endl;
  std::cout<<"areaREm43_S10: "<<areaREm43_S10<<std::endl;
  std::cout<<"areaREm43_S11: "<<areaREm43_S11<<std::endl;
  std::cout<<"areaREm43_S12: "<<areaREm43_S12<<std::endl;
  std::cout<<"areaREm12_S01: "<<areaREm12_S01<<std::endl;
  std::cout<<"areaREm12_S02: "<<areaREm12_S02<<std::endl;
  std::cout<<"areaREm12_S03: "<<areaREm12_S03<<std::endl;
  std::cout<<"areaREm12_S04: "<<areaREm12_S04<<std::endl;
  std::cout<<"areaREm12_S05: "<<areaREm12_S05<<std::endl;
  std::cout<<"areaREm12_S06: "<<areaREm12_S06<<std::endl;
  std::cout<<"areaREm12_S07: "<<areaREm12_S07<<std::endl;
  std::cout<<"areaREm12_S08: "<<areaREm12_S08<<std::endl;
  std::cout<<"areaREm12_S09: "<<areaREm12_S09<<std::endl;
  std::cout<<"areaREm12_S10: "<<areaREm12_S10<<std::endl;
  std::cout<<"areaREm12_S11: "<<areaREm12_S11<<std::endl;
  std::cout<<"areaREm12_S12: "<<areaREm12_S12<<std::endl;
  std::cout<<"areaREm13_S01: "<<areaREm13_S01<<std::endl;
  std::cout<<"areaREm13_S02: "<<areaREm13_S02<<std::endl;
  std::cout<<"areaREm13_S03: "<<areaREm13_S03<<std::endl;
  std::cout<<"areaREm13_S04: "<<areaREm13_S04<<std::endl;
  std::cout<<"areaREm13_S05: "<<areaREm13_S05<<std::endl;
  std::cout<<"areaREm13_S06: "<<areaREm13_S06<<std::endl;
  std::cout<<"areaREm13_S07: "<<areaREm13_S07<<std::endl;
  std::cout<<"areaREm13_S08: "<<areaREm13_S08<<std::endl;
  std::cout<<"areaREm13_S09: "<<areaREm13_S09<<std::endl;
  std::cout<<"areaREm13_S10: "<<areaREm13_S10<<std::endl;
  std::cout<<"areaREm13_S11: "<<areaREm13_S11<<std::endl;
  std::cout<<"areaREm13_S12: "<<areaREm13_S12<<std::endl;

  std::cout<<"areaREm32_S01: "<<areaREm32_S01<<std::endl;
  std::cout<<"areaREm32_S02: "<<areaREm32_S02<<std::endl;
  std::cout<<"areaREm32_S03: "<<areaREm32_S03<<std::endl;
  std::cout<<"areaREm32_S04: "<<areaREm32_S04<<std::endl;
  std::cout<<"areaREm32_S05: "<<areaREm32_S05<<std::endl;
  std::cout<<"areaREm32_S06: "<<areaREm32_S06<<std::endl;
  std::cout<<"areaREm32_S07: "<<areaREm32_S07<<std::endl;
  std::cout<<"areaREm32_S08: "<<areaREm32_S08<<std::endl;
  std::cout<<"areaREm32_S09: "<<areaREm32_S09<<std::endl;
  std::cout<<"areaREm32_S10: "<<areaREm32_S10<<std::endl;
  std::cout<<"areaREm32_S11: "<<areaREm32_S11<<std::endl;
  std::cout<<"areaREm32_S12: "<<areaREm32_S12<<std::endl;
  std::cout<<"areaREm33_S01: "<<areaREm33_S01<<std::endl;
  std::cout<<"areaREm33_S02: "<<areaREm33_S02<<std::endl;
  std::cout<<"areaREm33_S03: "<<areaREm33_S03<<std::endl;
  std::cout<<"areaREm33_S04: "<<areaREm33_S04<<std::endl;
  std::cout<<"areaREm33_S05: "<<areaREm33_S05<<std::endl;
  std::cout<<"areaREm33_S06: "<<areaREm33_S06<<std::endl;
  std::cout<<"areaREm33_S07: "<<areaREm33_S07<<std::endl;
  std::cout<<"areaREm33_S08: "<<areaREm33_S08<<std::endl;
  std::cout<<"areaREm33_S09: "<<areaREm33_S09<<std::endl;
  std::cout<<"areaREm33_S10: "<<areaREm33_S10<<std::endl;
  std::cout<<"areaREm33_S11: "<<areaREm33_S11<<std::endl;
  std::cout<<"areaREm33_S12: "<<areaREm33_S12<<std::endl;

  std::cout<<"areaREm22_S01: "<<areaREm22_S01<<std::endl;
  std::cout<<"areaREm22_S02: "<<areaREm22_S02<<std::endl;
  std::cout<<"areaREm22_S03: "<<areaREm22_S03<<std::endl;
  std::cout<<"areaREm22_S04: "<<areaREm22_S04<<std::endl;
  std::cout<<"areaREm22_S05: "<<areaREm22_S05<<std::endl;
  std::cout<<"areaREm22_S06: "<<areaREm22_S06<<std::endl;
  std::cout<<"areaREm22_S07: "<<areaREm22_S07<<std::endl;
  std::cout<<"areaREm22_S08: "<<areaREm22_S08<<std::endl;
  std::cout<<"areaREm22_S09: "<<areaREm22_S09<<std::endl;
  std::cout<<"areaREm22_S10: "<<areaREm22_S10<<std::endl;
  std::cout<<"areaREm22_S11: "<<areaREm22_S11<<std::endl;
  std::cout<<"areaREm22_S12: "<<areaREm22_S12<<std::endl;
  std::cout<<"areaREm23_S01: "<<areaREm23_S01<<std::endl;
  std::cout<<"areaREm23_S02: "<<areaREm23_S02<<std::endl;
  std::cout<<"areaREm23_S03: "<<areaREm23_S03<<std::endl;
  std::cout<<"areaREm23_S04: "<<areaREm23_S04<<std::endl;
  std::cout<<"areaREm23_S05: "<<areaREm23_S05<<std::endl;
  std::cout<<"areaREm23_S06: "<<areaREm23_S06<<std::endl;
  std::cout<<"areaREm23_S07: "<<areaREm23_S07<<std::endl;
  std::cout<<"areaREm23_S08: "<<areaREm23_S08<<std::endl;
  std::cout<<"areaREm23_S09: "<<areaREm23_S09<<std::endl;
  std::cout<<"areaREm23_S10: "<<areaREm23_S10<<std::endl;
  std::cout<<"areaREm23_S11: "<<areaREm23_S11<<std::endl;
  std::cout<<"areaREm23_S12: "<<areaREm23_S12<<std::endl;  

  std::cout<<"areaWp2_RB1out_B: "<<areaWp2_RB1out_B<<std::endl;
  std::cout<<"areaWp1_RB1out_B: "<<areaWp1_RB1out_B<<std::endl;
  std::cout<<"areaW0_RB1out_B: "<<areaW0_RB1out_B<<std::endl;
  std::cout<<"areaWm1_RB1out_B: "<<areaWm1_RB1out_B<<std::endl;
  std::cout<<"areaWm2_RB1out_B: "<<areaWm2_RB1out_B<<std::endl;
  std::cout<<"areaWp2_RB1out_F: "<<areaWp2_RB1out_F<<std::endl;
  std::cout<<"areaWp1_RB1out_F: "<<areaWp1_RB1out_F<<std::endl;
  std::cout<<"areaW0_RB1out_F: "<<areaW0_RB1out_F<<std::endl;
  std::cout<<"areaWm1_RB1out_F: "<<areaWm1_RB1out_F<<std::endl;
  std::cout<<"areaWm2_RB1out_F: "<<areaWm2_RB1out_F<<std::endl;
  std::cout<<"areaWp2_RB1in_B: "<<areaWp2_RB1in_B<<std::endl;
  std::cout<<"areaWp1_RB1in_B: "<<areaWp1_RB1in_B<<std::endl;
  std::cout<<"areaW0_RB1in_B: "<<areaW0_RB1in_B<<std::endl;
  std::cout<<"areaWm1_RB1in_B: "<<areaWm1_RB1in_B<<std::endl;
  std::cout<<"areaWm2_RB1in_B: "<<areaWm2_RB1in_B<<std::endl;
  std::cout<<"areaWp2_RB1in_F: "<<areaWp2_RB1in_F<<std::endl;
  std::cout<<"areaWp1_RB1in_F: "<<areaWp1_RB1in_F<<std::endl;
  std::cout<<"areaW0_RB1in_F: "<<areaW0_RB1in_F<<std::endl;
  std::cout<<"areaWm1_RB1in_F: "<<areaWm1_RB1in_F<<std::endl;
  std::cout<<"areaWm2_RB1in_F: "<<areaWm2_RB1in_F<<std::endl;
  std::cout<<"areaWp2_RB3_B: "<<areaWp2_RB3_B<<std::endl;
  std::cout<<"areaWp1_RB3_B: "<<areaWp1_RB3_B<<std::endl;
  std::cout<<"areaW0_RB3_B: "<<areaW0_RB3_B<<std::endl;
  std::cout<<"areaWm1_RB3_B: "<<areaWm1_RB3_B<<std::endl;
  std::cout<<"areaWm2_RB3_B: "<<areaWm2_RB3_B<<std::endl;
  std::cout<<"areaWp2_RB3_F: "<<areaWp2_RB3_F<<std::endl;
  std::cout<<"areaWp1_RB3_F: "<<areaWp1_RB3_F<<std::endl;
  std::cout<<"areaW0_RB3_F: "<<areaW0_RB3_F<<std::endl;
  std::cout<<"areaWm1_RB3_F: "<<areaWm1_RB3_F<<std::endl;
  std::cout<<"areaWm2_RB3_F: "<<areaWm2_RB3_F<<std::endl;
  std::cout<<"areaWp2_RB4_B: "<<areaWp2_RB4_B<<std::endl;
  std::cout<<"areaWp1_RB4_B: "<<areaWp1_RB4_B<<std::endl;
  std::cout<<"areaW0_RB4_B: "<<areaW0_RB4_B<<std::endl;
  std::cout<<"areaWm1_RB4_B: "<<areaWm1_RB4_B<<std::endl;
  std::cout<<"areaWm2_RB4_B: "<<areaWm2_RB4_B<<std::endl;
  std::cout<<"areaWp2_RB4_F: "<<areaWp2_RB4_F<<std::endl;
  std::cout<<"areaWp1_RB4_F: "<<areaWp1_RB4_F<<std::endl;
  std::cout<<"areaW0_RB4_F: "<<areaW0_RB4_F<<std::endl;
  std::cout<<"areaWm1_RB4_F: "<<areaWm1_RB4_F<<std::endl;
  std::cout<<"areaWm2_RB4_F: "<<areaWm2_RB4_F<<std::endl;
  std::cout<<"areaWp2_RB2out_B: "<<areaWp2_RB2out_B<<std::endl;
  std::cout<<"areaWp1_RB2out_B: "<<areaWp1_RB2out_B<<std::endl;
  std::cout<<"areaW0_RB2out_B: "<<areaW0_RB2out_B<<std::endl;
  std::cout<<"areaWm1_RB2out_B: "<<areaWm1_RB2out_B<<std::endl;
  std::cout<<"areaWm2_RB2out_B: "<<areaWm2_RB2out_B<<std::endl;
  std::cout<<"areaWp2_RB2out_F: "<<areaWp2_RB2out_F<<std::endl;
  std::cout<<"areaWp1_RB2out_F: "<<areaWp1_RB2out_F<<std::endl;
  std::cout<<"areaW0_RB2out_F: "<<areaW0_RB2out_F<<std::endl;
  std::cout<<"areaWm1_RB2out_F: "<<areaWm1_RB2out_F<<std::endl;
  std::cout<<"areaWm2_RB2out_F: "<<areaWm2_RB2out_F<<std::endl;
  std::cout<<"areaWp2_RB2out_M: "<<areaWp2_RB2out_M<<std::endl;
  std::cout<<"areaWm2_RB2out_M: "<<areaWm2_RB2out_M<<std::endl;
  std::cout<<"areaWp2_RB2in_B: "<<areaWp2_RB2in_B<<std::endl;
  std::cout<<"areaWp1_RB2in_B: "<<areaWp1_RB2in_B<<std::endl;
  std::cout<<"areaW0_RB2in_B: "<<areaW0_RB2in_B<<std::endl;
  std::cout<<"areaWm1_RB2in_B: "<<areaWm1_RB2in_B<<std::endl;
  std::cout<<"areaWm2_RB2in_B: "<<areaWm2_RB2in_B<<std::endl;
  std::cout<<"areaWp2_RB2in_F: "<<areaWp2_RB2in_F<<std::endl;
  std::cout<<"areaWp1_RB2in_F: "<<areaWp1_RB2in_F<<std::endl;
  std::cout<<"areaW0_RB2in_F: "<<areaW0_RB2in_F<<std::endl;
  std::cout<<"areaWm1_RB2in_F: "<<areaWm1_RB2in_F<<std::endl;
  std::cout<<"areaWm2_RB2in_F: "<<areaWm2_RB2in_F<<std::endl;
  std::cout<<"areaWp1_RB2in_M: "<<areaWp1_RB2in_M<<std::endl;
  std::cout<<"areaW0_RB2in_M: "<<areaW0_RB2in_M<<std::endl;
  std::cout<<"areaWm1_RB2in_M: "<<areaWm1_RB2in_M<<std::endl;

  std::cout<<"areaREp12_B: "<<areaREp12_B<<std::endl;
  std::cout<<"areaREp12_M: "<<areaREp12_M<<std::endl;
  std::cout<<"areaREp12_F: "<<areaREp12_F<<std::endl;
  std::cout<<"areaREp13_B: "<<areaREp13_B<<std::endl;
  std::cout<<"areaREp13_M: "<<areaREp13_M<<std::endl;
  std::cout<<"areaREp13_F: "<<areaREp13_F<<std::endl;

  std::cout<<"areaREp22_B: "<<areaREp22_B<<std::endl;
  std::cout<<"areaREp22_M: "<<areaREp22_M<<std::endl;
  std::cout<<"areaREp22_F: "<<areaREp22_F<<std::endl;
  std::cout<<"areaREp23_B: "<<areaREp23_B<<std::endl;
  std::cout<<"areaREp23_M: "<<areaREp23_M<<std::endl;
  std::cout<<"areaREp23_F: "<<areaREp23_F<<std::endl;

  std::cout<<"areaREp32_B: "<<areaREp32_B<<std::endl;
  std::cout<<"areaREp32_M: "<<areaREp32_M<<std::endl;
  std::cout<<"areaREp32_F: "<<areaREp32_F<<std::endl;
  std::cout<<"areaREp33_B: "<<areaREp33_B<<std::endl;
  std::cout<<"areaREp33_M: "<<areaREp33_M<<std::endl;
  std::cout<<"areaREp33_F: "<<areaREp33_F<<std::endl;  

  std::cout<<"areaREp42_B: "<<areaREp42_B<<std::endl;
  std::cout<<"areaREp42_M: "<<areaREp42_M<<std::endl;
  std::cout<<"areaREp42_F: "<<areaREp42_F<<std::endl;
  std::cout<<"areaREp43_B: "<<areaREp43_B<<std::endl;
  std::cout<<"areaREp43_M: "<<areaREp43_M<<std::endl;
  std::cout<<"areaREp43_F: "<<areaREp43_F<<std::endl;


  std::cout<<"areaREm12_B: "<<areaREm12_B<<std::endl;
  std::cout<<"areaREm12_M: "<<areaREm12_M<<std::endl;
  std::cout<<"areaREm12_F: "<<areaREm12_F<<std::endl;
  std::cout<<"areaREm13_B: "<<areaREm13_B<<std::endl;
  std::cout<<"areaREm13_M: "<<areaREm13_M<<std::endl;
  std::cout<<"areaREm13_F: "<<areaREm13_F<<std::endl;
  std::cout<<"areaREm42_B: "<<areaREm42_B<<std::endl;
  std::cout<<"areaREm42_M: "<<areaREm42_M<<std::endl;
  std::cout<<"areaREm42_F: "<<areaREm42_F<<std::endl;
  std::cout<<"areaREm43_B: "<<areaREm43_B<<std::endl;
  std::cout<<"areaREm43_M: "<<areaREm43_M<<std::endl;
  std::cout<<"areaREm43_F: "<<areaREm43_F<<std::endl;

  std::cout<<"areaREm22_B: "<<areaREm22_B<<std::endl;
  std::cout<<"areaREm22_M: "<<areaREm22_M<<std::endl;
  std::cout<<"areaREm22_F: "<<areaREm22_F<<std::endl;
  std::cout<<"areaREm23_B: "<<areaREm23_B<<std::endl;
  std::cout<<"areaREm23_M: "<<areaREm23_M<<std::endl;
  std::cout<<"areaREm23_F: "<<areaREm23_F<<std::endl;

  std::cout<<"areaREm32_B: "<<areaREm32_B<<std::endl;
  std::cout<<"areaREm32_M: "<<areaREm32_M<<std::endl;
  std::cout<<"areaREm32_F: "<<areaREm32_F<<std::endl;
  std::cout<<"areaREm33_B: "<<areaREm33_B<<std::endl;
  std::cout<<"areaREm33_M: "<<areaREm33_M<<std::endl;
  std::cout<<"areaREm33_F: "<<areaREm33_F<<std::endl; 

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RateVsLumi_PhiEtaRecompute::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Update this part according to the rpc digi analysis
  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RateVsLumi_PhiEtaRecompute);
