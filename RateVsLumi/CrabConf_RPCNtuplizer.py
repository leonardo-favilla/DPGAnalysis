# from CRABClient.UserUtilities import config, getUsernameFromCRIC
from WMCore.Configuration import Configuration

# config = config()
config = Configuration()

config.section_("General")
config.General.requestName   = 'ZB_RPCNtuplizer'
config.General.transferLogs = True
config.General.transferOutputs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'ConfFile_RPCNtuplizer.py'
config.JobType.inputFiles = ['All_Noisy_strips_ID.txt']
config.JobType.outputFiles = ['RPCNtuple.root']
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDBS = 'global' #'phys03'
config.Data.inputDataset = '/ZeroBias/Run2023C-PromptReco-v1/AOD' #'/ZeroBias/Run2023C-v1/RAW'#'/ZeroBias/Run2022D-PromptReco-v2/AOD'
#'/ZeroBias/Run2018D-PromptReco-v2/AOD'
#'/ZeroBias/dpg_rpc-zerobias_rpcRechits_FLTR-610a4611d89c65a564c7be1b47d3bb6c/USER'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/lfavilla/'
config.Data.publication = False
config.Data.outputDatasetTag = 'ZB_RPCNtuplizer'
#config.Data.lumiMask = 'json_2022_Scheme8149.txt'  
#config.Data.lumiMask = 'json_2022_Scheme8148.txt'
config.Data.lumiMask = 'json_2023_Scheme8754.txt'

config.section_("Site")
config.Site.storageSite = 'T2_IT_Pisa'
#config.Site.whitelist = ['T2_FR_IPHC']
