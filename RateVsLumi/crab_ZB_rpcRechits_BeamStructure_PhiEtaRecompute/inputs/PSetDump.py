import FWCore.ParameterSet.Config as cms
from HeterogeneousCore.CUDACore.SwitchProducerCUDA import SwitchProducerCUDA

process = cms.Process("Demo")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
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
        '/store/data/Run2022D/ZeroBias/AOD/PromptReco-v2/000/357/815/00000/abe9b493-4826-41c2-9e22-de3ceff31b1d.root'
    )
)
process.CondDB = cms.PSet(
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        connectionTimeout = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    connect = cms.string('')
)

process.HFRecalParameterBlock = cms.PSet(
    HFdepthOneParameterA = cms.vdouble(
        0.004123, 0.00602, 0.008201, 0.010489, 0.013379,
        0.016997, 0.021464, 0.027371, 0.034195, 0.044807,
        0.058939, 0.125497
    ),
    HFdepthOneParameterB = cms.vdouble(
        -4e-06, -2e-06, 0.0, 4e-06, 1.5e-05,
        2.6e-05, 6.3e-05, 8.4e-05, 0.00016, 0.000107,
        0.000425, 0.000209
    ),
    HFdepthTwoParameterA = cms.vdouble(
        0.002861, 0.004168, 0.0064, 0.008388, 0.011601,
        0.014425, 0.018633, 0.023232, 0.028274, 0.035447,
        0.051579, 0.086593
    ),
    HFdepthTwoParameterB = cms.vdouble(
        -2e-06, -0.0, -7e-06, -6e-06, -2e-06,
        1e-06, 1.9e-05, 3.1e-05, 6.7e-05, 1.2e-05,
        0.000157, -3e-06
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

process.maxLuminosityBlocks = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.nanoDQMIO_perLSoutput = cms.PSet(
    MEsToSave = cms.untracked.vstring(
        'DT/02-Segments/03-MeanT0/T0MeanAllWheels',
        'EcalBarrel/EBOccupancyTask/EBOT digi occupancy',
        'EcalEndcap/EEOccupancyTask/EEOT digi occupancy EE -',
        'EcalEndcap/EEOccupancyTask/EEOT digi occupancy EE +',
        'Muons/MuonRecoAnalyzer/',
        'Muons/MuonIdDQM/GlobalMuons/',
        'PixelPhase1/Phase1_MechanicalView/',
        'PixelPhase1/Tracks/',
        'SiStrip/MechanicalView/',
        'Tracking/PrimaryVertices/highPurityTracks/pt_0to1/offline/',
        'Tracking/TrackParameters/generalTracks/LSanalysis/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/LSanalysis/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/LSanalysis/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/LSanalysis/',
        'Tracking/TrackParameters/generalTracks/GeneralProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/GeneralProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/GeneralProperties/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/GeneralProperties/',
        'Tracking/TrackParameters/generalTracks/HitProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/HitProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/HitProperties/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/',
        'Tracking/TrackParameters/generalTracks/HitProperties/Pixel/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/HitProperties/Pixel/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/HitProperties/Pixel/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/Pixel/',
        'Tracking/TrackParameters/generalTracks/HitProperties/Strip/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/HitProperties/Strip/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/HitProperties/Strip/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/Strip/'
    )
)

process.options = cms.untracked.PSet(
    FailPath = cms.untracked.vstring(),
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    SkipEvent = cms.untracked.vstring(),
    accelerators = cms.untracked.vstring('*'),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(0)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    makeTriggerResults = cms.obsolete.untracked.bool,
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(0),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

process.bmtfDigis = cms.EDProducer("L1TRawToDigi",
    FWId = cms.uint32(1),
    FWOverride = cms.bool(False),
    FedIds = cms.vint32(1376, 1377),
    InputLabel = cms.InputTag("rawDataCollector"),
    Setup = cms.string('stage2::BMTFSetup'),
    lenAMC13Header = cms.untracked.int32(8),
    lenAMC13Trailer = cms.untracked.int32(8),
    lenAMCHeader = cms.untracked.int32(8),
    lenAMCTrailer = cms.untracked.int32(0),
    lenSlinkHeader = cms.untracked.int32(8),
    lenSlinkTrailer = cms.untracked.int32(8)
)


process.caloLayer1Digis = cms.EDProducer("L1TRawToDigi",
    CTP7 = cms.untracked.bool(True),
    FWId = cms.uint32(305419896),
    FedIds = cms.vint32(1354, 1356, 1358),
    InputLabel = cms.InputTag("rawDataCollector"),
    Setup = cms.string('stage2::CaloLayer1Setup'),
    debug = cms.untracked.bool(False)
)


process.caloStage1Digis = cms.EDProducer("L1TRawToDigi",
    FedIds = cms.vint32(1352),
    InputLabel = cms.InputTag("rawDataCollector"),
    Setup = cms.string('stage1::CaloSetup')
)


process.caloStage1FinalDigis = cms.EDProducer("L1TPhysicalEtAdder",
    InputCollection = cms.InputTag("caloStage1Digis"),
    InputHFCountsCollection = cms.InputTag("caloStage1Digis","HFBitCounts"),
    InputHFSumsCollection = cms.InputTag("caloStage1Digis","HFRingSums"),
    InputIsoTauCollection = cms.InputTag("caloStage1Digis","isoTaus"),
    InputPreGtJetCollection = cms.InputTag("caloStage1Digis"),
    InputRlxTauCollection = cms.InputTag("caloStage1Digis","rlxTaus")
)


process.caloStage1LegacyFormatDigis = cms.EDProducer("L1TCaloUpgradeToGCTConverter",
    InputCollection = cms.InputTag("caloStage1Digis"),
    InputHFCountsCollection = cms.InputTag("caloStage1Digis","HFBitCounts"),
    InputHFSumsCollection = cms.InputTag("caloStage1Digis","HFRingSums"),
    InputIsoTauCollection = cms.InputTag("caloStage1Digis","isoTaus"),
    InputRlxTauCollection = cms.InputTag("caloStage1Digis","rlxTaus")
)


process.caloStage2Digis = cms.EDProducer("L1TRawToDigi",
    FWId = cms.uint32(0),
    FWOverride = cms.bool(False),
    FedIds = cms.vint32(1360, 1366),
    InputLabel = cms.InputTag("rawDataCollector"),
    Setup = cms.string('stage2::CaloSetup'),
    TMTCheck = cms.bool(True)
)


process.castorDigis = cms.EDProducer("CastorRawToDigi",
    CastorCtdc = cms.bool(False),
    CastorFirstFED = cms.int32(690),
    ComplainEmptyData = cms.untracked.bool(False),
    ExceptionEmptyData = cms.untracked.bool(False),
    ExpectedOrbitMessageTime = cms.int32(-1),
    FEDs = cms.untracked.vint32(690, 691, 692, 693, 722),
    FilterDataQuality = cms.bool(True),
    InputLabel = cms.InputTag("rawDataCollector"),
    UnpackTTP = cms.bool(True),
    UnpackZDC = cms.bool(True),
    UseNominalOrbitMessageTime = cms.bool(True),
    ZDCFirstFED = cms.int32(693),
    firstSample = cms.int32(0),
    lastSample = cms.int32(9),
    silent = cms.untracked.bool(False)
)


process.csctfDigis = cms.EDProducer("CSCTFUnpacker",
    MaxBX = cms.int32(11),
    MinBX = cms.int32(5),
    mappingFile = cms.string(''),
    producer = cms.InputTag("rawDataCollector"),
    slot2sector = cms.vint32(
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0
    ),
    swapME1strips = cms.bool(False)
)


process.ctppsDiamondRawToDigi = cms.EDProducer("TotemVFATRawToDigi",
    RawToDigi = cms.PSet(
        BC_fraction = cms.untracked.double(0.6),
        BC_min = cms.untracked.uint32(10),
        EC_fraction = cms.untracked.double(0.6),
        EC_min = cms.untracked.uint32(10),
        printErrorSummary = cms.untracked.uint32(0),
        printUnknownFrameSummary = cms.untracked.uint32(0),
        testBCMostFrequent = cms.uint32(2),
        testCRC = cms.uint32(0),
        testECMostFrequent = cms.uint32(0),
        testFootprint = cms.uint32(2),
        testID = cms.uint32(2),
        verbosity = cms.untracked.uint32(0)
    ),
    RawUnpacking = cms.PSet(
        verbosity = cms.untracked.uint32(0)
    ),
    fedIds = cms.vuint32(579, 581, 582, 583),
    rawDataTag = cms.InputTag("rawDataCollector"),
    subSystem = cms.string('TimingDiamond')
)


process.ctppsPixelDigis = cms.EDProducer("CTPPSPixelRawToDigi",
    includeErrors = cms.bool(True),
    inputLabel = cms.InputTag("rawDataCollector"),
    isRun3 = cms.bool(True),
    mappingLabel = cms.string('RPix'),
    mightGet = cms.optional.untracked.vstring
)


process.dttfDigis = cms.EDProducer("DTTFFEDReader",
    DTTF_FED_Source = cms.InputTag("rawDataCollector"),
    verbose = cms.untracked.bool(False)
)


process.ecalDigisGPU = cms.EDProducer("EcalRawToDigiGPU",
    FEDs = cms.vint32(
        601, 602, 603, 604, 605,
        606, 607, 608, 609, 610,
        611, 612, 613, 614, 615,
        616, 617, 618, 619, 620,
        621, 622, 623, 624, 625,
        626, 627, 628, 629, 630,
        631, 632, 633, 634, 635,
        636, 637, 638, 639, 640,
        641, 642, 643, 644, 645,
        646, 647, 648, 649, 650,
        651, 652, 653, 654
    ),
    InputLabel = cms.InputTag("rawDataCollector"),
    digisLabelEB = cms.string('ebDigis'),
    digisLabelEE = cms.string('eeDigis'),
    maxChannelsEB = cms.uint32(61200),
    maxChannelsEE = cms.uint32(14648),
    mightGet = cms.optional.untracked.vstring
)


process.ecalPreshowerDigis = cms.EDProducer("ESRawToDigi",
    ESdigiCollection = cms.string(''),
    InstanceES = cms.string(''),
    LookupTable = cms.FileInPath('EventFilter/ESDigiToRaw/data/ES_lookup_table.dat'),
    debugMode = cms.untracked.bool(False),
    mightGet = cms.optional.untracked.vstring,
    sourceTag = cms.InputTag("rawDataCollector")
)


process.emtfStage2Digis = cms.EDProducer("L1TRawToDigi",
    FWId = cms.uint32(0),
    FedIds = cms.vint32(1384, 1385),
    InputLabel = cms.InputTag("rawDataCollector"),
    MTF7 = cms.untracked.bool(True),
    Setup = cms.string('stage2::EMTFSetup'),
    debug = cms.untracked.bool(False)
)


process.gctDigis = cms.EDProducer("GctRawToDigi",
    checkHeaders = cms.untracked.bool(False),
    gctFedId = cms.untracked.int32(745),
    hltMode = cms.bool(False),
    inputLabel = cms.InputTag("rawDataCollector"),
    mightGet = cms.optional.untracked.vstring,
    numberOfGctSamplesToUnpack = cms.uint32(1),
    numberOfRctSamplesToUnpack = cms.uint32(1),
    unpackSharedRegions = cms.bool(False),
    unpackerVersion = cms.uint32(0),
    verbose = cms.untracked.bool(False)
)


process.gmtStage2Digis = cms.EDProducer("L1TRawToDigi",
    FedIds = cms.vint32(1402),
    InputLabel = cms.InputTag("rawDataCollector"),
    Setup = cms.string('stage2::GMTSetup')
)


process.gtDigis = cms.EDProducer("L1GlobalTriggerRawToDigi",
    ActiveBoardsMask = cms.uint32(65535),
    DaqGtFedId = cms.untracked.int32(813),
    DaqGtInputTag = cms.InputTag("rawDataCollector"),
    UnpackBxInEvent = cms.int32(-1),
    Verbosity = cms.untracked.int32(0),
    mightGet = cms.optional.untracked.vstring
)


process.gtEvmDigis = cms.EDProducer("L1GlobalTriggerEvmRawToDigi",
    ActiveBoardsMask = cms.uint32(65535),
    BstLengthBytes = cms.int32(-1),
    EvmGtFedId = cms.untracked.int32(812),
    EvmGtInputTag = cms.InputTag("rawDataCollector"),
    UnpackBxInEvent = cms.int32(-1)
)


process.gtStage2Digis = cms.EDProducer("L1TRawToDigi",
    FedIds = cms.vint32(1404),
    InputLabel = cms.InputTag("rawDataCollector"),
    Setup = cms.string('stage2::GTSetup')
)


process.hcalDigis = cms.EDProducer("HcalRawToDigi",
    ComplainEmptyData = cms.untracked.bool(False),
    ElectronicsMap = cms.string(''),
    ExpectedOrbitMessageTime = cms.untracked.int32(-1),
    FEDs = cms.untracked.vint32(),
    FilterDataQuality = cms.bool(True),
    HcalFirstFED = cms.untracked.int32(700),
    InputLabel = cms.InputTag("rawDataCollector"),
    UnpackCalib = cms.untracked.bool(True),
    UnpackTTP = cms.untracked.bool(True),
    UnpackUMNio = cms.untracked.bool(True),
    UnpackZDC = cms.untracked.bool(True),
    UnpackerMode = cms.untracked.int32(0),
    firstSample = cms.int32(0),
    lastSample = cms.int32(9),
    mightGet = cms.optional.untracked.vstring,
    saveQIE10DataNSamples = cms.untracked.vint32(),
    saveQIE10DataTags = cms.untracked.vstring(),
    saveQIE11DataNSamples = cms.untracked.vint32(),
    saveQIE11DataTags = cms.untracked.vstring(),
    silent = cms.untracked.bool(True)
)


process.hfnoseDigis = cms.EDProducer("HFNoseRawToDigiFake",
    hfnoseDigis = cms.InputTag("simHFNoseUnsuppressedDigis","HFNose"),
    mightGet = cms.optional.untracked.vstring
)


process.hgcalDigis = cms.EDProducer("HGCalRawToDigiFake",
    bhDigis = cms.InputTag("simHGCalUnsuppressedDigis","HEback"),
    eeDigis = cms.InputTag("simHGCalUnsuppressedDigis","EE"),
    fhDigis = cms.InputTag("simHGCalUnsuppressedDigis","HEfront"),
    mightGet = cms.optional.untracked.vstring
)


process.muonCSCDigis = cms.EDProducer("CSCDCCUnpacker",
    B904Setup = cms.untracked.bool(False),
    B904dmb = cms.untracked.int32(3),
    B904vmecrate = cms.untracked.int32(1),
    Debug = cms.untracked.bool(False),
    DisableMappingCheck = cms.untracked.bool(False),
    ErrorMask = cms.uint32(0),
    ExaminerMask = cms.uint32(535558134),
    FormatedEventDump = cms.untracked.bool(False),
    InputObjects = cms.InputTag("rawDataCollector"),
    PrintEventNumber = cms.untracked.bool(False),
    SuppressZeroLCT = cms.untracked.bool(True),
    UnpackStatusDigis = cms.bool(False),
    UseExaminer = cms.bool(True),
    UseFormatStatus = cms.bool(True),
    UseSelectiveUnpacking = cms.bool(True),
    VisualFEDInspect = cms.untracked.bool(False),
    VisualFEDShort = cms.untracked.bool(False),
    mightGet = cms.optional.untracked.vstring,
    runDQM = cms.untracked.bool(False),
    useCSCShowers = cms.bool(True),
    useGEMs = cms.bool(True),
    useRPCs = cms.bool(False)
)


process.muonDTDigis = cms.EDProducer("DTUnpackingModule",
    dataType = cms.string('DDU'),
    dqmOnly = cms.bool(False),
    fedbyType = cms.optional.bool,
    inputLabel = cms.InputTag("rawDataCollector"),
    maxFEDid = cms.untracked.int32(779),
    mightGet = cms.optional.untracked.vstring,
    minFEDid = cms.untracked.int32(770),
    readOutParameters = cms.PSet(
        debug = cms.untracked.bool(False),
        localDAQ = cms.untracked.bool(False),
        performDataIntegrityMonitor = cms.untracked.bool(False),
        rosParameters = cms.PSet(
            debug = cms.untracked.bool(False),
            localDAQ = cms.untracked.bool(False),
            performDataIntegrityMonitor = cms.untracked.bool(False),
            readDDUIDfromDDU = cms.untracked.bool(True),
            readingDDU = cms.untracked.bool(True),
            writeSC = cms.untracked.bool(True)
        )
    ),
    useStandardFEDid = cms.bool(True)
)


process.muonGEMDigis = cms.EDProducer("GEMRawToDigiModule",
    InputLabel = cms.InputTag("rawDataCollector"),
    fedIdEnd = cms.uint32(1478),
    fedIdStart = cms.uint32(1467),
    ge21Off = cms.bool(False),
    keepDAQStatus = cms.bool(True),
    mightGet = cms.optional.untracked.vstring,
    readMultiBX = cms.bool(False),
    useDBEMap = cms.bool(False)
)


process.muonRPCDigis = cms.EDProducer("RPCUnpackingModule",
    InputLabel = cms.InputTag("rawDataCollector"),
    doSynchro = cms.bool(True),
    mightGet = cms.optional.untracked.vstring
)


process.omtfStage2Digis = cms.EDProducer("OmtfUnpacker",
    inputLabel = cms.InputTag("rawDataCollector"),
    skipRpc = cms.bool(False)
)


process.onlineMetaDataDigis = cms.EDProducer("OnlineMetaDataRawToDigi",
    mightGet = cms.optional.untracked.vstring,
    onlineMetaDataInputLabel = cms.InputTag("rawDataCollector")
)


process.onlineMetaDataRawToDigi = cms.EDProducer("OnlineMetaDataRawToDigi",
    mightGet = cms.optional.untracked.vstring,
    onlineMetaDataInputLabel = cms.InputTag("rawDataCollector")
)


process.randomEngineStateProducer = cms.EDProducer("RandomEngineStateProducer")


process.rpcCPPFRawToDigi = cms.EDProducer("RPCAMCRawToDigi",
    RPCAMCUnpacker = cms.string('RPCCPPFUnpacker'),
    RPCAMCUnpackerSettings = cms.PSet(
        bxMax = cms.int32(2),
        bxMin = cms.int32(-2),
        cppfDaqDelay = cms.int32(0),
        fillAMCCounters = cms.bool(True)
    ),
    calculateCRC = cms.bool(True),
    fillCounters = cms.bool(True),
    inputTag = cms.InputTag("rawDataCollector"),
    mightGet = cms.optional.untracked.vstring
)


process.rpcTwinMuxRawToDigi = cms.EDProducer("RPCTwinMuxRawToDigi",
    bxMax = cms.int32(2),
    bxMin = cms.int32(-2),
    calculateCRC = cms.bool(True),
    fillCounters = cms.bool(True),
    inputTag = cms.InputTag("rawDataCollector"),
    mightGet = cms.optional.untracked.vstring
)


process.scalersRawToDigi = cms.EDProducer("ScalersRawToDigi",
    mightGet = cms.optional.untracked.vstring,
    scalersInputTag = cms.InputTag("rawDataCollector")
)


process.siPixelDigiErrors = cms.EDProducer("SiPixelDigiErrorsFromSoA",
    CablingMapLabel = cms.string(''),
    ErrorList = cms.vint32(29),
    UsePhase1 = cms.bool(False),
    UserErrorList = cms.vint32(40),
    digiErrorSoASrc = cms.InputTag("siPixelDigiErrorsSoA"),
    mightGet = cms.optional.untracked.vstring
)


process.siPixelDigiErrorsSoA = cms.EDProducer("SiPixelDigiErrorsSoAFromCUDA",
    mightGet = cms.optional.untracked.vstring,
    src = cms.InputTag("siPixelClustersPreSplittingCUDA")
)


process.siPixelDigisSoA = cms.EDProducer("SiPixelDigisSoAFromCUDA",
    mightGet = cms.optional.untracked.vstring,
    src = cms.InputTag("siPixelClustersPreSplittingCUDA")
)


process.siStripDigis = cms.EDProducer("SiStripRawToDigiModule",
    AppendedBytes = cms.int32(0),
    DoAPVEmulatorCheck = cms.bool(False),
    DoAllCorruptBufferChecks = cms.bool(False),
    ErrorThreshold = cms.uint32(7174),
    LegacyUnpacker = cms.bool(False),
    MarkModulesOnMissingFeds = cms.bool(True),
    ProductLabel = cms.InputTag("rawDataCollector"),
    TriggerFedId = cms.int32(0),
    UnpackBadChannels = cms.bool(False),
    UnpackCommonModeValues = cms.bool(False),
    UseDaqRegister = cms.bool(False),
    UseFedKey = cms.bool(False)
)


process.simEcalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
    BarrelOnly = cms.bool(False),
    Debug = cms.bool(False),
    Famos = cms.bool(False),
    InstanceEB = cms.string(''),
    InstanceEE = cms.string(''),
    Label = cms.string('simEcalUnsuppressedDigis'),
    TcpOutput = cms.bool(False),
    binOfMaximum = cms.int32(6)
)


process.tcdsDigis = cms.EDProducer("TcdsRawToDigi",
    InputLabel = cms.InputTag("rawDataCollector"),
    mightGet = cms.optional.untracked.vstring
)


process.tcdsRawToDigi = cms.EDProducer("TcdsRawToDigi",
    InputLabel = cms.InputTag("rawDataCollector"),
    mightGet = cms.optional.untracked.vstring
)


process.totemRPRawToDigi = cms.EDProducer("TotemVFATRawToDigi",
    RawToDigi = cms.PSet(
        BC_fraction = cms.untracked.double(0.6),
        BC_min = cms.untracked.uint32(10),
        EC_fraction = cms.untracked.double(0.6),
        EC_min = cms.untracked.uint32(10),
        printErrorSummary = cms.untracked.uint32(0),
        printUnknownFrameSummary = cms.untracked.uint32(0),
        testBCMostFrequent = cms.uint32(2),
        testCRC = cms.uint32(2),
        testECMostFrequent = cms.uint32(2),
        testFootprint = cms.uint32(2),
        testID = cms.uint32(2),
        verbosity = cms.untracked.uint32(0)
    ),
    RawUnpacking = cms.PSet(
        verbosity = cms.untracked.uint32(0)
    ),
    fedIds = cms.vuint32(578, 580, 584, 585),
    rawDataTag = cms.InputTag("rawDataCollector"),
    subSystem = cms.string('TrackingStrip')
)


process.totemTimingRawToDigi = cms.EDProducer("TotemVFATRawToDigi",
    RawToDigi = cms.PSet(
        printErrorSummary = cms.untracked.uint32(0),
        printUnknownFrameSummary = cms.untracked.uint32(0),
        testBCMostFrequent = cms.uint32(0),
        testCRC = cms.uint32(0),
        testECMostFrequent = cms.uint32(0),
        testFootprint = cms.uint32(0),
        testID = cms.uint32(0),
        verbosity = cms.untracked.uint32(0)
    ),
    RawUnpacking = cms.PSet(
        verbosity = cms.untracked.uint32(0)
    ),
    fedIds = cms.vuint32(586, 587),
    rawDataTag = cms.InputTag("rawDataCollector"),
    subSystem = cms.string('TotemTiming')
)


process.totemTriggerRawToDigi = cms.EDProducer("TotemTriggerRawToDigi",
    fedId = cms.uint32(0),
    rawDataTag = cms.InputTag("rawDataCollector")
)


process.twinMuxStage2Digis = cms.EDProducer("L1TTwinMuxRawToDigi",
    DTTM7_FED_Source = cms.InputTag("rawDataCollector"),
    amcsecmap = cms.untracked.vint64(20015998343868, 20015998343868, 20015998343868, 20015998343868, 20015998343868),
    debug = cms.untracked.bool(False),
    feds = cms.untracked.vint32(1395, 1391, 1390, 1393, 1394),
    wheels = cms.untracked.vint32(-2, -1, 0, 1, 2)
)


process.ecalDigis = SwitchProducerCUDA(
    cpu = cms.EDProducer("EcalRawToDigi",
        DoRegional = cms.bool(False),
        FEDs = cms.vint32(
            601, 602, 603, 604, 605,
            606, 607, 608, 609, 610,
            611, 612, 613, 614, 615,
            616, 617, 618, 619, 620,
            621, 622, 623, 624, 625,
            626, 627, 628, 629, 630,
            631, 632, 633, 634, 635,
            636, 637, 638, 639, 640,
            641, 642, 643, 644, 645,
            646, 647, 648, 649, 650,
            651, 652, 653, 654
        ),
        FedLabel = cms.InputTag("listfeds"),
        InputLabel = cms.InputTag("rawDataCollector"),
        eventPut = cms.bool(True),
        feIdCheck = cms.bool(True),
        feUnpacking = cms.bool(True),
        forceToKeepFRData = cms.bool(False),
        headerUnpacking = cms.bool(True),
        memUnpacking = cms.bool(True),
        mightGet = cms.optional.untracked.vstring,
        numbTriggerTSamples = cms.int32(1),
        numbXtalTSamples = cms.int32(10),
        orderedDCCIdList = cms.vint32(
            1, 2, 3, 4, 5,
            6, 7, 8, 9, 10,
            11, 12, 13, 14, 15,
            16, 17, 18, 19, 20,
            21, 22, 23, 24, 25,
            26, 27, 28, 29, 30,
            31, 32, 33, 34, 35,
            36, 37, 38, 39, 40,
            41, 42, 43, 44, 45,
            46, 47, 48, 49, 50,
            51, 52, 53, 54
        ),
        orderedFedList = cms.vint32(
            601, 602, 603, 604, 605,
            606, 607, 608, 609, 610,
            611, 612, 613, 614, 615,
            616, 617, 618, 619, 620,
            621, 622, 623, 624, 625,
            626, 627, 628, 629, 630,
            631, 632, 633, 634, 635,
            636, 637, 638, 639, 640,
            641, 642, 643, 644, 645,
            646, 647, 648, 649, 650,
            651, 652, 653, 654
        ),
        silentMode = cms.untracked.bool(True),
        srpUnpacking = cms.bool(True),
        syncCheck = cms.bool(True),
        tccUnpacking = cms.bool(True)
    )
)


process.siPixelDigis = SwitchProducerCUDA(
    cpu = cms.EDProducer("SiPixelRawToDigi",
        CablingMapLabel = cms.string(''),
        ErrorList = cms.vint32(29),
        IncludeErrors = cms.bool(True),
        InputLabel = cms.InputTag("rawDataCollector"),
        Regions = cms.PSet(
            beamSpot = cms.optional.InputTag,
            deltaPhi = cms.optional.vdouble,
            inputs = cms.optional.VInputTag,
            maxZ = cms.optional.vdouble
        ),
        SiPixelQualityLabel = cms.string(''),
        UsePhase1 = cms.bool(False),
        UsePilotBlade = cms.bool(False),
        UseQualityInfo = cms.bool(False),
        UserErrorList = cms.vint32(40),
        mightGet = cms.optional.untracked.vstring
    )
)


process.demo = cms.EDAnalyzer("RateVsLumi_PhiEtaRecompute",
    debug = cms.untracked.bool(False),
    doAllBXno0 = cms.untracked.bool(False),
    doAllBXs = cms.untracked.bool(True),
    doRechits = cms.untracked.bool(True),
    myBlackList = cms.string('off_noisy_bar_endcap_new.txt'),
    numbBXs = cms.int32(5),
    rpcRecHits_tag = cms.untracked.InputTag("rpcRecHits"),
    scalersResults = cms.InputTag("onlineMetaDataDigis"),
    uncolliding = cms.string('nonColliding_fill8148.txt')
)


process.DQMStore = cms.Service("DQMStore",
    MEsToSave = cms.untracked.vstring(
        'DT/02-Segments/03-MeanT0/T0MeanAllWheels',
        'EcalBarrel/EBOccupancyTask/EBOT digi occupancy',
        'EcalEndcap/EEOccupancyTask/EEOT digi occupancy EE -',
        'EcalEndcap/EEOccupancyTask/EEOT digi occupancy EE +',
        'Muons/MuonRecoAnalyzer/',
        'Muons/MuonIdDQM/GlobalMuons/',
        'PixelPhase1/Phase1_MechanicalView/',
        'PixelPhase1/Tracks/',
        'SiStrip/MechanicalView/',
        'Tracking/PrimaryVertices/highPurityTracks/pt_0to1/offline/',
        'Tracking/TrackParameters/generalTracks/LSanalysis/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/LSanalysis/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/LSanalysis/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/LSanalysis/',
        'Tracking/TrackParameters/generalTracks/GeneralProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/GeneralProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/GeneralProperties/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/GeneralProperties/',
        'Tracking/TrackParameters/generalTracks/HitProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/HitProperties/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/HitProperties/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/',
        'Tracking/TrackParameters/generalTracks/HitProperties/Pixel/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/HitProperties/Pixel/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/HitProperties/Pixel/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/Pixel/',
        'Tracking/TrackParameters/generalTracks/HitProperties/Strip/',
        'Tracking/TrackParameters/highPurityTracks/pt_1/HitProperties/Strip/',
        'Tracking/TrackParameters/highPurityTracks/pt_0to1/HitProperties/Strip/',
        'Tracking/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/Strip/'
    ),
    assertLegacySafe = cms.untracked.bool(False),
    enableMultiThread = cms.untracked.bool(True),
    saveByLumi = cms.untracked.bool(False),
    trackME = cms.untracked.string(''),
    verbose = cms.untracked.int32(0)
)


process.MessageLogger = cms.Service("MessageLogger",
    cerr = cms.untracked.PSet(
        FwkReport = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            reportEvery = cms.untracked.int32(1)
        ),
        FwkSummary = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            reportEvery = cms.untracked.int32(1)
        ),
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        enable = cms.untracked.bool(True),
        enableStatistics = cms.untracked.bool(True),
        lineLength = cms.optional.untracked.int32,
        noLineBreaks = cms.optional.untracked.bool,
        noTimeStamps = cms.untracked.bool(False),
        resetStatistics = cms.untracked.bool(False),
        statisticsThreshold = cms.untracked.string('WARNING'),
        threshold = cms.untracked.string('DEBUG'),
        allowAnyLabel_=cms.optional.untracked.PSetTemplate(
            limit = cms.optional.untracked.int32,
            reportEvery = cms.untracked.int32(1),
            timespan = cms.optional.untracked.int32
        )
    ),
    cout = cms.untracked.PSet(
        enable = cms.untracked.bool(False),
        enableStatistics = cms.untracked.bool(False),
        lineLength = cms.optional.untracked.int32,
        noLineBreaks = cms.optional.untracked.bool,
        noTimeStamps = cms.optional.untracked.bool,
        resetStatistics = cms.untracked.bool(False),
        statisticsThreshold = cms.optional.untracked.string,
        threshold = cms.optional.untracked.string,
        allowAnyLabel_=cms.optional.untracked.PSetTemplate(
            limit = cms.optional.untracked.int32,
            reportEvery = cms.untracked.int32(1),
            timespan = cms.optional.untracked.int32
        )
    ),
    debugModules = cms.untracked.vstring(),
    default = cms.untracked.PSet(
        limit = cms.optional.untracked.int32,
        lineLength = cms.untracked.int32(80),
        noLineBreaks = cms.untracked.bool(False),
        noTimeStamps = cms.untracked.bool(False),
        reportEvery = cms.untracked.int32(1),
        statisticsThreshold = cms.untracked.string('INFO'),
        threshold = cms.untracked.string('INFO'),
        timespan = cms.optional.untracked.int32,
        allowAnyLabel_=cms.optional.untracked.PSetTemplate(
            limit = cms.optional.untracked.int32,
            reportEvery = cms.untracked.int32(1),
            timespan = cms.optional.untracked.int32
        )
    ),
    files = cms.untracked.PSet(
        allowAnyLabel_=cms.optional.untracked.PSetTemplate(
            enableStatistics = cms.untracked.bool(False),
            extension = cms.optional.untracked.string,
            filename = cms.optional.untracked.string,
            lineLength = cms.optional.untracked.int32,
            noLineBreaks = cms.optional.untracked.bool,
            noTimeStamps = cms.optional.untracked.bool,
            output = cms.optional.untracked.string,
            resetStatistics = cms.untracked.bool(False),
            statisticsThreshold = cms.optional.untracked.string,
            threshold = cms.optional.untracked.string,
            allowAnyLabel_=cms.optional.untracked.PSetTemplate(
                limit = cms.optional.untracked.int32,
                reportEvery = cms.untracked.int32(1),
                timespan = cms.optional.untracked.int32
            )
        )
    ),
    suppressDebug = cms.untracked.vstring(),
    suppressFwkInfo = cms.untracked.vstring(),
    suppressInfo = cms.untracked.vstring(),
    suppressWarning = cms.untracked.vstring(),
    allowAnyLabel_=cms.optional.untracked.PSetTemplate(
        limit = cms.optional.untracked.int32,
        reportEvery = cms.untracked.int32(1),
        timespan = cms.optional.untracked.int32
    )
)


