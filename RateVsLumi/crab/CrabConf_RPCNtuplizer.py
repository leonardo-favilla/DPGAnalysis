# from CRABClient.UserUtilities import config, getUsernameFromCRIC
from WMCore.Configuration import Configuration

# config = config()
config = Configuration()

config.section_("General")
config.General.requestName              = 'ZB_RPCNtuplizer_F9573_dead_and_noisy' # 'ZB_RPCNtuplizer_F<fill_number>
config.General.transferLogs             = True
config.General.transferOutputs          = True

config.section_("JobType")
config.JobType.pluginName               = 'Analysis'
config.JobType.psetName                 = 'ConfFile_RPCNtuplizer.py'
# config.JobType.inputFiles               = ['./noisy_files/Fill_9573/All_Noisy_strips_ID.txt']
config.JobType.inputFiles               = ['./noisy_files/Fill_9573/All_Dead_and_Noisy_strips_ID.txt']
# config.JobType.inputFiles               = ['Empty_Noisy_strips_ID.txt']
config.JobType.outputFiles              = ['RPCNtuple.root']
config.JobType.allowUndistributedCMSSW  = True

config.section_("Data")
config.Data.inputDBS                    = 'global' #'phys03'
# config.Data.inputDataset                = '/ZeroBias/Run2023C-PromptReco-v1/AOD' # Fill=8754 Run3 before NFS
config.Data.inputDataset                = '/ZeroBias/Run2024C-PromptReco-v1/AOD' # Fill=9573 Run3 after NFS
# config.Data.inputDataset                = '/ZeroBias/Run2018C-12Nov2019_UL2018_rsb-v1/AOD' # Fill=6919 Run2

config.Data.splitting                   = 'LumiBased'
config.Data.unitsPerJob                 = 20
config.Data.outLFNDirBase               = '/store/user/lfavilla/'
config.Data.publication                 = False
config.Data.outputDatasetTag            = 'ZB_RPCNtuplizer_F9573_dead_and_noisy' # 'ZB_RPCNtuplizer_F<fill_number>

# config.Data.lumiMask                    = '../golden/Fill_8754/golden_Fill8754.json' # 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions23/Cert_Collisions2023_eraC_367095_368823_Golden.json' # Fill=8754
config.Data.lumiMask                    = '../golden/Fill_9573/golden_Fill9573.json' # 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions24/Cert_Collisions2024_378981_380115_Golden.json' # Fill=9573
# config.Data.lumiMask                    = '../golden/Fill_6919/golden_Fill6919.json' # Fill=6919

config.section_("Site")
config.Site.storageSite                 = 'T2_IT_Pisa'
# config.Site.whitelist                   = ['T2_FR_IPHC']
