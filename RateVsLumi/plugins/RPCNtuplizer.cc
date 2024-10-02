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

class RPCNtuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources>  

{
   public:
      explicit RPCNtuplizer(const edm::ParameterSet&);
      ~RPCNtuplizer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

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
      int RPCbx=-99;


  std::string noisy_;
      int runNum;
      double orbitnumber=0;
      double area=0;
      TTree* hit_tree;
      TTree* event_tree;
      int bx=0;
      int cluSize=0;
      int myFirstStrip=0;
      int lumi=0;
      int region=0;
      int ring=0;
      int sector=0;
      int layer=0;
      int station=0;
      int roll_n=0;
      int subsector=0;
      int real_bunchNum=0;

      int rpcId_raw = 0;
      int colliding_region=0;
      int hit_colliding_region=0;
      int event_colliding_region=0;         
      edm::Service<TFileService> fs;
};

//FIXME mileva
RPCNtuplizer::RPCNtuplizer(const edm::ParameterSet& iConfig)
: rpcGeoToken_(esConsumes())
{
  rpcRecHitsLabel = consumes<RPCRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("rpcRecHits_tag"));
//  scalersSource_ = iConfig.getParameter<edm::InputTag>("scalersResults");
//  scalersSourceToken_ = consumes<LumiScalersCollection>(edm::InputTag(scalersSource_));

//  scalersSourceToken_ = consumes<LumiScalersCollection>(iConfig.getParameter<edm::InputTag>("scalersResults"));
  scalersSourceToken_ = consumes<OnlineLuminosityRecord>(iConfig.getParameter<edm::InputTag>("scalersResults"));
  noisy_ = iConfig.getParameter<std::string>("noisy");
  usesResource("TFileService");
}

RPCNtuplizer::~RPCNtuplizer()
{}

// ------------ method called for each event  ------------
void
RPCNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  fstream noisyStream;
//FIXME  uint32_t myId;
  string myName;
  //std::vector<int> uncolliding;
  int uncollBX;



  //uncollidingStream.open(uncolliding_, ios::in); //map the names and rollIds
   //for (; uncollidingStream >>uncollBX;)
   //{

   //uncolliding.push_back(uncollBX);
   //}
   //uncollidingStream.close();

   //int collision_region[6]={-1}; // default value, 0 Colliding, 1 Non Colliding, 2 PreBeam, 3 BeamAbort 
 

    map<int, vector<int>> dataMap;
    
    // Open the file in read mode
    noisyStream.open(noisy_, ios::in);

    // Check if the file was opened successfully
    if (!noisyStream.is_open()) {
        cerr << "Error opening the file: " << noisy_ << endl;
        return; // Exit the function if there's an error
    }

    // Read the file line-by-line
    string line;
    while (getline(noisyStream, line)) {
        // cout << line << endl;
        istringstream iss(line);
        string element;
        int i = 0;
        int key = 0;
        vector<int> numbers;
        while (getline(iss, element, ',')) {
            if (i==0){
                key = stoi(element);
            }
            else{
                numbers.push_back(stoi(element));
            }
            i++;
            }
        // Insert into the map
        dataMap[key] = numbers;
        // cout << endl;
    }

    // Close the file
    noisyStream.close();
    
    // Print the map
    // for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
    //     cout << "rpcId found:      " << it->first << endl;
    //     cout << "   noisy strips:  ";
    //     for (int i = 0; i < static_cast<int>(it->second.size()); i++) {
    //         cout << it->second[i] << " ";
    //     }
    //     cout << endl;
    // }
  
  using namespace edm;
//area;
//FIXME  double stripArea = 0.0;
 
  
  
//get the luminosity block
  lumiperblock = 0.;
  lumiblock = 0;
  bunchNum = 0;
  bunchCross = 0;
  event =0;

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

