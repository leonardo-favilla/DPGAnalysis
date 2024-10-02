#!/usr/bin/bash
cd /afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi/analyzer
eval 'scramv1 runtime -sh'
cmsenv
python3 RPCAnalyzer.py 9 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_76.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_1.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_85.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_58.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_63.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_59.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_28.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_84.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_33.root] /afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi/fill_schemes/Fill_9573/colliding_9573.txt /eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573
