#!/usr/bin/bash
cd /afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi/analyzer
eval 'scramv1 runtime -sh'
cmsenv
python3 RPCAnalyzer.py 0 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_43.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_64.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_60.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_88.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_47.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_31.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_50.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_8.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer_F9573/240623_091954/0000/RPCNtuple_80.root] /afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi/fill_schemes/Fill_9573/colliding_9573.txt /eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573