process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    CTPPSFastRecHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1357987)
    ),
    LHCTransport = cms.PSet(
        engineName = cms.untracked.string('TRandom3'),
        initialSeed = cms.untracked.uint32(87654321)
    ),
    MuonSimHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(987346)
    ),
    RPSiDetDigitizer = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(137137)
    ),
    RPixDetDigitizer = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(137137)
    ),
    VtxSmeared = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(98765432)
    ),
    ecalPreshowerRecHit = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(6541321)
    ),
    ecalRecHit = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(654321)
    ),
    externalLHEProducer = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(234567)
    ),
    famosPileUp = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    fastSimProducer = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(13579)
    ),
    fastTrackerRecHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(24680)
    ),
    g4SimHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(11)
    ),
    generator = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(123456789)
    ),
    hbhereco = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(541321)
    ),
    hfreco = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(541321)
    ),
    hiSignal = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(123456789)
    ),
    hiSignalG4SimHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(11)
    ),
    hiSignalLHCTransport = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(88776655)
    ),
    horeco = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(541321)
    ),
    l1ParamMuons = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(6453209)
    ),
    mix = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(12345)
    ),
    mixData = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(12345)
    ),
    mixGenPU = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    mixRecoTracks = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    mixSimCaloHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    paramMuons = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(54525)
    ),
    saveFileName = cms.untracked.string(''),
    simBeamSpotFilter = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(87654321)
    ),
    simMuonCSCDigis = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(11223344)
    ),
    simMuonDTDigis = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1234567)
    ),
    simMuonRPCDigis = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1234567)
    ),
    simSiStripDigiSimLink = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1234567)
    )
)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('rpcRechits_ZB_2022D_PhiEtaRecompute.root')
)


