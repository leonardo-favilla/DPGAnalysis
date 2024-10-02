import ROOT


###### Retrieve histograms saved into a .root file ######
def loadHists(histFile):
    f           = ROOT.TFile(histFile, "READ")
    histList    = {}
    keyList     = f.GetListOfKeys()
    for key in keyList:
        hist    = f.Get(key.GetName())
        if (type(hist) == ROOT.TH1F) or (type(hist) == ROOT.TH2F):
            hist.SetDirectory(ROOT.gROOT)
        # hist.SetName(key.GetName())
        histList[key.GetName()]=hist
    if len(histList)==0: 
        raise Exception("ERROR: histList is empty!")
    f.Close()
    return histList