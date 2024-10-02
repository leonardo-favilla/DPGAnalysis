from CRABClient.UserUtilities import config, getUsernameFromCRIC
from WMCore.Configuration import Configuration
#from CRABClient.UserUtilities import config, getUsernameFromCRIC
config = config()

config.section_("General")
config.General.requestName   = 'ZB_rpcRechits_BeamStructure_PhiEtaRecompute'
config.General.transferLogs = True
config.General.transferOutputs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'ConfFile_ZB_BeamStructure_PhiEtaRecompute.py'
config.JobType.inputFiles = ['off_noisy_bar_endcap_new.txt','nonColliding_fill8148.txt']
config.JobType.outputFiles = ['rpcRechits_ZB_2022D_PhiEtaRecompute.root']
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDBS = 'global' #'phys03'
config.Data.inputDataset = '/ZeroBias/Run2022D-PromptReco-v2/AOD'
#'/ZeroBias/dpg_rpc-zerobias_rpcRechits_FLTR-610a4611d89c65a564c7be1b47d3bb6c/USER'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/fcarneva/'
config.Data.publication = False
config.Data.outputDatasetTag = 'ZB_rpcRechits_BeamStructure_PhiEtaRecompute'
config.Data.lumiMask = 'json_2022_Scheme8148.txt'  

config.section_("Site")
config.Site.storageSite = 'T2_IT_Pisa'
#config.Site.whitelist = ['T2_FR_IPHC']