process.CSCGeometryESModule = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    debugV = cms.untracked.bool(False),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.CaloGeometryBuilder = cms.ESProducer("CaloGeometryBuilder",
    SelectedCalos = cms.vstring(
        'HCAL',
        'ZDC',
        'CASTOR',
        'EcalBarrel',
        'EcalEndcap',
        'EcalPreshower',
        'TOWER'
    )
)


process.CaloTopologyBuilder = cms.ESProducer("CaloTopologyBuilder")


process.CaloTowerGeometryFromDBEP = cms.ESProducer("CaloTowerGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.CaloTowerTopologyEP = cms.ESProducer("CaloTowerTopologyEP")


process.CastorDbProducer = cms.ESProducer("CastorDbProducer",
    appendToDataLabel = cms.string('')
)


process.CastorGeometryFromDBEP = cms.ESProducer("CastorGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.DTGeometryESModule = cms.ESProducer("DTGeometryESModule",
    DDDetector = cms.ESInputTag("",""),
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    attribute = cms.string('MuStructure'),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False),
    value = cms.string('MuonBarrelDT')
)


process.EcalBarrelGeometryFromDBEP = cms.ESProducer("EcalBarrelGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalElectronicsMappingBuilder = cms.ESProducer("EcalElectronicsMappingBuilder")


process.EcalEndcapGeometryFromDBEP = cms.ESProducer("EcalEndcapGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalLaserCorrectionService = cms.ESProducer("EcalLaserCorrectionService",
    maxExtrapolationTimeInSec = cms.uint32(0)
)


process.EcalLaserCorrectionServiceMC = cms.ESProducer("EcalLaserCorrectionServiceMC",
    appendToDataLabel = cms.string('')
)


process.EcalPreshowerGeometryFromDBEP = cms.ESProducer("EcalPreshowerGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalTrigTowerConstituentsMapBuilder = cms.ESProducer("EcalTrigTowerConstituentsMapBuilder",
    MapFile = cms.untracked.string('Geometry/EcalMapping/data/EndCap_TTMap.txt')
)


process.GlobalTrackingGeometryESProducer = cms.ESProducer("GlobalTrackingGeometryESProducer")


process.HcalAlignmentEP = cms.ESProducer("HcalAlignmentEP")


process.HcalGeometryFromDBEP = cms.ESProducer("HcalGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.MuonDetLayerGeometryESProducer = cms.ESProducer("MuonDetLayerGeometryESProducer")


process.MuonNumberingInitialization = cms.ESProducer("MuonNumberingInitialization")


process.RPCGeometryESModule = cms.ESProducer("RPCGeometryESModule",
    fromDD4hep = cms.untracked.bool(False),
    fromDDD = cms.untracked.bool(False)
)


process.SiStripRecHitMatcherESProducer = cms.ESProducer("SiStripRecHitMatcherESProducer",
    ComponentName = cms.string('StandardMatcher'),
    NSigmaInside = cms.double(3.0),
    PreFilter = cms.bool(False)
)


process.StripCPEfromTrackAngleESProducer = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('StripCPEfromTrackAngle'),
    ComponentType = cms.string('StripCPEfromTrackAngle'),
    parameters = cms.PSet(
        mLC_P0 = cms.double(-0.326),
        mLC_P1 = cms.double(0.618),
        mLC_P2 = cms.double(0.3),
        mTEC_P0 = cms.double(-1.885),
        mTEC_P1 = cms.double(0.471),
        mTIB_P0 = cms.double(-0.742),
        mTIB_P1 = cms.double(0.202),
        mTID_P0 = cms.double(-1.427),
        mTID_P1 = cms.double(0.433),
        mTOB_P0 = cms.double(-1.026),
        mTOB_P1 = cms.double(0.253),
        maxChgOneMIP = cms.double(6000.0),
        useLegacyError = cms.bool(False)
    )
)


process.TrackerAdditionalParametersPerDet = cms.ESProducer("TrackerAdditionalParametersPerDetESModule",
    appendToDataLabel = cms.string('')
)


process.TrackerRecoGeometryESProducer = cms.ESProducer("TrackerRecoGeometryESProducer",
    usePhase2Stacks = cms.bool(False)
)


process.XMLFromDBSource = cms.ESProducer("XMLIdealGeometryESProducer",
    label = cms.string('Extended'),
    rootDDName = cms.string('cms:OCMS')
)


process.ZdcGeometryFromDBEP = cms.ESProducer("ZdcGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.caloSimulationParameters = cms.ESProducer("CaloSimParametersESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False)
)