//get the event info


  runNum = iEvent.eventAuxiliary().id().run();
  event = iEvent.eventAuxiliary().id().event();
  
  //colliding_region = 0;
  //hit_colliding_region = 0;
  /*
  for(int bx=-2;bx<4;bx++){
    if(bunchNum+bx<62) collision_region[bx+2]=2;
    else if(bunchNum+bx>=3414) collision_region[bx+2]=3;
    else if(std::find(uncolliding.begin(), uncolliding.end(), bunchNum+bx) != uncolliding.end()) collision_region[bx+2]=1;
    else collision_region[bx+2]=0;
    event_colliding_region = collision_region[bx+2];
    real_bunchNum = bunchNum+bx;
    if(bx == 0) {
      event_tree->Fill();
      std::cout<<"Filling event tree only when bx==0"<<std::endl;
    }
  }
  */
  for(int bx=-3;bx<5;bx++){
    real_bunchNum = bunchNum+bx;
    RPCbx=bx;
    event_tree->Fill();

  }
  

  //colliding_region = collision_region[2];



// Get the RPC Geometry
//FIXME mileva
  auto rpcGeom = iSetup.getHandle(rpcGeoToken_);
//  edm::ESHandle<RPCGeometry> rpcGeom = iSetup.getHandle(rpcGeoToken_);
//  edm::ESHandle < RPCGeometry > rpcGeom;
//  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
  Handle<RPCRecHitCollection> rpcHits_handle;
  iEvent.getByToken(rpcRecHitsLabel,rpcHits_handle);

  const std::vector<  const RPCRoll * > rls = rpcGeom->rolls();

  for (int i = 0; i < (int) rls.size() ; ++i) {
    RPCDetId rpcId =  rls[i]->id();
    cout << "rpcId: " << static_cast<int>(rpcId) << endl;
    std::vector<int> noisy_strips = {};
    const RPCRoll* roll = dynamic_cast<const RPCRoll*>(rpcGeom->roll(rpcId));
//FIXME    const int nstrips = roll->nstrips();


    if (dataMap.find(static_cast<int>(rpcId)) != dataMap.end()) {
      // cout << "rpcId: " << static_cast<int>(rpcId) << " has some noisy strips" << endl;
      noisy_strips = dataMap.at(static_cast<int>(rpcId));
      // for (int i = 0; i < static_cast<int>(noisy_strips.size()); i++) {
        // cout << "\tnoisy strip found: " << noisy_strips.at(i) << endl;
      }

    // else {
      // cout << "rpcId: " << static_cast<int>(rpcId) << " has no noisy strips" << endl;
    // }


    // for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
    //   if (static_cast<int>(rpcId)==static_cast<int>(it->first)) {
    //     cout << "rpcId: " << static_cast<int>(rpcId) << " has some noisy strips" << endl;
    //     for (int i = 0; i < static_cast<int>(it->second.size()); i++) {
    //       noisy_strips.push_back(static_cast<int>(it->second[i]));
    //       cout << "\tnoisy strip found: " << noisy_strips.at(i) << endl;
    //     }
    //     break;
    //   }
    //   else {
    //     continue;
    //   }
    // }




    area = 0.0;
//FIXME    float myPitch;
    float xmin = 0.0;
    float xmax = 0.0;
    float striplength;

    if (rpcId.region() == 0)
      {
        const RectangularStripTopology* top_ = dynamic_cast<const RectangularStripTopology*>(&(roll->topology()));
        xmin = (top_->localPosition(0.)).x();
        xmax = (top_->localPosition((float)roll->nstrips())).x();
        striplength = (top_->stripLength());
      }
    else
      {
        const TrapezoidalStripTopology* top_ = dynamic_cast<const TrapezoidalStripTopology*>(&(roll->topology()));
        xmin = (top_->localPosition(0.)).x();
        xmax = (top_->localPosition((float)roll->nstrips())).x();
        striplength = (top_->stripLength());
      }
    


    // if len(noisy_strips) > 80% of the roll, skip the roll and put the area to 0
    if ((float)noisy_strips.size() > 0.8*(float)roll->nstrips()) {
      cout << "\tmore than 80% of the roll is NOISY or DEAD, setting area to 0 and skipping to next rpcId" << endl;
      area = 0.0;
      // cout << "\trpcId: " << static_cast<int>(rpcId) << " has an active area of: " << area  << ", while area was: " << striplength*(xmax-xmin) << endl;
      continue;
    }
  


    area = striplength*(xmax-xmin)*(1-(((float)noisy_strips.size())/((float)roll->nstrips())));
    // cout << "\t(float)roll->nstrips() is:" << (float)roll->nstrips() << endl;
    // cout << "\trpcId: " << static_cast<int>(rpcId) << " has an active area of: " << area  << ", while area was: " << striplength*(xmax-xmin) << endl;

    RPCRecHitCollection::range rpcRecHitRange = rpcHits_handle->get(rpcId);
    RPCRecHitCollection::const_iterator recHit_2itrat;   
    RPCGeomServ RPCname(rpcId);
//    std::string nameRoll = RPCname.name();
//    std::cout << nameRoll << std::endl;
   

    for(recHit_2itrat = rpcRecHitRange.first; recHit_2itrat!=rpcRecHitRange.second; ++recHit_2itrat)
    {
      bool noisyStrip_in_recHit = false;

      cluSize       = recHit_2itrat->clusterSize();    
      bx            = recHit_2itrat->BunchX();
      myFirstStrip  = recHit_2itrat->firstClusterStrip();

      // cout << "\trecHit cluster strips: [" << myFirstStrip << " - " << myFirstStrip+cluSize-1 << "]" << endl;
      region    = rpcId.region();
      ring      = rpcId.ring();
      sector    = rpcId.sector();
      layer     = rpcId.layer();
      station   = rpcId.station();
      roll_n    = rpcId.roll();
      subsector = rpcId.subsector();
      rpcId_raw = rpcId;
      //hit_colliding_region = collision_region[bx+2];

      for (int i = 0; i < static_cast<int>(noisy_strips.size()); i++) {
        if ((noisy_strips.at(i) >= myFirstStrip) && (noisy_strips.at(i) <= myFirstStrip+cluSize-1)) {
          // cout << "\t\tnoisy strip found: " << noisy_strips.at(i) << " in the cluster" << endl;
          noisyStrip_in_recHit = true;
          continue;
        }
      }

      if (noisyStrip_in_recHit) {
        // cout << "\t\tnoisy strip found in the cluster, not filling the tree" << endl;
        continue;
      }
      else {
      hit_tree->Fill();
      }

    }

  }
  cout << "-------------------------------------------------------------" << endl;

}// end RPCNtuplizer:analyzer

