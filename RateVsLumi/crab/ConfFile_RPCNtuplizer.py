import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery    = cms.untracked.int32(1) 
process.MessageLogger.cerr.threshold                = cms.untracked.string('DEBUG')
process.MessageLogger.debugModules                  = cms.untracked.vstring()
process.options                                     = cms.untracked.PSet(wantSummary=cms.untracked.bool(False))

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag                         = '124X_dataRun3_Prompt_v4'
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')


process.maxEvents                                   = cms.untracked.PSet(input = cms.untracked.int32(100)) # only local
# process.maxEvents                                   = cms.untracked.PSet(input = cms.untracked.int32(2))
process.source                                      = cms.Source("PoolSource",
                                                                    fileNames = cms.untracked.vstring(
                                                                        # "/store/data/Run2023C/ZeroBias/AOD/PromptReco-v1/000/367/515/00000/f1b0afc9-79cc-42e2-b9ea-c2334255e847.root", # Fill=8754
                                                                        "/store/data/Run2024C/ZeroBias/AOD/PromptReco-v1/000/380/115/00000/132c0550-308e-43c3-b099-3d34a6c33b5c.root", # Fill=9573
                                                                        )
                                                                ) # only local

process.demo                                        = cms.EDAnalyzer('RPCNtuplizer',
                                                                        rpcRecHits_tag      = cms.untracked.InputTag('rpcRecHits'),
                                                                        # scalersResults      = cms.InputTag("scalersRawToDigi"),
                                                                        scalersResults      = cms.InputTag("onlineMetaDataDigis"),
                                                                        # noisy               = cms.string('All_Noisy_strips_ID.txt')
                                                                        noisy               = cms.string('All_Dead_and_Noisy_strips_ID.txt') # USE THIS WHEN RUNNING WITH CRAB
                                                                        # noisy               = cms.string('./noisy_files/Fill_9573/All_Dead_and_Noisy_strips_ID.txt') # only when running on local
                                                                    )

process.TFileService                                = cms.Service("TFileService",
                                                                    fileName       = cms.string('RPCNtuple.root') 
                                                                ) # only local

process.p = cms.Path(process.demo)