process.ctppsBeamParametersFromLHCInfoESSource = cms.ESProducer("CTPPSBeamParametersFromLHCInfoESSource",
    appendToDataLabel = cms.string(''),
    beamDivX45 = cms.double(0.1),
    beamDivX56 = cms.double(0.1),
    beamDivY45 = cms.double(0.1),
    beamDivY56 = cms.double(0.1),
    lhcInfoLabel = cms.string(''),
    vtxOffsetX45 = cms.double(0.01),
    vtxOffsetX56 = cms.double(0.01),
    vtxOffsetY45 = cms.double(0.01),
    vtxOffsetY56 = cms.double(0.01),
    vtxOffsetZ45 = cms.double(0.01),
    vtxOffsetZ56 = cms.double(0.01),
    vtxStddevX = cms.double(0.02),
    vtxStddevY = cms.double(0.02),
    vtxStddevZ = cms.double(0.02)
)


process.ctppsInterpolatedOpticalFunctionsESSource = cms.ESProducer("CTPPSInterpolatedOpticalFunctionsESSource",
    appendToDataLabel = cms.string(''),
    lhcInfoLabel = cms.string(''),
    opticsLabel = cms.string('')
)


process.ecalElectronicsMappingGPUESProducer = cms.ESProducer("EcalElectronicsMappingGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalSimulationParametersEB = cms.ESProducer("EcalSimParametersESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False),
    name = cms.string('EcalHitsEB')
)


