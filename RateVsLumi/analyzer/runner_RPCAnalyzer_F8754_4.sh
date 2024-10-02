#!/usr/bin/bash
cd /afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi/analyzer
eval 'scramv1 runtime -sh'
cmsenv
python3 RPCAnalyzer.py 4 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_71.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_59.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_88.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_63.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_97.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_60.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_32.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_77.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_14.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_2.root] /afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi/fill_schemes/Fill_8754/colliding_8754.txt /eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754
