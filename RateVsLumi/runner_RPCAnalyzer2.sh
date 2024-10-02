#!/usr/bin/bash
cd /afs/cern.ch/user/l/lfavilla/CMSSW_13_0_5_patch1/src/DPGAnalysis/RateVsLumi
eval 'scramv1 runtime -sh'
cmsenv
python3 RPCAnalyzer2.py 0 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_10.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_89.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_66.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_74.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_92.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_37.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_64.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_49.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_73.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_53.root] colliding_8754.txt
python3 RPCAnalyzer2.py 1 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_87.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_56.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_58.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_79.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_34.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_68.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_86.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_76.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_50.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_99.root] colliding_8754.txt
python3 RPCAnalyzer2.py 2 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_78.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_93.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_75.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_96.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_52.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_43.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_36.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_67.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_33.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_54.root] colliding_8754.txt
python3 RPCAnalyzer2.py 3 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_90.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_91.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_69.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_80.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_46.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_81.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_35.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_1.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_94.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_65.root] colliding_8754.txt
python3 RPCAnalyzer2.py 4 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_71.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_59.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_88.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_63.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_97.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_60.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_32.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_77.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_14.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_2.root] colliding_8754.txt
python3 RPCAnalyzer2.py 5 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_20.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_44.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_51.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_9.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_8.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_70.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_72.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_98.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_40.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_45.root] colliding_8754.txt
python3 RPCAnalyzer2.py 6 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_4.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_3.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_100.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_5.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_28.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_23.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_11.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_18.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_42.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_39.root] colliding_8754.txt
python3 RPCAnalyzer2.py 7 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_21.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_61.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_19.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_47.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_26.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_85.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_62.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_57.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_7.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_13.root] colliding_8754.txt
python3 RPCAnalyzer2.py 8 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_6.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_83.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_29.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_22.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_82.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_84.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_16.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_95.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_55.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_17.root] colliding_8754.txt
python3 RPCAnalyzer2.py 9 [root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_31.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_15.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_41.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_25.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_38.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_12.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_48.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_24.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_30.root,root://cms-xrd-global.cern.ch//store/user/lfavilla/ZeroBias/ZB_RPCNtuplizer/240321_093138/0000/RPCNtuple_27.root] colliding_8754.txt