process.ecalSimulationParametersEE = cms.ESProducer("EcalSimParametersESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False),
    name = cms.string('EcalHitsEE')
)


process.ecalSimulationParametersES = cms.ESProducer("EcalSimParametersESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False),
    name = cms.string('EcalHitsES')
)


process.fakeForIdealAlignment = cms.ESProducer("FakeAlignmentProducer",
    appendToDataLabel = cms.string('fakeForIdeal')
)


process.hcalDDDRecConstants = cms.ESProducer("HcalDDDRecConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalDDDSimConstants = cms.ESProducer("HcalDDDSimConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalSimulationConstants = cms.ESProducer("HcalSimulationConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalSimulationParameters = cms.ESProducer("HcalSimParametersESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False)
)


process.hcalTopologyIdeal = cms.ESProducer("HcalTopologyIdealEP",
    Exclude = cms.untracked.string(''),
    MergePosition = cms.untracked.bool(False),
    appendToDataLabel = cms.string('')
)


process.hcal_db_producer = cms.ESProducer("HcalDbProducer",
    dump = cms.untracked.vstring(''),
    file = cms.untracked.string('')
)


process.idealForDigiCSCGeometry = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    debugV = cms.untracked.bool(False),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.idealForDigiDTGeometry = cms.ESProducer("DTGeometryESModule",
    DDDetector = cms.ESInputTag("",""),
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    attribute = cms.string('MuStructure'),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False),
    value = cms.string('MuonBarrelDT')
)