// ------------ method called once each job just before starting event loop  ------------
void
RPCNtuplizer::beginJob()
{
  hit_tree = fs->make<TTree>("hit_tree","hit_tree");
  hit_tree->Branch("bunchNum",&bunchNum);
  hit_tree->Branch("runNum",&runNum);
  hit_tree->Branch("eventNum",&event);
  hit_tree->Branch("lumi",&lumi);

  hit_tree->Branch("area",&area);

  hit_tree->Branch("cluSize",&cluSize);
  hit_tree->Branch("RPCbx",&bx);
  hit_tree->Branch("firstClusterStrip",&myFirstStrip);   

  hit_tree->Branch("region",&region);
  hit_tree->Branch("ring",&ring);
  hit_tree->Branch("sector",&sector);
  hit_tree->Branch("layer",&layer);
  hit_tree->Branch("station",&station);
  hit_tree->Branch("roll",&roll_n);
  hit_tree->Branch("subsector",&subsector);
  hit_tree->Branch("RPC_Id",&rpcId_raw);

  //hit_tree->Branch("colliding_region",&colliding_region);
  //hit_tree->Branch("hit_colliding_region",&hit_colliding_region);

  event_tree = fs->make<TTree>("event_tree","event_tree");
  event_tree->Branch("real_bunchNum",&real_bunchNum);
  event_tree->Branch("RPCbx",&RPCbx);
  event_tree->Branch("runNum",&runNum);
  event_tree->Branch("eventNum",&event);
  event_tree->Branch("lumi",&lumi);

  //event_tree->Branch("event_colliding_region",&event_colliding_region); 
}

// ------------ method called once each job just after ending the event loop  ------------
void
RPCNtuplizer::endJob()
{
 

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RPCNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCNtuplizer);
