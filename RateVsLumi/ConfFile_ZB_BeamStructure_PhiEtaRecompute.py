

import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.MessageLogger.cerr.threshold = cms.untracked.string('DEBUG')
process.MessageLogger.debugModules = cms.untracked.vstring()
process.options = cms.untracked.PSet( wantSummary=cms.untracked.bool(False))

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')                                                                    
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '124X_dataRun3_Prompt_v4'
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000))
process.source = cms.Source("PoolSource",

    fileNames = cms.untracked.vstring(#'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D580E361-B379-744F-B1E9-4F6041EC5FD7.root',  \
                                                                                                                                                        
                                      #'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D44A8FA4-672F-5549-84AC-6ECB68C2A098.root',  \
                                                                                                                                                        
                                      #'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/495DD4C5-9D8F-0B43-B0B9-4E34D455807F.root',  \
                                                                                                                                                        
                                      #'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1EF2E7F0-7170-AB49-8092-335AAFD06647.root',   
                                      #'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/CCE657B8-B293-D943-A566-BE5D384E41C5.root',   
                                      #'/store/data/Run2022A/ZeroBias/AOD/PromptReco-v1/000/354/507/00000/d1a5b8b4-6f66-41bf-b74e-4c751580d68a.root',   

'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/a2550a8c-63c1-41f3-9219-70b8994cce93.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/a2c040eb-29ff-4b1d-85cb-e42a040af5b5.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/a7bc34d5-6e28-4dda-b7eb-f079f41fb287.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/ab4be52e-fb9a-459d-ac8d-cc57c39c4f7b.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/ab5548ad-97c1-464c-9a0c-020eb66007f9.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/abb89e43-d249-4a19-8a8d-40b75f011663.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/abe9b493-4826-41c2-9e22-de3ceff31b1d.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/ae27786a-2243-48a3-b3d4-8b6832c93ea7.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/b30b6cc5-64c6-42de-a787-bde29aa6b0b8.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/b3cb5517-1ac6-471d-861b-454758657f37.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/b8930948-e9e9-43e0-92c8-bb1cd2533975.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/b8b37b5e-1c20-4f1c-8fa4-c3e275ec3016.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/b8d7a4bf-cd62-4879-b498-23b712610f3c.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/b8e424cf-2b29-4cae-8ba7-17039d53710a.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/ba57abd2-e359-4b94-8351-277d3c33b617.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/bcafbe07-9a07-4a78-bdd3-09a99af05366.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/c208a523-b00a-4194-8c6b-acdd1df7eae0.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/c379d418-d844-4bd7-9cba-809a7240fe11.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/c41a339c-fc99-4dcb-aab7-5c2597fb0c7f.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/ca462764-22b7-4fd3-94dd-a60e87ebcab4.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/cd8de443-91c3-406f-afee-8e933bcc4cca.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/cea6ce52-ec3f-4fbe-8ada-621e0463abf6.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/d3413f2f-79eb-4f9c-98b6-465d52b48cb3.root',
'/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/d63cd12c-1635-4ac6-aaa4-0022bb0c48bc.root',

                                      '/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/abe9b493-4826-41c2-9e22-de3ceff31b1d.root',
)
)

process.demo = cms.EDAnalyzer('RateVsLumi_PhiEtaRecompute'
     , debug = cms.untracked.bool(False)
     , doAllBXs = cms.untracked.bool(True)	# default is True. If true, please put numbBXs=6, put False if you want to investigate only particular BX window
     , doAllBXno0 = cms.untracked.bool(False)	# run over all the noncentral BX, i.e. all BX!=0
     #, doOnlyOneBX = cms.untracked.bool(True)	# run over one choosen BX, the ID number t be given in bxInvest
     , rpcRecHits_tag=cms.untracked.InputTag('rpcRecHits')                       
     , numbBXs = cms.int32(5)		#default number is 6 bx windows [-2, 3], change this number regarding the mubmer of time windows (BXs) you are investigating
     #, bxInvest = cms.int32(2) 	#put the BX number that you want to investigate, doAllBXs should be set to False and numbBXs to 1. For the default options(i.e. all BX) this parameter will be skipped by the code. 
     , scalersResults = cms.InputTag("onlineMetaDataDigis")
     , doRechits = cms.untracked.bool(True)	# default is True. # If true, the rate is counted from the rpc rechits.
# If False the rate will be counted from digis (belonging to the rechits,
# i.e. raw digis not entered in the reconstrcutions will not be counted)
# to run over all the digis the input dataformat should be changed.
# Reco format does not contain raw digis
     , myBlackList = cms.string('off_noisy_bar_endcap_new.txt')
     , uncolliding = cms.string('nonColliding_fill8148.txt')
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('rpcRechits_ZB_2022D_PhiEtaRecompute.root') 
)

#process.Tracer = cms.Service("Tracer")
process.p = cms.Path(process.demo)