process.idealForDigiTrackerGeometry = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    fromDDD = cms.bool(False)
)


process.multipleScatteringParametrisationMakerESProducer = cms.ESProducer("MultipleScatteringParametrisationMakerESProducer",
    appendToDataLabel = cms.string('')
)


process.muonGeometryConstants = cms.ESProducer("MuonGeometryConstantsESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False)
)


process.muonOffsetESProducer = cms.ESProducer("MuonOffsetESProducer",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False),
    names = cms.vstring(
        'MuonCommonNumbering',
        'MuonBarrel',
        'MuonEndcap',
        'MuonBarrelWheels',
        'MuonBarrelStation1',
        'MuonBarrelStation2',
        'MuonBarrelStation3',
        'MuonBarrelStation4',
        'MuonBarrelSuperLayer',
        'MuonBarrelLayer',
        'MuonBarrelWire',
        'MuonRpcPlane1I',
        'MuonRpcPlane1O',
        'MuonRpcPlane2I',
        'MuonRpcPlane2O',
        'MuonRpcPlane3S',
        'MuonRpcPlane4',
        'MuonRpcChamberLeft',
        'MuonRpcChamberMiddle',
        'MuonRpcChamberRight',
        'MuonRpcEndcap1',
        'MuonRpcEndcap2',
        'MuonRpcEndcap3',
        'MuonRpcEndcap4',
        'MuonRpcEndcapSector',
        'MuonRpcEndcapChamberB1',
        'MuonRpcEndcapChamberB2',
        'MuonRpcEndcapChamberB3',
        'MuonRpcEndcapChamberC1',
        'MuonRpcEndcapChamberC2',
        'MuonRpcEndcapChamberC3',
        'MuonRpcEndcapChamberE1',
        'MuonRpcEndcapChamberE2',
        'MuonRpcEndcapChamberE3',
        'MuonRpcEndcapChamberF1',
        'MuonRpcEndcapChamberF2',
        'MuonRpcEndcapChamberF3',
        'MuonEndcapStation1',
        'MuonEndcapStation2',
        'MuonEndcapStation3',
        'MuonEndcapStation4',
        'MuonEndcapSubrings',
        'MuonEndcapSectors',
        'MuonEndcapLayers',
        'MuonEndcapRing1',
        'MuonEndcapRing2',
        'MuonEndcapRing3',
        'MuonEndcapRingA',
        'MuonGEMEndcap',
        'MuonGEMSector',
        'MuonGEMChamber'
    )
)


process.siPixelQualityESProducer = cms.ESProducer("SiPixelQualityESProducer",
    ListOfRecordToMerge = cms.VPSet(
        cms.PSet(
            record = cms.string('SiPixelQualityFromDbRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiPixelDetVOffRcd'),
            tag = cms.string('')
        )
    ),
    siPixelQualityLabel = cms.string('')
)


process.siStripBackPlaneCorrectionDepESProducer = cms.ESProducer("SiStripBackPlaneCorrectionDepESProducer",
    BackPlaneCorrectionDeconvMode = cms.PSet(
        label = cms.untracked.string('deconvolution'),
        record = cms.string('SiStripBackPlaneCorrectionRcd')
    ),
    BackPlaneCorrectionPeakMode = cms.PSet(
        label = cms.untracked.string('peak'),
        record = cms.string('SiStripBackPlaneCorrectionRcd')
    ),
    LatencyRecord = cms.PSet(
        label = cms.untracked.string(''),
        record = cms.string('SiStripLatencyRcd')
    )
)


process.siStripGainESProducer = cms.ESProducer("SiStripGainESProducer",
    APVGain = cms.VPSet(
        cms.PSet(
            Label = cms.untracked.string(''),
            NormalizationFactor = cms.untracked.double(1.0),
            Record = cms.string('SiStripApvGainRcd')
        ),
        cms.PSet(
            Label = cms.untracked.string(''),
            NormalizationFactor = cms.untracked.double(1.0),
            Record = cms.string('SiStripApvGain2Rcd')
        )
    ),
    AutomaticNormalization = cms.bool(False),
    appendToDataLabel = cms.string(''),
    printDebug = cms.untracked.bool(False)
)


process.siStripLorentzAngleDepESProducer = cms.ESProducer("SiStripLorentzAngleDepESProducer",
    LatencyRecord = cms.PSet(
        label = cms.untracked.string(''),
        record = cms.string('SiStripLatencyRcd')
    ),
    LorentzAngleDeconvMode = cms.PSet(
        label = cms.untracked.string('deconvolution'),
        record = cms.string('SiStripLorentzAngleRcd')
    ),
    LorentzAnglePeakMode = cms.PSet(
        label = cms.untracked.string('peak'),
        record = cms.string('SiStripLorentzAngleRcd')
    )
)


process.siStripQualityESProducer = cms.ESProducer("SiStripQualityESProducer",
    ListOfRecordToMerge = cms.VPSet(
        cms.PSet(
            record = cms.string('SiStripDetVOffRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripDetCablingRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('RunInfoRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadChannelRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadFiberRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadModuleRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadStripRcd'),
            tag = cms.string('')
        )
    ),
    PrintDebugOutput = cms.bool(False),
    ReduceGranularity = cms.bool(False),
    ThresholdForReducedGranularity = cms.double(0.3),
    UseEmptyRunInfo = cms.bool(False),
    appendToDataLabel = cms.string('')
)


process.sistripconn = cms.ESProducer("SiStripConnectivity")


process.stripCPEESProducer = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('stripCPE'),
    ComponentType = cms.string('SimpleStripCPE'),
    parameters = cms.PSet(

    )
)


process.trackerGeometryDB = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(False)
)


process.trackerNumberingGeometryDB = cms.ESProducer("TrackerGeometricDetESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False)
)


process.trackerTopology = cms.ESProducer("TrackerTopologyEP",
    appendToDataLabel = cms.string('')
)


process.GlobalTag = cms.ESSource("PoolDBESSource",
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        connectionTimeout = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    DumpStat = cms.untracked.bool(False),
    ReconnectEachRun = cms.untracked.bool(False),
    RefreshAlways = cms.untracked.bool(False),
    RefreshEachRun = cms.untracked.bool(False),
    RefreshOpenIOVs = cms.untracked.bool(False),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
    globaltag = cms.string('124X_dataRun3_Prompt_v4'),
    pfnPostfix = cms.untracked.string(''),
    pfnPrefix = cms.untracked.string(''),
    snapshotTime = cms.string(''),
    toGet = cms.VPSet()
)


process.HcalTimeSlewEP = cms.ESSource("HcalTimeSlewEP",
    appendToDataLabel = cms.string('HBHE'),
    timeSlewParametersM2 = cms.VPSet(
        cms.PSet(
            slope = cms.double(-3.178648),
            tmax = cms.double(16.0),
            tzero = cms.double(23.960177)
        ),
        cms.PSet(
            slope = cms.double(-1.5610227),
            tmax = cms.double(10.0),
            tzero = cms.double(11.977461)
        ),
        cms.PSet(
            slope = cms.double(-1.075824),
            tmax = cms.double(6.25),
            tzero = cms.double(9.109694)
        )
    ),
    timeSlewParametersM3 = cms.VPSet(
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(12.2999),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-2.19142),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(0.0),
            tspar2_siPM = cms.double(0.0)
        ),
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(15.5),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-3.2),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(32.0),
            tspar2_siPM = cms.double(0.0)
        ),
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(12.2999),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-2.19142),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(0.0),
            tspar2_siPM = cms.double(0.0)
        ),
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(12.2999),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-2.19142),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(0.0),
            tspar2_siPM = cms.double(0.0)
        )
    )
)


process.HepPDTESSource = cms.ESSource("HepPDTESSource",
    pdtFileName = cms.FileInPath('SimGeneral/HepPDTESSource/data/pythiaparticle.tbl')
)


process.eegeom = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('EcalMappingRcd')
)


process.es_hardcode = cms.ESSource("HcalHardcodeCalibrations",
    GainWidthsForTrigPrims = cms.bool(False),
    HBRecalibration = cms.bool(False),
    HBmeanenergies = cms.FileInPath('CalibCalorimetry/HcalPlugins/data/meanenergiesHB.txt'),
    HBreCalibCutoff = cms.double(20.0),
    HERecalibration = cms.bool(False),
    HEmeanenergies = cms.FileInPath('CalibCalorimetry/HcalPlugins/data/meanenergiesHE.txt'),
    HEreCalibCutoff = cms.double(20.0),
    HFRecalParameterBlock = cms.PSet(
        HFdepthOneParameterA = cms.vdouble(
            0.004123, 0.00602, 0.008201, 0.010489, 0.013379,
            0.016997, 0.021464, 0.027371, 0.034195, 0.044807,
            0.058939, 0.125497
        ),
        HFdepthOneParameterB = cms.vdouble(
            -4e-06, -2e-06, 0.0, 4e-06, 1.5e-05,
            2.6e-05, 6.3e-05, 8.4e-05, 0.00016, 0.000107,
            0.000425, 0.000209
        ),
        HFdepthTwoParameterA = cms.vdouble(
            0.002861, 0.004168, 0.0064, 0.008388, 0.011601,
            0.014425, 0.018633, 0.023232, 0.028274, 0.035447,
            0.051579, 0.086593
        ),
        HFdepthTwoParameterB = cms.vdouble(
            -2e-06, -0.0, -7e-06, -6e-06, -2e-06,
            1e-06, 1.9e-05, 3.1e-05, 6.7e-05, 1.2e-05,
            0.000157, -3e-06
        )
    ),
    HFRecalibration = cms.bool(False),
    SiPMCharacteristics = cms.VPSet(
        cms.PSet(
            crosstalk = cms.double(0.0),
            nonlin1 = cms.double(1.0),
            nonlin2 = cms.double(0.0),
            nonlin3 = cms.double(0.0),
            pixels = cms.int32(36000)
        ),
        cms.PSet(
            crosstalk = cms.double(0.0),
            nonlin1 = cms.double(1.0),
            nonlin2 = cms.double(0.0),
            nonlin3 = cms.double(0.0),
            pixels = cms.int32(2500)
        ),
        cms.PSet(
            crosstalk = cms.double(0.17),
            nonlin1 = cms.double(1.00985),
            nonlin2 = cms.double(7.84089e-06),
            nonlin3 = cms.double(2.86282e-10),
            pixels = cms.int32(27370)
        ),
        cms.PSet(
            crosstalk = cms.double(0.196),
            nonlin1 = cms.double(1.00546),
            nonlin2 = cms.double(6.40239e-06),
            nonlin3 = cms.double(1.27011e-10),
            pixels = cms.int32(38018)
        ),
        cms.PSet(
            crosstalk = cms.double(0.17),
            nonlin1 = cms.double(1.00985),
            nonlin2 = cms.double(7.84089e-06),
            nonlin3 = cms.double(2.86282e-10),
            pixels = cms.int32(27370)
        ),
        cms.PSet(
            crosstalk = cms.double(0.196),
            nonlin1 = cms.double(1.00546),
            nonlin2 = cms.double(6.40239e-06),
            nonlin3 = cms.double(1.27011e-10),
            pixels = cms.int32(38018)
        ),
        cms.PSet(
            crosstalk = cms.double(0.0),
            nonlin1 = cms.double(1.0),
            nonlin2 = cms.double(0.0),
            nonlin3 = cms.double(0.0),
            pixels = cms.int32(0)
        )
    ),
    hb = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.19),
        gainWidth = cms.vdouble(0.0),
        mcShape = cms.int32(125),
        noiseCorrelation = cms.vdouble(0.0),
        pedestal = cms.double(3.285),
        pedestalWidth = cms.double(0.809),
        photoelectronsToAnalog = cms.double(0.3305),
        qieOffset = cms.vdouble(-0.49, 1.8, 7.2, 37.9),
        qieSlope = cms.vdouble(0.912, 0.917, 0.922, 0.923),
        qieType = cms.int32(0),
        recoShape = cms.int32(105),
        zsThreshold = cms.int32(8)
    ),
    hbUpgrade = cms.PSet(
        darkCurrent = cms.vdouble(0.01, 0.015),
        doRadiationDamage = cms.bool(True),
        gain = cms.vdouble(0.0006252),
        gainWidth = cms.vdouble(0),
        mcShape = cms.int32(206),
        noiseCorrelation = cms.vdouble(0.26, 0.254),
        pedestal = cms.double(17.3),
        pedestalWidth = cms.double(1.5),
        photoelectronsToAnalog = cms.double(40.0),
        qieOffset = cms.vdouble(0.0, 0.0, 0.0, 0.0),
        qieSlope = cms.vdouble(0.05376, 0.05376, 0.05376, 0.05376),
        qieType = cms.int32(2),
        radiationDamage = cms.PSet(
            depVsNeutrons = cms.vdouble(5.543e-10, 8.012e-10),
            depVsTemp = cms.double(0.0631),
            intlumiOffset = cms.double(150),
            intlumiToNeutrons = cms.double(367000000.0),
            temperatureBase = cms.double(20),
            temperatureNew = cms.double(-5)
        ),
        recoShape = cms.int32(208),
        zsThreshold = cms.int32(16)
    ),
    he = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.23),
        gainWidth = cms.vdouble(0),
        mcShape = cms.int32(125),
        noiseCorrelation = cms.vdouble(0.0),
        pedestal = cms.double(3.163),
        pedestalWidth = cms.double(0.9698),
        photoelectronsToAnalog = cms.double(0.3305),
        qieOffset = cms.vdouble(-0.38, 2.0, 7.6, 39.6),
        qieSlope = cms.vdouble(0.912, 0.916, 0.92, 0.922),
        qieType = cms.int32(0),
        recoShape = cms.int32(105),
        zsThreshold = cms.int32(9)
    ),
    heUpgrade = cms.PSet(
        darkCurrent = cms.vdouble(0.01, 0.015),
        doRadiationDamage = cms.bool(True),
        gain = cms.vdouble(0.0006252),
        gainWidth = cms.vdouble(0),
        mcShape = cms.int32(206),
        noiseCorrelation = cms.vdouble(0.26, 0.254),
        pedestal = cms.double(17.3),
        pedestalWidth = cms.double(1.5),
        photoelectronsToAnalog = cms.double(40.0),
        qieOffset = cms.vdouble(0.0, 0.0, 0.0, 0.0),
        qieSlope = cms.vdouble(0.05376, 0.05376, 0.05376, 0.05376),
        qieType = cms.int32(2),
        radiationDamage = cms.PSet(
            depVsNeutrons = cms.vdouble(5.543e-10, 8.012e-10),
            depVsTemp = cms.double(0.0631),
            intlumiOffset = cms.double(75),
            intlumiToNeutrons = cms.double(29200000.0),
            temperatureBase = cms.double(20),
            temperatureNew = cms.double(5)
        ),
        recoShape = cms.int32(208),
        zsThreshold = cms.int32(16)
    ),
    hf = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.14, 0.135),
        gainWidth = cms.vdouble(0.0, 0.0),
        mcShape = cms.int32(301),
        noiseCorrelation = cms.vdouble(0.0),
        pedestal = cms.double(9.354),
        pedestalWidth = cms.double(2.516),
        photoelectronsToAnalog = cms.double(0.0),
        qieOffset = cms.vdouble(-0.87, 1.4, 7.8, -29.6),
        qieSlope = cms.vdouble(0.359, 0.358, 0.36, 0.367),
        qieType = cms.int32(0),
        recoShape = cms.int32(301),
        zsThreshold = cms.int32(-9999)
    ),
    hfUpgrade = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.14, 0.135),
        gainWidth = cms.vdouble(0.0, 0.0),
        mcShape = cms.int32(301),
        noiseCorrelation = cms.vdouble(0.0),
        pedestal = cms.double(13.33),
        pedestalWidth = cms.double(3.33),
        photoelectronsToAnalog = cms.double(0.0),
        qieOffset = cms.vdouble(0.0697, -0.7405, 12.38, -671.9),
        qieSlope = cms.vdouble(0.297, 0.298, 0.298, 0.313),
        qieType = cms.int32(1),
        recoShape = cms.int32(301),
        zsThreshold = cms.int32(-9999)
    ),
    ho = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.006, 0.0087),
        gainWidth = cms.vdouble(0.0, 0.0),
        mcShape = cms.int32(201),
        noiseCorrelation = cms.vdouble(0.0),
        pedestal = cms.double(12.06),
        pedestalWidth = cms.double(0.6285),
        photoelectronsToAnalog = cms.double(4.0),
        qieOffset = cms.vdouble(-0.44, 1.4, 7.1, 38.5),
        qieSlope = cms.vdouble(0.907, 0.915, 0.92, 0.921),
        qieType = cms.int32(0),
        recoShape = cms.int32(201),
        zsThreshold = cms.int32(24)
    ),
    iLumi = cms.double(-1.0),
    killHE = cms.bool(False),
    testHEPlan1 = cms.bool(False),
    testHFQIE10 = cms.bool(False),
    toGet = cms.untracked.vstring('GainWidths'),
    useHBUpgrade = cms.bool(False),
    useHEUpgrade = cms.bool(False),
    useHFUpgrade = cms.bool(False),
    useHOUpgrade = cms.bool(True),
    useIeta18depth1 = cms.bool(True),
    useLayer0Weight = cms.bool(False)
)


process.totemDAQMappingESSourceXML_TimingDiamond = cms.ESSource("TotemDAQMappingESSourceXML",
    configuration = cms.VPSet(
        cms.PSet(
            mappingFileNames = cms.vstring(),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(1, 0, 1, 283819, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_timing_diamond.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(283820, 0, 1, 292520, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_timing_diamond_2017.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(292521, 0, 1, 310000, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_timing_diamond_2018.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(310001, 0, 1, 339999, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_timing_diamond_2022.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(340000, 0, 1, 999999999, 0, 0)
        )
    ),
    sampicSubDetId = cms.uint32(6),
    subSystem = cms.untracked.string('TimingDiamond'),
    verbosity = cms.untracked.uint32(0)
)


process.totemDAQMappingESSourceXML_TotemTiming = cms.ESSource("TotemDAQMappingESSourceXML",
    configuration = cms.VPSet(
        cms.PSet(
            mappingFileNames = cms.vstring(),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(1, 0, 1, 310000, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_totem_timing_2018.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(310001, 0, 1, 339999, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_totem_timing_2022.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(340000, 0, 1, 999999999, 0, 0)
        )
    ),
    sampicSubDetId = cms.uint32(5),
    subSystem = cms.untracked.string('TotemTiming'),
    verbosity = cms.untracked.uint32(0)
)


process.totemDAQMappingESSourceXML_TrackingStrip = cms.ESSource("TotemDAQMappingESSourceXML",
    configuration = cms.VPSet(
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_tracking_strip_2016_to_fill_5288.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(1, 0, 1, 280385, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring(),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(280386, 0, 1, 281600, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_tracking_strip_2016_from_fill_5330.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(281601, 0, 1, 290872, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_tracking_strip_2017.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(290873, 0, 1, 311625, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_tracking_strip_2018.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(311626, 0, 1, 339999, 0, 0)
        ),
        cms.PSet(
            mappingFileNames = cms.vstring('CondFormats/PPSObjects/xml/mapping_tracking_strip_2022.xml'),
            maskFileNames = cms.vstring(),
            validityRange = cms.EventRange(340000, 0, 1, 999999999, 0, 0)
        )
    ),
    sampicSubDetId = cms.uint32(6),
    subSystem = cms.untracked.string('TrackingStrip'),
    verbosity = cms.untracked.uint32(0)
)


process.prefer("es_hardcode")

process.L1TRawToDigi_Legacy = cms.Task(process.csctfDigis, process.dttfDigis, process.gctDigis, process.gtDigis, process.gtEvmDigis)


process.L1TRawToDigi_Stage1 = cms.Task(process.caloStage1Digis, process.caloStage1FinalDigis, process.caloStage1LegacyFormatDigis, process.csctfDigis, process.dttfDigis, process.gctDigis, process.gtDigis)


process.L1TRawToDigi_Stage2 = cms.Task(process.bmtfDigis, process.caloLayer1Digis, process.caloStage2Digis, process.emtfStage2Digis, process.gmtStage2Digis, process.gtStage2Digis, process.omtfStage2Digis, process.rpcCPPFRawToDigi, process.rpcTwinMuxRawToDigi, process.twinMuxStage2Digis)


process.RawToDigiTask_hcalOnly = cms.Task(process.hcalDigis)


process.ctppsRawToDigiTask = cms.Task(process.ctppsDiamondRawToDigi, process.ctppsPixelDigis, process.totemRPRawToDigi, process.totemTimingRawToDigi, process.totemTriggerRawToDigi)


process.ecalDigisTask = cms.Task(process.ecalDigis)


process.siPixelDigisTask = cms.Task(process.siPixelDigis)


process.L1TRawToDigiTask = cms.Task(process.L1TRawToDigi_Legacy)


process.RawToDigiTask = cms.Task(process.L1TRawToDigiTask, process.castorDigis, process.ecalDigisTask, process.ecalPreshowerDigis, process.hcalDigis, process.muonCSCDigis, process.muonDTDigis, process.muonRPCDigis, process.onlineMetaDataDigis, process.scalersRawToDigi, process.siPixelDigisTask, process.siStripDigis, process.tcdsDigis)


process.RawToDigiTask_ecalOnly = cms.Task(process.ecalDigisTask, process.ecalPreshowerDigis, process.scalersRawToDigi)


process.RawToDigiTask_noTk = cms.Task(process.L1TRawToDigiTask, process.castorDigis, process.ecalDigisTask, process.ecalPreshowerDigis, process.hcalDigis, process.muonCSCDigis, process.muonDTDigis, process.muonRPCDigis, process.onlineMetaDataDigis, process.scalersRawToDigi, process.tcdsDigis)


process.RawToDigiTask_pixelOnly = cms.Task(process.scalersRawToDigi, process.siPixelDigisTask)


process.L1TRawToDigi = cms.Sequence(process.L1TRawToDigiTask)


process.RawToDigi = cms.Sequence(process.RawToDigiTask)


process.RawToDigi_ecalOnly = cms.Sequence(process.RawToDigiTask_ecalOnly)


process.RawToDigi_hcalOnly = cms.Sequence(process.RawToDigiTask_hcalOnly)


process.RawToDigi_noTk = cms.Sequence(process.RawToDigiTask_noTk)


process.RawToDigi_pixelOnly = cms.Sequence(process.RawToDigiTask_pixelOnly)


process.ctppsRawToDigi = cms.Sequence(process.ctppsRawToDigiTask)


process.p = cms.Path(process.demo)


